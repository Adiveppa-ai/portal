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
--   Update script from DB version v4-05-01 to v4-10-01.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-05-01_v4-10-01.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2000/11/30 07:34:57 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-05-01_v4-10-01.sql,v $
-- Revision 1.2  2000/11/30 07:34:57  pengelbr
-- Updated due to renaming.
--
-- Revision 1.1  2000/10/20 07:40:37  pengelbr
-- Modified/Added for v4-10-01 by PE.
--
--------------------------------------------------------------------------------

spool update_v4-05-01_v4-10-01_Prepare.log;

@update_v4-05-01_v4-10-01_Prepare.sql;

spool out;

spool update_v4-05-01_v4-10-01_Create.log

@update_v4-05-01_v4-10-01_Create.sql;

spool out;

spool update_v4-05-01_v4-10-01_Copy.log;

@update_v4-05-01_v4-10-01_Copy.sql;

spool out;

spool update_v4-05-01_v4-10-01_Drop_tmp.log;

@update_v4-05-01_v4-10-01_Drop_tmp.sql;

spool out;

spool update_v4-05-01_v4-10-01_Constraints.log;

@update_v4-05-01_v4-10-01_Constraints.sql;

spool out;

spool update_v4-05-01_v4-10-01_Synonyms.log;

@update_v4-05-01_v4-10-01_Synonyms.sql;

spool out;
