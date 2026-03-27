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
--   Update script from DB version v6.7.2 to v6.7.3.
--------------------------------------------------------------------------------
-- Log:
-- PRSF00102674 Fix Incorrect SQL statement in alter IFW_DISCOUNTSTEP and 
                copy DISCOUNTSTEP value to CODE. (05/04/2004) 
--
-- PRSF00096150 A Code field needs to be added in the IFW_Discountstep.
                (03/03/2004)
--
--------------------------------------------------------------------------------

spool update_v6.7.2_v6.7.3.log

--
-- IFW_DISCOUNTSTEP
--
alter table IFW_DISCOUNTSTEP add CODE VARCHAR2(10) DEFAULT 'code' not null;
update IFW_DISCOUNTSTEP set CODE = DISCOUNTSTEP;
--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.7.3', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
