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
--   Update script from DB version v4-30-06 to v4-30-07.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-06_v4-30-07.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/10/31 08:37:49 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-06_v4-30-07.sql,v $
-- Revision 1.1  2001/10/31 08:37:49  pengelbr
-- PETS #40892 valid from in ifw_discountmdl_ver allows NULL, which is a bug
-- PETS #41081 Documentation bug for THRESHOLD columns in IFW_PRICEMODEL_STEP
-- Create all indices in index tablespaces (PK_IFW_SAC: INTEGRATE_TS_2_IDX,
-- PK_IFW_ASM: INTEGRATE_TS_1_IDX)
--
--------------------------------------------------------------------------------

spool update_v4-30-06_v4-30-07.log

--
-- IFW_DISCOUNTMDL_VER
--
update ifw_discountmdl_ver
set valid_from = to_date( '19900101', 'YYYYMMDD' )
where valid_from is null;

alter table ifw_discountmdl_ver modify ( valid_from not null );

--
-- IFW_PRICEMODEL_STEP
--
comment on column IFW_PRICEMODEL_STEP.THRESHOLD_FROM is 'lower boundary in UoM of the related servicecode (compare: >=), negative values allowed';

comment on column IFW_PRICEMODEL_STEP.THRESHOLD_TO is 'upper boundary in UoM of the related servicecode (compare: <)';

--
-- IFW_ALIAS_MAP
--
alter table ifw_alias_map 
  drop primary key;

alter table ifw_alias_map 
  add constraint PK_IFW_ASM primary key (EDRC_DESC, REFERENCE, KEY)
  using index tablespace INTEGRATE_TS_1_IDX
  storage ( initial 32K next 32K minextents 1 maxextents unlimited pctincrease 0 );

--
-- IFW_SUBS_ACCOUNT
--
alter table ifw_subs_account drop primary key;

alter table ifw_subs_account 
  add constraint PK_IFW_SAC primary key (ACCOUNT, RATEPLAN_CODE, PERIOD, DISCOUNTSTEP, DISCOUNTMASTER)
  using index pctfree 5 initrans 2 tablespace INTEGRATE_TS_2_IDX
  storage ( initial 128K next 128K minextents 1 maxextents unlimited pctincrease 0 );

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-07', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
