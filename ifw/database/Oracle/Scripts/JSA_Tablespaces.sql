-- ============================================================
--   DBMS name:      ORACLE Version 9 for simuLate             
--   Created on:     17.10.99  09:00                           
-- ============================================================

-- ============================================================
--   VERSION HISTORY
-- ============================================================
/* 
   17.10.99-at: created initial file
		- created tablespace JSA_TS_1_DAT
		- created tablespace JSA_TS_1_IDX 
*/


-- ============================================================
--   Tablespace: JSA_TS_1_DAT 
--   Caution: Replace *** with the true path and name of the datafile
-- ============================================================

create tablespace JSA_TS_1_DAT datafile '***' size 10m;

-- ============================================================
--   Tablespace: JSA_TS_1_IDX 
--   Caution: Replace *** with the true path and name of the datafile
-- ============================================================

create tablespace JSA_TS_1_IDX datafile '***' size 5m;

