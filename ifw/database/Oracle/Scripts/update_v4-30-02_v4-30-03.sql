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
--   Update script from DB version v4-30-02 to v4-30-03.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-02_v4-30-03.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/07/17 15:05:27 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-02_v4-30-03.sql,v $
-- Revision 1.1  2001/07/17 15:05:27  pengelbr
-- PETS #36857 naming of ifw db-scripts still integRate.
--             All database related files starting with integRate renamed to ifw.
-- PETS #37113 passthrough in rateplan configuration just allowes 1 or 0
--             Updated check constraint.
--
--------------------------------------------------------------------------------

spool update_v4-30-02_v4-30-03.log

--
-- IFW_RATEPLAN_CNF
--
alter table ifw_rateplan_cnf drop constraint CKC_PASSTHRO_IFW_RATEPLAN_CNF;

alter table ifw_rateplan_cnf add constraint CKC_PASSTHRO_IFW_RATEPLAN_CNF check (PASSTHROUGH in (0,1));

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-03', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
