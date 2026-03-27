#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#
#
# Copyright (c) 2007 , 2024, Oracle and/or its affiliates. 
#
# This material is the confidential property of Oracle Corporation or
# its licensors and may be used, reproduced, stored or transmitted only
# in accordance with a valid Oracle license or sublicense agreement.
#
# auditSize Perl module for the data extraction of the size of the audit tables
# specified in pin_db_alert.conf in terms of number of rows in those tables.

package auditSize;
use aes;
use Env;
use Cwd;
require readConfigUtility;

sub run(\@) {
print "\n#######################################################################################";
print "\n########									########";
print "\n########		AUDIT_SIZE DATA EXTRACTION MODULE			########";
print "\n########                                                                       ########";
print "\n#######################################################################################";
print "\n";
my $myUser = readConfigUtility::readConfigValue('DB_USER');
my $myPassword=readConfigUtility::readConfigValue('DB_PASSWD');
$PSWD = psiu_perl_decrypt_pw($myPassword);
my @ArgumentList=();
my @myArguments=();
$def_aud_tab_names = readConfigUtility::readConfigValue('DEFAULT_AUDIT_TABLES');
@ArgumentList = split(/\,/,$def_aud_tab_names);
@myArguments= @_;
$myDefaultCount=$#ArgumentList;
for $i (0 .. $#myArguments) {
  $ArgumentList[$i+1+$myDefaultCount]=$myArguments[$i];
}
print "\n";
my $myOS= $ENV{'OS'};
my $cmd;
$cmd = "mv auditSize_AuditTableSize.out auditSize_AuditTableSize.out"."."."back 2> /dev/null";
system("$cmd"); 
for $i (0..$#ArgumentList) {
	$sqlcmd = "sqlplus -L -s $myUser"."/"."$PSWD"."@"."$ORACLE_SID"." @"."./auditSize_AuditTableSize.sql $ArgumentList[$i] >> auditSize_AuditTableSize.out";
	system("$sqlcmd");
	}
return 0;
}
1;
