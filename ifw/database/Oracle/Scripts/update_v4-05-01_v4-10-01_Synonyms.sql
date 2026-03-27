--------------------------------------------------------------------------------
--
--      Copyright (c) 2000 - 2006 Oracle. All rights reserved.
--
--      This material is the confidential property of Oracle Corporation
--      or its licensors and may be used, reproduced, stored or transmitted
--      only in accordance with a valid Oracle license or sublicense agreement.
--
--------------------------------------------------------------------------------
-- Block: Database
--------------------------------------------------------------------------------
-- Module Description:
--   Create all public synonyms.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-05-01_v4-10-01_Synonyms.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2000/12/21 14:22:16 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-05-01_v4-10-01_Synonyms.sql,v $
-- Revision 1.2  2000/12/21 14:22:16  pengelbr
-- Updated to NOT modify INT_ISCRIPT and INT_RULE* tables.
-- iScript and iRules columns shall be of LONG type as before (v4-05).
--
-- Revision 1.1  2000/10/20 07:40:37  pengelbr
-- Modified/Added for v4-10-01 by PE.
--
--------------------------------------------------------------------------------

-- ============================================================
-- TABLES
-- ============================================================
create public synonym INT_SOCIALNUMBER for INT_SOCIALNUMBER
/
create public synonym INT_CLOSEDUSERGROUP for INT_CLOSEDUSERGROUP
/
create public synonym INT_SEMAPHORE for INT_SEMAPHORE
/
create public synonym INT_SUBS_ACCOUNT for INT_SUBS_ACCOUNT
/
create public synonym INT_DBVERSION for INT_DBVERSION
/
create public synonym IC_DAILY for IC_DAILY
/
create public synonym IC_DAILY_ALTERNATE for IC_DAILY_ALTERNATE
/
create public synonym AGG_HOLIDAY for AGG_HOLIDAY
/
create public synonym INT_DESTINATIONDESC for INT_DESTINATIONDESC
/
create public synonym INT_TIMEMODEL for INT_TIMEMODEL
/
create public synonym INT_DAYCODE for INT_DAYCODE
/
create public synonym INT_SPECIALDAYRATE for INT_SPECIALDAYRATE
/
create public synonym INT_PRICEMODEL for INT_PRICEMODEL
/
create public synonym INT_ZONE for INT_ZONE
/
create public synonym INT_TIMEINTERVAL for INT_TIMEINTERVAL
/
create public synonym INT_TIMEZONE for INT_TIMEZONE
/
create public synonym INT_SEGMENT for INT_SEGMENT
/
create public synonym INT_EDRFORMAT for INT_EDRFORMAT
/
create public synonym INT_GEOGRAPHICALMODEL for INT_GEOGRAPHICALMODEL
/
create public synonym INT_CALLCLASS for INT_CALLCLASS
/
create public synonym INT_CALENDAR for INT_CALENDAR
/
create public synonym INT_SYSTEM_BRAND for INT_SYSTEM_BRAND
/
create public synonym INT_DISCOUNTMODEL for INT_DISCOUNTMODEL
/
create public synonym INT_DISCOUNTRULE for INT_DISCOUNTRULE
/
create public synonym INT_DISCOUNTMASTER for INT_DISCOUNTMASTER
/
create public synonym INT_SUBS_BILLCYCLE for INT_SUBS_BILLCYCLE
/
create public synonym INT_CALLTYPE for INT_CALLTYPE
/
create public synonym INT_DISCOUNTTRIGGER for INT_DISCOUNTTRIGGER
/
create public synonym AGG_SCENARIO for AGG_SCENARIO
/
create public synonym AGG_CLASSITEM for AGG_CLASSITEM
/
create public synonym AGG_CLASS for AGG_CLASS
/
create public synonym SOL_OBJS for SOL_OBJS
/
create public synonym AGG_REFERENCESET for AGG_REFERENCESET
/
create public synonym SOL_SECTION for SOL_SECTION
/
create public synonym SOL_UNITS for SOL_UNITS
/
create public synonym AGG_QUEUE for AGG_QUEUE
/
create public synonym INT_CZT_GROUP for INT_CZT_GROUP
/
create public synonym INT_MAP_GROUP for INT_MAP_GROUP
/
create public synonym INT_TSC_GROUP for INT_TSC_GROUP
/
create public synonym INT_APN_GROUP for INT_APN_GROUP
/
create public synonym INT_UOM for INT_UOM
/
create public synonym INT_TAXGROUP for INT_TAXGROUP
/
create public synonym INT_TAXCODE for INT_TAXCODE
/
create public synonym INT_REVENUEGROUP for INT_REVENUEGROUP
/
create public synonym INT_CURRENCY for INT_CURRENCY
/
create public synonym INT_ICPRODUCT_GROUP for INT_ICPRODUCT_GROUP
/
create public synonym INT_DISCOUNTMDL_VER for INT_DISCOUNTMDL_VER
/
create public synonym INT_SUBSDISCOUNT_MAP for INT_SUBSDISCOUNT_MAP
/
create public synonym SOL_TABS for SOL_TABS
/
create public synonym SOL_CONSTRAINTS for SOL_CONSTRAINTS
/
create public synonym SOL_COLS for SOL_COLS
/
create public synonym AGG_GROUPING for AGG_GROUPING
/
create public synonym AGG_GROUPING_CNF for AGG_GROUPING_CNF
/
create public synonym AGG_CLASSCON for AGG_CLASSCON
/
create public synonym INT_ZONEMODEL for INT_ZONEMODEL
/
create public synonym INT_GLACCOUNT for INT_GLACCOUNT
/
create public synonym INT_SERVICE for INT_SERVICE
/
create public synonym INT_SUBSSERVICE_MAP for INT_SUBSSERVICE_MAP
/
create public synonym INT_SERVICECLASS for INT_SERVICECLASS
/
create public synonym INT_NETWORKOPERATOR for INT_NETWORKOPERATOR
/
create public synonym INT_CONTENTPROVIDER for INT_CONTENTPROVIDER
/
create public synonym INT_SUBS_CONTRACT for INT_SUBS_CONTRACT
/
create public synonym INT_TARIFFMODEL for INT_TARIFFMODEL
/
create public synonym INT_TRUNK for INT_TRUNK
/
create public synonym INT_SWITCH for INT_SWITCH
/
create public synonym INT_NOPRODUCT for INT_NOPRODUCT
/
create public synonym INT_ICPRODUCT for INT_ICPRODUCT
/
create public synonym INT_SUBSTARIFF_MAP for INT_SUBSTARIFF_MAP
/
create public synonym INT_CONTENT for INT_CONTENT
/
create public synonym INT_TARIFFMODEL_VER for INT_TARIFFMODEL_VER
/
create public synonym INT_NETWORKMODEL for INT_NETWORKMODEL
/
create public synonym INT_POI for INT_POI
/
create public synonym INT_CALLTYPE_MAP for INT_CALLTYPE_MAP
/
create public synonym INT_CLASSTYPEZONE_MAP for INT_CLASSTYPEZONE_MAP
/
create public synonym INT_PRICEMODEL_STEP for INT_PRICEMODEL_STEP
/
create public synonym INT_HOLIDAY for INT_HOLIDAY
/
create public synonym INT_TARIFFMODEL_CNF for INT_TARIFFMODEL_CNF
/
create public synonym INT_SPECIALDAY_LNK for INT_SPECIALDAY_LNK
/
create public synonym INT_TIMEMODEL_LNK for INT_TIMEMODEL_LNK
/
create public synonym INT_STANDARD_ZONE for INT_STANDARD_ZONE
/
create public synonym INT_GEOGRAPHICAL_ZONE for INT_GEOGRAPHICAL_ZONE
/
create public synonym INT_SEGZONE_LNK for INT_SEGZONE_LNK
/
create public synonym INT_POIAREA_LNK for INT_POIAREA_LNK
/
create public synonym INT_GEOAREACODE_LNK for INT_GEOAREACODE_LNK
/
create public synonym INT_SERVICECODE_MAP for INT_SERVICECODE_MAP
/
create public synonym INT_CALLCLASS_MAP for INT_CALLCLASS_MAP
/
create public synonym INT_SUBS_LOCAL for INT_SUBS_LOCAL
/
create public synonym INT_TARIFFDISCOUNT_LNK for INT_TARIFFDISCOUNT_LNK
/
create public synonym INT_SEGTARIFF_LNK for INT_SEGTARIFF_LNK
/
create public synonym INT_EDRSEQLOG for INT_EDRSEQLOG
/
create public synonym INT_SPLITTING_TYPE for INT_SPLITTING_TYPE
/
create public synonym INT_EXCHANGE_RATE for INT_EXCHANGE_RATE
/
create public synonym INT_APN_MAP for INT_APN_MAP
/
create public synonym INT_SUBS_CLI for INT_SUBS_CLI
/
create public synonym INT_SUBS_CONTRACT_HIST for INT_SUBS_CONTRACT_HIST
/
create public synonym INT_DISCOUNTMDL_CNF for INT_DISCOUNTMDL_CNF
/
create public synonym INT_DISCOUNTSTEP for INT_DISCOUNTSTEP
/
create public synonym INT_DISCOUNTDETAIL for INT_DISCOUNTDETAIL
/
create public synonym INT_SUBS_BILLRUN for INT_SUBS_BILLRUN
/
create public synonym INT_NOSP for INT_NOSP
/
create public synonym INT_ICPRODUCT_CNF for INT_ICPRODUCT_CNF
/
create public synonym INT_NOPRODUCT_CNF for INT_NOPRODUCT_CNF
/
create public synonym INT_DISCOUNTCONDITION for INT_DISCOUNTCONDITION
/
create public synonym INT_DISCARDING for INT_DISCARDING
/
create public synonym INT_NO_BILLRUN for INT_NO_BILLRUN
/
create public synonym INT_TARIFFSERVICECLASS for INT_TARIFFSERVICECLASS
/
create public synonym INT_TAX for INT_TAX
/
create public synonym INT_CONTENT_MAP for INT_CONTENT_MAP
/
create public synonym AGG_AGGREGATION for AGG_AGGREGATION
/
create public synonym AGG_CONDITION for AGG_CONDITION
/
create public synonym AGG_EDRCFIELD for AGG_EDRCFIELD
/
create public synonym SOL_CONST_COLS for SOL_CONST_COLS
/
create public synonym AGG_CLASS_LNK for AGG_CLASS_LNK
/
create public synonym AGG_REFERENCESET_CNF for AGG_REFERENCESET_CNF
/
create public synonym SOL_REGISTRY for SOL_REGISTRY
/
create public synonym AGG_CLASSCON_LNK for AGG_CLASSCON_LNK
/
create public synonym AGG_DICTIONARY for AGG_DICTIONARY
/
create public synonym INT_ICNO_LNK for INT_ICNO_LNK
/
create public synonym INT_UOM_MAP for INT_UOM_MAP
/
create public synonym INT_SUBS_REFERENCE_HIST for INT_SUBS_REFERENCE_HIST
/
create public synonym INT_TRUNK_CNF for INT_TRUNK_CNF
/

-- ============================================================
-- VIEWS
-- ============================================================
CREATE PUBLIC SYNONYM AGG_FORMAT_MAP_COLUMNS FOR AGG_FORMAT_MAP_COLUMNS
/
