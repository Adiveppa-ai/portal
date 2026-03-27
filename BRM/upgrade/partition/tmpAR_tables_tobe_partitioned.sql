--
-- @(#)$Id: tmpAR_tables_tobe_partitioned.sql /cgbubrm_mainbrm.portalbase/2 2018/12/11 03:22:44 sagaur Exp $
--
-- Copyright (c) 2018, Oracle and/or its affiliates. All rights reserved.
--
--      This material is the confidential property of Oracle Corporation or
--      its licensors and may be used, reproduced, stored or transmitted only
--      in accordance with a valid Oracle license or sublicense agreement.
--
--
-- sql script to find the list of tmp AR tables to be partitioned.
--

DECLARE
        v_ddl_stmt VARCHAR2(4000);

        v_errmsg VARCHAR2(200);
        C_STEP_NAME upg_log_t.step_name%TYPE := 'tables_tobe_partitioned';
BEGIN
	pin_upg_common.delete_info (C_STEP_NAME);

        IF (NOT pin_upg_common.table_exists ('tables_tobe_partitioned_t', v_errmsg)) THEN
                v_ddl_stmt := 'CREATE TABLE tables_tobe_partitioned_t 
				(table_name VARCHAR2(30), base_name VARCHAR2(30), object_name VARCHAR2(30), partition_exchanged INT)
				$UPG_TEMPTBLS_TABLESPACE 
				STORAGE (initial 16k next 16k minextents 2)';

		EXECUTE IMMEDIATE v_ddl_stmt;
        END IF;

        IF (NOT pin_upg_common.table_exists ('partition_time_t', v_errmsg)) THEN
                v_ddl_stmt := 'CREATE TABLE partition_time_t 
				(partition_time DATE)
				$UPG_TEMPTBLS_TABLESPACE 
				STORAGE (initial 16k next 16k minextents 2)';

		EXECUTE IMMEDIATE v_ddl_stmt;
        END IF;
EXCEPTION
        WHEN OTHERS THEN
                pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'E', v_ddl_stmt, sqlerrm);
END;
/

DECLARE
	--
       	-- By default, pick up the tables that belong to class /tmp_ar_item_to_roll_up
       	--
       
	CURSOR partition_tables_cur IS
        SELECT DISTINCT (SUBSTR(dof.sm_item_name, DECODE(INSTR(dof.sm_item_name,'T='), 0, 1,INSTR(dof.sm_item_name,'T=')+2), 32))
	AS table_name
        FROM dd_objects_t do,dd_objects_fields_t dof
        WHERE do.obj_id0=dof.obj_id0
        AND (do.name = '/tmp_ar_item_to_roll_up') 
        AND dof.field_type IN (6, 9, 10, 11);
      
      	v_dummy CHAR(1);

        C_STEP_NAME upg_log_t.step_name%TYPE := 'tables_tobe_partitioned';
BEGIN
	pin_upg_common.delete_info (C_STEP_NAME);

	FOR partition_tables_rec IN partition_tables_cur LOOP	
      	BEGIN
      		--
             	-- Insert the table only if it is not already present.
             	--
             
      		SELECT '*' 
            	INTO v_dummy
            	FROM tables_tobe_partitioned_t
            	WHERE UPPER(table_name) = UPPER(partition_tables_rec.table_name);
            
      	EXCEPTION
      		WHEN no_data_found THEN
            		INSERT INTO tables_tobe_partitioned_t (table_name, base_name, object_name, partition_exchanged)
                  	VALUES (UPPER(partition_tables_rec.table_name), 'TMP_AR_ITEM_TO_ROLL_UP_T', '/tmp_ar_item_to_roll_up', 0);
                  
                  	COMMIT;
      		WHEN OTHERS THEN
               		pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'E', 
					'Error querying the tables_tobe_partitioned_t table', sqlerrm);
	END;
	END LOOP;

	--
	-- Insert the partition time to used in the partition_time_t table.
	--
     
	BEGIN
		SELECT '*' INTO v_dummy
		FROM partition_time_t;
	EXCEPTION
		WHEN no_data_found THEN
			INSERT INTO partition_time_t (partition_time) VALUES (SYSDATE);
			COMMIT;
		WHEN others THEN
               		pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'E', 
					'Error querying the partition_time_t table', sqlerrm);
	END;
	

EXCEPTION
	WHEN OTHERS THEN
               	pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'E', 
			'Error finding the tmpAR table names to be partitioned', sqlerrm);
END;
/

