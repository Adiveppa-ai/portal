--
--
-- $Header: integrate_mod_vob/pipeline_general/Database/Oracle/Scripts/update_v7.0.8_v7.0.9.sql /cgbubrm_7.3.2.pipeline/1 2009/10/06 05:34:31 smalviya Exp $
--
-- update_PK_constraint.sql
--
-- Copyright (c) 2009, Oracle and/or its affiliates. All rights reserved. 
--
--    NAME
--      update_PK_constraint.sql 
--
--    DESCRIPTION
--      Sql Script to add new columns to the primary key constraint of
--	table IC_DAILY and IC_DAILY_ALTERNATE 
--
--    NOTES
--
--    MODIFIED   (MM/DD/YY)
--    smalviya    08/10/09 - Created
--
set serverout on
spool update_v7.0.8_v7.0.9.log

--------------------------------------------------------------------------------
--changes related to IC_DAILY table
--------------------------------------------------------------------------------
--
-- PRIMARY KEY: PK_ICD
--
alter table IC_DAILY drop constraint PK_ICD drop index;
alter table IC_DAILY add constraint PK_ICD PRIMARY KEY(NETWORKMODEL, NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, SWITCH, POI, TRUNK, ICPRODUCT, RATEPLAN, SERVICECODE, IMPACT_CATEGORY, TIMEMODEL, GLACCOUNT, RESOURCE_NAME, RUM, ENTRY_TYPE, ENTRY_TYPE_SEQ, BILLRUN, BILL_DIRECTION, TIMEZONE, SERVICECLASS) using index;
--------------------------------------------------------------------------------
--changes related to IC_DAILY_ALTERNATE table
--------------------------------------------------------------------------------
--
-- PRIMARY KEY: PK_ICA
--
alter table IC_DAILY_ALTERNATE drop constraint PK_ICA drop index;
alter table IC_DAILY_ALTERNATE add constraint PK_ICA PRIMARY KEY(NETWORKMODEL, NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, SWITCH, POI, TRUNK, ICPRODUCT, RATEPLAN, SERVICECODE, IMPACT_CATEGORY, TIMEMODEL, GLACCOUNT, RESOURCE_NAME, RUM, ENTRY_TYPE, ENTRY_TYPE_SEQ, TIMEZONE, SERVICECLASS, BILL_DIRECTION, BILLRUN) using index;
--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'P7.0.9', 'Pipeline', user, sysdate )
/
commit;
spool off;
