#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_perf.pl /cgbubrm_mainbrm.portalbase/2 2018/03/30 02:42:04 mkothari Exp $ 
# 
# Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the PERF Manager
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

##########################################
#
# Configure Perf Manager pin.conf files
#
##########################################
sub configure_perf_config_files {  
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;
  local ( @FileReadIn );
  local ( $Start );  
  &ReadIn_PinCnf( "pin_cnf_perf.pl" );

  &Configure_PinCnf( $PERF_SIM{'pin_cnf_location'}."/".$PINCONF,
                                    $PERF_PINCONF_HEADER,
                                %PERF_PINCONF_ENTRIES ); 

  &Configure_PinCnf( $PERF_SQL{'pin_cnf_location'}."/".$PINCONF,
                                    $PERF_PINCONF_HEADER,
                                %PERF_PINCONF_ENTRIES ); 
    
}
1;


#######
#
# Configuring database for Perf Manager
#
#######
#sub configure_perf_database {
#}
