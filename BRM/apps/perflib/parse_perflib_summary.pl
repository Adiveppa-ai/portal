# Copyright (c) 2020, Oracle and/or its affiliates. 
#------------------------------------------------------------------------------#
# SCRIPT: parse_perflib_summary.pl
#
# DESCRIPTION:
#
# Script to parse the output produced by the perflib flist trace (summary mode).
# This simply calculates durations and time between opcode calls and prints
# the results to a file in perflib aggregate trace format for further
# processing by the perf_parse.pl script.
#
# INFORMATION:
#
# Performance tracing tools ...
#
# REVISION:
#
# $Revision: 1.6 $
# $Author: pin $
# $Date: 2015/04/20 19:02:03 $
#------------------------------------------------------------------------------#
use File::Basename;
use Getopt::Std;
use Data::Dumper; # For debug ...
use strict;

use vars qw($CMD $DEF_PFILE $DEF_NDP);

$DEF_NDP = 9;
$DEF_PFILE = "123.123.123_123.plog.txt";
$CMD = basename ($0);

#------------------------------------------------------------------------------#
# Function     : Usage
#
# Description  : Print usage message and exit ...
#
# Input        : None
#
# Output       : None
#
# Return       : None
#------------------------------------------------------------------------------#
sub Usage {
   print STDERR <<XXX;
usage : $CMD [-h] [-n<dp>] [-s<n>] [-o<ofile>] <filename>

where : -h            This 'help' message
        -n<dp>        Number of decimal places of precision - default is 9
        -sn           Show status about processing (every <n> lines)
        -o<ofile>     Print output to specified output file (or - for STDOUT).
                      Default is '$DEF_PFILE'

        <filename>    Perflib logfile (or use - for STDIN)
XXX
   exit(1);
}

#------------------------------------------------------------------------------#
# Function     : Main
#
# Description  : Not really a function, but rather the entry point for the
#                program.
#
# Input        : None  - See "Usage" function for details ...
#
# Output       : None
#
# Return       : 0 if OK, non-zero otherwise
#------------------------------------------------------------------------------#
my $p_debug = 0;
my $perflib_file_name = $DEF_PFILE;
my $p_ndp = $DEF_NDP;
my $p_status = 0;

#
# Parse options and arguments ...
#
my %opt = ();

getopts('dhs:n:o:', \%opt) or Usage();
if ($opt{d}) { $p_debug = 1 }
if ($opt{h}) { Usage() }
if ($opt{n}) { $p_ndp = $opt{n} }
if ($opt{s}) { $p_status = $opt{s} }
if ($opt{o}) { $perflib_file_name = $opt{o} }

#
# Check arguments - we expect one or more filenames ...
#
Usage() if scalar(@ARGV) != 1;

#
# Processing ...
#
my $logfile = $ARGV[0];

if ($logfile ne "-") {
   open (STDIN, "<$logfile") or
      die ("Failed opening file '$logfile'");
}
if ($perflib_file_name ne "-") {
   open (STDOUT, ">$perflib_file_name") or
      die ("Failed creating file '$perflib_file_name'");
}

printf STDOUT "S,0,0,-2,0,VRT_OP_ELAPSED,0,file.c,0,pid,tid,perflib,0\n";

#
# Get file data ...
#
my $p_fmt = sprintf "%%.${p_ndp}f";
my @opstack = ();
my $last_level = -1;
my $last_time = 0;
my $line_no = 0;

while (<STDIN>) {
   chomp;
   ++$line_no;
   if ($p_status && $p_status > 0 && ($line_no % $p_status) == 0) {
      printf STDERR "%s : processed $line_no lines\n", localtime() . "";
   }

   if (/(\d+\.\d+)\s+([\d\.]+)\s+([\dXABCDEFxabcdef]+)  ([| ]*)(\S+) \((.*)\[(\d*)\](.*)?\)/ or
       /(\d+\.\d+)\s+([\d\.]+)\s+<(.*)>/)
   {
      my $timestamp = $1;
      my $ts = sprintf $p_fmt, $2;
      my $flags = $3;
      my $opcode_end = 0;
      if ($flags eq "opcode_end") {
         $flags = 0x0;
         $opcode_end = 1;
      }
      my $indent_str = $4;
      my $opcode = $5;
      my $file = $6;
      my $lineno = $7;
      my $obj_type = $8;

      my $dec_flags = hex(lc($flags));
      my $level = int(length($indent_str) / 2);
      my $duration = 0.0;
      my $errors = 0;
      my $program = "";

      if ($p_debug) {
         printf "FOUND: timestamp[$timestamp] level[$level] ts[$ts] " .
                "opcode[$opcode] flags[$flags] dec_flags[$dec_flags] " .
                "file/lineno[$file/$lineno]\n" 
      }

      my %op = ( ts => $ts, opcode => $opcode, level => $level, flags => $flags,
                 file => $file, lineno => $lineno, dec_flags => $dec_flags,
                 errors => $errors, program => $program,
                 obj_type => $obj_type );

      #
      # If we're going up or staying the same, we've finished an opcode and
      # need to calculate it's execution time and write it to the report.
      # NOTE: We loop as we can exit more than one level in a single step...
      #
      if ($last_level >= $level) {
         for (my $i = $level; $i <= $last_level; $i++) {
            my $op_ref = pop(@opstack);        
            $duration = $ts - $op_ref->{ts};
            printf STDOUT "F,$p_fmt,0,1,$p_fmt,$p_fmt,0,0,0,0,0,0,0\n",
               $duration, $duration, $duration;
         }
      }
      #
      # Print start entry for this opcode and pop the data on the stack, unless
      # it is the opcode end, in which case update the total time and reset the
      # level indicator.
      #
      if ($opcode_end) {
         $last_level = -1;
      } else {
         printf STDOUT "S,%d,0,0,%d,$opcode,0,$file,$lineno,pid,tid," .
                       "$program,0,$obj_type\n", $level+1, $dec_flags;
         #
         # Pop this onto the stack for calculation and the opcode end ...
         #
         push(@opstack, \%op);
         if ($p_debug) {
            printf "PUSH_STACK: %s\n",
               join (" ", map { $_->{opcode} } @opstack);
         }
         $last_level = $level;
      }
      $last_time = $ts;
   }
}

#
# Handle incomplete logs ...
#
while ((my $op_ref = pop(@opstack))) {
   my $duration = $last_time - $op_ref->{ts};
   printf STDOUT "F,$p_fmt,0,1,$p_fmt,$p_fmt,0,0,0,0,0,0,0\n",
                $duration, $duration, $duration;
}
printf STDOUT "F,$p_fmt,0,0,0,0,0,0,0,0,0\n", $last_time;
