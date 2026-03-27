#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_number_manager.pl /cgbubrm_mainbrm.portalbase/3 2018/03/30 02:42:04 mkothari Exp $
#    
# Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the Number Manager Component
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
# Configuring database for Number Manager
#
#####################################
sub configure_number_manager_database {
  
  require "./pin_".$MAIN_DM{'db'}->{'vendor'}."_functions.pl";
  require "./pin_cmp_dm_db.pl";
  local ( $TMP ) = $SKIP_INIT_OBJECTS;
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;
  &PreModularConfigureDatabase( %CM, %DM );
  
  	if ( VerifyPresenceOfTable( "DEVICE_NUM_T", %{$DM{"db"}} ) == 0 ){
  	
	$SKIP_INIT_OBJECTS = "YES";
  	$USE_SPECIAL_DD_FILE = "YES";

  
      	$SPECIAL_DD_FILE = "$DD{'location'}/dd_objects_num.source";
      	$SPECIAL_DD_DROP_FILE = "$DD{'location'}/drop_tables_num_".$MAIN_DM{'db'}->{'vendor'}.".source";
      	$SPECIAL_DD_CREATE_INDEXES_FILE = "$DD{'location'}/create_indexes_num_".$MAIN_DM{'db'}->{'vendor'}.".source";
  
      	if ( $SETUP_DROP_ALL_TABLES =~ m/^YES$/i ) {
        &DropTables( %{MAIN_DM->{"db"}} );
      	}
  
      	&pin_pre_modular( %{$DM{"db"}} );
      	&pin_init( %DM );
      	&pin_post_modular( %DM );
      
      	&ExecuteSQL_Statement_From_File( $SPECIAL_DD_CREATE_INDEXES_FILE, TRUE, TRUE, %{$DM{'db'}} );
       	$USE_SPECIAL_DD_FILE = "NO";
        $SKIP_INIT_OBJECTS = $TMP;
      

    }
    
    
     #
      # If this is an upgrade install from 6.5 to 6.7
      # the PIN_FLD_ORIG_NETWORK_ID field will not be present.
      # Hence call the upgrade script to create the new field and table.
      #
    if (  VerifyPresenceOfField( "PIN_FLD_ORIG_NETWORK_ID", %{$DM{"db"}} ) == 0 )
    {
       
       $SKIP_INIT_OBJECTS = "YES";
       $USE_SPECIAL_DD_FILE = "YES";
       $SPECIAL_DD_FILE = "$DD{'location'}/6.5_6.7_dd_objects_device_number.source";
    
       &pin_pre_modular( %{$DM{"db"}} );
       &pin_init( %DM );
       &pin_post_modular( %DM );
    
       $USE_SPECIAL_DD_FILE = "NO";
       $SKIP_INIT_OBJECTS = $TMP;
     }

&PostModularConfigureDatabase( %CM, %DM );
}


##########################################
#
# Configure Number Manager pin.conf files
#
##########################################
sub configure_number_manager_config_files {
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;

  &ReadIn_PinCnf( "pin_cnf_number_manager.pl" );
  
  #
  # If the sys/cm/pin.conf is there, add the entries to it.
  # If not, add the entries to the temporary pin.conf file.
  #
  if ( -f $CM{'location'}."/".$PINCONF )
  {
    &ReplacePinConfEntries( $CM{'location'}."/".$PINCONF, %NUMBER_MANAGER_CM_PINCONF_ENTRIES );
    
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

    &ReplacePinConfEntries( "$TEMP_PIN_CONF_FILE", %NUMBER_MANAGER_CM_PINCONF_ENTRIES );

    # Display a message saying to append this file to cm/pin.conf file.
    &Output( STDOUT, $IDS_APPEND_PIN_CONF_MESSAGE,
                        $CM{'location'}."/".$PINCONF,
                        $CurrentComponent,
                        $TEMP_PIN_CONF_FILE );

    }
    
    }
    
    
    #########################################
    # Additional configuration for number manager
    #########################################
    sub configure_number_manager_post_restart {
    
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
         &configure_device( *MAIN_CM, *MAIN_DM ); 
         &configure_num_state( *MAIN_CM, *MAIN_DM ); 
         &configure_num_config( *MAIN_CM, *MAIN_DM ); 
         &configure_networks( *MAIN_CM, *MAIN_DM );
         &configure_numcategories( *MAIN_CM, *MAIN_DM ); 
         &configure_numdevicestates( *MAIN_CM, *MAIN_DM ); 
         &configure_numvanities( *MAIN_CM, *MAIN_DM ); 
     }
     chdir $CurrentDir;
      }
    
    ##################################################
    # Load the pin_device_permit_map_num.
    ####################################################
    
        sub configure_device {
        
        &Output( fpLogFile, $IDS_NUMBER_DEVICE_LOADING );
        &Output( STDOUT, $IDS_NUMBER_DEVICE_LOADING );
    
        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_device_permit_map -d -v pin_device_permit_map_num");
        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
    
        if( $Cmd != 0 ) {
           &Output( fpLogFile, $IDS_NUMBER_DEVICE_FAILED );
           &Output( STDOUT, $IDS_NUMBER_DEVICE_FAILED );
           exit -1;
        } else {
           &Output( fpLogFile, $IDS_NUMBER_DEVICE_SUCCESS );
           &Output( STDOUT, $IDS_NUMBER_DEVICE_SUCCESS );
        }
      unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
     
      #############################################
      # Load the pin_device_state_num.
      #############################################
      
      sub configure_num_state {
      
             &Output( fpLogFile, $IDS_NUMBER_DEVICE_STATE_LOADING );
             &Output( STDOUT, $IDS_NUMBER_DEVICE_STATE_LOADING );
         
             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_device_state  pin_device_state_num");
             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
         
             if( $Cmd != 0 ) {
                &Output( fpLogFile, $IDS_NUMBER_DEVICE_STATE_FAILED );
                &Output( STDOUT, $IDS_NUMBER_DEVICE_STATE_FAILED );
                exit -1;
             } else {
                &Output( fpLogFile, $IDS_NUMBER_DEVICE_STATE_SUCCESS );
                &Output( STDOUT, $IDS_NUMBER_DEVICE_STATE_SUCCESS );
             }
         unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
     
      ###############################################
      # Load the pin_num_config .
      ####################################################
      
      sub configure_num_config {
      
             &Output( fpLogFile, $IDS_NUMBER_CONFIG_LOADING );
             &Output( STDOUT, $IDS_NUMBER_CONFIG_LOADING );
         
	     system(" sleep 20" );
             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_num_config pin_num_config");
             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
         
             if( $Cmd != 0 ) {
                &Output( fpLogFile, $IDS_NUMBER_CONFIG_FAILED );
                &Output( STDOUT, $IDS_NUMBER_CONFIG_FAILED );
                exit -1;
             } else {
                &Output( fpLogFile, $IDS_NUMBER_CONFIG_SUCCESS );
                &Output( STDOUT, $IDS_NUMBER_CONFIG_SUCCESS );
             }
    
            unlink( "$PIN_TEMP_DIR/tmp.out" );
	     }
      
      ###################################################
      # Load the pin_network_elements.
      ####################################################
      
      sub configure_networks {
      
             &Output( fpLogFile, $IDS_NUMBER_NETWORK_LOADING );
             &Output( STDOUT, $IDS_NUMBER_NETWORK_LOADING );
         
             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_network_elements -d -v pin_network_elements");
             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
         
             if( $Cmd != 0 ) {
                &Output( fpLogFile, $IDS_NUMBER_NETWORK_FAILED );
                &Output( STDOUT, $IDS_NUMBER_NETWORK_FAILED );
                exit -1;
             } else {
                &Output( fpLogFile, $IDS_NUMBER_NETWORK_SUCCESS );
                &Output( STDOUT, $IDS_NUMBER_NETWORK_SUCCESS );
             }
    
            unlink( "$PIN_TEMP_DIR/tmp.out" );
	     }
        
        ###################################################
        # Load localized strings for the Numcategories
        ##################################################
        
        sub configure_numcategories {
        
        &Output( fpLogFile, $IDS_NUMBER_CATEGORIES_STRINGS_LOADING );
        &Output( STDOUT, $IDS_NUMBER_CATEGORIES_STRINGS_LOADING );
    
        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_localized_strings \"$PIN_HOME/sys/msgs/numcategories/num_categories.en_US\"");
        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
    
        if( $Cmd != 0 ) {
           &Output( fpLogFile, $IDS_NUMBER_CATEGORIES_STRINGS_FAILED );
           &Output( STDOUT, $IDS_NUMBER_CATEGORIES_STRINGS_FAILED );
           exit -1;
        } else {
           &Output( fpLogFile, $IDS_NUMBER_CATEGORIES_STRINGS_SUCCESS );
           &Output( STDOUT, $IDS_NUMBER_CATEGORIES_STRINGS_SUCCESS );
        }
        unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
        
        ########################################################
        # Load localized strings for the Numdevicestates 
        ##########################################################
        
        sub configure_numdevicestates {
        
	        &Output( fpLogFile, $IDS_NUMBER_DEVICE_STRINGS_LOADING );
	        &Output( STDOUT, $IDS_NUMBER_DEVICE_STRINGS_LOADING );
	    
	        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_localized_strings \"$PIN_HOME/sys/msgs/numdevicestates/num_device_states.en_US\"");
	        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
	    
	        if( $Cmd != 0 ) {
	           &Output( fpLogFile, $IDS_NUMBER_DEVICE_STRINGS_FAILED );
	           &Output( STDOUT, $IDS_NUMBER_DEVICE_STRINGS_FAILED );
	           exit -1;
	        } else {
	           &Output( fpLogFile, $IDS_NUMBER_DEVICE_STRINGS_SUCCESS );
	           &Output( STDOUT, $IDS_NUMBER_DEVICE_STRINGS_SUCCESS );
                }
                unlink( "$PIN_TEMP_DIR/tmp.out" );
	        }
        
        #############################################
        # Load localized strings for the Numvanities 
        ##############################################
        
        sub configure_numvanities {
        
	        &Output( fpLogFile, $IDS_NUMBER_VANITIES_STRINGS_LOADING );
	        &Output( STDOUT, $IDS_NUMBER_VANITIES_STRINGS_LOADING );
	    
	        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_localized_strings \"$PIN_HOME/sys/msgs/numvanities/num_vanities.en_US\"");
	        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
	    
	        if( $Cmd != 0 ) {
	           &Output( fpLogFile, $IDS_NUMBER_VANITIES_STRINGS_FAILED );
	           &Output( STDOUT, $IDS_NUMBER_VANITIES_STRINGS_FAILED );
	           exit -1;
	        } else {
	           &Output( fpLogFile, $IDS_NUMBER_VANITIES_STRINGS_SUCCESS );
	           &Output( STDOUT, $IDS_NUMBER_VANITIES_STRINGS_SUCCESS );
               }
               unlink( "$PIN_TEMP_DIR/tmp.out" );
	       }
  	

1;
