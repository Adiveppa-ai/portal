#
#	@(#) % %
#       
# Copyright (c) 1996, 2015, Oracle and/or its affiliates. All rights reserved.
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#

#
#
use Getopt::Std;
require "..\ms_conf.pm";

($ME = $0) =~ s,.*/,,;

#
# Parse command line flags.
# r - count number of rows
# p - db performance
# a - table analyze
# s - allocated spaces
# h - print help (usage)
#
getopts('hsarpf:') || &usage("");
if (defined $opt_h) {
	&usage("");
}

	if (!(defined $opt_s || defined $opt_r || defined $opt_a ||defined $opt_p)) {
	&usage("");
}

$datafile = "data.lst";
if (defined $opt_f) {
	$datafile = $opt_f;
}

if (defined $opt_r) {
$user="public";
$input_file="ms_tables_stats.sql";
}

if (defined $opt_p) {
$user="system";
$input_file="ms_perf.sql";
}

if (defined $opt_a) {
$user="public";
$input_file="ms_analyze.sql";
}

if (defined $opt_s) {
$user="public";
$input_file="ms_spaces.sql";
}

	exec_sqlcommand($user,$input_file,$datafile);

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
		"    -r       count number of rows in tables\n");
	print(<STDERR>,
		"    -a       obtain allocated space by tables\n");
	print(<STDERR>,
		"    -s       obtain allocated space by tablespaces\n");
	print(<STDERR>,
		"    -p       display DB performance\n");
	print(<STDERR>,
		"    -h       this message\n");

	exit 1;
	}


