set serveroutput on size 1000000
set echo on
-- 2003 - 2023 Oracle. This material is the confidential property of Oracle Corporation
-- or its licensors and may be used, reproduced, stored or transmitted only in accordance with a valid Oracle
-- license or sublicense  agreement.
--
DECLARE
BEGIN
    dbms_output.put_line ('dropping queue table $queue_table ...');
    --
    dbms_aqadm.drop_queue_table
    (
        queue_table => '$queue_table',
        force => TRUE
    );
END;
/




