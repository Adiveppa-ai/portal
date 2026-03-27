#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#############################################################################
#
# @(#)$Id: pin_amt_install.pl /portalbase/1 2022/06/16 02:42:06 mkothari Exp $;
#
# Copyright (c) 1999, 2023, Oracle and/or its affiliates.
#
#       This material is the confidential property of Oracle Corporation
#       or its licensors and may be used, reproduced, stored or transmitted
#       only in accordance with a valid Oracle license or sublicense agreement.
#############################################################################

  #---------------------------------------------------------------------#
  #  This script does the Multi-Schema initialization and synchronization    #
  #  between two (or more) physically separate Infranet instances.      #
  #---------------------------------------------------------------------#

use Cwd;
use aes;
use Getopt::Std;
require "./pin_functions.pl";
require "../pin_setup.values";
require "./pin_tables.values";
require "./pin_multidb.conf";
require "./pin_multidb_utils";

my $cn = 0;
if(defined($ENV{'DOCKER'}) && $ENV{'DOCKER'} eq '1') {
	require "./pin_cmp_dm_db.pl";
	$cn = 1;
        if(not defined($PIN_MD_PRIMARY_PASSWD)) {
                $PIN_MD_PRIMARY_PASSWD = `cat /etc/secret/.oms_schema_password`;
        }
        for $i ($PIN_MD_SECONDARY_START_INST..$PIN_MD_SECONDARY_END_INST) {
                if(not defined($PIN_MD_SECONDARY_PASSWD[$i])) {
                        my $sn = $i + 2;
                        if(-e "/etc/secret_secondary/$sn") {  $PIN_MD_SECONDARY_PASSWD[$i] = `cat /etc/secret_secondary/$sn`; }
                }
                local ( %DB ) = %{$DM_ORACLE{"db"}};
                $DB{'user'} = $PIN_MD_SECONDARY_OWNER[$i];
                $DB{'password'} = $PIN_MD_SECONDARY_PASSWD[$i];

                require "./pin_oracle_functions.pl";
                my $max = 0;
                my $max_value = 60;
                if(defined($ENV{MULTISCHEMA_MAX_INIT_TIME})) {
                        $max_value = $ENV{MULTISCHEMA_MAX_INIT_TIME};
                }

                $ENV{PRIMARY_SCHEMA_USERNAME_TEMP}=1;
                while($max < $max_value) {
                        if (VerifyPresenceOfTable("REL_STATUS_T", %DB) == -1) {
                                print "Secondary schema $PIN_MD_SECONDARY_OWNER[$i] configured .. \n";
                                last;
                        } else {
                                print "$max Waiting for $PIN_MD_SECONDARY_OWNER[$i] to finish ...\n";
                                $max++;
                        }
                }
        }
	$ENV{PRIMARY_SCHEMA_USERNAME_TEMP}=0;
}

our $logging = "pin_multidb.log";
if(defined($ENV{BRM_LOG_STDOUT}) && $ENV{BRM_LOG_STDOUT} eq "TRUE") {
        $logging = "&STDOUT";
}

$DEBUG = 0;
$ME = $0;
$STEP = 0;
$REPLICATE_UNIQUENESS = 0;
$ARGS = "";
$poid_db_no = 0;


getopts('ifud:s') || &Usage();
  close (STDERR);				# hack to grab STDERR
  open (LOGFILE, ">>".$logging) ||
		die "$ME:  Could not open logfile\n";
  $old_fh = select(LOGFILE); $|=1; select($old_fh);

  for $refresh_group (@PIN_MD_REFRESH_GROUPS) {
    if ($refresh_group =~ /UNIQUENESS/i) {
      $REPLICATE_UNIQUENESS = 1;
    }
  }
  if ($opt_i) { 			# initialize
    #-------------------------------------------------------------
    #  Stopping Primary CM and DMs
    #-------------------------------------------------------------
        if( ! $opt_s ) {
		&Prompt_Msg_i1();
	}

STEP0:  if($STEP > 0) {
                goto STEP1;
        }
	&Stop_Primary_DM_CM() if($cn ==0);
	
	&Fix_Local_PinConf() if($cn ==0);
        if( ! $opt_s ) {
		&Prompt_Msg_i();
	}

        $STEP = 1;

    #-------------------------------------------------------------
    #  Create and initialize objects needed in the primary database
    #  to support a Infranet Multi-Schema configuration.
    #-------------------------------------------------------------
STEP1:  if($STEP > 2) {
                goto STEP3;
        }
	&Initialize_Primary_for_MultiDB();
        if( ! $opt_s ) {
        	&Prompt_Msg_i();
	}
        $STEP = 3;
	
    #-------------------------------------------------------------
    #  Starting Primary CM and DMs
    #-------------------------------------------------------------
STEP3:  if($STEP > 3) {
                goto STEP4;
        }
        &Start_Primary_DM_CM() if($cn == 0);
        if( ! $opt_s ) {
        	&Prompt_Msg_i();
	}
        $STEP = 4;
    #-------------------------------------------------------------
    #  Load the config distribution at the primary db
    #-------------------------------------------------------------
STEP4:  if($STEP > 4) {
                goto STEP5;
        }
        &Fix_Apps_MultiDB_PinConf() if($cn == 0);
	&Load_Config_Distribution() if($cn == 0);
        if( ! $opt_s ) {
        	&Prompt_Msg_i();
	}
        $STEP = 5;

    #-------------------------------------------------------------
    #  Update /uniqueness at primary
    #-------------------------------------------------------------
STEP5:  if($STEP > 5) {
                goto STEP6;
        }
	&Update_Primary_Uniqueness();
        if( ! $opt_s ) {
		&Prompt_Msg_i();
	}
	$STEP = 6;

    #-------------------------------------------------------------
    #  Stopping Primary CM and DMs.  (Ideally we should be
    #  shutting down the secondary DMs also (if any).  But..)
    #-------------------------------------------------------------
STEP6:  if($STEP > 6) {
                goto STEP7;
        }
	&Stop_Primary_DM_CM() if($cn == 0);
        if( ! $opt_s ) {
		&Prompt_Msg_i();
	}
	$STEP = 7;


    #-------------------------------------------------------------
    #  Create and initialize objects needes in the secondary
    #  database(s)
    #-------------------------------------------------------------
STEP7:  if($STEP > 7) {
                goto STEP8;
        }
	&Initialize_Secondary_for_MultiDB();
        if( ! $opt_s ) {
        	&Prompt_Msg_i();
	}
        $STEP = 8;

    #-------------------------------------------------------------
    # In case of SQL server start the replication agents
    # and update the db nrs in the secondary db
    #-------------------------------------------------------------
STEP8:	if ($PIN_MD_SQL_PLATFORM =~ /Oracle/i) {
		&Fix_DM_PinConf() if($cn == 0);
		if( ! $opt_s ) {
                	&Prompt_Msg_i2();
        	}
	}

	&Fix_CM_PinConf() if($cn == 0);

	&Fix_Multi_Confirm_Config_PinConf() if($cn == 0);
        if( ! $opt_s ) {
		&Prompt_Msg_i();
	}
	if($cn == 0) {
		&Amt_Sequence();
	} else {
		`java -cp $ENV{ORACLE_HOME}/lib/ojdbc8.jar:$PIN_HOME/jars/pin_reset_seq.jar:$PIN_HOME/jars/pcm.jar:$PIN_HOME/jars/oraclepki.jar:$PIN_HOME/jars/osdt_core.jar:$PIN_HOME/jars/osdt_cert.jar PinResetSeq /oms/pin_confs2/pin_reset_seq.properties`;
	}
	&Print_Information_Message();

  if(-e "$PIN_HOME/setup/scripts/create_boc_unified_views.pl" ) {
	  print " Calling create_boc_unified_views.pl \n" ;
	  system("perl create_boc_unified_views.pl");
  }
  } elsif ($opt_f) {			# finalize
	
    #-------------------------------------------------------------
    #  Update /uniqueness at primary again
    #-------------------------------------------------------------
        if( ! $opt_s ) {
		&Prompt_Msg_f1();
	}
	&Update_Primary_Uniqueness_Again() if($cn == 0);
	
        if( ! $opt_s ) {
		&Prompt_Msg_f();	
	}

	#-------------------------------------------
	# Only if uniqueness replication is enabled
	#-------------------------------------------
	if ($REPLICATE_UNIQUENESS == 1 ) {

            #------------------------------------------------
            # sleep 5 seconds to complete load_pin_uniqueness 
            #------------------------------------------------
            sleep 5;

            #---------------------------------------
            #  Stopping Primary CM and DMs
            #---------------------------------------
            &Stop_Primary_DM_CM() if($cn == 0);
            #---------------------------------------
            #  Starting Primary CM and DMs
            #----------------------------------------
            &Start_Primary_DM_CM() if($cn == 0);
	}	
    #-------------------------------------------------------------
    #  Start miscellaneuos programs
    #-------------------------------------------------------------
	&Start_Programs();
        if( ! $opt_s ) {
		&Prompt_Msg_f2();
	}

  } elsif ($opt_u) {
	&Update_Primary_Uniqueness;
  } else {
	&Usage();
  }

  close (LOGFILE);

exit (0);

#---------------------------------------------------------------------#
#  This subroutine creates and initializes the objects in the primary #
#  database to support a Infranet Multi-Schema configuration               #
#---------------------------------------------------------------------#
sub Initialize_Primary_for_MultiDB {
  
  my ($username, $passwd, $dbname, $sqlhost);

  &printout ("$ME: Initializing primary database.\n");
  print "$ME: Initializing primary database.\n";

  $username = $PIN_MD_PRIMARY_OWNER;
  $passwd   = $PIN_MD_PRIMARY_PASSWD;
  $dbname   = $PIN_MD_PRIMARY_DBNAME;	  
  $sqlhost  = $PIN_MD_PRIMARY_SQLHOST;

  if ($PIN_MD_SQL_PLATFORM =~ /Oracle/i) {
STEP1_O:
        if($STEP > 1) {
                goto STEP2_O;
        }

	$file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_PRIMARY_CREATE_INDEXES";

        &printout ("$ME: Executing $file\n");
        &Parse_and_Execute ($file, 1, $username, $passwd, $dbname, $sqlhost);

        if( ! $opt_s ) {
        	&Prompt_Msg_i();
	}
        $STEP = 2;

STEP2_O:

	$file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_PRIMARY_PRE_INIT_SCRIPT";

	&printout ("$ME: Executing $file\n");
	&Parse_and_Execute ($file, 1, $username, $passwd, $dbname, $sqlhost);

	if($REPLICATE_UNIQUENESS =~ 1) {
	  $file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_PRIMARY_INIT_UNIQ_SCRIPT";
	  &printout ("$ME: Executing $file\n");
	  &Parse_and_Execute ($file, 1, $username, $passwd, $dbname, $sqlhost);
	}

	$file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_PRIMARY_INIT_SCRIPT";

	&printout ("$ME: Executing $file\n");
	&Parse_and_Execute ($file, 1, $username, $passwd, $dbname, $sqlhost);
  }
  else {
	&printout ("$ME: You must specify a valid database. \n");
	print "$ME: You must specify a valid database. \n";
	exit(1);
  }
}

#---------------------------------------------------------------------#
#  This subroutine loads the configuration distribution at the        #
#  primary database                                                   #
#---------------------------------------------------------------------#
sub Load_Config_Distribution {

  my ($loadout, $currdir);

  &printout ("$ME: Loading Config Distribution\n");
  print "$ME: Loading Config Distribution\n";

				# fix pin.conf file  
  &Fix_Load_Config_Dist_PinConf();

  $currdir = &getcwd();  # get current working directory

                                # well this will work in Unix
  chdir ("$PIN_MD_APPS_MULTIDB_LOCATION");
  $loadout = `$PIN_MD_CONFIG_DIST_LOCATION/load_config_dist`;
  &printout ( $loadout);
  die "$ME: load_config_dist failed.  Exiting\n" if $?;

  chdir ($currdir);

  &printout ("$ME: End - Load Config Distribution\n");
}

#---------------------------------------------------------------------#
#  This subroutine updates the uniqueness entries for secondary dbs   #
#  in primary db						      #
#---------------------------------------------------------------------#
sub Update_Primary_Uniqueness {

  &printout ("\t $ME: Updating the uniqueness table in the primary "); 
  &printout ("database\n");
  print "\t $ME: Updating the uniqueness table in the primary "; 
  print "database\n";

  my ($i);

  for $i ($PIN_MD_SECONDARY_START_INST..$PIN_MD_SECONDARY_END_INST) {
    next if($PIN_MD_SECONDARY_DEPLOY[$i] eq "false");
    &Search_Update_Primary_Uniqueness ( $PIN_MD_SECONDARY_DBNO[$i]);
  }
  &printout ("$ME: End - Update primary \/uniqueness objects.\n");
}

#---------------------------------------------------------------------#
#  This subroutine checks the primary's /uniqueness for the secondary #
#  db entry.  It adds the entry, if it does'nt exist		      #
#---------------------------------------------------------------------#
sub Search_Update_Primary_Uniqueness {
  my ($secondary_dbno) = @_;

  					# search for it
  my ($searchflist, $testout, $tscript, $uniqueflist);
  my $curtime = time;

$searchflist =<<EOF
0 PIN_FLD_RESULTS	ARRAY [1] allocated 4, used 4
1	PIN_FLD_POID	POID [0] NULL
0 PIN_FLD_TEMPLATE	STR [0] "select X from /uniqueness where F1 = V1 "
0 PIN_FLD_ARGS		ARRAY [1]
1	PIN_FLD_LOGIN	STR [0] "root.$secondary_dbno"
0 PIN_FLD_FLAGS		INT [0] 0
0 PIN_FLD_POID		POID [0] $PIN_MD_PRIMARY_DBNO /search -1 0
EOF
  ;

  open (FLIST1, ">t1.flist") || die "$ME: Could not open t.flist file\n";
  print FLIST1 '<PCM_OP $PIN_OPNAME=PCM_OP_SEARCH; $PIN_OPFLAGS=0>' if($cn == 1);
  print FLIST1 "\n" if($cn == 1);
  print FLIST1 $searchflist;
  print FLIST1 '</PCM_OP>' if($cn == 1);
  close (FLIST1);

  $tscript = <<EOF

r t1.flist 1
search 1
EOF
  ;

  if($cn == 0) {
	$testout = &Execute_TestNAP_Command ($tscript);
	unlink "t1.flist";
  } else {
	&create_obj('t1.flist');
	open (FLIST1, "out.flist") || die "$ME: Could not open out.flist file\n";
	while(<FLIST1>) {
		if($_ =~ /PIN_FLD_RESULTS/) {
			$testout = $_;
		}
	}
	close (FLIST1);
  }

  if ($testout =~ /PIN_FLD_RESULTS/) {		# secondary db entry found
    &printout ("$ME:  $secondary_dbno found in /uniqueness. Skipping..\n");	
  } else {					# secondary db entry not found
    &printout ("$ME:  $secondary_dbno not found in /uniqueness. Adding..\n");	

  $uniqueflist =<<EOF
0 PIN_FLD_POID		POID [0] $PIN_MD_PRIMARY_DBNO /uniqueness 1 0
0 PIN_FLD_LOGIN		STR [0] "root.$secondary_dbno"
0 PIN_FLD_STATUS	ENUM [0] 2
0 PIN_FLD_SERVICE_OBJ	POID [0] $secondary_dbno /service/pcm_client 1 0
0 PIN_FLD_ACCOUNT_OBJ	POID [0] $secondary_dbno /account 1 0
0 PIN_FLD_ACCOUNT_NO	STR [0] "ROOT.$secondary_dbno"
0 PIN_FLD_CREATED_T	TSTAMP [0] ($curtime)
0 PIN_FLD_MOD_T		TSTAMP [0] (0)
0 PIN_FLD_TYPE          ENUM [0] 0
EOF
  ;

    &printout("$uniqueflist") if $DEBUG;

    open (FLIST2, ">t2.flist") || die "$ME: Could not open t.flist file\n";
    print FLIST2 '<PCM_OP $PIN_OPNAME=$PIN_CONF_INIT_OPNAME; $PIN_OPFLAGS=0>' if($cn == 1);
    print FLIST2 "\n" if($cn == 1);
    print FLIST2 $uniqueflist;
    print FLIST2 '</PCM_OP>' if($cn == 1);
    close (FLIST2);

    $tscript = <<EOF

r t2.flist 1
create 1
EOF
  ;

    if($cn ==0) {
	$testout = &Execute_TestNAP_Command ($tscript);
	unlink "t2.flist";
    } else {
	&create_obj('t2.flist');
    }

  $uniqueflist =<<EOF
0 PIN_FLD_POID		POID [0] $PIN_MD_PRIMARY_DBNO /uniqueness 2 0
0 PIN_FLD_LOGIN		STR [0] "root.$secondary_dbno"
0 PIN_FLD_STATUS	ENUM [0] 2
0 PIN_FLD_SERVICE_OBJ	POID [0] $secondary_dbno /service/admin_client 2 0
0 PIN_FLD_ACCOUNT_OBJ	POID [0] $secondary_dbno /account 1 0
0 PIN_FLD_ACCOUNT_NO	STR [0] "ROOT.$secondary_dbno"
0 PIN_FLD_CREATED_T	TSTAMP [0] ($curtime)
0 PIN_FLD_MOD_T		TSTAMP [0] (0)
0 PIN_FLD_TYPE          ENUM [0] 1
EOF
  ;

    &printout("$uniqueflist") if $DEBUG;

    open (FLIST3, ">t3.flist") || die "$ME: Could not open t.flist file\n";
    print FLIST3 '<PCM_OP $PIN_OPNAME=$PIN_CONF_INIT_OPNAME; $PIN_OPFLAGS=0>' if($cn == 1);
    print FLIST3 "\n" if($cn == 1);
    print FLIST3 $uniqueflist;
    print FLIST3 '</PCM_OP>' if($cn == 1);
    close (FLIST3);

    $tscript = <<EOF

r t3.flist 1
create 1
EOF
  ;

    if($cn ==0) {
	$testout = &Execute_TestNAP_Command ($tscript);
	unlink "t3.flist";
    } else {
	&create_obj('t3.flist');
    }

  }  # else
}

# Opcode call with dm_oracle perl API
sub create_obj {
        my ($file) = @_;
        our %MAIN_DM;
        $SKIP_INIT_OBJECTS   = "YES";
        $USE_SPECIAL_DD_FILE = "YES";
        $SPECIAL_DD_FILE     = "$PIN_HOME/setup/scripts/$file";
        &pin_init_non_partition(%MAIN_DM);
}

#---------------------------------------------------------------------#
#  This subroutine creates and initializes the objects in the         #
#  secondary database to support a Infranet MultiDB configuration     #
#---------------------------------------------------------------------#
sub Initialize_Secondary_for_MultiDB  {

  &printout ("$ME: Initializing Secondary Databases for Multi-Schema\n");
  print "$ME: Initializing Secondary Databases for Multi-Schema\n";

  my ($i, $username, $password, $dbname, $sqlhost, $file, %grant_list, $primPassFetch);
  $primPassFetch = 0;

  if ($PIN_MD_SQL_PLATFORM =~ /Oracle/i ){

    for $i ($PIN_MD_SECONDARY_START_INST..$PIN_MD_SECONDARY_END_INST) {
	next if($PIN_MD_SECONDARY_DEPLOY[$i] eq "false");

	&printout("$ME: Processing secondary database [$i]\n");

	$username = $PIN_MD_SECONDARY_OWNER  [$i];
	if ($PIN_MD_SECONDARY_PASSWD[$i] =~ m/^\&aes\|/ || $PIN_MD_SECONDARY_PASSWD[$i] =~ m/^\&ozt\|/) {
              $passwd   = aes::psiu_perl_decrypt_pw($PIN_MD_SECONDARY_PASSWD[$i]);
        } else {
              $passwd   = $PIN_MD_SECONDARY_PASSWD[$i];
        }
    	$dbname   = $PIN_MD_SECONDARY_DBNAME [$i];
    	$sqlhost  = $PIN_MD_SECONDARY_SQLHOST[$i];
	$DB_LINK = "MD_PRIMARY";
	$PIN_MD_DBNAME = $PIN_MD_PRIMARY_DBNAME;
	                       # create db link 
	$file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_SECONDARY_INIT_SCRIPT";
	if($cn == 0 && $primPassFetch == 0) {
		my $brmConfWallet=$ENV{'BRM_CONF_WALLET'};
		system("java -cp $PIN_HOME/jars/oraclepki.jar:/home/pin/opt/portal/setup/BRMActions.jar com.oracle.installer.brm.BRMInstallHelper 7 $brmConfWallet dbP");
		if (-e "$brmConfWallet/.wp") {
			open( TEMPFILE, "$brmConfWallet/.wp" );
			@FileReadIn = <TEMPFILE>;
			close( TEMPFILE );
			$WalletDBPassFile = join( "", @FileReadIn );

			$PIN_MD_PRIMARY_PASSWD = substr($WalletDBPassFile , (index ($WalletDBPassFile,'='))+1);
			chomp($PIN_MD_PRIMARY_PASSWD);

                        unlink("$brmConfWallet/.wp");
                        # Fetching the primary wallet password only once for all the secondary schema's. 
                        $primPassFetch = 1;
		} else {
			exit;
		}
	}
	&printout ("$ME: Executing $file\n");
	&Parse_and_Execute ($file, 1, $username, $passwd, $dbname, $sqlhost);

	if ( defined($PIN_MD_PRIMARY_BACKUP_DBNAME) ) {
		$DB_LINK = "MD_BACKUP";
		$PIN_MD_DBNAME = $PIN_MD_PRIMARY_BACKUP_DBNAME;
		$file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_SECONDARY_INIT_SCRIPT";
		&printout ("$ME: Executing $file\n");
		&Parse_and_Execute ($file, 1, $username, $passwd, $dbname, $sqlhost);
	}
    }

  }

}

#---------------------------------------------------------------------#
#  This subroutine updates  the uniqueness object at the              #
#  primary database                                                   #
#---------------------------------------------------------------------#
sub Update_Primary_Uniqueness_Again  {

  my ($loadout, $currdir);

  &printout ("$ME: Updating the uniqueness table in the "); 
  &printout ("primary database\n");
  print "$ME: Updating the uniqueness table in the "; 
  print "primary database\n";

  $currdir = &getcwd();  # get current working directory 

                                # well this will work in Unix

  chdir ("$PIN_MD_APPS_MULTIDB_LOCATION");

  &Fix_Load_Pin_Uniqueness_PinConf();

  $loadout = `$PIN_MD_LOAD_PIN_UNIQUENESS_LOCATION/load_pin_uniqueness`;
  &printout ( $loadout);
  die "$ME: load_pin_uniqueness failed.  Exiting\n" if $?;

  chdir ($currdir);

  &printout ("$ME: End - Update Uniqueness\n");
}

#---------------------------------------------------------------------#

#  This subroutine starts up the miscellaneous programs               #
#---------------------------------------------------------------------#
sub Start_Programs {

  my ($currdir);

  $currdir = &getcwd();  # get current working directory
                                # well this will work in Unix
                                # we should make the NT equivalent
  chdir ("$PIN_MD_APPS_MULTIDB_LOCATION");

  &printout ("$ME: Synchronizing the data dictionary of"); 
  &printout ("the secondary database(s)\n");
  print "$ME: Synchronizing the data dictionary of"; 
  print "the secondary database(s)\n";

  system "$PIN_MD_SYNCH_DD_LOCATION/multi_db_synch_dd";

  if ($PIN_MD_SQL_PLATFORM !~ /Oracle/i) {
    &printout ("$ME: Starting up pin_confirm_logins and ");
    &printout ("pin_config_distributions background programs\n");
    print "$ME: Starting up pin_confirm_logins and ";
    print "pin_config_distributions background programs\n";
    if ($^O !~ /Win/i) {
  	system "$PIN_MD_CONFIRM_LOGINS_LOCATION/start_pin_confirm_logins";
    } else {
  	system "startserv InfPinConfirmLogins";
    }
  } else {
    &printout ("$ME: Starting up pin_config_distributions background program\n");
    print "$ME: Starting up pin_config_distributions background program\n";
  } 

  if ($^O !~ /Win/i) {
  	system "$PIN_MD_CONFIG_DISTRIBUTION_LOCATION/start_pin_config_distribution";
  } else {
  	system "startserv InfPinConfigDistribution";
  }

  chdir ($currdir);
  &printout ("$ME: End - Started up background programs\n");
}

#---------------------------------------------------------------------#
#  This subroutine gets the current directory on NT                   #
#---------------------------------------------------------------------#
sub get_nt_curdir  {
  return &getcwd();  # get current working directory;
}

#---------------------------------------------------------------------#
#  This subroutine starts the CM and Primary DM                       #
#---------------------------------------------------------------------#
sub Start_Primary_DM_CM {
                                        # Start DM
  &printout("$ME: Starting DM $PIN_MD_SQL_PLATFORM...\n");
  print "$ME: Starting DM $PIN_MD_SQL_PLATFORM...\n";

  system "$PIN_MD_DM_DB_START_CMD";
  $status = ($? >> 8);
  if ($status || $?) {
     &printout("$ME: Cannot start DM (exit status $status)\n");
     exit(1);
  }
  &printout("$ME: Pausing 50 seconds to let the DM startup\n");
  print "$ME: Pausing 50 seconds to let the DM startup\n";
  sleep 50;
                                        # Start CM
  &printout("$ME: Starting CM ...\n");
  print "$ME: Starting CM ...\n";
  system "$PIN_MD_CM_START_CMD";
  $status = ($? >> 8);
  if ($status || $?) {
     &printout("$ME: Cannot start CM (exit status $status)\n");
     exit(1);
  }
  &printout("$ME: Pausing 50 seconds to let the CM startup\n");
  print "$ME: Pausing 50 seconds to let the CM startup\n";
  sleep 50;
}

#---------------------------------------------------------------------#
#  This subroutine stops the CM and Primary DM                        #
#---------------------------------------------------------------------#
sub Stop_Primary_DM_CM {
  if ($^O =~ /win/i) {
                                        # Stop CM
	&printout("$ME: Stopping CM ...\n");
	system "$PIN_MD_CM_STOP_CMD";
	&printout("$ME: Pausing 20 seconds to let the CM stop\n");
	print "$ME: Pausing 20 seconds to let the CM stop\n";
 	sleep 20;

                                        # Stop DM
	&printout("$ME: Stopping DM $PIN_MD_SQL_PLATFORM...\n");
	system "$PIN_MD_DM_DB_STOP_CMD";
	&printout("$ME: Pausing 20 seconds to let the DM Stop \n");
	print "$ME: Pausing 20 seconds to let the DM Stop\n";
	sleep 20;

  } elsif ($^O !=~ /win/i) {
        &printout("$ME: Stopping CM ...\n");
        &printout("$ME: Stopping DM $PIN_MD_SQL_PLATFORM...\n");
        if($logging=="&STDOUT") {
          #Stop CM
          system ("$PIN_MD_CM_STOP_CMD 1");
          #Stop DM
          system ("$PIN_MD_DM_DB_STOP_CMD 1");
      }
      else{
        # Stop CM
        system ("$PIN_MD_CM_STOP_CMD 1>>".$logging." 2>&1");
        # Stop DM
        system ("$PIN_MD_DM_DB_STOP_CMD 1>>".$logging." 2>&1");
      }
  }
}

#---------------------------------------------------------------------#
#  This subroutine prints the Usage information for this script       #
#---------------------------------------------------------------------#
sub Usage {
  print "Usage: pin_multidb.pl [-s] [-i | -f | -d]\n";
  print "\t -i - To initialize the primary and secondary db's\n";
  print "\t -f - To finalize the Multi-Schema installation\n";
  print "\t -s - Execute the script without prompts, runs in silent mode\n";
  print "\t -d - To drop the replication objects - Only for SQL Server\n";
  print "\t \t	  - Only for Oracle\n";
  exit(1);
}

#---------------------------------------------------------------------#
#  This subroutine prints out informatory message about steps needs   #
#  to be done before finalize					      #
#---------------------------------------------------------------------#
sub Print_Information_Message {
  &printout("--------------------------------------------------------------\n");
  print "--------------------------------------------------------------\n";
  &printout("Your primary and secondary databases have been initialized \n");
  print "Your primary and secondary databases have been initialized with\n";
  &printout("with Multi-Schema objects. Please check the pin_multidb.log ");
  print "Multi-Schema objects. Please check the pin_multidb.log ";
  &printout("file for errors. \n");
  print "file for errors. \n";
  &printout("If there are no errors, please perform the following: \n");
  print "If there are no errors, please perform the following: \n";
  &printout("\t1. Shutdown all primary and secondary DMs.\n");
  print "\t1. Shutdown all primary and secondary DMs.\n";
  &printout("\t2. Start all primary and secondary DMs.\n");
  print "\t2. Start all primary and secondary DMs.\n";
  &printout("\t3. Start the CM.\n");
  print "\t3. Start the CM.\n";
  &printout("\t4. Make sure all CMs and DMs are up and running "); 
  &printout("and are reachable.\n");
  print "\t4. Make sure all CMs and DMs are up and running "; 
  print "and are reachable.\n";
  &printout("\t5. Run pin_multidb.pl with the -f option to finalize "); 
  &printout("Multi-Schema installation.\n");
  print "\t5. Run pin_multidb.pl with the -f option to finalize "; 
  print "Multi-Schema installation.\n";
  &printout("------------------------------------------------------------\n");
  print "------------------------------------------------------------\n";
}


#---------------------------------------------------------------------#
#  This subroutine fixes the local pin.conf file with cm_ptr and other#
#  minimal information required for nap application		      #
#---------------------------------------------------------------------#
sub Fix_Local_PinConf {

  my (%napconf);
  my (%uid);

  &printout("$ME: Fixing local pin.conf file for testnap access\n");
  $napconf{'cm_ptr'} = "ip\t$PIN_MD_CM_HOST\t$PIN_MD_CM_PORT";
  $napconf{'login_type'} = "1";
  $napconf{'login_name'} = "root.$PIN_MD_PRIMARY_DBNO";
  $uid{'userid'} = "$PIN_MD_PRIMARY_DBNO /service/pcm_client 1";

  # Check if the pin.conf exists, if not create it
  if(! -e "pin.conf") {
    # create the zero byte file
    open (OUTFILE, ">pin.conf") ||
          die "$ME: Unable to create file pin.conf: $!\n";
    close(OUTFILE);
  }

  &fix_pinconf("pin.conf", "nap", %napconf);
  &fix_pinconf("pin.conf", "-", %uid);
}

#---------------------------------------------------------------------#
#  This subroutine fixes CMs  pin.conf file                           #
#  and updating all the dm_pointers for secondary databases           #
#---------------------------------------------------------------------#
sub Fix_CM_PinConf {
  
  my (%cmconf);
  my ($i);

  &printout("$ME: Fixing CM pin.conf file \n");
  $cmconf{'multi_db'} = 1;
  $cmconf{'primary_db'} = "$PIN_MD_PRIMARY_DBNO\t\/\t0";
  if( $REPLICATE_UNIQUENESS == 0 ) {
	$cmconf{'primary_uniqueness'} = "uniqueness 1";
  }

  $cmconf{'uniqueness_login'} = 1;
  $cmconf{'uniqueness_account_no'} = 0;

  for $i ($PIN_MD_SECONDARY_START_INST..$PIN_MD_SECONDARY_END_INST) {
    $cmconf{"dm_pointer\t$PIN_MD_SECONDARY_DBNO[$i]"} = 
	"ip\t$PIN_MD_SECONDARY_HOSTNAME[$i]\t$PIN_MD_SECONDARY_PORT[$i]";
    $cmconf{"dm_attributes\t$PIN_MD_SECONDARY_DBNO[$i]"} = 
	"scoped,assign_account_obj,searchable";
  }

  &fix_pinconf("$PIN_MD_CM_PINCONF", "cm", %cmconf);

if ($PIN_MD_SQL_PLATFORM =~ /Oracle/i) {
  	$fm_custconf{'use_legacy_uniqueness_population'} = 0;
  } else {
	$fm_custconf{'use_legacy_uniqueness_population'} = 1;
  }
  &fix_pinconf("$PIN_MD_CM_PINCONF", "fm_cust", %fm_custconf);
}

#-----------------------------------------------#
#  This subroutine fixes DMs pin.conf file      #
#-----------------------------------------------#
sub Fix_DM_PinConf {
 
  &printout("$ME: Fixing Secondary DMs pin.conf file for Multi-Schema\n");
  &printout("   ----------------------------------------------------------------\n");
  &printout("   Please manually add \"- dm schema 0.0.0.1 $PIN_MD_PRIMARY_OWNER\" \n");
  &printout("   ----------------------------------------------------------------\n");

  print "   Please manually add \"- dm schema 0.0.0.1 ${PIN_MD_PRIMARY_OWNER}\" \n";
  print "   ----------------------------------------------------------------\n";
  
}

#---------------------------------------------------------------------#
#  This subroutine fixes load_pin_uniqueness's  pin.conf file with    #
#  logfile value 	     					      #
#---------------------------------------------------------------------#
sub Fix_Load_Pin_Uniqueness_PinConf {
  my (%lpuconf, %napconf);

  $lpuconf{'logfile'} = "\${PIN_LOG_DIR}/multi_db/load_pin_uniqueness.pinlog";
  $lpuconf{'loglevel'} = 2; 
  $lpuconf{'use_account_no'} = "$PIN_MD_CONFIRM_LOGIN_USE_ACCT_NO";
  &fix_pinconf("$PIN_MD_MULTIDB_PINCONF", "load_pin_uniqueness", %lpuconf);
}

#---------------------------------------------------------------------#
#---------------------------------------------------------------------#
#  This subroutine fixes multi_db_synch_dd, pin_confirm_logins,       #
#  pin_config_distribution's  pin.conf file with frequency value,     #
#  loglevel and logfile                                               #
#---------------------------------------------------------------------#
sub Fix_Multi_Confirm_Config_PinConf {
  my (%mdsdconf, %pclconf, %pcdconf, %napconf);

  &printout("$ME: Fixing multi_db_synch_dd pin.conf file \n");
  $mdsdconf{'logfile'} = "\${PIN_LOG_DIR}/multi_db/multi_db_synch_dd.pinlog";
  $mdsdconf{'loglevel'} = 2; 
  &fix_pinconf("$PIN_MD_MULTIDB_PINCONF", "multi_db_synch_dd", %mdsdconf);

  &printout("$ME: Fixing pin_confirm_logins pin.conf file for frequency\n");
  $pclconf{'frequency'} = "$PIN_MD_CONFIRM_LOGIN_FREQ";
  $pclconf{'validation_delay'} = "$PIN_MD_CONFIRM_LOGIN_VALID_DELAY";
  $pclconf{'use_account_no'} = "$PIN_MD_CONFIRM_LOGIN_USE_ACCT_NO";
  $pclconf{'logfile'} = "\${PIN_LOG_DIR}/multi_db/pin_confirm_logins.pinlog";
  $pclconf{'loglevel'} = 2; 
  &fix_pinconf("$PIN_MD_MULTIDB_PINCONF", "pin_confirm_logins", %pclconf);

  &printout("$ME: Fixing pin_config_distribution pin.conf file for "); 
  &printout("frequency\n");
  $pcdconf{'frequency'} = "$PIN_MD_CONFIG_DIST_FREQ";
  $pcdconf{'logfile'} = 
		"\${PIN_LOG_DIR}/multi_db/pin_config_distribution.pinlog";
  $pcdconf{'loglevel'} = 2;
  &fix_pinconf("$PIN_MD_MULTIDB_PINCONF", "pin_config_distribution", 
								%pcdconf);

}

#---------------------------------------------------------------------#
#  This subroutine fixes apps/multi_db/pin.conf file with nap	      #
#  entriesl 							      #
#---------------------------------------------------------------------#
sub Fix_Apps_MultiDB_PinConf {
  my (%napconf);

  &printout("$ME: Fixing apps/multi_db pin.conf file \n");

  $napconf{'cm_ptr'} = "ip\t$PIN_MD_CM_HOST\t$PIN_MD_CM_PORT";
  $napconf{'login_name'} = "root.$PIN_MD_PRIMARY_DBNO";
  &fix_pinconf("$PIN_MD_MULTIDB_PINCONF", "nap", %napconf);
}

#---------------------------------------------------------------------#
#  This subroutine fixes apps/multi_db/pin.conf file with             #
#  logfile and loglevel for load_config_dist                          #
#---------------------------------------------------------------------#
sub Fix_Load_Config_Dist_PinConf() {
  my (%napconf);

  &printout("$ME: Fixing apps/multi_db pin.conf file \n");

  $napconf{'logfile'} = "\${PIN_LOG_DIR}/multi_db/load_config_dist.pinlog";
  $napconf{'loglevel'} = 2; 
  &fix_pinconf("$PIN_MD_MULTIDB_PINCONF", "load_config_dist", %napconf);
}

#---------------------------------------------------------------------#
#  This subroutine starts the sql server replication agents	      #
#  	 							      #
#---------------------------------------------------------------------#
sub Start_Snap_Agents{
  $file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_START_SNAP_AGENTS_SCRIPT";
  open(BATCH_FILE, "$file") || die "Cannot open file $file \n";
  @batch_cmd = <BATCH_FILE>;
  close (BATCH_FILE);
  $cmdstring = join('', @batch_cmd);
  $cmdstring = eval "qq~$cmdstring~";

  $tmpfile = "temp.bat";
  open(TMP_BATFILE, ">$tmpfile") || die "Cannot create file \n";
  print TMP_BATFILE $cmdstring;
  close(TMP_BATFILE);

  system($tmpfile);
  $exitcode = $?;

  if ($exitcode != 0) {
        &printout("$ME: Unable to start the replication agents \n");
  }
}

#---------------------------------------------------------------------#
#  This subroutine starts the sql server replication agents           #
#                                                                     #
#---------------------------------------------------------------------#

sub Start_Repl_Agents{
  local ($REP_ONE, $refresh_group) = @_;
  local ($file, $REF_GROUP);
  if ($REP_ONE =~ 0) {
    $file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_START_AGENTS_SCRIPT";
  } else {
    $REF_GROUP = "multidb_$refresh_group\_pub"; 
    $file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_START_SINGLE_AGENT_SCRIPT";
  }
  open(BATCH_FILE, "$file") || die "Cannot open file $file \n";
  @batch_cmd = <BATCH_FILE>;
  close (BATCH_FILE);

  $cmdstring = join('', @batch_cmd);
  $cmdstring = eval "qq~$cmdstring~";

  $tmpfile = "temp.bat";
  open(TMP_BATFILE, ">$tmpfile") || die "Cannot create file \n";
  print TMP_BATFILE $cmdstring;
  close(TMP_BATFILE);

  system($tmpfile);
  $exitcode = $?;

  if ($exitcode != 0) {
	&printout("$ME: Unable to start the replication agents \n");
  }
}

#---------------------------------------------------------------------#
#  This subroutine updates the database numbers in the secondary      #
#  database. It also creates the database triggers to do db nr update #
#---------------------------------------------------------------------#

sub Update_Poid_Dbs{

  local ($file) = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_UPDATE_DBNO_SCRIPT";

  open(BATCH_FILE, "$file") || die "Cannot open file $file \n";
  @batch_cmd = <BATCH_FILE>;
  close (BATCH_FILE);

  $cmdstring = join('', @batch_cmd);
  $cmdstring = eval "qq~$cmdstring~";

  $tmpfile = "temp.bat";
  open(TMP_BATFILE, ">$tmpfile") || die "Cannot create file \n";
  print TMP_BATFILE $cmdstring;
  close(TMP_BATFILE);

  system($tmpfile);
  $exitcode = $?;
 
  if ($exitcode != 0) {
	&printout("$ME: Unable to initialize the database numbers \n");
  }
}

sub Cleanup_For_DB2 {
  local($is_primary) = @_;
  local($cmd);
  my($file);

	    $file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_DB2_CLEANUP_DROP_CTL_TBS";
	    $ARGS = " -tvf "; 
	    &printout ("$ME: Executing $file.\n");
	    &Parse_and_Execute ($file, 1, $username, $passwd, $dbname, "");

	    $file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_DB2_CLEANUP_DROP_VIEW";
	    &printout ("$ME: Executing $file\n");
	    &Parse_and_Execute ($file, 1, $username, $passwd, $dbname, ""); 

	    $ARGS = " -td@ -vf  ";
	    $file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_DB2_CLEANUP_RECREATE_TABLE";
	    &printout ("$ME: Executing $file\n");
	    &Parse_and_Execute ($file, 1, $username, $passwd, $dbname, "");

	    $ARGS = " -td@ -vf  "; 
	    $file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_DB2_CLEANUP_POPULATE_TABLE";
	    &printout ("$ME: Executing $file\n");
	    &Parse_and_Execute ($file, 1, $username, $passwd, $dbname, ""); 

	    $ARGS = " -tvf "; 
	    if( $is_primary == 1 ) {
	        $file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_DB2_CLEANUP_ALTER";
	        &printout ("$ME: Executing $file\n");
	        &Parse_and_Execute ($file, 1, $username, $passwd, $dbname, ""); 
	    } else {
	        $cmd = "call cleanup_triggers();";
	        &Execute_SQL_Command ($cmd, $username, $passwd, $dbname, ""); 
	    }			

	    $file = "$PIN_MD_SCRIPT_LOCATION/$PIN_MD_DB2_CLEANUP_RENAME";
	    &printout ("$ME: Executing $file\n");
	    &Parse_and_Execute ($file, 1, $username, $passwd, $dbname, ""); 

}

# As the last step of -i, we will launch the java application to reset
# the sequence of all the databases so that the sequence will be unique
# across all the databases.

sub Amt_Sequence {

  if($PIN_MD_SQL_PLATFORM !~ /MSSQL/i) {
	#
	# test if java executable exists
	#
	if (! -e ${JAVA}) {
	    die "$ME: ${JAVA} executable does not exist\n";
	}

	#
	# test if database specific JDBC library exists
	#
	if (! -e ${JDBC_JAR_FILE}) {
	    die "$ME: ${JDBC_JAR_FILE} JDBC library does not exist\n";
	}

	#
	# test if pin_reset_seq.jar exists 
	#
	if (! -e ${PIN_RESET_SEQ_JAR_FILE}) {
	    die "$ME: ${PIN_RESET_SEQ_JAR_FILE} does not exist\n";
	}


	#
	# create pin_reset_seq.properties file for PinResetSeq program
	# (convert PERL variable/array definitions into name/value pairs)
	#
	$config_file_name = "pin_reset_seq.properties";
	open (CONFIG_FILE, ">${config_file_name}") || 
		die "$ME:  Could not open configuration file\n";

	print CONFIG_FILE "#\n# primary database\n#\n";
	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_user_name=";
	print CONFIG_FILE "${PIN_MD_PRIMARY_OWNER}\n";
	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_connection_url=";
	print CONFIG_FILE "${JDBC_URL_PREFIX}${PIN_MD_PRIMARY_DBNAME}\n";
	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_instance_name=";
	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNAME}\n";
	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_primary=true\n";
	if($DB_SSL_MODE eq '2'){
        	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_db_ssl_enabled=true\n";
        	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_db_ssl_client_auth=true\n";
	}elsif($DB_SSL_MODE eq '1' ){
        	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_db_ssl_enabled=true\n";
        	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_db_ssl_client_auth=false\n";
	}else{
        	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_db_ssl_enabled=false\n";
        	print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_db_ssl_client_auth=false\n";
	}
        print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_db_ssl_truststore_filename=cwallet.sso\n";
        print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_db_ssl_truststore_location=$DB_SSL_TRUST_STORE_LOCATION\n";
        print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_db_ssl_keystore_filename=cwallet.sso\n";
        print CONFIG_FILE "${PIN_MD_PRIMARY_DBNO}_db_ssl_keystore_location=$DB_SSL_KEY_STORE_LOCATION\n";

	for $i (0..$#PIN_MD_SECONDARY_DBNO) {
	    print CONFIG_FILE "#\n# secondary database\n#\n";
	    print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_user_name=";
	    print CONFIG_FILE "${PIN_MD_SECONDARY_OWNER[$i]}\n";
	    print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_connection_url=";
	    print CONFIG_FILE "${JDBC_URL_PREFIX}${PIN_MD_SECONDARY_DBNAME[$i]}\n";
	    print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_instance_name=";
	    print CONFIG_FILE "${PIN_MD_SECONDARY_DBNAME[$i]}\n";
	    print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_primary=false\n";
	    if($DB_SSL_MODE eq '2'){
            	print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_db_ssl_enabled=true\n";
            	print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_db_ssl_client_auth=true\n";
	    }elsif($DB_SSL_MODE eq '1' ){
            	print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_db_ssl_enabled=true\n";
            	print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_db_ssl_client_auth=false\n";
	     }else{
            	print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_db_ssl_enabled=false\n";
            	print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_db_ssl_client_auth=false\n";
	     }
            print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_db_ssl_truststore_filename=cwallet.sso\n";
            print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_db_ssl_truststore_location=$DB_SSL_TRUST_STORE_LOCATION\n";
            print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_db_ssl_keystore_filename=cwallet.sso\n";
            print CONFIG_FILE "${PIN_MD_SECONDARY_DBNO[$i]}_db_ssl_keystore_location=$DB_SSL_KEY_STORE_LOCATION\n";
	}
	# important: close CONFIG_FILE before it is being used by 
	# the external program PinResetSeq
	close(CONFIG_FILE);

	#
	# call PinResetSeq program
	#
	$pin_reset_seq_output = "pin_reset_seq.out";
	$pin_reset_seq_cmd = "$JAVA -cp ";
        if ($^O =~ /win/i) {
	  $pin_reset_seq_cmd .= "${JDBC_JAR_FILE};${PIN_RESET_SEQ_JAR_FILE} ";
        } else {
	  $pin_reset_seq_cmd .= "${JDBC_JAR_FILE}:${PIN_RESET_SEQ_JAR_FILE}:${PCM_JAR_FILE}:${ORACLEPKI_JAR_FILE}:$PIN_HOME/jars/osdt_core.jar:$PIN_HOME/jars/osdt_cert.jar ";
        }
	$pin_reset_seq_cmd .= "PinResetSeq ${config_file_name} > ";
	$pin_reset_seq_cmd .= "${pin_reset_seq_output}";
	$pin_reset_seq_out = `${pin_reset_seq_cmd}`;
	$exit_code = $?;

	if ($DEBUG) {
	    print "$ME: executing command = ${pin_reset_seq_cmd}\n";
	    print "$ME: exit code = ${exit_code}\n";
	}

	#
	# print PinResetSeq output
	#
	open (OUTPUT_FILE, "${pin_reset_seq_output}") ||
	    die "$ME: ${pin_reset_seq_output} could not be opened 
(check pin_reset_seq.log file) $!\n";
	while(defined($i = <OUTPUT_FILE>)) {
	    print $i
	}
	close(OUTPUT_FILE);
	if ($DEBUG) {
		#
		# pass through PinResetSeq exit code
		#
		exit(${exit_code});
	}
  }
}

sub Prompt_Msg_i1 {
        local ($reply);
        my $now = localtime(time());
        &printout ("\tStart -i Configuring at $now\n");
        print "\t You are about to configure Infranet to be "; 
	print "Multi-Schema enabled. \n";
	print "\t Before you continue, please verify the following: \n";
	print "\t 1. You either have the same database usernames/passwords \n"; 
	print "\t    for your secondary database as those of your ";
	print "primary database or \n";
	print "\t    have your secondary database db name to be the same \n";
	print "\t    as those of the primary schema in the RAC system. \n";
        print "\t 2. You can login to the primary database from your "; 
	print "secondary \n";
        print "\t    database machines.\n";
        print "\t 3. You can login to all the secondary databases from "; 
	print "your \n";
        print "\t    primary database machine.\n";
        print "\t 4. Each database has a different database ID, and "; 
	print "accordingly a different \n";
        print "\t    Infranet root username (eg. root.0.0.0.1 or "; 
	print "root.0.0.0.2, etc.)\n";
        print "\t 5. Modify your pin_multidb.conf file according to the ";
	print "documentation.\n";
        print "\t 6. Modify your config_dist.conf file according to the ";
	print "documentation.\n";
        if ($PIN_MD_SQL_PLATFORM =~ /MSSQL/i) {
                print "\t 7. The primary database must use either the ";
		print "Standard edition \n";
		print "\t    or Enterprise edition of SQL Server.\n";
                print "\t 8. Set up your SQL Server Replication such that "; 
		print "your primary database \n";
                print "\t    is the publisher, all your primary and "; 
		print "secondary databases are \n";
                print "\t    subscribers, and your primary machine is "; 
		print "the distributor. \n";
        } elsif ($PIN_MD_SQL_PLATFORM =~ /Oracle/i ) {
                print "\t 7. Make sure your secondary database ";
		print "init<sid>.ora \n";
		print "\t    file contains the following entries:\n";
                print "\t    job_queue_processes = 1\n";
                print "\t    job_queue_interval = 60\n";
                print "\t    global_names = false\n";
		print "\t 8. Grant create table, create users in all secondary databases.\n";
        } elsif ($PIN_MD_SQL_PLATFORM =~ /DB2/i ) {
        }
	else {
                print "\t You specified a platform in your pin_multidb.conf ";
		print " that we do not \n";
                print "\t support. Configuration is quitting...\n";
                exit(1);
        }
	while ($reply !~/y/i) 
	{
	    print "\t Do you want to start the configuration now? (y/n)\n";

            if($cn == 0) {
                    $reply = <STDIN> ;
            } else {
                    $reply = 'y';
            }

	    if ( $reply =~ /n/i) {
                print "\t quitting...\n";
                exit(1);
	    }
	}
        print "\t Please enter the starting step (0 - 8). ";
	print "If you don't know, enter 0 \n";

        if($cn == 0) {
                $STEP = <STDIN>;
        } else {
                $STEP = 0;
        }

        if ($STEP =~ /[0-8]/ ) {
                if ($STEP != 0 ) {
			$previous_step = $STEP - 1;
                        print "\t You choose to start from STEP $STEP \n";
                        print "\t We assume that you successfully completed "; 
                        print "STEPS 0 through $previous_step.\n";
			print "\t If not, do not continue and ";
			print "run perl pin_multidb.pl -i ";
			print "starting from STEP 0.\n"; 
                        print "\t Do you want to continue? (y/n)\n";
                        $reply = <STDIN>;
                        if ( $reply !~ /y/i) {
                                print "quitting...\n";
                                exit(1);
                        }
                }
        } else {
                print "\t You entered an invalid number. \n";
                print "\t quitting ...\n";
                exit(1);
        }
}

sub Prompt_Msg_i2() {
 	local ($reply);
	my ($i);

	for $i ($PIN_MD_SECONDARY_START_INST..$PIN_MD_SECONDARY_END_INST) {
		next if($PIN_MD_SECONDARY_DEPLOY[$i] eq "false");
        	print "\t PIN_MD_SECONDARY_DBNO[$i] =: ";
        	print "$PIN_MD_SECONDARY_DBNO[$i]\n";
        	print "\t Are you done adding db_link or primary_schema entry \n";
			print "\t into this secondary dm pin.conf? (y/n) \n";


		if($cn == 0) {
			$reply = <STDIN> ;
		} else {
			$reply = 'y';
		}

        	while ( $reply !~ /y/i) {
                	print "\t Try again. Are you done adding db_link or primary_schema entry ";
                	print "into this secondary dm pin.conf? (y/n) \n";
                	$reply = <STDIN> ;
        	}
  	}

	&printout("$ME: DM pin.conf fixing done for all DMs \n");
	print "$ME: DM pin.conf fixing done for all DMs \n";
}

sub Prompt_Msg_i() {
        print "\t We just finished STEP $STEP\n";
        &printout ("\n\t We just finished STEP $STEP\n");
        print "\t Please check your pin_multidb.log file for any errors. \n";
        if ($STEP =~ 0) {
                print "\t Please ignore the error messages if the messages "; 
		print "are about failing to stop \n";
                print "\t your primary CM or DM and your CM and DM is "; 
		print "actually stopped. \n";
        }
        if ($PIN_MD_SQL_PLATFORM =~ /MSSQL/i) {
            if($STEP =~ 8) {
                print "\t If you did not see the expected information on "; 
		print "the DOS pop out windows\n";
                print "\t then this step has failed.\n";
            }
            if($STEP =~ /[1,2,7,8]/ ) {
                print "\t If this step has failed, you must:\n";
		print "\t 1. Fix the error. \n"; 
		print "\t 2. Run perl pin_multidb.pl -d \n";
		if ($STEP =~ 8) {
			print "\t You also need to delete the ";
			print "following 3 \n";
			print "\t lines in your cm pin.conf before you re-start\n";
			print "- cm multi_db 1\n";
			print "- cm dm_attributes      ";
			print "<2nd db no> scoped,assign_account_obj,searchable \n";
			print "- cm dm_pointer <2nd db no> ip      <2nd hostname> ";
			print " <2nd dm port number> \n";
		}	
		print "\t 3. run perl pin_multidb.pl -i ";
		print "starting from STEP 0.\n";
	    }
            if($STEP =~ 7) {
                print "\t In STEP 8, you will see 4 DOS pop out windows "; 
		print "for each database.\n";
                print "\t You will see the following messages at "; 
		print "the end of \n";
                print "\t the pop out windows for primary database "; 
		print "snapshots:\n";
                print "\t \"A snapshot of [at least] 66 articles was "; 
		print "generated.\" for config pub.\n";
                print "\t \"A snapshot of [at least] 5 articles was "; 
		print "generated.\"for general pub.\n";
                print "\t \"A snapshot of [at least ] 37 articles was ";
		print "generated.\" for price pub.\n";
                print "\t \"A snapshot of [at least] 2 articles was ";
		print "generated.\" for uniqueness pub\n";
                print "\t You will see the following message at the ";
		print "end of \n";
                print "\t the pop out windows for secondary database "; 
		print "snapshots:\n";
                print "\t \"Applied the snapshot to the Subscriber.\"\n";
                print "\t Type Ctrl-C as instructed on the DOS window.\n "
            }
            if($STEP =~ /[1,2,7,8]/ ) {
		print "\t Do you want to continue? (y/n) \n";
		$reply = <STDIN> ;

		if ( $reply !~ /y/i) {
			print "\t quitting...\n";
			exit(1);
		}
		return;
	    }
	}
        if ($STEP =~ 3) {
                print "\t Please verify that your primary CM and DM "; 
		print "started successfully. \n";
        }
        if ($STEP =~ 6) {
                print "\t Please verify that your primary CM and DM "; 
		print "are stopped. \n";
        }
        if ($STEP =~ 8) {
                print "\t If this step failed, and you decide to ";
		print "start from any step \n";
		print "\t before step 8, you need to delete the ";
		print "following 3 \n";
		print "\t lines in your cm pin.conf before you re-start\n";
		print "- cm multi_db 1\n";
		print "- cm dm_attributes      ";
		print "<2nd db no> scoped,assign_account_obj,searchable \n";
		print "- cm dm_pointer <2nd db no> ip      <2nd hostname> ";
		print " <2nd dm port number> \n";
        }
        print "\t If there is an error that cannot be ignored, "; 
	print "please quit and fix the error first\n";
        print "\t and try again later. Please remember the step number, ";
	print "so after you fix the problem\n";
        print "\t you can choose to start from that step. \n";
        print "\t Do you want to continue? (y/n) \n";

        if($cn == 0) {
                $reply = <STDIN> ;
        } else {
                $reply = 'y';
        }

        if ( $reply !~ /y/i) {
                print "\t quitting...\n";
                exit(1);
        }
}

sub Prompt_Msg_f1() {
	my $now = localtime(time());
        &printout ("\tStart -f Configuring at $now\n");
	print "\t Before you run perl pin_multidb.pl -f, make sure: \n";
	print "\t 1. You ran perl pin_multidb.pl -i successfully.\n";
	print "\t 2. The DM pin.conf file contains the following ";
	print "entries:\n";
	print "\t - dm dd_write_enable_fields 1\n";
	print "\t - dm dd_write_enable_objects 1\n";
	print "\t - dm dd_write_enable_portal_objects 1\n";
	print "\t 3. The DM's and CM started successfully.\n";
        print "\t Do you want to continue? (y/n) \n";

        if($cn == 0) {
		$reply = <STDIN> ;
        } else {
		$reply = 'y';
        }

        if ( $reply !~ /y/i) {
                print "\t quitting...\n";
                exit(1);
        }
}
 
sub Prompt_Msg_f() {
  if ($PIN_MD_SQL_PLATFORM =~ /MSSQL/i) {
	print "\t It's okay if you see the following message\n";
	print "\t on the pop out DOS window in the next step:\n";
	print "\t \"No replication transactions are available\"\n";
	print "\t type Ctrl-C as directed on the DOS window.\n";
        print "\t Do you want to continue? (y/n) \n";

        $reply = <STDIN> ;

        if ( $reply !~ /y/i) {
                print "\t quitting...\n";
                exit(1);
        }
  }
}

sub Prompt_Msg_f2() {
	print "\t Multi-Schema configuration is complete.\n";
	print "\t Check the pin_multidb.log, CM, DM, and \n";
	print "\t the logs in your $PIN_MD_INFRANET_LOGS directory\n";
	print "\t to make sure that perl pin_multidb.pl -f ran \n";
	print "\t successfully.\n";
	print "\t If there are errors, fix the problem and run \n";
	print "\t perl pin_multidb.pl -f again.\n";
}

 
sub Prompt_Msg_sub() {
	print "\t You just finished step $SUB_STEP, please check your ";
	print "error log before you continue. \n";
        print "\t Do you want to continue? (y/n) \n";

        $reply = <STDIN> ;

        if ( $reply !~ /y/i) {
                print "\t quitting...\n";
                exit(1);
        }
}
