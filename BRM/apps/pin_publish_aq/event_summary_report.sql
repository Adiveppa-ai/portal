rem 2003 - 2023 Oracle. This material is the confidential property of Oracle Corporation
rem or its licensors and may be used, reproduced, stored or transmitted only in accordance with a valid Oracle
rem license or sublicense  agreement.
rem

SET verify off
ttitle 'Event Summary Report'

rem global settings
set feedback off
set headsep !
set linesize 80
set pagesize 50
rem set newpage 0

rem column heading
column msg_state heading 'Evt. State'
column event_name heading 'Event Name'
column cnt heading 'Event Count'

break on msg_state skip 1

compute sum of cnt on msg_state

rem main select statement
-- how many messages have been dequeued?
SELECT
t.msg_state msg_state,
t.user_data.event_name event_name,
count(*) cnt
FROM aq\$$queue_table t GROUP by t.user_data.event_name, t.msg_state ORDER BY t.msg_state;

rem display message if no messages have been found

set heading off
SELECT
'no data available'
FROM dual WHERE NOT EXISTS (SELECT 1 FROM aq\$$queue_table t);

quit;


