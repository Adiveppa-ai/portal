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
--   Update script from DB version v4-04-01 to v4-04-02.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-04-01_v4-04-02.sql,v $
-- $Revision: 1.3 $
-- $Author: pengelbr $
-- $Date: 2000/07/28 12:25:18 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-04-01_v4-04-02.sql,v $
-- Revision 1.3  2000/07/28 12:25:18  pengelbr
-- Add ';' to each command if missing (PR 2263).
--
-- Revision 1.2  2000/07/27 13:56:06  pengelbr
-- Add tablename to drop column command.
--
-- Revision 1.1  2000/07/20 14:58:48  pengelbr
-- Moved column BILLCYCLE from INT_SUBS_CONTRACT to INT_SUBS_CONTRACT_HIST.
--
--------------------------------------------------------------------------------

alter table INT_SUBS_CONTRACT_HIST
  add BILLCYCLE VARCHAR2(2) default '01' not null;

comment on column INT_SUBS_CONTRACT_HIST.BILLCYCLE is 'determines the bill cycle for this customer (e.g. 01-28)';

alter table INT_SUBS_CONTRACT_HIST
    add constraint FK_INT_SCH_SBC foreign key  (BILLCYCLE)
       references INT_SUBS_BILLCYCLE (BILLCYCLE);

update int_subs_contract_hist sch
  set billcycle = ( 
    select billcycle 
    from int_subs_contract sub
    where sch.contract = sub.contract );

alter table int_subs_contract drop constraint FK_INT_SUB_SBC;

alter table INT_SUBS_CONTRACT drop column BILLCYCLE;

insert into int_dbversion
( dbversion, description, username, install_date )
values
( 'v4-04-02', 'integRate/tariffIC', user, sysdate );

commit;

