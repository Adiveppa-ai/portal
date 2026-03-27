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
--   Update script from DB version v7.0.1 to v7.0.2.
--------------------------------------------------------------------------------
-- Responsible:Archan Misra 
--------------------------------------------------------------------------------
-- Log:
-- 2004/15/10 nchodnek 
-- PRSF00171802:Discount Balance Impact:impact_category,glid,taxcode columns of ifw_dscbalimpact table needs to be changed to varchar from number. 
--
--------------------------------------------------------------------------------

spool update_v7.0.1_v7.0.2.log

alter table ifw_dscbalimpact
modify (tax_code varchar2(5));


alter table ifw_dscbalimpact
modify (glid varchar2(10));

alter table ifw_dscbalimpact
modify (impact_category varchar2(10));

--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v7.0.2', 'Portal Pipeline', user, sysdate );

spool off;

