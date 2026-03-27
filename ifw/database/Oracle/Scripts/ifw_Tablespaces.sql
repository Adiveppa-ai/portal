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
--   Create all neccessary tablespaces for integRate and supporting products.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: ifw_Tablespaces.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/07/17 15:05:26 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: ifw_Tablespaces.sql,v $
-- Revision 1.1  2001/07/17 15:05:26  pengelbr
-- PETS #36857 naming of ifw db-scripts still integRate.
--             All database related files starting with integRate renamed to ifw.
-- PETS #37113 passthrough in rateplan configuration just allowes 1 or 0
--             Updated check constraint.
--
-- Revision 1.3  2001/07/10 13:55:28  pengelbr
-- PETS #36809 Add new column REF_PARAM to IFW_REF_MAP.
--
-- Revision 1.2  2000/10/20 07:40:37  pengelbr
-- Modified/Added for v4-10-01 by PE.
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
--   Tablespaces: aggreGate
-- ============================================================

CREATE TABLESPACE AGGREGATE_TS_1_DAT   DATAFILE 'ORA_DAT_PATH/ORA_SID/aggregate_ts_1_dat_01.dbf'   SIZE   5M AUTOEXTEND ON MAXSIZE UNLIMITED;
CREATE TABLESPACE AGGREGATE_TS_1_IDX   DATAFILE 'ORA_IDX_PATH/ORA_SID/aggregate_ts_1_idx_01.dbf'   SIZE  10M AUTOEXTEND ON MAXSIZE UNLIMITED;


-- ============================================================
--   Tablespaces: integRate
-- ============================================================

CREATE TABLESPACE INTEGRATE_TS_1_DAT   DATAFILE 'ORA_DAT_PATH/ORA_SID/integrate_ts_1_dat_01.dbf'   SIZE  25M AUTOEXTEND ON MAXSIZE UNLIMITED;
CREATE TABLESPACE INTEGRATE_TS_1_IDX   DATAFILE 'ORA_IDX_PATH/ORA_SID/integrate_ts_1_idx_01.dbf'   SIZE  15M AUTOEXTEND ON MAXSIZE UNLIMITED;

CREATE TABLESPACE INTEGRATE_TS_2_DAT   DATAFILE 'ORA_DAT_PATH/ORA_SID/integrate_ts_2_dat_01.dbf'   SIZE 200M AUTOEXTEND ON MAXSIZE UNLIMITED;
CREATE TABLESPACE INTEGRATE_TS_2_IDX   DATAFILE 'ORA_IDX_PATH/ORA_SID/integrate_ts_2_idx_01.dbf'   SIZE 200M AUTOEXTEND ON MAXSIZE UNLIMITED;

CREATE TABLESPACE INTEGRATE_TS_3_DAT   DATAFILE 'ORA_DAT_PATH/ORA_SID/integrate_ts_3_dat_01.dbf'   SIZE 200M AUTOEXTEND ON MAXSIZE UNLIMITED;
CREATE TABLESPACE INTEGRATE_TS_3_IDX   DATAFILE 'ORA_IDX_PATH/ORA_SID/integrate_ts_3_idx_01.dbf'   SIZE 200M AUTOEXTEND ON MAXSIZE UNLIMITED;

CREATE TABLESPACE INTEGRATE_TS_4_DAT   DATAFILE 'ORA_DAT_PATH/ORA_SID/integrate_ts_4_dat_01.dbf'   SIZE 200M AUTOEXTEND ON MAXSIZE UNLIMITED;
CREATE TABLESPACE INTEGRATE_TS_4_IDX   DATAFILE 'ORA_IDX_PATH/ORA_SID/integrate_ts_4_idx_01.dbf'   SIZE 200M AUTOEXTEND ON MAXSIZE UNLIMITED;

