#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_gprs_30.pl /cgbubrm_mainbrm.portalbase/2 2018/03/30 02:42:04 mkothari Exp $
#    
# Copyright (c) 2006, 2018, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the GPRS 3.0 Component
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
# Configure GSM Manager pin.conf files
#
##########################################
sub configure_gprs_30_config_files {
   local ( %CM ) = %MAIN_CM;
   local ( %DM ) = %MAIN_DM;
   
    &ReadIn_PinCnf( "pin_cnf_gprs_30.pl" );

    #
    # If the sys/cm/pin.conf is there, add the entries to it.
    # If not, add the entries to the temporary pin.conf file.
    #
    if ( -f $CM{'location'}."/".$PINCONF )
    {
  	open( PINCONFFILE, $CM{'location'}."/".$PINCONF );
  	@FileReadIn = <PINCONFFILE>;
  
      &ReplacePinConfEntries( $CM{'location'}."/".$PINCONF, %GPRS_MANAGER_CM_PINCONF_ENTRIES );  
      
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
  
      &ReplacePinConfEntries( "$TEMP_PIN_CONF_FILE", %GPRS_MANAGER_CM_PINCONF_ENTRIES );
  
      # Display a message saying to append this file to cm/pin.conf file.
      &Output( STDOUT, $IDS_APPEND_PIN_CONF_MESSAGE,
                          $CM{'location'}."/".$PINCONF,
                          $CurrentComponent,
                          $TEMP_PIN_CONF_FILE );
  
      }
  
}
#####################################
#
# Configuring database for GSM Manager
#
#####################################
sub configure_gprs_30_database {
  
  require "./pin_".$MAIN_DM{'db'}->{'vendor'}."_functions.pl";
  require "./pin_cmp_dm_db.pl";
  local ( $TMP ) = $SKIP_INIT_OBJECTS;
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;
  
  &PreModularConfigureDatabase( %CM, %DM );

  #########################################
  # Creating the tables for the GSM Manager
  #########################################
  $SKIP_INIT_OBJECTS = "YES";
  $USE_SPECIAL_DD_FILE = "YES";
  
    if ( VerifyPresenceOfTable( "ACTIVE_SESSION_TELCO_GPRS_T", %{$DM{"db"}} ) == 0 ){
    
    $SPECIAL_DD_FILE = "$DD{'location'}/dd_objects_telco_gprs.source";
    $SPECIAL_DD_DROP_FILE = "$DD{'location'}/drop_tables_telco_gprs_".$MAIN_DM{'db'}->{'vendor'}.".source";
    $SPECIAL_DD_CREATE_INDEXES_FILE = "$DD{'location'}/create_indexes_telco_gprs.source";
      
    if ( $SETUP_DROP_ALL_TABLES =~ m/^YES$/i ) {
       &DropTables( %{MAIN_DM->{"db"}} );
    }
     
    &pin_pre_modular( %{$DM{"db"}} );
    &pin_init( %DM );
    &pin_post_modular( %DM );
    &ExecuteSQL_Statement_From_File( $SPECIAL_DD_CREATE_INDEXES_FILE, TRUE, TRUE, %{$DM{'db'}} );
 
  }

  

  &PostModularConfigureDatabase( %CM, %DM );  

}
     #########################################
     # Additional configuration for gprs 30 manager
     #########################################
     sub configure_gprs_30_post_restart {
     
       local( $TempDir ) = &FixSlashes( "$AAA_LOAD_CONFIG_PATH" );
       local( $CurrentDir ) = cwd();
       local ( %CM ) = %MAIN_CM;
       local( %DM ) = %MAIN_DM;
     
       &ReadIn_PinCnf( "pin_cnf_connect.pl" );
     
       #
       # If the sys/data/config/pin.conf is present, then continue
       # If not, add the entries to the pin.conf file.
       #
       if (!( -e $AAA_LOAD_CONFIG_PATH."/".$PINCONF ))
       {
       	  #
     	  # Create pin.conf for loading.
     	  #
     	    &Configure_PinCnf( $AAA_LOAD_CONFIG_PATH."/".$PINCONF,
                            $CONNECT_PINCONF_HEADER,
                            %CONNECT_PINCONF_ENTRIES);
       }
       if ($DM{'db_num'} eq "0.0.0.1") {
          chdir $TempDir;
          &configure_event_map( *MAIN_CM, *MAIN_DM ); 
          &configure_service_order_gprs( *MAIN_CM, *MAIN_DM ); 
          &configure_provisioning_gprs( *MAIN_CM, *MAIN_DM ); 
          &configure_tags_gprs( *MAIN_CM, *MAIN_DM ); 
          chdir $CurrentDir;
      }
      }
    	
    ###########################################	
   # Load the pin_event_map_telco_gprs.
    ####################################################

	sub configure_event_map {
	
        &Output( fpLogFile, $IDS_GPRS_EVENT_MAP_LOADING );
        &Output( STDOUT, $IDS_GPRS_EVENT_MAP_LOADING );

   	$Cmd = &FixSlashes( "$PIN_HOME/bin/load_event_map pin_event_map_telco_gprs");
  	 $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
    
   	if( $Cmd != 0 ) {
              &Output( fpLogFile, $IDS_GPRS_EVENT_MAP_FAILED );
              &Output( STDOUT, $IDS_GPRS_EVENT_MAP_FAILED );
              exit -1;
           } else {
              &Output( fpLogFile, $IDS_GPRS_EVENT_MAP_SUCCESS );
              &Output( STDOUT, $IDS_GPRS_EVENT_MAP_SUCCESS );
        }
   	unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
	
	##################################################
	# Load the pin_telco_service_order_state_gprs.
	##################################################
	
	sub configure_service_order_gprs {
	
             &Output( fpLogFile, $IDS_GPRS_SERVICE_ORDER_LOADING );
             &Output( STDOUT, $IDS_GPRS_SERVICE_ORDER_LOADING );
         
             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_telco_service_order_state -v pin_telco_service_order_state_gprs");
             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
         
             if( $Cmd != 0 ) {
                &Output( fpLogFile, $IDS_GPRS_SERVICE_ORDER_FAILED );
                &Output( STDOUT, $IDS_GPRS_SERVICE_ORDER_FAILED );
                exit -1;
             } else {
                &Output( fpLogFile, $IDS_GPRS_SERVICE_ORDER_SUCCESS );
                &Output( STDOUT, $IDS_GPRS_SERVICE_ORDER_SUCCESS );
             }

	unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
	
	########################################################
	# Load the pin_telco_provisioning_gprs.
	######################################################
	sub configure_provisioning_gprs {
	             &Output( fpLogFile, $IDS_GPRS_PROVISIONING_LOADING );
	             &Output( STDOUT, $IDS_GPRS_PROVISIONING_LOADING );
	         
	             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_telco_provisioning -d -v pin_telco_provisioning_gprs");
	             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
	         
	             if( $Cmd != 0 ) {
	                &Output( fpLogFile, $IDS_GPRS_PROVISIONING_FAILED );
	                &Output( STDOUT, $IDS_GPRS_PROVISIONING_FAILED );
	                exit -1;
	             } else {
	                &Output( fpLogFile, $IDS_GPRS_PROVISIONING_SUCCESS );
	                &Output( STDOUT, $IDS_GPRS_PROVISIONING_SUCCESS );
             }
             unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
	
	 ##################################################
	 # Load the pin_telco_tags_gprs.
	 ##################################################
	 sub configure_tags_gprs {
	             &Output( fpLogFile, $IDS_GPRS_TAGS_LOADING );
	             &Output( STDOUT, $IDS_GPRS_TAGS_LOADING );
	         
	             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_telco_tags -d -v pin_telco_tags_gprs");
	             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
	         
	             if( $Cmd != 0 ) {
	                &Output( fpLogFile, $IDS_GPRS_TAGS_FAILED );
	                &Output( STDOUT, $IDS_GPRS_TAGS_FAILED );
	                exit -1;
	             } else {
	                &Output( fpLogFile, $IDS_GPRS_TAGS_SUCCESS );
	                &Output( STDOUT, $IDS_GPRS_TAGS_SUCCESS );
	             }
             unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
1;
