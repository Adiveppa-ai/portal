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
--   Update script from DB version v4-30-12 to v6.3.2.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--------------------------------------------------------------------------------
-- Log:
-- 2002/07/04 pengelbr
-- PRSF000aaaa1 Add UsageClass/-Type to IFW_DISCOUNTDETAIL
--
--------------------------------------------------------------------------------

spool update_v6.3.2_v6.3.3.log

--
-- IFW_DISCOUNTDETAIL
--
alter table ifw_discountdetail add USAGETYPE VARCHAR2(2000) default '.*' not null;

alter table ifw_discountdetail add USAGECLASS VARCHAR2(2000) default '.*' not null;

comment on column IFW_DISCOUNTDETAIL.USAGETYPE is 'condition: references a usage type (if empty all match), reg. expr. allowed';

comment on column IFW_DISCOUNTDETAIL.USAGECLASS is 'condition: references a usage class (if empty all match), reg. expr. allowed';


--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.3.3', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
