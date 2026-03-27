#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_sample.pl /cgbubrm_mainbrm.portalbase/5 2018/03/30 02:42:05 mkothari Exp $ 
# 
# Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the Sample Viewer Components
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
# Configure pin.conf's for Sample Components 
#
#####
sub configure_sample_config_files {

  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;

  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_mta.pl" )

  #
  # Add entries to the Sample Component's pin.conf file ...
  #
  &Configure_PinCnf( $SAMPLE{'location'}."/".$PINCONF, 
                     $CONNECT_PINCONF_HEADER,
                     %CONNECT_PINCONF_ENTRIES );
  #
  # Add entries to the Sample Viewer Component's pin.conf file ...
  #
  &Configure_PinCnf( $SAMPLE{'viewer_location'}."/".$PINCONF, 
                     $CONNECT_PINCONF_HEADER,
                     %CONNECT_PINCONF_ENTRIES );

  # Add MTA entries and CM entries
    &AddArrays( \%CONNECT_PINCONF_ENTRIES, \%MTA_PINCONF_ENTRIES );
  
    # Create pin.conf entry in the mta_samples directory
    &Configure_PinCnf( $SAMPLE{'mta_location'}."/".$PINCONF,
                       $MTA_PINCONF_HEADER,
                       %MTA_PINCONF_ENTRIES );

}

sub configure_sample_post_restart {

  if ( ( -e "pin_cmp_sample.pl" ) &&
       ( $SETUP_INIT_DB =~ /^YES$/i ) &&
       ( join ( " ", @COMPONENT_LIST, " " ) =~ /\bsample\b/i ) ) {
      if ( $SETUP_PRICING =~ /^YES$/i && $INSTALL_TYPE =~ /^OUI$/i && $DM{'db_num'} eq "0.0.0.1" ) {
        &setupLoad_PriceList( *MAIN_CM, *MAIN_DM );
      }
  }
}
  
sub setupLoad_PriceList {
   local( *CM ) = shift( @_ );
   local( *DM ) = shift( @_ );

   local( $Cmd );
   local( $Sep );

   &Stop( $ServiceName{ 'cm' } );
   sleep( 6 );
   &Start( $ServiceName{ 'cm' } );
   sleep( 30 );

   local( $CurrentDir ) = cwd();
   my $count = 0;
   while(!&chk_test()) {
      print "checking testnap, still not up...\n";
      sleep( 20 );
      $count++;
      last if($count == 5);
   }
   chdir $CurrentDir;

   &Output( fpLogFile, $IDS_PRICE_LOADING );
   &Output( STDOUT, $IDS_PRICE_LOADING );

   if ( $SETUP_INIT_DB =~ /^YES$/i ) {
      $Cmd = &FixSlashes( "loadpricelist$extension -f -v -c $BILLING{'price_list_file'}" );

      $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );

      if( $Cmd != 0 ) {
         &Output( fpLogFile, $IDS_PRICE_FAILED );
         &Output( STDOUT, $IDS_PRICE_FAILED );
         exit -1;
      } else {
         &Output( fpLogFile, $IDS_PRICE_SUCCESS );
         &Output( STDOUT, $IDS_PRICE_SUCCESS );
      }
      unlink( "$PIN_TEMP_DIR/tmp.out" );
   }
}

1;
