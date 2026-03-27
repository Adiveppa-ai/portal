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
--   Update script from DB version v4-30-10 to v4-30-11.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-10_v4-30-11.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2002/01/14 09:56:44 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-10_v4-30-11.sql,v $
-- Revision 1.1  2002/01/14 09:56:44  pengelbr
-- PETS #37924 Add IC_DAILY.ENTRY_TYPE to PK. Add 'S' to Check-Constraint for Storno.
-- Add IC_DAILY.ENTRY_TYPE_SEQ as "Identifirer for more than one correction"
--
--------------------------------------------------------------------------------

spool update_v4-30-10_v4-30-11.log

--
-- IC_DAILY
--
alter table ic_daily drop primary key;

alter table ic_daily drop constraint CKC_ENTRY_TY_IC_DAILY;

update ic_daily
set entry_type = 'N'
where entry_type is null;

alter table ic_daily modify entry_type not null;

alter table ic_daily add constraint CKC_ENTRY_TY_IC_DAILY check (ENTRY_TYPE in ('N','R','C','S')); 

alter table ic_daily add ( entry_type_seq number(9) default 0 not null );

alter table ic_daily add constraint PK_ICD primary key (NETWORKMODEL, NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN, SWITCH, POI, TRUNK, ICPRODUCT, BILL_DIRECTION, RATEPLAN, SERVICECODE, SERVICECLASS, IMPACT_CATEGORY, TIMEMODEL, TIMEZONE, RESOURCE_NAME, RUM, ENTRY_TYPE, ENTRY_TYPE_SEQ);

comment on column ic_daily.entry_type is 'Normal Booking: N; Cancellation/Reversal: R; Correction: C; Storno: S';

comment on column ic_daily.entry_type_seq is 'Identifier for more then one correction';

--
-- IC_DAILY_ALTERNATE
--
alter table ic_daily_alternate drop primary key;

alter table ic_daily_alternate drop constraint CKC_ENTRY_TY_IC_DAILY_ALTERNAT;

update ic_daily_alternate
set entry_type = 'N'
where entry_type is null;

alter table ic_daily_alternate modify entry_type not null;

alter table ic_daily_alternate add constraint CKC_ENTRY_TY_IC_DAILY_ALTERNAT check (ENTRY_TYPE in ('N','R','C','S')); 

alter table ic_daily_alternate add ( entry_type_seq number(9) default 0 not null );

alter table ic_daily_alternate add constraint PK_ICA primary key (NETWORKMODEL, NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN, SWITCH, POI, TRUNK, ICPRODUCT, BILL_DIRECTION, RATEPLAN, SERVICECODE, SERVICECLASS, IMPACT_CATEGORY, TIMEMODEL, TIMEZONE, RESOURCE_NAME, RUM, ENTRY_TYPE, ENTRY_TYPE_SEQ);

comment on column ic_daily_alternate.entry_type is 'Normal Booking: N; Cancellation/Reversal: R; Correction: C; Storno: S';

comment on column ic_daily_alternate.entry_type_seq is 'Identifier for more then one correction';

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-11', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
