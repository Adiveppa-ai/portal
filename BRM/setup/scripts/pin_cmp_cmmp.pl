#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_cmmp.pl /cgbubrm_mainbrm.portalbase/2 2018/03/30 02:42:05 mkothari Exp $ 
# 
# Copyright (c) 1999, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the Connection Manager Main Process Component
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
# Configure CMMP files
#
#####
sub configure_cmmp_config_files {
  %CM = %MAIN_CM;
  &ReadIn_PinCnf( "pin_cnf_cmmp.pl" );
  &Configure_PinCnf( $CMMP{'location'}."/".$PINCONF, 
                     $CMMP_PINCONF_HEADER, 
                     %CMMP_PINCONF_ENTRIES );
                     
  #
  # update pin_ctl.conf
  #                     
  &ReplacePinCtlConfEntries( "${PIN_HOME}/bin/pin_ctl.conf", 
			"__CMMP_PORT__",
			"$CMMP{'port'}" );                     
}
1;

#######
#
# Configuring database for CMMP
#
#######
#sub configure_cmmp_database {
#}
