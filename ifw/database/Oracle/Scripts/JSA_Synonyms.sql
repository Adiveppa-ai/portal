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
--   Create all public JSA synonyms.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: JSA_Synonyms.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2002/02/04 10:28:19 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: JSA_Synonyms.sql,v $
-- Revision 1.1  2002/02/04 10:28:19  pengelbr
-- Remove public synonyms from create script.
--
--------------------------------------------------------------------------------

-- ============================================================
-- SEQUENCES
-- ============================================================
create public synonym JSA_SEQ_USER_ID for JSA_SEQ_USER_ID;
create public synonym JSA_SEQ_MODULE_ID for JSA_SEQ_MODULE_ID;
create public synonym JSA_SEQ_USERGROUP_ID for JSA_SEQ_USERGROUP_ID;
create public synonym JSA_SEQ_BULLETINBOARD_ID for JSA_SEQ_BULLETINBOARD_ID;

-- ============================================================
-- TABLES
-- ============================================================
create public synonym JSA_BULLETINBOARD for JSA_BULLETINBOARD;
create public synonym JSA_USER for JSA_USER;
create public synonym JSA_USERGROUP for JSA_USERGROUP;
create public synonym JSA_MODULE for JSA_MODULE;
create public synonym JSA_USERRIGHT for JSA_USERRIGHT;
create public synonym JSA_GROUPRIGHT for JSA_GROUPRIGHT;
create public synonym JSA_GROUPUSER for JSA_GROUPUSER;
create public synonym JSA_CONFIG for JSA_CONFIG;
