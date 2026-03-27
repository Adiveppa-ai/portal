rem 2003 - 2023 Oracle. This material is the confidential property of Oracle Corporation
rem or its licensors and may be used, reproduced, stored or transmitted only in accordance with a valid Oracle
rem license or sublicense  agreement.
rem

SET verify off
ttitle 'Event Detail Report'

rem global settings
set feedback off
set headsep !
set linesize 120
set pagesize 50
rem set newpage 0

rem column heading
column msgid heading 'Mesg. ID'
column event_name heading 'Event Name'
column msg_state heading 'Evt. State'
column enq_time heading 'Enq. Time'
column deq_time heading 'Deq. Time'

rem main select statement
-- how many messages have been dequeued?
SELECT
t.msg_id msgid,
t.user_data.event_name event_name,
t.msg_state msg_state,
to_char(enq_time, 'MM/DD/YY HH24:MI:SS') enq_time,
to_char(deq_time, 'MM/DD/YY HH24:MI:SS') deq_time
FROM aq\$$queue_table t ORDER BY t.enq_time;

rem display message if no messages have been found

set heading off
SELECT
'no data available'
FROM dual WHERE NOT EXISTS (SELECT 1 FROM aq\$$queue_table t);

quit;


