# Copyright (c) 2021, Oracle and/or its affiliates.
#------------------------------------------------------------------------------#
# SCRIPT: report_perf_data.pl
#
# DESCRIPTION:
#
# Generates simple report from performance profile data ...
#
# INFORMATION:
#
# BRM Performance Tools ...
#
# REVISION:
#
# $Revision: 1.15 $
# $Author: ihargrea $
# $Date: 2020/11/30 11:05:46 $
#------------------------------------------------------------------------------#

#------------------------------------------------------------------------------#
#                     M O D U L E   I N C L U S I O N
#------------------------------------------------------------------------------#
use strict;
use Data::Dumper;
use File::Basename;
use POSIX qw(mktime);
use Getopt::Std;
use GG::Sqlplus;

#------------------------------------------------------------------------------#
#                     G L O B A L   V A R I A B L E S
#------------------------------------------------------------------------------#
use vars qw($G_VERSION $G_CMD $G_DEBUG $G_DEF_CONN_STR $G_SQL %G_WIDTH
            $G_BUCKETS);

$G_VERSION = do {my $v = '$Revision: 1.15 $'; $v =~ s/[^\d\.]//g; $v};
$G_DEBUG = 0;
$G_CMD = basename ($0, ".pl");
$G_DEF_CONN_STR = "pin/pin\@pindb";
$G_SQL = undef;
%G_WIDTH = (
  "level" => 3,
  "function" => 10,  # Minimum, will be calculated from rpt_width
  "elapsed" => 13,
  "percentage" => 7,
  "calls" => 10,
  "average" => 13,
  "min" => 13,
  "max" => 13,
  "results" => 13,
);
$G_BUCKETS = 0;

#------------------------------------------------------------------------------#
# Function     : abort
#
# Description  : Prints a message and exits the program ...
#
# Input        : errstr   Message to print
#
# Output       : None
#
# Return       : None
#------------------------------------------------------------------------------#
sub abort {
   my ($errstr) = @_;
   printf STDERR "$G_CMD: ERROR - $errstr\n";
   if (defined($G_SQL)) {
      sql_exec ($G_SQL, "rollback;", undef, undef);
      sql_close ($G_SQL);
   }
   exit (1);
}

#------------------------------------------------------------------------------#
# Function     : usage
#
# Description  : Prints usage information and exits.
#
# Input        : None
#
# Output       : None
#
# Return       : None
#------------------------------------------------------------------------------#
sub usage {
   my $def_width = get_report_width();
   print STDERR <<XXX;
usage : $G_CMD [-h] [-d] [-b] [-c<conn>] [-l<level>] <mode> <poid>
        $G_CMD [-h] [-d] [-c<conn>] [-n<name>] [-f<from>] [-t<to>] <mode>

where : -h         This message
        -d         Debug mode
        -b         Show opcode 'buckets' in the report (default is to show
                   only main opcode entries)
        -w<width>  Report width minium (and default) is $def_width.
        -c<conn>   Connection string for BRM database
        -l<level>  Max level of 'depth' for report
        -n<name>   Name to filter by
        -f<from>   From time for searching snapshots (YYYYMMDD[_HHMISS])
        -t<to>     To time for searching snapshots (YYYYMMDD[_HHMISS])

        <mode>     Mode of operation:
                      summary   Generate a summary report
                      detail    Generate a detail report
                      list      List /performance_snapshot objects

        <poid>     Poid Id of /performance_snapshot object in case of 'report'
                   modes.

XXX
   exit(1);
}

#------------------------------------------------------------------------------#
# Function     : yyyymmdd_hhmiss_to_unix
#
# Description  : Convert a time string in format YYYYMMDD_HHMISS to a UNIX
#
# Input        : str    String with date
#
# Output       : None
#
# Return       : Timestamp or -ve for error
#------------------------------------------------------------------------------#
sub yyyymmdd_hhmiss_to_unix {
   my ($str) = @_;

   my ($ss, $mi, $hh, $dd, $mm, $yyyy);

   if (length($str) == 8) {
      ($yyyy, $mm, $dd) = ($str =~ /(\d\d\d\d)(\d\d)(\d\d)/);
   } elsif (length($str) == 15) {
      ($yyyy, $mm, $dd, $hh, $mi, $ss) =
         ($str =~ /(\d\d\d\d)(\d\d)(\d\d)_(\d\d)(\d\d)/);
   } else {
      printf STDERR "yyyymmdd_hhmiss_to_unix : bad date/time format '$str'\n";
      return -1;
   }
   my $t = mktime ($ss, $mi, $hh, $dd, $mm-1, $yyyy-1900,
                   undef, undef, -1) + 0;

   if ($G_DEBUG) {
      printf "yyyymmdd_hhmiss_to_unix : " .
             "yyyy[$yyyy] mm[$mm] dd[$dd] hh[$hh] mi[$mi] ss[$ss] t[$t]\n";
   }
   return $t;
}

#------------------------------------------------------------------------------#
# Function     : get_ddmmyyyy_hhmiss
#
# Description  : Convert a timestamp into a date string (local time)
#
# Input        : ut    Unix timestamp
#
# Output       : None
#
# Return       : Data string
#------------------------------------------------------------------------------#
sub get_ddmmyyyy_hhmiss {
   my ($ut) = @_;
   my ($ss, $mi, $hh, $dd, $mm, $yyyy, $wday, $yday, $isdst) = localtime($ut);
   return sprintf "%02d/%02d/%04d %02d:%02d:%02d",
      $dd, $mm+1, $yyyy+1900, $hh, $mi, $ss;
}

#------------------------------------------------------------------------------#
# Function     : get_report_width
#
# Description  : Returns the report width based on the column lengths defined
#                in the global hash %G_WIDTH
#
# Input        : None
#
# Output       : None
#
# Return       : Length
#------------------------------------------------------------------------------#
sub get_report_width {
   my $width = 0; 
   foreach my $col (keys %G_WIDTH) {
      $width += $G_WIDTH{$col};
   }
   return $width;
}

#------------------------------------------------------------------------------#
# Function     : list_snapshots
#
# Description  : List performance snapshots that match the specified crieria.
#
# Input        : name    Name to restrict search
#                from    Time from which search will be restricted
#                to      Time to which search will be restricted
#
# Output       : None
#
# Return       : Hash ref of result data ...
#------------------------------------------------------------------------------#
sub list_snapshots {
   my ($name, $from, $to) = @_;
   my $add_and = 1;

   printf "list_snapshots : name[$name] from[$from] to[$to]\n" if ($G_DEBUG);

   my (%fields) = ( poid_id0  => 'p.poid_id0',
                    poid_type => 'p.poid_type',
                    name      => 'p.name',
                    start_t   => 'p.start_t',
                    end_t     => 'p.end_t',
                    pid       => 'p.pid' );
   my $sql_body = " from performance_snapshot_t p ";
   $sql_body .= " where p.poid_type like '/performance_snapshot%' ";
   $sql_body .= " and p.name = '$name' " if ($name);
   $sql_body .= " and p.end_t >= $from " if ($from);
   $sql_body .= " and p.end_t <= $to " if ($to);
   $sql_body .= " order by p.start_t, p.name, p.pid; ";
   my $output;
   my $elapsed;

   my $results = sql_query ($G_SQL, $sql_body, \%fields, "|", 0, \$elapsed);

   printf Data::Dumper->Dump ([$results], ["result_array"]) if ($G_DEBUG);

   if (scalar(@{$results}) > 0) {
      printf "%12s  %-5.5s  %-19.19s  %-19.19s  %8s  %-30.30s\n",
         "POID_ID0", "Start Date", "End Date", "PID", "Name";
      printf "%12s  %-5.5s  %-19.19s  %-19.19s  %8s  %-30.30s\n",
         "--------", "-----", "----------", "--------", "---", "----";
      foreach my $href (@{$results}) {
         printf "%12s  %-5.5s  %-19.19s  %-19.19s  %8d  %-30.30s\n",
            $href->{poid_id0},
            $href->{poid_type} eq "/performance_snapshot" ? "Batch" : "RT",
            get_ddmmyyyy_hhmiss($href->{start_t}),
            get_ddmmyyyy_hhmiss($href->{end_t}), $href->{pid}, $href->{name};
      }
   } else {
      printf "No snapshots found!\n";
   }
}

#------------------------------------------------------------------------------#
# Function     : get_performance_snapshot
#
# Description  : Find a matching snapshot record in the BRM database, if it
#                exists.
#
# Input        : poid    Poid to locate ...
#
# Output       : None
#
# Return       : Hash ref of result data ...
#------------------------------------------------------------------------------#
sub get_performance_snapshot {
   my ($poid) = @_;

   my (%fields) = ( poid_id0  => 'p.poid_id0',
                    poid_type => 'p.poid_type',
                    name      => 'p.name',
                    start_t   => 'p.start_t',
                    end_t     => 'p.end_t',
                    pid       => 'p.pid' );
   my $sql_body = " from performance_snapshot_t p where p.poid_id0 = $poid ";
   my $output;
   my $elapsed;

   my $results = sql_query ($G_SQL, $sql_body, \%fields, "|", 0, \$elapsed);

   printf Data::Dumper->Dump ([$results], ["result_array"]) if ($G_DEBUG);

   return $$results[0];
}

#------------------------------------------------------------------------------#
# Function     : report_header
#
# Description  : Produce report header details ...
#
# Input        : href       Hash ref to performance info
#                summary    Summary (true) or detail (false)
#                elapsed    Report generation time
#
# Output       : None
#
# Return       : Header string
#------------------------------------------------------------------------------#
sub report_header {
   my ($href, $summary, $elapsed) = @_;

   my $str = "";
   $str .= sprintf "SNAPSHOT POID_ID0 : %s\n", $href->{poid_id0};
   $str .= sprintf "             NAME : %s\n", $href->{name};
   $str .= sprintf "             FROM : %s\n", localtime($href->{start_t}) . "";
   $str .= sprintf "               TO : %s\n", localtime($href->{end_t}) . "";
   $str .= sprintf "             TYPE : %s\n", $summary ? "Summary" : "Detail";
   $str .= sprintf "      REPORT DATE : %s\n", localtime() . "";
   $str .= sprintf "  PROCESSING TIME : %.2f seconds\n", $elapsed;

   return $str;
}

#------------------------------------------------------------------------------#
# Function     : summary_report
#
# Description  : Produce a summary report of data contained in the specified
#                /performance_snapshot object.
#
# Input        : poid       Poid of /performance_snapshot object
#                max_level  Max level to retrieve data in the report
#                href       Hash ref to performance info
#
# Output       : None
#
# Return       : 0 if all OK, non-zero if error
#------------------------------------------------------------------------------#
sub summary_report {
   my ($poid, $max_level, $href) = @_;

   my $output = "";
   my $elapsed = 0;
   my $pad_str = "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  " .
                 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  " .
                 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  " .
                 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  ";
   my $rt = $href->{poid_type} eq "/performance_snapshot" ? 0 : 1;

   my $sql = <<THE_END;
SET LINES 300
SET TRIM ON
SET PAGES 0
SET FEEDBACK OFF
SET TAB OFF
VAR poid_id0 NUMBER;
VAR w_level NUMBER;
EXEC :w_level := $G_WIDTH{level};
VAR w_function NUMBER;
EXEC :w_function := $G_WIDTH{function};
VAR w_elapsed NUMBER;
EXEC :w_elapsed := $G_WIDTH{elapsed};
VAR w_percentage NUMBER;
EXEC :w_percentage := $G_WIDTH{percentage};
VAR w_calls NUMBER;
EXEC :w_calls := $G_WIDTH{calls};
VAR w_average NUMBER;
EXEC :w_average := $G_WIDTH{average};
VAR w_min NUMBER;
EXEC :w_min := $G_WIDTH{min};
VAR w_max NUMBER;
EXEC :w_max := $G_WIDTH{max};
VAR w_results NUMBER;
EXEC :w_results := $G_WIDTH{results};
EXEC :poid_id0 := $poid;
VAR max_level NUMBER;
EXEC :max_level := $max_level;
VAR pad_str VARCHAR2(1024);
EXEC :pad_str := '$pad_str';
VAR g_bucket NUMBER;
EXEC :g_bucket := $G_BUCKETS;

  SELECT LPAD('Lvl', :w_level, ' ') || '  ' ||
         RPAD('Function', :w_function, ' ') || '  ' ||
         LPAD('Elapsed', :w_elapsed, ' ') || '  ' ||
         LPAD('%age', :w_percentage, ' ') || '  ' ||
         LPAD('Calls', :w_calls, ' ') || '  ' ||
         LPAD('Average', :w_average, ' ') || '  ' ||
         LPAD('Min', :w_min, ' ') || '  ' ||
         LPAD('Max', :w_max, ' ') || '  ' ||
         LPAD('Results', :w_results, ' ')
    FROM dual;

  SELECT LPAD('---', :w_level, ' ') || '  ' ||
         RPAD('--------', :w_function, ' ') || '  ' ||
         LPAD('-------', :w_elapsed, ' ') || '  ' ||
         LPAD('----', :w_percentage, ' ') || '  ' ||
         LPAD('-----', :w_calls, ' ') || '  ' ||
         LPAD('-------', :w_average, ' ') || '  ' ||
         LPAD('---', :w_min, ' ') || '  ' ||
         LPAD('---', :w_max, ' ') || '  ' ||
         LPAD('-------', :w_results, ' ')
    FROM dual;

  SELECT LPAD(oplevel, :w_level, ' ') || '  ' ||
         initial_pad || function_name || '  ' ||
         LPAD(elapsed_t, :w_elapsed, ' ') || '  ' ||
         LPAD(pct, :w_percentage, ' ') || '  ' ||
         LPAD(calls, :w_calls, ' ') || '  ' ||
         LPAD(average_t, :w_average, ' ') || '  ' ||
         LPAD(min_t, :w_min, ' ') || '  ' ||
         LPAD(max_t, :w_max, ' ') || '  ' ||
         LPAD(records, :w_results, ' ')
    FROM (SELECT ROWNUM as rn,
                 pr.bucket_id,
                 TO_CHAR(level) as oplevel,
                 SUBSTR(:pad_str, 1, 3 * (level-1)) as initial_pad,
                 RPAD(DECODE($rt, 0, pr.function,
                    DECODE(level, 1, TO_CHAR(CAST((FROM_TZ(CAST(TO_DATE('01/01/1970','DD/MM/YYYY') +
                       pr.effective_t/86400 AS TIMESTAMP),'+00:00') AT TIME ZONE '$ENV{TZ}') AS DATE),
                       'YYYY-MM-DD HH24:MI:SS'), pr.function)) || ' ',
                       :w_function - (3 * (level-1)), '.') as function_name,
                 TO_CHAR(pr.total_elapsed, '99990.999999') as elapsed_t,
                 TO_CHAR(pr.min_elapsed, '99990.999999') as min_t,
                 TO_CHAR(pr.max_elapsed, '99990.999999') as max_t,
                 TO_CHAR(pr.calls, '999999999') as calls,
                 TO_CHAR((100 * pr.total_elapsed) /
                         (SELECT SUM(pr2.total_elapsed)
                            FROM performance_results_t pr2
                           WHERE pr2.obj_id0 = :poid_id0
                             AND pr2.bucket_id = 0
                             AND pr2.parent_element_id = 0), '990.99') as pct,
                 TO_CHAR(DECODE(pr.calls, 0, 0, pr.total_elapsed/pr.calls),
                         '99990.999999') as average_t,
                 TO_CHAR(pr.records) as records
            FROM (
                 SELECT obj_id0,
                        parent_element_id,
                        MIN(rec_id) as rec_id,
                        bucket_id,
                        DECODE(bucket_id, 0, function,
                               'Bucket' || TO_CHAR(bucket_id, '00') ||
                               TO_CHAR(bucket_start, '90.999999') || ' - ' ||
                               TO_CHAR(bucket_end, '90.999999')) as function,
                        effective_t,
                        SUM(total_elapsed) as total_elapsed,
                        SUM(min_elapsed) as min_elapsed,
                        SUM(max_elapsed) as max_elapsed,
                        SUM(calls) as calls,
                        SUM(records) as records
                   FROM performance_results_t pr2
                  WHERE obj_id0 = :poid_id0
                    AND bucket_id <= :g_bucket
                    AND item_level <= :max_level
               GROUP BY obj_id0, parent_element_id, function, effective_t,
                        bucket_id, bucket_start, bucket_end
                 ) pr
      START WITH pr.parent_element_id = 0
CONNECT BY PRIOR pr.rec_id = pr.parent_element_id
ORDER SIBLINGS BY pr.bucket_id, pr.effective_t, pr.total_elapsed DESC)
THE_END

   sql_exec ($G_SQL, $sql, \$output, \$elapsed);

   if ($output =~ /ORA-/) {
      abort ("summary_report : failed - output[$output]");
   } else {
      printf "summary_report : generated in $elapsed seconds\n" if ($G_DEBUG);
      printf "%s\n", report_header ($href, 1, $elapsed);
      print $output . "\n";
   }
   return 0;
}

#------------------------------------------------------------------------------#
# Function     : detailed_report
#
# Description  : Produce a detailed report of data contained in the specified
#                /performance_snapshot object.
#
# Input        : poid       Poid of /performance_snapshot object
#                max_level  Max level to retrieve data in the report
#                href       Hash ref to performance info
#
# Output       : None
#
# Return       : 0 if all OK, non-zero if error
#------------------------------------------------------------------------------#
sub detailed_report {
   my ($poid, $max_level, $href) = @_;

   my $output = "";
   my $elapsed = 0;
   my $pad_str = "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  " .
                 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  " .
                 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  " .
                 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  ";

   my $sql = <<THE_END;
SET LINES 300
SET TRIM ON
SET PAGES 0
SET FEEDBACK OFF
SET TAB OFF
VAR poid_id0 NUMBER;
EXEC:poid_id0 := $poid;
VAR max_level NUMBER;
EXEC :max_level := $max_level;
VAR w_level NUMBER;
EXEC :w_level := $G_WIDTH{level};
VAR w_function NUMBER;
EXEC :w_function := $G_WIDTH{function};
VAR w_elapsed NUMBER;
EXEC :w_elapsed := $G_WIDTH{elapsed};
VAR w_percentage NUMBER;
EXEC :w_percentage := $G_WIDTH{percentage};
VAR w_calls NUMBER;
EXEC :w_calls := $G_WIDTH{calls};
VAR w_average NUMBER;
EXEC :w_average := $G_WIDTH{average};
VAR w_min NUMBER;
EXEC :w_min := $G_WIDTH{min};
VAR w_max NUMBER;
EXEC :w_max := $G_WIDTH{max};
VAR w_results NUMBER;
EXEC :w_results := $G_WIDTH{results};
VAR pad_str VARCHAR2(1024);
EXEC :pad_str := '$pad_str';
VAR g_bucket NUMBER;
EXEC :g_bucket := $G_BUCKETS;

  SELECT LPAD('Lvl', :w_level, ' ') || '  ' ||
         RPAD('Function', :w_function, ' ') || '  ' ||
         LPAD('Elapsed', :w_elapsed, ' ') || '  ' ||
         LPAD('%age', :w_percentage, ' ') || '  ' ||
         LPAD('Calls', :w_calls, ' ') || '  ' ||
         LPAD('Average', :w_average, ' ') || '  ' ||
         LPAD('Min', :w_min, ' ') || '  ' ||
         LPAD('Max', :w_max, ' ') || '  ' ||
         LPAD('Results', :w_results, ' ')
    FROM dual;

  SELECT LPAD('---', :w_level, ' ') || '  ' ||
         RPAD('--------', :w_function, ' ') || '  ' ||
         LPAD('-------', :w_elapsed, ' ') || '  ' ||
         LPAD('----', :w_percentage, ' ') || '  ' ||
         LPAD('-----', :w_calls, ' ') || '  ' ||
         LPAD('-------', :w_average, ' ') || '  ' ||
         LPAD('---', :w_min, ' ') || '  ' ||
         LPAD('---', :w_max, ' ') || '  ' ||
         LPAD('-------', :w_results, ' ')
    FROM dual;

  SELECT LPAD(oplevel, :w_level, ' ') || '  ' ||
         initial_pad || function_name || '  ' ||
         LPAD(elapsed_t, :w_elapsed, ' ') || '  ' ||
         LPAD(pct, :w_percentage, ' ') || '  ' ||
         LPAD(calls, :w_calls, ' ') || '  ' ||
         LPAD(average_t, :w_average, ' ') || '  ' ||
         LPAD(min_t, :w_min, ' ') || '  ' ||
         LPAD(max_t, :w_max, ' ') || '  ' ||
         LPAD(records, :w_results, ' ')
    FROM (SELECT ROWNUM as rn,
                 pr.bucket_id,
                 TO_CHAR(level) as oplevel,
                 SUBSTR(:pad_str, 1, 3 * (level-1)) as initial_pad,
                 RPAD(DECODE(pr.bucket_id, 0,
                             function || ' ('||pr.filename||'['||
                                         TO_CHAR(pr.line_number)||']'||
                                         pr.object_type||') ',
                             'Bucket' || TO_CHAR(bucket_id, '00') ||
                             TO_CHAR(bucket_start, '90.999999') || ' - ' ||
                             TO_CHAR(bucket_end, '90.999999')),
                      :w_function - (3 * (level-1)),
                      '.') as function_name,
                 TO_CHAR(pr.total_elapsed, '99990.999999') as elapsed_t,
                 TO_CHAR(pr.min_elapsed, '99990.999999') as min_t,
                 TO_CHAR(pr.max_elapsed, '99990.999999') as max_t,
                 TO_CHAR(pr.calls, '999999999') as calls,
                 TO_CHAR((100 * pr.total_elapsed) /
                         (SELECT SUM(pr2.total_elapsed)
                            FROM performance_results_t pr2
                           WHERE pr2.obj_id0 = :poid_id0
                             AND pr2.bucket_id = 0
                             AND pr2.parent_element_id = 0), '990.99') as pct,
                 TO_CHAR(DECODE(pr.calls, 0, 0, pr.total_elapsed/pr.calls),
                         '99990.999999') as average_t,
                 TO_CHAR(pr.records) as records
            FROM performance_results_t pr
           WHERE pr.obj_id0 = :poid_id0
             AND bucket_id <= :g_bucket
             AND pr.item_level <= :max_level
      START WITH pr.parent_element_id = 0
             AND pr.obj_id0 = :poid_id0
CONNECT BY PRIOR pr.rec_id = pr.parent_element_id
             AND pr.obj_id0 = :poid_id0
ORDER SIBLINGS BY pr.bucket_id, pr.total_elapsed DESC)
THE_END

   sql_exec ($G_SQL, $sql, \$output, \$elapsed);

   if ($output =~ /ORA-/) {
      abort ("detailed_report : failed - output[$output]");
   } else {
      printf "detailed_report : generated in $elapsed seconds\n" if ($G_DEBUG);
      printf "%s\n", report_header ($href, 0, $elapsed);
      print $output . "\n";
   }
   return 0;
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
my $connect_str = $G_DEF_CONN_STR;
my %opt = ();
my $summary = 0;  # Default to detailed report
my $mode = "";
my $max_level = 999;
my $rpt_width = 130;
my $poid = 0;
my $from = 0;
my $to = 0;
my $name = "";
my $buckets = 0;

#
# Check options ...
#
getopts('hdl:c:n:f:t:w:b', \%opt) or usage();
if ($opt{h}) { usage() }
if ($opt{d}) { $G_DEBUG = 1 }
if ($opt{c}) { $connect_str = $opt{c} }
if ($opt{l}) {
   $max_level = $opt{l};
   abort ("bad -l option value - must be >= 1") if ($max_level < 1);
}
if ($opt{w}) { $rpt_width = $opt{w} }
if ($opt{n}) { $name = $opt{n} }
if ($opt{f}) {
   $from = yyyymmdd_hhmiss_to_unix($opt{f});
   usage() if ($from < 0);
}
if ($opt{t}) {
   $to = yyyymmdd_hhmiss_to_unix($opt{t});
   usage() if ($to < 0);
}
if ($opt{b}) { $G_BUCKETS = 999999999 }

if (scalar(@ARGV) == 2) {
   $mode = "REPORT";
   if ($ARGV[0] =~ /summary/i) {
      $summary = 1;
   } elsif ($ARGV[0] =~ /detail/i) {
      $summary = 0;
   } else {
      usage();
   }
   $poid = $ARGV[1];
} elsif (scalar(@ARGV) == 1) {
   if ($ARGV[0] =~ /list/i) {
      $mode = "LIST";
   } else {
      usage();
   }
} else {
   usage();
}

#
# Default to GMT if TZ not set ...
#
$ENV{TZ} = 'GMT' if (!$ENV{TZ});

#
# Check report width is at least as much as minimum ... Any extra is added to
# the 'functions' column (which is the only one which is not a fixed-width)
#
my $width = get_report_width(); 
if ($rpt_width < $width) {
   abort ("main : report width $rpt_width must be >= $width");
}
$G_WIDTH{function} += ($rpt_width - $width);

#
# Open SQL connection ...
#
$G_SQL = sql_open ($connect_str);
abort ("main : failed connecting to '$connect_str'") if (!defined($G_SQL));

#
# Set cursor-sharing = force for this session to avoid generating lots of
# SQL (as we're not using bind-variables... naughty, but not sure if this is
# supported in GG/Sqlplus.pm)
# 
my $output = "";
sql_exec ($G_SQL, "alter session set cursor_sharing = FORCE;\n",
          \$output, undef);

if ($mode eq "REPORT") {
   #
   # Validate the presence of the /performance_snapshot object and get some
   # basic header information ...
   #
   my $data = get_performance_snapshot ($poid);
   if ($data->{poid_id0} <= 0) {
      abort ("main : failed locating 0.0.0.1 /performance_snapshot $poid");
   }

   if ($summary) {
      if ($data->{poid_type} =~ /realtime/ && !$ENV{TZ}) {
         # Default to GMT
         $ENV{TZ} = 'GMT';
         printf STDERR "\nWARNING: TZ variable not set, defaulting to GMT!\n\n";
      }
      summary_report ($poid, $max_level, $data);
   } else {
      if ($data->{poid_type} =~ /realtime/) {
         abort ("main : detailed report is not allowed for realtime data");
      } else {
         detailed_report ($poid, $max_level, $data);
      }
   }
} elsif ($mode eq "LIST") {
   list_snapshots ($name, $from, $to);
}

sql_close ($G_SQL);
exit (0);
