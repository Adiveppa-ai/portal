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
--   Update script from DB version v4-05-00 to v4-05-01.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-05-00_v4-05-01.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2000/10/04 14:21:46 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-05-00_v4-05-01.sql,v $
-- Revision 1.1  2000/10/04 14:21:46  pengelbr
-- v4-05-01 / pe
-- - Removed obsolete tables and columns in AGG.
--
--------------------------------------------------------------------------------

drop index PK_AGG_EDRFORMAT_CNF;

drop table agg_edrformat_cnf;

drop index PK_AGG_EDRFORMAT_SCN;

drop table agg_edrformat_scn;

drop index AK_AGG_EDRFORMAT_CODE;

drop index PK_AGG_EDRFORMAT;

drop table agg_edrformat;

drop index AK_AGG_EDRCFIELD_INTERNAL_ID;

alter table AGG_EDRCFIELD
  drop column edrc_type;

alter table AGG_EDRCFIELD
  drop column internal_field_id;

alter table agg_scenario
  drop column valid_from;

alter table agg_scenario
  drop column valid_to;

insert into int_dbversion
( dbversion, description, username, install_date )
values
( 'v4-05-01', 'integRate/tariffIC + aggreGate', user, sysdate );

commit;

