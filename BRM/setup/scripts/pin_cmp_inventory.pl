#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_inventory.pl /cgbubrm_mainbrm.portalbase/2 2018/03/30 02:42:03 mkothari Exp $ 
#    
# Copyright (c) 2006, 2018, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the InventoryManager Component
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
# Configure InventoryManager pin.conf files
#
##########################################
sub configure_inventory_config_files {
  %CM = %MAIN_CM;
  %DM = %MAIN_DM;
  local ( @FileReadIn );
  local ( $Start );  

  &ReadIn_PinCnf( "pin_cnf_inventory.pl" );
  

# If the sys/cm/pin.conf is there, add the entries to it.
# If not, add the entries to the temporary pin.conf file.

  if ( -f $CM{'location'}."/".$PINCONF )
  {
   	&ReplacePinConfEntries( $CM{'location'}."/".$PINCONF, %INVENTORYMANAGER_CM_PINCONF_ENTRIES );
	
  }
  else
  {
   # Create temporary file, if it does not exist.
   $TEMP_PIN_CONF_FILE = $PIN_HOME."/".$IDS_TEMP_PIN_CONF;
   open( PINCONFFILE, ">> $TEMP_PIN_CONF_FILE" );
   close( PINCONFFILE );

   &ReplacePinConfEntries( "$TEMP_PIN_CONF_FILE", %INVENTORYMANAGER_CM_PINCONF_ENTRIES );
    
   # Display a message saying to append this file to cm/pin.conf file.
   &Output( STDOUT, $IDS_APPEND_PIN_CONF_MESSAGE,
                        $CM{'location'}."/".$PINCONF,
                       $CurrentComponent,
                        $TEMP_PIN_CONF_FILE );

   }

}

#####################################
#
# Configuring database for InventoryManager 
#
#####################################
sub configure_inventory_database {
  
  require "./pin_".$MAIN_DM{'db'}->{'vendor'}."_functions.pl";
  require "./pin_cmp_dm_db.pl";
  local ( $TMP ) = $SKIP_INIT_OBJECTS;
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;
  
  &PreModularConfigureDatabase( %CM, %DM );

  #########################################
  # Creating the tables for the OrderManager 
  #########################################
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
    
  $USE_SPECIAL_DD_FILE = "NO";
  $SKIP_INIT_OBJECTS = $TMP;
  
  if ( VerifyPresenceOfFieldName( "QUANTITY","ORDER_T", %{DM->{'db'}} ) == 0 ){      
    $SKIP_INIT_OBJECTS = "YES";
    $USE_SPECIAL_DD_FILE = "YES";
    $SPECIAL_DD_FILE = "$DD{'location'}/6.5SP2_6.7_dd_objects_order.source";      
        	   	   
          #This is a special condition for 6.5 to later version upgrades.
          #pre_modular and post_modular should not be called since there is an error with Obj Ids in 6.5
    #&pin_pre_modular( %{DM->{'db'}} );
    &pin_init( %DM );
    #&pin_post_modular( %DM );
               
    $USE_SPECIAL_DD_FILE = "NO";
    $SKIP_INIT_OBJECTS = $TMP;
  }  


 &PostModularConfigureDatabase( %CM, %DM );
}
1;
