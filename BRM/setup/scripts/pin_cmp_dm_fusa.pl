#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_dm_fusa.pl /cgbubrm_mainbrm.portalbase/3 2018/03/30 02:42:04 mkothari Exp $ 
#    
# Copyright (c) 1999, 2018, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the DM_FUSA Component
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
# Configure DM_fusa files
#
#####
sub configure_dm_fusa_config_files {
  %QM = %DM_FUSA;
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;  
  local ( @FileReadIn );
  local ( $Start );  

  &ReadIn_PinCnf( "pin_cnf_qm.pl" );

  $DM_FUSA_PINCONF_HEADER = $QM_PINCONF_HEADER;
  &ReadIn_PinCnf( "pin_cnf_dm_fusa.pl" );
  &AddArrays( \%QM_PINCONF_ENTRIES, \%DM_FUSA_PINCONF_ENTRIES );

  &Configure_PinCnf( $DM_FUSA{'location'}."/".$PINCONF, 
                     $DM_FUSA_PINCONF_HEADER,
                     %DM_FUSA_PINCONF_ENTRIES );

  &Configure_PinCnf( $DM_FUSA{'app_location'}."/".$PINCONF, 
                     $FUSA_SERVER_PINCONF_HEADER, 
                     %FUSA_SERVER_PINCONF_ENTRIES );

  #
  # If the CM is there, add the entries to it.
  # If not, add the entries to the temporary pin.conf file.
  #

  if ( -f $CM{'location'}."/".$PINCONF )
  {

	&AddPinConfEntries( $CM{'location'}."/".$PINCONF, %DM_FUSA_CM_PINCONF_ENTRIES );

    # Display a message current component entries are appended to cm/pin.conf file.
    &Output( STDOUT, $IDS_CM_PIN_CONF_APPEND_SUCCESS,
    			$CurrentComponent,
    			$CM{'location'}."/".$PINCONF);

  } 
  else
  {
    # Create temporary file, if it does not exist.
    $TEMP_PIN_CONF_FILE = $PIN_HOME."/".$IDS_TEMP_PIN_CONF;
    open( PINCONFFILE, ">> $TEMP_PIN_CONF_FILE" );
    close( PINCONFFILE );

    &AddPinConfEntries( "$TEMP_PIN_CONF_FILE", %DM_FUSA_CM_PINCONF_ENTRIES );

    # Display a message saying to append this file to cm/pin.conf file.
    &Output( STDOUT, $IDS_APPEND_PIN_CONF_MESSAGE,
                        $MAIN_CM{'location'}."/".$PINCONF,
                        $CurrentComponent,
                        $TEMP_PIN_CONF_FILE );
  };
  system(" $PIN_HOME/bin/pin_crypt_app -useZT -genkey -update_fusa_conf ");
}
1;


#######
#
# Configuring database for DM_fusa
#
#######
#sub configure_dm_fusa_database {
#}
