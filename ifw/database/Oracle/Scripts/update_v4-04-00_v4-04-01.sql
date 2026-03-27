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
--   Update script from DB version v4-04-00 to v4-04-01.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-04-00_v4-04-01.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2000/07/28 12:25:18 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-04-00_v4-04-01.sql,v $
-- Revision 1.2  2000/07/28 12:25:18  pengelbr
-- Add ';' to each command if missing (PR 2263).
--
-- Revision 1.1  2000/07/12 13:47:31  pengelbr
-- Apply changes for v4-04-01.
--
--------------------------------------------------------------------------------

alter table INT_SUBSTARIFF_MAP
    modify SUBS_TARIFFMODEL VARCHAR2(30);

alter table INT_SUBS_CONTRACT_HIST
    modify TARIFFMODEL VARCHAR2(30);

create index FK_INT_SCH on INT_SUBS_CONTRACT_HIST (TARIFFMODEL asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_4_IDX
storage
(
initial 32K
next 32K
minextents 1
maxextents unlimited
pctincrease 0
);

insert into int_dbversion
( dbversion, description, username, install_date )
values
( 'v4-04-01', 'integRate/tariffIC', user, sysdate );
 
commit;
