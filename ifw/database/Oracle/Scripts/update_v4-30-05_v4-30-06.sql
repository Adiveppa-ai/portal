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
--   Update script from DB version v4-30-05 to v4-30-06.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-05_v4-30-06.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2001/09/21 09:41:31 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-05_v4-30-06.sql,v $
-- Revision 1.2  2001/09/21 09:41:31  pengelbr
-- IC_DAILY/-_ALTERNATE rename column RESSOURCE to RESOURCE_NAME.
--
-- Revision 1.1  2001/09/21 08:54:22  pengelbr
-- Commit for INT_DB v4-30-06
--
--------------------------------------------------------------------------------

spool update_v4-30-05_v4-30-06.log

--
-- IFW_USAGETYPE_MAP
--
drop table ifw_usagetype_map cascade constraints;

--
-- IFW_DICTIONARY
--
alter table ifw_dictionary modify ( modifdate default sysdate );

--
-- IFW_QUEUE
--
alter table ifw_queue modify ( modifdate default sysdate );

--
-- IC_DAILY
--
alter table ic_daily drop primary key;

alter table ic_daily add ( resource_name varchar2(10) );

comment on column IC_DAILY.RESOURCE_NAME is 'ressource on which the ic-bill should be aggregated';

update ic_daily set resource_name = ressource;

alter table ic_daily modify ( resource_name not null );

alter table ic_daily drop column ressource;

alter table ic_daily add constraint PK_ICD primary key (NETWORKMODEL, NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN, SWITCH, POI, TRUNK, ICPRODUCT, BILL_DIRECTION, RATEPLAN, SERVICECODE, SERVICECLASS, IMPACT_CATEGORY, TIMEMODEL, TIMEZONE, RESOURCE_NAME, RUM);

--
-- IC_DAILY_ALTERNATE
--
alter table ic_daily_alternate drop primary key;

alter table ic_daily_alternate add ( resource_name varchar2(10) );

comment on column IC_DAILY_ALTERNATE.RESOURCE_NAME is 'ressource on which the ic-bill should be aggregated';

update ic_daily_alternate set resource_name = ressource;

alter table ic_daily_alternate modify ( resource_name not null );

alter table ic_daily_alternate drop column ressource;

alter table ic_daily_alternate add constraint PK_ICA primary key (NETWORKMODEL, NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN, SWITCH, POI, TRUNK, ICPRODUCT, BILL_DIRECTION, RATEPLAN, SERVICECODE, SERVICECLASS, IMPACT_CATEGORY, TIMEMODEL, TIMEZONE, RESOURCE_NAME, RUM);

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-06', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
