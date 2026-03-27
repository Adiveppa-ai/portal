/* Copyright (c) 2020, Oracle and/or its affiliates. */
/*----------------------------------------------------------------------------+
 | MODULE: perflib_package.sql
 |
 | DESCRIPTION:
 |
 | Defines all the Perflib SQL functions and procedures ...
 |
 | INFORMATION:
 |
 | BRM Performance Tuning ...
 |
 | REVISION:
 |
 | $Revision: 1.4 $
 | $Author: ihargrea $
 | $Date: 2020/04/30 14:03:34 $
 +----------------------------------------------------------------------------*/
CREATE OR REPLACE PACKAGE perflib AUTHID CURRENT_USER AS
   /*
    * Flags to control filtering / grouping ... If the flag is set then this
    * data will NOT be present in the report.
    */
   FILTER_FLAG_PROGRAM_NAME   CONSTANT PLS_INTEGER := 1;
   FILTER_FLAG_OBJECT_TYPE    CONSTANT PLS_INTEGER := 2;
   FILTER_FLAG_FILENAME       CONSTANT PLS_INTEGER := 4; /* and line number */
   FILTER_FLAG_FLAGS          CONSTANT PLS_INTEGER := 8;

   /*
    * Procedure to retrieve real-time snapshot data. This allows configurable
    * grouping and will handle the evaluation of the actual counts (as Perflib
    * records RT data as values since startup)
    */
   PROCEDURE get_rt_snapshot(
      i_poid_db     IN NUMBER,
      i_poid_type   IN VARCHAR2,
      i_poid_id0    IN NUMBER,
      i_poid_rev    IN NUMBER,
      i_flags       IN NUMBER,
      o_cv         OUT SYS_REFCURSOR);

   /*
    * Selects data from gv$sql and inserts into Perflib SQL tables.
    */
   PROCEDURE get_sql_snapshot(
      i_schema     IN VARCHAR2);

   /*
    * Purges snapshot data older than X seconds ...
    */
   PROCEDURE purge(
      i_delay      IN NUMBER);

   /*
    * Basic UNIX timestamp to date function ...
    */
   FUNCTION unix_to_date (unix_t IN NUMBER) RETURN DATE;

   FUNCTION date_to_unix (i_date IN DATE) RETURN NUMBER;

   FUNCTION timestamp_to_unix (i_ts IN TIMESTAMP) RETURN NUMBER;

   FUNCTION unix_to_timestamp (unix_t IN NUMBER) RETURN TIMESTAMP;

   /*
    * Get REL summary data ...
    */
   PROCEDURE get_rel_summary(
      i_filename    IN VARCHAR2,   /* Filename filter */
      i_start_t     IN NUMBER,     /* Start cutoff */
      i_end_t       IN NUMBER,     /* End cutoff */
      i_stage       IN VARCHAR2,   /* Stage filter */
      o_cv         OUT SYS_REFCURSOR);

   /*
    * Get REL cumulative data ...
    */
   PROCEDURE get_rel_cumulative(
      i_type       IN VARCHAR2,    /* Service type filter */
      o_cv         OUT SYS_REFCURSOR);

END perflib;
/
show errors;

CREATE OR REPLACE PACKAGE BODY perflib AS

/*
 * Selects data from gv$sql and inserts into Perflib SQL tables. 
 */
PROCEDURE get_sql_snapshot(i_schema IN VARCHAR2)
IS
   v_version VARCHAR2(100) := '1.0';
   v_data VARCHAR2(32000) := '';
   v_line_len NUMBER := 0;
   v_blob_size NUMBER := 0;
   v_chunk_size NUMBER := 0;
   v_poid_id0 NUMBER := 0;
   v_partition_mode NUMBER := 0;
   v_created_t NUMBER := 0;
   v_lob_loc BLOB;
   v_interval INTERVAL DAY(9) TO SECOND(9) := NULL;

   CURSOR sql_cv IS
   SELECT v_version || '~' ||
          sql_id || '~' ||
          TO_CHAR(child_number) || '~' ||
          TO_CHAR(parsing_schema_name) || '~' ||
          TO_CHAR(executions) || '~' ||
          TO_CHAR(cpu_time/1000000) || '~' ||
          TO_CHAR(elapsed_time/1000000) || '~' ||
          TO_CHAR(elapsed_time/executions/1000) || '~' ||
          TO_CHAR(disk_reads) || '~' ||
          TO_CHAR(buffer_gets) || '~' ||
          TO_CHAR(rows_processed) || '~' ||
          TO_CHAR(direct_writes) || '~' ||
          TO_CHAR(parse_calls) || '~' ||
          TO_CHAR(invalidations) || '~' ||
          TO_CHAR(concurrency_wait_time/1000000) || '~' ||
          TO_CHAR(application_wait_time/1000000) || '~' ||
          TO_CHAR(cluster_wait_time/1000000) || '~' ||
          TO_CHAR(user_io_wait_time/1000000) || '~' ||
          TO_CHAR(plsql_exec_time/1000000) || '~' ||
          SUBSTR(sql_text,1,4000) || CHR(10) AS sql_data
     FROM gv$sql
    WHERE executions > 0
      AND parsing_schema_name LIKE UPPER(i_schema);
BEGIN
   /*
    * Get a new poid and created_t ...
    */
   pin_sequence.get_new_poid_id(v_poid_id0, v_partition_mode, '/performance_sql_data', 0);

   v_interval := (SYSTIMESTAMP AT TIME ZONE 'UTC') -
                 (TO_TIMESTAMP_TZ('01/01/1970 0:00', 'DD/MM/YYYY TZH:TZM'));

   v_created_t := ROUND(EXTRACT(DAY FROM v_interval) * 86400 +
                        EXTRACT(HOUR FROM v_interval) * 3600 + 
                        EXTRACT(MINUTE FROM v_interval) * 60 + 
                        EXTRACT(SECOND FROM v_interval));

   /*
    * Insert main rows and retrieve the LOB selector into
    * which we're going to insert ...
    */
   INSERT INTO performance_sql_data_t (
      poid_db, poid_type, poid_id0, poid_rev,
      read_access, write_access, created_t, mod_t,
      account_obj_db, account_obj_type, account_obj_id0, account_obj_rev,
      sql_data_size)
    VALUES (
      1, '/performance_sql_data', v_poid_id0, 1,
      'L', 'L', v_created_t, v_created_t,
      1, '/account', 1, 1,
      0);

   INSERT INTO performance_sql_data_buf (
      obj_id0,
      sql_data_buf
   ) VALUES (
      v_poid_id0,
      EMPTY_BLOB) RETURNING sql_data_buf INTO v_lob_loc;
   
   /*
    * select all the data and add to the BLOB as necessary. For each line,
    * check if it will fit in our current 'chunk'... if not, write the chunk
    * and make this line the new current chunk. If it does, just add this line
    * to the chunk we're maintaining. At the end, just write anything that is
    * left over.
    */
   FOR sql_rec IN sql_cv() LOOP
      v_line_len := LENGTH(sql_rec.sql_data);
      IF (v_chunk_size + v_line_len > 32000) THEN
         DBMS_LOB.WRITE(v_lob_loc, v_chunk_size, v_blob_size+1,
                        UTL_RAW.CAST_TO_RAW(v_data));
         v_blob_size := v_blob_size + v_chunk_size;
         v_data := sql_rec.sql_data;
         v_chunk_size := v_line_len;
      ELSE 
         v_data := v_data || sql_rec.sql_data;
         v_chunk_size := v_chunk_size + v_line_len;
      END IF;
   END LOOP;
   IF (v_chunk_size > 0) THEN
      DBMS_LOB.WRITE(v_lob_loc, v_chunk_size, v_blob_size+1,
                     UTL_RAW.CAST_TO_RAW(v_data));
      v_blob_size := v_blob_size + v_chunk_size;
   END IF;

   /*
    * Finally, update the BLOB size in the BRM table, and commit ...
    */
   UPDATE performance_sql_data_t SET sql_data_size = v_blob_size
    WHERE poid_id0 = v_poid_id0;

   COMMIT;
EXCEPTION WHEN OTHERS THEN
   ROLLBACK;
   RAISE;
END get_sql_snapshot;

/*
 * get_rt_snapshot : Get basic data for real-time snapshot ordered according to time.
 * i_poid_XXX - POID of /performance_snapshot/realtime object
 * i_flags    - filter flags (see FILTER_FLAG_XXX)
 */
PROCEDURE get_rt_snapshot (
   i_poid_db     IN NUMBER,
   i_poid_type   IN VARCHAR2,
   i_poid_id0    IN NUMBER,
   i_poid_rev    IN NUMBER,
   i_flags       IN NUMBER,
   o_cv         OUT SYS_REFCURSOR) IS
BEGIN
   OPEN o_cv FOR
      SELECT function,
             program_name, 
             object_type, 
             filename, 
             line_number, 
             flags, 
             start_t,
             end_t,
             parent_element_id,
             item_level,
             SUM(calls) AS calls,
             SUM(records) AS records,
             SUM(errors) AS errors,
             SUM(cache_elapsed) AS cache_elapsed,
             SUM(cache_count) AS cache_count,
             SUM(total_elapsed) AS total_elapsed,
             SUM(system_cpu_time) AS system_cpu_time,
             SUM(user_cpu_time) AS user_cpu_time
        FROM (SELECT r.function,
                     CASE WHEN BITAND(i_flags, perflib.FILTER_FLAG_PROGRAM_NAME) = perflib.FILTER_FLAG_PROGRAM_NAME
                          THEN NULL
                          ELSE r.program_name
                     END AS program_name,
                     CASE WHEN BITAND(i_flags, perflib.FILTER_FLAG_OBJECT_TYPE) = perflib.FILTER_FLAG_OBJECT_TYPE
                          THEN NULL
                          ELSE r.object_type
                     END AS object_type,
                     CASE WHEN BITAND(i_flags, perflib.FILTER_FLAG_FILENAME) = perflib.FILTER_FLAG_FILENAME
                          THEN NULL
                          ELSE r.filename
                     END AS filename,
                     CASE WHEN BITAND(i_flags, perflib.FILTER_FLAG_FILENAME) = perflib.FILTER_FLAG_FILENAME
                          THEN NULL
                          ELSE r.line_number
                     END AS line_number,
                     CASE WHEN BITAND(i_flags, perflib.FILTER_FLAG_FLAGS) = perflib.FILTER_FLAG_FLAGS
                          THEN NULL
                          ELSE r.flags
                     END AS flags,
                     r.calls,
                     r.records,
                     r.errors,
                     r.cache_elapsed,
                     r.cache_count,
                     r.total_elapsed,
                     r.system_cpu_time,
                     r.user_cpu_time,
                     r.start_t,
                     r.end_t,
                     r.parent_element_id,
                     r.item_level
                FROM (SELECT t.function,
                             t.program_name,
                             t.object_type,
                             t.filename,
                             t.line_number,
                             t.flags,
                             t.this_calls - t.prev_calls AS calls,
                             t.this_records - t.prev_records AS records,
                             t.this_errors - t.prev_errors AS errors,
                             t.this_cache_elapsed - t.prev_cache_elapsed AS cache_elapsed,
                             t.this_cache_count - t.prev_cache_count AS cache_count,
                             t.this_total_elapsed - t.prev_total_elapsed AS total_elapsed,
                             t.this_system_cpu_time - t.prev_system_cpu_time AS system_cpu_time,
                             t.this_user_cpu_time - t.prev_user_cpu_time AS user_cpu_time,
                             t.start_t,
                             t.end_t,
                             t.parent_element_id,
                             t.item_level
                        FROM (SELECT function,
                                     program_name,
                                     object_type,
                                     filename,
                                     line_number,
                                     flags,
                                     LAG(effective_t, 1, 0) OVER (PARTITION BY function, flags, program_name, object_type, filename, line_number
                                                                      ORDER BY function, flags, program_name, object_type, filename, line_number, effective_t) start_t,
                                     effective_t AS end_t,
                                     parent_element_id,
                                     calls AS this_calls,
                                     LAG(calls, 1, 0) OVER (PARTITION BY function, flags, program_name, object_type, filename, line_number
                                                                ORDER BY function, flags, program_name, object_type, filename, line_number, effective_t) prev_calls,
                                     records AS this_records,
                                     LAG(records, 1, 0) OVER (PARTITION BY function, flags, program_name, object_type, filename, line_number
                                                                  ORDER BY function, flags, program_name, object_type, filename, line_number, effective_t) prev_records,
                                     errors AS this_errors,
                                     LAG(errors, 1, 0) OVER (PARTITION BY function, flags, program_name, object_type, filename, line_number
                                                                 ORDER BY function, flags, program_name, object_type, filename, line_number, effective_t) prev_errors,
                                     cache_elapsed AS this_cache_elapsed,
                                     LAG(cache_elapsed, 1, 0) OVER (PARTITION BY function, flags, program_name, object_type, filename, line_number
                                                                        ORDER BY function, flags, program_name, object_type, filename, line_number, effective_t) prev_cache_elapsed,
                                     cache_count AS this_cache_count,
                                     LAG(cache_count, 1, 0) OVER (PARTITION BY function, flags, program_name, object_type, filename, line_number
                                                                      ORDER BY function, flags, program_name, object_type, filename, line_number, effective_t) prev_cache_count,
                                     total_elapsed AS this_total_elapsed,
                                     LAG(total_elapsed, 1, 0) OVER (PARTITION BY function, flags, program_name, object_type, filename, line_number
                                                                        ORDER BY function, flags, program_name, object_type, filename, line_number, effective_t) prev_total_elapsed,
                                     system_cpu_time AS this_system_cpu_time,
                                     LAG(system_cpu_time, 1, 0) OVER (PARTITION BY function, flags, program_name, object_type, filename, line_number
                                                                          ORDER BY function, flags, program_name, object_type, filename, line_number, effective_t) prev_system_cpu_time,
                                     user_cpu_time AS this_user_cpu_time,
                                     LAG(user_cpu_time, 1, 0) OVER (PARTITION BY function, flags, program_name, object_type, filename, line_number
                                                                        ORDER BY function, flags, program_name, object_type, filename, line_number, effective_t) prev_user_cpu_time,
                                     item_level
                                FROM performance_results_t
                               WHERE obj_id0 = i_poid_id0) t) r)
    GROUP BY function, flags, program_name, object_type, filename, line_number, start_t, end_t, parent_element_id, item_level
    ORDER BY end_t, total_elapsed desc;
END get_rt_snapshot;

/*
 * purge : Removes snapshot data that is older than X seconds ...
 * i_delay - Delay in seconds ...
 */
PROCEDURE purge (
   i_delay     IN NUMBER)
IS
   CURSOR snap_cv(i_cutoff NUMBER) IS
         SELECT p.poid_id0, p.poid_type
           FROM performance_snapshot_t p
          WHERE p.end_t < i_cutoff
      UNION ALL
         SELECT psd.poid_id0, psd.poid_type
           FROM performance_sql_data_t psd
          WHERE psd.created_t < i_cutoff;
   v_cutoff  NUMBER := 0;
   v_interval INTERVAL DAY(9) TO SECOND(9) := NULL;
BEGIN
   v_interval := (SYSTIMESTAMP AT TIME ZONE 'UTC') -
                 (TO_TIMESTAMP_TZ('01/01/1970 0:00', 'DD/MM/YYYY TZH:TZM'));

   v_cutoff := ROUND(EXTRACT(DAY FROM v_interval) * 86400 +
                     EXTRACT(HOUR FROM v_interval) * 3600 + 
                     EXTRACT(MINUTE FROM v_interval) * 60 + 
                     EXTRACT(SECOND FROM v_interval) - i_delay);

   dbms_output.put_line('PURGE CUTOFF['||TO_CHAR(v_cutoff)||']');

   FOR s_rec IN snap_cv(v_cutoff) LOOP
      IF s_rec.poid_type = '/performance_sql_data' THEN
         DELETE performance_sql_data_buf WHERE obj_id0 = s_rec.poid_id0;
         DELETE performance_sql_data_t WHERE poid_id0 = s_rec.poid_id0;
      ELSE
         DELETE performance_results_t WHERE obj_id0 = s_rec.poid_id0;
         DELETE performance_snapshot_t WHERE poid_id0 = s_rec.poid_id0;
      END IF;
      dbms_output.put_line('PURGED['||s_rec.poid_type||' '||TO_CHAR(s_rec.poid_id0)||']');
      COMMIT;
   END LOOP;
END purge;

/*
 * UNIX timestamp to Oracle DATE function ...
 */
FUNCTION unix_to_date (unix_t IN NUMBER) RETURN DATE
IS
BEGIN
   RETURN CAST(((TIMESTAMP '1970-01-01 00:00:00 UTC' +
                 NUMTODSINTERVAL(unix_t, 'SECOND'))
                 AT TIME ZONE SESSIONTIMEZONE) AS DATE);
END unix_to_date;

/*
 * Oracle DATE to UNIX timestamp function ...
 */
FUNCTION date_to_unix (i_date IN DATE) RETURN NUMBER
IS
BEGIN
   RETURN (CAST((FROM_TZ(CAST(i_date AS TIMESTAMP), SESSIONTIMEZONE) AT TIME ZONE 'UTC') AS DATE)
           -
           TO_DATE('01/01/1970', 'DD/MM/YYYY')) * 86400;
END date_to_unix;

/*
 * Oracle TIMESTAMP to UNIX timestamp ...
 */
FUNCTION timestamp_to_unix (i_ts IN TIMESTAMP) RETURN NUMBER
IS
BEGIN
   RETURN date_to_unix(CAST(i_ts AT TIME ZONE 'UTC' AS DATE));
END timestamp_to_unix;

/*
 * UNIX timstamp or Oracle TIMESTAMP conversion ...
 */
FUNCTION unix_to_timestamp (unix_t IN NUMBER) RETURN TIMESTAMP
IS
BEGIN
   RETURN FROM_TZ(CAST(unix_to_date(unix_t) AS TIMESTAMP), 'UTC') AT TIME ZONE 'UTC';
END unix_to_timestamp;

/*
 * get_rel_summary : Get REL summary results.
 *
 * i_filename    - Filename filter (e.g. '%GSM%')
 * i_start_t     - Start time cutoff
 * i_end_t       - End time cutoff 
 * i_stage       - Filter for stage (default is '%')
 */
PROCEDURE get_rel_summary (
   i_filename    IN VARCHAR2,   /* Filename filter */
   i_start_t     IN NUMBER,     /* Start cutoff */
   i_end_t       IN NUMBER,     /* End cutoff */
   i_stage       IN VARCHAR2,   /* Stage filter */
   o_cv         OUT SYS_REFCURSOR)
IS
   v_filename   VARCHAR2(500) := '%';
   v_start_t    NUMBER(38) := 0;
   v_end_t      NUMBER(38) := 0;
   v_stage      VARCHAR2(500) := '%';
BEGIN
   /*
    * Set filters ...
    */
   IF i_filename IS NOT NULL THEN v_filename := i_filename; END IF;
   IF i_start_t IS NOT NULL AND i_start_t > 0 THEN v_start_t := i_start_t; END IF;
   IF i_end_t IS NOT NULL AND i_end_t > 0 THEN v_end_t := i_end_t; END IF;
   IF i_stage IS NOT NULL THEN v_stage := i_stage; END IF;
   /*
    * Select results ...
    */
   OPEN o_cv FOR
      SELECT br.input_file_name as filename,
             rms.descr as stage,
             ROUND(rms.elapsed, 3) AS elapsed,
             rms.num_cdrs,
             ROUND(rms.throughput, 3) AS throughput
        FROM batch_t b,
             batch_rel_t br,
             rel_monitor_summary_t rms
       WHERE rms.poid_id0 = b.poid_id0
         AND b.poid_id0 = br.obj_id0
         AND rms.descr LIKE v_stage
         AND br.input_file_name LIKE v_filename
         AND (v_start_t = 0 OR b.start_t >= v_start_t)
         AND (v_end_t = 0 OR b.end_t < v_end_t);
END get_rel_summary;

/*
 * get_rel_cumulative : Get REL monitor cumulative results.
 *
 * i_type    - Service type filter
 */
PROCEDURE get_rel_cumulative (
   i_type    IN VARCHAR2,
   o_cv     OUT SYS_REFCURSOR)
IS
   v_type   VARCHAR(500) := '%';
BEGIN
   /*
    * Set filter parameters ...
    */
   IF i_type IS NOT NULL THEN v_type := i_type; END IF;
   /*
    * Perform query ...
    */
   OPEN o_cv FOR
      SELECT service_type,
             num_files,
             num_cdrs,
             ROUND(preproc_time, 3) AS preproc_time,
             ROUND(load_time, 3) AS load_time,
             ROUND(preupdate_time, 3) AS preupdate_time,
             ROUND(update_time, 3) AS update_time,
             ROUND(preproc_time + load_time + preupdate_time + update_time, 3) AS total_time
        FROM rel_monitor_cumulative_t
       WHERE service_type LIKE v_type;
END get_rel_cumulative;

END perflib;
/
show errors;
exit;
