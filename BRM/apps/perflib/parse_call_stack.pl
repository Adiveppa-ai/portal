# Copyright (c) 2020, Oracle and/or its affiliates. 
#------------------------------------------------------------------------------#
# SCRIPT: parse_call_stack.pl
#
# DESCRIPTION:
#
# Script to parse the output produced by the CM call-stack tracing
# functionality. This simply calculates durations and time between opcode calls.
#
# INFORMATION:
#
# Performance tracing tools ...
#
# The perflib trace format contains the following records:
#
# Start record: 
#
#   0 - (S)tart record marker
#   1 - Level of indentation
#   2 - Unique operation ID (numeric)
#   3 - Opcode number
#   4 - Opcode flags (numeric)
#   5 - Opcode name (or function name)
#   6 - Opcode timestamp
#   7 - Source code filename
#   8 - Source code line number
#   9 - Process ID
#   10 - Thread ID
#   11 - Program name
#   12 - Bucket ID (for histogram data)
#   13 - Object Type (for reads/searches etc.)
#
# Finish record:
#
#   0 - (F)inish record marker
#   1 - Opcode duration
#   2 - Record count
#   3 - Call count
#   4 - Minumum exec time
#   5 - Maximum exec time
#   6 - Bucket start time (for histogram data)
#   7 - Bucket end time (for histogram data)
#   8 - Cache calls (number of operations returned from CM cache)
#   9 - Cache duration (duration of operations returned from CM cache)
#   10 - Number of failures (error buffer set on exit)
#   11 - User CPU time
#   12 - System CPU time
#
# REVISION:
#
# $Revision: 1.17 $
# $Author: ihargrea $
# $Date: 2017/05/10 14:10:30 $
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
usage : $CMD [-h] [-v] [-p|-P] [-n<dp>] [-l<limit>] [-z<n>] <filename>

where : -h            This 'help' message
        -d            Print debug information
        -v            Print 'virtual' times - calculated processing times.
        -p            Produce an output file like that of the PerfLib - so that
                      the results can be processed by perf_parse.pl. The file
                      is '$DEF_PFILE' (mutually exclusive with -P)
        -P            Like -p option, but data is printed to STDOUT and read
                      from STDIN (mutually exclusive with -p)
        -n<dp>        Number of decimal places of precision - default is 9
        -l<limit>     Cutoff for recording opcode data (anything less than
                      this time - in seconds - will not be recorded)
        -z<n>         Show progress (on STDERR) every 'n' lines processed

        <filename>    CM logfile (with call-stack tracing present)
XXX
   exit(1);
}


#------------------------------------------------------------------------------#
# Function     : Main
#
# Description  : Not really a function, but rather the entry point for the
#                program.
#
# Input        : None  - See "usage" function for details ...
#
# Output       : None
#
# Return       : 0 if OK, non-zero otherwise
#------------------------------------------------------------------------------#
my $p_debug = 0;
my $p_show_virtual = 0;
my $p_perflib_file = 0;
my $p_perflib_stdout = 0;
my $perflib_file_name = $DEF_PFILE;
my $p_ndp = $DEF_NDP;
my $p_limit = 0.0;
my $p_progress = 0;

#
# Parse options and arguments ...
#
my %opt = ();

getopts('dhvpPl:n:z:', \%opt) or usage();
if ($opt{d}) { $p_debug = 1 }
if ($opt{h}) { usage() }
if ($opt{v}) { $p_show_virtual = 1; }
if ($opt{p}) { $p_perflib_file = 1; }
if ($opt{P}) { $p_perflib_stdout = 1; }
if ($opt{n}) { $p_ndp = $opt{n} }
if ($opt{l}) { $p_limit = $opt{l} }
if ($opt{z}) { $p_progress = $opt{z} }

#
# Check arguments - we expect one filename ...
#
my $logfile = "";
if ($p_perflib_stdout && $p_perflib_file) {
   printf STDERR "ERROR: cannot use -p and -P together.\n";
   usage();
} elsif ($p_perflib_stdout) {
   if (scalar(@ARGV) != 0) {
      printf STDERR "ERROR: no log filename required for STDIN/STDOUT\n";
      usage();
   }
   $logfile = $ARGV[0];
} else {
   if (scalar(@ARGV) != 1) {
      printf STDERR "ERROR: Must provide one call-stack logfile name.\n";
      usage();
   }
   $logfile = $ARGV[0];
}

#
# Processing ...
#
my $line = 0;
my @lines = ();
my @line_groups = ();
my $total = 0;
my $all_time = 0;
my @time_stack = ();
my $duration;
my $total_duration;
my $p_fmt = sprintf "%%.${p_ndp}f";
my $p_fmt2 = sprintf "%%12.${p_ndp}f";
my $program = "";
my $log_location = "";
my $processed = 0;
my $last_ts = 0;
my $last_level = 0;

#
# Open files as STDIN / STDOUT as appropriate ...
#
if ($logfile) {
   open (STDIN, "<$logfile") or
      die ("Failed opening file '$logfile'");
}
if (!$p_perflib_stdout && $p_perflib_file) {
   open (STDOUT, ">$perflib_file_name") or
      die ("Failed creating file '$perflib_file_name'");
}

#
# If printing perflib output, put VRT_OP_ELAPSED header ...
#
if ($p_perflib_file || $p_perflib_stdout) {
   printf STDOUT "S,0,0,-2,0,VRT_OP_ELAPSED,0,file.c,0,pid,tid," .
                 "$program,0\n";
}

#
# Get file data ...
#
while (<STDIN>) {
   #
   # Progress information ...
   #
   if ($processed > 0 && $p_progress > 0 &&
       ($processed % $p_progress) == 0)
   {
      printf STDERR "%s : processed $processed lines\n", localtime() . "";
   }
   ++$processed;

   #
   # Match records ...
   #
   if (/^D /) {
      chomp;
      $log_location = $_;
   } elsif (/^\s+([\d.]+)\s+([.]*)(\w+)\s+(\w+) \(([\dabcdefx]+)\)(.*)/) {
      my $ts = sprintf $p_fmt, $1;
      $last_ts = $ts;
      my $indent_str = $2;
      my $level = length ($indent_str);
      $last_level = $level;
      my $type = $3;
      my $opcode = $4;
      my $flags = $5;
      my $notes = $6;
      my $dec_flags = hex($flags);
   
      if ($p_debug) {
         printf "FOUND: ts[$ts] level[$level] type[$type] " .
                "opcode[$opcode] flags[$flags] notes[$notes]\n" 
      }

      $indent_str =~ s/\./  /g;
      $notes =~ s/(^\s*|\s*$)//g;
  
      # 
      # Handle initialisation ...
      #
      if ($p_perflib_file == 0 && $type eq "Enter" && $level == 0) {
         $line = 0;
         @lines = ();
         printf "RESET: lines() - TOP-LEVEL\n" if ($p_debug);
      }

      #
      # Handle start/end records ...
      #
      $duration = 0;
      if ($type eq "Enter") {
         $time_stack[$level] = $ts;
         if ($p_perflib_file || $p_perflib_stdout) {
           printf STDOUT "S,%d,0,0,%d,$opcode,$p_fmt,file.c,0,pid,tid," .
                          "$program,0\n", $level+1, $dec_flags, 0;
         }
      } else {  # Exit ...
         $duration = $ts - $time_stack[$level];

         if ($p_perflib_file || $p_perflib_stdout) {
            # 
            # Determine if this was from the transaction cache ...
            #   1.085230567 ...Exit  PCM_OP_READ_FLDS (0x400) - from cache
            #   If so, set cache_calls=1 and put the cache duration.
            # Or, if it is a DM trace, from the DB:
            #    - from DB 0.0.0.1 DB Time    0.007942432
            #
            if ($notes =~ /from cache/) {
               printf STDOUT "F,$p_fmt,0,1,$p_fmt,$p_fmt,0,0,1,$p_fmt,0,0,0\n",
                             $duration, $duration, $duration, $duration;
            } elsif ($notes =~ /.*DB Time\s+([\d.]+)/) {
               my $db_time = $1;

               printf STDOUT "S,%d,0,0,%d,OCI_$opcode,$p_fmt,file.c,0,pid,tid," .
                             "$program,0\n", $level+2, $dec_flags, 0;

               printf STDOUT "F,$p_fmt,0,1,$p_fmt,$p_fmt,0,0,0,0,0,0,0\n",
                             $db_time, $db_time, $db_time;

               printf STDOUT "F,$p_fmt,0,1,$p_fmt,$p_fmt,0,0,0,0,0,0,0\n",
                             $duration, $duration, $duration;
            } else {
               printf STDOUT "F,$p_fmt,0,1,$p_fmt,$p_fmt,0,0,0,0,0,0,0\n",
                             $duration, $duration, $duration;
            }
         }
      }

      #
      # Store data, not required if we're producing perflib output ...
      #
      if ($p_perflib_file == 0 && $p_perflib_stdout == 0) {
         my %line_info = ( "ts" => $ts,
                           "indent_str" => $indent_str,
                           "level" => $level,
                           "type" => $type,
                           "opcode" => $opcode,
                           "flags" => $flags,
                           "notes" => $notes,
                           "duration" => $duration );
         $lines[$line++] = \%line_info;

         #
         # This is the end record ...
         #
         if ($type eq "Exit" && $level == 0) {
            $all_time += $ts;

            if ($ts > $p_limit) {
               my @lines_copy = @lines;
               my %group_info = ( "lines" => \@lines_copy,
                                  "num_lines" => $line,
                                  "total_time" => $ts,
                                  "log_location" => $log_location,
               );
               push (@line_groups, \%group_info);
            }

            if ($p_debug) {
               printf "EXIT OPCODE[$opcode]: lines[$line] time[$ts] " .
                      "- TOP-LEVEL\n";
            }
         }
      }
   }
}

#
# If the stack was interrupted, record everything as though all the
# opcodes terminated "instantaneously"... not much else we can do.
# 
my $level = $last_level;
while (--$level >= 0) {
   my $duration = $last_ts - $time_stack[$level];
   printf STDOUT "F,$p_fmt,0,1,$p_fmt,$p_fmt,0,0,0,0,0,0,0\n",
                 $duration, $duration, $duration;
}
if ($p_perflib_file || $p_perflib_stdout) {
   printf STDOUT "F,0,0,0,0,0,0,0,0,0,0,0,0\n";
   exit(0);
}

#
# Print out report information ...
#
if ($p_debug) {
   $Data::Dumper::Indent = 1;
   printf "LINE_GROUPS:\n%s\n",
      Data::Dumper->Dump( [ \@line_groups ], [ "line_groups" ]);
}

#
# Print out each performance group ...
#
my $group_num = 0;

foreach my $group_ref (@line_groups) {
   my $last_end = 0;
   my $last_start = 0;

   if ($p_debug) {
      printf "PROCESS GROUP[$group_num] lines[%s] num_lines[%d] " .
             "total_time[%s]\n", $group_ref->{lines}, $group_ref->{num_lines},
             $group_ref->{total_time};
   }

   #
   # Print group header ...
   #
   printf "\n" if ($group_num > 0);
   printf "$group_ref->{log_location}\n";
   printf "%-54.54s %12s %6s %12s %12s %s\n",
      "Lvl Opcode", "Duration", "%age", "Start/Stop", "Flags", "Notes";
   printf "%-54.54s %12s %6s %12s %12s %s\n",
      "--- ------", "--------", "----", "----------", "-----", "-----";

   #
   # Process lines for this group ...
   #
   for (my $i = 0; $i < $group_ref->{num_lines}; $i++) {

      my $line_arr = $group_ref->{lines};
      my $op = $line_arr->[$i];

      if ($p_debug) {
         printf "PROCESSING line[$i] line_arr[$line_arr] op[$op]\n";
      }

      #
      # Track 'virtual' processing time - calculated as the difference between
      # two opcode calls ... This is either:
      #
      # o Entering a new opcode. The time is calculated from the end of the
      #   previous opcode if it was at the same level as this, or the start of
      #   the previous opcode.
      #
      # o Exiting an opcode, in which case the time is compared with the end of
      #   the previous opcode (if it's at a different level).
      #
      if ($p_show_virtual) {
         my $ptime = 0;
         my $level;
         my $indent_str;

         if ($op->{type} eq "Enter") {
            if ($last_end && $last_end->{level} == $op->{level}) {
               $ptime = $op->{ts} - $last_end->{ts};
               $level = $op->{level};
               $indent_str = $op->{indent_str}; 
            } elsif ($last_start) {
               $ptime = $op->{ts} - $last_start->{ts};
               $level = $op->{level};
               $indent_str = $op->{indent_str};
            }
         } else {
            if ($last_end && $last_end->{level} > $op->{level}) {
               $ptime = $op->{ts} - $last_end->{ts};
               $level = $last_end->{level};
               $indent_str = $last_end->{indent_str};
            }
         }

         if ($ptime) {
            printf " %02d ", $level;
            printf "%-50.50s $p_fmt2 %6.2f %12s %s\n",
               $indent_str . "processing        ",
               $ptime, (100 * $ptime) / $group_ref->{total_time}, "", "";
         }
      }

      #
      # Print opcode entry information ...
      #
      if ($op->{type} eq "Enter") {
         printf "S%02d ", $op->{level};
         printf "%-50.50s %12s %6s $p_fmt2\n",
            $op->{indent_str} . $op->{opcode}, "", "", $op->{ts};
         $last_start = $op;
      }

      #
      # Print opcode exit information ...
      #
      if ($op->{type} eq "Exit") {
         printf "F%02d ", $op->{level};
         printf "%-50.50s $p_fmt2 %6.2f $p_fmt2 %12s %s\n",
            $op->{indent_str} . $op->{opcode}, $op->{duration},
            (100 * $op->{duration}) / $group_ref->{total_time}, $op->{ts},
            $op->{flags}, $op->{notes};
         $last_end = $op;
      }
   }
   $group_num++;
}
exit(0);
