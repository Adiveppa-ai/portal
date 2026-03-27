--
-- @(#) %full_filespec: crt_pinlog.sql~2:sql:3 %
--
--      Copyright (c) 2001 - 2006 Oracle. All rights reserved.
--
--      This material is the confidential property of Oracle Corporation or
--      its licensors and may be used, reproduced, stored or transmitted only
--      in accordance with a valid Oracle license or sublicense agreement.
--
-- sql file to produce the pinlog file for the given step.
-- $step_name will be substituted by the calling script.
-- 

SET pagesize 100
SET linesize 130
SET verify off
SET feedback off

COLUMN "MSG TYPE" FORMAT A10
COLUMN "TIME" FORMAT A18 
COLUMN "BATCH" FORMAT A40
COLUMN "END TIME" FORMAT A30
COLUMN "INFRANET MSG" FORMAT A30
COLUMN "ORACLE MSG" FORMAT A25
COLUMN step_name NEW_VALUE stepvar NOPRINT
TTITLE LEFT "STEP NAME:: " stepvar SKIP 2
BREAK ON step_name SKIP PAGE

SELECT step_name, DECODE (msg_type, 'I', 'INFO', 'W', 'WARNING', 'E', 'ERROR', 'C', 'COMPLETED') "MSG TYPE", 
	to_char(curr_time, 'DD-MON-YY HH24:MI:SS') "TIME",
        pin_upg_common.inf2ora_time(start_created_t) || ' to ' || pin_upg_common.inf2ora_time(end_created_t) "BATCH",
	infranet_msg "INFRANET MSG", 
	oracle_error "ORACLE MSG"
FROM upg_log_t
WHERE UPPER(step_name) like UPPER('$step_name%')
AND log_type IS NULL
ORDER BY curr_time, step_name, start_created_t DESC;

