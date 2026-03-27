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
--   Update script from DB version v6.7.5 to v6.7.6.
--------------------------------------------------------------------------------
-- Responsible: Mark Murthy
--------------------------------------------------------------------------------
-- Log:
-- 2004/11/08 mmurthy 
-- PRSF00124446 Sequencer problem: ORA-00904: "PROCESSEDBY_PPL": invalid 
-- identifier
--
--------------------------------------------------------------------------------

spool update_v6.7.5_v6.7.6.log

alter table IFW_SEQLOG_OUT add PROCESSEDBY_PPL VARCHAR2(50) null;

alter table IFW_SEQLOG_IN add PROCESSEDBY_PPL VARCHAR2(50) not null;

alter table IFW_SEQLOG_IN add SEQUENCE_NAME VARCHAR2(50) not null;

comment on column IFW_SEQLOG_OUT.PROCESSEDBY_PPL is 'defines the pipeline which has processed the related stream (could be different from the orig-format in case of sequence sharring)';

comment on column IFW_SEQLOG_IN.PROCESSEDBY_PPL is 'Name of the pipeline the stream has been processed by.';

comment on column IFW_SEQLOG_IN.SEQUENCE_NAME is 'Sequence name used to check input sequences.';

--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.7.6', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

