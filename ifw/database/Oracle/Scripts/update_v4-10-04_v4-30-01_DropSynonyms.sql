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
--   Drop all v4-10 public synonyms before upgrading to v4-30.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-10-04_v4-30-01_DropSynonyms.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/07/06 07:43:43 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-10-04_v4-30-01_DropSynonyms.sql,v $
-- Revision 1.1  2001/07/06 07:43:43  pengelbr
-- PETS #36686 Create a database migration script from v4-10-04 to v4-30-00
--
--------------------------------------------------------------------------------

-- select 'drop public synonym ' || object_name || ';' 
-- from user_objects 
-- where object_type in ( 'TABLE', 'SEQUENCE', 'VIEW' ) and 
--     ( object_name like 'AGG_%' or object_name like 'INT_%' or object_name like 'SOL_%' ) 
-- order by object_type;

-- ============================================================
-- SEQUENCES
-- ============================================================
drop public synonym AGG_AGGREGATION_SEQ;
drop public synonym AGG_CLASSCON_SEQ;
drop public synonym AGG_CLASSITEM_SEQ;
drop public synonym AGG_CONDITION_SEQ;
drop public synonym AGG_EDRFORMAT_SEQ;
drop public synonym AGG_GROUPING_SEQ;
drop public synonym AGG_SCENARIO_SEQ;
drop public synonym INT_SEQ_CONTENTPROVIDER;
drop public synonym INT_SEQ_DISCOUNTCONDITION;
drop public synonym INT_SEQ_GRANTED_DISCOUNT;
drop public synonym INT_SEQ_GEOMODEL;
drop public synonym INT_SEQ_GENERIC;
drop public synonym INT_SEQ_DISCOUNTTRIGGER;
drop public synonym INT_SEQ_DISCOUNTSTEP;
drop public synonym INT_SEQ_DISCOUNTRULE;
drop public synonym INT_SEQ_DISCOUNTMODEL;
drop public synonym INT_SEQ_DISCOUNTMASTER;
drop public synonym INT_SEQ_DISCOUNTCONFIG;
drop public synonym SOL_UNITS_SEQ;
drop public synonym SOL_OBJS_SEQ;
drop public synonym SOL_CONSTRAINTS_SEQ;
drop public synonym INT_SEQ_ZONEMODEL;
drop public synonym INT_SEQ_TIMEZONE;
drop public synonym INT_SEQ_TIMEMODEL;
drop public synonym INT_SEQ_TIMEINTERVAL;
drop public synonym INT_SEQ_TARIFFMODEL;
drop public synonym INT_SEQ_SYSTEMBRAND;
drop public synonym INT_SEQ_SPECIALDAYRATE;
drop public synonym INT_SEQ_SEMAPHORE;
drop public synonym INT_SEQ_PRICEMODEL;
drop public synonym INT_SEQ_NO;
drop public synonym INT_SEQ_NETWORKMODEL;
drop public synonym INT_SEQ_DAYCODE;
drop public synonym INT_SEQ_CALENDAR;
drop public synonym AGG_REFERENCESET_SEQ;
drop public synonym AGG_GROUPING_CNF_SEQ;
drop public synonym AGG_EDRCFIELD_SEQ;
drop public synonym AGG_CLASS_SEQ;

-- ============================================================
-- TABLES
-- ============================================================
drop public synonym AGG_AGGREGATION;
drop public synonym AGG_CLASS;
drop public synonym INT_APN_MAP;
drop public synonym INT_APN_GROUP;
drop public synonym AGG_SCENARIO;
drop public synonym AGG_REFERENCESET_CNF;
drop public synonym AGG_REFERENCESET;
drop public synonym AGG_QUEUE;
drop public synonym AGG_HOLIDAY;
drop public synonym AGG_GROUPING_CNF;
drop public synonym AGG_GROUPING;
drop public synonym INT_CONTENTPROVIDER;
drop public synonym INT_CONTENT;
drop public synonym INT_CLOSEDUSERGROUP;
drop public synonym INT_CLASSTYPEZONE_MAP;
drop public synonym INT_CALLTYPE_MAP;
drop public synonym INT_CALLTYPE;
drop public synonym INT_CALLCLASS_MAP;
drop public synonym INT_CALLCLASS;
drop public synonym INT_CALENDAR;
drop public synonym INT_EDRFORMAT;
drop public synonym INT_DISCOUNTTRIGGER;
drop public synonym INT_DISCOUNTSTEP;
drop public synonym INT_DISCOUNTRULE;
drop public synonym INT_DISCOUNTMODEL;
drop public synonym INT_DISCOUNTMDL_VER;
drop public synonym INT_DISCOUNTMDL_CNF;
drop public synonym INT_DISCOUNTMASTER;
drop public synonym INT_DISCOUNTDETAIL;
drop public synonym INT_SUBS_CONTRACT;
drop public synonym INT_SUBS_CLI;
drop public synonym INT_SUBS_BILLRUN;
drop public synonym INT_SUBS_BILLCYCLE;
drop public synonym INT_SUBS_ACCOUNT;
drop public synonym INT_SUBSTARIFF_MAP;
drop public synonym INT_SUBSSERVICE_MAP;
drop public synonym INT_SUBSDISCOUNT_MAP;
drop public synonym INT_STANDARD_ZONE;
drop public synonym SOL_UNITS;
drop public synonym SOL_TABS;
drop public synonym SOL_OBJS;
drop public synonym SOL_CONST_COLS;
drop public synonym SOL_CONSTRAINTS;
drop public synonym SOL_COLS;
drop public synonym INT_ZONEMODEL;
drop public synonym INT_ZONE;
drop public synonym INT_UOM_MAP;
drop public synonym INT_UOM;
drop public synonym INT_TSC_GROUP;
drop public synonym INT_TRUNK_CNF;
drop public synonym INT_TRUNK;
drop public synonym INT_TIMEZONE;
drop public synonym INT_TIMEMODEL_LNK;
drop public synonym INT_TIMEMODEL;
drop public synonym INT_TIMEINTERVAL;
drop public synonym INT_TAXGROUP;
drop public synonym INT_TAXCODE;
drop public synonym INT_TAX;
drop public synonym INT_TARIFFSERVICECLASS;
drop public synonym INT_TARIFFMODEL_VER;
drop public synonym INT_TARIFFMODEL_CNF;
drop public synonym INT_TARIFFMODEL;
drop public synonym INT_TARIFFDISCOUNT_LNK;
drop public synonym INT_SYSTEM_BRAND;
drop public synonym INT_SWITCH;
drop public synonym INT_SUBS_REFERENCE_HIST;
drop public synonym INT_SUBS_LOCAL;
drop public synonym INT_SUBS_CONTRACT_HIST;
drop public synonym INT_SUBS_CONTRACT_BC;
drop public synonym INT_SPLITTING_TYPE;
drop public synonym INT_SPECIALDAY_LNK;
drop public synonym INT_SPECIALDAYRATE;
drop public synonym INT_SOCIALNUMBER;
drop public synonym INT_SERVICECODE_MAP;
drop public synonym INT_SERVICECLASS;
drop public synonym INT_SERVICE;
drop public synonym INT_NOPRODUCT_CNF;
drop public synonym INT_NOPRODUCT;
drop public synonym INT_NETWORKOPERATOR;
drop public synonym INT_NETWORKMODEL;
drop public synonym INT_MAP_GROUP;
drop public synonym INT_ISCRIPT;
drop public synonym INT_ICPRODUCT_GROUP;
drop public synonym INT_ICPRODUCT_CNF;
drop public synonym INT_ICPRODUCT;
drop public synonym INT_SEMAPHORE;
drop public synonym INT_SEGZONE_LNK;
drop public synonym INT_SEGTARIFF_LNK;
drop public synonym INT_SEGMENT;
drop public synonym INT_RULESETLIST;
drop public synonym INT_RULESET;
drop public synonym INT_RULEITEM;
drop public synonym INT_RULE;
drop public synonym INT_REVENUEGROUP;
drop public synonym INT_PRICEMODEL_STEP;
drop public synonym INT_PRICEMODEL;
drop public synonym INT_POIAREA_LNK;
drop public synonym INT_POI;
drop public synonym INT_NO_BILLRUN;
drop public synonym INT_NOSP;
drop public synonym INT_ICNO_LNK;
drop public synonym INT_HOLIDAY;
drop public synonym INT_GLACCOUNT;
drop public synonym INT_GEOGRAPHICAL_ZONE;
drop public synonym INT_GEOGRAPHICALMODEL;
drop public synonym INT_GEOAREACODE_LNK;
drop public synonym INT_EXCHANGE_RATE;
drop public synonym INT_EDRSEQLOG;
drop public synonym INT_DISCOUNTCONDITION;
drop public synonym INT_DISCARDING;
drop public synonym INT_DESTINATIONDESC;
drop public synonym INT_DBVERSION;
drop public synonym INT_DAYCODE;
drop public synonym INT_CZT_GROUP;
drop public synonym INT_CURRENCY;
drop public synonym INT_CONTENT_MAP;
drop public synonym AGG_EDRCFIELD;
drop public synonym AGG_DICTIONARY;
drop public synonym AGG_CONDITION;
drop public synonym AGG_CLASS_LNK;
drop public synonym AGG_CLASSITEM;
drop public synonym AGG_CLASSCON;
drop public synonym AGG_CLASSCON_LNK;

-- ============================================================
-- VIEWS
-- ============================================================
drop public synonym AGG_FORMAT_MAP_COLUMNS;

