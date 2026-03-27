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
--   Update script from DB version v4-01-00 to v4-03-00.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-01-00_v4-03-00.sql,v $
-- $Revision: 1.4 $
-- $Author: pengelbr $
-- $Date: 2000/07/28 12:25:18 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-01-00_v4-03-00.sql,v $
-- Revision 1.4  2000/07/28 12:25:18  pengelbr
-- Add ';' to each command if missing (PR 2263).
--
-- Revision 1.3  2000/07/25 12:49:02  pengelbr
-- Fixed PRs 2264, 2265.
--
-- Revision 1.2  2000/07/20 14:01:06  pengelbr
-- Added prepare script. Modified responsible for update scripts.
--
-- Revision 1.1  2000/06/26 15:24:38  pengelbr
-- Added update database scripts.
--
--------------------------------------------------------------------------------

create table INT_RESELLER_LNK
(
    EDR_FORMAT            VARCHAR2(10)           not null,
    ROAMING_TYPE          CHAR(1)                not null
        constraint CKC_ROAMING__INT_RESELLER_LNK check (ROAMING_TYPE in ('S','B','C','O')),
    RANK                  NUMBER(9)              not null,
    VALID_FROM            DATE                   not null,
    VALID_TO              DATE                   null    ,
    RECORDTYPE            VARCHAR2(255)          default '*' not null,
    SERVICECODE           VARCHAR2(255)          default '*' not null,
    CALLCLASS             VARCHAR2(255)          default '*' not null,
    SOURCE_NETWORK        VARCHAR2(255)          default '*' not null,
    DESTIN_NETWORK        VARCHAR2(255)          default '*' not null,
    ORIGIN_AREACODE       VARCHAR2(255)          default '*' not null,
    DESTIN_AREACODE       VARCHAR2(255)          default '*' not null,
    TRANSIT_AREACODE      VARCHAR2(255)          default '*' not null,
    TARIFFMODEL           NUMBER(9)              not null,
    SEGMENT               VARCHAR2(5)            null    ,
    NAME                  VARCHAR2(30)           null    ,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_RESELLER_LNK check (MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
    constraint PK_INT_RML primary key (EDR_FORMAT, ROAMING_TYPE, RANK, VALID_FROM)
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

create public synonym INT_RESELLER_LNK for INT_RESELLER_LNK;

grant select, insert, update, delete on INT_RESELLER_LNK to ROLE_INTEGRATE_ALL;

grant select on INT_RESELLER_LNK to ROLE_INTEGRATE_SEL;

comment on table INT_RESELLER_LNK is 'defines the link to a tariffmodel for reseller (e.g. roaming) rating';

comment on column INT_RESELLER_LNK.EDR_FORMAT is 'references the edr format this mapping is related to';

comment on column INT_RESELLER_LNK.ROAMING_TYPE is 'ROAMING_TYPE';

comment on column INT_RESELLER_LNK.RANK is 'unique sequence order in which the mapping should be evaluated';

comment on column INT_RESELLER_LNK.VALID_FROM is 'date from when on the mapping is valid';

comment on column INT_RESELLER_LNK.VALID_TO is 'date til when the mapping is valid';

comment on column INT_RESELLER_LNK.RECORDTYPE is 'the record type for which a tariffmodel should be defined (logical expression)';

comment on column INT_RESELLER_LNK.SERVICECODE is 'the service code for which a tariffmodel should be defined (logical expression)';

comment on column INT_RESELLER_LNK.CALLCLASS is 'the call class for which a tariffmodel should be defined (logical expression)';

comment on column INT_RESELLER_LNK.SOURCE_NETWORK is 'the source network (VPLMN) for which a tariffmodel should be defined (logical expression)';

comment on column INT_RESELLER_LNK.DESTIN_NETWORK is 'the destination network (HPLMN) for which a tariffmodel should be defined (logical expression)';

comment on column INT_RESELLER_LNK.ORIGIN_AREACODE is 'the a-number for which a tariffmodel should be defined (logical expression)';

comment on column INT_RESELLER_LNK.DESTIN_AREACODE is 'the b-number for which a tariffmodel should be defined (logical expression)';

comment on column INT_RESELLER_LNK.TRANSIT_AREACODE is 'the c-number for which a tariffmodel should be defined (logical expression)';

comment on column INT_RESELLER_LNK.TARIFFMODEL is 'the tariffmodel which should be used for this entry (roaming rating)';

comment on column INT_RESELLER_LNK.SEGMENT is 'segment id (used as a reference for segment zoning and segment pricing)';

comment on column INT_RESELLER_LNK.NAME is 'name or description';

comment on column INT_RESELLER_LNK.ENTRYBY is 'ENTRYBY';

comment on column INT_RESELLER_LNK.ENTRYDATE is 'ENTRYDATE';

comment on column INT_RESELLER_LNK.MODIFBY is 'MODIFBY';

comment on column INT_RESELLER_LNK.MODIFDATE is 'MODIFDATE';

comment on column INT_RESELLER_LNK.MODIFIED is 'MODIFIED';

comment on column INT_RESELLER_LNK.RECVER is 'RECVER';


alter table INT_SERVICE drop constraint CKC_CHARGE_I_INT_SERVICE;

alter table INT_SERVICE add constraint CKC_CHARGE_I_INT_SERVICE check (CHARGE_ITEM in ('D','E','V','S','R','T','A','B'));

alter table INT_ICPRODUCT drop constraint CKC_ZONE_DIR_INT_ICPRODUCT;

alter table INT_ICPRODUCT add constraint CKC_ZONE_DIR_INT_ICPRODUCT check (ZONE_DIRECTION in ('I','O','T','N','S'));

alter table INT_NETWORKOPERATOR
    modify PLMN_ID NUMBER(7);

alter table INT_PRICEMODEL_STEP
    drop primary key;

alter table INT_PRICEMODEL_STEP
    add     VALID_FROM            DATE                   default sysdate not null;

alter table INT_PRICEMODEL_STEP
    add constraint PK_INT_PMS primary key (PRICEMODEL, VALID_FROM, CHARGE_ITEM, STEP)
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
     );

alter table INT_TARIFFDISCOUNT_LNK
    add     SOURCE_NETWORK        VARCHAR2(255)          default '*' not null;

alter table INT_TARIFFDISCOUNT_LNK
    add     DESTIN_NETWORK        VARCHAR2(255)          default '*' not null;

alter table INT_DISCOUNTDETAIL
    modify ZONEMODEL not null;

alter table INT_DISCOUNTDETAIL
    modify ZONEMODEL default '*';

alter table INT_DISCOUNTDETAIL
    modify ZONE not null;

alter table INT_DISCOUNTDETAIL
    modify ZONE default '*';

alter table INT_DISCOUNTDETAIL
    modify SERVICECODE not null;

alter table INT_DISCOUNTDETAIL
    modify SERVICECODE default '*';

alter table INT_DISCOUNTDETAIL
    modify SERVICECLASS not null;

alter table INT_DISCOUNTDETAIL
    modify SERVICECLASS default '*';

alter table INT_DISCOUNTDETAIL
    modify TIMEMODEL not null;

alter table INT_DISCOUNTDETAIL
    modify TIMEMODEL default '*';

alter table INT_DISCOUNTDETAIL
    modify TIMEZONE not null;

alter table INT_DISCOUNTDETAIL
    modify TIMEZONE default '*';

alter table INT_DISCOUNTDETAIL
    modify PRICEMODEL not null;

alter table INT_DISCOUNTDETAIL
    modify PRICEMODEL default '*';

alter table INT_DISCOUNTDETAIL
    modify RECORDTYPE not null;

alter table INT_DISCOUNTDETAIL
    modify RECORDTYPE default '*';

alter table INT_TARIFFSERVICECLASS
    modify CALLCLASS not null;

alter table INT_TARIFFSERVICECLASS
    modify CALLCLASS default '*';

alter table INT_TARIFFSERVICECLASS
    modify CALLTYPE not null;

alter table INT_TARIFFSERVICECLASS
    modify CALLTYPE default '*';

alter table INT_TARIFFSERVICECLASS
    modify SERVICECODE not null;

alter table INT_TARIFFSERVICECLASS
    modify SERVICECODE default '*';

alter table INT_TARIFFSERVICECLASS
    modify ZONE not null;

alter table INT_TARIFFSERVICECLASS
    modify ZONE default '*';

alter table INT_DISCARDING
    add constraint FK_INT_DIC_EDR foreign key  (EDR_FORMAT)
       references INT_EDRFORMAT (EDR_FORMAT);

-- alter table INT_NOPRODUCT
--   modify TAXCODE NULL;

alter table INT_CALLCLASS_MAP
  ADD (
    CONNECTTYPE VARCHAR2(255) default '*' not null,
    CONNECTSUBTYPE VARCHAR2(255) default '*' not null
  );

comment on column INT_CALLCLASS_MAP.CONNECTTYPE is 'external connect type (used within the edr format) that should be mapped';

comment on column INT_CALLCLASS_MAP.CONNECTSUBTYPE is 'external connect subtype type (used within the edr format) that should be mapped';

insert into int_dbversion
( dbversion, description, username, install_date )
values
( 'v4-03-00', 'integRate', user, sysdate );
 
commit;
