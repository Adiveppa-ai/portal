--------------------------------------------------------------------------------
--
--      Copyright (c) 1998 - 2006 Oracle. All rights reserved.
--
--      This material is the confidential property of Oracle Corporation
--      or its licensors and may be used, reproduced, stored or transmitted
--      only in accordance with a valid Oracle license or sublicense agreement.
--
--------------------------------------------------------------------------------
-- Block: Database
--------------------------------------------------------------------------------
-- Module Description:
--   Update script from DB version v4-10-01 to v4-10-02.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-10-01_v4-10-02.sql,v $
-- $Revision: 1.5 $
-- $Author: pengelbr $
-- $Date: 2001/02/08 13:35:37 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-10-01_v4-10-02.sql,v $
-- Revision 1.5  2001/02/08 13:35:37  pengelbr
-- #2997# Create log-file for update script.
--
-- Revision 1.4  2000/12/21 14:22:16  pengelbr
-- Updated to NOT modify INT_ISCRIPT and INT_RULE* tables.
-- iScript and iRules columns shall be of LONG type as before (v4-05).
--
-- Revision 1.3  2000/11/29 13:47:11  pengelbr
-- More latest changes for v4-10-02
--
-- Revision 1.2  2000/11/27 09:47:30  pengelbr
-- Latest updates for release v4-10-02.
--
-- Revision 1.1  2000/10/30 13:00:19  pengelbr
-- lastest changes for v4-10 database version
--
--------------------------------------------------------------------------------

spool update_v4-10-01_v4-10-02.log

--
-- INT_UOM
--
update int_uom set modified = NULL;

alter table int_uom modify modified number(1) default 1;

update int_uom set modified = 1;

alter table int_uom modify modified not null;


--
-- INT_SUBS_CLI
--
alter table INT_SUBS_CLI modify CLI varchar2(40);


--
-- Drop Sequence INT_SEQ_ZONE
--
drop sequence INT_SEQ_ZONE;


--
-- New Check Constraint for ChargeBase in INT_PRICEMODEL_STEP
--
alter table INT_PRICEMODEL_STEP add constraint CKC_CHARGE_B_INT_PRICEMODEL_ST check (CHARGE_BASE >= 1);


--
-- Add missing FK constraints
--
alter table INT_ICPRODUCT_GROUP
    add constraint FK_INT_ICG_NWM foreign key  (NETWORKMODEL)
       references INT_NETWORKMODEL (NETWORKMODEL);

alter table INT_ICPRODUCT_CNF
    add constraint FK_INT_IPC_NWM foreign key  (NETWORKMODEL)
       references INT_NETWORKMODEL (NETWORKMODEL);


--
-- modify stream domains
--

-- INT_CALLTYPE_MAP
alter table INT_CALLTYPE_MAP modify COMPAREPATTERN default '.*';


-- INT_DISCARDING
alter table INT_DISCARDING modify RECORDTYPE default '.*';

alter table INT_DISCARDING modify SOURCE_NETWORK default '.*';

alter table INT_DISCARDING modify CALL_COMPLETION default '.*';

alter table INT_DISCARDING modify LONG_DURATION default '.*';

alter table INT_DISCARDING modify CALLCLASS default '.*';

alter table INT_DISCARDING modify SERVICECODE default '.*';

alter table INT_DISCARDING modify SWITCH default '.*';

alter table INT_DISCARDING modify TARIFFCLASS default '.*';

alter table INT_DISCARDING modify TARIFFSUBCLASS default '.*';

alter table INT_DISCARDING modify CONNECTTYPE default '.*';

alter table INT_DISCARDING modify CONNECTSUBTYPE default '.*';

alter table INT_DISCARDING modify B_NUMBER default '.*';


-- INT_SPLITTING_TYPE
alter table INT_SPLITTING_TYPE modify RECORDTYPE default '.*';

alter table INT_SPLITTING_TYPE modify SERVICECODE default '.*';

alter table INT_SPLITTING_TYPE modify CALLCLASS default '.*';

alter table INT_SPLITTING_TYPE modify SOURCE_NETWORK default '.*';

alter table INT_SPLITTING_TYPE modify DESTIN_NETWORK default '.*';

alter table INT_SPLITTING_TYPE modify SWITCH default '.*';

alter table INT_SPLITTING_TYPE modify TRUNK_IN default '.*';

alter table INT_SPLITTING_TYPE modify TRUNK_OUT default '.*';

alter table INT_SPLITTING_TYPE modify ORIGIN_AREACODE default '.*';

alter table INT_SPLITTING_TYPE modify DESTIN_AREACODE default '.*';

alter table INT_SPLITTING_TYPE modify TRANSIT_AREACODE default '.*';


-- INT_ICPRODUCT_CNF
alter table INT_ICPRODUCT_CNF modify SOURCE_NETWORK default '.*';

alter table INT_ICPRODUCT_CNF modify DESTIN_NETWORK default '.*';

alter table INT_ICPRODUCT_CNF modify ORIGIN_AREACODE default '.*';

alter table INT_ICPRODUCT_CNF modify DESTIN_AREACODE default '.*';

alter table INT_ICPRODUCT_CNF modify TRANSIT_AREACODE default '.*';

alter table INT_ICPRODUCT_CNF modify RECORDTYPE default '.*';

alter table INT_ICPRODUCT_CNF modify SERVICECODE default '.*';

alter table INT_ICPRODUCT_CNF modify CALLCLASS default '.*';


-- INT_SERVICECODE_MAP
alter table INT_SERVICECODE_MAP modify EXT_SERVICECODE default '.*';

alter table INT_SERVICECODE_MAP modify CALLCLASS default '.*';

alter table INT_SERVICECODE_MAP modify LOCARIND_VASEVENT default '.*';

alter table INT_SERVICECODE_MAP modify QOS_REQUESTED default '.*';

alter table INT_SERVICECODE_MAP modify QOS_USED default '.*';

alter table INT_SERVICECODE_MAP modify RECORDTYPE default '.*';


-- INT_CALLCLASS_MAP
alter table INT_CALLCLASS_MAP modify EXT_CALLCLASS default '.*';

alter table INT_CALLCLASS_MAP modify CALLTYPE default '.*';

alter table INT_CALLCLASS_MAP modify AOCZONE default '.*';

alter table INT_CALLCLASS_MAP modify TARIFFCLASS default '.*';

alter table INT_CALLCLASS_MAP modify TARIFFSUBCLASS default '.*';

alter table INT_CALLCLASS_MAP modify RECORDTYPE default '.*';

alter table INT_CALLCLASS_MAP modify CONNECTTYPE default '.*';

alter table INT_CALLCLASS_MAP modify CONNECTSUBTYPE varchar2(2000) default '.*';

alter table INT_CALLCLASS_MAP modify APPLICATION default '.*';

alter table INT_CALLCLASS_MAP modify TRANSIT_AREACODE default '.*';


-- INT_CLASSTYPEZONE_MAP
alter table INT_CLASSTYPEZONE_MAP modify CALLCLASS default '.*';

alter table INT_CLASSTYPEZONE_MAP modify CALLTYPE default '.*';

alter table INT_CLASSTYPEZONE_MAP modify SERVICECODE default '.*';

alter table INT_CLASSTYPEZONE_MAP modify SERVICECLASS default '.*';

alter table INT_CLASSTYPEZONE_MAP modify ZONE_WS default '.*';

alter table INT_CLASSTYPEZONE_MAP modify ZONE_RT default '.*';


-- INT_APN_MAP
alter table INT_APN_MAP modify SERVICECODE default '.*';

alter table INT_APN_MAP modify ACCESSPOINTNAME default '.*';

alter table INT_APN_MAP modify ZONE_WS default '.*';

alter table INT_APN_MAP modify ZONE_RT default '.*';


-- INT_TARIFFDISCOUNT_LNK
alter table INT_TARIFFDISCOUNT_LNK modify CALLCLASS default '.*';

alter table INT_TARIFFDISCOUNT_LNK modify CALLTYPE default '.*';

alter table INT_TARIFFDISCOUNT_LNK modify SERVICECODE default '.*';

alter table INT_TARIFFDISCOUNT_LNK modify SERVICECLASS default '.*';

alter table INT_TARIFFDISCOUNT_LNK modify ZONE default '.*';

alter table INT_TARIFFDISCOUNT_LNK modify SOURCE_NETWORK default '.*';

alter table INT_TARIFFDISCOUNT_LNK modify DESTIN_NETWORK default '.*';


-- INT_TARIFFSERVICECLASS
alter table INT_TARIFFSERVICECLASS modify QOS_REQUESTED default '.*';

alter table INT_TARIFFSERVICECLASS modify QOS_USED default '.*';

alter table INT_TARIFFSERVICECLASS modify CALLCLASS default '.*';

alter table INT_TARIFFSERVICECLASS modify CALLTYPE default '.*';

alter table INT_TARIFFSERVICECLASS modify SERVICECODE default '.*';

alter table INT_TARIFFSERVICECLASS modify SERVICECLASS default '.*';

alter table INT_TARIFFSERVICECLASS modify ZONE default '.*';


-- INT_DISCOUNTDETAIL
alter table INT_DISCOUNTDETAIL modify ZONEMODEL default '.*';

alter table INT_DISCOUNTDETAIL modify ZONE default '.*';

alter table INT_DISCOUNTDETAIL modify SERVICECODE default '.*';

alter table INT_DISCOUNTDETAIL modify SERVICECLASS default '.*';

alter table INT_DISCOUNTDETAIL modify TIMEMODEL default '.*';

alter table INT_DISCOUNTDETAIL modify TIMEZONE default '.*';

alter table INT_DISCOUNTDETAIL modify PRICEMODEL default '.*';

alter table INT_DISCOUNTDETAIL modify RECORDTYPE default '.*';


-- INT_CONTENT_MAP
alter table INT_CONTENT_MAP modify DESTIN_AREACODE default '.*';

alter table INT_CONTENT_MAP modify TRANSIT_AREACODE default '.*';

alter table INT_CONTENT_MAP modify CALLCLASS default '.*';

alter table INT_CONTENT_MAP modify SERVICECODE default '.*';

alter table INT_CONTENT_MAP modify VAS_CODE default '.*';

alter table INT_CONTENT_MAP modify APPLICATION default '.*';


-- AGG_CONDITION
alter table AGG_CONDITION modify CONDITION_VALUE default '.*';


-- AGG_CLASSITEM
alter table AGG_CLASSITEM modify CLASSITEM_VALUE default '.*';


--
-- [aggre'gate]
--
alter table AGG_EDRFORMAT_CNF drop primary key;

drop table AGG_EDRFORMAT_CNF;

alter table AGG_EDRFORMAT_SCN drop primary key;

drop table AGG_EDRFORMAT_SCN;

drop index AK_AGG_EDRFORMAT_CODE;

alter table AGG_EDRFORMAT drop primary key;

drop table AGG_EDRFORMAT;

drop index AK_AGG_EDRCFIELD_INTERNAL_ID;

alter table AGG_EDRCFIELD
  drop column EDRC_TYPE;

alter table AGG_EDRCFIELD
  drop column INTERNAL_FIELD_ID;

alter table AGG_SCENARIO
  drop column VALID_FROM;

alter table AGG_SCENARIO
  drop column VALID_TO;
  
drop table SOL_REGISTRY;

drop table SOL_SECTION;


-- ============================================================
--   View: AGG_FORMAT_MAP_COLUMNS                              
-- ============================================================
create or replace view AGG_FORMAT_MAP_COLUMNS as
SELECT 
  SOL_OBJS.OBJ_ID OBJ_ID,
  SOL_OBJS.OWNER OWNER,
  SOL_OBJS.NAME NAME,
  SOL_OBJS.DESCRIPTION DESCRIPTION,
  SOL_OBJS.OBJ_TYPE OBJ_TYPE,
  SOL_OBJS.OBJ_STATUS OBJ_STATUS,
  SOL_COLS.EXPRESSION EXPRESSION,
  SOL_COLS.DATATYPE DATATYPE,
  SOL_COLS.DATALENGTH DATALENGTH,
  SOL_COLS.DATAPRECISION DATAPRECISION,
  SOL_COLS.DATASCALE DATASCALE,
  SOL_COLS.STRINGTYPE STRINGTYPE,
  SOL_COLS.NULLABLE NULLABLE,
  SOL_COLS.DOMAIN DOMAIN,
  SOL_COLS.FORMAT FORMAT,
  SOL_COLS.PIVOTPOSITION PIVOTPOSITION,
  SOL_COLS.ALIGNMENT ALIGNMENT,
  SOL_COLS.RANGEITEM_DOMAIN RANGEITEM_DOMAIN,
  SOL_COLS.VALUEITEM_DOMAIN VALUEITEM_DOMAIN,
  AGG_EDRCFIELD.EDRCFIELD_ID EDRCFIELD_ID,
  AGG_EDRCFIELD.INTERNAL_FIELDNAME INTERNAL_FIELDNAME,
  AGG_EDRCFIELD.RULE_USAGE RULE_USAGE
FROM 
  SOL_OBJS,
  SOL_COLS,
  AGG_EDRCFIELD
WHERE 
  SOL_COLS.OBJ_ID = AGG_EDRCFIELD.COL_OBJ_ID    and
  SOL_OBJS.OBJ_ID = SOL_COLS.OBJ_ID
UNION    
SELECT 
  SOL_OBJS.OBJ_ID OBJ_ID,
  SOL_OBJS.OWNER OWNER,
  SOL_OBJS.NAME NAME,
  SOL_OBJS.DESCRIPTION DESCRIPTION,
  SOL_OBJS.OBJ_TYPE OBJ_TYPE,
  SOL_OBJS.OBJ_STATUS OBJ_STATUS,
  SOL_COLS.EXPRESSION EXPRESSION,
  SOL_COLS.DATATYPE DATATYPE,
  SOL_COLS.DATALENGTH DATALENGTH,
  SOL_COLS.DATAPRECISION DATAPRECISION,
  SOL_COLS.DATASCALE DATASCALE,
  SOL_COLS.STRINGTYPE STRINGTYPE,
  SOL_COLS.NULLABLE NULLABLE,
  SOL_COLS.DOMAIN DOMAIN,
  SOL_COLS.FORMAT FORMAT,
  SOL_COLS.PIVOTPOSITION PIVOTPOSITION,
  SOL_COLS.ALIGNMENT ALIGNMENT,
  SOL_COLS.RANGEITEM_DOMAIN RANGEITEM_DOMAIN,
  SOL_COLS.VALUEITEM_DOMAIN VALUEITEM_DOMAIN,
  AGG_EDRCFIELD.EDRCFIELD_ID EDRCFIELD_ID,
  AGG_EDRCFIELD.INTERNAL_FIELDNAME INTERNAL_FIELDNAME,
  AGG_EDRCFIELD.RULE_USAGE RULE_USAGE
FROM 
  SOL_OBJS,
  SOL_COLS,
  AGG_EDRCFIELD,
  AGG_REFERENCESET_CNF
WHERE 
  SOL_COLS.OBJ_ID = AGG_REFERENCESET_CNF.COL_OBJ_ID    and
  SOL_OBJS.OBJ_ID = SOL_COLS.OBJ_ID    and
  AGG_REFERENCESET_CNF.REFERENCESET_ID = AGG_EDRCFIELD.REFERENCESET_ID;

--
-- INT_DBVERSION
--
insert into int_dbversion
( dbversion, description, username, install_date )
values
( 'v4-10-02', '[integ''rate] and [tariff''ic]', user, sysdate );

spool off;

commit;
