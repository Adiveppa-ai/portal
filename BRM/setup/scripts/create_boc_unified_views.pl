#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#
#==================================================================== 
#
# create_boc_unified_views.pl
# 
# Copyright (c) 2021, Oracle and/or its affiliates. All rights reserved.
# This material is the confidential property of Oracle Corporation
# or its licensors and may be used, reproduced, stored
# or transmitted only in accordance with a valid Oracle license or
# sublicense agreement.
#
#==================================================================== 

require "./pin_functions.pl";
require "../pin_setup.values";
require "./pin_oracle_functions.pl";
require "./pin_multidb_utils";
require "./pin_multidb.conf";

if(defined($ENV{'DOCKER'}) && $ENV{'DOCKER'} eq '1') {
        require "./pin_cmp_dm_db.pl";
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

#
# File into which output of SQL query is written into #
#
local ( $PIN_TEMP_DIR ) = $PIN_TEMP_DIR;
my ( $tmpFile ) = $PIN_TEMP_DIR."/tmp.out";

#==================================================
# Setting the primary schema login details in 
# a hash which is understood by ExecuteSQL_Statement 
# subroutine 
#==================================================
%PRIMARY_DB = ("user", $PIN_MD_PRIMARY_OWNER, "password", $PIN_MD_PRIMARY_PASSWD, "alias", $PIN_MD_PRIMARY_DBNAME);

my @tables = ("JOB_T","JOB_TEMPLATE_T","JOB_HISTORY_VW","JOB_TEMPLATE_COLL_AC_INFO_T","PROC_AUD_T",
			"PROC_AUD_BILL_T","PROC_AUD_PRICE_SYNC_T","JOB_BOC_T","REV_ASSURANCE_VW");
my $len = @tables;

my @f_tables = ("EVENT_T","ACCOUNT_T","ACCOUNT_NAMEINFO_T","EVENT_BILLING_VALID_T","EVENT_BILLING_CHARGE_T",
				"EVENT_PAYMENT_BATCH_T","TRANS_TYPE1_LEVEL0_VW","TRANS_TYPE2_LEVEL0_VW",
				"TRANS_TYPE2_LEVEL1_VW","TRANS_TYPE3_LEVEL0_VW");
my $f_len = @f_tables;

print "\n\nGranting permissions for tables specific to primary schema!!\n\n";

for $i ($PIN_MD_SECONDARY_START_INST..$PIN_MD_SECONDARY_END_INST) {

	for($idx = 1; $idx < $len; $idx = $idx + 1) {
	        $result = &ExecuteSQL_Statement("GRANT SELECT ON $tables[$idx] TO $PIN_MD_SECONDARY_OWNER[$i] WITH GRANT OPTION;", 
								FALSE, FALSE, %PRIMARY_DB);
		&CheckResult($tmpFile, %PRIMARY_DB);
	}

}

print "\n\nGRANTED!!!\n\n";

print "\n\nGranting permissions for tables required for job_history and failed transactions view!!\n\n";

$ENV{PRIMARY_SCHEMA_USERNAME_TEMP} = 1;
for $i ($PIN_MD_SECONDARY_START_INST..$PIN_MD_SECONDARY_END_INST) {
	#==================================================
	# Setting the secondary schema login details in
	# a hash for each of the secondary schemas which is 
	# understood by ExecuteSQL_Statement subroutine
	#==================================================
	%SECONDARY_DB = ("user", $PIN_MD_SECONDARY_OWNER[$i], "password", $PIN_MD_SECONDARY_PASSWD[$i], "alias", $PIN_MD_PRIMARY_DBNAME); 

	#==========================================
	# For History data
	#=========================================
	
	for($idx = 0; $idx < $len; $idx = $idx + 1) {
		$result = &ExecuteSQL_Statement("GRANT SELECT ON $tables[$idx] TO $PIN_MD_PRIMARY_OWNER;", FALSE, FALSE, %SECONDARY_DB);
		&CheckResult($tmpFile, %SECONDARY_DB);
	}
	
	#==========================================
	# For Failed transaction
	#==========================================

	for($f_idx = 0; $f_idx < $f_len; $f_idx = $f_idx + 1) {
		$result = &ExecuteSQL_Statement("GRANT SELECT ON $f_tables[$f_idx] TO $PIN_MD_PRIMARY_OWNER;", FALSE, FALSE, %SECONDARY_DB);
		&CheckResult($tmpFile, %SECONDARY_DB);
	}
}
$ENV{PRIMARY_SCHEMA_USERNAME_TEMP} = 0;

print "\n\nGRANTED!!!\n\n";

print "\n\nCreating unified view!!\n";

@unified_tables = (['UNIFIED_JOB_HISTORY_VW','JOB_HISTORY_VW'],
		   ['UNIFIED_JOB_TEMPLATE_COLL_VW','JOB_TEMPLATE_COLL_AC_INFO_T'],
		   ['UNIFIED_REV_ASSURANCE_VW','REV_ASSURANCE_VW'],
		   ['UNIFIED_TTYPE1_LEVEL0_VW','TRANS_TYPE1_LEVEL0_VW'],
		   ['UNIFIED_TTYPE2_LEVEL0_VW','TRANS_TYPE2_LEVEL0_VW'],
		   ['UNIFIED_TTYPE2_LEVEL1_VW','TRANS_TYPE2_LEVEL1_VW'],
		   ['UNIFIED_TTYPE3_LEVEL0_VW','TRANS_TYPE3_LEVEL0_VW']);
my $u_len = @unified_tables;
my @unified_view;

for ( $u_idx = 0; $u_idx < $u_len ; $u_idx = $u_idx + 1){				
	$job_view = "CREATE OR REPLACE VIEW $unified_tables[$u_idx][0] AS SELECT * FROM $PIN_MD_PRIMARY_OWNER.$unified_tables[$u_idx][1] ";
	for $i ($PIN_MD_SECONDARY_START_INST..$PIN_MD_SECONDARY_END_INST) {
			$job_view = $job_view." UNION SELECT * FROM $PIN_MD_SECONDARY_OWNER[$i].$unified_tables[$u_idx][1]";
	}
	$unified_view[$u_idx] = $job_view.";";
}

$full_view = $job_view.";"."\n";

for ( $u_idx = 0; $u_idx < $u_len-1 ; $u_idx = $u_idx + 1){
	$full_view = $full_view.$unified_view[$u_idx]."\n";
}

$result = &ExecuteSQL_Statement($full_view, FALSE, FALSE, %PRIMARY_DB);
&CheckResult($tmpFile, %PRIMARY_DB);

print "\n\nCREATED!!!\n\n";

#==========================================
# Load the tmp.sql
#==========================================
$file = "$PIN_TEMP_DIR/tmp.sql";
print " Executing $file\n";
&Parse_and_Execute ($file, 0, $PIN_MD_PRIMARY_OWNER, $PIN_MD_PRIMARY_PASSWD, $PIN_MD_PRIMARY_DBNAME, $PIN_MD_PRIMARY_SQLHOST);

#===========================================================================
#  This function looks for Oracle Errors in the output from a SQL statement,
#  which is passed to this function as the argument '$tmpFile'.
#
#  If no errors are found, 0 is returned.
#  For errors, an error message will be displayed, then the function exits.
#
#  Arguments:
#    $tmpFile  - file which contains the SQL statement output
#    %DB       - local copy of %DB.
#  Returns:  0 if no errors
#            exit(2) if major error
#============================================================================
sub CheckResult {
	local ( $tempFile ) = shift( @_ ); 
	local ( %DB ) = @_;

	local ( $Error ) = "NONE";

	open( TMPFILE, "<$tempFile " ) || die "\n\nCannot read $tmpfile\n\n";
	while( $ReadString = <TMPFILE> ) {
		if ( $ReadString =~ /ORA-([\d]*):.*/ ) {
			$Error = $1;
			last;
		}
	}


	#
	# If no Oracle errors, then return now
	#
	if ( $Error eq "NONE" ) {
		return 0;
	}

	#
	# Process any Oracle errors found in the SQL statement output file
	#
	if ( $Error eq "12154" ) {
		print "\n\n$DB{'alias'} is not a valid service name for this machine."; 
		print "\nPlease make sure you have created this entry in the TNSNAMES.ORA file."; 
		print "\nFor further details refer to $tmpFile\n\n";
		exit( 2 );
	}
	elsif ( $Error eq "01017" ) {
		print "\n\nThe login credentials you have supplied are not valid.";
		print "\nPlease make sure you entered the correct 'user', 'password', and 'alias'.";
		print "\nFor further details refer to $tmpFile\n\n";
		exit( 2 );
	}
	elsif ( $Error eq "00942" ) {
		print "\n\nTable or view does not exist. For further details refer to $tmpFile\n\n";
		exit ( 2 );
	}
	else {
		print "\n\nUnknown error. For further details refer to $tmpFile\n\n";
		exit ( 2 );
	}

	close( TMPFILE );
	return 0;
}
