#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=======================================================================
#  @(#)%Portal Version: pin_setup.pl:PortalBase7.3.1Int:1:2007-Sep-11 23:43:12 %
# 
# $Header: install_vob/install_common/Unix/install/pin_setup.pl /cgbubrm_mainbrm.portalbase/18 2018/07/26 02:46:57 mkothari Exp $
#
# Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Main Perl script for the Portal installation
#
#=============================================================

use Cwd;
require "pin_oracle_functions.pl";
require "./pin_res.pl";
require "./pin_functions.pl";
require "../pin_setup.values";

$RUNNING_IN_PIN_SETUP = TRUE;

$StartTime = localtime(time());

if($INSTALL_TYPE =~ /^OUI$/i) {
        system("perl ../../../setup/scripts/postInstallReplace.pl");
}

if ($ARGV[0] =~ /-GA/) {
	my $perlVersion = $];

	if($perlVersion !~ /5.024/) {
		#print "perl version should be 5.24.0 for GA pin_setup \n";
		#exit;
	}

        if(-f "$PIN_HOME/lib/aes.so.GA") {

                if(!-f "$PIN_HOME/lib/aes.so.PS") {
			system(" cp -rf $PIN_HOME/lib/aes.so $PIN_HOME/lib/aes.so.PS ");
			system(" cp -rf $PIN_HOME/lib/pcmdd.so $PIN_HOME/lib/pcmdd.so.PS ");
			system(" cp -rf $PIN_HOME/lib/pcmif.so $PIN_HOME/lib/pcmif.so.PS ");
		}
		system(" cp -rf $PIN_HOME/lib/aes.so.GA $PIN_HOME/lib/aes.so ");
		system(" cp -rf $PIN_HOME/lib/pcmdd.so.GA $PIN_HOME/lib/pcmdd.so ");
		system(" cp -rf $PIN_HOME/lib/pcmif.so.GA $PIN_HOME/lib/pcmif.so ");
	}
}

#
#Run pin_setup for a particular product by passing the product name as arguments and
#Run pin_setup for all products by passing the argument "-all"
# usage:  pin_setup.pl <product_name> or 
#	  pin_setup.pl -all
#
#  product_name - Name of the product to be present in the PRODUCT_LIST array of pin_etup.values.  


if ( @ARGV && $ARGV[0] !~ /-all/) {
	@PRODUCT_LIST = reverse @PRODUCT_LIST;
	undef(@COMPONENT_LIST) if ($ARGV[0] !~ /-GA/);
	foreach $arg (@ARGV) {			   
	   if(grep(/^$arg$/,@PRODUCT_LIST)) {  	      
	      print "configuring for $arg \n";
	      push(@COMPONENT_LIST,@$arg);
	      print "\nConfiguring pin_setup for $arg\n";
	      &call_pinsetup();
	      undef(@COMPONENT_LIST);
	      }
	   else {
              if ($ARGV[0] =~ /-GA/) {
                  print "Running pin_setup for GA component.\n";
                  &call_pinsetup();
	      } else {
	          print "$arg is not present in the  @PRODUCT_LIST array of pin_setup.values\n";
	      }
	   }
	}
}

if ($ARGV[0] =~ /-all/) {
        print "\n Configuring pin_setup for the all the products\n";
        undef(@COMPONENT_LIST);
        if($INSTALL_TYPE =~ /^OUI$/i) {
                open FILE, "../pin_setup.values"  or die $!;
                        while(<FILE>) {
                                if($_ =~ /#\@COMPONENT_LIST/) {
                                        @a = split('\(',$_);
                                        @b = split('\)',$a[1]);
                                        @c = split(',',$b[0]);
                                        foreach $co (@c) {
                                                $co =~ s/"//g;
                                                $co =~ s/^\s+//g;
                                                $co =~ s/\s+$//g;
                                                push(@COMPONENT_LIST,$co);
                                        }
                                }
                        }
                close(FILE);
                &call_pinsetup();
                undef(@COMPONENT_LIST);
        } else {
                @MY_PRODUCT_LIST = reverse @PRODUCT_LIST;
                foreach $prod(@MY_PRODUCT_LIST) {
                        print "configuring for $prod \n";
                        push(@COMPONENT_LIST,@$prod);
                        print "\nConfiguring pin_setup for $prod\n";
                        &call_pinsetup();
                        undef(@COMPONENT_LIST);
                }
        }
}

#
#Existing method of calling pin_setup for last installed product
#need to be removed once started using PRODUCT_LIST array
#

if (!@ARGV) {
    &call_pinsetup();
}
		   
sub call_pinsetup {
#
# Open the log file for installation
#
&OpenLogFile( $SETUP_LOG_FILENAME, $SETUP_LOG_ACCESS_TYPE );
&Output( fpLogFile, $IDS_LOG_TIME, $StartTime );
&Output( STDOUT, $IDS_SHOW_TIME, $StartTime );
if( ! exists ($ENV{'PIN_HOME'}) )
{
  &Output( STDOUT,$IDS_ENV_VARIABLES_NOT_FOUND,"\$PIN_HOME");
  exit;
}
if( ! -e "$ENV{'PIN_HOME'}" )
{
  &Output( STDOUT,$IDS_ENV_VARIABLES_PATH_INVALID,"\$PIN_HOME");
  exit;
}
if(! exists ( $ENV{'PIN_LOG_DIR'}) )
{
  &Output( STDOUT,$IDS_ENV_VARIABLES_NOT_FOUND,"\$PIN_LOG_DIR");
  exit;
}
if(! -e "$ENV{'PIN_LOG_DIR'}" )
{
  &Output( STDOUT,$IDS_ENV_VARIABLES_PATH_INVALID,"\$PIN_LOG_DIR");
  exit;
}


if ( $^O !~ /win/i )
{
	if(! exists ( $ENV{'LIBRARYPREFIX'}) )
  	{
  		&Output( STDOUT,$IDS_ENV_VARIABLES_NOT_FOUND,"\$LIBRARYPREFIX");
 		 exit;
	}
}

if(! exists ( $ENV{'LIBRARYEXTENSION'}) )
{
  &Output( STDOUT,$IDS_ENV_VARIABLES_NOT_FOUND,"\$LIBRARYEXTENSION");
  exit;
}

#
if ( join ( " ", @COMPONENT_LIST ) =~ /(\bdm_oracle\b)/i ) {
  ($DB_TYPE = $1) =~ s/dm_//;
  eval qq!require "./pin_".$DB_TYPE."_functions.pl"!;

# Skip the sanity check for New DB user , which will be created later
  if ( $CREATE_DATABASE_TABLES =~ /NO/i) {
    &VerifyLogin( "portal", %MAIN_DB );
  }
}


#
# Adjust the order of components in @COMPONENT_LIST.
# This is because the cm/pin.conf creation and the main database configuration must occur first.
#
@TEMP_LIST = ();
$add_cm = "";
$add_dm_oracle = "";
$add_inventory = "";
$add_tcframework = "";
$i = 0;
foreach $CurrentComponent ( @COMPONENT_LIST ) {
	next if($CurrentComponent eq "" && $INSTALL_TYPE =~ /^OUI$/i);
	if ( $CurrentComponent =~ /(\bcm\b|\bdm_oracle\b|\binventory\b|\btcframework\b)/i )
	{
		# Set flags if these special components are found.
		if ( $CurrentComponent =~ /^cm$/i ) { $add_cm = "y" };
		if ( $CurrentComponent =~ /^dm_oracle$/i ) { $add_dm_oracle = "y" };
                if ( $CurrentComponent =~ /^inventory$/i ) { $add_inventory = "y" };
                if ( $CurrentComponent =~ /^tcframework$/i ) { $add_tcframework = "y" };
	}
	elsif ( $CurrentComponent =~ /[a-z]+/ )
	{
		# Add the regular components to the list.
		$TEMP_LIST[$i++] = $CurrentComponent;
	}
}
# Add these special components to the end of the list.
if ( $add_inventory =~ /^y$/ )  { $TEMP_LIST[$i++] = "inventory" };
if ( $add_tcframework =~ /^y$/ )  { $TEMP_LIST[$i++] = "tcframework" };
if ( $add_dm_oracle =~ /^y$/ )  { $TEMP_LIST[$i++] = "dm_oracle" };
if ( $add_cm =~ /^y$/ )         { $TEMP_LIST[$i++] = "cm" };
$TEMP_LIST[$i] = "";
@COMPONENT_LIST = @TEMP_LIST;


#
# For each component in the list (starting at the end), configure their pin.conf
# entries and their database
#
@TEMP_LIST = reverse( @COMPONENT_LIST );
foreach $CurrentComponent ( @TEMP_LIST ) {
   #
   # Is this a real component or is this just a stub for starting and stopping
   # 
   eval qq!require "./pin_cmp_$CurrentComponent.pl"!;

   #
   # If the pre-configure script is there, run it.
   #
   &pre_configure;
     
   $skip = eval '$setup_execute_pin_cmp_'.$CurrentComponent;

   if ( $skip eq TRUE ) {
      &Output( fpLogFile, $IDS_SCRIPT_SKIPPED, "pin_cmp_$CurrentComponent.pl" );
      &Output( STDOUT, $IDS_SCRIPT_SKIPPED, "pin_cmp_$CurrentComponent.pl" );
   } else {

      # Make sure the component is stopped
      if ( $ServiceName{ $CurrentComponent } !~ /^$/ ) {
          &Stop( $ServiceName{ $CurrentComponent } );
      }

      #
      # if the function for configure_xxx_config file is defined, call it
      #
      $function_name = "configure_$CurrentComponent"."_config_files";
      if ( ( $SETUP_CONFIGURE =~ /^YES$/i ) &&
           ( defined ( &$function_name ) ) ) {
         #&Output( STDOUT, $IDS_CONFIGURING_PIN_CONF, $CurrentComponent );
         #&Output( fpLogFile, $IDS_CONFIGURING_PIN_CONF, $CurrentComponent );
         eval "&configure_$CurrentComponent"."_config_files;";
      }
      $function_name = "configure_$CurrentComponent"."_database";
      if ( ( $SETUP_INIT_DB =~ /^YES$/i ) &&  
           ( defined( &$function_name ) ) ) {
    	 &Output( STDOUT, $IDS_CONFIGURING_DATABASE, $CurrentComponent );
         &Output( fpLogFile, $IDS_CONFIGURING_DATABASE, $CurrentComponent );
         eval '&configure_'.$CurrentComponent.'_database;';
      }
   }
   #
   # If there is a post-install script there, run it
   # 
   &post_configure;

}

#
# Create the views using create_views.source
#

if ( ( -f "$PIN_HOME/sys/dd/data/create_views.source" ) &&
     ( $SETUP_INIT_DB =~ /^YES$/i ) ) {
        &ExecuteSQL_Statement_From_File( "$PIN_HOME/sys/dd/data/create_views.source",
                TRUE,
                TRUE,
                %MAIN_DB );

                if ( VerifyPresenceOfError() == 0) {

                        print"Your installation has completed with errors \nLook into pin_setup.log for detail error messages \n";
                        exit ( 0 );
                }
}

#
# Encrypt passwords in config. files
#
#if (-e "encryptpassword.pl") {
#  my $my_cmd = "./encryptpassword.pl pin_setup";
#  my $ret = system($my_cmd);
#  if ($ret >> 8 != 0) {
#     print "fail to run $my_cmd. Reason: $! \n val is $? \n";
#  }
#}

#
# Make sure the CM is stopped before starting all components.
#
if ( -f $MAIN_CM{'location'}."/".$PINCONF )
{
    &Stop( $ServiceName{ "cm" } );
    sleep( 10 );
}

#
# Stop & Start all the components 
#
if ( ( $SETUP_INIT_DB =~ /^YES$/i ) ) {
    foreach $CurrentComponent ( @COMPONENT_LIST ) {
        if ( $ServiceName{ $CurrentComponent } !~ /^$/ ) {
            &Output( STDOUT, $IDS_STARTING, $CurrentComponent );
            &Output( fpLogFile, $IDS_STARTING, $CurrentComponent );
            &Stop( $ServiceName{ "$CurrentComponent" } );
            &Start( $ServiceName{ "$CurrentComponent" } );
        }
    }
}

#
# Make sure the CM is started incase CM is not in the COMPONENT list.
#
if  ( join ( " ", @COMPONENT_LIST, " " ) !~ /\bcm\b/i ) {
        if ( ( $SETUP_INIT_DB =~ /^YES$/i ) ) {
		&Start( $ServiceName{ 'cm' } );
		sleep( 10 );
	}
}

#
# We should now have Portal up and running. If testnap is present,
# let's test out our connection
#
if ( ( join ( " ", @COMPONENT_LIST, " " ) =~ /\btestnap\b/i ) &&
     ( join ( " ", @COMPONENT_LIST, " " ) =~ /\bcm\b/i ) &&
     ( $SETUP_INIT_DB =~ /^YES$/i ) ) {
  &WaitWithDots( $IDS_WAITING_FOR_PORTAL, 50 );
  &testnap_TestConnection( %MAIN_CM );
}


#
# Do additional configuration after all components have been started 
#
if($DM{'db_num'} eq "0.0.0.1") {
    foreach $CurrentComponent ( @COMPONENT_LIST ) {
        $function_name = "configure_$CurrentComponent"."_post_restart";
        if ( ( $SETUP_INIT_DB =~ /^YES$/i ) &&
	    ( defined( &$function_name ) ) ) {
            eval '&configure_'.$CurrentComponent.'_post_restart;';
        }
    }
} 


#
# Do any final configuration for all components
#
foreach $CurrentComponent ( @COMPONENT_LIST ) {
      $function_name = "configure_$CurrentComponent"."_post_configure";
      if ( defined( &$function_name ) ) {
         eval '&configure_'.$CurrentComponent.'_post_configure;';
      }
}

#
# change permission for config. files post restart
#
if (-e "encryptpassword.pl" && ($ARGV[0] !~ /-GA/)) {
  my $my_cmd = "perl ./encryptpassword.pl pin_setup_chmod";
  my $ret = system($my_cmd);
  if ($ret >> 8 != 0) {
     print "fail to run $my_cmd. Reason: $! \n val is $? \n";
  }
}

# Restart the CM to clear cached Information
if ( ( join ( " ", @COMPONENT_LIST, " " ) =~ /\bcm\b/i ) &&
     ( $SETUP_INIT_DB =~ /^YES$/i ) ) {
      &Output( STDOUT, $RESTARTING_CM ); 
      &Output( fpLogFile, $RESTARTING_CM ); 
      if ( $ServiceName{ 'cm' } !~ /^$/ ) {
        &Stop( $ServiceName{ 'cm' } );
	sleep( 6 );
        &Start( $ServiceName{ 'cm' } );
	sleep( 10 );
      }
}
   

$partlog = "partition_utils.log";

if(-e $partlog) {
  open(PARTUTIL, "$partlog");
  $errlog=1;
  &Err_Validation();
}
else {
  &Output( fpLogFile, $IDS_SUCCESS );
  &Output( STDOUT, $IDS_SUCCESS );
}

sub Err_Validation {
  while(<PARTUTIL>) {
    if($_=~/ERROR/) {
       print"Your installation has completed with errors \nLook into partition_utils.log for detail error messages \n";
       exit ( 0 );
       $errlog=0;
    }
  }

  if($errlog){
    &Output( fpLogFile, $IDS_SUCCESS );
    &Output( STDOUT, $IDS_SUCCESS );
  }

}

if($INSTALL_TYPE =~ /^OUI$/i && $ARGV[0] !~ /-all/) {
	&modify_component_list();
}

if($ENABLE_SSL =~ /^1$/ &&  $INSTALL_TYPE =~ /^OUI$/i) {
        system("perl $PIN_HOME/setup/scripts/sslConfig.pl 1");
        
        if (-e "$PIN_LOG_DIR/dm_oracle/dm_oracle.pinlog") {
                open (TMPFILE,">$PIN_LOG_DIR/dm_oracle/dm_oracle.pinlog ")|| die "cannot open . \n";
                close (TMPFILE);
        }

        if (-e "$PIN_LOG_DIR/cm/cm.pinlog") {
                open (TMPFILE,">$PIN_LOG_DIR/cm/cm.pinlog ")|| die "cannot open . \n";
                close (TMPFILE);
        }

        if ( ( $SETUP_INIT_DB =~ /^YES$/i ) ) {
	    foreach $CurrentComponent ( @COMPONENT_LIST ) {
	        if ( $ServiceName{ $CurrentComponent } !~ /^$/ ) {
		    &Output( STDOUT, $IDS_STARTING, $CurrentComponent );
		    &Output( fpLogFile, $IDS_STARTING, $CurrentComponent );
		    &Stop( $ServiceName{ "$CurrentComponent" } );
		    &Start( $ServiceName{ "$CurrentComponent" } );
	        }
	    }
        }
}

}

sub modify_component_list{
        $pin_setup_values = "$PIN_HOME/setup/pin_setup.values";
        open (IN,$pin_setup_values) || die "unable to open $pin_setup_values";
        @lines=<IN>;
        close(IN);
        open(OUT,">",$pin_setup_values) || die "unable to open $pin_setup_values";
        foreach my $line (@lines){
		if ($line =~ /^#/) {
			print OUT $line;
			next;
		}
		if ($line =~ /\@COMPONENT_LIST/) {
			print OUT "\#"."$line";
			print OUT "\@COMPONENT_LIST= (\" \");\n";
			next;
		}
		print OUT $line;
	}
	close(OUT);
}

if ($ARGV[0] =~ /-GA/ && -f "$PIN_HOME/lib/aes.so.PS" && -f "$PIN_HOME/lib/aes.so.GA") {
	system(" cp -rf $PIN_HOME/lib/aes.so.PS $PIN_HOME/lib/aes.so ");
	system(" cp -rf $PIN_HOME/lib/pcmdd.so.PS $PIN_HOME/lib/pcmdd.so ");
	system(" cp -rf $PIN_HOME/lib/pcmif.so.PS $PIN_HOME/lib/pcmif.so ");
}
exit ( 0 );
