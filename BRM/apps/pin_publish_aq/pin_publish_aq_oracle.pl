#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#
#      2003, 2023, Oracle and/or its affiliates.
#      This material is the confidential property of Oracle Corporation or its 
#      licensors and may be used, reproduced, stored or transmitted only in
#      accordance with a valid Oracle license or sublicense agreement.
#

#
# pin_acct_sync
#

use Getopt::Std;

$ME = $0;

## constants

$PIN_HOME    = $ENV{"PIN_HOME"};

# check if PIN_HOME is defined
if( $PIN_HOME =~ /^$/ ) {
    print "$ME: ERROR: PIN_HOME environment variable is undefined\n";
    exit(1);
}

# temporary directory to create files
$TEMPDIR     = "/tmp";

# command to run Oracle sqlplus
$SQLPLUS       = "sqlplus -s";

# report scripts
$EVENT_SUMMARY_REPORT="$PIN_HOME/apps/pin_publish_aq/event_summary_report.sql";
$EVENT_DETAIL_REPORT="$PIN_HOME/apps/pin_publish_aq/event_detail_report.sql";

# account sync queue
$CREATE_SYNC_QUEUE = "$PIN_HOME/apps/pin_publish_aq/create_aq_queue.sql";
$CREATE_SYNC_QUEUE_CONF = "$PIN_HOME/apps/pin_publish_aq/create_aq_queue.conf";
$DROP_SYNC_QUEUE = "$PIN_HOME/apps/pin_publish_aq/drop_aq_queue.sql";

# account sync package
$CREATE_SYNC_PKG = "$PIN_HOME/apps/pin_publish_aq/create_acct_aq_pkg.sql";
$CREATE_SYNC_PKB = "$PIN_HOME/apps/pin_publish_aq/create_acct_aq_pkb.sql";

# self test procedures
$CREATE_SEND_EVENT = "$PIN_HOME/apps/pin_publish_aq/create_send_event.sql";
$CREATE_RECEIVE_EVENT = "$PIN_HOME/apps/pin_publish_aq/create_receive_event.sql";

require $CREATE_SYNC_QUEUE_CONF;

# Define the event's payload default type as pin_event_ty 
$primary_schema_payload_type = "pin_event_ty";

## procedures/functions

#
# exec_sqlcommand_file(login,passwd,database_name,command_file)
#
# Calls SQLPLUS with command_file as input. Results
# are stored in global variable $sqlout (output text) and $exitcode
# (SQLPLUS process exit code). Terminates program if
# string ERROR is found in $sqlout.
#
# parameters:
#   login          - login name
#   passwd   -     - login password
#   database_name  - database identifier
#   command_file   - file name of SQL or PL/SQL script
#
sub exec_sqlcommand_file {
    local ($login, $passwd,$db_connect,$cmd_file) = @_;
    local ($status) = 0;
    local ($exitcode) = 0;

    #
    # SQLPLUS gives a zero status back if the user/passwd is
    # wrong. So, instead of using system(), we need to capture the output
    # of SQLPLUS and parse it to see if there was an error.
    #
    $sqlout = `$SQLPLUS /\@$db_connect < $cmd_file`;
    $exitcode = $?;
    $status = ($? >> 8);

    if (($sqlout =~ m/ERROR: /) or ($sqlout =~ m/Errors /)) {
	print("$ME: ERROR: SQLPLUS failed (exitcode = $exitcode)\n");
	print $sqlout;
	exit(1);
    }

    #
    # On NT, we are getting the exit status as is in $?...
    # so, $status after right shifting becomes 0! So, check for
    # non-zero $? even though it is not "absolutely" right on unix.
    #
    if ($status || $exitcode) {
	print("$ME: ERROR: $SQLPLUS failed with status $status\n");
	print $sqlout;
	exit (1);
    }
}

#
# exec_sqlcommand(login,passwd,database_name,command)
#
# Calls SQLPLUS with command as input. Results
# are stored in global variable $sqlout (output text) and $exitcode
# (SQLPLUS process exit code). Terminates program if
# string ERROR is found in $sqlout.
#
# parameters:
#   login          - login name
#   passwd   -     - login password
#   database_name  - database identifier
#   cmd            - SQL command string
#
sub exec_sqlcommand {
    local ($login,$passwd,$db_connect,$cmd) = @_;
    local ($tmpfile) = "$TEMPDIR/pintmp$file_suffix.sql";

    # create a temporary file with the sqlplus input.
    open(TMPFILE, ">$tmpfile") || die "$ME: cannot create $tmpfile\n";
    print TMPFILE "$cmd";
    print TMPFILE "\nexit;\n";
    close(TMPFILE);

    exec_sqlcommand_file($login,$passwd,$db_connect,$tmpfile);

    unlink "$tmpfile";
}

#
# parse_and_exec()
#
sub parse_exec_sqlcommand_file {
    local ($login, $passwd, $db_connect, $perl_sql_file) = @_;
    local @cmd_file;
    local $cmd_string;
    local $eval_cmd;

    open(FILE, "$perl_sql_file") || die "$ME: Unable to open file '$perl_sql_file': $!\n";
    @cmd_file = <FILE>;
    close (FILE);

    $cmd_string = join('', @cmd_file);

    # substitute perl replacement variables

    $eval_cmd = eval "qq~$cmd_string~";

    exec_sqlcommand($login, $passwd, $db_connect, $eval_cmd);
}

#
# set_database_parameter()
#
sub set_database_parameter {
    local($login_parameter_value) = @_;
    if(!($login_parameter_value =~ /^$/)) {
	($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME) = split(/\/|\@/, $opt_l);
	# check if all parameters are defined
	if(($PIN_LOGIN =~ /^$/) || ($PIN_PASSWD =~ /^$/) || ($PIN_DBNAME =~ /^$/)) {
	    #print "$ME: ERROR: login parameter format: <login/password\@connection>\n";
	    #exit(1);
	}
    } else {
	print "Login: ";
	chomp($PIN_LOGIN = <STDIN>);

	system "stty -echo";
	print "Password: ";
	chomp($PIN_PASSWD = <STDIN>);
	print "\n";
	system "stty echo";

	print "Connection: ";
	chomp($PIN_DBNAME = <STDIN>);
    }
}

#
# get_queue_table_name()
#
sub get_queue_table_name {
    local ($login, $passwd, $db_connect, $queue_name) = @_;
    local ($queue_table) = "";
    local $strp_queue_name = substr $queue_name, index($queue_name,'.')+1;

    $sqlcommand =<<SQLPLUSENDPROC
set pagesize 0
SELECT queue_table FROM all_queues WHERE name = '$strp_queue_name';
SQLPLUSENDPROC
;
    exec_sqlcommand($login, $passwd, $db_connect, $sqlcommand);
    if ($sqlout =~ /no rows/) {
	return $queue_table;
    } else {
	($queue_table)=split (' ', $sqlout,99);
	return $queue_table;
    }
}

#
# drop()
#
sub drop {
    print "$ME: 1) drop $queue_name queue\n";
    parse_exec_sqlcommand_file($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,$DROP_SYNC_QUEUE);
    print $sqlout;

    # the payload type 'pin_event_ty' could used for the payload type definition of multiple
    # queues and can therefore only be deleted when the last queue is being removed. the same applies
    # for the 'acct_sync' package.

    exec_sqlcommand($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME,
		    "set serveroutput on size 1000000 \n
                     set pagesize 0 \n
                     SELECT name FROM user_queues WHERE queue_type = 'NORMAL_QUEUE';\n");

    if($sqlout =~ /no rows/) {
	print "$ME: 2) drop acct_sync package body\n";
	exec_sqlcommand($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,
			"DROP PACKAGE BODY acct_sync;\n");
	print "$ME: 3) drop acct_sync package\n";
	exec_sqlcommand($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,
			"DROP PACKAGE acct_sync;\n");
	print "$ME: 4) drop pin_event_ty payload type\n";
	exec_sqlcommand($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,
			"DROP TYPE pin_event_ty;\n");
	print "$ME: 5) drop deq_event_table_ty type\n";
	exec_sqlcommand($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,
			"DROP TYPE deq_event_table_ty;\n");
	print "$ME: 6) drop deq_event_ty type\n";
	exec_sqlcommand($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,
			"DROP TYPE deq_event_ty;\n");
    }
}

#
# create()
#
sub create {
# Check if the queue is being created with the default option <pin> in the .conf file
# The payload type of the event would be created accordingly

    if($primary_schema =~ /<pin>/) {
       $primary_schema_payload_type = "pin_event_ty";
    } else {
      $primary_schema_payload_type = "$primary_schema.pin_event_ty";
    }
    print "$ME: 1) create $queue_name queue\n";
    parse_exec_sqlcommand_file($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,$CREATE_SYNC_QUEUE);
    print $sqlout;
    print "$ME: 2) create acct_sync package\n";
    exec_sqlcommand_file($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,$CREATE_SYNC_PKG);
    print $sqlout;
    print "$ME: 3) create acct_sync package body\n";
    parse_exec_sqlcommand_file($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,$CREATE_SYNC_PKB);
    print $sqlout;
}

#
# report()
#
sub report {
    if($report_type =~ /summary/) {
	parse_exec_sqlcommand_file($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME, $EVENT_SUMMARY_REPORT);
	print $sqlout;
    } elsif ($report_type =~ /detail/) {
	parse_exec_sqlcommand_file($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME, $EVENT_DETAIL_REPORT);
	print $sqlout;
    } else {
	print "$ME: ERROR: report_type = $report_type unknown\n";
    }
}

#
# test()
#
sub test {
    print "$ME: 1) create self test PL/SQL procedures send_event() and receive_event()\n";
    exec_sqlcommand_file($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME, $CREATE_RECEIVE_EVENT);
    exec_sqlcommand_file($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME, $CREATE_SEND_EVENT);
    print "$ME: 2) create test events\n";
    exec_sqlcommand($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME,
		    "set serveroutput on size 1000000 \n
                     EXEC send_event('SHORT', 10, '$queue_name');\n");
    print $sqlout;
    exec_sqlcommand($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME,
		    "set serveroutput on size 1000000 \n
                     EXEC send_event('LONG', 10, '$queue_name');\n");
    print $sqlout;
    print "$ME: 3) receive test events\n";
    exec_sqlcommand($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME,
		    "set serveroutput on size 1000000 \n
                    EXEC receive_event_rc(20, '$queue_name', 'TAB.USER_DATA.EVENT_NAME = ''ShortTestEvent'' OR TAB.USER_DATA.EVENT_NAME = ''LongTestEvent''');\n");
    print $sqlout;
    print "$ME: 4) drop self test PL/SQL procedures send_event() and receive_event()\n";
    exec_sqlcommand($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,
		    "DROP PROCEDURE send_event;\n");
    exec_sqlcommand($PIN_LOGIN,$PIN_PASSWD,$PIN_DBNAME,
		    "DROP PROCEDURE receive_event_rc;\n");

    print "$ME: 5) event summary report\n";
    parse_exec_sqlcommand_file($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME, $EVENT_SUMMARY_REPORT);
    print $sqlout;
}

#
# list()
#
sub list {
    exec_sqlcommand($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME,
		    "set serveroutput on size 1000000 \n
                     set pagesize 0 \n
                     SELECT name FROM user_queues WHERE queue_type = 'NORMAL_QUEUE';\n");
    print $sqlout;
}

#
# usage()
#
sub usage {
    print "Sync Queue administration tool (IFS): Release 1.0 (10262003)\n";
    print "(c) Copyright 2003 - 2021 Oracle. All rights reserved.\n";
    print "usage: $ME \n";
    print "\tcreate [-q <queue_name> -t <queue_table> -r <retention_time> -s <storage_clause>] [-l < /\@db_alias >] \t create sync queue/package\n";
    print "\tdrop [-q <queue_name] [-l < /\@db_alias >] \t\t\t\t drop sync queue/package\n";
    print "\treport -r summary|detail [-q <queue_name>] [-l < /\@db_alias >] \t generate sync queue reports\n";
    print "\ttest [-q <queue_name>] [-l < /\@db_alias >] \t\t\t perform sync queue self test\n";
    print "\tlist [-l < /\@db_alias >] \t\t\t\t\t\t list all queues\n";
    print "\thelp \t\t\t\t\t\t\t\t\t\t short synopsis of commands\n";
    print "NOTE:  DB username/password will be read from Oracle Wallet\n";
}

## main

$cmd = @ARGV[0];

if(!($cmd =~ /(create|drop|report|help|list|test)/)) {
    usage();
    exit(1);
}

shift(@ARGV);

#
# This creates /tmp directory if it does not exist.
# This is for Windows environment.
#

mkdir($TEMPDIR);

#
# Filename suffix is created using the timestamp so that the temp files created are unique.
#
my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime;
$year += 1900;
$mon += 1;

my $datetime = sprintf "%04d%02d%02d%02d%02d%02d", $year, $mon, $mday, $hour, $min, $sec;
$file_suffix = "$$"."_$datetime";

if($cmd =~ /create/) {
    unless( getopts('q:t:l:r:s:')) {
	print "$ME: ERROR: $cmd [-q <queue_name> -t <queue_table> -r <retention_time> -s <storage_clause>] [-l < /\@db_alias >]\n";
	exit(1);
    }

    set_database_parameter($opt_l);

    if(!($opt_q =~ /^$/)) {
	$queue_name = $opt_q;
    } else {
	# default queue_name
	$queue_name = 'IFW_SYNC_QUEUE'
    }

    if(!($opt_t =~ /^$/)) {
	$queue_table = $opt_t;
    } else {
	# default queue_table
	$queue_table = 'IFW_SYNC';
    }

    # default value is contained in $CREATE_SYNC_QUEUE_CONF file
    if(!($opt_s =~ /^$/)) {
	$storage_clause = $opt_s;
    }

    # default value is contained in $CREATE_SYNC_QUEUE_CONF file
    if(!($opt_r =~ /^$/)) {
	$retention_time = $opt_r;
    }

    # check if either both on no parameter has been specified
    if(($opt_q =~ /^$/) xor ($opt_t =~ /^$/)) {
	print "$ME: ERROR: -q and -t parameters need to be specified together\n";
	print "$ME: ERROR: $cmd [-q <queue_name> -t <queue_name>]\n";
	exit(1);
    }

    print "queue_name = $queue_name\n";
    print "queue_table = $queue_table\n";
    print "retention_time = $retention_time\n";
    print "storage_clause = $storage_clause\n";

    create();

} elsif ($cmd =~ /drop/ || $cmd =~ /test/) {
    unless(getopts('q:l:')) {
	print "$ME: ERROR: $cmd [-q <queue_name>] [-l < /\@db_alias >]\n";
	exit(1);
    }

    set_database_parameter($opt_l);

    if(!($opt_q =~ /^$/)) {
	$queue_name = $opt_q;
    } else {
	# default queue_table
	$queue_name = 'IFW_SYNC_QUEUE';
    }

    $queue_table = get_queue_table_name($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME, $queue_name);
    if(!($queue_table =~ /^$/)) {
	print "queue_table = $queue_table\n";
    } else {
	print "$ME: ERROR: queue_name = $queue_name does not exist\n";
	exit(1);
    }

    print "queue_name = $queue_name\n";

    if($cmd =~ /test/) {
	test();
    } else {
	drop();
    }

} elsif ($cmd =~ /report/) {
    unless(getopts('r:q:l:')) {
	print "$ME: ERROR: report -r summary|detail [-q <queue_name>] [-l < /\@db_alias >]\n";
	exit(1);
    }

    set_database_parameter($opt_l);

    # mandatory parameter
    if(!($opt_r =~ /^$/)) {
	$report_type = $opt_r;
    } else {
	print "$ME: ERROR: mandatory parameter -r summary/detail is missing\n";
	print "$ME: ERROR: report -r summary|detail [-t <queue_table>]\n";
	exit(1);
    }
    # optional parameter
    if(!($opt_q =~ /^$/)) {
	$queue_name = $opt_q;
    } else {
	$queue_name = "IFW_SYNC_QUEUE";
    }

    $queue_table = get_queue_table_name($PIN_LOGIN, $PIN_PASSWD, $PIN_DBNAME, $queue_name);
    if(!($queue_table =~ /^$/)) {
	print "queue_table = $queue_table\n";
    } else {
	print "$ME: ERROR: queue_name = $queue_name does not exist\n";
	exit(1);
    }

    print "queue_name = $queue_name\n";

    report();

} elsif ($cmd =~ /help/) {
    usage();
} elsif ($cmd =~ /list/) {
    unless(getopts('l:')) {
	print "$ME: ERROR: list [-l < /\@db_alias >]\n";
	exit(1);
    }
    set_database_parameter($opt_l);
    list();
}
