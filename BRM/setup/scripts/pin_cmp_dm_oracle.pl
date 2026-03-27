#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_dm_oracle.pl /cgbubrm_mainbrm.portalbase/5 2018/03/30 02:42:03 mkothari Exp $
# 
# Copyright (c) 2000, 2023, Oracle and/or its affiliates.
#
#    This material is the confidential property of Oracle Corporation 
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the DM_ORACLE Component
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

require "./pin_cmp_virtual_col.pl";

#######
#
# Configuring DM_ORACLE files
#
#######
sub configure_dm_oracle_config_files {
  %DM = %DM_ORACLE;
  local ( $ReadIn );
  &ReadIn_PinCnf( "pin_cnf_dm.pl" );
  &ReadIn_PinCnf( "pin_cnf_connect.pl" );
  
  # create sample pin.conf with default CM entries in the setup/scripts directory.
  &AddArrays( \%CONNECT_PERL_ENTRIES, \%CONNECT_PINCONF_ENTRIES );
  &Configure_PinCnf( "$PIN_HOME/setup/scripts/$PINCONF",
                     $CONNECT_PINCONF_HEADER,
                     %CONNECT_PINCONF_ENTRIES );

  $DM_ORACLE_PINCONF_HEADER = $DM_PINCONF_HEADER;
  &ReadIn_PinCnf( "pin_cnf_dm_db.pl" );
  &AddArrays( \%DM_ORACLE_DB_PINCONF_ENTRIES, \%DM_DB_PINCONF_ENTRIES );
  &AddArrays( \%DM_PINCONF_ENTRIES, \%DM_DB_PINCONF_ENTRIES );

  &Configure_PinCnf( $DM_ORACLE{'location'}."/".$PINCONF, 
                     $DM_ORACLE_PINCONF_HEADER, 
                     %DM_DB_PINCONF_ENTRIES ); 
                     
  #
  # update pin_ctl.conf
  #
 
    &ReplacePinCtlConfEntries( "${PIN_HOME}/bin/pin_ctl.conf", 
			"__DM_ORACLE_PORT__",
			"$DM_ORACLE{'port'}" );

    # Adding a demarcation of  "#======="  before the addition of DMO key on pin.conf
    # This  will separate DMO key from other entries
    my $DMOfilename = "$PIN_HOME/sys/dm_oracle/pin.conf";
    my $keyWord = "- dm stmt_cache_entries";
    &AddCommentPinConfEntry($DMOfilename,$keyWord,%DM_DB_ADD_DEMARCATION_ENTRIES);

    if(defined($ENV{PRIMARY_SCHEMA_USERNAME}) && defined($ENV{DOCKER})) {
	local ( %DB ) = %{$DM_ORACLE{"db"}};
	$DB{'user'} = $ENV{PRIMARY_SCHEMA_USERNAME};
	$DB{'password'} = `cat /etc/secret_primary/.oms_schema_password`;
	local( $tmpFile ) = $PIN_TEMP_DIR."/tmp.out";
	my @j = ();
	$ENV{PRIMARY_SCHEMA_USERNAME_TEMP} = 1;
	print " Configuring cryptkey_t for secondary schema...\n";
	my $max = 0;
	my $max_value = 60;
	if(defined($ENV{MULTISCHEMA_MAX_INIT_TIME})) {
		$max_value = $ENV{MULTISCHEMA_MAX_INIT_TIME};
	}
	
	while($max < $max_value) {
		if ((VerifyPresenceOfTable("CRYPTKEY_T", %DB) != 0) && (getCountFromTable("CRYPTKEY_T", %DB) > 0)) { 
			last;
		} else {
			print "$max Waiting for $ENV{PRIMARY_SCHEMA_USERNAME}.cryptkey_t ...\n";
			$max++;
		}
	}
	&ExecuteSQL_Statement("select CRYPT_KEY from cryptkey_t where CRYPT_KEY_ID IN (select max(CRYPT_KEY_ID) from cryptkey_t);", TRUE, TRUE, %DB );
	open( TMPFILE, "<$tmpFile " );
	my $ReadString ='';
	while( $ReadString = <TMPFILE> ) {
	    next if($ReadString =~ /CRYPT_KEY/ || $ReadString =~ /---/ || $ReadString =~ /Executing/);
	    $ReadString =~ s/^\s+//;
	    $ReadString =~ s/\s+$//;
	    push(@j,$ReadString) if($ReadString ne '');
	}
	@j = join("",@j);
	print "\n@j\n";
	close( TMPFILE );
	my $ozt = "- crypt aes| /oms/lib/libpin_crypt_aes4dm.so \"@j\"";
	open( PINCONF, ">>/oms/sys/dm_oracle/pin.conf " );
        print PINCONF "\n\n";
        print PINCONF $ozt;
	close( PINCONF );
	$ENV{PRIMARY_SCHEMA_USERNAME_TEMP} = 0;
	createWalletForSecondary();
    } elsif ($DM{'db_num'} ne "0.0.0.1" && ( !defined($ENV{DOCKER}))) {
	createWalletForSecondary();
	updateCryptKeyFromPrimary();
    } elsif ($DM{'db_num'} eq "0.0.0.1") {
	system(" $PIN_HOME/bin/pin_crypt_app -useZT -genkey -update_dm_conf ");
    }

    
#
# Update create_aq_queue.conf with the user input for tablespace and retention time
#
  local( $ConfFile ) = &FixSlashes( "$PIN_HOME/apps/pin_publish_aq/create_aq_queue.conf" );
  open ( CONFFILE, "+< $ConfFile" ) || die( "Can't open $ConfFile" );

  seek( CONFFILE, 0, 0 );
  $out = '';
  while ( <CONFFILE> )
  {
	s /__TABLESPACE_NAME__/$MAIN_DB{'queuing_tablespace'}/ ;
	s /__RETENTION_TIME__/$MAIN_DB{retention_time}/ ;
	$out .= $_;
  }
  seek( CONFFILE, 0, 0 );
  print CONFFILE $out;
  truncate( CONFFILE, tell(CONFFILE ) );
  close( CONFFILE );
}


#######
#
# Configuring database for DM_ORACLE
#
#######
sub configure_dm_oracle_database {
  require "./pin_oracle_functions.pl";
  require "./pin_cmp_dm_db.pl";

  %DM = %DM_ORACLE;
  local ( %DB ) = %{$DM_ORACLE{"db"}};

  # Confirm that we can login to the database as the Portal user
  &VerifyLogin( "portal", %DB );

  $DM_ORACLE{'db'}->{'vendor'} = "oracle";

  if ( &VerifyPresenceOfData( %{$DM_ORACLE{"db"}} ) == -1 )  {
    if ( $SETUP_DROP_ALL_TABLES =~ m/^YES$/i ) {
	&DropTables( %{$DM_ORACLE{"db"}} );
        &DropAllTables( %{$DM_ORACLE{"db"}} );

	# Drop "PIN_PARTITION" package 
	&ExecuteSQL_Statement("drop package PIN_PARTITION;", TRUE, TRUE, %DB );

	# Drop "PIN_VIRTUAL_COLUMNS" package 
	&ExecuteSQL_Statement("drop package PIN_VIRTUAL_COLUMNS;", TRUE, TRUE, %DB );
    } 
  }

  #
  # Make sure everything is writeable
  #
  &ReplacePinConfEntry( $DM_ORACLE{'location'}."/".$PINCONF, 
			"dd_write_enable_fields",
			"- dm dd_write_enable_fields 1" );
  &ReplacePinConfEntry( $DM_ORACLE{'location'}."/".$PINCONF, 
			"dd_write_enable_objects",
			"- dm dd_write_enable_objects 1" );
  &ReplacePinConfEntry( $DM_ORACLE{'location'}."/".$PINCONF, 
			"dd_write_enable_portal_objects",
			"- dm dd_write_enable_portal_objects 1" );
  &ReplacePinConfEntry( $DM_ORACLE{'location'}."/".$PINCONF, 
			"dd_mark_as_portal",
			"- dm dd_mark_as_portal 1" );
  &ReplacePinConfEntry( $DM_ORACLE{'location'}."/".$PINCONF, 
			"stmt_cache_entries",
			"- dm stmt_cache_entries 0" );

  &pin_pre_init( %{$DM_ORACLE{"db"}} );
  # Add Virtual Columns to database
  &AddVirtualColumns( %{$DM_ORACLE{"db"}} );
  &ExecutePLB_file ("$DM_ORACLE{'location'}/data/create_pkg_pin_sequence_oracle.plb",
		    "Portal PIN Sequence",
		    %DM_ORACLE );
  &pin_init( %DM_ORACLE );
  &pin_post_init( %DM_ORACLE );
  &pin_create_event_essential( %DM_ORACLE );

  #
  # Make sure everything is back to normal
  #
  &ReplacePinConfEntry( $DM_ORACLE{'location'}."/".$PINCONF, 
			"dd_write_enable_fields",
			"- dm dd_write_enable_fields $DM_ORACLE{'enable_write_fields'}" );
  &ReplacePinConfEntry( $DM_ORACLE{'location'}."/".$PINCONF, 
			"dd_write_enable_objects",
			"- dm dd_write_enable_objects $DM_ORACLE{'enable_write_objects'}" );
  &ReplacePinConfEntry( $DM_ORACLE{'location'}."/".$PINCONF, 
			"dd_write_enable_portal_objects",
			"- dm dd_write_enable_portal_objects $DM_ORACLE{'enable_write_portal_objects'}" );
  &CommentOutPinConfEntry( $DM_ORACLE{'location'}."/".$PINCONF, 
			"dd_mark_as_portal" );
    
  #
  # Perform the database updates needed for RatedEventLoader.
  #
  if ( -f "$DM{'location'}/data/create_event_v.source" )
  {
	&ExecuteSQL_Statement_From_File( "$DM{'location'}/data/create_event_v.source", 
		TRUE, 
		TRUE, 
		%{$DM{'db'}} );
  }

  # Add Partitions to database
  &AddPartitions( %{$DM_ORACLE{"db"}} );

  $PIN_UPG_COMMON_FILE="$PIN_HOME/sys/dd/data/pin_upg_common.source";
  if ( -f "$PIN_UPG_COMMON_FILE" ) {
        print "Loading pin_upg_common.source\n";
        &ExecuteSQL_Statement_From_File( $PIN_UPG_COMMON_FILE, TRUE, TRUE, %DB );
  }

  my $psv = "$ENV{BRM_VERSION}";
  my $curVersion = substr($psv, 5, (rindex($psv, "."))-7);
  my $curStream = substr($psv, 0, index ($psv, '.'));

  # Creating/Updating BRM_PS_T Table in DB with Patchset Details.
  if ( $SETUP_INIT_DB =~ /^YES$/i )  {
    if (VerifyPresenceOfTable("BRM_PS_T", %{ $DM{"db"} }) != 0)  {
	my $dml_sql = "DELETE FROM BRM_PS_T;";
        &ExecuteSQL_Statement($dml_sql,$statusflag,$statusflag, %{$DM{"db"}});
        &ExecuteSQL_Statement("COMMIT;",$statusflag,$statusflag, %{$DM{"db"}});
    }
    else {
        &ExecuteSQL_Statement("CREATE TABLE BRM_PS_T ( STREAM NUMBER, PATCH_NUMBER NUMBER);",$statusflag,$statusflag, %{$DM{"db"}});
    }
    my $dml_sql = "INSERT INTO BRM_PS_T (STREAM,PATCH_NUMBER) VALUES (" . $curStream . "," . $curVersion . ") ;"; 
    &ExecuteSQL_Statement($dml_sql,$statusflag,$statusflag, %{$DM{"db"}});
    &ExecuteSQL_Statement("COMMIT;",$statusflag,$statusflag, %{$DM{"db"}});
  }
&configure_dm_publish_aq_database()
}


#######
#
# Post configuration for DM_ORACLE
#
#######
sub configure_dm_oracle_post_configure
{
    if ( ( $SETUP_INIT_DB =~ /^YES$/i ) ) {
	if ( $ServiceName{ 'cm' } !~ /^$/ )
	{
		&Stop( $ServiceName{ 'cm' } );
		sleep( 6 );
	}
	&Stop ( $ServiceName{ 'dm_oracle' } );
    }
    #
    # Reset 'dm stmt_cache_entries' to the original value, then restart dm_oracle.
    #
    &ReplacePinConfEntry( $DM_ORACLE{'location'}."/".$PINCONF,
		"stmt_cache_entries",
		"- dm stmt_cache_entries $DM_ORACLE{'stmt_cache_entries'}" );
    if ( ( $SETUP_INIT_DB =~ /^YES$/i ) ) {
	&Start( $ServiceName{ 'dm_oracle' } );
	if ( $ServiceName{ 'cm' } !~ /^$/ )
	{
		&Start( $ServiceName{ 'cm' } );
		sleep( 10 );
	}
    }
}


#######
#
# This function verifies if PinPartition package is present in the database.
# If not, then run partition_utils.sql to create PIN_PARTITION package.
# After that, run partition_utils with -f option,
# which will check if the default partitions exist, and add them if necessary.
#
#######
sub AddPartitions {
  	local( %DB ) = @_;
  	local( $tmpFile ) = $PIN_TEMP_DIR."/tmp.out";
  	local( $ReadString );

	#
	# Updating the configuration for partition_utils in partition_utils.values.
	#
	&ReplacePinConfEntry( $PARTITION_UTILS{'location'}."/partition_utils.values",
		"Database alias",
		"\$MAIN_DB{'alias'} = \"".$DB{alias}."\";");

	&ReplacePinConfEntry( $PARTITION_UTILS{'location'}."/partition_utils.values",
		"Database user",
		"\$MAIN_DB{'user'} = \"".$DB{user}."\";");

	#&ReplacePinConfEntry( $PARTITION_UTILS{'location'}."/partition_utils.values",
	#	"Database password",
	#	"\$MAIN_DB{'password'} = \"".$DB{password}."\";");

  	&ExecuteSQL_Statement("select object_name from user_objects where object_type= 'PACKAGE BODY' and status = 'VALID' and object_name = 'PIN_PARTITION';", TRUE, TRUE, %DB );

  	open( TMPFILE, "<$tmpFile " );
  	while( $ReadString = <TMPFILE> ) {
    		if ( $ReadString =~ m/no\s+rows\s+selected/ ) {
      			&ExecutePLB_file("../../apps/partition_utils/sql_utils/oracle/partition_utils.plb",
					  "pin_partition", %DM_ORACLE );
    		}
  	}
	close( TMPFILE );


  	if ( $SETUP_CREATE_PARTITIONS =~ m/^YES$/i ) {

		#
		# Getting current system time in seconds.
		#
		$nsec = time(); 
		#
		# Adding 2 days(172800 secs) to current time
		#
		$nsec = $nsec + 172800;
		($sec, $min, $hour, $day, $mon, $year, $weekday, $yearday, $isdst) = localtime($nsec);
		$mon = $mon + 1;
		$year = 1900 + $year;
		$startdate = sprintf("%02d%02d%d", $mon, $day, $year);

		# Use ExecuteShell so that error will be handled by partition_utils and not directed to tmp.out
        	$Cmd = &FixSlashes( '/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl '.$PIN_HOME.'/bin/partition_utils -o add -t realtime -s '.$startdate.' -u month -w 1 -q 12 -f' );
		&ExecuteShell( TRUE, $Cmd );
	}

}

# Really this procedure just loads the package to the db and initializes the Infranet.properties file
sub AddVirtualColumns {
  	local( %DB ) = @_;
  	local( $tmpFile ) = $PIN_TEMP_DIR."/tmp.out";
  	local( $ReadString );
	my($i) = 0;
	
	&Configure_VirtCol_Cnf;

	#
	#  Load the pin_virtual_columns package provided it is not already loaded
	#
  	&ExecuteSQL_Statement("select object_name from user_objects where object_type= 'PACKAGE BODY' and status = 'VALID' and object_name = 'PIN_VIRTUAL_COLUMNS';", TRUE, TRUE, %DB );

  	open( TMPFILE, "<$tmpFile " );
  	while( $ReadString = <TMPFILE> ) {
    		if ( $ReadString =~ m/no\s+rows\s+selected/ ) {
      			&ExecutePLB_file("../../apps/pin_virtual_columns/oracle/create_pkg_pin_virtual_columns.plb",
					  "pin_virtual_columns", %DM_ORACLE );
    		}
  	}
	close( TMPFILE );
}

sub configure_dm_publish_aq_database {
  local( $Cmd );
  local( $Dir );
  local ( %DB ) = %{$DM_ORACLE{"db"}};
  my($i) = 0;
  my $crm_sync_aq_name ="AQ_QUEUE";

   #
   # Run pin_publish_aq script to create the default queue and AQ_QUEUE
   #

   $Dir = &FixSlashes( "$PIN_HOME/apps/pin_publish_aq/pin_publish_aq_oracle.pl");

   $Cmd = "$Dir create -l /\@$MAIN_DB{'alias'}";

   &Output( fpLogFile, $IDS_IFW_SYNC_QUEUE_CREATION );
   &Output( STDOUT, $IDS_IFW_SYNC_QUEUE_CREATION );
   if(defined($ENV{PRIMARY_SCHEMA_USERNAME}) && defined($ENV{DOCKER})) 
   {
        while($i < $ENV{MULTISCHEMA_MAX_INIT_TIME}) {
                if ((VerifyPresenceOfType("pin_event_ty",$ENV{PRIMARY_SCHEMA_USERNAME}, %DB) != 0)) {
                        last;
                } else {
                        print "$i Waiting for pin_event_ty in primary ...\n";
                        sleep(10);
                        $i++;
                }
        }
        if ($i == $ENV{MULTISCHEMA_MAX_INIT_TIME}) {
            print"\n Secondary Schema installation not successful, because primary Schema Not initialized\n";
            exit(1);
        }
   }

   $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd, "" );
   if( $Cmd != 0 ) {
      &Output( fpLogFile, $IDS_IFW_SYNC_QUEUE_CREATION_FAILED );
      &Output( STDOUT,$IDS_IFW_SYNC_QUEUE_CREATION_FAILED );
      exit -1;
   } else {
      &Output( fpLogFile, $IDS_IFW_SYNC_QUEUE_CREATION_SUCCESS );
      &Output( STDOUT, $IDS_IFW_SYNC_QUEUE_CREATION_SUCCESS );
   }

   if(defined($ENV{CRM_SYNC_AQ_NAME})) {
        $crm_sync_aq_name = $ENV{CRM_SYNC_AQ_NAME};
   }

   $Cmd = "$Dir create -q $crm_sync_aq_name -t AQ_SYNC -l /\@$MAIN_DB{'alias'}";

   &Output( fpLogFile, $IDS_AQ_SYNC_QUEUE_CREATION );
   &Output( STDOUT, $IDS_AQ_SYNC_QUEUE_CREATION );

   $Cmd = &ExecuteShell_Piped( "$PIN_TEMP_DIR/tmp.out", TRUE, $Cmd , "" );
   if( $Cmd != 0 ) {
      &Output( fpLogFile, $IDS_AQ_SYNC_QUEUE_CREATION_FAILED );
      &Output( STDOUT,$IDS_AQ_SYNC_QUEUE_CREATION_FAILED );
      exit -1;
   } else {
      &Output( fpLogFile, $IDS_AQ_SYNC_QUEUE_CREATION_SUCCESS );
      &Output( STDOUT, $IDS_AQ_SYNC_QUEUE_CREATION_SUCCESS );
   }
   unlink( "$PIN_TEMP_DIR/tmp.out" );

}

sub updateCryptKeyFromPrimary
{
        local ( %DB ) = %{$DM_ORACLE{"db"}};
        local( $tmpFile ) = $PIN_TEMP_DIR."/tmp.out";
	local $dm_file = $PIN_HOME."/sys/dm_oracle/pin.conf";
	local $dm_file_bkp = $PIN_HOME."/sys/dm_oracle/pin.conf_temp";
        &ExecuteSQL_Statement("select CRYPT_KEY from cryptkey_t where CRYPT_KEY_ID IN (select max(CRYPT_KEY_ID) from cryptkey_t);", TRUE, TRUE, %DB );
        open( TMPFILE, "<$tmpFile " );
        my $ReadString ='';
        while( $ReadString = <TMPFILE> ) {
            next if($ReadString =~ /CRYPT_KEY/ || $ReadString =~ /---/ || $ReadString =~ /Executing/);
            $ReadString =~ s/^\s+//;
            $ReadString =~ s/\s+$//;
            push(@j,$ReadString) if($ReadString ne '');
        }
        @j = join("",@j);
        print "\n@j\n";
        close( TMPFILE );
        open( DM_BKP, '>',$dm_file_bkp ) or die $!;
        open( DM_ORG, '<', $dm_file  ) or die $!;
        while(<DM_ORG>) {
                my $line=$_;
                if ($line =~ /^- crypt aes/) {
                        $line="#$line";
                }
                print DM_BKP $line;
        }
        close (DM_BKP);
        close (DM_ORG);
        open( DM_BKP, ">>$dm_file_bkp");
        print DM_BKP '- crypt aes| ${PIN_HOME}/lib/${LIBRARYPREFIX}pin_crypt_aes4dm${LIBRARYEXTENSION} "'.@j[0].'"' ;
        print DM_BKP "\n";
        system("cp $dm_file_bkp $dm_file");
}

sub createWalletForSecondary
{
        local ( %DB ) = %{$DM_ORACLE{"db"}};
        local( $tmpFile ) = $PIN_TEMP_DIR."/tmp.out";
	my $primaryUser=$PRIMARY_DB_USER;
	if(defined($ENV{PRIMARY_SCHEMA_USERNAME}) && defined($ENV{DOCKER})) {
		$primaryUser=$ENV{PRIMARY_SCHEMA_USERNAME};
	}elsif ($DM{'db_num'} ne "0.0.0.1" && ( !defined($ENV{DOCKER}))) {
		$primaryUser=$PRIMARY_DB_USER;
	}else{
		print "sub createWalletForSecondary is for secondary only\n";
		return;
	}
	my $query="create or replace view wallet_file_storage_t as (select * from ".$primaryUser.".wallet_file_storage_t);";
        &ExecuteSQL_Statement($query, TRUE, TRUE, %DB );

}

1;
