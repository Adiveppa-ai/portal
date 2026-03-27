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
--   Update script from DB version v4-10-04 to v4-30-01.
--------------------------------------------------------------------------------
-- Responsible: Peter Engelbrecht
--
-- $RCSfile: update_v4-10-04_v4-30-01_Drop.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2001/09/21 08:54:22 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-10-04_v4-30-01_Drop.sql,v $
-- Revision 1.2  2001/09/21 08:54:22  pengelbr
-- Commit for INT_DB v4-30-06
--
-- Revision 1.1  2001/07/06 07:43:43  pengelbr
-- PETS #36686 Create a database migration script from v4-10-04 to v4-30-00
--
-- Revision 1.1  2001/06/19 13:58:16  pengelbr
-- Most recent changes for v4-30-00
--
--------------------------------------------------------------------------------

spool update_v4-10-04_v4-30-01_Drop.log


--
-- drop all old references, tables and views
--
drop table agg_aggregation cascade constraints;
drop table agg_class cascade constraints;
drop table agg_classcon cascade constraints;
drop table agg_classcon_lnk cascade constraints;
drop table agg_classitem cascade constraints;
drop table agg_class_lnk cascade constraints;
drop table agg_condition cascade constraints;
drop table agg_dictionary cascade constraints;
drop table agg_edrcfield cascade constraints;
drop table agg_grouping cascade constraints;
drop table agg_grouping_cnf cascade constraints;
drop table agg_holiday cascade constraints;
drop table agg_queue cascade constraints;
drop table agg_referenceset cascade constraints;
drop table agg_referenceset_cnf cascade constraints;
drop table agg_scenario;
drop table int_apn_group cascade constraints;
drop table int_apn_map cascade constraints;
drop table int_calendar cascade constraints;
drop table int_callclass cascade constraints;
drop table int_callclass_map cascade constraints;
drop table int_calltype cascade constraints;
drop table int_calltype_map cascade constraints;
drop table int_classtypezone_map cascade constraints;
drop table int_closedusergroup cascade constraints;
drop table int_content cascade constraints;
drop table int_contentprovider cascade constraints;
drop table int_content_map cascade constraints;
drop table int_currency cascade constraints;
drop table int_czt_group cascade constraints;
drop table int_daycode cascade constraints;
drop table int_dbversion cascade constraints;
drop table int_destinationdesc cascade constraints;
drop table int_discarding cascade constraints;
drop table int_discountcondition cascade constraints;
drop table int_discountdetail cascade constraints;
drop table int_discountmaster cascade constraints;
drop table int_discountmdl_cnf cascade constraints;
drop table int_discountmdl_ver cascade constraints;
drop table int_discountmodel cascade constraints;
drop table int_discountrule cascade constraints;
drop table int_discountstep cascade constraints;
drop table int_discounttrigger cascade constraints;
drop table int_edrformat cascade constraints;
drop table int_edrseqlog cascade constraints;
drop table int_exchange_rate cascade constraints;
drop table int_geoareacode_lnk cascade constraints;
drop table int_geographicalmodel cascade constraints;
drop table int_geographical_zone cascade constraints;
drop table int_glaccount cascade constraints;
drop table int_holiday cascade constraints;
drop table int_icno_lnk cascade constraints;
drop table int_icproduct cascade constraints;
drop table int_icproduct_cnf cascade constraints;
drop table int_icproduct_group cascade constraints;
drop table int_map_group cascade constraints;
drop table int_networkmodel cascade constraints;
drop table int_networkoperator cascade constraints;
drop table int_noproduct cascade constraints;
drop table int_noproduct_cnf cascade constraints;
drop table int_nosp cascade constraints;
drop table int_no_billrun cascade constraints;
drop table int_poi cascade constraints;
drop table int_poiarea_lnk cascade constraints;
drop table int_pricemodel cascade constraints;
drop table int_pricemodel_step cascade constraints;
drop table int_revenuegroup cascade constraints;
drop table int_ruleset cascade constraints;
drop table int_rulesetlist cascade constraints;
drop table int_segment cascade constraints;
drop table int_segtariff_lnk cascade constraints;
drop table int_segzone_lnk cascade constraints;
drop table int_service cascade constraints;
drop table int_serviceclass cascade constraints;
drop table int_servicecode_map cascade constraints;
drop table int_socialnumber cascade constraints;
drop table int_specialdayrate cascade constraints;
drop table int_specialday_lnk cascade constraints;
drop table int_splitting_type cascade constraints;
drop table int_standard_zone cascade constraints;
drop table int_subsdiscount_map cascade constraints;
drop table int_subsservice_map cascade constraints;
drop table int_substariff_map cascade constraints;
drop table int_subs_account cascade constraints;
drop table int_subs_billcycle cascade constraints;
drop table int_subs_billrun cascade constraints;
drop table int_subs_cli cascade constraints;
drop table int_subs_contract cascade constraints;
drop table int_subs_contract_hist cascade constraints;
drop table int_subs_local cascade constraints;
drop table int_subs_reference_hist cascade constraints;
drop table int_switch cascade constraints;
drop table int_system_brand cascade constraints;
drop table int_tariffdiscount_lnk cascade constraints;
drop table int_tariffmodel cascade constraints;
drop table int_tariffmodel_cnf cascade constraints;
drop table int_tariffmodel_ver cascade constraints;
drop table int_tax cascade constraints;
drop table int_taxcode cascade constraints;
drop table int_taxgroup cascade constraints;
drop table int_timeinterval cascade constraints;
drop table int_timemodel cascade constraints;
drop table int_timemodel_lnk cascade constraints;
drop table int_timezone cascade constraints;
drop table int_trunk cascade constraints;
drop table int_trunk_cnf cascade constraints;
drop table int_tsc_group cascade constraints;
drop table int_tariffserviceclass cascade constraints;
drop table int_uom cascade constraints;
drop table int_uom_map cascade constraints;
drop table int_zone cascade constraints;
drop table int_zonemodel cascade constraints;

drop table sol_cols cascade constraints;
drop table sol_constraints cascade constraints;
drop table sol_const_cols cascade constraints;
drop table sol_objs cascade constraints;
drop table sol_tabs cascade constraints;
drop table sol_units cascade constraints;

drop view agg_format_map_columns;

drop sequence agg_aggregation_seq;
drop sequence agg_classcon_seq;
drop sequence agg_classitem_seq;
drop sequence agg_class_seq;
drop sequence agg_condition_seq;
drop sequence agg_edrcfield_seq;
drop sequence agg_edrformat_seq;
drop sequence agg_grouping_seq;
drop sequence agg_referenceset_seq;
drop sequence agg_scenario_seq;
drop sequence int_seq_calendar;
drop sequence int_seq_contentprovider;
drop sequence int_seq_daycode;
drop sequence int_seq_discountcondition;
drop sequence int_seq_discountconfig;
drop sequence int_seq_discountmaster;
drop sequence int_seq_discountmodel;
drop sequence int_seq_discountrule;
drop sequence int_seq_discountstep;
drop sequence int_seq_discounttrigger;
drop sequence int_seq_generic;
drop sequence int_seq_geomodel;
drop sequence int_seq_granted_discount;
drop sequence int_seq_networkmodel;
drop sequence int_seq_no;
drop sequence int_seq_pricemodel;
drop sequence int_seq_semaphore;
drop sequence int_seq_specialdayrate;
drop sequence int_seq_specialistsystem;
drop sequence int_seq_tariffmodel;
drop sequence int_seq_timeinterval;
drop sequence int_seq_timemodel;
drop sequence int_seq_timezone;
drop sequence int_seq_zonemodel;
drop sequence sol_constraints_seq;
drop sequence sol_objs_seq;
drop sequence sol_units_seq;

--
-- Create all public synonyms
--
@ifw_Synonyms.sql

spool off;
