#
#	@(#)$Id: pin_amt_install.pl /cgbubrm_mainbrm.portalbase/4 2018/03/30 02:42:06 mkothari Exp $;
# 
# Copyright (c) 1996, 2021, Oracle and/or its affiliates. All rights reserved.
# 
#	This material is the confidential property of Oracle Corporation or its
#	licensors and may be used, reproduced, stored or transmitted only in
#	accordance with a valid Oracle license or sublicense agreement.
#

#
#  This script does the AMT initialization between two 
#  (or more) physically separate Infranet MultiDB instances.
#

require "./pin_functions.pl";
require "../pin_setup.values";
require "./pin_tables.values";
require "./pin_multidb_utils";
require "./pin_multidb.conf";
require "./pin_amt_install.conf";

use Getopt::Std;
use aes;

my $cn = 0;
if(defined($ENV{'DOCKER'}) && ($ENV{'DOCKER'} eq '1')) {
	$cn = 1;
        if(not defined($PIN_MD_PRIMARY_PASSWD)) {
                $PIN_MD_PRIMARY_PASSWD = `cat /etc/secret/.oms_schema_password`;
        }
        for $i ($PIN_MD_SECONDARY_START_INST..$PIN_MD_SECONDARY_END_INST) {
                if(not defined($PIN_MD_SECONDARY_PASSWD[$i])) {
                        my $sn = $i + 2;
                        $PIN_MD_SECONDARY_PASSWD[$i] = `cat /etc/secret_secondary/$sn`;
                }
        }
}

$ME = $0;
$DEBUG = 0;

# command to run Oracle loadjava
$LOADJAVA      = "loadjava";

sub Generate_Amt_Properties {

    $HOSTNAME = `hostname`;
    chomp($HOSTNAME); # remove new line

    open (AMT_PROPERTIES, ">${PIN_AMT_PROPERTIES_LOCATION}/${PIN_AMT_PROPERTIES}")
	|| die "$ME:  could not create ${PIN_AMT_PROPERTIES_LOCATION}/$PIN_AMT_PROPERTIES\n";

    print AMT_PROPERTIES "#\n# primary database\n#\n";
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_user_name=$PIN_MD_PRIMARY_OWNER\n";
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_instance_name=$PIN_MD_PRIMARY_DBNAME\n";
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_primary=true\n";
    print AMT_PROPERTIES "# AMT mover\n";
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_mover_log_file_dir=unknown\n";
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_mover_log_file_flag=N\n";
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_grp_srch_log_file_dir=unknown\n";
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_grp_srch_log_file_flag=N\n";
    if($DB_SSL_MODE eq '2'){
        print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_db_ssl_enabled=true\n";
        print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_db_ssl_client_auth=true\n";
    }
    elsif($DB_SSL_MODE eq '1'){
        print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_db_ssl_enabled=true\n";
        print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_db_ssl_enabled=false\n";
    }
    else{
        print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_db_ssl_enabled=false\n";
        print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_db_ssl_client_auth=false\n";
    }
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_db_ssl_truststore_filename=cwallet.sso\n";
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_db_ssl_truststore_location=$DB_SSL_TRUST_STORE_LOCATION\n";
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_db_ssl_keystore_filename=cwallet.sso\n";
    print AMT_PROPERTIES "${PIN_MD_PRIMARY_DBNO}_db_ssl_keystore_location=$DB_SSL_KRY_STORE_LOCATION\n";

    for $i (0..$#PIN_MD_SECONDARY_DBNO) {
	print AMT_PROPERTIES "#\n# secondary database(s)\n#\n";
	print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_user_name=$PIN_MD_SECONDARY_OWNER[$i]\n";
	print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_instance_name=$PIN_MD_SECONDARY_DBNAME[$i]\n";
	print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_primary=false\n";
	print AMT_PROPERTIES "# AMT mover\n";
	print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_mover_log_file_dir=unknown\n";
	print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_mover_log_file_flag=N\n";
        print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_grp_srch_log_file_dir=unknown\n";
        print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_grp_srch_log_file_flag=N\n";
    if($DB_SSL_MODE eq '2'){
        print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_db_ssl_enabled=true\n";
        print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_db_ssl_client_auth=true\n";
    }
    elsif($DB_SSL_MODE eq '1'){
        print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_db_ssl_enabled=true\n";
        print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_db_ssl_client_auth=false\n";
    }
    else{
        print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_db_ssl_enabled=false\n";
        print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_db_ssl_client_auth=false\n";
    }    
    print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_db_ssl_truststore_filename=cwallet.sso\n";
    print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_db_ssl_truststore_location=$DB_SSL_TRUST_STORE_LOCATION\n";
    print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_db_ssl_keystore_filename=cwallet.sso\n";
    print AMT_PROPERTIES "$PIN_MD_SECONDARY_DBNO[$i]_db_ssl_keystore_location=$DB_SSL_KEY_STORE_LOCATION\n";
    }
    
    print AMT_PROPERTIES "#\n# controller definitions\n#\n";
    print AMT_PROPERTIES "controller_1_log_directory=$PIN_MD_INFRANET_LOGS\n";
    print AMT_PROPERTIES "controller_1_port_number=18566\n";
    print AMT_PROPERTIES "controller_1_server=${HOSTNAME}\n";
    print AMT_PROPERTIES "controller_1_thread_count=2\n";
    print AMT_PROPERTIES "controller_1_syslog_priority=7\n";
    print AMT_PROPERTIES "controller_1_event_generation=false\n";
    print AMT_PROPERTIES "controller_1_concurrent_job_number=20\n";
    print AMT_PROPERTIES "controller_1_hold_period=120\n";
    print AMT_PROPERTIES "controller_1_amt_queue_owner_name=pinq\n";
    print AMT_PROPERTIES "controller_1_amt_queue_name=ifw_sync_queue_amt\n";
    
    print AMT_PROPERTIES "#\n# pin_amt definitions\n#\n";
    print AMT_PROPERTIES "pin_amt_log_directory=$PIN_MD_INFRANET_LOGS\n";

    print AMT_PROPERTIES "#\n# CM connection properties\n";
    print AMT_PROPERTIES "# 	connect string in the format\n";
    print AMT_PROPERTIES "#     infranet.login.type=1\n#\n";
    print AMT_PROPERTIES "infranet.login.type=1\n";


    print AMT_PROPERTIES "\n\n#\n# timesten configuration\n#\n";
    print AMT_PROPERTIES "\n#Parameter to indicate if timesten is used or not.\n";
    print AMT_PROPERTIES "timesten_enabled=false\n\n";
    print AMT_PROPERTIES "\n#Parameter to indicate the PIN HOME of target node.\n";
    print AMT_PROPERTIES "target_pin_home=/opt/portal/7.5\n";
    print AMT_PROPERTIES "\n# The next set of parameters are for the credentials of timesten \n";
    print AMT_PROPERTIES "# datastores on the source side that would be involved in migration.\n";
    print AMT_PROPERTIES "# The next 4 parameters need to be replicated for each data stores incrementing the number in the parameter name \n#\n";
    print AMT_PROPERTIES "# DataStore USER, PASSWORD, DataStore Name, Database ID for the data store\n#\n";
    print AMT_PROPERTIES "\n\n#oracle_db_pwd=pin\n";
    print AMT_PROPERTIES "\n\ntimesten_node_1_user=pin\n";
    print AMT_PROPERTIES "#timesten_node_1_pwd=pin\n";
    print AMT_PROPERTIES "timesten_node_1_dsn=tt_0.0.0.1\n";
    print AMT_PROPERTIES "timesten_node_1_db_id=0.0.0.1\n";
    print AMT_PROPERTIES "# To  enable SSL, make sure to provide correct values for below config \n";
    print AMT_PROPERTIES "infranet.pcp.ssl.enabled = true\n";
    print AMT_PROPERTIES "infranet.pcp.ssl.wallet.location = /home/pin/opt/portal/BRM/wallet/client\n";
    print AMT_PROPERTIES "infranet.pcp.ssl.wallet.filename = cwallet.sso\n";
    
    &printout ("generated AMT configuration file ${PIN_AMT_PROPERTIES_LOCATION}/${PIN_AMT_PROPERTIES}\n");
    
    close(AMT_PROPERTIES);
}

sub Grant_Amt_Permissions() {

   &printout ("$ME: Granting permissions across SCHEMAs"); 
   $primary_username = $PIN_MD_PRIMARY_OWNER;
   $primary_passwd   = $PIN_MD_PRIMARY_PASSWD;
   $primary_dbname   = $PIN_MD_PRIMARY_DBNAME;
   $primary_sqlhost  = $PIN_MD_PRIMARY_SQLHOST;

   $file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_GRANT_PERMISSIONS";
   &printout ("$ME: Loading Grant Permissions Procedure in $PIN_MD_PRIMARY_OWNER \n");
   &Parse_and_Execute($file,
                   1,
                   $primary_username,
                   $primary_passwd,
                   $primary_dbname,
                   $primary_sqlhost);

   for $i (0..$#PIN_MD_SECONDARY_DBNO) {
	$username = $PIN_MD_SECONDARY_OWNER  [$i];
        $passwd   = $PIN_MD_SECONDARY_PASSWD [$i];
        $dbname   = $PIN_MD_SECONDARY_DBNAME [$i];
        $sqlhost  = $PIN_MD_SECONDARY_SQLHOST[$i];

	&printout ("$ME: Loading Grant Permissions Procedure in $username \n");
	&Parse_and_Execute($file,
                   1,
                   $username,
                   $passwd,
                   $dbname,
                   $sqlhost);
   }

   for $j (0..$#PIN_MD_SECONDARY_DBNO) {
      $in_username = $PIN_MD_SECONDARY_OWNER  [$j];

      for $i (0..$#PIN_MD_SECONDARY_DBNO) {

          $username = $PIN_MD_SECONDARY_OWNER  [$i];
          $passwd   = $PIN_MD_SECONDARY_PASSWD [$i];
          $dbname   = $PIN_MD_SECONDARY_DBNAME [$i];
          $sqlhost  = $PIN_MD_SECONDARY_SQLHOST[$i];

          if ($in_username ne $username) {	

             &printout ("$ME: Granting Permissions for $in_username in $username \n");
             &Execute_SQL_Command("exec grant_amt_permissions(\'$in_username\');",
                             $username,
                             $passwd,
                             $dbname,
                             $sqlhost);
	  } else {
             &printout ("$ME: Granting Permissions for $primary_username in $username \n");
             &Execute_SQL_Command("exec grant_amt_permissions(\'$primary_username\');",
                             $username,
                             $passwd,
                             $dbname,
                             $sqlhost);	
          }
      }
      &printout ("$ME: Granting Permissions for $in_username in $primary_username \n");
      &Execute_SQL_Command("exec grant_amt_permissions(\'$in_username\');",
                             $primary_username,
                             $primary_passwd,
                             $primary_dbname,
                             $primary_sqlhost);
   }
}

sub Generate_Amt_Datadictionary() {
    $primary_username = $PIN_MD_PRIMARY_OWNER;
    $primary_passwd   = $PIN_MD_PRIMARY_PASSWD;
    $primary_dbname   = $PIN_MD_PRIMARY_DBNAME;	  
    $primary_sqlhost  = $PIN_MD_PRIMARY_SQLHOST;

    &printout ("primary_username = $primary_username \n");
    &printout ("primary_passwd = $primary_passwd \n");
    &printout ("primary_dbname = $primary_dbname \n ");

    &printout ("$ME: initialize AMT schema in primary MultiDB instance");
    &Execute_SQL_Command("truncate table amt_metadata_t;",
			 $primary_username,
			 $primary_passwd,
			 $primary_dbname,
			 $primary_sqlhost);
    &Execute_SQL_Command("exec generate_amt_metadata(\'$primary_username\');",
			 $primary_username,
			 $primary_passwd,
			 $primary_dbname,
			 $primary_sqlhost);
    &Execute_SQL_Command("truncate table amt_poid_type_map_t;",
			 $primary_username,
			 $primary_passwd,
			 $primary_dbname,
			 $primary_sqlhost);
    &Execute_SQL_Command("exec generate_poid_type_map();",
			 $primary_username,
			 $primary_passwd,
			 $primary_dbname,
			 $primary_sqlhost);

    for $i (0..$#PIN_MD_SECONDARY_DBNO) {
	
	&printout ("$ME: Processing secondary database [$i]\n");

	$username = $PIN_MD_SECONDARY_OWNER  [$i];
	$passwd   = $PIN_MD_SECONDARY_PASSWD [$i];
	$dbname   = $PIN_MD_SECONDARY_DBNAME [$i];
	$sqlhost  = $PIN_MD_SECONDARY_SQLHOST[$i];

	&printout ("username = $username \n");
	&printout ("passwd = $passwd \n");
	&printout ("dbname = $dbname \n ");

	&printout ("$ME: initialize AMT schema in secondary MultiDB instance");
	&Execute_SQL_Command("truncate table amt_metadata_t;",
			     $username,
			     $passwd,
			     $dbname,
			     $sqlhost);
	&Execute_SQL_Command("exec generate_amt_metadata(\'$primary_username\');",
			     $username,
			     $passwd,
			     $dbname,
			     $sqlhost);
	&Execute_SQL_Command("truncate table amt_poid_type_map_t;",
			     $username,
			     $passwd,
			     $dbname,
			     $sqlhost);
	&Execute_SQL_Command("exec generate_poid_type_map();",
			     $username,
			     $passwd,
			     $dbname,
			     $sqlhost);
    }
}

#
# usage()
#
sub usage {
    print "AMT Installation Tool: \n";
    print "(c) Copyright 2009 Oracle Corporation. All rights reserved.\n";
    print "usage: $ME [-m|-h]\n"; 
    print "\t-m update AMT data dictionary\n"; 
    print "\t-h help\n"; 
} 

# main()

open (LOGFILE, ">>pin_amt_install.log") || die "$ME:  could not open logfile\n";

# commandline parameter processing
getopts('mh');

if($opt_h == 1) {
    usage();
    exit(0);
} elsif ($opt_m == 1) {
    &printout ("Re-generating AMT data dictionary\n");
    &Grant_Amt_Permissions();
    &Generate_Amt_Datadictionary();
    exit(0);    
}

&Generate_Amt_Properties() if($cn == 0);

$primary_username = $PIN_MD_PRIMARY_OWNER;
$primary_passwd   = $PIN_MD_PRIMARY_PASSWD;
$primary_dbname   = $PIN_MD_PRIMARY_DBNAME;	  
$primary_sqlhost  = $PIN_MD_PRIMARY_SQLHOST;

&printout ("primary_username = $primary_username \n");
&printout ("primary_passwd = **** \n");
&printout ("primary_dbname = $primary_dbname \n ");

&printout ("load AMT Java stored procedures and PCM libraries\n");
&printout ("load $PCMEXT_JAR\n");
$loadjavaout = `$LOADJAVA -user /\@$primary_dbname $PIN_AMT_JARS_LOCATION/$PCMEXT_JAR`;
&printout ("$loadjavaout\n");
&printout ("load $PCM_JAR\n");
$loadjavaout = `$LOADJAVA -user /\@$primary_dbname $PIN_AMT_JARS_LOCATION/$PCM_JAR`;
&printout ("$loadjavaout\n");
&printout ("load $SPAMT_JAR\n");
$loadjavaout = `$LOADJAVA -user /\@$primary_dbname $PIN_AMT_JARS_LOCATION/$SPAMT_JAR`;
&printout ("$loadjavaout\n");

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_CONTROLLER_SCHEMA_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
		   1,
		   $primary_username,
		   $primary_passwd,
		   $primary_dbname,
		   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_MOVER_SCHEMA_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
		   1,
		   $primary_username,
		   $primary_passwd,
		   $primary_dbname,
		   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_GENERATE_POID_TYPE_MAP_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
		   0,
		   $primary_username,
		   $primary_passwd,
		   $primary_dbname,
		   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_GENERATE_AMT_METADATA_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
		   0,
		   $primary_username,
		   $primary_passwd,
		   $primary_dbname,
		   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_UPDATE_UNIQUENESS_TABLE_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
		   0,
		   $primary_username,
		   $primary_passwd,
		   $primary_dbname,
		   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_MV_PKG_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
		   0,
		   $primary_username,
		   $primary_passwd,
		   $primary_dbname,
		   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_MV_PKB_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
		   0,
		   $primary_username,
		   $primary_passwd,
		   $primary_dbname,
		   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_RERATE_PKG_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
                   0,
                   $primary_username,
                   $primary_passwd,
                   $primary_dbname,
                   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_RERATE_PKB_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
                   0,
                   $primary_username,
                   $primary_passwd,
                   $primary_dbname,
                   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_GROUP_SEARCH_PKG_SCRIPT"; 
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
                   0,
                   $primary_username,
                   $primary_passwd,
                   $primary_dbname,
                   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_GROUP_SEARCH_PKB_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
                   0,
                   $primary_username,
                   $primary_passwd,
                   $primary_dbname,
                   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_CLEANUP_INSTANCE_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
		   0,
		   $primary_username,
		   $primary_passwd,
		   $primary_dbname,
		   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_COMPARE_RECORD_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
		   0,
		   $primary_username,
		   $primary_passwd,
		   $primary_dbname,
		   $primary_sqlhost);

$file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_CREATE_INDEXES_SCRIPT";
&printout ("$ME: Executing $file\n");

&Parse_and_Execute($file,
                   1,
                   $primary_username,
                   $primary_passwd,
                   $primary_dbname,
                   $primary_sqlhost);

&printout ("$ME: initialize AMT schema in primary MultiDB instance");
&Execute_SQL_Command("exec generate_amt_metadata(\'$primary_username\');",
		     $primary_username,
		     $primary_passwd,
		     $primary_dbname,
		     $primary_sqlhost);
&Execute_SQL_Command("exec generate_poid_type_map();",
		     $primary_username,
		     $primary_passwd,
		     $primary_dbname,
		     $primary_sqlhost);

for $i (0..$#PIN_MD_SECONDARY_DBNO) {
    
    &printout ("$ME: Processing secondary database [$i]\n");

    $username = $PIN_MD_SECONDARY_OWNER  [$i];
    $passwd   = $PIN_MD_SECONDARY_PASSWD [$i];
    $dbname   = $PIN_MD_SECONDARY_DBNAME [$i];
    $sqlhost  = $PIN_MD_SECONDARY_SQLHOST[$i];

    my $user_pass = '/';
    if($cn) {
      $user_pass = "$username/$passwd";
    }

    &printout ("username = $username \n");
    &printout ("passwd = **** \n");
    &printout ("dbname = $dbname \n ");

    &printout ("load AMT Java stored procedures and PCM libraries\n");
    &printout ("load $PCMEXT_JAR\n");
    $loadjavaout = `$LOADJAVA -user $user_pass\@$dbname $PIN_AMT_JARS_LOCATION/$PCMEXT_JAR`;
    &printout ("$loadjavaout\n");
    &printout ("load $PCM_JAR\n");
    $loadjavaout = `$LOADJAVA -user $user_pass\@$dbname $PIN_AMT_JARS_LOCATION/$PCM_JAR`;
    &printout ("$loadjavaout\n");
    &printout ("load $SPAMT_JAR\n");
    $loadjavaout = `$LOADJAVA -user $user_pass\@$dbname $PIN_AMT_JARS_LOCATION/$SPAMT_JAR`;
    &printout ("$loadjavaout\n");

    $file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_MOVER_SCHEMA_SCRIPT";
    &printout ("$ME: Executing $file\n");

    &Parse_and_Execute($file,
		       1,
		       $username,
		       $passwd,
		       $dbname,
		       $sqlhost);

    $file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_GENERATE_POID_TYPE_MAP_SCRIPT";
    &printout ("$ME: Executing $file\n");

    &Parse_and_Execute($file,
		       0,
		       $username,
		       $passwd,
		       $dbname,
		       $sqlhost);

    $file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_GENERATE_AMT_METADATA_SCRIPT";
    &printout ("$ME: Executing $file\n");

    &Parse_and_Execute($file,
		       0,
		       $username,
		       $passwd,
		       $dbname,
		       $sqlhost);

    $file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_MV_PKG_SCRIPT";
    &printout ("$ME: Executing $file\n");

    &Parse_and_Execute($file,
		       0,
		       $username,
		       $passwd,
		       $dbname,
		       $sqlhost);

    $file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_MV_PKB_SCRIPT";
    &printout ("$ME: Executing $file\n");

    &Parse_and_Execute($file,
		       0,
		       $username,
		       $passwd,
		       $dbname,
		       $sqlhost);

    $file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_GROUP_SEARCH_PKG_SCRIPT";
    &printout ("$ME: Executing $file\n");

    &Parse_and_Execute($file,
                       0,
                       $username,
                       $passwd,
                       $dbname,
                       $sqlhost);

    $file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_GROUP_SEARCH_PKB_SCRIPT";
    &printout ("$ME: Executing $file\n");

    &Parse_and_Execute($file,
                       0,
                       $username,
                       $passwd,
                       $dbname,
                       $sqlhost);


    $file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_COMPARE_RECORD_SCRIPT";
    &printout ("$ME: Executing $file\n");

    &Parse_and_Execute($file,
		       0,
		       $username,
		       $passwd,
		       $dbname,
		       $sqlhost);

    $file = "$PIN_AMT_SCRIPT_LOCATION/$PIN_AMT_CREATE_INDEXES_SCRIPT";
    &printout ("$ME: Executing $file\n");

    &Parse_and_Execute($file,
                       1,
                       $username,
                       $passwd,
                       $dbname,
                       $sqlhost);

    &printout ("$ME: Grant privelages on MD_STATIC_OBJECTS_T to secondary user $username\n");
    &Execute_SQL_Command("GRANT SELECT ON MD_STATIC_OBJECTS_T TO $username;",
                         $primary_username,
                         $primary_passwd,
                         $primary_dbname,
                         $primary_sqlhost);

    &printout ("$ME: initialize AMT schema in secondary MultiDB instance");
    &Execute_SQL_Command("exec generate_amt_metadata(\'$primary_username\');",
			 $username,
			 $passwd,
			 $dbname,
			 $sqlhost);
    &Execute_SQL_Command("exec generate_poid_type_map();",
			 $username,
			 $passwd,
			 $dbname,
			 $sqlhost);
}
&Grant_Amt_Permissions();



