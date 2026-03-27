--
-- @(#) $Id: optional_partition.sql /cgbubrm_7.5.0.portalbase/1 2015/11/27 06:09:28 nishahan Exp $
--
-- Copyright (c) 2005, 2015, Oracle and/or its affiliates. All rights reserved.
--
--      This material is the confidential property of Oracle Corporation or
--      its licensors and may be used, reproduced, stored or transmitted only
--      in accordance with a valid Oracle license or sublicense agreement.
--    
--
-- sql package to implement optional partitioning.
--

ALTER SESSION SET sql_trace = $SQL_TRACE;

--
-- Marker to identify the sql_trace file.
--

SELECT 'optional_partition.sql' 
FROM SYS.dual;

CREATE OR REPLACE PACKAGE optional_partition IS
       --
       -- Various constants used.
       --
       
       c_table_not_partitioned CONSTANT PLS_INTEGER := 0;
       c_table_partitioned CONSTANT PLS_INTEGER := 1;
       c_table_pin_partitioned CONSTANT PLS_INTEGER := 2;
       
       c_partition_migrate_hi_val CONSTANT INT := 2251799813685247; -- 2^51 -1

       c_historical_partition_hi_val CONSTANT INT := 4503599627370496; -- 2^52

	c_partition_lsb_44_bit CONSTANT VARCHAR2(45) := '11111111111111111111111111111111111111111111';

       c_monthly_partitions CONSTANT VARCHAR2(3) := UPPER('$MONTHLY_PARTITIONS');
       
       --
       -- Procedure to partition the given table as per BRM specifications.
       --
       
       PROCEDURE partition_given_optional_table (i_table_name IN VARCHAR2, i_base_name IN VARCHAR2);
       
       --
       -- Partitions all the optional table specified in the tables_tobe_partitioned_t table
       -- 
       
       PROCEDURE partition_all_optional_tables;
       
       --
       -- Function to check whether the table is partitoned.
       --
       
       FUNCTION is_table_partitioned (i_table_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2) RETURN BOOLEAN;
       
       -- 
       -- Function to check whether the table is partitioned as per BRM specifications.
       --

       FUNCTION partition_status (i_table_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2) RETURN PLS_INTEGER;

       FUNCTION is_index_partitioned (i_index_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2) RETURN BOOLEAN;
       
       PROCEDURE partition_index(v_table_name IN VARCHAR2, i_table_partition_status IN INT);
       
END optional_partition;
/

CREATE OR REPLACE PACKAGE BODY optional_partition IS

FUNCTION is_table_partitioned (i_table_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN AS
        v_dummy VARCHAR2(1);
BEGIN
        SELECT '*' INTO v_dummy
        FROM user_tab_partitions
        WHERE table_name = UPPER(i_table_name);

        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN too_many_rows THEN
                RETURN TRUE;
        WHEN others THEN
                io_errmsg := sqlerrm;
                RETURN false;
END is_table_partitioned;

PROCEDURE update_dd_partition_flag (i_table_name IN VARCHAR2, i_object_name IN VARCHAR2) AS
        v_errmsg VARCHAR2(200);
	C_STEP_NAME upg_log_t.step_name%TYPE := 'update_dd_objects_flag';
	v_update_dd_partition_cmd VARCHAR2(32767);
        v_table_name VARCHAR2(30) := UPPER(i_table_name);
        v_object_name VARCHAR2(30) := i_object_name;
BEGIN
     
     pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'I', 
                             'Table:: ' || v_table_name, 
                              NULL);
        -- If optional_t table is partitioned, user is using the partition option.
        -- Update the Infranet data dictionary to reflect this.
        

       IF (pin_upg_common.partition_exists (v_table_name, 'partition_migrate',
                                                to_char(c_partition_migrate_hi_val), 1, v_errmsg)) THEN

		-- is_partitioned values : 0 ==> The tables for this object is not partitioned.
                --                         1 ==> The tables for this object are partitioned.
                --                         2 ==> The tables for this object are partitioned in 12.0 PS 2
                -- partition_mode values : 0 ==> The tables for this object partitioned as partition_historic.
                --                         1 ==> The tables for this object partitioned as partition_finite.
                IF (v_object_name = '/item' OR v_object_name = '/event') THEN
                        v_update_dd_partition_cmd := 'UPDATE dd_objects_t
                        SET is_partitioned = 2, partition_mode=1
                        WHERE name = ''' || v_object_name || ''' or name like ''' || v_object_name || '/%' || '''';
                ELSE
                        v_update_dd_partition_cmd := 'UPDATE dd_objects_t
                        SET is_partitioned = 1, partition_mode=1
                        WHERE name = ''' || v_object_name || ''' or name like ''' || v_object_name || '/%' || '''';
                END IF;

                EXECUTE IMMEDIATE v_update_dd_partition_cmd;
       END IF;

EXCEPTION
        WHEN others THEN
                pin_upg_common.log_info (C_STEP_NAME, NULL, NULL,
                                        'E', 'Error updating is_partitioned and partition_mode flag in Infranet data dictionary.', sqlerrm);
END update_dd_partition_flag;


FUNCTION is_index_partitioned (i_index_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN BOOLEAN AS
        v_dummy VARCHAR2(1);
BEGIN
        SELECT '*' INTO v_dummy
        FROM user_part_indexes
        WHERE index_name = UPPER(i_index_name);

        RETURN true;
EXCEPTION
        WHEN no_data_found THEN
                RETURN false;
        WHEN too_many_rows THEN
                RETURN TRUE;
        WHEN others THEN
                io_errmsg := sqlerrm;
                RETURN false;
END is_index_partitioned;

FUNCTION partition_status (i_table_name IN VARCHAR2, io_errmsg IN OUT VARCHAR2)
RETURN PLS_INTEGER AS
        v_dummy VARCHAR2(1);
        v_partition_name user_tab_partitions.partition_name%TYPE;
        
        v_partition_status PLS_INTEGER := c_table_not_partitioned;
        
BEGIN

       -- Is the table partitioned?

       IF (NOT is_table_partitioned (i_table_name, io_errmsg)) THEN
               RETURN v_partition_status;
       END IF;
       
       v_partition_status := c_table_partitioned;
       
       -- Is the table partitioned as per BRM specification?
       
       --
       -- See whether we can find the partition for migrated objects?
       --
       
       IF (NOT pin_upg_common.partition_exists (i_table_name, 'partition_migrate', 
                                                to_char(c_partition_migrate_hi_val), 1, io_errmsg)) THEN
               RETURN v_partition_status;
       END IF;
       
       IF (NOT pin_upg_common.partition_exists (i_table_name, 'partition_historic', 
                                                to_char(c_historical_partition_hi_val), 2, io_errmsg)) THEN
               RETURN v_partition_status;
       END IF;

       --
       -- Let us check partition_last 
       --

       IF (NOT pin_upg_common.partition_exists (i_table_name, 'partition_last',
                                                'MAXVALUE', 15, io_errmsg)) THEN
               RETURN v_partition_status;
       END IF;
                                                      
       IF (c_monthly_partitions = 'YES') THEN
       	        -- 
                -- What about the standard 12 partitions we recomend?
                --
      
                FOR i IN 1 .. 12 LOOP
               		v_partition_name := 'P_' || to_char (i);
               		IF (NOT pin_upg_common.partition_exists (i_table_name, v_partition_name, 
                                                i+2, io_errmsg)) THEN
                       		RETURN v_partition_status;
               		END IF;
       		END LOOP;
       END IF;

       v_partition_status := c_table_pin_partitioned;
       
       RETURN v_partition_status;
       
EXCEPTION 
       WHEN OTHERS THEN
              io_errmsg := SQLERRM;
              RETURN v_partition_status;
END partition_status;

PROCEDURE partition_given_optional_table (i_table_name IN VARCHAR2, i_base_name IN VARCHAR2) AS

          v_table_info_rec user_tables%ROWTYPE;
          v_table_name VARCHAR2(30) := UPPER(i_table_name);
          v_base_name VARCHAR2(30) := UPPER(i_base_name);
          
          --
          -- Cursors to get all the indexes for the given table.
          --
          
          CURSOR index_cur IS 
          SELECT *
          FROM user_indexes 
          WHERE table_name = v_table_name
	  AND index_name NOT like 'SYS_%\$\$'; -- ignore the indexes that are used for maintaining the BLOBs;
          
          v_crt_table_cmd VARCHAR2(32767);
          v_partition_table_cmd VARCHAR2(32767);
          v_partitioned_temp_table VARCHAR2(30);
          v_errmsg VARCHAR2(200);
          
          C_STEP_NAME upg_log_t.step_name%TYPE := v_table_name || '_partition';
          
          v_partition_time DATE;
          
          v_partition_status PLS_INTEGER;   
          v_partition_key VARCHAR2(30);
          v_storage_info VARCHAR2(1000);
          v_storage VARCHAR2(4000);
          v_p_x_partition_hi_val INT; -- Upper bound for the P_x partition; x is 1 .. 12
          
          v_partition_exchanged INT;

          CURSOR raw_cur is 
             SELECT column_name
                   ,data_length
               FROM cols
              WHERE table_name = v_table_name
                AND data_type = 'RAW';

          v_ddl_stmt VARCHAR2(200);
-- column spec for create table instead of ' as select * from'
          v_col_desc VARCHAR2(32767); 
          v_dbms_metadata CLOB;
          v_dbms_metadatalen  INTEGER; 
          v_start_col_desc INTEGER;
          v_end_col_desc INTEGER;


BEGIN

     pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'I', 
                             'Table:: ' || v_table_name, 
                              NULL);
     --
     -- Does this table exist?
     --
     
     IF (NOT pin_upg_common.table_exists (v_table_name, v_errmsg)) THEN
          pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'E', 
                                  'Table ' ||v_table_name || ' does not exist.', 
                                  v_errmsg);
          RETURN;
     END IF;
     
     --
     -- If the table is already partitioned as per BRM specs, no more processing needed.
     --
     
     v_partition_status := partition_status(v_table_name, v_errmsg);
     
     IF (v_errmsg IS NOT NULL) THEN
          pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'E', NULL, v_errmsg);
          RETURN;
     END IF;     
     
     IF (v_partition_status = c_table_pin_partitioned) THEN
             pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'I', 
                                     v_table_name ||' table is already partitioned as per BRM specifications.', 
                                     NULL);
             partition_index(v_table_name,1);
             RETURN;
     ELSIF (v_partition_status = c_table_partitioned) THEN
             pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'W', 
                                     v_table_name ||' table is already partitioned. ' ||
                                     ' Skipping this table.', 
                                     NULL);
             partition_index(v_table_name,1);
             RETURN;
     END IF;
     
     IF (v_table_name = v_base_name) THEN
           v_partition_key := 'poid_id0';
     ELSE
           v_partition_key := 'obj_id0';
     END IF;
     
     --
     -- Create another temporary optional table with same attributes.
     -- This temp table will have the same name except for the last letter.
     -- Last letter will be "P" instead of the normal "T".
     -- The initial partition (called partition_migrate) will have a small initial, 
     -- next and min extent values. This will be dropped after the partition exchange, 
     -- So why allocate lot of space.
     --
     -- We will also pre-create 13 more partitions (p_1 .. p_12 and partition_last) to hold next 12 months 
     -- data. For each of these partitions, the initial extent, next extent and 
     -- all other storage parameter will be same as the orginal optional table which is going to be 
     -- partitioned.
     --

     v_partitioned_temp_table := SUBSTR (v_table_name, 1, LENGTH (v_table_name) - 1) || 'P';
     
     --
     -- Get all the data related to this table.
     --
     
     BEGIN
          SELECT * 
          INTO v_table_info_rec
          FROM user_tables
          WHERE table_name = UPPER(v_table_name);
     EXCEPTION
          WHEN OTHERS THEN
               pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'E', 
                                     'Error getting information about table ' || v_table_name, 
                                     NULL);
     END;
         

               IF v_table_info_rec.tablespace_name IS NOT NULL THEN
                    v_storage_info := ' TABLESPACE ' || v_table_info_rec.tablespace_name;
                END IF;

                IF v_table_info_rec.ini_trans IS NOT NULL THEN
                   v_storage_info := NVL(v_storage_info,' ') || ' INITRANS ' || v_table_info_rec.ini_trans ;
                END IF;
                      
                IF v_table_info_rec.initial_extent IS NOT NULL THEN
                   v_storage  :=  ' INITIAL ' || v_table_info_rec.initial_extent ;
                END IF;                

                IF v_table_info_rec.next_extent IS NOT NULL THEN 
                   v_storage := v_storage || ' NEXT ' || v_table_info_rec.next_extent ;
                END IF;

                IF v_table_info_rec.min_extents IS NOT NULL THEN 
                   v_storage := v_storage || ' MINEXTENTS ' || v_table_info_rec.min_extents  ;
                END IF;

                IF v_table_info_rec.max_extents IS NOT NULL THEN 
                   v_storage := v_storage || ' MAXEXTENTS ' || v_table_info_rec.max_extents  ;
                END IF;

                IF v_table_info_rec.pct_increase IS NOT NULL THEN 
                   v_storage := v_storage || ' PCTINCREASE ' || v_table_info_rec.pct_increase ;
                END IF;


                IF v_table_info_rec.freelists IS NOT NULL THEN 
                   v_storage := v_storage || ' FREELISTS ' || v_table_info_rec.freelists ;
                END IF;

                IF v_storage IS NOT NULL THEN
                   v_storage_info  := v_storage_info  || ' STORAGE (' || v_storage || ')';
                END IF;
                 
                IF v_table_info_rec.pct_free IS NOT NULL THEN
                   v_storage_info  := v_storage_info  || ' PCTFREE ' || v_table_info_rec.pct_free;
                END IF; 
                       
     v_crt_table_cmd := 'CREATE TABLE '|| v_partitioned_temp_table  || ' ' ;

     IF (v_base_name = 'ITEM_T' OR v_base_name = 'EVENT_T') THEN
         v_partition_table_cmd := ' PARTITION BY RANGE (' || v_partition_key || ' ) ' ||
                        '(PARTITION partition_migrate VALUES LESS THAN (' || to_char(c_partition_migrate_hi_val) || '), ' ||
                        'PARTITION partition_historic VALUES LESS THAN ( ' || to_char(c_historical_partition_hi_val) || ') ';
     ELSE
         v_partition_table_cmd := ' PARTITION BY RANGE (' || v_partition_key || ' ) ' ||
                        '(PARTITION partition_migrate VALUES LESS THAN (' || to_char(c_partition_migrate_hi_val) || ') ';
     END IF;
     
     --
     -- Get the partitioning time.
     -- This time has to be the same for all optional tables.
     -- Otherwise the partition boundaries will be inconsistant.
     --
     
     BEGIN
            SELECT partition_time INTO v_partition_time
            FROM partition_time_t;
     EXCEPTION
            WHEN no_data_found THEN
                  pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                          'Unable to find partitioning time. partition_time_t table is empty.', 
                                          SQLERRM);
                  RAISE;
            WHEN too_many_rows THEN      
                  pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                          'More than one partitioning time found in the partition_time_t table.', 
                                          SQLERRM);   
                  RAISE;     
            WHEN OTHERS THEN
                  pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                          'Unable to find partitioning time.', 
                                          SQLERRM);
                  RAISE;
     END;       
     
     IF (c_monthly_partitions = 'YES') THEN
      	    FOR i IN 1 .. 12 LOOP
            DECLARE
                  v_days_since_start_time PLS_INTEGER;
                  v_p_x_partition_name VARCHAR2(10);
            BEGIN  
                  v_p_x_partition_name := 'P_' || to_char(i);

                  --  
                  -- 01-JAN-1970 is considered as day 1, that is why we need to add 1, to get the correct result.
                  --

            	  v_days_since_start_time :=  add_months(v_partition_time, i) - to_date('01-JAN-1970', 'DD-MON-YYYY') + 1;
            
                  --
                  -- Append this date encoding as the most significant bits
                  --
            
                  v_p_x_partition_hi_val := pin_upg_common.bin_to_dec(pin_upg_common.dec_to_bin( v_days_since_start_time) || 
		      							      c_partition_lsb_44_bit);

--                  v_crt_table_cmd := v_crt_table_cmd || ', PARTITION ' || v_p_x_partition_name || 
--                                                            ' VALUES LESS THAN (' || to_char(v_p_x_partition_hi_val) || ')';
                   
            END;
            END LOOP;
     END IF;

--     v_crt_table_cmd := v_crt_table_cmd || ', PARTITION partition_last_pin VALUES LESS THAN (1152921504606846976)';
 
     
     v_partition_table_cmd := v_partition_table_cmd || ', PARTITION partition_last VALUES LESS THAN (MAXVALUE)';
     v_partition_table_cmd := v_partition_table_cmd || ')' || v_storage_info;

-- With virtual columns, CTAS results in losing the virtualness in the 
-- target table so exchange partition will fail. So we get the table
-- metadata and use that instead.
--     v_crt_table_cmd := v_crt_table_cmd || ' AS SELECT * FROM ' || v_table_name || ' WHERE 1 = 2';

     DBMS_METADATA.SET_TRANSFORM_PARAM (DBMS_METADATA.SESSION_TRANSFORM, 'SEGMENT_ATTRIBUTES', false);
     v_dbms_metadata  := DBMS_METADATA.GET_DDL('TABLE', v_table_name);
     v_dbms_metadatalen  := DBMS_LOB.GETLENGTH(v_dbms_metadata);
     v_start_col_desc := DBMS_LOB.INSTR(v_dbms_metadata, '(', 1);
     v_end_col_desc := DBMS_LOB.INSTR(v_dbms_metadata, CHR(10) || '   )', 1);

     v_col_desc  := DBMS_LOB.SUBSTR(v_dbms_metadata, v_end_col_desc - v_start_col_desc + 5, v_start_col_desc);


     v_crt_table_cmd := v_crt_table_cmd || v_col_desc || ' ' || v_partition_table_cmd;
     
     
     -- 
     -- Create this table only if it is not already created.
     --
      
     IF (NOT pin_upg_common.table_exists(v_partitioned_temp_table, v_errmsg)) THEN  
     BEGIN
             EXECUTE IMMEDIATE v_crt_table_cmd;    

             FOR REC in raw_cur LOOP
                 v_ddl_stmt := 'ALTER TABLE ' || v_partitioned_temp_table || ' MODIFY ( ' || rec.column_name || ' RAW(' || rec.data_length || '))';
                 EXECUTE IMMEDIATE v_ddl_stmt;
             END LOOP;

     EXCEPTION
              WHEN OTHERS THEN
                   pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', v_crt_table_cmd, SQLERRM);
                   RAISE; -- Cannot continue, goto the outer exception handler.
     END;  
     END IF;                                 
     
     --
     -- Scan through all the indexes and create temporary local indexes.
     -- The name for these temporary indexes is same as the original index, 
     -- except for the first letter (it will be L). 
     --
     
     partition_index(v_table_name,0);
     --
     -- Do the exchange partition including the indexes.
     -- Also no validating the existing data.
     --

     DECLARE
             v_xcnge_partition_cmd VARCHAR2(4000);
     BEGIN
             BEGIN
                  SELECT partition_exchanged INTO v_partition_exchanged
                  FROM tables_tobe_partitioned_t
                  WHERE table_name = v_table_name;
             EXCEPTION
                  WHEN no_data_found THEN
                         pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                                 'Unable to find entry for table ' ||
                                                  v_table_name || ' in tables_tobe_partitioned_t table.', 
                                                  NULL);
                         RAISE;  
                  WHEN too_many_rows THEN
                         pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                                 'More than one entry for table ' ||
                                                  v_table_name || ' in tables_tobe_partitioned_t table.', 
                                                  NULL);
                         RAISE;                                
                  WHEN OTHERS THEN
                         pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                                 'Error getting entry for table ' ||
                                                  v_table_name || ' in tables_tobe_partitioned_t table.', 
                                                  SQLERRM);
                         RAISE;                                                          
             END;      
                                 
             IF (v_partition_exchanged = 0) THEN
                    v_xcnge_partition_cmd := 'ALTER TABLE ' || v_partitioned_temp_table || 
                                             ' EXCHANGE PARTITION partition_migrate WITH TABLE ' ||
                                             v_table_name || ' INCLUDING INDEXES WITHOUT VALIDATION'; 
                                                
                    BEGIN
                         EXECUTE IMMEDIATE v_xcnge_partition_cmd;
                    EXCEPTION
                         WHEN OTHERS THEN    
                                pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                                 v_xcnge_partition_cmd, 
                                                 SQLERRM);
                                RAISE;  
                    END;
                    
                    BEGIN
                         UPDATE tables_tobe_partitioned_t
                         SET partition_exchanged = 1
                         WHERE table_name = v_table_name;
                         
                         IF (SQL%ROWCOUNT =0) THEN
                              RAISE no_data_found;
                         END IF;
                         
                         COMMIT;  
                    EXCEPTION   
                         WHEN OTHERS THEN
                                pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                                 'Error updating tables_tobe_partitioned_t table', 
                                                 SQLERRM);
                                RAISE;  
                    END;
             END IF;
     END;
     
     --
     -- Drop the original table and rename the new partitioned table to the old name.
     -- But only if the partition exchange is complete.
     --

     BEGIN
          SELECT partition_exchanged INTO v_partition_exchanged
          FROM tables_tobe_partitioned_t
          WHERE table_name = v_table_name;
     EXCEPTION                          
          WHEN OTHERS THEN
                  pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', 
                                          'Error getting entry for table ' ||
                                          v_table_name || ' in tables_tobe_partitioned_t table.', 
                                           SQLERRM);
                  RAISE;                                                          
     END;  
          
     IF (v_partition_exchanged = 1) THEN
           DECLARE
                  v_ddl_cmd VARCHAR2(1000);
           BEGIN
                v_ddl_cmd := 'DROP TABLE ' || v_table_name;
                IF (pin_upg_common.table_exists(v_table_name, v_errmsg)) THEN
                       EXECUTE IMMEDIATE v_ddl_cmd;
                END IF;

                v_ddl_cmd := 'RENAME ' || v_partitioned_temp_table || ' TO ' || v_table_name;
           
                IF (pin_upg_common.table_exists(v_partitioned_temp_table, v_errmsg) AND
                               (NOT pin_upg_common.table_exists(v_table_name, v_errmsg))) THEN
                       EXECUTE IMMEDIATE v_ddl_cmd;
                END IF;
                
           EXCEPTION
                WHEN OTHERS THEN
                       pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', v_ddl_cmd, SQLERRM);
                       RAISE;
           END;
     
           FOR index_rec IN index_cur LOOP
           DECLARE
                 v_new_local_index_name VARCHAR2(30);
                 v_alter_index_cmd VARCHAR2(4000);
           BEGIN
                 v_new_local_index_name := 'I' || SUBSTR (index_rec.index_name, 2, LENGTH(index_rec.index_name) - 1);
             
                 v_alter_index_cmd := 'ALTER INDEX ' || index_rec.index_name || ' RENAME TO ' || v_new_local_index_name;
                 
                 IF (NOT pin_upg_common.index_exists (v_new_local_index_name, v_errmsg)) THEN
                      EXECUTE IMMEDIATE v_alter_index_cmd;
                 END IF;
             
           EXCEPTION
                 WHEN OTHERS THEN
                       pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', v_alter_index_cmd, SQLERRM);
                       RAISE;
           END;
           END LOOP;
     END IF;
     
     pin_upg_common.log_info (C_STEP_NAME, NULL, NULL, 'C', 
                             v_table_name || ' partitioned as per BRM specifications.',
                             NULL);
EXCEPTION 
          WHEN OTHERS THEN
                 pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', NULL, SQLERRM);
END partition_given_optional_table;

PROCEDURE partition_all_optional_tables IS
     v_partition_status PLS_INTEGER;
     v_errmsg VARCHAR2(200);

     CURSOR optional_tables_cur IS
     SELECT table_name , base_name, object_name 
     FROM tables_tobe_partitioned_t;

     v_base_name tables_tobe_partitioned_t.base_name%TYPE;

     C_STEP_NAME upg_log_t.step_name%TYPE := 'optional_partition';

BEGIN
     pin_upg_common.delete_info (C_STEP_NAME);

     FOR optional_tables_rec IN optional_tables_cur LOOP
        v_base_name := UPPER(optional_tables_rec.base_name);
          IF (v_base_name = 'ITEM_T' OR v_base_name = 'EVENT_T') THEN
                v_partition_status := partition_status(optional_tables_rec.table_name, v_errmsg);
                IF (v_partition_status = 0) THEN
                        partition_given_optional_table (optional_tables_rec.table_name, optional_tables_rec.base_name);

                        -- Now update the dd_objects_t partition flag through this procedure.
                        IF (optional_tables_rec.table_name = optional_tables_rec.base_name) THEN

                                update_dd_partition_flag(optional_tables_rec.table_name, optional_tables_rec.object_name);
                        END IF;
                END IF;
           ELSE
                 partition_given_optional_table (optional_tables_rec.table_name, optional_tables_rec.base_name);

                -- Now update the dd_objects_t partition flag through this procedure.
                IF (optional_tables_rec.table_name = optional_tables_rec.base_name) THEN

                        update_dd_partition_flag(optional_tables_rec.table_name, optional_tables_rec.object_name);
                END IF;
           END IF;
     END LOOP;


EXCEPTION
     WHEN others THEN
          pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', NULL, SQLERRM);
END partition_all_optional_tables;

PROCEDURE partition_index(v_table_name IN VARCHAR2,i_table_partition_status IN INT) IS
    v_temp_local_index_name VARCHAR2(30);
    v_crt_index_cmd VARCHAR2(4000);
    v_index_storage_info VARCHAR2(4000);
    v_storage_info VARCHAR2(4000);
    v_storage VARCHAR2(4000);
    v_partitioned_temp_table VARCHAR2(30);
    
    v_ddl_stmt VARCHAR2(4000);
    v_return_msg VARCHAR2(2000);
    
    CURSOR index_cur IS 
    SELECT *
    FROM user_indexes 
    WHERE table_name = v_table_name
    AND index_name NOT like 'SYS_%\$\$'; -- ignore the indexes that are used for maintaining the BLOBs;

    CURSOR index_col_cur (i_index_name IN VARCHAR2) IS 
    SELECT column_position, column_name
    FROM user_ind_columns 
    WHERE index_name = i_index_name
    ORDER BY column_position;

    C_STEP_NAME upg_log_t.step_name%TYPE := 'partition_index';
BEGIN

     v_partitioned_temp_table := SUBSTR (v_table_name, 1, LENGTH (v_table_name) - 1) || 'P';
     
     FOR index_rec IN index_cur LOOP
     BEGIN
     
                IF index_rec.tablespace_name IS NOT NULL THEN
                    v_index_storage_info := ' TABLESPACE ' || index_rec.tablespace_name;
                END IF;

                IF index_rec.ini_trans IS NOT NULL THEN
                   v_index_storage_info := NVL(v_index_storage_info,' ') || ' INITRANS ' || index_rec.ini_trans ;
                END IF;                      
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

             v_temp_local_index_name := 'L' || SUBSTR (index_rec.index_name, 2, LENGTH(index_rec.index_name) - 1);
             
             IF (index_rec.uniqueness = 'UNIQUE') THEN
                   v_crt_index_cmd := 'CREATE UNIQUE INDEX ' || v_temp_local_index_name;
             ELSE
                   v_crt_index_cmd := 'CREATE INDEX ' || v_temp_local_index_name;
             END IF;
             
             v_crt_index_cmd := v_crt_index_cmd || ' ON ' || v_partitioned_temp_table || '(';
             
             FOR index_col_rec IN index_col_cur (index_rec.index_name) LOOP
                   v_crt_index_cmd := v_crt_index_cmd || index_col_rec.column_name || ', ';              
             END LOOP;   

             v_crt_index_cmd := SUBSTR (v_crt_index_cmd, 1, LENGTH(v_crt_index_cmd) - 2);
             
             -- Adding the storage info for the indexes.

             v_crt_index_cmd := v_crt_index_cmd || ') LOCAL ' || v_index_storage_info;

             
             
             IF(i_table_partition_status = 1) THEN                
             	IF (pin_upg_common.index_exists (index_rec.index_name, v_return_msg)) THEN
             	      IF (NOT is_index_partitioned (index_rec.index_name, v_return_msg)) THEN
		      	v_ddl_stmt := 'DROP INDEX ' || index_rec.index_name;
		   	EXECUTE IMMEDIATE v_ddl_stmt;
		   	
		   	v_crt_index_cmd := REPLACE(v_crt_index_cmd,v_partitioned_temp_table,v_table_name);
		   	EXECUTE IMMEDIATE v_crt_index_cmd;
		      END IF;
		ELSE
			EXECUTE IMMEDIATE v_crt_index_cmd;
                END IF;		
	     ELSE	     
             	IF (NOT pin_upg_common.index_exists (v_temp_local_index_name, v_return_msg)) THEN
                   EXECUTE IMMEDIATE v_crt_index_cmd;
             	END IF;
             END IF;         
     EXCEPTION
             WHEN OTHERS THEN
                  pin_upg_common.log_info(C_STEP_NAME, NULL, NULL, 'E', v_crt_index_cmd, SQLERRM);
                  RAISE;
     END;   
     END LOOP;
END;     

END optional_partition;
/

SHOW ERRORS

EXEC optional_partition.partition_all_optional_tables;

