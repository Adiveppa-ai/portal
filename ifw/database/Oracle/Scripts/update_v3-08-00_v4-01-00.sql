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
--   Update script from DB version v3-08-00 to v4-01-00.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v3-08-00_v4-01-00.sql,v $
-- $Revision: 1.4 $
-- $Author: pengelbr $
-- $Date: 2000/07/28 12:25:17 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v3-08-00_v4-01-00.sql,v $
-- Revision 1.4  2000/07/28 12:25:17  pengelbr
-- Add ';' to each command if missing (PR 2263).
--
-- Revision 1.3  2000/07/25 12:48:46  pengelbr
-- Fixed PRs 2254, 2255, 2261.
--
-- Revision 1.2  2000/07/20 14:01:06  pengelbr
-- Added prepare script. Modified responsible for update scripts.
--
-- Revision 1.1  2000/06/26 15:24:38  pengelbr
-- Added update database scripts.
--
--------------------------------------------------------------------------------

-- ============================================================
--    CREATE Tables
-- ============================================================

-- ============================================================
--   Table: INT_CONTENT                                        
-- ============================================================
create table INT_CONTENT
(
    CONTENTPROVIDER       NUMBER(9)              not null,
    CONTENTCODE           VARCHAR2(8)            not null,
    VALID_FROM            DATE                   not null,
    VALID_TO              DATE                   null    ,
    NAME                  VARCHAR2(30)           null    ,
    TARIFFMODEL           NUMBER(9)              not null,
    SHARRING              NUMBER(4)              default 0 not null,
    CURRENCY              VARCHAR2(3)            default 'DEM' not null,
    TAXCODE               VARCHAR2(10)           not null,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CONTENT check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
    constraint PK_INT_CNT primary key (CONTENTPROVIDER, CONTENTCODE)
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

create public synonym INT_CONTENT for INT_CONTENT;

grant select, insert, update, delete on INT_CONTENT to INTEGRATE_ROLE_ALL;

grant select on INT_CONTENT to INTEGRATE_ROLE_SEL;

comment on table INT_CONTENT is 'content table, defines content codes (e.g. premium rate, shared coast, freephone, etc.) for content-provider rating';

comment on column INT_CONTENT.CONTENTPROVIDER is 'reference to a related content provider associated to this special number';

comment on column INT_CONTENT.CONTENTCODE is 'content product code (e.g. a value added service or a';

comment on column INT_CONTENT.VALID_FROM is 'date from when on this content should be evaluated';

comment on column INT_CONTENT.VALID_TO is 'date till when the content is active';

comment on column INT_CONTENT.NAME is 'name or description';

comment on column INT_CONTENT.TARIFFMODEL is 'reference to the tariff model which should be used';

comment on column INT_CONTENT.SHARRING is 'defines a possible sharring rate for this content product (e.g. 1200 for 12,00%)';

comment on column INT_CONTENT.CURRENCY is 'overwrites the default content provider currency for this specific product; if empty the no currency is valid';

comment on column INT_CONTENT.TAXCODE is 'tax code which applies to this poduct';

comment on column INT_CONTENT.ENTRYBY is 'ENTRYBY';

comment on column INT_CONTENT.ENTRYDATE is 'ENTRYDATE';

comment on column INT_CONTENT.MODIFBY is 'MODIFBY';

comment on column INT_CONTENT.MODIFDATE is 'MODIFDATE';

comment on column INT_CONTENT.MODIFIED is 'MODIFIED';

comment on column INT_CONTENT.RECVER is 'RECVER';


-- ============================================================
--   Index: FK_INT_CNT_CPD                                     
-- ============================================================
create index FK_INT_CNT_CPD on INT_CONTENT (CONTENTPROVIDER asc)
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
);


-- ============================================================
--   Table: INT_CONTENT_MAP                                    
-- ============================================================
create table INT_CONTENT_MAP
(
    EDR_FORMAT            VARCHAR2(10)           not null,
    RANK                  NUMBER(9)              not null,
    B_NUMBER              VARCHAR2(255)          default '*' not null,
    C_NUMBER              VARCHAR2(255)          default '*' not null,
    CALLCLASS             VARCHAR2(255)          default '*' not null,
    SERVICECODE           VARCHAR2(255)          default '*' not null,
    APPLICATION           VARCHAR2(255)          default '*' not null,
    CONTENTPROVIDER       NUMBER(9)              null    ,
    CONTENTCODE           VARCHAR2(8)            null    ,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_CONTENT_MAP check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
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
);

create public synonym INT_CONTENT_MAP for INT_CONTENT_MAP;

grant select, insert, update, delete on INT_CONTENT_MAP to INTEGRATE_ROLE_ALL;

grant select on INT_CONTENT_MAP to INTEGRATE_ROLE_SEL;


comment on table INT_CONTENT_MAP is 'defines possible content mapping rules';

comment on column INT_CONTENT_MAP.EDR_FORMAT is 'references the related edr format for which this mapping should be applied';

comment on column INT_CONTENT_MAP.RANK is 'unique sequence order in which the mapping should be performed';

comment on column INT_CONTENT_MAP.B_NUMBER is 'B_NUMBER';

comment on column INT_CONTENT_MAP.C_NUMBER is 'C_NUMBER';

comment on column INT_CONTENT_MAP.CALLCLASS is 'CALLCLASS';

comment on column INT_CONTENT_MAP.SERVICECODE is 'SERVICECODE';

comment on column INT_CONTENT_MAP.APPLICATION is 'APPLICATION';

comment on column INT_CONTENT_MAP.CONTENTPROVIDER is 'references the related content provider to which the mapping belongs';

comment on column INT_CONTENT_MAP.CONTENTCODE is 'references the related content code to which the mapping should apply';

comment on column INT_CONTENT_MAP.ENTRYBY is 'ENTRYBY';

comment on column INT_CONTENT_MAP.ENTRYDATE is 'ENTRYDATE';

comment on column INT_CONTENT_MAP.MODIFBY is 'MODIFBY';

comment on column INT_CONTENT_MAP.MODIFDATE is 'MODIFDATE';

comment on column INT_CONTENT_MAP.MODIFIED is 'MODIFIED';

comment on column INT_CONTENT_MAP.RECVER is 'RECVER';


-- ============================================================
--   Table: INT_EXCHANGE_RATE                                  
-- ============================================================
drop public synonym INT_EXCHANGE_RATE;

alter table INT_EXCHANGE_RATE drop primary key;

rename INT_EXCHANGE_RATE to BACKUP_INT_EXCHANGE_RATE;

create table INT_EXCHANGE_RATE
(
    FROM_CURRENCY         VARCHAR2(3)            default 'DEM' not null,
    VALID_FROM            DATE                   not null,
    TO_CURRENCY           VARCHAR2(3)            default 'DEM' not null,
    EXCHANGE_RATE         NUMBER                 not null,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_EXCHANGE_RATE check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
    constraint PK_INT_XCR primary key (FROM_CURRENCY, VALID_FROM, TO_CURRENCY)
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
buffer_pool keep
)
tablespace INTEGRATE_TS_1_DAT;

create public synonym INT_EXCHANGE_RATE for INT_EXCHANGE_RATE;

grant select, insert, update, delete on INT_EXCHANGE_RATE to INTEGRATE_ROLE_ALL;

grant select on INT_EXCHANGE_RATE to INTEGRATE_ROLE_SEL;


comment on table INT_EXCHANGE_RATE is 'defines the exchange rates for given currencies';

comment on column INT_EXCHANGE_RATE.FROM_CURRENCY is 'specifies the origin currency an exchange rate should apply to';

comment on column INT_EXCHANGE_RATE.VALID_FROM is 'date from when on the exchange rate is valid';

comment on column INT_EXCHANGE_RATE.TO_CURRENCY is 'specifies the destination currency the exchange is valid for';

comment on column INT_EXCHANGE_RATE.EXCHANGE_RATE is 'the exchange rate amount';

comment on column INT_EXCHANGE_RATE.ENTRYBY is 'ENTRYBY';

comment on column INT_EXCHANGE_RATE.ENTRYDATE is 'ENTRYDATE';

comment on column INT_EXCHANGE_RATE.MODIFBY is 'MODIFBY';

comment on column INT_EXCHANGE_RATE.MODIFDATE is 'MODIFDATE';

comment on column INT_EXCHANGE_RATE.MODIFIED is 'MODIFIED';

comment on column INT_EXCHANGE_RATE.RECVER is 'RECVER';


-- ============================================================
--   Table: INT_ISCRIPT                                        
-- ============================================================
create table INT_ISCRIPT
(
    SCRIPTCODE            VARCHAR2(10)           not null,
    NAME                  VARCHAR2(30)           null    ,
    SCRIPT                LONG VARCHAR           null    ,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_ISCRIPT check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
    constraint PK_INT_ISC primary key (SCRIPTCODE)
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
pctfree 30
pctused 50
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

create public synonym INT_ISCRIPT for INT_ISCRIPT;

grant select, insert, update, delete on INT_ISCRIPT to INTEGRATE_ROLE_ALL;

grant select on INT_ISCRIPT to INTEGRATE_ROLE_SEL;

comment on table INT_ISCRIPT is 'table to define programming sequences';

comment on column INT_ISCRIPT.SCRIPTCODE is 'unique script code identifier';

comment on column INT_ISCRIPT.NAME is 'name or description';

comment on column INT_ISCRIPT.SCRIPT is 'contains the script programming language itself';

comment on column INT_ISCRIPT.ENTRYBY is 'ENTRYBY';

comment on column INT_ISCRIPT.ENTRYDATE is 'ENTRYDATE';

comment on column INT_ISCRIPT.MODIFBY is 'MODIFBY';

comment on column INT_ISCRIPT.MODIFDATE is 'MODIFDATE';

comment on column INT_ISCRIPT.MODIFIED is 'MODIFIED';

comment on column INT_ISCRIPT.RECVER is 'RECVER';


-- ============================================================
--   Table: INT_RULESET                                        
-- ============================================================
create table INT_RULESET
(
    RULESET               VARCHAR2(10)           not null,
    NAME                  VARCHAR2(30)           null    ,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_RULESET check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
    constraint PK_INT_RUS primary key (RULESET)
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

create public synonym INT_RULESET for INT_RULESET;

grant select, insert, update, delete on INT_RULESET to INTEGRATE_ROLE_ALL;

grant select on INT_RULESET to INTEGRATE_ROLE_SEL;

comment on table INT_RULESET is 'defines a ruleset, which groups different rules';

comment on column INT_RULESET.RULESET is 'internal unique ruleset code';

comment on column INT_RULESET.NAME is 'name or description';

comment on column INT_RULESET.ENTRYBY is 'ENTRYBY';

comment on column INT_RULESET.ENTRYDATE is 'ENTRYDATE';

comment on column INT_RULESET.MODIFBY is 'MODIFBY';

comment on column INT_RULESET.MODIFDATE is 'MODIFDATE';

comment on column INT_RULESET.MODIFIED is 'MODIFIED';

comment on column INT_RULESET.RECVER is 'RECVER';


-- ============================================================
--   Table: INT_RULE                                           
-- ============================================================
create table INT_RULE
(
    RULE                  VARCHAR2(10)           not null,
    NAME                  VARCHAR2(30)           null    ,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_RULE check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
    constraint PK_INT_RUL primary key (RULE)
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

create public synonym INT_RULE for INT_RULE;

grant select, insert, update, delete on INT_RULE to INTEGRATE_ROLE_ALL;

grant select on INT_RULE to INTEGRATE_ROLE_SEL;


comment on table INT_RULE is 'defines the actual rules';

comment on column INT_RULE.RULE is 'uniquely identifies a rule';

comment on column INT_RULE.NAME is 'name or description';

comment on column INT_RULE.ENTRYBY is 'ENTRYBY';

comment on column INT_RULE.ENTRYDATE is 'ENTRYDATE';

comment on column INT_RULE.MODIFBY is 'MODIFBY';

comment on column INT_RULE.MODIFDATE is 'MODIFDATE';

comment on column INT_RULE.MODIFIED is 'MODIFIED';

comment on column INT_RULE.RECVER is 'RECVER';



-- ============================================================
--   Table: INT_RULESETLIST                                    
-- ============================================================
create table INT_RULESETLIST
(
    RULESET               VARCHAR2(10)           not null,
    RANK                  NUMBER(9)              not null,
    RULE                  VARCHAR2(10)           not null,
    NAME                  VARCHAR2(30)           null    ,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               VARCHAR2(2000)         null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_RULESETLIST check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
    constraint PK_INT_RSL primary key (RULESET, RANK)
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

create public synonym INT_RULESETLIST for INT_RULESETLIST;

grant select, insert, update, delete on INT_RULESETLIST to INTEGRATE_ROLE_ALL;

grant select on INT_RULESETLIST to INTEGRATE_ROLE_SEL;

comment on table INT_RULESETLIST is 'defines a list of rules which should all be performed within a ruleset';

comment on column INT_RULESETLIST.RULESET is 'references the related ruleset';

comment on column INT_RULESETLIST.RANK is 'sequence order, in which the rule should be executed';

comment on column INT_RULESETLIST.RULE is 'lists the rules which should be executed one after each other';

comment on column INT_RULESETLIST.NAME is 'name or description';

comment on column INT_RULESETLIST.ENTRYBY is 'ENTRYBY';

comment on column INT_RULESETLIST.ENTRYDATE is 'ENTRYDATE';

comment on column INT_RULESETLIST.MODIFBY is 'MODIFBY';

comment on column INT_RULESETLIST.MODIFDATE is 'MODIFDATE';

comment on column INT_RULESETLIST.MODIFIED is 'MODIFIED';

comment on column INT_RULESETLIST.RECVER is 'RECVER';


-- ============================================================
--   Table: INT_RULEITEM                                       
-- ============================================================
create table INT_RULEITEM
(
    RULE                  VARCHAR2(10)           not null,
    RANK                  NUMBER(9)              not null,
    NAME                  VARCHAR2(30)           null    ,
    CONDITION             VARCHAR2(4000)         null    ,
    RESULT                LONG VARCHAR           null    ,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_RULEITEM check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
    constraint PK_INT_RUI primary key (RULE, RANK)
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

create public synonym INT_RULEITEM for INT_RULEITEM;

grant select, insert, update, delete on INT_RULEITEM to INTEGRATE_ROLE_ALL;

grant select on INT_RULEITEM to INTEGRATE_ROLE_SEL;


comment on table INT_RULEITEM is 'defines the single rule items (with conditions and result functions)';

comment on column INT_RULEITEM.RULE is 'defines the rule';

comment on column INT_RULEITEM.RANK is 'defines the sequence order for all occuring rule items';

comment on column INT_RULEITEM.NAME is 'name or description';

comment on column INT_RULEITEM.CONDITION is 'contains the condition rule values';

comment on column INT_RULEITEM.RESULT is 'defines the result values for the given condition';

comment on column INT_RULEITEM.ENTRYBY is 'ENTRYBY';

comment on column INT_RULEITEM.ENTRYDATE is 'ENTRYDATE';

comment on column INT_RULEITEM.MODIFBY is 'MODIFBY';

comment on column INT_RULEITEM.MODIFDATE is 'MODIFDATE';

comment on column INT_RULEITEM.MODIFIED is 'MODIFIED';

comment on column INT_RULEITEM.RECVER is 'RECVER';




-- ============================================================
--   Table: INT_SERVICECLASS                                   
-- ============================================================
create table INT_SERVICECLASS
(
    SERVICECODE           VARCHAR2(5)            not null,
    SERVICECLASS          VARCHAR2(5)            default '*' not null,
    NAME                  VARCHAR2(30)           null    ,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_SERVICECLASS check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
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
tablespace INTEGRATE_TS_1_DAT;

create public synonym INT_SERVICECLASS for INT_SERVICECLASS;

grant select, insert, update, delete on INT_SERVICECLASS to INTEGRATE_ROLE_ALL;

grant select on INT_SERVICECLASS to INTEGRATE_ROLE_SEL;


comment on table INT_SERVICECLASS is 'defines all possible service class''s per service code';

comment on column INT_SERVICECLASS.SERVICECODE is 'references the related service code';

comment on column INT_SERVICECLASS.SERVICECLASS is 'uniquely defines a service class for the given service code';

comment on column INT_SERVICECLASS.NAME is 'name or description';

comment on column INT_SERVICECLASS.ENTRYBY is 'ENTRYBY';

comment on column INT_SERVICECLASS.ENTRYDATE is 'ENTRYDATE';

comment on column INT_SERVICECLASS.MODIFBY is 'MODIFBY';

comment on column INT_SERVICECLASS.MODIFDATE is 'MODIFDATE';

comment on column INT_SERVICECLASS.MODIFIED is 'MODIFIED';

comment on column INT_SERVICECLASS.RECVER is 'RECVER';



-- ============================================================
--   Table: INT_TARIFFSERVICECLASS                             
-- ============================================================
create table INT_TARIFFSERVICECLASS
(
    TARIFFMODEL           NUMBER(9)              not null,
    RANK                  NUMBER(9)              not null,
    VALID_FROM            VARCHAR2(8)            not null,
    VALID_TO              VARCHAR2(8)            null    ,
    CALLCLASS             VARCHAR2(255)          null    ,
    CALLTYPE              VARCHAR2(255)          null    ,
    SERVICECODE           VARCHAR2(255)          null    ,
    ZONE                  VARCHAR2(255)          null    ,
    NEW_SERVICECODE       VARCHAR2(5)            null    ,
    NEW_SERVICECLASS      VARCHAR2(5)            null    ,
    NAME                  VARCHAR2(30)           null    ,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TARIFFSERVICE check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
    constraint PK_INT_TSC primary key (TARIFFMODEL, RANK)
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

create public synonym INT_TARIFFSERVICECLASS for INT_TARIFFSERVICECLASS;

grant select, insert, update, delete on INT_TARIFFSERVICECLASS to INTEGRATE_ROLE_ALL;

grant select on INT_TARIFFSERVICECLASS to INTEGRATE_ROLE_SEL;

comment on table INT_TARIFFSERVICECLASS is 'defines all valid service codes and service class''s for a given tariffmodel';

comment on column INT_TARIFFSERVICECLASS.TARIFFMODEL is 'TARIFFMODEL';

comment on column INT_TARIFFSERVICECLASS.RANK is 'RANK';

comment on column INT_TARIFFSERVICECLASS.VALID_FROM is 'this mapping entry is valid from (Format: YYYYMMDD or MON-SUN[HH:MM]) (compare: >=)';

comment on column INT_TARIFFSERVICECLASS.VALID_TO is 'defines the date till when this entry is valid (Format: YYYYMMDD or MON-SUN[HH:MM]) (compare: <)';

comment on column INT_TARIFFSERVICECLASS.CALLCLASS is 'CALLCLASS';

comment on column INT_TARIFFSERVICECLASS.CALLTYPE is 'CALLTYPE';

comment on column INT_TARIFFSERVICECLASS.SERVICECODE is 'SERVICECODE';

comment on column INT_TARIFFSERVICECLASS.ZONE is 'ZONE';

comment on column INT_TARIFFSERVICECLASS.NEW_SERVICECODE is 'NEW_SERVICECODE';

comment on column INT_TARIFFSERVICECLASS.NEW_SERVICECLASS is 'NEW_SERVICECLASS';

comment on column INT_TARIFFSERVICECLASS.NAME is 'NAME';

comment on column INT_TARIFFSERVICECLASS.ENTRYBY is 'ENTRYBY';

comment on column INT_TARIFFSERVICECLASS.ENTRYDATE is 'ENTRYDATE';

comment on column INT_TARIFFSERVICECLASS.MODIFBY is 'MODIFBY';

comment on column INT_TARIFFSERVICECLASS.MODIFDATE is 'MODIFDATE';

comment on column INT_TARIFFSERVICECLASS.MODIFIED is 'MODIFIED';

comment on column INT_TARIFFSERVICECLASS.RECVER is 'RECVER';


-- ============================================================
--   Table: INT_TAX                                            
-- ============================================================
create table INT_TAX
(
    TAXCODE               VARCHAR2(10)           not null,
    VALID_FROM            DATE                   not null,
    TAXRATE               NUMBER(4)              not null,
    ENTRYBY               NUMBER(9)              default 0 not null,
    ENTRYDATE             DATE                   default sysdate not null,
    MODIFBY               NUMBER(9)              null    ,
    MODIFDATE             DATE                   default sysdate null    ,
    MODIFIED              NUMBER(1)              default 1 not null
        constraint CKC_MODIFIED_INT_TAX check (
            MODIFIED in (0,1)),
    RECVER                NUMBER(9)              default 0 not null,
    constraint PK_INT_TAX primary key (TAXCODE, VALID_FROM)
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

create public synonym INT_TAX for INT_TAX;

grant select, insert, update, delete on INT_TAX to INTEGRATE_ROLE_ALL;

grant select on INT_TAX to INTEGRATE_ROLE_SEL;

comment on table INT_TAX is 'defines the different possible tax codes and tax rates';

comment on column INT_TAX.TAXCODE is 'tax code identifier';

comment on column INT_TAX.VALID_FROM is 'defines the date form which on a specific tax rate should be applied';

comment on column INT_TAX.TAXRATE is 'applied tax rate (e.g. 1600 for 16%), used for tax conversion';

comment on column INT_TAX.ENTRYBY is 'ENTRYBY';

comment on column INT_TAX.ENTRYDATE is 'ENTRYDATE';

comment on column INT_TAX.MODIFBY is 'MODIFBY';

comment on column INT_TAX.MODIFDATE is 'MODIFDATE';

comment on column INT_TAX.MODIFIED is 'MODIFIED';

comment on column INT_TAX.RECVER is 'RECVER';




-- ============================================================
-- ALTER Tables
-- ============================================================

-- ============================================================
--   Table: INT_CALLCLASS_MAP                                  
-- ============================================================
alter table INT_CALLCLASS_MAP
ADD (
    APPLICATION      VARCHAR2(255) default '*' not null,
    TRANSIT_AREACODE VARCHAR2(255) default '*' not null
);

comment on column INT_CALLCLASS_MAP.APPLICATION is 'external application (used within the edr format) that should be mapped';

comment on column INT_CALLCLASS_MAP.TRANSIT_AREACODE is 'external c-number (used within the edr format) that should be mapped';



-- ============================================================
--   Table: INT_CONTENTPROVIDER                                
-- ============================================================
alter table INT_CONTENTPROVIDER
ADD (
    CURRENCY VARCHAR2(3) default 'DEM' not null
);

comment on column INT_CONTENTPROVIDER.CURRENCY is 'the currency in which the content provider will typically be charged'



-- ============================================================
--   Table: INT_DISCOUNTDETAIL                                 
-- ============================================================
alter table INT_DISCOUNTDETAIL
ADD (
    SERVICECLASS          VARCHAR2(255)          null,
    PRICEMODEL            VARCHAR2(255)          null
);

comment on column INT_DISCOUNTDETAIL.SERVICECLASS is 'condition: references an internal service class (if empty all match), reg. expr. allowed';

comment on column INT_DISCOUNTDETAIL.PRICEMODEL is 'condition: references an internal price model (if empty all match), reg. expr. allowed';



-- ============================================================
--   Table: INT_EDRSEQLOG                                      
-- ============================================================
-- alter table INT_EDRSEQLOG
-- ADD (
--     PROCESSEDBY_FORMAT    VARCHAR2(10)           null
-- )

-- comment on column INT_EDRSEQLOG.PROCESSEDBY_FORMAT is 'defines the edr-format which has processed the related stream (could be different from the orig-format in case of sequence sharring)'



-- ============================================================
--   Table: INT_NOPRODUCT                                      
-- ============================================================
alter table INT_NOPRODUCT
ADD (
    CURRENCY              VARCHAR2(3)            default 'DEM' not null,
    TAXCODE               VARCHAR2(10)
);

comment on column INT_NOPRODUCT.CURRENCY is 'overwrites the default network operator currency for this specific product; if empty the no currency is valid';

comment on column INT_NOPRODUCT.TAXCODE is 'tax code which applies to this poduct';



-- ============================================================
--   Table: INT_SPLITTING_TYPE                                 
-- ============================================================
-- alter table INT_SPLITTING_TYPE
-- DROP ( RECORDTYPE, SERVICECODE, CALLCLASS );

alter table INT_SPLITTING_TYPE
ADD (
--    RECORDTYPE            VARCHAR2(255)          default '*' null    ,
--    SERVICECODE           VARCHAR2(255)          default '*' null    ,
--    CALLCLASS             VARCHAR2(255)          default '*' null    ,
    SOURCE_NETWORK        VARCHAR2(255)          default '*' null    ,
    DESTIN_NETWORK        VARCHAR2(255)          default '*' null    ,
    SWITCH                VARCHAR2(255)          default '*' not null,
    TRUNK_IN              VARCHAR2(255)          default '*' not null,
    TRUNK_OUT             VARCHAR2(255)          default '*' not null,
    ORIGIN_AREACODE       VARCHAR2(255)          default '*' null    ,
    DESTIN_AREACODE       VARCHAR2(255)          default '*' null    ,
    TRANSIT_AREACODE      VARCHAR2(255)          default '*' null
);

-- comment on column INT_SPLITTING_TYPE.RECORDTYPE is 'the record type for which a specialistsystem should be defined';

-- comment on column INT_SPLITTING_TYPE.SERVICECODE is 'the edr specific service code for which a specialistsystem should be defined';

-- comment on column INT_SPLITTING_TYPE.CALLCLASS is 'the callclass for which a specialistsystem should be defined';

comment on column INT_SPLITTING_TYPE.SOURCE_NETWORK is 'SOURCE_NETWORK';

comment on column INT_SPLITTING_TYPE.DESTIN_NETWORK is 'DESTIN_NETWORK';

comment on column INT_SPLITTING_TYPE.SWITCH is 'SWITCH';

comment on column INT_SPLITTING_TYPE.TRUNK_IN is 'TRUNK_IN';

comment on column INT_SPLITTING_TYPE.TRUNK_OUT is 'TRUNK_OUT';

comment on column INT_SPLITTING_TYPE.ORIGIN_AREACODE is 'the A# cli prefix for which a specialistsystem should be defined';

comment on column INT_SPLITTING_TYPE.DESTIN_AREACODE is 'the B# cli prefix for which a specialistsystem should be defined';

comment on column INT_SPLITTING_TYPE.TRANSIT_AREACODE is 'TRANSIT_AREACODE';


-- ============================================================
--   Table: INT_SUBS_ACCOUNT                                   
-- ============================================================
alter table INT_SUBS_ACCOUNT
add (
    SUM_VOL_SENT          NUMBER                 default 0 not null,
    SUM_VOL_RECEIVED      NUMBER                 default 0 not null,
    FRAME_VOL_SENT        NUMBER                 default 0 not null,
    FRAME_VOL_RECEIVED    NUMBER                 default 0 not null,
    DISC_VOL_SENT         NUMBER                 default 0 not null,
    DISC_VOL_RECEIVED     NUMBER                 default 0 not null
);

comment on column INT_SUBS_ACCOUNT.SUM_VOL_SENT is 'sum of all original volume sent values (any granted discounts are not inkluded in here!)';

comment on column INT_SUBS_ACCOUNT.SUM_VOL_RECEIVED is 'sum of all original volume received values (any granted discounts are not inkluded in here!)';

comment on column INT_SUBS_ACCOUNT.FRAME_VOL_SENT is 'sum of all frame based volume sent values (any granted discounts are not inkluded in here!)';

comment on column INT_SUBS_ACCOUNT.FRAME_VOL_RECEIVED is 'sum of all frame based volume received values (any granted discounts are not inkluded in here!)';

comment on column INT_SUBS_ACCOUNT.DISC_VOL_SENT is 'sum of granted discount volume sent (frame based)';

comment on column INT_SUBS_ACCOUNT.DISC_VOL_RECEIVED is 'sum of granted discount volume received (frame based)';


-- ============================================================
--   Table: INT_TARIFFMODEL_CNF                                
-- ============================================================

alter table INT_TARIFFMODEL_CNF
drop constraint PK_INT_TMC;

alter table INT_TARIFFMODEL_CNF
add (
    SERVICECLASS          VARCHAR2(5)            default '*' not null
);

alter table INT_TARIFFMODEL_CNF
add     constraint PK_INT_TMC primary key (TARIFFMODEL, VERSION, SERVICECODE, SERVICECLASS, ZONE, TIMEMODEL, TIMEZONE)
        using index
        pctfree 5
        initrans 2
        tablespace INTEGRATE_TS_4_IDX
        storage
        (
        initial 32M
        next 16M
        minextents 1
        maxextents unlimited
        pctincrease 0
);

comment on column INT_TARIFFMODEL_CNF.SERVICECLASS is 'default ''*'', but may define a special sub-service class, e.g. QoS as a combination of callclass, calltype ...';


-- ============================================================
--   Table: INT_PRICEMODEL_STEP
-- ============================================================

alter table INT_PRICEMODEL_STEP 
add CHARGE_ITEM CHAR(1) default 'Q' not null;

comment on column INT_PRICEMODEL_STEP.CHARGE_ITEM is 'defines if the pricemodel steps are related to Q=quantity, S=sent volume or R=received volume';

alter table INT_PRICEMODEL_STEP add constraint CKC_CHARGE_I_INT_PRICEMODEL_ST check (CHARGE_ITEM in ('Q','S','R','E'));

alter table INT_PRICEMODEL_STEP 
add CHARGE_BASE NUMBER(9) default 1 not null;

comment on column INT_PRICEMODEL_STEP.CHARGE_BASE is 'defines a charge base (e.g. a value of 60 means, that the charge value is base on 60 units, e.g. a minute)';


-- ============================================================
--   ADD Constraints                                    
-- ============================================================
alter table INT_CONTENT
    add constraint FK_INT_CNT_TMD foreign key  (TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL);

alter table INT_CONTENT
    add constraint FK_INT_CNT_CPD foreign key  (CONTENTPROVIDER)
       references INT_CONTENTPROVIDER (CONTENTPROVIDER);

alter table INT_CONTENT_MAP
    add constraint FK_INT_CNM_CNT foreign key  (CONTENTPROVIDER, CONTENTCODE)
       references INT_CONTENT (CONTENTPROVIDER, CONTENTCODE) on delete cascade;

alter table INT_CONTENT_MAP
    add constraint FK_INT_CNM_EDR foreign key  (EDR_FORMAT)
       references INT_EDRFORMAT (EDR_FORMAT);

alter table INT_RULESETLIST
    add constraint FK_INT_RSL_RUS foreign key  (RULESET)
       references INT_RULESET (RULESET);

alter table INT_RULESETLIST
    add constraint FK_INT_RSL_RUL foreign key  (RULE)
       references INT_RULE (RULE);

alter table INT_RULEITEM
    add constraint FK_INT_RUI_RUL foreign key  (RULE)
       references INT_RULE (RULE);

alter table INT_SERVICECLASS
    add constraint FK_INT_SVC_SRV foreign key  (SERVICECODE)
       references INT_SERVICE (SERVICECODE);

alter table INT_TARIFFSERVICECLASS
    add constraint FK_INT_TSC_TMD foreign key  (TARIFFMODEL)
       references INT_TARIFFMODEL (TARIFFMODEL);
       
alter table INT_TARIFFSERVICECLASS
    add constraint FK_INT_TSC_SVC foreign key  (NEW_SERVICECODE, NEW_SERVICECLASS)
       references INT_SERVICECLASS (SERVICECODE, SERVICECLASS);




-- ============================================================
--   Drop unused Tables and Constraints                                    
-- ============================================================
drop index FK_INT_SVN_CPD;

drop table INT_SERVICENUMBER cascade constraints;

drop table INT_SPLITTING_PREFIX cascade constraints;

insert into int_dbversion
( dbversion, description, username, install_date )
values
( 'v4-01-00', 'integRate', user, sysdate );
 
commit;
