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
--   Update script from DB version v4-04-02 to v4-05-00.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-04-02_v4-05-00.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2000/08/24 14:43:03 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-04-02_v4-05-00.sql,v $
-- Revision 1.2  2000/08/24 14:43:03  pengelbr
-- Fix errors.
--
-- Revision 1.1  2000/07/31 11:46:08  pengelbr
-- New/updated scripts for merged database model v4-05-00.
--
--------------------------------------------------------------------------------

insert into int_dbversion
( dbversion, description, username, install_date )
values
( 'v4-05-00', 'integRate/tariffIC + aggreGate', user, sysdate );

commit;

