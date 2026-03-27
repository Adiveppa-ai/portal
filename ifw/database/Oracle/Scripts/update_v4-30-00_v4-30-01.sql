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
--   Update script from DB version v4-30-00 to v4-30-01.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-00_v4-30-01.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/07/06 07:43:43 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-00_v4-30-01.sql,v $
-- Revision 1.1  2001/07/06 07:43:43  pengelbr
-- PETS #36686 Create a database migration script from v4-10-04 to v4-30-00
--
--------------------------------------------------------------------------------

spool update_v4-30-00_v4-30-01.log

--
-- General
--
alter table ifw_alias_map modify ( field_id not null );

--
-- AggreGate
--
alter table ifw_scenario modify ( name varchar2(255) );

alter table ifw_classitem modify ( name varchar2(255) );

alter table ifw_class modify ( name varchar2(255) );

--
-- Interconnect
--
comment on column IFW_ICPRODUCT_RATE.NETWORKMODEL is 'references the related network model this configuration entry is valid to';

comment on column IFW_ICPRODUCT_RATE.FIXCOST is 'Defines a fixed cost value that should be added to the calculated rate of this service invocation.';

--
-- INT_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-01', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
