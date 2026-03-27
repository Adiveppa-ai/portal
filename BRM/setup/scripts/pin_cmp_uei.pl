#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_uei.pl /cgbubrm_mainbrm.portalbase/4 2018/03/30 02:42:06 mkothari Exp $
# 
# Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the UEI Component
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
# Configure UEI Infranet.properties and pin.conf files
#
#####
sub configure_uei_config_files {

  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;

  $MAIN_CM{'login_name'} = "java_client";
  $MAIN_CM{'user_id'} = "409"; 
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );

  #
  #  Configure Infranet.properties with current values ...
  #
  $i = 0;
  open( PROPFILE, "+< $UEI{'location'}/Infranet.properties" ) || die( "Can't open $UEI{'location'}/Infranet.properties" );
  @Array_PROP = <PROPFILE>;
  seek( PROPFILE, 0, 0 );
  while ( <PROPFILE> )
  {
    $_ =~ s/infranet\.connection.*/#infranet\.connection=pcp:\/\/root.$DM{'db_num'}:$MAIN_CM{'pcm_admin_passwd'}\@$CM{'hostname'}:$CM{'port'}\/service\/pcm_client/i;
    $_ =~ s/infranet\.uel\.event_log_file_location.*/infranet\.uel\.event_log_file_location=$UEI{'location'}\//i;
    $_ =~ s/infranet\.uel\.cache_file_location.*/infranet\.uel\.cache_file_location=$UEI{'location'}\//i;
    $_ =~ s/infranet\.uel\.filter_log_file_location.*/infranet\.uel\.filter_log_file_location=$UEI{'location'}\//i;
    $_ =~ s/infranet\.uel\.load_error_file_location.*/infranet\.uel\.load_error_file_location=$UEI{'location'}\//i;
    $_ =~ s/infranet\.uel\.load_success_file_location.*/infranet\.uel\.load_success_file_location=$UEI{'location'}\//i;
    $_ =~ s/infranet\.uel\.error_log_file_location.*/infranet\.uel\.error_log_file_location=$UEI{'location'}\//i;
    $Array_PROP[$i++] = $_;
  }
  seek( PROPFILE, 0, 0 );
  print PROPFILE @Array_PROP;
  print PROPFILE "\n";
  truncate( PROPFILE, tell( PROPFILE ) );
  close( PROPFILE );
  chmod(0640,"$UEI{'location'}/Infranet.properties");

  #
  # Add entries to the pin.conf file ...
  #
  &Configure_PinCnf( $UEI{'location'}."/".$PINCONF, 
                     $CONNECT_PINCONF_HEADER,
                     %CONNECT_PINCONF_ENTRIES );
  $MAIN_CM{'login_name'} = $CM{'login_name'};
  $MAIN_CM{'user_id'} = $CM{'user_id'};

  #
  # Configure apps/batch_controller/Infranet.properties with values for RatedEventLoader ...
  #
  # If the file exists, add the entries to it.
  # If not, add the entries to a temporary file.
  #

  #####################################################################
  # Configure batchcontroller Infranet.properties files for UEL Handler 
  #####################################################################
  $PROP_full_pathname = "$BATCH_CONTROLLER{'location'}/Infranet.properties";

  # The *.pl entries are named *.bat in Infranet.properties, for NT installs.
  if ( $^O =~ /win/i )
  {
    $PERL_EXTENSION = "";
  }
  else
  {
    $PERL_EXTENSION = ".pl";
  }

  # Create temporary file, if it does not exist.
  if ( -f $PROP_full_pathname )
  {
    $PROP_pathname = $PROP_full_pathname;
  }
  else
  {
    $PROP_pathname = "$PIN_HOME/append_to_Infranet_properties";
    $PROP_short_pathname = "Infranet.properties";
    open( PROPFILE, ">> $PROP_pathname" );
    close( PROPFILE );
  }

  open( PROPFILE, "+< $PROP_pathname" ) || die( "Can't open $PROP_pathname" );

  @Array_PROP = <PROPFILE>;
  seek( PROPFILE, 0, 0 );

  $DoUpdate = TRUE;
  if ( -f $PROP_pathname )
  {
    while ( <PROPFILE> )
    {
      if ( $_ =~ /^relHandler/ )
      {
        $DoUpdate = FALSE;
      }
    }
  }

  if ( $DoUpdate eq TRUE )
  {

    #
    # Append the RatedEventLoader events to the existing entries.
    #
    $i = 0;
    seek( PROPFILE, 0, 0 );
    push( @Array_PROP, <<END

UEL.name = UEL
UEL.handlers = UEL_hdlr
UEL.file.location =		$UEI{'uel_input_dir_location'}
UEL.file.pattern  =		*
UEL_hdlr.name 	  =		UEL
UEL_hdlr.max.at.highload.time =	3
UEL_hdlr.max.at.lowload.time  =	3
UEL_hdlr.start.string 	=	$UEI{'location'}/UELRelHandler$PERL_EXTENSION
END
    );

    seek( PROPFILE, 0, 0 );
    print PROPFILE @Array_PROP;
    print PROPFILE "\n";
    truncate( PROPFILE, tell( PROPFILE ) );
    close( PROPFILE );
    chmod(0640,$PROP_pathname);

    if ( ! -f $PROP_full_pathname )
    {
      # Display a message saying to append this file to apps/batch_controller/Infranet.properties file.
      &Output( STDOUT, $IDS_APPEND_TO_FILE_MESSAGE,
                        $PROP_full_pathname,
                        $CurrentComponent,
                        $PROP_short_pathname,
                        $PROP_pathname );
    };

  }

  if ( ! -e "$PIN_HOME/BATCH_FILES_GEN" ){
   mkdir ("$PIN_HOME/BATCH_FILES_GEN", 0755) || die "Unable to create $PIN_HOME/BATCH_FILES_GEN directory" ;
  }
}
1;
