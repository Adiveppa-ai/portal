SET TERMOUT off
COLUMN 1 new_value 1 noprint
SELECT '' "1" FROM dual WHERE ROWNUM = 0;
DEFINE purge_days = &1 "90"
COLUMN 2 new_value 2 noprint
SELECT '' "2" FROM dual WHERE ROWNUM = 0;
DEFINE test_mode = &2 "N"
VAR is_test NUMBER;
VAR num_rows NUMBER;
exec SELECT DECODE(UPPER('&test_mode'), 'Y', 1, 'YES', 1, '1', 1, 0) INTO :is_test FROM dual;
SET TERMOUT on
exec rel_monitor.purge(&purge_days, :is_test, :num_rows);
SET HEAD OFF
SELECT DECODE(:is_test, 0, 'Purged ', 'Would purge ')||:num_rows||' rows from rel_monitor tables.' FROM dual;
exit;
