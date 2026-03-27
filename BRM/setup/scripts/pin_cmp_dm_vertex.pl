#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_dm_vertex.pl /cgbubrm_mainbrm.portalbase/2 2018/03/30 02:42:03 mkothari Exp $ 
# 
# Copyright (c) 2001, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the DM_VERTEX Component
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
# Configure pin.conf files for dm_vertex
#
#####
sub configure_dm_vertex_config_files {
  local ( %QM ) = %DM_VERTEX;     # For use by pin_cnf_qm.pl
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;

  &ReadIn_PinCnf( "pin_cnf_qm.pl" );
  &ReadIn_PinCnf( "pin_cnf_dm_vertex.pl" );

  # First, inherit the QM PINCONF ENTRIES ...
  &AddArrays( \%QM_PINCONF_ENTRIES, \%DM_VERTEX_PINCONF_ENTRIES );

  &AddArrays( \%DM_VERTEX_PINCONF_ENTRIES, \%DM_VERTEX_NEW_PINCONF_ENTRIES );

  # Add entries to the sys/dm_vertex/pin.conf file.
  &Configure_PinCnf( $DM_VERTEX{'location'}."/".$PINCONF,
                     $DM_VERTEX_PINCONF_HEADER,
                     %DM_VERTEX_NEW_PINCONF_ENTRIES );

  #
  # If the CM is there, add the entries to it.
  # If not, add the entries to the temporary pin.conf file.
  #
  if ( -f $CM{'location'}."/".$PINCONF )
  {
    &ReplacePinConfEntries( $CM{'location'}."/".$PINCONF, %DM_VERTEX_CM_PINCONF_ENTRIES );
  }
  else
  {
    # Create temporary file, if it does not exist.
    $TEMP_PIN_CONF_FILE = $PIN_HOME."/".$IDS_TEMP_PIN_CONF;
    open( PINCONFFILE, ">> $TEMP_PIN_CONF_FILE" );
    close( PINCONFFILE );

    &ReplacePinConfEntries( "$TEMP_PIN_CONF_FILE", %DM_VERTEX_CM_PINCONF_ENTRIES );

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
  };

}
1;


#######
#
# Configuring database for DM VERTEX
#
#######
#sub configure_dm_vertex_database {

