#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_pin_export_price.pl /cgbubrm_mainbrm.portalbase/1 2018/03/30 02:42:05 mkothari Exp $ 
# 
# Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the export price Component
#
#=============================================================

use Cwd;

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
# Configure pin export price files
#
#####
sub configure_pin_export_price_config_files {
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;

  $MAIN_CM{'login_name'} = "load_utils";
  $MAIN_CM{'user_id'} = "413";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_mta.pl" );
  
    # Add MTA entries and Connect entries

  &AddArrays( \%MTA_PINCONF_ENTRIES, \%CONNECT_PINCONF_ENTRIES );

  
  
  &Configure_PinCnf( $EXPORT_PRICE{'location'}."/".$PINCONF, 
                     $CONNECT_PINCONF_HEADER, 
                     %CONNECT_PINCONF_ENTRIES );
  $MAIN_CM{'login_name'} = $CM{'login_name'};
  $MAIN_CM{'user_id'} = $CM{'user_id'};                      
}



#######
#
# Configuring database for pin export price
#
#######
#sub configure_pin_export_price_database {
#}

1;
