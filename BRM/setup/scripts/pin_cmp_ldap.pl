#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_ldap.pl /cgbubrm_mainbrm.portalbase/4 2018/03/30 02:42:04 mkothari Exp $ 
#    
# Copyright (c) 2000, 2024, Oracle and/or its affiliates.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the LDAP Component
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
# Configure LDAP files
#
#####
sub configure_ldap_config_files {
  local ( %QM ) = %LDAP;     # For use by pin_cnf_qm.pl
  local ( %CM ) = %MAIN_CM;  # For use by pin_cnf_connect.pl
  local ( %DM ) = %MAIN_DM;  # For use by pin_cnf_connect.pl

  $CurrentComponent_ORIG = $CurrentComponent;
  $CurrentComponent = "dm_ldap";
  $LDAP{'env'} = "ldap";

  $MAIN_CM{'login_name'} = "load_utils";
  $MAIN_CM{'user_id'} = "413";
  &ReadIn_PinCnf( "pin_cnf_qm.pl" );
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_ldap.pl" );
  &ReadIn_PinCnf( "pin_cnf_mta.pl" );
 
  #Create a link for the correct version of the dm_ldap file for Unix platforms
  &createlink();
  
  # First, inherit the QM PINCONF ENTRIES ...
  &AddArrays( \%QM_PINCONF_ENTRIES, \%LDAP_PINCONF_ENTRIES );

  # Add MTA entries and LDAP connect entries
  &AddArrays( \%MTA_PINCONF_ENTRIES, \%LDAP_CONNECT_PINCONF_ENTRIES );

  # Next, inherit the CONNECT PINCONF ENTRIES ...
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%LDAP_CONNECT_PINCONF_ENTRIES );

  # Add entries to the LDAP sys pin.conf file ...
  &Configure_PinCnf( $LDAP{'location'}."/".$PINCONF, $LDAP_PINCONF_HEADER, %LDAP_PINCONF_ENTRIES );

  # Add entries to the LDAP apps pin.conf file ...
  &Configure_PinCnf( $LDAP{'app_location'}."/".$PINCONF, $CONNECT_PINCONF_HEADER, %LDAP_CONNECT_PINCONF_ENTRIES );

  # Add entries for the LDAP load_channel_config.
  &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%LDAP_CHANNEL_PINCONF_ENTRIES );
 
  &Configure_PinCnf( $LDAP{'channel_location'}."/".$PINCONF, $CONNECT_PINCONF_HEADER, %LDAP_CHANNEL_PINCONF_ENTRIES );
  $MAIN_CM{'login_name'} = $CM{'login_name'};
  $MAIN_CM{'user_id'} = $CM{'user_id'};
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );

  #
  # If the CM is there, add the entries to it.
  # If not, add the entries to the temporary pin.conf file.
  #
  if ( -f $CM{'location'}."/".$PINCONF )
  {
    open( PINCONFFILE, $CM{'location'}."/".$PINCONF );
    @FileReadIn = <PINCONFFILE>;
    close( PINCONFFILE );

    $Start = &LocateEntry( "fm_trans_pol_fm_required", @FileReadIn );
    if( $Start == -1 ) {
      &AddArrays( \%TRANSPOL_FM_PINCONF_ENTRIES, \%LDAP_CM_ENTRIES );
    }
    &ReplacePinConfEntries( $CM{'location'}."/".$PINCONF, %LDAP_CM_ENTRIES );
  }
  else
  {
    # Create temporary file, if it does not exist.
    $TEMP_PIN_CONF_FILE = $PIN_HOME."/".$IDS_TEMP_PIN_CONF;
    open( PINCONFFILE, ">> $TEMP_PIN_CONF_FILE" );
    close( PINCONFFILE );
    &ReplacePinConfEntries( $TEMP_PIN_CONF_FILE, %LDAP_CM_ENTRIES );

    # Display a message saying to append this file to cm/pin.conf file.
    &Output( STDOUT, $IDS_APPEND_PIN_CONF_MESSAGE,
                        $CM{'location'}."/".$PINCONF,
                        $CurrentComponent,
                        $TEMP_PIN_CONF_FILE );
 
    if ( $^O =~ /win/i )
    {
      &Output( STDOUT, "\nPress enter to continue " );
      $TmpInput = <STDIN>;
    }
  }

  $CurrentComponent = $CurrentComponent_ORIG;

}



#######
#
# Configuring database for LDAP
#
#######
sub configure_ldap_database {

  require "./pin_".$MAIN_DM{'db'}->{'vendor'}."_functions.pl";
  require "./pin_cmp_dm_db.pl";
  local ( $TMP ) = $SKIP_INIT_OBJECTS;
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;

  sleep ( 10 );
  # If the CM is running, then stop it !
  if ( -f $CM{'location'}."/".$PINCONF ) {
    &Stop( $ServiceName{ "cm" } );
  }

  # If the DM is running, then stop it !
  &Stop( $ServiceName{ "dm_$MAIN_DM{'db'}->{'vendor'}" } );
  sleep ( 10 );

  $SPECIAL_DD_CREATE_INDEXES_FILE = "$DD{'location'}/create_indexes_ldap_".$MAIN_DM{'db'}->{'vendor'}.".source";
  &ExecuteSQL_Statement_From_File( $SPECIAL_DD_CREATE_INDEXES_FILE, TRUE, TRUE, %{DM->{'db'}} );

  sleep ( 10 );
  if ( -f $DM{'location'}."/".$PINCONF ) {
    &Start ( $ServiceName{'dm_'.$DM{'db'}->{'vendor'}} );
  }
  if ( -f $CM{'location'}."/".$PINCONF ) {
    &Start( $ServiceName{ "cm" } );
    sleep( 20 );
  }

}


#
# Create a link for the correct version of the dm_ldap file for Unix platforms
# and copy it for Windows
sub createlink {

  $Cmd =&FixSlashes( "ln -s $PIN_HOME/bin/dm_ldap19c $PIN_HOME/bin/dm_ldap");
  &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
  unlink( "$PIN_TEMP_DIR/tmp.out" );
}
1;
