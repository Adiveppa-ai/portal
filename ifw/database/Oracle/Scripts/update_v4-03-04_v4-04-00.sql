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
--   Update script from DB version v4-03-04 to v4-04-00.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-03-04_v4-04-00.sql,v $
-- $Revision: 1.3 $
-- $Author: pengelbr $
-- $Date: 2000/07/28 12:25:18 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-03-04_v4-04-00.sql,v $
-- Revision 1.3  2000/07/28 12:25:18  pengelbr
-- Add ';' to each command if missing (PR 2263).
--
-- Revision 1.2  2000/07/20 14:01:06  pengelbr
-- Added prepare script. Modified responsible for update scripts.
--
-- Revision 1.1  2000/06/26 15:37:02  pengelbr
-- Apply updates.
--
-- Revision 1.1  2000/06/26 15:24:38  pengelbr
-- Added update database scripts.
--
--------------------------------------------------------------------------------

-- ============================================================
--   Table: IC_DAILY                                           
-- ============================================================
alter table IC_DAILY drop constraint PK_ICD;

drop public synonym IC_DAILY;

rename IC_DAILY to IC_DAILY_BACKUP;

create table IC_DAILY
(
    NETWORK_OPERATOR      VARCHAR2(10)           not null,
    DAY                   DATE                   not null,
    SEQUENCE_NUMBER       NUMBER(9)              default 0 not null,
    BILLRUN               VARCHAR2(10)           not null,
    TRUNK                 VARCHAR2(15)           not null,
    ICPRODUCT             VARCHAR2(10)           not null,
    BILLING_DIRECTION     CHAR(1)                not null
        constraint CKC_BILLING__IC_DAILY check (BILLING_DIRECTION in ('I','O')),
    ZONE                  VARCHAR2(5)            not null,
    TIMEZONE              VARCHAR2(10)           not null,
    NUM_ITEMS             NUMBER(9)              default 0 not null,
    DURATION              NUMBER                 default 0 not null,
    ROUNDED_DURATION      NUMBER                 default 0 not null,
    VOLUME_SENT           NUMBER                 default 0 not null,
    VOLUME_RECEIVED       NUMBER                 default 0 not null,
    CHARGE_AMOUNT         NUMBER                 default 0 not null,
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
);

create public synonym IC_DAILY for IC_DAILY;

grant select, insert, update, delete on IC_DAILY to INTEGRATE_ROLE_ALL;

grant select on IC_DAILY to INTEGRATE_ROLE_SEL;

comment on table IC_DAILY is 'tariffIC result table for the default online interconnection billing';

comment on column IC_DAILY.NETWORK_OPERATOR is 'related network operator to whom the ic-bill belongs';

comment on column IC_DAILY.DAY is 'day for which the ic-bill should be aggregated';

comment on column IC_DAILY.SEQUENCE_NUMBER is 'optional stream/file sequence number of the aggregated ic-bill part';

comment on column IC_DAILY.BILLRUN is 'defines the bill run periode for the ic-bill, format ''BCYYYYMMxx''; -1 for open periode';

comment on column IC_DAILY.TRUNK is 'trunk-id on which the ic-bill should be aggregated';

comment on column IC_DAILY.ICPRODUCT is 'internal ic-product code on which the ic-bill should be aggregated';

comment on column IC_DAILY.BILLING_DIRECTION is 'bill direction code on which the ic-bill should be aggregated (I=Incomming, O=Outgoing)';

comment on column IC_DAILY.ZONE is 'zone value on which the ic-bill should be aggregated ';

comment on column IC_DAILY.TIMEZONE is 'timezone code on which the ic-bill should be aggregated ';

comment on column IC_DAILY.NUM_ITEMS is 'aggregation result: count of all single edrs';

comment on column IC_DAILY.DURATION is 'aggregation result: sum original duration';

comment on column IC_DAILY.ROUNDED_DURATION is 'aggregation result: sum rounded duration according to price model beats';

comment on column IC_DAILY.VOLUME_SENT is 'aggregation result: sum of total volume sent';

comment on column IC_DAILY.VOLUME_RECEIVED is 'aggregation result: sum of total volume received';

comment on column IC_DAILY.CHARGE_AMOUNT is 'aggregation result: sum of total charge amount to be billed';


-- ============================================================
--   Table: IC_DAILY_ALTERNATE                                 
-- ============================================================
alter table IC_DAILY_ALTERNATE drop constraint PK_IDA;

drop public synonym IC_DAILY_ALTERNATE;

rename IC_DAILY_ALTERNATE to IC_DAILY_ALTERNATE_BACKUP;

create table IC_DAILY_ALTERNATE
(
    NETWORK_OPERATOR      VARCHAR2(10)           not null,
    DAY                   DATE                   default sysdate not null,
    SEQUENCE_NUMBER       NUMBER(9)              default 0 not null,
    BILLRUN               VARCHAR2(10)           default '-1' not null,
    TRUNK                 VARCHAR2(15)           not null,
    ICPRODUCT             VARCHAR2(10)           not null,
    BILLING_DIRECTION     CHAR(1)                not null
        constraint CKC_BILLING__IC_DAILY_ALTERNAT check (BILLING_DIRECTION in ('I','O')),
    ZONE                  VARCHAR2(5)            not null,
    TIMEZONE              VARCHAR2(10)           not null,
    NUM_ITEMS             NUMBER(9)              default 0 null    ,
    DURATION              NUMBER                 default 0 not null,
    ROUNDED_DURATION      NUMBER                 default 0 not null,
    VOLUME_SENT           NUMBER                 default 0 not null,
    VOLUME_RECEIVED       NUMBER                 default 0 not null,
    CHARGE_AMOUNT         NUMBER                 default 0 not null,
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
);

create public synonym IC_DAILY_ALTERNATE for IC_DAILY_ALTERNATE;

grant select, insert, update, delete on IC_DAILY_ALTERNATE to INTEGRATE_ROLE_ALL;

grant select on IC_DAILY_ALTERNATE to INTEGRATE_ROLE_SEL;

comment on table IC_DAILY_ALTERNATE is 'tariffIC result table for the alternate online interconnection billing';

comment on column IC_DAILY_ALTERNATE.NETWORK_OPERATOR is 'related network operator to whom the ic-bill belongs';

comment on column IC_DAILY_ALTERNATE.DAY is 'day for which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.SEQUENCE_NUMBER is 'optional stream/file sequence number of the aggregated ic-bill part';

comment on column IC_DAILY_ALTERNATE.BILLRUN is 'defines the bill run periode for the ic-bill, format ''BCYYYYMMxx''; -1 for open periode';

comment on column IC_DAILY_ALTERNATE.TRUNK is 'trunk-id on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.ICPRODUCT is 'internal ic-product code on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.BILLING_DIRECTION is 'bill direction code on which the ic-bill should be aggregated (I=Incomming, O=Outgoing)';

comment on column IC_DAILY_ALTERNATE.ZONE is 'zone value on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.TIMEZONE is 'timezone code on which the ic-bill should be aggregated';

comment on column IC_DAILY_ALTERNATE.NUM_ITEMS is 'aggregation result: count of all single edrs';

comment on column IC_DAILY_ALTERNATE.DURATION is 'aggregation result: sum original duration';

comment on column IC_DAILY_ALTERNATE.ROUNDED_DURATION is 'aggregation result: sum rounded duration according to price model beats';

comment on column IC_DAILY_ALTERNATE.VOLUME_SENT is 'aggregation result: sum of total volume sent';

comment on column IC_DAILY_ALTERNATE.VOLUME_RECEIVED is 'aggregation result: sum of total volume received';

comment on column IC_DAILY_ALTERNATE.CHARGE_AMOUNT is 'aggregation result: sum of total charge amount to be billed';

insert into int_dbversion
( dbversion, description, username, install_date )
values
( 'v4-04-00', 'integRate/tariffIC', user, sysdate );
 
commit;
