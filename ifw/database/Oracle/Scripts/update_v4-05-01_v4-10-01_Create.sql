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
--   Update script from DB version v4-05-00 to v4-10-01.
--   Create all modified tables.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-05-01_v4-10-01_Create.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2000/12/21 14:22:16 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-05-01_v4-10-01_Create.sql,v $
-- Revision 1.2  2000/12/21 14:22:16  pengelbr
-- Updated to NOT modify INT_ISCRIPT and INT_RULE* tables.
-- iScript and iRules columns shall be of LONG type as before (v4-05).
--
-- Revision 1.1  2000/10/20 07:40:37  pengelbr
-- Modified/Added for v4-10-01 by PE.
--
--------------------------------------------------------------------------------

-- ============================================================
--   Table: INT_SOCIALNUMBER                                   
-- ============================================================
drop table INT_SOCIALNUMBER cascade constraints;

create table INT_SOCIALNUMBER
(
    SOCIALNUMBER             VARCHAR2(40)           not null,
    NAME                     VARCHAR2(30)           null    ,
    constraint PK_INT_SON primary key (SOCIALNUMBER)
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
tablespace INTEGRATE_TS_1_DAT
storage
(
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
)
/
grant select, insert, update, delete on INT_SOCIALNUMBER to INTEGRATE_ROLE_ALL
/
grant select on INT_SOCIALNUMBER to INTEGRATE_ROLE_SEL
/

comment on table INT_SOCIALNUMBER is 'social number table'
/

comment on column INT_SOCIALNUMBER.SOCIALNUMBER is 'specifies a social number'
/

comment on column INT_SOCIALNUMBER.NAME is 'description or organisation name'
/


-- ============================================================
--   Table: INT_CLOSEDUSERGROUP                                
-- ============================================================
drop table INT_CLOSEDUSERGROUP cascade constraints;

create table INT_CLOSEDUSERGROUP
(
    CLI                      VARCHAR2(40)           not null,
    VALID_FROM               DATE                   not null,
    CLOSEDUSERGROUP          VARCHAR2(5)            not null,
    VALID_TO                 DATE                   null    ,
    constraint PK_INT_CUG primary key (CLI, VALID_FROM, CLOSEDUSERGROUP)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_CLOSEDUSERGROUP to INTEGRATE_ROLE_ALL
/
grant select on INT_CLOSEDUSERGROUP to INTEGRATE_ROLE_SEL
/

comment on table INT_CLOSEDUSERGROUP is 'defines per cli the closeusergroup relationship'
/

comment on column INT_CLOSEDUSERGROUP.CLI is 'list of all cli''s related to the closed user group'
/

comment on column INT_CLOSEDUSERGROUP.VALID_FROM is 'date from when on this entry is valid'
/

comment on column INT_CLOSEDUSERGROUP.CLOSEDUSERGROUP is 'closed user group code'
/

comment on column INT_CLOSEDUSERGROUP.VALID_TO is 'date till when this entry is valid'
/


-- ============================================================
--   Index: IDX_INT_SEMEXEC                                    
-- ============================================================
create index IDX_INT_SEMEXEC on INT_SEMAPHORE (EXECUTION_DATE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_1_IDX
storage
(
initial 512K
next 512K
minextents 1
maxextents unlimited
pctincrease 0
)
/

-- ============================================================
--   Table: INT_SUBS_ACCOUNT                                   
-- ============================================================
drop table INT_SUBS_ACCOUNT cascade constraints;

create table INT_SUBS_ACCOUNT
(
    ACCOUNT                  VARCHAR2(40)           not null,
    TARIFFMODEL_CODE         VARCHAR2(10)           not null,
    PERIOD                   VARCHAR2(8)            not null,
    BILLCYCLE                VARCHAR2(2)            default '0' not null,
    DISCOUNTSTEP             NUMBER(9)              not null,
    DISCOUNTMASTER           NUMBER(9)              not null,
    STATUS                   CHAR(1)                default 'O' not null
        constraint CKC_STATUS_INT_SUBS_ACCOUNT check (STATUS in ('O','B','F','R')),
    ROLLOVER_UNITS           NUMBER                 default 0 not null,
    SUM_CHARGE               NUMBER                 default 0 not null,
    SUM_QUANTITY             NUMBER                 default 0 not null,
    SUM_VOL_SENT             NUMBER                 default 0 not null,
    SUM_VOL_RECEIVED         NUMBER                 default 0 not null,
    SUM_EVENT                NUMBER                 default 0 not null,
    FRAME_CHARGE             NUMBER                 default 0 not null,
    FRAME_QUANTITY           NUMBER                 default 0 not null,
    FRAME_VOL_SENT           NUMBER                 default 0 not null,
    FRAME_VOL_RECEIVED       NUMBER                 default 0 not null,
    FRAME_EVENT              NUMBER                 default 0 not null,
    DISC_AMOUNT              NUMBER                 default 0 not null,
    DISC_QUANTITY            NUMBER                 default 0 not null,
    DISC_VOL_SENT            NUMBER                 default 0 not null,
    DISC_VOL_RECEIVED        NUMBER                 default 0 not null,
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SAC primary key (ACCOUNT, TARIFFMODEL_CODE, PERIOD, BILLCYCLE, DISCOUNTSTEP, DISCOUNTMASTER)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_DAT
        storage
        (
        initial 1M
        next 1M
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
initial 4M
next 4M
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_2_IDX
/
grant select, insert, update, delete on INT_SUBS_ACCOUNT to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBS_ACCOUNT to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBS_ACCOUNT is 'subscriber accounts, keeps all discount related charge and quantity account values'
/

comment on column INT_SUBS_ACCOUNT.ACCOUNT is 'references the account to which the balance is related to (could be a customer-code, a contract-id or...)'
/

comment on column INT_SUBS_ACCOUNT.TARIFFMODEL_CODE is 'references the tariffmodel which is in use by the account'
/

comment on column INT_SUBS_ACCOUNT.PERIOD is 'specifies the period for this account (Format: YYYYMMBC, where BC defines the related BillCycle)'
/

comment on column INT_SUBS_ACCOUNT.BILLCYCLE is 'unique billcycle identifier'
/

comment on column INT_SUBS_ACCOUNT.DISCOUNTSTEP is 'references the discountstep this accout is related to'
/

comment on column INT_SUBS_ACCOUNT.DISCOUNTMASTER is 'DISCOUNTMASTER'
/

comment on column INT_SUBS_ACCOUNT.STATUS is 'defines the status of the entry (B=billed, O=open, F=overflow; R=billrun)'
/

comment on column INT_SUBS_ACCOUNT.ROLLOVER_UNITS is 'the granted units, which can be rolled over to the following period (rollover is only allowed for linear forwarded discounts)'
/

comment on column INT_SUBS_ACCOUNT.SUM_CHARGE is 'sum of all original charges (any granted discounts are not inkluded in here!)'
/

comment on column INT_SUBS_ACCOUNT.SUM_QUANTITY is 'sum of all original quantity values (any granted discounts are not inkluded in here!)'
/

comment on column INT_SUBS_ACCOUNT.SUM_VOL_SENT is 'sum of all original volume sent values (any granted discounts are not inkluded in here!)'
/

comment on column INT_SUBS_ACCOUNT.SUM_VOL_RECEIVED is 'sum of all original volume received values (any granted discounts are not inkluded in here!)'
/

comment on column INT_SUBS_ACCOUNT.SUM_EVENT is 'sum of all original events, number of records (any granted discounts are not inkluded in here!)'
/

comment on column INT_SUBS_ACCOUNT.FRAME_CHARGE is 'sum of all frame based charges (any granted discounts are not inkluded in here!)'
/

comment on column INT_SUBS_ACCOUNT.FRAME_QUANTITY is 'sum of all frame based quantity values (any granted discounts are not inkluded in here!)'
/

comment on column INT_SUBS_ACCOUNT.FRAME_VOL_SENT is 'sum of all frame based volume sent values (any granted discounts are not inkluded in here!)'
/

comment on column INT_SUBS_ACCOUNT.FRAME_VOL_RECEIVED is 'sum of all frame based volume received values (any granted discounts are not inkluded in here!)'
/

comment on column INT_SUBS_ACCOUNT.FRAME_EVENT is 'sum of all frame based events, number of records (any granted discounts are not inkluded in here!)'
/

comment on column INT_SUBS_ACCOUNT.DISC_AMOUNT is 'sum of granted discount amount (frame based)'
/

comment on column INT_SUBS_ACCOUNT.DISC_QUANTITY is 'sum of granted discount quantity (frame based)'
/

comment on column INT_SUBS_ACCOUNT.DISC_VOL_SENT is 'sum of granted discount volume sent (frame based)'
/

comment on column INT_SUBS_ACCOUNT.DISC_VOL_RECEIVED is 'sum of granted discount volume received (frame based)'
/

comment on column INT_SUBS_ACCOUNT.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_DBVERSION                                      
-- ============================================================
drop table INT_DBVERSION cascade constraints;

create table INT_DBVERSION
(
    DBVERSION                VARCHAR2(10)           not null,
    DESCRIPTION              VARCHAR2(30)           null    ,
    USERNAME                 VARCHAR2(30)           not null,
    INSTALL_DATE             DATE                   not null,
    constraint PK_INT_DBV primary key (DBVERSION)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_DBVERSION to INTEGRATE_ROLE_ALL
/
grant select on INT_DBVERSION to INTEGRATE_ROLE_SEL
/

comment on table INT_DBVERSION is 'INT_DBVERSION'
/

comment on column INT_DBVERSION.DBVERSION is 'Code / Short Description of version'
/

comment on column INT_DBVERSION.DESCRIPTION is 'Long description for DB-version'
/

comment on column INT_DBVERSION.USERNAME is 'Username / Shortname who has installed the version'
/

comment on column INT_DBVERSION.INSTALL_DATE is 'Install Date. The newest date describes the currrent version'
/


-- ============================================================
--   Table: IC_DAILY                                           
-- ============================================================
drop table IC_DAILY cascade constraints;

create table IC_DAILY
(
    NETWORK_OPERATOR         VARCHAR2(10)           not null,
    DAY                      DATE                   not null,
    SEQUENCE_NUMBER          NUMBER(9)              default 0 not null,
    BILLRUN                  VARCHAR2(10)           not null,
    TRUNK                    VARCHAR2(15)           not null,
    ICPRODUCT                VARCHAR2(10)           not null,
    BILLING_DIRECTION        CHAR(1)                not null
        constraint CKC_BILLING__IC_DAILY check (BILLING_DIRECTION in ('I','O')),
    ZONE                     VARCHAR2(5)            not null,
    TIMEZONE                 VARCHAR2(10)           not null,
    NUM_ITEMS                NUMBER(9)              default 0 not null,
    DURATION                 NUMBER                 default 0 not null,
    ROUNDED_DURATION         NUMBER                 default 0 not null,
    VOLUME_SENT              NUMBER                 default 0 not null,
    VOLUME_RECEIVED          NUMBER                 default 0 not null,
    CHARGE_AMOUNT            NUMBER                 default 0 not null,
    constraint PK_ICD primary key (NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN, TRUNK, ICPRODUCT, BILLING_DIRECTION, ZONE, TIMEZONE)
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
)
/
grant select, insert, update, delete on IC_DAILY to INTEGRATE_ROLE_ALL
/
grant select on IC_DAILY to INTEGRATE_ROLE_SEL
/

comment on table IC_DAILY is 'tariffIC result table for the default online interconnection billing'
/

comment on column IC_DAILY.NETWORK_OPERATOR is 'related network operator to whom the ic-bill belongs'
/

comment on column IC_DAILY.DAY is 'day for which the ic-bill should be aggregated'
/

comment on column IC_DAILY.SEQUENCE_NUMBER is 'optional stream/file sequence number of the aggregated ic-bill part'
/

comment on column IC_DAILY.BILLRUN is 'defines the bill run periode for the ic-bill, format ''BCYYYYMMxx''; -1 for open periode'
/

comment on column IC_DAILY.TRUNK is 'trunk-id on which the ic-bill should be aggregated'
/

comment on column IC_DAILY.ICPRODUCT is 'internal ic-product code on which the ic-bill should be aggregated'
/

comment on column IC_DAILY.BILLING_DIRECTION is 'bill direction code on which the ic-bill should be aggregated (I=Incomming, O=Outgoing)'
/

comment on column IC_DAILY.ZONE is 'zone value on which the ic-bill should be aggregated'
/

comment on column IC_DAILY.TIMEZONE is 'timezone code on which the ic-bill should be aggregated'
/

comment on column IC_DAILY.NUM_ITEMS is 'aggregation result: count of all single edrs'
/

comment on column IC_DAILY.DURATION is 'aggregation result: sum original duration'
/

comment on column IC_DAILY.ROUNDED_DURATION is 'aggregation result: sum rounded duration according to price model beats'
/

comment on column IC_DAILY.VOLUME_SENT is 'aggregation result: sum of total volume sent'
/

comment on column IC_DAILY.VOLUME_RECEIVED is 'aggregation result: sum of total volume received'
/

comment on column IC_DAILY.CHARGE_AMOUNT is 'aggregation result: sum of total charge amount to be billed'
/


-- ============================================================
--   Table: IC_DAILY_ALTERNATE                                 
-- ============================================================
drop table IC_DAILY_ALTERNATE cascade constraints;

create table IC_DAILY_ALTERNATE
(
    NETWORK_OPERATOR         VARCHAR2(10)           not null,
    DAY                      DATE                   default sysdate not null,
    SEQUENCE_NUMBER          NUMBER(9)              default 0 not null,
    BILLRUN                  VARCHAR2(10)           default '-1' not null,
    TRUNK                    VARCHAR2(15)           not null,
    ICPRODUCT                VARCHAR2(10)           not null,
    BILLING_DIRECTION        CHAR(1)                not null
        constraint CKC_BILLING__IC_DAILY_ALTERNAT check (BILLING_DIRECTION in ('I','O')),
    ZONE                     VARCHAR2(5)            not null,
    TIMEZONE                 VARCHAR2(10)           not null,
    NUM_ITEMS                NUMBER(9)              default 0 null    ,
    DURATION                 NUMBER                 default 0 not null,
    ROUNDED_DURATION         NUMBER                 default 0 not null,
    VOLUME_SENT              NUMBER                 default 0 not null,
    VOLUME_RECEIVED          NUMBER                 default 0 not null,
    CHARGE_AMOUNT            NUMBER                 default 0 not null,
    constraint PK_IDA primary key (NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN, TRUNK, ICPRODUCT, BILLING_DIRECTION, ZONE, TIMEZONE)
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
)
/
grant select, insert, update, delete on IC_DAILY_ALTERNATE to INTEGRATE_ROLE_ALL
/
grant select on IC_DAILY_ALTERNATE to INTEGRATE_ROLE_SEL
/

comment on table IC_DAILY_ALTERNATE is 'tariffIC result table for the alternate online interconnection billing'
/

comment on column IC_DAILY_ALTERNATE.NETWORK_OPERATOR is 'related network operator to whom the ic-bill belongs'
/

comment on column IC_DAILY_ALTERNATE.DAY is 'day for which the ic-bill should be aggregated'
/

comment on column IC_DAILY_ALTERNATE.SEQUENCE_NUMBER is 'optional stream/file sequence number of the aggregated ic-bill part'
/

comment on column IC_DAILY_ALTERNATE.BILLRUN is 'defines the bill run periode for the ic-bill, format ''BCYYYYMMxx''; -1 for open periode'
/

comment on column IC_DAILY_ALTERNATE.TRUNK is 'trunk-id on which the ic-bill should be aggregated'
/

comment on column IC_DAILY_ALTERNATE.ICPRODUCT is 'internal ic-product code on which the ic-bill should be aggregated'
/

comment on column IC_DAILY_ALTERNATE.BILLING_DIRECTION is 'bill direction code on which the ic-bill should be aggregated (I=Incomming, O=Outgoing)'
/

comment on column IC_DAILY_ALTERNATE.ZONE is 'zone value on which the ic-bill should be aggregated'
/

comment on column IC_DAILY_ALTERNATE.TIMEZONE is 'timezone code on which the ic-bill should be aggregated'
/

comment on column IC_DAILY_ALTERNATE.NUM_ITEMS is 'aggregation result: count of all single edrs'
/

comment on column IC_DAILY_ALTERNATE.DURATION is 'aggregation result: sum original duration'
/

comment on column IC_DAILY_ALTERNATE.ROUNDED_DURATION is 'aggregation result: sum rounded duration according to price model beats'
/

comment on column IC_DAILY_ALTERNATE.VOLUME_SENT is 'aggregation result: sum of total volume sent'
/

comment on column IC_DAILY_ALTERNATE.VOLUME_RECEIVED is 'aggregation result: sum of total volume received'
/

comment on column IC_DAILY_ALTERNATE.CHARGE_AMOUNT is 'aggregation result: sum of total charge amount to be billed'
/


-- ============================================================
--   Table: AGG_HOLIDAY                                        
-- ============================================================
drop table AGG_HOLIDAY cascade constraints;

create table AGG_HOLIDAY
(
    HOLIDAY                  DATE                   not null,
    NAME                     VARCHAR2(35)           null    ,
    RECURRING                NUMBER(1)              default 0 not null
        constraint CKC_RECURRIN_AGG_HOLIDAY check (RECURRING in (0,1)),
    constraint PK_AGG_HOLIDAY primary key (HOLIDAY)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_HOLIDAY to INTEGRATE_ROLE_ALL
/
grant select on AGG_HOLIDAY to INTEGRATE_ROLE_SEL
/

comment on table AGG_HOLIDAY is 'Defines all special days, i.g. holidays ,....'
/

comment on column AGG_HOLIDAY.HOLIDAY is 'Defines the date of holiday'
/

comment on column AGG_HOLIDAY.NAME is 'External Name / Description'
/

comment on column AGG_HOLIDAY.RECURRING is 'Flag specifies, wether the holiday is recurring or not'
/


-- ============================================================
--   Index: BIDX_AGG_HOLIDAY_RECURRING                         
-- ============================================================
create index BIDX_AGG_HOLIDAY_RECURRING on AGG_HOLIDAY (RECURRING asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: INT_DESTINATIONDESC                                
-- ============================================================
drop table INT_DESTINATIONDESC cascade constraints;

create table INT_DESTINATIONDESC
(
    AREACODE                 VARCHAR2(40)           not null,
    TYPE                     CHAR(1)                default 'S' not null
        constraint CKC_TYPE_INT_DESTINATIONDES check (TYPE in ('N','I','S')),
    NAME                     VARCHAR2(30)           null    ,
    constraint PK_INT_DDC primary key (AREACODE)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_DESTINATIONDESC to INTEGRATE_ROLE_ALL
/
grant select on INT_DESTINATIONDESC to INTEGRATE_ROLE_SEL
/

comment on table INT_DESTINATIONDESC is 'destination description definition, gives an areacode a name'
/

comment on column INT_DESTINATIONDESC.AREACODE is 'specifies the area code the description is valid for'
/

comment on column INT_DESTINATIONDESC.TYPE is 'type of the areacode, could be N=national, I=international, S=special'
/

comment on column INT_DESTINATIONDESC.NAME is 'description for this areacode'
/


-- ============================================================
--   Table: INT_TIMEMODEL                                      
-- ============================================================
drop table INT_TIMEMODEL cascade constraints;

create table INT_TIMEMODEL
(
    TIMEMODEL                NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TIMEMODEL check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TIM primary key (TIMEMODEL)
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
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_TIMEMODEL to INTEGRATE_ROLE_ALL
/
grant select on INT_TIMEMODEL to INTEGRATE_ROLE_SEL
/

comment on table INT_TIMEMODEL is 'time model definition (groups different timezones to a tariff zone)'
/

comment on column INT_TIMEMODEL.TIMEMODEL is 'unique time model id'
/

comment on column INT_TIMEMODEL.CODE is 'external time model code'
/

comment on column INT_TIMEMODEL.NAME is 'description'
/

comment on column INT_TIMEMODEL.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TIMEMODEL.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TIMEMODEL.MODIFBY is 'MODIFBY'
/

comment on column INT_TIMEMODEL.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TIMEMODEL.MODIFIED is 'MODIFIED'
/

comment on column INT_TIMEMODEL.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_TIM                                         
-- ============================================================
create unique index AK_INT_TIM on INT_TIMEMODEL (CODE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_4_IDX
storage
(
initial 64K
next 64K
minextents 1
maxextents unlimited
pctincrease 0
)
/

-- ============================================================
--   Table: INT_DAYCODE                                        
-- ============================================================
drop table INT_DAYCODE cascade constraints;

create table INT_DAYCODE
(
    DAYCODE                  NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    DATEDAY                  DATE                   null    ,
    MONDAY                   NUMBER(1)              default 0 not null
        constraint CKC_MONDAY_INT_DAYCODE check (MONDAY in (0,1)),
    TUESDAY                  NUMBER(1)              default 0 not null
        constraint CKC_TUESDAY_INT_DAYCODE check (TUESDAY in (0,1)),
    WEDNESDAY                NUMBER(1)              default 0 not null
        constraint CKC_WEDNESDA_INT_DAYCODE check (WEDNESDAY in (0,1)),
    THURSDAY                 NUMBER(1)              default 0 not null
        constraint CKC_THURSDAY_INT_DAYCODE check (THURSDAY in (0,1)),
    FRIDAY                   NUMBER(1)              default 0 not null
        constraint CKC_FRIDAY_INT_DAYCODE check (FRIDAY in (0,1)),
    SATURDAY                 NUMBER(1)              default 0 not null
        constraint CKC_SATURDAY_INT_DAYCODE check (SATURDAY in (0,1)),
    SUNDAY                   NUMBER(1)              default 0 not null
        constraint CKC_SUNDAY_INT_DAYCODE check (SUNDAY in (0,1)),
    HOLIDAY                  NUMBER(1)              default 0 not null
        constraint CKC_HOLIDAY_INT_DAYCODE check (HOLIDAY in (0,1)),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_DAYCODE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DAY primary key (DAYCODE)
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
buffer_pool keep
)
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_DAYCODE to INTEGRATE_ROLE_ALL
/
grant select on INT_DAYCODE to INTEGRATE_ROLE_SEL
/

comment on table INT_DAYCODE is 'definition of possible day codes (e.g. weekday, weekend, holiday etc.)'
/

comment on column INT_DAYCODE.DAYCODE is 'unique daycode id'
/

comment on column INT_DAYCODE.CODE is 'external code for this daycode'
/

comment on column INT_DAYCODE.NAME is 'description'
/

comment on column INT_DAYCODE.DATEDAY is 'a special day, specified by this date'
/

comment on column INT_DAYCODE.MONDAY is '0=False, 1=True'
/

comment on column INT_DAYCODE.TUESDAY is '0=False, 1=True'
/

comment on column INT_DAYCODE.WEDNESDAY is '0=False, 1=True'
/

comment on column INT_DAYCODE.THURSDAY is '0=False, 1=True'
/

comment on column INT_DAYCODE.FRIDAY is '0=False, 1=True'
/

comment on column INT_DAYCODE.SATURDAY is '0=False, 1=True'
/

comment on column INT_DAYCODE.SUNDAY is '0=False, 1=True'
/

comment on column INT_DAYCODE.HOLIDAY is '0=False, 1=True (if specified the holiday calendar will be used)'
/

comment on column INT_DAYCODE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_DAYCODE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_DAYCODE.MODIFBY is 'MODIFBY'
/

comment on column INT_DAYCODE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_DAYCODE.MODIFIED is 'MODIFIED'
/

comment on column INT_DAYCODE.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_DAY                                         
-- ============================================================
create unique index AK_INT_DAY on INT_DAYCODE (CODE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_4_IDX
storage
(
initial 64K
next 64K
minextents 1
maxextents unlimited
pctincrease 0
)
/

-- ============================================================
--   Table: INT_SPECIALDAYRATE                                 
-- ============================================================
drop table INT_SPECIALDAYRATE cascade constraints;

create table INT_SPECIALDAYRATE
(
    SPECIALDAYRATE           NUMBER(9)              not null,
    NAME                     VARCHAR2(30)           null    ,
    VALID_FROM               VARCHAR2(8)            not null,
    VALID_TO                 VARCHAR2(8)            null    ,
    TIME_FROM                VARCHAR2(5)            null    ,
    TIME_TO                  VARCHAR2(5)            null    ,
    DISCOUNT_TYPE            CHAR(1)                default 'P' not null
        constraint CKC_DISCOUNT_INT_SPECIALDAYRAT check (DISCOUNT_TYPE in ('P','A','N')),
    DISCOUNT_VALUE           NUMBER                 not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SPECIALDAYRAT check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SDR primary key (SPECIALDAYRATE)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_4_IDX
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
tablespace INTEGRATE_TS_4_DAT
storage
(
initial 512K
next 512K
minextents 1
maxextents unlimited
pctincrease 0
)
/
grant select, insert, update, delete on INT_SPECIALDAYRATE to INTEGRATE_ROLE_ALL
/
grant select on INT_SPECIALDAYRATE to INTEGRATE_ROLE_SEL
/

comment on table INT_SPECIALDAYRATE is 'definition of special day rates (discounts given for a tariff model)'
/

comment on column INT_SPECIALDAYRATE.SPECIALDAYRATE is 'unique specail day rate id'
/

comment on column INT_SPECIALDAYRATE.NAME is 'name or description'
/

comment on column INT_SPECIALDAYRATE.VALID_FROM is 'date for this special rate (if empty only the time is used) (Format: YYYYMMDD or MON-FRI[HH:MM]) (compare: >=)'
/

comment on column INT_SPECIALDAYRATE.VALID_TO is 'date for this special rate (if empty only the time is used) (Format: YYYYMMDD or MON-FRI[HH:MM]) (compare: <)'
/

comment on column INT_SPECIALDAYRATE.TIME_FROM is 'starting date and time for this special day rate (compare: >=)'
/

comment on column INT_SPECIALDAYRATE.TIME_TO is 'ending date and time for this special day rate (compare: <)'
/

comment on column INT_SPECIALDAYRATE.DISCOUNT_TYPE is 'type of the discount value (P=percantage, A=addon value, N=absolute new value)'
/

comment on column INT_SPECIALDAYRATE.DISCOUNT_VALUE is 'the discount value itself (content is related to DISCOUNT_TYPE)'
/

comment on column INT_SPECIALDAYRATE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SPECIALDAYRATE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SPECIALDAYRATE.MODIFBY is 'MODIFBY'
/

comment on column INT_SPECIALDAYRATE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SPECIALDAYRATE.MODIFIED is 'MODIFIED'
/

comment on column INT_SPECIALDAYRATE.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_PRICEMODEL                                     
-- ============================================================
drop table INT_PRICEMODEL cascade constraints;

create table INT_PRICEMODEL
(
    PRICEMODEL               NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_PRICEMODEL check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_PMD primary key (PRICEMODEL)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_4_IDX
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
buffer_pool keep
)
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_PRICEMODEL to INTEGRATE_ROLE_ALL
/
grant select on INT_PRICEMODEL to INTEGRATE_ROLE_SEL
/

comment on table INT_PRICEMODEL is 'price model definition (groups different rating steps)'
/

comment on column INT_PRICEMODEL.PRICEMODEL is 'unique price model id'
/

comment on column INT_PRICEMODEL.CODE is 'external code for this price model'
/

comment on column INT_PRICEMODEL.NAME is 'description'
/

comment on column INT_PRICEMODEL.ENTRYBY is 'ENTRYBY'
/

comment on column INT_PRICEMODEL.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_PRICEMODEL.MODIFBY is 'MODIFBY'
/

comment on column INT_PRICEMODEL.MODIFDATE is 'MODIFDATE'
/

comment on column INT_PRICEMODEL.MODIFIED is 'MODIFIED'
/

comment on column INT_PRICEMODEL.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_PMD                                         
-- ============================================================
create unique index AK_INT_PMD on INT_PRICEMODEL (CODE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_4_IDX
storage
(
initial 64K
next 64K
minextents 1
maxextents unlimited
pctincrease 0
)
/

-- ============================================================
--   Table: INT_ZONE                                           
-- ============================================================
drop table INT_ZONE cascade constraints;

create table INT_ZONE
(
    ZONE                     VARCHAR2(5)            not null,
    RESULT                   VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_ZONE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_ZON primary key (ZONE)
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
storage
(
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_3_DAT
/
grant select, insert, update, delete on INT_ZONE to INTEGRATE_ROLE_ALL
/
grant select on INT_ZONE to INTEGRATE_ROLE_SEL
/

comment on table INT_ZONE is 'zone codes (defines the result zone values)'
/

comment on column INT_ZONE.ZONE is 'internal zone id, uniquely defines a zone value reference'
/

comment on column INT_ZONE.RESULT is 'result value for the zone'
/

comment on column INT_ZONE.NAME is 'name or description of the defined zone'
/

comment on column INT_ZONE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_ZONE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_ZONE.MODIFBY is 'MODIFBY'
/

comment on column INT_ZONE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_ZONE.MODIFIED is 'MODIFIED'
/

comment on column INT_ZONE.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_ZON                                         
-- ============================================================
create unique index AK_INT_ZON on INT_ZONE (RESULT asc)
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
/

-- ============================================================
--   Table: INT_TIMEINTERVAL                                   
-- ============================================================
drop table INT_TIMEINTERVAL cascade constraints;

create table INT_TIMEINTERVAL
(
    INTERVAL                 NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    TIME_FROM                VARCHAR2(5)            null    ,
    TIME_TO                  VARCHAR2(5)            null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TIMEINTERVAL check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TII primary key (INTERVAL)
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
buffer_pool keep
)
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_TIMEINTERVAL to INTEGRATE_ROLE_ALL
/
grant select on INT_TIMEINTERVAL to INTEGRATE_ROLE_SEL
/

comment on table INT_TIMEINTERVAL is 'defines possible time intervals (e.g. peak, off-peak etc.)'
/

comment on column INT_TIMEINTERVAL.INTERVAL is 'unique interval id'
/

comment on column INT_TIMEINTERVAL.CODE is 'external code for this interval'
/

comment on column INT_TIMEINTERVAL.NAME is 'description'
/

comment on column INT_TIMEINTERVAL.TIME_FROM is 'lower boundary of the time interval (HH:MM) = starting time for this interval (compare: >=)'
/

comment on column INT_TIMEINTERVAL.TIME_TO is 'upper boundary of the time interval (HH:MM) = ending time for this interval (compare: <)'
/

comment on column INT_TIMEINTERVAL.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TIMEINTERVAL.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TIMEINTERVAL.MODIFBY is 'MODIFBY'
/

comment on column INT_TIMEINTERVAL.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TIMEINTERVAL.MODIFIED is 'MODIFIED'
/

comment on column INT_TIMEINTERVAL.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_TII                                         
-- ============================================================
create unique index AK_INT_TII on INT_TIMEINTERVAL (CODE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_4_IDX
storage
(
initial 64K
next 64K
minextents 1
maxextents unlimited
pctincrease 0
)
/

-- ============================================================
--   Table: INT_TIMEZONE                                       
-- ============================================================
drop table INT_TIMEZONE cascade constraints;

create table INT_TIMEZONE
(
    TIMEZONE                 NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    TIMEZONE_VALUE           VARCHAR2(2000)         null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TIMEZONE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TIZ primary key (TIMEZONE)
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
tablespace INTEGRATE_TS_4_DAT
storage
(
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
)
/
grant select, insert, update, delete on INT_TIMEZONE to INTEGRATE_ROLE_ALL
/
grant select on INT_TIMEZONE to INTEGRATE_ROLE_SEL
/

comment on table INT_TIMEZONE is 'time zone definition (groups a daycode, time interval combination)'
/

comment on column INT_TIMEZONE.TIMEZONE is 'unique time zone'
/

comment on column INT_TIMEZONE.CODE is 'external time zone code'
/

comment on column INT_TIMEZONE.NAME is 'description'
/

comment on column INT_TIMEZONE.TIMEZONE_VALUE is 'only the default definition of the timezone configuration'
/

comment on column INT_TIMEZONE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TIMEZONE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TIMEZONE.MODIFBY is 'MODIFBY'
/

comment on column INT_TIMEZONE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TIMEZONE.MODIFIED is 'MODIFIED'
/

comment on column INT_TIMEZONE.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_TIZ                                         
-- ============================================================
create unique index AK_INT_TIZ on INT_TIMEZONE (CODE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_4_IDX
storage
(
initial 64K
next 64K
minextents 1
maxextents unlimited
pctincrease 0
)
/

-- ============================================================
--   Table: INT_SEGMENT                                        
-- ============================================================
drop table INT_SEGMENT cascade constraints;

create table INT_SEGMENT
(
    SEGMENT                  VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SEGMENT check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SGM primary key (SEGMENT)
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
tablespace INTEGRATE_TS_1_DAT
storage
(
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
)
/
grant select, insert, update, delete on INT_SEGMENT to INTEGRATE_ROLE_ALL
/
grant select on INT_SEGMENT to INTEGRATE_ROLE_SEL
/

comment on table INT_SEGMENT is 'segments, groups subscribers in a vertical manner (customer-segmentation, foCust-related)'
/

comment on column INT_SEGMENT.SEGMENT is 'internal ID, a segment vertically groups multiple customers'
/

comment on column INT_SEGMENT.NAME is 'just a description for the segment'
/

comment on column INT_SEGMENT.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SEGMENT.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SEGMENT.MODIFBY is 'MODIFBY'
/

comment on column INT_SEGMENT.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SEGMENT.MODIFIED is 'MODIFIED'
/

comment on column INT_SEGMENT.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_EDRFORMAT                                      
-- ============================================================
drop table INT_EDRFORMAT cascade constraints;

create table INT_EDRFORMAT
(
    EDR_FORMAT               VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    SEQ_NUMBER               NUMBER(9)              null    ,
    SEQ_ORIGNUMBER           NUMBER(9)              null    ,
    SEQ_OFFSET               NUMBER(9)              null    ,
    SEQ_MAXSEQUENCE          NUMBER(9)              null    ,
    SEQ_MAXOFFSET            NUMBER(9)              null    ,
    SEQ_MINSEQUENCE          NUMBER(9)              null    ,
    SEQ_MINOFFSET            NUMBER(9)              null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_EDRFORMAT check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_EDR primary key (EDR_FORMAT)
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
buffer_pool keep
)
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_EDRFORMAT to INTEGRATE_ROLE_ALL
/
grant select on INT_EDRFORMAT to INTEGRATE_ROLE_SEL
/

comment on table INT_EDRFORMAT is 'edr format definition table, defines the possible logical edr formats that can be used'
/

comment on column INT_EDRFORMAT.EDR_FORMAT is 'unique logical edr format code'
/

comment on column INT_EDRFORMAT.NAME is 'name of the logical edr format'
/

comment on column INT_EDRFORMAT.SEQ_NUMBER is 'SEQ_NUMBER'
/

comment on column INT_EDRFORMAT.SEQ_ORIGNUMBER is 'SEQ_ORIGNUMBER'
/

comment on column INT_EDRFORMAT.SEQ_OFFSET is 'SEQ_OFFSET'
/

comment on column INT_EDRFORMAT.SEQ_MAXSEQUENCE is 'SEQ_MAXSEQUENCE'
/

comment on column INT_EDRFORMAT.SEQ_MAXOFFSET is 'SEQ_MAXOFFSET'
/

comment on column INT_EDRFORMAT.SEQ_MINSEQUENCE is 'SEQ_MINSEQUENCE'
/

comment on column INT_EDRFORMAT.SEQ_MINOFFSET is 'SEQ_MINOFFSET'
/

comment on column INT_EDRFORMAT.ENTRYBY is 'ENTRYBY'
/

comment on column INT_EDRFORMAT.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_EDRFORMAT.MODIFBY is 'MODIFBY'
/

comment on column INT_EDRFORMAT.MODIFDATE is 'MODIFDATE'
/

comment on column INT_EDRFORMAT.MODIFIED is 'MODIFIED'
/

comment on column INT_EDRFORMAT.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_GEOGRAPHICALMODEL                              
-- ============================================================
drop table INT_GEOGRAPHICALMODEL cascade constraints;

create table INT_GEOGRAPHICALMODEL
(
    GEOMODEL                 NUMBER(9)              not null,
    NAME                     VARCHAR2(30)           null    ,
    STATUS                   CHAR(1)                default 'A' not null
        constraint CKC_STATUS_INT_GEOGRAPHICALMO check (STATUS in ('A','D')),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_GEOGRAPHICALM check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_GMD primary key (GEOMODEL)
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
)
/
grant select, insert, update, delete on INT_GEOGRAPHICALMODEL to INTEGRATE_ROLE_ALL
/
grant select on INT_GEOGRAPHICALMODEL to INTEGRATE_ROLE_SEL
/

comment on table INT_GEOGRAPHICALMODEL is 'geographical model definition'
/

comment on column INT_GEOGRAPHICALMODEL.GEOMODEL is 'internal id, defines the geographical model id'
/

comment on column INT_GEOGRAPHICALMODEL.NAME is 'description'
/

comment on column INT_GEOGRAPHICALMODEL.STATUS is 'status of the model (A=active, D=deactive)'
/

comment on column INT_GEOGRAPHICALMODEL.ENTRYBY is 'ENTRYBY'
/

comment on column INT_GEOGRAPHICALMODEL.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_GEOGRAPHICALMODEL.MODIFBY is 'MODIFBY'
/

comment on column INT_GEOGRAPHICALMODEL.MODIFDATE is 'MODIFDATE'
/

comment on column INT_GEOGRAPHICALMODEL.MODIFIED is 'MODIFIED'
/

comment on column INT_GEOGRAPHICALMODEL.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_CALLCLASS                                      
-- ============================================================
drop table INT_CALLCLASS cascade constraints;

create table INT_CALLCLASS
(
    CALLCLASS                VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CALLCLASS check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CCL primary key (CALLCLASS)
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
buffer_pool keep
)
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_CALLCLASS to INTEGRATE_ROLE_ALL
/
grant select on INT_CALLCLASS to INTEGRATE_ROLE_SEL
/

comment on table INT_CALLCLASS is 'defines the internal callclass'
/

comment on column INT_CALLCLASS.CALLCLASS is 'unique call classification which can be used'
/

comment on column INT_CALLCLASS.NAME is 'description'
/

comment on column INT_CALLCLASS.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CALLCLASS.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CALLCLASS.MODIFBY is 'MODIFBY'
/

comment on column INT_CALLCLASS.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CALLCLASS.MODIFIED is 'MODIFIED'
/

comment on column INT_CALLCLASS.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_CALENDAR                                       
-- ============================================================
drop table INT_CALENDAR cascade constraints;

create table INT_CALENDAR
(
    CALENDAR                 NUMBER(9)              not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CALENDAR check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CAL primary key (CALENDAR)
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
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_CALENDAR to INTEGRATE_ROLE_ALL
/
grant select on INT_CALENDAR to INTEGRATE_ROLE_SEL
/

comment on table INT_CALENDAR is 'defines a holiday calendar'
/

comment on column INT_CALENDAR.CALENDAR is 'unique calendar id'
/

comment on column INT_CALENDAR.NAME is 'description'
/

comment on column INT_CALENDAR.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CALENDAR.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CALENDAR.MODIFBY is 'MODIFBY'
/

comment on column INT_CALENDAR.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CALENDAR.MODIFIED is 'MODIFIED'
/

comment on column INT_CALENDAR.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SYSTEM_BRAND                                   
-- ============================================================
drop table INT_SYSTEM_BRAND cascade constraints;

create table INT_SYSTEM_BRAND
(
    SYSTEM_BRAND             VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ACTIVE                   NUMBER(1)              default 0 not null
        constraint CKC_ACTIVE_INT_SYSTEM_BRAND check (ACTIVE in (0,1)),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SYSTEM_BRAND check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SYB primary key (SYSTEM_BRAND)
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
buffer_pool keep
)
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_SYSTEM_BRAND to INTEGRATE_ROLE_ALL
/
grant select on INT_SYSTEM_BRAND to INTEGRATE_ROLE_SEL
/

comment on table INT_SYSTEM_BRAND is 'defines the different systems used for branding, labeling or splitting'
/

comment on column INT_SYSTEM_BRAND.SYSTEM_BRAND is 'unique specialistsystem id'
/

comment on column INT_SYSTEM_BRAND.NAME is 'description'
/

comment on column INT_SYSTEM_BRAND.ACTIVE is 'is this specialistsystem active (1=yes, 0=no)'
/

comment on column INT_SYSTEM_BRAND.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SYSTEM_BRAND.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SYSTEM_BRAND.MODIFBY is 'MODIFBY'
/

comment on column INT_SYSTEM_BRAND.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SYSTEM_BRAND.MODIFIED is 'MODIFIED'
/

comment on column INT_SYSTEM_BRAND.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_DISCOUNTMODEL                                  
-- ============================================================
drop table INT_DISCOUNTMODEL cascade constraints;

create table INT_DISCOUNTMODEL
(
    DISCOUNTMODEL            NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    PERIOD                   NUMBER(2)              default 1 not null
        constraint CKC_PERIOD_INT_DISCOUNTMODEL check (PERIOD between 1 and 12),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_DISCOUNTMODEL check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DML primary key (DISCOUNTMODEL)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_DISCOUNTMODEL to INTEGRATE_ROLE_ALL
/
grant select on INT_DISCOUNTMODEL to INTEGRATE_ROLE_SEL
/

comment on table INT_DISCOUNTMODEL is 'defines the volume or quantity based discount models'
/

comment on column INT_DISCOUNTMODEL.DISCOUNTMODEL is 'unique discount model identifier'
/

comment on column INT_DISCOUNTMODEL.CODE is 'unique external code for this discount model'
/

comment on column INT_DISCOUNTMODEL.NAME is 'description name of the discount model'
/

comment on column INT_DISCOUNTMODEL.PERIOD is 'defines the discount period (1=monthly, 2=2month, 3=3month,..,12=yearly)'
/

comment on column INT_DISCOUNTMODEL.ENTRYBY is 'ENTRYBY'
/

comment on column INT_DISCOUNTMODEL.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_DISCOUNTMODEL.MODIFBY is 'MODIFBY'
/

comment on column INT_DISCOUNTMODEL.MODIFDATE is 'MODIFDATE'
/

comment on column INT_DISCOUNTMODEL.MODIFIED is 'MODIFIED'
/

comment on column INT_DISCOUNTMODEL.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_DML                                         
-- ============================================================
create unique index AK_INT_DML on INT_DISCOUNTMODEL (CODE asc)
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
/

-- ============================================================
--   Table: INT_DISCOUNTRULE                                   
-- ============================================================
drop table INT_DISCOUNTRULE cascade constraints;

create table INT_DISCOUNTRULE
(
    DISCOUNTRULE             NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_DISCOUNTRULE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DCR primary key (DISCOUNTRULE)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_DISCOUNTRULE to INTEGRATE_ROLE_ALL
/
grant select on INT_DISCOUNTRULE to INTEGRATE_ROLE_SEL
/

comment on table INT_DISCOUNTRULE is 'defines a set of discount steps'
/

comment on column INT_DISCOUNTRULE.DISCOUNTRULE is 'unique id, defining a discount rule'
/

comment on column INT_DISCOUNTRULE.CODE is 'external code for a discount rule'
/

comment on column INT_DISCOUNTRULE.NAME is 'name or description'
/

comment on column INT_DISCOUNTRULE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_DISCOUNTRULE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_DISCOUNTRULE.MODIFBY is 'MODIFBY'
/

comment on column INT_DISCOUNTRULE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_DISCOUNTRULE.MODIFIED is 'MODIFIED'
/

comment on column INT_DISCOUNTRULE.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_DCR                                         
-- ============================================================
create unique index AK_INT_DCR on INT_DISCOUNTRULE (CODE asc)
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
/

-- ============================================================
--   Table: INT_DISCOUNTMASTER                                 
-- ============================================================
drop table INT_DISCOUNTMASTER cascade constraints;

create table INT_DISCOUNTMASTER
(
    DISCOUNTMASTER           NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_DISCOUNTMASTE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DCM primary key (DISCOUNTMASTER)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_DISCOUNTMASTER to INTEGRATE_ROLE_ALL
/
grant select on INT_DISCOUNTMASTER to INTEGRATE_ROLE_SEL
/

comment on table INT_DISCOUNTMASTER is 'the discountmaster defines a set of discount conditions'
/

comment on column INT_DISCOUNTMASTER.DISCOUNTMASTER is 'unique internal id'
/

comment on column INT_DISCOUNTMASTER.CODE is 'unique external code or short reference'
/

comment on column INT_DISCOUNTMASTER.NAME is 'name or description'
/

comment on column INT_DISCOUNTMASTER.ENTRYBY is 'ENTRYBY'
/

comment on column INT_DISCOUNTMASTER.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_DISCOUNTMASTER.MODIFBY is 'MODIFBY'
/

comment on column INT_DISCOUNTMASTER.MODIFDATE is 'MODIFDATE'
/

comment on column INT_DISCOUNTMASTER.MODIFIED is 'MODIFIED'
/

comment on column INT_DISCOUNTMASTER.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_DCM                                         
-- ============================================================
create unique index AK_INT_DCM on INT_DISCOUNTMASTER (CODE asc)
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
/

-- ============================================================
--   Table: INT_SUBS_BILLCYCLE                                 
-- ============================================================
drop table INT_SUBS_BILLCYCLE cascade constraints;

create table INT_SUBS_BILLCYCLE
(
    BILLCYCLE                VARCHAR2(2)            not null,
    END_OF_CYCLE             NUMBER(2)              default 1 not null
        constraint CKC_END_OF_C_INT_SUBS_BILLCYCL check (END_OF_CYCLE between 1 and 31),
    BILLPERIOD               NUMBER(2)              default 1 not null
        constraint CKC_BILLPERI_INT_SUBS_BILLCYCL check (BILLPERIOD in (1,2,3,6,12)),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SUBS_BILLCYCL check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SBC primary key (BILLCYCLE)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_SUBS_BILLCYCLE to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBS_BILLCYCLE to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBS_BILLCYCLE is 'defines the possible billcycles for subscriber related billing'
/

comment on column INT_SUBS_BILLCYCLE.BILLCYCLE is 'unique billcycle identifier'
/

comment on column INT_SUBS_BILLCYCLE.END_OF_CYCLE is 'end of cycle day, defines the last day within the billcycle period (e.g. 04=forth day of a month)'
/

comment on column INT_SUBS_BILLCYCLE.BILLPERIOD is 'defines the period for the cycle (e.g. 1=monthly, 2=every two month, 3=quaterly, 6=half a year, 12=yearly)'
/

comment on column INT_SUBS_BILLCYCLE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SUBS_BILLCYCLE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SUBS_BILLCYCLE.MODIFBY is 'MODIFBY'
/

comment on column INT_SUBS_BILLCYCLE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SUBS_BILLCYCLE.MODIFIED is 'MODIFIED'
/

comment on column INT_SUBS_BILLCYCLE.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_CALLTYPE                                       
-- ============================================================
drop table INT_CALLTYPE cascade constraints;

create table INT_CALLTYPE
(
    CALLTYPE                 VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CALLTYPE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CTP primary key (CALLTYPE)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_1_IDX
        storage
        (
        initial 8K
        next 8K
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
initial 32K
next 32K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_CALLTYPE to INTEGRATE_ROLE_ALL
/
grant select on INT_CALLTYPE to INTEGRATE_ROLE_SEL
/

comment on table INT_CALLTYPE is 'call type definition table'
/

comment on column INT_CALLTYPE.CALLTYPE is 'unique call type code'
/

comment on column INT_CALLTYPE.NAME is 'name of the call type'
/

comment on column INT_CALLTYPE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CALLTYPE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CALLTYPE.MODIFBY is 'MODIFBY'
/

comment on column INT_CALLTYPE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CALLTYPE.MODIFIED is 'MODIFIED'
/

comment on column INT_CALLTYPE.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_DISCOUNTTRIGGER                                
-- ============================================================
drop table INT_DISCOUNTTRIGGER cascade constraints;

create table INT_DISCOUNTTRIGGER
(
    DISCOUNTTRIGGER          NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_DISCOUNTTRIGG check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DTR primary key (DISCOUNTTRIGGER)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_DISCOUNTTRIGGER to INTEGRATE_ROLE_ALL
/
grant select on INT_DISCOUNTTRIGGER to INTEGRATE_ROLE_SEL
/

comment on table INT_DISCOUNTTRIGGER is 'defines a set of discount conditions'
/

comment on column INT_DISCOUNTTRIGGER.DISCOUNTTRIGGER is 'DISCOUNTTRIGGER'
/

comment on column INT_DISCOUNTTRIGGER.CODE is 'unique external code or short reference'
/

comment on column INT_DISCOUNTTRIGGER.NAME is 'name or description'
/

comment on column INT_DISCOUNTTRIGGER.ENTRYBY is 'ENTRYBY'
/

comment on column INT_DISCOUNTTRIGGER.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_DISCOUNTTRIGGER.MODIFBY is 'MODIFBY'
/

comment on column INT_DISCOUNTTRIGGER.MODIFDATE is 'MODIFDATE'
/

comment on column INT_DISCOUNTTRIGGER.MODIFIED is 'MODIFIED'
/

comment on column INT_DISCOUNTTRIGGER.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_RULESET                                        
-- ============================================================
-- do not drop this table because no changes.


-- ============================================================
--   Table: INT_RULE                                           
-- ============================================================
-- do not copy this table because no changes.


-- ============================================================
--   Table: AGG_SCENARIO                                       
-- ============================================================
drop table AGG_SCENARIO cascade constraints;

create table AGG_SCENARIO
(
    SCENARIO_ID              NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(35)           null    ,
    VALID_FROM               DATE                   null    ,
    VALID_TO                 DATE                   null    ,
    DEFAULT_TAB_NAME         VARCHAR2(30)           default 'TAB_NAME' not null,
    DEFAULT_FLUSHMODE        NUMBER(1)              default 0 not null
        constraint CKC_DEFAULT__AGG_SCENARIO check (DEFAULT_FLUSHMODE in (0,1,2,3)),
    DEFAULT_THRESHOLD        NUMBER(9)              default 100000 not null,
    DEFAULT_TEMP_DIR         VARCHAR2(254)          default '.' not null,
    DEFAULT_DONE_DIR         VARCHAR2(254)          default '.' not null,
    DEFAULT_CTL_DIR          VARCHAR2(254)          default '.' not null,
    DEFAULT_FIELD_DELIMITER  CHAR(1)                default ';' not null,
    SCENARIO_STATUS          NUMBER(1)              default 0 not null
        constraint CKC_SCENARIO_AGG_SCENARIO check (SCENARIO_STATUS in (0,1)),
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_AGG_SCENARIO check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_AGG_SCENARIO primary key (SCENARIO_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_SCENARIO to INTEGRATE_ROLE_ALL
/
grant select on AGG_SCENARIO to INTEGRATE_ROLE_SEL
/

comment on table AGG_SCENARIO is 'AGG_SCENARIO'
/

comment on column AGG_SCENARIO.SCENARIO_ID is 'Internal ID => Generated by sequence ''AGG_SCENARIO_SEQ'''
/

comment on column AGG_SCENARIO.CODE is 'External Code. Could be used as Alternate Key'
/

comment on column AGG_SCENARIO.NAME is 'External Name / Description'
/

comment on column AGG_SCENARIO.VALID_FROM is 'VALID_FROM'
/

comment on column AGG_SCENARIO.VALID_TO is 'VALID_TO'
/

comment on column AGG_SCENARIO.DEFAULT_TAB_NAME is 'Default Tablename defined for a scenario'
/

comment on column AGG_SCENARIO.DEFAULT_FLUSHMODE is 'Defines the flushing strategy for the FCT-aggregate'
/

comment on column AGG_SCENARIO.DEFAULT_THRESHOLD is 'Default threshold value which defines the max amount of internal entries for an aggregate scenario'
/

comment on column AGG_SCENARIO.DEFAULT_TEMP_DIR is 'Default Path for the temporary aggregation results'
/

comment on column AGG_SCENARIO.DEFAULT_DONE_DIR is 'Default Path for the aggregation results'
/

comment on column AGG_SCENARIO.DEFAULT_CTL_DIR is 'Default Path for Controlfiles'
/

comment on column AGG_SCENARIO.DEFAULT_FIELD_DELIMITER is 'Default Fielddelimiter used to delimit the fields in aggregation results'
/

comment on column AGG_SCENARIO.SCENARIO_STATUS is 'Boolean Flag which specifies whether the scenario is currently active (will be used) or not.'
/

comment on column AGG_SCENARIO.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column AGG_SCENARIO.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column AGG_SCENARIO.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column AGG_SCENARIO.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column AGG_SCENARIO.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column AGG_SCENARIO.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: IDX_AGG_SCENARIO_NAME                              
-- ============================================================
create index IDX_AGG_SCENARIO_NAME on AGG_SCENARIO (NAME asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Index: AK_AGG_SCENARIO_CODE                               
-- ============================================================
create unique index AK_AGG_SCENARIO_CODE on AGG_SCENARIO (CODE asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Index: BIDX_AGG_SCENARIO_STATUS                           
-- ============================================================
create index BIDX_AGG_SCENARIO_STATUS on AGG_SCENARIO (SCENARIO_STATUS asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: AGG_CLASSITEM                                      
-- ============================================================
drop table AGG_CLASSITEM cascade constraints;

create table AGG_CLASSITEM
(
    CLASSITEM_ID             NUMBER(9)              not null,
    CODE                     VARCHAR2(20)           not null,
    NAME                     VARCHAR2(35)           null    ,
    CLASSITEM_DATATYPE       NUMBER(1)              not null
        constraint CKC_CLASSITE_AGG_CLASSITEM check (CLASSITEM_DATATYPE in (0,1,2)),
    CLASSITEM_VALUE          VARCHAR2(2000)         not null,
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_AGG_CLASSITEM check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_AGG_CLASSITEM primary key (CLASSITEM_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_CLASSITEM to INTEGRATE_ROLE_ALL
/
grant select on AGG_CLASSITEM to INTEGRATE_ROLE_SEL
/

comment on table AGG_CLASSITEM is 'Defines the individual classes'
/

comment on column AGG_CLASSITEM.CLASSITEM_ID is 'Internal ID => Generated by sequence ''AGG_CLASSITEM_SEQ'''
/

comment on column AGG_CLASSITEM.CODE is 'External Code. Could be used as Alternate Key'
/

comment on column AGG_CLASSITEM.NAME is 'External Name / Description'
/

comment on column AGG_CLASSITEM.CLASSITEM_DATATYPE is 'Datatype of the result values for a grouping column'
/

comment on column AGG_CLASSITEM.CLASSITEM_VALUE is 'lexical pattern to describe the classitem, this attribute contains the real value to check for'
/

comment on column AGG_CLASSITEM.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column AGG_CLASSITEM.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column AGG_CLASSITEM.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column AGG_CLASSITEM.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column AGG_CLASSITEM.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column AGG_CLASSITEM.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: IDX_AGG_CLASSITEM_NAME                             
-- ============================================================
create index IDX_AGG_CLASSITEM_NAME on AGG_CLASSITEM (NAME asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Index: AK_AGG_CLASSITEM_CODE                              
-- ============================================================
create unique index AK_AGG_CLASSITEM_CODE on AGG_CLASSITEM (CODE asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: AGG_CLASS                                          
-- ============================================================
drop table AGG_CLASS cascade constraints;

create table AGG_CLASS
(
    CLASS_ID                 NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(35)           null    ,
    CLASS_DATATYPE           NUMBER(1)              default 0 not null
        constraint CKC_CLASS_DA_AGG_CLASS check (CLASS_DATATYPE in (0,1,2)),
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_AGG_CLASS check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_AGG_CLASS primary key (CLASS_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_CLASS to INTEGRATE_ROLE_ALL
/
grant select on AGG_CLASS to INTEGRATE_ROLE_SEL
/

comment on table AGG_CLASS is 'This table holds all information about classes that are build by the user as grouping for all individual classitems'
/

comment on column AGG_CLASS.CLASS_ID is 'Internal ID => Generated by sequence ''AGG_CLASS_SEQ'''
/

comment on column AGG_CLASS.CODE is 'External Code. Could be used as Alternate Key'
/

comment on column AGG_CLASS.NAME is 'External Name / Description'
/

comment on column AGG_CLASS.CLASS_DATATYPE is 'Datatype of the result values for a grouping column'
/

comment on column AGG_CLASS.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column AGG_CLASS.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column AGG_CLASS.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column AGG_CLASS.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column AGG_CLASS.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column AGG_CLASS.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: IDX_AGG_CLASS_NAME                                 
-- ============================================================
create index IDX_AGG_CLASS_NAME on AGG_CLASS (NAME asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Index: AK_AGG_CLASS_CODE                                  
-- ============================================================
create unique index AK_AGG_CLASS_CODE on AGG_CLASS (CODE asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: AGG_EDRFORMAT                                      
-- ============================================================
drop table AGG_EDRFORMAT cascade constraints;

create table AGG_EDRFORMAT
(
    FORMAT_ID                NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(35)           null    ,
    EDRFORMAT_STATUS         NUMBER(1)              default 0 not null
        constraint CKC_EDRFORMA_AGG_EDRFORMAT check (EDRFORMAT_STATUS in (0,1)),
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_AGG_EDRFORMAT check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_AGG_EDRFORMAT primary key (FORMAT_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_EDRFORMAT to INTEGRATE_ROLE_ALL
/
grant select on AGG_EDRFORMAT to INTEGRATE_ROLE_SEL
/

comment on table AGG_EDRFORMAT is 'Defines all attributes to describe a formatpipline'
/

comment on column AGG_EDRFORMAT.FORMAT_ID is 'Internal ID => Generated by sequence ''AGG_EDRFORMAT_SEQ'''
/

comment on column AGG_EDRFORMAT.CODE is 'External Code. Could be used as Alternate Key'
/

comment on column AGG_EDRFORMAT.NAME is 'External Name / Description'
/

comment on column AGG_EDRFORMAT.EDRFORMAT_STATUS is 'Boolean Flag which specifies whether the edr-format is currently active (will be used) or not.'
/

comment on column AGG_EDRFORMAT.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column AGG_EDRFORMAT.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column AGG_EDRFORMAT.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column AGG_EDRFORMAT.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column AGG_EDRFORMAT.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column AGG_EDRFORMAT.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: AK_AGG_EDRFORMAT_CODE                              
-- ============================================================
create unique index AK_AGG_EDRFORMAT_CODE on AGG_EDRFORMAT (CODE asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: SOL_OBJS                                           
-- ============================================================
drop table SOL_OBJS cascade constraints;

create table SOL_OBJS
(
    OBJ_ID                   NUMBER(9)              not null,
    OWNER                    VARCHAR2(35)           not null,
    NAME                     VARCHAR2(35)           null    ,
    DESCRIPTION              VARCHAR2(254)          null    ,
    OBJ_TYPE                 NUMBER(2)              not null
        constraint CKC_OBJ_TYPE_SOL_OBJS check (OBJ_TYPE in (0,1,2,3,5,6,7)),
    OBJ_STATUS               NUMBER(2)              not null
        constraint CKC_OBJ_STAT_SOL_OBJS check (OBJ_STATUS in (0,1)),
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_SOL_OBJS check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_SOL_OBJS primary key (OBJ_ID)
        using index
     tablespace SOL_TS_1_IDX
)
tablespace SOL_TS_1_DAT
/
grant select, insert, update, delete on SOL_OBJS to INTEGRATE_ROLE_ALL
/
grant select on SOL_OBJS to INTEGRATE_ROLE_SEL
/

comment on table SOL_OBJS is 'SOL_OBJS'
/

comment on column SOL_OBJS.OBJ_ID is 'Internal ID => Generated by sequence ''SOL_OBJS_SEQ'''
/

comment on column SOL_OBJS.OWNER is 'Specifies the owner of the object. Value depends on OBJ_TYPE. TABLE/VIEW=> Table Owner, COLUMN/EXPRESSION=> Name of Parent Table'
/

comment on column SOL_OBJS.NAME is 'External Name / Description'
/

comment on column SOL_OBJS.DESCRIPTION is 'Description for the object'
/

comment on column SOL_OBJS.OBJ_TYPE is 'Describes the type of object, i.g.table, view, column,.....'
/

comment on column SOL_OBJS.OBJ_STATUS is 'Flag, determines whether Object is active (TRUE=1) or not(FALSE=0)'
/

comment on column SOL_OBJS.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column SOL_OBJS.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column SOL_OBJS.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column SOL_OBJS.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column SOL_OBJS.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column SOL_OBJS.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: IDX_SOL_OBJS_OWNER_NAME                            
-- ============================================================
create unique index IDX_SOL_OBJS_OWNER_NAME on SOL_OBJS (OBJ_ID asc, OWNER asc, NAME asc, OBJ_TYPE asc)
tablespace SOL_TS_1_IDX
/

-- ============================================================
--   Index: BIDX_SOL_OBJS_TYPE                                 
-- ============================================================
create index BIDX_SOL_OBJS_TYPE on SOL_OBJS (OBJ_TYPE asc)
tablespace SOL_TS_1_IDX
/

-- ============================================================
--   Index: BIDX_SOL_OBJS_STATUS                               
-- ============================================================
create index BIDX_SOL_OBJS_STATUS on SOL_OBJS (OBJ_STATUS asc)
tablespace SOL_TS_1_IDX
/

-- ============================================================
--   Table: AGG_REFERENCESET                                   
-- ============================================================
drop table AGG_REFERENCESET cascade constraints;

create table AGG_REFERENCESET
(
    REFERENCESET_ID          NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(35)           null    ,
    REFERENCESET_STATUS      NUMBER(1)              default 0 not null
        constraint CKC_REFERENC_AGG_REFERENCESET check (REFERENCESET_STATUS in (0,1)),
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_AGG_REFERENCESET check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_AGG_REFERENCESET primary key (REFERENCESET_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_REFERENCESET to INTEGRATE_ROLE_ALL
/
grant select on AGG_REFERENCESET to INTEGRATE_ROLE_SEL
/

comment on table AGG_REFERENCESET is 'Defines sets of referencedata'
/

comment on column AGG_REFERENCESET.REFERENCESET_ID is 'Internal ID => Generated by sequence ''AGG_REFERENCESET_SEQ'''
/

comment on column AGG_REFERENCESET.CODE is 'External Code. Could be used as Alternate Key'
/

comment on column AGG_REFERENCESET.NAME is 'External Name / Description'
/

comment on column AGG_REFERENCESET.REFERENCESET_STATUS is 'Boolean Flag which specifies whether the referenceser is currently active (will be used) or not.'
/

comment on column AGG_REFERENCESET.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column AGG_REFERENCESET.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column AGG_REFERENCESET.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column AGG_REFERENCESET.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column AGG_REFERENCESET.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column AGG_REFERENCESET.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: AK_AGG_REFERENCESET_CODE                           
-- ============================================================
create index AK_AGG_REFERENCESET_CODE on AGG_REFERENCESET (CODE asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: SOL_SECTION                                        
-- ============================================================
drop table SOL_SECTION cascade constraints;

create table SOL_SECTION
(
    SECTION                  VARCHAR2(10)           not null,
    NAME                     VARCHAR2(254)          not null,
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_SOL_SECTION check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_SOL_SECTION primary key (SECTION)
        using index
     tablespace SOL_TS_1_IDX
)
tablespace SOL_TS_1_DAT
/
grant select, insert, update, delete on SOL_SECTION to INTEGRATE_ROLE_ALL
/
grant select on SOL_SECTION to INTEGRATE_ROLE_SEL
/

comment on table SOL_SECTION is 'SOL_SECTION'
/

comment on column SOL_SECTION.SECTION is 'SECTION'
/

comment on column SOL_SECTION.NAME is 'External Name / Description'
/

comment on column SOL_SECTION.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column SOL_SECTION.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column SOL_SECTION.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column SOL_SECTION.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column SOL_SECTION.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column SOL_SECTION.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Table: SOL_UNITS                                          
-- ============================================================
drop table SOL_UNITS cascade constraints;

create table SOL_UNITS
(
    UNIT_ID                  NUMBER(9)              not null,
    NAME                     VARCHAR2(35)           null    ,
    DESCRIPTION              VARCHAR2(254)          null    ,
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_SOL_UNITS check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_SOL_UNITS primary key (UNIT_ID)
        using index
     tablespace SOL_TS_1_IDX
)
tablespace SOL_TS_1_DAT
/
grant select, insert, update, delete on SOL_UNITS to INTEGRATE_ROLE_ALL
/
grant select on SOL_UNITS to INTEGRATE_ROLE_SEL
/

comment on table SOL_UNITS is 'defines all avalaible units'
/

comment on column SOL_UNITS.UNIT_ID is 'UNIT_ID'
/

comment on column SOL_UNITS.NAME is 'External Name / Description'
/

comment on column SOL_UNITS.DESCRIPTION is 'DESCRIPTION'
/

comment on column SOL_UNITS.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column SOL_UNITS.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column SOL_UNITS.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column SOL_UNITS.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column SOL_UNITS.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column SOL_UNITS.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: IDX_SOL_UNITS_NAME                                 
-- ============================================================
create index IDX_SOL_UNITS_NAME on SOL_UNITS (NAME asc)
tablespace SOL_TS_1_IDX
/

-- ============================================================
--   Table: AGG_QUEUE                                          
-- ============================================================
drop table AGG_QUEUE cascade constraints;

create table AGG_QUEUE
(
    IMPORT_TABLE             VARCHAR2(30)           not null,
    DESTINATION_TABLE        VARCHAR2(30)           not null,
    STATUS                   CHAR(1)                default 'O' not null
        constraint CKC_STATUS_AGG_QUEUE check (STATUS in ('O','L', 'C','A','E','D')),
    ENTRY_DATE               DATE                   default SYSDATE not null,
    constraint PK_AGG_QUEUE primary key (IMPORT_TABLE)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_QUEUE to INTEGRATE_ROLE_ALL
/
grant select on AGG_QUEUE to INTEGRATE_ROLE_SEL
/

comment on table AGG_QUEUE is 'interface between sqlLoader and sqlAggregator'
/

comment on column AGG_QUEUE.IMPORT_TABLE is 'name of the import table'
/

comment on column AGG_QUEUE.DESTINATION_TABLE is 'name of the destination table'
/

comment on column AGG_QUEUE.STATUS is 'status of the import table (''O''pen, ''L''oading, ''C''losed, ''A''ggregating, ''D''ropped, ''E''rror)'
/

comment on column AGG_QUEUE.ENTRY_DATE is 'entry date of the import table'
/


-- ============================================================
--   Table: INT_CZT_GROUP                                      
-- ============================================================
drop table INT_CZT_GROUP cascade constraints;

create table INT_CZT_GROUP
(
    CZT_GROUP                VARCHAR2(10)           not null,
    CZT_NAME                 VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CZT_GROUP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CMG primary key (CZT_GROUP)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_CZT_GROUP to INTEGRATE_ROLE_ALL
/
grant select on INT_CZT_GROUP to INTEGRATE_ROLE_SEL
/

comment on table INT_CZT_GROUP is 'Definition of CZT-Mapping Groups'
/

comment on column INT_CZT_GROUP.CZT_GROUP is 'unique czt-mapping group code'
/

comment on column INT_CZT_GROUP.CZT_NAME is 'name or description'
/

comment on column INT_CZT_GROUP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CZT_GROUP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CZT_GROUP.MODIFBY is 'MODIFBY'
/

comment on column INT_CZT_GROUP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CZT_GROUP.MODIFIED is 'MODIFIED'
/

comment on column INT_CZT_GROUP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_MAP_GROUP                                      
-- ============================================================
drop table INT_MAP_GROUP cascade constraints;

create table INT_MAP_GROUP
(
    MAP_GROUP                VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_MAP_GROUP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_MGR primary key (MAP_GROUP)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_MAP_GROUP to INTEGRATE_ROLE_ALL
/
grant select on INT_MAP_GROUP to INTEGRATE_ROLE_SEL
/

comment on table INT_MAP_GROUP is 'definition mapping groups'
/

comment on column INT_MAP_GROUP.MAP_GROUP is 'unique mapping group code'
/

comment on column INT_MAP_GROUP.NAME is 'name or description'
/

comment on column INT_MAP_GROUP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_MAP_GROUP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_MAP_GROUP.MODIFBY is 'MODIFBY'
/

comment on column INT_MAP_GROUP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_MAP_GROUP.MODIFIED is 'MODIFIED'
/

comment on column INT_MAP_GROUP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_TSC_GROUP                                      
-- ============================================================
drop table INT_TSC_GROUP cascade constraints;

create table INT_TSC_GROUP
(
    TSC_GROUP                VARCHAR2(10)           not null,
    TSC_NAME                 VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TSC_GROUP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TMG primary key (TSC_GROUP)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_TSC_GROUP to INTEGRATE_ROLE_ALL
/
grant select on INT_TSC_GROUP to INTEGRATE_ROLE_SEL
/

comment on table INT_TSC_GROUP is 'Definition of TSC-Mapping Groups'
/

comment on column INT_TSC_GROUP.TSC_GROUP is 'unque TSC mapping group code'
/

comment on column INT_TSC_GROUP.TSC_NAME is 'name or description'
/

comment on column INT_TSC_GROUP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TSC_GROUP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TSC_GROUP.MODIFBY is 'MODIFBY'
/

comment on column INT_TSC_GROUP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TSC_GROUP.MODIFIED is 'MODIFIED'
/

comment on column INT_TSC_GROUP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_APN_GROUP                                      
-- ============================================================
drop table INT_APN_GROUP cascade constraints;

create table INT_APN_GROUP
(
    APN_GROUP                VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_APN_GROUP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_APG primary key (APN_GROUP)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_APN_GROUP to INTEGRATE_ROLE_ALL
/
grant select on INT_APN_GROUP to INTEGRATE_ROLE_SEL
/

comment on table INT_APN_GROUP is 'definition of access-point-name groups'
/

comment on column INT_APN_GROUP.APN_GROUP is 'unique APN group code'
/

comment on column INT_APN_GROUP.NAME is 'name or description'
/

comment on column INT_APN_GROUP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_APN_GROUP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_APN_GROUP.MODIFBY is 'MODIFBY'
/

comment on column INT_APN_GROUP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_APN_GROUP.MODIFIED is 'MODIFIED'
/

comment on column INT_APN_GROUP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_UOM                                            
-- ============================================================
drop table INT_UOM cascade constraints;

create table INT_UOM
(
    UOM                      VARCHAR2(3)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 DATE                   default sysdate null    ,
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_UOM primary key (UOM)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_UOM to INTEGRATE_ROLE_ALL
/
grant select on INT_UOM to INTEGRATE_ROLE_SEL
/

comment on table INT_UOM is 'defines possible Units of Measurement'
/

comment on column INT_UOM.UOM is 'defines a possible Unit of Measurement code (3-characters uppercase, e.g. SEC, BYT, CLK)'
/

comment on column INT_UOM.NAME is 'name or description'
/

comment on column INT_UOM.ENTRYBY is 'ENTRYBY'
/

comment on column INT_UOM.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_UOM.MODIFBY is 'MODIFBY'
/

comment on column INT_UOM.MODIFDATE is 'MODIFDATE'
/

comment on column INT_UOM.MODIFIED is 'MODIFIED'
/

comment on column INT_UOM.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_TAXGROUP                                       
-- ============================================================
drop table INT_TAXGROUP cascade constraints;

create table INT_TAXGROUP
(
    TAXGROUP                 VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TAXGROUP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TXG primary key (TAXGROUP)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_TAXGROUP to INTEGRATE_ROLE_ALL
/
grant select on INT_TAXGROUP to INTEGRATE_ROLE_SEL
/

comment on table INT_TAXGROUP is 'defines all possible customer related tax groups (e.g. normal tax, no-tax etc.)'
/

comment on column INT_TAXGROUP.TAXGROUP is 'unique tax group related to a specifc group of customers to handle specific taxation'
/

comment on column INT_TAXGROUP.NAME is 'name or description'
/

comment on column INT_TAXGROUP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TAXGROUP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TAXGROUP.MODIFBY is 'MODIFBY'
/

comment on column INT_TAXGROUP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TAXGROUP.MODIFIED is 'MODIFIED'
/

comment on column INT_TAXGROUP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_TAXCODE                                        
-- ============================================================
drop table INT_TAXCODE cascade constraints;

create table INT_TAXCODE
(
    TAXCODE                  VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TAXCODE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TXC primary key (TAXCODE)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_TAXCODE to INTEGRATE_ROLE_ALL
/
grant select on INT_TAXCODE to INTEGRATE_ROLE_SEL
/

comment on table INT_TAXCODE is 'defines all possible tax codes'
/

comment on column INT_TAXCODE.TAXCODE is 'defines all possible tax codes (e.g. high, reduced, no tax)'
/

comment on column INT_TAXCODE.NAME is 'name or description'
/

comment on column INT_TAXCODE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TAXCODE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TAXCODE.MODIFBY is 'MODIFBY'
/

comment on column INT_TAXCODE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TAXCODE.MODIFIED is 'MODIFIED'
/

comment on column INT_TAXCODE.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_REVENUEGROUP                                   
-- ============================================================
drop table INT_REVENUEGROUP cascade constraints;

create table INT_REVENUEGROUP
(
    REVENUEGROUP             VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_REVENUEGROUP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_RVG primary key (REVENUEGROUP)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_REVENUEGROUP to INTEGRATE_ROLE_ALL
/
grant select on INT_REVENUEGROUP to INTEGRATE_ROLE_SEL
/

comment on table INT_REVENUEGROUP is 'defines possible revenue groups (for splitted billing)'
/

comment on column INT_REVENUEGROUP.REVENUEGROUP is 'unique revenue group code'
/

comment on column INT_REVENUEGROUP.NAME is 'name or description'
/

comment on column INT_REVENUEGROUP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_REVENUEGROUP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_REVENUEGROUP.MODIFBY is 'MODIFBY'
/

comment on column INT_REVENUEGROUP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_REVENUEGROUP.MODIFIED is 'MODIFIED'
/

comment on column INT_REVENUEGROUP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_CURRENCY                                       
-- ============================================================
drop table INT_CURRENCY cascade constraints;

create table INT_CURRENCY
(
    CURRENCY                 VARCHAR2(3)            default 'DEM' not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CURRENCY check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CUR primary key (CURRENCY)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_CURRENCY to INTEGRATE_ROLE_ALL
/
grant select on INT_CURRENCY to INTEGRATE_ROLE_SEL
/

comment on table INT_CURRENCY is 'defines all possible currencies'
/

comment on column INT_CURRENCY.CURRENCY is 'unique identifier for a currency (use 3-digit ISO code)'
/

comment on column INT_CURRENCY.NAME is 'name or description'
/

comment on column INT_CURRENCY.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CURRENCY.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CURRENCY.MODIFBY is 'MODIFBY'
/

comment on column INT_CURRENCY.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CURRENCY.MODIFIED is 'MODIFIED'
/

comment on column INT_CURRENCY.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_ICPRODUCT_GROUP                                
-- ============================================================
drop table INT_ICPRODUCT_GROUP cascade constraints;

create table INT_ICPRODUCT_GROUP
(
    NETWORKMODEL             NUMBER(9)              not null,
    ICPRODUCT_GROUP          VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_ICPRODUCT_GRO check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_IPG primary key (NETWORKMODEL, ICPRODUCT_GROUP)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_ICPRODUCT_GROUP to INTEGRATE_ROLE_ALL
/
grant select on INT_ICPRODUCT_GROUP to INTEGRATE_ROLE_SEL
/

comment on table INT_ICPRODUCT_GROUP is 'defines possible ic product groups'
/

comment on column INT_ICPRODUCT_GROUP.NETWORKMODEL is 'uniquely identifies a related network model'
/

comment on column INT_ICPRODUCT_GROUP.ICPRODUCT_GROUP is 'defines a unique ic product group'
/

comment on column INT_ICPRODUCT_GROUP.NAME is 'name or description'
/

comment on column INT_ICPRODUCT_GROUP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_ICPRODUCT_GROUP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_ICPRODUCT_GROUP.MODIFBY is 'MODIFBY'
/

comment on column INT_ICPRODUCT_GROUP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_ICPRODUCT_GROUP.MODIFIED is 'MODIFIED'
/

comment on column INT_ICPRODUCT_GROUP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_DISCOUNTMDL_VER                                
-- ============================================================
drop table INT_DISCOUNTMDL_VER cascade constraints;

create table INT_DISCOUNTMDL_VER
(
    DISCOUNTMODEL            NUMBER(9)              not null,
    VERSION                  NUMBER(9)              not null,
    VALID_FROM               DATE                   null    ,
    STATUS                   CHAR(1)                default 'D' not null
        constraint CKC_STATUS_INT_DISCOUNTMDL_VE check (STATUS in ('A','D','T','S')),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_DISCOUNTMDL_V check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DMV primary key (DISCOUNTMODEL, VERSION)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_DISCOUNTMDL_VER to INTEGRATE_ROLE_ALL
/
grant select on INT_DISCOUNTMDL_VER to INTEGRATE_ROLE_SEL
/

comment on table INT_DISCOUNTMDL_VER is 'defines different versions of a discount model'
/

comment on column INT_DISCOUNTMDL_VER.DISCOUNTMODEL is 'references the discount model'
/

comment on column INT_DISCOUNTMDL_VER.VERSION is 'unique version within the discount model'
/

comment on column INT_DISCOUNTMDL_VER.VALID_FROM is 'date from when on this version is valid (if empty it is always valid)'
/

comment on column INT_DISCOUNTMDL_VER.STATUS is 'status of this discount model version (A=active, D=deactive, T=test, S=simulation)'
/

comment on column INT_DISCOUNTMDL_VER.ENTRYBY is 'ENTRYBY'
/

comment on column INT_DISCOUNTMDL_VER.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_DISCOUNTMDL_VER.MODIFBY is 'MODIFBY'
/

comment on column INT_DISCOUNTMDL_VER.MODIFDATE is 'MODIFDATE'
/

comment on column INT_DISCOUNTMDL_VER.MODIFIED is 'MODIFIED'
/

comment on column INT_DISCOUNTMDL_VER.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SUBSDISCOUNT_MAP                               
-- ============================================================
drop table INT_SUBSDISCOUNT_MAP cascade constraints;

create table INT_SUBSDISCOUNT_MAP
(
    SUBS_DISCOUNTMODEL       VARCHAR2(5)            not null,
    INT_DISCOUNTMODEL        NUMBER(9)              null    ,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SUBSDISCOUNT_ check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SDM primary key (SUBS_DISCOUNTMODEL)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_SUBSDISCOUNT_MAP to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBSDISCOUNT_MAP to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBSDISCOUNT_MAP is 'discountmodel mapping table, maps an external subscriber specific discountmodel to an internal discountmodel'
/

comment on column INT_SUBSDISCOUNT_MAP.SUBS_DISCOUNTMODEL is 'references the subscriber related discountmodel, which should be mapped'
/

comment on column INT_SUBSDISCOUNT_MAP.INT_DISCOUNTMODEL is 'references the internal discountmodel which should be used instead'
/

comment on column INT_SUBSDISCOUNT_MAP.NAME is 'name or description of the subscriber discountmodel'
/

comment on column INT_SUBSDISCOUNT_MAP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SUBSDISCOUNT_MAP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SUBSDISCOUNT_MAP.MODIFBY is 'MODIFBY'
/

comment on column INT_SUBSDISCOUNT_MAP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SUBSDISCOUNT_MAP.MODIFIED is 'MODIFIED'
/

comment on column INT_SUBSDISCOUNT_MAP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: SOL_TABS                                           
-- ============================================================
drop table SOL_TABS cascade constraints;

create table SOL_TABS
(
    OBJ_ID                   NUMBER(9)              not null,
    TAB_TYPE                 NUMBER(1)              not null
        constraint CKC_TAB_TYPE_SOL_TABS check (TAB_TYPE in (0,1,5)),
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_SOL_TABS check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_SOL_TABS primary key (OBJ_ID)
        using index
     tablespace SOL_TS_1_IDX
)
tablespace SOL_TS_1_DAT
/
grant select, insert, update, delete on SOL_TABS to INTEGRATE_ROLE_ALL
/
grant select on SOL_TABS to INTEGRATE_ROLE_SEL
/

comment on table SOL_TABS is 'SOL_TABS'
/

comment on column SOL_TABS.OBJ_ID is 'Internal ID => Generated by sequence ''SOL_OBJS_SEQ'''
/

comment on column SOL_TABS.TAB_TYPE is 'type of table-object (0=Table, 1=View, 5=External-Table)'
/

comment on column SOL_TABS.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column SOL_TABS.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column SOL_TABS.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column SOL_TABS.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column SOL_TABS.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column SOL_TABS.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: BIDX_SOL_TABS_TAB_TYPE                             
-- ============================================================
create index BIDX_SOL_TABS_TAB_TYPE on SOL_TABS (TAB_TYPE asc)
tablespace SOL_TS_1_IDX
/

-- ============================================================
--   Table: SOL_CONSTRAINTS                                    
-- ============================================================
drop table SOL_CONSTRAINTS cascade constraints;

create table SOL_CONSTRAINTS
(
    CONSTRAINT_ID            NUMBER(9)              not null,
    NAME                     VARCHAR2(35)           null    ,
    PARENT_TAB_ID            NUMBER(9)              not null,
    CHILD_TAB_ID             NUMBER(9)              not null,
    STATUS                   NUMBER(1)              default 0 not null
        constraint CKC_STATUS_SOL_CONSTRAINTS check (STATUS in (0,1)),
    CONST_TYPE               NUMBER(1)              not null
        constraint CKC_CONST_TY_SOL_CONSTRAINTS check (CONST_TYPE in (0,1,2,3)),
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_SOL_CONSTRAINTS check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_SOL_CONSTRAINTS primary key (CONSTRAINT_ID)
        using index
     tablespace SOL_TS_1_IDX
)
tablespace SOL_TS_1_DAT
/
grant select, insert, update, delete on SOL_CONSTRAINTS to INTEGRATE_ROLE_ALL
/
grant select on SOL_CONSTRAINTS to INTEGRATE_ROLE_SEL
/

comment on table SOL_CONSTRAINTS is 'SOL_CONSTRAINTS'
/

comment on column SOL_CONSTRAINTS.CONSTRAINT_ID is 'Internal ID => Generated by sequence ''SOL_CONSTRAINTS_SEQ'''
/

comment on column SOL_CONSTRAINTS.NAME is 'External Name / Description'
/

comment on column SOL_CONSTRAINTS.PARENT_TAB_ID is 'PARENT_TAB_ID'
/

comment on column SOL_CONSTRAINTS.CHILD_TAB_ID is 'Internal ID => Generated by sequence ''SOL_OBJS_SEQ'''
/

comment on column SOL_CONSTRAINTS.STATUS is 'STATUS'
/

comment on column SOL_CONSTRAINTS.CONST_TYPE is 'Defines the type of constraint'
/

comment on column SOL_CONSTRAINTS.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column SOL_CONSTRAINTS.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column SOL_CONSTRAINTS.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column SOL_CONSTRAINTS.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column SOL_CONSTRAINTS.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column SOL_CONSTRAINTS.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: BIDX_SOL_CONSTRAINTS_CTYPE                         
-- ============================================================
create index BIDX_SOL_CONSTRAINTS_CTYPE on SOL_CONSTRAINTS (CONST_TYPE asc)
tablespace SOL_TS_1_IDX
/

-- ============================================================
--   Index: BIDX_SOL_CONSTRAINTS_STATUS                        
-- ============================================================
create index BIDX_SOL_CONSTRAINTS_STATUS on SOL_CONSTRAINTS (STATUS asc)
tablespace SOL_TS_1_IDX
/

-- ============================================================
--   Table: SOL_COLS                                           
-- ============================================================
drop table SOL_COLS cascade constraints;

create table SOL_COLS
(
    OBJ_ID                   NUMBER(9)              not null,
    TAB_OBJ_ID               NUMBER(9)              not null,
    UNIT_ID                  NUMBER(9)              null    ,
    COL_TYPE                 NUMBER(1)              not null
        constraint CKC_COL_TYPE_SOL_COLS check (COL_TYPE in (2,3,6,7)),
    ALIAS                    VARCHAR2(18)           null    ,
    EXPRESSION               VARCHAR2(2000)         not null,
    DATATYPE                 NUMBER(1)              not null
        constraint CKC_DATATYPE_SOL_COLS check (DATATYPE in (0,1,2,3,4,5)),
    DATALENGTH               NUMBER(9)              not null,
    DATAPRECISION            NUMBER(9)              null    ,
    DATASCALE                NUMBER(9)              null    ,
    STRINGTYPE               NUMBER(1)              not null
        constraint CKC_STRINGTY_SOL_COLS check (STRINGTYPE in (0,1,2,3,4,5)),
    NULLABLE                 NUMBER(1)              default 0 not null
        constraint CKC_NULLABLE_SOL_COLS check (NULLABLE in (0,1)),
    DOMAIN                   VARCHAR2(2000)         null    ,
    FORMAT                   VARCHAR2(35)           null    ,
    PIVOTPOSITION            NUMBER(1)              default 0 not null
        constraint CKC_PIVOTPOS_SOL_COLS check (PIVOTPOSITION in (0,1,2,3)),
    ALIGNMENT                NUMBER(1)              default 0 not null
        constraint CKC_ALIGNMEN_SOL_COLS check (ALIGNMENT in (0,1,2,3)),
    RANGEITEM_DOMAIN         VARCHAR2(2000)         null    ,
    VALUEITEM_DOMAIN         VARCHAR2(2000)         null    ,
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_SOL_COLS check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_SOL_COLS primary key (OBJ_ID)
        using index
     tablespace SOL_TS_1_IDX
)
tablespace SOL_TS_1_DAT
/
grant select, insert, update, delete on SOL_COLS to INTEGRATE_ROLE_ALL
/
grant select on SOL_COLS to INTEGRATE_ROLE_SEL
/

comment on table SOL_COLS is 'SOL_COLS'
/

comment on column SOL_COLS.OBJ_ID is 'Internal ID => Generated by sequence ''SOL_OBJS_SEQ'''
/

comment on column SOL_COLS.TAB_OBJ_ID is 'TAB_OBJ_ID'
/

comment on column SOL_COLS.UNIT_ID is 'UNIT_ID'
/

comment on column SOL_COLS.COL_TYPE is 'COL_TYPE'
/

comment on column SOL_COLS.ALIAS is 'Specifies the default aliasname which can be used by a select-statement'
/

comment on column SOL_COLS.EXPRESSION is 'EXPRESSION'
/

comment on column SOL_COLS.DATATYPE is 'Defines the datatype of column'
/

comment on column SOL_COLS.DATALENGTH is 'DATALENGTH'
/

comment on column SOL_COLS.DATAPRECISION is 'total number of digits for datatype number'
/

comment on column SOL_COLS.DATASCALE is 'number of digits to the right of the decimal point for datatype number'
/

comment on column SOL_COLS.STRINGTYPE is 'STRINGTYPE'
/

comment on column SOL_COLS.NULLABLE is 'NULLABLE'
/

comment on column SOL_COLS.DOMAIN is 'Definition of domain values, i.g. "select key, value from dual union select key, value from dual", .....'
/

comment on column SOL_COLS.FORMAT is 'FORMAT'
/

comment on column SOL_COLS.PIVOTPOSITION is 'Defines the default positition in a pivot table'
/

comment on column SOL_COLS.ALIGNMENT is 'specifies the default allignment for online components which can not distinguish datatype alignment'
/

comment on column SOL_COLS.RANGEITEM_DOMAIN is 'RANGEITEM_DOMAIN'
/

comment on column SOL_COLS.VALUEITEM_DOMAIN is 'VALUEITEM_DOMAIN'
/

comment on column SOL_COLS.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column SOL_COLS.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column SOL_COLS.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column SOL_COLS.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column SOL_COLS.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column SOL_COLS.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: BIDX_SOL_COLS_COL_TYPE                             
-- ============================================================
create index BIDX_SOL_COLS_COL_TYPE on SOL_COLS (COL_TYPE asc)
tablespace SOL_TS_1_IDX
/

-- ============================================================
--   Index: BIDX_SOL_COLS_DATATYPE                             
-- ============================================================
create index BIDX_SOL_COLS_DATATYPE on SOL_COLS (DATATYPE asc)
tablespace SOL_TS_1_IDX
/

-- ============================================================
--   Index: BIDX_SOL_COLS_STRINGTYPE                           
-- ============================================================
create index BIDX_SOL_COLS_STRINGTYPE on SOL_COLS (STRINGTYPE asc)
tablespace SOL_TS_1_IDX
/

-- ============================================================
--   Table: AGG_GROUPING                                       
-- ============================================================
drop table AGG_GROUPING cascade constraints;

create table AGG_GROUPING
(
    GROUPING_ID              NUMBER(9)              not null,
    SCENARIO_ID              NUMBER(9)              not null,
    COL_OBJ_ID               NUMBER(9)              not null,
    RANK                     NUMBER(9)              not null,
    COL_NAME                 VARCHAR2(30)           not null,
    COL_FORMAT               VARCHAR2(35)           null    ,
    GROUPING_DATATYPE        NUMBER(1)              not null
        constraint CKC_GROUPING_AGG_GRPDAT check (GROUPING_DATATYPE in (0,1,2,3,4,5)),
    GROUPING_STATUS          NUMBER(1)              default 0 not null
        constraint CKC_GROUPING_AGG_GRSTAT check (GROUPING_STATUS in (0,1)),
    constraint PK_AGG_GROUPING primary key (GROUPING_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_GROUPING to INTEGRATE_ROLE_ALL
/
grant select on AGG_GROUPING to INTEGRATE_ROLE_SEL
/

comment on table AGG_GROUPING is 'Defines the grouping conditions for aggregatescenarios'
/

comment on column AGG_GROUPING.GROUPING_ID is 'Internal ID => Generated by sequence ''AGG_GROUPING_SEQ'''
/

comment on column AGG_GROUPING.SCENARIO_ID is 'Internal ID => Generated by sequence ''AGG_SCENARIO_SEQ'''
/

comment on column AGG_GROUPING.COL_OBJ_ID is 'Internal ID => Generated by sequence ''SOL_OBJS_SEQ'''
/

comment on column AGG_GROUPING.RANK is 'Internal ID to specify the position of a grouping column through all defined grouping columns in a scenario'
/

comment on column AGG_GROUPING.COL_NAME is 'Specifies the column name used by the aggregate process'
/

comment on column AGG_GROUPING.COL_FORMAT is 'Specifies the column format for datevalues used by the aggregate process'
/

comment on column AGG_GROUPING.GROUPING_DATATYPE is 'Datatype of the result values for a grouping column'
/

comment on column AGG_GROUPING.GROUPING_STATUS is 'Boolean Flag which specifies whether the grouping rules is currently active (will be used) or not.'
/


-- ============================================================
--   Index: AK_AGG_GRP_SCN_COL                                 
-- ============================================================
create unique index AK_AGG_GRP_SCN_COL on AGG_GROUPING (SCENARIO_ID asc, COL_OBJ_ID asc, RANK asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Index: BIDX_AGG_GRP_STATUS                                
-- ============================================================
create index BIDX_AGG_GRP_STATUS on AGG_GROUPING (GROUPING_STATUS asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: AGG_EDRCFIELD                                      
-- ============================================================
drop table AGG_EDRCFIELD cascade constraints;

create table AGG_EDRCFIELD
(
    EDRCFIELD_ID             NUMBER(9)              not null,
    EDRC_TYPE                NUMBER(1)              null    
        constraint CKC_EDRC_TYP_AGG_EDRCFIELD check (EDRC_TYPE is null or (EDRC_TYPE in (0,1,2,3,4,5,8,9))),
    INTERNAL_FIELD_ID        NUMBER(9)              not null,
    INTERNAL_FIELDNAME       VARCHAR2(254)          not null,
    COL_OBJ_ID               NUMBER(9)              not null,
    REFERENCESET_ID          NUMBER(9)              null    ,
    RULE_USAGE               NUMBER(1)              not null
        constraint CKC_RULE_USA_AGG_EDRCFIELD check (RULE_USAGE in (0,1,2,9)),
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_AGG_EDRCFIELD check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_AGG_EDRCFIELD primary key (EDRCFIELD_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_EDRCFIELD to INTEGRATE_ROLE_ALL
/
grant select on AGG_EDRCFIELD to INTEGRATE_ROLE_SEL
/

comment on table AGG_EDRCFIELD is 'Defines all available fields in an EDR-Stream'
/

comment on column AGG_EDRCFIELD.EDRCFIELD_ID is 'Internal ID => Generated by sequence ''AGG_EDRCFIELD_SEQ'''
/

comment on column AGG_EDRCFIELD.EDRC_TYPE is 'Defines whether Column is Part of sol42 Basic Detail (Value 0),  Chargebreakdown (Value 1), Chargepaket (Value 2), ....'
/

comment on column AGG_EDRCFIELD.INTERNAL_FIELD_ID is 'Internal Fieldnumber can be used for Mapping Purpose to internal COL_OBJ_ID'
/

comment on column AGG_EDRCFIELD.INTERNAL_FIELDNAME is 'External Fieldname, can be used for Mapping Purpose to internal COL_OBJ_ID'
/

comment on column AGG_EDRCFIELD.COL_OBJ_ID is 'Internal ID => Generated by sequence ''SOL_OBJS_SEQ'''
/

comment on column AGG_EDRCFIELD.REFERENCESET_ID is 'Internal ID => Generated by sequence ''AGG_REFERENCESET_SEQ'''
/

comment on column AGG_EDRCFIELD.RULE_USAGE is 'Flag defines, whether the EDR-Column fits for Grouping and/or Aggregation or not'
/

comment on column AGG_EDRCFIELD.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column AGG_EDRCFIELD.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column AGG_EDRCFIELD.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column AGG_EDRCFIELD.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column AGG_EDRCFIELD.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column AGG_EDRCFIELD.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: AK_AGG_EDRCFIELD_INTERNAL_ID                       
-- ============================================================
create unique index AK_AGG_EDRCFIELD_INTERNAL_ID on AGG_EDRCFIELD (INTERNAL_FIELD_ID asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Index: AK_AGG_EDRCFIELD_INTERNAL_NAME                     
-- ============================================================
create unique index AK_AGG_EDRCFIELD_INTERNAL_NAME on AGG_EDRCFIELD (INTERNAL_FIELDNAME asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: AGG_GROUPING_CNF                                   
-- ============================================================
drop table AGG_GROUPING_CNF cascade constraints;

create table AGG_GROUPING_CNF
(
    GROUPING_CNF_ID          NUMBER(9)              not null,
    GROUPING_ID              NUMBER(9)              not null,
    CLASS_ID                 NUMBER(9)              not null,
    constraint PK_AGG_GROUPING_CNF primary key (GROUPING_CNF_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_GROUPING_CNF to INTEGRATE_ROLE_ALL
/
grant select on AGG_GROUPING_CNF to INTEGRATE_ROLE_SEL
/

comment on table AGG_GROUPING_CNF is 'Defines the usage of classes for groupingrules'
/

comment on column AGG_GROUPING_CNF.GROUPING_CNF_ID is 'Internal ID => Generated by sequence ''AGG_GROUPING_CNF_SEQ'''
/

comment on column AGG_GROUPING_CNF.GROUPING_ID is 'Internal ID => Generated by sequence ''AGG_GROUPING_SEQ'''
/

comment on column AGG_GROUPING_CNF.CLASS_ID is 'Internal ID => Generated by sequence ''AGG_CLASS_SEQ'''
/


-- ============================================================
--   Index: AK_AGG_GRPCNF_GRP_CLS                              
-- ============================================================
create unique index AK_AGG_GRPCNF_GRP_CLS on AGG_GROUPING_CNF (GROUPING_ID asc, CLASS_ID asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: AGG_CLASSCON                                       
-- ============================================================
drop table AGG_CLASSCON cascade constraints;

create table AGG_CLASSCON
(
    CLASSCON_ID              NUMBER(9)              not null,
    NODE_GROUPING_CNF_ID     NUMBER(9)              not null,
    NEXT_GROUPING_CNF_ID     NUMBER(9)              not null,
    constraint PK_AGG_CLASSCON primary key (CLASSCON_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_CLASSCON to INTEGRATE_ROLE_ALL
/
grant select on AGG_CLASSCON to INTEGRATE_ROLE_SEL
/

comment on table AGG_CLASSCON is 'Defines a conditional reference between used grouping classes'
/

comment on column AGG_CLASSCON.CLASSCON_ID is 'Internal ID => Generated by sequence ''AGG_CLASSCON_SEQ'''
/

comment on column AGG_CLASSCON.NODE_GROUPING_CNF_ID is 'Node classgrouping configuration (Internal ID => Generated by sequence ''AGG_GROUPING_CNF_SEQ'')'
/

comment on column AGG_CLASSCON.NEXT_GROUPING_CNF_ID is 'Next classgrouping configuration (Internal ID => Generated by sequence ''AGG_GROUPING_CNF_SEQ'')'
/


-- ============================================================
--   Index: AK_AGG_CLASSCON_NODE_NEXT                          
-- ============================================================
create unique index AK_AGG_CLASSCON_NODE_NEXT on AGG_CLASSCON (NODE_GROUPING_CNF_ID asc, NEXT_GROUPING_CNF_ID asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: INT_ZONEMODEL                                      
-- ============================================================
drop table INT_ZONEMODEL cascade constraints;

create table INT_ZONEMODEL
(
    ZONEMODEL                NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    MODELTYPE                CHAR(1)                default 'S' not null
        constraint CKC_MODELTYP_INT_ZONEMODEL check (MODELTYPE in ('S','G','E')),
    FRAME                    CHAR(1)                default 'N' not null
        constraint CKC_FRAME_INT_ZONEMODEL check (FRAME in ('N','R','I','S')),
    STATUS                   CHAR(1)                default 'D' not null
        constraint CKC_STATUS_INT_ZONEMODEL check (STATUS in ('A','D','T','S')),
    APN_GROUP                VARCHAR2(10)           null    ,
    GEOMODEL                 NUMBER(9)              null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_ZONEMODEL check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_ZMD primary key (ZONEMODEL)
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
)
/
grant select, insert, update, delete on INT_ZONEMODEL to INTEGRATE_ROLE_ALL
/
grant select on INT_ZONEMODEL to INTEGRATE_ROLE_SEL
/

comment on table INT_ZONEMODEL is 'zone model definition (main entry point for any zoning)'
/

comment on column INT_ZONEMODEL.ZONEMODEL is 'internal ID, uniquely identifies the zone model'
/

comment on column INT_ZONEMODEL.CODE is 'defines a unique external zone model code'
/

comment on column INT_ZONEMODEL.NAME is 'name of the model, just for info'
/

comment on column INT_ZONEMODEL.MODELTYPE is 'type of zone model (S=standard, G=geographical, E=External)'
/

comment on column INT_ZONEMODEL.FRAME is 'group, classification for this model (N=normal retail, R=reseller IC, I=carrier IC, S=segmentation)'
/

comment on column INT_ZONEMODEL.STATUS is 'status of the model (A=active, D=deactive, T=test, S=simulation)'
/

comment on column INT_ZONEMODEL.APN_GROUP is 'references to an optional APN group which should be used'
/

comment on column INT_ZONEMODEL.GEOMODEL is 'geographical model which should be used (or empty)'
/

comment on column INT_ZONEMODEL.ENTRYBY is 'ENTRYBY'
/

comment on column INT_ZONEMODEL.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_ZONEMODEL.MODIFBY is 'MODIFBY'
/

comment on column INT_ZONEMODEL.MODIFDATE is 'MODIFDATE'
/

comment on column INT_ZONEMODEL.MODIFIED is 'MODIFIED'
/

comment on column INT_ZONEMODEL.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_ZMD                                         
-- ============================================================
create unique index AK_INT_ZMD on INT_ZONEMODEL (CODE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_3_IDX
storage
(
initial 64K
next 64K
minextents 1
maxextents unlimited
pctincrease 0
)
/

-- ============================================================
--   Table: INT_GLACCOUNT                                      
-- ============================================================
drop table INT_GLACCOUNT cascade constraints;

create table INT_GLACCOUNT
(
    GLACCOUNT                VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    TAXCODE                  VARCHAR2(5)            not null,
    GLA_TYPE                 CHAR(1)                default 'R' not null
        constraint CKC_GLA_TYPE_INT_GLACCOUNT check (GLA_TYPE in ('R','E','L','A')),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_GLACCOUNT check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_GLA primary key (GLACCOUNT)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_GLACCOUNT to INTEGRATE_ROLE_ALL
/
grant select on INT_GLACCOUNT to INTEGRATE_ROLE_SEL
/

comment on table INT_GLACCOUNT is 'defines all general ledger accounts'
/

comment on column INT_GLACCOUNT.GLACCOUNT is 'g/l account code'
/

comment on column INT_GLACCOUNT.NAME is 'name or description'
/

comment on column INT_GLACCOUNT.TAXCODE is 'tax code as a reference to the type of tax'
/

comment on column INT_GLACCOUNT.GLA_TYPE is 'defines the type of the g/l account (R=revenue, E=expence, L=liability, A=asset)'
/

comment on column INT_GLACCOUNT.ENTRYBY is 'ENTRYBY'
/

comment on column INT_GLACCOUNT.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_GLACCOUNT.MODIFBY is 'MODIFBY'
/

comment on column INT_GLACCOUNT.MODIFDATE is 'MODIFDATE'
/

comment on column INT_GLACCOUNT.MODIFIED is 'MODIFIED'
/

comment on column INT_GLACCOUNT.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SERVICE                                        
-- ============================================================
drop table INT_SERVICE cascade constraints;

create table INT_SERVICE
(
    SERVICECODE              VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    RANK                     NUMBER(9)              default 1 not null,
    UOM_Q                    VARCHAR2(3)            not null,
    UOM_S                    VARCHAR2(3)            not null,
    UOM_R                    VARCHAR2(3)            not null,
    TOS                      CHAR(1)                default 'B' not null
        constraint CKC_TOS_INT_SERVICE check (TOS in ('B','V','E','L','C')),
    CHARGE_ITEM              CHAR(1)                default 'D' not null
        constraint CKC_CHARGE_I_INT_SERVICE check (CHARGE_ITEM in ('D','E','V','S','R','T','A','B')),
    DEF_GLACCOUNT            VARCHAR2(10)           null    ,
    DEF_REVENUEGROUP         VARCHAR2(5)            null    ,
    PARENT_SERVICE           VARCHAR2(5)            null    ,
    BASIC                    NUMBER(1)              default 1 not null
        constraint CKC_BASIC_INT_SERVICE check (BASIC in (0,1)),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SERVICE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SRV primary key (SERVICECODE)
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
buffer_pool keep
)
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_SERVICE to INTEGRATE_ROLE_ALL
/
grant select on INT_SERVICE to INTEGRATE_ROLE_SEL
/

comment on table INT_SERVICE is 'defines all valid service codes which can be used internally'
/

comment on column INT_SERVICE.SERVICECODE is 'unique service code which can be used'
/

comment on column INT_SERVICE.NAME is 'description'
/

comment on column INT_SERVICE.RANK is 'rank, evaluation order during zone determination'
/

comment on column INT_SERVICE.UOM_Q is 'units of measurement for the quantity value'
/

comment on column INT_SERVICE.UOM_S is 'UoM_S'
/

comment on column INT_SERVICE.UOM_R is 'UoM_R'
/

comment on column INT_SERVICE.TOS is 'Type of Service (B=Basic, V=VAS, E=Event, L=Logical), just for info or grouping reasons'
/

comment on column INT_SERVICE.CHARGE_ITEM is 'defines the type of the charge which will apply to this service (e.g. D=quantity based, V=volume based, E=event based, etc.)'
/

comment on column INT_SERVICE.DEF_GLACCOUNT is 'references a default general ledger account code for this basic service'
/

comment on column INT_SERVICE.DEF_REVENUEGROUP is 'references a default revenue group code for this basic service'
/

comment on column INT_SERVICE.PARENT_SERVICE is 'references a parent service code (to define hierarchical structures)'
/

comment on column INT_SERVICE.BASIC is 'indicator, if this is a basic service code to be usable in a tariffmodel'
/

comment on column INT_SERVICE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SERVICE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SERVICE.MODIFBY is 'MODIFBY'
/

comment on column INT_SERVICE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SERVICE.MODIFIED is 'MODIFIED'
/

comment on column INT_SERVICE.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SUBSSERVICE_MAP                                
-- ============================================================
drop table INT_SUBSSERVICE_MAP cascade constraints;

create table INT_SUBSSERVICE_MAP
(
    SUBS_SERVICECODE         VARCHAR2(5)            not null,
    INT_SERVICECODE          VARCHAR2(5)            null    ,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SUBSSERVICE_M check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SSM primary key (SUBS_SERVICECODE)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_SUBSSERVICE_MAP to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBSSERVICE_MAP to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBSSERVICE_MAP is 'service code mapping table, maps an external subscriber specific servicecode to an internal servicecode'
/

comment on column INT_SUBSSERVICE_MAP.SUBS_SERVICECODE is 'external subscriber servicecode (which should be mapped)'
/

comment on column INT_SUBSSERVICE_MAP.INT_SERVICECODE is 'internal service code (which should be used instead)'
/

comment on column INT_SUBSSERVICE_MAP.NAME is 'name or description of the subscriber servicecode'
/

comment on column INT_SUBSSERVICE_MAP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SUBSSERVICE_MAP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SUBSSERVICE_MAP.MODIFBY is 'MODIFBY'
/

comment on column INT_SUBSSERVICE_MAP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SUBSSERVICE_MAP.MODIFIED is 'MODIFIED'
/

comment on column INT_SUBSSERVICE_MAP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SERVICECLASS                                   
-- ============================================================
drop table INT_SERVICECLASS cascade constraints;

create table INT_SERVICECLASS
(
    SERVICECODE              VARCHAR2(5)            not null,
    SERVICECLASS             VARCHAR2(5)            default '*' not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SERVICECLASS check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SVC primary key (SERVICECODE, SERVICECLASS)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_SERVICECLASS to INTEGRATE_ROLE_ALL
/
grant select on INT_SERVICECLASS to INTEGRATE_ROLE_SEL
/

comment on table INT_SERVICECLASS is 'defines all possible service class''s per service code'
/

comment on column INT_SERVICECLASS.SERVICECODE is 'references the related service code'
/

comment on column INT_SERVICECLASS.SERVICECLASS is 'uniquely defines a service class for the given service code'
/

comment on column INT_SERVICECLASS.NAME is 'name or description'
/

comment on column INT_SERVICECLASS.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SERVICECLASS.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SERVICECLASS.MODIFBY is 'MODIFBY'
/

comment on column INT_SERVICECLASS.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SERVICECLASS.MODIFIED is 'MODIFIED'
/

comment on column INT_SERVICECLASS.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_NETWORKOPERATOR                                
-- ============================================================
drop table INT_NETWORKOPERATOR cascade constraints;

create table INT_NETWORKOPERATOR
(
    NO                       NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    NOTYPE                   CHAR(1)                default 'I' not null
        constraint CKC_NOTYPE_INT_NETWORKOPERATO check (NOTYPE in ('I','S','R','O','X')),
    CAC                      VARCHAR2(6)            null    ,
    CIC                      VARCHAR2(5)            null    ,
    PLMN_ID                  NUMBER(7)              null    ,
    TADIG                    VARCHAR2(5)            null    ,
    CURRENCY                 VARCHAR2(3)            default 'DEM' not null,
    TAXGROUP                 VARCHAR2(5)            not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_NETWORKOPERAT check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_NOP primary key (NO)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_NETWORKOPERATOR to INTEGRATE_ROLE_ALL
/
grant select on INT_NETWORKOPERATOR to INTEGRATE_ROLE_SEL
/

comment on table INT_NETWORKOPERATOR is 'defined all valid network operators (either carrier, reseller or service-provider or virtual references)'
/

comment on column INT_NETWORKOPERATOR.NO is 'internal ID'
/

comment on column INT_NETWORKOPERATOR.CODE is 'the code for the network operator'
/

comment on column INT_NETWORKOPERATOR.NAME is 'name of the network operator'
/

comment on column INT_NETWORKOPERATOR.NOTYPE is 'type of no (I=interconnection partner, S=service-provider partner, R=reseller partner, O=Offline Billing NO, X=myself)'
/

comment on column INT_NETWORKOPERATOR.CAC is 'carrier access code (e.g. 10042)'
/

comment on column INT_NETWORKOPERATOR.CIC is 'carrier identification code (e.g. a ported Dxxx code for the network operator)'
/

comment on column INT_NETWORKOPERATOR.PLMN_ID is 'public land mobile network code'
/

comment on column INT_NETWORKOPERATOR.TADIG is 'tadig name for the operator'
/

comment on column INT_NETWORKOPERATOR.CURRENCY is 'defines the default currency for this operator (data exchange and billing has to be converted into this currency)'
/

comment on column INT_NETWORKOPERATOR.TAXGROUP is 'references a tax group which is associated with this network operator'
/

comment on column INT_NETWORKOPERATOR.ENTRYBY is 'ENTRYBY'
/

comment on column INT_NETWORKOPERATOR.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_NETWORKOPERATOR.MODIFBY is 'MODIFBY'
/

comment on column INT_NETWORKOPERATOR.MODIFDATE is 'MODIFDATE'
/

comment on column INT_NETWORKOPERATOR.MODIFIED is 'MODIFIED'
/

comment on column INT_NETWORKOPERATOR.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_NOP                                         
-- ============================================================
create unique index AK_INT_NOP on INT_NETWORKOPERATOR (CODE asc)
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
/

-- ============================================================
--   Table: INT_CONTENTPROVIDER                                
-- ============================================================
drop table INT_CONTENTPROVIDER cascade constraints;

create table INT_CONTENTPROVIDER
(
    CONTENTPROVIDER          NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    CURRENCY                 VARCHAR2(3)            default 'DEM' not null,
    TAXGROUP                 VARCHAR2(5)            not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CONTENTPROVID check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CPD primary key (CONTENTPROVIDER)
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
tablespace INTEGRATE_TS_1_DAT
storage
(
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
)
/
grant select, insert, update, delete on INT_CONTENTPROVIDER to INTEGRATE_ROLE_ALL
/
grant select on INT_CONTENTPROVIDER to INTEGRATE_ROLE_SEL
/

comment on table INT_CONTENTPROVIDER is 'content provider definition'
/

comment on column INT_CONTENTPROVIDER.CONTENTPROVIDER is 'unique content provider id'
/

comment on column INT_CONTENTPROVIDER.CODE is 'external content provider code'
/

comment on column INT_CONTENTPROVIDER.NAME is 'name or description'
/

comment on column INT_CONTENTPROVIDER.CURRENCY is 'the currency in which the content provider will typically be charged'
/

comment on column INT_CONTENTPROVIDER.TAXGROUP is 'references a tax group code which should apply for this content provider'
/

comment on column INT_CONTENTPROVIDER.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CONTENTPROVIDER.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CONTENTPROVIDER.MODIFBY is 'MODIFBY'
/

comment on column INT_CONTENTPROVIDER.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CONTENTPROVIDER.MODIFIED is 'MODIFIED'
/

comment on column INT_CONTENTPROVIDER.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_CPD                                         
-- ============================================================
create unique index AK_INT_CPD on INT_CONTENTPROVIDER (CODE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_1_IDX
storage
(
initial 64K
next 64K
minextents 1
maxextents unlimited
pctincrease 0
)
/

-- ============================================================
--   Table: INT_SUBS_CONTRACT                                  
-- ============================================================
drop table INT_SUBS_CONTRACT cascade constraints;

create table INT_SUBS_CONTRACT
(
    CONTRACT                 NUMBER(38)             not null,
    SYSTEM_BRAND             VARCHAR2(5)            null    ,
    SKELETON                 VARCHAR2(11)           null    ,
    CUSTOMER                 VARCHAR2(10)           null    ,
    SUBSCRIBER               VARCHAR2(20)           null    ,
    DEALER                   VARCHAR2(10)           null    ,
    ACTIVATED_DATE           DATE                   null    ,
    CONTRACT_PERIOD          NUMBER(9)              null    ,
    SUBS_TAXGROUP            VARCHAR2(5)            null    ,
    SUBS_CURRENCY            VARCHAR2(3)            default 'DEM' null    ,
    SUBS_BIRTHDAY            DATE                   null    ,
    SUBS_QUALITY             CHAR(1)                null    ,
    SUBS_CLASS               VARCHAR2(5)            null    ,
    SUBS_TYPE                VARCHAR2(5)            null    ,
    constraint PK_INT_SUB primary key (CONTRACT)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_IDX
        storage
        (
        initial 4M
        next 4M
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
initial 8M
next 8M
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_SUBS_CONTRACT to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBS_CONTRACT to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBS_CONTRACT is 'definition of all subscriber cli''s with all the customer data representation'
/

comment on column INT_SUBS_CONTRACT.CONTRACT is 'contract id for this subscriber-cli'
/

comment on column INT_SUBS_CONTRACT.SYSTEM_BRAND is 'external specialistsystem (or oem code or reseller code)'
/

comment on column INT_SUBS_CONTRACT.SKELETON is 'goup or skeleton agreement code (groups can combine different customers)'
/

comment on column INT_SUBS_CONTRACT.CUSTOMER is 'customer code for this subscriber (customer can group single subscribers)'
/

comment on column INT_SUBS_CONTRACT.SUBSCRIBER is 'subscriber code for this customer'
/

comment on column INT_SUBS_CONTRACT.DEALER is 'external dealer code who is referenced to this contract'
/

comment on column INT_SUBS_CONTRACT.ACTIVATED_DATE is 'date when the subscriber was activated'
/

comment on column INT_SUBS_CONTRACT.CONTRACT_PERIOD is 'number month the contract is running (e.g. 24 month contract)'
/

comment on column INT_SUBS_CONTRACT.SUBS_TAXGROUP is 'tax group of the subscriber'
/

comment on column INT_SUBS_CONTRACT.SUBS_CURRENCY is 'SUBS_CURRENCY'
/

comment on column INT_SUBS_CONTRACT.SUBS_BIRTHDAY is 'birthdate of the subscriber'
/

comment on column INT_SUBS_CONTRACT.SUBS_QUALITY is 'quality of the subscriber'
/

comment on column INT_SUBS_CONTRACT.SUBS_CLASS is 'customer/subscriber classification (e.g. vip, branch, region etc.)'
/

comment on column INT_SUBS_CONTRACT.SUBS_TYPE is 'type of customer/subscriber (e.g. residential, business etc.)'
/


-- ============================================================
--   Index: IDX_INT_SUB_CUSTOMER                               
-- ============================================================
create index IDX_INT_SUB_CUSTOMER on INT_SUBS_CONTRACT (CUSTOMER asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_2_IDX
storage
(
initial 2M
next 2M
minextents 1
maxextents unlimited
pctincrease 0
)
/

-- ============================================================
--   Table: INT_TARIFFMODEL                                    
-- ============================================================
drop table INT_TARIFFMODEL cascade constraints;

create table INT_TARIFFMODEL
(
    TARIFFMODEL              NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    STATUS                   CHAR(1)                default 'D' not null
        constraint CKC_STATUS_INT_TARIFFMODEL check (STATUS in ('A','D','T','S')),
    SYSTEM_BRAND             VARCHAR2(5)            null    ,
    MODELTYPE                CHAR(1)                default 'R' not null
        constraint CKC_MODELTYP_INT_TARIFFMODEL check (MODELTYPE in ('W','R')),
    SPLITTING                NUMBER(1)              default 0 not null
        constraint CKC_SPLITTIN_INT_TARIFFMODEL check (SPLITTING in (0,1)),
    CALENDAR                 NUMBER(9)              not null,
    UTC_TIME_OFFSET          VARCHAR2(5)            default '+0100' not null,
    CURRENCY                 VARCHAR2(3)            default 'DEM' not null,
    TAXTREATMENT             NUMBER(1)              default 0 not null
        constraint CKC_TAXTREAT_INT_TARIFFMODEL check (TAXTREATMENT in (0,1)),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TARIFFMODEL check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TMD primary key (TARIFFMODEL)
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
buffer_pool keep
)
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_TARIFFMODEL to INTEGRATE_ROLE_ALL
/
grant select on INT_TARIFFMODEL to INTEGRATE_ROLE_SEL
/

comment on table INT_TARIFFMODEL is 'tariff model definition (main entry point for rating, defines currency, tax, type of model etc.)'
/

comment on column INT_TARIFFMODEL.TARIFFMODEL is 'unique internal id to reference the tariffmodel'
/

comment on column INT_TARIFFMODEL.CODE is 'defines a unique external tariff model code'
/

comment on column INT_TARIFFMODEL.NAME is 'description'
/

comment on column INT_TARIFFMODEL.STATUS is 'status of the model (A=active, D=deactive, T=test, S=simulation)'
/

comment on column INT_TARIFFMODEL.SYSTEM_BRAND is 'references a special system/brand'
/

comment on column INT_TARIFFMODEL.MODELTYPE is 'type of tariff model (W=wholesale, R=retail)'
/

comment on column INT_TARIFFMODEL.SPLITTING is 'should an edr splitting take place, if an edr overlaps a timezone (1=Yes, N0=No)'
/

comment on column INT_TARIFFMODEL.CALENDAR is 'reference to a holiday calendar'
/

comment on column INT_TARIFFMODEL.UTC_TIME_OFFSET is 'determines, which time zone will be used when evaluating timemodels'
/

comment on column INT_TARIFFMODEL.CURRENCY is 'currency for the tariff model (e.g. DEM or EUR)'
/

comment on column INT_TARIFFMODEL.TAXTREATMENT is 'should a tax be included within the related procemodels ? (1=Yes, 0=No)'
/

comment on column INT_TARIFFMODEL.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TARIFFMODEL.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TARIFFMODEL.MODIFBY is 'MODIFBY'
/

comment on column INT_TARIFFMODEL.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TARIFFMODEL.MODIFIED is 'MODIFIED'
/

comment on column INT_TARIFFMODEL.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_TMD                                         
-- ============================================================
create unique index AK_INT_TMD on INT_TARIFFMODEL (CODE asc)
pctfree 5
initrans 2
tablespace INTEGRATE_TS_1_IDX
storage
(
initial 64K
next 64K
minextents 1
maxextents unlimited
pctincrease 0
)
/

-- ============================================================
--   Table: INT_TRUNK                                          
-- ============================================================
drop table INT_TRUNK cascade constraints;

create table INT_TRUNK
(
    NETWORKMODEL             NUMBER(9)              not null,
    TRUNK                    VARCHAR2(15)           not null,
    NAME                     VARCHAR2(30)           null    ,
    TRUNKTYPE                CHAR(1)                default 'P' not null
        constraint CKC_TRUNKTYP_INT_TRUNK check (TRUNKTYPE in ('P','V')),
    STATUS                   CHAR(1)                default 'A' not null
        constraint CKC_STATUS_INT_TRUNK check (STATUS in ('A','D')),
    NO                       NUMBER(9)              not null,
    POI                      VARCHAR2(15)           not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TRUNK check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TRK primary key (NETWORKMODEL, TRUNK)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_TRUNK to INTEGRATE_ROLE_ALL
/
grant select on INT_TRUNK to INTEGRATE_ROLE_SEL
/

comment on table INT_TRUNK is 'defines all POI related trunks'
/

comment on column INT_TRUNK.NETWORKMODEL is 'references the related network model'
/

comment on column INT_TRUNK.TRUNK is 'code which uniquely identifies a trunk'
/

comment on column INT_TRUNK.NAME is 'description'
/

comment on column INT_TRUNK.TRUNKTYPE is 'defines the type of the trunk (P=physical existing trunk, V=virtual trunk due to mapping)'
/

comment on column INT_TRUNK.STATUS is 'status of the network-element (A=active, D=deactive)'
/

comment on column INT_TRUNK.NO is 'references to the other network operator this trunk is connected with'
/

comment on column INT_TRUNK.POI is 'references the poi this trunk is related to'
/

comment on column INT_TRUNK.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TRUNK.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TRUNK.MODIFBY is 'MODIFBY'
/

comment on column INT_TRUNK.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TRUNK.MODIFIED is 'MODIFIED'
/

comment on column INT_TRUNK.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SWITCH                                         
-- ============================================================
drop table INT_SWITCH cascade constraints;

create table INT_SWITCH
(
    NETWORKMODEL             NUMBER(9)              not null,
    SWITCH                   VARCHAR2(15)           not null,
    NAME                     VARCHAR2(30)           null    ,
    STATUS                   CHAR(1)                default 'A' not null
        constraint CKC_STATUS_INT_SWITCH check (STATUS in ('A','D')),
    NO                       NUMBER(9)              not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SWITCH check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SWI primary key (NETWORKMODEL, SWITCH)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_SWITCH to INTEGRATE_ROLE_ALL
/
grant select on INT_SWITCH to INTEGRATE_ROLE_SEL
/

comment on table INT_SWITCH is 'switch definition table (groups all trunks related to a switch, just for info)'
/

comment on column INT_SWITCH.NETWORKMODEL is 'unique internal model id'
/

comment on column INT_SWITCH.SWITCH is 'unique switch code'
/

comment on column INT_SWITCH.NAME is 'description'
/

comment on column INT_SWITCH.STATUS is 'status of the network-element (A=active, D=deactive)'
/

comment on column INT_SWITCH.NO is 'references to network operator this switch belongs to'
/

comment on column INT_SWITCH.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SWITCH.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SWITCH.MODIFBY is 'MODIFBY'
/

comment on column INT_SWITCH.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SWITCH.MODIFIED is 'MODIFIED'
/

comment on column INT_SWITCH.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_NOPRODUCT                                      
-- ============================================================
drop table INT_NOPRODUCT cascade constraints;

create table INT_NOPRODUCT
(
    NO                       NUMBER(9)              not null,
    PRODUCTCODE              VARCHAR2(10)           not null,
    VALID_FROM               DATE                   null    ,
    NAME                     VARCHAR2(30)           null    ,
    CURRENCY                 VARCHAR2(3)            default 'DEM' not null,
    TAXCODE                  VARCHAR2(10)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_NOPRODUCT check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_NPR primary key (NO, PRODUCTCODE)
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
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_NOPRODUCT to INTEGRATE_ROLE_ALL
/
grant select on INT_NOPRODUCT to INTEGRATE_ROLE_SEL
/

comment on table INT_NOPRODUCT is 'defines the network operator product codes'
/

comment on column INT_NOPRODUCT.NO is 'references the related network operator'
/

comment on column INT_NOPRODUCT.PRODUCTCODE is 'unique network operator product code'
/

comment on column INT_NOPRODUCT.VALID_FROM is 'date from when on the no-product is valid'
/

comment on column INT_NOPRODUCT.NAME is 'name or description'
/

comment on column INT_NOPRODUCT.CURRENCY is 'overwrites the default network operator currency for this specific product; if empty the no currency is valid'
/

comment on column INT_NOPRODUCT.TAXCODE is 'tax code which applies to this poduct'
/

comment on column INT_NOPRODUCT.ENTRYBY is 'ENTRYBY'
/

comment on column INT_NOPRODUCT.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_NOPRODUCT.MODIFBY is 'MODIFBY'
/

comment on column INT_NOPRODUCT.MODIFDATE is 'MODIFDATE'
/

comment on column INT_NOPRODUCT.MODIFIED is 'MODIFIED'
/

comment on column INT_NOPRODUCT.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_ICPRODUCT                                      
-- ============================================================
drop table INT_ICPRODUCT cascade constraints;

create table INT_ICPRODUCT
(
    ICPRODUCT                VARCHAR2(10)           not null,
    VALID_FROM               DATE                   not null,
    NAME                     VARCHAR2(30)           null    ,
    ZONE_DIRECTION           CHAR(1)                default 'N' not null
        constraint CKC_ZONE_DIR_INT_ICPRODUCT check (ZONE_DIRECTION in ('I','O','T','N','S','1','2','3','4','5','6')),
    ZONE_TYPE                CHAR(1)                default 'N' not null
        constraint CKC_ZONE_TYP_INT_ICPRODUCT check (ZONE_TYPE in ('N','R')),
    BILL_DIRECTION           CHAR(1)                not null
        constraint CKC_BILL_DIR_INT_ICPRODUCT check (BILL_DIRECTION in ('I','O')),
    BILL_TYPE                CHAR(1)                default 'C' not null
        constraint CKC_BILL_TYP_INT_ICPRODUCT check (BILL_TYPE in ('C','D')),
    NO                       NUMBER(9)              not null,
    TARIFFMODEL              NUMBER(9)              not null,
    ALT_TARIFFMODEL          NUMBER(9)              null    ,
    FIXCOST                  NUMBER                 not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_ICPRODUCT check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_ICP primary key (ICPRODUCT)
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
initial 512K
next 512K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_ICPRODUCT to INTEGRATE_ROLE_ALL
/
grant select on INT_ICPRODUCT to INTEGRATE_ROLE_SEL
/

comment on table INT_ICPRODUCT is 'definition of all interconnect products'
/

comment on column INT_ICPRODUCT.ICPRODUCT is 'uniquely identifies the poi'
/

comment on column INT_ICPRODUCT.VALID_FROM is 'date from when on the ic-product is valid'
/

comment on column INT_ICPRODUCT.NAME is 'just a name for the poi'
/

comment on column INT_ICPRODUCT.ZONE_DIRECTION is 'zoning type (I=inroute, O=outroute, T=transit, N=none, S=standard a/b, 1=POI->A, 2=POI->B, 3=POI->C, 4=A->B, 5=A->C, 6=B->C)'
/

comment on column INT_ICPRODUCT.ZONE_TYPE is 'type of zoning (N=zone direction used as normal; R=reverse zone direction), e.g. R: will be used in reverse mode POI->A will be switched to A->POI'
/

comment on column INT_ICPRODUCT.BILL_DIRECTION is 'type of billing, defines the cash-flow (I=incomming, O=outgoing)'
/

comment on column INT_ICPRODUCT.BILL_TYPE is 'type of billing (C=cascade, D=direct)'
/

comment on column INT_ICPRODUCT.NO is 'reference to the network operator'
/

comment on column INT_ICPRODUCT.TARIFFMODEL is 'references the tariff model which should be used for (reseller or carrier) interconnection purpose'
/

comment on column INT_ICPRODUCT.ALT_TARIFFMODEL is 'alternative tariffmodel for simulation purpose'
/

comment on column INT_ICPRODUCT.FIXCOST is 'here you can place a fixcost charge which should be added per trunk-edr'
/

comment on column INT_ICPRODUCT.ENTRYBY is 'ENTRYBY'
/

comment on column INT_ICPRODUCT.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_ICPRODUCT.MODIFBY is 'MODIFBY'
/

comment on column INT_ICPRODUCT.MODIFDATE is 'MODIFDATE'
/

comment on column INT_ICPRODUCT.MODIFIED is 'MODIFIED'
/

comment on column INT_ICPRODUCT.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SUBSTARIFF_MAP                                 
-- ============================================================
drop table INT_SUBSTARIFF_MAP cascade constraints;

create table INT_SUBSTARIFF_MAP
(
    SUBS_TARIFFMODEL         VARCHAR2(30)           not null,
    INT_TARIFFMODEL          NUMBER(9)              null    ,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SUBSTARIFF_MA check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_STM primary key (SUBS_TARIFFMODEL)
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
tablespace INTEGRATE_TS_2_DAT
storage
(
initial 128K
next 128K
minextents 1
maxextents unlimited
pctincrease 0
)
/
grant select, insert, update, delete on INT_SUBSTARIFF_MAP to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBSTARIFF_MAP to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBSTARIFF_MAP is 'tariff mapping table, maps an external subscriber specific tariff model to an internal tariff model'
/

comment on column INT_SUBSTARIFF_MAP.SUBS_TARIFFMODEL is 'references the subscriber related tariffmodel, which should be mapped'
/

comment on column INT_SUBSTARIFF_MAP.INT_TARIFFMODEL is 'references the internal tariffmodel which should be used instead'
/

comment on column INT_SUBSTARIFF_MAP.NAME is 'name or description of the subscriber tariff model'
/

comment on column INT_SUBSTARIFF_MAP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SUBSTARIFF_MAP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SUBSTARIFF_MAP.MODIFBY is 'MODIFBY'
/

comment on column INT_SUBSTARIFF_MAP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SUBSTARIFF_MAP.MODIFIED is 'MODIFIED'
/

comment on column INT_SUBSTARIFF_MAP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_CONTENT                                        
-- ============================================================
drop table INT_CONTENT cascade constraints;

create table INT_CONTENT
(
    CONTENTPROVIDER          NUMBER(9)              not null,
    CONTENTCODE              VARCHAR2(8)            not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    NAME                     VARCHAR2(30)           null    ,
    TARIFFMODEL              NUMBER(9)              not null,
    SHARRING                 NUMBER(4)              default 0 not null,
    CURRENCY                 VARCHAR2(3)            default 'DEM' not null,
    GLACCOUNT                VARCHAR2(10)           not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CONTENT check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CNT primary key (CONTENTPROVIDER, CONTENTCODE)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_CONTENT to INTEGRATE_ROLE_ALL
/
grant select on INT_CONTENT to INTEGRATE_ROLE_SEL
/

comment on table INT_CONTENT is 'content table, defines content codes (e.g. premium rate, shared coast, freephone, etc.) for content-provider rating'
/

comment on column INT_CONTENT.CONTENTPROVIDER is 'reference to a related content provider associated to this special number'
/

comment on column INT_CONTENT.CONTENTCODE is 'content product code (e.g. a value added service or a'
/

comment on column INT_CONTENT.VALID_FROM is 'date from when on this content should be evaluated'
/

comment on column INT_CONTENT.VALID_TO is 'date till when the content is active'
/

comment on column INT_CONTENT.NAME is 'name or description'
/

comment on column INT_CONTENT.TARIFFMODEL is 'reference to the tariff model which should be used'
/

comment on column INT_CONTENT.SHARRING is 'defines a possible sharring rate for this content product (e.g. 1200 for 12,00%)'
/

comment on column INT_CONTENT.CURRENCY is 'overwrites the default content provider currency for this specific product; if empty the no currency is valid'
/

comment on column INT_CONTENT.GLACCOUNT is 'g/l account which applies to this poduct'
/

comment on column INT_CONTENT.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CONTENT.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CONTENT.MODIFBY is 'MODIFBY'
/

comment on column INT_CONTENT.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CONTENT.MODIFIED is 'MODIFIED'
/

comment on column INT_CONTENT.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_TARIFFMODEL_VER                                
-- ============================================================
drop table INT_TARIFFMODEL_VER cascade constraints;

create table INT_TARIFFMODEL_VER
(
    TARIFFMODEL              NUMBER(9)              not null,
    VERSION                  NUMBER(9)              not null,
    VALID_FROM               DATE                   not null,
    STATUS                   CHAR(1)                default 'D' not null
        constraint CKC_STATUS_INT_TARIFFMODEL_VE check (STATUS in ('A','D','T','S')),
    ZONEMODEL                NUMBER(9)              not null,
    BASIC_TARIFFMODEL        NUMBER(9)              null    ,
    BASIC_VERSION            NUMBER(9)              null    ,
    BASIC                    NUMBER(1)              default 1 not null
        constraint CKC_BASIC_INT_TARIFFMODEL_VE check (BASIC in (0,1)),
    DISCOUNTMODEL            NUMBER(9)              null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TARIFFMODEL_V check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TMV primary key (TARIFFMODEL, VERSION)
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
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_TARIFFMODEL_VER to INTEGRATE_ROLE_ALL
/
grant select on INT_TARIFFMODEL_VER to INTEGRATE_ROLE_SEL
/

comment on table INT_TARIFFMODEL_VER is 'defines different versions of a tariff model'
/

comment on column INT_TARIFFMODEL_VER.TARIFFMODEL is 'reference to the tariff model definition'
/

comment on column INT_TARIFFMODEL_VER.VERSION is 'actual version of this tariff model'
/

comment on column INT_TARIFFMODEL_VER.VALID_FROM is 'date from when on this version is valid'
/

comment on column INT_TARIFFMODEL_VER.STATUS is 'status of this tariff model version (A=active, D=deactive, T=test, S=simulation)'
/

comment on column INT_TARIFFMODEL_VER.ZONEMODEL is 'which zone model is related to this tariff model'
/

comment on column INT_TARIFFMODEL_VER.BASIC_TARIFFMODEL is 'pointer to the basic tariff model (enables delta tariff model definitions)'
/

comment on column INT_TARIFFMODEL_VER.BASIC_VERSION is 'pointer to the basic tariff model version (enables delta tariff model definitions)'
/

comment on column INT_TARIFFMODEL_VER.BASIC is 'is this tariff model a basic one (1=yes, not referenced by another tariff model, 0=no)'
/

comment on column INT_TARIFFMODEL_VER.DISCOUNTMODEL is 'references an optional and default discountmodel, which should be used with this tariffmodel, if no specific customer discount has been specified'
/

comment on column INT_TARIFFMODEL_VER.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TARIFFMODEL_VER.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TARIFFMODEL_VER.MODIFBY is 'MODIFBY'
/

comment on column INT_TARIFFMODEL_VER.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TARIFFMODEL_VER.MODIFIED is 'MODIFIED'
/

comment on column INT_TARIFFMODEL_VER.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_NETWORKMODEL                                   
-- ============================================================
drop table INT_NETWORKMODEL cascade constraints;

create table INT_NETWORKMODEL
(
    NETWORKMODEL             NUMBER(9)              not null,
    CODE                     VARCHAR2(10)           not null,
    NAME                     VARCHAR2(30)           null    ,
    CALCMODE                 CHAR(1)                default '3' not null
        constraint CKC_CALCMODE_INT_NETWORKMODEL check (CALCMODE in ('1','2','3','4','5','6')),
    MODELTYPE                CHAR(1)                default 'C' not null
        constraint CKC_MODELTYP_INT_NETWORKMODEL check (MODELTYPE in ('C','R','O')),
    USE_SWITCH_FOR_IDENT     NUMBER(1)              default 0 not null
        constraint CKC_USE_SWIT_INT_NETWORKMODEL check (USE_SWITCH_FOR_IDENT in (0,1)),
    USE_FIXCOST              NUMBER(1)              default 0 not null
        constraint CKC_USE_FIXC_INT_NETWORKMODEL check (USE_FIXCOST in (0,1)),
    SYSTEM_BRAND             VARCHAR2(5)            null    ,
    TARIFFMODEL              NUMBER(9)              null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_NETWORKMODEL check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_NWM primary key (NETWORKMODEL)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_NETWORKMODEL to INTEGRATE_ROLE_ALL
/
grant select on INT_NETWORKMODEL to INTEGRATE_ROLE_SEL
/

comment on table INT_NETWORKMODEL is 'defines different networkmodels, a model defines a physical network layout with all pois'
/

comment on column INT_NETWORKMODEL.NETWORKMODEL is 'unique internal model id'
/

comment on column INT_NETWORKMODEL.CODE is 'just a name'
/

comment on column INT_NETWORKMODEL.NAME is 'description'
/

comment on column INT_NETWORKMODEL.CALCMODE is 'defines how the tariff should be calculated (1=in, 2=out, 3=in+out, 4=in+transit+out, 5=in+transit, 6=transit+out)'
/

comment on column INT_NETWORKMODEL.MODELTYPE is 'the type of the model (C=Carrier-Interconnect, R=Reseller-Interconnect, 0=Reseller-Roaming)'
/

comment on column INT_NETWORKMODEL.USE_SWITCH_FOR_IDENT is 'if set to true, switch information is available and is used for product identification'
/

comment on column INT_NETWORKMODEL.USE_FIXCOST is 'if set to true, network information is available and is used for product identification'
/

comment on column INT_NETWORKMODEL.SYSTEM_BRAND is 'references a system/brand'
/

comment on column INT_NETWORKMODEL.TARIFFMODEL is 'references the tariff model which should be used for (reseller or carrier) interconnection purpose'
/

comment on column INT_NETWORKMODEL.ENTRYBY is 'ENTRYBY'
/

comment on column INT_NETWORKMODEL.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_NETWORKMODEL.MODIFBY is 'MODIFBY'
/

comment on column INT_NETWORKMODEL.MODIFDATE is 'MODIFDATE'
/

comment on column INT_NETWORKMODEL.MODIFIED is 'MODIFIED'
/

comment on column INT_NETWORKMODEL.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_POI                                            
-- ============================================================
drop table INT_POI cascade constraints;

create table INT_POI
(
    NETWORKMODEL             NUMBER(9)              not null,
    POI                      VARCHAR2(15)           not null,
    NAME                     VARCHAR2(30)           null    ,
    AREACODE                 VARCHAR2(40)           not null,
    UTC_TIME_OFFSET          VARCHAR2(5)            null    ,
    STATUS                   CHAR(1)                default 'A' not null
        constraint CKC_STATUS_INT_POI check (STATUS in ('A','D')),
    SWITCH                   VARCHAR2(15)           not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_POI check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_POI primary key (NETWORKMODEL, POI)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_POI to INTEGRATE_ROLE_ALL
/
grant select on INT_POI to INTEGRATE_ROLE_SEL
/

comment on table INT_POI is 'definition off all trunk related points of interconnect'
/

comment on column INT_POI.NETWORKMODEL is 'references the related network model'
/

comment on column INT_POI.POI is 'uniquely identifies a poi'
/

comment on column INT_POI.NAME is 'name or description'
/

comment on column INT_POI.AREACODE is 'area code for this poi (for use with standard or reseller-ic/ic zone models)'
/

comment on column INT_POI.UTC_TIME_OFFSET is 'utc time offset for this poi (+/-HHMM)'
/

comment on column INT_POI.STATUS is 'status of the network-element (A=active, D=deactive)'
/

comment on column INT_POI.SWITCH is 'references the switch this poi is related to'
/

comment on column INT_POI.ENTRYBY is 'ENTRYBY'
/

comment on column INT_POI.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_POI.MODIFBY is 'MODIFBY'
/

comment on column INT_POI.MODIFDATE is 'MODIFDATE'
/

comment on column INT_POI.MODIFIED is 'MODIFIED'
/

comment on column INT_POI.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_CALLTYPE_MAP                                   
-- ============================================================
drop table INT_CALLTYPE_MAP cascade constraints;

create table INT_CALLTYPE_MAP
(
    MAP_GROUP                VARCHAR2(10)           not null,
    RANK                     NUMBER(9)              not null,
    CALLTYPE                 VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    COMPAREPATTERN           VARCHAR2(4000)         null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CALLTYPE_MAP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CTM primary key (MAP_GROUP, RANK)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_CALLTYPE_MAP to INTEGRATE_ROLE_ALL
/
grant select on INT_CALLTYPE_MAP to INTEGRATE_ROLE_SEL
/

comment on table INT_CALLTYPE_MAP is 'calltype mapping table, defines per edr format how a call type should be generated'
/

comment on column INT_CALLTYPE_MAP.MAP_GROUP is 'reference to the logical map-group code, mapping is defined for that edr format'
/

comment on column INT_CALLTYPE_MAP.RANK is 'rank, defines the order sequence in which the compare patterns will be evaluated'
/

comment on column INT_CALLTYPE_MAP.CALLTYPE is 'unique calltype value, as it should be resulted'
/

comment on column INT_CALLTYPE_MAP.NAME is 'description just for info'
/

comment on column INT_CALLTYPE_MAP.COMPAREPATTERN is 'condition: the compare pattern as a comma seperated string (for each pattern field)'
/

comment on column INT_CALLTYPE_MAP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CALLTYPE_MAP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CALLTYPE_MAP.MODIFBY is 'MODIFBY'
/

comment on column INT_CALLTYPE_MAP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CALLTYPE_MAP.MODIFIED is 'MODIFIED'
/

comment on column INT_CALLTYPE_MAP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_CLASSTYPEZONE_MAP                              
-- ============================================================
drop table INT_CLASSTYPEZONE_MAP cascade constraints;

create table INT_CLASSTYPEZONE_MAP
(
    CZT_GROUP                VARCHAR2(10)           not null,
    ZONEMODEL                NUMBER(9)              not null,
    RANK                     NUMBER(9)              not null,
    VALID_FROM               VARCHAR2(8)            not null,
    VALID_TO                 VARCHAR2(8)            null    ,
    TIME_FROM                VARCHAR2(5)            null    ,
    TIME_TO                  VARCHAR2(5)            null    ,
    QUANTITY_VALUE           NUMBER(9)              null    ,
    MIN_AOC_AMOUNT           NUMBER                 null    ,
    MAX_AOC_AMOUNT           NUMBER                 null    ,
    CALLCLASS                VARCHAR2(2000)         default '*' not null,
    CALLTYPE                 VARCHAR2(2000)         default '*' not null,
    SERVICECODE              VARCHAR2(2000)         default '*' not null,
    SERVICECLASS             VARCHAR2(2000)         default '*' not null,
    ZONE_WS                  VARCHAR2(2000)         default '*' not null,
    ZONE_RT                  VARCHAR2(2000)         default '*' not null,
    NEW_CALLTYPE             VARCHAR2(5)            null    ,
    NEW_ZONE_WS              VARCHAR2(5)            null    ,
    NEW_ZONE_RT              VARCHAR2(5)            null    ,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CLASSTYPEZONE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CZT primary key (CZT_GROUP, ZONEMODEL, RANK)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_CLASSTYPEZONE_MAP to INTEGRATE_ROLE_ALL
/
grant select on INT_CLASSTYPEZONE_MAP to INTEGRATE_ROLE_SEL
/

comment on table INT_CLASSTYPEZONE_MAP is 'mapping table for callclass/calltype/zone to new calltype, zone'
/

comment on column INT_CLASSTYPEZONE_MAP.CZT_GROUP is 'references the mapping group the configuration is bound to'
/

comment on column INT_CLASSTYPEZONE_MAP.ZONEMODEL is 'reference to the zone model, this mapping is related to'
/

comment on column INT_CLASSTYPEZONE_MAP.RANK is 'defines the mapping order for the single entries'
/

comment on column INT_CLASSTYPEZONE_MAP.VALID_FROM is 'this mapping entry is valid from (Format: YYYYMMDD or MON-SUN[HH:SS]) (compare: >=)'
/

comment on column INT_CLASSTYPEZONE_MAP.VALID_TO is 'defines the date till when this entry is valid (Format: YYYYMMDD or MON-SUN[HH:SS]) (compare: <)'
/

comment on column INT_CLASSTYPEZONE_MAP.TIME_FROM is 'optional time, within the given valid_date, when the mapping should take place (Format: HH:SS) (compare: >=)'
/

comment on column INT_CLASSTYPEZONE_MAP.TIME_TO is 'optional time, within the given valid_date, when the mapping should take place (Format: HH:SS) (compare: <)'
/

comment on column INT_CLASSTYPEZONE_MAP.QUANTITY_VALUE is 'optional Quantity-Value (e.g. Duration), the mapping only takes place, if the cdr-value is smaller or equal'
/

comment on column INT_CLASSTYPEZONE_MAP.MIN_AOC_AMOUNT is 'optional minimal AoC-Amount-Value (e.g. Wholesale-Charge), the mapping only takes place, if the cdr-value is greater or equal'
/

comment on column INT_CLASSTYPEZONE_MAP.MAX_AOC_AMOUNT is 'optional maximal AoC-Amount-Value (e.g. Wholesale-Charge), the mapping only takes place, if the cdr-value is smaller or equal'
/

comment on column INT_CLASSTYPEZONE_MAP.CALLCLASS is 'condition: the call classification which should be mapped (if empty all match)'
/

comment on column INT_CLASSTYPEZONE_MAP.CALLTYPE is 'condition: the call type which should be mapped (if empty all match)'
/

comment on column INT_CLASSTYPEZONE_MAP.SERVICECODE is 'condition: the servicecode which should be mapped (if empty all match)'
/

comment on column INT_CLASSTYPEZONE_MAP.SERVICECLASS is 'condition: the serviceclass which should be mapped (if empty all match)'
/

comment on column INT_CLASSTYPEZONE_MAP.ZONE_WS is 'condition: the wholesale zone which should be mapped (if empty all match)'
/

comment on column INT_CLASSTYPEZONE_MAP.ZONE_RT is 'condition: the retail zone which should be mapped (if empty all match)'
/

comment on column INT_CLASSTYPEZONE_MAP.NEW_CALLTYPE is 'result: returns the new calltype (if empty nothing changes)'
/

comment on column INT_CLASSTYPEZONE_MAP.NEW_ZONE_WS is 'result: returns the new wholesale zone (if empty nothing changes)'
/

comment on column INT_CLASSTYPEZONE_MAP.NEW_ZONE_RT is 'result: returns the new retail zone (if empty nothing changes)'
/

comment on column INT_CLASSTYPEZONE_MAP.NAME is 'NAME'
/

comment on column INT_CLASSTYPEZONE_MAP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CLASSTYPEZONE_MAP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CLASSTYPEZONE_MAP.MODIFBY is 'MODIFBY'
/

comment on column INT_CLASSTYPEZONE_MAP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CLASSTYPEZONE_MAP.MODIFIED is 'MODIFIED'
/

comment on column INT_CLASSTYPEZONE_MAP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_PRICEMODEL_STEP                                
-- ============================================================
drop table INT_PRICEMODEL_STEP cascade constraints;

create table INT_PRICEMODEL_STEP
(
    PRICEMODEL               NUMBER(9)              not null,
    VALID_FROM               DATE                   default sysdate not null,
    CHARGE_ITEM              CHAR(1)                default 'Q' not null
        constraint CKC_CHARGE_I_INT_PRICEMODEL_ST check (CHARGE_ITEM in ('Q','S','R','E')),
    STEP                     NUMBER(9)              not null,
    THRESHOLD_FROM           NUMBER                 not null,
    THRESHOLD_TO             NUMBER                 null    ,
    BEAT                     NUMBER(9)              not null,
    CHARGE                   NUMBER                 null    ,
    CHARGE_BASE              NUMBER(9)              default 1 not null,
    FRAME                    NUMBER(9)              null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_PRICEMODEL_ST check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_PMS primary key (PRICEMODEL, VALID_FROM, CHARGE_ITEM, STEP)
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
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_PRICEMODEL_STEP to INTEGRATE_ROLE_ALL
/
grant select on INT_PRICEMODEL_STEP to INTEGRATE_ROLE_SEL
/

comment on table INT_PRICEMODEL_STEP is 'price model rating steps (duration based price calculation)'
/

comment on column INT_PRICEMODEL_STEP.PRICEMODEL is 'reference to the price model these rating steps are related to'
/

comment on column INT_PRICEMODEL_STEP.VALID_FROM is 'VALID_FROM'
/

comment on column INT_PRICEMODEL_STEP.CHARGE_ITEM is 'defines if the pricemodel steps are related to Q=quantity, S=sent volume or R=received volume'
/

comment on column INT_PRICEMODEL_STEP.STEP is 'step id'
/

comment on column INT_PRICEMODEL_STEP.THRESHOLD_FROM is 'lower boundary in UoM of the related servicecode (compare: >), negativ values allowed'
/

comment on column INT_PRICEMODEL_STEP.THRESHOLD_TO is 'upper boundary in UoM of the related servicecode (compare: <=)'
/

comment on column INT_PRICEMODEL_STEP.BEAT is 'beat in seconds for this threshold'
/

comment on column INT_PRICEMODEL_STEP.CHARGE is 'charge for this beat within this threshold (charge without decimals)'
/

comment on column INT_PRICEMODEL_STEP.CHARGE_BASE is 'defines a charge base (e.g. a value of 60 means, that the charge value is base on 60 units, e.g. a minute)'
/

comment on column INT_PRICEMODEL_STEP.FRAME is 'frame id (used to group steps for splitting to find linear entries which can be split)'
/

comment on column INT_PRICEMODEL_STEP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_PRICEMODEL_STEP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_PRICEMODEL_STEP.MODIFBY is 'MODIFBY'
/

comment on column INT_PRICEMODEL_STEP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_PRICEMODEL_STEP.MODIFIED is 'MODIFIED'
/

comment on column INT_PRICEMODEL_STEP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_HOLIDAY                                        
-- ============================================================
drop table INT_HOLIDAY cascade constraints;

create table INT_HOLIDAY
(
    CALENDAR                 NUMBER(9)              not null,
    HOLIDAY                  DATE                   not null,
    RECURRING                NUMBER(1)              default 0 not null
        constraint CKC_RECURRIN_INT_HOLIDAY check (RECURRING in (0,1)),
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_HOLIDAY check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_HDY primary key (CALENDAR, HOLIDAY)
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
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_HOLIDAY to INTEGRATE_ROLE_ALL
/
grant select on INT_HOLIDAY to INTEGRATE_ROLE_SEL
/

comment on table INT_HOLIDAY is 'defines the holidays within a calendar to be used together with tariff models'
/

comment on column INT_HOLIDAY.CALENDAR is 'reference to the holiday calendar'
/

comment on column INT_HOLIDAY.HOLIDAY is 'date of the holiday'
/

comment on column INT_HOLIDAY.RECURRING is 'recurring date (1=Yes recurring every year only dd.mm is used from holiday, 0=No)'
/

comment on column INT_HOLIDAY.NAME is 'description of the calendar entry'
/

comment on column INT_HOLIDAY.ENTRYBY is 'ENTRYBY'
/

comment on column INT_HOLIDAY.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_HOLIDAY.MODIFBY is 'MODIFBY'
/

comment on column INT_HOLIDAY.MODIFDATE is 'MODIFDATE'
/

comment on column INT_HOLIDAY.MODIFIED is 'MODIFIED'
/

comment on column INT_HOLIDAY.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_TARIFFMODEL_CNF                                
-- ============================================================
drop table INT_TARIFFMODEL_CNF cascade constraints;

create table INT_TARIFFMODEL_CNF
(
    TARIFFMODEL              NUMBER(9)              not null,
    VERSION                  NUMBER(9)              not null,
    SERVICECODE              VARCHAR2(5)            not null,
    SERVICECLASS             VARCHAR2(5)            default '*' not null,
    ZONE                     VARCHAR2(5)            not null,
    TIMEMODEL                NUMBER(9)              not null,
    TIMEZONE                 NUMBER(9)              not null,
    PRICEMODEL               NUMBER(9)              not null,
    ALT_PRICEMODEL           NUMBER(9)              null    ,
    PASSTHROUGH              NUMBER(1)              default 0 not null
        constraint CKC_PASSTHRO_INT_TARIFFMODEL_C check (PASSTHROUGH in (0,1,2)),
    ADDON_TYPE               CHAR(1)                default 'P' not null
        constraint CKC_ADDON_TY_INT_TARIFFMODEL_C check (ADDON_TYPE in ('P','A','N')),
    ADDON_CHARGE             NUMBER                 default 0 not null,
    GLACCOUNT                VARCHAR2(10)           null    ,
    REVENUEGROUP             VARCHAR2(5)            null    ,
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TMC primary key (TARIFFMODEL, VERSION, SERVICECODE, SERVICECLASS, ZONE, TIMEMODEL, TIMEZONE)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_4_IDX
        storage
        (
        initial 4M
        next 4M
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
initial 8M
next 8M
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_TARIFFMODEL_CNF to INTEGRATE_ROLE_ALL
/
grant select on INT_TARIFFMODEL_CNF to INTEGRATE_ROLE_SEL
/

comment on table INT_TARIFFMODEL_CNF is 'tariff model configuration (main entry point for price calculation for a given tariff model, using service,zone,timemodel combinations)'
/

comment on column INT_TARIFFMODEL_CNF.TARIFFMODEL is 'reference to the tariff model version'
/

comment on column INT_TARIFFMODEL_CNF.VERSION is 'reference to the tariff model version'
/

comment on column INT_TARIFFMODEL_CNF.SERVICECODE is 'servicecode value for this entry'
/

comment on column INT_TARIFFMODEL_CNF.SERVICECLASS is 'default ''*'', but may define a special sub-service class, e.g. QoS as a combination of callclass, calltype ...'
/

comment on column INT_TARIFFMODEL_CNF.ZONE is 'zone value for this entry'
/

comment on column INT_TARIFFMODEL_CNF.TIMEMODEL is 'there is always only one timemodel detached to a zone'
/

comment on column INT_TARIFFMODEL_CNF.TIMEZONE is 'defines the different time zones (e.g. Mo-Fr8-18, Mo-Fr18-8, SaSo0-24)'
/

comment on column INT_TARIFFMODEL_CNF.PRICEMODEL is 'reference to the price model which should be used for the defined entry'
/

comment on column INT_TARIFFMODEL_CNF.ALT_PRICEMODEL is 'reference to alternative pricemodel which should be calculated in addition'
/

comment on column INT_TARIFFMODEL_CNF.PASSTHROUGH is 'use external price and addon charge (pass an original price contained within an edr through, 0=no, 1=use BasicDetail, 2=use Ass.Roamer)'
/

comment on column INT_TARIFFMODEL_CNF.ADDON_TYPE is 'type of the addon charge (P=percantage, A=addon value, N=new value)'
/

comment on column INT_TARIFFMODEL_CNF.ADDON_CHARGE is 'addon charge for the external reachthrough price'
/

comment on column INT_TARIFFMODEL_CNF.GLACCOUNT is 'references a specific usage based general ledger account code for this configuration entry'
/

comment on column INT_TARIFFMODEL_CNF.REVENUEGROUP is 'references a usage group (for splitted billing purposes)'
/

comment on column INT_TARIFFMODEL_CNF.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SPECIALDAY_LNK                                 
-- ============================================================
drop table INT_SPECIALDAY_LNK cascade constraints;

create table INT_SPECIALDAY_LNK
(
    TARIFFMODEL              NUMBER(9)              not null,
    VERSION                  NUMBER(9)              not null,
    SPECIALDAYRATE           NUMBER(9)              not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SPECIALDAY_LN check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SRL primary key (TARIFFMODEL, VERSION, SPECIALDAYRATE)
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
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_SPECIALDAY_LNK to INTEGRATE_ROLE_ALL
/
grant select on INT_SPECIALDAY_LNK to INTEGRATE_ROLE_SEL
/

comment on table INT_SPECIALDAY_LNK is 'link table between special day rates and tariff model versions'
/

comment on column INT_SPECIALDAY_LNK.TARIFFMODEL is 'reference to the tariff model version'
/

comment on column INT_SPECIALDAY_LNK.VERSION is 'reference to the tariff model version'
/

comment on column INT_SPECIALDAY_LNK.SPECIALDAYRATE is 'reference to the special day rates this which are all valid for this tariff model version'
/

comment on column INT_SPECIALDAY_LNK.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SPECIALDAY_LNK.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SPECIALDAY_LNK.MODIFBY is 'MODIFBY'
/

comment on column INT_SPECIALDAY_LNK.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SPECIALDAY_LNK.MODIFIED is 'MODIFIED'
/

comment on column INT_SPECIALDAY_LNK.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_TIMEMODEL_LNK                                  
-- ============================================================
drop table INT_TIMEMODEL_LNK cascade constraints;

create table INT_TIMEMODEL_LNK
(
    TIMEMODEL                NUMBER(9)              not null,
    DAYCODE                  NUMBER(9)              not null,
    INTERVAL                 NUMBER(9)              not null,
    VALID_FROM               DATE                   not null,
    TIMEZONE                 NUMBER(9)              not null,
    VALID_TO                 DATE                   null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TIMEMODEL_LNK check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TML primary key (TIMEMODEL, DAYCODE, INTERVAL, VALID_FROM)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_4_IDX
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
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_TIMEMODEL_LNK to INTEGRATE_ROLE_ALL
/
grant select on INT_TIMEMODEL_LNK to INTEGRATE_ROLE_SEL
/

comment on table INT_TIMEMODEL_LNK is 'link table defines for a given time model all possible time zone combinations (in conjuction with a time interval and daycode)'
/

comment on column INT_TIMEMODEL_LNK.TIMEMODEL is 'TIMEMODEL'
/

comment on column INT_TIMEMODEL_LNK.DAYCODE is 'DAYCODE'
/

comment on column INT_TIMEMODEL_LNK.INTERVAL is 'INTERVAL'
/

comment on column INT_TIMEMODEL_LNK.VALID_FROM is 'date from when on this configuration is valid'
/

comment on column INT_TIMEMODEL_LNK.TIMEZONE is 'TIMEZONE'
/

comment on column INT_TIMEMODEL_LNK.VALID_TO is 'date til when this configuration entry is valid'
/

comment on column INT_TIMEMODEL_LNK.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TIMEMODEL_LNK.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TIMEMODEL_LNK.MODIFBY is 'MODIFBY'
/

comment on column INT_TIMEMODEL_LNK.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TIMEMODEL_LNK.MODIFIED is 'MODIFIED'
/

comment on column INT_TIMEMODEL_LNK.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_STANDARD_ZONE                                  
-- ============================================================
drop table INT_STANDARD_ZONE cascade constraints;

create table INT_STANDARD_ZONE
(
    ZONEMODEL                NUMBER(9)              not null,
    ORIGIN_AREACODE          VARCHAR2(40)           not null,
    DESTIN_AREACODE          VARCHAR2(40)           not null,
    SERVICECODE              VARCHAR2(5)            not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    ZONE_WS                  VARCHAR2(5)            not null,
    ZONE_RT                  VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ALT_ZONEMODEL            NUMBER(9)              null    ,
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_STZ primary key (ZONEMODEL, ORIGIN_AREACODE, DESTIN_AREACODE, SERVICECODE, VALID_FROM)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_3_IDX
        storage
        (
        initial 12M
        next 4M
        minextents 1
        maxextents unlimited
        pctincrease 0
     )
)
pctfree 10
pctused 65
initrans 2
storage
(
initial 16M
next 8M
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_3_DAT
/
grant select, insert, update, delete on INT_STANDARD_ZONE to INTEGRATE_ROLE_ALL
/
grant select on INT_STANDARD_ZONE to INTEGRATE_ROLE_SEL
/

comment on table INT_STANDARD_ZONE is 'zone definition table for standard zone models (defines the origin-destination relationship)'
/

comment on column INT_STANDARD_ZONE.ZONEMODEL is 'internal ID, reference to the zone model, this entry is related to'
/

comment on column INT_STANDARD_ZONE.ORIGIN_AREACODE is 'source cli range (in international notation, e.g. 0049171)'
/

comment on column INT_STANDARD_ZONE.DESTIN_AREACODE is 'destination cli range (in international notation, e.g. 004919012345)'
/

comment on column INT_STANDARD_ZONE.SERVICECODE is 'the internal service code, this entry is related to'
/

comment on column INT_STANDARD_ZONE.VALID_FROM is 'defines the starting date this entry is valid from'
/

comment on column INT_STANDARD_ZONE.VALID_TO is 'defines the date till when this entry is valid'
/

comment on column INT_STANDARD_ZONE.ZONE_WS is 'link to the result zone value (wholesale)'
/

comment on column INT_STANDARD_ZONE.ZONE_RT is 'link to the result zone value (retail)'
/

comment on column INT_STANDARD_ZONE.NAME is 'description of the zone entry'
/

comment on column INT_STANDARD_ZONE.ALT_ZONEMODEL is 'internal ID, reference to an alternative zone model'
/

comment on column INT_STANDARD_ZONE.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_GEOGRAPHICAL_ZONE                              
-- ============================================================
drop table INT_GEOGRAPHICAL_ZONE cascade constraints;

create table INT_GEOGRAPHICAL_ZONE
(
    ZONEMODEL                NUMBER(9)              not null,
    DISTANCE                 NUMBER                 not null,
    SERVICECODE              VARCHAR2(5)            not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    ZONE_WS                  VARCHAR2(5)            not null,
    ZONE_RT                  VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ALT_ZONEMODEL            NUMBER(9)              null    ,
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_GOZ primary key (ZONEMODEL, DISTANCE, SERVICECODE, VALID_FROM)
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
tablespace INTEGRATE_TS_3_DAT
/
grant select, insert, update, delete on INT_GEOGRAPHICAL_ZONE to INTEGRATE_ROLE_ALL
/
grant select on INT_GEOGRAPHICAL_ZONE to INTEGRATE_ROLE_SEL
/

comment on table INT_GEOGRAPHICAL_ZONE is 'geographical distance translation table (translates a distance into a zone value)'
/

comment on column INT_GEOGRAPHICAL_ZONE.ZONEMODEL is 'internal ID (references to the related zone model)'
/

comment on column INT_GEOGRAPHICAL_ZONE.DISTANCE is 'the distance (upper boundary) which should be translated'
/

comment on column INT_GEOGRAPHICAL_ZONE.SERVICECODE is 'SERVICECODE'
/

comment on column INT_GEOGRAPHICAL_ZONE.VALID_FROM is 'VALID_FROM'
/

comment on column INT_GEOGRAPHICAL_ZONE.VALID_TO is 'defines the date till when this entry is valid'
/

comment on column INT_GEOGRAPHICAL_ZONE.ZONE_WS is 'reference pointer to the zone value definition table (wholesales)'
/

comment on column INT_GEOGRAPHICAL_ZONE.ZONE_RT is 'reference pointer to the zone value definition table (retail)'
/

comment on column INT_GEOGRAPHICAL_ZONE.NAME is 'description of the zone entry'
/

comment on column INT_GEOGRAPHICAL_ZONE.ALT_ZONEMODEL is 'internal ID'
/

comment on column INT_GEOGRAPHICAL_ZONE.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SEGZONE_LNK                                    
-- ============================================================
drop table INT_SEGZONE_LNK cascade constraints;

create table INT_SEGZONE_LNK
(
    SEGMENT                  VARCHAR2(5)            not null,
    VALID_FROM               DATE                   not null,
    ZONEMODEL                NUMBER(9)              not null,
    VALID_TO                 DATE                   null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SEGZONE_LNK check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SZL primary key (SEGMENT, VALID_FROM, ZONEMODEL)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_SEGZONE_LNK to INTEGRATE_ROLE_ALL
/
grant select on INT_SEGZONE_LNK to INTEGRATE_ROLE_SEL
/

comment on table INT_SEGZONE_LNK is 'link table, defines which zone models have to be evaluated for a segment'
/

comment on column INT_SEGZONE_LNK.SEGMENT is 'reference to the segment (for which the following models have to be evaluated)'
/

comment on column INT_SEGZONE_LNK.VALID_FROM is 'date from when on this configuration is valid'
/

comment on column INT_SEGZONE_LNK.ZONEMODEL is 'the zone models which have to be evaluated for the specified segment'
/

comment on column INT_SEGZONE_LNK.VALID_TO is 'date until this entry is valid'
/

comment on column INT_SEGZONE_LNK.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SEGZONE_LNK.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SEGZONE_LNK.MODIFBY is 'MODIFBY'
/

comment on column INT_SEGZONE_LNK.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SEGZONE_LNK.MODIFIED is 'MODIFIED'
/

comment on column INT_SEGZONE_LNK.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_POIAREA_LNK                                    
-- ============================================================
drop table INT_POIAREA_LNK cascade constraints;

create table INT_POIAREA_LNK
(
    NETWORKMODEL             NUMBER(9)              not null,
    POI                      VARCHAR2(15)           not null,
    VALID_FROM               DATE                   not null,
    AREACODE                 VARCHAR2(40)           not null,
    VALID_TO                 DATE                   null    ,
    constraint PK_INT_PAL primary key (NETWORKMODEL, POI, VALID_FROM, AREACODE)
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
initial 512K
next 512K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_POIAREA_LNK to INTEGRATE_ROLE_ALL
/
grant select on INT_POIAREA_LNK to INTEGRATE_ROLE_SEL
/

comment on table INT_POIAREA_LNK is 'defines all areacodes related to a given virtual poi (only for reseller-interconnection)'
/

comment on column INT_POIAREA_LNK.NETWORKMODEL is 'reference to the related networkmodel'
/

comment on column INT_POIAREA_LNK.POI is 'reference to the related poi'
/

comment on column INT_POIAREA_LNK.VALID_FROM is 'date when this entry is valid from'
/

comment on column INT_POIAREA_LNK.AREACODE is 'list of all area codes for this poi'
/

comment on column INT_POIAREA_LNK.VALID_TO is 'defines the date till when this entry is valid'
/


-- ============================================================
--   Table: INT_GEOAREACODE_LNK                                
-- ============================================================
drop table INT_GEOAREACODE_LNK cascade constraints;

create table INT_GEOAREACODE_LNK
(
    GEOMODEL                 INTEGER                not null,
    AREACODE                 VARCHAR2(40)           not null,
    NAME                     VARCHAR2(30)           null    ,
    LONGITUDE                NUMBER                 null    ,
    LATITUDE                 NUMBER                 null    ,
    constraint PK_INT_GAL primary key (GEOMODEL, AREACODE)
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
tablespace INTEGRATE_TS_3_DAT
/
grant select, insert, update, delete on INT_GEOAREACODE_LNK to INTEGRATE_ROLE_ALL
/
grant select on INT_GEOAREACODE_LNK to INTEGRATE_ROLE_SEL
/

comment on table INT_GEOAREACODE_LNK is 'link table, defines the geographical coordinates per virtual or physical areacode'
/

comment on column INT_GEOAREACODE_LNK.GEOMODEL is 'GEOMODEL'
/

comment on column INT_GEOAREACODE_LNK.AREACODE is 'the area code the coordinates are valid for'
/

comment on column INT_GEOAREACODE_LNK.NAME is 'description for the defined area code'
/

comment on column INT_GEOAREACODE_LNK.LONGITUDE is 'north coordinates'
/

comment on column INT_GEOAREACODE_LNK.LATITUDE is 'east coordinates'
/


-- ============================================================
--   Table: INT_SERVICECODE_MAP                                
-- ============================================================
drop table INT_SERVICECODE_MAP cascade constraints;

create table INT_SERVICECODE_MAP
(
    MAP_GROUP                VARCHAR2(10)           not null,
    RANK                     NUMBER(9)              not null,
    NAME                     VARCHAR2(30)           null    ,
    EXT_SERVICECODE          VARCHAR2(2000)         default '*' not null,
    CALLCLASS                VARCHAR2(2000)         default '*' not null,
    LOCARIND_VASEVENT        VARCHAR2(2000)         default '*' not null,
    QOS_REQUESTED            VARCHAR2(2000)         default '*' not null,
    QOS_USED                 VARCHAR2(2000)         default '*' not null,
    RECORDTYPE               VARCHAR2(2000)         default '*' not null,
    INT_SERVICECODE          VARCHAR2(5)            not null,
    INT_SERVICECLASS         VARCHAR2(5)            not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SERVICECODE_M check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SVM primary key (MAP_GROUP, RANK)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_SERVICECODE_MAP to INTEGRATE_ROLE_ALL
/
grant select on INT_SERVICECODE_MAP to INTEGRATE_ROLE_SEL
/

comment on table INT_SERVICECODE_MAP is 'service code mapping table, maps an external edr specific servicecode to an internal servicecode'
/

comment on column INT_SERVICECODE_MAP.MAP_GROUP is 'reference to the logical map-group code, mapping is defined for that edr format'
/

comment on column INT_SERVICECODE_MAP.RANK is 'defines the sequence order in which the mapping will be performed'
/

comment on column INT_SERVICECODE_MAP.NAME is 'name or description of the edr specific servicecode'
/

comment on column INT_SERVICECODE_MAP.EXT_SERVICECODE is 'external service code (used within the edr format) that should be mapped'
/

comment on column INT_SERVICECODE_MAP.CALLCLASS is 'defines the callclass'' which should be used as an add. maping rule (empty maps all), wildcards allowed'
/

comment on column INT_SERVICECODE_MAP.LOCARIND_VASEVENT is 'defines the location area indicator/vas-/event-code which should be used as an add. maping rule (empty maps all), wildcards allowed'
/

comment on column INT_SERVICECODE_MAP.QOS_REQUESTED is 'defines the quality-of-service which should be used as an add. maping rule (empty maps all), wildcards allowed'
/

comment on column INT_SERVICECODE_MAP.QOS_USED is 'defines the quality-of-service which should be used as an add. maping rule (empty maps all), wildcards allowed'
/

comment on column INT_SERVICECODE_MAP.RECORDTYPE is 'defines the record types which should be used as an add. maping rule (empty maps all), wildcards allowed'
/

comment on column INT_SERVICECODE_MAP.INT_SERVICECODE is 'mapping value, unique generic service code which can be used'
/

comment on column INT_SERVICECODE_MAP.INT_SERVICECLASS is 'mapping value, unique generic service class which can be used'
/

comment on column INT_SERVICECODE_MAP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SERVICECODE_MAP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SERVICECODE_MAP.MODIFBY is 'MODIFBY'
/

comment on column INT_SERVICECODE_MAP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SERVICECODE_MAP.MODIFIED is 'MODIFIED'
/

comment on column INT_SERVICECODE_MAP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_CALLCLASS_MAP                                  
-- ============================================================
drop table INT_CALLCLASS_MAP cascade constraints;

create table INT_CALLCLASS_MAP
(
    MAP_GROUP                VARCHAR2(10)           not null,
    RANK                     NUMBER(9)              not null,
    EXT_CALLCLASS            VARCHAR2(2000)         default '*' not null,
    CALLTYPE                 VARCHAR2(2000)         default '*' not null,
    AOCZONE                  VARCHAR2(2000)         default '*' not null,
    TARIFFCLASS              VARCHAR2(2000)         default '*' not null,
    TARIFFSUBCLASS           VARCHAR2(2000)         default '*' not null,
    RECORDTYPE               VARCHAR2(2000)         default '*' not null,
    CONNECTTYPE              VARCHAR2(2000)         default '*' not null,
    CONNECTSUBTYPE           VARCHAR2(255)          default '*' not null,
    APPLICATION              VARCHAR2(2000)         default '*' not null,
    TRANSIT_AREACODE         VARCHAR2(2000)         default '*' not null,
    NAME                     VARCHAR2(30)           null    ,
    INT_CALLCLASS            VARCHAR2(5)            not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CALLCLASS_MAP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CCM primary key (MAP_GROUP, RANK)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_CALLCLASS_MAP to INTEGRATE_ROLE_ALL
/
grant select on INT_CALLCLASS_MAP to INTEGRATE_ROLE_SEL
/

comment on table INT_CALLCLASS_MAP is 'callclass mapping table, maps an external edr specific callclass to an internal callclass'
/

comment on column INT_CALLCLASS_MAP.MAP_GROUP is 'reference to the logical map-group code, mapping is defined for that edr format'
/

comment on column INT_CALLCLASS_MAP.RANK is 'defines the sequence order in which the mapping will be performed'
/

comment on column INT_CALLCLASS_MAP.EXT_CALLCLASS is 'external call classification code (used within the edr format) that should be mapped'
/

comment on column INT_CALLCLASS_MAP.CALLTYPE is 'external call type (used within the edr format) that should be mapped'
/

comment on column INT_CALLCLASS_MAP.AOCZONE is 'external AoC Zone (used within the edr format) that should be mapped'
/

comment on column INT_CALLCLASS_MAP.TARIFFCLASS is 'external tariff class (used within the edr format) that should be mapped'
/

comment on column INT_CALLCLASS_MAP.TARIFFSUBCLASS is 'external tariff sub class (used within the edr format) that should be mapped'
/

comment on column INT_CALLCLASS_MAP.RECORDTYPE is 'external record type (used within the edr format) that should be mapped'
/

comment on column INT_CALLCLASS_MAP.CONNECTTYPE is 'external connect type (used within the edr format) that should be mapped'
/

comment on column INT_CALLCLASS_MAP.CONNECTSUBTYPE is 'external connect subtype type (used within the edr format) that should be mapped'
/

comment on column INT_CALLCLASS_MAP.APPLICATION is 'external application (used within the edr format) that should be mapped'
/

comment on column INT_CALLCLASS_MAP.TRANSIT_AREACODE is 'external c-number (used within the edr format) that should be mapped'
/

comment on column INT_CALLCLASS_MAP.NAME is 'name or description of the edr specific call classification'
/

comment on column INT_CALLCLASS_MAP.INT_CALLCLASS is 'mapping value, unique generic call classification code which can be used'
/

comment on column INT_CALLCLASS_MAP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CALLCLASS_MAP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CALLCLASS_MAP.MODIFBY is 'MODIFBY'
/

comment on column INT_CALLCLASS_MAP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CALLCLASS_MAP.MODIFIED is 'MODIFIED'
/

comment on column INT_CALLCLASS_MAP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SUBS_LOCAL                                     
-- ============================================================
drop table INT_SUBS_LOCAL cascade constraints;

create table INT_SUBS_LOCAL
(
    CONTRACT                 NUMBER(38)             not null,
    VALID_FROM               DATE                   not null,
    DESTIN_CLI               VARCHAR2(40)           not null,
    VALID_TO                 DATE                   null    ,
    CLITYPE                  CHAR(1)                default 'H' not null
        constraint CKC_CLITYPE_INT_SUBS_LOCAL check (CLITYPE in ('H','F','C')),
    constraint PK_INT_LOC primary key (CONTRACT, VALID_FROM, DESTIN_CLI)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_2_IDX
        storage
        (
        initial 1M
        next 1M
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
initial 2M
next 2M
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_SUBS_LOCAL to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBS_LOCAL to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBS_LOCAL is 'subscriber related local numbers, defines friends and family and/or home-regions'
/

comment on column INT_SUBS_LOCAL.CONTRACT is 'logical reference to the subscriber table (contract id for the subscriber-cli)'
/

comment on column INT_SUBS_LOCAL.VALID_FROM is 'Date from when on this entry is valid'
/

comment on column INT_SUBS_LOCAL.DESTIN_CLI is 'cli or area code for the subscribers home regions or friends and family numbers'
/

comment on column INT_SUBS_LOCAL.VALID_TO is 'date til when this entry is valid to'
/

comment on column INT_SUBS_LOCAL.CLITYPE is 'defines the kind of destination cli (''H''=Homeregion, ''F''=FriendsFamily, ''C''=Cell-Id)'
/


-- ============================================================
--   Table: INT_TARIFFDISCOUNT_LNK                             
-- ============================================================
drop table INT_TARIFFDISCOUNT_LNK cascade constraints;

create table INT_TARIFFDISCOUNT_LNK
(
    TARIFFMODEL              NUMBER(9)              not null,
    VERSION                  NUMBER(9)              not null,
    RANK                     NUMBER(9)              not null,
    VALID_FROM               VARCHAR2(8)            not null,
    VALID_TO                 VARCHAR2(8)            null    ,
    TIME_FROM                VARCHAR2(5)            null    ,
    TIME_TO                  VARCHAR2(5)            null    ,
    QUANTITY_VALUE           NUMBER(9)              null    ,
    CALLCLASS                VARCHAR2(2000)         default '*' not null,
    CALLTYPE                 VARCHAR2(2000)         default '*' not null,
    SERVICECODE              VARCHAR2(2000)         default '*' not null,
    SERVICECLASS             VARCHAR2(2000)         default '*' not null,
    ZONE                     VARCHAR2(2000)         default '*' not null,
    SOURCE_NETWORK           VARCHAR2(2000)         default '*' not null,
    DESTIN_NETWORK           VARCHAR2(2000)         default '*' not null,
    DISCOUNT_TYPE            CHAR(1)                default 'P' not null
        constraint CKC_DISCOUNT_INT_TARIFFDISCOUN check (DISCOUNT_TYPE in ('P','A','N')),
    DISCOUNT_VALUE           NUMBER                 not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TARIFFDISCOUN check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TDL primary key (TARIFFMODEL, VERSION, RANK)
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
tablespace INTEGRATE_TS_1_DAT
storage
(
initial 512K
next 512K
minextents 1
maxextents unlimited
pctincrease 0
)
/
grant select, insert, update, delete on INT_TARIFFDISCOUNT_LNK to INTEGRATE_ROLE_ALL
/
grant select on INT_TARIFFDISCOUNT_LNK to INTEGRATE_ROLE_SEL
/

comment on table INT_TARIFFDISCOUNT_LNK is 'mapping table defining the discounts given for a tariff model (based on a service,zone,callclass,calltype relationship)'
/

comment on column INT_TARIFFDISCOUNT_LNK.TARIFFMODEL is 'reference to the tariff model version'
/

comment on column INT_TARIFFDISCOUNT_LNK.VERSION is 'reference to the tariff model version'
/

comment on column INT_TARIFFDISCOUNT_LNK.RANK is 'defines the mapping order for the single entries'
/

comment on column INT_TARIFFDISCOUNT_LNK.VALID_FROM is 'this mapping entry is valid from (Format: YYYYMMDD or MON-SUN[HH:MM]) (compare: >=)'
/

comment on column INT_TARIFFDISCOUNT_LNK.VALID_TO is 'defines the date till when this entry is valid (Format: YYYYMMDD or MON-SUN[HH:MM]) (compare: <)'
/

comment on column INT_TARIFFDISCOUNT_LNK.TIME_FROM is 'optional time, within the given valid_date, when the mapping should take place (Format: HH:MM) (compare: >=)'
/

comment on column INT_TARIFFDISCOUNT_LNK.TIME_TO is 'optional time, within the given valid_date, when the mapping should take place (Format: HH:MM) (compare: <)'
/

comment on column INT_TARIFFDISCOUNT_LNK.QUANTITY_VALUE is 'optional Quantity-Value (e.g. Duration), the discount only takes place, if the cdr-value is smaller'
/

comment on column INT_TARIFFDISCOUNT_LNK.CALLCLASS is 'condition: the call classification which should be matched (if empty all match)'
/

comment on column INT_TARIFFDISCOUNT_LNK.CALLTYPE is 'condition: the calltype which should be matched (if empty all match)'
/

comment on column INT_TARIFFDISCOUNT_LNK.SERVICECODE is 'condition: the servicecode which should be matched (if empty all match)'
/

comment on column INT_TARIFFDISCOUNT_LNK.SERVICECLASS is 'condition: the serviceclass which should be mapped (if empty all match)'
/

comment on column INT_TARIFFDISCOUNT_LNK.ZONE is 'condition: the zone value which should be matched (if empty all match)'
/

comment on column INT_TARIFFDISCOUNT_LNK.SOURCE_NETWORK is 'condition: the source network (VPLMN) which should be matched (if empty all match)'
/

comment on column INT_TARIFFDISCOUNT_LNK.DESTIN_NETWORK is 'condition: the destination network (HPLMN) which should be matched (if empty all match)'
/

comment on column INT_TARIFFDISCOUNT_LNK.DISCOUNT_TYPE is 'result: type of the discount value (P=percantage, A=addon value, N=absolute new value)'
/

comment on column INT_TARIFFDISCOUNT_LNK.DISCOUNT_VALUE is 'result: the discount value itself (content is related to DISCOUNT_TYPE)'
/

comment on column INT_TARIFFDISCOUNT_LNK.NAME is 'NAME'
/

comment on column INT_TARIFFDISCOUNT_LNK.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TARIFFDISCOUNT_LNK.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TARIFFDISCOUNT_LNK.MODIFBY is 'MODIFBY'
/

comment on column INT_TARIFFDISCOUNT_LNK.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TARIFFDISCOUNT_LNK.MODIFIED is 'MODIFIED'
/

comment on column INT_TARIFFDISCOUNT_LNK.RECVER is 'RECVER'
/


-- ============================================================
--   Index: FK_INT_TDL_TMD                                     
-- ============================================================
create index FK_INT_TDL_TMD on INT_TARIFFDISCOUNT_LNK (TARIFFMODEL asc)
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
/

-- ============================================================
--   Table: INT_SEGTARIFF_LNK                                  
-- ============================================================
drop table INT_SEGTARIFF_LNK cascade constraints;

create table INT_SEGTARIFF_LNK
(
    SEGMENT                  VARCHAR2(5)            not null,
    VALID_FROM               DATE                   not null,
    TARIFFMODEL              NUMBER(9)              not null,
    VALID_TO                 DATE                   null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SEGTARIFF_LNK check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_STL primary key (SEGMENT, VALID_FROM, TARIFFMODEL)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_SEGTARIFF_LNK to INTEGRATE_ROLE_ALL
/
grant select on INT_SEGTARIFF_LNK to INTEGRATE_ROLE_SEL
/

comment on table INT_SEGTARIFF_LNK is 'link table, defines which tariff models have to be evaluated for a segment'
/

comment on column INT_SEGTARIFF_LNK.SEGMENT is 'references the segment id'
/

comment on column INT_SEGTARIFF_LNK.VALID_FROM is 'date from when on this configuration is valid'
/

comment on column INT_SEGTARIFF_LNK.TARIFFMODEL is 'defines which tariff models should be evaluated for the defined segment'
/

comment on column INT_SEGTARIFF_LNK.VALID_TO is 'date until is entry valid'
/

comment on column INT_SEGTARIFF_LNK.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SEGTARIFF_LNK.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SEGTARIFF_LNK.MODIFBY is 'MODIFBY'
/

comment on column INT_SEGTARIFF_LNK.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SEGTARIFF_LNK.MODIFIED is 'MODIFIED'
/

comment on column INT_SEGTARIFF_LNK.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_EDRSEQLOG                                      
-- ============================================================
drop table INT_EDRSEQLOG cascade constraints;

create table INT_EDRSEQLOG
(
    EDR_FORMAT               VARCHAR2(10)           not null,
    ORIG_SEQNO               NUMBER(9)              not null,
    NEW_SEQNO                NUMBER(9)              not null,
    PROCESSED                DATE                   null    ,
    STATUS                   CHAR(1)                default 'O' not null
        constraint CKC_STATUS_INT_EDRSEQLOG check (STATUS in ('O','W','R')),
    RECYCLING                NUMBER(1)              default 0 not null
        constraint CKC_RECYCLIN_INT_EDRSEQLOG check (RECYCLING in (0,1)),
    NUM_REC_IN               NUMBER(9)              null    ,
    NUM_REC_OUT              NUMBER(9)              null    ,
    NUM_REC_WARN             NUMBER(9)              null    ,
    DURATION                 NUMBER(9)              null    ,
    SUM_QUANTITY             NUMBER                 null    ,
    SUM_CHARGE               NUMBER                 null    ,
    SUM_AOC                  NUMBER                 null    ,
    PROCESSEDBY_FORMAT       VARCHAR2(10)           null    ,
    STREAMNAME_IN            VARCHAR2(255)          null    ,
    constraint PK_INT_ESQ primary key (EDR_FORMAT, ORIG_SEQNO, NEW_SEQNO)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_EDRSEQLOG to INTEGRATE_ROLE_ALL
/
grant select on INT_EDRSEQLOG to INTEGRATE_ROLE_SEL
/

comment on table INT_EDRSEQLOG is 'edr sequence log, logging of each processed edr stream'
/

comment on column INT_EDRSEQLOG.EDR_FORMAT is 'references the edr format'
/

comment on column INT_EDRSEQLOG.ORIG_SEQNO is 'original sequence number'
/

comment on column INT_EDRSEQLOG.NEW_SEQNO is 'new calculated sequence number (or equal to orig_seqno)'
/

comment on column INT_EDRSEQLOG.PROCESSED is 'date when the edr stream had been processed (finish date)'
/

comment on column INT_EDRSEQLOG.STATUS is 'status after the edr stream has been processed (O=ok, W=warning, R=rejections)'
/

comment on column INT_EDRSEQLOG.RECYCLING is 'was the edr stream a recycling stream (1=Yes, 0=No)'
/

comment on column INT_EDRSEQLOG.NUM_REC_IN is 'number of input records'
/

comment on column INT_EDRSEQLOG.NUM_REC_OUT is 'number of output records'
/

comment on column INT_EDRSEQLOG.NUM_REC_WARN is 'number of records with a warning'
/

comment on column INT_EDRSEQLOG.DURATION is 'duration in seconds to perform the total processing'
/

comment on column INT_EDRSEQLOG.SUM_QUANTITY is 'sum of the Quantity Amount Value out of the edr-stream (e.g. total duration)'
/

comment on column INT_EDRSEQLOG.SUM_CHARGE is 'sum of the Charged Amount Value out of the edr-stream (total retail charge amount)'
/

comment on column INT_EDRSEQLOG.SUM_AOC is 'sum of the AoC Amount Value out of the edr-stream (total wholesale charge amount)'
/

comment on column INT_EDRSEQLOG.PROCESSEDBY_FORMAT is 'defines the edr-format which has processed the related stream (could be different from the orig-format in case of sequence sharring)'
/

comment on column INT_EDRSEQLOG.STREAMNAME_IN is 'name of the input stream'
/


-- ============================================================
--   Table: INT_SPLITTING_TYPE                                 
-- ============================================================
drop table INT_SPLITTING_TYPE cascade constraints;

create table INT_SPLITTING_TYPE
(
    EDR_FORMAT               VARCHAR2(10)           not null,
    RANK                     NUMBER(9)              not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    RECORDTYPE               VARCHAR2(2000)         default '*' not null,
    SERVICECODE              VARCHAR2(2000)         default '*' not null,
    CALLCLASS                VARCHAR2(2000)         default '*' not null,
    SOURCE_NETWORK           VARCHAR2(2000)         default '*' not null,
    DESTIN_NETWORK           VARCHAR2(2000)         default '*' not null,
    SWITCH                   VARCHAR2(2000)         default '*' not null,
    TRUNK_IN                 VARCHAR2(2000)         default '*' not null,
    TRUNK_OUT                VARCHAR2(2000)         default '*' not null,
    ORIGIN_AREACODE          VARCHAR2(2000)         default '*' not null,
    DESTIN_AREACODE          VARCHAR2(2000)         default '*' not null,
    TRANSIT_AREACODE         VARCHAR2(2000)         default '*' not null,
    SYSTEM_BRAND             VARCHAR2(5)            not null,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SPLITTING_TYP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SPT primary key (EDR_FORMAT, RANK, VALID_FROM)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_SPLITTING_TYPE to INTEGRATE_ROLE_ALL
/
grant select on INT_SPLITTING_TYPE to INTEGRATE_ROLE_SEL
/

comment on table INT_SPLITTING_TYPE is 'defines the type(service,callclass)-specialistsystem relation used for edr splitting and reseller rating'
/

comment on column INT_SPLITTING_TYPE.EDR_FORMAT is 'reference to the edr format these prefix entries are valid for'
/

comment on column INT_SPLITTING_TYPE.RANK is 'ranking order for proceeding the splitting entries'
/

comment on column INT_SPLITTING_TYPE.VALID_FROM is 'date from when on this entry is valid'
/

comment on column INT_SPLITTING_TYPE.VALID_TO is 'defines the date till when this entry is valid'
/

comment on column INT_SPLITTING_TYPE.RECORDTYPE is 'the record type for which a specialistsystem should be defined'
/

comment on column INT_SPLITTING_TYPE.SERVICECODE is 'the edr specific service code for which a specialistsystem should be defined'
/

comment on column INT_SPLITTING_TYPE.CALLCLASS is 'the callclass for which a specialistsystem should be defined'
/

comment on column INT_SPLITTING_TYPE.SOURCE_NETWORK is 'SOURCE_NETWORK'
/

comment on column INT_SPLITTING_TYPE.DESTIN_NETWORK is 'DESTIN_NETWORK'
/

comment on column INT_SPLITTING_TYPE.SWITCH is 'SWITCH'
/

comment on column INT_SPLITTING_TYPE.TRUNK_IN is 'TRUNK_IN'
/

comment on column INT_SPLITTING_TYPE.TRUNK_OUT is 'TRUNK_OUT'
/

comment on column INT_SPLITTING_TYPE.ORIGIN_AREACODE is 'the A# cli prefix for which a specialistsystem should be defined'
/

comment on column INT_SPLITTING_TYPE.DESTIN_AREACODE is 'the B# cli prefix for which a specialistsystem should be defined'
/

comment on column INT_SPLITTING_TYPE.TRANSIT_AREACODE is 'TRANSIT_AREACODE'
/

comment on column INT_SPLITTING_TYPE.SYSTEM_BRAND is 'the specialistsystem which should be used for this entry (defines the splitting output)'
/

comment on column INT_SPLITTING_TYPE.NAME is 'description'
/

comment on column INT_SPLITTING_TYPE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SPLITTING_TYPE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SPLITTING_TYPE.MODIFBY is 'MODIFBY'
/

comment on column INT_SPLITTING_TYPE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SPLITTING_TYPE.MODIFIED is 'MODIFIED'
/

comment on column INT_SPLITTING_TYPE.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_EXCHANGE_RATE                                  
-- ============================================================
drop table INT_EXCHANGE_RATE cascade constraints;

create table INT_EXCHANGE_RATE
(
    FROM_CURRENCY            VARCHAR2(3)            default 'DEM' not null,
    VALID_FROM               DATE                   not null,
    TO_CURRENCY              VARCHAR2(3)            default 'DEM' not null,
    EXCHANGE_RATE            NUMBER                 not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_EXCHANGE_RATE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_XCR primary key (FROM_CURRENCY, VALID_FROM, TO_CURRENCY)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_EXCHANGE_RATE to INTEGRATE_ROLE_ALL
/
grant select on INT_EXCHANGE_RATE to INTEGRATE_ROLE_SEL
/

comment on table INT_EXCHANGE_RATE is 'defines the exchange rates for given currencies'
/

comment on column INT_EXCHANGE_RATE.FROM_CURRENCY is 'specifies the origin currency an exchange rate should apply to'
/

comment on column INT_EXCHANGE_RATE.VALID_FROM is 'date from when on the exchange rate is valid'
/

comment on column INT_EXCHANGE_RATE.TO_CURRENCY is 'specifies the destination currency the exchange is valid for'
/

comment on column INT_EXCHANGE_RATE.EXCHANGE_RATE is 'the exchange rate amount'
/

comment on column INT_EXCHANGE_RATE.ENTRYBY is 'ENTRYBY'
/

comment on column INT_EXCHANGE_RATE.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_EXCHANGE_RATE.MODIFBY is 'MODIFBY'
/

comment on column INT_EXCHANGE_RATE.MODIFDATE is 'MODIFDATE'
/

comment on column INT_EXCHANGE_RATE.MODIFIED is 'MODIFIED'
/

comment on column INT_EXCHANGE_RATE.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_APN_MAP                                        
-- ============================================================
drop table INT_APN_MAP cascade constraints;

create table INT_APN_MAP
(
    APN_GROUP                VARCHAR2(10)           not null,
    RANK                     NUMBER(9)              not null,
    SERVICECODE              VARCHAR2(2000)         default '*' not null,
    ACCESSPOINTNAME          VARCHAR2(2000)         default '*' not null,
    ZONE_WS                  VARCHAR2(2000)         default '*' not null,
    ZONE_RT                  VARCHAR2(2000)         default '*' not null,
    PDP_ADDRESS              VARCHAR2(40)           null    ,
    NEW_ZONE_WS              VARCHAR2(5)            null    ,
    NEW_ZONE_RT              VARCHAR2(5)            null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_APN_MAP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_APM primary key (APN_GROUP, RANK)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_APN_MAP to INTEGRATE_ROLE_ALL
/
grant select on INT_APN_MAP to INTEGRATE_ROLE_SEL
/

comment on table INT_APN_MAP is 'mapping or grouping of access-point-names'
/

comment on column INT_APN_MAP.APN_GROUP is 'reference to the APN group for which this mapping should be performed'
/

comment on column INT_APN_MAP.RANK is 'defines the mapping order for the single entries'
/

comment on column INT_APN_MAP.SERVICECODE is 'condition: the servicecode which should be mapped (if empty all match)'
/

comment on column INT_APN_MAP.ACCESSPOINTNAME is 'condition: the access-point-name which should be mapped (if empty all match)'
/

comment on column INT_APN_MAP.ZONE_WS is 'condition: the wholesale zone value calculated so far which should be mapped (if empty all match)'
/

comment on column INT_APN_MAP.ZONE_RT is 'condition: the retail zone value calculated so far which should be mapped (if empty all match)'
/

comment on column INT_APN_MAP.PDP_ADDRESS is 'result: the pdp-address (e.g. ip-address) which will be used (if empty no mapping is performed)'
/

comment on column INT_APN_MAP.NEW_ZONE_WS is 'result: returns the new wholesale zone (if empty nothing changes)'
/

comment on column INT_APN_MAP.NEW_ZONE_RT is 'result: returns the new wholesale zone (if empty nothing changes)'
/

comment on column INT_APN_MAP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_APN_MAP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_APN_MAP.MODIFBY is 'MODIFBY'
/

comment on column INT_APN_MAP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_APN_MAP.MODIFIED is 'MODIFIED'
/

comment on column INT_APN_MAP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SUBS_CLI                                       
-- ============================================================
drop table INT_SUBS_CLI cascade constraints;

create table INT_SUBS_CLI
(
    CLI                      VARCHAR2(24)           not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    SERVICECODE              VARCHAR2(5)            null    ,
    CONTRACT                 NUMBER(38)             null    ,
    MAPPING_CLI              VARCHAR2(40)           null    ,
    DXXX                     VARCHAR2(4)            null    ,
    constraint PK_INT_CLI primary key (CLI, VALID_FROM)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_3_IDX
        storage
        (
        initial 4M
        next 4M
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
initial 8M
next 8M
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_3_DAT
/
grant select, insert, update, delete on INT_SUBS_CLI to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBS_CLI to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBS_CLI is 'subscribers cli'
/

comment on column INT_SUBS_CLI.CLI is 'primary cli for this subscriber (for each cli there is one record here)'
/

comment on column INT_SUBS_CLI.VALID_FROM is 'date from when on this entry'
/

comment on column INT_SUBS_CLI.VALID_TO is 'date till when this entry is valid'
/

comment on column INT_SUBS_CLI.SERVICECODE is 'the service which is related to the cli (e.g. TEL or FAX or DATA etc.)'
/

comment on column INT_SUBS_CLI.CONTRACT is 'CONTRACT'
/

comment on column INT_SUBS_CLI.MAPPING_CLI is 'optional mapping cli (e.g. fixed network cli), if empty no mapping will take place'
/

comment on column INT_SUBS_CLI.DXXX is 'contains the DXXX number portability information as a reference to the carrier keeping this number'
/


-- ============================================================
--   Table: INT_SUBS_CONTRACT_HIST                             
-- ============================================================
drop table INT_SUBS_CONTRACT_HIST cascade constraints;

create table INT_SUBS_CONTRACT_HIST
(
    CONTRACT                 NUMBER(38)             default 01 not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    BILLCYCLE                VARCHAR2(2)            not null,
    SEGMENT                  VARCHAR2(5)            default 'DEF' not null,
    RATEPLAN                 VARCHAR2(10)           null    ,
    TARIFFMODEL              VARCHAR2(30)           null    ,
    TARIFFINDICATOR          VARCHAR2(5)            null    ,
    SLA_CODE                 VARCHAR2(5)            null    ,
    DISCOUNTMODEL            VARCHAR2(5)            null    ,
    constraint PK_INT_SCH primary key (CONTRACT, VALID_FROM)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_4_IDX
        storage
        (
        initial 8M
        next 8M
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
initial 16M
next 16M
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_SUBS_CONTRACT_HIST to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBS_CONTRACT_HIST to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBS_CONTRACT_HIST is 'subscriber contract history'
/

comment on column INT_SUBS_CONTRACT_HIST.CONTRACT is 'references the contract id these historical data is referenced to'
/

comment on column INT_SUBS_CONTRACT_HIST.VALID_FROM is 'date from when on this entry is valid'
/

comment on column INT_SUBS_CONTRACT_HIST.VALID_TO is 'date til when this entry is valid'
/

comment on column INT_SUBS_CONTRACT_HIST.BILLCYCLE is 'determines the bill cycle for this customer (e.g. 01-28)'
/

comment on column INT_SUBS_CONTRACT_HIST.SEGMENT is 'segment id (used as a reference for segemnt zoning and segment pricing)'
/

comment on column INT_SUBS_CONTRACT_HIST.RATEPLAN is 'the rate-plan which should be used for customer individual rating'
/

comment on column INT_SUBS_CONTRACT_HIST.TARIFFMODEL is 'the tariffmodel which should be used for customer individual rating'
/

comment on column INT_SUBS_CONTRACT_HIST.TARIFFINDICATOR is 'the actual tariffindicator the subscriber has choosen (e.g. city, regio, weekend), specifies an option of the tariffmodel'
/

comment on column INT_SUBS_CONTRACT_HIST.SLA_CODE is 'references the related service level agreement associated with this subscriber'
/

comment on column INT_SUBS_CONTRACT_HIST.DISCOUNTMODEL is 'references the related discount model associated with this subscriber'
/


-- ============================================================
--   Table: INT_DISCOUNTMDL_CNF                                
-- ============================================================
drop table INT_DISCOUNTMDL_CNF cascade constraints;

create table INT_DISCOUNTMDL_CNF
(
    DISCOUNTCONFIG           NUMBER(9)              not null,
    DISCOUNTMODEL            NUMBER(9)              not null,
    VERSION                  NUMBER(9)              not null,
    RANK                     NUMBER(9)              not null,
    DISCOUNTTRIGGER          NUMBER(9)              not null,
    DISCOUNTRULE             NUMBER(9)              not null,
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DMC primary key (DISCOUNTCONFIG)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_DISCOUNTMDL_CNF to INTEGRATE_ROLE_ALL
/
grant select on INT_DISCOUNTMDL_CNF to INTEGRATE_ROLE_SEL
/

comment on table INT_DISCOUNTMDL_CNF is 'discount model configuration (main entry point for price calculation for a given tariff model, using service,zone,timemodel combinations)'
/

comment on column INT_DISCOUNTMDL_CNF.DISCOUNTCONFIG is 'unique internal id identifying the configuration entry'
/

comment on column INT_DISCOUNTMDL_CNF.DISCOUNTMODEL is 'references the related discountmodel this configuration entry belongs to'
/

comment on column INT_DISCOUNTMDL_CNF.VERSION is 'references the related discountmodel version this configuration entry belongs to'
/

comment on column INT_DISCOUNTMDL_CNF.RANK is 'defines the order of configuration entries within a discount model'
/

comment on column INT_DISCOUNTMDL_CNF.DISCOUNTTRIGGER is 'DISCOUNTTRIGGER'
/

comment on column INT_DISCOUNTMDL_CNF.DISCOUNTRULE is 'unique id, defining a discount rule'
/

comment on column INT_DISCOUNTMDL_CNF.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_DMC                                         
-- ============================================================
create unique index AK_INT_DMC on INT_DISCOUNTMDL_CNF (DISCOUNTMODEL asc, VERSION asc, RANK asc)
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
/

-- ============================================================
--   Table: INT_DISCOUNTSTEP                                   
-- ============================================================
drop table INT_DISCOUNTSTEP cascade constraints;

create table INT_DISCOUNTSTEP
(
    DISCOUNTSTEP             NUMBER(9)              not null,
    DISCOUNTRULE             NUMBER(9)              not null,
    RANK                     NUMBER(9)              not null,
    DISCOUNTMASTER           NUMBER(9)              not null,
    THRESHOLD_TYPE           CHAR(1)                not null
        constraint CKC_THRESHOL_INT_DISCOUNTSTEP check (THRESHOLD_TYPE in ('C','Q','E','S','R')),
    THRESHOLD_FROM           NUMBER                 not null,
    THRESHOLD_TO             NUMBER                 null    ,
    DISCOUNT_TYPE            CHAR(1)                default 'A' not null
        constraint CKC_DISCOUNT_INT_DISCOUNTSTEP check (DISCOUNT_TYPE in ('A','P')),
    GRANT_TYPE               CHAR(1)                not null
        constraint CKC_GRANT_TY_INT_DISCOUNTSTEP check (GRANT_TYPE in ('C','Q','S','R')),
    GRANT_PRORATEDBEAT       NUMBER(1)              default 1 not null
        constraint CKC_GRANT_PR_INT_DISCOUNTSTEP check (GRANT_PRORATEDBEAT in (0,1)),
    GRANT_UNITS              NUMBER                 not null,
    GRANT_BEAT               NUMBER                 default 0 not null,
    GRANT_UOM                VARCHAR2(3)            not null,
    ROLLOVER_UNITS           NUMBER                 default 0 not null,
    EDR_ENRICHMENT           NUMBER(1)              default 0 not null
        constraint CKC_EDR_ENRI_INT_DISCOUNTSTEP check (EDR_ENRICHMENT in (0,1)),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_DISCOUNTSTEP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DCS primary key (DISCOUNTSTEP)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_DISCOUNTSTEP to INTEGRATE_ROLE_ALL
/
grant select on INT_DISCOUNTSTEP to INTEGRATE_ROLE_SEL
/

comment on table INT_DISCOUNTSTEP is 'defines the single discount steps (thresholds)'
/

comment on column INT_DISCOUNTSTEP.DISCOUNTSTEP is 'DISCOUNTSTEP'
/

comment on column INT_DISCOUNTSTEP.DISCOUNTRULE is 'references the related discount rule under which this step is grouped'
/

comment on column INT_DISCOUNTSTEP.RANK is 'unique step identifier'
/

comment on column INT_DISCOUNTSTEP.DISCOUNTMASTER is 'unique internal id'
/

comment on column INT_DISCOUNTSTEP.THRESHOLD_TYPE is 'the unit of the tresholds measurement (''C''harge, ''Q''uantity, ''E''vent, ''S''ent volume, ''R''eceived volume)'
/

comment on column INT_DISCOUNTSTEP.THRESHOLD_FROM is 'lower boundary threshold from when on this discount stagger step is valid (compare: >), negative values allowed'
/

comment on column INT_DISCOUNTSTEP.THRESHOLD_TO is 'lower boundary threshold from when on this discount stagger step is valid (compare: <=)'
/

comment on column INT_DISCOUNTSTEP.DISCOUNT_TYPE is 'type of the discount value (P=percantage, A=addon value)'
/

comment on column INT_DISCOUNTSTEP.GRANT_TYPE is 'defines what should be granted: Q - grant quantity, C - grant charge, S - grant volume sent, R - grant volume received'
/

comment on column INT_DISCOUNTSTEP.GRANT_PRORATEDBEAT is 'grant pro-rated beats (1=TRUE=pro-rated, 0=FALSE=absolut beat-based)'
/

comment on column INT_DISCOUNTSTEP.GRANT_UNITS is 'defines the granted discount (the content of this value is dependent to the GRANT_TYPE)'
/

comment on column INT_DISCOUNTSTEP.GRANT_BEAT is 'defines an optional beat for the gant_units (e.g. the unit should be granted every X seconds)'
/

comment on column INT_DISCOUNTSTEP.GRANT_UOM is 'info about the unit of measurement, that is to be granted'
/

comment on column INT_DISCOUNTSTEP.ROLLOVER_UNITS is 'defines the granted units, which can be rolled over to the following period (rollover is only allowed for linear forwarded discounts)'
/

comment on column INT_DISCOUNTSTEP.EDR_ENRICHMENT is 'boolean defines if the EDRs should be enriched by the discount PlugIn (0=FALSE=reverse discounting, 1=TRUE=foreward discounting)'
/

comment on column INT_DISCOUNTSTEP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_DISCOUNTSTEP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_DISCOUNTSTEP.MODIFBY is 'MODIFBY'
/

comment on column INT_DISCOUNTSTEP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_DISCOUNTSTEP.MODIFIED is 'MODIFIED'
/

comment on column INT_DISCOUNTSTEP.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_DCS                                         
-- ============================================================
create unique index AK_INT_DCS on INT_DISCOUNTSTEP (DISCOUNTRULE asc, RANK asc)
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
/

-- ============================================================
--   Table: INT_DISCOUNTDETAIL                                 
-- ============================================================
drop table INT_DISCOUNTDETAIL cascade constraints;

create table INT_DISCOUNTDETAIL
(
    DISCOUNTMASTER           NUMBER(9)              not null,
    RANK                     NUMBER(9)              not null,
    VALID_FROM               VARCHAR2(8)            not null,
    VALID_TO                 VARCHAR2(8)            null    ,
    TIME_FROM                VARCHAR2(5)            null    ,
    TIME_TO                  VARCHAR2(5)            null    ,
    ZONEMODEL                VARCHAR2(2000)         default '*' not null,
    ZONE                     VARCHAR2(2000)         default '*' not null,
    SERVICECODE              VARCHAR2(2000)         default '*' not null,
    SERVICECLASS             VARCHAR2(2000)         default '*' not null,
    TIMEMODEL                VARCHAR2(2000)         default '*' not null,
    TIMEZONE                 VARCHAR2(2000)         default '*' not null,
    PRICEMODEL               VARCHAR2(2000)         default '*' not null,
    RECORDTYPE               VARCHAR2(2000)         default '*' not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_DISCOUNTDETAI check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DCD primary key (DISCOUNTMASTER, RANK)
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
initial 512K
next 512K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_DISCOUNTDETAIL to INTEGRATE_ROLE_ALL
/
grant select on INT_DISCOUNTDETAIL to INTEGRATE_ROLE_SEL
/

comment on table INT_DISCOUNTDETAIL is 'defines one condition to be used within a discountmaster'
/

comment on column INT_DISCOUNTDETAIL.DISCOUNTMASTER is 'references the related discountmaster (under which this condition will be grouped)'
/

comment on column INT_DISCOUNTDETAIL.RANK is 'rank, defines the sequence order in which the conditions should be checked'
/

comment on column INT_DISCOUNTDETAIL.VALID_FROM is 'date from when on the condition is valid (Format: YYYYMMDD or MON-SUN[HH:MM]) (compare: >=)'
/

comment on column INT_DISCOUNTDETAIL.VALID_TO is 'date til when the condition is valid (Format: YYYYMMDD or MON-SUN[HH:MM]) (compare: <)'
/

comment on column INT_DISCOUNTDETAIL.TIME_FROM is 'optional time starting intervall within the valid date range (Format: HH:MM) (compare: >=)'
/

comment on column INT_DISCOUNTDETAIL.TIME_TO is 'optional time ending intervall within the valid date range (Format: HH:MM) (compare: <)'
/

comment on column INT_DISCOUNTDETAIL.ZONEMODEL is 'condition: references a zonemodel (if empty all match), reg. expr. allowed'
/

comment on column INT_DISCOUNTDETAIL.ZONE is 'condition: references a zone value (if empty all match), reg. expr. allowed'
/

comment on column INT_DISCOUNTDETAIL.SERVICECODE is 'condition: references an internal service code (if empty all match), reg. expr. allowed'
/

comment on column INT_DISCOUNTDETAIL.SERVICECLASS is 'condition: references an internal service class (if empty all match), reg. expr. allowed'
/

comment on column INT_DISCOUNTDETAIL.TIMEMODEL is 'condition: references a time model (if empty all match), reg. expr. allowed'
/

comment on column INT_DISCOUNTDETAIL.TIMEZONE is 'condition: references a time zone (if empty all match), reg. expr. allowed'
/

comment on column INT_DISCOUNTDETAIL.PRICEMODEL is 'condition: references an internal price model (if empty all match), reg. expr. allowed'
/

comment on column INT_DISCOUNTDETAIL.RECORDTYPE is 'condition: references related recordtypes (if empty all match), reg. expr. allowed'
/

comment on column INT_DISCOUNTDETAIL.ENTRYBY is 'ENTRYBY'
/

comment on column INT_DISCOUNTDETAIL.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_DISCOUNTDETAIL.MODIFBY is 'MODIFBY'
/

comment on column INT_DISCOUNTDETAIL.MODIFDATE is 'MODIFDATE'
/

comment on column INT_DISCOUNTDETAIL.MODIFIED is 'MODIFIED'
/

comment on column INT_DISCOUNTDETAIL.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SUBS_BILLRUN                                   
-- ============================================================
drop table INT_SUBS_BILLRUN cascade constraints;

create table INT_SUBS_BILLRUN
(
    BILLRUN                  VARCHAR2(10)           not null,
    BILLCYCLE                VARCHAR2(2)            not null,
    BOC_DATE                 DATE                   not null,
    EOC_DATE                 DATE                   not null,
    BILLRUN_DATE             DATE                   null    ,
    STATUS                   CHAR(1)                default 'O' not null
        constraint CKC_STATUS_INT_SUBS_BILLRUN check (STATUS in ('O','C','R')),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SUBS_BILLRUN check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_SBR primary key (BILLRUN)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_SUBS_BILLRUN to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBS_BILLRUN to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBS_BILLRUN is 'records the subscriber related bill runs which had been performed. used to identify the next bill period for each cycle'
/

comment on column INT_SUBS_BILLRUN.BILLRUN is 'unique bill run period in format YYYYMMBC, e.g. 20000301 - 3rd billrun for cycle 01 in year 2000'
/

comment on column INT_SUBS_BILLRUN.BILLCYCLE is 'references the related bill cycle for which a bill run had been performed or will be performed'
/

comment on column INT_SUBS_BILLRUN.BOC_DATE is 'actual end-of-cycle date for the bill run of this cycle, e.g. 18.02.2000'
/

comment on column INT_SUBS_BILLRUN.EOC_DATE is 'actual end-of-cycle date for the bill run of this cycle, e.g. 17.03.2000'
/

comment on column INT_SUBS_BILLRUN.BILLRUN_DATE is 'date when the bill run was performed (is alway some days later)'
/

comment on column INT_SUBS_BILLRUN.STATUS is 'status of the current billcycle (C=closed, O=open, R=running)'
/

comment on column INT_SUBS_BILLRUN.ENTRYBY is 'ENTRYBY'
/

comment on column INT_SUBS_BILLRUN.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_SUBS_BILLRUN.MODIFBY is 'MODIFBY'
/

comment on column INT_SUBS_BILLRUN.MODIFDATE is 'MODIFDATE'
/

comment on column INT_SUBS_BILLRUN.MODIFIED is 'MODIFIED'
/

comment on column INT_SUBS_BILLRUN.RECVER is 'RECVER'
/


-- ============================================================
--   Index: AK_INT_SCR                                         
-- ============================================================
create unique index AK_INT_SCR on INT_SUBS_BILLRUN (BILLCYCLE asc, EOC_DATE asc)
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
/

-- ============================================================
--   Table: INT_NOSP                                           
-- ============================================================
drop table INT_NOSP cascade constraints;

create table INT_NOSP
(
    MAP_GROUP                VARCHAR2(10)           not null,
    RANK                     NUMBER(9)              not null,
    OLD_SOURCE               VARCHAR2(14)           null    ,
    OLD_DESTINATION          VARCHAR2(14)           null    ,
    A_PREFIX                 VARCHAR2(40)           null    ,
    NEW_SOURCE               VARCHAR2(14)           null    ,
    NEW_DESTINATION          VARCHAR2(14)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_NOSP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_NSP primary key (MAP_GROUP, RANK)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_NOSP to INTEGRATE_ROLE_ALL
/
grant select on INT_NOSP to INTEGRATE_ROLE_SEL
/

comment on table INT_NOSP is 'network operator-serviceprovider definition'
/

comment on column INT_NOSP.MAP_GROUP is 'references the logical map-group this nosp-definition belongs to'
/

comment on column INT_NOSP.RANK is 'rank, defines the order sequence in which the mapping will be evaluated'
/

comment on column INT_NOSP.OLD_SOURCE is 'references the "source network" out of an origin edr stream, for which a mapping should take place'
/

comment on column INT_NOSP.OLD_DESTINATION is 'references the "destination network" out of an origin edr stream, for which a mapping should take place'
/

comment on column INT_NOSP.A_PREFIX is 'references an A# out of an origin edr stream, for which a mapping should take place'
/

comment on column INT_NOSP.NEW_SOURCE is 'the new "source network" code which should be used for this mapping'
/

comment on column INT_NOSP.NEW_DESTINATION is 'the new "destination network" code which should be used for this mapping'
/

comment on column INT_NOSP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_NOSP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_NOSP.MODIFBY is 'MODIFBY'
/

comment on column INT_NOSP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_NOSP.MODIFIED is 'MODIFIED'
/

comment on column INT_NOSP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_ICPRODUCT_CNF                                  
-- ============================================================
drop table INT_ICPRODUCT_CNF cascade constraints;

create table INT_ICPRODUCT_CNF
(
    NETWORKMODEL             NUMBER(9)              not null,
    ICPRODUCT_GROUP          VARCHAR2(10)           not null,
    RANK                     NUMBER(9)              not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    NAME                     VARCHAR2(30)           null    ,
    SOURCE_NETWORK           VARCHAR2(2000)         default '*' not null,
    DESTIN_NETWORK           VARCHAR2(2000)         default '*' not null,
    ORIGIN_AREACODE          VARCHAR2(2000)         default '*' not null,
    DESTIN_AREACODE          VARCHAR2(2000)         default '*' not null,
    TRANSIT_AREACODE         VARCHAR2(2000)         default '*' not null,
    RECORDTYPE               VARCHAR2(2000)         default '*' not null,
    SERVICECODE              VARCHAR2(2000)         default '*' not null,
    CALLCLASS                VARCHAR2(2000)         default '*' not null,
    ICPRODUCT                VARCHAR2(10)           not null,
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_IPC primary key (NETWORKMODEL, ICPRODUCT_GROUP, RANK, VALID_FROM)
        using index
        pctfree 10
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_ICPRODUCT_CNF to INTEGRATE_ROLE_ALL
/
grant select on INT_ICPRODUCT_CNF to INTEGRATE_ROLE_SEL
/

comment on table INT_ICPRODUCT_CNF is 'mapping table to support special call-senarios, mapping a trunk to a poi-service'
/

comment on column INT_ICPRODUCT_CNF.NETWORKMODEL is 'references the related network model'
/

comment on column INT_ICPRODUCT_CNF.ICPRODUCT_GROUP is 'references a related ic product group for which this FSM rules are valid'
/

comment on column INT_ICPRODUCT_CNF.RANK is 'identifies the unique mapping sequence order'
/

comment on column INT_ICPRODUCT_CNF.VALID_FROM is 'date from when on this entry is valid'
/

comment on column INT_ICPRODUCT_CNF.VALID_TO is 'til when this mapping entry is valid to'
/

comment on column INT_ICPRODUCT_CNF.NAME is 'just a name or description for the mapping rule'
/

comment on column INT_ICPRODUCT_CNF.SOURCE_NETWORK is 'FSM-condition: references the source network (e.g. the A# related DXXX) this mapping is related to'
/

comment on column INT_ICPRODUCT_CNF.DESTIN_NETWORK is 'FSM-condition: references the destination network (e.g. the B# related DXXX) this mapping is related to'
/

comment on column INT_ICPRODUCT_CNF.ORIGIN_AREACODE is 'FSM-condition: references an A# this mapping is related to'
/

comment on column INT_ICPRODUCT_CNF.DESTIN_AREACODE is 'FSM-condition: references a B# this mapping is related to'
/

comment on column INT_ICPRODUCT_CNF.TRANSIT_AREACODE is 'FSM-condition: references a C# this mapping is related to'
/

comment on column INT_ICPRODUCT_CNF.RECORDTYPE is 'FSM-condition: references the recordtype this mapping is related to'
/

comment on column INT_ICPRODUCT_CNF.SERVICECODE is 'FSM-condition: references the service code used this mapping is related to'
/

comment on column INT_ICPRODUCT_CNF.CALLCLASS is 'FSM-condition: references the callclass this mapping is related to'
/

comment on column INT_ICPRODUCT_CNF.ICPRODUCT is 'uniquely identifies the poi-service which is refered by this configuration entry'
/

comment on column INT_ICPRODUCT_CNF.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_NOPRODUCT_CNF                                  
-- ============================================================
drop table INT_NOPRODUCT_CNF cascade constraints;

create table INT_NOPRODUCT_CNF
(
    ICPRODUCT                VARCHAR2(10)           not null,
    TIMEZONE                 NUMBER(9)              not null,
    ZONE                     VARCHAR2(5)            not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    NO                       NUMBER(9)              not null,
    PRODUCTCODE              VARCHAR2(10)           not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_NOPRODUCT_CNF check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_NPC primary key (ICPRODUCT, TIMEZONE, ZONE, VALID_FROM)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_NOPRODUCT_CNF to INTEGRATE_ROLE_ALL
/
grant select on INT_NOPRODUCT_CNF to INTEGRATE_ROLE_SEL
/

comment on table INT_NOPRODUCT_CNF is 'defines the configuration to find a  network operator related product code'
/

comment on column INT_NOPRODUCT_CNF.ICPRODUCT is 'references the poi which will map the the productcode'
/

comment on column INT_NOPRODUCT_CNF.TIMEZONE is 'references the timezone which will map the the productcode'
/

comment on column INT_NOPRODUCT_CNF.ZONE is 'references the zone which will map the the productcode'
/

comment on column INT_NOPRODUCT_CNF.VALID_FROM is 'date from when on the no-product configuration is valid'
/

comment on column INT_NOPRODUCT_CNF.VALID_TO is 'date till when on the no-product configuration is valid'
/

comment on column INT_NOPRODUCT_CNF.NO is 'reference to the network operator'
/

comment on column INT_NOPRODUCT_CNF.PRODUCTCODE is 'defines the product code for a given poi'
/

comment on column INT_NOPRODUCT_CNF.ENTRYBY is 'ENTRYBY'
/

comment on column INT_NOPRODUCT_CNF.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_NOPRODUCT_CNF.MODIFBY is 'MODIFBY'
/

comment on column INT_NOPRODUCT_CNF.MODIFDATE is 'MODIFDATE'
/

comment on column INT_NOPRODUCT_CNF.MODIFIED is 'MODIFIED'
/

comment on column INT_NOPRODUCT_CNF.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_DISCOUNTCONDITION                              
-- ============================================================
drop table INT_DISCOUNTCONDITION cascade constraints;

create table INT_DISCOUNTCONDITION
(
    DISCOUNTCONDITION        NUMBER(9)              not null,
    DISCOUNTTRIGGER          NUMBER(9)              not null,
    DISCOUNTMASTER           NUMBER(9)              not null,
    CONDITION_BASE           CHAR(1)                not null
        constraint CKC_CONDITIO_INT_DISCOUNTCONDI check (CONDITION_BASE in ('C','Q','E','S','R')),
    CONDITION_VALUE          NUMBER                 not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_DISCOUNTCONDI check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DCN primary key (DISCOUNTCONDITION)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_DISCOUNTCONDITION to INTEGRATE_ROLE_ALL
/
grant select on INT_DISCOUNTCONDITION to INTEGRATE_ROLE_SEL
/

comment on table INT_DISCOUNTCONDITION is 'defines one or more trigger conditions'
/

comment on column INT_DISCOUNTCONDITION.DISCOUNTCONDITION is 'internal id'
/

comment on column INT_DISCOUNTCONDITION.DISCOUNTTRIGGER is 'referenced discount trigger'
/

comment on column INT_DISCOUNTCONDITION.DISCOUNTMASTER is 'referenced discount master'
/

comment on column INT_DISCOUNTCONDITION.CONDITION_BASE is 'defines the measure base for a condition (''C''harge, ''Q''uantity or ''E''vent, ''S''ent volume, ''R''eceived volume)'
/

comment on column INT_DISCOUNTCONDITION.CONDITION_VALUE is 'defines the value for a condition'
/

comment on column INT_DISCOUNTCONDITION.ENTRYBY is 'ENTRYBY'
/

comment on column INT_DISCOUNTCONDITION.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_DISCOUNTCONDITION.MODIFBY is 'MODIFBY'
/

comment on column INT_DISCOUNTCONDITION.MODIFDATE is 'MODIFDATE'
/

comment on column INT_DISCOUNTCONDITION.MODIFIED is 'MODIFIED'
/

comment on column INT_DISCOUNTCONDITION.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_DISCARDING                                     
-- ============================================================
drop table INT_DISCARDING cascade constraints;

create table INT_DISCARDING
(
    EDR_FORMAT               VARCHAR2(10)           not null,
    RANK                     NUMBER(9)              not null,
    NAME                     VARCHAR2(30)           null    ,
    RECORDTYPE               VARCHAR2(2000)         default '*' not null,
    SOURCE_NETWORK           VARCHAR2(2000)         default '*' not null,
    CALL_COMPLETION          VARCHAR2(2000)         default '*' not null,
    LONG_DURATION            VARCHAR2(2000)         default '*' not null,
    CALLCLASS                VARCHAR2(2000)         default '*' not null,
    SERVICECODE              VARCHAR2(2000)         default '*' not null,
    SWITCH                   VARCHAR2(2000)         default '*' not null,
    TARIFFCLASS              VARCHAR2(2000)         default '*' not null,
    TARIFFSUBCLASS           VARCHAR2(2000)         default '*' not null,
    CONNECTTYPE              VARCHAR2(2000)         default '*' not null,
    CONNECTSUBTYPE           VARCHAR2(2000)         default '*' not null,
    B_NUMBER                 VARCHAR2(2000)         default '*' not null,
    MAX_AGE                  NUMBER(9)              null    ,
    AOC_NULL                 NUMBER(1)              default 0 not null
        constraint CKC_AOC_NULL_INT_DISCARDING check (AOC_NULL in (0,1)),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_DISCARDING check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_DIC primary key (EDR_FORMAT, RANK)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_DISCARDING to INTEGRATE_ROLE_ALL
/
grant select on INT_DISCARDING to INTEGRATE_ROLE_SEL
/

comment on table INT_DISCARDING is 'Definition of all discarding rules'
/

comment on column INT_DISCARDING.EDR_FORMAT is 'references the edr format'
/

comment on column INT_DISCARDING.RANK is 'defines the sequence order in which the rules are processed'
/

comment on column INT_DISCARDING.NAME is 'name or description'
/

comment on column INT_DISCARDING.RECORDTYPE is 'RECORDTYPE'
/

comment on column INT_DISCARDING.SOURCE_NETWORK is 'SOURCE_NETWORK'
/

comment on column INT_DISCARDING.CALL_COMPLETION is 'CALL_COMPLETION'
/

comment on column INT_DISCARDING.LONG_DURATION is 'LONG_DURATION'
/

comment on column INT_DISCARDING.CALLCLASS is 'CALLCLASS'
/

comment on column INT_DISCARDING.SERVICECODE is 'SERVICECODE'
/

comment on column INT_DISCARDING.SWITCH is 'SWITCH'
/

comment on column INT_DISCARDING.TARIFFCLASS is 'TARIFFCLASS'
/

comment on column INT_DISCARDING.TARIFFSUBCLASS is 'TARIFFSUBCLASS'
/

comment on column INT_DISCARDING.CONNECTTYPE is 'CONNECTTYPE'
/

comment on column INT_DISCARDING.CONNECTSUBTYPE is 'CONNECTSUBTYPE'
/

comment on column INT_DISCARDING.B_NUMBER is 'B_NUMBER'
/

comment on column INT_DISCARDING.MAX_AGE is 'max. age (in number of days) the edr should have, older edrs will be discarded'
/

comment on column INT_DISCARDING.AOC_NULL is '1=Yes, the aoc amount must be null (zero) in order to match this rule; 0=No, if there is any aoc amount present the rule also matches'
/

comment on column INT_DISCARDING.ENTRYBY is 'ENTRYBY'
/

comment on column INT_DISCARDING.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_DISCARDING.MODIFBY is 'MODIFBY'
/

comment on column INT_DISCARDING.MODIFDATE is 'MODIFDATE'
/

comment on column INT_DISCARDING.MODIFIED is 'MODIFIED'
/

comment on column INT_DISCARDING.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_RULESETLIST                                    
-- ============================================================
-- do not copy this table because no changes.


-- ============================================================
--   Table: INT_NO_BILLRUN                                     
-- ============================================================
drop table INT_NO_BILLRUN cascade constraints;

create table INT_NO_BILLRUN
(
    NO                       NUMBER(9)              not null,
    BILLRUN                  VARCHAR2(10)           not null,
    BOC_DATE                 DATE                   not null,
    EOC_DATE                 DATE                   not null,
    BILLRUN_DATE             DATE                   null    ,
    STATUS                   CHAR(1)                default 'O' not null
        constraint CKC_STATUS_INT_NO_BILLRUN check (STATUS in ('O','C','R')),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_NO_BILLRUN check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_NBR primary key (NO, BILLRUN)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_NO_BILLRUN to INTEGRATE_ROLE_ALL
/
grant select on INT_NO_BILLRUN to INTEGRATE_ROLE_SEL
/

comment on table INT_NO_BILLRUN is 'records the no related bill runs which had been performed. used to identify the next bill period for each cycle'
/

comment on column INT_NO_BILLRUN.NO is 'references the related network operator, to which the billruns belong'
/

comment on column INT_NO_BILLRUN.BILLRUN is 'unique bill run period in format YYYYMMBC, e.g. 20000301 - 3rd billrun for cycle 01 in year 2000'
/

comment on column INT_NO_BILLRUN.BOC_DATE is 'defines the begin-of-cycle date for the billrun, e.g. 01.03.2000'
/

comment on column INT_NO_BILLRUN.EOC_DATE is 'defines the end-of-cycle date for the billrun, e.g. 31.03.2000'
/

comment on column INT_NO_BILLRUN.BILLRUN_DATE is 'date when the bill run was performed (is typically some days later than the eoc-date)'
/

comment on column INT_NO_BILLRUN.STATUS is 'defines the status for the bill run (O=open, C=closed, R=running)'
/

comment on column INT_NO_BILLRUN.ENTRYBY is 'ENTRYBY'
/

comment on column INT_NO_BILLRUN.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_NO_BILLRUN.MODIFBY is 'MODIFBY'
/

comment on column INT_NO_BILLRUN.MODIFDATE is 'MODIFDATE'
/

comment on column INT_NO_BILLRUN.MODIFIED is 'MODIFIED'
/

comment on column INT_NO_BILLRUN.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_TARIFFSERVICECLASS                             
-- ============================================================
drop table INT_TARIFFSERVICECLASS cascade constraints;

create table INT_TARIFFSERVICECLASS
(
    TSC_GROUP                VARCHAR2(10)           not null,
    TARIFFMODEL              NUMBER(9)              not null,
    RANK                     NUMBER(9)              not null,
    VALID_FROM               VARCHAR2(8)            not null,
    VALID_TO                 VARCHAR2(8)            null    ,
    QOS_REQUESTED            VARCHAR2(2000)         default '*' not null,
    QOS_USED                 VARCHAR2(2000)         default '*' not null,
    CALLCLASS                VARCHAR2(2000)         default '*' not null,
    CALLTYPE                 VARCHAR2(2000)         default '*' not null,
    SERVICECODE              VARCHAR2(2000)         default '*' not null,
    SERVICECLASS             VARCHAR2(2000)         default '*' not null,
    ZONE                     VARCHAR2(2000)         default '*' not null,
    NEW_SERVICECODE          VARCHAR2(5)            null    ,
    NEW_SERVICECLASS         VARCHAR2(5)            null    ,
    NAME                     VARCHAR2(30)           null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TARIFFSERVICE check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TSC primary key (TSC_GROUP, TARIFFMODEL, RANK)
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
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_TARIFFSERVICECLASS to INTEGRATE_ROLE_ALL
/
grant select on INT_TARIFFSERVICECLASS to INTEGRATE_ROLE_SEL
/

comment on table INT_TARIFFSERVICECLASS is 'defines all valid service codes and service class''s for a given tariffmodel'
/

comment on column INT_TARIFFSERVICECLASS.TSC_GROUP is 'references the tsc mapping group code'
/

comment on column INT_TARIFFSERVICECLASS.TARIFFMODEL is 'TARIFFMODEL'
/

comment on column INT_TARIFFSERVICECLASS.RANK is 'RANK'
/

comment on column INT_TARIFFSERVICECLASS.VALID_FROM is 'this mapping entry is valid from (Format: YYYYMMDD or MON-SUN[HH:MM]) (compare: >=)'
/

comment on column INT_TARIFFSERVICECLASS.VALID_TO is 'defines the date till when this entry is valid (Format: YYYYMMDD or MON-SUN[HH:MM]) (compare: <)'
/

comment on column INT_TARIFFSERVICECLASS.QOS_REQUESTED is 'condition: the QoS-Requested which should be matched (if empty all match)'
/

comment on column INT_TARIFFSERVICECLASS.QOS_USED is 'condition: the QoS-Used which should be matched (if empty all match)'
/

comment on column INT_TARIFFSERVICECLASS.CALLCLASS is 'CALLCLASS'
/

comment on column INT_TARIFFSERVICECLASS.CALLTYPE is 'CALLTYPE'
/

comment on column INT_TARIFFSERVICECLASS.SERVICECODE is 'SERVICECODE'
/

comment on column INT_TARIFFSERVICECLASS.SERVICECLASS is 'condition: the serviceclass which should be mapped (if empty all match)'
/

comment on column INT_TARIFFSERVICECLASS.ZONE is 'ZONE'
/

comment on column INT_TARIFFSERVICECLASS.NEW_SERVICECODE is 'NEW_SERVICECODE'
/

comment on column INT_TARIFFSERVICECLASS.NEW_SERVICECLASS is 'NEW_SERVICECLASS'
/

comment on column INT_TARIFFSERVICECLASS.NAME is 'NAME'
/

comment on column INT_TARIFFSERVICECLASS.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TARIFFSERVICECLASS.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TARIFFSERVICECLASS.MODIFBY is 'MODIFBY'
/

comment on column INT_TARIFFSERVICECLASS.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TARIFFSERVICECLASS.MODIFIED is 'MODIFIED'
/

comment on column INT_TARIFFSERVICECLASS.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_TAX                                            
-- ============================================================
drop table INT_TAX cascade constraints;

create table INT_TAX
(
    TAXGROUP                 VARCHAR2(5)            not null,
    TAXCODE                  VARCHAR2(5)            not null,
    VALID_FROM               DATE                   not null,
    TAXRATE                  NUMBER(4)              not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TAX check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TAX primary key (TAXGROUP, TAXCODE, VALID_FROM)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_TAX to INTEGRATE_ROLE_ALL
/
grant select on INT_TAX to INTEGRATE_ROLE_SEL
/

comment on table INT_TAX is 'defines the different possible tax codes and tax rates'
/

comment on column INT_TAX.TAXGROUP is 'tax group identifier as handed over via a subscriber'
/

comment on column INT_TAX.TAXCODE is 'tax code identifier as handed over via a g/l account'
/

comment on column INT_TAX.VALID_FROM is 'defines the date form which on a specific tax rate should be applied'
/

comment on column INT_TAX.TAXRATE is 'applied tax rate (e.g. 1600 for 16%), used for tax conversion'
/

comment on column INT_TAX.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TAX.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TAX.MODIFBY is 'MODIFBY'
/

comment on column INT_TAX.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TAX.MODIFIED is 'MODIFIED'
/

comment on column INT_TAX.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_CONTENT_MAP                                    
-- ============================================================
drop table INT_CONTENT_MAP cascade constraints;

create table INT_CONTENT_MAP
(
    EDR_FORMAT               VARCHAR2(10)           not null,
    RANK                     NUMBER(9)              not null,
    DESTIN_AREACODE          VARCHAR2(2000)         default '*' not null,
    TRANSIT_AREACODE         VARCHAR2(2000)         default '*' not null,
    CALLCLASS                VARCHAR2(2000)         default '*' not null,
    SERVICECODE              VARCHAR2(2000)         default '*' not null,
    VAS_CODE                 VARCHAR2(2000)         default '*' not null,
    APPLICATION              VARCHAR2(2000)         default '*' not null,
    CONTENTPROVIDER          NUMBER(9)              null    ,
    CONTENTCODE              VARCHAR2(8)            null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CONTENT_MAP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_CNM primary key (EDR_FORMAT, RANK)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_CONTENT_MAP to INTEGRATE_ROLE_ALL
/
grant select on INT_CONTENT_MAP to INTEGRATE_ROLE_SEL
/

comment on table INT_CONTENT_MAP is 'defines possible content mapping rules'
/

comment on column INT_CONTENT_MAP.EDR_FORMAT is 'references the related edr format for which this mapping should be applied'
/

comment on column INT_CONTENT_MAP.RANK is 'unique sequence order in which the mapping should be performed'
/

comment on column INT_CONTENT_MAP.DESTIN_AREACODE is 'DESTIN_AREACODE'
/

comment on column INT_CONTENT_MAP.TRANSIT_AREACODE is 'TRANSIT_AREACODE'
/

comment on column INT_CONTENT_MAP.CALLCLASS is 'CALLCLASS'
/

comment on column INT_CONTENT_MAP.SERVICECODE is 'SERVICECODE'
/

comment on column INT_CONTENT_MAP.VAS_CODE is 'VAS_CODE'
/

comment on column INT_CONTENT_MAP.APPLICATION is 'APPLICATION'
/

comment on column INT_CONTENT_MAP.CONTENTPROVIDER is 'references the related content provider to which the mapping belongs'
/

comment on column INT_CONTENT_MAP.CONTENTCODE is 'references the related content code to which the mapping should apply'
/

comment on column INT_CONTENT_MAP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_CONTENT_MAP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_CONTENT_MAP.MODIFBY is 'MODIFBY'
/

comment on column INT_CONTENT_MAP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_CONTENT_MAP.MODIFIED is 'MODIFIED'
/

comment on column INT_CONTENT_MAP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: AGG_AGGREGATION                                    
-- ============================================================
drop table AGG_AGGREGATION cascade constraints;

create table AGG_AGGREGATION
(
    AGGREGATION_ID           NUMBER(9)              not null,
    SCENARIO_ID              NUMBER(9)              not null,
    COL_OBJ_ID               NUMBER(9)              not null,
    RANK                     NUMBER(9)              not null,
    COL_NAME                 VARCHAR2(30)           not null,
    PRECISION                NUMBER(9)              null    ,
    AGGREGATION_FUNCTION     NUMBER(2)              not null
        constraint CKC_AGGREGAT_AGG_FUNC check (AGGREGATION_FUNCTION in (00,01,02)),
    AGGREGATION_STATUS       NUMBER(1)              default 0 not null
        constraint CKC_AGGREGAT_AGG_STATUS check (AGGREGATION_STATUS in (0,1)),
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_AGG_AGGREGATION check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_AGG_AGGREGATION primary key (AGGREGATION_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_AGGREGATION to INTEGRATE_ROLE_ALL
/
grant select on AGG_AGGREGATION to INTEGRATE_ROLE_SEL
/

comment on table AGG_AGGREGATION is 'This table holds all information about aggregation columns'
/

comment on column AGG_AGGREGATION.AGGREGATION_ID is 'Internal ID => Generated by sequence ''AGG_AGGREGATION_SEQ'''
/

comment on column AGG_AGGREGATION.SCENARIO_ID is 'Internal ID => Generated by sequence ''AGG_SCENARIO_SEQ'''
/

comment on column AGG_AGGREGATION.COL_OBJ_ID is 'Internal ID => Generated by sequence ''SOL_OBJS_SEQ'''
/

comment on column AGG_AGGREGATION.RANK is 'Internal ID to specify the position of an aggregation column through all defined aggregation columns in a scenario'
/

comment on column AGG_AGGREGATION.COL_NAME is 'Specifies the column name used by the aggregate process'
/

comment on column AGG_AGGREGATION.PRECISION is 'NULL for maximum precision'
/

comment on column AGG_AGGREGATION.AGGREGATION_FUNCTION is 'Specifies the function which will be used for the aggregation process'
/

comment on column AGG_AGGREGATION.AGGREGATION_STATUS is 'Boolean Flag which specifies whether the aggregation is currently active (will be used) or not.'
/

comment on column AGG_AGGREGATION.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column AGG_AGGREGATION.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column AGG_AGGREGATION.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column AGG_AGGREGATION.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column AGG_AGGREGATION.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column AGG_AGGREGATION.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: BIDX_AGG_AGG_STATUS                                
-- ============================================================
create index BIDX_AGG_AGG_STATUS on AGG_AGGREGATION (AGGREGATION_STATUS asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Index: BIDX_AGG_AGG_FUNCTION                              
-- ============================================================
create index BIDX_AGG_AGG_FUNCTION on AGG_AGGREGATION (AGGREGATION_FUNCTION asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Index: AK_AGG_AGG_SCN_COL                                 
-- ============================================================
create unique index AK_AGG_AGG_SCN_COL on AGG_AGGREGATION (SCENARIO_ID asc, COL_OBJ_ID asc, RANK asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: AGG_CONDITION                                      
-- ============================================================
drop table AGG_CONDITION cascade constraints;

create table AGG_CONDITION
(
    CONDITION_ID             NUMBER(9)              not null,
    SCENARIO_ID              NUMBER(9)              not null,
    COL_OBJ_ID               NUMBER(9)              not null,
    CONDITION_VALUE          VARCHAR2(2000)         not null,
    CONDITION_DATATYPE       NUMBER(1)              not null
        constraint CKC_CONDITIO_AGG_COND_DAT check (CONDITION_DATATYPE in (0,1,2)),
    CONDITION_STATUS         NUMBER(1)              default 0 not null
        constraint CKC_CONDITIO_COND_STAT check (CONDITION_STATUS in (0,1)),
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_AGG_CONDITION check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_AGG_CONDITION primary key (CONDITION_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_CONDITION to INTEGRATE_ROLE_ALL
/
grant select on AGG_CONDITION to INTEGRATE_ROLE_SEL
/

comment on table AGG_CONDITION is 'Defines the conditions used for an aggregatescenario'
/

comment on column AGG_CONDITION.CONDITION_ID is 'Internal ID => Generated by sequence ''AGG_CONDITION_SEQ'''
/

comment on column AGG_CONDITION.SCENARIO_ID is 'Internal ID => Generated by sequence ''AGG_SCENARIO_SEQ'''
/

comment on column AGG_CONDITION.COL_OBJ_ID is 'Internal ID => Generated by sequence ''SOL_OBJS_SEQ'''
/

comment on column AGG_CONDITION.CONDITION_VALUE is 'Value depends on Datatype; Decimalpoint for NumberValues is ''.'' (DOT); Date/Time Format: YYYYMMDDHHMMSS'
/

comment on column AGG_CONDITION.CONDITION_DATATYPE is 'CONDITION_DATATYPE'
/

comment on column AGG_CONDITION.CONDITION_STATUS is 'Boolean Flag which specifies whether the condition is currently active (will be used) or not.'
/

comment on column AGG_CONDITION.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column AGG_CONDITION.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column AGG_CONDITION.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column AGG_CONDITION.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column AGG_CONDITION.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column AGG_CONDITION.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Index: AK_AGG_COND_SCN_COL                                
-- ============================================================
create unique index AK_AGG_COND_SCN_COL on AGG_CONDITION (SCENARIO_ID asc, COL_OBJ_ID asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Index: BIDX_AGG_COND_STATUS                               
-- ============================================================
create index BIDX_AGG_COND_STATUS on AGG_CONDITION (CONDITION_STATUS asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Index: BIDX_AGG_COND_TYPE                                 
-- ============================================================
create index BIDX_AGG_COND_TYPE on AGG_CONDITION (CONDITION_DATATYPE asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: SOL_CONST_COLS                                     
-- ============================================================
drop table SOL_CONST_COLS cascade constraints;

create table SOL_CONST_COLS
(
    CONSTRAINT_ID            NUMBER(9)              not null,
    PARENT_COL_ID            NUMBER(9)              not null,
    CHILD_COL_ID             NUMBER(9)              not null,
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    constraint PK_SOL_CONST_COLS primary key (CONSTRAINT_ID, PARENT_COL_ID, CHILD_COL_ID)
        using index
     tablespace SOL_TS_1_IDX
)
tablespace SOL_TS_1_DAT
/
grant select, insert, update, delete on SOL_CONST_COLS to INTEGRATE_ROLE_ALL
/
grant select on SOL_CONST_COLS to INTEGRATE_ROLE_SEL
/

comment on table SOL_CONST_COLS is 'SOL_CONST_COLS'
/

comment on column SOL_CONST_COLS.CONSTRAINT_ID is 'Internal ID => Generated by sequence ''SOL_CONSTRAINTS_SEQ'''
/

comment on column SOL_CONST_COLS.PARENT_COL_ID is 'PARENT_COL_ID'
/

comment on column SOL_CONST_COLS.CHILD_COL_ID is 'CHILD_COL_ID'
/

comment on column SOL_CONST_COLS.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column SOL_CONST_COLS.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/


-- ============================================================
--   Table: AGG_REFERENCESET_CNF                               
-- ============================================================
drop table AGG_REFERENCESET_CNF cascade constraints;

create table AGG_REFERENCESET_CNF
(
    REFERENCESET_ID          NUMBER(9)              not null,
    COL_OBJ_ID               NUMBER(9)              not null,
    RANK                     NUMBER(9)              not null,
    constraint PK_AGG_REFERENCESET_CNF primary key (REFERENCESET_ID, COL_OBJ_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_REFERENCESET_CNF to INTEGRATE_ROLE_ALL
/
grant select on AGG_REFERENCESET_CNF to INTEGRATE_ROLE_SEL
/

comment on table AGG_REFERENCESET_CNF is 'Defines the available attributes in a referenceset'
/

comment on column AGG_REFERENCESET_CNF.REFERENCESET_ID is 'Internal ID => Generated by sequence ''AGG_REFERENCESET_SEQ'''
/

comment on column AGG_REFERENCESET_CNF.COL_OBJ_ID is 'Internal ID => Generated by sequence ''SOL_OBJS_SEQ'''
/

comment on column AGG_REFERENCESET_CNF.RANK is 'Internal ID to specify the position of an column through all defined columns in a referenceset'
/


-- ============================================================
--   Index: AK_AGG_REFSETCNF_REFSET_RANK                       
-- ============================================================
create unique index AK_AGG_REFSETCNF_REFSET_RANK on AGG_REFERENCESET_CNF (REFERENCESET_ID asc, RANK asc)
tablespace AGGREGATE_TS_1_IDX
/

-- ============================================================
--   Table: AGG_EDRFORMAT_SCN                                  
-- ============================================================
drop table AGG_EDRFORMAT_SCN cascade constraints;

create table AGG_EDRFORMAT_SCN
(
    FORMAT_ID                NUMBER(9)              not null,
    SCENARIO_ID              NUMBER(9)              not null,
    TAB_NAME                 VARCHAR2(30)           null    ,
    FLUSHMODE                NUMBER(1)              null    
        constraint CKC_FLUSHMOD_AGG_EDRFORMAT_SCN check (FLUSHMODE is null or (FLUSHMODE in (0,1,2,3))),
    THRESHOLD                NUMBER(9)              null    ,
    TEMP_DIR                 VARCHAR2(254)          null    ,
    DONE_DIR                 VARCHAR2(254)          null    ,
    CTL_DIR                  VARCHAR2(254)          null    ,
    FIELD_DELIMITER          CHAR(1)                null    ,
    ENTRYDATE                DATE                   default sysdate not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_AGG_EDRF_MODIFIED check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_AGG_EDRFORMAT_SCN primary key (FORMAT_ID, SCENARIO_ID)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_EDRFORMAT_SCN to INTEGRATE_ROLE_ALL
/
grant select on AGG_EDRFORMAT_SCN to INTEGRATE_ROLE_SEL
/

comment on table AGG_EDRFORMAT_SCN is 'Defines the EDR-Format Scenario relationship. Which scenario is valid for which EDR-Format'
/

comment on column AGG_EDRFORMAT_SCN.FORMAT_ID is 'Internal ID => Referenced Format ID. Produced by sequence ''AGG_EDRFORMAT_SEQ'''
/

comment on column AGG_EDRFORMAT_SCN.SCENARIO_ID is 'Internal ID => Generated by sequence ''AGG_SCENARIO_SEQ'''
/

comment on column AGG_EDRFORMAT_SCN.TAB_NAME is 'Name of the table in the target database'
/

comment on column AGG_EDRFORMAT_SCN.FLUSHMODE is 'Defines the flushing strategy for the FCT-aggregate'
/

comment on column AGG_EDRFORMAT_SCN.THRESHOLD is 'THRESHOLD'
/

comment on column AGG_EDRFORMAT_SCN.TEMP_DIR is 'Path for the temporary aggregation results'
/

comment on column AGG_EDRFORMAT_SCN.DONE_DIR is 'Path for the aggregation results'
/

comment on column AGG_EDRFORMAT_SCN.CTL_DIR is 'Path for controlfiles'
/

comment on column AGG_EDRFORMAT_SCN.FIELD_DELIMITER is 'Fielddelimiter used to delimit the fields in aggregation results'
/

comment on column AGG_EDRFORMAT_SCN.ENTRYDATE is 'DateTime Stamp should be set when a row is inserted. Default SYSDATE'
/

comment on column AGG_EDRFORMAT_SCN.ENTRYBY is 'User-ID which should be set when a row is inserted.'
/

comment on column AGG_EDRFORMAT_SCN.MODIFDATE is 'DateTime Stamp should be set when a row is updated.'
/

comment on column AGG_EDRFORMAT_SCN.MODIFBY is 'User-ID which should be set when a row is updated.'
/

comment on column AGG_EDRFORMAT_SCN.MODIFIED is 'Flag specifies, whether a Row is modified since last Export. Should be set be a row is inserted or updated'
/

comment on column AGG_EDRFORMAT_SCN.RECVER is 'Record Version of a row'
/


-- ============================================================
--   Table: AGG_DICTIONARY                                     
-- ============================================================
drop table AGG_DICTIONARY cascade constraints;

create table AGG_DICTIONARY
(
    IMPORT_TABLE             VARCHAR2(30)           not null,
    IMPORT_COLUMN            VARCHAR2(30)           not null,
    DESTINATION_COLUMN       VARCHAR2(30)           not null,
    EXPAND_VALUE             VARCHAR2(30)           null    ,
    KEY                      NUMBER(1)              default 0 not null
        constraint CKC_KEY_AGG_DICTIONARY check (KEY in (0,1)),
    COLUMN_GROUP             VARCHAR2(30)           null    ,
    constraint PK_AGG_DICTIONARY primary key (IMPORT_TABLE, IMPORT_COLUMN)
        using index
     tablespace AGGREGATE_TS_1_IDX
)
tablespace AGGREGATE_TS_1_DAT
/
grant select, insert, update, delete on AGG_DICTIONARY to INTEGRATE_ROLE_ALL
/
grant select on AGG_DICTIONARY to INTEGRATE_ROLE_SEL
/

comment on table AGG_DICTIONARY is 'keeps the sqlAggregator dictionary for the import table'
/

comment on column AGG_DICTIONARY.IMPORT_TABLE is 'name of the import table'
/

comment on column AGG_DICTIONARY.IMPORT_COLUMN is 'name of the column in the import table'
/

comment on column AGG_DICTIONARY.DESTINATION_COLUMN is 'name of the column in the destination table'
/

comment on column AGG_DICTIONARY.EXPAND_VALUE is 'the value of the expanded key column'
/

comment on column AGG_DICTIONARY.KEY is 'defines wether column is a key columns (1:true, 0:false)'
/

comment on column AGG_DICTIONARY.COLUMN_GROUP is 'the column group'
/


-- ============================================================
--   Table: INT_ICNO_LNK                                       
-- ============================================================
drop table INT_ICNO_LNK cascade constraints;

create table INT_ICNO_LNK
(
    ICPRODUCT                VARCHAR2(10)           not null,
    NO                       NUMBER(9)              not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    TARIFFMODEL              NUMBER(9)              not null,
    ALT_TARIFFMODEL          NUMBER(9)              null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_ICNO_LNK check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_INL primary key (ICPRODUCT, NO, VALID_FROM)
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
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_ICNO_LNK to INTEGRATE_ROLE_ALL
/
grant select on INT_ICNO_LNK to INTEGRATE_ROLE_SEL
/

comment on table INT_ICNO_LNK is 'defines all affected carriers with their tariffmodel in direct billing mode'
/

comment on column INT_ICNO_LNK.ICPRODUCT is 'references the ic-product for this configuration'
/

comment on column INT_ICNO_LNK.NO is 'references the related network operator this configuration entry is valid to'
/

comment on column INT_ICNO_LNK.VALID_FROM is 'date from when on this entry is valid'
/

comment on column INT_ICNO_LNK.VALID_TO is 'date till when this entry is valid'
/

comment on column INT_ICNO_LNK.TARIFFMODEL is 'references the tariff model which should be used for (reseller or carrier) interconnection purpose'
/

comment on column INT_ICNO_LNK.ALT_TARIFFMODEL is 'alternative tariffmodel for simulation purpose'
/

comment on column INT_ICNO_LNK.ENTRYBY is 'ENTRYBY'
/

comment on column INT_ICNO_LNK.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_ICNO_LNK.MODIFBY is 'MODIFBY'
/

comment on column INT_ICNO_LNK.MODIFDATE is 'MODIFDATE'
/

comment on column INT_ICNO_LNK.MODIFIED is 'MODIFIED'
/

comment on column INT_ICNO_LNK.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_UOM_MAP                                        
-- ============================================================
drop table INT_UOM_MAP cascade constraints;

create table INT_UOM_MAP
(
    CHARGE_ITEM              CHAR(1)                default 'Q' not null
        constraint CKC_CHARGE_I_INT_UOM_MAP check (CHARGE_ITEM in ('Q','S','R','E')),
    FROM_UOM                 VARCHAR2(3)            not null,
    TO_UOM                   VARCHAR2(3)            not null,
    UOM_FACTOR               NUMBER                 default 1 not null,
    ROUNDING                 CHAR(1)                default 'N' not null
        constraint CKC_ROUNDING_INT_UOM_MAP check (ROUNDING in ('N','U','D')),
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_UOM_MAP check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_UMM primary key (CHARGE_ITEM, FROM_UOM, TO_UOM)
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
tablespace INTEGRATE_TS_1_DAT
/
grant select, insert, update, delete on INT_UOM_MAP to INTEGRATE_ROLE_ALL
/
grant select on INT_UOM_MAP to INTEGRATE_ROLE_SEL
/

comment on table INT_UOM_MAP is 'mapping table for UoM mapping and conversion'
/

comment on column INT_UOM_MAP.CHARGE_ITEM is 'defines if the mapping conversion is related to Q=quantity, S=sent volume or R=received volume'
/

comment on column INT_UOM_MAP.FROM_UOM is 'defines from which UoM a mapping-conversion should apply'
/

comment on column INT_UOM_MAP.TO_UOM is 'defines to which UoM a mapping-conversion should apply'
/

comment on column INT_UOM_MAP.UOM_FACTOR is 'describes the factor for converting one UoM to another UoM (e.g. a factor of 1024 whould convert KiloBytes into Bytes)'
/

comment on column INT_UOM_MAP.ROUNDING is 'describes the method of rounding (N=nearest, U=aleays up, D=always down)'
/

comment on column INT_UOM_MAP.ENTRYBY is 'ENTRYBY'
/

comment on column INT_UOM_MAP.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_UOM_MAP.MODIFBY is 'MODIFBY'
/

comment on column INT_UOM_MAP.MODIFDATE is 'MODIFDATE'
/

comment on column INT_UOM_MAP.MODIFIED is 'MODIFIED'
/

comment on column INT_UOM_MAP.RECVER is 'RECVER'
/


-- ============================================================
--   Table: INT_SUBS_REFERENCE_HIST                            
-- ============================================================
drop table INT_SUBS_REFERENCE_HIST cascade constraints;

create table INT_SUBS_REFERENCE_HIST
(
    CONTRACT                 NUMBER(38)             not null,
    KEY                      VARCHAR2(10)           not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   default sysdate null    ,
    VALUE                    VARCHAR2(20)           null    ,
    constraint PK_INT_SRH primary key (CONTRACT, KEY, VALID_FROM)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_4_IDX
        storage
        (
        initial 2M
        next 2M
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
initial 4M
next 4M
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_4_DAT
/
grant select, insert, update, delete on INT_SUBS_REFERENCE_HIST to INTEGRATE_ROLE_ALL
/
grant select on INT_SUBS_REFERENCE_HIST to INTEGRATE_ROLE_SEL
/

comment on table INT_SUBS_REFERENCE_HIST is 'defines flexible subscriber specific add-on reference fields'
/

comment on column INT_SUBS_REFERENCE_HIST.CONTRACT is 'references the contract id these historical data is referenced to'
/

comment on column INT_SUBS_REFERENCE_HIST.KEY is 'defines a unique subscriber related new reference key'
/

comment on column INT_SUBS_REFERENCE_HIST.VALID_FROM is 'date from when on this entry is valid'
/

comment on column INT_SUBS_REFERENCE_HIST.VALID_TO is 'date till when on this entry is'
/

comment on column INT_SUBS_REFERENCE_HIST.VALUE is 'VALUE'
/


-- ============================================================
--   Table: INT_TRUNK_CNF                                      
-- ============================================================
drop table INT_TRUNK_CNF cascade constraints;

create table INT_TRUNK_CNF
(
    NETWORKMODEL             NUMBER(9)              not null,
    DIRECTION                CHAR(1)                default 'I' not null
        constraint CKC_DIRECTIO_INT_TRUNK_CNF check (DIRECTION in ('I','O')),
    TRUNK                    VARCHAR2(15)           not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    ICPRODUCT_GROUP          VARCHAR2(10)           not null,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFIED                 NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TRUNK_CNF check (MODIFIED in (0,1)),
    RECVER                   NUMBER(9)              default 0 not null,
    constraint PK_INT_TRC primary key (NETWORKMODEL, DIRECTION, TRUNK, VALID_FROM)
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
initial 512K
next 512K
minextents 1
maxextents unlimited
pctincrease 0
)
tablespace INTEGRATE_TS_2_DAT
/
grant select, insert, update, delete on INT_TRUNK_CNF to INTEGRATE_ROLE_ALL
/
grant select on INT_TRUNK_CNF to INTEGRATE_ROLE_SEL
/

comment on table INT_TRUNK_CNF is 'trunk configuration and link table for ic product groups'
/

comment on column INT_TRUNK_CNF.NETWORKMODEL is 'uniquely identifies a related network model'
/

comment on column INT_TRUNK_CNF.DIRECTION is 'defines which trunk direction should be used (I = inroute, O = outroute)'
/

comment on column INT_TRUNK_CNF.TRUNK is 'refers to the related trunk id for which an ic product group should be defined'
/

comment on column INT_TRUNK_CNF.VALID_FROM is 'date from when on this entry is valid'
/

comment on column INT_TRUNK_CNF.VALID_TO is 'date til when this entry is valid'
/

comment on column INT_TRUNK_CNF.ICPRODUCT_GROUP is 'defines the ic product group which should be used for a given direction and trunk id'
/

comment on column INT_TRUNK_CNF.ENTRYBY is 'ENTRYBY'
/

comment on column INT_TRUNK_CNF.ENTRYDATE is 'ENTRYDATE'
/

comment on column INT_TRUNK_CNF.MODIFBY is 'MODIFBY'
/

comment on column INT_TRUNK_CNF.MODIFDATE is 'MODIFDATE'
/

comment on column INT_TRUNK_CNF.MODIFIED is 'MODIFIED'
/

comment on column INT_TRUNK_CNF.RECVER is 'RECVER'
/


-- ============================================================
--   View: AGG_FORMAT_MAP_COLUMNS                              
-- ============================================================
create or replace view AGG_FORMAT_MAP_COLUMNS as
SELECT 
  SOL_OBJS.OBJ_ID OBJ_ID,
  SOL_OBJS.OWNER OWNER,
  SOL_OBJS.NAME NAME,
  SOL_OBJS.DESCRIPTION DESCRIPTION,
  SOL_OBJS.OBJ_TYPE OBJ_TYPE,
  SOL_OBJS.OBJ_STATUS OBJ_STATUS,
  SOL_COLS.EXPRESSION EXPRESSION,
  SOL_COLS.DATATYPE DATATYPE,
  SOL_COLS.DATALENGTH DATALENGTH,
  SOL_COLS.DATAPRECISION DATAPRECISION,
  SOL_COLS.DATASCALE DATASCALE,
  SOL_COLS.STRINGTYPE STRINGTYPE,
  SOL_COLS.NULLABLE NULLABLE,
  SOL_COLS.DOMAIN DOMAIN,
  SOL_COLS.FORMAT FORMAT,
  SOL_COLS.PIVOTPOSITION PIVOTPOSITION,
  SOL_COLS.ALIGNMENT ALIGNMENT,
  SOL_COLS.RANGEITEM_DOMAIN RANGEITEM_DOMAIN,
  SOL_COLS.VALUEITEM_DOMAIN VALUEITEM_DOMAIN,
  AGG_EDRCFIELD.EDRCFIELD_ID EDRCFIELD_ID,
  AGG_EDRCFIELD.EDRC_TYPE EDRC_TYPE,
  AGG_EDRCFIELD.INTERNAL_FIELD_ID INTERNAL_FIELD_ID,
  AGG_EDRCFIELD.INTERNAL_FIELDNAME INTERNAL_FIELDNAME,
  AGG_EDRCFIELD.RULE_USAGE RULE_USAGE,
  AGG_EDRFORMAT_CNF.FORMAT_ID FORMAT_ID
FROM 
  SOL_OBJS,
  SOL_COLS,
  AGG_EDRCFIELD,
  AGG_EDRFORMAT_CNF
WHERE 
  SOL_COLS.OBJ_ID = AGG_EDRCFIELD.COL_OBJ_ID    and
  SOL_OBJS.OBJ_ID = SOL_COLS.OBJ_ID    and
  AGG_EDRCFIELD.EDRCFIELD_ID = AGG_EDRFORMAT_CNF.EDRCFIELD_ID    
UNION    
SELECT 
  SOL_OBJS.OBJ_ID OBJ_ID,
  SOL_OBJS.OWNER OWNER,
  SOL_OBJS.NAME NAME,
  SOL_OBJS.DESCRIPTION DESCRIPTION,
  SOL_OBJS.OBJ_TYPE OBJ_TYPE,
  SOL_OBJS.OBJ_STATUS OBJ_STATUS,
  SOL_COLS.EXPRESSION EXPRESSION,
  SOL_COLS.DATATYPE DATATYPE,
  SOL_COLS.DATALENGTH DATALENGTH,
  SOL_COLS.DATAPRECISION DATAPRECISION,
  SOL_COLS.DATASCALE DATASCALE,
  SOL_COLS.STRINGTYPE STRINGTYPE,
  SOL_COLS.NULLABLE NULLABLE,
  SOL_COLS.DOMAIN DOMAIN,
  SOL_COLS.FORMAT FORMAT,
  SOL_COLS.PIVOTPOSITION PIVOTPOSITION,
  SOL_COLS.ALIGNMENT ALIGNMENT,
  SOL_COLS.RANGEITEM_DOMAIN RANGEITEM_DOMAIN,
  SOL_COLS.VALUEITEM_DOMAIN VALUEITEM_DOMAIN,
  AGG_EDRCFIELD.EDRCFIELD_ID EDRCFIELD_ID,
  AGG_EDRCFIELD.EDRC_TYPE EDRC_TYPE,
  AGG_EDRCFIELD.INTERNAL_FIELD_ID INTERNAL_FIELD_ID,
  AGG_EDRCFIELD.INTERNAL_FIELDNAME INTERNAL_FIELDNAME,
  AGG_EDRCFIELD.RULE_USAGE RULE_USAGE,
  AGG_EDRFORMAT_CNF.FORMAT_ID FORMAT_ID
FROM 
  SOL_OBJS,
  SOL_COLS,
  AGG_EDRCFIELD,
  AGG_EDRFORMAT_CNF,
  AGG_REFERENCESET_CNF
WHERE 
  SOL_COLS.OBJ_ID = AGG_REFERENCESET_CNF.COL_OBJ_ID    and
  SOL_OBJS.OBJ_ID = SOL_COLS.OBJ_ID    and
  AGG_REFERENCESET_CNF.REFERENCESET_ID = AGG_EDRCFIELD.REFERENCESET_ID    and
  AGG_EDRCFIELD.EDRCFIELD_ID = AGG_EDRFORMAT_CNF.EDRCFIELD_ID
/

GRANT SELECT ON AGG_FORMAT_MAP_COLUMNS TO INTEGRATE_ROLE_SEL
/

comment on table AGG_FORMAT_MAP_COLUMNS is 'AGG_FORMAT_MAP_COLUMNS'
/

alter table INT_DISCOUNTMDL_VER
    add constraint FK_INT_DMV_DML foreign key  (DISCOUNTMODEL)
       references INT_DISCOUNTMODEL (DISCOUNTMODEL)
/

alter table INT_SUBSDISCOUNT_MAP
    add constraint FK_INT_SDM_DML foreign key  (INT_DISCOUNTMODEL)
       references INT_DISCOUNTMODEL (DISCOUNTMODEL) on delete cascade
/

alter table SOL_TABS
    add constraint FK_SOL_TABS_SOL_OBJS foreign key  (OBJ_ID)
       references SOL_OBJS (OBJ_ID) on delete cascade
/

alter table SOL_CONSTRAINTS
    add constraint FK_SOL_TAB_PARENT_CONSTR foreign key  (PARENT_TAB_ID)
       references SOL_TABS (OBJ_ID) on delete cascade
/

alter table SOL_CONSTRAINTS
    add constraint FK_SOL_TAB_CHILD_CONSTR foreign key  (CHILD_TAB_ID)
       references SOL_TABS (OBJ_ID) on delete cascade
/

alter table SOL_COLS
    add constraint FK_SOL_COLS_SOL_UNITS foreign key  (UNIT_ID)
       references SOL_UNITS (UNIT_ID)
/

alter table SOL_COLS
    add constraint FK_SOL_COLS_SOL_TABS foreign key  (TAB_OBJ_ID)
       references SOL_TABS (OBJ_ID) on delete cascade
/

alter table SOL_COLS
    add constraint FK_SOL_COLS_SOL_OBJS foreign key  (OBJ_ID)
       references SOL_OBJS (OBJ_ID) on delete cascade
/

alter table AGG_GROUPING
    add constraint FK_AGG_GROUPING_SOL_COLS foreign key  (COL_OBJ_ID)
       references SOL_COLS (OBJ_ID)
/

alter table AGG_GROUPING
    add constraint FK_AGG_GROUPING_AGG_SCENARIO foreign key  (SCENARIO_ID)
       references AGG_SCENARIO (SCENARIO_ID) on delete cascade
/

alter table AGG_EDRCFIELD
    add constraint FK_AGG_EDRCFIELD_AGG_REFSET foreign key  (REFERENCESET_ID)
       references AGG_REFERENCESET (REFERENCESET_ID)
/

alter table AGG_EDRCFIELD
    add constraint FK_AGG_EDRCFIELD_SOL_COLS foreign key  (COL_OBJ_ID)
       references SOL_COLS (OBJ_ID)
/

alter table AGG_GROUPING_CNF
    add constraint FK_AGG_GRPCNF_AGG_GRP foreign key  (GROUPING_ID)
       references AGG_GROUPING (GROUPING_ID) on delete cascade
/

alter table AGG_GROUPING_CNF
    add constraint FK_AGG_GRPCNF_AGG_CLASS foreign key  (CLASS_ID)
       references AGG_CLASS (CLASS_ID)
/

alter table AGG_CLASSCON
    add constraint FK_AGG_CLSCON_AGG_GRPNEXT foreign key  (NEXT_GROUPING_CNF_ID)
       references AGG_GROUPING_CNF (GROUPING_CNF_ID) on delete cascade
/

alter table AGG_CLASSCON
    add constraint FK_AGG_CLSCON_AGG_GRPNODE foreign key  (NODE_GROUPING_CNF_ID)
       references AGG_GROUPING_CNF (GROUPING_CNF_ID) on delete cascade
/

alter table INT_ZONEMODEL
    add constraint FK_INT_ZMD_GMD foreign key  (GEOMODEL)
       references INT_GEOGRAPHICALMODEL (GEOMODEL)
/

alter table INT_ZONEMODEL
    add constraint FK_INT_ZMD_APG foreign key  (APN_GROUP)
       references INT_APN_GROUP (APN_GROUP)
/

alter table INT_GLACCOUNT
    add constraint FK_INT_GLA_TXC foreign key  (TAXCODE)
       references INT_TAXCODE (TAXCODE)
/

alter table INT_SERVICE
    add constraint FK_INT_SRV_SRV foreign key  (PARENT_SERVICE)
       references INT_SERVICE (SERVICECODE)
/

alter table INT_SERVICE
    add constraint FK_INT_SRV_QUOM foreign key  (UOM_Q)
       references INT_UOM (UOM)
/

alter table INT_SERVICE
    add constraint FK_INT_SRV_SUOM foreign key  (UOM_S)
       references INT_UOM (UOM)
/

alter table INT_SERVICE
    add constraint FK_INT_SRV_RUOM foreign key  (UOM_R)
       references INT_UOM (UOM)
/

alter table INT_SERVICE
    add constraint FK_INT_SRV_GLA foreign key  (DEF_GLACCOUNT)
       references INT_GLACCOUNT (GLACCOUNT)
/

alter table INT_SERVICE
    add constraint FK_INT_SRV_RVG foreign key  (DEF_REVENUEGROUP)
       references INT_REVENUEGROUP (REVENUEGROUP)
/

alter table INT_SUBSSERVICE_MAP
    add constraint FK_INT_SSM_SRV foreign key  (INT_SERVICECODE)
       references INT_SERVICE (SERVICECODE)
/

alter table INT_SERVICECLASS
    add constraint FK_INT_SVC_SRV foreign key  (SERVICECODE)
       references INT_SERVICE (SERVICECODE)
/

alter table INT_NETWORKOPERATOR
    add constraint FK_INT_NOP_TXG foreign key  (TAXGROUP)
       references INT_TAXGROUP (TAXGROUP)
/

alter table INT_NETWORKOPERATOR
    add constraint FK_INT_NOP_CUR foreign key  (CURRENCY)
       references INT_CURRENCY (CURRENCY)
/

alter table INT_CONTENTPROVIDER
    add constraint FK_INT_CPD_TXG foreign key  (TAXGROUP)
       references INT_TAXGROUP (TAXGROUP)
/

alter table INT_CONTENTPROVIDER
    add constraint FK_INT_CPD_CUR foreign key  (CURRENCY)
       references INT_CURRENCY (CURRENCY)
/

alter table INT_SUBS_CONTRACT
    add constraint FK_INT_SUB_SYB foreign key  (SYSTEM_BRAND)
       references INT_SYSTEM_BRAND (SYSTEM_BRAND)
/

alter table INT_SUBS_CONTRACT
    add constraint FK_INT_SUB_TXG foreign key  (SUBS_TAXGROUP)
       references INT_TAXGROUP (TAXGROUP)
/

alter table INT_SUBS_CONTRACT
    add constraint FK_INT_SUB_CUR foreign key  (SUBS_CURRENCY)
       references INT_CURRENCY (CURRENCY)
/

alter table INT_TARIFFMODEL
    add constraint FK_INT_TMD_CAL foreign key  (CALENDAR)
       references INT_CALENDAR (CALENDAR)
/

alter table INT_TARIFFMODEL
    add constraint FK_INT_TMD_SYB foreign key  (SYSTEM_BRAND)
       references INT_SYSTEM_BRAND (SYSTEM_BRAND)
/

alter table INT_TARIFFMODEL
    add constraint FK_INT_TMD_CUR foreign key  (CURRENCY)
       references INT_CURRENCY (CURRENCY)
/

alter table INT_TRUNK
    add constraint FK_INT_TRK_NOP foreign key  (NO)
       references INT_NETWORKOPERATOR (NO)
/

alter table INT_TRUNK
    add constraint FK_INT_TRK_NWM foreign key  (NETWORKMODEL)
       references INT_NETWORKMODEL (NETWORKMODEL)
/

alter table INT_TRUNK
    add constraint FK_INT_TRK_POI foreign key  (NETWORKMODEL, POI)
       references INT_POI (NETWORKMODEL, POI)
/

alter table INT_SWITCH
    add constraint FK_INT_SWI_NWM foreign key  (NETWORKMODEL)
       references INT_NETWORKMODEL (NETWORKMODEL)
/

alter table INT_SWITCH
    add constraint FK_INT_SWI_NOP foreign key  (NO)
       references INT_NETWORKOPERATOR (NO)
/

alter table INT_NOPRODUCT
    add constraint FK_INT_NPR_NOP foreign key  (NO)
       references INT_NETWORKOPERATOR (NO)
/

alter table INT_NOPRODUCT
    add constraint FK_INT_NPR_CUR foreign key  (CURRENCY)
       references INT_CURRENCY (CURRENCY)
/

alter table INT_ICPRODUCT
    add constraint FK_INT_ICP_TMD foreign key  (TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL)
/

alter table INT_ICPRODUCT
    add constraint FK_INT_ICP_NOP foreign key  (NO)
       references INT_NETWORKOPERATOR (NO)
/

alter table INT_ICPRODUCT
    add constraint FK_INT_ICP_ALTTMD foreign key  (ALT_TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL)
/

alter table INT_SUBSTARIFF_MAP
    add constraint FK_INT_STM_TMD foreign key  (INT_TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL)
/

alter table INT_CONTENT
    add constraint FK_INT_CNT_TMD foreign key  (TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL)
/

alter table INT_CONTENT
    add constraint FK_INT_CNT_CPD foreign key  (CONTENTPROVIDER)
       references INT_CONTENTPROVIDER (CONTENTPROVIDER)
/

alter table INT_CONTENT
    add constraint FK_INT_CNT_CUR foreign key  (CURRENCY)
       references INT_CURRENCY (CURRENCY)
/

alter table INT_CONTENT
    add constraint FK_INT_CNT_GLA foreign key  (GLACCOUNT)
       references INT_GLACCOUNT (GLACCOUNT)
/

alter table INT_TARIFFMODEL_VER
    add constraint FK_INT_TMV_DML foreign key  (DISCOUNTMODEL)
       references INT_DISCOUNTMODEL (DISCOUNTMODEL)
/

alter table INT_TARIFFMODEL_VER
    add constraint FK_INT_TMV_TMV foreign key  (BASIC_TARIFFMODEL, BASIC_VERSION)
       references INT_TARIFFMODEL_VER (TARIFFMODEL, VERSION)
/

alter table INT_TARIFFMODEL_VER
    add constraint FK_INT_TMV_ZMD foreign key  (ZONEMODEL)
       references INT_ZONEMODEL (ZONEMODEL)
/

alter table INT_TARIFFMODEL_VER
    add constraint FK_INT_TMV_TMD foreign key  (TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL)
/

alter table INT_NETWORKMODEL
    add constraint FK_INT_NWM_TMD foreign key  (TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL)
/

alter table INT_NETWORKMODEL
    add constraint FK_INT_NWM_SYB foreign key  (SYSTEM_BRAND)
       references INT_SYSTEM_BRAND (SYSTEM_BRAND)
/

alter table INT_POI
    add constraint FK_INT_POI_SWI foreign key  (NETWORKMODEL, SWITCH)
       references INT_SWITCH (NETWORKMODEL, SWITCH)
/

alter table INT_POI
    add constraint FK_INT_POI_NWM foreign key  (NETWORKMODEL)
       references INT_NETWORKMODEL (NETWORKMODEL)
/

alter table INT_CALLTYPE_MAP
    add constraint FK_INT_CTM_CTP foreign key  (CALLTYPE)
       references INT_CALLTYPE (CALLTYPE) on delete cascade
/

alter table INT_CALLTYPE_MAP
    add constraint FK_INT_CTM_MGR foreign key  (MAP_GROUP)
       references INT_MAP_GROUP (MAP_GROUP)
/

alter table INT_CLASSTYPEZONE_MAP
    add constraint FK_INT_CZT_NEWCTP foreign key  (NEW_CALLTYPE)
       references INT_CALLTYPE (CALLTYPE) on delete cascade
/

alter table INT_CLASSTYPEZONE_MAP
    add constraint FK_INT_CZT_WSZON foreign key  (NEW_ZONE_WS)
       references INT_ZONE (ZONE)
/

alter table INT_CLASSTYPEZONE_MAP
    add constraint FK_INT_CZT_RTZON foreign key  (NEW_ZONE_RT)
       references INT_ZONE (ZONE)
/

alter table INT_CLASSTYPEZONE_MAP
    add constraint FK_INT_CZT_ZMD foreign key  (ZONEMODEL)
       references INT_ZONEMODEL (ZONEMODEL)
/

alter table INT_CLASSTYPEZONE_MAP
    add constraint FK_INT_CZT_CMG foreign key  (CZT_GROUP)
       references INT_CZT_GROUP (CZT_GROUP)
/

alter table INT_PRICEMODEL_STEP
    add constraint FK_INT_PMS_PMD foreign key  (PRICEMODEL)
       references INT_PRICEMODEL (PRICEMODEL) on delete cascade
/

alter table INT_HOLIDAY
    add constraint FK_INT_HDY_CAL foreign key  (CALENDAR)
       references INT_CALENDAR (CALENDAR)
/

alter table INT_TARIFFMODEL_CNF
    add constraint FK_INT_TMC_SRV foreign key  (SERVICECODE)
       references INT_SERVICE (SERVICECODE)
/

alter table INT_TARIFFMODEL_CNF
    add constraint FK_INT_TMC_TMV foreign key  (TARIFFMODEL, VERSION)
       references INT_TARIFFMODEL_VER (TARIFFMODEL, VERSION)
/

alter table INT_TARIFFMODEL_CNF
    add constraint FK_INT_TMC_PMD foreign key  (PRICEMODEL)
       references INT_PRICEMODEL (PRICEMODEL)
/

alter table INT_TARIFFMODEL_CNF
    add constraint FK_INT_TMC_ZON foreign key  (ZONE)
       references INT_ZONE (ZONE)
/

alter table INT_TARIFFMODEL_CNF
    add constraint FK_INT_TMC_TIZ foreign key  (TIMEZONE)
       references INT_TIMEZONE (TIMEZONE)
/

alter table INT_TARIFFMODEL_CNF
    add constraint FK_INT_TMC_TIM foreign key  (TIMEMODEL)
       references INT_TIMEMODEL (TIMEMODEL)
/

alter table INT_TARIFFMODEL_CNF
    add constraint FK_INT_TMC_ALTPMD foreign key  (ALT_PRICEMODEL)
       references INT_PRICEMODEL (PRICEMODEL)
/

alter table INT_TARIFFMODEL_CNF
    add constraint FK_INT_TMC_GMA foreign key  (GLACCOUNT)
       references INT_GLACCOUNT (GLACCOUNT)
/

alter table INT_TARIFFMODEL_CNF
    add constraint FK_INT_TMC_RVG foreign key  (REVENUEGROUP)
       references INT_REVENUEGROUP (REVENUEGROUP)
/

alter table INT_SPECIALDAY_LNK
    add constraint FK_INT_SRL_TMV foreign key  (TARIFFMODEL, VERSION)
       references INT_TARIFFMODEL_VER (TARIFFMODEL, VERSION)
/

alter table INT_SPECIALDAY_LNK
    add constraint FK_INT_SRL_SDR foreign key  (SPECIALDAYRATE)
       references INT_SPECIALDAYRATE (SPECIALDAYRATE)
/

alter table INT_TIMEMODEL_LNK
    add constraint FK_INT_TML_TIZ foreign key  (TIMEZONE)
       references INT_TIMEZONE (TIMEZONE)
/

alter table INT_TIMEMODEL_LNK
    add constraint FK_INT_TML_DAY foreign key  (DAYCODE)
       references INT_DAYCODE (DAYCODE)
/

alter table INT_TIMEMODEL_LNK
    add constraint FK_INT_TML_TII foreign key  (INTERVAL)
       references INT_TIMEINTERVAL (INTERVAL)
/

alter table INT_TIMEMODEL_LNK
    add constraint FK_INT_TML_TIM foreign key  (TIMEMODEL)
       references INT_TIMEMODEL (TIMEMODEL)
/

alter table INT_STANDARD_ZONE
    add constraint FK_INT_STZ_SRV foreign key  (SERVICECODE)
       references INT_SERVICE (SERVICECODE)
/

alter table INT_STANDARD_ZONE
    add constraint FK_INT_STZ_ALTZMD foreign key  (ALT_ZONEMODEL)
       references INT_ZONEMODEL (ZONEMODEL)
/

alter table INT_STANDARD_ZONE
    add constraint FK_INT_STZ_ZMD foreign key  (ZONEMODEL)
       references INT_ZONEMODEL (ZONEMODEL)
/

alter table INT_STANDARD_ZONE
    add constraint FK_INT_STZ_RTZON foreign key  (ZONE_RT)
       references INT_ZONE (ZONE)
/

alter table INT_STANDARD_ZONE
    add constraint FK_INT_STZ_WSZON foreign key  (ZONE_WS)
       references INT_ZONE (ZONE)
/

alter table INT_GEOGRAPHICAL_ZONE
    add constraint FK_INT_GOZ_ZMD foreign key  (ZONEMODEL)
       references INT_ZONEMODEL (ZONEMODEL)
/

alter table INT_GEOGRAPHICAL_ZONE
    add constraint FK_INT_GOZ_SRV foreign key  (SERVICECODE)
       references INT_SERVICE (SERVICECODE)
/

alter table INT_GEOGRAPHICAL_ZONE
    add constraint FK_INT_GOZ_ALTZMD foreign key  (ALT_ZONEMODEL)
       references INT_ZONEMODEL (ZONEMODEL)
/

alter table INT_GEOGRAPHICAL_ZONE
    add constraint FK_INT_GOZ_RTZON foreign key  (ZONE_RT)
       references INT_ZONE (ZONE)
/

alter table INT_GEOGRAPHICAL_ZONE
    add constraint FK_INT_GOZ_WSZON foreign key  (ZONE_WS)
       references INT_ZONE (ZONE)
/

alter table INT_SEGZONE_LNK
    add constraint FK_INT_SZL_SGM foreign key  (SEGMENT)
       references INT_SEGMENT (SEGMENT)
/

alter table INT_SEGZONE_LNK
    add constraint FK_INT_SZL_ZMD foreign key  (ZONEMODEL)
       references INT_ZONEMODEL (ZONEMODEL) on delete cascade
/

alter table INT_POIAREA_LNK
    add constraint FK_INT_PAL_NWM foreign key  (NETWORKMODEL)
       references INT_NETWORKMODEL (NETWORKMODEL) on delete cascade
/

alter table INT_POIAREA_LNK
    add constraint FK_INT_PAL_POI foreign key  (NETWORKMODEL, POI)
       references INT_POI (NETWORKMODEL, POI)
/

alter table INT_GEOAREACODE_LNK
    add constraint FK_INT_GAL_GMD foreign key  (GEOMODEL)
       references INT_GEOGRAPHICALMODEL (GEOMODEL)
/

alter table INT_SERVICECODE_MAP
    add constraint FK_INT_SVM_MGR foreign key  (MAP_GROUP)
       references INT_MAP_GROUP (MAP_GROUP)
/

alter table INT_SERVICECODE_MAP
    add constraint FK_INT_SVM_SVC foreign key  (INT_SERVICECODE, INT_SERVICECLASS)
       references INT_SERVICECLASS (SERVICECODE, SERVICECLASS)
/

alter table INT_CALLCLASS_MAP
    add constraint FK_INT_CCM_CCL foreign key  (INT_CALLCLASS)
       references INT_CALLCLASS (CALLCLASS) on delete cascade
/

alter table INT_CALLCLASS_MAP
    add constraint FK_INT_CCM_MGR foreign key  (MAP_GROUP)
       references INT_MAP_GROUP (MAP_GROUP)
/

alter table INT_SUBS_LOCAL
    add constraint FK_INT_LOC_SUB foreign key  (CONTRACT)
       references INT_SUBS_CONTRACT (CONTRACT) on delete cascade
/

alter table INT_TARIFFDISCOUNT_LNK
    add constraint FK_INT_TDL_TMV foreign key  (TARIFFMODEL, VERSION)
       references INT_TARIFFMODEL_VER (TARIFFMODEL, VERSION)
/

alter table INT_SEGTARIFF_LNK
    add constraint FK_INT_STL_TMD foreign key  (TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL)
/

alter table INT_SEGTARIFF_LNK
    add constraint FK_INT_STL_SGM foreign key  (SEGMENT)
       references INT_SEGMENT (SEGMENT)
/

alter table INT_EDRSEQLOG
    add constraint FK_INT_ESQ_EDR foreign key  (EDR_FORMAT)
       references INT_EDRFORMAT (EDR_FORMAT)
/

alter table INT_SPLITTING_TYPE
    add constraint FK_INT_SPT_EDR foreign key  (EDR_FORMAT)
       references INT_EDRFORMAT (EDR_FORMAT)
/

alter table INT_SPLITTING_TYPE
    add constraint FK_INT_SPT_SYB foreign key  (SYSTEM_BRAND)
       references INT_SYSTEM_BRAND (SYSTEM_BRAND)
/

alter table INT_EXCHANGE_RATE
    add constraint FK_INT_XCR_FCUR foreign key  (FROM_CURRENCY)
       references INT_CURRENCY (CURRENCY)
/

alter table INT_EXCHANGE_RATE
    add constraint FK_INT_XCR_TCUR foreign key  (TO_CURRENCY)
       references INT_CURRENCY (CURRENCY)
/

alter table INT_APN_MAP
    add constraint FK_INT_APM_APG foreign key  (APN_GROUP)
       references INT_APN_GROUP (APN_GROUP)
/

alter table INT_APN_MAP
    add constraint FK_INT_APM_RTZON foreign key  (NEW_ZONE_RT)
       references INT_ZONE (ZONE)
/

alter table INT_APN_MAP
    add constraint FK_INT_APM_WSZON foreign key  (NEW_ZONE_WS)
       references INT_ZONE (ZONE)
/

alter table INT_SUBS_CLI
    add constraint FK_INT_CLI_SUB foreign key  (CONTRACT)
       references INT_SUBS_CONTRACT (CONTRACT) on delete cascade
/

alter table INT_SUBS_CLI
    add constraint FK_INT_CLI_SSM foreign key  (SERVICECODE)
       references INT_SUBSSERVICE_MAP (SUBS_SERVICECODE)
/

alter table INT_SUBS_CONTRACT_HIST
    add constraint FK_INT_SCH_SGM foreign key  (SEGMENT)
       references INT_SEGMENT (SEGMENT)
/

alter table INT_SUBS_CONTRACT_HIST
    add constraint FK_INT_SCH_SUB foreign key  (CONTRACT)
       references INT_SUBS_CONTRACT (CONTRACT) on delete cascade
/

alter table INT_SUBS_CONTRACT_HIST
    add constraint FK_INT_SCH_STM foreign key  (TARIFFMODEL)
       references INT_SUBSTARIFF_MAP (SUBS_TARIFFMODEL)
/

alter table INT_SUBS_CONTRACT_HIST
    add constraint FK_INT_SCH_SBC foreign key  (BILLCYCLE)
       references INT_SUBS_BILLCYCLE (BILLCYCLE)
/

alter table INT_SUBS_CONTRACT_HIST
    add constraint FK_INT_SCH_SDM foreign key  (DISCOUNTMODEL)
       references INT_SUBSDISCOUNT_MAP (SUBS_DISCOUNTMODEL)
/

alter table INT_DISCOUNTMDL_CNF
    add constraint FK_INT_DMC_DCR foreign key  (DISCOUNTRULE)
       references INT_DISCOUNTRULE (DISCOUNTRULE)
/

alter table INT_DISCOUNTMDL_CNF
    add constraint FK_INT_DMC_DTR foreign key  (DISCOUNTTRIGGER)
       references INT_DISCOUNTTRIGGER (DISCOUNTTRIGGER)
/

alter table INT_DISCOUNTMDL_CNF
    add constraint FK_INT_DMC_DMV foreign key  (DISCOUNTMODEL, VERSION)
       references INT_DISCOUNTMDL_VER (DISCOUNTMODEL, VERSION) on delete cascade
/

alter table INT_DISCOUNTSTEP
    add constraint FK_INT_DCS_DCM foreign key  (DISCOUNTMASTER)
       references INT_DISCOUNTMASTER (DISCOUNTMASTER)
/

alter table INT_DISCOUNTSTEP
    add constraint FK_INT_DCS_DCR foreign key  (DISCOUNTRULE)
       references INT_DISCOUNTRULE (DISCOUNTRULE) on delete cascade
/

alter table INT_DISCOUNTSTEP
    add constraint FK_INT_DCS_UOM foreign key  (GRANT_UOM)
       references INT_UOM (UOM)
/

alter table INT_DISCOUNTDETAIL
    add constraint FK_INT_DCD_DCM foreign key  (DISCOUNTMASTER)
       references INT_DISCOUNTMASTER (DISCOUNTMASTER) on delete cascade
/

alter table INT_SUBS_BILLRUN
    add constraint FK_INT_SBR_SBC foreign key  (BILLCYCLE)
       references INT_SUBS_BILLCYCLE (BILLCYCLE)
/

alter table INT_NOSP
    add constraint FK_INT_NSP_MGR foreign key  (MAP_GROUP)
       references INT_MAP_GROUP (MAP_GROUP)
/

alter table INT_ICPRODUCT_CNF
    add constraint FK_INT_IPC_ICP foreign key  (ICPRODUCT)
       references INT_ICPRODUCT (ICPRODUCT)
/

alter table INT_ICPRODUCT_CNF
    add constraint FK_INT_IPC_NWM foreign key  (NETWORKMODEL)
       references INT_NETWORKMODEL (NETWORKMODEL)
/

alter table INT_ICPRODUCT_CNF
    add constraint FK_INT_IPC_IPG foreign key  (NETWORKMODEL, ICPRODUCT_GROUP)
       references INT_ICPRODUCT_GROUP (NETWORKMODEL, ICPRODUCT_GROUP)
/

alter table INT_NOPRODUCT_CNF
    add constraint FK_INT_NPR_ICP foreign key  (ICPRODUCT)
       references INT_ICPRODUCT (ICPRODUCT)
/

alter table INT_NOPRODUCT_CNF
    add constraint FK_INT_NPR_TIZ foreign key  (TIMEZONE)
       references INT_TIMEZONE (TIMEZONE)
/

alter table INT_NOPRODUCT_CNF
    add constraint FK_INT_NPR_ZON foreign key  (ZONE)
       references INT_ZONE (ZONE)
/

alter table INT_NOPRODUCT_CNF
    add constraint FK_INT_NPC_NPR foreign key  (NO, PRODUCTCODE)
       references INT_NOPRODUCT (NO, PRODUCTCODE)
/

alter table INT_DISCOUNTCONDITION
    add constraint FK_INT_DCN_DCM foreign key  (DISCOUNTMASTER)
       references INT_DISCOUNTMASTER (DISCOUNTMASTER)
/

alter table INT_DISCOUNTCONDITION
    add constraint FK_INT_DCN_DTR foreign key  (DISCOUNTTRIGGER)
       references INT_DISCOUNTTRIGGER (DISCOUNTTRIGGER) on delete cascade
/

alter table INT_DISCARDING
    add constraint FK_INT_DIC_EDR foreign key  (EDR_FORMAT)
       references INT_EDRFORMAT (EDR_FORMAT)
/

alter table INT_NO_BILLRUN
    add constraint FK_INT_NBR_NOP foreign key  (NO)
       references INT_NETWORKOPERATOR (NO)
/

alter table INT_TARIFFSERVICECLASS
    add constraint FK_INT_TSC_TMD foreign key  (TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL)
/

alter table INT_TARIFFSERVICECLASS
    add constraint FK_INT_TSC_SVC foreign key  (NEW_SERVICECODE, NEW_SERVICECLASS)
       references INT_SERVICECLASS (SERVICECODE, SERVICECLASS)
/

alter table INT_TARIFFSERVICECLASS
    add constraint FK_INT_TSC_TMG foreign key  (TSC_GROUP)
       references INT_TSC_GROUP (TSC_GROUP)
/

alter table INT_TAX
    add constraint FK_INT_TAX_TXG foreign key  (TAXGROUP)
       references INT_TAXGROUP (TAXGROUP)
/

alter table INT_TAX
    add constraint FK_INT_TAX_TXC foreign key  (TAXCODE)
       references INT_TAXCODE (TAXCODE)
/

alter table INT_CONTENT_MAP
    add constraint FK_INT_CNM_CNT foreign key  (CONTENTPROVIDER, CONTENTCODE)
       references INT_CONTENT (CONTENTPROVIDER, CONTENTCODE) on delete cascade
/

alter table INT_CONTENT_MAP
    add constraint FK_INT_CNM_EDR foreign key  (EDR_FORMAT)
       references INT_EDRFORMAT (EDR_FORMAT)
/

alter table AGG_AGGREGATION
    add constraint FK_AGG_AGG_SOL_COLS foreign key  (COL_OBJ_ID)
       references SOL_COLS (OBJ_ID)
/

alter table AGG_AGGREGATION
    add constraint FK_AGG_AGG_AGG_SCN foreign key  (SCENARIO_ID)
       references AGG_SCENARIO (SCENARIO_ID) on delete cascade
/

alter table AGG_CONDITION
    add constraint FK_AGG_CONDITION_SOL_COLS foreign key  (COL_OBJ_ID)
       references SOL_COLS (OBJ_ID)
/

alter table AGG_CONDITION
    add constraint FK_AGG_CONDITION_AGG_SCENARIO foreign key  (SCENARIO_ID)
       references AGG_SCENARIO (SCENARIO_ID) on delete cascade
/

alter table SOL_CONST_COLS
    add constraint FK_SC_SCC_CHILD foreign key  (CHILD_COL_ID)
       references SOL_COLS (OBJ_ID) on delete cascade
/

alter table SOL_CONST_COLS
    add constraint FK_SC_SCC_PARENT foreign key  (PARENT_COL_ID)
       references SOL_COLS (OBJ_ID) on delete cascade
/

alter table SOL_CONST_COLS
    add constraint FK_SOL_CONST_COL_SOL_CONSTRAIN foreign key  (CONSTRAINT_ID)
       references SOL_CONSTRAINTS (CONSTRAINT_ID) on delete cascade
/

alter table AGG_REFERENCESET_CNF
    add constraint FK_AGG_REFSET_CNF_AGG_REFSET foreign key  (REFERENCESET_ID)
       references AGG_REFERENCESET (REFERENCESET_ID) on delete cascade
/

alter table AGG_REFERENCESET_CNF
    add constraint FK_AGG_REFSETCNF_SOL_COLS foreign key  (COL_OBJ_ID)
       references SOL_COLS (OBJ_ID)
/

alter table AGG_EDRFORMAT_SCN
    add constraint FK_AGG_EDRF_SCN_AGG_SCENARIO foreign key  (SCENARIO_ID)
       references AGG_SCENARIO (SCENARIO_ID)
/

alter table AGG_EDRFORMAT_SCN
    add constraint FK_AGG_EDRF_SCN_AGG_EDRF_AGG foreign key  (FORMAT_ID)
       references AGG_EDRFORMAT (FORMAT_ID)
/

alter table AGG_DICTIONARY
    add constraint FK_AGG_DICTIONAR_AGG_QUEUE foreign key  (IMPORT_TABLE)
       references AGG_QUEUE (IMPORT_TABLE)
/

alter table INT_ICNO_LNK
    add constraint FK_INT_INL_ICP foreign key  (ICPRODUCT)
       references INT_ICPRODUCT (ICPRODUCT)
/

alter table INT_ICNO_LNK
    add constraint FK_INT_INL_NOP foreign key  (NO)
       references INT_NETWORKOPERATOR (NO)
/

alter table INT_ICNO_LNK
    add constraint FK_INT_INL_TMD foreign key  (TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL)
/

alter table INT_UOM_MAP
    add constraint FK_INT_UMM_FUOM foreign key  (FROM_UOM)
       references INT_UOM (UOM)
/

alter table INT_UOM_MAP
    add constraint FK_INT_UMM_TUOM foreign key  (TO_UOM)
       references INT_UOM (UOM)
/

alter table INT_SUBS_REFERENCE_HIST
    add constraint FK_INT_SRH_SUB foreign key  (CONTRACT)
       references INT_SUBS_CONTRACT (CONTRACT)
/

alter table INT_TRUNK_CNF
    add constraint FK_INT_TRC_TRK foreign key  (NETWORKMODEL, TRUNK)
       references INT_TRUNK (NETWORKMODEL, TRUNK)
/

alter table INT_TRUNK_CNF
    add constraint FK_INT_TRC_IPG foreign key  (NETWORKMODEL, ICPRODUCT_GROUP)
       references INT_ICPRODUCT_GROUP (NETWORKMODEL, ICPRODUCT_GROUP)
/

commit
/
