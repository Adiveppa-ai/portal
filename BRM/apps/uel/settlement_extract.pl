#!/usr/bin/perl
#===============================================================================
#
# settlement_extract.pl
#
# Copyright (c) 2002, 2021, Oracle and/or its affiliates. All rights reserved. 
#
# This material is the confidential property of Oracle Corporation 
# or its licensors and may be used, reproduced, stored or transmitted
# only in accordance with a valid Oracle license or sublicense agreement.
#       
#
#===============================================================================
# Module Description:
#   Extracts one or more events from IC_DAILY to a text file to be loaded
#   into Infranet
#
# Notes:
# On HP you have to load the library libjava.sl before the script
# will work correctly.
# Here is one way that works.  Set the env variable LD_PRELOAD equal to the
# full path of the library:
# setenv LD_PRELOAD /u01/app/oracle/product/817/JRE/lib/PA_RISC/native_threads/libjava.sl
#===============================================================================

# Make sure they have at least Perl 5.004_00
require 5.00400;

use File::Spec;
use DBI;
use DBI qw(:sql_types);
use Getopt::Std;
require qw(./settlement_extract.values);

# ###############################################################
# These flags can be freely changed by the user
# ###############################################################
my $DEBUG = 1; # set to 1 to turn on debugging statements


# ###############################################################
# These variables are for the program - Please don't alter them.
# ###############################################################
$IC_DAILY_RESOURCE_NAME = ""; # only to get rid of warning
$IC_DAILY_ICPRODUCT     = ""; # only to get rid of warning

#############################################################################
# Sub          : main
# Description  : Starting point of the program
#--------------+-------------------------------------------------------------
# In           : -u          - (optional)  UNIQUE FILENAMES - If specified, 
#              :                           the output filename will be 
#              :                           created with an unique name so 
#              :                           it won't be overwritten.  This is 
#              :                           done by appending the current 
#              :                           date/time to the filename.
# In           : dbsn        - (mandatory) The Database connection string.
# In           : username    - (mandatory) The Database username
# In           : filepath    - (optional)  The path to create the file in.
#              :                           If this is blank, the current
#              :                           directory is used.
#--------------+-------------------------------------------------------------
# Returns      : 1 if an error occurs   or 0 if successfull
#############################################################################
$opt_u = "";
getopts("u");
#=============================================
# Check and assign the command line arguments
#=============================================
if ( ($#ARGV != 1) && ($#ARGV != 2) ) {
    print STDERR "usage: settlement_extract.pl [-u] <dbsn> <username> [<filepath>]\n\n";

    print STDERR "The -u argument is optional.  If specified, it will create an unique\n";
    print STDERR "filename in the format 'settlement_YYYY-MM-DD_HH-MM-SS.txt.\n\n";

    print STDERR "<dbsn> is the Perl Database Source Name. It is different for each database.\n";
    print STDERR "They all start with dbi: then the name of the driver.  For example,\n";
    print STDERR "the source name for Oracle is dbi:Oracle: and the name of the database\n";
    print STDERR "alias.  The source name for DB2 is dbi:DB2: and the\n";
    print STDERR "database name.  Please see the documentation for the different dbi modules\n";
    print STDERR "for the database specific source names.\n\n";

    print STDERR "<username> is the database username.\n\n";

    print STDERR "<filepath> is an optional argument.  If supplied, it is the location where\n";
    print STDERR "the script should write the file to.  If not supplied then\n";
    print STDERR "the current directory is used.\n\n";

    print STDERR "Example: settlement_extract.pl dbi:Oracle:orcl scott tiger \n";
    print STDERR "Example: settlement_extract.pl -u dbi:Oracle:orcl scott tiger /usr/home/files\n\n";

    exit(1);
}

my $dbsn = $ARGV[0];
my $user = $ARGV[1];
my $filepath    = "";

if ($#ARGV == 2) {
    $filepath = $ARGV[2];
}

my %attr = (
	PrintError  => 1,  # Log errors to the screen
	RaiseError  => 0,  # Don't die on errors
    AutoCommit  => 0,  # Don't auto commit deletes
    LongReadLen => 256000
);

if ($DEBUG) {
    print "dbsn=$dbsn; user=$user; pass=****; filepath=$filepath\n";
}


#=============================================
# Login to the database
#=============================================
print ("Connecting to database $dbsn; user=$user; pass=****\n");
my $dbh = DBI->connect($dbsn, '', '', \%attr) 
    or printErrAndExit("Can't connect to database $dbsn: ", $DBI::errstr);

my $tmpfname = "settlement";
if ($opt_u) {
    #Force unique filename
    print "Exporting with an unique filename.\n";
    $tmpfname .= "_" . getDateTimeString();
}
$tmpfname .= ".txt";

my $fname = "";
if ($filepath && ($filepath ne "") ) {
    $fname = File::Spec->catfile($filepath, $tmpfname);
} else {
    $fname = File::Spec->catfile(File::Spec->curdir(), $tmpfname);
}

my $today = getTodayStr();
if ($DEBUG) {
    print "Today is $today\n";
    print "Export filename=$fname\n";
}


#=============================================
# Create the SQL select count statement
#=============================================
my $tablename = "IC_DAILY";
my $sql_select_count = 
"SELECT COUNT (*) FROM $tablename
WHERE
    BILLRUN != " . $dbh->quote(-1) . "
AND
    EXPORTED  = 0
AND 
    ENTRY_TYPE = " . $dbh->quote(N);


#=============================================
# Create the SQL select statement
#=============================================
my $sql_select = 
"SELECT 
    PIN_LOGIN_ALIAS,
    " . getDBDate2StrFunction("DAY", $dbh->quote("YYYY-MM-DD"), $dbsn) . ",
    ICPRODUCT,
    BILLRUN,
    RESOURCE_NAME,
    BILL_DIRECTION,
    GLACCOUNT,
    TIMEMODEL,
    TIMEZONE,
    SERVICECODE,
    SERVICECLASS,
    IMPACT_CATEGORY,
    RUM,
    NETWORKMODEL,
    SWITCH,
    POI,
    TRUNK,
    NETWORK_OPERATOR,
    SEQUENCE_NUMBER,
    ENTRY_TYPE,
    ENTRY_TYPE_SEQ,
    NUM_ITEMS,
    QUANTITY,
    ROUNDED_QUANTITY,
    EVENTRATE_AMOUNT,
    EVENTBILL_AMOUNT,
    EVENTHOME_AMOUNT,
    BILLRATE_AMOUNT,
    BILLBILL_AMOUNT,
    BILLHOME_AMOUNT,
    RATEPLAN,
    EXPORTED,
    EXPORT_DATE
FROM
    $tablename
WHERE
    BILLRUN != " . $dbh->quote(-1) . "
AND
    EXPORTED  = 0
AND 
    ENTRY_TYPE = " . $dbh->quote(N) . "
FOR UPDATE";

if ($DEBUG) {
    print "$sql_select_count\n\n";
}

#=============================================
# Prepare the Statement the FETCH
#=============================================
my $sth = $dbh->prepare($sql_select_count)
    or printErrAndExit("Unable to prepare SQL statement:\n", $sql_select_count, "\n",
        $dbh->errstr(), "\n");

#=============================================
# Execute the FETCH
#=============================================
$sth->execute()
    or printErrAndExit("Unable to execute FETCH:\n", $sql_select_count, "\n");

my $rowCount = 0;
$rowCount = $sth->fetchrow_array();
$sth->finish();

if ($DEBUG) {
    print "Number of rows found->$rowCount\n\n";
}
my $exitCode = 0; # assume success for return.

#=============================================
# If we got back a count greater than zero
# from our select count(*) then process 
# the rows.
#=============================================
if ($rowCount > 0) {
    if ($DEBUG) {
        print "$sql_select\n\n";
    }
    #=============================================
    # Prepare the Statement the FETCH
    #=============================================
    my $sth = $dbh->prepare($sql_select)
        or printErrAndExit("Unable to prepare SQL statement:\n", $sql_select, "\n",
            $dbh->errstr(), "\n");

    #=============================================
    # Execute the FETCH
    #=============================================
    $sth->execute()
        or printErrAndExit("Unable to execute FETCH:\n", $sql_select, "\n");

    #=============================================
    # Create and Bind variable names for each
    # column
    #=============================================
    my $PIN_LOGIN_ALIAS         = "";
    my $DAY                     = "";
    my $ICPRODUCT               = "";
    my $BILLRUN                 = "";
    my $RESOURCE_NAME           = "";
    my $BILL_DIRECTION          = "";
    my $GLACCOUNT               = "";
    my $TIMEMODEL               = "";
    my $TIMEZONE                = "";
    my $SERVICECODE             = "";
    my $SERVICECLASS            = "";
    my $IMPACT_CATEGORY         = "";
    my $RUM                     = "";
    my $NETWORKMODEL            = "";
    my $SWITCH                  = "";
    my $POI                     = "";
    my $TRUNK                   = "";
    my $NETWORK_OPERATOR        = "";
    my $SEQUENCE_NUMBER         = "";
    my $ENTRY_TYPE              = "";
    my $ENTRY_TYPE_SEQ          = "";
    my $NUM_ITEMS               = "";
    my $QUANTITY                = "";
    my $ROUNDED_QUANTITY        = "";
    my $EVENTRATE_AMOUNT = "";
    my $EVENTBILL_AMOUNT = "";
    my $EVENTHOME_AMOUNT = "";
    my $BILLRATE_AMOUNT  = "";
    my $BILLBILL_AMOUNT  = "";
    my $BILLHOME_AMOUNT  = "";
    my $RATEPLAN                = "";
    my $EXPORTED                = "";
    my $EXPORT_DATE             = "";

    $sth->bind_col( 1, \$PIN_LOGIN_ALIAS);
    $sth->bind_col( 2, \$DAY);
    $sth->bind_col( 3, \$ICPRODUCT);
    $sth->bind_col( 4, \$BILLRUN);
    $sth->bind_col( 5, \$RESOURCE_NAME);
    $sth->bind_col( 6, \$BILL_DIRECTION);
    $sth->bind_col( 7, \$GLACCOUNT);
    $sth->bind_col( 8, \$TIMEMODEL);
    $sth->bind_col( 9, \$TIMEZONE);
    $sth->bind_col(10, \$SERVICECODE);
    $sth->bind_col(11, \$SERVICECLASS);
    $sth->bind_col(12, \$IMPACT_CATEGORY);
    $sth->bind_col(13, \$RUM);
    $sth->bind_col(14, \$NETWORKMODEL);
    $sth->bind_col(15, \$SWITCH);
    $sth->bind_col(16, \$POI);
    $sth->bind_col(17, \$TRUNK);
    $sth->bind_col(18, \$NETWORK_OPERATOR);
    $sth->bind_col(19, \$SEQUENCE_NUMBER);
    $sth->bind_col(20, \$ENTRY_TYPE);
    $sth->bind_col(21, \$ENTRY_TYPE_SEQ);
    $sth->bind_col(22, \$NUM_ITEMS);
    $sth->bind_col(23, \$QUANTITY);
    $sth->bind_col(24, \$ROUNDED_QUANTITY);
    $sth->bind_col(25, \$EVENTRATE_AMOUNT);
    $sth->bind_col(26, \$EVENTBILL_AMOUNT);
    $sth->bind_col(27, \$EVENTHOME_AMOUNT);
    $sth->bind_col(28, \$BILLRATE_AMOUNT);
    $sth->bind_col(29, \$BILLBILL_AMOUNT);
    $sth->bind_col(30, \$BILLHOME_AMOUNT);
    $sth->bind_col(31, \$RATEPLAN);
    $sth->bind_col(32, \$EXPORTED);
    $sth->bind_col(33, \$EXPORT_DATE);

    #=============================================
    # Open the output file and write to it
    #=============================================
    print ("Opening file $fname\n");
    open (TXTFILEHANDLE, ">$fname") 
        or printErrAndExit("Can't open file: ", $fname);

    #=============================================
    # Create File Header
    #=============================================
    print TXTFILEHANDLE "[LOGIN],";
    print TXTFILEHANDLE "[DATE],";
    print TXTFILEHANDLE "[IC_DAILY.ICPRODUCT],";
    print TXTFILEHANDLE "[IC_DAILY.BILLRUN],";
    print TXTFILEHANDLE "[PIN_INVOICE_DATA],";
    
    print TXTFILEHANDLE "[IC_DAILY.RESOURCE_NAME],";
    print TXTFILEHANDLE "[PIN_RESOURCE_ID],";
    print TXTFILEHANDLE "[IC_DAILY.ICPRODUCT],";
    print TXTFILEHANDLE "[IC_DAILY.BILL_DIRECTION],";
    print TXTFILEHANDLE "[PIN_PRODUCT_POID],";

    print TXTFILEHANDLE "[PIN_GL_ID],";
    print TXTFILEHANDLE "[IC_DAILY.TIMEMODEL],";
    print TXTFILEHANDLE "[IC_DAILY.TIMEZONE],";
    print TXTFILEHANDLE "[IC_DAILY.RATEPLAN],";
    print TXTFILEHANDLE "[PIN_RATE_TAG],";

    print TXTFILEHANDLE "[IC_DAILY.SERVICECODE],";
    print TXTFILEHANDLE "[IC_DAILY.SERVICECLASS],";
    print TXTFILEHANDLE "[IC_DAILY.IMPACT_CATEGORY],";
    print TXTFILEHANDLE "[IC_DAILY.RUM],";
    print TXTFILEHANDLE "[PIN_LINEAGE],";

    print TXTFILEHANDLE "[IC_DAILY.NETWORKMODEL],";
    print TXTFILEHANDLE "[IC_DAILY.SWITCH],";
    print TXTFILEHANDLE "[IC_DAILY.POI],";
    print TXTFILEHANDLE "[IC_DAILY.TRUNK],";
    print TXTFILEHANDLE "[PIN_NODE_LOCATION],";

    print TXTFILEHANDLE "[IC_DAILY.NETWORK_OPERATOR],";
    print TXTFILEHANDLE "[IC_DAILY.SEQUENCE_NUMBER],";
    print TXTFILEHANDLE "[IC_DAILY.ENTRY_TYPE],";
    print TXTFILEHANDLE "[IC_DAILY.ENTRY_TYPE_SEQ],";
    print TXTFILEHANDLE "[IC_DAILY.NUM_ITEMS],";

    print TXTFILEHANDLE "[IC_DAILY.QUANTITY],";
    print TXTFILEHANDLE "[IC_DAILY.ROUNDED_QUANTITY],";
    print TXTFILEHANDLE "[IC_DAILY.BILLBILL_AMOUNT],";
    print TXTFILEHANDLE "[IC_DAILY.EVENTBILL_AMOUNT],";
    print TXTFILEHANDLE "[IC_DAILY.EVENTRATE_AMOUNT],";

    print TXTFILEHANDLE "[IC_DAILY.EVENTHOME_AMOUNT],";
    print TXTFILEHANDLE "[IC_DAILY.BILLRATE_AMOUNT],";
    print TXTFILEHANDLE "[IC_DAILY.BILLHOME_AMOUNT],";
    print TXTFILEHANDLE "[CHARGED_AMOUNT]";
    print TXTFILEHANDLE "\n";

    #=============================================
    # Fetch all the rows from IC_DAILY table
    # and write them to the txt file.
    #=============================================
    print ("Fetching rows from table $tablename\n");
    my $rowsFound = 0;
    my $temp = "";
    my $charged_amount = 0;
    while (my $row = $sth->fetch) {
        
        #=============================================
        # Calculate the CHARGE AMOUNT
        #=============================================
        if ($BILLBILL_AMOUNT) {
            $charged_amount = $BILLBILL_AMOUNT;
        } elsif ($EVENTBILL_AMOUNT) {
            $charged_amount = $EVENTBILL_AMOUNT;
        } elsif ($EVENTRATE_AMOUNT) {
            $charged_amount = $EVENTRATE_AMOUNT;
        } else {
            $charged_amount = 0;
        }

        #=============================================
        # For incoming bills we flip the CHARGE AMOUNT
	# by subtracting from zero.
        #=============================================
	if ($BILL_DIRECTION == "I") {
		$charged_amount = 0 - ($charged_amount);
	}

        print "."; #some indication that the program is working...

        print TXTFILEHANDLE formatOutputStr($PIN_LOGIN_ALIAS) . ",";
        print TXTFILEHANDLE formatOutputStr($DAY) . ",";
        print TXTFILEHANDLE formatOutputStr($ICPRODUCT) . ",";
        print TXTFILEHANDLE formatOutputStr($BILLRUN) . ",";
        print TXTFILEHANDLE formatOutputStr("$ICPRODUCT, $BILLRUN") . ",";

        print TXTFILEHANDLE formatOutputStr($RESOURCE_NAME) . ",";
        print TXTFILEHANDLE formatOutputStr($IC_DAILY_RESOURCE_NAME{"$RESOURCE_NAME"}) . ",";
        print TXTFILEHANDLE formatOutputStr($ICPRODUCT) . ",";
        print TXTFILEHANDLE formatOutputStr($BILL_DIRECTION) . ",";
        print TXTFILEHANDLE formatOutputStr($IC_DAILY_ICPRODUCT{"$ICPRODUCT$BILL_DIRECTION"}) . ",";

        print TXTFILEHANDLE formatOutputStr($GLACCOUNT) . ",";
        print TXTFILEHANDLE formatOutputStr($TIMEMODEL) . ",";
        print TXTFILEHANDLE formatOutputStr($TIMEZONE) . ",";
        print TXTFILEHANDLE formatOutputStr($RATEPLAN) . ",";
        print TXTFILEHANDLE formatOutputStr("$TIMEMODEL, $TIMEZONE, $RATEPLAN") . ",";

        print TXTFILEHANDLE formatOutputStr($SERVICECODE) . ",";
        print TXTFILEHANDLE formatOutputStr($SERVICECLASS) . ",";
        print TXTFILEHANDLE formatOutputStr($IMPACT_CATEGORY) . ",";
        print TXTFILEHANDLE formatOutputStr($RUM) . ",";
        print TXTFILEHANDLE formatOutputStr("$SERVICECODE, $SERVICECLASS, $IMPACT_CATEGORY, $RESOURCE_NAME, $RUM") . ",";

        print TXTFILEHANDLE formatOutputStr($NETWORKMODEL) . ",";
        print TXTFILEHANDLE formatOutputStr($SWITCH) . ",";
        print TXTFILEHANDLE formatOutputStr($POI) . ",";
        print TXTFILEHANDLE formatOutputStr($TRUNK) . ",";
        print TXTFILEHANDLE formatOutputStr("$NETWORKMODEL, $SWITCH, $POI, $TRUNK") . ",";

        print TXTFILEHANDLE formatOutputStr($NETWORK_OPERATOR) . ",";
        print TXTFILEHANDLE formatOutputStr($SEQUENCE_NUMBER) . ",";
        print TXTFILEHANDLE formatOutputStr($ENTRY_TYPE) . ",";
        print TXTFILEHANDLE formatOutputStr($ENTRY_TYPE_SEQ) . ",";
        print TXTFILEHANDLE formatOutputStr($NUM_ITEMS) . ",";

        print TXTFILEHANDLE formatOutputStr($QUANTITY) . ",";
        print TXTFILEHANDLE formatOutputStr($ROUNDED_QUANTITY) . ",";
        print TXTFILEHANDLE formatOutputStr($BILLBILL_AMOUNT) . ",";
        print TXTFILEHANDLE formatOutputStr($EVENTBILL_AMOUNT) . ",";
        print TXTFILEHANDLE formatOutputStr($EVENTRATE_AMOUNT) . ",";

        print TXTFILEHANDLE formatOutputStr($EVENTHOME_AMOUNT) . ",";
        print TXTFILEHANDLE formatOutputStr($BILLRATE_AMOUNT) . ",";
        print TXTFILEHANDLE formatOutputStr($BILLHOME_AMOUNT) . ",";
        print TXTFILEHANDLE formatOutputStr($charged_amount);
        print TXTFILEHANDLE "\n";

        $rowsFound ++;
    }

    if ($rowsFound > 0) {
        #=============================================
        # Now update the Export Date on all
        # the rows we just processed
        #=============================================
        print ("\nUpdating the Export Date on the extracted rows.\n");

        #=============================================
        # Prepare the UPDATE statement
        #=============================================
        $sth->finish();
        my $sql_update = "UPDATE $tablename \n";
        $sql_update   .= "  SET EXPORTED = 1, \n";
        $sql_update   .= "  EXPORT_DATE = ";
        $sql_update   .= getDBStr2DateFunction($dbh->quote(getTodayStr()), $dbh->quote("YYYY-MM-DD"), $dbsn) . " \n";
        $sql_update   .= "WHERE BILLRUN != " . $dbh->quote(-1) . "\n  AND EXPORTED = 0 \n  AND ";
        $sql_update   .= "ENTRY_TYPE = " . $dbh->quote(N);


        #=============================================
        # Prepare the Statement the FETCH
        #=============================================
        $sth = $dbh->prepare($sql_update)
            or printErrAndExit("Unable to prepare SQL statement:\n", $sql_update, "\n",
                $dbh->errstr(), "\n");


        if ($DEBUG) {
            print "$sql_update\n\n";
        }

        #=============================================
        # Execute the UPDATE
        #=============================================
        if ( $sth->execute() ) {
            #=============================================
            # Commit
            #=============================================
            print "Updated $rowsFound row(s).\n";
            print ("Committing transaction.\n");
            unless ( $dbh->commit() ) {
                $exitCode = 1; # if commit fails, we didn't update successfully.
                print STDERR "Commit to database failed: " . $dbh->errstr() . "\n";
            }
        } else {
            printErrAndRollback("Unable to execute SQL statement:\n", $sql_update, "\n",
                $dbh->errstr(), "\n");
            $exitCode = 1; # We didn't update successfully.
        }
    }
    $sth->finish();
} else {
    print "No rows found in table $tablename\n";
}


#=============================================
# Logoff
#=============================================
print ("\nDisconnecting from database $dbsn\n");
$dbh->disconnect()
    	or warn "Disconnect from database $dbsn failed: ",$dbh->errstr(), "\n";

exit($exitCode);

# ################## END OF SCRIPT MAIN ###############################


#############################################################################
# Sub          : PrintError
# Description  : Prints an error message to STDERR,
#--------------+-------------------------------------------------------------
# In           : An array of values to print to STDERR
#--------------+-------------------------------------------------------------
# Returns      : none - 
#############################################################################
sub PrintError {
    print STDERR "ERROR: ";
    for my $str (@_) {
        print STDERR $str;
    }
    print STDERR "\n";
}

#############################################################################
# Sub          : printErrAndExit
# Description  : Prints an error message to STDERR and exit's the program.
#--------------+-------------------------------------------------------------
# In           : An array of values to print to STDERR
#--------------+-------------------------------------------------------------
# Returns      : none - Exits the progam with exit code 1
#############################################################################
sub printErrAndExit {
    PrintError(@_);
    exit (1);
}

#############################################################################
# Sub          : printErrAndRollback
# Description  : Prints an error message to STDERR, and rolls back 
#              : any changes to the database
#--------------+-------------------------------------------------------------
# In           : An array of values to print to STDERR
#--------------+-------------------------------------------------------------
# Returns      : none - 
#############################################################################
sub printErrAndRollback {
    
    PrintError(@_);

    if ( defined($dbh) ) {
        print "Rolling back transaction\n";
        #=============================================
        # Rollback
        #=============================================
        $dbh->rollback()
           or warn "Transaction rollback failed: ",$dbh->errstr(), "\n";
    }
}

#############################################################################
# Sub          : getDateTimeString
# Description  : Returns a string representing the current date and time
#              : in localtime format.  The date will be in ISO-8601
#              : format (YYYY-MM-DD) and the time will be in the format
#              : (HH-MM-SS).
#              : See-> http://perl.about.com/library/weekly/aa051601b.htm
#              : See ->http://www.cs.tut.fi/~jkorpela/iso8601.html
#--------------+-------------------------------------------------------------
# Returns      : A date string in the format YYYY-MM-DD-HH-MM-SS
#############################################################################
sub getDateTimeString {
    my $retstr = "";

    # Get the all the values for current time
    (my $Second,  my $Minute,    my $Hour, my $Day, my $Month, my $Year, 
     my $WeekDay, my $DayOfYear, my $IsDST) = localtime(time);
    
    $retstr = sprintf "%04d-%02d-%02d_%02d-%02d-%02d",
        1900+$Year, $Month+1, $Day, $Hour, $Minute, $Second;

    return $retstr;
}

#############################################################################
# Sub          : getTodayStr
# Description  : Returns a string representing the current date in the
#              : format (YYYY-MM-DD).
#--------------+-------------------------------------------------------------
# Returns      : A date string in the format YYYY-MM-DD
#############################################################################
sub getTodayStr {
    my $retstr = "";
                    
    # Get the all the values for current date/time
    (my $Second,  my $Minute,    my $Hour, my $Day, my $Month, my $Year, 
     my $WeekDay, my $DayOfYear, my $IsDST) = localtime(time);
    
    $retstr = sprintf "%04d-%02d-%02d", 1900+$Year, $Month+1, $Day;

    return $retstr;
}

#############################################################################
# Sub          : getDBDate2StrFunction
# Description  : Returns a string representing the database specific
#              : function to return a date as a string from the database
#              : See ->http://www.thefillmoregroup.com/sqlfunctions.cfm#date
#--------------+-------------------------------------------------------------
# In           : The Column name
# In           : The Date format (wrapped in database specific quotes)
# In           : The Connection string
#--------------+-------------------------------------------------------------
# Returns      : A string with the date specific function
#############################################################################
sub getDBDate2StrFunction {
    my $db_Column = shift;
    my $db_Format = shift;
    my $db_type   = shift;
    my $retstr    = "";

    if ($db_type =~ m/dbi:Oracle/) { 
        $retstr = "TO_CHAR($db_Column, $db_Format)";
    } elsif ($db_type =~ m/dbi:DB2/) {
        $retstr = "DATE_TO($db_Column, $db_Format)";
    } else {
        $retstr = "$db_Column";
    }
    
    return $retstr;
}

#############################################################################
# Sub          : getDBStr2DateFunction
# Description  : Returns a string representing the database specific
#              : function to write a date as a string to the database
#--------------+-------------------------------------------------------------
# In           : A Date String (wrapped in database specific quotes)
# In           : The Date format (wrapped in database specific quotes)
# In           : The Connection string
#--------------+-------------------------------------------------------------
# Returns      : A string with the date specific function
#############################################################################
sub getDBStr2DateFunction {
    my $db_Data   = shift;
    my $db_Format = shift;
    my $db_type   = shift;
    my $retstr    = "";

    if ($db_type =~ m/dbi:Oracle/) { 
        $retstr = "TO_DATE($db_Data, $db_Format)";
    } elsif ($db_type =~ m/dbi:DB2/) {
        $retstr = "TO_DATE($db_Data, $db_Format)";
    } else {
        $retstr = "$db_Data";
    }
    
    return $retstr;
}

#############################################################################
# Sub          : formatOutputStr
# Description  : Formats a string with wrapping quotes.  Also takes care of
#              : empty strings.
#--------------+-------------------------------------------------------------
# In           : A string to format.
#--------------+-------------------------------------------------------------
# Returns      : A quote wrapped string.
#############################################################################
sub formatOutputStr {
    my $data   = "";
    my $retval = "";

    $data = shift;

    $retval = '"';
    if (defined $data) {
        $retval .= "$data";
    }
    $retval .= '"';
    
    return $retval;
}
