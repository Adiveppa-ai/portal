set serveroutput on size 1000000
--  2003, 2023, Oracle and/or its affiliates.
-- or its licensors and may be used, reproduced, stored or transmitted only in accordance with a valid Oracle 
-- license or sublicense  agreement. 
--
CREATE OR REPLACE PACKAGE BODY acct_sync
AS
   -- log file variables
   enq_log_file    utl_file.file_type;
   deq_log_file    utl_file.file_type;
   log_file_dir    VARCHAR2(100);
   log_file_name   VARCHAR2(100);
   log_file_flag   CHAR;

   v_ece_rating    NUMBER(1);


     -- Check if ECE rating business parameter is set
     PROCEDURE init IS
	 v_param_value VARCHAR2(20);
         BEGIN
	    v_ece_rating  := 0;

	    SELECT param_value
	    INTO v_param_value
	    FROM config_business_params_t
	    WHERE param_name = 'ece_rating';

	    IF v_param_value = '1' THEN
		v_ece_rating := 1;
	    END IF;

	    DBMS_OUTPUT.PUT_LINE('Initializing v_ece_rating = '||v_ece_rating);

         EXCEPTION
         WHEN OTHERS THEN
	    -- Default if business parameter not found
	    v_ece_rating := 0; 
	 DBMS_OUTPUT.PUT_LINE('Exception - Initializing v_ece_rating = '||v_ece_rating);
     END init;

   --
   -- open log file
   --
   PROCEDURE log_open (p_log_file_flag IN CHAR, 
                       p_log_file_dir IN VARCHAR2, 
                       p_log_file_name IN VARCHAR2,
                       p_log_file OUT utl_file.file_type) IS 
   BEGIN
     IF (p_log_file_flag = 'Y') THEN  
       p_log_file := utl_file.fopen(p_log_file_dir, 
                                    p_log_file_name,
                                    'a',   -- append mode
                                    5000); -- indiv. message can be as long as 5000 bytes
     END IF;
   END;  
   --
   -- close log file
   --
   PROCEDURE log_close (p_log_file_flag IN CHAR, p_log_file IN OUT utl_file.file_type) IS
   BEGIN
     IF (p_log_file_flag = 'Y') THEN
       IF (utl_file.is_open(p_log_file)) THEN        
           utl_file.fflush(p_log_file);
	   utl_file.fclose(p_log_file);
       END IF;	  
     END IF;   
   END;	
   --
   -- write message to log file
   --
   PROCEDURE log_mesg(p_log_file_flag IN CHAR, p_log_file IN utl_file.file_type, p_mesg IN VARCHAR2) IS
   BEGIN
     IF (p_log_file_flag = 'Y') THEN
       utl_file.put_line(p_log_file, to_char(sysdate, 'MM/DD/YY HH24:MM:SS')||' '||p_mesg);
       utl_file.fflush(p_log_file);
     ELSE
       dbms_output.put_line(to_char(sysdate, 'MM/DD/YY HH24:MM:SS')||' '||p_mesg);
     END IF;  
   END; 
   --
   -- enq_event
   --  
   PROCEDURE enq_event(event_name    IN VARCHAR2,
		       flist_buf     IN VARCHAR2, 
		       flist_buf_len IN NUMBER,
		       queue_name    IN VARCHAR2,
		       mesg_id       OUT NOCOPY VARCHAR2)
   IS
     enq_opts	     DBMS_AQ.ENQUEUE_OPTIONS_T;
     mesg_props	     DBMS_AQ.MESSAGE_PROPERTIES_T;
     id   	     RAW(16);
     event	     pin_event_ty;
     event_pr_type   $primary_schema_payload_type;
     queue_table     VARCHAR2(30);
     blob_storage    BOOLEAN;
     cross_schema    BOOLEAN;
     blob_locator    CLOB;
     queue_len       NUMBER;
     queue_name_pos  NUMBER;
     queue_name_local VARCHAR2(30);
     schema_qualifier VARCHAR2(30);
   BEGIN
     cross_schema := FALSE;
     queue_name_pos := instr(queue_name,'.');
     IF (queue_name_pos > 0) THEN
        schema_qualifier := substr(queue_name,0, queue_name_pos - 1);
        IF (upper('$primary_schema') = upper(schema_qualifier)) THEN
            cross_schema := TRUE;
        END IF;
     END IF;
     IF (lengthb(flist_buf) > 4000) THEN
         blob_storage := TRUE;
         IF (cross_schema = TRUE) THEN 
           event_pr_type := $primary_schema_payload_type(event_name, NULL, EMPTY_CLOB());
         ELSE
           event := pin_event_ty(event_name, NULL, EMPTY_CLOB());
         END IF;
     ELSE 
       blob_storage := FALSE;
       IF (cross_schema = TRUE) THEN 
            event_pr_type := $primary_schema_payload_type(event_name, flist_buf, EMPTY_CLOB());
       ELSE
           event := pin_event_ty(event_name, flist_buf, EMPTY_CLOB());
       END IF;
     END IF;
     -- setting the correlation id as event name
     mesg_props.correlation := event_name;
     --
     IF (cross_schema = TRUE) THEN
        DBMS_AQ.ENQUEUE(queue_name,
                     enq_opts,
                     mesg_props,
                     event_pr_type,
                     id);
     ELSE
        DBMS_AQ.ENQUEUE(queue_name,
                     enq_opts,
                     mesg_props,
                     event,
                     id);
     END IF;
     --
     IF (blob_storage = TRUE) THEN
        -- t.userdata is a standard AQ message field, in this case of the type pin_event_ty
	IF (queue_name_pos > 0) THEN
	   queue_len := length(queue_name);
           schema_qualifier := schema_qualifier ||'.';
	   queue_name_local := substr(queue_name,queue_name_pos + 1,queue_len - queue_name_pos);
	ELSE
	   queue_name_local := queue_name;
           schema_qualifier := '';
	END IF;
	SELECT queue_table INTO queue_table FROM user_queues WHERE name = queue_name_local;
        --
        EXECUTE IMMEDIATE 'SELECT t.user_data.large_flist_buf '||
	                  'FROM '||schema_qualifier||'AQ\$'||queue_table||' t WHERE t.msg_id = :id' INTO blob_locator USING id;
        -- 
        DBMS_LOB.OPEN(blob_locator, DBMS_LOB.LOB_READWRITE);
        DBMS_LOB.WRITE(blob_locator, length(flist_buf), 1, flist_buf);     
        DBMS_LOB.CLOSE(blob_locator);
     END IF;
     --
     mesg_id := RAWTOHEX(id); 
     --
     IF (log_file_flag = 'Y') THEN  
       log_mesg(log_file_flag, enq_log_file,
                'event_name = '||event_name);
       log_mesg(log_file_flag, enq_log_file,
                'flist_buf = '||substr(flist_buf, 1, 4000));
       log_mesg(log_file_flag, enq_log_file,
                'flist_buf_len = '||flist_buf_len);
       log_mesg(log_file_flag, enq_log_file,
                'queue_name = '||queue_name);
       log_mesg(log_file_flag, enq_log_file,
                'mesg_id = '||mesg_id);
     END IF;
     --
   END;
   -- 
   -- enq_event_append
   --
   PROCEDURE enq_event_append(flist_buf     IN VARCHAR2,
                              flist_buf_len IN NUMBER,
                              queue_name    IN VARCHAR2,
                              mesg_id       IN VARCHAR2)
   IS
     id              RAW(16);
     queue_table     VARCHAR2(30);
     blob_storage    BOOLEAN;
     blob_locator    CLOB;
     queue_len       NUMBER;
     queue_name_pos  NUMBER;
     queue_name_local VARCHAR2(30);
   BEGIN
     -- Introducing Strict Input Parameter Checking
     IF (REGEXP_LIKE(mesg_id, '[^0-9A-Fa-f]+')) THEN
      RAISE_APPLICATION_ERROR(-20003, 'enq_event_append: Invalid parameter - mesg_id validation failed', TRUE);
     END IF;
     -- additions can only be made to LOBs
     -- convert hex mesg_id back to raw
     id := HEXTORAW(mesg_id);
     --
     queue_name_pos := instr(queue_name,'.');
     IF (queue_name_pos > 0) THEN
        queue_len := length(queue_name);
        queue_name_local := substr(queue_name,queue_name_pos + 1,queue_len - queue_name_pos);
     ELSE
        queue_name_local := queue_name;
     END IF;
     SELECT queue_table INTO queue_table FROM user_queues WHERE name = queue_name_local;
     --
     EXECUTE IMMEDIATE 'SELECT t.user_data.large_flist_buf '||
                       'FROM AQ\$'||queue_table||' t WHERE t.msg_id = :id' INTO blob_locator USING id;
     -- pre-condition: Oracle AQ message need to exist
     -- todo: check if blob_locator is valid
     -- Calculate the length of buffer before passing to WRITEAPPEND call as length passed from 
     -- application may not be correct for special character containing string.
     DBMS_LOB.OPEN(blob_locator, DBMS_LOB.LOB_READWRITE);
     DBMS_LOB.WRITEAPPEND(blob_locator, length(flist_buf), flist_buf);
     DBMS_LOB.CLOSE(blob_locator);
     --
   END;
   --
   -- deq_event_rc
   --
   PROCEDURE deq_event_rc(queue_name		IN VARCHAR2,
			  event_name_cond       IN VARCHAR2,
			  batch_size		IN NUMBER,
			  ack_queue_name	IN VARCHAR2,
			  event_cursor		IN OUT deq_event_cursor) 
   IS 
     deq_opts		DBMS_AQ.DEQUEUE_OPTIONS_T;
     mesg_props		DBMS_AQ.MESSAGE_PROPERTIES_T;
     id	  	        RAW(16);
     event		pin_event_ty;
     event_table	deq_event_table_ty := deq_event_table_ty(); 	
     no_messages        exception;
     pragma exception_init (no_messages, -25228);
     mesg_id 		VARCHAR2(256);

   BEGIN
     -- Introducing Strict Input Parameter Checking
     IF(queue_name IS NULL ) THEN
      RAISE_APPLICATION_ERROR(-20003, 'deq_event_rc: Invalid parameter - queue_name; validation failed', TRUE);
     END IF;

     IF(LENGTH(event_name_cond) > 4000) THEN
      RAISE_APPLICATION_ERROR(-20003, 'deq_event_rc: Invalid parameter - event_name_cond; validation failed', TRUE);
     END IF;

     -- wait period
     deq_opts.wait := 5;
     -- 
     deq_opts.deq_condition := event_name_cond;
     --

     FOR i IN 1..batch_size LOOP
       BEGIN
         DBMS_AQ.DEQUEUE(queue_name,
	                 deq_opts,
                         mesg_props,
                         event,
                         id);
	 --		 
         event_table.extend();
	 --
         event_table(i) := deq_event_ty(
   	                 event.event_name,
                         event.flist_buf,
                         event.large_flist_buf,
	                 RAWTOHEX(id),
                         mesg_props.enqueue_time);

	-- For pipeline:
	-- enqueue the ack event here for performance improvement
	-- by avoiding the call to listener and notification thereafter
	--
	-- For ECE rating: 
	-- Donot enqueue the ack event. Listener gets called.
	-- Assumption made here is that queue and BRM 
	-- are in same schema inorder to access the config data.
        IF (v_ece_rating = 0) THEN
	    IF ack_queue_name IS NOT NULL THEN
	       IF (event.event_name = 'PrepareToRerate' OR
	          event.event_name = 'ReratingCompleted' )THEN
		  
	          enq_event('ACK'||event.event_name,
                       event.flist_buf, 
                       LENGTH(event.flist_buf),
                       ack_queue_name,
                       mesg_id);
	       END IF;
	    END IF; 
        END IF; 

        IF (log_file_flag = 'Y') THEN
           log_mesg(log_file_flag, enq_log_file,
                    'event_name = '||event.event_name);
           log_mesg(log_file_flag, enq_log_file,
                    'mesg_id = '||RAWTOHEX(id));
           log_mesg(log_file_flag, enq_log_file,
                    'enq_time = '||mesg_props.enqueue_time);
        END IF;

	 --
       EXCEPTION
         WHEN no_messages THEN
	     -- Queue is empty. Exit without raising an exception to avoid ORA-25228 and the resulting ORA-04043
             -- Return partially filled event_table
	     EXIT;
       END;
     END LOOP;
     --
     	OPEN event_cursor FOR SELECT * FROM TABLE ( CAST ( event_table AS deq_event_table_ty ));
     --
   END;
   --
   -- deq_event
   --
   PROCEDURE deq_event(event_name      OUT NOCOPY VARCHAR2,
                       flist_buf       OUT NOCOPY VARCHAR2,
                       large_flist_buf OUT NOCOPY CLOB,
                       mesg_id         OUT NOCOPY VARCHAR2,
                       enq_time        OUT NOCOPY DATE,
                       queue_name      IN VARCHAR2,
                       event_name_cond IN VARCHAR2) 
   IS 
     deq_opts           DBMS_AQ.DEQUEUE_OPTIONS_T;
     mesg_props         DBMS_AQ.MESSAGE_PROPERTIES_T;
     id                 RAW(16);
     event              pin_event_ty;
   BEGIN
     -- Introducing Strict Input Parameter Checking
     IF(queue_name IS NULL ) THEN
       RAISE_APPLICATION_ERROR(-20003, 'deq_event: Invalid parameter - queue_name; validation failed', TRUE);
     END IF;

     IF(LENGTH(event_name_cond) > 4000) THEN
       RAISE_APPLICATION_ERROR(-20003, 'deq_event: Invalid parameter - event_name_cond; validation failed', TRUE);
     END IF;

     -- wait period
     deq_opts.wait := 5;
     -- 
     deq_opts.deq_condition := event_name_cond;
     -- 
     DBMS_AQ.DEQUEUE(queue_name,
                     deq_opts,
                     mesg_props,
                     event,
                     id);
     -- 
     flist_buf := event.flist_buf;
     large_flist_buf := event.large_flist_buf;
     event_name := event.event_name;
     mesg_id := RAWTOHEX(id);
     enq_time := mesg_props.enqueue_time;
     --
     IF (log_file_flag = 'Y') THEN 
       log_mesg(log_file_flag, deq_log_file,
                'event_name = '||event_name);
       log_mesg(log_file_flag, deq_log_file,
                'flist_buf = '||flist_buf);
       log_mesg(log_file_flag, deq_log_file,
                'large_flist_buf = '||DBMS_LOB.SUBSTR(large_flist_buf,
                                                      4000,
                                                      1));
       log_mesg(log_file_flag, deq_log_file,
                'queue_name = '||queue_name);
       log_mesg(log_file_flag, deq_log_file,
                'mesg_id = '||mesg_id);
       log_mesg(log_file_flag, deq_log_file,
                'enq_time = '||enq_time);
     END IF;
     --
   END;
   -- 
   -- purge_event
   --
   PROCEDURE purge_event(queue_name      IN VARCHAR2,
                         purge_mesg_cnt  OUT NOCOPY NUMBER)
   IS
     purgeOption         dbms_aqadm.aq\$_purge_options_t;
     sqlString           VARCHAR2(256);
     queueTable          VARCHAR2(20);
     msgCountBeforePurge NUMBER;
     msgCountAfterPurge  NUMBER;
     --
   BEGIN
     --
     purge_mesg_cnt := 0;
     msgCountBeforePurge := 0;
     msgCountAfterPurge := 0;
     --
     SELECT queue_table INTO queueTable FROM user_queues WHERE name = UPPER(queue_name);
     --
     sqlString := 'SELECT count(1)'  ||
                         ' FROM ' ||queueTable|| ' WHERE q_name = UPPER('''||queue_name||''') ';
     EXECUTE IMMEDIATE sqlString INTO msgCountBeforePurge;
     --
     DBMS_OUTPUT.PUT_LINE('Before Purge, msgCountBeforePurge = '||msgCountBeforePurge);
     --
     -- Events of type RecycleRequest, ResubmitBatchRequest, HoldCDRProcessing,
     -- ResumeCDRProcessing, MigrateAccount, MigrateSource, MigrateDestination,
     -- ReratingCompleted, PrepareToRerate are not purged.
     --
     purgeOption.block := TRUE;
     dbms_aqadm.purge_queue_table(
          queue_table     => queueTable,
          purge_condition => 'qtview.corr_id not in
                (''RecycleRequest'',''ResubmitBatchRequest'',''HoldCDRProcessing'',''ResumeCDRProcessing'',
                 ''MigrateAccount'',''MigrateSource'',''MigrateDestination'',''ReratingCompleted'',''PrepareToRerate'') and
                 qtview.enq_time < (SYSDATE - 2/1440)' ,
          purge_options   => purgeOption);
     --
     COMMIT;
     --
     EXECUTE IMMEDIATE sqlString INTO msgCountAfterPurge;
     purge_mesg_cnt := msgCountBeforePurge - msgCountAfterPurge;
     --
     DBMS_OUTPUT.PUT_LINE('After Purge, msgCountAfterPurge = '||msgCountAfterPurge);
     --
   END;
--
-- package initialization
-- 
BEGIN
  -- configuration begin

  -- The default is the current directory.
  -- Please specify any specific location (if any).
  log_file_dir := '.';

  -- And set flag to 'Y' to turn on the debug.
  log_file_flag := 'N';

  -- configuration end

  IF (log_file_flag = 'Y') THEN 
    log_file_name := 'enq_event.log';
    log_open(log_file_flag, log_file_dir, log_file_name, enq_log_file);   
    log_file_name := 'deq_event.log';
    log_open(log_file_flag, log_file_dir, log_file_name, deq_log_file);
  END IF;
 
  -- Load the config business param for ece_rating param_name
  init;

END; 
/
show errors;
  

