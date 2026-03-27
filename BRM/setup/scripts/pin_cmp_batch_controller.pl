#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_batch_controller.pl /cgbubrm_mainbrm.portalbase/4 2018/03/30 02:42:03 mkothari Exp $ 
# 
# Copyright (c) 2000, 2024, Oracle and/or its affiliates.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the BATCH_CONTROLLER Component
#


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
# Configure BATCH CONTROLLER files
#
#####
sub configure_batch_controller_config_files {

  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;

  #
  #  Configure Infranet.properties with current values ...
  #

  $i = 0;
  open( PROPFILE, "+< $BATCH_CONTROLLER{'location'}/Infranet.properties" ) || die( "Can't open $BATCH_CONTROLLER{'location'}/Infranet.properties" );
  @Array_PROP = <PROPFILE>;
  seek( PROPFILE, 0, 0 );
  while ( <PROPFILE> )
  {
    $_ =~ s/^\s*infranet\.connection.*/#infranet\.connection	pcp:\/\/root.$DM{'db_num'}:$CM{'pcm_admin_passwd'}\@$CM{'hostname'}:$CM{'port'}\/service\/pcm_client/i;
    $_ =~ s/^\s*infranet\.log\.file.*/infranet\.log\.file =	$BATCH_CONTROLLER{'location'}\/batch_controller.pinlog/i;
    $Array_PROP[$i++] = $_;
  }
  seek( PROPFILE, 0, 0 );
  print PROPFILE @Array_PROP;
  print PROPFILE "\n";
  truncate( PROPFILE, tell( PROPFILE ) );
  close( PROPFILE );
  chmod(0640,"$BATCH_CONTROLLER{'location'}/Infranet.properties");


  #
  # Add entries to apps/sample_handler/pin.conf ...
  #

  $MAIN_CM{'login_name'} = "java_client";
  $MAIN_CM{'user_id'} = "409";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_batch_controller.pl" );

  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%BATCH_CONTROLLER_PINCONF_ENTRIES );

  &Configure_PinCnf( $BATCH_CONTROLLER{'sample_handler_location'}."/".$PINCONF,
                     $BATCH_CONTROLLER_PINCONF_HEADER,
                     %BATCH_CONTROLLER_PINCONF_ENTRIES );

  $MAIN_CM{'login_name'} = $CM{'login_name'};
  $MAIN_CM{'user_id'} = $CM{'user_id'};
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );

}
1;


#######
#
# Configuring database for BATCH CONTROLLER
#
#######
#sub configure_batch_controller_database {
