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
-- $RCSfile: update_v4-10-04_v4-30-01_CreateCopy.sql,v $
-- $Revision: 1.2 $
-- $Author: pengelbr $
-- $Date: 2001/09/21 08:54:22 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-10-04_v4-30-01_CreateCopy.sql,v $
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

spool update_v4-10-04_v4-30-01_CreateCopy.log


--
-- drop duplicate primary keys
--
alter table ic_daily drop primary key;

alter table ic_daily_alternate drop primary key;

rename ic_daily to tmp_daily;

rename ic_daily_alternate to tmp_daily_alternate;


--
-- drop all old public synonyms
--
@update_v4-10-04_v4-30-01_DropSynonyms.sql


--
-- Create new database tables...
--
@ifw_Create.sql


--
-- Copy/Migrate all existing data from old to new tables
--


-- all general stuff

insert into ifw_dbversion
( dbversion, description, username, install_date )
select dbversion, description, username, install_date
from int_dbversion;

insert into ifw_pipeline
( pipeline, name, edrc_desc, seq_number, seq_orignumber, 
  seq_offset, seq_maxsequence, seq_maxoffset, 
  seq_minsequence, seq_minoffset )
select edr_format, name, 'EXAMPLE', seq_number, seq_orignumber, 
     seq_offset, seq_maxsequence, seq_maxoffset, 
     seq_minsequence, seq_minoffset
from int_edrformat;

insert into ifw_edrseqlog
( pipeline, orig_seqno, new_seqno, processed, status,
  recycling, num_rec_in, num_rec_out, num_rec_warn,
  duration, sum_quantity, sum_rt_charge, sum_ws_charge, 
  processedby_format, streamname_in )
select edr_format, orig_seqno, new_seqno, processed, status,
     recycling, num_rec_in, num_rec_out, num_rec_warn,
     duration, sum_quantity, sum_charge, sum_aoc, 
     processedby_format, streamname_in
from int_edrseqlog;

insert into ifw_discarding
( pipeline, rank, name, recordtype, source_network,
  call_completion, long_duration, usageclass,
  servicecode, switch, tariffclass, tariffsubclass,
  connecttype, connectsubtype, b_number, max_age, ws_null )
select edr_format, rank, name, recordtype, source_network,
     call_completion, long_duration, callclass,
     servicecode, switch, tariffclass, tariffsubclass,
     connecttype, connectsubtype, b_number, max_age, aoc_null
from int_discarding;

insert into ifw_system_brand
( system_brand, name, active )
select system_brand, name, active
from int_system_brand;

insert into ifw_splitting_type
( pipeline, rank, valid_from, valid_to, recordtype, 
  servicecode, usageclass, source_network,
  destin_network, switch, trunk_in, trunk_out, 
  origin_areacode, destin_areacode, transit_areacode, 
  system_brand, name )
select edr_format, rank, valid_from, valid_to, recordtype, 
     servicecode, callclass, source_network,
     destin_network, switch, trunk_in, trunk_out, 
     origin_areacode, destin_areacode, transit_areacode, 
     system_brand, name
from int_splitting_type;

insert into ifw_destinationdesc
( areacode, type, name )
select areacode, type, name
from int_destinationdesc;

insert into ifw_socialnumber
( socialnumber, name )
select socialnumber, name
from int_socialnumber;

drop table ifw_semaphore;

rename int_semaphore to ifw_semaphore;

insert into ifw_currency
( currency, currency_id, name )
select from_currency, 0, from_currency
from int_exchange_rate
where from_currency not in ( select currency from ifw_currency );

insert into ifw_currency
( currency, currency_id, name )
select to_currency, 0, from_currency
from int_exchange_rate
where to_currency not in ( select currency from ifw_currency );

insert into ifw_exchange_rate
( from_currency, valid_from, to_currency, exchange_rate )
select from_currency, valid_from, to_currency, exchange_rate
from int_exchange_rate;


-- GLOBAL MAPPING

insert into ifw_taxgroup
( taxgroup, name )
select taxgroup, name 
from int_taxgroup;
  
insert into ifw_taxcode
( taxcode, name )
select taxcode, name
from int_taxcode;

insert into ifw_tax
( taxgroup, taxcode, valid_from, taxrate )
select taxgroup, taxcode, valid_from, taxrate
from int_tax;
  
insert into ifw_glaccount
( glaccount, name, taxcode, gla_type )
select glaccount, name, taxcode, gla_type
from int_glaccount;
  
insert into ifw_revenuegroup
( revenuegroup, name )
select revenuegroup, name
from int_revenuegroup;

insert into ifw_uom a
( uom, name )
select uom, name
from int_uom b
where b.uom not in ( select c.uom from ifw_uom c );

insert into ifw_uom_map
( rum, from_uom, to_uom, uom_factor, rounding )
select decode( charge_item, 'Q', 'DUR', 'R', 'REC', 'S', 'SND' ),
       from_uom, to_uom, uom_factor, rounding
from int_uom_map;

insert into ifw_rumgroup
( rumgroup, name, type )
values 
( 'EVENT', 'Event', 'S' );

insert into ifw_rumgroup
( rumgroup, name, type )
values 
( 'SND', 'Volume Sent', 'S' );

insert into ifw_rumgroup
( rumgroup, name, type )
values 
( 'REC', 'Volume Received', 'S' );

insert into ifw_rumgroup
( rumgroup, name, type )
values 
( 'DUR_SND', 'Duration + Volume Sent', 'S' );

insert into ifw_rumgroup
( rumgroup, name, type )
values 
( 'DUR_REC', 'Duration + Volume Received', 'S' );

insert into ifw_rumgroup_lnk
( rumgroup, rum, uom )
values
( 'EVENT', 'EVT', 'SEC' );

insert into ifw_rumgroup_lnk
( rumgroup, rum, uom )
values
( 'SND', 'SND', 'BYT' );

insert into ifw_rumgroup_lnk
( rumgroup, rum, uom )
values
( 'REC', 'REC', 'BYT' );

insert into ifw_rumgroup_lnk
( rumgroup, rum, uom )
values
( 'DUR_SND', 'DUR', 'SEC' );

insert into ifw_rumgroup_lnk
( rumgroup, rum, uom )
values
( 'DUR_SND', 'SND', 'BYT' );

insert into ifw_rumgroup_lnk
( rumgroup, rum, uom )
values
( 'DUR_REC', 'DUR', 'SEC' );

insert into ifw_rumgroup_lnk
( rumgroup, rum, uom )
values
( 'DUR_REC', 'REC', 'BYT' );

delete from ifw_service;

insert into ifw_service
( servicecode, name, rank, tos, 
  rumgroup, 
  def_glaccount, def_revenuegroup, parent_service, basic )
select servicecode, name, rank, tos, 
       decode( charge_item, 'D', 'DURATION', 'E', 'EVENT', 
               'S', 'SND', 'R', 'REC', 'V', 'VOLUME',
               'T', 'TOTAL', 'A', 'DUR_SND', 'B', 'DUR_REC' ), 
       def_glaccount, def_revenuegroup, parent_service, basic
from int_service;

insert into ifw_serviceclass
( servicecode, serviceclass, name )
select servicecode, serviceclass, name
from int_serviceclass;

insert into ifw_map_group
( map_group, name )
select map_group, name
from int_map_group;
  
insert into ifw_nosp
( map_group, rank, old_source, old_destination,
  a_prefix, new_source, new_destination )
select map_group, rank, old_source, old_destination,
       a_prefix, new_source, new_destination
from int_nosp;

insert into ifw_usagetype
( usagetype, name )
select calltype, name
from int_calltype;

insert into ifw_usagetype_map
( map_group, rank, usagetype, name, comparepattern )
select map_group, rank, calltype, name, comparepattern
from int_calltype_map;

insert into ifw_usageclass
( usageclass, name )
select callclass, name
from int_callclass;

insert into ifw_usageclass_map
( map_group, rank, ext_usageclass, usagetype, zone_ws,
  tariffclass, tariffsubclass, recordtype, 
  connecttype, connectsubtype, ss_packet, apn_address, transit_areacode,
  name, int_usageclass )
select map_group, rank, ext_callclass, calltype, aoczone,
       tariffclass, tariffsubclass, recordtype, 
       connecttype, connectsubtype, application, '.*', transit_areacode,
       name, int_callclass
from int_callclass_map;

insert into ifw_servicecode_map
( map_group, rank, name, ext_servicecode, usageclass, 
  locarind_vasevent, qos_requested, qos_used,
  recordtype, int_servicecode, int_serviceclass )
select map_group, rank, name, ext_servicecode, callclass, 
       locarind_vasevent, qos_requested, qos_used,
       recordtype, int_servicecode, int_serviceclass
from int_servicecode_map;

insert into ifw_apn_group
( apn_group, name )
select apn_group, name
from int_apn_group;

insert into ifw_apn_map
( apn_group, rank, servicecode, 
  accesspointname, zone_ws, zone_rt,
  pdp_address, new_zone_ws, new_zone_rt )
select apn_group, rank, servicecode, 
       accesspointname, zone_ws, zone_rt,
       pdp_address, new_zone_ws, new_zone_rt
from int_apn_map;


-- ZONING

insert into ifw_geographicalmodel
( geomodel, code, name, status )
select geomodel, to_char(geomodel), name, status
from int_geographicalmodel;

insert into ifw_geoareacode_lnk
( geomodel, areacode, name, longitude, latitude )
select geomodel, areacode, name, longitude, latitude
from int_geoareacode_lnk;

insert into ifw_zonemodel
( zonemodel, code, name, modeltype,
  frame, status, apn_group, geomodel )
select zonemodel, code, name, modeltype,
       frame, status, apn_group, geomodel
from int_zonemodel;

insert into ifw_impact_category
( impact_category, result, type, name )
select zone, result, 0, name
from int_zone;

insert into ifw_standard_zone
( zonemodel, origin_areacode, destin_areacode, 
  servicecode, valid_from, valid_to,
  zone_ws, zone_rt, name, alt_zonemodel )
select zonemodel, origin_areacode, destin_areacode, 
       servicecode, valid_from, valid_to,
       zone_ws, zone_rt, name, alt_zonemodel
from int_standard_zone;

insert into ifw_geographical_zone
( zonemodel, distance, servicecode,
  valid_from, valid_to, zone_ws, zone_rt,
  name, alt_zonemodel )
select zonemodel, distance, servicecode,
       valid_from, valid_to, zone_ws, zone_rt,
       name, alt_zonemodel
from int_geographical_zone;

insert into ifw_usc_group
( usc_group, name )
select czt_group, czt_name
from int_czt_group;

insert into ifw_usagescenario_map
( usc_group, zonemodel, rank, valid_from, valid_to,
  time_from, time_to, quantity_value, min_ws_amount,
  max_ws_amount, usageclass, usagetype, servicecode,
  serviceclass, zone_ws, zone_rt, new_usagetype,
  impact_category_ws, impact_category_rt, name )
select czt_group, zonemodel, rank, valid_from, valid_to,
       time_from, time_to, quantity_value, min_aoc_amount,
       max_aoc_amount, callclass, calltype, servicecode,
       serviceclass, zone_ws, zone_rt, new_calltype,
       new_zone_ws, new_zone_rt, name
from int_classtypezone_map


-- DISCOUNT

insert into ifw_discountmodel
( discountmodel, code, name, period )
select discountmodel, code, name, period
from int_discountmodel;

insert into ifw_discountmdl_ver
( discountmodel, version, valid_from, status )
select discountmodel, version, valid_from, status
from int_discountmdl_ver;

insert into ifw_discountrule
( discountrule, code, name )
select discountrule, code, name
from int_discountrule;

insert into ifw_discounttrigger
( discounttrigger, code, name )
select discounttrigger, code, name
from int_discounttrigger;

insert into ifw_discountmaster
( discountmaster, code, name )
select discountmaster, code, name
from int_discountmaster;

insert into ifw_discountmdl_cnf
( discountconfig, discountmodel, version, 
  rank, discounttrigger, discountrule )
select discountconfig, discountmodel, version, 
     rank, discounttrigger, discountrule
from int_discountmdl_cnf;

insert into ifw_discountstep
( discountstep, discountrule, rank, discountmaster,
  threshold_type, threshold_from, threshold_to,
  discount_type, grant_type, grant_proratedbeat,
  grant_units, grant_beat, grant_uom, 
  rollover_units, edr_enrichment )
select discountstep, discountrule, rank, discountmaster,
     decode( threshold_type, 'S', 'Q', 'R', 'Q', threshold_type ), 
     threshold_from, threshold_to,
     discount_type, decode( grant_type, 'S', 'Q', 'R', 'Q', grant_type),
     grant_proratedbeat, grant_units, grant_beat, grant_uom, 
     rollover_units, edr_enrichment
from int_discountstep;

insert into ifw_discountcondition
( discountcondition, discounttrigger, discountmaster,
  condition_base, condition_value )
select discountcondition, discounttrigger, discountmaster,
     decode( condition_base, 'S', 'Q', 'R', 'Q', condition_base ), 
     condition_value
from int_discountcondition;

--
-- !!! ATTENTION !!! The contents of ifw_discountdetail have to be checked manually !!!

insert into ifw_discountdetail
( discountmaster, rank, valid_from, valid_to, time_from, time_to,
  zonemodel, impact_category, servicecode, serviceclass, timemodel,
  timezone, pricemodel, ressource, rum, recordtype )
select discountmaster, rank, valid_from, valid_to, time_from, time_to,
     zonemodel, zone, servicecode, serviceclass, timemodel,
     timezone, pricemodel, '.*', '.*', 
     recordtype
from int_discountdetail;

-- !!! ATTENTION !!! The contents of ifw_discountdetail have to be checked manually !!!
--

insert into ifw_subs_account
( account, rateplan_code, period, discountstep, discountmaster,
  status, rollover_units, sum_charge, sum_quantity, sum_event,
  frame_charge, frame_quantity, frame_event, 
  disc_amount, disc_quantity )
select account, tariffmodel_code, period, sa.discountstep, sa.discountmaster,
     status, sa.rollover_units, sum_charge, sum_quantity, sum_event,
     frame_charge, frame_quantity, frame_event, 
     disc_amount, disc_quantity
from int_subs_account sa, int_discountstep ds
where ds.discountstep = sa.discountstep and ds.grant_type = 'Q';

insert into ifw_subs_account
( account, rateplan_code, period, discountstep, discountmaster,
  status, rollover_units, sum_charge, sum_quantity, sum_event,
  frame_charge, frame_quantity, frame_event, 
  disc_amount, disc_quantity )
select account, tariffmodel_code, period, sa.discountstep, sa.discountmaster,
     status, sa.rollover_units, sum_charge, sum_quantity, sum_event,
     frame_charge, frame_vol_sent, frame_event, 
     disc_amount, disc_vol_sent
from int_subs_account sa, int_discountstep ds
where ds.discountstep = sa.discountstep and ds.grant_type = 'S';

insert into ifw_subs_account
( account, rateplan_code, period, discountstep, discountmaster,
  status, rollover_units, sum_charge, sum_quantity, sum_event,
  frame_charge, frame_quantity, frame_event, 
  disc_amount, disc_quantity )
select account, tariffmodel_code, period, sa.discountstep, sa.discountmaster,
     status, sa.rollover_units, sum_charge, sum_quantity, sum_event,
     frame_charge, frame_vol_received, frame_event, 
     disc_amount, disc_vol_received
from int_subs_account sa, int_discountstep ds
where ds.discountstep = sa.discountstep and ds.grant_type = 'R';


-- RATING

-- Calendar and Holidays
insert into ifw_calendar
( calendar, code, name )
select calendar, to_char(calendar), name
from int_calendar;

insert into ifw_holiday
( calendar, holiday, recurring, name )
select calendar, holiday, recurring, name
from int_holiday;

-- Timemodel
insert into ifw_timemodel
( timemodel, code, name )
select timemodel, code, name
from int_timemodel;

insert into ifw_daycode
( daycode, code, name, dateday,
  monday, tuesday, wednesday, thursday,
  friday, saturday, sunday, holiday )
select daycode, code, name, dateday,
       monday, tuesday, wednesday, thursday,
       friday, saturday, sunday, holiday
from int_daycode;

insert into ifw_timeinterval
( interval, code, name, time_from, time_to )
select interval, code, name, time_from, time_to
from int_timeinterval;

insert into ifw_timezone
( timezone, code, name )
select timezone, code, name
from int_timezone;

insert into ifw_timemodel_lnk
( timemodel, daycode, interval, valid_from, timezone, valid_to )
select timemodel, daycode, interval, valid_from, timezone, valid_to
from int_timemodel_lnk;

-- Pricemodel
insert into ifw_pricemodel
( pricemodel, code, name )
select pricemodel, code, name
from int_pricemodel;

insert into ifw_currency
( currency, currency_id, name )
select distinct currency, 0, currency
from int_tariffmodel
where currency not in ( select currency from ifw_currency );

insert into ifw_resource
( resource_name, symbol, type, currency )
select distinct currency, currency, 'M', currency
from int_tariffmodel;

--
-- !!! ATTENTION !!! The RESOURCE_NAME needs to be set manually after
-- !!! ATTENTION !!! migration. This cannot be done automatically.

insert into ifw_currency
( currency, currency_id, name )
values
( 'ZZZ', 0, 'Dummy entry for migration purposes only.' );

insert into ifw_resource
( resource_name, symbol, type, currency )
values
( 'ZZZ', 'ZZZ', 'O', 'ZZZ' );

insert into ifw_pricemodel_step
( pricemodel, valid_from, resource_name, rum, 
  step, threshold_from, threshold_to, beat,
  charge, charge_base, frame )
select pricemodel, valid_from, 'ZZZ', 
     decode( charge_item, 'Q', 'DUR', 'S', 'SND', 'R', 'REC' ), 
       step, threshold_from, threshold_to, beat, 
       charge, charge_base, nvl( frame, 0 )
from int_pricemodel_step;

-- !!! ATTENTION !!! The RESOURCE_NAME needs to be set manually after
-- !!! ATTENTION !!! migration. This cannot be done automatically.
--

insert into ifw_rateplan
( rateplan, code, name, status, system_brand,
  modeltype, splitting, calendar, utc_time_offset,
  currency, taxtreatment )
select tariffmodel, code, name, status, system_brand,
       modeltype, splitting, calendar, utc_time_offset,
       currency, taxtreatment
from int_tariffmodel;

insert into ifw_rsc_group
( rsc_group, name )
select tsc_group, tsc_name
from int_tsc_group;

insert into ifw_rateservice_map
( rsc_group, rank, valid_from, valid_to, rateplan, qos_requested, qos_used,
  usageclass, usagetype, servicecode, serviceclass, impact_category, 
  new_servicecode, new_serviceclass, name )
select tsc_group, rank, valid_from, valid_to, concat( to_char(tariffmodel), '.*' ), qos_requested, qos_used,
  callclass, calltype, servicecode, serviceclass, zone, 
  new_servicecode, new_serviceclass, name
from int_tariffserviceclass;

insert into ifw_rateplan_ver
( rateplan, version, valid_from, status, zonemodel,
  basic_rateplan, basic_version, basic, discountmodel )
select tariffmodel, version, valid_from, status, zonemodel,
       basic_tariffmodel, basic_version, basic, discountmodel
from int_tariffmodel_ver;

insert into ifw_taxcode
( taxcode, name )
values
( 'DUMMY', 'This is a dummy TAXCODE for migration purposes.' );

insert into ifw_glaccount
( glaccount, name, taxcode, gla_type )
values
( 'DUMMY', 'This is a dummy GL/ACCOUNT for migration purposes.', 'DUMMY', 'R' );

insert into ifw_rateplan_cnf
( rateplan, version, servicecode, serviceclass, impact_category,
  timemodel, timezone, pricemodel, alt_pricemodel, 
  passthrough, addon_type, addon_charge, glaccount, revenuegroup )
select tariffmodel, version, servicecode, serviceclass, zone,
       timemodel, timezone, pricemodel, alt_pricemodel, 
       passthrough, addon_type, addon_charge, nvl(glaccount, 'DUMMY'), revenuegroup
from int_tariffmodel_cnf;

-- Specialdayrates
insert into ifw_specialday_lnk
( rateplan, version, specialdayrate )
select tariffmodel, version, specialdayrate
from int_specialday_lnk;

insert into ifw_specialdayrate
( specialdayrate, code, name, valid_from, valid_to,
  time_from, time_to, discount_type, discount_value )
select specialdayrate, to_char(specialdayrate), name, valid_from, valid_to,
     time_from, time_to, discount_type, discount_value
from int_specialdayrate;

-- Reteadjust
insert into ifw_rateadjust
( rateplan, version, rank, valid_from, valid_to,
  time_from, time_to, quantity_value, usageclass,
  usagetype, servicecode, serviceclass,
  impact_category, source_network, destin_network,
  discount_type, discount_value, name )
select tariffmodel, version, rank, valid_from, valid_to,
     time_from, time_to, quantity_value, callclass,
     calltype, servicecode, serviceclass,
     zone, source_network, destin_network,
     discount_type, discount_value, name
from int_tariffdiscount_lnk;


-- SCRIPTING

drop table ifw_iscript;

rename int_iscript to ifw_iscript;

insert into ifw_ruleset
( ruleset, name )
select ruleset, name
from int_ruleset;

drop table ifw_rule cascade constraints;

rename int_rule to ifw_rule;

insert into ifw_rulesetlist
( ruleset, rank, rule, name )
select ruleset, rank, rule, name
from int_rulesetlist;

drop table ifw_ruleitem cascade constraints;

rename int_ruleitem to ifw_ruleitem;

alter table IFW_RULESETLIST
  add constraint FK_IFW_RSL_RUL foreign key (RULE) references IFW_RULE (RULE);


-- Segments
     
insert into ifw_segment
( segment, name )
select segment, name
from int_segment;

insert into ifw_segzone_lnk
( segment, valid_from, zonemodel, valid_to )
select segment, valid_from, zonemodel, valid_to
from int_segzone_lnk;

insert into ifw_segrate_lnk
( segment, valid_from, rateplan, valid_to )
select segment, valid_from, tariffmodel, valid_to
from int_segtariff_lnk;


-- INTERCONNECTION

insert into ifw_networkoperator
( no, code, name, notype, cac, cic, plmn_id, 
  tadig, currency, taxgroup )
select no, code, name, notype, cac, cic, plmn_id, 
     tadig, currency, taxgroup
from int_networkoperator;

insert into ifw_taxgroup
( taxgroup, name )
values
( 'MIGRATE', 'Dummy Taxgroup for IC migration purposes' );

insert into ifw_networkoperator
( no, code, name, notype, currency, taxgroup )
values
( 999999999, 'MIGRATE', 'Dummy NO for migration purposes',
  'X', 'ZZZ', 'MIGRATE' );

insert into ifw_networkmodel
( networkmodel, code, name, calcmode, modeltype, 
  use_switch_for_ident, use_fixcost, 
  system_brand, rateplan, no, currency )
select networkmodel, code, name, calcmode, modeltype, 
     use_switch_for_ident, use_fixcost, 
     system_brand, tariffmodel, 999999999, 'ZZZ' 
from int_networkmodel;

insert into ifw_poi
( poi, name, valid_from, valid_to, 
  areacode, utc_time_offset, status )
select distinct poi, name, to_date('19900101', 'YYYYMMDD'), NULL, 
     areacode, utc_time_offset, status
from int_poi;

insert into ifw_poiarea_lnk
( networkmodel, poi, valid_from, areacode, valid_to )
select networkmodel, poi, valid_from, areacode, valid_to
from int_poiarea_lnk;

insert into ifw_switch
( no, switch, valid_from, valid_to, name, status )
select no, switch, to_date('19900101', 'YYYYMMDD'), NULL, name, status
from int_switch;

insert into ifw_trunk
( no, switch, trunk, valid_from, valid_to,
  name, trunktype, status, connected_no )
select sw.no, sw.switch, trunk, 
     to_date('19900101', 'YYYYMMDD'), NULL,
     tr.name, trunktype, tr.status, tr.no
from int_trunk tr, int_poi poi, int_switch sw
where poi.poi = tr.poi and sw.SWITCH = poi.SWITCH;

insert into ifw_icproduct_group
( networkmodel, icproduct_group, name )
select networkmodel, icproduct_group, name
from int_icproduct_group;

insert into ifw_trunk_cnf
( networkmodel, no, switch, trunk, direction,
  valid_from, valid_to, poi, icproduct_group )
select trc.networkmodel, sw.no, sw.switch, trc.trunk,
     direction, valid_from, valid_to, tr.poi,
     icproduct_group
from int_trunk_cnf trc, int_trunk tr, int_poi poi, int_switch sw
where tr.networkmodel = trc.networkmodel and
    tr.trunk = trc.trunk and
    poi.poi = tr.poi and
    sw.switch = poi.switch;

insert into ifw_icproduct
( icproduct, name, valid_from, valid_to, status )
select distinct icproduct, name, valid_from, NULL, 'A'
from int_icproduct;

insert into ifw_icproduct_cnf
( networkmodel, icproduct_group, rank, valid_from,
  valid_to, name, source_network, destin_network,
  origin_areacode, destin_areacode, transit_areacode, 
  recordtype, servicecode, serviceclass,
  usageclass, icproduct )
select networkmodel, icproduct_group, rank, valid_from,
     valid_to, name, source_network, destin_network,
     origin_areacode, destin_areacode, transit_areacode, 
     recordtype, servicecode, '.*',
     callclass, icproduct
from int_icproduct_cnf;

insert into ifw_icproduct_rate
( networkmodel, no, icproduct, valid_from, valid_to,
  zone_direction, zone_type, bill_direction,
  rateplan, alt_rateplan, fixcost )
select distinct icc.networkmodel, icp.no, icp.icproduct, nvl(icl.valid_from,icp.VALID_FROM),
     NULL, icp.zone_direction, icp.zone_type, icp.bill_direction, 
     nvl(icl.tariffmodel,icp.TARIFFMODEL), nvl(icl.alt_tariffmodel,icl.ALT_TARIFFMODEL), icp.fixcost
from int_icproduct_cnf icc, int_icproduct icp, int_icno_lnk icl
where icp.icproduct = icc.icproduct and icl.icproduct(+) = icp.icproduct;

insert into ifw_noproduct
( no, productcode, valid_from, name, currency, taxcode )
select no, productcode, valid_from, name, currency, taxcode
from int_noproduct;

insert into ifw_noproduct_cnf
( icproduct, timezone, impact_category, valid_from, 
  valid_to, no, productcode )
select icproduct, timezone, zone, valid_from, 
     valid_to, no, productcode
from int_noproduct_cnf;

insert into ifw_no_billrun
( networkmodel, no, billrun, boc_date, eoc_date, 
  billrun_date, status )
select networkmodel, no, billrun, boc_date, eoc_date,
     billrun_date, status
from int_no_billrun br, int_networkmodel nm;

spool off;
