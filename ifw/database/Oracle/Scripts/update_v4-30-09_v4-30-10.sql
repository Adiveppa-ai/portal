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
--   Update script from DB version v4-30-09 to v4-30-10.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-30-09_v4-30-10.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2002/01/10 15:18:10 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-30-09_v4-30-10.sql,v $
-- Revision 1.2  2002/01/10 15:18:10  pengelbr
-- PETS #42764 Column comment contains &-Sign which causes trouble
-- with sqlplus. Replaced by '+'.
--
-- Revision 1.1  2001/12/21 08:32:17  pengelbr
-- PETS #42574 LERG database extension.
-- - new table: IFW_LERG_DATA
-- - new ModelType 'L' in IFW_ZONEMODEL.MODELTYPE
-- - new column ruleset in IFW_GEOGRAPHICAL_MODEL
-- - new columns valid_from, valid_to in IFW_GEOAREACODE_LNK
-- PETS #41122 Pricemodel rounding rules-database extension.
-- - new columns rounding_method, decimal_places in IFW_PRICEMODEL
--
--------------------------------------------------------------------------------

spool update_v4-30-09_v4-30-10.log

--
-- IFW_PRICEMODEL
--
alter table ifw_pricemodel add rounding_method varchar2(5) default 'NONE' not null;

alter table ifw_pricemodel add decimal_places number(9) null;

alter table ifw_pricemodel add constraint CKC_ROUNDING_IFW_PRICEMODEL check (ROUNDING_METHOD in ('PLAIN','UP','DOWN','BANK','NONE'));

comment on column IFW_PRICEMODEL.ROUNDING_METHOD is 'Rounding method to be applied to calculated charge (PLAIN (nearest), UP, DOWN, BANK, NONE)';

comment on column IFW_PRICEMODEL.DECIMAL_PLACES is 'Number of relevant digits after decimal point.';

--
-- IFW_ZONEMODEL
--
alter table IFW_ZONEMODEL drop constraint CKC_MODELTYP_IFW_ZONEMODEL;

alter table IFW_ZONEMODEL add constraint CKC_MODELTYP_IFW_ZONEMODEL check (MODELTYPE in ('S','G','E','L'));

comment on column IFW_ZONEMODEL.MODELTYPE is 'type of zone model (S=standard, G=geographical, L=LERG, E=External)';

--
-- IFW_GEOGRAPHICALMODEL
--
alter table ifw_geographicalmodel add RULESET VARCHAR2(10) null;

comment on column IFW_GEOGRAPHICALMODEL.RULESET is 'Ruleset to map LERG-Info and calculated distance to new impact category.';

alter table IFW_GEOGRAPHICALMODEL
    add constraint FK_IFW_GMD_RUS foreign key  (RULESET)
       references IFW_RULESET (RULESET);
       
--
-- IFW_GEOAREACODE_LNK
--
alter table ifw_geoareacode_lnk drop primary key;

alter table ifw_geoareacode_lnk add valid_from date null;

update ifw_geoareacode_lnk 
set valid_from = to_date( '20010101', 'YYYYMMDD' )
where valid_from is null;

alter table ifw_geoareacode_lnk modify valid_from not null;

alter table ifw_geoareacode_lnk add valid_to date null;

alter table ifw_geoareacode_lnk add constraint PK_IFW_GAL primary key (GEOMODEL, AREACODE, VALID_FROM)
  using index pctfree 5 initrans 2 tablespace INTEGRATE_TS_3_IDX
  storage ( initial 256K next 256K minextents 1 maxextents unlimited pctincrease 0 );

update ifw_geoareacode_lnk set longitude = 0 where longitude is null;

alter table ifw_geoareacode_lnk modify longitude not null;

update ifw_geoareacode_lnk set latitude = 0 where latitude is null;

alter table ifw_geoareacode_lnk modify latitude not null;

comment on column IFW_GEOAREACODE_LNK.VALID_FROM is 'Date this entry is valid from.';

comment on column IFW_GEOAREACODE_LNK.VALID_TO is 'Date this entry is valid till (just for info, may be {null})';

--
-- IFW_LERG_DATA
--
create table IFW_LERG_DATA
(
    GEOMODEL                 NUMBER(9)              not null,
    AREACODE                 VARCHAR2(40)           not null,
    VALID_FROM               DATE                   not null,
    VALID_TO                 DATE                   null    ,
    LATA_SUBZONE             VARCHAR2(2)            null    ,
    LATA                     VARCHAR2(3)            null    ,
    LATA_NAME                VARCHAR2(20)           null    ,
    IDDD_IND                 CHAR(1)                null    ,
    TBPI                     CHAR(1)                null    ,
    DIALABLE_IND             CHAR(1)                null    ,
    NPA_NONMEX               VARCHAR2(3)            null    ,
    NPA                      VARCHAR2(3)            null    ,
    NXX                      VARCHAR2(3)            null    ,
    NXX_TYPE                 VARCHAR2(2)            null    ,
    PORTABLE_IND             CHAR(1)                null    ,
    SEND_TO_RAO              VARCHAR2(3)            null    ,
    OTHER_LINE_RATE_STEP     VARCHAR2(2)            null    ,
    OCN                      VARCHAR2(4)            null    ,
    BILL_TO_RAO              VARCHAR2(3)            null    ,
    SPECIAL_RATING_IND       CHAR(1)                null    ,
    TIMEZONE                 CHAR(1)                null    ,
    DSO_IND                  CHAR(1)                null    ,
    STATE                    VARCHAR2(2)            null    ,
    COMPANY_CODE             VARCHAR2(2)            null    ,
    COMPANY_TYPE             CHAR(1)                null    ,
    POINT_ID                 CHAR(1)                null    ,
    SSC                      VARCHAR2(4)            null    ,
    TD_EO                    VARCHAR2(2)            null    ,
    TD_AT                    VARCHAR2(2)            null    ,
    AOCN                     VARCHAR2(4)            null    ,
    LOC_NAME                 VARCHAR2(10)           null    ,
    LOC_COUNTY               VARCHAR2(2)            null    ,
    RC_ABBREV                VARCHAR2(10)           null    ,
    RC_TYPE                  CHAR(1)                null    ,
    SWITCH                   VARCHAR2(11)           null    ,
    SHA_IND                  VARCHAR2(2)            null    ,
    RANGE_OCN                VARCHAR2(4)            null    ,
    ENTRYBY                  NUMBER(9)              default 0 not null,
    ENTRYDATE                DATE                   default sysdate not null,
    MODIFDATE                DATE                   default sysdate null    ,
    MODIFBY                  NUMBER(9)              null    ,
    MODIFIED                 NUMBER(1)              default 1 null    
        constraint CKC_MODIFIED_IFW_LERG_DATA check (MODIFIED is null or (MODIFIED in (0,1))),
    RECVER                   NUMBER(9)              default 0 not null,
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

comment on column IFW_LERG_DATA.OTHER_LINE_RATE_STEP is 'Coded information needed to properly determine the rating associated in certain non-US areas.  In the case of Mexican data, this pertains to bands 1-8.';

comment on column IFW_LERG_DATA.OCN is 'A four digit code that refers to the party owning or responsible for a given record.  0000 indicates unknown or not applicable.';

comment on column IFW_LERG_DATA.BILL_TO_RAO is 'The "bill to" Revenue Accounting Office (RAO).  In V+H Data NXX files, if this is an "additional" RAO, the "main" RAO will be in the "Send to RAO" field.';

comment on column IFW_LERG_DATA.SPECIAL_RATING_IND is '0 = No Special Rating, 1 = Person Day Rate Only, 2 = No Collect Calls, 3 = Collect Calls Person Only';

comment on column IFW_LERG_DATA.TIMEZONE is '0 = Not applicable, 1 = Guam and the Commonwealth of the Northern Mariana Islands (CNMI), 2 = Hawaii, 3 = Alaska/Yukon, 4 = Pacific, 5 = Mountain, 6 = Central, 7 = Eastern, 8 = Atlantic, 9 = Newfoundland ';

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

alter table IFW_LERG_DATA
    add constraint FK_IFW_LERG_GAL foreign key  (GEOMODEL, AREACODE, VALID_FROM)
       references IFW_GEOAREACODE_LNK (GEOMODEL, AREACODE, VALID_FROM);

--
-- IFW_DBVERSION
--
insert into ifw_dbversion
( dbversion, description, username, install_date )
values
( 'v4-30-10', 'IntegRate,Interconnect,Analyze', user, sysdate );

spool off;

commit;
