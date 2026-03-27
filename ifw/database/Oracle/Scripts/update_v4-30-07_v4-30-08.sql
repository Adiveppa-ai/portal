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
--   Update script from DB version v4-30-07 to v4-30-08.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-07_v4-30-08.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/11/09 09:41:57 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-07_v4-30-08.sql,v $
-- Revision 1.1  2001/11/09 09:41:57  pengelbr
-- IFW_REF_MAP.REF_COL needs to be null allowed (not mandatory).
-- PETS #41288 IFW_RULESETLIST.MODIFBY changed from varchar2(2000) to number(9).
--
--------------------------------------------------------------------------------

spool update_v4-30-07_v4-30-08.log

--
-- IFW_REF_MAP
--
alter table ifw_ref_map modify ( ref_col null );

--
-- IFW_RULESETLIST
--
alter table ifw_rulesetlist modify ( modifby number(9) );

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-08', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
