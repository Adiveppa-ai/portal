#
#	@(#) % %
#       
# Copyright (c) 1996, 2015, Oracle and/or its affiliates. All rights reserved.
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#

use Getopt::Std;
require "..\ms_conf.pm";
######################################################################
## Configuration stuff
######################################################################
#--------------------------------------------
# end of configuration section
#--------------------------------------------
#=============================================================================
# Temporary directory to create files
$PIN_CONF_TEMPDIR     = "C:\\temp";

($ME = $0) =~ s,.*/,,;

#
# Parse command line flags.
# n - how many rows process from DB ( mandatory )
# f - name of file to create ( mandatory )
# s - options ( all, md5, clear, ipt )
# o - origination
# d - destination
# r - repeating

getopts('n:f:o:d:r:s:') || &usage("");

if (!(defined $opt_n || defined $opt_f )) {
	&usage("");
}

if ((defined $opt_s ) && ( $opt_s eq "ipt") ) {
	$option = 1;   # create file for caar matrix
} else {
	$option = 0;   # create file for admin_load
}
if ((defined $opt_s )) {
	$selection = $opt_s ;
} else {
	$selection = "clear";
}

if ((defined $opt_o )) {
	$origin = $opt_o ;
} else {
	$origin = 1111111;
}

if ((defined $opt_d )) {
	$dest = $opt_d ;
} else {
	$dest = $origin;
}

if ((defined $opt_r )) {
	$repeat = $opt_r ;
} else {
	$repeat = 5;
}

if ( $option == 1 ) {
$sql_cmnd =<<SQLPLUSEND 
-- set up cursors to fetch data from service_t
--
SET NOCOUNT ON
DECLARE \@value1 char(255)
DECLARE \@value2 char(255)
DECLARE \@count int

declare db_id cursor for
	select RATE_CATEGORY,IMPACT_CATEGORY from config_impact_categories_t
BEGIN
	-- db no
	select \@count = 0
	open db_id
 WHILE ( \@count < $opt_n and \@\@FETCH_STATUS = 0 )
	BEGIN
		fetch next from db_id into \@value1, \@value2
		print RTRIM(\@value1) + ':' + RTRIM(\@value2) + ':'
		SELECT \@count        = \@count + 1
 	END
	close db_id
	deallocate db_id

END
go

SQLPLUSEND
;

} else {
$sql_cmnd =<<SQLPLUSEND 
-- set up cursors to fetch data from service_t
--
SET NOCOUNT ON
DECLARE \@value1 char(255)
DECLARE \@value2 char(255)
DECLARE \@count int

declare db_id cursor for
	select login,passwd from service_t 

BEGIN
	-- db no
	select \@count = 0
	open db_id
 WHILE ( \@count < $opt_n and \@\@FETCH_STATUS = 0 )
	BEGIN
		fetch next from db_id into \@value1, \@value2
		print RTRIM(\@value1) + ':' + RTRIM(\@value2) + ':'
		SELECT \@count        = \@count + 1
 	END
	close db_id
	deallocate db_id

END
go
SQLPLUSEND
;

}

##################################################
	open(OFILE, ">exfile") || die "$ME: cannot open $exfile\n";
	printf OFILE "%s", $sql_cmnd;
	close(OFILE);

##################################################
#  execute prepared file
#################################################
`isql -n -U $CONF_OWNER -P $CONF_PASSWD -d $CONF_DBNAME -S $CONF_SERVER -i exfile -o outfile`;

# convert spool file to output

	open(INFILE, "<outfile") || die "$ME: cannot read outfile\n";
	open(OUTFILE, ">$opt_f") || die "$ME: cannot create $opt_f\n";

	$j = 0;
line:   while (<INFILE>) {
        	($value1,$value2) = split(':', $_, 9999);
		if ($value2 eq "") {
			next line;
		}
		if ( $option == 0 ) {
			($prefix,$clear_passwd)=split('\|', $value2, 9999);
	       		 if ((defined $opt_s ) && ( $opt_s ne "all") && 
		  		( $opt_s ne $prefix)) {
				     next line;
	  			}
        		printf OUTFILE "%s:%s:\n",$value1,$clear_passwd;
        	} else {
			printf OUTFILE "%d:%d:1:%s:%s\n",$origin+$j/$repeat,
				$dest+$j%$repeat,$value1,$value2;
			$j = $j +1;

		}
	}
	close(INFILE);
	close(OUTFILE);
	unlink "outfile";

print "***************************************************************\n";
printf " File $opt_f created. \n";
print "***************************************************************\n";

1;

################################################################################
# usage:  Print usage message and exit.
# n - how many lines in file to create
# f - name of file to create
# s - options ( all, md5, clear, ipt )
# o - origination
# d - destination
# r - repeating
#
################################################################################
sub usage {
	print(<STDERR>, @_);

	print(<STDERR>, "Usage: $ME [options] \n");
	print(<STDERR>, "    -n       how many rows read from DB");
        print(<STDERR>, "    -f       name of file to create \n");
        print(<STDERR>, "    -s       options ( all, md5, clear, ipt )\n");
        print(<STDERR>, "    -o       starting phone number ( origination)\n");

        print(<STDERR>, "    -d       starting phone number ( destination)\n");

        print(<STDERR>, "    -r       how many times to repeat phones number \n");
	exit 1;
}

