#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#
# @(#) %full_filespec: SampleReload.pl~3:perl:1%
#
# Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.
#      This material is the confidential property of Oracle Corporation
#      or its licensors and may be used, reproduced, stored
#      or transmitted only in accordance with a valid Oracle license
#      or sublicense agreement.
#
#=============================================================


#
# File:  SampleReload.pl
# Title: Utility reload script for sample batch handler
#
# Description:
#	This script calls the batch application to reprocess
#	input files.  Typically, this script is manually
#	executed after the user has corrected those error
#	records found by the batch application during an
#	earlier run.
#
# Note:
#	The scipt will sensibly handle the name of the input
#	file if "_cache.xml" was appended to the filename by
#	the earlier batch application run.  This reflects the
#	behavior of the UEL application.
#
#=============================================================


require "./SampleHandler_config.values";
use File::Basename;

#
# Check that a command line argument is present.
#
if (!defined @ARGV[0]) {
	&usage;
}

#
# Reform filename if it has "_cache.xml" appended.
#
if (@ARGV[0] =~ /_cache.xml$/) {
	@file_split = split(/\_cache.xml/, @ARGV[0]);
	$filename = @file_split[0];
}
else {
	$filename = @ARGV[0];
}

#
# Reformat directory path name to use forward slash separators.
#
if ($pinUELDir =~ /\\/) {
	$pinUELDir =~ s/\\/\//g;
}

#
# Which operating system are we on?
#
if ($^O =~/win/i) {
	$pinUELDir =~ s/\//\\/g;
}

#
# Change directory to the batch application directory, execute the
# batch appplication, and exit.
#
$uelCmd = basename($pinUEL) . " -t " . $template . " -m load" . " $filename ";
chdir ("$pinUELDir") || die "Cannot chdir to $pinUELDir: $!\n";
system($uelCmd);
exit;

#-----------------------------------------------------------------
#
# usage: Print usage message and exit.
sub usage {
	print STDERR "Usage: $0 <filename>\n";
	exit(-1);
}
