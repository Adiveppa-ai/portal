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
--   Update script from DB version v4-30-04 to v4-30-05.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-04_v4-30-05.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/08/30 14:35:03 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-04_v4-30-05.sql,v $
-- Revision 1.1  2001/08/30 14:35:03  pengelbr
-- - PETS #38201 Name for CURRENCY 'ISK' contains special char!
--   Causes trouble in Smacc.
-- - Updates on some comment fields.
-- - Added check constraints for:
--   . IFW_ICPRODUCT_RATE ZONE_DIRECTION, ZONE_TYPE and BILL_DIRECTION and
--   . IC_DAILY/_ALTERNATE BILL_DIRECTION.
--
--------------------------------------------------------------------------------

spool update_v4-30-04_v4-30-05.log

--
-- IFW_ICPRODUCT_RATE
--
alter table ifw_icproduct_rate
add constraint CKC_ZONE_DIR_IFW_ICR check (ZONE_DIRECTION in ('I','O','T','N','S','1','2','3','4','5','6'));

alter table ifw_icproduct_rate
add constraint CKC_ZONE_TYP_IFW_ICR check (ZONE_TYPE in ('N','R'));

alter table ifw_icproduct_rate
add constraint CKC_BILL_DIR_IFW_ICR check (BILL_DIRECTION in ('I','O'));

--
-- IC_DAILY
--
alter table ic_daily
add constraint CKC_BILL_DIR_ICD check (BILL_DIRECTION in ('I','O'));

alter table ic_daily_alternate
add constraint CKC_BILL_DIR_ICA check (BILL_DIRECTION in ('I','O'));

--
-- IFW_CURRENCY
--
update ifw_currency
set name = 'Iceland Krona' where currency = 'ISK';

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-05', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
