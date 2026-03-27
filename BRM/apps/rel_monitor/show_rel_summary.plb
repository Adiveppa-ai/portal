SET FEEDBACK off
SET VERIFY off
SET PAGESIZE 150
SET LINESIZE 250
COLUMN start_time      FORMAT A20
COLUMN end_time        FORMAT A20
COLUMN num_cdrs        FORMAT 999,999,999
COLUMN num_files       FORMAT 999,999,999
COLUMN preproc_t       FORMAT 999,990.99
COLUMN load_t          FORMAT 999,990.99
COLUMN preupdate_t     FORMAT 999,990.99
COLUMN update_t        FORMAT 999,990.99
COLUMN total_t         FORMAT 999,990.99
COLUMN "cdrs_per_file" FORMAT 999,999,999
COLUMN "preproc_rate"  FORMAT 999,990.99
COLUMN "load_rate"     FORMAT 999,990.99
COLUMN "preupd_rate"   FORMAT 999,990.99
COLUMN "update_rate"   FORMAT 999,990.99
COLUMN "total_rate"    FORMAT 999,990.99
COLUMN "real_rate"     FORMAT 999,990.99
SET TERMOUT off
COLUMN 1 new_value 1 noprint
SELECT '' "1" FROM dual WHERE ROWNUM = 0;
DEFINE bucket_size = &1 "60"
COLUMN 2 new_value 2 noprint
SELECT '' "2" FROM dual WHERE ROWNUM = 0;
DEFINE bucket_unit = &2 "MINUTE"
COLUMN 3 new_value 3 noprint
SELECT '' "3" FROM dual WHERE ROWNUM = 0;
DEFINE start_t = &3 "2000-01-01T00:00"
COLUMN 4 new_value 4 noprint
SELECT '' "4" FROM dual WHERE ROWNUM = 0;
DEFINE end_t = &4 "3000-01-01T00:00"
SET TERMOUT on
var start_t_filter varchar2(100);
var end_t_filter varchar2(100);
exec SELECT REPLACE('&start_t', 'T', ' ') INTO :start_t_filter FROM dual;
exec SELECT REPLACE('&end_t', 'T', ' ') INTO :end_t_filter FROM dual;
SELECT start_time,
       end_time,
       num_files,
       num_cdrs,
       cdrs_per_file,
       load_t,
       load_rate,
       preupdate_t,
       preupdate_rate,
       update_t,
       update_rate,
       total_t,
       total_rate,
       real_rate
  FROM TABLE(rel_monitor.summary_report_fn('&bucket_unit', &bucket_size, :start_t_filter, :end_t_filter));
exit;
