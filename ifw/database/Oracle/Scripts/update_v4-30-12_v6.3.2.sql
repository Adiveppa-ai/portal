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
-- 2002/06/14 pengelbr
-- CQUEST: PRSF00012257 update script update_v4-30-12_v6.3.2.sql contains 2 errors
--   - fixed first error!
--   - Cannot fix second error!
--
-- 2002/06/10 pengelbr
-- a) ECR_Roaming
--   - IC_DAILY: remove ACCOUNT_POID and replace by PIN_LOGIN_ALIAS
--   - IC_DAILY: add column and agg.attribute GLACCOUNT
--   - IFW_NETWORKOPERATOR: remove ACCOUNT_POID
--   - IFW_ICPRODUCT_RATE: add column PIN_LOGIN_ALIAS
-- b) PETS #39719 
--   - add column SEQ_GAPNUMBERS to IFW_SEQCHECK.
--   - add columns STATUS, PROCESSED to IFW_SEQLOG_IN
--   - add column NUM_REC_OUT to IFW_SEQLOG_OUT
--   - drop column STATUS from IFW_SEQLOG_OUT
--
-- 2002/06/07 pengelbr
-- PETS #44871 some errors in update_v4-30-12_v6-30-00.sql
--
--------------------------------------------------------------------------------

spool update_v4-30-12_v6.3.2.log

-- =============================================================================
-- == ECR Roaming
-- == - Enhance sequencer
-- =============================================================================

--
-- IFW_SEQCHECK
--
create table IFW_SEQCHECK
(
    SEQUENCE_NAME            VARCHAR2(50)           not null,
    SEQ_NUMBER               NUMBER(9)              not null,
    SEQ_ORIGNUMBER           NUMBER(9)              not null,
    SEQ_GAPNUMBERS           VARCHAR2(254)          null    ,
    SEQ_OFFSET               NUMBER(9)              not null,
    SEQ_MAXSEQUENCE          NUMBER(9)              not null,
    SEQ_MAXOFFSET            NUMBER(9)              not null,
    SEQ_MINSEQUENCE          NUMBER(9)              not null,
    SEQ_MINOFFSET            NUMBER(9)              not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_IFW_SEQCHECK check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_IFW_ESC primary key (SEQUENCE_NAME)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_1_IDX
        storage
        (
        initial 32K
        next 32K
        minextents 1
        maxextents unlimited
        pctincrease 0
     )
)
pctfree 10
pctused 80
initrans 2
storage
(
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_1_DAT;

grant select, insert, update, delete on IFW_SEQCHECK to INTEGRATE_ROLE_ALL;

grant select on IFW_SEQCHECK to INTEGRATE_ROLE_SEL;

comment on table IFW_SEQCHECK is 'Sequence check definition table.';

comment on column IFW_SEQCHECK.SEQUENCE_NAME is 'Name of the Sequencer used.';

comment on column IFW_SEQCHECK.SEQ_NUMBER is 'last generated sequence number';

comment on column IFW_SEQCHECK.SEQ_ORIGNUMBER is 'last original sequence number';

comment on column IFW_SEQCHECK.SEQ_GAPNUMBERS is 'remember seq-number gaps';

comment on column IFW_SEQCHECK.SEQ_OFFSET is 'number of recycling processes';

comment on column IFW_SEQCHECK.SEQ_MAXSEQUENCE is 'max sequence number';

comment on column IFW_SEQCHECK.SEQ_MAXOFFSET is 'max offset';

comment on column IFW_SEQCHECK.SEQ_MINSEQUENCE is 'min sequence number';

comment on column IFW_SEQCHECK.SEQ_MINOFFSET is 'min offset';

comment on column IFW_SEQCHECK.ENTRYBY is 'ENTRYBY';

comment on column IFW_SEQCHECK.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_SEQCHECK.MODIFBY is 'MODIFBY';

comment on column IFW_SEQCHECK.MODIFDATE is 'MODIFDATE';

comment on column IFW_SEQCHECK.MODIFIED is 'MODIFIED';

comment on column IFW_SEQCHECK.RECVER is 'RECVER';

--
-- IFW_SEQLOG_IN
--
create table IFW_SEQLOG_IN
(
    STREAMNAME               VARCHAR2(255)          not null,
    ORIG_SEQNO               NUMBER(9)              not null,
    RECYCLING                NUMBER(1)              default 0 not null
        constraint CKC_SLI_RECYCLING check (RECYCLING in (0,1)),
    PROCESSED                DATE                   null    ,
    STATUS                   CHAR(1)                default 'O' not null
        constraint CKC_SLI_STATUS check (STATUS in ('O','W','R')),
    NUM_REC_IN               NUMBER(9)              null    ,
    NUM_REC_OUT              NUMBER(9)              null    ,
    NUM_REC_WARN             NUMBER(9)              null    ,
    DURATION                 NUMBER(9)              null    ,
    PROCESSEDBY_PIPELINE     VARCHAR2(50)           not null,
    SEQUENCE_NAME            VARCHAR2(50)           not null,
    constraint PK_IFW_SLI primary key (STREAMNAME, ORIG_SEQNO, RECYCLING)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_1_IDX
        storage
        (
        initial 32K
        next 32K
        minextents 1
        maxextents unlimited
        pctincrease 0
     )
)
pctfree 10
pctused 80
initrans 2
storage
(
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_1_DAT;

grant select, insert, update, delete on IFW_SEQLOG_IN to INTEGRATE_ROLE_ALL;

grant select on IFW_SEQLOG_IN to INTEGRATE_ROLE_SEL;

comment on table IFW_SEQLOG_IN is 'IFW_SEQLOG_IN';

comment on column IFW_SEQLOG_IN.STREAMNAME is 'Name of the Stream to be processed.';

comment on column IFW_SEQLOG_IN.ORIG_SEQNO is 'Sequence number read from Stream.';

comment on column IFW_SEQLOG_IN.RECYCLING is 'Was the edr stream a recycling stream (1=Yes, 0=No)?';

comment on column IFW_SEQLOG_IN.PROCESSED is 'date when the edr stream had been processed (finish date)';

comment on column IFW_SEQLOG_IN.STATUS is 'status after the edr stream has been processed (O=ok, W=warning, R=rejections)';

comment on column IFW_SEQLOG_IN.NUM_REC_IN is 'number of input records';

comment on column IFW_SEQLOG_IN.NUM_REC_OUT is 'number of output records';

comment on column IFW_SEQLOG_IN.NUM_REC_WARN is 'number of records with a warning';

comment on column IFW_SEQLOG_IN.DURATION is 'duration in seconds to perform the total processing';

comment on column IFW_SEQLOG_IN.PROCESSEDBY_PIPELINE is 'Name of the pipeline the stream has been processed by.';

comment on column IFW_SEQLOG_IN.SEQUENCE_NAME is 'Sequence name used to check input sequences.';

--
-- IFW_SEQLOG_OUT
--
create table IFW_SEQLOG_OUT
(
    STREAMNAME_IN            VARCHAR2(255)          not null,
    ORIG_SEQNO               NUMBER(9)              not null,
    RECYCLING                NUMBER(1)              default 0 not null
        constraint CKC_SLO_RECYCLING check (RECYCLING in (0,1)),
    SEQUENCE_NAME            VARCHAR2(50)           not null,
    NEW_SEQNO                NUMBER(9)              not null,
    PROCESSED                DATE                   null    ,
    NUM_REC_OUT              NUMBER(9)              null    ,
    SUM_QUANTITY             NUMBER                 null    ,
    SUM_RT_CHARGE            NUMBER                 null    ,
    SUM_WS_CHARGE            NUMBER                 null    ,
    STREAMNAME_OUT           VARCHAR2(255)          not null,
    PROCESSEDBY_PIPELINE     VARCHAR2(50)           null    ,
    constraint PK_IFW_SLO primary key (STREAMNAME_IN, ORIG_SEQNO, RECYCLING, SEQUENCE_NAME, NEW_SEQNO)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_1_IDX
        storage
        (
        initial 128K
        next 128K
        minextents 1
        maxextents unlimited
        pctincrease 0
     )
)
pctfree 10
pctused 80
initrans 2
storage
(
initial 512K
next 512K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_1_DAT;

grant select, insert, update, delete on IFW_SEQLOG_OUT to INTEGRATE_ROLE_ALL;

grant select on IFW_SEQLOG_OUT to INTEGRATE_ROLE_SEL;

comment on table IFW_SEQLOG_OUT is 'edr sequence log, logging of each processed edr stream';

comment on column IFW_SEQLOG_OUT.STREAMNAME_IN is 'name of the input stream';

comment on column IFW_SEQLOG_OUT.ORIG_SEQNO is 'Sequence number read from Stream.';

comment on column IFW_SEQLOG_OUT.RECYCLING is 'Was the edr stream a recycling stream (1=Yes, 0=No)?';

comment on column IFW_SEQLOG_OUT.SEQUENCE_NAME is 'Pipelines output stream name.';

comment on column IFW_SEQLOG_OUT.NEW_SEQNO is 'new calculated sequence number (or equal to orig_seqno)';

comment on column IFW_SEQLOG_OUT.PROCESSED is 'date when the edr stream had been processed (finish date)';

comment on column IFW_SEQLOG_OUT.NUM_REC_OUT is 'number of output records';

comment on column IFW_SEQLOG_OUT.SUM_QUANTITY is 'sum of the Quantity Amount Value out of the edr-stream (e.g. total duration)';

comment on column IFW_SEQLOG_OUT.SUM_RT_CHARGE is 'sum of the Charged Amount Value out of the edr-stream (total retail charge amount)';

comment on column IFW_SEQLOG_OUT.SUM_WS_CHARGE is 'sum of the AoC Amount Value out of the edr-stream (total wholesale charge amount)';

comment on column IFW_SEQLOG_OUT.STREAMNAME_OUT is 'name of the output stream';

comment on column IFW_SEQLOG_OUT.PROCESSEDBY_PIPELINE is 'defines the pipeline which has processed the related stream (could be different from the orig-format in case of sequence sharring)';

--
-- Add foreign key references
--
alter table IFW_SEQLOG_IN
    add constraint FK_IFW_SLI_PPL foreign key  (PROCESSEDBY_PIPELINE)
       references IFW_PIPELINE (PIPELINE);
       
alter table IFW_SEQLOG_IN
    add constraint FK_IFW_SLI_SCK foreign key  (SEQUENCE_NAME)
       references IFW_SEQCHECK (SEQUENCE_NAME);
       
alter table IFW_SEQLOG_OUT
    add constraint FK_IFW_SLO_SCK foreign key  (SEQUENCE_NAME)
       references IFW_SEQCHECK (SEQUENCE_NAME);

alter table IFW_SEQLOG_OUT
    add constraint FK_IFW_SLO_PPL foreign key  (PROCESSEDBY_PIPELINE)
       references IFW_PIPELINE (PIPELINE);

--
-- Copy prev. data!
--
insert into IFW_SEQCHECK
( SEQUENCE_NAME, SEQ_NUMBER, SEQ_ORIGNUMBER, SEQ_OFFSET, SEQ_MAXSEQUENCE, SEQ_MAXOFFSET, SEQ_MINSEQUENCE, SEQ_MINOFFSET )
select 'UNKNOWN_'||PIPELINE, SEQ_NUMBER, SEQ_ORIGNUMBER, SEQ_OFFSET, SEQ_MAXSEQUENCE, SEQ_MAXOFFSET, SEQ_MINSEQUENCE, SEQ_MINOFFSET
from IFW_PIPELINE;

insert into IFW_SEQLOG_IN
( STREAMNAME, ORIG_SEQNO, RECYCLING, PROCESSED, STATUS, NUM_REC_IN, NUM_REC_OUT, NUM_REC_WARN, DURATION, PROCESSEDBY_PIPELINE, SEQUENCE_NAME )
select STREAMNAME_IN, ORIG_SEQNO, RECYCLING, PROCESSED, STATUS, NUM_REC_IN, NUM_REC_OUT, NUM_REC_WARN, DURATION, PIPELINE, 'UNKNOWN_'||PIPELINE 
from IFW_EDRSEQLOG;

insert into IFW_SEQLOG_OUT
( STREAMNAME_IN, ORIG_SEQNO, RECYCLING, SEQUENCE_NAME, NEW_SEQNO, PROCESSED, NUM_REC_OUT, SUM_QUANTITY, SUM_RT_CHARGE, SUM_WS_CHARGE, PROCESSEDBY_PIPELINE, STREAMNAME_OUT )
select STREAMNAME_IN, ORIG_SEQNO, RECYCLING, 'UNKNOWN_'||PIPELINE, NEW_SEQNO, PROCESSED, NUM_REC_OUT, SUM_QUANTITY, SUM_RT_CHARGE, SUM_WS_CHARGE, PROCESSEDBY_FORMAT, STREAMNAME_IN
from IFW_EDRSEQLOG;

--
-- IFW_PIPELINE
--
alter table ifw_pipeline drop column seq_number;

alter table ifw_pipeline drop column seq_orignumber;

alter table ifw_pipeline drop column seq_offset;

alter table ifw_pipeline drop column seq_maxsequence;

alter table ifw_pipeline drop column seq_maxoffset;

alter table ifw_pipeline drop column seq_minsequence;

alter table ifw_pipeline drop column seq_minoffset;

--
-- Foreign Key References
--
alter table IFW_EDRSEQLOG drop constraint fk_ifw_esq_ppl;

drop table ifw_edrseqlog;


-- =============================================================================
-- == ECR Roaming
-- == - Add Account POID to IFW_NETWORKOPERATOR
-- =============================================================================

--
-- IC_DAILY
--
alter table ic_daily add PIN_LOGIN_ALIAS VARCHAR2(255);

alter table ic_daily add GLACCOUNT VARCHAR2(10);

comment on column IC_DAILY.PIN_LOGIN_ALIAS is 'Login or Alias for Infranets NetworkOperator Account this entry has to be billed to.';

comment on column IC_DAILY.GLACCOUNT is 'glaccount on which the ic-bill should be aggregated';

alter table ic_daily drop primary key;

alter table ic_daily add constraint PK_ICD primary key (NETWORKMODEL, NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN, SWITCH, POI, TRUNK, ICPRODUCT, BILL_DIRECTION, RATEPLAN, SERVICECODE, SERVICECLASS, IMPACT_CATEGORY, TIMEMODEL, TIMEZONE, GLACCOUNT, RESOURCE_NAME, RUM, ENTRY_TYPE, ENTRY_TYPE_SEQ)
  using index
    pctfree 5
    initrans 2
    tablespace INTEGRATE_TS_4_IDX
    storage
    (
      initial 512K
      next 512K
      minextents 1
      maxextents unlimited
      pctincrease 0
    );

--
-- IC_DAILY_ALTERNATE
--
alter table ic_daily_alternate add PIN_LOGIN_ALIAS VARCHAR2(255);

alter table ic_daily_alternate add GLACCOUNT VARCHAR2(10);

comment on column IC_DAILY_ALTERNATE.PIN_LOGIN_ALIAS is 'Login or Alias for Infranets NetworkOperator Account this entry has to be billed to.';

comment on column IC_DAILY_ALTERNATE.GLACCOUNT is 'glaccount on which the ic-bill should be aggregated';

alter table ic_daily_alternate drop primary key;

alter table ic_daily_alternate add constraint PK_ICA primary key (NETWORKMODEL, NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN, SWITCH, POI, TRUNK, ICPRODUCT, BILL_DIRECTION, RATEPLAN, SERVICECODE, SERVICECLASS, IMPACT_CATEGORY, TIMEMODEL, TIMEZONE, GLACCOUNT, RESOURCE_NAME, RUM, ENTRY_TYPE, ENTRY_TYPE_SEQ)
  using index
    pctfree 5
    initrans 2
    tablespace INTEGRATE_TS_4_IDX
    storage
    (
      initial 512K
      next 512K
      minextents 1
      maxextents unlimited
      pctincrease 0
    );

--
-- IFW_ICPRODUCT_RATE
--
alter table ifw_icproduct_rate add PIN_LOGIN_ALIAS VARCHAR2(255);

comment on column IFW_ICPRODUCT_RATE.PIN_LOGIN_ALIAS is 'Infranet Login or Alias for NetworkModel, NetworkOperator and IcProduct to Identify Account to be billed (optional for Infranet integration).'

alter table ifw_icproduct_rate drop constraint CKC_ICR_ZONE_DIR;

alter table ifw_icproduct_rate drop constraint CKC_ZONE_DIR_IFW_ICR;

update ifw_icproduct_rate
set zone_direction = '1'
where zone_direction = 'I' or zone_direction = 'i';

update ifw_icproduct_rate
set zone_type = 'R'
where zone_direction = '1' and ( zone_type = 'N' or zone_type = 'n' );

update ifw_icproduct_rate
set zone_direction = '2'
where zone_direction = 'O' or zone_direction = 'o';

update ifw_icproduct_rate
set zone_direction = '4'
where zone_direction = 'S' or zone_direction = 's';

update ifw_icproduct_rate
set zone_direction = '7'
where zone_direction = 'T' or zone_direction = 't';

update ifw_icproduct_rate
set zone_direction = '0'
where zone_direction = 'N' or zone_direction = 'n';

alter table ifw_icproduct_rate add constraint CKC_ICR_ZONE_DIR check (ZONE_DIRECTION in ('0','1','2','3','4','5','6','7'));

comment on column IFW_ICPRODUCT_RATE.ZONE_DIRECTION is 'zoning direction (0=none, 1=A->POI/Inroute, 2=POI->B/Outroute, 3=POI->C, 4=A->B/Standard, 5=A->C, 6=B->C, 7=POI-In->POI-Out/Transit)';


-- =============================================================================
-- == ECR Roaming
-- == - Move GL/Account and RevenueGroup from IFW_RATEPLAN_CNF to 
-- ==   IFW_PRICEMODEL_STEP
-- =============================================================================

--
-- IFW_PRICEMODEL_STEP
--
alter table ifw_pricemodel_step add GLACCOUNT VARCHAR2(10) null;

alter table ifw_pricemodel_step add REVENUEGROUP VARCHAR2(5) null;

update ifw_pricemodel_step pms
set pms.glaccount = ( select rpc.glaccount 
			  	      from ifw_rateplan_cnf rpc
				      where rpc.pricemodel = pms.pricemodel and rownum = 1 );

update ifw_pricemodel_step pms
set pms.revenuegroup = ( select revenuegroup 
			  	         from ifw_rateplan_cnf rpc
					 	 where rpc.pricemodel = pms.pricemodel and rownum = 1 );

insert into ifw_taxcode
( taxcode, name )
values 
( 'DUMMY', 'Dummy TaxCode for migration v4-30-12 to v6-30-00' );

insert into ifw_glaccount
( glaccount, name, taxcode, gla_type )
values
( 'DUMMY', 'Dummy GL/Account for migration v4-30-12 to v6-30-00', 'DUMMY', 'R' );

update ifw_pricemodel_step
set glaccount = 'DUMMY'
where glaccount is null;

alter table ifw_pricemodel_step modify GLACCOUNT not null;

comment on column IFW_PRICEMODEL_STEP.GLACCOUNT is 'references a specific usage based general ledger account code for this configuration entry';

comment on column IFW_PRICEMODEL_STEP.REVENUEGROUP is 'references a usage group (for splitted billing purposes)';

alter table IFW_PRICEMODEL_STEP
    add constraint FK_IFW_PMS_GLA foreign key  (GLACCOUNT)
       references IFW_GLACCOUNT (GLACCOUNT);

alter table IFW_PRICEMODEL_STEP
    add constraint FK_IFW_PMS_RVG foreign key  (REVENUEGROUP)
       references IFW_REVENUEGROUP (REVENUEGROUP);

--
-- IFW_RATEPLAN_CNF
--
alter table ifw_rateplan_cnf drop constraint fk_ifw_rpc_gma;

alter table ifw_rateplan_cnf drop constraint fk_ifw_rpc_rvg;

alter table ifw_rateplan_cnf drop column glaccount;

alter table ifw_rateplan_cnf drop column revenuegroup;

--
-- IFW_ISCRIPT
--
alter table ifw_iscript modify scriptcode varchar2(50);

alter table ifw_ruleitem modify rule varchar2(50);

alter table ifw_rulesetlist modify ruleset varchar2(50);

alter table ifw_rulesetlist modify rule varchar2(50);

alter table ifw_ruleset modify ruleset varchar2(50);

alter table ifw_rule modify rule varchar2(50);

alter table ifw_ruleset add description varchar2(2000);

comment on column ifw_ruleset.description is 'Description/Comment';


-- =============================================================================
-- == ECR Discount
-- == - Rollover discounts
-- =============================================================================

--
-- IFW_DISCOUNTSTEP
--
alter table ifw_discountstep add ROLLOVER_MONTHS NUMBER(9) default 1 not null;

alter table ifw_discountstep add ROLLOVER_MAX NUMBER null;

update ifw_discountstep set rollover_max = rollover_units;

alter table ifw_discountstep modify ROLLOVER_MAX not null;

alter table ifw_discountstep add ROLLOVER_EDR_PERIOD NUMBER(1) null;

alter table ifw_discountstep add constraint CKC_DSC_ROLLPERIOD check (ROLLOVER_EDR_PERIOD in (0,1));

update ifw_discountstep set rollover_edr_period = 1;

alter table ifw_discountstep modify ROLLOVER_EDR_PERIOD not null;

alter table ifw_discountstep add RESOURCE_ID NUMBER(9) null;

comment on column IFW_DISCOUNTSTEP.ROLLOVER_MONTHS is 'number of months/periods rollover units are valid (0: valid forever)';

comment on column IFW_DISCOUNTSTEP.ROLLOVER_MAX is 'maximum value of rollover-units sum to be rolled over (has to be greater or equal rollover_units)';

comment on column IFW_DISCOUNTSTEP.ROLLOVER_EDR_PERIOD is '1 is use only the related EDR rollover period; 0 is EDR period does not matter';

comment on column IFW_DISCOUNTSTEP.RESOURCE_ID is 'Infranets resource-id';

--
-- IFW_DISCOUNTMDL_CNF
--
alter table ifw_discountmdl_cnf add CASCADING NUMBER(1) default 0 not null;

comment on column IFW_DISCOUNTMDL_CNF.CASCADING is 'use entry only if previous rank is completed (completely used)';

--
-- IFW_SUBS_ACCOUNT
--
drop table ifw_subs_account;


--
-- IFW_SEMAPHORE
--
drop table ifw_semaphore;


--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.3.2', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
