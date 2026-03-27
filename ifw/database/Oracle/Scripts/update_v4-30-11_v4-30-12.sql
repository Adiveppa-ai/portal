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
--   Update script from DB version v4-30-11 to v4-30-12.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-11_v4-30-12.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2002/02/15 10:27:29 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-11_v4-30-12.sql,v $
-- Revision 1.2  2002/02/15 10:27:29  pengelbr
-- - PETS #39719 Sequencer can't handle files from different senders.
--   - Move SEQ columns for Sequencer from IFW_PIPELINE into
--     new table IFW_EDRSEQCHECK.
--   - Add new column STREAM_NAME to Pk of IFW_EDRSEQLOG.
-- - PETS #43397 Missing right parenthesis in script update_v4-30-11_v4-30-12.sql
--
-- Revision 1.1  2002/01/30 16:02:45  pengelbr
-- Changes for ifw 6.2 SP1
--
--------------------------------------------------------------------------------

spool update_v4-30-11_v4-30-12.log

--
-- IFW_DISCARDING
--
alter table ifw_discarding add ( DESTIN_NETWORK VARCHAR2(2000) default '.*' not null );

comment on column IFW_DISCARDING.DESTIN_NETWORK is 'Condition: the ''destination network'' which should be mapped (regular expression, default ''.*'')';

--
-- IFW_RATEPLAN
--
alter table ifw_rateplan add ( split char(1) );

update ifw_rateplan set split = to_char(splitting);

alter table ifw_rateplan drop column splitting;

alter table ifw_rateplan add ( splitting char(1) default '0' not null );

alter table ifw_rateplan add constraint CKC_RPD_SPLITTING check (SPLITTING in ('0','1','2','3'));

comment on column IFW_RATEPLAN.SPLITTING is 'Defines the type of TimeZone-Splitting. (0: NO-Splitting based on Start-Time, 1: CONSECUTIVE-Splitting based on Start-Time, 2: NO-Splitting based on End-Time, 3: ISOLATED-Splitting based on Start-Time)';

update ifw_rateplan set splitting = split;

alter table ifw_rateplan drop column split;

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-12', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
