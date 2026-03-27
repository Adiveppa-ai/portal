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
--   Update script from DB version v6.3.4 to v6.5.1.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--------------------------------------------------------------------------------
-- Log:
-- 2004/06/15 knijhawa
-- PRSF00114365 Server side dependency for Revence Assurance related Smacc works...
--
-- 2002/10/23 pengelbr
-- PRSF00020915 database update scripts for IFW are not clear- they say 6.4 
-- should be 6.5, unclear how to move from 6.2-6.5 or 6.3-6.5 
--
-- 2002/10/01 gireesh
-- PRSF00019276 database scripts contain wrong init values for the new sequencer key
--
-- 2002/09/17 pengelbr
-- PRSF00018585 update script update_v6.3.4_v6.5.1.sql contains a misstype
--
-- 2002/08/05 pengelbr
-- PRSF000xxxxx Database changes for Athena
--
--------------------------------------------------------------------------------

--
-- Cegetel: Adjust table-/column-names to max length 18
-- Decimal beats for rating.
--

--
-- Drop ref. constraints for affected tables
--
alter table IFW_DISCOUNTMDL_VER drop constraint FK_IFW_DMV_DML;

alter table IFW_GEOGRAPHICALMODEL drop constraint FK_IFW_GMD_RUS;

alter table IFW_GEOAREACODE_LNK drop constraint FK_IFW_GAL_GMD;

alter table IFW_NETWORKOPERATOR drop constraint FK_IFW_NOP_TXG;

alter table IFW_NETWORKOPERATOR drop constraint FK_IFW_NOP_CUR;

alter table IFW_NETWORKMODEL drop constraint FK_IFW_NWM_RPD;

alter table IFW_NETWORKMODEL drop constraint FK_IFW_NWM_SYB;

alter table IFW_NETWORKMODEL drop constraint FK_IFW_NWM_NOP;

alter table IFW_NETWORKMODEL drop constraint FK_IFW_NWM_CUR;

alter table IFW_SCENARIO drop constraint FK_IFW_SCN_EDE;

alter table IFW_CLASSCON drop constraint FK_IFW_CLC_GRCNEXT;

alter table IFW_CLASSCON drop constraint FK_IFW_CLC_GRPNODE;

alter table IFW_USAGESCENARIO_MAP drop constraint FK_IFW_USM_NEWCTP;

alter table IFW_USAGESCENARIO_MAP drop constraint FK_IFW_USM_ZMD;

alter table IFW_USAGESCENARIO_MAP drop constraint FK_IFW_USM_USC;

alter table IFW_USAGESCENARIO_MAP drop constraint FK_IFW_USM_RTICT;

alter table IFW_USAGESCENARIO_MAP drop constraint FK_IFW_USM_WSICT;

alter table IFW_PRICEMODEL_STEP drop constraint FK_IFW_PMS_PMD;

alter table IFW_PRICEMODEL_STEP drop constraint FK_IFW_PMS_RES;

alter table IFW_PRICEMODEL_STEP drop constraint FK_IFW_PMS_RUM;

alter table IFW_PRICEMODEL_STEP drop constraint FK_IFW_PMS_GLA;

alter table IFW_PRICEMODEL_STEP drop constraint FK_IFW_PMS_RVG;

alter table IFW_GEOGRAPHICAL_ZONE drop constraint FK_IFW_GOZ_ZMD;

alter table IFW_GEOGRAPHICAL_ZONE drop constraint FK_IFW_GOZ_SRV;

alter table IFW_GEOGRAPHICAL_ZONE drop constraint FK_IFW_GOZ_ALTZMD;

alter table IFW_GEOGRAPHICAL_ZONE drop constraint FK_IFW_GEZW_ICT;

alter table IFW_GEOGRAPHICAL_ZONE drop constraint FK_IFW_GEZRT_ICT;

alter table IFW_SERVICECODE_MAP drop constraint FK_IFW_SVM_MGR;

alter table IFW_SERVICECODE_MAP drop constraint FK_IFW_SCM_SRV;

alter table IFW_SEQLOG_OUT drop constraint FK_IFW_SLO_SCK;

alter table IFW_SEQLOG_OUT drop constraint FK_IFW_SLO_PPL;

alter table IFW_DISCOUNTMDL_CNF drop constraint FK_IFW_DMC_DCR;

alter table IFW_DISCOUNTMDL_CNF drop constraint FK_IFW_DMC_DTR;

alter table IFW_DISCOUNTMDL_CNF drop constraint FK_IFW_DMC_DMV;

alter table IFW_DISCOUNTSTEP drop constraint FK_IFW_DCS_DCM;

alter table IFW_DISCOUNTSTEP drop constraint FK_IFW_DCS_DCR;

alter table IFW_DISCOUNTSTEP drop constraint FK_IFW_DCS_UOM;

alter table IFW_DISCOUNTCONDITION drop constraint FK_IFW_DCN_DCM;

alter table IFW_DISCOUNTCONDITION drop constraint FK_IFW_DCN_DTR;

alter table IFW_RATESERVICE_MAP drop constraint FK_IFW_RSM_SVC;

alter table IFW_RATESERVICE_MAP drop constraint FK_IFW_RSM_RSG;

alter table IFW_AGGREGATION drop constraint FK_IFW_AGG_SCN;

alter table IFW_AGGREGATION drop constraint FK_IFW_AGG_EFD;

alter table IFW_ICPRODUCT_RATE drop constraint FK_IFW_IPR_NWM;

alter table IFW_ICPRODUCT_RATE drop constraint FK_IFW_IPR_NOP;

alter table IFW_LERG_DATA drop constraint FK_IFW_LERG_GAL;

alter table IFW_SEQLOG_IN drop constraint FK_IFW_SLI_PPL;

alter table IFW_SEQLOG_IN drop constraint FK_IFW_SLI_SCK;

alter table IFW_ZONEMODEL drop constraint FK_IFW_ZMD_GMD;

alter table IFW_SWITCH drop constraint FK_IFW_SWI_NOP;

alter table IFW_NOPRODUCT drop constraint FK_IFW_NPR_NOP;

alter table IFW_TRUNK drop constraint FK_IFW_TRK_CNO;

alter table IFW_ICPRODUCT_GROUP drop constraint FK_IFW_IPG_NWM;

alter table IFW_GROUPING drop constraint FK_IFW_GRP_SCN;

alter table IFW_STANDARD_ZONE drop constraint FK_IFW_STZ_ICT;

alter table IFW_STANDARD_ZONE drop constraint FK_IFW_STZRT_ICT;

alter table IFW_POIAREA_LNK drop constraint FK_IFW_PAL_NWM;

alter table IFW_APN_MAP drop constraint FK_IFW_APNWS_ICT;

alter table IFW_APN_MAP drop constraint FK_IFW_APNRT_ICT;

alter table IFW_NOPRODUCT_CNF drop constraint FK_IFW_NPC_ICT;

alter table IFW_NO_BILLRUN drop constraint FK_IFW_NBR_NOP;

alter table IFW_NO_BILLRUN drop constraint FK_IFW_NBR_NWM;

alter table IFW_CONDITION drop constraint FK_IFW_CND_SCN;

alter table IFW_TRUNK_CNF drop constraint FK_IFW_TRC_IPG;

alter table IFW_TRUNK_CNF drop constraint FK_IFW_TRC_NWM;

alter table IFW_TRUNK_CNF drop constraint FK_IFW_TRC_NOP;

alter table IFW_ICPRODUCT_CNF drop constraint FK_IFW_IPC_IPG;

alter table IFW_RATEPLAN_CNF drop constraint FK_IFW_RPC_ICT;

alter table IFW_CLASSCON_LNK drop constraint FK_IFW_CCL_CLC;

--
-- update all tables
--

-- IFW_DISCOUNTMDL_CNF   -> IFW_DSCMDL_CNF
drop index AK_IFW_DMC;

alter table IFW_DISCOUNTMDL_CNF drop constraint CKC_DMC_CASCADING;

alter table IFW_DISCOUNTMDL_CNF drop primary key;

rename IFW_DISCOUNTMDL_CNF to TMP_DISCOUNTMDL_CNF;

create table IFW_DSCMDL_CNF
(
    DISCOUNTCONFIG      NUMBER(9)              not null,
    DISCOUNTMODEL       NUMBER(9)              not null,
    VERSION             NUMBER(9)              not null,
    RANK                NUMBER(9)              not null,
    DISCOUNTTRIGGER     NUMBER(9)              not null,
    DISCOUNTRULE        NUMBER(9)              not null,
    CASCADING           NUMBER(1)              default 0 not null
        constraint CKC_DMC_CASCADING check (CASCADING in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_DMC primary key (DISCOUNTCONFIG)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_IDX
        storage
        (
        initial 256K
        next 256K
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
initial 1024K
next 1024K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_2_DAT;

grant select, insert, update, delete on IFW_DSCMDL_CNF to INTEGRATE_ROLE_ALL;

grant select on IFW_DSCMDL_CNF to INTEGRATE_ROLE_SEL;

comment on table IFW_DSCMDL_CNF is 'discount model configuration (main entry point for price calculation for a given tariff model, using service,zone,timemodel combinations)';

comment on column IFW_DSCMDL_CNF.DISCOUNTCONFIG is 'unique internal id identifying the configuration entry';

comment on column IFW_DSCMDL_CNF.DISCOUNTMODEL is 'references the related discountmodel this configuration entry belongs to';

comment on column IFW_DSCMDL_CNF.VERSION is 'references the related discountmodel version this configuration entry belongs to';

comment on column IFW_DSCMDL_CNF.RANK is 'defines the order of configuration entries within a discount model';

comment on column IFW_DSCMDL_CNF.DISCOUNTTRIGGER is 'unique id, defining a discount trigger';

comment on column IFW_DSCMDL_CNF.DISCOUNTRULE is 'unique id, defining a discount rule';

comment on column IFW_DSCMDL_CNF.CASCADING is 'use entry only if previous rank is completed (completely used)';

comment on column IFW_DSCMDL_CNF.RECVER is 'RECVER';

create unique index AK_IFW_DMC on IFW_DSCMDL_CNF (DISCOUNTMODEL asc, VERSION asc, RANK asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_2_IDX
storage
(
initial 256K
next 256K
minextents 1
maxextents unlimited
pctincrease 0
);

insert into IFW_DSCMDL_CNF
( DISCOUNTCONFIG, DISCOUNTMODEL, VERSION, RANK, DISCOUNTTRIGGER, DISCOUNTRULE, CASCADING, RECVER )
select DISCOUNTCONFIG, DISCOUNTMODEL, VERSION, RANK, DISCOUNTTRIGGER, DISCOUNTRULE, CASCADING, RECVER
from TMP_DISCOUNTMDL_CNF;

-- IFW_DISCOUNTMDL_VER   -> IFW_DSCMDL_VER
alter table IFW_DISCOUNTMDL_VER drop constraint CKC_DMV_STATUS;

alter table IFW_DISCOUNTMDL_VER drop constraint CKC_DMV_MODIFIED;

alter table IFW_DISCOUNTMDL_VER drop primary key;

rename IFW_DISCOUNTMDL_VER to TMP_DISCOUNTMDL_VER;

create table IFW_DSCMDL_VER
(
    DISCOUNTMODEL       NUMBER(9)              not null,
    VERSION             NUMBER(9)              not null,
    VALID_FROM          DATE                   not null,
    STATUS              CHAR(1)                default 'D' not null
        constraint CKC_DMV_STATUS check (STATUS in ('A','D','T','S')),
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_DMV_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_DMV primary key (DISCOUNTMODEL, VERSION)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_IDX
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
tablespace INTEGRATE_TS_2_DAT;

grant select, insert, update, delete on IFW_DSCMDL_VER to INTEGRATE_ROLE_ALL;

grant select on IFW_DSCMDL_VER to INTEGRATE_ROLE_SEL;

comment on table IFW_DSCMDL_VER is 'defines different versions of a discount model';

comment on column IFW_DSCMDL_VER.DISCOUNTMODEL is 'references the discount model';

comment on column IFW_DSCMDL_VER.VERSION is 'unique version within the discount model';

comment on column IFW_DSCMDL_VER.VALID_FROM is 'date from when on this version is valid (if empty it is always valid)';

comment on column IFW_DSCMDL_VER.STATUS is 'status of this discount model version (A=active, D=deactive, T=test, S=simulation)';

comment on column IFW_DSCMDL_VER.ENTRYBY is 'ENTRYBY';

comment on column IFW_DSCMDL_VER.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_DSCMDL_VER.MODIFBY is 'MODIFBY';

comment on column IFW_DSCMDL_VER.MODIFDATE is 'MODIFDATE';

comment on column IFW_DSCMDL_VER.MODIFIED is 'MODIFIED';

comment on column IFW_DSCMDL_VER.RECVER is 'RECVER';

insert into IFW_DSCMDL_VER
( DISCOUNTMODEL, VERSION, VALID_FROM, STATUS, ENTRYBY, ENTRYDATE, MODIFBY, MODIFDATE, MODIFIED, RECVER )
select DISCOUNTMODEL, VERSION, VALID_FROM, STATUS, ENTRYBY, ENTRYDATE, MODIFBY, MODIFDATE, MODIFIED, RECVER
from TMP_DISCOUNTMDL_VER;

-- IFW_DISCOUNTTRIGGER   -> IFW_DSCTRIGGER
alter table IFW_DISCOUNTTRIGGER drop constraint CKC_DTR_MODIFIED;

alter table IFW_DISCOUNTTRIGGER drop primary key;

rename IFW_DISCOUNTTRIGGER to TMP_DISCOUNTTRIGGER;

create table IFW_DSCTRIGGER
(
    DISCOUNTTRIGGER     NUMBER(9)              not null,
    CODE                VARCHAR2(10)           not null,
    NAME                VARCHAR2(255)          null    ,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_DTR_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_DTR primary key (DISCOUNTTRIGGER)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_IDX
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
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_2_DAT;

grant select, insert, update, delete on IFW_DSCTRIGGER to INTEGRATE_ROLE_ALL;

grant select on IFW_DSCTRIGGER to INTEGRATE_ROLE_SEL;

comment on table IFW_DSCTRIGGER is 'defines a set of discount conditions';

comment on column IFW_DSCTRIGGER.DISCOUNTTRIGGER is 'Unique internal id';

comment on column IFW_DSCTRIGGER.CODE is 'unique external code or short reference';

comment on column IFW_DSCTRIGGER.NAME is 'name or description';

comment on column IFW_DSCTRIGGER.ENTRYBY is 'ENTRYBY';

comment on column IFW_DSCTRIGGER.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_DSCTRIGGER.MODIFBY is 'MODIFBY';

comment on column IFW_DSCTRIGGER.MODIFDATE is 'MODIFDATE';

comment on column IFW_DSCTRIGGER.MODIFIED is 'MODIFIED';

comment on column IFW_DSCTRIGGER.RECVER is 'RECVER';

insert into IFW_DSCTRIGGER
(DISCOUNTTRIGGER, CODE, NAME, ENTRYBY, ENTRYDATE, MODIFBY, MODIFDATE, MODIFIED, RECVER)
select DISCOUNTTRIGGER, CODE, NAME, ENTRYBY, ENTRYDATE, MODIFBY, MODIFDATE, MODIFIED, RECVER
from TMP_DISCOUNTTRIGGER;

-- IFW_DISCOUNTCONDITION -> IFW_DSCCONDITION
alter table IFW_DISCOUNTCONDITION drop constraint CKC_DCN_BASE;

alter table IFW_DISCOUNTCONDITION drop constraint CKC_DCN_MODIFIED;

alter table IFW_DISCOUNTCONDITION drop primary key;

rename IFW_DISCOUNTCONDITION to TMP_DISCOUNTCONDITION;

create table IFW_DSCCONDITION
(
    DISCOUNTCONDITION   NUMBER(9)              not null,
    DISCOUNTTRIGGER     NUMBER(9)              not null,
    DISCOUNTMASTER      NUMBER(9)              not null,
    CONDITION_BASE      CHAR(1)                not null
        constraint CKC_DCN_BASE check (CONDITION_BASE in ('C','E','Q')),
    CONDITION_VALUE     NUMBER                 not null,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_DCN_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_DCN primary key (DISCOUNTCONDITION)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_IDX
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
tablespace INTEGRATE_TS_2_DAT;

grant select, insert, update, delete on IFW_DSCCONDITION to INTEGRATE_ROLE_ALL;

grant select on IFW_DSCCONDITION to INTEGRATE_ROLE_SEL;

comment on table IFW_DSCCONDITION is 'defines one or more trigger conditions';

comment on column IFW_DSCCONDITION.DISCOUNTCONDITION is 'internal id';

comment on column IFW_DSCCONDITION.DISCOUNTTRIGGER is 'referenced discount trigger';

comment on column IFW_DSCCONDITION.DISCOUNTMASTER is 'referenced discount master';

comment on column IFW_DSCCONDITION.CONDITION_BASE is 'defines the measure base for a condition (''C''harge, ''Q''uantity or ''E''vent)';

comment on column IFW_DSCCONDITION.CONDITION_VALUE is 'defines the value for a condition';

comment on column IFW_DSCCONDITION.ENTRYBY is 'ENTRYBY';

comment on column IFW_DSCCONDITION.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_DSCCONDITION.MODIFBY is 'MODIFBY';

comment on column IFW_DSCCONDITION.MODIFDATE is 'MODIFDATE';

comment on column IFW_DSCCONDITION.MODIFIED is 'MODIFIED';

comment on column IFW_DSCCONDITION.RECVER is 'RECVER';

insert into IFW_DSCCONDITION
(DISCOUNTCONDITION, DISCOUNTTRIGGER, DISCOUNTMASTER, CONDITION_BASE, CONDITION_VALUE, ENTRYBY, ENTRYDATE, MODIFBY, MODIFDATE, MODIFIED, RECVER)
select DISCOUNTCONDITION, DISCOUNTTRIGGER, DISCOUNTMASTER, CONDITION_BASE, CONDITION_VALUE, ENTRYBY, ENTRYDATE, MODIFBY, MODIFDATE, MODIFIED, RECVER
from TMP_DISCOUNTCONDITION;

-- IFW_DISCOUNTSTEP.ROLLOVER_EDR_PERIOD       -> ROLLOVER_PERIOD
drop index AK_IFW_DCS;

alter table IFW_DISCOUNTSTEP drop constraint CKC_DCS_THRESHOLD;

alter table IFW_DISCOUNTSTEP drop constraint CKC_DCS_DISCTYPE;

alter table IFW_DISCOUNTSTEP drop constraint CKC_DCS_GRANTTYPE;

alter table IFW_DISCOUNTSTEP drop constraint CKC_DCS_PRORATE;

alter table IFW_DISCOUNTSTEP drop constraint CKC_DCS_ROLLPERIOD;

alter table IFW_DISCOUNTSTEP drop constraint CKC_DCS_ENRICH;

alter table IFW_DISCOUNTSTEP drop constraint CKC_DCS_MODIFIED;

alter table IFW_DISCOUNTSTEP drop primary key;

rename IFW_DISCOUNTSTEP to TMP_DISCOUNTSTEP;

create table IFW_DISCOUNTSTEP
(
    DISCOUNTSTEP        NUMBER(9)              not null,
    DISCOUNTRULE        NUMBER(9)              not null,
    RANK                NUMBER(9)              not null,
    DISCOUNTMASTER      NUMBER(9)              not null,
    THRESHOLD_TYPE      CHAR(1)                not null
        constraint CKC_DCS_THRESHOLD check (THRESHOLD_TYPE in ('C','E','Q')),
    THRESHOLD_FROM      NUMBER                 null    ,
    THRESHOLD_TO        NUMBER                 null    ,
    DISCOUNT_TYPE       CHAR(1)                default 'A' not null
        constraint CKC_DCS_DISCTYPE check (DISCOUNT_TYPE in ('A','P')),
    GRANT_TYPE          CHAR(1)                not null
        constraint CKC_DCS_GRANTTYPE check (GRANT_TYPE in ('C','Q')),
    GRANT_PRORATEDBEAT  NUMBER(1)              default 1 not null
        constraint CKC_DCS_PRORATE check (GRANT_PRORATEDBEAT in (0,1)),
    GRANT_UNITS         NUMBER                 not null,
    GRANT_BEAT          NUMBER                 default 0 not null,
    GRANT_UOM           VARCHAR2(3)            not null,
    ROLLOVER_UNITS      NUMBER                 default 0 not null,
    ROLLOVER_MONTHS     NUMBER(9)              default 1 not null,
    ROLLOVER_MAX        NUMBER                 not null,
    ROLLOVER_PERIOD     NUMBER(1)              default 1 not null
        constraint CKC_DCS_ROLLPERIOD check (ROLLOVER_PERIOD in (0,1)),
    RESOURCE_ID         NUMBER(9)              null    ,
    EDR_ENRICHMENT      NUMBER(1)              default 0 not null
        constraint CKC_DCS_ENRICH check (EDR_ENRICHMENT in (0,1)),
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_DCS_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_DCS primary key (DISCOUNTSTEP)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_IDX
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
tablespace INTEGRATE_TS_2_DAT;

grant select, insert, update, delete on IFW_DISCOUNTSTEP to INTEGRATE_ROLE_ALL;

grant select on IFW_DISCOUNTSTEP to INTEGRATE_ROLE_SEL;

comment on table IFW_DISCOUNTSTEP is 'defines the single discount steps (thresholds)';

comment on column IFW_DISCOUNTSTEP.DISCOUNTSTEP is 'DISCOUNTSTEP';

comment on column IFW_DISCOUNTSTEP.DISCOUNTRULE is 'references the related discount rule under which this step is grouped';

comment on column IFW_DISCOUNTSTEP.RANK is 'unique step identifier';

comment on column IFW_DISCOUNTSTEP.DISCOUNTMASTER is 'unique internal id';

comment on column IFW_DISCOUNTSTEP.THRESHOLD_TYPE is 'the unit of the tresholds measurement (''C''harge, ''Q''uantity or ''E''vent)';

comment on column IFW_DISCOUNTSTEP.THRESHOLD_FROM is 'lower boundary threshold from when on this discount stagger step is valid (compare: >), negative values allowed';

comment on column IFW_DISCOUNTSTEP.THRESHOLD_TO is 'lower boundary threshold from when on this discount stagger step is valid (compare: <=)';

comment on column IFW_DISCOUNTSTEP.DISCOUNT_TYPE is 'type of the discount value (P=percantage, A=addon value)';

comment on column IFW_DISCOUNTSTEP.GRANT_TYPE is 'defines what should be granted: Q - grant quantity, C - grant charge';

comment on column IFW_DISCOUNTSTEP.GRANT_PRORATEDBEAT is 'grant pro-rated beats (1=TRUE=pro-rated, 0=FALSE=absolut beat-based)';

comment on column IFW_DISCOUNTSTEP.GRANT_UNITS is 'defines the granted discount (the content of this value is dependent to the GRANT_TYPE)';

comment on column IFW_DISCOUNTSTEP.GRANT_BEAT is 'defines an optional beat for the gant_units (e.g. the unit should be granted every X seconds)';

comment on column IFW_DISCOUNTSTEP.GRANT_UOM is 'info about the unit of measurement, that is to be granted';

comment on column IFW_DISCOUNTSTEP.ROLLOVER_UNITS is 'defines the granted units, which can be rolled over to the following period (rollover is only allowed for linear forwarded discounts)';

comment on column IFW_DISCOUNTSTEP.ROLLOVER_MONTHS is 'number of months/periods rollover units are valid (0: valid forever)';

comment on column IFW_DISCOUNTSTEP.ROLLOVER_MAX is 'maximum value of rollover-units sum to be rolled over (has to be greater or equal rollover_units)';

comment on column IFW_DISCOUNTSTEP.ROLLOVER_PERIOD is '1 is use only the related EDR rollover period; 0 is EDR period does not matter';

comment on column IFW_DISCOUNTSTEP.RESOURCE_ID is 'Infranets resource-id';

comment on column IFW_DISCOUNTSTEP.EDR_ENRICHMENT is 'boolean defines if the EDRs should be enriched by the discount PlugIn (0=FALSE=reverse discounting, 1=TRUE=foreward discounting)';

comment on column IFW_DISCOUNTSTEP.ENTRYBY is 'ENTRYBY';

comment on column IFW_DISCOUNTSTEP.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_DISCOUNTSTEP.MODIFBY is 'MODIFBY';

comment on column IFW_DISCOUNTSTEP.MODIFDATE is 'MODIFDATE';

comment on column IFW_DISCOUNTSTEP.MODIFIED is 'MODIFIED';

comment on column IFW_DISCOUNTSTEP.RECVER is 'RECVER';

create unique index AK_IFW_DCS on IFW_DISCOUNTSTEP (DISCOUNTRULE asc, RANK asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_2_IDX
storage
(
initial 32K
next 32K
minextents 1
maxextents unlimited
pctincrease 0
);

insert into IFW_DISCOUNTSTEP
(DISCOUNTSTEP,DISCOUNTRULE,RANK,DISCOUNTMASTER,THRESHOLD_TYPE,THRESHOLD_FROM,THRESHOLD_TO,DISCOUNT_TYPE,GRANT_TYPE,GRANT_PRORATEDBEAT,GRANT_UNITS,GRANT_BEAT,GRANT_UOM,ROLLOVER_UNITS,ROLLOVER_MONTHS,ROLLOVER_MAX,ROLLOVER_PERIOD,RESOURCE_ID,EDR_ENRICHMENT,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER)
select DISCOUNTSTEP,DISCOUNTRULE,RANK,DISCOUNTMASTER,THRESHOLD_TYPE,THRESHOLD_FROM,THRESHOLD_TO,DISCOUNT_TYPE,GRANT_TYPE,GRANT_PRORATEDBEAT,GRANT_UNITS,GRANT_BEAT,GRANT_UOM,ROLLOVER_UNITS,ROLLOVER_MONTHS,ROLLOVER_MAX,ROLLOVER_EDR_PERIOD,RESOURCE_ID,EDR_ENRICHMENT,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER
from TMP_DISCOUNTSTEP;

-- IFW_NETWORKOPERATOR   -> IFW_NETWORKOPER
drop index AK_IFW_NOP;

alter table ifw_networkoperator drop constraint CKC_NOP_NOTYPE;

alter table ifw_networkoperator drop constraint CKC_NOP_MODIFIED;

alter table ifw_networkoperator drop primary key;

rename ifw_networkoperator to tmp_networkoperator;

create table IFW_NETWORKOPER
(
    NO                  NUMBER(9)              not null,
    CODE                VARCHAR2(10)           not null,
    NAME                VARCHAR2(255)          null    ,
    NOTYPE              CHAR(1)                default 'I' not null
        constraint CKC_NOP_NOTYPE check (NOTYPE in ('I','S','R','O','X')),
    CAC                 VARCHAR2(6)            null    ,
    CIC                 VARCHAR2(5)            null    ,
    PLMN_ID             NUMBER(7)              null    ,
    TADIG               VARCHAR2(5)            null    ,
    CURRENCY            VARCHAR2(3)            not null,
    TAXGROUP            VARCHAR2(5)            not null,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_NOP_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_NOP primary key (NO)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_IDX
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
tablespace INTEGRATE_TS_2_DAT;

grant select, insert, update, delete on IFW_NETWORKOPER to INTEGRATE_ROLE_ALL;

grant select on IFW_NETWORKOPER to INTEGRATE_ROLE_SEL;

comment on table IFW_NETWORKOPER is 'defined all valid network operators (either carrier, reseller or service-provider or virtual references)';

comment on column IFW_NETWORKOPER.NO is 'internal ID';

comment on column IFW_NETWORKOPER.CODE is 'the code for the network operator';

comment on column IFW_NETWORKOPER.NAME is 'name of the network operator';

comment on column IFW_NETWORKOPER.NOTYPE is 'type of no (I=interconnection partner, S=service-provider partner, R=reseller partner, O=Offline Billing NO, X=myself)';

comment on column IFW_NETWORKOPER.CAC is 'carrier access code (e.g. 10042)';

comment on column IFW_NETWORKOPER.CIC is 'carrier identification code (e.g. a ported Dxxx code for the network operator)';

comment on column IFW_NETWORKOPER.PLMN_ID is 'public land mobile network code';

comment on column IFW_NETWORKOPER.TADIG is 'tadig name for the operator';

comment on column IFW_NETWORKOPER.CURRENCY is 'defines the default BILLING currency for this operator (data exchange and billing has to be converted into this currency)';

comment on column IFW_NETWORKOPER.TAXGROUP is 'references a tax group which is associated with this network operator';

comment on column IFW_NETWORKOPER.ENTRYBY is 'ENTRYBY';

comment on column IFW_NETWORKOPER.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_NETWORKOPER.MODIFBY is 'MODIFBY';

comment on column IFW_NETWORKOPER.MODIFDATE is 'MODIFDATE';

comment on column IFW_NETWORKOPER.MODIFIED is 'MODIFIED';

comment on column IFW_NETWORKOPER.RECVER is 'RECVER';

create unique index AK_IFW_NOP on IFW_NETWORKOPER (CODE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_2_IDX
storage
(
initial 32K
next 32K
minextents 1
maxextents unlimited
pctincrease 0
);

insert into IFW_NETWORKOPER
(NO,CODE,NAME,NOTYPE,CAC,CIC,PLMN_ID,TADIG,CURRENCY,TAXGROUP,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER)
select NO,CODE,NAME,NOTYPE,CAC,CIC,PLMN_ID,TADIG,CURRENCY,TAXGROUP,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER
from TMP_NETWORKOPERATOR;

-- IFW_ICPRODUCT_GROUP   -> IFW_ICPRODUCT_GRP
alter table ifw_icproduct_group drop constraint CKC_IPG_MODIFIED;

alter table ifw_icproduct_group drop primary key;

rename IFW_ICPRODUCT_GROUP to TMP_ICPRODUCT_GROUP;

create table IFW_ICPRODUCT_GRP
(
    NETWORKMODEL        NUMBER(9)              not null,
    ICPRODUCT_GROUP     VARCHAR2(10)           not null,
    NAME                VARCHAR2(255)          null    ,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_IPG_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_IPG primary key (NETWORKMODEL, ICPRODUCT_GROUP)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_IDX
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
tablespace INTEGRATE_TS_2_DAT;

grant select, insert, update, delete on IFW_ICPRODUCT_GRP to INTEGRATE_ROLE_ALL;

grant select on IFW_ICPRODUCT_GRP to INTEGRATE_ROLE_SEL;

comment on table IFW_ICPRODUCT_GRP is 'defines possible ic product groups';

comment on column IFW_ICPRODUCT_GRP.NETWORKMODEL is 'uniquely identifies a related network model';

comment on column IFW_ICPRODUCT_GRP.ICPRODUCT_GROUP is 'defines a unique ic product group';

comment on column IFW_ICPRODUCT_GRP.NAME is 'name or description';

comment on column IFW_ICPRODUCT_GRP.ENTRYBY is 'ENTRYBY';

comment on column IFW_ICPRODUCT_GRP.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_ICPRODUCT_GRP.MODIFBY is 'MODIFBY';

comment on column IFW_ICPRODUCT_GRP.MODIFDATE is 'MODIFDATE';

comment on column IFW_ICPRODUCT_GRP.MODIFIED is 'MODIFIED';

comment on column IFW_ICPRODUCT_GRP.RECVER is 'RECVER';

insert into IFW_ICPRODUCT_GRP
(NETWORKMODEL,ICPRODUCT_GROUP,NAME,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER)
select NETWORKMODEL,ICPRODUCT_GROUP,NAME,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER
from TMP_ICPRODUCT_GROUP;

-- IFW_NETWORKMODEL.USE_SWITCH_FOR_IDENT      -> USE_SWITCH
alter table ifw_networkmodel drop constraint CKC_NWM_CALCMODE;

alter table ifw_networkmodel drop constraint CKC_NWM_MODELTYPE;

alter table ifw_networkmodel drop constraint CKC_NWM_USE_SWITCH;

alter table ifw_networkmodel drop constraint CKC_NWM_USE_FIX;

alter table ifw_networkmodel drop constraint CKC_NWM_MODIFIED;

alter table ifw_networkmodel drop primary key;

rename ifw_networkmodel to tmp_networkmodel;

create table IFW_NETWORKMODEL
(
    NETWORKMODEL        NUMBER(9)              not null,
    CODE                VARCHAR2(10)           not null,
    NAME                VARCHAR2(255)          null    ,
    CALCMODE            CHAR(1)                default '3' not null
        constraint CKC_NWM_CALCMODE check (CALCMODE in ('1','2','3','4','5','6')),
    MODELTYPE           CHAR(1)                default 'C' not null
        constraint CKC_NWM_MODELTYPE check (MODELTYPE in ('C','R','O')),
    USE_SWITCH          NUMBER(1)              default 0 not null
        constraint CKC_NWM_USE_SWITCH check (USE_SWITCH in (0,1)),
    USE_FIXCOST         NUMBER(1)              default 0 not null
        constraint CKC_NWM_USE_FIX check (USE_FIXCOST in (0,1)),
    SYSTEM_BRAND        VARCHAR2(5)            null    ,
    RATEPLAN            NUMBER(9)              null    ,
    NO                  NUMBER(9)              not null,
    CURRENCY            VARCHAR2(3)            not null,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_NWM_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_NWM primary key (NETWORKMODEL)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_IDX
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
tablespace INTEGRATE_TS_2_DAT;

grant select, insert, update, delete on IFW_NETWORKMODEL to INTEGRATE_ROLE_ALL;

grant select on IFW_NETWORKMODEL to INTEGRATE_ROLE_SEL;

comment on table IFW_NETWORKMODEL is 'defines different networkmodels, a model defines a physical network layout with all pois';

comment on column IFW_NETWORKMODEL.NETWORKMODEL is 'unique internal model id';

comment on column IFW_NETWORKMODEL.CODE is 'just a name';

comment on column IFW_NETWORKMODEL.NAME is 'description';

comment on column IFW_NETWORKMODEL.CALCMODE is 'defines which trunks shall be used (1=in, 2=out, 3=in+out)';

comment on column IFW_NETWORKMODEL.MODELTYPE is 'the type of the model (C=Carrier-Interconnect, R=Reseller-Interconnect, 0=Reseller-Roaming)';

comment on column IFW_NETWORKMODEL.USE_SWITCH is 'if set to true, switch information is available and is used for product identification';

comment on column IFW_NETWORKMODEL.USE_FIXCOST is 'if set to true, network information is available and is used for product identification';

comment on column IFW_NETWORKMODEL.SYSTEM_BRAND is 'references a system/brand';

comment on column IFW_NETWORKMODEL.RATEPLAN is 'references the tariff model which should be used for (reseller or carrier) interconnection purpose';

comment on column IFW_NETWORKMODEL.NO is 'Operator who owns this network model within a multi network model configuration (has to be of NO_TYPE=X)';

comment on column IFW_NETWORKMODEL.CURRENCY is 'Defines the default HOME currency of this networkmodel';

comment on column IFW_NETWORKMODEL.ENTRYBY is 'ENTRYBY';

comment on column IFW_NETWORKMODEL.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_NETWORKMODEL.MODIFBY is 'MODIFBY';

comment on column IFW_NETWORKMODEL.MODIFDATE is 'MODIFDATE';

comment on column IFW_NETWORKMODEL.MODIFIED is 'MODIFIED';

comment on column IFW_NETWORKMODEL.RECVER is 'RECVER';

insert into ifw_networkmodel
(NETWORKMODEL,CODE,NAME,CALCMODE,MODELTYPE,USE_SWITCH,USE_FIXCOST,SYSTEM_BRAND,RATEPLAN,NO,CURRENCY,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER)
select NETWORKMODEL,CODE,NAME,CALCMODE,MODELTYPE,USE_SWITCH_FOR_IDENT,USE_FIXCOST,SYSTEM_BRAND,RATEPLAN,NO,CURRENCY,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER
from tmp_networkmodel;

-- IFW_DESTINATIONDESC   -> IFW_DESTINDESC
alter table ifw_destinationdesc drop constraint CKC_DDC_TYPE;

alter table ifw_destinationdesc drop primary key;

rename ifw_destinationdesc to tmp_destinationdesc;

create table IFW_DESTINDESC
(
    AREACODE            VARCHAR2(40)           not null,
    TYPE                CHAR(1)                default 'S' not null
        constraint CKC_DDC_TYPE check (TYPE in ('N','I','S')),
    NAME                VARCHAR2(255)          null    ,
    constraint PK_IFW_DDC primary key (AREACODE)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_1_IDX
        storage
        (
        initial 256K
        next 256K
        minextents 1
        maxextents unlimited
        pctincrease 0
     )
)
pctfree 10
pctused 70
initrans 2
storage
(
initial 1024K
next 1024K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_1_DAT;

grant select, insert, update, delete on IFW_DESTINDESC to INTEGRATE_ROLE_ALL;

grant select on IFW_DESTINDESC to INTEGRATE_ROLE_SEL;

comment on table IFW_DESTINDESC is 'destination description definition, gives an areacode a name';

comment on column IFW_DESTINDESC.AREACODE is 'specifies the area code the description is valid for';

comment on column IFW_DESTINDESC.TYPE is 'type of the areacode, could be N=national, I=international, S=special';

comment on column IFW_DESTINDESC.NAME is 'description for this areacode';

insert into ifw_destindesc
(AREACODE,TYPE,NAME)
select AREACODE,TYPE,NAME
from tmp_destinationdesc;

-- IFW_PRICEMODEL_STEP   -> IFW_PRICEMDL_STEP
alter table ifw_pricemodel_step drop constraint CKC_PMS_BASE;

alter table ifw_pricemodel_step drop constraint CKC_PMS_MODIFIED;

alter table ifw_pricemodel_step drop primary key;

rename ifw_pricemodel_step to tmp_pricemodel_step;

create table IFW_PRICEMDL_STEP
(
    PRICEMODEL          NUMBER(9)              not null,
    VALID_FROM          DATE                   default sysdate not null,
    RESOURCE_NAME       VARCHAR2(10)           not null,
    RUM                 VARCHAR2(10)           not null,
    STEP                NUMBER(9)              not null,
    THRESHOLD_FROM      NUMBER(15)             not null,
    THRESHOLD_TO        NUMBER(15)             null    ,
    BEAT                NUMBER                 not null,
    CHARGE              NUMBER                 not null,
    CHARGE_BASE         NUMBER(9)              default 1 not null
        constraint CKC_PMS_BASE check (CHARGE_BASE >= 1),
    FRAME               NUMBER(9)              default 0 not null,
    GLACCOUNT           VARCHAR2(10)           not null,
    REVENUEGROUP        VARCHAR2(5)            null    ,
    MINIMUM_CHARGE      NUMBER                 null    ,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_PMS_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_PMS primary key (PRICEMODEL, VALID_FROM, RESOURCE_NAME, RUM, STEP)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_4_IDX
        storage
        (
        initial 256K
        next 256K
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
initial 1024K
next 1024K
minextents 1
maxextents unlimited
pctincrease 0
buffer_pool keep
)
tablespace INTEGRATE_TS_4_DAT;

grant select, insert, update, delete on IFW_PRICEMDL_STEP to INTEGRATE_ROLE_ALL;

grant select on IFW_PRICEMDL_STEP to INTEGRATE_ROLE_SEL;

comment on table IFW_PRICEMDL_STEP is 'price model rating steps (duration based price calculation)';

comment on column IFW_PRICEMDL_STEP.PRICEMODEL is 'reference to the price model these rating steps are related to';

comment on column IFW_PRICEMDL_STEP.VALID_FROM is 'VALID_FROM';

comment on column IFW_PRICEMDL_STEP.RESOURCE_NAME is 'defines the RESOURCE the pricemodel steps are related to';

comment on column IFW_PRICEMDL_STEP.RUM is 'defines the RUM the pricemodel steps are related to';

comment on column IFW_PRICEMDL_STEP.STEP is 'step id';

comment on column IFW_PRICEMDL_STEP.THRESHOLD_FROM is 'lower boundary in UoM of the related servicecode (compare: >=), negative values allowed';

comment on column IFW_PRICEMDL_STEP.THRESHOLD_TO is 'upper boundary in UoM of the related servicecode (compare: <)';

comment on column IFW_PRICEMDL_STEP.BEAT is 'beat in seconds (fractions allowed) for this threshold';

comment on column IFW_PRICEMDL_STEP.CHARGE is 'charge for this beat within this threshold (charge without decimals)';

comment on column IFW_PRICEMDL_STEP.CHARGE_BASE is 'defines a charge base (e.g. a value of 60 means, that the charge value is base on 60 units, e.g. a minute)';

comment on column IFW_PRICEMDL_STEP.FRAME is 'frame id (used to group steps for splitting to find linear entries which can be split)';

comment on column IFW_PRICEMDL_STEP.GLACCOUNT is 'references a specific usage based general ledger account code for this configuration entry';

comment on column IFW_PRICEMDL_STEP.REVENUEGROUP is 'references a usage group (for splitted billing purposes)';

comment on column IFW_PRICEMDL_STEP.MINIMUM_CHARGE is 'Define Minimum Charge per Call per Resource.';

comment on column IFW_PRICEMDL_STEP.ENTRYBY is 'ENTRYBY';

comment on column IFW_PRICEMDL_STEP.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_PRICEMDL_STEP.MODIFBY is 'MODIFBY';

comment on column IFW_PRICEMDL_STEP.MODIFDATE is 'MODIFDATE';

comment on column IFW_PRICEMDL_STEP.MODIFIED is 'MODIFIED';

comment on column IFW_PRICEMDL_STEP.RECVER is 'RECVER';

insert into ifw_pricemdl_step
(PRICEMODEL,VALID_FROM,RESOURCE_NAME,RUM,STEP,THRESHOLD_FROM,THRESHOLD_TO,BEAT,CHARGE,CHARGE_BASE,FRAME,GLACCOUNT,REVENUEGROUP,MINIMUM_CHARGE,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER)
select PRICEMODEL,VALID_FROM,RESOURCE_NAME,RUM,STEP,THRESHOLD_FROM,THRESHOLD_TO,BEAT,CHARGE,CHARGE_BASE,FRAME,GLACCOUNT,REVENUEGROUP,MINIMUM_CHARGE,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER
from tmp_pricemodel_step;

-- IFW_GEOGRAPHICAL_ZONE -> IFW_GEO_ZONE
alter table ifw_geographical_zone drop primary key;

rename ifw_geographical_zone to tmp_geographical_zone;

create table IFW_GEO_ZONE
(
    ZONEMODEL           NUMBER(9)              not null,
    DISTANCE            NUMBER                 not null,
    SERVICECODE         VARCHAR2(5)            not null,
    VALID_FROM          DATE                   not null,
    VALID_TO            DATE                   null    ,
    ZONE_WS             VARCHAR2(10)           not null,
    ZONE_RT             VARCHAR2(10)           not null,
    NAME                VARCHAR2(255)          null    ,
    ALT_ZONEMODEL       NUMBER(9)              null    ,
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_GOZ primary key (ZONEMODEL, DISTANCE, SERVICECODE, VALID_FROM)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_3_IDX
        storage
        (
        initial 256K
        next 256K
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
initial 1024K
next 1024K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_3_DAT;

grant select, insert, update, delete on IFW_GEO_ZONE to INTEGRATE_ROLE_ALL;

grant select on IFW_GEO_ZONE to INTEGRATE_ROLE_SEL;

comment on table IFW_GEO_ZONE is 'geographical distance translation table (translates a distance into a zone value)';

comment on column IFW_GEO_ZONE.ZONEMODEL is 'internal ID (references to the related zone model)';

comment on column IFW_GEO_ZONE.DISTANCE is 'the distance (upper boundary) which should be translated';

comment on column IFW_GEO_ZONE.SERVICECODE is 'Service code this entry is valid for';

comment on column IFW_GEO_ZONE.VALID_FROM is 'defines the date from when on this entry is valid';

comment on column IFW_GEO_ZONE.VALID_TO is 'defines the date till when this entry is valid';

comment on column IFW_GEO_ZONE.ZONE_WS is 'reference pointer to the zone value definition table (wholesales)';

comment on column IFW_GEO_ZONE.ZONE_RT is 'reference pointer to the zone value definition table (retail)';

comment on column IFW_GEO_ZONE.NAME is 'description of the zone entry';

comment on column IFW_GEO_ZONE.ALT_ZONEMODEL is 'Optional reference to an alternative zonemodel';

comment on column IFW_GEO_ZONE.RECVER is 'RECVER';

insert into ifw_geo_zone
(ZONEMODEL,DISTANCE,SERVICECODE,VALID_FROM,VALID_TO,ZONE_WS,ZONE_RT,NAME,ALT_ZONEMODEL,RECVER)
select ZONEMODEL,DISTANCE,SERVICECODE,VALID_FROM,VALID_TO,ZONE_WS,ZONE_RT,NAME,ALT_ZONEMODEL,RECVER
from tmp_geographical_zone;

-- IFW_GEOGRAPHICALMODEL -> IFW_GEO_MODEL
drop index AK_IFW_GMD;

alter table IFW_GEOGRAPHICALMODEL drop constraint CKC_GMD_STATUS;

alter table IFW_GEOGRAPHICALMODEL drop constraint CKC_GMD_MODIFIED;

alter table IFW_GEOGRAPHICALMODEL drop primary key;

rename ifw_geographicalmodel to tmp_geographicalmodel;

create table IFW_GEO_MODEL
(
    GEOMODEL            NUMBER(9)              not null,
    CODE                VARCHAR2(10)           not null,
    NAME                VARCHAR2(255)          null    ,
    STATUS              CHAR(1)                default 'A' not null
        constraint CKC_GMD_STATUS check (STATUS in ('A','D')),
    RULESET             VARCHAR2(10)           null    ,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_GMD_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_GMD primary key (GEOMODEL)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_3_IDX
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
tablespace INTEGRATE_TS_3_DAT
storage
(
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
);

grant select, insert, update, delete on IFW_GEO_MODEL to INTEGRATE_ROLE_ALL;

grant select on IFW_GEO_MODEL to INTEGRATE_ROLE_SEL;

comment on table IFW_GEO_MODEL is 'geographical model definition';

comment on column IFW_GEO_MODEL.GEOMODEL is 'internal id, defines the geographical model id';

comment on column IFW_GEO_MODEL.CODE is 'a short name to display in Smacc';

comment on column IFW_GEO_MODEL.NAME is 'description';

comment on column IFW_GEO_MODEL.STATUS is 'status of the model (A=active, D=deactive)';

comment on column IFW_GEO_MODEL.RULESET is 'Ruleset to map LERG-Info and calculated distance to new impact category.';

comment on column IFW_GEO_MODEL.ENTRYBY is 'ENTRYBY';

comment on column IFW_GEO_MODEL.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_GEO_MODEL.MODIFBY is 'MODIFBY';

comment on column IFW_GEO_MODEL.MODIFDATE is 'MODIFDATE';

comment on column IFW_GEO_MODEL.MODIFIED is 'MODIFIED';

comment on column IFW_GEO_MODEL.RECVER is 'RECVER';

create unique index AK_IFW_GMD on IFW_GEO_MODEL (CODE asc)
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
);

insert into ifw_geo_model
(GEOMODEL,CODE,NAME,STATUS,RULESET,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER)
select GEOMODEL,CODE,NAME,STATUS,RULESET,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER
from tmp_geographicalmodel;

-- IFW_GEOAREACODE_LNK   -> IFW_GEOAREA_LNK
alter table ifw_geoareacode_lnk drop primary key;

rename ifw_geoareacode_lnk to tmp_geoareacode_lnk;

create table IFW_GEOAREA_LNK
(
    GEOMODEL            NUMBER(9)              not null,
    AREACODE            VARCHAR2(40)           not null,
    VALID_FROM          DATE                   not null,
    VALID_TO            DATE                   null    ,
    NAME                VARCHAR2(255)          null    ,
    LONGITUDE           NUMBER                 null    ,
    LATITUDE            NUMBER                 null    ,
    constraint PK_IFW_GAL primary key (GEOMODEL, AREACODE, VALID_FROM)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_3_IDX
        storage
        (
        initial 256K
        next 256K
        minextents 1
        maxextents unlimited
        pctincrease 0
     )
)
pctfree 10
pctused 70
initrans 2
storage
(
initial 1024K
next 1024K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_3_DAT;

grant select, insert, update, delete on IFW_GEOAREA_LNK to INTEGRATE_ROLE_ALL;

grant select on IFW_GEOAREA_LNK to INTEGRATE_ROLE_SEL;

comment on table IFW_GEOAREA_LNK is 'link table, defines the geographical coordinates per virtual or physical areacode';

comment on column IFW_GEOAREA_LNK.GEOMODEL is 'Unique internal id';

comment on column IFW_GEOAREA_LNK.AREACODE is 'the area code the coordinates are valid for';

comment on column IFW_GEOAREA_LNK.VALID_FROM is 'Date this entry is valid from.';

comment on column IFW_GEOAREA_LNK.VALID_TO is 'Date this entry is valid till (just for info, may be {null})';

comment on column IFW_GEOAREA_LNK.NAME is 'description for the defined area code';

comment on column IFW_GEOAREA_LNK.LONGITUDE is 'north coordinates (vertical coordinates)';

comment on column IFW_GEOAREA_LNK.LATITUDE is 'east coordinates (horizontal coordinates)';

insert into ifw_geoarea_lnk
(GEOMODEL,AREACODE,VALID_FROM,VALID_TO,NAME,LONGITUDE,LATITUDE)
select GEOMODEL,AREACODE,VALID_FROM,VALID_TO,NAME,LONGITUDE,LATITUDE
from tmp_geoareacode_lnk;

-- IFW_IMPACT_CATEGORY   -> IFW_IMPACT_CAT
alter table IFW_IMPACT_CATEGORY drop constraint CKC_ICY_TYPE;

alter table IFW_IMPACT_CATEGORY drop constraint CKC_ICY_MODIFIED;

alter table IFW_IMPACT_CATEGORY drop primary key;

rename IFW_IMPACT_CATEGORY to TMP_IMPACT_CATEGORY;

create table IFW_IMPACT_CAT
(
    IMPACT_CATEGORY     VARCHAR2(10)           not null,
    RESULT              VARCHAR2(10)           not null,
    TYPE                NUMBER(1)              default 0 not null
        constraint CKC_ICY_TYPE check (TYPE between 0 and 1),
    NAME                VARCHAR2(255)          null    ,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_ICY_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_ICY primary key (IMPACT_CATEGORY)
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

grant select, insert, update, delete on IFW_IMPACT_CAT to INTEGRATE_ROLE_ALL;

grant select on IFW_IMPACT_CAT to INTEGRATE_ROLE_SEL;

comment on table IFW_IMPACT_CAT is 'zone/impact-category codes (defines the zone values)';

comment on column IFW_IMPACT_CAT.IMPACT_CATEGORY is 'Impact category name';

comment on column IFW_IMPACT_CAT.RESULT is 'Result value of impact category (FCT_ZoneMap will overwrite IMPACT_CATEGORY with RESULT)';

comment on column IFW_IMPACT_CAT.TYPE is 'Identifies if this is only an ImpactCategory-Value: 1';

comment on column IFW_IMPACT_CAT.NAME is 'Name or description';

comment on column IFW_IMPACT_CAT.ENTRYBY is 'ENTRYBY';

comment on column IFW_IMPACT_CAT.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_IMPACT_CAT.MODIFBY is 'MODIFBY';

comment on column IFW_IMPACT_CAT.MODIFDATE is 'MODIFDATE';

comment on column IFW_IMPACT_CAT.MODIFIED is 'MODIFIED';

comment on column IFW_IMPACT_CAT.RECVER is 'RECVER';

insert into ifw_impact_cat
(IMPACT_CATEGORY,RESULT,TYPE,NAME,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER)
select IMPACT_CATEGORY,RESULT,TYPE,NAME,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER
from tmp_impact_category;

create or replace view IFW_ZONE as
select IFW_IMPACT_CAT.IMPACT_CATEGORY ZONE, IFW_IMPACT_CAT.RESULT, IFW_IMPACT_CAT.NAME
from IFW_IMPACT_CAT
where IFW_IMPACT_CAT.TYPE = 0
with check option;

comment on table IFW_ZONE is 'IFW_ZONE';

-- IFW_USAGESCENARIO_MAP -> IFW_USC_MAP
alter table IFW_USAGESCENARIO_MAP drop constraint CKC_USM_MODIFIED;

alter table IFW_USAGESCENARIO_MAP drop primary key;

rename IFW_USAGESCENARIO_MAP to TMP_USAGESCENARIO_MAP;

create table IFW_USC_MAP
(
    USC_GROUP           VARCHAR2(10)           not null,
    ZONEMODEL           NUMBER(9)              not null,
    RANK                NUMBER(9)              not null,
    VALID_FROM          VARCHAR2(8)            not null,
    VALID_TO            VARCHAR2(8)            null    ,
    TIME_FROM           VARCHAR2(5)            null    ,
    TIME_TO             VARCHAR2(5)            null    ,
    QUANTITY_VALUE      NUMBER(9)              null    ,
    MIN_WS_AMOUNT       NUMBER                 null    ,
    MAX_WS_AMOUNT       NUMBER                 null    ,
    USAGECLASS          VARCHAR2(2000)         default '.*' not null,
    USAGETYPE           VARCHAR2(2000)         default '.*' not null,
    SERVICECODE         VARCHAR2(2000)         default '.*' not null,
    SERVICECLASS        VARCHAR2(2000)         default '.*' not null,
    ZONE_WS             VARCHAR2(2000)         default '.*' not null,
    ZONE_RT             VARCHAR2(2000)         default '.*' not null,
    NEW_USAGETYPE       VARCHAR2(5)            null    ,
    IMPACT_CATEGORY_WS  VARCHAR2(10)           null    ,
    IMPACT_CATEGORY_RT  VARCHAR2(10)           null    ,
    NAME                VARCHAR2(255)          null    ,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_USM_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_USM primary key (USC_GROUP, ZONEMODEL, RANK)
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
pctfree 20
pctused 70
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

grant select, insert, update, delete on IFW_USC_MAP to INTEGRATE_ROLE_ALL;

grant select on IFW_USC_MAP to INTEGRATE_ROLE_SEL;

comment on table IFW_USC_MAP is 'mapping table for callclass/calltype/zone to new calltype, impact category';

comment on column IFW_USC_MAP.USC_GROUP is 'references the mapping group the configuration is bound to';

comment on column IFW_USC_MAP.ZONEMODEL is 'reference to the zone model, this mapping is related to';

comment on column IFW_USC_MAP.RANK is 'defines the mapping order for the single entries';

comment on column IFW_USC_MAP.VALID_FROM is 'this mapping entry is valid from (Format: YYYYMMDD or MON-SUN[HH:SS]) (compare: >=)';

comment on column IFW_USC_MAP.VALID_TO is 'defines the date till when this entry is valid (Format: YYYYMMDD or MON-SUN[HH:SS]) (compare: <)';

comment on column IFW_USC_MAP.TIME_FROM is 'optional time, within the given valid_date, when the mapping should take place (Format: HH:SS) (compare: >=)';

comment on column IFW_USC_MAP.TIME_TO is 'optional time, within the given valid_date, when the mapping should take place (Format: HH:SS) (compare: <)';

comment on column IFW_USC_MAP.QUANTITY_VALUE is 'optional Quantity-Value (e.g. Duration), the mapping only takes place, if the cdr-value is smaller or equal';

comment on column IFW_USC_MAP.MIN_WS_AMOUNT is 'optional minimal Wholesale-Amount-Value (e.g. Wholesale-Charge), the mapping only takes place, if the cdr-value is greater or equal';

comment on column IFW_USC_MAP.MAX_WS_AMOUNT is 'optional maximal Wholesale-Amount-Value (e.g. Wholesale-Charge), the mapping only takes place, if the cdr-value is smaller or equal';

comment on column IFW_USC_MAP.USAGECLASS is 'condition: the usage class which should be mapped (regular expression, default: ''.*'')';

comment on column IFW_USC_MAP.USAGETYPE is 'condition: the usage type which should be mapped (regular expression, default: ''.*'')';

comment on column IFW_USC_MAP.SERVICECODE is 'condition: the servicecode which should be mapped (regular expression, default: ''.*'')';

comment on column IFW_USC_MAP.SERVICECLASS is 'condition: the serviceclass which should be mapped (regular expression, default: ''.*'')';

comment on column IFW_USC_MAP.ZONE_WS is 'condition: the wholesale zone which should be mapped (regular expression, default: ''.*'')';

comment on column IFW_USC_MAP.ZONE_RT is 'condition: the retail zone which should be mapped (regular expression, default: ''.*'')';

comment on column IFW_USC_MAP.NEW_USAGETYPE is 'result: returns the new usage type (if empty nothing changes)';

comment on column IFW_USC_MAP.IMPACT_CATEGORY_WS is 'result: returns the wholesale impact category (if empty nothing changes)';

comment on column IFW_USC_MAP.IMPACT_CATEGORY_RT is 'result: returns the retail impact category (if empty nothing changes)';

comment on column IFW_USC_MAP.NAME is 'Name or description';

comment on column IFW_USC_MAP.ENTRYBY is 'ENTRYBY';

comment on column IFW_USC_MAP.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_USC_MAP.MODIFBY is 'MODIFBY';

comment on column IFW_USC_MAP.MODIFDATE is 'MODIFDATE';

comment on column IFW_USC_MAP.MODIFIED is 'MODIFIED';

comment on column IFW_USC_MAP.RECVER is 'RECVER';

insert into ifw_usc_map
(USC_GROUP,ZONEMODEL,RANK,VALID_FROM,VALID_TO,TIME_FROM,TIME_TO,QUANTITY_VALUE,MIN_WS_AMOUNT,MAX_WS_AMOUNT,USAGECLASS,USAGETYPE,SERVICECODE,SERVICECLASS,ZONE_WS,ZONE_RT,NEW_USAGETYPE,IMPACT_CATEGORY_WS,IMPACT_CATEGORY_RT,NAME,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER)
select USC_GROUP,ZONEMODEL,RANK,VALID_FROM,VALID_TO,TIME_FROM,TIME_TO,QUANTITY_VALUE,MIN_WS_AMOUNT,MAX_WS_AMOUNT,USAGECLASS,USAGETYPE,SERVICECODE,SERVICECLASS,ZONE_WS,ZONE_RT,NEW_USAGETYPE,IMPACT_CATEGORY_WS,IMPACT_CATEGORY_RT,NAME,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER
from tmp_usagescenario_map;

-- IFW_RATESERVICE_MAP   -> IFW_RSC_MAP
alter table IFW_RATESERVICE_MAP drop constraint CKC_RSM_MODIFIED;

alter table IFW_RATESERVICE_MAP drop primary key;

rename IFW_RATESERVICE_MAP to TMP_RATESERVICE_MAP;

create table IFW_RSC_MAP
(
    RSC_GROUP           VARCHAR2(10)           not null,
    RANK                NUMBER(9)              not null,
    VALID_FROM          VARCHAR2(8)            not null,
    VALID_TO            VARCHAR2(8)            null    ,
    RATEPLAN            VARCHAR2(2000)         default '.*' not null,
    QOS_REQUESTED       VARCHAR2(2000)         default '.*' not null,
    QOS_USED            VARCHAR2(2000)         default '.*' not null,
    USAGECLASS          VARCHAR2(2000)         default '.*' not null,
    USAGETYPE           VARCHAR2(2000)         default '.*' not null,
    SERVICECODE         VARCHAR2(2000)         default '.*' not null,
    SERVICECLASS        VARCHAR2(2000)         default '.*' not null,
    IMPACT_CATEGORY     VARCHAR2(2000)         default '.*' not null,
    NEW_SERVICECODE     VARCHAR2(5)            null    ,
    NEW_SERVICECLASS    VARCHAR2(5)            null    ,
    NAME                VARCHAR2(255)          null    ,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_RSM_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_RSM primary key (RSC_GROUP, RANK)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_4_IDX
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
tablespace INTEGRATE_TS_4_DAT;

grant select, insert, update, delete on IFW_RSC_MAP to INTEGRATE_ROLE_ALL;

grant select on IFW_RSC_MAP to INTEGRATE_ROLE_SEL;

comment on table IFW_RSC_MAP is 'defines all valid service codes and service class''s for a given tariffmodel';

comment on column IFW_RSC_MAP.RSC_GROUP is 'references the rsc mapping group code';

comment on column IFW_RSC_MAP.RANK is 'defines the sequence order in which the mapping will be performed';

comment on column IFW_RSC_MAP.VALID_FROM is 'this mapping entry is valid from (Format: YYYYMMDD or MON-SUN[HH:MM]) (compare: >=)';

comment on column IFW_RSC_MAP.VALID_TO is 'defines the date till when this entry is valid (Format: YYYYMMDD or MON-SUN[HH:MM]) (compare: <)';

comment on column IFW_RSC_MAP.RATEPLAN is 'Condition: the rateplan which should be matched (regular expression, default ''.*'')';

comment on column IFW_RSC_MAP.QOS_REQUESTED is 'Condition: the QoS-Requested which should be matched (regular expression, default ''.*'')';

comment on column IFW_RSC_MAP.QOS_USED is 'Condition: the QoS-Used which should be matched (regular expression, default ''.*'')';

comment on column IFW_RSC_MAP.USAGECLASS is 'Condition: the Usage Class which should be matched (regular expression, default ''.*'')';

comment on column IFW_RSC_MAP.USAGETYPE is 'Condition: the Usage Type which should be matched (regular expression, default ''.*'')';

comment on column IFW_RSC_MAP.SERVICECODE is 'Condition: the Service Code which should be matched (regular expression, default ''.*'')';

comment on column IFW_RSC_MAP.SERVICECLASS is 'Condition: the serviceclass which should be mapped (regular expression, default ''.*'')';

comment on column IFW_RSC_MAP.IMPACT_CATEGORY is 'Condition: the Impact Category which should be matched (regular expression, default ''.*'')';

comment on column IFW_RSC_MAP.NEW_SERVICECODE is 'Result: the new Service Code (if empty nothing changes)';

comment on column IFW_RSC_MAP.NEW_SERVICECLASS is 'Result: the new Service Class (if empty nothing changes)';

comment on column IFW_RSC_MAP.NAME is 'Name or description';

comment on column IFW_RSC_MAP.ENTRYBY is 'ENTRYBY';

comment on column IFW_RSC_MAP.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_RSC_MAP.MODIFBY is 'MODIFBY';

comment on column IFW_RSC_MAP.MODIFDATE is 'MODIFDATE';

comment on column IFW_RSC_MAP.MODIFIED is 'MODIFIED';

comment on column IFW_RSC_MAP.RECVER is 'RECVER';

insert into IFW_RSC_MAP
(RSC_GROUP,RANK,VALID_FROM,VALID_TO,RATEPLAN,QOS_REQUESTED,QOS_USED,USAGECLASS,USAGETYPE,SERVICECODE,SERVICECLASS,IMPACT_CATEGORY,NEW_SERVICECODE,NEW_SERVICECLASS,NAME,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER)
select RSC_GROUP,RANK,VALID_FROM,VALID_TO,RATEPLAN,QOS_REQUESTED,QOS_USED,USAGECLASS,USAGETYPE,SERVICECODE,SERVICECLASS,IMPACT_CATEGORY,NEW_SERVICECODE,NEW_SERVICECLASS,NAME,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER
from TMP_RATESERVICE_MAP;

-- IFW_SERVICECODE_MAP   -> IFW_SERVICE_MAP
alter table IFW_SERVICECODE_MAP drop constraint CKC_SVM_MODIFIED;

alter table IFW_SERVICECODE_MAP drop primary key;

rename IFW_SERVICECODE_MAP to TMP_SERVICECODE_MAP;

create table IFW_SERVICE_MAP
(
    MAP_GROUP           VARCHAR2(10)           not null,
    RANK                NUMBER(9)              not null,
    NAME                VARCHAR2(255)          null    ,
    EXT_SERVICECODE     VARCHAR2(2000)         default '.*' not null,
    USAGECLASS          VARCHAR2(2000)         default '.*' not null,
    LOCARIND_VASEVENT   VARCHAR2(2000)         default '.*' not null,
    QOS_REQUESTED       VARCHAR2(2000)         default '.*' not null,
    QOS_USED            VARCHAR2(2000)         default '.*' not null,
    RECORDTYPE          VARCHAR2(2000)         default '.*' not null,
    INT_SERVICECODE     VARCHAR2(5)            not null,
    INT_SERVICECLASS    VARCHAR2(5)            null    ,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFBY             NUMBER(9)              null    ,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_SVM_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_SVM primary key (MAP_GROUP, RANK)
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
pctfree 20
pctused 70
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

grant select, insert, update, delete on IFW_SERVICE_MAP to INTEGRATE_ROLE_ALL;

grant select on IFW_SERVICE_MAP to INTEGRATE_ROLE_SEL;

comment on table IFW_SERVICE_MAP is 'service code mapping table, maps an external edr specific servicecode to an internal servicecode';

comment on column IFW_SERVICE_MAP.MAP_GROUP is 'reference to the logical map-group code, mapping is defined for that edr format';

comment on column IFW_SERVICE_MAP.RANK is 'defines the sequence order in which the mapping will be performed';

comment on column IFW_SERVICE_MAP.NAME is 'name or description of the edr specific servicecode';

comment on column IFW_SERVICE_MAP.EXT_SERVICECODE is 'external service code (used within the edr format) that should be mapped';

comment on column IFW_SERVICE_MAP.USAGECLASS is 'Condition: the usage class which should be matched (regular expression, default ''.*'')';

comment on column IFW_SERVICE_MAP.LOCARIND_VASEVENT is 'Condition: the location area indicator/vas-/event-code which should be matched (regular expression, default ''.*'')';

comment on column IFW_SERVICE_MAP.QOS_REQUESTED is 'Condition: the QoS requested which should be matched (regular expression, default ''.*'')';

comment on column IFW_SERVICE_MAP.QOS_USED is 'Condition: the QoS used which should be matched (regular expression, default ''.*'')';

comment on column IFW_SERVICE_MAP.RECORDTYPE is 'Condition: the record type which should be matched (regular expression, default ''.*'')';

comment on column IFW_SERVICE_MAP.INT_SERVICECODE is 'mapping value, unique generic service code which can be used';

comment on column IFW_SERVICE_MAP.INT_SERVICECLASS is 'mapping value, unique generic service class which can be used';

comment on column IFW_SERVICE_MAP.ENTRYBY is 'ENTRYBY';

comment on column IFW_SERVICE_MAP.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_SERVICE_MAP.MODIFBY is 'MODIFBY';

comment on column IFW_SERVICE_MAP.MODIFDATE is 'MODIFDATE';

comment on column IFW_SERVICE_MAP.MODIFIED is 'MODIFIED';

comment on column IFW_SERVICE_MAP.RECVER is 'RECVER';

insert into IFW_SERVICE_MAP
(MAP_GROUP,RANK,NAME,EXT_SERVICECODE,USAGECLASS,LOCARIND_VASEVENT,QOS_REQUESTED,QOS_USED,RECORDTYPE,INT_SERVICECODE,INT_SERVICECLASS,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER)
select MAP_GROUP,RANK,NAME,EXT_SERVICECODE,USAGECLASS,LOCARIND_VASEVENT,QOS_REQUESTED,QOS_USED,RECORDTYPE,INT_SERVICECODE,INT_SERVICECLASS,ENTRYBY,ENTRYDATE,MODIFBY,MODIFDATE,MODIFIED,RECVER
from TMP_SERVICECODE_MAP;

-- IFW_SEQLOG_IN.PROCESSEDBY_PIPELINE         -> PROCESSEDBY_PPL
alter table IFW_SEQLOG_IN drop constraint CKC_SLI_RECYCLING;

alter table IFW_SEQLOG_IN drop constraint CKC_SLI_STATUS;

alter table IFW_SEQLOG_IN drop primary key;

rename IFW_SEQLOG_IN to TMP_SEQLOG_IN;

create table IFW_SEQLOG_IN
(
    STREAMNAME          VARCHAR2(255)          not null,
    ORIG_SEQNO          NUMBER(9)              not null,
    RECYCLING           NUMBER(1)              default 0 not null
        constraint CKC_SLI_RECYCLING check (RECYCLING in (0,1)),
    PROCESSED           DATE                   null    ,
    STATUS              CHAR(1)                default 'O' not null
        constraint CKC_SLI_STATUS check (STATUS in ('O','W','R')),
    NUM_REC_IN          NUMBER(9)              null    ,
    NUM_REC_OUT         NUMBER(9)              null    ,
    NUM_REC_WARN        NUMBER(9)              null    ,
    DURATION            NUMBER(9)              null    ,
    PROCESSEDBY_PPL     VARCHAR2(50)           not null,
    SEQUENCE_NAME       VARCHAR2(50)           not null,
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

comment on column IFW_SEQLOG_IN.PROCESSEDBY_PPL is 'Name of the pipeline the stream has been processed by.';

comment on column IFW_SEQLOG_IN.SEQUENCE_NAME is 'Sequence name used to check input sequences.';

insert into IFW_SEQLOG_IN
(STREAMNAME,ORIG_SEQNO,RECYCLING,PROCESSED,STATUS,NUM_REC_IN,NUM_REC_WARN,NUM_REC_OUT,DURATION,PROCESSEDBY_PPL,SEQUENCE_NAME)
select STREAMNAME,ORIG_SEQNO,RECYCLING,PROCESSED,STATUS,NUM_REC_IN,NUM_REC_WARN,NUM_REC_OUT,DURATION,PROCESSEDBY_PIPELINE,SEQUENCE_NAME
from tmp_seqlog_in;

-- IFW_SEQLOG_OUT.PROCESSEDBY_PIPELINE        -> PROCESSEDBY_PPL
alter table IFW_SEQLOG_OUT drop constraint CKC_SLO_RECYCLING;

alter table IFW_SEQLOG_OUT drop primary key;

rename IFW_SEQLOG_OUT to TMP_SEQLOG_OUT;

create table IFW_SEQLOG_OUT
(
    STREAMNAME_IN       VARCHAR2(255)          not null,
    ORIG_SEQNO          NUMBER(9)              not null,
    RECYCLING           NUMBER(1)              default 0 not null
        constraint CKC_SLO_RECYCLING check (RECYCLING in (0,1)),
    SEQUENCE_NAME       VARCHAR2(50)           not null,
    NEW_SEQNO           NUMBER(9)              not null,
    PROCESSED           DATE                   null    ,
    NUM_REC_OUT         NUMBER(9)              null    ,
    SUM_QUANTITY        NUMBER                 null    ,
    SUM_RT_CHARGE       NUMBER                 null    ,
    SUM_WS_CHARGE       NUMBER                 null    ,
    STREAMNAME_OUT      VARCHAR2(255)          not null,
    PROCESSEDBY_PPL     VARCHAR2(50)           null    ,
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

comment on column IFW_SEQLOG_OUT.PROCESSEDBY_PPL is 'defines the pipeline which has processed the related stream (could be different from the orig-format in case of sequence sharring)';

insert into IFW_SEQLOG_OUT
(STREAMNAME_IN,ORIG_SEQNO,RECYCLING,SEQUENCE_NAME,NEW_SEQNO,PROCESSED,NUM_REC_OUT,SUM_QUANTITY,SUM_RT_CHARGE,SUM_WS_CHARGE,STREAMNAME_OUT,PROCESSEDBY_PPL)
select STREAMNAME_IN,ORIG_SEQNO,RECYCLING,SEQUENCE_NAME,NEW_SEQNO,PROCESSED,NUM_REC_OUT,SUM_QUANTITY,SUM_RT_CHARGE,SUM_WS_CHARGE,STREAMNAME_OUT,PROCESSEDBY_PIPELINE
from tmp_seqlog_out;

-- IFW_SCENARIO.DEFAULT_FIELD_DELIMITER       -> DEFAULT_FLD_DELIM
drop index IDX_IFW_SCN_NAME;

drop index AK_IFW_SCN_CODE;

drop index BIDX_IFW_SCN_STATE;

alter table IFW_SCENARIO drop constraint CKC_SCN_FLUSHMODE;

alter table IFW_SCENARIO drop constraint CKC_SCN_STATUS;

alter table IFW_SCENARIO drop constraint CKC_SCN_MODIFIED;

alter table IFW_SCENARIO drop primary key;

rename IFW_SCENARIO to TMP_SCENARIO;

create table IFW_SCENARIO
(
    SCENARIO_ID         NUMBER(9)              not null,
    CODE                VARCHAR2(10)           not null,
    NAME                VARCHAR2(255)          null    ,
    EDRC_DESC           VARCHAR2(50)           not null,
    DEFAULT_TAB_NAME    VARCHAR2(30)           default 'TAB_NAME' not null,
    DEFAULT_FLUSHMODE   NUMBER(1)              default 0 not null
        constraint CKC_SCN_FLUSHMODE check (DEFAULT_FLUSHMODE in (0,1,2,3)),
    DEFAULT_THRESHOLD   NUMBER(9)              default 100000 not null,
    DEFAULT_TEMP_DIR    VARCHAR2(254)          default '.' not null,
    DEFAULT_DONE_DIR    VARCHAR2(254)          default '.' not null,
    DEFAULT_CTL_DIR     VARCHAR2(254)          default '.' not null,
    DEFAULT_FLD_DELIM   CHAR(1)                default ';' not null,
    STATUS              CHAR(1)                default 'A' not null
        constraint CKC_SCN_STATUS check (STATUS in ('A','D')),
    ENTRYDATE           DATE                   default sysdate not null,
    ENTRYBY             NUMBER(9)              default 0 not null,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFBY             NUMBER(9)              null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_SCN_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_SCENARIO primary key (SCENARIO_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT;

grant select, insert, update, delete on IFW_SCENARIO to INTEGRATE_ROLE_ALL;

grant select on IFW_SCENARIO to INTEGRATE_ROLE_SEL;

comment on table IFW_SCENARIO is 'Defines aggregation scenarios';

comment on column IFW_SCENARIO.SCENARIO_ID is 'Internal ID => Generated by sequence ''AGG_SCENARIO_SEQ''';

comment on column IFW_SCENARIO.CODE is 'External Code. Could be used as Alternate Key';

comment on column IFW_SCENARIO.NAME is 'External Name / Description';

comment on column IFW_SCENARIO.EDRC_DESC is 'The EDR-C description to be used in scenario configuration';

comment on column IFW_SCENARIO.DEFAULT_TAB_NAME is 'Default Tablename defined for a scenario';

comment on column IFW_SCENARIO.DEFAULT_FLUSHMODE is 'Defines the flushing strategy for the FCT-aggregate';

comment on column IFW_SCENARIO.DEFAULT_THRESHOLD is 'Default threshold value which defines the max amount of internal entries for an aggregate scenario';

comment on column IFW_SCENARIO.DEFAULT_TEMP_DIR is 'Default Path for the temporary aggregation results';

comment on column IFW_SCENARIO.DEFAULT_DONE_DIR is 'Default Path for the aggregation results';

comment on column IFW_SCENARIO.DEFAULT_CTL_DIR is 'Default Path for Controlfiles';

comment on column IFW_SCENARIO.DEFAULT_FLD_DELIM is 'Default Fielddelimiter used to delimit the fields in aggregation results';

comment on column IFW_SCENARIO.STATUS is 'Flag which specifies whether the scenario is currently active ''A'' (will be used) or not ''D''.';

comment on column IFW_SCENARIO.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE';

comment on column IFW_SCENARIO.ENTRYBY is 'User-ID which should be set when a row is inserted.';

comment on column IFW_SCENARIO.MODIFDATE is 'DateTime Stamp should be set when a row is updated.';

comment on column IFW_SCENARIO.MODIFBY is 'User-ID which should be set when a row is updated.';

comment on column IFW_SCENARIO.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated';

comment on column IFW_SCENARIO.RECVER is 'Record Version of a row';

create index IDX_IFW_SCN_NAME on IFW_SCENARIO (NAME asc)
tablespace AGGREGATE_TS_1_IDX;

create unique index AK_IFW_SCN_CODE on IFW_SCENARIO (CODE asc)
tablespace AGGREGATE_TS_1_IDX;

create index BIDX_IFW_SCN_STATE on IFW_SCENARIO (STATUS asc)
tablespace AGGREGATE_TS_1_IDX;

insert into IFW_SCENARIO
(SCENARIO_ID,CODE,NAME,EDRC_DESC,DEFAULT_TAB_NAME,DEFAULT_FLUSHMODE,DEFAULT_THRESHOLD,DEFAULT_TEMP_DIR,DEFAULT_DONE_DIR,DEFAULT_CTL_DIR,DEFAULT_FLD_DELIM,STATUS,ENTRYDATE,ENTRYBY,MODIFDATE,MODIFBY,MODIFIED,RECVER)
select SCENARIO_ID,CODE,NAME,EDRC_DESC,DEFAULT_TAB_NAME,DEFAULT_FLUSHMODE,DEFAULT_THRESHOLD,DEFAULT_TEMP_DIR,DEFAULT_DONE_DIR,DEFAULT_CTL_DIR,DEFAULT_FIELD_DELIMITER,STATUS,ENTRYDATE,ENTRYBY,MODIFDATE,MODIFBY,MODIFIED,RECVER
from tmp_scenario;

-- IFW_AGGREGATION.AGGREGATION_FUNCTION       -> FUNCTION
drop index BIDX_IFW_AGG_STATE;

drop index BIDX_IFW_AGG_FCT;

drop index AK_IFW_AGG_SCN_COL;

alter table IFW_AGGREGATION drop constraint CKC_AGG_FUNCTION;

alter table IFW_AGGREGATION drop constraint CKC_AGG_STATUS;

alter table IFW_AGGREGATION drop constraint CKC_AGG_MODIFIED;

alter table IFW_AGGREGATION drop primary key;

rename IFW_AGGREGATION to TMP_AGGREGATION;

create table IFW_AGGREGATION
(
    AGGREGATION_ID      NUMBER(9)              not null,
    SCENARIO_ID         NUMBER(9)              not null,
    FIELD_ID            NUMBER(9)              not null,
    RANK                NUMBER(9)              not null,
    COL_NAME            VARCHAR2(30)           not null,
    PRECISION           NUMBER(9)              null    ,
    FUNCTION            CHAR(1)                not null
        constraint CKC_AGG_FUNCTION check (FUNCTION in ('C','S','Q','M','X')),
    STATUS              CHAR(1)                default 'A' not null
        constraint CKC_AGG_STATUS check (STATUS in ('A','D')),
    ENTRYDATE           DATE                   default sysdate not null,
    ENTRYBY             NUMBER(9)              default 0 not null,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFBY             NUMBER(9)              null    ,
    MODIFIED            NUMBER(1)              default 1 not null
        constraint CKC_AGG_MODIFIED check (MODIFIED in (0,1)),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_AGGREGATION primary key (AGGREGATION_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT;

grant select, insert, update, delete on IFW_AGGREGATION to INTEGRATE_ROLE_ALL;

grant select on IFW_AGGREGATION to INTEGRATE_ROLE_SEL;

comment on table IFW_AGGREGATION is 'This table holds all information about aggregation columns';

comment on column IFW_AGGREGATION.AGGREGATION_ID is 'Internal ID => Generated by sequence ''AGG_AGGREGATION_SEQ''';

comment on column IFW_AGGREGATION.SCENARIO_ID is 'Internal ID => Generated by sequence ''AGG_SCENARIO_SEQ''';

comment on column IFW_AGGREGATION.FIELD_ID is 'Internal ID => Generated by sequence ''IFW_FIELD_ID_SEQ''';

comment on column IFW_AGGREGATION.RANK is 'Internal ID to specify the position of an aggregation column through all defined aggregation columns in a scenario';

comment on column IFW_AGGREGATION.COL_NAME is 'Specifies the column name used by the aggregate process';

comment on column IFW_AGGREGATION.PRECISION is 'NULL for maximum precision';

comment on column IFW_AGGREGATION.FUNCTION is 'Specifies the function which will be used for the aggregation process: ''C''ount, ''S''um, S''Q''uareSum, ''M''inimum, Ma''X''imum';

comment on column IFW_AGGREGATION.STATUS is 'Boolean Flag which specifies whether the aggregation is currently active ''A'' (will be used) or not ''D''.';

comment on column IFW_AGGREGATION.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE';

comment on column IFW_AGGREGATION.ENTRYBY is 'User-ID which should be set when a row is inserted.';

comment on column IFW_AGGREGATION.MODIFDATE is 'DateTime Stamp should be set when a row is updated.';

comment on column IFW_AGGREGATION.MODIFBY is 'User-ID which should be set when a row is updated.';

comment on column IFW_AGGREGATION.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated';

comment on column IFW_AGGREGATION.RECVER is 'Record Version of a row';

create index BIDX_IFW_AGG_STATE on IFW_AGGREGATION (STATUS asc)
tablespace AGGREGATE_TS_1_IDX;

create index BIDX_IFW_AGG_FCT on IFW_AGGREGATION (FUNCTION asc)
tablespace AGGREGATE_TS_1_IDX;

create unique index AK_IFW_AGG_SCN_COL on IFW_AGGREGATION (SCENARIO_ID asc, FIELD_ID asc, RANK asc)
tablespace AGGREGATE_TS_1_IDX;

insert into IFW_AGGREGATION
(AGGREGATION_ID,SCENARIO_ID,FIELD_ID,RANK,COL_NAME,PRECISION,FUNCTION,STATUS,ENTRYDATE,ENTRYBY,MODIFDATE,MODIFBY,MODIFIED,RECVER)
select AGGREGATION_ID,SCENARIO_ID,FIELD_ID,RANK,COL_NAME,PRECISION,AGGREGATION_FUNCTION,STATUS,ENTRYDATE,ENTRYBY,MODIFDATE,MODIFBY,MODIFIED,RECVER
from tmp_aggregation;

-- IFW_CLASSCON.NODE_GROUPING_CNF_ID          -> NODE_GRPG_CNF_ID
-- IFW_CLASSCON.NEXT_GROUPING_CNF_ID          -> NEXT_GRPG_CNF_ID
drop index AK_IFW_CLC_NDE_NXT;

alter table IFW_CLASSCON drop primary key;

rename IFW_CLASSCON to TMP_CLASSCON;

create table IFW_CLASSCON
(
    CLASSCON_ID         NUMBER(9)              not null,
    NODE_GRPG_CNF_ID    NUMBER(9)              not null,
    NEXT_GRPG_CNF_ID    NUMBER(9)              not null,
    constraint PK_IFW_CLC primary key (CLASSCON_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT;

grant select, insert, update, delete on IFW_CLASSCON to INTEGRATE_ROLE_ALL;

grant select on IFW_CLASSCON to INTEGRATE_ROLE_SEL;

comment on table IFW_CLASSCON is 'Defines a conditional reference between used grouping classes';

comment on column IFW_CLASSCON.CLASSCON_ID is 'Internal ID => Generated by sequence ''AGG_CLASSCON_SEQ''';

comment on column IFW_CLASSCON.NODE_GRPG_CNF_ID is 'Node classgrouping configuration (Internal ID => Generated by sequence ''AGG_GROUPING_CNF_SEQ'')';

comment on column IFW_CLASSCON.NEXT_GRPG_CNF_ID is 'Next classgrouping configuration (Internal ID => Generated by sequence ''AGG_GROUPING_CNF_SEQ'')';

create unique index AK_IFW_CLC_NDE_NXT on IFW_CLASSCON (NODE_GRPG_CNF_ID asc, NEXT_GRPG_CNF_ID asc)
tablespace AGGREGATE_TS_1_IDX;

insert into ifw_classcon
(CLASSCON_ID,NODE_GRPG_CNF_ID,NEXT_GRPG_CNF_ID)
select CLASSCON_ID,NODE_GROUPING_CNF_ID,NEXT_GROUPING_CNF_ID
from tmp_classcon;

-- IFW_LERG_DATA.OTHER_LINE_RATE_STEP         -> OTHER_LINE_RS
alter table IFW_LERG_DATA drop constraint CKC_LERG_MODIFIED;

alter table ifw_lerg_data drop primary key;

rename IFW_LERG_DATA to TMP_LERG_DATA;

create table IFW_LERG_DATA
(
    GEOMODEL            NUMBER(9)              not null,
    AREACODE            VARCHAR2(40)           not null,
    VALID_FROM          DATE                   not null,
    VALID_TO            DATE                   null    ,
    LATA_SUBZONE        VARCHAR2(2)            null    ,
    LATA                VARCHAR2(3)            null    ,
    LATA_NAME           VARCHAR2(20)           null    ,
    IDDD_IND            CHAR(1)                null    ,
    TBPI                CHAR(1)                null    ,
    DIALABLE_IND        CHAR(1)                null    ,
    NPA_NONMEX          VARCHAR2(3)            null    ,
    NPA                 VARCHAR2(3)            null    ,
    NXX                 VARCHAR2(3)            null    ,
    NXX_TYPE            VARCHAR2(2)            null    ,
    PORTABLE_IND        CHAR(1)                null    ,
    SEND_TO_RAO         VARCHAR2(3)            null    ,
    OTHER_LINE_RS       VARCHAR2(2)            null    ,
    OCN                 VARCHAR2(4)            null    ,
    BILL_TO_RAO         VARCHAR2(3)            null    ,
    SPECIAL_RATING_IND  CHAR(1)                null    ,
    TIMEZONE            CHAR(1)                null    ,
    DSO_IND             CHAR(1)                null    ,
    STATE               VARCHAR2(2)            null    ,
    COMPANY_CODE        VARCHAR2(2)            null    ,
    COMPANY_TYPE        CHAR(1)                null    ,
    POINT_ID            CHAR(1)                null    ,
    SSC                 VARCHAR2(4)            null    ,
    TD_EO               VARCHAR2(2)            null    ,
    TD_AT               VARCHAR2(2)            null    ,
    AOCN                VARCHAR2(4)            null    ,
    LOC_NAME            VARCHAR2(10)           null    ,
    LOC_COUNTY          VARCHAR2(2)            null    ,
    RC_ABBREV           VARCHAR2(10)           null    ,
    RC_TYPE             CHAR(1)                null    ,
    SWITCH              VARCHAR2(11)           null    ,
    SHA_IND             VARCHAR2(2)            null    ,
    RANGE_OCN           VARCHAR2(4)            null    ,
    ENTRYBY             NUMBER(9)              default 0 not null,
    ENTRYDATE           DATE                   default sysdate not null,
    MODIFDATE           DATE                   default sysdate null    ,
    MODIFBY             NUMBER(9)              null    ,
    MODIFIED            NUMBER(1)              default 1 null    
        constraint CKC_LERG_MODIFIED check (MODIFIED is null or (MODIFIED in (0,1))),
    RECVER              NUMBER(9)              default 0 not null,
    constraint PK_IFW_LERG primary key (GEOMODEL, AREACODE, VALID_FROM)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_3_IDX
        storage
        (
        initial 256K
        next 256K
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
initial 1M
next 1M
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_3_DAT;

grant select, insert, update, delete on IFW_LERG_DATA to INTEGRATE_ROLE_ALL;

grant select on IFW_LERG_DATA to INTEGRATE_ROLE_SEL;

comment on table IFW_LERG_DATA is 'LERG data to be used for mapping.';

comment on column IFW_LERG_DATA.GEOMODEL is 'Geographical model this entry is related to';

comment on column IFW_LERG_DATA.AREACODE is 'IAC+CC+NPA+NXX';

comment on column IFW_LERG_DATA.VALID_FROM is 'Date this entry is valid from';

comment on column IFW_LERG_DATA.VALID_TO is 'Date this entry is valid to. May be {null}: valid to infinity';

comment on column IFW_LERG_DATA.LATA_SUBZONE is 'Finer LATA breakdown (Florida only) (2 numerics).';

comment on column IFW_LERG_DATA.LATA is 'Local Access Transport Area (3 numerics), may be 000 in certain cases.';

comment on column IFW_LERG_DATA.LATA_NAME is 'LATA_NAME';

comment on column IFW_LERG_DATA.IDDD_IND is '0 = indicates that International Direct Distance Dialing (IDDD) cannot originate from the NPA NXX.  1 = indicates it can.';

comment on column IFW_LERG_DATA.TBPI is 'Thousands Block Pooling Indicator';

comment on column IFW_LERG_DATA.DIALABLE_IND is '0 = indicates the NPA NXX cannot be directly dialed by a subscriber.  1 = indicates it can be directly dialed by a subscriber.';

comment on column IFW_LERG_DATA.NPA_NONMEX is 'Actual NPA for Non-Mexican "Other Place"';

comment on column IFW_LERG_DATA.NPA is 'Numbering Plan Area (Area Code)';

comment on column IFW_LERG_DATA.NXX is 'NXX (N=2-9, X=0-9) (also called exchange, prefix and Central Office (CO) Code).  Note that NXXTYPEs 14 will have N=0,1 and NXXTYPE 17 will have N=0-9.';

comment on column IFW_LERG_DATA.NXX_TYPE is 'Provides information on how the NXX is being used.';

comment on column IFW_LERG_DATA.PORTABLE_IND is 'TPM Master, Activity, and Minor VH files only.  0 = Lines in the NXX have not been designated to be "portable" to another company.  1 = The NXX has been identified as one which other companies can "port" numbers from - a 1 however does not necessarily me';

comment on column IFW_LERG_DATA.SEND_TO_RAO is 'The Revenue Accounting Office to which the Centralized Message Distribution System (CMDS) will "send" data.  See "Bill to RAO".';

comment on column IFW_LERG_DATA.OTHER_LINE_RS is 'OTHER_LINE_RATE_STEP Coded information needed to properly determine the rating associated in certain non-US areas.  In the case of Mexican data, this pertains to bands 1-8.';

comment on column IFW_LERG_DATA.OCN is 'A four digit code that refers to the party owning or responsible for a given record.  0000 indicates unknown or not applicable.';

comment on column IFW_LERG_DATA.BILL_TO_RAO is 'The "bill to" Revenue Accounting Office (RAO).  In V+H Data NXX files, if this is an "additional" RAO, the "main" RAO will be in the "Send to RAO" field.';

comment on column IFW_LERG_DATA.SPECIAL_RATING_IND is '0 = No Special Rating, 1 = Person Day Rate Only, 2 = No Collect Calls, 3 = Collect Calls Person Only';

comment on column IFW_LERG_DATA.TIMEZONE is '0 = Not applicable, 1 = Guam and the Commonwealth of the Northern Mariana Islands (CNMI), 2 = Hawaii, 3 = Alaska/Yukon, 4 = Pacific, 5 = Mountain, 6 = Central, 7 = Eastern, 8 = Atlantic, 9 = Newfoundland';

comment on column IFW_LERG_DATA.DSO_IND is '0 = Not observed, 1 = Observed, for the given NXX.Note: For NXXTYPEs 14 and 17, although a value may exist in the field, Daylight Savings observance is not a factor and the field does not apply.';

comment on column IFW_LERG_DATA.STATE is 'Standardized two-character code for US states.  Other areas are based on the two carrier identifier used by COMMON LANGUAGEƒ due to correlate these records with other telephony data which may or may not correlate with standard postal abbreviations.';

comment on column IFW_LERG_DATA.COMPANY_CODE is 'A code equaling the last two digits of the Bell Operating Company (BOC) operating in the area of the assigned NPA NXX.  Various locations and NXXTYPEs default this to 00.';

comment on column IFW_LERG_DATA.COMPANY_TYPE is 'Company Type (0-9)';

comment on column IFW_LERG_DATA.POINT_ID is 'Point Identification (0, 2-6, 9, B, C)';

comment on column IFW_LERG_DATA.SSC is 'Special Service Code (SSC)';

comment on column IFW_LERG_DATA.TD_EO is 'Terminating Digits End Office';

comment on column IFW_LERG_DATA.TD_AT is 'Terminating Digits Access Tandem';

comment on column IFW_LERG_DATA.AOCN is 'Administrative OCN';

comment on column IFW_LERG_DATA.LOC_NAME is 'Locality Name';

comment on column IFW_LERG_DATA.LOC_COUNTY is 'Locality County';

comment on column IFW_LERG_DATA.RC_ABBREV is 'Rate Center (RC) Name Abbreviation';

comment on column IFW_LERG_DATA.RC_TYPE is 'Rate Center Type';

comment on column IFW_LERG_DATA.SWITCH is 'Switch';

comment on column IFW_LERG_DATA.SHA_IND is 'Switch Homing Arrangement (SHA) Indicator';

comment on column IFW_LERG_DATA.RANGE_OCN is 'Operating Company Number (OCN) for range';

comment on column IFW_LERG_DATA.ENTRYBY is 'ENTRYBY';

comment on column IFW_LERG_DATA.ENTRYDATE is 'ENTRYDATE';

comment on column IFW_LERG_DATA.MODIFDATE is 'MODIFDATE';

comment on column IFW_LERG_DATA.MODIFBY is 'MODIFBY';

comment on column IFW_LERG_DATA.MODIFIED is 'MODIFIED';

comment on column IFW_LERG_DATA.RECVER is 'RECVER';

insert into IFW_LERG_DATA
(GEOMODEL,AREACODE,VALID_FROM,VALID_TO,LATA_SUBZONE,LATA,LATA_NAME,IDDD_IND,TBPI,DIALABLE_IND,NPA_NONMEX,NPA,NXX,NXX_TYPE,PORTABLE_IND,SEND_TO_RAO,OTHER_LINE_RS,OCN,BILL_TO_RAO,SPECIAL_RATING_IND,TIMEZONE,DSO_IND,STATE,COMPANY_CODE,COMPANY_TYPE,POINT_ID,SSC,TD_EO,TD_AT,AOCN,LOC_NAME,LOC_COUNTY,RC_ABBREV,RC_TYPE,SWITCH,SHA_IND,RANGE_OCN,ENTRYDATE,ENTRYBY,MODIFDATE,MODIFBY,MODIFIED,RECVER)
select GEOMODEL,AREACODE,VALID_FROM,VALID_TO,LATA_SUBZONE,LATA,LATA_NAME,IDDD_IND,TBPI,DIALABLE_IND,NPA_NONMEX,NPA,NXX,NXX_TYPE,PORTABLE_IND,SEND_TO_RAO,OTHER_LINE_RATE_STEP,OCN,BILL_TO_RAO,SPECIAL_RATING_IND,TIMEZONE,DSO_IND,STATE,COMPANY_CODE,COMPANY_TYPE,POINT_ID,SSC,TD_EO,TD_AT,AOCN,LOC_NAME,LOC_COUNTY,RC_ABBREV,RC_TYPE,SWITCH,SHA_IND,RANGE_OCN,ENTRYDATE,ENTRYBY,MODIFDATE,MODIFBY,MODIFIED,RECVER
from tmp_lerg_data;

-- IC_DAILY.EVENTRATE_CHARGE_AMOUNT           -> EVENTRATE_AMOUNT
-- IC_DAILY.EVENTBILL_CHARGE_AMOUNT           -> EVENTBILL_AMOUNT
-- IC_DAILY.EVENTHOME_CHARGE_AMOUNT           -> EVENTHOME_AMOUNT
-- IC_DAILY.BILLRATE_CHARGE_AMOUNT            -> BILLRATE_AMOUNT
-- IC_DAILY.BILLBILL_CHARGE_AMOUNT            -> BILLBILL_AMOUNT
-- IC_DAILY.BILLHOME_CHARGE_AMOUNT            -> BILLHOME_AMOUNT
alter table ic_daily drop constraint CKC_ICD_BILLDIR;

alter table ic_daily drop constraint CKC_ICD_ENTRY_TYPE;

alter table ic_daily drop primary key;

rename ic_daily to tmp_daily;

create table IC_DAILY
(
    NETWORKMODEL        VARCHAR2(10)           not null,
    NETWORK_OPERATOR    VARCHAR2(10)           not null,
    PIN_LOGIN_ALIAS     VARCHAR2(255)          null    ,
    DAY                 DATE                   not null,
    SEQUENCE_NUMBER     NUMBER(9)              default 0 not null,
    BILLRUN             VARCHAR2(30)           default '-1' not null,
    SWITCH              VARCHAR2(15)           not null,
    POI                 VARCHAR2(15)           not null,
    TRUNK               VARCHAR2(15)           not null,
    ICPRODUCT           VARCHAR2(10)           not null,
    BILL_DIRECTION      CHAR(1)                not null
        constraint CKC_ICD_BILLDIR check (BILL_DIRECTION in ('I','O')),
    RATEPLAN            VARCHAR2(10)           not null,
    SERVICECODE         VARCHAR2(5)            not null,
    SERVICECLASS        VARCHAR2(5)            not null,
    IMPACT_CATEGORY     VARCHAR2(10)           not null,
    TIMEMODEL           VARCHAR2(10)           not null,
    TIMEZONE            VARCHAR2(10)           not null,
    GLACCOUNT           VARCHAR2(10)           not null,
    RESOURCE_NAME       VARCHAR2(10)           not null,
    RUM                 VARCHAR2(10)           not null,
    ENTRY_TYPE          CHAR(1)                default 'N' not null
        constraint CKC_ICD_ENTRY_TYPE check (ENTRY_TYPE in ('N','R','C','S')),
    ENTRY_TYPE_SEQ      NUMBER(9)              not null,
    NUM_ITEMS           NUMBER(9)              default 0 not null,
    QUANTITY            NUMBER(15)             default 0 not null,
    ROUNDED_QUANTITY    NUMBER(15)             default 0 not null,
    EVENTRATE_AMOUNT    NUMBER                 default 0 not null,
    EVENTBILL_AMOUNT    NUMBER                 default 0 not null,
    EVENTHOME_AMOUNT    NUMBER                 default 0 not null,
    BILLRATE_AMOUNT     NUMBER                 default 0 not null,
    BILLBILL_AMOUNT     NUMBER                 default 0 not null,
    BILLHOME_AMOUNT     NUMBER                 default 0 not null,
    EXPORTED            NUMBER(1)              default 0 not null,
    EXPORT_DATE         DATE                   null    ,
    constraint PK_ICD primary key (NETWORKMODEL, NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN, SWITCH, POI, TRUNK, ICPRODUCT, BILL_DIRECTION, RATEPLAN, SERVICECODE, SERVICECLASS, IMPACT_CATEGORY, TIMEMODEL, TIMEZONE, GLACCOUNT, RESOURCE_NAME, RUM, ENTRY_TYPE, ENTRY_TYPE_SEQ)
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
     )
)
pctfree 10
pctused 80
initrans 2
storage
(
initial 2M
next 2M
minextents 1
maxextents unlimited
pctincrease 0
);

grant select, insert, update, delete on IC_DAILY to INTEGRATE_ROLE_ALL;

grant select on IC_DAILY to INTEGRATE_ROLE_SEL;

comment on table IC_DAILY is 'tariffIC result table for the default online interconnection billing';

comment on column IC_DAILY.NETWORKMODEL is 'related networkmodel to which the ic-bill belongs';

comment on column IC_DAILY.NETWORK_OPERATOR is 'related network operator to whom the ic-bill belongs';

comment on column IC_DAILY.PIN_LOGIN_ALIAS is 'Login or Alias for Infranets NetworkOperator Account this entry has to be billed to.';

comment on column IC_DAILY.DAY is 'day for which the ic-bill should be aggregated';

comment on column IC_DAILY.SEQUENCE_NUMBER is 'optional stream/file sequence number of the aggregated ic-bill part';

comment on column IC_DAILY.BILLRUN is 'defines the bill run periode for the ic-bill, format ''BCYYYYMMxx'', -1 for open periode';

comment on column IC_DAILY.SWITCH is 'switch-code on which the ic-bill should be aggregated';

comment on column IC_DAILY.POI is 'poi-code on which the ic-bill should be aggregated';

comment on column IC_DAILY.TRUNK is 'trunk-id on which the ic-bill should be aggregated';

comment on column IC_DAILY.ICPRODUCT is 'internal ic-product code on which the ic-bill should be aggregated';

comment on column IC_DAILY.BILL_DIRECTION is 'internal bill-direction on which the ic-bill should be aggregated (equals IFW_ICPRODUCT_RATE.BILL_DIRECTION)';

comment on column IC_DAILY.RATEPLAN is 'rateplan code on which the ic-bill should be aggregated';

comment on column IC_DAILY.SERVICECODE is 'servicecode code on which the ic-bill should be aggregated';

comment on column IC_DAILY.SERVICECLASS is 'serviceclass on which the ic-bill should be aggregated';

comment on column IC_DAILY.IMPACT_CATEGORY is 'impact category on which the ic-bill should be aggregated';

comment on column IC_DAILY.TIMEMODEL is 'timemodel code on which the ic-bill should be aggregated';

comment on column IC_DAILY.TIMEZONE is 'timezone code on which the ic-bill should be aggregated';

comment on column IC_DAILY.GLACCOUNT is 'glaccount on which the ic-bill should be aggregated';

comment on column IC_DAILY.RESOURCE_NAME is 'ressource on which the ic-bill should be aggregated';

comment on column IC_DAILY.RUM is 'RUM of Quantity fields, rum on which the ic-bill should be aggregated';

comment on column IC_DAILY.ENTRY_TYPE is 'Normal Booking: N, Cancellation/Reversal: R, Correction: C, Storno: S';

comment on column IC_DAILY.ENTRY_TYPE_SEQ is 'Identifirer for more than one correction';

comment on column IC_DAILY.NUM_ITEMS is 'aggregation result: count of all single edrs';

comment on column IC_DAILY.QUANTITY is 'aggregation result: sum original duration';

comment on column IC_DAILY.ROUNDED_QUANTITY is 'aggregation result: sum rounded duration according to price model beats';

comment on column IC_DAILY.EVENTRATE_AMOUNT is 'Event Charge amount based on the currency defined within an icproduct tariffmodel. (Event Rating Currency)';

comment on column IC_DAILY.EVENTBILL_AMOUNT is 'Event Charge amount based on the currency defined within a networkoperator and configured exchange rate plug-in. (Event Billing Currency)';

comment on column IC_DAILY.EVENTHOME_AMOUNT is 'Event Charge amount based on the currency defined within a networkoperator and configured exchange rate plug-in. (Event Home Currency)';

comment on column IC_DAILY.BILLRATE_AMOUNT is 'Billing Charge amount based on the currency defined within an icproduct tariffmodell. (Billing Rating Currency)';

comment on column IC_DAILY.BILLBILL_AMOUNT is 'Billing Charge amount based on the currency defined within a networkoperator and configured exchange rate plug-in. (Billing Billing Currency)';

comment on column IC_DAILY.BILLHOME_AMOUNT is 'Billing Charge amount based on the currency defined within a networkmodel and configured exchange rate plug-in. (Billing Home Currency)';

comment on column IC_DAILY.EXPORTED is 'Exported by export tool';

comment on column IC_DAILY.EXPORT_DATE is 'Date when row was exported';

insert into ic_daily
(NETWORKMODEL,NETWORK_OPERATOR,PIN_LOGIN_ALIAS,DAY,SEQUENCE_NUMBER,BILLRUN,SWITCH,POI,TRUNK,ICPRODUCT,BILL_DIRECTION,RATEPLAN,SERVICECODE,SERVICECLASS,IMPACT_CATEGORY,TIMEMODEL,TIMEZONE,GLACCOUNT,RESOURCE_NAME,RUM,ENTRY_TYPE,ENTRY_TYPE_SEQ,NUM_ITEMS,QUANTITY,ROUNDED_QUANTITY,EVENTRATE_AMOUNT,EVENTBILL_AMOUNT,EVENTHOME_AMOUNT,BILLRATE_AMOUNT,BILLBILL_AMOUNT,BILLHOME_AMOUNT,EXPORTED,EXPORT_DATE)
select NETWORKMODEL,NETWORK_OPERATOR,PIN_LOGIN_ALIAS,DAY,SEQUENCE_NUMBER,BILLRUN,SWITCH,POI,TRUNK,ICPRODUCT,BILL_DIRECTION,RATEPLAN,SERVICECODE,SERVICECLASS,IMPACT_CATEGORY,TIMEMODEL,TIMEZONE,GLACCOUNT,RESOURCE_NAME,RUM,ENTRY_TYPE,ENTRY_TYPE_SEQ,NUM_ITEMS,QUANTITY,ROUNDED_QUANTITY,EVENTRATE_CHARGE_AMOUNT,EVENTBILL_CHARGE_AMOUNT,EVENTHOME_CHARGE_AMOUNT,BILLRATE_CHARGE_AMOUNT,BILLBILL_CHARGE_AMOUNT,BILLHOME_CHARGE_AMOUNT,EXPORTED,EXPORT_DATE
from tmp_daily;

-- IC_DAILY_ALTERNATE.EVENTRATE_CHARGE_AMOUNT -> EVENTRATE_AMOUNT
-- IC_DAILY_ALTERNATE.EVENTBILL_CHARGE_AMOUNT -> EVENTBILL_AMOUNT
-- IC_DAILY_ALTERNATE.EVENTHOME_CHARGE_AMOUNT -> EVENTHOME_AMOUNT
-- IC_DAILY_ALTERNATE.BILLRATE_CHARGE_AMOUNT  -> BILLRATE_AMOUNT
-- IC_DAILY_ALTERNATE.BILLBILL_CHARGE_AMOUNT  -> BILLBILL_AMOUNT
-- IC_DAILY_ALTERNATE.BILLHOME_CHARGE_AMOUNT  -> BILLHOME_AMOUNT
alter table ic_daily_alternate drop constraint CKC_ICA_BILLDIR;

alter table ic_daily_alternate drop constraint CKC_ICA_ENTRY_TYPE;

alter table ic_daily_alternate drop primary key;

rename ic_daily_alternate to tmp_daily_a;

create table IC_DAILY_ALTERNATE
(
    NETWORKMODEL        VARCHAR2(10)           not null,
    NETWORK_OPERATOR    VARCHAR2(10)           not null,
    PIN_LOGIN_ALIAS     VARCHAR2(255)          null    ,
    DAY                 DATE                   not null,
    SEQUENCE_NUMBER     NUMBER(9)              not null,
    BILLRUN             VARCHAR2(30)           default '-1' not null,
    SWITCH              VARCHAR2(15)           not null,
    POI                 VARCHAR2(15)           not null,
    TRUNK               VARCHAR2(15)           not null,
    ICPRODUCT           VARCHAR2(10)           not null,
    BILL_DIRECTION      CHAR(1)                not null
        constraint CKC_ICA_BILLDIR check (BILL_DIRECTION in ('I','O')),
    RATEPLAN            VARCHAR2(10)           not null,
    SERVICECODE         VARCHAR2(5)            not null,
    SERVICECLASS        VARCHAR2(5)            not null,
    IMPACT_CATEGORY     VARCHAR2(10)           not null,
    TIMEMODEL           VARCHAR2(10)           not null,
    TIMEZONE            VARCHAR2(10)           not null,
    GLACCOUNT           VARCHAR2(10)           not null,
    RESOURCE_NAME       VARCHAR2(10)           not null,
    RUM                 VARCHAR2(10)           not null,
    ENTRY_TYPE          CHAR(1)                default 'N' not null
        constraint CKC_ICA_ENTRY_TYPE check (ENTRY_TYPE in ('N','R','C','S')),
    ENTRY_TYPE_SEQ      NUMBER(9)              not null,
    NUM_ITEMS           NUMBER(9)              null    ,
    QUANTITY            NUMBER(15)             default 0 not null,
    ROUNDED_QUANTITY    NUMBER(15)             default 0 not null,
    EVENTRATE_AMOUNT    NUMBER                 default 0 not null,
    EVENTBILL_AMOUNT    NUMBER                 default 0 not null,
    EVENTHOME_AMOUNT    NUMBER                 default 0 not null,
    BILLRATE_AMOUNT     NUMBER                 default 0 not null,
    BILLBILL_AMOUNT     NUMBER                 default 0 not null,
    BILLHOME_AMOUNT     NUMBER                 default 0 not null,
    EXPORTED            NUMBER(1)              default 0 not null,
    EXPORT_DATE         DATE                   null    ,
    constraint PK_ICA primary key (NETWORKMODEL, NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN, SWITCH, POI, TRUNK, ICPRODUCT, BILL_DIRECTION, RATEPLAN, SERVICECODE, SERVICECLASS, IMPACT_CATEGORY, TIMEMODEL, TIMEZONE, GLACCOUNT, RESOURCE_NAME, RUM, ENTRY_TYPE, ENTRY_TYPE_SEQ)
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
     )
)
pctfree 10
pctused 80
initrans 2
storage
(
initial 2M
next 2M
minextents 1
maxextents unlimited
pctincrease 0
);

grant select, insert, update, delete on IC_DAILY_ALTERNATE to INTEGRATE_ROLE_ALL;

grant select on IC_DAILY_ALTERNATE to INTEGRATE_ROLE_SEL;

comment on table IC_DAILY_ALTERNATE is 'tariffIC result table for the alternate online interconnection billing';

comment on column IC_DAILY_ALTERNATE.NETWORKMODEL is 'related networkmodel to which the ic-bill belongs';

comment on column IC_DAILY_ALTERNATE.NETWORK_OPERATOR is 'related network operator to whom the ic-bill belongs';

comment on column IC_DAILY_ALTERNATE.PIN_LOGIN_ALIAS is 'Login or Alias for Infranets NetworkOperator Account this entry has to be billed to.';

comment on column IC_DAILY_ALTERNATE.DAY is 'day for which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.SEQUENCE_NUMBER is 'optional stream/file sequence number of the aggregated ic-bill part';

comment on column IC_DAILY_ALTERNATE.BILLRUN is 'defines the bill run periode for the ic-bill, format ''BCYYYYMMxx'', -1 for open periode';

comment on column IC_DAILY_ALTERNATE.SWITCH is 'switch-code on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.POI is 'poi-code on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.TRUNK is 'trunk-id on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.ICPRODUCT is 'internal ic-product code on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.BILL_DIRECTION is 'internal bill-direction on which the ic-bill should be aggregated (equals IFW_ICPRODUCT_RATE.BILL_DIRECTION)';

comment on column IC_DAILY_ALTERNATE.RATEPLAN is 'rateplan code on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.SERVICECODE is 'servicecode code on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.SERVICECLASS is 'serviceclass on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.IMPACT_CATEGORY is 'impact category on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.TIMEMODEL is 'timemodel code on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.TIMEZONE is 'timezone code on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.GLACCOUNT is 'glaccount on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.RESOURCE_NAME is 'ressource on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.RUM is 'RUM of Quantity fields, rum on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.ENTRY_TYPE is 'Normal Booking: N, Cancellation/Reversal: R, Correction: C, Storno: S';

comment on column IC_DAILY_ALTERNATE.ENTRY_TYPE_SEQ is 'Identifirer for more than one correction';

comment on column IC_DAILY_ALTERNATE.NUM_ITEMS is 'aggregation result: count of all single edrs';

comment on column IC_DAILY_ALTERNATE.QUANTITY is 'aggregation result: sum original duration';

comment on column IC_DAILY_ALTERNATE.ROUNDED_QUANTITY is 'aggregation result: sum rounded duration according to price model beats';

comment on column IC_DAILY_ALTERNATE.EVENTRATE_AMOUNT is 'Event Charge amount based on the currency defined within an icproduct tariffmodel. (Event Rating Currency)';

comment on column IC_DAILY_ALTERNATE.EVENTBILL_AMOUNT is 'Event Charge amount based on the currency defined within a networkoperator and configured exchange rate plug-in. (Event Billing Currency)';

comment on column IC_DAILY_ALTERNATE.EVENTHOME_AMOUNT is 'Event Charge amount based on the currency defined within a networkoperator and configured exchange rate plug-in. (Event Home Currency)';

comment on column IC_DAILY_ALTERNATE.BILLRATE_AMOUNT is 'Billing Charge amount based on the currency defined within an icproduct tariffmodell. (Billing Rating Currency)';

comment on column IC_DAILY_ALTERNATE.BILLBILL_AMOUNT is 'Billing Charge amount based on the currency defined within a networkoperator and configured exchange rate plug-in. (Billing Billing Currency)';

comment on column IC_DAILY_ALTERNATE.BILLHOME_AMOUNT is 'Billing Charge amount based on the currency defined within a networkmodel and configured exchange rate plug-in. (Billing Home Currency)';

comment on column IC_DAILY_ALTERNATE.EXPORTED is 'Exported by export tool';

comment on column IC_DAILY_ALTERNATE.EXPORT_DATE is 'Date when row was exported';

insert into ic_daily_alternate
(NETWORKMODEL,NETWORK_OPERATOR,PIN_LOGIN_ALIAS,DAY,SEQUENCE_NUMBER,BILLRUN,SWITCH,POI,TRUNK,ICPRODUCT,BILL_DIRECTION,RATEPLAN,SERVICECODE,SERVICECLASS,IMPACT_CATEGORY,TIMEMODEL,TIMEZONE,GLACCOUNT,RESOURCE_NAME,RUM,ENTRY_TYPE,ENTRY_TYPE_SEQ,NUM_ITEMS,QUANTITY,ROUNDED_QUANTITY,EVENTRATE_AMOUNT,EVENTBILL_AMOUNT,EVENTHOME_AMOUNT,BILLRATE_AMOUNT,BILLBILL_AMOUNT,BILLHOME_AMOUNT,EXPORTED,EXPORT_DATE)
select NETWORKMODEL,NETWORK_OPERATOR,PIN_LOGIN_ALIAS,DAY,SEQUENCE_NUMBER,BILLRUN,SWITCH,POI,TRUNK,ICPRODUCT,BILL_DIRECTION,RATEPLAN,SERVICECODE,SERVICECLASS,IMPACT_CATEGORY,TIMEMODEL,TIMEZONE,GLACCOUNT,RESOURCE_NAME,RUM,ENTRY_TYPE,ENTRY_TYPE_SEQ,NUM_ITEMS,QUANTITY,ROUNDED_QUANTITY,EVENTRATE_CHARGE_AMOUNT,EVENTBILL_CHARGE_AMOUNT,EVENTHOME_CHARGE_AMOUNT,BILLRATE_CHARGE_AMOUNT,BILLBILL_CHARGE_AMOUNT,BILLHOME_CHARGE_AMOUNT,EXPORTED,EXPORT_DATE
from tmp_daily_a;


--
-- Add ref. constraints for affected tables
--
alter table IFW_DSCMDL_VER
    add constraint FK_IFW_DMV_DML foreign key  (DISCOUNTMODEL)
       references IFW_DISCOUNTMODEL (DISCOUNTMODEL);

alter table IFW_GEO_MODEL
    add constraint FK_IFW_GMD_RUS foreign key  (RULESET)
       references IFW_RULESET (RULESET);

alter table IFW_GEOAREA_LNK
    add constraint FK_IFW_GAL_GMD foreign key  (GEOMODEL)
       references IFW_GEO_MODEL (GEOMODEL);

alter table IFW_NETWORKOPER
    add constraint FK_IFW_NOP_TXG foreign key  (TAXGROUP)
       references IFW_TAXGROUP (TAXGROUP);

alter table IFW_NETWORKOPER
    add constraint FK_IFW_NOP_CUR foreign key  (CURRENCY)
       references IFW_CURRENCY (CURRENCY);

alter table IFW_NETWORKMODEL
    add constraint FK_IFW_NWM_RPD foreign key  (RATEPLAN)
       references IFW_RATEPLAN (RATEPLAN);

alter table IFW_NETWORKMODEL
    add constraint FK_IFW_NWM_SYB foreign key  (SYSTEM_BRAND)
       references IFW_SYSTEM_BRAND (SYSTEM_BRAND);

alter table IFW_NETWORKMODEL
    add constraint FK_IFW_NWM_NOP foreign key  (NO)
       references IFW_NETWORKOPER (NO);

alter table IFW_NETWORKMODEL
    add constraint FK_IFW_NWM_CUR foreign key  (CURRENCY)
       references IFW_CURRENCY (CURRENCY);

alter table IFW_SCENARIO
    add constraint FK_IFW_SCN_EDE foreign key  (EDRC_DESC)
       references IFW_EDRC_DESC (EDRC_DESC);

alter table IFW_CLASSCON
    add constraint FK_IFW_CLC_GRCNEXT foreign key  (NEXT_GRPG_CNF_ID)
       references IFW_GROUPING_CNF (GROUPING_CNF_ID);

alter table IFW_CLASSCON
    add constraint FK_IFW_CLC_GRPNODE foreign key  (NODE_GRPG_CNF_ID)
       references IFW_GROUPING_CNF (GROUPING_CNF_ID);

alter table IFW_USC_MAP
    add constraint FK_IFW_USM_NEWCTP foreign key  (NEW_USAGETYPE)
       references IFW_USAGETYPE (USAGETYPE);

alter table IFW_USC_MAP
    add constraint FK_IFW_USM_ZMD foreign key  (ZONEMODEL)
       references IFW_ZONEMODEL (ZONEMODEL);

alter table IFW_USC_MAP
    add constraint FK_IFW_USM_USC foreign key  (USC_GROUP)
       references IFW_USC_GROUP (USC_GROUP);

alter table IFW_USC_MAP
    add constraint FK_IFW_USM_RTICT foreign key  (IMPACT_CATEGORY_RT)
       references IFW_IMPACT_CAT (IMPACT_CATEGORY);

alter table IFW_USC_MAP
    add constraint FK_IFW_USM_WSICT foreign key  (IMPACT_CATEGORY_WS)
       references IFW_IMPACT_CAT (IMPACT_CATEGORY);

alter table IFW_PRICEMDL_STEP
    add constraint FK_IFW_PMS_PMD foreign key  (PRICEMODEL)
       references IFW_PRICEMODEL (PRICEMODEL);

alter table IFW_PRICEMDL_STEP
    add constraint FK_IFW_PMS_RES foreign key  (RESOURCE_NAME)
       references IFW_RESOURCE (RESOURCE_NAME);

alter table IFW_PRICEMDL_STEP
    add constraint FK_IFW_PMS_RUM foreign key  (RUM)
       references IFW_RUM (RUM);

alter table IFW_PRICEMDL_STEP
    add constraint FK_IFW_PMS_GLA foreign key  (GLACCOUNT)
       references IFW_GLACCOUNT (GLACCOUNT);

alter table IFW_PRICEMDL_STEP
    add constraint FK_IFW_PMS_RVG foreign key  (REVENUEGROUP)
       references IFW_REVENUEGROUP (REVENUEGROUP);

alter table IFW_GEO_ZONE
    add constraint FK_IFW_GOZ_ZMD foreign key  (ZONEMODEL)
       references IFW_ZONEMODEL (ZONEMODEL);

alter table IFW_GEO_ZONE
    add constraint FK_IFW_GOZ_SRV foreign key  (SERVICECODE)
       references IFW_SERVICE (SERVICECODE);

alter table IFW_GEO_ZONE
    add constraint FK_IFW_GOZ_ALTZMD foreign key  (ALT_ZONEMODEL)
       references IFW_ZONEMODEL (ZONEMODEL);

alter table IFW_GEO_ZONE
    add constraint FK_IFW_GEZW_ICT foreign key  (ZONE_WS)
       references IFW_IMPACT_CAT (IMPACT_CATEGORY);

alter table IFW_GEO_ZONE
    add constraint FK_IFW_GEZRT_ICT foreign key  (ZONE_RT)
       references IFW_IMPACT_CAT (IMPACT_CATEGORY);

alter table IFW_SERVICE_MAP
    add constraint FK_IFW_SVM_MGR foreign key  (MAP_GROUP)
       references IFW_MAP_GROUP (MAP_GROUP);

alter table IFW_SERVICE_MAP
    add constraint FK_IFW_SCM_SRV foreign key  (INT_SERVICECODE)
       references IFW_SERVICE (SERVICECODE);

alter table IFW_SEQLOG_OUT
    add constraint FK_IFW_SLO_SCK foreign key  (SEQUENCE_NAME)
       references IFW_SEQCHECK (SEQUENCE_NAME);

alter table IFW_SEQLOG_OUT
    add constraint FK_IFW_SLO_PPL foreign key  (PROCESSEDBY_PPL)
       references IFW_PIPELINE (PIPELINE);

alter table IFW_DSCMDL_CNF
    add constraint FK_IFW_DMC_DCR foreign key  (DISCOUNTRULE)
       references IFW_DISCOUNTRULE (DISCOUNTRULE);

alter table IFW_DSCMDL_CNF
    add constraint FK_IFW_DMC_DTR foreign key  (DISCOUNTTRIGGER)
       references IFW_DSCTRIGGER (DISCOUNTTRIGGER);

alter table IFW_DSCMDL_CNF
    add constraint FK_IFW_DMC_DMV foreign key  (DISCOUNTMODEL, VERSION)
       references IFW_DSCMDL_VER (DISCOUNTMODEL, VERSION);

alter table IFW_DISCOUNTSTEP
    add constraint FK_IFW_DCS_DCM foreign key  (DISCOUNTMASTER)
       references IFW_DISCOUNTMASTER (DISCOUNTMASTER);

alter table IFW_DISCOUNTSTEP
    add constraint FK_IFW_DCS_DCR foreign key  (DISCOUNTRULE)
       references IFW_DISCOUNTRULE (DISCOUNTRULE);

alter table IFW_DISCOUNTSTEP
    add constraint FK_IFW_DCS_UOM foreign key  (GRANT_UOM)
       references IFW_UOM (UOM);

alter table IFW_DSCCONDITION
    add constraint FK_IFW_DCN_DCM foreign key  (DISCOUNTMASTER)
       references IFW_DISCOUNTMASTER (DISCOUNTMASTER);

alter table IFW_DSCCONDITION
    add constraint FK_IFW_DCN_DTR foreign key  (DISCOUNTTRIGGER)
       references IFW_DSCTRIGGER (DISCOUNTTRIGGER);

alter table IFW_RSC_MAP
    add constraint FK_IFW_RSM_SVC foreign key  (NEW_SERVICECODE, NEW_SERVICECLASS)
       references IFW_SERVICECLASS (SERVICECODE, SERVICECLASS);

alter table IFW_RSC_MAP
    add constraint FK_IFW_RSM_RSG foreign key  (RSC_GROUP)
       references IFW_RSC_GROUP (RSC_GROUP);

alter table IFW_AGGREGATION
    add constraint FK_IFW_AGG_SCN foreign key  (SCENARIO_ID)
       references IFW_SCENARIO (SCENARIO_ID);

alter table IFW_AGGREGATION
    add constraint FK_IFW_AGG_EFD foreign key  (FIELD_ID)
       references IFW_EDRC_FIELD (FIELD_ID);

alter table IFW_ICPRODUCT_RATE
    add constraint FK_IFW_IPR_NOP foreign key  (NO)
       references IFW_NETWORKOPER (NO);

alter table IFW_ICPRODUCT_RATE
    add constraint FK_IFW_IPR_NWM foreign key  (NETWORKMODEL)
       references IFW_NETWORKMODEL (NETWORKMODEL);

alter table IFW_LERG_DATA
    add constraint FK_IFW_LERG_GAL foreign key  (GEOMODEL, AREACODE, VALID_FROM)
       references IFW_GEOAREA_LNK (GEOMODEL, AREACODE, VALID_FROM);

alter table IFW_SEQLOG_IN
    add constraint FK_IFW_SLI_PPL foreign key  (PROCESSEDBY_PPL)
       references IFW_PIPELINE (PIPELINE);

alter table IFW_SEQLOG_IN
    add constraint FK_IFW_SLI_SCK foreign key  (SEQUENCE_NAME)
       references IFW_SEQCHECK (SEQUENCE_NAME);

alter table IFW_ZONEMODEL
    add constraint FK_IFW_ZMD_GMD foreign key  (GEOMODEL)
       references IFW_GEO_MODEL (GEOMODEL);

alter table IFW_SWITCH
    add constraint FK_IFW_SWI_NOP foreign key  (NO)
       references IFW_NETWORKOPER (NO);

alter table IFW_NOPRODUCT
    add constraint FK_IFW_NPR_NOP foreign key  (NO)
       references IFW_NETWORKOPER (NO);

alter table IFW_TRUNK
    add constraint FK_IFW_TRK_CNO foreign key  (CONNECTED_NO)
       references IFW_NETWORKOPER (NO);

alter table IFW_ICPRODUCT_GRP
    add constraint FK_IFW_IPG_NWM foreign key  (NETWORKMODEL)
       references IFW_NETWORKMODEL (NETWORKMODEL);

alter table IFW_GROUPING
    add constraint FK_IFW_GRP_SCN foreign key  (SCENARIO_ID)
       references IFW_SCENARIO (SCENARIO_ID);

alter table IFW_STANDARD_ZONE
    add constraint FK_IFW_STZ_ICT foreign key  (ZONE_WS)
       references IFW_IMPACT_CAT (IMPACT_CATEGORY);

alter table IFW_STANDARD_ZONE
    add constraint FK_IFW_STZRT_ICT foreign key  (ZONE_RT)
       references IFW_IMPACT_CAT (IMPACT_CATEGORY);

alter table IFW_POIAREA_LNK
    add constraint FK_IFW_PAL_NWM foreign key  (NETWORKMODEL)
       references IFW_NETWORKMODEL (NETWORKMODEL);

alter table IFW_APN_MAP
    add constraint FK_IFW_APNWS_ICT foreign key  (NEW_ZONE_WS)
       references IFW_IMPACT_CAT (IMPACT_CATEGORY);

alter table IFW_APN_MAP
    add constraint FK_IFW_APNRT_ICT foreign key  (NEW_ZONE_RT)
       references IFW_IMPACT_CAT (IMPACT_CATEGORY);

alter table IFW_NOPRODUCT_CNF
    add constraint FK_IFW_NPC_ICT foreign key  (IMPACT_CATEGORY)
       references IFW_IMPACT_CAT (IMPACT_CATEGORY);

alter table IFW_NO_BILLRUN
    add constraint FK_IFW_NBR_NOP foreign key  (NO)
       references IFW_NETWORKOPER (NO);

alter table IFW_NO_BILLRUN
    add constraint FK_IFW_NBR_NWM foreign key  (NETWORKMODEL)
       references IFW_NETWORKMODEL (NETWORKMODEL);

alter table IFW_CONDITION
    add constraint FK_IFW_CND_SCN foreign key  (SCENARIO_ID)
       references IFW_SCENARIO (SCENARIO_ID);

alter table IFW_TRUNK_CNF
    add constraint FK_IFW_TRC_IPG foreign key  (NETWORKMODEL, ICPRODUCT_GROUP)
       references IFW_ICPRODUCT_GRP (NETWORKMODEL, ICPRODUCT_GROUP);

alter table IFW_TRUNK_CNF
    add constraint FK_IFW_TRC_NWM foreign key  (NETWORKMODEL)
       references IFW_NETWORKMODEL (NETWORKMODEL);

alter table IFW_TRUNK_CNF
    add constraint FK_IFW_TRC_NOP foreign key  (NO)
       references IFW_NETWORKOPER (NO);

alter table IFW_ICPRODUCT_CNF
    add constraint FK_IFW_IPC_IPG foreign key  (NETWORKMODEL, ICPRODUCT_GROUP)
       references IFW_ICPRODUCT_GRP (NETWORKMODEL, ICPRODUCT_GROUP) on delete cascade;

alter table IFW_RATEPLAN_CNF
    add constraint FK_IFW_RPC_ICT foreign key  (IMPACT_CATEGORY)
       references IFW_IMPACT_CAT (IMPACT_CATEGORY);

alter table IFW_CLASSCON_LNK
    add constraint FK_IFW_CCL_CLC foreign key  (CLASSCON_ID)
       references IFW_CLASSCON (CLASSCON_ID) on delete cascade;


--
-- Enhancement for sequence-check/Roaming (Ciber)
--
alter table IFW_SEQLOG_IN drop constraint FK_IFW_SLI_PPL;

alter table IFW_SEQLOG_IN drop constraint FK_IFW_SLI_SCK;

alter table IFW_SEQLOG_OUT drop constraint FK_IFW_SLO_SCK;

alter table IFW_SEQLOG_OUT drop constraint FK_IFW_SLO_PPL;

alter table IFW_SEQCHECK drop primary key;

alter table IFW_SEQCHECK add KEY VARCHAR2(255) default '-1' not null;

alter table IFW_SEQCHECK add constraint PK_IFW_ESC primary key (SEQUENCE_NAME, KEY);

alter table IFW_SEQLOG_IN drop primary key;

alter table IFW_SEQLOG_IN add CHECK_KEY VARCHAR2(255) default '-1' not null;

alter table IFW_SEQLOG_IN add constraint PK_IFW_SLI primary key (STREAMNAME, CHECK_KEY, ORIG_SEQNO, RECYCLING);

alter table IFW_SEQLOG_OUT drop primary key;

alter table IFW_SEQLOG_OUT add GENERATION_KEY VARCHAR2(255) default '-1' not null;

alter table IFW_SEQLOG_OUT add constraint PK_IFW_ESQ primary key (STREAMNAME_IN, GENERATION_KEY, ORIG_SEQNO, RECYCLING, SEQUENCE_NAME, NEW_SEQNO);

alter table IFW_SEQLOG_IN
    add constraint FK_IFW_SLI_PPL foreign key  (PROCESSEDBY_PPL)
       references IFW_PIPELINE (PIPELINE);

alter table IFW_SEQLOG_IN
    add constraint FK_IFW_SLI_SCK foreign key  (SEQUENCE_NAME, CHECK_KEY)
       references IFW_SEQCHECK (SEQUENCE_NAME, KEY);

alter table IFW_SEQLOG_OUT
    add constraint FK_IFW_SLO_SCK foreign key  (SEQUENCE_NAME, GENERATION_KEY)
       references IFW_SEQCHECK (SEQUENCE_NAME, KEY);

alter table IFW_SEQLOG_OUT
    add constraint FK_IFW_SLO_PPL foreign key  (PROCESSEDBY_PPL)
       references IFW_PIPELINE (PIPELINE);


--
-- IFW_RATEPLAN_CNF
--
alter table ifw_rateplan_cnf add INFO VARCHAR2(40);

comment on column IFW_RATEPLAN_CNF.INFO is 'rateplan config info (e.g. Revenue Group)';


--
-- remove previously created temp. tables
-- (uncomment section or manually exec. statements if satisfied w/ migration.
--
--drop table TMP_DISCOUNTMODEL_VER;

--drop table TMP_DISCOUNTMDL_CNF;

--drop table TMP_DISCOUNTTRIGGER;

--drop table TMP_DISCOUNTCONDITION;

--drop table TMP_DISCOUNTSTEP;

--drop table tmp_networkoperator;

--drop table tmp_networkmodel;

--drop table TMP_ICPRODUCT_GROUP;

--drop table tmp_destinationdesc;

--drop table tmp_pricemodel_step;

--drop table tmp_geographical_zone;

--drop table tmp_geographicalmodel;

--drop table tmp_geoareacode_lnk;

--drop table TMP_IMPACT_CATEGORY;

--drop table TMP_USAGESCENARIO_MAP;

--drop table TMP_RATESERVICE_MAP;

--drop table TMP_SERVICECODE_MAP;

--drop table TMP_SEQLOG_IN;

--drop table TMP_SEQLOG_OUT;

--drop table TMP_SCENARIO;

--drop table TMP_AGGREGATION;

--drop table TMP_CLASSCON;

--drop table TMP_LERG_DATA;

--drop table tmp_daily;

--drop table tmp_daily_a;


--
-- IFW_DBVERSION
--
insert into IFW_DBVERSION
( dbversion, description, username, install_date )
values
( 'v6.5.1', 'IntegRate,Interconnect,Analyze', user, sysdate );

commit;
