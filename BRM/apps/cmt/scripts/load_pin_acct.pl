#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl

# @(#) %full_filespec: load_pin_acct.pl~1:perl:1 %
#
# Copyright (c) 2004, 2015, Oracle and/or its affiliates. All rights reserved.

#	This material is the confidential property of Oracle Corporation       
#       or its licensors and may be used, reproduced, stored or transmitted
#       only in accordance with a valid Oracle license or sublicense agreement.
#
#=============================================================

use Socket;
use pcmdd;
use pcmif;

use Getopt::Std;

($ME = $0) =~ s,.*/,,;
$DEBUG = $ENV{"DEBUG"} || 0;

#
# Parse command line flags.
#
getopts('h:I:') || &usage("");
if (defined $opt_h) {
	&usage("");
}

if (!defined $opt_I) {
	&usage("");
}
$dm_hostname = `hostname`;
chop($dm_hostname);

$dm_port = 22251;

$db_no = "0.0.0.1";
$PIN_CONF_DB_NO=$db_no;
$PIN_CONF_INIT_OPNAME="PCM_OP_CREATE_OBJ";
$PIN_CONF_INIT_OPFLAGS=0x40;
$PIN_CONF_SYS_CURRENCY=840;
$PIN_CONF_DATE_NOW=time();

if (defined $opt_I) {
	$initacct = $opt_I;
}


if ($DEBUG) {
	printout("$ME: dm_hostname $dm_hostname\n");
	printout("$ME: dm_port $dm_port\n");
	printout("$ME: db_no $db_no\n");
	printout("$ME: initacct $initacct\n");
}

#
# Create a new EBUF
#
$ebufp = pcmif::pcm_perl_new_ebuf();

#
# connect to a DM of a given name
# XXX WARNING - only use this to connect to a DM XXX SPECIAL
#
$pcm_ctxp = pcmdd::pcmdd_connect($dm_hostname, $dm_port, $db_no, $ebufp);

if (pcmif::pcm_perl_is_err($ebufp)) {
	pcmif::pcm_perl_print_ebuf($ebufp);
	exit(1);
} 

if ($DEBUG) {
	printout("back from pcmdd_connect()\n");
	printout("    DEFAULT db is: $db_no \n");
}

printout("$ME: Parsing  $initobjs\n");
&parse_file ($initacct);


printout("  No  Opcode                    Flag  Poid\n");
printout("-----------------------------------------------------------------\n");
$opnum = 1;

#
# Walk through @oplist and execute each opcode with the associated flist.
#
foreach $op (@oplist) {
	($opname, $opflags, $flist) = split(',', $op, 3);

	#
	# Get PIN_FLD_POID from the flist
	#	
	($j1,$poid,$j2) = $flist =~ 
		m#(^|\n)0\s+PIN_FLD_POID\s+POID\s+\[0\]\s+([\w\s/\.]+)(\n|$)#;
	chomp($poid);
	$s=sprintf(" %3d  %-26s %2d   %s\n", 
			$opnum, $opname, $opflags, $poid);	
	printout($s);

	if ($DEBUG) {
		printout("$ME: $flist");
		printout("...\n");
	}

	#
	# Convert the flist string to a pin flist
	#
	$in_flistp = pcmif::pin_perl_str_to_flist($flist, $db_no, $ebufp);
	if (pcmif::pcm_perl_is_err($ebufp)) {
	      	pcmif::pcm_perl_print_ebuf($ebufp);
		exit(1);
	}
	
	if ($DEBUG) {
		printout("$ME: Converted string to flist\n");
	}

	if ($opname eq "PCM_OP_SET_DD") {	
		printout("$ME: Executing $opname\n");
	} # end if SET_DD

	#
	# Invoke PCM_OP
	#
	$out_flistp = pcmif::pcm_perl_op($pcm_ctxp, $opname, $opflags, 
					 $in_flistp, $ebufp);

	#
	# Check the error from the previous PCM_OP
	#
	if (pcmif::pcm_perl_is_err($ebufp)) {
		printout("$ME: BAD op: $opname\n");
	      	pcmif::pcm_perl_print_ebuf($ebufp);
		exit(1);
	}

	#
	# Convert the output flist to a string
	#
	$out = pcmif::pin_perl_flist_to_str($out_flistp, $ebufp);
	if (pcmif::pcm_perl_is_err($ebufp)) {
	      	pcmif::pcm_perl_print_ebuf($ebufp);
		exit(1);
	}

	#
 	# cleanup
	#
        pcmif::pin_flist_destroy($in_flistp);
      	pcmif::pin_flist_destroy($out_flistp);

	if ($DEBUG) {
		printout("$ME: OUTPUT Flist:\n$out\n--------\n");
	}

	$opnum++;
}

printout("-----------------------------------------------------------------\n");

#
# Cleanup
#
pcmif::pcm_context_close($pcm_ctxp, 0, $ebufp);
if (pcmif::pcm_perl_is_err($ebufp)) {
	print STDERR "$ME: BAD context close\n",
	    pcmif::pcm_perl_ebuf_to_str($ebufp), "\n";
	exit(1);
}

exit(0);

###############################################################################
# parse_file:
#	input:
#		filename with opcode data
#	output:
#		add entry to @oplist as "opname,opflags,flist"
###############################################################################
sub parse_file {
	local ($FILE) = @_;
	local $flist;

	open (FILE, "$FILE") || die "$ME: Unable to open file '$FILE': $!\n";

	while (<FILE>) {
		#
		# skip comment lines
		#
		next if /^\s*#/;

		#
		# skip blank lines
		#
		next if /^\s*$/;
		
		#
		# Match line containing the following regexp match:
		# <PCM_OP var1=val1; var2=val2>	
		#
		if (m/\s*<PCM_OP\s+((\s*\$\w+\s*=\s*\$?\w+;?)*)\s*>/) {
			#
			# evaluate the variables
			#
			eval qq!$1!;

			#
			# change the rec separator to read flist in one shot.
			#
			$/ = "<\/PCM_OP>";
		
			#
			# read in the next record
			#
			$_ = <FILE>;

			#
			# take everything except the separator
			#
			s/<\/PCM_OP>$//;
		
			#
			# evaluate the collected string to perform substitution
			#
			$flist = eval "qq!$_!";

			#
			# change the record separator back to newline
			#
			$/ = "\n";

			if ($DEBUG) {
				printout("Evaluated flist read from $FILE\n");
				printout("OPNAME= $PIN_OPNAME\n");
				printout("OPFLAG= $PIN_OPFLAGS\n");
				printout("--------\n");
			}

			#
			# Add this flist, opname to the "@oplist"
			#
			push(@oplist, 
			     join(',', $PIN_OPNAME, $PIN_OPFLAGS, $flist));

		} else {
			print(<STDERR>, "Bad input in file $FILE: $_\n");
			exit(1);
		}
	} # end while

	close (FILE);

} # end sub parse_file

################################################################################
# usage:  Print usage message and exit.
#
################################################################################
sub usage {
	print(<STDERR>, 
		@_);
	print(<STDERR>, 
		"Usage: $ME [options] \n");
	print(<STDERR>, 
		"    -I arg  use arg instead of init_acct.source\n");
	print(<STDERR>, 
		"    -h       this message\n");

	exit 1;
}
sub printout {
        local ($outstr) = @_;

        syswrite STDOUT, $outstr, length($outstr);
}
