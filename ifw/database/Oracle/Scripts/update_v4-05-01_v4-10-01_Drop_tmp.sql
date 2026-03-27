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
--   Drop all temporary tables.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-05-01_v4-10-01_Drop_tmp.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2000/12/21 14:22:16 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-05-01_v4-10-01_Drop_tmp.sql,v $
-- Revision 1.2  2000/12/21 14:22:16  pengelbr
-- Updated to NOT modify INT_ISCRIPT and INT_RULE* tables.
-- iScript and iRules columns shall be of LONG type as before (v4-05).
--
-- Revision 1.1  2000/10/20 07:40:37  pengelbr
-- Modified/Added for v4-10-01 by PE.
--
--------------------------------------------------------------------------------

drop table tmp_INT_SOCIALNUMBER;

drop table tmp_INT_CLOSEDUSERGROUP;

drop table tmp_INT_EXCHANGE_RATE;

drop table tmp_INT_SUBS_ACCOUNT;

drop table tmp_INT_DBVERSION;

drop table tmp_INT_TAX;

drop table tmp_IC_DAILY;

drop table tmp_IC_DAILY_ALTERNATE;

drop table tmp_AGG_HOLIDAY;

drop table tmp_INT_DESTINATIONDESC;

drop table tmp_INT_TIMEMODEL;

drop table tmp_INT_CONTENTPROVIDER;

drop table tmp_INT_DAYCODE;

drop table tmp_INT_SPECIALDAYRATE;

drop table tmp_INT_PRICEMODEL;

drop table tmp_INT_ZONE;

drop table tmp_INT_TIMEINTERVAL;

drop table tmp_INT_TIMEZONE;

drop table tmp_INT_SEGMENT;

drop table tmp_INT_NETWORKOPERATOR;

drop table tmp_INT_EDRFORMAT;

drop table tmp_INT_GEOGRAPHICALMODEL;

drop table tmp_INT_SERVICE;

drop table tmp_INT_CALLCLASS;

drop table tmp_INT_CALENDAR;

drop table tmp_INT_DISCOUNTMODEL;

drop table tmp_INT_DISCOUNTRULE;

drop table tmp_INT_DISCOUNTMASTER;

drop table tmp_INT_SUBS_BILLCYCLE;

drop table tmp_INT_CALLTYPE;

drop table tmp_INT_DISCOUNTTRIGGER;

drop table tmp_AGG_SCENARIO;

drop table tmp_AGG_CLASSITEM;

drop table tmp_AGG_CLASS;

drop table tmp_AGG_EDRFORMAT;

drop table tmp_SOL_OBJS;

drop table tmp_AGG_REFERENCESET;

drop table tmp_SOL_SECTION;

drop table tmp_SOL_UNITS;

drop table tmp_AGG_QUEUE;

drop table tmp_INT_NOPRODUCT;

drop table tmp_INT_ZONEMODEL;

drop table tmp_INT_SUBSSERVICE_MAP;

drop table tmp_INT_SERVICECLASS;

drop table tmp_INT_TARIFFMODEL;

drop table tmp_INT_ICPRODUCT;

drop table tmp_INT_SPECIALISTSYSTEM;

drop table tmp_INT_SUBSTARIFF_MAP;

drop table tmp_INT_CONTENT;

drop table tmp_INT_TARIFFMODEL_VER;

drop table tmp_INT_NETWORKMODEL;

drop table tmp_INT_SUBS_CONTRACT;

drop table tmp_INT_SWITCH;

drop table tmp_INT_POI;

drop table tmp_INT_TRUNK;

drop table tmp_INT_DISCOUNTMDL_VER;

drop table tmp_INT_SUBSDISCOUNT_MAP;

drop table tmp_SOL_TABS;

drop table tmp_SOL_CONSTRAINTS;

drop table tmp_SOL_COLS;

drop table tmp_AGG_GROUPING;

drop table tmp_AGG_GROUPING_CNF;

drop table tmp_AGG_CLASSCON;

drop table tmp_INT_CALLTYPE_MAP;

drop table tmp_INT_CLASSTYPEZONE_MAP;

drop table tmp_INT_PRICEMODEL_STEP;

drop table tmp_INT_HOLIDAY;

drop table tmp_INT_TARIFFMODEL_CNF;

drop table tmp_INT_SPECIALDAY_LNK;

drop table tmp_INT_TIMEMODEL_LNK;

drop table tmp_INT_STANDARD_ZONE;

drop table tmp_INT_GEOGRAPHICAL_ZONE;

drop table tmp_INT_SEGZONE_LNK;

drop table tmp_INT_POIAREA_LNK;

drop table tmp_INT_GEOAREACODE_LNK;

drop table tmp_INT_SERVICECODE_MAP;

drop table tmp_INT_CALLCLASS_MAP;

drop table tmp_INT_SUBS_LOCAL;

drop table tmp_INT_TARIFFDISCOUNT_LNK;

drop table tmp_INT_SEGTARIFF_LNK;

drop table tmp_INT_EDRSEQLOG;

drop table tmp_INT_SPLITTING_TYPE;

drop table tmp_INT_AREACODE_MAP;

drop table tmp_INT_SUBS_CLI;

drop table tmp_INT_SUBS_CONTRACT_HIST;

drop table tmp_INT_DISCOUNTMDL_CNF;

drop table tmp_INT_DISCOUNTSTEP;

drop table tmp_INT_DISCOUNTDETAIL;

drop table tmp_INT_SUBS_BILLRUN;

drop table tmp_INT_NOSP;

drop table tmp_INT_ICPRODUCT_CNF;

drop table tmp_INT_NOPRODUCT_CNF;

drop table tmp_INT_DISCOUNTCONDITION;

drop table tmp_INT_DISCARDING;

drop table tmp_INT_TIMEMODEL_CNF;

drop table tmp_INT_NO_BILLRUN;

drop table tmp_INT_TARIFFSERVICECLASS;

drop table tmp_INT_CONTENT_MAP;

drop table tmp_INT_RESELLER_LNK;

drop table tmp_AGG_AGGREGATION;

drop table tmp_AGG_CONDITION;

drop table tmp_AGG_EDRCFIELD;

drop table tmp_SOL_CONST_COLS;

drop table tmp_AGG_REFERENCESET_CNF;

drop table tmp_AGG_EDRFORMAT_SCN;

drop table tmp_AGG_DICTIONARY;

