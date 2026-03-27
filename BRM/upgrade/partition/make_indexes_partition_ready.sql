--
-- @(#)$Id: make_indexes_partition_ready.sql /cgbubrm_7.5.0.portalbase/1 2015/11/27 06:10:05 nishahan Exp $
--
-- Copyright (c) 2001, 2015, Oracle and/or its affiliates. All rights reserved.
--
--      This material is the confidential property of Oracle Corporation or
--      its licensors and may be used, reproduced, stored or transmitted only
--      in accordance with a valid Oracle license or sublicense agreement.
--
--

ALTER SESSION SET sql_trace = $SQL_TRACE;

--
-- Marker to identify the sql_trace file.
--

SELECT 'make_indexes_partition_ready.sql'
FROM SYS.dual;


/*
 * If there are unique indexes without the partitioning key (poid_id0/obj_id0)
 * partition key should be added.
 *
 * This procedure checks all the indexes in the given table and if there are 
 * any indexes with the above condition, adds the partition key to the index.
 * 
 * Can be called from the SQL prompt as well. Also calling it many times
 * does not cause any harm.
 */

CREATE OR REPLACE PROCEDURE make_indexes_partition_ready (
	i_table_name VARCHAR2,
	i_base_name VARCHAR2) is

	--
	-- Cursors to get all the indexes for the given table.
	--

	CURSOR index_cur IS
	SELECT *
	FROM user_indexes
	WHERE table_name = i_table_name
	AND index_name NOT like 'SYS_%\$\$'; -- ignore the indexes that are used for maintaining the BLOBs

	CURSOR index_col_cur (i_index_name IN VARCHAR2) IS
	SELECT column_name
	FROM user_ind_columns
	WHERE index_name = i_index_name
	ORDER BY column_position;
        
        e_skip_index EXCEPTION;
        
        v_poid_column VARCHAR2(30);
        v_poid_in_index BOOLEAN;
        v_errmsg VARCHAR2(200);
        
        C_STEP_NAME upg_log_t.step_name%TYPE := 'make_indexes_partition_ready::' || i_table_name;
BEGIN

        pin_upg_common.delete_info (C_STEP_NAME);

        IF (i_table_name = i_base_name) THEN
                v_poid_column := 'POID_ID0';
        ELSE
                v_poid_column := 'OBJ_ID0';
        END IF;
        
	FOR index_rec IN index_cur LOOP
        DECLARE
             v_crt_index_cmd VARCHAR2(4000);
             v_index_storage_info VARCHAR2(4000);
             v_storage VARCHAR2(4000);
        BEGIN
                --
                -- We do not care about the nonunique indexes.
                --
                
                IF (index_rec.uniqueness = 'NONUNIQUE') THEN 
                      RAISE e_skip_index;
                END IF;

                v_index_storage_info := ' TABLESPACE ' || index_rec.tablespace_name || ' INITRANS ' || index_rec.ini_trans ;
                      
                IF index_rec.initial_extent IS NOT NULL THEN
                   v_storage  :=  ' INITIAL ' || index_rec.initial_extent ;
                END IF;                

                IF index_rec.next_extent IS NOT NULL THEN 
                   v_storage := v_storage || ' NEXT ' || index_rec.next_extent ;
                END IF;

                IF index_rec.min_extents IS NOT NULL THEN 
                   v_storage := v_storage || ' MINEXTENTS ' || index_rec.min_extents  ;
                END IF;

                IF index_rec.max_extents IS NOT NULL THEN 
                   v_storage := v_storage || ' MAXEXTENTS ' || index_rec.max_extents  ;
                END IF;

                IF index_rec.pct_increase IS NOT NULL THEN 
                   v_storage := v_storage || ' PCTINCREASE ' || index_rec.pct_increase ;
                END IF;


                IF index_rec.freelists IS NOT NULL THEN 
                   v_storage := v_storage || ' FREELISTS ' || index_rec.freelists ;
                END IF;

                IF v_storage IS NOT NULL THEN
                   v_index_storage_info  := v_index_storage_info  || ' STORAGE (' || v_storage || ')';
                END IF;
                 
                IF index_rec.pct_free IS NOT NULL THEN
                   v_index_storage_info  := v_index_storage_info  || ' PCTFREE ' || index_rec.pct_free;
                END IF; 
                       
                v_crt_index_cmd := 'CREATE UNIQUE INDEX ' || index_rec.index_name || ' ON ' || index_rec.table_name || '(';    
                       
                v_poid_in_index := FALSE;
                
		FOR index_col_rec IN index_col_cur(index_rec.index_name) LOOP
                      v_crt_index_cmd := v_crt_index_cmd || index_col_rec.column_name || ', ';
                      
                      IF (index_col_rec.column_name = v_poid_column) THEN
                            v_poid_in_index := TRUE;        
                      END IF;
		END LOOP;
                
                --
                -- If the poid_id0/obj_id0 is part of this index, there is no need to proceed further.
                -- Else drop this index and recreate it with the poid column.
                --
                
                IF (v_poid_in_index) THEN
                      RAISE e_skip_index;                
                END IF;
                
                v_crt_index_cmd := v_crt_index_cmd || v_poid_column || ')' || v_index_storage_info;
                
                BEGIN
                     EXECUTE IMMEDIATE 'DROP INDEX ' || index_rec.index_name;
                EXCEPTION
                     WHEN OTHERS THEN
                          pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                                  'Unable to drop the index ' || index_rec.index_name,
                                                  SQLERRM);
                          RAISE;
                END;
                
                IF (NOT pin_upg_common.index_exists (index_rec.index_name, v_errmsg)) THEN
                BEGIN
                      EXECUTE IMMEDIATE v_crt_index_cmd;
                EXCEPTION
                      WHEN OTHERS THEN
                          pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                                  'Index creation failed:: Run this command manually to create the index ' || v_crt_index_cmd,
                                                  SQLERRM);
                          RAISE;
                END;
                END IF;

		pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'C', 
					'Index ' || index_rec.index_name || ' recreated with ' || v_poid_column || ' column.',
					NULL);
        EXCEPTION
                 WHEN e_skip_index THEN
                      NULL;   
        END;
	END LOOP;   
 
EXCEPTION
        WHEN OTHERS THEN
             pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', NULL, SQLERRM);
END make_indexes_partition_ready;
/


DECLARE
        C_STEP_NAME upg_log_t.step_name%TYPE := 'make_indexes_partition_ready';

BEGIN
	pin_upg_common.delete_info (C_STEP_NAME);

	FOR event_tables_rec IN (SELECT table_name, base_name FROM tables_tobe_partitioned_t) LOOP
        	make_indexes_partition_ready (event_tables_rec.table_name, event_tables_rec.base_name);
	END LOOP;
END;
/

