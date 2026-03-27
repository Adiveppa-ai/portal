#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_vouchermanager.pl /cgbubrm_mainbrm.portalbase/2 2018/03/30 02:42:06 mkothari Exp $ 
#    
# Copyright (c) 2003, 2018, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the VoucherManager Component
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
# Configure VoucherManager pin.conf files
#
##########################################
sub configure_vouchermanager_config_files {
  %CM = %MAIN_CM;
  %DM = %MAIN_DM;
  local ( @FileReadIn );
  local ( $Start );  

  &ReadIn_PinCnf( "pin_cnf_vouchermanager.pl" );
  

# If the sys/cm/pin.conf is there, add the entries to it.
# If not, add the entries to the temporary pin.conf file.

  if ( -f $CM{'location'}."/".$PINCONF )
  {
   	&ReplacePinConfEntries( $CM{'location'}."/".$PINCONF, %VOUCHERMANAGER_CM_PINCONF_ENTRIES );
	
  }
  else
  {
   # Create temporary file, if it does not exist.
   $TEMP_PIN_CONF_FILE = $PIN_HOME."/".$IDS_TEMP_PIN_CONF;
   open( PINCONFFILE, ">> $TEMP_PIN_CONF_FILE" );
   close( PINCONFFILE );
   
   &ReplacePinConfEntries( "$TEMP_PIN_CONF_FILE", %VOUCHERMANAGER_CM_PINCONF_ENTRIES );

   # Display a message saying to append this file to cm/pin.conf file.
   &Output( STDOUT, $IDS_APPEND_PIN_CONF_MESSAGE,
                        $CM{'location'}."/".$PINCONF,
                       $CurrentComponent,
                        $TEMP_PIN_CONF_FILE );

   }   

}

#####################################
#
# Configuring database for VoucherManager 
#
#####################################
sub configure_vouchermanager_database {
  
  require "./pin_".$MAIN_DM{'db'}->{'vendor'}."_functions.pl";
  require "./pin_cmp_dm_db.pl";
  local ( $TMP ) = $SKIP_INIT_OBJECTS;
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;
  
  &PreModularConfigureDatabase( %CM, %DM );

  #########################################
  # Creating the tables for the VoucherManager 
  #########################################  
    if ( VerifyPresenceOfFieldName( "QUANTITY","ORDER_T", %{DM->{'db'}} ) == 0 ){      
          $SKIP_INIT_OBJECTS = "YES";
          $USE_SPECIAL_DD_FILE = "YES";
          $SPECIAL_DD_FILE = "$DD{'location'}/6.5SP2_6.7_dd_objects_order.source";      
              	   	   
          #&pin_pre_modular( %{DM->{'db'}} );
          &pin_init( %DM );
          #&pin_post_modular( %DM );
                     
          $USE_SPECIAL_DD_FILE = "NO";
          $SKIP_INIT_OBJECTS = $TMP;

          #This is a special condition for 6.5 to later version upgrades.
          #pre_modular and post_modular should not be called since there is an error with Obj Ids in 6.5
	    if ( VerifyPresenceOfObject( "/order/voucher", %{DM->{'db'}} ) == 0 ){  
		$SKIP_INIT_OBJECTS = "YES";
		$USE_SPECIAL_DD_FILE = "YES";

		$SPECIAL_DD_FILE = "$DD{'location'}/dd_objects_voucher.source";
		$SPECIAL_DD_DROP_FILE = "$DD{'location'}/drop_tables_voucher_".$MAIN_DM{'db'}->{'vendor'}.".source";

		if ( $SETUP_DROP_ALL_TABLES =~ m/^YES$/i ) {
		     &DropTables( %{MAIN_DM->{"db"}} );
		}

		#&pin_pre_modular( %{DM->{'db'}} );
		&pin_init( %DM );
		#&pin_post_modular( %DM );

		$USE_SPECIAL_DD_FILE = "NO";
		$SKIP_INIT_OBJECTS = $TMP;
	    }

    }  

    #If it not upgrade from 6.5 use pre_modular and post modular.
    if ( VerifyPresenceOfTable( "ORDER_VOUCHER_T", %{DM->{'db'}} ) == 0 ){  
        $SKIP_INIT_OBJECTS = "YES";
        $USE_SPECIAL_DD_FILE = "YES";
    
        $SPECIAL_DD_FILE = "$DD{'location'}/dd_objects_voucher.source";
        $SPECIAL_DD_DROP_FILE = "$DD{'location'}/drop_tables_voucher_".$MAIN_DM{'db'}->{'vendor'}.".source";
    
        if ( $SETUP_DROP_ALL_TABLES =~ m/^YES$/i ) {
             &DropTables( %{MAIN_DM->{"db"}} );
        }
   
        &pin_pre_modular( %{DM->{'db'}} );
        &pin_init( %DM );
        &pin_post_modular( %DM );
    
        $USE_SPECIAL_DD_FILE = "NO";
        $SKIP_INIT_OBJECTS = $TMP;
    }
 
 # If pin_fld_voucher_pin field is not present in device_voucher_t then calls "7.3_7.3Patch_dd_objects_device_voucher.source"
    if ( VerifyPresenceOfFieldName( "PIN_FLD_VOUCHER_PIN","DEVICE_VOUCHER_T", %{DM->{'db'}} ) == 0 ){      
        $SKIP_INIT_OBJECTS = "YES";
        $USE_SPECIAL_DD_FILE = "YES";
        $SPECIAL_DD_FILE = "$DD{'location'}/7.3_7.3Patch_dd_objects_device_voucher.source";      
            	   	   
        &pin_pre_modular( %{DM->{'db'}} );
        &pin_init( %DM );
        &pin_post_modular( %DM );
                    
        $USE_SPECIAL_DD_FILE = "NO";
        $SKIP_INIT_OBJECTS = $TMP;
    }  

    &PostModularConfigureDatabase( %CM, %DM );
}

#########################################
     # Additional configuration for voucher manager
     #########################################
     sub configure_vouchermanager_post_restart {
     
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
          &configure_device_permit_map( *MAIN_CM, *MAIN_DM ); 
          &configure_voucher_config( *MAIN_CM, *MAIN_DM ); 
          &configure_state_voucher( *MAIN_CM, *MAIN_DM ); 
          &configure_order_state( *MAIN_CM, *MAIN_DM ); 
          &configure_dealers( *MAIN_CM, *MAIN_DM ); 
          &configure_card_type( *MAIN_CM, *MAIN_DM ); 
          &configure_devicestates( *MAIN_CM, *MAIN_DM ); 
          &configure_orderstates( *MAIN_CM, *MAIN_DM ); 
          chdir $CurrentDir;
      }
      }
    	
    ###########################################	
   # Load the pin_device_permit_map_voucher.
    ####################################################

	sub configure_device_permit_map {
	
        &Output( fpLogFile, $IDS_VOUCHER_MAP_LOADING );
        &Output( STDOUT, $IDS_VOUCHER_MAP_LOADING );

   	$Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_device_permit_map -v pin_device_permit_map_voucher");
  	 $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
    
   	if( $Cmd != 0 ) {
              &Output( fpLogFile, $IDS_VOUCHER_MAP_FAILED );
              &Output( STDOUT, $IDS_VOUCHER_MAP_FAILED );
              exit -1;
           } else {
              &Output( fpLogFile, $IDS_VOUCHER_MAP_SUCCESS );
              &Output( STDOUT, $IDS_VOUCHER_MAP_SUCCESS );
        }
   	unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
	
	##################################################
	# Load the pin_voucher_config.
	##################################################
	
	sub configure_voucher_config {
	
             &Output( fpLogFile, $IDS_VOUCHER_CONFIG_LOADING );
             &Output( STDOUT, $IDS_VOUCHER_CONFIG_LOADING );
         
             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_voucher_config -d -v pin_voucher_config");
             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
         
             if( $Cmd != 0 ) {
                &Output( fpLogFile, $IDS_VOUCHER_CONFIG_FAILED );
                &Output( STDOUT, $IDS_VOUCHER_CONFIG_FAILED );
                exit -1;
             } else {
                &Output( fpLogFile, $IDS_VOUCHER_CONFIG_SUCCESS );
                &Output( STDOUT, $IDS_VOUCHER_CONFIG_SUCCESS );
             }

	unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
	
	########################################################
	# Load the pin_device_state_voucher.
	######################################################
	sub configure_state_voucher {
	             &Output( fpLogFile, $IDS_VOUCHER_DEVICE_LOADING );
	             &Output( STDOUT, $IDS_VOUCHER_DEVICE_LOADING );
	         
	             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_device_state -v pin_device_state_voucher");
	             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
	         
	             if( $Cmd != 0 ) {
	                &Output( fpLogFile, $IDS_VOUCHER_DEVICE_FAILED );
	                &Output( STDOUT, $IDS_VOUCHER_DEVICE_FAILED );
	                exit -1;
	             } else {
	                &Output( fpLogFile, $IDS_VOUCHER_DEVICE_SUCCESS );
	                &Output( STDOUT, $IDS_VOUCHER_DEVICE_SUCCESS );
             }
             unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
	
	 ##################################################
	 # Load the pin_order_state_voucher.
	 ##################################################
	 sub configure_order_state {
	             &Output( fpLogFile, $IDS_VOUCHER_ORDER_LOADING );
	             &Output( STDOUT, $IDS_VOUCHER_ORDER_LOADING );
	         
	             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_order_state -dv pin_order_state_voucher");
	             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
	         
	             if( $Cmd != 0 ) {
	                &Output( fpLogFile, $IDS_VOUCHER_ORDER_FAILED );
	                &Output( STDOUT, $IDS_VOUCHER_ORDER_FAILED );
	                exit -1;
	             } else {
	                &Output( fpLogFile, $IDS_VOUCHER_ORDER_SUCCESS );
	                &Output( STDOUT, $IDS_VOUCHER_ORDER_SUCCESS );
	             }
             unlink( "$PIN_TEMP_DIR/tmp.out" );
	}

       ##################################################
       	 # Load the pin_dealers.
       	 ##################################################
       	 sub configure_dealers {
       	             &Output( fpLogFile, $IDS_VOUCHER_DEALERS_LOADING );
       	             &Output( STDOUT, $IDS_VOUCHER_DEALERS_LOADING );
       	         
       	             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_dealers -dv pin_dealers");
       	             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
       	         
       	             if( $Cmd != 0 ) {
       	                &Output( fpLogFile, $IDS_VOUCHER_DEALERS_FAILED );
       	                &Output( STDOUT, $IDS_VOUCHER_DEALERS_FAILED );
       	                exit -1;
       	             } else {
       	                &Output( fpLogFile, $IDS_VOUCHER_DEALERS_SUCCESS );
       	                &Output( STDOUT, $IDS_VOUCHER_DEALERS_SUCCESS );
       	             }
                    unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
	
	##################################################
		 # Load the pin_recharge_card_type.
		 ##################################################
		 sub configure_card_type {
		             &Output( fpLogFile, $IDS_VOUCHER_CARD_TYPE_LOADING );
		             &Output( STDOUT, $IDS_VOUCHER_CARD_TYPE_LOADING );
		         
		             $Cmd = &FixSlashes( "$PIN_HOME/bin/load_pin_recharge_card_type -dv pin_recharge_card_type");
		             $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
		         
		             if( $Cmd != 0 ) {
		                &Output( fpLogFile, $IDS_VOUCHER_CARD_TYPE_FAILED );
		                &Output( STDOUT, $IDS_VOUCHER_CARD_TYPE_FAILED );
		                exit -1;
		             } else {
		                &Output( fpLogFile, $IDS_VOUCHER_CARD_TYPE_SUCCESS );
		                &Output( STDOUT, $IDS_VOUCHER_CARD_TYPE_SUCCESS );
		             }
	             unlink( "$PIN_TEMP_DIR/tmp.out" );
	}
	
        ########################################################
        # Load localized strings for the voucher_devicestates 
        ##########################################################
        
        sub configure_devicestates {
        
	        &Output( fpLogFile, $IDS_VOUCHER_DEVICE_STRINGS_LOADING );
	        &Output( STDOUT, $IDS_VOUCHER_DEVICE_STRINGS_LOADING );
	    
	        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_localized_strings \"$PIN_HOME/sys/msgs/voucher_devicestates/device_state_voucher.en_US\"");
	        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
	    
	        if( $Cmd != 0 ) {
	           &Output( fpLogFile, $IDS_VOUCHER_DEVICE_STRINGS_FAILED );
	           &Output( STDOUT, $IDS_VOUCHER_DEVICE_STRINGS_FAILED );
	           exit -1;
	        } else {
	           &Output( fpLogFile, $IDS_VOUCHER_DEVICE_STRINGS_SUCCESS );
	           &Output( STDOUT, $IDS_VOUCHER_DEVICE_STRINGS_SUCCESS );
                }
                unlink( "$PIN_TEMP_DIR/tmp.out" );
	        }
        
        #############################################
        # Load localized strings for the voucher_orderstates  
        ##############################################
        
        sub configure_orderstates {
        
	        &Output( fpLogFile, $IDS_VOUCHER_ORDER_STRINGS_LOADING );
	        &Output( STDOUT, $IDS_VOUCHER_ORDER_STRINGS_LOADING );
	    
	        $Cmd = &FixSlashes( "$PIN_HOME/bin/load_localized_strings \"$PIN_HOME/sys/msgs/voucher_orderstates/order_state_voucher.en_US\"");
	        $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
	    
	        if( $Cmd != 0 ) {
	           &Output( fpLogFile, $IDS_VOUCHER_ORDER_STRINGS_FAILED );
	           &Output( STDOUT, $IDS_VOUCHER_ORDER_STRINGS_FAILED );
	           exit -1;
	        } else {
	           &Output( fpLogFile, $IDS_VOUCHER_ORDER_STRINGS_SUCCESS );
	           &Output( STDOUT, $IDS_VOUCHER_ORDER_STRINGS_SUCCESS );
               }
               unlink( "$PIN_TEMP_DIR/tmp.out" );
	       }
  	
1;
