--
-- @(#) %full_filespec: crt_upg_indexes.sql~2:sql:1 %
--
--      Copyright (c) 2001 - 2006 Oracle. All rights reserved.
--
--      This material is the confidential property of Oracle Corporation or
--      its licensors and may be used, reproduced, stored or transmitted only
--      in accordance with a valid Oracle license or sublicense agreement.
--
--
--
-- sql file to created the indexes required for the upgrade.
-- These indexes are in addition to the standard Infranet indexes.


SET serverout on size 1000000

DECLARE
v_ddl_stmt VARCHAR2(4000);

v_errmsg VARCHAR2(200);

BEGIN

        IF NOT pin_upg_common.index_exists('i_bill_ndx', 'bill_t', 'created_t, poid_id0', 'yes', v_errmsg) THEN
                v_ddl_stmt := 'CREATE unique index i_bill_ndx ON bill_t (created_t, poid_id0) 
				$UPG_TEMPINDX_TABLESPACE $PIN_CONF_STORAGE_LARGE';
                EXECUTE IMMEDIATE v_ddl_stmt;
        END IF;

        IF NOT pin_upg_common.index_exists('i_event_ndx', 'event_t', 'created_t, poid_id0', 'yes', v_errmsg) THEN
                v_ddl_stmt := 'CREATE unique index i_event_ndx ON event_t (created_t, poid_id0) 
				$UPG_TEMPINDX_TABLESPACE $PIN_CONF_STORAGE_LARGE';
                EXECUTE IMMEDIATE v_ddl_stmt;
        END IF;

        IF NOT pin_upg_common.index_exists('i_item_ndx', 'item_t', 'created_t, poid_id0', 'yes', v_errmsg) THEN
                v_ddl_stmt := 'CREATE unique index i_item_ndx ON item_t (created_t, poid_id0) 
				$UPG_TEMPINDX_TABLESPACE $PIN_CONF_STORAGE_LARGE';
                EXECUTE IMMEDIATE v_ddl_stmt;
        END IF;

EXCEPTION
        WHEN OTHERS THEN
                dbms_output.put_line (sqlerrm);
                dbms_output.put_line (v_ddl_stmt);
END;
/

