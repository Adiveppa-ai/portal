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
--   Update script from DB version v4-03-02 to v4-03-03.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-03-02_v4-03-03.sql,v $
-- $Revision: 1.3 $
-- $Author: pengelbr $
-- $Date: 2000/07/28 12:25:18 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-03-02_v4-03-03.sql,v $
-- Revision 1.3  2000/07/28 12:25:18  pengelbr
-- Add ';' to each command if missing (PR 2263).
--
-- Revision 1.2  2000/07/20 14:01:06  pengelbr
-- Added prepare script. Modified responsible for update scripts.
--
-- Revision 1.1  2000/06/26 15:24:38  pengelbr
-- Added update database scripts.
--
--------------------------------------------------------------------------------

alter table INT_CLASSTYPEZONE_MAP add AoC_AMOUNT NUMBER null;

comment on column INT_CLASSTYPEZONE_MAP.AoC_AMOUNT is 'optional AoC-Amount-Value (e.g. Wholesale-Charge), the mapping only takes place, if the cdr-value is smaller or equal';

insert into int_dbversion
( dbversion, description, username, install_date )
values
( 'v4-03-03', 'integRate', user, sysdate );
 
commit;
