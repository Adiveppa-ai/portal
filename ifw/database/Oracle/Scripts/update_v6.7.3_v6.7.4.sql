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
--   Update script from DB version v6.7.3 to v6.7.4.
--------------------------------------------------------------------------------
-- Responsible: Gireesh Malaksamudra
--------------------------------------------------------------------------------
-- Log:
-- 2004/03/10 gireesh 
-- PRSF00098150 Changes related to Sequential Discount JP1004
--
--------------------------------------------------------------------------------

spool update_v6.7.3_v6.7.4.log

--
-- IFW_DSCMDL_CNF Drop the old Check Constraint 
-- CKC_DMC_CASCADING (0,1) on DSC_MODE 
--
alter table IFW_DSCMDL_CNF 
drop constraint CKC_DMC_CASCADING;

--
-- IFW_DSCMDL_CNF Add a new Check Constraint CKC_DMC_MODE (0,1,2) on DSC_MODE 
--
  alter table IFW_DSCMDL_CNF add (
  constraint CKC_DMC_MODE CHECK (DSC_MODE in (0,1,2)));

--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.7.4', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

