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
--   Update script from DB version v4-05-00 to v4-10-00.
--   Drop all constraints and rename all tables.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-05-01_v4-10-01_Prepare.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2000/12/21 14:22:16 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-05-01_v4-10-01_Prepare.sql,v $
-- Revision 1.2  2000/12/21 14:22:16  pengelbr
-- Updated to NOT modify INT_ISCRIPT and INT_RULE* tables.
-- iScript and iRules columns shall be of LONG type as before (v4-05).
--
-- Revision 1.1  2000/10/20 07:40:37  pengelbr
-- Modified/Added for v4-10-01 by PE.
--
--------------------------------------------------------------------------------

-- ============================================================
--   Drop foreign keys.
-- ============================================================
alter table INT_SERVICE drop constraint FK_INT_SRV_SRV;

alter table INT_NOPRODUCT drop constraint FK_INT_NPR_NOP;

alter table INT_ZONEMODEL drop constraint FK_INT_ZMD_GMD;

alter table INT_SUBSSERVICE_MAP drop constraint FK_INT_SSM_SRV;

alter table INT_SERVICECLASS drop constraint FK_INT_SVC_SRV;

alter table INT_TARIFFMODEL drop constraint FK_INT_TMD_CAL;

alter table INT_ICPRODUCT drop constraint FK_INT_ICP_TMD;

alter table INT_ICPRODUCT drop constraint FK_INT_ICP_NOP;

alter table INT_ICPRODUCT drop constraint FK_INT_ICP_ALTTMD;

alter table INT_SPECIALISTSYSTEM drop constraint FK_INT_SPS_TMD;

alter table INT_SUBSTARIFF_MAP drop constraint FK_INT_STM_TMD;

alter table INT_CONTENT drop constraint FK_INT_CNT_TMD;

alter table INT_CONTENT drop constraint FK_INT_CNT_CPD;

alter table INT_TARIFFMODEL_VER drop constraint FK_INT_TMV_DML;

alter table INT_TARIFFMODEL_VER drop constraint FK_INT_TMV_TMV;

alter table INT_TARIFFMODEL_VER drop constraint FK_INT_TMV_ZMD;

alter table INT_TARIFFMODEL_VER drop constraint FK_INT_TMV_TMD;

alter table INT_NETWORKMODEL drop constraint FK_INT_NWM_TMD;

alter table INT_SUBS_CONTRACT drop constraint FK_INT_SUB_SPS;

-- This is because in an older version the billcycle was here.
alter table INT_SUBS_CONTRACT drop constraint FK_INT_SUB_SBC;

alter table INT_SWITCH drop constraint FK_INT_SWI_NWM;

alter table INT_SWITCH drop constraint FK_INT_SWI_NOP;

alter table INT_POI drop constraint FK_INT_POI_SWI;

alter table INT_POI drop constraint FK_INT_POI_NWM;

alter table INT_TRUNK drop constraint FK_INT_TRK_NOP;

alter table INT_TRUNK drop constraint FK_INT_TRK_NWM;

alter table INT_TRUNK drop constraint FK_INT_TRK_POI;

alter table INT_DISCOUNTMDL_VER drop constraint FK_INT_DMV_DML;

alter table INT_SUBSDISCOUNT_MAP drop constraint FK_INT_SDM_DML;

alter table SOL_TABS drop constraint FK_SOL_TABS_SOL_OBJS;

alter table SOL_CONSTRAINTS drop constraint FK_SOL_TAB_PARENT_CONSTR;

alter table SOL_CONSTRAINTS drop constraint FK_SOL_TAB_CHILD_CONSTR;

alter table SOL_COLS drop constraint FK_SOL_COLS_SOL_UNITS;

alter table SOL_COLS drop constraint FK_SOL_COLS_SOL_TABS;

alter table SOL_COLS drop constraint FK_SOL_COLS_SOL_OBJS;

alter table AGG_GROUPING drop constraint FK_AGG_GROUPING_SOL_COLS;

alter table AGG_GROUPING drop constraint FK_AGG_GROUPING_AGG_SCENARIO;

alter table AGG_GROUPING_CNF drop constraint FK_AGG_GRPCNF_AGG_GRP;

alter table AGG_GROUPING_CNF drop constraint FK_AGG_GRPCNF_AGG_CLASS;

alter table AGG_CLASSCON drop constraint FK_AGG_CLSCON_AGG_GRPNEXT;

alter table AGG_CLASSCON drop constraint FK_AGG_CLSCON_AGG_GRPNODE;

alter table INT_CALLTYPE_MAP drop constraint FK_INT_CTM_CTP;

alter table INT_CALLTYPE_MAP drop constraint FK_INT_CTM_EDR;

alter table INT_CLASSTYPEZONE_MAP drop constraint FK_INT_CTZ_NEWCTP;

alter table INT_CLASSTYPEZONE_MAP drop constraint FK_INT_CTZ_NEWWSZON;

alter table INT_CLASSTYPEZONE_MAP drop constraint FK_INT_CTZ_NEWRTZON;

alter table INT_CLASSTYPEZONE_MAP drop constraint FK_INT_CTZ_ZMD;

alter table INT_PRICEMODEL_STEP drop constraint FK_INT_PMS_PMD;

alter table INT_HOLIDAY drop constraint FK_INT_HDY_CAL;

alter table INT_TARIFFMODEL_CNF drop constraint FK_INT_TMC_SRV;

alter table INT_TARIFFMODEL_CNF drop constraint FK_INT_TMC_TMV;

alter table INT_TARIFFMODEL_CNF drop constraint FK_INT_TMC_PMD;

alter table INT_TARIFFMODEL_CNF drop constraint FK_INT_TMC_ZON;

alter table INT_TARIFFMODEL_CNF drop constraint FK_INT_TMC_TIZ;

alter table INT_TARIFFMODEL_CNF drop constraint FK_INT_TMC_TIM;

alter table INT_TARIFFMODEL_CNF drop constraint FK_INT_TMC_ALTPMD;

alter table INT_SPECIALDAY_LNK drop constraint FK_INT_SRL_TMV;

alter table INT_SPECIALDAY_LNK drop constraint FK_INT_SRL_SDR;

alter table INT_TIMEMODEL_LNK drop constraint FK_INT_TML_TIZ;

alter table INT_TIMEMODEL_LNK drop constraint FK_INT_TML_DAY;

alter table INT_TIMEMODEL_LNK drop constraint FK_INT_TML_TII;

alter table INT_TIMEMODEL_LNK drop constraint FK_INT_TML_TIM;

alter table INT_STANDARD_ZONE drop constraint FK_INT_STZ_SRV;

alter table INT_STANDARD_ZONE drop constraint FK_INT_STZ_ALTZMD;

alter table INT_STANDARD_ZONE drop constraint FK_INT_STZ_ZMD;

alter table INT_STANDARD_ZONE drop constraint FK_INT_STZ_RTZON;

alter table INT_STANDARD_ZONE drop constraint FK_INT_STZ_WSZON;

alter table INT_GEOGRAPHICAL_ZONE drop constraint FK_INT_GOZ_ZMD;

alter table INT_GEOGRAPHICAL_ZONE drop constraint FK_INT_GOZ_SRV;

alter table INT_GEOGRAPHICAL_ZONE drop constraint FK_INT_GOZ_ALTZMD;

alter table INT_GEOGRAPHICAL_ZONE drop constraint FK_INT_GOZ_RTZON;

alter table INT_GEOGRAPHICAL_ZONE drop constraint FK_INT_GOZ_WSZON;

alter table INT_SEGZONE_LNK drop constraint FK_INT_SZL_SGM;

alter table INT_SEGZONE_LNK drop constraint FK_INT_SZL_ZMD;

alter table INT_POIAREA_LNK drop constraint FK_INT_PAL_NWM;

alter table INT_POIAREA_LNK drop constraint FK_INT_PAL_POI;

alter table INT_GEOAREACODE_LNK drop constraint FK_INT_GAL_GMD;

alter table INT_SERVICECODE_MAP drop constraint FK_INT_SVM_SRV;

alter table INT_SERVICECODE_MAP drop constraint FK_INT_SVM_EDR;

alter table INT_CALLCLASS_MAP drop constraint FK_INT_CCM_CCL;

alter table INT_CALLCLASS_MAP drop constraint FK_INT_CCM_EDR;

alter table INT_SUBS_LOCAL drop constraint FK_INT_LOC_SUB;

alter table INT_TARIFFDISCOUNT_LNK drop constraint FK_INT_TDL_TMV;

alter table INT_SEGTARIFF_LNK drop constraint FK_INT_STL_TMD;

alter table INT_SEGTARIFF_LNK drop constraint FK_INT_STL_SGM;

alter table INT_EDRSEQLOG drop constraint FK_INT_ESQ_EDR;

alter table INT_SPLITTING_TYPE drop constraint FK_INT_SPT_EDR;

alter table INT_SPLITTING_TYPE drop constraint FK_INT_SPT_SPS;

alter table INT_AREACODE_MAP drop constraint FK_INT_ACM_EDR;

alter table INT_SUBS_CLI drop constraint FK_INT_CLI_SUB;

alter table INT_SUBS_CLI drop constraint FK_INT_CLI_SSM;

alter table INT_SUBS_CONTRACT_HIST drop constraint FK_INT_SCH_SDM;

alter table INT_SUBS_CONTRACT_HIST drop constraint FK_INT_SCH_SGM;

alter table INT_SUBS_CONTRACT_HIST drop constraint FK_INT_SCH_SUB;

alter table INT_SUBS_CONTRACT_HIST drop constraint FK_INT_SCH_STM;

alter table INT_SUBS_CONTRACT_HIST drop constraint FK_INT_SCH_SBC;

alter table INT_DISCOUNTMDL_CNF drop constraint FK_INT_DMC_DCR;

alter table INT_DISCOUNTMDL_CNF drop constraint FK_INT_DMC_DTR;

alter table INT_DISCOUNTMDL_CNF drop constraint FK_INT_DMC_DMV;

alter table INT_DISCOUNTSTEP drop constraint FK_INT_DCS_DCM;

alter table INT_DISCOUNTSTEP drop constraint FK_INT_DCS_DCR;

alter table INT_DISCOUNTDETAIL drop constraint FK_INT_DCD_DCM;

alter table INT_SUBS_BILLRUN drop constraint FK_INT_SBR_SBC;

alter table INT_NOSP drop constraint INT_NOSP_EDR;

alter table INT_ICPRODUCT_CNF drop constraint FK_INT_IPC_ICP;

alter table INT_ICPRODUCT_CNF drop constraint FK_INT_IPC_NWM;

alter table INT_ICPRODUCT_CNF drop constraint FK_INT_IPC_TRK;

alter table INT_NOPRODUCT_CNF drop constraint FK_INT_NPR_ICP;

alter table INT_NOPRODUCT_CNF drop constraint FK_INT_NPR_TIZ;

alter table INT_NOPRODUCT_CNF drop constraint FK_INT_NPR_ZON;

alter table INT_NOPRODUCT_CNF drop constraint FK_INT_NPC_NPR;

alter table INT_DISCOUNTCONDITION drop constraint FK_INT_DCN_DCM;

alter table INT_DISCOUNTCONDITION drop constraint FK_INT_DCN_DTR;

alter table INT_DISCARDING drop constraint FK_INT_DIC_EDR;

alter table INT_TIMEMODEL_CNF drop constraint FK_INT_TIC_TIZ;

alter table INT_TIMEMODEL_CNF drop constraint FK_INT_TIC_TIM;

alter table INT_NO_BILLRUN drop constraint FK_INT_NBR_NOP;

alter table INT_TARIFFSERVICECLASS drop constraint FK_INT_TSC_TMD;

alter table INT_TARIFFSERVICECLASS drop constraint FK_INT_TSC_SVC;

alter table INT_CONTENT_MAP drop constraint FK_INT_CNM_CNT;

alter table INT_CONTENT_MAP drop constraint FK_INT_CNM_EDR;

alter table INT_RESELLER_LNK drop constraint FK_INT_RML_TMD;

alter table INT_RESELLER_LNK drop constraint FK_INT_RML_EDR;

alter table INT_RESELLER_LNK drop constraint FK_INT_RESELLER__INT_SEGMENT;

alter table AGG_AGGREGATION drop constraint FK_AGG_AGG_SOL_COLS;

alter table AGG_AGGREGATION drop constraint FK_AGG_AGG_AGG_SCN;

alter table AGG_CONDITION drop constraint FK_AGG_CONDITION_SOL_COLS;

alter table AGG_CONDITION drop constraint FK_AGG_CONDITION_AGG_SCENARIO;

alter table AGG_EDRCFIELD drop constraint FK_AGG_EDRCFIELD_AGG_REFSET;

alter table AGG_EDRCFIELD drop constraint FK_AGG_EDRCFIELD_SOL_COLS;

alter table SOL_CONST_COLS drop constraint FK_SC_SCC_CHILD;

alter table SOL_CONST_COLS drop constraint FK_SC_SCC_PARENT;

alter table SOL_CONST_COLS drop constraint FK_SOL_CONST_COL_SOL_CONSTRAIN;

alter table AGG_CLASS_LNK drop constraint FK_AGG_CLASSLNK_AGG_CLASS;

alter table AGG_CLASS_LNK drop constraint FK_AGG_CLASS_LNK_AGG_CLASSITEM;

alter table AGG_REFERENCESET_CNF drop constraint FK_AGG_REFSET_CNF_AGG_REFSET;

alter table AGG_REFERENCESET_CNF drop constraint FK_AGG_REFSETCNF_SOL_COLS;

alter table SOL_REGISTRY drop constraint FK_SOL_REGISTRY_SOL_SECTION;

alter table AGG_CLASSCON_LNK drop constraint FK_AGG_CLSCONLNK_AGG_CLASSITEM;

alter table AGG_CLASSCON_LNK drop constraint FK_AGG_CLSCONLNK_AGG_CLSCON;

alter table AGG_EDRFORMAT_CNF drop constraint FK_AGG_EDRF_CNF_AGG_EDRF;

alter table AGG_EDRFORMAT_CNF drop constraint FK_AGG_EDRF_CNF_AGG_EDRC_FIELD;

alter table AGG_EDRFORMAT_SCN drop constraint FK_AGG_EDRF_SCN_AGG_SCENARIO;

alter table AGG_EDRFORMAT_SCN drop constraint FK_AGG_EDRF_SCN_AGG_EDRF_AGG;

alter table AGG_DICTIONARY drop constraint FK_AGG_DICTIONAR_AGG_QUEUE;

-- ============================================================
--   Table: INT_SOCIALNUMBER                                   
-- ============================================================
alter table INT_SOCIALNUMBER drop primary key;

drop public synonym INT_SOCIALNUMBER;

rename INT_SOCIALNUMBER to tmp_INT_SOCIALNUMBER;

-- ============================================================
--   Table: INT_CLOSEDUSERGROUP                                
-- ============================================================
alter table INT_CLOSEDUSERGROUP drop primary key;

drop public synonym INT_CLOSEDUSERGROUP;

rename INT_CLOSEDUSERGROUP to tmp_INT_CLOSEDUSERGROUP;

-- ============================================================
--   Index: IDX_INT_SEMEXEC                                    
-- ============================================================
drop index IDX_INT_SEMEXEC;

-- ============================================================
--   Table: INT_SEMAPHORE                                      
-- ============================================================
-- alter table INT_SEMAPHORE drop primary key;
-- alter table INT_SEMAPHORE drop constraint CKC_PERIODE_INT_SEMAPHORE;
-- alter table INT_SEMAPHORE drop constraint CKC_EXECUTED_INT_SEMAPHORE;
-- alter table INT_SEMAPHORE drop constraint CKC_RESULTST_INT_SEMAPHORE;
-- rename INT_SEMAPHORE to tmp_INT_SEMAPHORE;

drop public synonym INT_SEMAPHORE;

-- ============================================================
--   Table: INT_EXCHANGE_RATE                                  
-- ============================================================
alter table INT_EXCHANGE_RATE drop primary key;

alter table INT_EXCHANGE_RATE drop constraint CKC_MODIFIED_INT_EXCHANGE_RATE;

drop public synonym INT_EXCHANGE_RATE;

rename INT_EXCHANGE_RATE to tmp_INT_EXCHANGE_RATE;

-- ============================================================
--   Table: INT_SUBS_ACCOUNT                                   
-- ============================================================
alter table INT_SUBS_ACCOUNT drop primary key;

alter table INT_SUBS_ACCOUNT drop constraint CKC_STATUS_INT_SUBS_ACCOUNT;

drop public synonym INT_SUBS_ACCOUNT;

rename INT_SUBS_ACCOUNT to tmp_INT_SUBS_ACCOUNT;

-- ============================================================
--   Table: INT_DBVERSION                                      
-- ============================================================
alter table INT_DBVERSION drop primary key;

drop public synonym INT_DBVERSION;

rename INT_DBVERSION to tmp_INT_DBVERSION;

-- ============================================================
--   Table: INT_TAX                                            
-- ============================================================
alter table INT_TAX drop primary key;

alter table INT_TAX drop constraint CKC_MODIFIED_INT_TAX;

drop public synonym INT_TAX;

rename INT_TAX to tmp_INT_TAX;

-- ============================================================
--   Table: IC_DAILY                                           
-- ============================================================
alter table IC_DAILY drop primary key;

alter table IC_DAILY drop constraint CKC_BILLING__IC_DAILY;

drop public synonym IC_DAILY;

rename IC_DAILY to tmp_IC_DAILY;

-- ============================================================
--   Table: IC_DAILY_ALTERNATE                                 
-- ============================================================
alter table IC_DAILY_ALTERNATE drop primary key;

alter table IC_DAILY_ALTERNATE drop constraint CKC_BILLING__IC_DAILY_ALTERNAT;

drop public synonym IC_DAILY_ALTERNATE;

rename IC_DAILY_ALTERNATE to tmp_IC_DAILY_ALTERNATE;

-- ============================================================
--   Index: BIDX_AGG_HOLIDAY_RECURRING                         
-- ============================================================
drop index BIDX_AGG_HOLIDAY_RECURRING;

-- ============================================================
--   Table: AGG_HOLIDAY                                        
-- ============================================================
alter table AGG_HOLIDAY drop primary key;

alter table AGG_HOLIDAY drop constraint CKC_RECURRIN_AGG_HOLIDAY;

drop public synonym AGG_HOLIDAY;

rename AGG_HOLIDAY to tmp_AGG_HOLIDAY;

-- ============================================================
--   Table: INT_DESTINATIONDESC                                
-- ============================================================
alter table INT_DESTINATIONDESC drop primary key;

alter table INT_DESTINATIONDESC drop constraint CKC_TYPE_INT_DESTINATIONDES;

drop public synonym INT_DESTINATIONDESC;

rename INT_DESTINATIONDESC to tmp_INT_DESTINATIONDESC;

-- ============================================================
--   Index: AK_INT_TIM                                         
-- ============================================================
drop index AK_INT_TIM;

-- ============================================================
--   Table: INT_TIMEMODEL                                      
-- ============================================================
alter table INT_TIMEMODEL drop primary key;

alter table INT_TIMEMODEL drop constraint CKC_MODIFIED_INT_TIMEMODEL;

drop public synonym INT_TIMEMODEL;

rename INT_TIMEMODEL to tmp_INT_TIMEMODEL;

-- ============================================================
--   Index: AK_INT_CPD                                         
-- ============================================================
drop index AK_INT_CPD;

-- ============================================================
--   Table: INT_CONTENTPROVIDER                                
-- ============================================================
alter table INT_CONTENTPROVIDER drop primary key;

alter table INT_CONTENTPROVIDER drop constraint CKC_MODIFIED_INT_CONTENTPROVID;

drop public synonym INT_CONTENTPROVIDER;

rename INT_CONTENTPROVIDER to tmp_INT_CONTENTPROVIDER;

-- ============================================================
--   Index: AK_INT_DAY                                         
-- ============================================================
drop index AK_INT_DAY;

-- ============================================================
--   Table: INT_DAYCODE                                        
-- ============================================================
alter table INT_DAYCODE drop primary key;

alter table INT_DAYCODE drop constraint CKC_MONDAY_INT_DAYCODE;

alter table INT_DAYCODE drop constraint CKC_TUESDAY_INT_DAYCODE;

alter table INT_DAYCODE drop constraint CKC_WEDNESDA_INT_DAYCODE;

alter table INT_DAYCODE drop constraint CKC_THURSDAY_INT_DAYCODE;

alter table INT_DAYCODE drop constraint CKC_FRIDAY_INT_DAYCODE;

alter table INT_DAYCODE drop constraint CKC_SATURDAY_INT_DAYCODE;

alter table INT_DAYCODE drop constraint CKC_SUNDAY_INT_DAYCODE;

alter table INT_DAYCODE drop constraint CKC_HOLIDAY_INT_DAYCODE;

alter table INT_DAYCODE drop constraint CKC_MODIFIED_INT_DAYCODE;

drop public synonym INT_DAYCODE;

rename INT_DAYCODE to tmp_INT_DAYCODE;

-- ============================================================
--   Table: INT_SPECIALDAYRATE                                 
-- ============================================================
alter table INT_SPECIALDAYRATE drop primary key;

alter table INT_SPECIALDAYRATE drop constraint CKC_DISCOUNT_INT_SPECIALDAYRAT;

alter table INT_SPECIALDAYRATE drop constraint CKC_MODIFIED_INT_SPECIALDAYRAT;

drop public synonym INT_SPECIALDAYRATE;

rename INT_SPECIALDAYRATE to tmp_INT_SPECIALDAYRATE;

-- ============================================================
--   Index: AK_INT_PMD                                         
-- ============================================================
drop index AK_INT_PMD;

-- ============================================================
--   Table: INT_PRICEMODEL                                     
-- ============================================================
alter table INT_PRICEMODEL drop primary key;

alter table INT_PRICEMODEL drop constraint CKC_MODIFIED_INT_PRICEMODEL;

drop public synonym INT_PRICEMODEL;

rename INT_PRICEMODEL to tmp_INT_PRICEMODEL;

-- ============================================================
--   Index: AK_INT_ZON                                         
-- ============================================================
drop index AK_INT_ZON;

-- ============================================================
--   Table: INT_ZONE                                           
-- ============================================================
alter table INT_ZONE drop primary key;

alter table INT_ZONE drop constraint CKC_MODIFIED_INT_ZONE;

drop public synonym INT_ZONE;

rename INT_ZONE to tmp_INT_ZONE;

-- ============================================================
--   Index: AK_INT_TII                                         
-- ============================================================
drop index AK_INT_TII;

-- ============================================================
--   Table: INT_TIMEINTERVAL                                   
-- ============================================================
alter table INT_TIMEINTERVAL drop primary key;

alter table INT_TIMEINTERVAL drop constraint CKC_MODIFIED_INT_TIMEINTERVAL;

drop public synonym INT_TIMEINTERVAL;

rename INT_TIMEINTERVAL to tmp_INT_TIMEINTERVAL;

-- ============================================================
--   Table: INT_NOPRODUCT_CNF                                  
-- ============================================================
alter table INT_NOPRODUCT_CNF drop primary key;

alter table INT_NOPRODUCT_CNF drop constraint CKC_MODIFIED_INT_NOPRODUCT_CNF;

drop public synonym INT_NOPRODUCT_CNF;

rename INT_NOPRODUCT_CNF to tmp_INT_NOPRODUCT_CNF;

-- ============================================================
--   Index: AK_INT_TIZ                                         
-- ============================================================
drop index AK_INT_TIZ;

-- ============================================================
--   Table: INT_TIMEZONE                                       
-- ============================================================
alter table INT_TIMEZONE drop primary key;

alter table INT_TIMEZONE drop constraint CKC_MODIFIED_INT_TIMEZONE;

drop public synonym INT_TIMEZONE;

rename INT_TIMEZONE to tmp_INT_TIMEZONE;

-- ============================================================
--   Table: INT_SEGMENT                                        
-- ============================================================
alter table INT_SEGMENT drop primary key;

alter table INT_SEGMENT drop constraint CKC_MODIFIED_INT_SEGMENT;

drop public synonym INT_SEGMENT;

rename INT_SEGMENT to tmp_INT_SEGMENT;

-- ============================================================
--   Table: INT_NOPRODUCT                                      
-- ============================================================
alter table INT_NOPRODUCT drop primary key;

alter table INT_NOPRODUCT drop constraint CKC_MODIFIED_INT_NOPRODUCT;

drop public synonym INT_NOPRODUCT;

rename INT_NOPRODUCT to tmp_INT_NOPRODUCT;

-- ============================================================
--   Index: AK_INT_NOP                                         
-- ============================================================
drop index AK_INT_NOP;

-- ============================================================
--   Table: INT_NETWORKOPERATOR                                
-- ============================================================
alter table INT_NETWORKOPERATOR drop primary key;

alter table INT_NETWORKOPERATOR drop constraint CKC_NOTYPE_INT_NETWORKOPERATO;

alter table INT_NETWORKOPERATOR drop constraint CKC_MODIFIED_INT_NETWORKOPERAT;

drop public synonym INT_NETWORKOPERATOR;

rename INT_NETWORKOPERATOR to tmp_INT_NETWORKOPERATOR;

-- ============================================================
--   Table: INT_EDRFORMAT                                      
-- ============================================================
alter table INT_EDRFORMAT drop primary key;

alter table INT_EDRFORMAT drop constraint CKC_MODIFIED_INT_EDRFORMAT;

drop public synonym INT_EDRFORMAT;

rename INT_EDRFORMAT to tmp_INT_EDRFORMAT;

-- ============================================================
--   Table: INT_GEOGRAPHICALMODEL                              
-- ============================================================
alter table INT_GEOGRAPHICALMODEL drop primary key;

alter table INT_GEOGRAPHICALMODEL drop constraint CKC_STATUS_INT_GEOGRAPHICALMO;

alter table INT_GEOGRAPHICALMODEL drop constraint CKC_MODIFIED_INT_GEOGRAPHICALM;

drop public synonym INT_GEOGRAPHICALMODEL;

rename INT_GEOGRAPHICALMODEL to tmp_INT_GEOGRAPHICALMODEL;

-- ============================================================
--   Table: INT_SERVICE                                        
-- ============================================================
alter table INT_SERVICE drop primary key;

alter table INT_SERVICE drop constraint CKC_UOM_INT_SERVICE;

alter table INT_SERVICE drop constraint CKC_TOS_INT_SERVICE;

alter table INT_SERVICE drop constraint CKC_CHARGE_I_INT_SERVICE;

alter table INT_SERVICE drop constraint CKC_BASIC_INT_SERVICE;

alter table INT_SERVICE drop constraint CKC_MODIFIED_INT_SERVICE;

drop public synonym INT_SERVICE;

rename INT_SERVICE to tmp_INT_SERVICE;

-- ============================================================
--   Table: INT_CALLCLASS                                      
-- ============================================================
alter table INT_CALLCLASS drop primary key;

alter table INT_CALLCLASS drop constraint CKC_MODIFIED_INT_CALLCLASS;

drop public synonym INT_CALLCLASS;

rename INT_CALLCLASS to tmp_INT_CALLCLASS;

-- ============================================================
--   Table: INT_CALENDAR                                       
-- ============================================================
alter table INT_CALENDAR drop primary key;

alter table INT_CALENDAR drop constraint CKC_MODIFIED_INT_CALENDAR;

drop public synonym INT_CALENDAR;

rename INT_CALENDAR to tmp_INT_CALENDAR;

-- ============================================================
--   Index: AK_INT_DML                                         
-- ============================================================
drop index AK_INT_DML;

-- ============================================================
--   Table: INT_DISCOUNTMODEL                                  
-- ============================================================
alter table INT_DISCOUNTMODEL drop primary key;

alter table INT_DISCOUNTMODEL drop constraint CKC_PERIOD_INT_DISCOUNTMODEL;

alter table INT_DISCOUNTMODEL drop constraint CKC_MODIFIED_INT_DISCOUNTMODEL;

drop public synonym INT_DISCOUNTMODEL;

rename INT_DISCOUNTMODEL to tmp_INT_DISCOUNTMODEL;

-- ============================================================
--   Index: AK_INT_DCR                                         
-- ============================================================
drop index AK_INT_DCR;

-- ============================================================
--   Table: INT_DISCOUNTRULE                                   
-- ============================================================
alter table INT_DISCOUNTRULE drop primary key;

alter table INT_DISCOUNTRULE drop constraint CKC_MODIFIED_INT_DISCOUNTRULE;

drop public synonym INT_DISCOUNTRULE;

rename INT_DISCOUNTRULE to tmp_INT_DISCOUNTRULE;

-- ============================================================
--   Index: AK_INT_DCM                                         
-- ============================================================
drop index AK_INT_DCM;

-- ============================================================
--   Table: INT_DISCOUNTMASTER                                 
-- ============================================================
alter table INT_DISCOUNTMASTER drop primary key;

alter table INT_DISCOUNTMASTER drop constraint CKC_MODIFIED_INT_DISCOUNTMASTE;

drop public synonym INT_DISCOUNTMASTER;

rename INT_DISCOUNTMASTER to tmp_INT_DISCOUNTMASTER;

-- ============================================================
--   Table: INT_SUBS_BILLCYCLE                                 
-- ============================================================
alter table INT_SUBS_BILLCYCLE drop primary key;

alter table INT_SUBS_BILLCYCLE drop constraint CKC_END_OF_C_INT_SUBS_BILLCYCL;

alter table INT_SUBS_BILLCYCLE drop constraint CKC_BILLPERI_INT_SUBS_BILLCYCL;

alter table INT_SUBS_BILLCYCLE drop constraint CKC_MODIFIED_INT_SUBS_BILLCYCL;

drop public synonym INT_SUBS_BILLCYCLE;

rename INT_SUBS_BILLCYCLE to tmp_INT_SUBS_BILLCYCLE;

-- ============================================================
--   Table: INT_CALLTYPE                                       
-- ============================================================
alter table INT_CALLTYPE drop primary key;

alter table INT_CALLTYPE drop constraint CKC_MODIFIED_INT_CALLTYPE;

drop public synonym INT_CALLTYPE;

rename INT_CALLTYPE to tmp_INT_CALLTYPE;

-- ============================================================
--   Table: INT_DISCOUNTTRIGGER                                
-- ============================================================
alter table INT_DISCOUNTTRIGGER drop primary key;

drop public synonym INT_DISCOUNTTRIGGER;

rename INT_DISCOUNTTRIGGER to tmp_INT_DISCOUNTTRIGGER;

-- ============================================================
--   Index: IDX_AGG_SCENARIO_NAME                              
-- ============================================================
drop index IDX_AGG_SCENARIO_NAME;

-- ============================================================
--   Index: AK_AGG_SCENARIO_CODE                               
-- ============================================================
drop index AK_AGG_SCENARIO_CODE;

-- ============================================================
--   Index: BIDX_AGG_SCENARIO_STATUS                           
-- ============================================================
drop index BIDX_AGG_SCENARIO_STATUS;

-- ============================================================
--   Table: AGG_SCENARIO                                       
-- ============================================================
alter table AGG_SCENARIO drop primary key;

alter table AGG_SCENARIO drop constraint CKC_DEFAULT__AGG_SCENARIO;

alter table AGG_SCENARIO drop constraint CKC_SCENARIO_AGG_SCENARIO;

alter table AGG_SCENARIO drop constraint CKC_MODIFIED_AGG_SCENARIO;

drop public synonym AGG_SCENARIO;

rename AGG_SCENARIO to tmp_AGG_SCENARIO;

-- ============================================================
--   Index: IDX_AGG_CLASSITEM_NAME                             
-- ============================================================
drop index IDX_AGG_CLASSITEM_NAME;

-- ============================================================
--   Index: AK_AGG_CLASSITEM_CODE                              
-- ============================================================
drop index AK_AGG_CLASSITEM_CODE;

-- ============================================================
--   Table: AGG_CLASSITEM                                      
-- ============================================================
alter table AGG_CLASSITEM drop primary key;

alter table AGG_CLASSITEM drop constraint CKC_CLASSITE_AGG_CLASSITEM;

alter table AGG_CLASSITEM drop constraint CKC_MODIFIED_AGG_CLASSITEM;

drop public synonym AGG_CLASSITEM;

rename AGG_CLASSITEM to tmp_AGG_CLASSITEM;

-- ============================================================
--   Index: IDX_AGG_CLASS_NAME                                 
-- ============================================================
drop index IDX_AGG_CLASS_NAME;

-- ============================================================
--   Index: AK_AGG_CLASS_CODE                                  
-- ============================================================
drop index AK_AGG_CLASS_CODE;

-- ============================================================
--   Table: AGG_CLASS                                          
-- ============================================================
alter table AGG_CLASS drop primary key;

alter table AGG_CLASS drop constraint CKC_CLASS_DA_AGG_CLASS;

alter table AGG_CLASS drop constraint CKC_MODIFIED_AGG_CLASS;

drop public synonym AGG_CLASS;

rename AGG_CLASS to tmp_AGG_CLASS;

-- ============================================================
--   Index: AK_AGG_EDRFORMAT_CODE                              
-- ============================================================
drop index AK_AGG_EDRFORMAT_CODE;

-- ============================================================
--   Table: AGG_EDRFORMAT                                      
-- ============================================================
alter table AGG_EDRFORMAT drop primary key;

alter table AGG_EDRFORMAT drop constraint CKC_EDRFORMA_AGG_EDRFORMAT;

alter table AGG_EDRFORMAT drop constraint CKC_MODIFIED_AGG_EDRFORMAT;

drop public synonym AGG_EDRFORMAT;

rename AGG_EDRFORMAT to tmp_AGG_EDRFORMAT;

-- ============================================================
--   Index: IDX_SOL_OBJS_OWNER_NAME                            
-- ============================================================
drop index IDX_SOL_OBJS_OWNER_NAME;

-- ============================================================
--   Index: BIDX_SOL_OBJS_TYPE                                 
-- ============================================================
drop index BIDX_SOL_OBJS_TYPE;

-- ============================================================
--   Index: BIDX_SOL_OBJS_STATUS                               
-- ============================================================
drop index BIDX_SOL_OBJS_STATUS;

-- ============================================================
--   Table: SOL_OBJS                                           
-- ============================================================
alter table SOL_OBJS drop primary key;

alter table SOL_OBJS drop constraint CKC_OBJ_TYPE_SOL_OBJS;

alter table SOL_OBJS drop constraint CKC_OBJ_STAT_SOL_OBJS;

alter table SOL_OBJS drop constraint CKC_MODIFIED_SOL_OBJS;

drop public synonym SOL_OBJS;

rename SOL_OBJS to tmp_SOL_OBJS;

-- ============================================================
--   Index: AK_AGG_REFERENCESET_CODE                           
-- ============================================================
drop index AK_AGG_REFERENCESET_CODE;

-- ============================================================
--   Table: AGG_REFERENCESET                                   
-- ============================================================
alter table AGG_REFERENCESET drop primary key;

alter table AGG_REFERENCESET drop constraint CKC_REFERENC_AGG_REFERENCESET;

alter table AGG_REFERENCESET drop constraint CKC_MODIFIED_AGG_REFERENCESET;

drop public synonym AGG_REFERENCESET;

rename AGG_REFERENCESET to tmp_AGG_REFERENCESET;

-- ============================================================
--   Table: SOL_SECTION                                        
-- ============================================================
alter table SOL_SECTION drop primary key;

alter table SOL_SECTION drop constraint CKC_MODIFIED_SOL_SECTION;

drop public synonym SOL_SECTION;

rename SOL_SECTION to tmp_SOL_SECTION;

-- ============================================================
--   Index: IDX_SOL_UNITS_NAME                                 
-- ============================================================
drop index IDX_SOL_UNITS_NAME;

-- ============================================================
--   Table: SOL_UNITS                                          
-- ============================================================
alter table SOL_UNITS drop primary key;

alter table SOL_UNITS drop constraint CKC_MODIFIED_SOL_UNITS;

drop public synonym SOL_UNITS;

rename SOL_UNITS to tmp_SOL_UNITS;

-- ============================================================
--   Table: AGG_QUEUE                                          
-- ============================================================
alter table AGG_QUEUE drop primary key;

alter table AGG_QUEUE drop constraint CKC_STATUS_AGG_QUEUE;

drop public synonym AGG_QUEUE;

rename AGG_QUEUE to tmp_AGG_QUEUE;

-- ============================================================
--   Index: AK_INT_ZMD                                         
-- ============================================================
drop index AK_INT_ZMD;

-- ============================================================
--   Table: INT_ZONEMODEL                                      
-- ============================================================
alter table INT_ZONEMODEL drop primary key;

alter table INT_ZONEMODEL drop constraint CKC_MODELTYP_INT_ZONEMODEL;

alter table INT_ZONEMODEL drop constraint CKC_FRAME_INT_ZONEMODEL;

alter table INT_ZONEMODEL drop constraint CKC_STATUS_INT_ZONEMODEL;

alter table INT_ZONEMODEL drop constraint CKC_MODIFIED_INT_ZONEMODEL;

drop public synonym INT_ZONEMODEL;

rename INT_ZONEMODEL to tmp_INT_ZONEMODEL;

-- ============================================================
--   Table: INT_SUBSSERVICE_MAP                                
-- ============================================================
alter table INT_SUBSSERVICE_MAP drop primary key;

alter table INT_SUBSSERVICE_MAP drop constraint CKC_MODIFIED_INT_SUBSSERVICE_M;

drop public synonym INT_SUBSSERVICE_MAP;

rename INT_SUBSSERVICE_MAP to tmp_INT_SUBSSERVICE_MAP;

-- ============================================================
--   Table: INT_SERVICECLASS                                   
-- ============================================================
alter table INT_SERVICECLASS drop primary key;

alter table INT_SERVICECLASS drop constraint CKC_MODIFIED_INT_SERVICECLASS;

drop public synonym INT_SERVICECLASS;

rename INT_SERVICECLASS to tmp_INT_SERVICECLASS;

-- ============================================================
--   Index: AK_INT_TMD                                         
-- ============================================================
drop index AK_INT_TMD;

-- ============================================================
--   Table: INT_TARIFFMODEL                                    
-- ============================================================
alter table INT_TARIFFMODEL drop primary key;

alter table INT_TARIFFMODEL drop constraint CKC_STATUS_INT_TARIFFMODEL;

alter table INT_TARIFFMODEL drop constraint CKC_MODELTYP_INT_TARIFFMODEL;

alter table INT_TARIFFMODEL drop constraint CKC_SPLITTIN_INT_TARIFFMODEL;

alter table INT_TARIFFMODEL drop constraint CKC_TAXTREAT_INT_TARIFFMODEL;

alter table INT_TARIFFMODEL drop constraint CKC_MODIFIED_INT_TARIFFMODEL;

drop public synonym INT_TARIFFMODEL;

rename INT_TARIFFMODEL to tmp_INT_TARIFFMODEL;

-- ============================================================
--   Table: INT_ICPRODUCT                                      
-- ============================================================
alter table INT_ICPRODUCT drop primary key;

alter table INT_ICPRODUCT drop constraint CKC_ZONE_DIR_INT_ICPRODUCT;

alter table INT_ICPRODUCT drop constraint CKC_BILL_DIR_INT_ICPRODUCT;

alter table INT_ICPRODUCT drop constraint CKC_MODIFIED_INT_ICPRODUCT;

drop public synonym INT_ICPRODUCT;

rename INT_ICPRODUCT to tmp_INT_ICPRODUCT;

-- ============================================================
--   Index: AK_INT_SPS                                         
-- ============================================================
drop index AK_INT_SPS;

-- ============================================================
--   Table: INT_SPECIALISTSYSTEM                               
-- ============================================================
alter table INT_SPECIALISTSYSTEM drop primary key;

alter table INT_SPECIALISTSYSTEM drop constraint CKC_ACTIVE_INT_SPECIALISTSYST;

alter table INT_SPECIALISTSYSTEM drop constraint CKC_MODIFIED_INT_SPECIALISTSYS;

drop public synonym INT_SPECIALISTSYSTEM;

rename INT_SPECIALISTSYSTEM to tmp_INT_SPECIALISTSYSTEM;

-- ============================================================
--   Table: INT_SUBSTARIFF_MAP                                 
-- ============================================================
alter table INT_SUBSTARIFF_MAP drop primary key;

alter table INT_SUBSTARIFF_MAP drop constraint CKC_MODIFIED_INT_SUBSTARIFF_MA;

drop public synonym INT_SUBSTARIFF_MAP;

rename INT_SUBSTARIFF_MAP to tmp_INT_SUBSTARIFF_MAP;

-- ============================================================
--   Table: INT_CONTENT                                        
-- ============================================================
alter table INT_CONTENT drop primary key;

alter table INT_CONTENT drop constraint CKC_MODIFIED_INT_CONTENT;

drop public synonym INT_CONTENT;

rename INT_CONTENT to tmp_INT_CONTENT;

-- ============================================================
--   Table: INT_TARIFFMODEL_VER                                
-- ============================================================
alter table INT_TARIFFMODEL_VER drop primary key;

alter table INT_TARIFFMODEL_VER drop constraint CKC_STATUS_INT_TARIFFMODEL_VE;

alter table INT_TARIFFMODEL_VER drop constraint CKC_BASIC_INT_TARIFFMODEL_VE;

alter table INT_TARIFFMODEL_VER drop constraint CKC_MODIFIED_INT_TARIFFMODEL_V;

drop public synonym INT_TARIFFMODEL_VER;

rename INT_TARIFFMODEL_VER to tmp_INT_TARIFFMODEL_VER;

-- ============================================================
--   Table: INT_NETWORKMODEL                                   
-- ============================================================
alter table INT_NETWORKMODEL drop primary key;

alter table INT_NETWORKMODEL drop constraint CKC_CALCMODE_INT_NETWORKMODEL;

alter table INT_NETWORKMODEL drop constraint CKC_MODELTYP_INT_NETWORKMODEL;

alter table INT_NETWORKMODEL drop constraint CKC_USE_SWIT_INT_NETWORKMODEL;

alter table INT_NETWORKMODEL drop constraint CKC_USE_FIXC_INT_NETWORKMODEL;

alter table INT_NETWORKMODEL drop constraint CKC_MODIFIED_INT_NETWORKMODEL;

drop public synonym INT_NETWORKMODEL;

rename INT_NETWORKMODEL to tmp_INT_NETWORKMODEL;

-- ============================================================
--   Table: INT_SUBS_CONTRACT                                  
-- ============================================================
alter table INT_SUBS_CONTRACT drop primary key;

drop public synonym INT_SUBS_CONTRACT;

rename INT_SUBS_CONTRACT to tmp_INT_SUBS_CONTRACT;

-- ============================================================
--   Index: IDX_INT_SUB_CUSTOMER                               
-- ============================================================
drop index IDX_INT_SUB_CUSTOMER;

-- ============================================================
--   Table: INT_SWITCH                                         
-- ============================================================
alter table INT_SWITCH drop primary key;

alter table INT_SWITCH drop constraint CKC_MODIFIED_INT_SWITCH;

drop public synonym INT_SWITCH;

rename INT_SWITCH to tmp_INT_SWITCH;

-- ============================================================
--   Table: INT_POI                                            
-- ============================================================
alter table INT_POI drop primary key;

alter table INT_POI drop constraint CKC_MODIFIED_INT_POI;

drop public synonym INT_POI;

rename INT_POI to tmp_INT_POI;

-- ============================================================
--   Table: INT_TRUNK                                          
-- ============================================================
alter table INT_TRUNK drop primary key;

alter table INT_TRUNK drop constraint CKC_TRUNKTYP_INT_TRUNK;

alter table INT_TRUNK drop constraint CKC_MODIFIED_INT_TRUNK;

drop public synonym INT_TRUNK;

rename INT_TRUNK to tmp_INT_TRUNK;

-- ============================================================
--   Table: INT_DISCOUNTMDL_VER                                
-- ============================================================
alter table INT_DISCOUNTMDL_VER drop primary key;

alter table INT_DISCOUNTMDL_VER drop constraint CKC_STATUS_INT_DISCOUNTMDL_VE;

alter table INT_DISCOUNTMDL_VER drop constraint CKC_MODIFIED_INT_DISCOUNTMDL_V;

drop public synonym INT_DISCOUNTMDL_VER;

rename INT_DISCOUNTMDL_VER to tmp_INT_DISCOUNTMDL_VER;

-- ============================================================
--   Table: INT_SUBSDISCOUNT_MAP                               
-- ============================================================
alter table INT_SUBSDISCOUNT_MAP drop primary key;

alter table INT_SUBSDISCOUNT_MAP drop constraint CKC_MODIFIED_INT_SUBSDISCOUNT_;

drop public synonym INT_SUBSDISCOUNT_MAP;

rename INT_SUBSDISCOUNT_MAP to tmp_INT_SUBSDISCOUNT_MAP;

-- ============================================================
--   Index: BIDX_SOL_TABS_TAB_TYPE                             
-- ============================================================
drop index BIDX_SOL_TABS_TAB_TYPE;

-- ============================================================
--   Table: SOL_TABS                                           
-- ============================================================
alter table SOL_TABS drop primary key;

alter table SOL_TABS drop constraint CKC_TAB_TYPE_SOL_TABS;

alter table SOL_TABS drop constraint CKC_MODIFIED_SOL_TABS;

drop public synonym SOL_TABS;

rename SOL_TABS to tmp_SOL_TABS;

-- ============================================================
--   Index: BIDX_SOL_CONSTRAINTS_CTYPE                         
-- ============================================================
drop index BIDX_SOL_CONSTRAINTS_CTYPE;

-- ============================================================
--   Index: BIDX_SOL_CONSTRAINTS_STATUS                        
-- ============================================================
drop index BIDX_SOL_CONSTRAINTS_STATUS;

-- ============================================================
--   Table: SOL_CONSTRAINTS                                    
-- ============================================================
alter table SOL_CONSTRAINTS drop primary key;

alter table SOL_CONSTRAINTS drop constraint CKC_STATUS_SOL_CONSTRAINTS;

alter table SOL_CONSTRAINTS drop constraint CKC_CONST_TY_SOL_CONSTRAINTS;

alter table SOL_CONSTRAINTS drop constraint CKC_MODIFIED_SOL_CONSTRAINTS;

drop public synonym SOL_CONSTRAINTS;

rename SOL_CONSTRAINTS to tmp_SOL_CONSTRAINTS;

-- ============================================================
--   Index: BIDX_SOL_COLS_COL_TYPE                             
-- ============================================================
drop index BIDX_SOL_COLS_COL_TYPE;

-- ============================================================
--   Index: BIDX_SOL_COLS_DATATYPE                             
-- ============================================================
drop index BIDX_SOL_COLS_DATATYPE;

-- ============================================================
--   Index: BIDX_SOL_COLS_STRINGTYPE                           
-- ============================================================
drop index BIDX_SOL_COLS_STRINGTYPE;

-- ============================================================
--   Table: SOL_COLS                                           
-- ============================================================
alter table SOL_COLS drop primary key;

alter table SOL_COLS drop constraint CKC_COL_TYPE_SOL_COLS;

alter table SOL_COLS drop constraint CKC_DATATYPE_SOL_COLS;

alter table SOL_COLS drop constraint CKC_STRINGTY_SOL_COLS;

alter table SOL_COLS drop constraint CKC_NULLABLE_SOL_COLS;

alter table SOL_COLS drop constraint CKC_PIVOTPOS_SOL_COLS;

alter table SOL_COLS drop constraint CKC_ALIGNMEN_SOL_COLS;

alter table SOL_COLS drop constraint CKC_MODIFIED_SOL_COLS;

drop public synonym SOL_COLS;

rename SOL_COLS to tmp_SOL_COLS;

-- ============================================================
--   Index: AK_AGG_GRP_SCN_COL                                 
-- ============================================================
drop index AK_AGG_GRP_SCN_COL;

-- ============================================================
--   Index: BIDX_AGG_GRP_STATUS                                
-- ============================================================
drop index BIDX_AGG_GRP_STATUS;

-- ============================================================
--   Table: AGG_GROUPING                                       
-- ============================================================
alter table AGG_GROUPING drop primary key;

alter table AGG_GROUPING drop constraint CKC_GROUPING_AGG_GRPDAT;

alter table AGG_GROUPING drop constraint CKC_GROUPING_AGG_GRSTAT;

drop public synonym AGG_GROUPING;

rename AGG_GROUPING to tmp_AGG_GROUPING;

-- ============================================================
--   Index: AK_AGG_GRPCNF_GRP_CLS                              
-- ============================================================
drop index AK_AGG_GRPCNF_GRP_CLS;

-- ============================================================
--   Table: AGG_GROUPING_CNF                                   
-- ============================================================
alter table AGG_GROUPING_CNF drop primary key;

drop public synonym AGG_GROUPING_CNF;

rename AGG_GROUPING_CNF to tmp_AGG_GROUPING_CNF;

-- ============================================================
--   Index: AK_AGG_CLASSCON_NODE_NEXT                          
-- ============================================================
drop index AK_AGG_CLASSCON_NODE_NEXT;

-- ============================================================
--   Table: AGG_CLASSCON                                       
-- ============================================================
alter table AGG_CLASSCON drop primary key;

drop public synonym AGG_CLASSCON;

rename AGG_CLASSCON to tmp_AGG_CLASSCON;

-- ============================================================
--   Table: INT_CALLTYPE_MAP                                   
-- ============================================================
alter table INT_CALLTYPE_MAP drop primary key;

alter table INT_CALLTYPE_MAP drop constraint CKC_MODIFIED_INT_CALLTYPE_MAP;

drop public synonym INT_CALLTYPE_MAP;

rename INT_CALLTYPE_MAP to tmp_INT_CALLTYPE_MAP;

-- ============================================================
--   Table: INT_CLASSTYPEZONE_MAP                              
-- ============================================================
alter table INT_CLASSTYPEZONE_MAP drop primary key;

alter table INT_CLASSTYPEZONE_MAP drop constraint CKC_MODIFIED_INT_CLASSTYPEZONE;

drop public synonym INT_CLASSTYPEZONE_MAP;

rename INT_CLASSTYPEZONE_MAP to tmp_INT_CLASSTYPEZONE_MAP;

-- ============================================================
--   Table: INT_PRICEMODEL_STEP                                
-- ============================================================
alter table INT_PRICEMODEL_STEP drop primary key;

alter table INT_PRICEMODEL_STEP drop constraint CKC_CHARGE_I_INT_PRICEMODEL_ST;

alter table INT_PRICEMODEL_STEP drop constraint CKC_MODIFIED_INT_PRICEMODEL_ST;

drop public synonym INT_PRICEMODEL_STEP;

rename INT_PRICEMODEL_STEP to tmp_INT_PRICEMODEL_STEP;

-- ============================================================
--   Table: INT_HOLIDAY                                        
-- ============================================================
alter table INT_HOLIDAY drop primary key;

alter table INT_HOLIDAY drop constraint CKC_RECURRIN_INT_HOLIDAY;

alter table INT_HOLIDAY drop constraint CKC_MODIFIED_INT_HOLIDAY;

drop public synonym INT_HOLIDAY;

rename INT_HOLIDAY to tmp_INT_HOLIDAY;

-- ============================================================
--   Table: INT_TARIFFMODEL_CNF                                
-- ============================================================
alter table INT_TARIFFMODEL_CNF drop primary key;

alter table INT_TARIFFMODEL_CNF drop constraint CKC_PASSTHRO_INT_TARIFFMODEL_C;

alter table INT_TARIFFMODEL_CNF drop constraint CKC_ADDON_TY_INT_TARIFFMODEL_C;

drop public synonym INT_TARIFFMODEL_CNF;

rename INT_TARIFFMODEL_CNF to tmp_INT_TARIFFMODEL_CNF;

-- ============================================================
--   Table: INT_SPECIALDAY_LNK                                 
-- ============================================================
alter table INT_SPECIALDAY_LNK drop primary key;

alter table INT_SPECIALDAY_LNK drop constraint CKC_MODIFIED_INT_SPECIALDAY_LN;

drop public synonym INT_SPECIALDAY_LNK;

rename INT_SPECIALDAY_LNK to tmp_INT_SPECIALDAY_LNK;

-- ============================================================
--   Table: INT_TIMEMODEL_LNK                                  
-- ============================================================
alter table INT_TIMEMODEL_LNK drop primary key;

alter table INT_TIMEMODEL_LNK drop constraint CKC_MODIFIED_INT_TIMEMODEL_LNK;

drop public synonym INT_TIMEMODEL_LNK;

rename INT_TIMEMODEL_LNK to tmp_INT_TIMEMODEL_LNK;

-- ============================================================
--   Table: INT_STANDARD_ZONE                                  
-- ============================================================
alter table INT_STANDARD_ZONE drop primary key;

drop public synonym INT_STANDARD_ZONE;

rename INT_STANDARD_ZONE to tmp_INT_STANDARD_ZONE;

-- ============================================================
--   Table: INT_GEOGRAPHICAL_ZONE                              
-- ============================================================
alter table INT_GEOGRAPHICAL_ZONE drop primary key;

drop public synonym INT_GEOGRAPHICAL_ZONE;

rename INT_GEOGRAPHICAL_ZONE to tmp_INT_GEOGRAPHICAL_ZONE;

-- ============================================================
--   Table: INT_SEGZONE_LNK                                    
-- ============================================================
alter table INT_SEGZONE_LNK drop primary key;

alter table INT_SEGZONE_LNK drop constraint CKC_MODIFIED_INT_SEGZONE_LNK;

drop public synonym INT_SEGZONE_LNK;

rename INT_SEGZONE_LNK to tmp_INT_SEGZONE_LNK;

-- ============================================================
--   Table: INT_POIAREA_LNK                                    
-- ============================================================
alter table INT_POIAREA_LNK drop primary key;

drop public synonym INT_POIAREA_LNK;

rename INT_POIAREA_LNK to tmp_INT_POIAREA_LNK;

-- ============================================================
--   Table: INT_GEOAREACODE_LNK                                
-- ============================================================
alter table INT_GEOAREACODE_LNK drop primary key;

drop public synonym INT_GEOAREACODE_LNK;

rename INT_GEOAREACODE_LNK to tmp_INT_GEOAREACODE_LNK;

-- ============================================================
--   Table: INT_SERVICECODE_MAP                                
-- ============================================================
alter table INT_SERVICECODE_MAP drop primary key;

alter table INT_SERVICECODE_MAP drop constraint CKC_UOM_INT_SERVICECODE_MA;

alter table INT_SERVICECODE_MAP drop constraint CKC_MODIFIED_INT_SERVICECODE_M;

drop public synonym INT_SERVICECODE_MAP;

rename INT_SERVICECODE_MAP to tmp_INT_SERVICECODE_MAP;

-- ============================================================
--   Table: INT_CALLCLASS_MAP                                  
-- ============================================================
alter table INT_CALLCLASS_MAP drop primary key;

alter table INT_CALLCLASS_MAP drop constraint CKC_MODIFIED_INT_CALLCLASS_MAP;

drop public synonym INT_CALLCLASS_MAP;

rename INT_CALLCLASS_MAP to tmp_INT_CALLCLASS_MAP;

-- ============================================================
--   Table: INT_SUBS_LOCAL                                     
-- ============================================================
alter table INT_SUBS_LOCAL drop primary key;

alter table INT_SUBS_LOCAL drop constraint CKC_CLITYPE_INT_SUBS_LOCAL;

drop public synonym INT_SUBS_LOCAL;

rename INT_SUBS_LOCAL to tmp_INT_SUBS_LOCAL;

-- ============================================================
--   Table: INT_TARIFFDISCOUNT_LNK                             
-- ============================================================
alter table INT_TARIFFDISCOUNT_LNK drop primary key;

alter table INT_TARIFFDISCOUNT_LNK drop constraint CKC_DISCOUNT_INT_TARIFFDISCOUN;

alter table INT_TARIFFDISCOUNT_LNK drop constraint CKC_MODIFIED_INT_TARIFFDISCOUN;

drop public synonym INT_TARIFFDISCOUNT_LNK;

rename INT_TARIFFDISCOUNT_LNK to tmp_INT_TARIFFDISCOUNT_LNK;

-- ============================================================
--   Table: INT_SEGTARIFF_LNK                                  
-- ============================================================
alter table INT_SEGTARIFF_LNK drop primary key;

alter table INT_SEGTARIFF_LNK drop constraint CKC_MODIFIED_INT_SEGTARIFF_LNK;

drop public synonym INT_SEGTARIFF_LNK;

rename INT_SEGTARIFF_LNK to tmp_INT_SEGTARIFF_LNK;

-- ============================================================
--   Table: INT_EDRSEQLOG                                      
-- ============================================================
alter table INT_EDRSEQLOG drop primary key;

alter table INT_EDRSEQLOG drop constraint CKC_STATUS_INT_EDRSEQLOG;

alter table INT_EDRSEQLOG drop constraint CKC_RECYCLIN_INT_EDRSEQLOG;

drop public synonym INT_EDRSEQLOG;

rename INT_EDRSEQLOG to tmp_INT_EDRSEQLOG;

-- ============================================================
--   Table: INT_SPLITTING_TYPE                                 
-- ============================================================
alter table INT_SPLITTING_TYPE drop primary key;

alter table INT_SPLITTING_TYPE drop constraint CKC_MODIFIED_INT_SPLITTING_TYP;

drop public synonym INT_SPLITTING_TYPE;

rename INT_SPLITTING_TYPE to tmp_INT_SPLITTING_TYPE;

-- ============================================================
--   Table: INT_AREACODE_MAP                                   
-- ============================================================
alter table INT_AREACODE_MAP drop primary key;

alter table INT_AREACODE_MAP drop constraint CKC_MODIFIED_INT_AREACODE_MAP;

drop public synonym INT_AREACODE_MAP;

rename INT_AREACODE_MAP to tmp_INT_AREACODE_MAP;

-- ============================================================
--   Table: INT_SUBS_CLI                                       
-- ============================================================
alter table INT_SUBS_CLI drop primary key;

drop public synonym INT_SUBS_CLI;

rename INT_SUBS_CLI to tmp_INT_SUBS_CLI;

-- ============================================================
--   Table: INT_SUBS_CONTRACT_HIST                             
-- ============================================================
alter table INT_SUBS_CONTRACT_HIST drop primary key;

drop public synonym INT_SUBS_CONTRACT_HIST;

rename INT_SUBS_CONTRACT_HIST to tmp_INT_SUBS_CONTRACT_HIST;

-- ============================================================
--   Index: AK_INT_DMC                                         
-- ============================================================
drop index AK_INT_DMC;

-- ============================================================
--   Table: INT_DISCOUNTMDL_CNF                                
-- ============================================================
alter table INT_DISCOUNTMDL_CNF drop primary key;

drop public synonym INT_DISCOUNTMDL_CNF;

rename INT_DISCOUNTMDL_CNF to tmp_INT_DISCOUNTMDL_CNF;

-- ============================================================
--   Index: AK_INT_DCS                                         
-- ============================================================
drop index AK_INT_DCS;

-- ============================================================
--   Table: INT_DISCOUNTSTEP                                   
-- ============================================================
alter table INT_DISCOUNTSTEP drop primary key;

alter table INT_DISCOUNTSTEP drop constraint CKC_THRESHOL_INT_DISCOUNTSTEP;

alter table INT_DISCOUNTSTEP drop constraint CKC_DISCOUNT_INT_DISCOUNTSTEP;

alter table INT_DISCOUNTSTEP drop constraint CKC_GRANT_TY_INT_DISCOUNTSTEP;

alter table INT_DISCOUNTSTEP drop constraint CKC_GRANT_PR_INT_DISCOUNTSTEP;

alter table INT_DISCOUNTSTEP drop constraint CKC_GRANT_UO_INT_DISCOUNTSTEP;

alter table INT_DISCOUNTSTEP drop constraint CKC_EDR_ENRI_INT_DISCOUNTSTEP;

alter table INT_DISCOUNTSTEP drop constraint CKC_MODIFIED_INT_DISCOUNTSTEP;

drop public synonym INT_DISCOUNTSTEP;

rename INT_DISCOUNTSTEP to tmp_INT_DISCOUNTSTEP;

-- ============================================================
--   Table: INT_DISCOUNTDETAIL                                 
-- ============================================================
alter table INT_DISCOUNTDETAIL drop primary key;

alter table INT_DISCOUNTDETAIL drop constraint CKC_MODIFIED_INT_DISCOUNTDETAI;

drop public synonym INT_DISCOUNTDETAIL;

rename INT_DISCOUNTDETAIL to tmp_INT_DISCOUNTDETAIL;

-- ============================================================
--   Index: AK_INT_SCR                                         
-- ============================================================
drop index AK_INT_SCR;

-- ============================================================
--   Table: INT_SUBS_BILLRUN                                   
-- ============================================================
alter table INT_SUBS_BILLRUN drop primary key;

alter table INT_SUBS_BILLRUN drop constraint CKC_STATUS_INT_SUBS_BILLRUN;

alter table INT_SUBS_BILLRUN drop constraint CKC_MODIFIED_INT_SUBS_BILLRUN;

drop public synonym INT_SUBS_BILLRUN;

rename INT_SUBS_BILLRUN to tmp_INT_SUBS_BILLRUN;

-- ============================================================
--   Table: INT_NOSP                                           
-- ============================================================
alter table INT_NOSP drop primary key;

alter table INT_NOSP drop constraint CKC_MODIFIED_INT_NOSP;

drop public synonym INT_NOSP;

rename INT_NOSP to tmp_INT_NOSP;

-- ============================================================
--   Table: INT_ICPRODUCT_CNF                                  
-- ============================================================
alter table INT_ICPRODUCT_CNF drop primary key;

alter table INT_ICPRODUCT_CNF drop constraint CKC_DIRECTIO_INT_ICPRODUCT_CNF;

drop public synonym INT_ICPRODUCT_CNF;

rename INT_ICPRODUCT_CNF to tmp_INT_ICPRODUCT_CNF;

-- ============================================================
--   Table: INT_DISCOUNTCONDITION                              
-- ============================================================
alter table INT_DISCOUNTCONDITION drop primary key;

alter table INT_DISCOUNTCONDITION drop constraint CKC_CONDITIO_INT_DISCOUNTCONDI;

drop public synonym INT_DISCOUNTCONDITION;

rename INT_DISCOUNTCONDITION to tmp_INT_DISCOUNTCONDITION;

-- ============================================================
--   Table: INT_DISCARDING                                     
-- ============================================================
alter table INT_DISCARDING drop primary key;

alter table INT_DISCARDING drop constraint CKC_AOC_NULL_INT_DISCARDING;

alter table INT_DISCARDING drop constraint CKC_MODIFIED_INT_DISCARDING;

drop public synonym INT_DISCARDING;

rename INT_DISCARDING to tmp_INT_DISCARDING;

-- ============================================================
--   Table: INT_TIMEMODEL_CNF                                  
-- ============================================================
alter table INT_TIMEMODEL_CNF drop primary key;

alter table INT_TIMEMODEL_CNF drop constraint CKC_MODIFIED_INT_TIMEMODEL_CNF;

drop public synonym INT_TIMEMODEL_CNF;

rename INT_TIMEMODEL_CNF to tmp_INT_TIMEMODEL_CNF;

-- ============================================================
--   Table: INT_NO_BILLRUN                                     
-- ============================================================
alter table INT_NO_BILLRUN drop primary key;

alter table INT_NO_BILLRUN drop constraint CKC_STATUS_INT_NO_BILLRUN;

alter table INT_NO_BILLRUN drop constraint CKC_MODIFIED_INT_NO_BILLRUN;

drop public synonym INT_NO_BILLRUN;

rename INT_NO_BILLRUN to tmp_INT_NO_BILLRUN;

-- ============================================================
--   Table: INT_TARIFFSERVICECLASS                             
-- ============================================================
alter table INT_TARIFFSERVICECLASS drop primary key;

alter table INT_TARIFFSERVICECLASS drop constraint CKC_MODIFIED_INT_TARIFFSERVICE;

drop public synonym INT_TARIFFSERVICECLASS;

rename INT_TARIFFSERVICECLASS to tmp_INT_TARIFFSERVICECLASS;

-- ============================================================
--   Table: INT_CONTENT_MAP                                    
-- ============================================================
alter table INT_CONTENT_MAP drop primary key;

alter table INT_CONTENT_MAP drop constraint CKC_MODIFIED_INT_CONTENT_MAP;

drop public synonym INT_CONTENT_MAP;

rename INT_CONTENT_MAP to tmp_INT_CONTENT_MAP;

-- ============================================================
--   Table: INT_RESELLER_LNK                                   
-- ============================================================
alter table INT_RESELLER_LNK drop primary key;

alter table INT_RESELLER_LNK drop constraint CKC_ROAMING__INT_RESELLER_LNK;

alter table INT_RESELLER_LNK drop constraint CKC_MODIFIED_INT_RESELLER_LNK;

drop public synonym INT_RESELLER_LNK;

rename INT_RESELLER_LNK to tmp_INT_RESELLER_LNK;

-- ============================================================
--   Index: BIDX_AGG_AGG_STATUS                                
-- ============================================================
drop index BIDX_AGG_AGG_STATUS;

-- ============================================================
--   Index: BIDX_AGG_AGG_FUNCTION                              
-- ============================================================
drop index BIDX_AGG_AGG_FUNCTION;

-- ============================================================
--   Index: AK_AGG_AGG_SCN_COL                                 
-- ============================================================
drop index AK_AGG_AGG_SCN_COL;

-- ============================================================
--   Table: AGG_AGGREGATION                                    
-- ============================================================
alter table AGG_AGGREGATION drop primary key;

alter table AGG_AGGREGATION drop constraint CKC_AGGREGAT_AGG_FUNC;

alter table AGG_AGGREGATION drop constraint CKC_AGGREGAT_AGG_STATUS;

alter table AGG_AGGREGATION drop constraint CKC_MODIFIED_AGG_AGGREGATION;

drop public synonym AGG_AGGREGATION;

rename AGG_AGGREGATION to tmp_AGG_AGGREGATION;

-- ============================================================
--   Index: AK_AGG_COND_SCN_COL                                
-- ============================================================
drop index AK_AGG_COND_SCN_COL;

-- ============================================================
--   Index: BIDX_AGG_COND_STATUS                               
-- ============================================================
drop index BIDX_AGG_COND_STATUS;

-- ============================================================
--   Index: BIDX_AGG_COND_TYPE                                 
-- ============================================================
drop index BIDX_AGG_COND_TYPE;

-- ============================================================
--   Table: AGG_CONDITION                                      
-- ============================================================
alter table AGG_CONDITION drop primary key;

alter table AGG_CONDITION drop constraint CKC_CONDITIO_AGG_COND_DAT;

alter table AGG_CONDITION drop constraint CKC_CONDITIO_COND_STAT;

alter table AGG_CONDITION drop constraint CKC_MODIFIED_AGG_CONDITION;

drop public synonym AGG_CONDITION;

rename AGG_CONDITION to tmp_AGG_CONDITION;

-- ============================================================
--   Index: AK_AGG_EDRCFIELD_INTERNAL_NAME                     
-- ============================================================
drop index AK_AGG_EDRCFIELD_INTERNAL_NAME;

-- ============================================================
--   Index: AK_AGG_EDRCFIELD_INTERNAL_NAME                     
-- ============================================================
drop index AK_AGG_EDRCFIELD_INTERNAL_ID;

-- ============================================================
--   Table: AGG_EDRCFIELD                                      
-- ============================================================
alter table AGG_EDRCFIELD drop primary key;

alter table AGG_EDRCFIELD drop constraint CKC_EDRC_TYP_AGG_EDRCFIELD;

alter table AGG_EDRCFIELD drop constraint CKC_RULE_USA_AGG_EDRCFIELD;

alter table AGG_EDRCFIELD drop constraint CKC_MODIFIED_AGG_EDRCFIELD;

drop public synonym AGG_EDRCFIELD;

rename AGG_EDRCFIELD to tmp_AGG_EDRCFIELD;

-- ============================================================
--   Table: SOL_CONST_COLS                                     
-- ============================================================
alter table SOL_CONST_COLS drop primary key;

drop public synonym SOL_CONST_COLS;

rename SOL_CONST_COLS to tmp_SOL_CONST_COLS;

-- ============================================================
--   Table: AGG_CLASS_LNK                                      
-- ============================================================
-- Table was not modified and is index organized!
--
-- alter table AGG_CLASS_LNK drop primary key;
-- rename AGG_CLASS_LNK to tmp_AGG_CLASS_LNK;

drop public synonym AGG_CLASS_LNK;

-- ============================================================
--   Index: AK_AGG_REFSETCNF_REFSET_RANK                       
-- ============================================================
drop index AK_AGG_REFSETCNF_REFSET_RANK;

-- ============================================================
--   Table: AGG_REFERENCESET_CNF                               
-- ============================================================
alter table AGG_REFERENCESET_CNF drop primary key;

drop public synonym AGG_REFERENCESET_CNF;

rename AGG_REFERENCESET_CNF to tmp_AGG_REFERENCESET_CNF;

-- ============================================================
--   Table: SOL_REGISTRY                                       
-- ============================================================
-- alter table SOL_REGISTRY drop primary key;
-- rename SOL_REGISTRY to tmp_SOL_REGISTRY;

drop public synonym SOL_REGISTRY;

-- ============================================================
--   Table: AGG_CLASSCON_LNK                                   
-- ============================================================
-- Table was not modified and is index organized!
--
-- alter table AGG_CLASSCON_LNK drop primary key;
-- rename AGG_CLASSCON_LNK to tmp_AGG_CLASSCON_LNK;

drop public synonym AGG_CLASSCON_LNK;

-- ============================================================
--   Table: AGG_EDRFORMAT_CNF                                  
-- ============================================================
-- Table was not modified and is index organized!
--
-- alter table AGG_EDRFORMAT_CNF drop primary key;
-- rename AGG_EDRFORMAT_CNF to tmp_AGG_EDRFORMAT_CNF;

drop public synonym AGG_EDRFORMAT_CNF;

-- ============================================================
--   Table: AGG_EDRFORMAT_SCN                                  
-- ============================================================
alter table AGG_EDRFORMAT_SCN drop primary key;

alter table AGG_EDRFORMAT_SCN drop constraint CKC_FLUSHMOD_AGG_EDRFORMAT_SCN;

alter table AGG_EDRFORMAT_SCN drop constraint CKC_AGG_EDRF_MODIFIED;

drop public synonym AGG_EDRFORMAT_SCN

rename AGG_EDRFORMAT_SCN to tmp_AGG_EDRFORMAT_SCN;

-- ============================================================
--   Table: AGG_DICTIONARY                                     
-- ============================================================
alter table AGG_DICTIONARY drop primary key;

alter table AGG_DICTIONARY drop constraint CKC_KEY_AGG_DICTIONARY;

drop public synonym AGG_DICTIONARY;

rename AGG_DICTIONARY to tmp_AGG_DICTIONARY;

