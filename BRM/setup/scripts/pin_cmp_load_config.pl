#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
#  @$Id: pin_cmp_load_config.pl /cgbubrm_mainbrm.portalbase/2 2018/03/30 02:42:05 mkothari Exp $
# 
# Copyright (c) 1999, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the load_config Component
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
# Configure pin_rerate files
#
#####
sub configure_load_config_config_files {
  local( %CM ) = %MAIN_CM;
  local( %DM ) = %MAIN_DM;

  # create directory app/load_config as needed
  if ( ! -e "$PIN_HOME/apps" ){
   mkdir ("$PIN_HOME/apps", 0755) || die "Unable to create $PIN_HOME/apps directory";
  }
  if ( ! -e "$PIN_HOME/apps/load_config" ){
   mkdir ("$PIN_HOME/apps/load_config", 0755) || die "Unable to create $PIN_HOME/apps/load_config directory";
  }
  if ( ! -e "$PIN_HOME/apps/pin_state_change" ){
   mkdir ("$PIN_HOME/apps/pin_state_change", 0755) || die "Unable to create $PIN_HOME/apps/pin_state_change directory";
  }

  # create directory var as needed
  if ( ! -e "$PIN_HOME/var" ){
   mkdir ("$PIN_HOME/var", 0755) || die "Unable to create $PIN_HOME/var directory";
  }
  if ( ! -e "$PIN_HOME/var/load_config" ){
   mkdir ("$PIN_HOME/var/load_config", 0755) || die "Unable to create $PIN_HOME/var/load_config directory";
  }
  if ( ! -e "$PIN_HOME/var/pin_state_change" ){
   mkdir ("$PIN_HOME/var/pin_state_change", 0755) || die "Unable to create $PIN_HOME/var/pin_state_change directory";
  }

  my $MY_PINCONF=$PIN_HOME."/apps/load_config/".$PINCONF;

  $MAIN_CM{'login_name'} = "load_utils";
  $MAIN_CM{'user_id'} = "413";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_load_config.pl" );

  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%LOAD_CONFIG_PINCONF_ENTRIES );
  &Configure_PinCnf( $MY_PINCONF,
	             $LOAD_CONFIG_PINCONF_HEADER,
                     %LOAD_CONFIG_PINCONF_ENTRIES );

  if(!defined($psv)) {
      $MY_PINCONF=$PIN_HOME."/setup/scripts/".$PINCONF;
      &AddPinConfEntries( $MY_PINCONF, %LOAD_CONFIG_PINCONF_ENTRIES);
  }

  $MY_PINCONF=$PIN_HOME."/apps/pin_state_change/".$PINCONF;
  $MAIN_CM{'login_name'} = "cust_mgnt";
  $MAIN_CM{'user_id'} = "406";
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_pin_state_change.pl" );

  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%PIN_STATE_CHANGE_PINCONF_ENTRIES );
  &Configure_PinCnf( $MY_PINCONF,
                     $PIN_STATE_CHANGE_PINCONF_HEADER,
                     %PIN_STATE_CHANGE_PINCONF_ENTRIES );
  $MAIN_CM{'login_name'} = $CM{'login_name'};
  $MAIN_CM{'user_id'} = $CM{'user_id'};
  #
  # If the apps/pin_state_change/pin.conf is there, add the entries for logfile
  # If not, add the entries to the temporary pin.conf file and append.
  #
  if ( -f "$PIN_HOME/apps/pin_state_change"."/".$PINCONF )
  {
    &ReplacePinConfEntries( "$PIN_HOME/apps/pin_state_change"."/".$PINCONF, %PIN_MTA_ENTRIES );
  }
  else
  {
    # Create temporary file, if it does not exist.
    $TEMP_PIN_CONF_FILE = $PIN_HOME."/".$IDS_TEMP_PIN_CONF;
    open( PINCONFFILE, ">> $TEMP_PIN_CONF_FILE" );
    close( PINCONFFILE );

    &ReplacePinConfEntries( "$TEMP_PIN_CONF_FILE", %PIN_MTA_ENTRIES );
  }
}
1;
