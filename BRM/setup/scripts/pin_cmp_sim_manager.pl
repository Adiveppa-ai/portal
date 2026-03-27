#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_sim_manager.pl /cgbubrm_mainbrm.portalbase/2 2018/03/30 02:42:06 mkothari Exp $ 
#    
# Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the SIM Manager Component
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


#####################################
#
# Configuring database for SIM Manager
#
#####################################
sub configure_sim_manager_database {
  
  require "./pin_".$MAIN_DM{'db'}->{'vendor'}."_functions.pl";
  require "./pin_cmp_dm_db.pl";
  local ( $TMP ) = $SKIP_INIT_OBJECTS;
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;
  
  &PreModularConfigureDatabase( %CM, %DM );

  $SKIP_INIT_OBJECTS = "YES";
  $USE_SPECIAL_DD_FILE = "YES";
  
  if ( VerifyPresenceOfTable( "ORDER_T", %{DM->{'db'}} ) == 0 ){
	$SPECIAL_DD_FILE = "$DD{'location'}/dd_objects_order.source";
	$SPECIAL_DD_DROP_FILE = "$DD{'location'}/drop_tables_order_".$MAIN_DM{'db'}->{'vendor'}.".source";
	$SPECIAL_DD_CREATE_INDEXES_FILE = "$DD{'location'}/create_indexes_order_".$MAIN_DM{'db'}->{'vendor'}.".source";

	if ( $SETUP_DROP_ALL_TABLES =~ m/^YES$/i ) {
	   &DropTables( %{MAIN_DM->{"db"}} );
	}

	&pin_pre_modular( %{DM->{'db'}} );
	&pin_init( %DM );
	&pin_post_modular( %DM );
	&ExecuteSQL_Statement_From_File( $SPECIAL_DD_CREATE_INDEXES_FILE, TRUE, TRUE, %{DM->{'db'}} );
  }

  if ( VerifyPresenceOfFieldName( "QUANTITY","ORDER_T", %{DM->{'db'}} ) == 0 ){      
        $SKIP_INIT_OBJECTS = "YES";
        $USE_SPECIAL_DD_FILE = "YES";
        $SPECIAL_DD_FILE = "$DD{'location'}/6.5SP2_6.7_dd_objects_order.source";      
        #
        # Removing pre_modular and post_modular for upgrade from 6.5
        # alone, since Optional managers are out of portal poid range
        # in 6.5 and before.
        &pin_init( %DM );

  }  

  if ( VerifyPresenceOfTable( "DEVICE_SIM_T", %{DM->{'db'}} ) == 0 ){
	  $SPECIAL_DD_FILE = "$DD{'location'}/dd_objects_sim.source";
	  $SPECIAL_DD_DROP_FILE = "$DD{'location'}/drop_tables_sim_".$MAIN_DM{'db'}->{'vendor'}.".source";
	  $SPECIAL_DD_CREATE_INDEXES_FILE = "$DD{'location'}/create_indexes_sim_".$MAIN_DM{'db'}->{'vendor'}.".source";

	  if ( $SETUP_DROP_ALL_TABLES =~ m/^YES$/i ) {
	    &DropTables( %{MAIN_DM->{"db"}} );
	  }

	  &pin_pre_modular( %{DM->{'db'}} );
	  &pin_init( %DM );
	  &pin_post_modular( %DM );

	  &ExecuteSQL_Statement_From_File( $SPECIAL_DD_CREATE_INDEXES_FILE, TRUE, TRUE, %{DM->{'db'}} );
 
  }

  $USE_SPECIAL_DD_FILE = "NO";
  $SKIP_INIT_OBJECTS = $TMP;

  &PostModularConfigureDatabase( %CM, %DM );
}


##########################################
#
# Configure SIM Manager pin.conf files
#
##########################################
sub configure_sim_manager_config_files {
  local ( %CM ) = %MAIN_CM;

  &ReadIn_PinCnf( "pin_cnf_sim_manager.pl" );
  
  #
  # If the sys/cm/pin.conf is there, add the entries to it.
  # If not, add the entries to the temporary pin.conf file.
  #
  if ( -f $CM{'location'}."/".$PINCONF )
  {
    &ReplacePinConfEntries( $CM{'location'}."/".$PINCONF, %SIM_MANAGER_CM_PINCONF_ENTRIES );
  }
  else
  {
    # Create temporary file, if it does not exist.
    $TEMP_PIN_CONF_FILE = $PIN_HOME."/".$IDS_TEMP_PIN_CONF;
    open( PINCONFFILE, ">> $TEMP_PIN_CONF_FILE" );
    close( PINCONFFILE );

    &ReplacePinConfEntries( "$TEMP_PIN_CONF_FILE", %SIM_MANAGER_CM_PINCONF_ENTRIES );

    # Display a message saying to append this file to cm/pin.conf file.
    &Output( STDOUT, $IDS_APPEND_PIN_CONF_MESSAGE,
                        $CM{'location'}."/".$PINCONF,
                        $CurrentComponent,
                        $TEMP_PIN_CONF_FILE );

    }

}

    #########################################
    # Additional configuration for sim manager
    #########################################
    sub configure_sim_manager_post_restart {
    
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
    
      chdir $TempDir;
      if ($DM{'db_num'} eq "0.0.0.1") {
          &configure_sim_device( *MAIN_CM, *MAIN_DM ); 
          &configure_device_state( *MAIN_CM, *MAIN_DM ); 
          &configure_sim_config( *MAIN_CM, *MAIN_DM ); 
          &configure_network_elements( *MAIN_CM, *MAIN_DM ); 
          &configure_ordersimstatus( *MAIN_CM, *MAIN_DM ); 
          &configure_simcardtypes( *MAIN_CM, *MAIN_DM ); 
          &configure_simdevicestates( *MAIN_CM, *MAIN_DM ); 
      }
      chdir $CurrentDir;
      } 
    	
        ###########################################
        # Load the pin_device_permit_map_sim.
        ##############################################
        
        sub configure_sim_device {
	
        &Output( fpLogFile, $IDS_SIM_DEVICE_LOADING );
        &Output( STDOUT, $IDS_SIM_DEVICE_LOADING );
    
        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_device_permit_map -d -v pin_device_permit_map_sim");
        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
    
        if( $Cmd != 0 ) {
           &Output( fpLogFile, $IDS_SIM_DEVICE_FAILED );
           &Output( STDOUT, $IDS_SIM_DEVICE_FAILED );
           exit -1;
        } else {
           &Output( fpLogFile, $IDS_SIM_DEVICE_SUCCESS );
           &Output( STDOUT, $IDS_SIM_DEVICE_SUCCESS );
        }
        unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
     
      ##########################################
      # Load the pin_device_state_sim .
      ##########################################
      
      sub configure_device_state {
	
             &Output( fpLogFile, $IDS_SIM_DEVICE_STATE_LOADING );
             &Output( STDOUT, $IDS_SIM_DEVICE_STATE_LOADING );
         
             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_device_state pin_device_state_sim");
             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
         
             if( $Cmd != 0 ) {
                &Output( fpLogFile, $IDS_SIM_DEVICE_STATE_FAILED );
                &Output( STDOUT, $IDS_SIM_DEVICE_STATE_FAILED );
                exit -1;
             } else {
                &Output( fpLogFile, $IDS_SIM_DEVICE_STATE_SUCCESS );
                &Output( STDOUT, $IDS_SIM_DEVICE_STATE_SUCCESS );
             }
         
        unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
      
      #######################################
      # Load the pin_sim_config .
      ########################################
      
      sub configure_sim_config {
	
             &Output( fpLogFile, $IDS_SIM_CONFIG_LOADING );
             &Output( STDOUT, $IDS_SIM_CONFIG_LOADING );
         
             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_sim_config pin_sim_config");
             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
         
             if( $Cmd != 0 ) {
                &Output( fpLogFile, $IDS_SIM_CONFIG_FAILED );
                &Output( STDOUT, $IDS_NUMBER_CONFIG_FAILED );
                exit -1;
             } else {
                &Output( fpLogFile, $IDS_SIM_CONFIG_SUCCESS );
                &Output( STDOUT, $IDS_SIM_CONFIG_SUCCESS );
             }
         unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
     
      ########################################
      # Load the pin_network_elements.
      ########################################
      
      sub configure_network_elements {
	
             &Output( fpLogFile, $IDS_SIM_NETWORK_LOADING );
             &Output( STDOUT, $IDS_SIM_NETWORK_LOADING );
         
             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_network_elements -d -v pin_network_elements");
             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
         
             if( $Cmd != 0 ) {
                &Output( fpLogFile, $IDS_SIM_NETWORK_FAILED );
                &Output( STDOUT, $IDS_SIM_NETWORK_FAILED );
                exit -1;
             } else {
                &Output( fpLogFile, $IDS_SIM_NETWORK_SUCCESS );
                &Output( STDOUT, $IDS_SIM_NETWORK_SUCCESS );
             }
    
        unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
	
	###############################################
        # Load localized strings for the Ordersimstatus
        ###############################################
        
        sub configure_ordersimstatus {
	
        &Output( fpLogFile, $IDS_SIM_STATUS_STRINGS_LOADING );
        &Output( STDOUT, $IDS_SIM_STATUS_STRINGS_LOADING );
    
        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_localized_strings \"$PIN_HOME/sys/msgs/ordersimstatus/order_sim_status.en_US\"");
        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
    
        if( $Cmd != 0 ) {
           &Output( fpLogFile, $IDS_SIM_STATUS_STRINGS_FAILED );
           &Output( STDOUT, $IDS_SIM_STATUS_STRINGS_FAILED );
           exit -1;
        } else {
           &Output( fpLogFile, $IDS_SIM_STATUS_STRINGS_SUCCESS );
           &Output( STDOUT, $IDS_SIM_STATUS_STRINGS_SUCCESS );
        }
        unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
	
	############################################
        # Load localized strings for the Simcardtypes  
        ############################################
        
        sub configure_simcardtypes {
	
	        &Output( fpLogFile, $IDS_SIM_CARD_STRINGS_LOADING );
	        &Output( STDOUT, $IDS_SIM_CARD_STRINGS_LOADING );
	    
	        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_localized_strings \"$PIN_HOME/sys/msgs/simcardtypes/sim_card_types.en_US\"");
	        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
	    
	        if( $Cmd != 0 ) {
	           &Output( fpLogFile, $IDS_SIM_CARD_STRINGS_FAILED );
	           &Output( STDOUT, $IDS_SIM_CARD_STRINGS_FAILED );
	           exit -1;
	        } else {
	           &Output( fpLogFile, $IDS_SIM_CARD_STRINGS_SUCCESS );
	           &Output( STDOUT, $IDS_SIM_CARD_STRINGS_SUCCESS );
        }
        unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
        
        #################################################
        # Load localized strings for the Simdevicestates  
        ###################################################
        
        sub configure_simdevicestates {
	
	        &Output( fpLogFile, $IDS_SIM_DEVICE_STRINGS_LOADING );
	        &Output( STDOUT, $IDS_SIM_DEVICE_STRINGS_LOADING );
	    
	        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_localized_strings \"$PIN_HOME/sys/msgs/simdevicestates/sim_device_states.en_US\"");
	        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
	    
	        if( $Cmd != 0 ) {
	           &Output( fpLogFile, $IDS_SIM_DEVICE_STRINGS_FAILED );
	           &Output( STDOUT, $IDS_SIM_DEVICE_STRINGS_FAILED );
	           exit -1;
	        } else {
	           &Output( fpLogFile, $IDS_SIM_DEVICE_STRINGS_SUCCESS );
	           &Output( STDOUT, $IDS_SIM_DEVICE_STRINGS_SUCCESS );
        }
        unlink( "$PIN_TEMP_DIR/tmp.out" );
	}

1;
