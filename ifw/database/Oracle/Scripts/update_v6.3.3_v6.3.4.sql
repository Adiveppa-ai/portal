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
--   Update script from DB version v6.3.3 to v6.3.4.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--------------------------------------------------------------------------------
-- Log:
-- 2002/07/17 pengelbr
-- PRSF00014374 Minimum Charge in IFW_PRICEMODEL required
--
--------------------------------------------------------------------------------

spool update_v6.3.3_v6.3.4.log

--
-- IFW_PRICEMODEL_STEP
--
alter table ifw_pricemodel_step add MINIMUM_CHARGE NUMBER;

comment on column IFW_PRICEMODEL_STEP.MINIMUM_CHARGE is 'Define Minimum Charge per Call per Resource.';


--
-- IFW_ALIAS_MAP
--
update ifw_alias_map
set reference = 'Account_CustA'
where reference = 'UniData_CustA';

update ifw_alias_map
set reference = 'Account_CustB'
where reference = 'UniData_CustB';


--
-- IFW_REF_MAP
--
update ifw_ref_map
set id = 'AccountData'
where id = 'CustomerData';


--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.3.4', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
