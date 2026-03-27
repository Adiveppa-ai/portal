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
--   Update script from DB version v6.5.3 to v6.5.4.
--------------------------------------------------------------------------------
-- Responsible: Lalita Tadikonda
--------------------------------------------------------------------------------
-- Log:
-- 2003/02/19 lalita 
-- PRSF00030091 Drop index AK_IFW_CLI_CODE from table IFW_CLASSITEM
--
--------------------------------------------------------------------------------

spool update_v6.5.3_v6.5.4.log

--
-- IFW_CLASSITEM
--
drop index AK_IFW_CLI_CODE;


--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.5.4', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
