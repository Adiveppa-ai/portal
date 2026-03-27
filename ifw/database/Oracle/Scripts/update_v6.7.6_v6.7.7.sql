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
--   Update script from DB version v6.7.6 to v6.7.7.
--------------------------------------------------------------------------------
-- Responsible: Philip Thomas
--------------------------------------------------------------------------------
-- Log:
-- 2004/1/10 pthomas
-- PRSF00047463 no unique contraint checking for Discount Trigger
--
--------------------------------------------------------------------------------

spool update_v6.7.6_v6.7.7.log

-- ============================================================
--   Index: AK_IFW_DTR
-- ============================================================
create unique index AK_IFW_DTR on IFW_DSCTRIGGER (CODE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_2_IDX
storage
(
initial 32K
next 32K
minextents 1
maxextents unlimited
pctincrease 0
)
/
--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.7.7', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

