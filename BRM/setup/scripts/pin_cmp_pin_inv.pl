#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_pin_inv.pl /cgbubrm_mainbrm.portalbase/3 2018/03/30 02:42:05 mkothari Exp $ 
# 
# Copyright (c) 1999, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for pin_inv 
#
#=============================================================

# If running stand alone, without pin_setup
if ( ! ( $RUNNING_IN_PIN_SETUP eq TRUE ) )
{
   require "./pin_res.pl";
   require "./pin_functions.pl";
   require "../pin_setup.values";

   &ConfigureComponentCalledSeparately ( $0 );
}


#####
#
# Configure pin_inv files
#
#####
sub configure_pin_inv_config_files {
  local( %CM ) = %MAIN_CM;
  local( %DM ) = %MAIN_DM;

  &ReadIn_PinCnf( "pin_cnf_mta.pl" );
  $PIN_INV_PINCONF_HEADER = $MTA_PINCONF_HEADER;

  &ReadIn_PinCnf( "pin_cnf_pin_inv.pl" );
  &AddArrays( \%MTA_PINCONF_ENTRIES, \%PIN_INV_PINCONF_ENTRIES );

  $MAIN_CM{'login_name'} = "invoicing";
  $MAIN_CM{'user_id'} = "403";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%PIN_INV_PINCONF_ENTRIES );

  &Configure_PinCnf( $PIN_INV{'location'}."/".$PINCONF, 
                     $PIN_INV_PINCONF_HEADER,
                     %PIN_INV_PINCONF_ENTRIES );
  $MAIN_CM{'login_name'} = $CM{'login_name'};
  $MAIN_CM{'user_id'} = $CM{'user_id'};
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_araframework.pl" );
  if ( -f $PIN_INV{'location'}."/".$PINCONF ) {
     &AddPinConfEntries( $PIN_INV{'location'}."/".$PINCONF, %RA_ENABLE_ERA_PINCONF_ENTRIES );
  }

}	
1;

#######
#
# Configuring database for pin_inv
#
#######
#sub configure_pin_inv_database {
#}
