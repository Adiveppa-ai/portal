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
--   Drop all constraints and rename all tables.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-05-01_v4-10-01_Copy.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2000/12/21 14:22:16 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-05-01_v4-10-01_Copy.sql,v $
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
insert into INT_SOCIALNUMBER
  ( SOCIALNUMBER, NAME )
  select SOCIALNUMBER, NAME 
  from tmp_INT_SOCIALNUMBER;

-- ============================================================
--   Table: INT_CLOSEDUSERGROUP                                
-- ============================================================
insert into INT_CLOSEDUSERGROUP
  ( CLI, VALID_FROM, CLOSEDUSERGROUP, VALID_TO )
  select CLI, VALID_FROM, CLOSEDUSERGROUP, VALID_TO
  from tmp_INT_CLOSEDUSERGROUP;

-- ============================================================
--   Table: INT_SEMAPHORE                                      
-- ============================================================
-- insert into INT_SEMAPHORE
--   ( REQUEST_ID, SEMAPHORE, EXECUTION_DATE, PERIODE, 
--     EXECUTED, RESULTSTATUS, CONTENT )
--   select REQUEST_ID, SEMAPHORE, EXECUTION_DATE, PERIODE, 
--     EXECUTED, RESULTSTATUS, to_lob( CONTENT )
--   from tmp_INT_SEMAPHORE;

-- ============================================================
--   Table: INT_CURRENCY
-- ============================================================
insert into INT_CURRENCY
  ( CURRENCY, NAME )
  select distinct CURRENCY, CURRENCY
  from tmp_INT_NETWORKOPERATOR;
  
insert into INT_CURRENCY
  ( CURRENCY, NAME )
  select distinct CURRENCY, CURRENCY
  from tmp_INT_NOPRODUCT
  where CURRENCY not in 
    ( select CURRENCY from INT_CURRENCY );

insert into INT_CURRENCY
  ( CURRENCY, NAME )
  select distinct CURRENCY, CURRENCY
  from tmp_INT_CONTENTPROVIDER
  where CURRENCY not in 
    ( select CURRENCY from INT_CURRENCY );

insert into INT_CURRENCY
  ( CURRENCY, NAME )
  select distinct CURRENCY, CURRENCY
  from tmp_INT_CONTENT
  where CURRENCY not in 
    ( select CURRENCY from INT_CURRENCY );
  
insert into INT_CURRENCY
  ( CURRENCY, NAME )
  select distinct CURRENCY, CURRENCY
  from tmp_INT_TARIFFMODEL
  where CURRENCY not in 
    ( select CURRENCY from INT_CURRENCY );
  
insert into INT_CURRENCY
  ( CURRENCY, NAME )
  select distinct FROM_CURRENCY, FROM_CURRENCY
  from tmp_INT_EXCHANGE_RATE
  where FROM_CURRENCY not in 
    ( select CURRENCY from INT_CURRENCY );

insert into INT_CURRENCY
  ( CURRENCY, NAME )
  select distinct TO_CURRENCY, TO_CURRENCY
  from tmp_INT_EXCHANGE_RATE
  where TO_CURRENCY not in 
    ( select CURRENCY from INT_CURRENCY );

-- ============================================================
--   Table: INT_EXCHANGE_RATE                                  
-- ============================================================
insert into INT_EXCHANGE_RATE
  ( FROM_CURRENCY, VALID_FROM, TO_CURRENCY, EXCHANGE_RATE )
  select FROM_CURRENCY, VALID_FROM, TO_CURRENCY, EXCHANGE_RATE
  from tmp_INT_EXCHANGE_RATE;

-- ============================================================
--   Table: INT_SUBS_ACCOUNT                                   
-- ============================================================
insert into INT_SUBS_ACCOUNT
  ( ACCOUNT, TARIFFMODEL_CODE, PERIOD, DISCOUNTSTEP,
    DISCOUNTMASTER, STATUS, ROLLOVER_UNITS,
    SUM_CHARGE, SUM_QUANTITY, SUM_VOL_SENT, SUM_VOL_RECEIVED,
    SUM_EVENT, FRAME_CHARGE, FRAME_QUANTITY, FRAME_VOL_SENT,
    FRAME_VOL_RECEIVED, FRAME_EVENT, DISC_AMOUNT, 
    DISC_QUANTITY, DISC_VOL_SENT, DISC_VOL_RECEIVED )
  select ACCOUNT, TARIFFMODEL_CODE, PERIOD, DISCOUNTSTEP,
    DISCOUNTMASTER, STATUS, 0,
    SUM_CHARGE, SUM_QUANTITY, SUM_VOL_SENT, SUM_VOL_RECEIVED,
    SUM_EVENT, FRAME_CHARGE, FRAME_QUANTITY, FRAME_VOL_SENT,
    FRAME_VOL_RECEIVED, FRAME_EVENT, DISC_AMOUNT, 
    DISC_QUANTITY, DISC_VOL_SENT, DISC_VOL_RECEIVED
  from tmp_INT_SUBS_ACCOUNT;

-- ============================================================
--   Table: INT_DBVERSION                                      
-- ============================================================
insert into INT_DBVERSION
  ( DBVERSION, DESCRIPTION, USERNAME, INSTALL_DATE )
  select DBVERSION, DESCRIPTION, USERNAME, INSTALL_DATE
  from tmp_INT_DBVERSION;

-- ============================================================
--   Table: INT_TAXGROUP                                      
-- ============================================================
insert into INT_TAXGROUP
  ( TAXGROUP, NAME )
  values
  ( 'NORM', 'Normal Taxgroup' );

-- ============================================================
--   Table: INT_TAXCODE
-- ============================================================
insert into INT_TAXCODE
  ( TAXCODE, NAME )
  select distinct substr( tmp_INT_TAX.TAXCODE, 1, 5 ), tmp_INT_TAX.TAXCODE
  from tmp_INT_TAX;
  
insert into INT_TAXCODE
  ( TAXCODE, NAME )
  values ( 'NORM', 'Normal Tax' );

-- ============================================================
--   Table: INT_TAX                                            
-- ============================================================
insert into INT_TAX
  ( TAXGROUP, TAXCODE, VALID_FROM, TAXRATE )
  select 'NORM', substr( tmp_INT_TAX.TAXCODE, 1, 5 ), tmp_INT_TAX.VALID_FROM, tmp_INT_TAX.TAXRATE
  from tmp_INT_TAX;
  
insert into INT_TAX
  ( TAXGROUP, TAXCODE, VALID_FROM, TAXRATE )
  values 
  ( 'NORM', 'NORM', to_date( '19900101', 'YYYYMMDD' ), 1600 );

-- ============================================================
--   Table: INT_ISCRIPT                                        
-- ============================================================
-- do not copy this table because no changes.

-- ============================================================
--   Table: IC_DAILY                                           
-- ============================================================
insert into IC_DAILY
  ( NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN,
    TRUNK, ICPRODUCT, BILLING_DIRECTION, ZONE, TIMEZONE,
    NUM_ITEMS, DURATION, ROUNDED_DURATION, VOLUME_SENT,
    VOLUME_RECEIVED, CHARGE_AMOUNT )
  select NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN,
    TRUNK, ICPRODUCT, BILLING_DIRECTION, ZONE, TIMEZONE,
    NUM_ITEMS, DURATION, ROUNDED_DURATION, VOLUME_SENT,
    VOLUME_RECEIVED, CHARGE_AMOUNT
  from tmp_IC_DAILY;

-- ============================================================
--   Table: IC_DAILY_ALTERNATE                                 
-- ============================================================
insert into IC_DAILY_ALTERNATE
  ( NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN,
    TRUNK, ICPRODUCT, BILLING_DIRECTION, ZONE, TIMEZONE,
    NUM_ITEMS, DURATION, ROUNDED_DURATION, VOLUME_SENT,
    VOLUME_RECEIVED, CHARGE_AMOUNT )
  select NETWORK_OPERATOR, DAY, SEQUENCE_NUMBER, BILLRUN,
    TRUNK, ICPRODUCT, BILLING_DIRECTION, ZONE, TIMEZONE,
    NUM_ITEMS, DURATION, ROUNDED_DURATION, VOLUME_SENT,
    VOLUME_RECEIVED, CHARGE_AMOUNT
  from tmp_IC_DAILY_ALTERNATE;

-- ============================================================
--   Table: INT_DESTINATIONDESC                                
-- ============================================================
insert into INT_DESTINATIONDESC
  ( AREACODE, TYPE, NAME )
  select AREACODE, TYPE, NAME
  from tmp_INT_DESTINATIONDESC;

-- ============================================================
--   Table: INT_TIMEMODEL                                      
-- ============================================================
insert into INT_TIMEMODEL
  ( TIMEMODEL, CODE, NAME )
  select TIMEMODEL, CODE, NAME
  from tmp_INT_TIMEMODEL;

-- ============================================================
--   Table: INT_CONTENTPROVIDER                                
-- ============================================================
insert into INT_CONTENTPROVIDER
  ( CONTENTPROVIDER, CODE, NAME, CURRENCY, TAXGROUP )
  select CONTENTPROVIDER, CODE, NAME, CURRENCY, 'NORM'
  from tmp_INT_CONTENTPROVIDER;

-- ============================================================
--   Table: INT_DAYCODE                                        
-- ============================================================
insert into INT_DAYCODE
  ( DAYCODE, CODE, NAME, DATEDAY,
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, 
    SATURDAY, SUNDAY, HOLIDAY )
  select DAYCODE, CODE, NAME, DATEDAY,
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, 
    SATURDAY, SUNDAY, HOLIDAY
  from tmp_INT_DAYCODE;

-- ============================================================
--   Table: INT_SPECIALDAYRATE                                 
-- ============================================================
insert into INT_SPECIALDAYRATE
  ( SPECIALDAYRATE, NAME, VALID_FROM, VALID_TO,
    TIME_FROM, TIME_TO, DISCOUNT_TYPE, DISCOUNT_VALUE )
  select SPECIALDAYRATE, NAME, VALID_FROM, VALID_TO,
    TIME_FROM, TIME_TO, DISCOUNT_TYPE, DISCOUNT_VALUE
  from tmp_INT_SPECIALDAYRATE;

-- ============================================================
--   Table: INT_PRICEMODEL                                     
-- ============================================================
insert into INT_PRICEMODEL
  ( PRICEMODEL, CODE, NAME )
  select PRICEMODEL, CODE, NAME
  from tmp_INT_PRICEMODEL;

-- ============================================================
--   Table: INT_ZONE                                           
-- ============================================================
insert into INT_ZONE
  ( ZONE, RESULT, NAME )
  select to_char( ZONE ), RESULT, NAME
  from tmp_INT_ZONE;

-- ============================================================
--   Table: INT_TIMEINTERVAL                                   
-- ============================================================
insert into INT_TIMEINTERVAL
  ( INTERVAL, CODE, NAME, TIME_FROM, TIME_TO )
  select INTERVAL, CODE, NAME, TIME_FROM, TIME_TO
  from tmp_INT_TIMEINTERVAL;

-- ============================================================
--   Table: INT_TIMEZONE                                       
-- ============================================================
insert into INT_TIMEZONE
  ( TIMEZONE, CODE, NAME, TIMEZONE_VALUE )
  select TIMEZONE, CODE, NAME, TIMEZONE_VALUE
  from tmp_INT_TIMEZONE;
  
-- ============================================================
--   Table: INT_SEGMENT                                        
-- ============================================================
insert into INT_SEGMENT
  ( SEGMENT, NAME )
  select SEGMENT, NAME
  from tmp_INT_SEGMENT;
  
-- ============================================================
--   Table: INT_EDRFORMAT                                      
-- ============================================================
insert into INT_EDRFORMAT
  ( EDR_FORMAT, NAME, SEQ_NUMBER, SEQ_ORIGNUMBER,
    SEQ_OFFSET, SEQ_MAXSEQUENCE, SEQ_MAXOFFSET,
    SEQ_MINSEQUENCE, SEQ_MINOFFSET )
  select EDR_FORMAT, NAME, SEQ_NUMBER, SEQ_ORIGNUMBER,
    SEQ_OFFSET, SEQ_MAXSEQUENCE, SEQ_MAXOFFSET,
    SEQ_MINSEQUENCE, SEQ_MINOFFSET
  from tmp_INT_EDRFORMAT;

-- ============================================================
--   Table: INT_GEOGRAPHICALMODEL                              
-- ============================================================
insert into INT_GEOGRAPHICALMODEL
  ( GEOMODEL, NAME, STATUS )
  select GEOMODEL, NAME, STATUS
  from tmp_INT_GEOGRAPHICALMODEL;

-- ============================================================
--   Table: INT_REVENUEGROUP
-- ============================================================
insert into INT_REVENUEGROUP
  ( REVENUEGROUP, NAME )
  values ( 'DEF', 'Default Revenue' );

-- ============================================================
--   Table: INT_GLACCOUNT
-- ============================================================
insert into INT_GLACCOUNT
  ( GLACCOUNT, NAME, TAXCODE, GLA_TYPE )
  select distinct TAXCODE, TAXCODE, substr( TAXCODE, 1, 5 ), 'R'
  from tmp_INT_TAX;
  
insert into INT_GLACCOUNT
  ( GLACCOUNT, NAME, TAXCODE, GLA_TYPE )
  values ( 'DEF', 'Default Usage Receipts', 'NORM', 'R' );

-- ============================================================
--   Table: INT_UOM
-- ============================================================
insert into INT_UOM
  ( UOM, NAME )
  select distinct UOM, UOM
  from tmp_INT_SERVICE;
  
insert into INT_UOM
  ( UOM, NAME )
  select distinct GRANT_UOM, GRANT_UOM
  from tmp_INT_DISCOUNTSTEP
  where tmp_INT_DISCOUNTSTEP.GRANT_UOM not in ( select UOM from INT_UOM );
  
-- ============================================================
--   Table: INT_SERVICE                                        
-- ============================================================
insert into INT_SERVICE
  ( SERVICECODE, NAME, RANK, UOM_Q, UOM_S, UOM_R, TOS,
    CHARGE_ITEM, DEF_GLACCOUNT, DEF_REVENUEGROUP,
    PARENT_SERVICE, BASIC )
  select SERVICECODE, NAME, RANK, UOM, UOM, UOM, TOS,
    CHARGE_ITEM, 'DEF', 'DEF', PARENT_SERVICE, BASIC
  from tmp_INT_SERVICE
  where PARENT_SERVICE is null;

insert into INT_SERVICE
  ( SERVICECODE, NAME, RANK, UOM_Q, UOM_S, UOM_R, TOS,
    CHARGE_ITEM, DEF_GLACCOUNT, DEF_REVENUEGROUP,
    PARENT_SERVICE, BASIC )
  select SERVICECODE, NAME, RANK, UOM, UOM, UOM, TOS,
    CHARGE_ITEM, 'DEF', 'DEF', PARENT_SERVICE, BASIC
  from tmp_INT_SERVICE
  where PARENT_SERVICE is not null;

-- ============================================================
--   Table: INT_CALLCLASS                                      
-- ============================================================
insert into INT_CALLCLASS
  ( CALLCLASS, NAME )
  select CALLCLASS, NAME
  from tmp_INT_CALLCLASS;

-- ============================================================
--   Table: INT_CALENDAR                                       
-- ============================================================
insert into INT_CALENDAR
  ( CALENDAR, NAME )
  select CALENDAR, NAME
  from tmp_INT_CALENDAR;
  
insert into INT_CALENDAR
  ( CALENDAR, NAME )
  select CALENDAR, to_char( CALENDAR )
  from tmp_INT_TARIFFMODEL
  where tmp_INT_TARIFFMODEL.CALENDAR not in ( select CALENDAR from INT_CALENDAR );

-- ============================================================
--   Table: INT_DISCOUNTMODEL                                  
-- ============================================================
insert into INT_DISCOUNTMODEL
  ( DISCOUNTMODEL, CODE, NAME, PERIOD )
  select DISCOUNTMODEL, CODE, NAME, PERIOD
  from tmp_INT_DISCOUNTMODEL;

-- ============================================================
--   Table: INT_DISCOUNTRULE                                   
-- ============================================================
insert into INT_DISCOUNTRULE
  ( DISCOUNTRULE, CODE, NAME )
  select DISCOUNTRULE, CODE, NAME
  from tmp_INT_DISCOUNTRULE;

-- ============================================================
--   Table: INT_DISCOUNTMASTER                                 
-- ============================================================
insert into INT_DISCOUNTMASTER
  ( DISCOUNTMASTER, CODE, NAME )
  select DISCOUNTMASTER, CODE, NAME
  from tmp_INT_DISCOUNTMASTER;

-- ============================================================
--   Table: INT_SUBS_BILLCYCLE                                 
-- ============================================================
insert into INT_SUBS_BILLCYCLE
  ( BILLCYCLE, END_OF_CYCLE, BILLPERIOD )
  select BILLCYCLE, END_OF_CYCLE, BILLPERIOD
  from tmp_INT_SUBS_BILLCYCLE;

-- ============================================================
--   Table: INT_CALLTYPE                                       
-- ============================================================
insert into INT_CALLTYPE
  ( CALLTYPE, NAME )
  select CALLTYPE, NAME
  from tmp_INT_CALLTYPE;

-- ============================================================
--   Table: INT_DISCOUNTTRIGGER                                
-- ============================================================
insert into INT_DISCOUNTTRIGGER
  ( DISCOUNTTRIGGER, CODE, NAME )
  select DISCOUNTTRIGGER, CODE, NAME
  from tmp_INT_DISCOUNTTRIGGER;

-- ============================================================
--   Table: INT_RULESET                                        
-- ============================================================
-- do not copy this table because no changes.

-- ============================================================
--   Table: INT_RULE                                           
-- ============================================================
-- do not copy this table because no changes.

-- ============================================================
--   Table: INT_APN_GROUP
-- ============================================================
insert into INT_APN_GROUP
  ( APN_GROUP, NAME )
  values ( 'DEFAULT', 'Default APN Group' );

-- ============================================================
--   Table: INT_ZONEMODEL                                      
-- ============================================================
insert into INT_ZONEMODEL
  ( ZONEMODEL, CODE, NAME, MODELTYPE, 
    FRAME, STATUS, APN_GROUP, GEOMODEL )
  select ZONEMODEL, CODE, NAME, MODELTYPE, 
    FRAME, STATUS, 'DEFAULT', GEOMODEL
  from tmp_INT_ZONEMODEL;

-- ============================================================
--   Table: INT_SUBSSERVICE_MAP                                
-- ============================================================
insert into INT_SUBSSERVICE_MAP
  ( SUBS_SERVICECODE, INT_SERVICECODE, NAME )
  select SUBS_SERVICECODE, INT_SERVICECODE, NAME
  from tmp_INT_SUBSSERVICE_MAP;

-- ============================================================
--   Table: INT_SERVICECLASS                                   
-- ============================================================
insert into INT_SERVICECLASS
  ( SERVICECODE, SERVICECLASS, NAME )
  select SERVICECODE, SERVICECLASS, NAME
  from tmp_INT_SERVICECLASS;

insert into INT_SERVICECLASS
  ( SERVICECODE, SERVICECLASS, NAME ) 
  select distinct INT_SERVICECODE, '*', concat( INT_SERVICECODE, '*' )  
  from tmp_INT_SERVICECODE_MAP, INT_SERVICECLASS
  where INT_SERVICECLASS.SERVICECODE != tmp_INT_SERVICECODE_MAP.INT_SERVICECODE and
      INT_SERVICECLASS.SERVICECLASS != '*';

insert into INT_SERVICECLASS
  ( SERVICECODE, SERVICECLASS )
  select distinct SERVICECODE, SERVICECLASS 
  from tmp_INT_TARIFFMODEL_CNF
  where SERVICECODE in ( select SERVICECODE from INT_SERVICE )
  minus
  select SERVICECODE, SERVICECLASS from INT_SERVICECLASS;

insert into INT_SERVICECLASS
  ( SERVICECODE, SERVICECLASS )
  select distinct INT_SERVICECODE, '*' from tmp_INT_SERVICECODE_MAP
  minus
  select SERVICECODE, SERVICECLASS from INT_SERVICECLASS;

-- ============================================================
--   Table: INT_SYSTEM_BRAND
-- ============================================================
insert into INT_SYSTEM_BRAND
  ( SYSTEM_BRAND, NAME, ACTIVE )
  select substr( to_char( SPECIALISTSYSTEM ), 1, 5 ),
    NAME, ACTIVE
  from tmp_INT_SPECIALISTSYSTEM;
  
insert into INT_SYSTEM_BRAND
  ( SYSTEM_BRAND, NAME, ACTIVE )
  values ( 'DEF', 'Default System-Brand', 1 );

-- ============================================================
--   Table: INT_TARIFFMODEL                                    
-- ============================================================
insert into INT_TARIFFMODEL
  ( TARIFFMODEL, CODE, NAME, STATUS, 
    SYSTEM_BRAND, MODELTYPE, SPLITTING, CALENDAR,
    UTC_TIME_OFFSET, CURRENCY, TAXTREATMENT )
  select TARIFFMODEL, CODE, NAME, STATUS, 
    'DEF', MODELTYPE, SPLITTING, 
    NVL( CALENDAR, ( select min(calendar) from INT_CALENDAR ) ),
    UTC_TIME_OFFSET, CURRENCY, TAXTREATMENT
  from tmp_INT_TARIFFMODEL;

-- ============================================================
--   Table: INT_SUBSTARIFF_MAP                                 
-- ============================================================
insert into INT_SUBSTARIFF_MAP
  ( SUBS_TARIFFMODEL, INT_TARIFFMODEL, NAME )
  select SUBS_TARIFFMODEL, INT_TARIFFMODEL, NAME
  from tmp_INT_SUBSTARIFF_MAP;

-- ============================================================
--   Table: INT_CONTENT                                        
-- ============================================================
insert into INT_CONTENT
  ( CONTENTPROVIDER, CONTENTCODE, VALID_FROM, VALID_TO,
    NAME, TARIFFMODEL, SHARRING, CURRENCY, GLACCOUNT )
  select CONTENTPROVIDER, CONTENTCODE, VALID_FROM, VALID_TO,
    NAME, TARIFFMODEL, SHARRING, CURRENCY, 'DEF'
  from tmp_INT_CONTENT;

-- ============================================================
--   Table: INT_TARIFFMODEL_VER                                
-- ============================================================
insert into INT_TARIFFMODEL_VER
  ( TARIFFMODEL, VERSION, VALID_FROM, STATUS,
    ZONEMODEL, BASIC_TARIFFMODEL, BASIC_VERSION,
    BASIC, DISCOUNTMODEL )
  select TARIFFMODEL, VERSION, VALID_FROM, STATUS,
    ZONEMODEL, BASIC_TARIFFMODEL, BASIC_VERSION,
    BASIC, DISCOUNTMODEL
  from tmp_INT_TARIFFMODEL_VER  
  where zonemodel in ( select zonemodel from INT_ZONEMODEL );

-- ============================================================
--   Table: INT_SUBS_CONTRACT                                  
-- ============================================================
insert into INT_SUBS_CONTRACT
  ( CONTRACT, SYSTEM_BRAND, SKELETON,
    CUSTOMER, SUBSCRIBER, DEALER, ACTIVATED_DATE,
    CONTRACT_PERIOD, SUBS_TAXGROUP, SUBS_CURRENCY, 
    SUBS_BIRTHDAY, SUBS_QUALITY, SUBS_CLASS, SUBS_TYPE )
  select CONTRACT, substr( to_char( SPECIALISTSYSTEM ), 1, 5 ), SKELETON,
    CUSTOMER, SUBSCRIBER, DEALER, ACTIVATED_DATE,
    CONTRACT_PERIOD, 'NORM', 
    ( select CURRENCY from INT_CURRENCY where rownum <= 1 ), 
    SUBS_BIRTHDAY, SUBS_QUALITY, SUBS_CLASS, SUBS_TYPE
  from tmp_INT_SUBS_CONTRACT;

-- ============================================================
--   Table: INT_DISCOUNTMDL_VER                                
-- ============================================================
insert into INT_DISCOUNTMDL_VER
  ( DISCOUNTMODEL, VERSION, VALID_FROM, STATUS )
  select DISCOUNTMODEL, VERSION, VALID_FROM, STATUS
  from tmp_INT_DISCOUNTMDL_VER;

-- ============================================================
--   Table: INT_SUBSDISCOUNT_MAP                               
-- ============================================================
insert into INT_SUBSDISCOUNT_MAP
  ( SUBS_DISCOUNTMODEL, INT_DISCOUNTMODEL, NAME )
  select SUBS_DISCOUNTMODEL, INT_DISCOUNTMODEL, NAME
  from tmp_INT_SUBSDISCOUNT_MAP;

-- ============================================================
--   Table: INT_MAP_GROUP
-- ============================================================
insert into INT_MAP_GROUP
  ( MAP_GROUP, NAME )
  select EDR_FORMAT, NAME
  from INT_EDRFORMAT;

-- ============================================================
--   Table: INT_CALLTYPE_MAP                                   
-- ============================================================
insert into INT_CALLTYPE_MAP
  ( MAP_GROUP, RANK, CALLTYPE, NAME, COMPAREPATTERN )
  select EDR_FORMAT, RANK, CALLTYPE, NAME, COMPAREPATTERN
  from tmp_INT_CALLTYPE_MAP;

-- ============================================================
--   Table: INT_CZT_GROUP
-- ============================================================
insert into INT_CZT_GROUP
  ( CZT_GROUP, CZT_NAME )
  values ( 'DEF_GROUP', 'Default CZT Group' );

-- ============================================================
--   Table: INT_CLASSTYPEZONE_MAP                              
-- ============================================================
insert into INT_CLASSTYPEZONE_MAP
  ( CZT_GROUP, ZONEMODEL, RANK, VALID_FROM, VALID_TO,
    TIME_FROM, TIME_TO, QUANTITY_VALUE,
    MIN_AOC_AMOUNT, MAX_AOC_AMOUNT, CALLCLASS, CALLTYPE,
    SERVICECODE, SERVICECLASS, ZONE_WS, ZONE_RT, 
    NEW_CALLTYPE, NEW_ZONE_WS, NEW_ZONE_RT, NAME )
  select 'DEF_GROUP', ZONEMODEL, RANK, VALID_FROM, VALID_TO,
    TIME_FROM, TIME_TO, QUANTITY_VALUE,
    MIN_AOC_AMOUNT, MAX_AOC_AMOUNT, CALLCLASS, CALLTYPE,
    SERVICECODE, '*', ZONE_WS, ZONE_RT, 
    NEW_CALLTYPE, NEW_ZONE_WS, NEW_ZONE_RT, NAME
  from tmp_INT_CLASSTYPEZONE_MAP;

-- ============================================================
--   Table: INT_PRICEMODEL_STEP                                
-- ============================================================
insert into INT_PRICEMODEL_STEP
  ( PRICEMODEL, VALID_FROM, CHARGE_ITEM, STEP,
    THRESHOLD_FROM, THRESHOLD_TO, BEAT,
    CHARGE, CHARGE_BASE, FRAME )
  select PRICEMODEL, VALID_FROM, CHARGE_ITEM, STEP,
    THRESHOLD_FROM, THRESHOLD_TO, BEAT,
    CHARGE, CHARGE_BASE, FRAME
  from tmp_INT_PRICEMODEL_STEP;

-- ============================================================
--   Table: INT_HOLIDAY                                        
-- ============================================================
insert into INT_HOLIDAY
  ( CALENDAR, HOLIDAY, RECURRING, NAME )
  select CALENDAR, HOLIDAY, RECURRING, NAME
  from tmp_INT_HOLIDAY;

-- ============================================================
--   Table: INT_TARIFFMODEL_CNF                                
-- ============================================================
insert into INT_TARIFFMODEL_CNF
  ( TARIFFMODEL, VERSION, SERVICECODE, SERVICECLASS,
    ZONE, TIMEMODEL, TIMEZONE, PRICEMODEL, ALT_PRICEMODEL,
    PASSTHROUGH, ADDON_TYPE, ADDON_CHARGE,
    GLACCOUNT, REVENUEGROUP )
  select TARIFFMODEL, VERSION, SERVICECODE, SERVICECLASS,
    ZONE, TIMEMODEL, TIMEZONE, PRICEMODEL, ALT_PRICEMODEL,
    PASSTHROUGH, ADDON_TYPE, ADDON_CHARGE,
    'DEF', 'DEF'
  from tmp_INT_TARIFFMODEL_CNF
  where TARIFFMODEL in ( select TARIFFMODEL from INT_TARIFFMODEL_VER 
                         where tariffmodel = tmp_INT_TARIFFMODEL_CNF.TARIFFMODEL and 
                               version = tmp_INT_TARIFFMODEL_CNF.VERSION ) and
        VERSION in ( select VERSION from INT_TARIFFMODEL_VER 
                     where tariffmodel = tmp_INT_TARIFFMODEL_CNF.TARIFFMODEL and 
                           version = tmp_INT_TARIFFMODEL_CNF.VERSION ) and
        TIMEMODEL in ( select TIMEMODEL from INT_TIMEMODEL ) and
        TIMEZONE in ( select TIMEZONE from INT_TIMEMODEL_LNK
                      where TIMEMODEL = tmp_INT_TARIFFMODEL_CNF.TIMEMODEL ) and
        PRICEMODEL in ( select PRICEMODEL from INT_PRICEMODEL ) and
        SERVICECODE in ( select SERVICECODE from INT_SERVICE );

-- ============================================================
--   Table: INT_SPECIALDAY_LNK                                 
-- ============================================================
insert into INT_SPECIALDAY_LNK
  ( TARIFFMODEL, VERSION, SPECIALDAYRATE )
  select TARIFFMODEL, VERSION, SPECIALDAYRATE
  from tmp_INT_SPECIALDAY_LNK;

-- ============================================================
--   Table: INT_TIMEMODEL_LNK                                  
-- ============================================================
insert into INT_TIMEMODEL_LNK
  ( TIMEMODEL, DAYCODE, INTERVAL, VALID_FROM, TIMEZONE, VALID_TO )
  select TIMEMODEL, DAYCODE, INTERVAL, VALID_FROM, TIMEZONE, VALID_TO
  from tmp_INT_TIMEMODEL_LNK;

-- ============================================================
--   Table: INT_STANDARD_ZONE                                  
-- ============================================================
insert into INT_STANDARD_ZONE
  ( ZONEMODEL, ORIGIN_AREACODE, DESTIN_AREACODE,
    SERVICECODE, VALID_FROM, VALID_TO,
    ZONE_WS, ZONE_RT, NAME, ALT_ZONEMODEL )
  select ZONEMODEL, ORIGIN_AREACODE, DESTIN_AREACODE,
    SERVICECODE, VALID_FROM, VALID_TO,
    ZONE_WS, ZONE_RT, NAME, ALT_ZONEMODEL
  from tmp_INT_STANDARD_ZONE
  where ZONEMODEL in ( select ZONEMODEL from INT_ZONEMODEL ) and
        SERVICECODE in ( select SERVICECODE from INT_SERVICE ) and
        to_char( ZONE_WS ) in ( select ZONE from INT_ZONE ) and
        to_char( ZONE_RT ) in ( select ZONE from INT_ZONE );

-- ============================================================
--   Table: INT_GEOGRAPHICAL_ZONE                              
-- ============================================================
insert into INT_GEOGRAPHICAL_ZONE
  ( ZONEMODEL, DISTANCE, SERVICECODE, VALID_FROM, 
    VALID_TO, ZONE_WS, ZONE_RT, NAME, ALT_ZONEMODEL )
  select ZONEMODEL, DISTANCE, SERVICECODE, VALID_FROM, 
    VALID_TO, ZONE_WS, ZONE_RT, NAME, ALT_ZONEMODEL
  from tmp_INT_GEOGRAPHICAL_ZONE
  where ZONEMODEL in ( select ZONEMODEL from INT_ZONEMODEL ) and
      SERVICECODE in ( select SERVICECODE from INT_SERVICE ) and
    to_char( ZONE_WS ) in ( select ZONE from INT_ZONE ) and
    to_char( ZONE_RT ) in ( select ZONE from INT_ZONE );

-- ============================================================
--   Table: INT_SEGZONE_LNK                                    
-- ============================================================
insert into INT_SEGZONE_LNK
  ( SEGMENT, VALID_FROM, ZONEMODEL, VALID_TO )
  select SEGMENT, VALID_FROM, ZONEMODEL, VALID_TO
  from tmp_INT_SEGZONE_LNK;

-- ============================================================
--   Table: INT_GEOAREACODE_LNK                                
-- ============================================================
insert into INT_GEOAREACODE_LNK
  ( GEOMODEL, AREACODE, NAME, LONGITUDE, LATITUDE )
  select GEOMODEL, AREACODE, NAME, LONGITUDE, LATITUDE
  from tmp_INT_GEOAREACODE_LNK;

-- ============================================================
--   Table: INT_SERVICECODE_MAP                                
-- ============================================================
insert into INT_SERVICECODE_MAP
  ( MAP_GROUP, RANK, NAME, EXT_SERVICECODE, CALLCLASS, 
    LOCARIND_VASEVENT, QOS_REQUESTED, QOS_USED, 
    RECORDTYPE, INT_SERVICECODE, INT_SERVICECLASS )
  select EDR_FORMAT, RANK, NAME, EXT_SERVICECODE, CALLCLASS, 
    LOCARIND_VASEVENT, QOS_REQUESTED, QOS_USED, 
    RECORDTYPE, INT_SERVICECODE, '*'
  from tmp_INT_SERVICECODE_MAP;

-- ============================================================
--   Table: INT_CALLCLASS_MAP                                  
-- ============================================================
insert into INT_CALLCLASS_MAP
  ( MAP_GROUP, RANK, EXT_CALLCLASS, CALLTYPE, AOCZONE,
    TARIFFCLASS, TARIFFSUBCLASS, RECORDTYPE, CONNECTTYPE,
    CONNECTSUBTYPE, APPLICATION, TRANSIT_AREACODE,
    NAME, INT_CALLCLASS )
  select EDR_FORMAT, RANK, EXT_CALLCLASS, CALLTYPE, AOCZONE,
    TARIFFCLASS, TARIFFSUBCLASS, RECORDTYPE, CONNECTTYPE,
    CONNECTSUBTYPE, APPLICATION, TRANSIT_AREACODE,
    NAME, INT_CALLCLASS
  from tmp_INT_CALLCLASS_MAP;

-- ============================================================
--   Table: INT_SUBS_LOCAL                                     
-- ============================================================
insert into INT_SUBS_LOCAL
  ( CONTRACT, VALID_FROM, DESTIN_CLI, VALID_TO, CLITYPE )
  select CONTRACT, VALID_FROM, DESTIN_CLI, VALID_TO, CLITYPE
  from tmp_INT_SUBS_LOCAL;

-- ============================================================
--   Table: INT_TARIFFDISCOUNT_LNK                             
-- ============================================================
insert into INT_TARIFFDISCOUNT_LNK
  ( TARIFFMODEL, VERSION, RANK, VALID_FROM, VALID_TO,
    TIME_FROM, TIME_TO, QUANTITY_VALUE, CALLCLASS,
    CALLTYPE, SERVICECODE, SERVICECLASS, ZONE, 
    SOURCE_NETWORK, DESTIN_NETWORK, DISCOUNT_TYPE, 
    DISCOUNT_VALUE, NAME )
  select TARIFFMODEL, VERSION, RANK, VALID_FROM, VALID_TO,
    TIME_FROM, TIME_TO, QUANTITY_VALUE, CALLCLASS,
    CALLTYPE, SERVICECODE, '*', 
    ZONE, SOURCE_NETWORK, DESTIN_NETWORK, 
    DISCOUNT_TYPE, DISCOUNT_VALUE, NAME
  from tmp_INT_TARIFFDISCOUNT_LNK;

-- ============================================================
--   Table: INT_SEGTARIFF_LNK                                  
-- ============================================================
insert into INT_SEGTARIFF_LNK
  ( SEGMENT, VALID_FROM, TARIFFMODEL, VALID_TO )
  select SEGMENT, VALID_FROM, TARIFFMODEL, VALID_TO
  from tmp_INT_SEGTARIFF_LNK;

-- ============================================================
--   Table: INT_EDRSEQLOG                                      
-- ============================================================
insert into INT_EDRSEQLOG
  ( EDR_FORMAT, ORIG_SEQNO, NEW_SEQNO, PROCESSED,
    STATUS, RECYCLING, NUM_REC_IN, NUM_REC_OUT,
    NUM_REC_WARN, DURATION, SUM_QUANTITY, SUM_CHARGE,
    SUM_AOC, PROCESSEDBY_FORMAT, STREAMNAME_IN )
  select EDR_FORMAT, ORIG_SEQNO, NEW_SEQNO, PROCESSED,
    STATUS, RECYCLING, NUM_REC_IN, NUM_REC_OUT,
    NUM_REC_WARN, DURATION, SUM_QUANTITY, SUM_CHARGE,
    SUM_AOC, PROCESSEDBY_FORMAT, STREAMNAME_IN
  from tmp_INT_EDRSEQLOG;

-- ============================================================
--   Table: INT_SPLITTING_TYPE                                 
-- ============================================================
insert into INT_SPLITTING_TYPE
  ( EDR_FORMAT, RANK, VALID_FROM, VALID_TO,
    RECORDTYPE, SERVICECODE, CALLCLASS, SOURCE_NETWORK,
    DESTIN_NETWORK, SWITCH, TRUNK_IN, TRUNK_OUT,
    ORIGIN_AREACODE, DESTIN_AREACODE, TRANSIT_AREACODE,
    SYSTEM_BRAND, NAME )
  select EDR_FORMAT, RANK, VALID_FROM, VALID_TO,
    NVL( RECORDTYPE, '*' ), NVL( SERVICECODE, '*' ), 
  NVL( CALLCLASS, '*' ), NVL( SOURCE_NETWORK, '*' ),
    NVL( DESTIN_NETWORK, '*' ), NVL( SWITCH, '*' ), 
  NVL( TRUNK_IN, '*' ), NVL( TRUNK_OUT, '*' ),
    NVL( ORIGIN_AREACODE, '*' ), NVL( DESTIN_AREACODE, '*' ), NVL( TRANSIT_AREACODE, '*' ),
    substr( to_char( SPECIALISTSYSTEM ), 1, 5 ), NAME
  from tmp_INT_SPLITTING_TYPE;

-- ============================================================
--   Table: INT_SUBS_CLI                                       
-- ============================================================
insert into INT_SUBS_CLI
  ( CLI, VALID_FROM, VALID_TO, SERVICECODE,
    CONTRACT, MAPPING_CLI, DXXX )
  select CLI, VALID_FROM, VALID_TO, SERVICECODE,
    CONTRACT, MAPPING_CLI, DXXX
  from tmp_INT_SUBS_CLI
  where CONTRACT in ( select CONTRACT from INT_SUBS_CONTRACT );

-- ============================================================
--   Table: INT_SUBS_CONTRACT_HIST                             
-- ============================================================
insert into INT_SUBS_CONTRACT_HIST
  ( CONTRACT, VALID_FROM, VALID_TO, BILLCYCLE, SEGMENT,
    RATEPLAN, TARIFFMODEL, TARIFFINDICATOR, 
    SLA_CODE, DISCOUNTMODEL )
  select CONTRACT, VALID_FROM, VALID_TO, BILLCYCLE, SEGMENT,
    NULL, TARIFFMODEL, TARIFFINDICATOR, 
    NULL, DISCOUNTMODEL
  from tmp_INT_SUBS_CONTRACT_HIST;

-- ============================================================
--   Table: INT_DISCOUNTMDL_CNF                                
-- ============================================================
insert into INT_DISCOUNTMDL_CNF
  ( DISCOUNTCONFIG, DISCOUNTMODEL, VERSION, RANK,
    DISCOUNTTRIGGER, DISCOUNTRULE )
  select DISCOUNTCONFIG, DISCOUNTMODEL, VERSION, RANK,
    DISCOUNTTRIGGER, DISCOUNTRULE
  from tmp_INT_DISCOUNTMDL_CNF;

-- ============================================================
--   Table: INT_DISCOUNTSTEP                                   
-- ============================================================
insert into INT_DISCOUNTSTEP
  ( DISCOUNTSTEP, DISCOUNTRULE, RANK, DISCOUNTMASTER,
    THRESHOLD_TYPE, THRESHOLD_FROM, THRESHOLD_TO,
    DISCOUNT_TYPE, GRANT_TYPE, GRANT_UNITS, GRANT_BEAT,
    GRANT_UOM, ROLLOVER_UNITS, EDR_ENRICHMENT )
  select DISCOUNTSTEP, DISCOUNTRULE, RANK, DISCOUNTMASTER,
    THRESHOLD_TYPE, THRESHOLD_FROM, THRESHOLD_TO,
    DISCOUNT_TYPE, GRANT_TYPE, GRANT_UNITS, GRANT_BEAT,
    GRANT_UOM, 0, EDR_ENRICHMENT
  from tmp_INT_DISCOUNTSTEP;

-- ============================================================
--   Table: INT_DISCOUNTDETAIL                                 
-- ============================================================
insert into INT_DISCOUNTDETAIL
  ( DISCOUNTMASTER, RANK, VALID_FROM, VALID_TO, TIME_FROM, 
    TIME_TO, ZONEMODEL, ZONE, SERVICECODE, SERVICECLASS, 
    TIMEMODEL, TIMEZONE, PRICEMODEL, RECORDTYPE )
  select DISCOUNTMASTER, RANK, VALID_FROM, VALID_TO, TIME_FROM, 
    TIME_TO, ZONEMODEL, ZONE, SERVICECODE, SERVICECLASS, 
    TIMEMODEL, TIMEZONE, PRICEMODEL, RECORDTYPE
  from tmp_INT_DISCOUNTDETAIL;

-- ============================================================
--   Table: INT_SUBS_BILLRUN                                   
-- ============================================================
insert into INT_SUBS_BILLRUN
  ( BILLRUN, BILLCYCLE, BOC_DATE, EOC_DATE, BILLRUN_DATE, STATUS )
  select BILLRUN, BILLCYCLE, BOC_DATE, EOC_DATE, BILLRUN_DATE, STATUS
  from tmp_INT_SUBS_BILLRUN;

-- ============================================================
--   Table: INT_NOSP                                           
-- ============================================================
insert into INT_NOSP
  ( MAP_GROUP, RANK, OLD_SOURCE, OLD_DESTINATION,
    A_PREFIX, NEW_SOURCE, NEW_DESTINATION )
  select EDR_FORMAT, RANK, OLD_SOURCE, OLD_DESTINATION,
    A_PREFIX, NEW_SOURCE, NEW_DESTINATION
  from tmp_INT_NOSP;

-- ============================================================
--   Table: INT_DISCOUNTCONDITION                              
-- ============================================================
  insert into INT_DISCOUNTCONDITION
  ( DISCOUNTCONDITION, DISCOUNTTRIGGER, DISCOUNTMASTER,
    CONDITION_BASE, CONDITION_VALUE )
  select DISCOUNTCONDITION, DISCOUNTTRIGGER, DISCOUNTMASTER,
    CONDITION_BASE, CONDITION_VALUE
  from tmp_INT_DISCOUNTCONDITION;

-- ============================================================
--   Table: INT_DISCARDING                                     
-- ============================================================
insert into INT_DISCARDING
  ( EDR_FORMAT, RANK, NAME, RECORDTYPE, SOURCE_NETWORK,
    CALL_COMPLETION, LONG_DURATION, CALLCLASS, SERVICECODE,
    SWITCH, TARIFFCLASS, TARIFFSUBCLASS, CONNECTTYPE,
    CONNECTSUBTYPE, B_NUMBER, MAX_AGE, AOC_NULL )
  select EDR_FORMAT, RANK, NAME, RECORDTYPE, SOURCE_NETWORK,
    CALL_COMPLETION, LONG_DURATION, CALLCLASS, SERVICECODE,
    SWITCH, TARIFFCLASS, TARIFFSUBCLASS, CONNECTTYPE,
    CONNECTSUBTYPE, B_NUMBER, MAX_AGE, AOC_NULL
  from tmp_INT_DISCARDING;

-- ============================================================
--   Table: INT_RULESETLIST                                    
-- ============================================================
-- do not copy this table because no changes.

-- ============================================================
--   Table: INT_RULEITEM                                       
-- ============================================================
-- do not copy this table because no changes.

-- ============================================================
--   Table: INT_TSC_GROUP
-- ============================================================
insert into INT_TSC_GROUP
  ( TSC_GROUP, TSC_NAME )
  values ( 'DEF', 'Default TSC Group' );
  
-- ============================================================
--   Table: INT_TARIFFSERVICECLASS                             
-- ============================================================
insert into INT_TARIFFSERVICECLASS
  ( TSC_GROUP, TARIFFMODEL, RANK, VALID_FROM, VALID_TO, QOS_REQUESTED, 
    QOS_USED, CALLCLASS, CALLTYPE, SERVICECODE, SERVICECLASS,
    ZONE, NEW_SERVICECODE, NEW_SERVICECLASS, NAME )
  select 'DEF', TARIFFMODEL, RANK, VALID_FROM, VALID_TO, '*', 
    '*', CALLCLASS, CALLTYPE, SERVICECODE, '*', 
    ZONE, NEW_SERVICECODE, NEW_SERVICECLASS, NAME
  from tmp_INT_TARIFFSERVICECLASS;

-- ============================================================
--   Table: INT_CONTENT_MAP                                    
-- ============================================================
insert into INT_CONTENT_MAP
  ( EDR_FORMAT, RANK, DESTIN_AREACODE, TRANSIT_AREACODE,
    CALLCLASS, SERVICECODE, VAS_CODE, APPLICATION,
    CONTENTPROVIDER, CONTENTCODE )
  select EDR_FORMAT, RANK, B_NUMBER, C_NUMBER,
    CALLCLASS, SERVICECODE, '*', APPLICATION,
    CONTENTPROVIDER, CONTENTCODE
  from tmp_INT_CONTENT_MAP;

-- ============================================================
--   Table: INT_NETWORKOPERATOR                                
-- ============================================================
insert into INT_NETWORKOPERATOR
  ( NO, CODE, NAME, NOTYPE, CAC, CIC, 
    PLMN_ID, TADIG, CURRENCY, TAXGROUP )
  select NO, CODE, NAME, NOTYPE, CAC, CIC, 
    PLMN_ID, TADIG, CURRENCY, 'NORM'
  from tmp_INT_NETWORKOPERATOR;

-- ============================================================
--   Table: INT_NOPRODUCT                                      
-- ============================================================
insert into INT_NOPRODUCT
  ( NO, PRODUCTCODE, NAME, CURRENCY, TAXCODE )
  select NO, PRODUCTCODE, NAME, CURRENCY, TAXCODE
  from tmp_INT_NOPRODUCT;

-- ============================================================
--   Table: INT_ICPRODUCT                                      
-- ============================================================
insert into INT_ICPRODUCT
  ( ICPRODUCT, VALID_FROM, NAME, ZONE_DIRECTION, ZONE_TYPE, 
    BILL_DIRECTION, BILL_TYPE, NO, 
    TARIFFMODEL, ALT_TARIFFMODEL, FIXCOST )
  select ICPRODUCT, to_date( '19900101', 'YYYYMMDD' ), 
    NAME, ZONE_DIRECTION, 'N', BILL_DIRECTION, 'C', NO, 
    TARIFFMODEL, ALT_TARIFFMODEL, FIXCOST
  from tmp_INT_ICPRODUCT;

-- ============================================================
--   Table: INT_ICNO_LNK
-- ============================================================
insert into INT_ICNO_LNK
  ( ICPRODUCT, NO, VALID_FROM, VALID_TO, 
    TARIFFMODEL, ALT_TARIFFMODEL )
  select ICPRODUCT, NO, VALID_FROM, NULL, 
    TARIFFMODEL, ALT_TARIFFMODEL
  from INT_ICPRODUCT;

-- ============================================================
--   Table: INT_NETWORKMODEL                                   
-- ============================================================
insert into INT_NETWORKMODEL
  ( NETWORKMODEL, CODE, NAME, CALCMODE, MODELTYPE,
    USE_SWITCH_FOR_IDENT, USE_FIXCOST, SYSTEM_BRAND, 
    TARIFFMODEL )
  select NETWORKMODEL, CODE, NAME, CALCMODE, MODELTYPE,
    USE_SWITCH_FOR_IDENT, USE_FIXCOST, NULL, 
    TARIFFMODEL
  from tmp_INT_NETWORKMODEL;

-- ============================================================
--   Table: INT_SWITCH                                         
-- ============================================================
insert into INT_SWITCH
  ( NETWORKMODEL, SWITCH, NAME, STATUS, NO )
  select NETWORKMODEL, SWITCH, NAME, 'A', NO
  from tmp_INT_SWITCH;

-- ============================================================
--   Table: INT_POI                                            
-- ============================================================
insert into INT_POI
  ( NETWORKMODEL, POI, NAME, AREACODE, 
    UTC_TIME_OFFSET, STATUS, SWITCH )
  select NETWORKMODEL, POI, NAME, AREACODE, 
    UTC_TIME_OFFSET, 'A', SWITCH
  from tmp_INT_POI;

-- ============================================================
--   Table: INT_TRUNK                                          
-- ============================================================
insert into INT_TRUNK
  ( NETWORKMODEL, TRUNK, NAME, TRUNKTYPE, STATUS, NO, POI )
  select NETWORKMODEL, TRUNK, NAME, TRUNKTYPE, 'A', NO, POI
  from tmp_INT_TRUNK;

-- ============================================================
--   Table: INT_POIAREA_LNK                                    
-- ============================================================
insert into INT_POIAREA_LNK
  ( NETWORKMODEL, POI, VALID_FROM, AREACODE, VALID_TO )
  select NETWORKMODEL, POI, VALID_FROM, AREACODE, VALID_TO
  from tmp_INT_POIAREA_LNK;

-- ============================================================
--   Table: INT_ICPRODUCT_GROUP
-- ============================================================
insert into INT_ICPRODUCT_GROUP
  ( NETWORKMODEL, ICPRODUCT_GROUP, NAME )
  select distinct NETWORKMODEL, concat( DIRECTION, TRUNK ), concat( DIRECTION, TRUNK )
  from tmp_INT_ICPRODUCT_CNF;

-- ============================================================
--   Table: INT_TRUNK_CNF
-- ============================================================
insert into INT_TRUNK_CNF
  ( NETWORKMODEL, DIRECTION, TRUNK, 
    VALID_FROM, VALID_TO, ICPRODUCT_GROUP )
  select distinct NETWORKMODEL, DIRECTION, TRUNK, 
    to_date( '19900101', 'YYYYMMDD' ), NULL, concat( DIRECTION, TRUNK )
  from tmp_INT_ICPRODUCT_CNF;

-- ============================================================
--   Table: INT_ICPRODUCT_CNF
-- ============================================================
insert into INT_ICPRODUCT_CNF
  ( NETWORKMODEL, ICPRODUCT_GROUP, RANK, 
    VALID_FROM, VALID_TO, NAME, SOURCE_NETWORK,
    DESTIN_NETWORK, ORIGIN_AREACODE, DESTIN_AREACODE,
    TRANSIT_AREACODE, RECORDTYPE, SERVICECODE, 
    CALLCLASS, ICPRODUCT )
  select NETWORKMODEL, concat( DIRECTION, TRUNK ), RANK, 
    to_date( '19900101', 'YYYYMMDD' ), NULL, NAME, SOURCE_NETWORK,
    DESTIN_NETWORK, ORIGIN_AREACODE, DESTIN_AREACODE,
    TRANSIT_AREACODE, '*', '*', '*', ICPRODUCT
  from tmp_INT_ICPRODUCT_CNF;

-- ============================================================
--   Table: INT_NOPRODUCT_CNF                                  
-- ============================================================
insert into INT_NOPRODUCT_CNF
  ( ICPRODUCT, TIMEZONE, ZONE, VALID_FROM, 
    VALID_TO, NO, PRODUCTCODE )
  select ICPRODUCT, TIMEZONE, ZONE, to_date( '19900101', 'YYYYMMDD' ), 
    NULL, NO, PRODUCTCODE
  from tmp_INT_NOPRODUCT_CNF;

-- ============================================================
--   Table: INT_NO_BILLRUN                                     
-- ============================================================
insert into INT_NO_BILLRUN
  ( NO, BILLRUN, BOC_DATE, EOC_DATE, BILLRUN_DATE, STATUS )
  select NO, BILLRUN, BOC_DATE, EOC_DATE, BILLRUN_DATE, STATUS
  from tmp_INT_NO_BILLRUN;

-- ============================================================
--   Table: INT_NETWORKMODEL
-- ============================================================
insert into INT_NETWORKMODEL
  ( NETWORKMODEL, CODE, NAME, CALCMODE, MODELTYPE, 
    USE_SWITCH_FOR_IDENT, USE_FIXCOST, SYSTEM_BRAND, TARIFFMODEL )
  select distinct INT_SEQ_NETWORKMODEL.nextval, EDR_FORMAT, 
    concat( EDR_FORMAT, ROAMING_TYPE ), 4, 'O', 
    0, 0, 'DEF', NULL
  from tmp_INT_RESELLER_LNK;

-- ============================================================
--   Table: INT_ICPRODUCT_GROUP
-- ============================================================
insert into INT_ICPRODUCT_GROUP
  ( NETWORKMODEL, ICPRODUCT_GROUP )
  select distinct ( select networkmodel 
                    from INT_NETWORKMODEL 
                    where name = concat ( EDR_FORMAT, ROAMING_TYPE ) ), 
    EDR_FORMAT
  from tmp_INT_RESELLER_LNK;

-- ============================================================
--   Table: INT_ICPRODUCT
-- ============================================================
insert into INT_ICPRODUCT
  ( ICPRODUCT, VALID_FROM,
    ZONE_DIRECTION, ZONE_TYPE, BILL_DIRECTION, BILL_TYPE,
    NO, TARIFFMODEL, ALT_TARIFFMODEL, FIXCOST )
  select distinct ( select CODE 
                    from INT_TARIFFMODEL 
                    where TARIFFMODEL = tmp_INT_RESELLER_LNK.TARIFFMODEL ),
    VALID_FROM, 'S', 'N', 'I', 'C', 
    ( select no from INT_NETWORKOPERATOR where rownum = 1 ),
    TARIFFMODEL, NULL, 0
  from tmp_INT_RESELLER_LNK;

-- ============================================================
--   Table: INT_ICPRODUCT_CNF
-- ============================================================
insert into INT_ICPRODUCT_CNF
  ( NETWORKMODEL, ICPRODUCT_GROUP, RANK, 
    VALID_FROM, VALID_TO, NAME, SOURCE_NETWORK,
    DESTIN_NETWORK, ORIGIN_AREACODE, DESTIN_AREACODE,
    TRANSIT_AREACODE, RECORDTYPE, SERVICECODE, 
    CALLCLASS, ICPRODUCT )
  select ( select networkmodel from INT_NETWORKMODEL where name = concat ( EDR_FORMAT, ROAMING_TYPE ) ),
    EDR_FORMAT, RANK, VALID_FROM, VALID_TO, NAME, 
    SOURCE_NETWORK, DESTIN_NETWORK, ORIGIN_AREACODE, 
    DESTIN_AREACODE, TRANSIT_AREACODE, RECORDTYPE, 
    SERVICECODE, CALLCLASS,
    ( select CODE 
      from INT_TARIFFMODEL 
      where TARIFFMODEL = tmp_INT_RESELLER_LNK.TARIFFMODEL )
  from tmp_INT_RESELLER_LNK;

-- ============================================================
--   Table: AGG_HOLIDAY                                        
-- ============================================================
insert into AGG_HOLIDAY
  ( HOLIDAY, NAME, RECURRING )
  select HOLIDAY, NAME, RECURRING
  from tmp_AGG_HOLIDAY;

-- ============================================================
--   Table: AGG_SCENARIO                                       
-- ============================================================
insert into AGG_SCENARIO
  ( SCENARIO_ID, CODE, NAME, VALID_FROM, VALID_TO,
    DEFAULT_TAB_NAME, DEFAULT_FLUSHMODE, DEFAULT_THRESHOLD,
    DEFAULT_TEMP_DIR, DEFAULT_DONE_DIR, DEFAULT_CTL_DIR,
    DEFAULT_FIELD_DELIMITER, SCENARIO_STATUS )
  select SCENARIO_ID, CODE, NAME, VALID_FROM, VALID_TO,
    DEFAULT_TAB_NAME, DEFAULT_FLUSHMODE, DEFAULT_THRESHOLD,
    DEFAULT_TEMP_DIR, DEFAULT_DONE_DIR, DEFAULT_CTL_DIR,
    DEFAULT_FIELD_DELIMITER, SCENARIO_STATUS
  from tmp_AGG_SCENARIO;

-- ============================================================
--   Table: AGG_CLASSITEM                                      
-- ============================================================
insert into AGG_CLASSITEM
  ( CLASSITEM_ID, CODE, NAME,
    CLASSITEM_DATATYPE, CLASSITEM_VALUE )
  select CLASSITEM_ID, CODE, NAME,
    CLASSITEM_DATATYPE, CLASSITEM_VALUE
  from tmp_AGG_CLASSITEM;

-- ============================================================
--   Table: AGG_CLASS                                          
-- ============================================================
insert into AGG_CLASS
  ( CLASS_ID, CODE, NAME, CLASS_DATATYPE )
  select CLASS_ID, CODE, NAME, CLASS_DATATYPE
  from tmp_AGG_CLASS;

-- ============================================================
--   Table: AGG_EDRFORMAT                                      
-- ============================================================
insert into AGG_EDRFORMAT
  ( FORMAT_ID, CODE, NAME, EDRFORMAT_STATUS )
  select FORMAT_ID, CODE, NAME, EDRFORMAT_STATUS
  from tmp_AGG_EDRFORMAT;

-- ============================================================
--   Table: SOL_OBJS                                           
-- ============================================================
insert into SOL_OBJS
  ( OBJ_ID, OWNER, NAME, DESCRIPTION,
    OBJ_TYPE, OBJ_STATUS )
  select OBJ_ID, OWNER, NAME, DESCRIPTION,
    OBJ_TYPE, OBJ_STATUS
  from tmp_SOL_OBJS;

-- ============================================================
--   Table: AGG_REFERENCESET                                   
-- ============================================================
insert into AGG_REFERENCESET
  ( REFERENCESET_ID, CODE, NAME, REFERENCESET_STATUS )
  select REFERENCESET_ID, CODE, NAME, REFERENCESET_STATUS
  from tmp_AGG_REFERENCESET;

-- ============================================================
--   Table: SOL_SECTION                                        
-- ============================================================
insert into SOL_SECTION
  ( SECTION, NAME )
  select SECTION, NAME
  from tmp_SOL_SECTION;

-- ============================================================
--   Table: SOL_UNITS                                          
-- ============================================================
insert into SOL_UNITS
  ( UNIT_ID, NAME, DESCRIPTION )
  select UNIT_ID, NAME, DESCRIPTION
  from tmp_SOL_UNITS;
  
-- ============================================================
--   Table: AGG_QUEUE                                          
-- ============================================================
insert into AGG_QUEUE
  ( IMPORT_TABLE, DESTINATION_TABLE, STATUS, ENTRY_DATE )
  select IMPORT_TABLE, DESTINATION_TABLE, STATUS, ENTRY_DATE
  from tmp_AGG_QUEUE;

-- ============================================================
--   Table: SOL_TABS                                           
-- ============================================================
insert into SOL_TABS
  ( OBJ_ID, TAB_TYPE )
  select OBJ_ID, TAB_TYPE
  from tmp_SOL_TABS;

-- ============================================================
--   Table: SOL_CONSTRAINTS                                    
-- ============================================================
insert into SOL_CONSTRAINTS
  ( CONSTRAINT_ID, NAME, PARENT_TAB_ID,
    CHILD_TAB_ID, STATUS, CONST_TYPE )
  select CONSTRAINT_ID, NAME, PARENT_TAB_ID,
    CHILD_TAB_ID, STATUS, CONST_TYPE
  from tmp_SOL_CONSTRAINTS;

-- ============================================================
--   Table: SOL_COLS                                           
-- ============================================================
insert into SOL_COLS
  ( OBJ_ID, TAB_OBJ_ID, UNIT_ID, COL_TYPE,
    ALIAS, EXPRESSION, DATATYPE, DATALENGTH,
    DATAPRECISION, DATASCALE, STRINGTYPE,
    NULLABLE, DOMAIN, FORMAT, PIVOTPOSITION,
    ALIGNMENT, RANGEITEM_DOMAIN, VALUEITEM_DOMAIN )
  select OBJ_ID, TAB_OBJ_ID, UNIT_ID, COL_TYPE,
    ALIAS, EXPRESSION, DATATYPE, DATALENGTH,
    DATAPRECISION, DATASCALE, STRINGTYPE,
    NULLABLE, DOMAIN, FORMAT, PIVOTPOSITION,
    ALIGNMENT, RANGEITEM_DOMAIN, VALUEITEM_DOMAIN
  from tmp_SOL_COLS;

-- ============================================================
--   Table: AGG_GROUPING                                       
-- ============================================================
insert into AGG_GROUPING
  ( GROUPING_ID, SCENARIO_ID, COL_OBJ_ID,
    RANK, COL_NAME, COL_FORMAT,
    GROUPING_DATATYPE, GROUPING_STATUS )
  select GROUPING_ID, SCENARIO_ID, COL_OBJ_ID,
    RANK, COL_NAME, COL_FORMAT,
    GROUPING_DATATYPE, GROUPING_STATUS
  from tmp_AGG_GROUPING;

-- ============================================================
--   Table: AGG_GROUPING_CNF                                   
-- ============================================================
insert into AGG_GROUPING_CNF
  ( GROUPING_CNF_ID, GROUPING_ID, CLASS_ID )
  select GROUPING_CNF_ID, GROUPING_ID, CLASS_ID
  from tmp_AGG_GROUPING_CNF;

-- ============================================================
--   Table: AGG_CLASSCON                                       
-- ============================================================
insert into AGG_CLASSCON
  ( CLASSCON_ID, NODE_GROUPING_CNF_ID, NEXT_GROUPING_CNF_ID )
  select CLASSCON_ID, NODE_GROUPING_CNF_ID, NEXT_GROUPING_CNF_ID
  from tmp_AGG_CLASSCON;

-- ============================================================
--   Table: AGG_AGGREGATION                                    
-- ============================================================
insert into AGG_AGGREGATION
  ( AGGREGATION_ID, SCENARIO_ID, COL_OBJ_ID, RANK, COL_NAME, 
    PRECISION, AGGREGATION_FUNCTION, AGGREGATION_STATUS )
  select AGGREGATION_ID, SCENARIO_ID, COL_OBJ_ID, RANK, COL_NAME, 
    PRECISION, AGGREGATION_FUNCTION, AGGREGATION_STATUS
  from tmp_AGG_AGGREGATION;

-- ============================================================
--   Table: AGG_CONDITION                                      
-- ============================================================
insert into AGG_CONDITION
  ( CONDITION_ID, SCENARIO_ID, COL_OBJ_ID, CONDITION_VALUE,
    CONDITION_DATATYPE, CONDITION_STATUS )
  select CONDITION_ID, SCENARIO_ID, COL_OBJ_ID, CONDITION_VALUE,
    CONDITION_DATATYPE, CONDITION_STATUS
  from tmp_AGG_CONDITION;

-- ============================================================
--   Table: AGG_EDRCFIELD                                      
-- ============================================================
insert into AGG_EDRCFIELD
  ( EDRCFIELD_ID, EDRC_TYPE, INTERNAL_FIELD_ID, 
    INTERNAL_FIELDNAME, COL_OBJ_ID, REFERENCESET_ID, RULE_USAGE )
  select EDRCFIELD_ID, EDRC_TYPE, INTERNAL_FIELD_ID,
    INTERNAL_FIELDNAME, COL_OBJ_ID, REFERENCESET_ID, RULE_USAGE
  from tmp_AGG_EDRCFIELD;

-- ============================================================
--   Table: SOL_CONST_COLS                                     
-- ============================================================
insert into SOL_CONST_COLS
  ( CONSTRAINT_ID, PARENT_COL_ID, CHILD_COL_ID )
  select CONSTRAINT_ID, PARENT_COL_ID, CHILD_COL_ID
  from tmp_SOL_CONST_COLS;

-- ============================================================
--   Table: AGG_CLASS_LNK                                      
-- ============================================================
-- insert into AGG_CLASS_LNK
--   ( CLASS_ID, CLASSITEM_ID )
--   select CLASS_ID, CLASSITEM_ID
--   from tmp_AGG_CLASS_LNK;

-- ============================================================
--   Table: AGG_REFERENCESET_CNF                               
-- ============================================================
insert into AGG_REFERENCESET_CNF
  ( REFERENCESET_ID, COL_OBJ_ID, RANK )
  select REFERENCESET_ID, COL_OBJ_ID, RANK
  from tmp_AGG_REFERENCESET_CNF;

-- ============================================================
--   Table: SOL_REGISTRY                                       
-- ============================================================
-- insert into SOL_REGISTRY
--   ( SECTION, KEYVALUE, CONTENT, CONTENT_TYPE, REMARK )
--   select SECTION, KEYVALUE, CONTENT, CONTENT_TYPE, REMARK
--   from tmp_SOL_REGISTRY;

-- ============================================================
--   Table: AGG_CLASSCON_LNK                                   
-- ============================================================
-- insert into AGG_CLASSCON_LNK
--   ( CLASSCON_ID, CLASSITEM_ID )
--   select CLASSCON_ID, CLASSITEM_ID
--   from tmp_AGG_CLASSCON_LNK;

-- ============================================================
--   Table: AGG_EDRFORMAT_CNF                                  
-- ============================================================
-- insert into AGG_EDRFORMAT_CNF
--   ( EDRCFIELD_ID, FORMAT_ID )
--   select EDRCFIELD_ID, FORMAT_ID
--   from tmp_AGG_EDRFORMAT_CNF;

-- ============================================================
--   Table: AGG_EDRFORMAT_SCN                                  
-- ============================================================
insert into AGG_EDRFORMAT_SCN
  ( FORMAT_ID, SCENARIO_ID, TAB_NAME, FLUSHMODE, THRESHOLD, 
    TEMP_DIR, DONE_DIR, CTL_DIR, FIELD_DELIMITER )
  select FORMAT_ID, SCENARIO_ID, TAB_NAME, FLUSHMODE, THRESHOLD, 
    TEMP_DIR, DONE_DIR, CTL_DIR, FIELD_DELIMITER
  from tmp_AGG_EDRFORMAT_SCN;

-- ============================================================
--   Table: AGG_DICTIONARY                                     
-- ============================================================
insert into AGG_DICTIONARY
  ( IMPORT_TABLE, IMPORT_COLUMN, DESTINATION_COLUMN,
    EXPAND_VALUE, KEY, COLUMN_GROUP )
  select IMPORT_TABLE, IMPORT_COLUMN, DESTINATION_COLUMN,
    EXPAND_VALUE, KEY, COLUMN_GROUP
  from tmp_AGG_DICTIONARY;

-- ============================================================
--   Table: INT_DBVERSION
-- ============================================================
insert into int_dbversion
( dbversion, description, username, install_date )
values
( 'v4-10-01', '[integ''rate] and [tariff''ic]', USER, SYSDATE );

commit;

