#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_eet.pl /cgbubrm_mainbrm.portalbase/2 2018/03/30 02:42:06 mkothari Exp $ 
# 
# Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the Event Extraction Tool
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


#################################################################
#
# Configure Event Extraction files
#
#################################################################
sub configure_eet_config_files {
  local( %CM ) = %MAIN_CM;
  local( %DM ) = %MAIN_DM;

  $MAIN_CM{'login_name'} = "rerating";
  $MAIN_CM{'user_id'} = "407";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_eet.pl" );
  
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%EET_PINCONF_ENTRIES );
  &Configure_PinCnf( $EVENT_EXTRACTION_TOOL{'location'}."/".$PINCONF,
                     $EET_PINCONF_HEADER,
                     %EET_PINCONF_ENTRIES );
  $MAIN_CM{'login_name'} = $CM{'login_name'};
  $MAIN_CM{'user_id'} = $CM{'user_id'};
}
1;


#######
#
# Configuring database for Event Extraction
#
#######
#sub configure_eet_database {
#}
