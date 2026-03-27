--------------------------------------------------------------------------------
--
-- Copyright (c) 1998, 2009, Oracle and/or its affiliates. 
-- All rights reserved. 
--
--      This material is the confidential property of Oracle Corporation
--      or its licensors and may be used, reproduced, stored or transmitted
--      only in accordance with a valid Oracle license or sublicense agreement.
--
--------------------------------------------------------------------------------
-- Block: Database
--------------------------------------------------------------------------------
-- Module Description:
--   Create all neccessary tablespaces for Pipeline and supporting products.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: ifw_Roles.sql $
-- $Revision: /cgbubrm_7.3.2.pipeline/1 $
-- $Author: smalviya $
-- $Date: 2009/03/27 07:50:18 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: ifw_Roles.sql,v $
-- Revision 1.1  2001/07/17 15:04:41  pengelbr
-- PETS #36857 naming of ifw db-scripts still integRate.
--             All database related files starting with integRate renamed to ifw.
-- PETS #37073 create user 'integrate' fails because SOL tablespaces are referenced.
--             Removed quota for SOL tablespaces.
-- PETS #37113 passthrough in rateplan configuration just allowes 1 or 0
--             Updated check constraint.
--
-- Revision 1.2  2001/02/08 13:36:39  pengelbr
-- #2980# Do not add quotas on FOCUST and RESULT tablespaces.
--
-- Revision 1.1  2000/10/05 07:12:51  pengelbr
-- Split integRate_Prepare.sql into integRate_Tablespaces.sql 
-- and integRate_Roles.sql and remove it.
--
-- Revision 1.4  2000/09/27 07:58:51  pengelbr
-- Fix PR2552. User INTEGRATE will now have right to drop public synonyms.
--
-- Revision 1.3  2000/08/24 14:43:03  pengelbr
-- Fix errors.
--
-- Revision 1.2  2000/07/27 13:48:15  pengelbr
-- Update create user and drop some tablespaces because the products have their own create scripts.
--
-- Revision 1.1  2000/07/20 14:01:06  pengelbr
-- Added prepare script. Modified responsible for update scripts.
--
--------------------------------------------------------------------------------

-- ============================================================
--   Role: INTEGRATE_ROLE_SEL
-- ============================================================

create role INTEGRATE_ROLE_SEL;

grant create session to INTEGRATE_ROLE_SEL;

grant ROLE_JSA_SEL to INTEGRATE_ROLE_SEL;

grant ROLE_JSA_ALL to INTEGRATE_ROLE_SEL;

-- ============================================================
--   Role: INTEGRATE_ROLE_ALL
-- ============================================================

create role INTEGRATE_ROLE_ALL;

grant connect to INTEGRATE_ROLE_ALL;

grant INTEGRATE_ROLE_SEL to INTEGRATE_ROLE_ALL;

-- ============================================================
--   User: INTEGRATE
-- ============================================================

create user
        INTEGRATE identified by INTEGRATE
        default tablespace INTEGRATE_TS_1_DAT
        temporary tablespace TEMP
        quota unlimited on INTEGRATE_TS_1_DAT
        quota unlimited on INTEGRATE_TS_1_IDX
        quota unlimited on INTEGRATE_TS_2_DAT
        quota unlimited on INTEGRATE_TS_2_IDX
        quota unlimited on INTEGRATE_TS_3_DAT
        quota unlimited on INTEGRATE_TS_3_IDX
        quota unlimited on INTEGRATE_TS_4_DAT
        quota unlimited on INTEGRATE_TS_4_IDX
        quota unlimited on AGGREGATE_TS_1_DAT
        quota unlimited on AGGREGATE_TS_1_IDX;

grant INTEGRATE_ROLE_ALL to INTEGRATE with admin option;

grant create public synonym to INTEGRATE;
grant drop public synonym   to INTEGRATE;
grant create view           to INTEGRATE;
grant create sequence       to INTEGRATE;
grant create table          to INTEGRATE;
grant create any index      to INTEGRATE;
grant create procedure      to INTEGRATE;

