#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_multidb.pl /cgbubrm_mainbrm.portalbase/2 2018/03/30 02:42:04 mkothari Exp $ 
# 
# Copyright (c) 2000, 2023, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the MultiDB Manager
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
# Configure MultiDB Manager pin.conf files
#
##########################################
sub configure_multidb_config_files {  
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;
  local ( @FileReadIn );
  local ( $Start );  

  &ReadIn_PinCnf( "pin_cnf_multidb.pl" );
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
      # Add CM entries and  multi db pin_confirm and pin_config entries
      &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%MULTIDB_PINCONF_ENTRIES );     


           
# Generating multi_db pin.conf
      local ($CONF) = $MULTI_DB{'pin_cnf_location'}."/".$PINCONF;
      if (-f $CONF)
      {
      # if the file already exist, retain the current configuration and make
      # pin.conf.unmodified for references
	$CONF = "$CONF.$CONFIGDISTEXT";
      }
      &Configure_PinCnf($CONF,
	  $MULTIDB_PINCONF_HEADER,
	  %MULTIDB_PINCONF_ENTRIES ); 

      #Generate $PIN_HOME/apps/multidb/config_dist.conf
      &ConfigDist();
}

sub configure_multidb_post_restart {

    if(( -e "pin_cmp_multidb.pl" ) && ( $SETUP_INIT_DB =~ /^YES$/i ) && ( join ( " ", @COMPONENT_LIST, " " ) =~ /\bmultidb\b/i ) && ($DM{'db_num'} eq "0.0.0.1") ) {
    
    local( $Cmd );
    local( $TempDir ) = &FixSlashes( "$PIN_HOME/apps/multi_db" );
    local( $CurrentDir ) = cwd();

    chdir( $TempDir );

    &Output( fpLogFile, "\nLoading config_dist.conf file into database\n" );
    &Output( STDOUT, "\nLoading config_dist.conf file into database\n" );

    $Cmd = &FixSlashes( "$PIN_HOME/bin/load_config_dist -v" );

    &Output( fpLogFile, $IDS_DISTRIBUTION_LOADING );
    &Output( STDOUT, $IDS_DISTRIBUTION_LOADING );

    $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );

    if( $Cmd != 0 ) {
        &Output( fpLogFile, $IDS_DISTRIBUTION_FAILED );
        &Output( STDOUT, $IDS_DISTRIBUTION_FAILED );
      exit -1;
    } else {
        &Output( fpLogFile, $IDS_DISTRIBUTION_SUCCESS );
        &Output( STDOUT, $IDS_DISTRIBUTION_SUCCESS );
    }
    unlink( "$PIN_TEMP_DIR/tmp.out" );
    chdir $CurrentDir;
    }
}
1;

#######
#
# Configuring database for MultiDB Mgr
#
#######
#sub configure_multidb_database {
#}
