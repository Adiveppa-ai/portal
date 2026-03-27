--------------------------------------------------------------------------------
-- Copyright (c) 1998 - 2007 Oracle .  All rights reserved.
-- This material is the confidential property of Oracle Corporation
-- or its licensors and may be used, reproduced, stored or transmitted only in
-- accordance with a valid Oracle license or sublicense agreement.
--
--------------------------------------------------------------------------------
-- Block: Database
--------------------------------------------------------------------------------
-- Module Description:
--   Update script from DB version v6.7.4 to v6.7.5.
--------------------------------------------------------------------------------
-- Responsible: Mark Murthy
--------------------------------------------------------------------------------
-- Log:
-- 2004/13/08 knijhawa 
-- PRSF00126156 Need to add constraint change on IFW_AGGREGATION to pipeline upgrade script
-- The constraint has been changed to allow two new values for function field which
-- are M - Minimum and X - Maximum.
--
--------------------------------------------------------------------------------
-- 2004/28/07 mmurthy 
-- PRSF00123035 DuplicateCheck testcase fails because of missing procedure.
-- The procedure is not loaded in the database
--
--------------------------------------------------------------------------------

spool update_v6.7.4_v6.7.5.log

ALTER TABLE IFW_AGGREGATION DROP CONSTRAINT CKC_AGG_FUNCTION;

ALTER TABLE IFW_AGGREGATION ADD (CONSTRAINT CKC_AGG_FUNCTION CHECK (FUNCTION IN ('C', 'S', 'Q', 'M', 'X')));


alter table IFW_DUPLICATECHECK drop constraint PK_IFW_DUPCK;

-- ============================================================
--   Index: BIDX_DUPCHK_DATA                                    
-- ============================================================

create unique index BIDX_DUPCHK_DATA on IFW_DUPLICATECHECK (DATA asc)
parallel 6
pctfree 5
initrans 2
maxtrans 255
tablespace INTEGRATE_TS_1_IDX
storage
(
initial 1M
next 1M
freelists 12
)
nologging
/

-- =============================================================
-- Procedure : PROC_CHECK_IDX_DUPCHK
-- Changes need to be done while TableSuffix registry entry added :
--      The TableSuffix needs to be appended to the Procedure name , Table name as 
--      well as the Index name after an under_score
--      Ex : If TableSuffix = GSM then the 
--           Procedure name will be PROC_CHECK_IDX_DUPCHK_GSM
--           Table name will be IFW_DUPLICATECHECK_GSM and the 
--           Index name will be IDX_DUPCHK_DATA_GSM
-- =============================================================

CREATE OR REPLACE PROCEDURE PROC_CHECK_IDX_DUPCHK (RET_VAL OUT number) AS
BEGIN
DECLARE
  counter NUMBER;
  partitionflag VARCHAR2(3);
  indexname  VARCHAR2(40);
  totalpartitions NUMBER;
BEGIN
        counter := 0;
        totalpartitions := 0;
        RET_VAL := 0;

        SELECT PARTITIONED, index_name INTO partitionflag, indexname
        FROM user_indexes
        WHERE table_name = 'IFW_DUPLICATECHECK' AND index_name = 'BIDX_DUPCHK_DATA';

        IF (partitionflag = 'YES') THEN
                SELECT count(*) INTO counter
                FROM user_ind_partitions
                WHERE index_name = indexname
                AND status ='USABLE';

                SELECT COUNT(*) INTO totalpartitions
                FROM user_ind_partitions
                WHERE index_name = indexname ;

                IF (counter != totalpartitions) THEN
                RET_VAL := -1;
                END IF;
        ELSE
           SELECT count(*) INTO counter
           from user_indexes WHERE table_name = 'IFW_DUPLICATECHECK'
           AND index_name = 'BIDX_DUPCHK_DATA'
           AND STATUS = 'VALID';

                IF (counter != 1) THEN
                RET_VAL := -1;
                END IF;
        END IF;

        EXCEPTION WHEN OTHERS THEN
        RET_VAL := -1;
        END;

DBMS_OUTPUT.PUT_LINE(RET_VAL);
RETURN;
END;
/

-- ============================================================
-- Procedure : PROC_CREATE_IDX_DUPCHK
-- Changes need to be done while TableSuffix registry entry added :
--      The TableSuffix needs to be appended to the Procedure name , Table name as 
--       well as the Index name  after an under_score
--      Ex : If TableSuffix = GSM then the
--           Procedure name will be PROC_CREATE_IDX_DUPCHK_GSM
--           Table name will be IFW_DUPLICATECHECK_GSM and the
--           Index name will be IDX_DUPCHK_DATA_GSM
-- ============================================================

CREATE OR REPLACE PROCEDURE PROC_CREATE_IDX_DUPCHK AS 
BEGIN 
DECLARE 
  counter NUMBER; 
  partitionflag VARCHAR2(3); 
  indexname  VARCHAR2(40); 
BEGIN 
   counter := 0; 
  
   SELECT PARTITIONED INTO partitionflag 
   FROM user_tables
   WHERE table_name = 'IFW_DUPLICATECHECK';
  
 IF (partitionflag = 'YES') THEN 
  begin
      EXECUTE IMMEDIATE ' create unique index BIDX_DUPCHK_DATA on IFW_DUPLICATECHECK (DATA, EDR_DATE) ' ||
         ' LOCAL ' ||
         ' Tablespace AGGREGATE_TS_1_DAT initrans 12 ' ||
         ' storage (initial 1M next 1M freelists 12 ) nologging parallel 6 ';
  end;
   ELSE 
  begin
      EXECUTE IMMEDIATE ' create unique index BIDX_DUPCHK_DATA on IFW_DUPLICATECHECK (DATA) ' ||
         ' Tablespace AGGREGATE_TS_1_DAT initrans 12 ' ||
         ' storage (initial 1M next 1M freelists 12 ) nologging parallel 6 ';
  end;
   
 END IF; 
 
END; 
 
RETURN; 
END; 
/

-- ============================================================
-- Procedure : PROC_DROP_IDX_DUPCHK
--      The TableSuffix needs to be appended to the Procedure name as well as the 
--      Index name
--      after an under_score
--      Ex : If TableSuffix = GSM then the
--           Procedure name will be PROC_DROP_IDX_DUPCHK_GSM
--           Index name will be IDX_DUPCHK_DATA_GSM
-- ============================================================

CREATE OR REPLACE PROCEDURE PROC_DROP_IDX_DUPCHK AS
BEGIN
EXECUTE IMMEDIATE ' drop index BIDX_DUPCHK_DATA ';
END;
/

--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.7.5', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

