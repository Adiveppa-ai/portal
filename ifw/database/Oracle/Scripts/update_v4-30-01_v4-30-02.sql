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
--   Update script from DB version v4-30-01 to v4-30-02.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-01_v4-30-02.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/07/10 13:55:28 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-01_v4-30-02.sql,v $
-- Revision 1.1  2001/07/10 13:55:28  pengelbr
-- PETS #36809 Add new column REF_PARAM to IFW_REF_MAP.
--
--------------------------------------------------------------------------------

spool update_v4-30-01_v4-30-02.log

--
-- IFW_REF_MAP
--
alter table ifw_ref_map add ( ref_param varchar2(254) null );

comment on column IFW_REF_MAP.REF_PARAM is 'Additional optional parameter';

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-02', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
