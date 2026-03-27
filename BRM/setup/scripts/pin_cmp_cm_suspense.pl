#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_cm_suspense.pl /cgbubrm_mainbrm.portalbase/4 2018/03/30 02:42:06 mkothari Exp $ 
# 
# Copyright (c) 2003, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
# Portal installation for the Suspense CM Component
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
# Configure CM pin.conf file for Suspense Manager
#
#####
sub configure_cm_suspense_config_files {
  local ( %CM ) = %MAIN_CM;

  &ReadIn_PinCnf( "pin_cnf_cm_suspense.pl" );


  #
  # If the sys/cm/pin.conf is there, add the entries to it.
  # If not, add the entries to the temporary pin.conf file.
  #
  if ( -f $CM{'location'}."/".$PINCONF )
  {
    &ReplacePinConfEntries( $CM{'location'}."/".$PINCONF, %SUSPENSE_MANAGER_CM_PINCONF_ENTRIES );
  }
  else
  {
    # Create temporary file, if it does not exist.
    $TEMP_PIN_CONF_FILE = $PIN_HOME."/".$IDS_TEMP_PIN_CONF;
    open( PINCONFFILE, ">> $TEMP_PIN_CONF_FILE" );
    close( PINCONFFILE );

    &ReplacePinConfEntries( "$TEMP_PIN_CONF_FILE", %SUSPENSE_MANAGER_CM_PINCONF_ENTRIES );

    # Display a message saying to append this file to cm/pin.conf file.
    &Output( STDOUT, $IDS_APPEND_PIN_CONF_MESSAGE,
                        $CM{'location'}."/".$PINCONF,
                        $CurrentComponent,
                        $TEMP_PIN_CONF_FILE );

    }
}

#########################################
#
# Load the suspense reason codes and editable fields
#
##########################################
sub configure_cm_suspense_post_restart {
	local ($Cmd);

    local( $CurrentDir ) = cwd();
    my $count = 0;
    while(!&chk_test()) {
      print "checking testnap, still not up...\n";
      sleep( 20 );
      $count++;
      last if($count == 5);
    }
    chdir $CurrentDir;

    if ($DM{'db_num'} eq "0.0.0.1") {
    # Load the reason codes.
    &Output( fpLogFile, $IDS_SUSPENSE_REASON_LOADING );
    &Output( STDOUT, $IDS_SUSPENSE_REASON_LOADING );

    $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_suspense_reason_code \"$PIN_HOME/sys/data/config/pin_suspense_reason_code\"");
    $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );

    if( $Cmd != 0 ) {
       &Output( fpLogFile, $IDS_SUSPENSE_REASON_FAILED );
       &Output( STDOUT, $IDS_SUSPENSE_REASON_FAILED );
       exit -1;
    } else {
       &Output( fpLogFile, $IDS_SUSPENSE_REASON_SUCCESS );
       &Output( STDOUT, $IDS_SUSPENSE_REASON_SUCCESS );
    }

    # Load localized strings for the reason codes
    &Output( fpLogFile, $IDS_SUSPENSE_REASON_STRINGS_LOADING );
    &Output( STDOUT, $IDS_SUSPENSE_REASON_STRINGS_LOADING );

    $Cmd = &FixSlashes( "$PIN_HOME/bin/load_localized_strings \"$PIN_HOME/sys/msgs/suspense_reason_code/suspense_reason_code.en_US\"");
    $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );

    if( $Cmd != 0 ) {
       &Output( fpLogFile, $IDS_SUSPENSE_REASON_STRINGS_FAILED );
       &Output( STDOUT, $IDS_SUSPENSE_REASON_STRINGS_FAILED );
       exit -1;
    } else {
       &Output( fpLogFile, $IDS_SUSPENSE_REASON_STRINGS_SUCCESS );
       &Output( STDOUT, $IDS_SUSPENSE_REASON_STRINGS_SUCCESS );
    }
    
    # Load the batch reason codes.
        &Output( fpLogFile, $IDS_BATCH_SUSPENSE_REASON_LOADING );
        &Output( STDOUT, $IDS_BATCH_SUSPENSE_REASON_LOADING );
    
        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_batch_suspense_reason_code \"$PIN_HOME/sys/data/config/pin_batch_suspense_reason_code\"");
        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
    
        if( $Cmd != 0 ) {
           &Output( fpLogFile, $IDS_BATCH_SUSPENSE_REASON_FAILED );
           &Output( STDOUT, $IDS_BATCH_SUSPENSE_REASON_FAILED );
           exit -1;
        } else {
           &Output( fpLogFile, $IDS_BATCH_SUSPENSE_REASON_SUCCESS );
           &Output( STDOUT, $IDS_BATCH_SUSPENSE_REASON_SUCCESS );
        }
        
    
    # Load localized strings for the batch reason codes
    &Output( fpLogFile, $IDS_BATCH_SUSPENSE_REASON_STRINGS_LOADING );
    &Output( STDOUT, $IDS_BATCH_SUSPENSE_REASON_STRINGS_LOADING );

    $Cmd = &FixSlashes( "$PIN_HOME/bin/load_localized_strings \"$PIN_HOME/sys/msgs/suspense_reason_code/batch_suspense_reason_code.en_US\"");
    $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );

    if( $Cmd != 0 ) {
       &Output( fpLogFile, $IDS_BATCH_SUSPENSE_REASON_STRINGS_FAILED );
       &Output( STDOUT, $IDS_BATCH_SUSPENSE_REASON_STRINGS_FAILED );
       exit -1;
    } else {
       &Output( fpLogFile, $IDS_BATCH_SUSPENSE_REASON_STRINGS_SUCCESS );
       &Output( STDOUT, $IDS_BATCH_SUSPENSE_REASON_STRINGS_SUCCESS );
    } 

  
    # Load the editable fields. 
    &Output( fpLogFile, $IDS_SUSPENSE_EDITABLE_FLDS_LOADING );
    &Output( STDOUT, $IDS_SUSPENSE_EDITABLE_FLDS_LOADING );

    $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_suspense_editable_flds \"$PIN_HOME/sys/data/config/pin_suspense_editable_flds\"");
    $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );

    if( $Cmd != 0 ) {
       &Output( fpLogFile, $IDS_SUSPENSE_EDITABLE_FLDS_FAILED );
       &Output( STDOUT, $IDS_SUSPENSE_EDITABLE_FLDS_FAILED );
       exit -1;
    } else {
       &Output( fpLogFile, $IDS_SUSPENSE_EDITABLE_FLDS_SUCCESS );
       &Output( STDOUT, $IDS_SUSPENSE_EDITABLE_FLDS_SUCCESS );
    }

    # Load the edr field mapping
    &Output( fpLogFile, $IDS_EDR_FIELD_MAPPING_LOADING );
    &Output( STDOUT, $IDS_EDR_FIELD_MAPPING_LOADING );

    $Cmd = &FixSlashes( "$PIN_HOME/bin/load_edr_field_mapping \"$PIN_HOME/sys/data/config/edr_field_mapping.xml\"");
    $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );

    if( $Cmd != 0 ) {
       &Output( fpLogFile, $IDS_EDR_FIELD_MAPPING_FAILED );
       &Output( STDOUT, $IDS_EDR_FIELD_MAPPING_FAILED );
       exit -1;
    } else {
       &Output( fpLogFile, $IDS_EDR_FIELD_MAPPING_SUCCESS );
       &Output( STDOUT, $IDS_EDR_FIELD_MAPPING_SUCCESS );
    }
   }
 }
1;
