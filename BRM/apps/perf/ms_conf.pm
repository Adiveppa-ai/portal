#
#	@(#) % %
#       
#       Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#

# This file is used by sql_loader and the db_stat.pl scripts which are 
# used for creating SS7 DB and collecting statistics   from MSSQLServer DB
# file contains also some commonly used  functions
#

$CONF_OWNER="pin";
$CONF_PASSWD="pin";
$SYS_OWNER="sa";
$SYS_PASSWD="";
$CONF_SERVER="larry";
$CONF_DBNAME="demo";
$PIN_CONF_TEMPDIR="C:/temp";
###############################################################################
# exec_sqlcommand()
#       input:
#               sql command(s)
###############################################################################
sub exec_sqlcommand {
	local ($user,$infile,$resfile) = @_;
	local ($tmpfile) = "$PIN_CONF_TEMPDIR/pintmp.sql";

	if ( $user ne 'system' ) {
	$PIN_PRINT_FLAG     = "-h-1 ";
	$PIN_CONF_SQLPLUS     = "isql ";
	$OWNER="$CONF_OWNER";
	$PASSWD="$CONF_PASSWD";
	} else {
	$PIN_PRINT_FLAG     = " ";
	$PIN_CONF_SQLPLUS     = "isql ";
	$OWNER="$CONF_OWNER";
	$PASSWD="$CONF_PASSWD";
	}
	#
	#
	`$PIN_CONF_SQLPLUS -U $OWNER -P $PASSWD -d $CONF_DBNAME -S $CONF_SERVER -i $infile -o $tmpfile -w 256 -n $PIN_PRINT_FLAG`;


       #
       # trim output from MSSQL server
       #
	open(IFILE, "<$tmpfile") || die "$ME: cannot open $tmpfile\n";
	open(OFILE, ">$resfile") || die "$ME: cannot open $resfile\n";
line: 	while (<IFILE>) {
        $_=~s/ *\n$/\n/;
	if (/^\n/) {
	next line;
	}
	if (/^-----/) {
	next line;
	}
	if (/affected/) {
	next line;
	}
	printf OFILE "%s", $_;
	}
	close(IFILE);
	close(OFILE);
        unlink "$tmpfile";
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

