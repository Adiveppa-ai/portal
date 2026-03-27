set feedback off
set verify off
set pagesize 150
set linesize 200
column filename       format A60
column stage          format A15
column time           format A25
column service_type   format A15
column elapsed        format 99999999990.99
column CDRs           format 9999999
column num_cdrs       format 99,999,999,999
column num_files      format 99,999,999,999
column "CDRs/s"       format 99999999990.99
column preproc_time   format 999,999,990.99
column load_time      format 999,999,990.99
column preupdate_time format 999,999,990.99
column update_time    format 999,999,990.99
column total_time     format 999,999,990.99
column "AvgCdrs/File" format 99999999990.99
column "PreProc/s"    format 99999999990.99
column "Loads/s"      format 99999999990.99
column "PreUpdate/s"  format 99999999990.99
column "Update/s"     format 99999999990.99
column "CDRs/s"       format 99999999990.99
COLUMN 1 new_value 1 NOPRINT
SELECT '' "1" FROM DUAL WHERE ROWNUM = 0;
DEFINE param1 = &1 "_no_details_required_"
   SELECT SUBSTR(br.input_file_name, INSTR(br.input_file_name, '/', -1)+1) AS filename,
          rms.descr AS stage,
          TO_CHAR(rms.tstamp, 'DD/MM/YYYY HH24:MI:SS.FF3') AS time,
          rms.elapsed,
          rms.num_cdrs AS CDRs,
          rms.throughput AS "CDRs/s"
     FROM rel_monitor_summary_t rms,
          batch_rel_t br
    WHERE br.obj_id0 = rms.poid_id0
      AND br.input_file_name LIKE '&1'
 ORDER BY rms.tstamp, br.input_file_name;
prompt
prompt TOTAL PROCESSING TIME BY EVENT TYPE:
SELECT service_type,
       num_files,
       num_cdrs,
       (num_cdrs / num_files) AS "AvgCdrs/File",
       preproc_time,
       load_time,
       preupdate_time,
       update_time,
       (preproc_time + load_time + preupdate_time + update_time) AS total_time
  FROM rel_monitor_cumulative_t;
prompt
prompt TOTAL PROCESSING RATE BY EVENT TYPE:
SELECT service_type,
       num_files,
       num_cdrs,
       (num_cdrs / num_files) AS "AvgCdrs/File",
       DECODE(preproc_time, 0, 0, (num_cdrs / preproc_time)) AS "PreProc/s",
       DECODE(load_time, 0, 0, (num_cdrs / load_time)) "Loads/s",
       DECODE(preupdate_time, 0, 0, (num_cdrs / preupdate_time)) AS "PreUpdate/s",
       DECODE(update_time, 0, 0, (num_cdrs / update_time)) AS "Update/s",
       (num_cdrs / (preproc_time + load_time + preupdate_time + update_time)) AS "CDRs/s"
  FROM rel_monitor_cumulative_t;
column duration format 999,999,990.9
prompt
prompt TOTAL EFFECTITVE RATE:
SELECT TO_CHAR(min_t, 'YYYY/MM/DD HH24:MI:SS') AS "Start Time",
       TO_CHAR(max_t, 'YYYY/MM/DD HH24:MI:SS') AS "End Time",
       duration,
       num_cdrs,
       (num_cdrs/DECODE(duration, 0, 1, duration)) AS "CDRs/s"
  FROM (SELECT c.service_type,
               c.num_cdrs,
               EXTRACT(hour FROM (t.max_t - t.min_t)) * 3600 + EXTRACT(minute FROM (t.max_t - t.min_t)) * 60 + EXTRACT(second FROM (t.max_t - t.min_t)) duration,
               t.min_t,
               t.max_t
          FROM (SELECT MIN(rms.tstamp) min_t, MAX(rms.tstamp) max_t FROM rel_monitor_summary_t rms) t,
               (SELECT service_type, num_cdrs FROM rel_monitor_cumulative_t) c);
exit;
