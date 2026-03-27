#
#       @(#) % %
#
# Copyright (c) 1996, 2010, Oracle and/or its affiliates. All rights reserved. 
#      
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#

# This file is used by sql_loader tools and the db_run.pl scripts 
# contains common parameters and functions
#
use Math::BigInt;

$CONF_OWNER="pin";
$CONF_PASSWD="pin";
$SYS_OWNER="system";
$SYS_PASSWD="manager";
$CONF_DBNAME="oahu";
$ORACLE_VERSION="Oracle9";
$CONFIG_ITEMS=0;        # 0 -disabled, 1 - enabled for all services
$USER_PREFIX="user";
$USER_PASSWORD="password";
$LOGICAL_PARTITIONS=2;    # 0 and 1 is the same just 1 logical partition
$PARTITION_KEY_ENABLED="YES";  # If selected YES event poid will be created 
                              # as compound encypted KEY
                              # if set as HISTORIC poid will be encrypted to go
                              # in historic partition
                              # NO - means no encryption, no partitions

$MAX_POID_CMND1="select TO_CHAR(max(poid_id0) + 10000) from event_t";
$MAX_POID_CMND2="select TO_CHAR(max(poid_id0) + 10000 - 17592186044416) from event_t partition(PARTITION_HISTORIC)";
$MAX_POID_CMND3="select TO_CHAR(max(poid_id0) + 10000 - 17592186044416*floor(max(poid_id0)/17592186044416)) from event_t";
$MAX_POID_CMND=$MAX_POID_CMND1;
#=============================================================================
# check what operation system we are running on
# $^O will return name of OS
if ( $^O =~ /win/i )
{
# NT computer ( actually any windows operation system )
# Command to run sqlplus
$PIN_CONF_SQLPLUS     = "plus80 -s";
# For Windows NT Oracle 8 has a different batch sql processor
if ( $ORACLE_VERSION =~ /^Oracle8i$/i ) {
$PIN_CONF_SQLPLUS     = "sqlplus -s";
}

# Temporary directory to create files
$PIN_CONF_TEMPDIR     = "C:/temp";
$MOVE="move";
}
else
{
# UNIX assignment
# Command to run sqlplus
$PIN_CONF_SQLPLUS       = "sqlplus -s";

# Temporary directory to create files
$PIN_CONF_TEMPDIR       = "/tmp";
$MOVE="mv";
}

###############################################################################
# 2 functions below I stole from pin_init_utils
###############################################################################
# exec_sqlcommand()
#       input:
#               sql command(s)
###############################################################################
sub exec_sqlcommand {
	local ($user,$db_connect,$cmd) = @_;
	local ($status) = 0;
	local ($exitcode) = 0;
	local ($tmpfile) = "$PIN_CONF_TEMPDIR/pintmp$$.sql";
	# Create a temporary file with the sqlplus input.
	#
	open(TMPFILE, ">$tmpfile") || die "$ME: cannot create $tmpfile\n";
	print TMPFILE "$cmd";
	print TMPFILE "\nexit;\n";
	close(TMPFILE);

	if ( $user ne 'system' ) {
	$OWNER="$CONF_OWNER";
	$PASSWD="$CONF_PASSWD";
	} else {
	$OWNER="$SYS_OWNER";
	$PASSWD="$SYS_PASSWD";
	}
	#
	# Cheese 1: SQLPLUS gives a zero status back if the user/passwd is
	# wrong. So, instead of using system(), we need to capture the output
	# of SQLPLUS and parse it to see if there was an error.
	#
	$sqlout = `$PIN_CONF_SQLPLUS $OWNER/$PASSWD\@$db_connect < $tmpfile`;
	$exitcode = $?;
	$status = ($? >> 8);

#       printout("$sqlout");
        unlink "$tmpfile";

       if ($sqlout =~ m/ERROR: /) {
       printt("$ME: SQLPLUS failed (exitcode = $exitcode)\n");
       exit(1);
       }

       #
       # Cheese 2: on NT, we are getting the exit status as is in $?...
       # so, $status after right shifting becomes 0! So, check for
       # non-zero $? even though it is not "absolutely" right on unix.
       #
       if ($status || $exitcode) {
       print("$ME: $PIN_CONF_SQLPLUS failed with status $status\n");
       exit (1);
       }
}

###############################################################################
# printout
#       input:
#               string to be printed out
###############################################################################
sub printout {
	local ($outstr) = @_;

	syswrite STDOUT, $outstr, length($outstr);
	}

###############################################################################
# stat_process   ()
#       input: statistics from Oracle
#       output: print file    
###############################################################################
sub stat_process {
	local ($sfile,$ofile) = @_;
	#
	$SYSTABLE="v\$parameter";
	local ($tmpfile) = "$PIN_CONF_TEMPDIR/pintmp.sql";
	# Create a temporary file with the sqlplus input.
	#
	open(TMPFILE, ">$tmpfile") || die "$ME: cannot create $tmpfile\n";
	print TMPFILE "set pagesize 0\n";
	print TMPFILE "select value from $SYSTABLE where name='db_block_size';\n";
	print TMPFILE "\nexit;\n";
	close(TMPFILE);

	open(OFILE, ">$ofile") || die "$ME: cannot create $ofile\n";
	open(IFILE, "<$sfile") || die "$ME: cannot open $sfile\n";

print OFILE "-----------------------------------------------------------------------\n";
print OFILE "Table name                        Num Rows        Space (kB)        RowLen\n";
print OFILE "-----------------------------------------------------------------------\n";
	$total = 0.0;
	$Fld1 = 0;
	$Fld2 = $Fld3 = $Fld4 = $Fld5 = $Fld6 = $Fld7 = 0;
	$xx = 0.0;
	# read block size from system table 
	$block =`$PIN_CONF_SQLPLUS $SYS_OWNER/$SYS_PASSWD\@$CONF_DBNAME < $tmpfile`;
        unlink "$tmpfile";

line: 	while (<IFILE>) {

	($Fld1,$Fld2,$Fld3,$Fld4,$Fld5,$Fld6,$Fld7) = split(' ', $_, 9999);
	if (!(defined $Fld2 ) || ($Fld2 eq "rows") ) {
	next line;
	}

	if (/^-----/) {
	next line;
	}

	if (/^TABLE_NAME/) {
	  next line;
	}
	$xx = $Fld2 * $Fld3;
	if ($xx != 0) {
	$xx = $Fld3 * ($block - $Fld4);
	$xx = $xx / 1000.0;
	printf OFILE "%-30s  %9d        %10.1f     %4d\n", $Fld1, $Fld2, $xx,$Fld6;
	$total = $total + $xx;
	}


	}

print OFILE "------------------------------------------------------------\n";
printf OFILE "Total  used                                      %10.1f\n", $total;
print OFILE "------------------------------------------------------------\n";

	close(OFILE);
	close(IFILE);
}

###############################################################################
# encrypt_poid   ()
#       input: date
#       output: encrypting code which should be added to poid
###############################################################################
sub encrypt_poid {
	local ($create_time) = @_;
	local ($encode_str );
	#
	$enc_code = new Math::BigInt 0 ;
        if ( $PARTITION_KEY_ENABLED =~ /YES/i )
         {
           $enc_code = int($create_time/(3600*24)+1)*17592186044416 ;
           $MAX_POID_CMND=$MAX_POID_CMND3;
         }

        if ( $PARTITION_KEY_ENABLED =~ /HISTORIC/i )
         {
           $enc_code = 17592186044416 ;
           $MAX_POID_CMND=$MAX_POID_CMND2;
         }

	 $encode_str = sprintf ( "%.0f", $enc_code );

        return $encode_str;
}

1;


