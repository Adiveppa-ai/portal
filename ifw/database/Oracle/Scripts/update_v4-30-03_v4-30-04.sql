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
--   Update script from DB version v4-30-03 to v4-30-04.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-03_v4-30-04.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/07/26 09:51:51 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-03_v4-30-04.sql,v $
-- Revision 1.1  2001/07/26 09:51:51  pengelbr
-- PETS #37420 ifw with carriericrating cored while processing a cdr file.
--   - IFW_NETWORKMODEL.NO has to be mandatory.
-- PETS #37527 Small database corrections/enhancements
--   - IFW_EDRC_FIELD: add check constraint to allow only distinct values
--     (Block, Date, Decimal, Integer, String) for TYPE.
--   - NAME columns, check if all are VARCHAR2(255)!
--     Modified IFW_RATEADJUST, IFW_UOM, IFW_DISCOUNTTRIGGER, IFW_RATESERVICE_MAP, IFW_RATEPLAN
--   - IFW_TIMEINTERVAL
--     TimeFrom/To need to be mandatory.
--
--------------------------------------------------------------------------------

spool update_v4-30-03_v4-30-04.log

--
-- IFW_EDRC_FIELD
--
update ifw_edrc_field
set type = 'Block'
where upper(type) = 'BLOCK';
 
update ifw_edrc_field
set type = 'Date'
where upper(type) = 'DATE';
 
update ifw_edrc_field
set type = 'Decimal'
where upper(type) = 'DECIMAL';
 
update ifw_edrc_field
set type = 'Integer'
where upper(type) = 'INTEGER';
 
update ifw_edrc_field
set type = 'String'
where upper(type) = 'STRING';
 
alter table ifw_edrc_field add constraint CKC_TYPE_IFW_EDRC_FIELD check (TYPE is null or (TYPE in ('Block','Date','Decimal','Integer','String')));

--
-- IFW_RATEADJUST
--
alter table ifw_rateadjust modify (name varchar2(255));

--
-- IFW_UOM
--
alter table ifw_uom modify (name varchar2(255));

--
-- IFW_DISCOUNTTRIGGER
--
alter table ifw_discounttrigger modify (name varchar2(255));

--
-- IFW_RATESERVICE_MAP
--
alter table ifw_rateservice_map modify (name varchar2(255));

--
-- IFW_RATEPLAN
--
alter table ifw_rateplan modify (name varchar2(255));

--
-- IFW_TIMEINTERVAL
--
alter table ifw_timeinterval modify (time_from not null);

alter table ifw_timeinterval modify (time_to not null);

--
-- IFW_NETWORKMODEL
--
alter table ifw_networkmodel modify (no not null);

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-04', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;

