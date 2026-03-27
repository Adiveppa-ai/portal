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
--   Update script from DB version v6.5.2 to v6.5.3.
--------------------------------------------------------------------------------
-- Responsible: Mark Murthy
--------------------------------------------------------------------------------
-- Log:
-- 2003/02/12 mmurthy
-- PRSF00031659 deliver IntegRate6.5EBFInt on 02/12/03 11:31:54.
--    This merges changes from PRSF00030484 and PRSF00028509.
--
--------------------------------------------------------------------------------

spool update_v6.5.2_v6.5.3.log

--
-- IFW_DISCOUNTSTEP
--
alter table IFW_DISCOUNTSTEP modify ROLLOVER_PERIOD NUMBER(1) default 0;

alter table IFW_DISCOUNTSTEP add RECURRING NUMBER(1) default 1 not null;

comment on column IFW_DISCOUNTSTEP.RECURRING is 'flag to indicate if it is one time or recurring';

-- 
--   Old synonyms                                 
-- 
drop public synonym IFW_DESTINATIONDESC;
drop public synonym IFW_DISCOUNTCONDITION;
drop public synonym IFW_DISCOUNTMDL_CNF;
drop public synonym IFW_DISCOUNTMDL_VER;
drop public synonym IFW_DISCOUNTTRIGGER;
drop public synonym IFW_EDRSEQLOG;
drop public synonym IFW_GEOAREACODE_LNK;
drop public synonym IFW_GEOGRAPHICALMODEL;
drop public synonym IFW_GEOGRAPHICAL_ZONE;
drop public synonym IFW_ICPRODUCT_GROUP;
drop public synonym IFW_IMPACT_CATEGORY;
drop public synonym IFW_NETWORKOPERATOR;
drop public synonym IFW_PRICEMODEL_STEP;
drop public synonym IFW_RATESERVICE_MAP;
drop public synonym IFW_RESSOURCE;
drop public synonym IFW_SEMAPHORE;
drop public synonym IFW_SERVICECODE_MAP;
drop public synonym IFW_SUBS_ACCOUNT;
drop public synonym IFW_USAGESCENARIO_MAP;
drop public synonym IFW_USAGETYPE_MAP;

-- 
--   New synonyms                                 
-- 
create public synonym IFW_DBVERSION for IFW_DBVERSION;
create public synonym IFW_DESTINDESC for IFW_DESTINDESC;
create public synonym IFW_DSCCONDITION for IFW_DSCCONDITION;
create public synonym IFW_DSCMDL_CNF for IFW_DSCMDL_CNF;
create public synonym IFW_DSCMDL_VER for IFW_DSCMDL_VER;
create public synonym IFW_DSCTRIGGER for IFW_DSCTRIGGER;
create public synonym IFW_DUPLICATECHECK for IFW_DUPLICATECHECK;
create public synonym IFW_GEOAREA_LNK for IFW_GEOAREA_LNK;
create public synonym IFW_GEO_MODEL for IFW_GEO_MODEL;
create public synonym IFW_GEO_ZONE for IFW_GEO_ZONE;
create public synonym IFW_ICPRODUCT_GRP for IFW_ICPRODUCT_GRP;
create public synonym IFW_IMPACT_CAT for IFW_IMPACT_CAT;
create public synonym IFW_LERG_DATA for IFW_LERG_DATA;
create public synonym IFW_NETWORKOPER for IFW_NETWORKOPER;
create public synonym IFW_PRICEMDL_STEP for IFW_PRICEMDL_STEP;
create public synonym IFW_RESOURCE for IFW_RESOURCE;
create public synonym IFW_RSC_MAP for IFW_RSC_MAP;
create public synonym IFW_SEQCHECK for IFW_SEQCHECK;
create public synonym IFW_SEQLOG_IN for IFW_SEQLOG_IN;
create public synonym IFW_SEQLOG_OUT for IFW_SEQLOG_OUT;
create public synonym IFW_SERVICE_MAP for IFW_SERVICE_MAP;
create public synonym IFW_USC_MAP for IFW_USC_MAP;


--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.5.3', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
