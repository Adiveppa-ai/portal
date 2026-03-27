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
--   Update script from DB version v6.7.7 to v6.7.8.
--------------------------------------------------------------------------------
-- Responsible: Neeta Chodnekar
--------------------------------------------------------------------------------
-- Log:
-- 2004/15/10 nchodnek 
-- PRSF00128698 Discount Balance Impact: EBAL default value should be null
--
--------------------------------------------------------------------------------

spool update_v6.7.7_v6.7.8.log

alter table IFW_DSCBALIMPACT modify ( EVENT_BALANCE_ID null);

--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.7.8', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

