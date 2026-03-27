set serveroutput on size 1000000
-- 2003 - 2023 Oracle. This material is the confidential property of Oracle Corporation
-- or its licensors and may be used, reproduced, stored or transmitted only in accordance with a valid Oracle
-- license or sublicense  agreement.
--
DECLARE
  type_exists NUMBER;
BEGIN
   BEGIN
     SELECT 1 INTO type_exists FROM user_types WHERE type_name = 'PIN_EVENT_TY';
   EXCEPTION
     WHEN NO_DATA_FOUND THEN
       type_exists := 0;
   END;
   IF type_exists = 0 THEN
     EXECUTE IMMEDIATE 'CREATE TYPE pin_event_ty AS OBJECT '||
       ' (event_name VARCHAR2(32), '||
       ' flist_buf  VARCHAR2(4000), '||
       ' large_flist_buf  CLOB) ';
     dbms_output.put_line('pin_event_ty type has been created.');
   ELSE
     dbms_output.put_line('pin_event_ty type already exists.');
   END IF;
     --

   BEGIN
     SELECT 1 INTO type_exists FROM user_types WHERE type_name = 'DEQ_EVENT_TY';
   EXCEPTION
     WHEN NO_DATA_FOUND THEN
       type_exists := 0;
   END;
   IF type_exists = 0 THEN
     EXECUTE IMMEDIATE 'CREATE OR REPLACE TYPE deq_event_ty AS OBJECT '||
       ' (event_name             VARCHAR2(32), '||
       ' flist_buf               VARCHAR2(4000), '||
       ' large_flist_buf         CLOB, '||
       ' mesg_id                 VARCHAR2(32), '||
       ' enq_time                DATE) ';
     dbms_output.put_line('deq_event_ty type has been created.');
   ELSE
     dbms_output.put_line('deq_event_ty type already exists.');
   END IF;
     --

   BEGIN
     SELECT 1 INTO type_exists FROM user_types WHERE type_name = 'DEQ_EVENT_TABLE_TY';
   EXCEPTION
     WHEN NO_DATA_FOUND THEN
       type_exists := 0;
   END;
   IF type_exists = 0 THEN
     EXECUTE IMMEDIATE 'CREATE OR REPLACE TYPE deq_event_table_ty AS TABLE OF deq_event_ty';
     dbms_output.put_line('deq_event_table_ty type has been created.');
   ELSE
     dbms_output.put_line('deq_event_table_ty  type already exists.');
   END IF;
END;
/

BEGIN 
DBMS_AQADM.CREATE_QUEUE_TABLE(queue_table => '$queue_table', 
			      compatible => '8.1', 
			      storage_clause => '$storage_clause',
			      queue_payload_type => 'pin_event_ty',
			      sort_list => 'priority,enq_time'); 
END; 
/ 

BEGIN 
DBMS_AQADM.CREATE_QUEUE(queue_name => '$queue_name', 
			retention_time => $retention_time, 
			retry_delay => 6, 
			queue_table => '$queue_table'); 
END; 
/ 

BEGIN 
DBMS_AQADM.START_QUEUE(queue_name => '$queue_name', 
	   	       enqueue => TRUE, 
                       dequeue => TRUE); 
END; 
/ 


