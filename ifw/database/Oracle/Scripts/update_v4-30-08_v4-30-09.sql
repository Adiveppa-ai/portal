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
--   Update script from DB version v4-30-08 to v4-30-09.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-08_v4-30-09.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/12/10 13:56:01 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-08_v4-30-09.sql,v $
-- Revision 1.1  2001/12/10 13:56:01  pengelbr
-- PETS #42412 IFW_DISCARDING.MODIFIED disappeared accidently
-- since v4-30-05. Re-added column.
--
--------------------------------------------------------------------------------

spool update_v4-30-08_v4-30-09.log

--
-- IFW_DISCARDING
--
alter table ifw_discarding add ( modified number(1) default 1 not null );

alter table ifw_discarding add constraint CKC_MODIFIED_IFW_DISCARDING check (MODIFIED in (0,1));

comment on column IFW_DISCARDING.MODIFIED is 'MODIFIED';

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-09', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
