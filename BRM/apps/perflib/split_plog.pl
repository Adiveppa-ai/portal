# Copyright (c) 2020, Oracle and/or its affiliates. 
#------------------------------------------------------------------------------#
# SCRIPT: split_plog.pl
#
# DESCRIPTION:
#
# Script to parse a perflib raw log file and to split it into the individual
# periods for which data has been collected in the file (e.g. where the flush
# time is shorter than the aggregation time).
#
# INFORMATION:
#
# BRM Performance tools ...
#
# REVISION:
#
# $Revision: 1.3 $
# $Author: pin $
# $Date: 2015/07/14 17:05:52 $
#------------------------------------------------------------------------------#

#------------------------------------------------------------------------------#
#                     M O D U L E   I N C L U S I O N
#------------------------------------------------------------------------------#
use strict;
use File::Basename;
use Getopt::Std;

#------------------------------------------------------------------------------#
#                     G L O B A L   V A R I A B L E S
#------------------------------------------------------------------------------#
our $CMD = basename($0);
our $KEEP_EMPTY = 0;
our $QUIET = 0;

#------------------------------------------------------------------------------#
# Function     : usage
#
# Description  : Print usage message and exit ...
#
# Input        : None
#
# Output       : None
#
# Return       : None
#------------------------------------------------------------------------------#
sub usage {
   print STDERR <<XXX;
usage : $CMD [-h] [-k] [-q] <log_file> [<log_file2> ...]

where : -h            This 'help' message
        -k            Keep empty files
        -q            Quiet mode (don't print file data on STDOUT)

        <log_file>    Perflib log file(s)
XXX
   exit(1);
}

#------------------------------------------------------------------------------#
# Function     : handle_rename
#
# Description  : Handle renaming of temp file to final file ...
#
# Input        : tmp_file   Temp file name
#                tstamp     Timestamp (unix)
#                num_rows   Number of rows of data
#                pid        Process ID
#                tid        Thread ID
#                basef      Base file name 
#
# Output       : None
#
# Return       : None
#------------------------------------------------------------------------------#
sub handle_rename {
   my ($tmp_file, $tstamp, $num_rows, $pid, $tid, $basef) = @_;

   my ($ss, $mi, $hh, $dd, $mm, $yyyy, $wday, $yday, $isdst) =
      localtime($tstamp);

   my $newf = sprintf("SPLIT_${basef}.${pid}.${tid}." .
                      "%04d%02d%02d_%02d%02d%02d.plog.txt",
                      $yyyy + 1900, $mm+1, $dd, $hh, $mi, $ss);

   if ($num_rows > 0 || $KEEP_EMPTY) {
      rename($tmp_file, $newf);
      printf "Generated new file : $newf\n" unless ($QUIET);
   } else {
      printf "Remove empty file  : $newf\n" unless ($QUIET);
      unlink($tmp_file);
   }
}

#------------------------------------------------------------------------------#
# Function     : main
#
# Description  : Program entry point ...
#
# Input        : poid   Poid of snahsphot object
#
# Output       : None
#
# Return       : None
#------------------------------------------------------------------------------#

#
# Check options ...
#
my %opt = ();
getopts('hk', \%opt) or usage();
if ($opt{h}) { usage() }
if ($opt{k}) { $KEEP_EMPTY = 1 }

my $nargs = scalar(@ARGV);

usage() if ($nargs < 1);

#
# Process all files one by one ...
#
foreach my $fname (@ARGV) {
   my $tmpf = "tmp.$$";
   my $newf = "";

   #
   # retrieve the 'tag' for the file ...
   # E.g. perf_log.6028.20130723_150000.20130723_160000.plog.txt
   #
   my @a = split(/\./, $fname);
   my $basef = $a[0];
   # Start at -1 as we don't want to count VRT_OP_ELAPSED end
   my $has_data = -1;
   my $in_section = 0;
   my $pid = "";
   my $tid = "";
   my $tstamp = 0;
   my $last_line = "";

   #
   # Open and process log file ...
   #
   open(F, "<$fname") or die ("failed opening '$fname'");
   while (<F>) {
      chomp;
      my $line = $_;

      #
      # If necessary, open a new temp file ...
      #
      open(OUT, ">$tmpf") unless (-e $tmpf);

      #
      # We process the VRT_OP_ELAPSED records to get data about each individual
      # "flush" ...
      # E.g.:                     Timestamp                        Process ID
      #                              |                                  |
      #                              V                                  V
      # S,0,0,-2,0,VRT_OP_ELAPSED,1374591769.226939000,perf_log.c,1364,7037,4145...
      # F,1374595204.881587000,perf_log.c,1406,7037,4145...
      #
      if (/^S,.*VRT_OP_ELAPSED,(\d+)\.(\d+),.*$/) {
         $tstamp = $1;
         if ($in_section) { 
            close(OUT);
            handle_rename ($tmpf, $tstamp, $has_data, $pid, $tid, $basef);
         }
         my @cols = split(",", $line);
         $pid = $cols[9];
         $tid = $cols[10];
         $has_data = -1;
         $last_line = "";
         $in_section = 1;
      } else {
         printf OUT "$last_line\n" if ($last_line);
         $last_line = $_;
         $has_data++;
      }
   }
   if ($in_section) { 
      close(OUT);
      handle_rename ($tmpf, $tstamp, $has_data, $pid, $tid, $basef);
   }
   close(F);
}
