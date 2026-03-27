#!__PERL__
#=============================================================
# @(#)$Id: pin_cmp_cmt.pl /cgbubrm_mainbrm.portalbase/10 2018/11/22 01:06:23 njuturu Exp $
#
# Copyright (c) 2001, 2020, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation 
#       or its licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
# Portal installation for the Common Migration Tool Component
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
# Configure commonmigration Manager pin.conf files
#
##########################################
sub configure_commonmigration_config_files {
  local ( %CM ) = %MAIN_CM;

  $MAIN_CM{'login_name'} = "java_client";
  $MAIN_CM{'user_id'} = "409";  
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  &ReadIn_PinCnf( "pin_cnf_cmt.pl" );
  &ReadIn_PinCnf( "pin_cnf_mta.pl" );

  &AddArrays( \%MTA_PINCONF_ENTRIES, \%CONNECT_PINCONF_ENTRIES );

#
# Create pin.conf for CMT.
#
  &Configure_PinCnf( $CMT{'location'}."/".$PINCONF, 
                     $COMMONMIGRATION_HEADER, 
                     %CONNECT_PINCONF_ENTRIES);
  $MAIN_CM{'login_name'} = $CM{'login_name'};
  $MAIN_CM{'user_id'} = $CM{'user_id'};
}


#########################################
# Configure Infranet.properties files
#########################################
sub configure_cmt_config_files {

  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;

  local( $Cmd );
  local( $Sep );

  &configure_commonmigration_config_files();

  #
  #  Configure Infranet.properties with current values ...
  #
  $i = 0;
  &Configure_Infranet("$PIN_HOME/apps/cmt/Infranet.properties");
  open( PROPFILE, "+< ${PIN_HOME}/apps/cmt/Infranet.properties" ) || die( "Can't open ${PIN_HOME}/apps/cmt/Infranet.properties" );
  @Array_PROP = <PROPFILE>;
  seek( PROPFILE, 0, 0 );
  while ( <PROPFILE> )
  {
    $_ =~ s/^\s*infranet\.cmt\.dbname.*/infranet\.cmt\.dbname = $CMT{'alias'}/i;
    $_ =~ s/^\s*infranet\.cmt\.userid.*/infranet\.cmt\.userid = $CMT{'userid'}/i;
    $_ =~ s/^\s*infranet\.cmt\.passwd.*/#infranet\.cmt\.passwd = $CMT{'passwd'}/i;
	$_ =~ s/^\s*infranet\.cmt\.schema\.location.*/infranet\.cmt\.schema\.location = $CMT{'schema'}/i;
	$_ =~ s/^\s*infranet\.cmt\.datfile\.location.*/infranet\.cmt\.datfile\.location = $CMT{'datfile'}/i;
	$_ =~ s/^\s*infranet\.cmt\.ctlfile\.location.*/infranet\.cmt\.ctlfile\.location = $CMT{'ctlfile'}/i;
	$_ =~ s/^\s*infranet\.cmt\.preprocess\.validation.*/infranet\.cmt\.preprocess\.validation = $CMT{'preprocess_validation'}/i;
	$_ =~ s/^\s*infranet\.cmt\.file\.location.*/infranet\.cmt\.file\.location = $CMT{'lfile'}/i;
	$_ =~ s/^\s*infranet\.connection.*/#infranet\.connection=pcp:\/\/root.0.0.0.1:$MAIN_CM{'pcm_admin_passwd'}\@$HOSTNAME:$MAIN_CM{'port'}\/service\/admin_client 1/i;
	
	$_ =~ s/^\s*infranet\.cmt\.dbnumber\.location.*/infranet\.cmt\.dbnumber\.location = $CMT{'dbnumber'}/i;
    $_ =~ s/^\s*infranet\.cmt\.primarydbname.*/infranet\.cmt\.primarydbname = $CMT{'primarydbname'}/i;
    $_ =~ s/^\s*infranet\.cmt\.primarydbuserid.*/infranet\.cmt\.primarydbuserid = $CMT{'primarydbuserid'}/i;
    $_ =~ s/^\s*infranet\.cmt\.primarydbpasswd.*/#infranet\.cmt\.primarydbpasswd = $CMT{'primarydbpasswd'}/i;
	$_ =~ s/^\s*infranet\.cmt\.primarydbnumber\.location.*/infranet\.cmt\.primarydbnumber\.location = $CMT{'primarydbnumber'}/i;
    
    $Array_PROP[$i++] = $_;
  }
  seek( PROPFILE, 0, 0 );
  print PROPFILE @Array_PROP;
  print PROPFILE "\n";
  truncate( PROPFILE, tell( PROPFILE ) );
  close( PROPFILE );
  chmod(0640,"${PIN_HOME}/apps/cmt/Infranet.properties");

   if ( $^O =~ /win/i ) {
     $Pref = "@";
     $Sep = ";";
     $wild = "\%*";
     $extension = ".bat";
   } else {
     $Pref = "";
     $Sep = ":";
     $wild = "\$1 \$2 \$3 \$4 \$5 \$6 \$7 \$8 \$9";
     $extension = "";
   }

   # Create the script to launch the application  
	$Cmd = &FixSlashes( $Pref."__JAVA_HOME__/bin/java -Dfile.encoding=utf-8 -cp \"$PIN_HOME/apps/cmt/cmt.jar".$Sep
		   ."$ENV{ORACLE_HOME}/jdbc/lib/ojdbc8.jar".$Sep
		   ."$ENV{ORACLE_HOME}/lib/ojdbc8.jar".$Sep
		   ."$PIN_HOME/jars/pcm.jar".$Sep
		   ."$PIN_HOME/jars/pcmext.jar".$Sep
		   ."$PIN_HOME/jars/oraclepki.jar".$Sep
		   ."$PIN_HOME/jars/osdt_cert.jar".$Sep
		   ."$PIN_HOME/jars/osdt_core.jar".$Sep
		   ."$PIN_HOME/apps/cmt\" com.portal.cmt.Cmt $wild" );

	        open( BATCHFILE, "$PIN_HOME/apps/cmt/pin_cmt$extension" );
	 	@Array_BATCHFILE = <BATCHFILE>;
		$z = 0;
	 	seek( BATCHFILE, 0, 0 );
	  	while ( <BATCHFILE> ){
		    $_ =~ s/__REPLACE__JAVA__APP__/$Cmd/;

		    my @list = ("httpclient-4.4", "httpclient-4.5.3", "httpclient-4.5.6", "httpclient-4.5.8", "httpclient-4.5.11", "httpclient-4.5.13", "httpclient5-5.2.1");
		    foreach $list (@list)
		    {
      			$_ =~ s/$list/httpclient5-5.3.1/;
		    }

		    my @list = ("httpcore-4.4.10", "httpcore-4.4.11", "httpcore-4.4.13", "httpcore-4.4.14", "httpcore5-5.2");
		    foreach $list (@list)
		    {
        		$_ =~ s/$list/httpcore5-5.2.4/;
		    }

		    $Array_BATCHFILE[$z++] = $_;
		}
		
                close( BATCHFILE );
                open( BATCHFILE, ">$PIN_HOME/apps/cmt/pin_cmt$extension" );
		print BATCHFILE @Array_BATCHFILE;
		print BATCHFILE "\n";
		close( BATCHFILE );
	
	
		chmod 0755, "$PIN_HOME/apps/cmt/pin_cmt$extension";

}

#####################################################
# Configure pin_cmt java class with updated classpath
#####################################################
sub config_cmt_upg_config_files {

   $Pref = "";
   $Sep = ":";
   $wild = "\$1 \$2 \$3 \$4 \$5 \$6 \$7 \$8 \$9";
   $extension = "";

   # Create the script to launch the application
        $Cmd = &FixSlashes( $Pref."$JAVA_HOME/bin/java -Dfile.encoding=utf-8 -cp \"$PIN_HOME/apps/cmt/cmt.jar".$Sep
                   ."$ENV{ORACLE_HOME}/jdbc/lib/ojdbc8.jar".$Sep
                   ."$ENV{ORACLE_HOME}/lib/ojdbc8.jar".$Sep
                   ."$PIN_HOME/jars/pcm.jar".$Sep
                   ."$PIN_HOME/jars/pcmext.jar".$Sep
                   ."$PIN_HOME/jars/oraclepki.jar".$Sep
                   ."$PIN_HOME/jars/osdt_cert.jar".$Sep
                   ."$PIN_HOME/jars/osdt_core.jar".$Sep
                   ."$PIN_HOME/apps/cmt\" com.portal.cmt.Cmt $wild" );
               open( BATCHFILE, "$PIN_HOME/apps/cmt/pin_cmt$extension" );

                @Array_BATCHFILE = <BATCHFILE>;
                $z = 0;
                seek( BATCHFILE, 0, 0 );
                while ( <BATCHFILE> ){
                    $_ =~ s/__REPLACE__JAVA__APP__/$Cmd/;

                    $Array_BATCHFILE[$z++] = $_;
                }

                close( BATCHFILE );
                open( BATCHFILE, ">$PIN_HOME/apps/cmt/pin_cmt$extension" );
                print BATCHFILE @Array_BATCHFILE;
                print BATCHFILE "\n";
                close( BATCHFILE );


                chmod 0755, "$PIN_HOME/apps/cmt/pin_cmt$extension";
}


#########################################
# Configure database for the Common Migration Tool
#########################################
sub configure_cmt_database {


  #
  # Skip the database updates if not oracle was selected,
  # since  Common migration tool is supported only in oracle.
  #
  if ( $MAIN_DM{'db'}->{'vendor'} !~ /oracle/i ) {
  	return 0;
  }

  require "./pin_".$MAIN_DM{'db'}->{'vendor'}."_functions.pl";
  require "./pin_cmp_dm_db.pl";
  local ( $TMP ) = $SKIP_INIT_OBJECTS;
  local ( %CM ) = %MAIN_CM;
  local ( %DM ) = %MAIN_DM;
  
  &PreModularConfigureDatabase( %CM, %DM );

  #########################################
  # Creating the tables for the Common Migration Tool
  #########################################
  $SKIP_INIT_OBJECTS = "YES";
  $USE_SPECIAL_DD_FILE = "YES";
  
  if ( VerifyPresenceOfTable( "BATCH_CMT_T", %{$DM{"db"}} ) == 0 ){
	  $SPECIAL_DD_FILE = "$DD{'location'}/dd_objects_cmt.source";
	  $SPECIAL_DD_DROP_FILE = "$DD{'location'}/drop_tables_cmt_".$MAIN_DM{'db'}->{'vendor'}.".source";

	  if ( $SETUP_DROP_ALL_TABLES =~ m/^YES$/i ) {
		&DropTables( %{MAIN_DM->{"db"}} );
	  }

	  &pin_pre_modular( %{$DM{"db"}} );
	  &pin_init( %DM );
	  &pin_post_modular( %DM );
  }
  
  $USE_SPECIAL_DD_FILE = "NO";
  $SKIP_INIT_OBJECTS = $TMP;

  &PostModularConfigureDatabase( %CM, %DM );

  #
  # Create table :
  #
  if(-e "$DD{'location'}/cmt_clean_old_balances_$MAIN_DM{'db'}->{'vendor'}.sql"){
	  &ExecuteSQL_Statement_From_File( "$DD{'location'}/cmt_clean_old_balances_$MAIN_DM{'db'}->{'vendor'}.sql", 
									   TRUE, 
									   TRUE, 
									   %{$DM{'db'}} );
	}

  #
  # Create Procedure :
  #
  if(-e "$DD{'location'}/update_realtime_batch_cntr_$MAIN_DM{'db'}->{'vendor'}.sql"){
	  &ExecuteSQL_Statement_From_File( "$DD{'location'}/update_realtime_batch_cntr_$MAIN_DM{'db'}->{'vendor'}.sql", 
									   TRUE, 
									   TRUE, 
									   %{$DM{'db'}} );
	}

  if(-e "$DD{'location'}/update_due_amount_$MAIN_DM{'db'}->{'vendor'}.sql"){
	  &ExecuteSQL_Statement_From_File( "$DD{'location'}/update_due_amount_$MAIN_DM{'db'}->{'vendor'}.sql", 
									   TRUE, 
									   TRUE, 
									   %{$DM{'db'}} );
	}





  $SPECIAL_DD_CREATE_INDEXES_FILE = "$DD{'location'}/create_cmt_reference_index_".$MAIN_DM{'db'}->{'vendor'}.".source";
  &ExecuteSQL_Statement_From_File( $SPECIAL_DD_CREATE_INDEXES_FILE, TRUE, TRUE, %{$DM{'db'}} );
  
  #
  # Create stored procedures for CMT: :
  #
  if ( $DM{'delimiter'} =~ /^$/ )
  {
	&ExecuteSQL_Statement_From_File(
	"$DD{'location'}/create_cmt_procedure_$MAIN_DM{'db'}->{'vendor'}.sql", 
				TRUE, 
				TRUE, 
				%{$DM{'db'}} );
  }
  else
  {
  	&ExecuteSQL_Statement_From_File_with_delimiter(
	"$DD{'location'}/create_cmt_procedure_$MAIN_DM{'db'}->{'vendor'}.sql",
				TRUE,
				TRUE, 
				%{$DM{'db'}} );
  }
}
1;

