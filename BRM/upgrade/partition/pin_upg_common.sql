--
-- @(#) %full_filespec: pin_upg_common.sql~9:sql:5 %
--
--      Copyright (c) 2001 - 2007 Oracle. All rights reserved.
--
--      This material is the confidential property of Oracle Corporation or
--      its licensors and may be used, reproduced, stored or transmitted only
--      in accordance with a valid Oracle license or sublicense agreement.
--
-- sql file to create all the common APIs for Upgrade Process.
--

/* 
 * Table to keep track of the status of the upgrade.
 */

set serveroutput on

DECLARE
	v_dummy PLS_INTEGER := 0;
BEGIN
        SELECT count(*) INTO v_dummy
        FROM user_tables 
        WHERE table_name = 'UPG_LOG_T';

        IF (v_dummy = 0) THEN
                EXECUTE IMMEDIATE 'CREATE TABLE upg_log_t (step_name VARCHAR2(70),
						curr_time DATE,
						start_created_t INT,
						end_created_t INT,
						msg_type CHAR(1),
						infranet_msg VARCHAR2(4000),
						oracle_error VARCHAR2(250),
						log_type VARCHAR2(1))
					$UPG_TEMPTBLS_TABLESPACE $UPG_STORAGE';
	END IF;

	SELECT count(*) INTO v_dummy
        FROM user_indexes
        WHERE table_name = 'UPG_LOG_T'
        AND index_name = 'I_UPG_LOG_NDX';

	IF (v_dummy = 0) THEN
                EXECUTE IMMEDIATE  'CREATE INDEX i_upg_log_ndx ON upg_log_t (step_name)
					$UPG_TEMPINDX_TABLESPACE $UPG_STORAGE';
	END IF;

EXCEPTION
	WHEN others THEN
		dbms_output.put_line(sqlerrm);
		dbms_output.put_line('Unable to create the upgrade meta tables');
END;
/
/****************************************
 * This package contains the common routines
 * used by the upgrade scripts
 ****************************************/

CREATE or REPLACE PACKAGE pin_upg_common AS

C_NO_OF_SECONDS_IN_A_DAY CONSTANT PLS_INTEGER := 86400;

/*
 *
 * Function to do decimal to binary conversion.
 */

FUNCTION dec_to_bin(i_dec IN INT) RETURN VARCHAR2; 

/*
 * Function to do decimal to binary conversion.
 * Return number of bits can be specified.
 * Will pad with the trailing zeros if the specified 
 * number of bits are not present.
 */

FUNCTION dec_to_bin (i_dec IN INT, i_length IN INT) RETURN VARCHAR2;

/*
 * Function to do binary to decimal conversion.
 */


FUNCTION bin_to_dec(i_binary_str IN VARCHAR2) RETURN INT;

/*
 * Converts Infranet time to Oracle date format.
 * The returned value is in the format 'dd-mon-yy hh:mi:ss'.
 */

FUNCTION inf2ora_time(inf_time INTEGER) RETURN VARCHAR2; 

PRAGMA RESTRICT_REFERENCES (inf2ora_time, WNDS);

FUNCTION inf2ora_time_yyyy(inf_time INTEGER) RETURN VARCHAR2; 

FUNCTION inf2ora_time_yyyy_offset(inf_time INTEGER) RETURN VARCHAR2; 

PRAGMA RESTRICT_REFERENCES (inf2ora_time_yyyy_offset, WNDS);

PRAGMA RESTRICT_REFERENCES (inf2ora_time_yyyy, WNDS);


/* 
 * Converts the Oracle date to the Infranet time format.
 */

FUNCTION ora2inf_time(ora_time DATE) RETURN INTEGER; 

PRAGMA RESTRICT_REFERENCES (ora2inf_time, WNDS);

FUNCTION ora2inf_time_offset(ora_time DATE) RETURN INTEGER;

PRAGMA RESTRICT_REFERENCES (ora2inf_time_offset, WNDS);

/*
 * Returns TRUE if the table is present in the current schema,
 * FALSE otherwise.
 */

FUNCTION table_exists (i_table_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2 )
RETURN BOOLEAN;

/*
 * Returns TRUE if the view is present in the current schema,
 * FALSE otherwise.
 */

FUNCTION view_exists (i_view_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN; 

/*
 * Returns TRUE if the index is present in the current schema,
 * FALSE otherwise.
 */

FUNCTION index_exists (i_index_name VARCHAR2, io_errmsg IN OUT VARCHAR2 )
RETURN BOOLEAN;


/*
 * Returns TRUE if the index with the given conditions is present in the current schema,
 * FALSE otherwise.
 */

FUNCTION index_exists (i_index_name VARCHAR2, i_table_name IN VARCHAR2, 
			i_is_unique VARCHAR2, io_errmsg IN OUT VARCHAR2 )
RETURN BOOLEAN;


/*
 * Returns TRUE if the index with the given conditions is present in the current schema,
 * FALSE otherwise.
 */

FUNCTION index_exists (i_index_name VARCHAR2, i_table_name IN VARCHAR2, i_column_list IN VARCHAR2,  
			i_is_unique VARCHAR2, io_errmsg IN OUT VARCHAR2 )
RETURN BOOLEAN;


/* 
 * Returns TRUE if the table has this column
 */

FUNCTION column_exists (i_table_name IN VARCHAR2, i_column_name IN VARCHAR2,
			io_errmsg IN OUT VARCHAR2 )
RETURN BOOLEAN;

FUNCTION sequence_exists (i_sequence_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN;

 
/*
 * Returns TRUE if the partition with the given conditions exist.
 */

FUNCTION partition_exists (i_table_name IN VARCHAR2, i_partition_name IN VARCHAR2,
                           i_high_value IN VARCHAR2, i_partition_position IN INT,
                           io_errmsg IN OUT VARCHAR2) 
RETURN BOOLEAN;     

FUNCTION synonym_exists (i_synonym_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN;     

FUNCTION partition_exists (i_table_name IN VARCHAR2, i_partition_name IN VARCHAR2,
                           i_partition_position IN INT, io_errmsg IN OUT VARCHAR2) 
RETURN BOOLEAN;                      
  

/*
 * Logs upgrade progress information into the upg_log_t table.
 */

PROCEDURE log_info (i_step_name IN VARCHAR2, i_start_created_t IN INT, 
		    i_end_created_t IN INT, i_msg_type IN VARCHAR2, 
		    i_infranet_msg IN VARCHAR2, i_oracle_error IN VARCHAR2 DEFAULT NULL);

/*
 * Deletes the logged information related to a step.
 */

PROCEDURE delete_info (i_step_name IN VARCHAR2);

/*
 * Deletes only the error information related to a step.
 * This is usually called by the programs which process the
 * data using the date range. In this case, deleteing all the
 * information related to a step will cause it to restart all over 
 * again (in case the program was terminated due to an error).
 * Not getting ridding of the old errors will confuse the users.
 */

PROCEDURE delete_error_info (i_step_name IN VARCHAR2);

/*
 * Returns true if the step is already completed.
 */

FUNCTION step_completed (i_step_name IN VARCHAR2) 
RETURN BOOLEAN;

FUNCTION step_completed (i_step_name IN VARCHAR2, i_start_created_t IN INT) 
RETURN BOOLEAN;

FUNCTION get_created_t_bounds (i_step_name IN VARCHAR2, i_interval IN INT, i_start_created_t IN INT, i_end_created_t IN INT,
				o_start_created_t OUT INT, o_end_created_t OUT INT)
RETURN BOOLEAN; 


--
-- This procedure resets the obj_ids sequence to 1000
--

PROCEDURE reset_obj_ids_seq;

--
-- This procedure moves the obj_ids sequence outside the Portal range.
--

PROCEDURE move_up_obj_ids_seq;

--
-- This procedure is used to move up the poid_ids sequence by the given number.
--

PROCEDURE move_up_poid_ids_seq (i_interval IN INT);
FUNCTION new_poid RETURN NUMBER;

END pin_upg_common;
/


CREATE or REPLACE PACKAGE BODY pin_upg_common AS


FUNCTION dec_to_bin(i_dec IN INT) RETURN VARCHAR2 AS
        v_binary_str VARCHAR2(100) := NULL;
        v_decimal_value INT := i_dec;
BEGIN
        WHILE (v_decimal_value > 0) LOOP
                v_binary_str := to_char (v_decimal_value MOD 2) || v_binary_str;
                v_decimal_value := FLOOR(v_decimal_value/2);
        END LOOP;

        RETURN NVL(v_binary_str, '0');
EXCEPTION
        WHEN others THEN
                dbms_output.put_line(sqlerrm);
END dec_to_bin;


FUNCTION dec_to_bin (i_dec IN INT, i_length IN INT) RETURN VARCHAR2 AS
	v_binary_str VARCHAR2(100) := NULL;
BEGIN
	v_binary_str := dec_to_bin(i_dec);
	
	--
	-- If the length of the string is less than i_length, pad with zeros.
	--

	FOR i IN 1 .. (i_length - LENGTH(v_binary_str)) LOOP
		v_binary_str := '0' || v_binary_str;
	END LOOP;

	RETURN v_binary_str;
EXCEPTION
        WHEN others THEN
                dbms_output.put_line(sqlerrm);
END dec_to_bin;


FUNCTION bin_to_dec(i_binary_str IN VARCHAR2) RETURN INT AS
        v_binary_str_len INT := LENGTH(i_binary_str);
        v_decimal_value INT := 0;
        v_single_digit INT;
BEGIN
        FOR i IN 1 .. v_binary_str_len LOOP
                v_single_digit := to_number(SUBSTR(i_binary_str, i, 1));
                v_decimal_value := v_decimal_value + v_single_digit * POWER (2, v_binary_str_len - i);
        END LOOP;

        RETURN v_decimal_value;
EXCEPTION
        WHEN others THEN
                dbms_output.put_line(sqlerrm);
END bin_to_dec;


FUNCTION inf2ora_time(inf_time INTEGER) RETURN VARCHAR2 AS
        v_temp_var DATE;
BEGIN
        v_temp_var := to_date('01-jan-1970', 'dd-mon-yyyy') + (inf_time / 86400);

        RETURN to_char(v_temp_var, 'DD-MON-YY HH:MI:SS');
	
EXCEPTION
	WHEN others THEN
		dbms_output.put_line(sqlerrm);
END inf2ora_time;

FUNCTION inf2ora_time_yyyy(inf_time INTEGER) RETURN VARCHAR2 AS
        v_temp_var DATE;
BEGIN
        v_temp_var := to_date('01-jan-1970', 'dd-mon-yyyy') + (inf_time / 86400);

        RETURN to_char(v_temp_var, 'DD-MON-YYYY HH:MI:SS');
	
EXCEPTION
	WHEN others THEN
		dbms_output.put_line(sqlerrm);
END inf2ora_time_yyyy;

FUNCTION inf2ora_time_yyyy_offset(inf_time INTEGER) RETURN VARCHAR2 AS
        v_temp_var DATE;
	v_seconds_offset NUMBER;
	v_hour NUMBER;
	v_minutes NUMBER;        
BEGIN

	SELECT extract(TIMEZONE_HOUR FROM CURRENT_TIMESTAMP)
             ,extract(TIMEZONE_MINUTE FROM CURRENT_TIMESTAMP) 
         INTO v_hour
             ,v_minutes
         FROM dual;

        v_seconds_offset := v_hour * 60 * 60 +  v_minutes * 60;

        v_temp_var := to_date('01-jan-1970 00:00:00', 'dd-mon-yyyy hh24:mi:ss') + ((inf_time + v_seconds_offset) / 86400);

        RETURN to_char(v_temp_var, 'DD-MON-YYYY HH24:MI:SS');
	
EXCEPTION
	WHEN others THEN
		dbms_output.put_line(sqlerrm);
END inf2ora_time_yyyy_offset;

FUNCTION ora2inf_time(ora_time DATE) RETURN INTEGER AS
BEGIN
        RETURN (ora_time - to_date('01-jan-1970', 'dd-mon-yyyy')) * 86400;
EXCEPTION
	WHEN others THEN
		dbms_output.put_line(sqlerrm);
END ora2inf_time;

FUNCTION ora2inf_time_offset(ora_time DATE) RETURN INTEGER AS
        v_seconds_offset NUMBER;
        v_hour NUMBER;
        v_minutes NUMBER;
BEGIN
        
        SELECT extract(TIMEZONE_HOUR FROM CURRENT_TIMESTAMP)
             ,extract(TIMEZONE_MINUTE FROM CURRENT_TIMESTAMP)
         INTO v_hour
             ,v_minutes
         FROM dual;

        v_seconds_offset := v_hour * 60 * 60 +  v_minutes * 60;

        RETURN ((ora_time - to_date('01-jan-1970 00:00:00', 'dd-mon-yyyy hh24:mi:ss')) * 86400 - v_seconds_offset);
EXCEPTION
        WHEN others THEN
                dbms_output.put_line(sqlerrm);
END ora2inf_time_offset;


FUNCTION table_exists (i_table_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN AS
	v_dummy VARCHAR2(1);
BEGIN
	SELECT '*' INTO v_dummy
	FROM user_tables
	WHERE table_name = UPPER(i_table_name);

	RETURN true;
EXCEPTION
	WHEN no_data_found THEN
		RETURN false;
	WHEN others THEN
		io_errmsg := sqlerrm;
		RETURN false;
END table_exists;


FUNCTION view_exists (i_view_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN AS
        v_dummy VARCHAR2(1);
BEGIN
        SELECT '*' INTO v_dummy
        FROM user_views
        WHERE view_name = UPPER(i_view_name);

        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN others THEN
                io_errmsg := sqlerrm;
                RETURN false;
END view_exists;


FUNCTION index_exists (i_index_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN AS
        v_dummy VARCHAR2(1);
BEGIN
        SELECT '*' INTO v_dummy
        FROM user_indexes
        WHERE index_name = UPPER(i_index_name);

        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN others THEN
                io_errmsg := sqlerrm;
                RETURN false;
END index_exists;


FUNCTION index_exists (i_index_name VARCHAR2, i_table_name IN VARCHAR2, 
			i_is_unique VARCHAR2, io_errmsg IN OUT VARCHAR2 )
RETURN BOOLEAN AS
	v_dummy VARCHAR2(1);
BEGIN
	SELECT '*' INTO v_dummy
	FROM user_indexes
	WHERE table_name = UPPER(i_table_name)
	AND index_name = UPPER(i_index_name)
	AND uniqueness = DECODE (UPPER(i_is_unique), 'YES', 'UNIQUE', 'NO', 'NONUNIQUE');

	RETURN true;
EXCEPTION
	WHEN no_data_found THEN
		RETURN false;
	WHEN others THEN
		io_errmsg := sqlerrm;
		RETURN false;
END index_exists;


FUNCTION index_exists (i_index_name VARCHAR2, i_table_name IN VARCHAR2, i_column_list IN VARCHAR2,  
			i_is_unique VARCHAR2, io_errmsg IN OUT VARCHAR2 )
RETURN BOOLEAN AS
	v_dummy VARCHAR2(1);
	occurrence INT := 1;
	prev_comma_position INT := 0;
	comma_position INT;
	col_name VARCHAR2(30);
BEGIN
        SELECT '*' INTO v_dummy
        FROM user_indexes
        WHERE table_name = UPPER(i_table_name)
        AND index_name = UPPER(i_index_name)
        AND uniqueness = DECODE (UPPER(i_is_unique), 'YES', 'UNIQUE', 'NO', 'NONUNIQUE');

	-- i_column_list contains the list of columns (seperated by commas) in the index,
	-- in the order it is in the index. Let us parse it now.
	
	LOOP 
		comma_position := instr(i_column_list, ',', 1, occurrence);

		IF (comma_position = 0) THEN
			col_name := substr(i_column_list, prev_comma_position+1);
		ELSE
			col_name := substr(i_column_list, prev_comma_position+1, comma_position - prev_comma_position - 1);
			prev_comma_position := comma_position;
		END IF; 

		col_name := UPPER (LTRIM(RTRIM(col_name)));

		SELECT '*' INTO v_dummy
		FROM user_ind_columns
		WHERE index_name = UPPER(i_index_name)
		AND column_name = col_name
		AND column_position = occurrence;

		occurrence := occurrence + 1;

		EXIT WHEN ( comma_position = 0 );
	END LOOP;

	-- If we are here, all the conditions are met.
        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN others THEN
                io_errmsg := sqlerrm;
                RETURN false;

END index_exists;

FUNCTION column_exists (i_table_name VARCHAR2, i_column_name IN VARCHAR2,
			io_errmsg IN OUT VARCHAR2 )
RETURN BOOLEAN AS
	v_dummy VARCHAR2(1);
BEGIN
	SELECT '*' INTO v_dummy
	FROM user_tab_columns
	WHERE table_name = UPPER(i_table_name)
	AND column_name = UPPER(i_column_name);

	RETURN true;
EXCEPTION
	WHEN no_data_found THEN
		RETURN false;
	WHEN others THEN
		io_errmsg := sqlerrm;
		RETURN false;
END column_exists;

FUNCTION sequence_exists (i_sequence_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN AS
        v_dummy VARCHAR2(1);
BEGIN
        SELECT '*' INTO v_dummy
        FROM user_sequences
        WHERE sequence_name = UPPER(i_sequence_name);

        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN others THEN
                io_errmsg := sqlerrm;
                RETURN false;
END sequence_exists;

FUNCTION partition_exists (i_table_name IN VARCHAR2, i_partition_name IN VARCHAR2,
                           i_high_value IN VARCHAR2, i_partition_position IN INT,
                           io_errmsg IN OUT VARCHAR2) 
RETURN BOOLEAN AS
        v_high_value VARCHAR2(100);
BEGIN
        SELECT high_value INTO v_high_value
        FROM user_tab_partitions
        WHERE table_name = UPPER(i_table_name)
        AND partition_name = UPPER(i_partition_name)
        AND partition_position = i_partition_position;

	IF (v_high_value = i_high_value) THEN
		RETURN TRUE;
	ELSE
		RETURN FALSE;
	END IF;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN others THEN
                io_errmsg := sqlerrm;
                RETURN false;
END partition_exists;

FUNCTION partition_exists (i_table_name IN VARCHAR2, i_partition_name IN VARCHAR2,
                           i_partition_position IN INT, io_errmsg IN OUT VARCHAR2) 
RETURN BOOLEAN AS
        v_dummy VARCHAR2(1);
BEGIN
        SELECT '*' INTO v_dummy
        FROM user_tab_partitions
        WHERE table_name = UPPER(i_table_name)
        AND partition_name = UPPER(i_partition_name)
        AND partition_position = i_partition_position;

        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN others THEN
                io_errmsg := sqlerrm;
                RETURN false;
END partition_exists;


FUNCTION synonym_exists (i_synonym_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN AS
        v_dummy VARCHAR2(1);
BEGIN
        SELECT '*' INTO v_dummy
        FROM user_synonyms
        WHERE synonym_name = UPPER(i_synonym_name);

        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN others THEN
		io_errmsg := sqlerrm;
                RETURN false;
END synonym_exists;


PROCEDURE log_info (i_step_name IN VARCHAR2, i_start_created_t IN INT, 
		    i_end_created_t IN INT, i_msg_type IN VARCHAR2, 
		    i_infranet_msg IN VARCHAR2, i_oracle_error IN VARCHAR2 DEFAULT NULL) IS
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
	INSERT INTO upg_log_t (step_name, 
			       curr_time, 
			       start_created_t, 
			       end_created_t, 
			       msg_type, 
			       infranet_msg, 
  			       oracle_error, 
			       log_type)
			VALUES (UPPER(i_step_name), 
				sysdate, 
				i_start_created_t,
				i_end_created_t,
				i_msg_type, 
				SUBSTR (i_infranet_msg, 1, 4000), 
				SUBSTR (i_oracle_error, 1, 250),
				NULL);

	COMMIT;

EXCEPTION
	WHEN others THEN
		dbms_output.put_line(sqlerrm);
END log_info;

PROCEDURE delete_info (i_step_name IN VARCHAR2) AS
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN

	--
	-- No actual deletion. Just make them history.
	--

	UPDATE upg_log_t SET log_type = 'H'
	WHERE step_name = UPPER(i_step_name);

	COMMIT;

EXCEPTION
	WHEN others THEN
		log_info(i_step_name, NULL, NULL, 'E', NULL, sqlerrm);
END delete_info;

PROCEDURE delete_error_info (i_step_name IN VARCHAR2) AS
PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN

        --
        -- No actual deletion. Just make them history.
        --

        UPDATE upg_log_t SET log_type = 'H'
        WHERE step_name = UPPER(i_step_name)
	AND msg_type = 'E';

        COMMIT;

EXCEPTION
        WHEN others THEN
                log_info(i_step_name, NULL, NULL, 'E', NULL, sqlerrm);
END delete_error_info;

FUNCTION step_completed (i_step_name IN VARCHAR2) 
RETURN BOOLEAN AS
        v_dummy VARCHAR2(1);
BEGIN
        SELECT '*' INTO v_dummy
        FROM upg_log_t
        WHERE step_name = UPPER(i_step_name)
	AND msg_type = 'C'
	AND log_type IS NULL;

        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN others THEN
		log_info(i_step_name, NULL, NULL, 'E', NULL, sqlerrm);
END step_completed;


FUNCTION step_completed (i_step_name IN VARCHAR2, i_start_created_t IN INT)
RETURN BOOLEAN AS
	v_min_start_created_t upg_log_t.start_created_t%TYPE;
BEGIN
        SELECT min(start_created_t) INTO v_min_start_created_t
        FROM upg_log_t
        WHERE step_name = UPPER(i_step_name)
	AND msg_type = 'I'
        AND log_type IS NULL;

	
	IF v_min_start_created_t IS NULL THEN
		RETURN FALSE;
	ELSIF (v_min_start_created_t > i_start_created_t) THEN
		RETURN FALSE;
	ELSIF (v_min_start_created_t <= i_start_created_t) THEN
        	RETURN true;
	END IF;

EXCEPTION
	WHEN others THEN
		log_info(i_step_name, NULL, NULL, 'E', NULL, sqlerrm);
		RETURN FALSE;	
END step_completed;


FUNCTION get_created_t_bounds (i_step_name IN VARCHAR2, i_interval IN INT, i_start_created_t IN INT, i_end_created_t IN INT,
				o_start_created_t OUT INT, o_end_created_t OUT INT) RETURN BOOLEAN AS

v_min_start_created_t upg_log_t.start_created_t%TYPE;
v_start_created_t upg_log_t.start_created_t%TYPE;
v_end_created_t upg_log_t.end_created_t%TYPE;

BEGIN

	--
	-- Let us see upto where we already processed the data.
	--

	SELECT min(start_created_t) INTO v_min_start_created_t
	FROM upg_log_t
        WHERE step_name = UPPER(i_step_name)
	AND msg_type = 'I'
        AND log_type IS NULL;

	--
	-- If v_min_start_created_t is NULL that means, this is the 
	-- first time we are trying to do this step.
	-- 

	IF v_min_start_created_t IS NULL THEN
		v_start_created_t := i_end_created_t - i_interval;
		v_end_created_t := i_end_created_t;

		-- 
		-- No need to process the rows below the user specied range.
		--

		IF (v_start_created_t < i_start_created_t) THEN
			v_start_created_t := i_start_created_t;
		END IF;

		-- Before returning assign the v_start_created_t and v_end_created_t to the OUT parameters

		o_start_created_t := v_start_created_t;
		o_end_created_t := v_end_created_t;
		RETURN TRUE;

	END IF;

	--
	-- If v_min_start_created_t is less than or equal to the range we specified, then we are done.
	--

	IF (v_min_start_created_t <= i_start_created_t) THEN
		RETURN FALSE;
	END IF;

	v_start_created_t := v_min_start_created_t - i_interval;
	v_end_created_t := v_min_start_created_t;

	IF (v_start_created_t < i_start_created_t) THEN
		v_start_created_t := i_start_created_t;
	END IF;

	-- Before returning assign the v_start_created_t and v_end_created_t to the OUT parameters

	o_start_created_t := v_start_created_t;
	o_end_created_t := v_end_created_t;
	RETURN TRUE;	

EXCEPTION
	WHEN others THEN
		log_info(i_step_name, NULL, NULL, 'E', NULL, sqlerrm);
		RETURN FALSE;	

END get_created_t_bounds;


PROCEDURE reset_obj_ids_seq AS
	v_dummy CHAR(1); 
        v_errmsg VARCHAR2(200);
	v_ddl_stmt VARCHAR2(2000);
        C_STEP_NAME upg_log_t.step_name%TYPE := 'reset_obj_ids_seq';

BEGIN
        /*
         * Before dropping the sequence, see whether there is previlege to
         * recreate.
         */

        BEGIN
               SELECT '*' INTO v_dummy
               FROM user_sys_privs
               WHERE privilege = 'CREATE SEQUENCE';
        EXCEPTION
               WHEN no_data_found THEN
                      log_info (C_STEP_NAME, NULL, NULL, 'E',
                               'User ' || USER || ' does not have CREATE SEQUENCE privileges ' ||
                               'directly granted. Please grant CREATE SEQUENCE previlege. ' ||
                               'Also it looks like the sanity checks were not ' ||
                               'performed before starting the upgrade. Please complete the ' ||
                               'sanity checks before proceeding.', NULL);
                      RETURN;
        END;

	BEGIN
        	IF (sequence_exists('obj_ids', v_errmsg)) THEN
	       		v_ddl_stmt := 'DROP SEQUENCE obj_ids';
               		EXECUTE IMMEDIATE v_ddl_stmt;
        	END IF;

        	v_ddl_stmt := 'CREATE SEQUENCE obj_ids START WITH ' || to_char(1000);
        	EXECUTE IMMEDIATE v_ddl_stmt;

	EXCEPTION
		WHEN others THEN
               		log_info (C_STEP_NAME, NULL, NULL, 'E', v_ddl_stmt, sqlerrm);
	END;
EXCEPTION
        WHEN OTHERS THEN
               log_info (C_STEP_NAME, NULL, NULL, 'E', 'Reinitializing the obj_ids sequence failed', sqlerrm);
END reset_obj_ids_seq;



PROCEDURE move_up_obj_ids_seq AS
    MAX_RESERVED_PORTAL_OBJ_ID CONSTANT PLS_INTEGER := 100000;
    v_new_obj_ids_seq_start PLS_INTEGER;
    v_next_obj_id0 PLS_INTEGER ;
    v_errmsg VARCHAR2(200);
    v_dummy CHAR(1);
    v_ddl_stmt VARCHAR2(2000);

    C_STEP_NAME upg_log_t.step_name%TYPE := 'move_up_obj_ids_seq';

BEGIN
        /*
         * obj_ids sequence is used to get the obj_id0 values for
         * the Infranet data dictionary .
         * If this sequence is with in Portal range, reinitialize it
         * to avoid future problems.
         */

         SELECT obj_ids.nextval
         INTO v_next_obj_id0
         FROM sys.dual;

         IF (v_next_obj_id0 <=  MAX_RESERVED_PORTAL_OBJ_ID) THEN
                SELECT NVL(max(obj_id0), 0) + MAX_RESERVED_PORTAL_OBJ_ID
                INTO v_new_obj_ids_seq_start
                FROM dd_objects_t;

                /*
                 * Before dropping the sequence, see whether there is previlege to
                 * recreate.
                 */

                BEGIN
                       SELECT '*' INTO v_dummy
                       FROM user_sys_privs
                       WHERE privilege = 'CREATE SEQUENCE';
                EXCEPTION
                       WHEN no_data_found THEN
                               log_info (C_STEP_NAME, NULL, NULL, 'E',
                                                        'User ' || USER || ' does not have CREATE SEQUENCE privileges ' ||
                                                        'directly granted. Please grant CREATE SEQUENCE previlege. ' ||
                                                        'Also it looks like the sanity checks were not ' ||
                                                        'performed before starting the upgrade. Please complete the ' ||
                                                        'sanity checks before proceeding.', NULL);
                               RETURN;
                END;

		BEGIN
                	IF (sequence_exists('obj_ids', v_errmsg)) THEN
                        	v_ddl_stmt := 'DROP SEQUENCE obj_ids';
                        	EXECUTE IMMEDIATE v_ddl_stmt;
                	END IF;

                	v_ddl_stmt := 'CREATE SEQUENCE obj_ids START WITH ' || TO_CHAR(v_new_obj_ids_seq_start);
                	EXECUTE IMMEDIATE v_ddl_stmt;
        	EXCEPTION
                	WHEN others THEN
                        	log_info (C_STEP_NAME, NULL, NULL,
                                                	'E', v_ddl_stmt, sqlerrm);
        	END;

         END IF;

EXCEPTION
                WHEN OTHERS THEN
                        log_info (C_STEP_NAME, NULL, NULL,
                                  'E', 'Reinitializing the obj_ids sequence failed', sqlerrm);
END move_up_obj_ids_seq;


PROCEDURE move_up_poid_ids_seq (i_interval IN INT) AS
	v_dummy INT;
    	C_STEP_NAME upg_log_t.step_name%TYPE := 'move_up_poid_ids_seq';
BEGIN
        FOR i IN 1 .. i_interval LOOP
                SELECT pin_sequence.get_nextval() INTO v_dummy FROM sys.dual;
        END LOOP;
EXCEPTION
	WHEN others THEN
                log_info (C_STEP_NAME, NULL, NULL,
                          'E', 'Error moving up the poid_ids sequence.', sqlerrm);
END move_up_poid_ids_seq;

FUNCTION new_poid RETURN NUMBER AS

	m_a					NUMBER:=0;
	m_b					NUMBER:=0;
	m_c					NUMBER:=0;
	m_d					NUMBER:=0;
	m_poid_id0				NUMBER:=0;


BEGIN
	SELECT pin_sequence.get_nextval() INTO m_a FROM dual;

	m_poid_id0 := TRUNC(m_a/4096)*4096;

	m_a := m_a-m_poid_id0;

	m_d := 2048;

	FOR m_b IN 1 .. 12
		LOOP
			m_c := TRUNC(m_a/2);
			IF (m_c*2) <> m_a
			THEN
				m_poid_id0 := m_poid_id0+m_d;
			END IF;
			m_a := m_c;
			m_d := TRUNC(m_d/2);
		END LOOP;

	RETURN m_poid_id0;

END NEW_POID;


END pin_upg_common;
/
