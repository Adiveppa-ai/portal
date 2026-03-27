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
-- $RCSfile: update_v4-10-04_v4-30-01_AggreGate.sql,v $
-- $Revision: 1.1 $
-- $Author: pengelbr $
-- $Date: 2001/07/06 07:43:43 $
-- $Locker:  $
--------------------------------------------------------------------------------
-- $Log: update_v4-10-04_v4-30-01_AggreGate.sql,v $
-- Revision 1.1  2001/07/06 07:43:43  pengelbr
-- PETS #36686 Create a database migration script from v4-10-04 to v4-30-00
--
-- Revision 1.1  2001/06/19 13:58:16  pengelbr
-- Most recent changes for v4-30-00
--
--------------------------------------------------------------------------------

spool update_v4-10-04_v4-30-01_AggreGate.log


-- AGGREGATE

insert into ifw_queue
( import_table, destination_table, status )
select import_table, destination_table, status
from agg_queue;

insert into ifw_dictionary
( import_table, import_column, destination_column,
  expand_value, key, column_group )
select import_table, import_column, destination_column,
       expand_value, key, column_group
from agg_dictionary;

insert into ifw_scenario
( scenario_id, code, name, edrc_desc, default_tab_name, 
  default_flushmode, default_threshold, default_temp_dir,
  default_done_dir, default_ctl_dir, default_field_delimiter,
  status )
select scenario_id, code, name, 'PORTAL', default_tab_name, 
       default_flushmode, default_threshold, default_temp_dir,
       default_done_dir, default_ctl_dir, default_field_delimiter,
       decode( scenario_status, 0, 'D', 1, 'A' )
from agg_scenario;

insert into ifw_condition
( condition_id, scenario_id, field_id, 
  value, datatype, status )
select condition_id, scenario_id, field_id, condition_value, 
       decode( condition_datatype, '0', 'S', '1', 'N', '2', 'D' ), 
       decode( condition_status, 0, 'D', 1, 'A' )
from agg_edrcfield ae, agg_condition c, ifw_edrc_field ie
where ae.COL_OBJ_ID = c.COL_OBJ_ID and
      field_name = replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( 
                            internal_fieldname, 
                            'ASSOCIATED_CHARGE.', 'DETAIL.ASS_CBD.'), 
                            'MF.', 'CP.'),
                            'TARIFFMODEL', 'RATEPLAN'),
                            'L.CHARGED_A', 'L.RETAIL_CHARGED_A'),
                            'AOC_A', 'WHOLESALE_CHARGED_A'),
                            'CHARGEABLE_QUANTITY_VALUE', 'DURATION'),
                            'ROUNDED_CHARGED', 'ROUNDED'),
                            '_ID', '_CODE'),
                            'SPECIALIST_SYSTEM_', 'SYSTEM_BRAND_'),
                            'AOC_ZONE', 'WHOLESALE_IMPACT_CATEGORY'),
                            '.PORT_NUMBER', '.ASS_GSMW_EXT.PORT_NUMBER'),
                            'OR_B', 'EURB'), 'NETWORK_OPERATOR', 'NETWORK_OPERATOR_CODE'), 'EURB', 'OR_B'),
                            'ZONE_RESULT_VALUE', 'IMPACT_CATEGORY') and
      edrc_desc = 'PORTAL';

insert into ifw_aggregation
( aggregation_id, scenario_id, field_id, rank,
  col_name, precision, aggregation_function, status )
select aggregation_id, scenario_id, field_id, rank, col_name, precision, 
       decode( aggregation_function, 0, 'S', 1, 'C', 2, 'Q' ), 
       decode( aggregation_status, 0, 'D', 1, 'A' )
from agg_edrcfield ae, agg_aggregation a, ifw_edrc_field ie
where ae.COL_OBJ_ID = a.COL_OBJ_ID and
      field_name = replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( 
                            internal_fieldname, 
                            'ASSOCIATED_CHARGE.', 'DETAIL.ASS_CBD.'), 
                            'MF.', 'CP.'),
                            'TARIFFMODEL', 'RATEPLAN'),
                            'L.CHARGED_A', 'L.RETAIL_CHARGED_A'),
                            'AOC_A', 'WHOLESALE_CHARGED_A'),
                            'CHARGEABLE_QUANTITY_VALUE', 'DURATION'),
                            'ROUNDED_CHARGED', 'ROUNDED'),
                            '_ID', '_CODE'),
                            'SPECIALIST_SYSTEM_', 'SYSTEM_BRAND_'),
                            'AOC_ZONE', 'WHOLESALE_IMPACT_CATEGORY'),
                            '.PORT_NUMBER', '.ASS_GSMW_EXT.PORT_NUMBER'),
                            'OR_B', 'EURB'), 'NETWORK_OPERATOR', 'NETWORK_OPERATOR_CODE'), 'EURB', 'OR_B'),
                            'ZONE_RESULT_VALUE', 'IMPACT_CATEGORY') and
      edrc_desc = 'PORTAL';

insert into ifw_grouping
( grouping_id, scenario_id, field_id, rank, col_name,
  col_format, datatype, status )
select grouping_id, scenario_id, field_id, rank, col_name, col_format, 
  decode( grouping_datatype, '0', 'S', '1', 'N', '2', 'D' ),
  decode( grouping_status, 0, 'D', 1, 'A' )
from agg_edrcfield ae, agg_grouping g, ifw_edrc_field ie
where ae.COL_OBJ_ID = g.COL_OBJ_ID and
      field_name = replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( replace( 
                            internal_fieldname, 
                            'ASSOCIATED_CHARGE.', 'DETAIL.ASS_CBD.'), 
                            'MF.', 'CP.'),
                            'TARIFFMODEL', 'RATEPLAN'),
                            'L.CHARGED_A', 'L.RETAIL_CHARGED_A'),
                            'AOC_A', 'WHOLESALE_CHARGED_A'),
                            'CHARGEABLE_QUANTITY_VALUE', 'DURATION'),
                            'ROUNDED_CHARGED', 'ROUNDED'),
                            '_ID', '_CODE'),
                            'SPECIALIST_SYSTEM_', 'SYSTEM_BRAND_'),
                            'AOC_ZONE', 'WHOLESALE_IMPACT_CATEGORY'),
                            '.PORT_NUMBER', '.ASS_GSMW_EXT.PORT_NUMBER'),
                            'OR_B', 'EURB'), 'NETWORK_OPERATOR', 'NETWORK_OPERATOR_CODE'), 'EURB', 'OR_B'),
                            'ZONE_RESULT_VALUE', 'IMPACT_CATEGORY') and
      edrc_desc = 'PORTAL';

insert into ifw_class
( class_id, code, name, datatype )
select class_id, code, name, 
       decode( class_datatype, 0, 'S', 1, 'N', 2, 'D' )
from agg_class;

insert into ifw_classitem
( classitem_id, code, name, datatype, value )
select classitem_id, code, name, 
       decode( classitem_datatype, 0, 'S', 1, 'N', 2, 'D' ), 
       classitem_value
from agg_classitem
where classitem_id != 0;

insert into ifw_class_lnk
( class_id, classitem_id )
select class_id, classitem_id
from agg_class_lnk;

insert into ifw_grouping_cnf
( grouping_cnf_id, grouping_id, class_id )
select grouping_cnf_id, grouping_id, class_id
from agg_grouping_cnf
where grouping_id in ( select grouping_id from ifw_grouping );

insert into ifw_classcon
( classcon_id, node_grouping_cnf_id, next_grouping_cnf_id )
select classcon_id, node_grouping_cnf_id, next_grouping_cnf_id
from agg_classcon;

insert into ifw_classcon_lnk
( classcon_id, classitem_id )
select classcon_id, classitem_id
from agg_classcon_lnk;

spool off;
