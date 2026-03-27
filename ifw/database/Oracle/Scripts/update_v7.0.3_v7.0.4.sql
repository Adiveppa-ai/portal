//==============================================================================
//
//      Copyright (c) 1998 - 2006 Oracle. All rights reserved.
//
//      This material is the confidential property of Oracle Corporation
//      or its licensors and may be used, reproduced, stored or transmitted
//      only in accordance with a valid Oracle license or sublicense agreement.
//
//------------------------------------------------------------------------------
-- Block: Database
--------------------------------------------------------------------------------
-- Module Description:
--   Update script from DB version v7.0.3 to v7.0.4
--------------------------------------------------------------------------------
-- Responsible: Archan Misra 
--------------------------------------------------------------------------------
-- Log:
-- 2006/02/13 amisra 
-- PRSF00192762 IFW_NETWORKOPER table related changes
--
--------------------------------------------------------------------------------

spool update_v7.0.3_v7.0.4.log

--------------------------------------------------------------------------------
--changes related to table ifw_networkoper table  for roaming functionality
---please ensure PLMN_ID column contains unique value before running this
--------------------------------------------------------------------------------
ALTER TABLE IFW_NETWORKOPER ADD (TAXFLAG CHAR(1) DEFAULT 'N' NOT NULL)
/
COMMENT ON COLUMN IFW_NETWORKOPER.TAXFLAG IS 'This flag indicates whether incoming tax packets of the TAP records will be passed to the subscriber or not'
/
set serverout on
/
declare

prim_cnt integer;
temp_cnt integer;
sql_stmt varchar(1000);

begin

execute immediate 'ALTER TABLE IFW_CIBER_OCC DROP CONSTRAINT FK_IFW_OCC_NO'; 
execute immediate 'ALTER TABLE IFW_ICPRODUCT_RATE DROP CONSTRAINT FK_IFW_IPR_NOP'; 
execute immediate 'ALTER TABLE IFW_NETWORKMODEL DROP CONSTRAINT FK_IFW_NWM_NOP';
execute immediate 'ALTER TABLE IFW_NO_BILLRUN DROP CONSTRAINT FK_IFW_NBR_NOP'; 
execute immediate 'ALTER TABLE IFW_NOPRODUCT DROP CONSTRAINT FK_IFW_NPR_NOP'; 
execute immediate 'ALTER TABLE IFW_SWITCH DROP CONSTRAINT FK_IFW_SWI_NOP';
execute immediate 'ALTER TABLE IFW_TRUNK DROP CONSTRAINT FK_IFW_TRK_CNO'; 
execute immediate 'ALTER TABLE IFW_TRUNK_CNF DROP CONSTRAINT FK_IFW_TRC_NOP';

execute immediate 'CREATE TABLE IFW_NETWORKOPER_TEMP AS SELECT * FROM IFW_NETWORKOPER';

begin

select count(*) into prim_cnt from IFW_NETWORKOPER;
execute immediate 'select count(*) from IFW_NETWORKOPER_TEMP' into temp_cnt;
execute immediate 'truncate table ifw_networkoper';

if prim_cnt = temp_cnt then
execute immediate 'truncate table ifw_networkoper';
else 
dbms_output.put_line('Data is not properly backed up');
return;
end if;

end;

execute immediate 'ALTER TABLE IFW_NETWORKOPER MODIFY ( PLMN_ID VARCHAR2(5) NOT NULL)';
execute immediate 'CREATE UNIQUE INDEX AK_IFW_NOP_PLMN ON IFW_NETWORKOPER(PLMN_ID) PCTFREE 5 INITRANS 2 TABLESPACE INTEGRATE_TS_2_IDX STORAGE(INITIAL 32K NEXT 32K MINEXTENTS 1 MAXEXTENTS UNLIMITED PCTINCREASE 0)';
        

execute immediate 'INSERT INTO IFW_NETWORKOPER SELECT * FROM IFW_NETWORKOPER_TEMP WHERE PLMN_ID IS NOT NULL';

if (sql%rowcount = prim_cnt) then
execute immediate 'DROP TABLE IFW_NETWORKOPER_TEMP';
commit;
else dbms_output.put_line('Original Data on PLMN_ID is wrong,please check the temp table IFW_NETWORKOPER_TEMP');
ROLLBACK;
return;
end if;

execute immediate 'ALTER TABLE IFW_CIBER_OCC ADD CONSTRAINT FK_IFW_OCC_NO FOREIGN KEY (NO) REFERENCES IFW_NETWORKOPER(NO)';
execute immediate 'ALTER TABLE IFW_ICPRODUCT_RATE ADD CONSTRAINT FK_IFW_IPR_NOP FOREIGN KEY (NO) REFERENCES IFW_NETWORKOPER(NO)';
execute immediate 'ALTER TABLE IFW_NETWORKMODEL ADD CONSTRAINT FK_IFW_NWM_NOP FOREIGN KEY (NO) REFERENCES IFW_NETWORKOPER(NO)';
execute immediate 'ALTER TABLE IFW_NO_BILLRUN ADD CONSTRAINT FK_IFW_NBR_NOP FOREIGN KEY (NO) REFERENCES IFW_NETWORKOPER(NO)';
execute immediate 'ALTER TABLE IFW_NOPRODUCT ADD CONSTRAINT FK_IFW_NPR_NOP FOREIGN KEY (NO) REFERENCES IFW_NETWORKOPER(NO)';
execute immediate 'ALTER TABLE IFW_SWITCH ADD CONSTRAINT FK_IFW_SWI_NOP FOREIGN KEY (NO) REFERENCES IFW_NETWORKOPER(NO)';
execute immediate 'ALTER TABLE IFW_TRUNK ADD CONSTRAINT FK_IFW_TRK_CNO FOREIGN KEY (CONNECTED_NO) REFERENCES IFW_NETWORKOPER(NO)';
execute immediate 'ALTER TABLE IFW_TRUNK_CNF ADD CONSTRAINT FK_IFW_TRC_NOP FOREIGN KEY (NO) REFERENCES IFW_NETWORKOPER(NO)';
end;
/

--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'P7.0.4', 'Portal Pipeline', user, sysdate )
/

commit;

spool off;
