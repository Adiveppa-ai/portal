#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_sms_settle_report.pl /cgbubrm_mainbrm.portalbase/3 2018/03/30 02:42:06 mkothari Exp $ 
#    
# Copyright (c) 2004, 2018, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the Sms Settle Report Component
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
# Configure Sms Settle Report pin.conf files
#
##########################################
sub configure_sms_settle_report_config_files {
  %CM = %MAIN_CM;
  %DM = %MAIN_DM;
  local ( @FileReadIn );
  local ( $Start );  

  &ReadIn_PinCnf( "pin_cnf_sms_settle_report.pl" );
  

# If the sys/cm/pin.conf is there, add the entries to it.
# If not, add the entries to the temporary pin.conf file.

  if ( -f $CM{'location'}."/".$PINCONF )
  {
   	open( PINCONFFILE, $CM{'location'}."/".$PINCONF );
   	@FileReadIn = <PINCONFFILE>;
   	close( PINCONFFILE );

	# Search for sms_settle_report_fm_required... If not found, we need
	# to add the sms_settle_report fm's to the pin.conf file... We also
	#
	$Start = &LocateEntry( "sms_settle_report_fm_required", @FileReadIn );
	if ( $Start == -1 )  # Entry not created before hence create it.
	{
		&AddArrays( \%SMS_SETTLE_REPORT_CM_PINCONF_ENTRIES);
	}

        my $entry = `grep "fm_ic_config" $CM{'location'}"/"$PINCONF | wc -l`;
        if($entry == 0) {
		&AddPinConfEntries( $CM{'location'}."/".$PINCONF, %SMS_SETTLE_REPORT_CM_PINCONF_ENTRIES );
        }

	
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

    &AddArrays( \%SMS_SETTLE_REPORT_CM_PINCONF_ENTRIES);
    &AddPinConfEntries( "$TEMP_PIN_CONF_FILE", %SMS_SETTLE_REPORT_CM_PINCONF_ENTRIES );

    # Display a message saying to append this file to cm/pin.conf file.
   &Output( STDOUT, $IDS_APPEND_PIN_CONF_MESSAGE,
                        $CM{'location'}."/".$PINCONF,
                       $CurrentComponent,
                        $TEMP_PIN_CONF_FILE );

   }

}

#####################################
#
# Configuring database for Sms Settle Report
#
#####################################
sub configure_sms_settle_report_database {
  
  require "./pin_".$MAIN_DM{'db'}->{'vendor'}."_functions.pl";
  require "./pin_cmp_dm_db.pl";
  local ( $TMP ) = $SKIP_INIT_OBJECTS;
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;
  
  &PreModularConfigureDatabase( %CM, %DM );

  #########################################
  # Creating the tables for the Sms Settle Report
  #########################################
  $SKIP_INIT_OBJECTS = "YES";
  $USE_SPECIAL_DD_FILE = "YES";

    if ( VerifyPresenceOfTable( "sms_settle_rpt_t", %{DM->{'db'}} ) == 0 ){
    
    $SPECIAL_DD_FILE = "$DD{'location'}/dd_objects_sms_settle_report.source";
    $SPECIAL_DD_DROP_FILE = "$DD{'location'}/drop_tables_sms_settle_report".$MAIN_DM{'db'}->{'vendor'}.".source";
  
    if ( $SETUP_DROP_ALL_TABLES =~ m/^YES$/i ) {
       &DropTables( %{MAIN_DM->{"db"}} );
    }
     
    &pin_pre_modular( %{DM->{'db'}} );
    &pin_init( %DM );
    &pin_post_modular( %DM );
  }
    
$USE_SPECIAL_DD_FILE = "NO";
$SKIP_INIT_OBJECTS = $TMP;
&PostModularConfigureDatabase( %CM, %DM );
}
1;
