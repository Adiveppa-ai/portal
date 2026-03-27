# Copyright (c) 2020, Oracle and/or its affiliates. 
#------------------------------------------------------------------------------#
# SCRIPT: perfd.pl
#
# DESCRIPTION:
#
# Script to monitor one or more perflib output directories and collect files
# which need loading and process them. Loaded files will be archived. This may
# also be used to collect and load real-time data retrieved from a perflib
# memory mapped file.
#
# INFORMATION:
#
# BRM Performance Tools
#
# REVISION:
#
# $Revision: 1.15 $
# $Author: ihargrea $
# $Date: 2019/11/11 11:24:45 $
#------------------------------------------------------------------------------#

#------------------------------------------------------------------------------#
#                     M O D U L E   I N C L U S I O N
#------------------------------------------------------------------------------#
use strict;
use File::Basename;
use Getopt::Std;
use Sys::Hostname;
use Data::Dumper;
use POSIX qw(mktime);
use GG::Sqlplus;
use Time::HiRes;

#------------------------------------------------------------------------------#
#             C O N S T A N T S   A N D   D E F A U L T S 
#------------------------------------------------------------------------------#
#
# Field positions in record ...
#
use constant {
   #
   # Start record ...
   #
   S_FLD_OPSTATUS     => 0,
   S_FLD_OPLEVEL      => 1,
   S_FLD_OPID         => 2,
   S_FLD_OPCODE       => 3,
   S_FLD_OPFLAGS      => 4,
   S_FLD_OPNAME       => 5,
   S_FLD_OPTIME       => 6,
   S_FLD_FNAME        => 7,
   S_FLD_LINENO       => 8,
   S_FLD_PID          => 9,
   S_FLD_TID          => 10,
   S_FLD_PROGRAM      => 11,
   S_FLD_BUCKET_ID    => 12,
   S_FLD_OBJ_TYPE     => 13,
   #
   # Finish record ...
   #
   F_FLD_OPSTATUS     => 0,
   F_FLD_OPTIME       => 1,
   F_FLD_REC_COUNT    => 2,
   F_FLD_CALLS        => 3,
   F_FLD_MIN          => 4,
   F_FLD_MAX          => 5,
   F_FLD_BUCKET_START => 6,
   F_FLD_BUCKET_END   => 7,
   F_FLD_CACHE_CALLS  => 8,
   F_FLD_CACHE_TIME   => 9,
   F_FLD_ERRORS       => 10,
   F_FLD_USER_CPU     => 11,
   F_FLD_SYSTEM_CPU   => 12,
};

our $DEF_LOGFILE = "perfd.log";
our $DEF_FREQUENCY = 60;         # 1 minute
our $DEF_RT_FREQUENCY = 30;      # 30 seconds
our $DEF_RT_FREQUENCY_UNIT = ""; # seconds (not aligned)
our $DEF_SQL_FREQUENCY = "15m";  # 15 minutes
our $DEF_PURGE_FREQUENCY = 300;  # 5 minutes
our $DEF_PURGE_DELAY = "";       # No purging by default ...
our $DEF_ARCHIVE_DIR = "archive";
our $DEF_PIDFILE = "perfd.pid";
our $DEF_AGGREGATION_PERIOD = "30m";
our $DEF_RECID_MAP_CLEANUP_OFFSET = 15 * 60;   # 30 minutes;

#------------------------------------------------------------------------------#
#                  G L O B A L   V A R I A B L E S 
#------------------------------------------------------------------------------#
our $G_VERSION = do {my $v = '$Revision: 1.15 $'; $v =~ s/[^\d\.]//g; $v};
our @G_RT_FILES = ();
our @G_DIRLIST = ();
our $G_EXIT_REQUESTED = 0;
our $G_DEBUG = 0;
our $G_CMD = "perfd";
our $G_NOWAIT = 0;
our $G_FREQUENCY = $DEF_FREQUENCY;
our $G_RT_FREQUENCY = $DEF_RT_FREQUENCY;
our $G_RT_FREQUENCY_UNIT = $DEF_RT_FREQUENCY_UNIT;
our $G_SQL_FREQUENCY = $DEF_SQL_FREQUENCY;
our $G_SQL_AGGR_PERIOD = 0;
our $G_SQL_AGGR_UNIT = "";
our $G_SQL_COLLECT = 0;
our $G_PURGE_FREQUENCY = $DEF_PURGE_FREQUENCY;
our $G_PURGE_DELAY = $DEF_PURGE_DELAY;
our $G_LOGFILE_NAME = "$DEF_LOGFILE";
our $G_LOGFILE_OPEN = 0;
our $G_ARCHIVE_DIR = $DEF_ARCHIVE_DIR;
our $G_ARCHIVE_ONLY = 0;
our $G_DELETE_FILES = 0;
our $G_PIDFILE = $DEF_PIDFILE;
our $G_AGGR_PERIOD = 0;
our $G_AGGR_UNIT = "";
our $G_DB_ALIAS = "";
our $G_DB_USER = "";
our $G_DB_PASSWD = "";
our $G_CONN_STR = "";
our $G_DEF_CONN_STR = "pin/pin\@pindb";
our $G_SQL = undef;
our $G_PERF_TYPE = "/performance_snapshot";
our $G_RT_PERF_TYPE = "/performance_snapshot/realtime";
our $G_HOSTNAME = hostname();
our %G_RECID_MAPS = ();
our $G_RECID_MAP_CLEANUP_OFFSET = $DEF_RECID_MAP_CLEANUP_OFFSET;
our $G_MAIN_PID = 0;

#------------------------------------------------------------------------------#
# Function     : parse_fname
#
# Description  : Parse a Perflib file name to extract basic information.
#
# Input        : fname   Filename to be processed
#
# Output       : None
#
# Return       : [ $tag, $pid, $from_t, $to_t ]
#------------------------------------------------------------------------------#
sub parse_fname {
   my ($fname) = @_;

   my ($f_yyyy, $f_mm, $f_dd, $f_hh, $f_mi, $f_ss);
   my ($t_yyyy, $t_mm, $t_dd, $t_hh, $t_mi, $t_ss);
   my ($from_t, $to_t, $tag, $pid);

   # perf_log.25637.20120423_223000.20120423_224000.plog.txt
   # or
   # perf_log.16909.20120524_120000.20120524_130000.1337855755.plog.txt

   if ($fname =~ /([^\.]*)\.(\d*)\.(\d\d\d\d)(\d\d)(\d\d)_(\d\d)(\d\d)(\d\d)\.
                  (\d\d\d\d)(\d\d)(\d\d)_(\d\d)(\d\d)(\d\d)(\.\d+)?
                  \.plog\.txt/x)
   {
      $tag = $1;
      $pid = $2;
      $f_yyyy = $3;
      $f_mm = $4;
      $f_dd = $5;
      $f_hh = $6;
      $f_mi = $7;
      $f_ss = $8;

      $t_yyyy = $9;
      $t_mm = $10;
      $t_dd = $11;
      $t_hh = $12;
      $t_mi = $13;
      $t_ss = $14;

      $from_t = mktime($f_ss, $f_mi, $f_hh, $f_dd, $f_mm-1,
                       $f_yyyy-1900, undef, undef, -1) + 0;

      $to_t = mktime($t_ss, $t_mi, $t_hh, $t_dd, $t_mm-1,
                     $t_yyyy-1900, undef, undef, -1) + 0;

      log_msg ("D", "parse_fname : tag[$tag] pid[$pid] from_t[$from_t] " .
                    "to_t[$to_t]");

      return ($tag, $pid, $from_t, $to_t);
   }
   return undef;
}

#------------------------------------------------------------------------------#
# Function     : pre_aggregate_log
#
# Description  : Pre-aggregates the log-file records to improve performance
#
# Input        : fname   log file name
#
# Output       : None
#
# Return       : aggregation array reference and hash reference
#------------------------------------------------------------------------------#
sub pre_aggregate_log {
   my ($fname) = @_;

   my @stacked_keys = ();
   my %agg_data = ();
   my $lno = 0;
   my $t = Time::HiRes::time();

   #
   # Parse the log file and, as we go key up all the opcodes we
   # have and aggregate the statistics ...
   #
   open (LOGF, "<$fname") or die ("failed opening[$fname]");
   while (<LOGF>) {
      ++$lno;
      chomp;

      my @rec = split(/,/, $_);

      if ($rec[S_FLD_OPSTATUS] eq "S") {
         #
         # Start record - just push position. The key must ensure ordering
         # according to the opcode hierarchy, and buckets.
         #
         my $key = join ("|", $rec[S_FLD_OPCODE],
                              $rec[S_FLD_OPFLAGS],
                              $rec[S_FLD_OPNAME],
                              $rec[S_FLD_PROGRAM],
                              $rec[S_FLD_OBJ_TYPE],
                              $rec[S_FLD_FNAME],
                              $rec[S_FLD_LINENO],
                              sprintf("%03d",$rec[S_FLD_BUCKET_ID]));
         push(@stacked_keys, $key);
         my $full_key = join("-", @stacked_keys);
         if (!exists($agg_data{$full_key}{s})) {
            $agg_data{$full_key}{s} = \@rec;
         }
      } else {
         #
         # Finish record - add to aggregated data ...
         #
         my $full_key = join("-", @stacked_keys);
         pop(@stacked_keys);

         if (exists($agg_data{$full_key}{f})) {
            my $rec_ref = $agg_data{$full_key}{f};
            $rec_ref->[F_FLD_CALLS] += $rec[F_FLD_CALLS];
            $rec_ref->[F_FLD_CACHE_CALLS] += $rec[F_FLD_CACHE_CALLS];
            $rec_ref->[F_FLD_CACHE_TIME] += $rec[F_FLD_CACHE_TIME];
            $rec_ref->[F_FLD_REC_COUNT] += $rec[F_FLD_REC_COUNT];
            $rec_ref->[F_FLD_OPTIME] += $rec[F_FLD_OPTIME];
            $rec_ref->[F_FLD_ERRORS] += $rec[F_FLD_ERRORS];
            $rec_ref->[F_FLD_USER_CPU] += $rec[F_FLD_USER_CPU];
            $rec_ref->[F_FLD_SYSTEM_CPU] += $rec[F_FLD_SYSTEM_CPU];
            if ($rec[F_FLD_CALLS] > 0 &&
                $rec[F_FLD_MIN] < $rec_ref->[F_FLD_MIN])
            {
               $rec_ref->[F_FLD_MIN] = $rec[F_FLD_MIN];
            }
            if ($rec[F_FLD_CALLS] > 0 &&
                $rec[F_FLD_MAX] > $rec_ref->[F_FLD_MAX])
            {
               $rec_ref->[F_FLD_MAX] = $rec[F_FLD_MAX];
            }
         } else {
            $agg_data{$full_key}{f} = \@rec;
         }
      }
   }
   close (LOGF);

   log_msg ("D", Data::Dumper->Dump ([\%agg_data], ["agg_data"])) if ($G_DEBUG);

   #
   # OK, now we have aggregated data, build a hierarchical (S)tart / (F)inish
   # set of logs.
   #
   my @agg_file = ();
   my @stacked_keys = ();
   my $last_key = "";

   foreach my $key (sort keys %agg_data) {
      if ($last_key eq "" ||
          ($agg_data{$last_key}{s}->[S_FLD_OPLEVEL] <
              $agg_data{$key}{s}->[S_FLD_OPLEVEL]))
      {
         # Descending ... stack it ...
         my %rec = (type => "S",
                    srec => $agg_data{$key}{s},
                    frec => $agg_data{$key}{f});
         push(@agg_file, \%rec);
         push(@stacked_keys, $key);
      } else {
         # Same level or lower, pop everything ...
         while ($agg_data{$key}{s}->[S_FLD_OPLEVEL] < scalar(@stacked_keys)) {
            my $pop_key = pop(@stacked_keys);
            my %rec = (type => "F",
                       srec => $agg_data{$pop_key}{s},
                       frec => $agg_data{$pop_key}{f});
            push(@agg_file, \%rec);
         }
         my %rec = (type => "S",
                    srec => $agg_data{$key}{s},
                    frec => $agg_data{$key}{f});
         push(@agg_file, \%rec);
         push(@stacked_keys, $key);
      }
      $last_key = $key;
   }
   # Pop what's left
   while (my $key = pop(@stacked_keys)) {
      my %rec = (type => "F",
                 srec => $agg_data{$key}{s},
                 frec => $agg_data{$key}{f});
      push(@agg_file, \%rec);
   }
   if ($G_DEBUG > 1) {
      log_msg ("D", Data::Dumper->Dump ([\@agg_file], ["agg_file"]));
   }
   my $n = scalar(@agg_file);
   $t = sprintf ("%.6f", Time::HiRes::time() - $t);
   my $f = basename($fname);
   log_msg ("I", "aggregated file[$f] lines before[$lno] after[$n] - " .
            "elapsed[$t]");

   return ( \@agg_file, \%agg_data);
}

#------------------------------------------------------------------------------#
# Function     : get_performance_snapshot
#
# Description  : Find a matching snapshot record in the BRM database - it will
#                be created if it doesn't exist.
#
# Input        : type    Type of snapshot (realtime or normal)
#                host    Hostname
#                tag     Tag name of snapshot
#                pid     PID of application
#                from_t  Period start
#                to_t    Period end
#
# Output       : None
#
# Return       : poid (string) of object created
#------------------------------------------------------------------------------#
sub get_performance_snapshot {
   my ($type, $host, $tag, $pid, $from_t, $to_t) = @_;
   my $poid = "";
   my $now = time();
   my $duration = $to_t - $from_t;

   log_msg ("D", "get_performance_snapshot : type[$type] host[$host] " .
                 "tag[$tag] pid[$pid] from_t[$from_t] to_t[$to_t]");

   #
   # Search ...
   #
   my (%fields) = ( poid_id0 => 'p.poid_id0',
                    poid_rev => 'p.poid_rev',
                    hostname => 'p.hostname',
                    name     => 'p.name',
                    start_t  => 'p.start_t',
                    end_t    => 'p.end_t',
                    pid      => 'p.pid' );
   my $sql_body = "  from performance_snapshot_t p " .
                  " where p.poid_type = '$type' " .
                  "   and p.hostname = '$host' " .
                  "   and p.name = '$tag' " .
                  "   and p.pid = $pid " .
                  "   and p.start_t = $from_t " .
                  "   and p.end_t = $to_t";
   my $output;
   my $elapsed;

   my $results = sql_query ($G_SQL, $sql_body, \%fields, "|", 0, \$elapsed);

   log_msg ("D", "get_performance_snapshot : searched for object - " .
            "elapsed[$elapsed]");
   if ($G_DEBUG > 1) {
      log_msg ("D", Data::Dumper->Dump ([$results], ["result_array"]));
   }

   #
   # Check if we found anything... if not, we must create the new row.
   #
   if (scalar(@{$results}) <= 0) {
      sql_exec ($G_SQL,
         "INSERT INTO performance_snapshot_t (" .
         "   poid_db, poid_id0, poid_type, poid_rev," .
         "   hostname, name, start_t, end_t, duration_seconds," .
         "   pid, created_t, mod_t, account_obj_db, account_obj_id0, " .
         "   account_obj_type, account_obj_rev, read_access, write_access)" .
         "VALUES (" .
         "   1, pin_sequence.get_nextval(), '$type', 1," .
         "   '$host', '$tag', $from_t, $to_t, $duration," .
         "   $pid, $now, $now, 1, 1, '/account', 1, 'L', 'L');",
         \$output, \$elapsed);

         if ($output =~ /ORA-/) {
            log_msg ("E", "failed insert into performance_snapshot_t - " .
                          "output:\n$output\n");
            return undef;
         }
         log_msg ("D", "get_performance_snapshot : created new object - " .
                  "elapsed[$elapsed]");
         return get_performance_snapshot ($type, $host, $tag, $pid,
                                          $from_t, $to_t);
   } 
   return $$results[0]->{poid_id0};
}

#------------------------------------------------------------------------------#
# Function     : get_next_rec_id
#
# Description  : Get the next rec_id for use in the map.
#
# Input        : map_ref   Map reference
#
# Output       : None
#
# Return       : Next rec_id to use
#------------------------------------------------------------------------------#
sub get_next_rec_id {
   my ($map_ref) = @_;

   my $max_rec_id = 0;

   while (my ($key, $value) = each %{$map_ref}) {
      if ($value > $max_rec_id) {
         $max_rec_id = $value;
      }
   }

   return $max_rec_id + 1;
}

#------------------------------------------------------------------------------#
# Function     : get_rec_id_map
#
# Description  : Retrieve all the current rec_id information for the snapshot.
#
# Input        : poid             Poid of /performance_snapshot object
#
# Output       : None
#
# Return       : hash reference to rec_ids
#------------------------------------------------------------------------------#
sub get_rec_id_map {
   my ($poid_id0) = @_;

   log_msg ("D", "get_rec_id_map : poid_id0[$poid_id0]");

   my (%fields) = ( rec_id => 'r.rec_id',
                    parent_element_id => 'r.parent_element_id',
                    item_level => 'r.item_level',
                    function => 'r.function',
                    program_name => 'NVL(r.program_name,\'NULL\')',
                    obj_type => 'NVL(r.object_type,\'NULL\')',
                    filename => 'NVL(r.filename,\'NULL\')',
                    bucket_id => 'r.bucket_id',
                    effective_t => 'r.effective_t');
   my $sql_body = "  from performance_results_t r " .
      " where r.obj_id0 = $poid_id0 ";
   my $output;
   my $elapsed;

   log_msg ("D", "get_rec_id_map : sql_body[$sql_body]");

   my $results = sql_query ($G_SQL, $sql_body, \%fields, "|", 0, \$elapsed);

   if ($G_DEBUG > 1) {
      log_msg ("D", Data::Dumper->Dump ([$results], ["search_results"]));
   }

   my %map = ();
   foreach my $ref (@{$results}) {
      my $key = join ("|", $ref->{parent_element_id},
                           $ref->{item_level},
                           $ref->{function},
                           $ref->{program_name},
                           $ref->{obj_type},
                           $ref->{filename},
                           $ref->{bucket_id},
                           $ref->{effective_t});
      $map{$key} = $ref->{rec_id};
   }

   log_msg ("D", Data::Dumper->Dump ([\%map], ["map"])) if ($G_DEBUG > 1);

   return \%map;
}

#------------------------------------------------------------------------------#
# Function     : insert_level
#
# Description  : Find and, if necessary, create a particuler level in the
#                hierarchy. The numbers are updated later, this just creates
#                the appropriate place-holder in the tree.
#
# Input        : poid             Poid of /performance_snapshot object
#                rec_id           Specific rec_id to create (or -1)
#                parent_elem_id   Level of parent (rec_id)
#                level            Level of function
#                opname           Function name
#                opflags          Operation flags
#                filename         File name
#                lineno           Line number
#                program          Program name
#                obj_type         Object type
#                bucket_id        Bucket ID
#                bucket_start     Bucket start
#                bucket_end       Bucket end
#                effective_t      Effective time
#                map_ref          Hash reference for mapping
#
# Output       : None
#
# Return       : rec_id of row (-1 for error)
#------------------------------------------------------------------------------#
sub insert_level {
   my ($poid, $rec_id, $parent_elem_id, $oplevel, $opname, $opflags, $filename,
       $lineno, $program, $obj_type, $bucket_id, $bucket_start, $bucket_end,
       $effective_t, $map_ref) = @_;

   my $must_insert = 1;  # Assume we'll create something ...

   log_msg ("D", "insert_level : poid[$poid] rec_id[$rec_id] " .
                 "parent_elem_id[$parent_elem_id] oplevel[$oplevel] " .
                 "opname[$opname] opflags[$opflags] filename[$filename] " .
                 "lineno[$lineno] program[$program] obj_type[$obj_type] " .
                 "bucket_id[$bucket_id] bucket_start[$bucket_start] " .
                 "bucket_end[$bucket_end] effective_t[$effective_t] " .
                 "map_ref[$map_ref]");

   #
   # If a specific rec_id isn't provided, search for entry to see if one
   # already exists... In the case of real-time data, we must look up the
   # appropriate value. 
   #
   if ($rec_id < 0) {
      if ($map_ref) {
         my $key = join("|", "$parent_elem_id",
                             "$oplevel",
                             "$opname",
                             $program ? "$program" : "NULL",
                             $obj_type ? "$obj_type" : "NULL",
                             $filename ? "$filename" : "NULL",
                             $bucket_id,
                             $effective_t);
                          
         $rec_id = $map_ref->{$key};

         log_msg ("D", "insert_level : search key[$key] => rec_id[$rec_id]");

         if (!defined($rec_id)) {
            #
            # Didn't find it, so we must create a record. First find the next
            # available record id, then insert into our map for future referene.
            #
            $rec_id = get_next_rec_id ($map_ref);
            $map_ref->{$key} = $rec_id;
            log_msg ("D", "insert_level : got next rec_id[$rec_id]");
         } else {
            #
            # We already have it, no need to insert ...
            #
            $must_insert = 0;
         }
      } else { 
         #
         # No map-ref ... must search DB ...
         #
         my (%fields) = ( rec_id => 'MAX(rec_id)');
         my $sql_body = "  from performance_results_t r " .
                        " where r.obj_id0 = $poid";
         my $output;
         my $elapsed;

         my $results = sql_query ($G_SQL, $sql_body, \%fields, "|", 0,
                                  \$elapsed);

         if (scalar(@{$results}) <= 0) {
            $rec_id = 1;
         } else {
            $rec_id = $$results[0]->{rec_id} + 1;
         }
         log_msg ("D", "insert_level : found MAX(rec_id)[$rec_id]");
      }
   }

   #
   # OK, if we need to then insert a new row. The rec_id has
   # already been calculated.
   #
   if ($must_insert) {
      my $output;
      my $elapsed;

      sql_exec ($G_SQL,
         "INSERT INTO performance_results_t (" .
         "   obj_id0, rec_id, parent_element_id, item_level, " .
         "   program_name, function, flags, filename, " .
         "   line_number, calls, records, effective_t, " .
         "   total_elapsed, min_elapsed, max_elapsed, " .
         "   cache_count, cache_elapsed, errors, " .
         "   user_cpu_time, system_cpu_time, object_type, " .
         "   bucket_id, bucket_start, bucket_end ) " .
         "VALUES (" .
         "   $poid, $rec_id, $parent_elem_id, $oplevel, " .
         "   '$program', '$opname', $opflags, '$filename', " .
         "   $lineno, 0, 0, $effective_t, " .
         "   0, 0, 0, " .
         "   0, 0, 0, " .
         "   0, 0, '$obj_type', " .
         "   $bucket_id, ROUND($bucket_start,9), ROUND($bucket_end,9) );",
         \$output, \$elapsed);

      if ($output =~ /ORA-/) {
         log_msg ("E", "insert_level : failed insert into " .
                       "performance_results_t - output:\n$output\n");
         return -1;
      }
      log_msg ("D", "insert_level : inserted new rec_id[$rec_id] " .
                    "elapsed[$elapsed]");
   }
   log_msg ("D", "insert_level : return rec_id[$rec_id]");
   return $rec_id;
}

#------------------------------------------------------------------------------#
# Function     : update_level
#
# Description  : Update a particuler level in the hierarchy ...
#
# Input        : poid           Poid of /performance_snapshot object
#                rec_id         Record ID
#                records        Records retrieved
#                calls          Executions
#                total_elapsed  Total elapsed execution time
#                min_elapsed    Minimum elapsed
#                max_elapsed    Maximum elapsed
#                cache_count    Cache calls
#                cache_elapsed  Cache elapsed time
#                errors         Error count
#                u_cpu          User CPU
#                s_cpu          System CPU
#
# Output       : None
#
# Return       : 1 if all OK, 0 if error
#------------------------------------------------------------------------------#
sub update_level {
   my ($poid, $rec_id, $records, $calls, $total_elapsed, $min_elapsed,
       $max_elapsed, $cache_count, $cache_elapsed, $errors, $u_cpu,
       $s_cpu) = @_;
   my $output = "";
   my $elapsed = 0;

   log_msg ("D", "update_level : poid[$poid] rec_id[$rec_id] " .
            "calls[$calls] records[$records]  " .
            "total_elapsed[$total_elapsed] min_elapsed[$min_elapsed] " .
            "max_elapsed[$max_elapsed] cache_count[$cache_count] " .
            "cache_elapsed[$cache_elapsed] errors[$errors] u_cpu[$u_cpu] " .
            "s_cpu[$s_cpu]");

   #
   # Update ...
   #
   sql_exec ($G_SQL,
      "UPDATE performance_results_t SET " .
      "   calls = calls + $calls, " .
      "   records = records + $records, " .
      "   total_elapsed = total_elapsed + ROUND($total_elapsed,9),  " .
      "   min_elapsed = min_elapsed + ROUND($min_elapsed,9), " .
      "   max_elapsed = max_elapsed + ROUND($max_elapsed,9), " .
      "   cache_count = cache_count + $cache_count, " .
      "   cache_elapsed = cache_elapsed + ROUND($cache_elapsed,9), " .
      "   errors = errors + $errors, " .
      "   user_cpu_time = user_cpu_time + ROUND($u_cpu,9), " .
      "   system_cpu_time = system_cpu_time + ROUND($s_cpu,9) " .
      " WHERE obj_id0 = $poid " .
      "   AND rec_id = $rec_id;",
      \$output, \$elapsed);

   if ($output =~ /ORA-/) {
      log_msg ("E", "update_level : failed updating " .
                     "performance_results_t:\n$output\n");
      return 0;
   } else {
      log_msg ("D", "update_level : updated rec_id[$rec_id] - " .
                    "output[$output] elapsed[$elapsed]");
   }
   return 1;
}

#------------------------------------------------------------------------------#
# Function     : validate_aggregation_period
#
# Description  : Determines whether an aggregtion period (defined as <x>[H|M|S])
#                is valid and (optionally) returns the period and unit.
#
# Input        : str          Input string
#
# Output       : agg_p_ref    Aggregation period (width)
#                agg_u_ref    H, M or S
#
# Return       : 1 if all OK, 0 if error.
#------------------------------------------------------------------------------#
sub validate_aggregation_period {
   my ($str, $agg_p_ref, $agg_u_ref) = @_;
   my $valid = 0;
   my $period = 0;
   my $unit = "";
   #
   # Check for valid input data and retrieve period and unit ...
   #
   if ($str =~ /^\s*(\d+)([H|h|M|m|S|s])\s*$/) {
      $period = $1;
      $unit = uc($2);
      if ($unit eq "H") {
         if ($period > 0 && $period <= 24 && (24 % $period == 0)) {
            $valid = 1;
         }
      } elsif ($unit eq "M" || $unit eq "S") {
         if ($period > 0 && $period <= 60 && (60 % $period == 0)) {
            $valid = 1;
         }
      }
   } elsif ($str =~ /^\s*(\d+)\s*$/) {
      $period = $1;
   }
   #
   # Populate output references, unless we're just doing validation.
   #
   if ($valid) {
      $$agg_p_ref = $period if (defined($agg_p_ref));
      $$agg_u_ref = $unit if (defined($agg_u_ref));
   }
   return $valid;
}

#------------------------------------------------------------------------------#
# Function     : get_current_aggregation_period
#
# Description  : Gets the aggregation period for the current time.
#
# Input        : agg_period   Aggregation period (width)
#                agg_unit     Aggregation unit (H, M, S, or "" (unaligned))
#
# Output       : start_ref    Starting tstamp (UNIX)
#                end_ref      Ending tstmap (UNIX)
#
# Return       : 0 if all OK, non zero if error.
#------------------------------------------------------------------------------#
sub get_current_aggregation_period {
   my ($agg_period, $agg_unit, $start_ref, $end_ref) = @_;

   my ($ss, $mi, $hh, $dd, $mm, $yyyy, $wday, $yday, $isdst) = localtime();

   $$start_ref = 0;
   $$end_ref = 0;

   if ($agg_unit eq "H") {
      #
      # Round off the minutes and seconds and align the hour ...
      #
      $hh = int($hh / $agg_period) * $agg_period;
      $mi = 0;
      $ss = 0;
      $$start_ref = mktime ($ss, $mi, $hh, $dd, $mm, $yyyy,
                            $wday, $yday, -1) + 0;
      $hh += $agg_period;
      $$end_ref = mktime ($ss, $mi, $hh, $dd, $mm, $yyyy,
                          $wday, $yday, -1) + 0;

   } elsif ($agg_unit eq "M") {
      #
      # Round off the seconds and align the minutes ...
      #
      $mi = int($mi / $agg_period) * $agg_period;
      $ss = 0;
      $$start_ref = mktime ($ss, $mi, $hh, $dd, $mm, $yyyy,
                            $wday, $yday, -1) + 0;
      $mi += $agg_period;
      $$end_ref = mktime ($ss, $mi, $hh, $dd, $mm, $yyyy,
                          $wday, $yday, -1) + 0;

   } elsif ($agg_unit eq "S") {
      #
      # align seconds ...
      #
      $ss = int($ss / $agg_period) * $agg_period;
      $$start_ref = mktime ($ss, $mi, $hh, $dd, $mm, $yyyy,
                            $wday, $yday, -1) + 0;
      $ss += $agg_period;
      $$end_ref = mktime ($ss, $mi, $hh, $dd, $mm, $yyyy,
                          $wday, $yday, -1) + 0;
   } elsif ($agg_unit eq "") {
      #
      # unaligned seconds ...
      #
      $$start_ref = time();
      $$end_ref = $$start_ref + $agg_period;
   }

   return 0;
}

#------------------------------------------------------------------------------#
# Function     : insert_rt_data
#
# Description  : Inserts a real-time data set into a snapshot object. This will
#                create a new "top-level" summary object with the snapshot
#                timestamp and underneath that, the individual opcode totals.
#
# Input        : snap_poid    POID of /performance_snapshot/realtime object
#                effective_t  Data effective time
#                rt_data_ref  Array reference containing data objects to load
#
# Output       : None
#
# Return       : 1 if all OK, 0 if error.
#------------------------------------------------------------------------------#
sub insert_rt_data {
   my ($snap_poid, $effective_t, $rt_data_ref) = @_;

   my $total_calls = 0;
   my $total_errors = 0;
   my $total_records = 0;
   my $total_elapsed = 0;
   my $total_user_cpu = 0;
   my $total_system_cpu = 0;

   #
   # Calculate total times for all opcodes in this snapshot ...
   #
   foreach my $href (@{$rt_data_ref}) {
      $total_calls += $href->{calls};
      $total_errors += $href->{errors};
      $total_records += $href->{records};
      $total_elapsed += $href->{elapsed};
      $total_user_cpu += $href->{u_cpu};
      $total_system_cpu += $href->{s_cpu};
   }

   #
   # Insert first level summary and update totals ... We need to
   # get the next record ID using SQL ...
   #
   my $rec_id = insert_level ($snap_poid, -1, 0, 0, "RT_SUMMARY",
                              0, "", 0, "load_perf_data", "", 0, 0, 0,
                              $effective_t, undef);
   if ($rec_id < 0) {
      log_msg ("E", "insert_rt_data : failed inserting RT summary");
      return 0;
   }

   if (!update_level ($snap_poid, $rec_id, $total_records, $total_calls,
                      $total_elapsed, 0, 0, 0, 0, $total_errors,
                      $total_user_cpu, $total_system_cpu)) {
      log_msg ("E", "insert_rt_data : failed updating RT summary");
      return 0;
   }

   #
   # Insert all the individual rows ...
   # 
   my $new_rec_id = $rec_id;
   foreach my $href (@{$rt_data_ref}) {
      $new_rec_id += 1;

      my $output;
      my $elapsed;

      sql_exec ($G_SQL,
         "INSERT INTO performance_results_t (" .
         "   obj_id0, rec_id, parent_element_id, item_level, " .
         "   program_name, function, flags, filename, " .
         "   line_number, calls, records, effective_t, " .
         "   total_elapsed, min_elapsed, max_elapsed, " .
         "   cache_count, cache_elapsed, errors, " .
         "   user_cpu_time, system_cpu_time, object_type, " .
         "   bucket_id, bucket_start, bucket_end ) " .
         "VALUES (" .
         "   $snap_poid, $new_rec_id, $rec_id, 1, " .
         "   '$href->{program}', '$href->{opname}', $href->{opflags}, " .
         "   '$href->{filename}', " .
         "   $href->{line_no}, $href->{calls}, $href->{records}, " .
         "   $effective_t, " .
         "   ROUND($href->{elapsed},9), 0, 0, " .
         "   0, 0, $href->{errors}, " .
         "   ROUND($href->{u_cpu},9), ROUND($href->{s_cpu},9), " .
         "   '$href->{obj_type}', 0, 0, 0 );",
         \$output, \$elapsed);

      if ($output =~ /ORA-/) {
         log_msg ("E", "insert_rt_data : failed insert into " .
                       "performance_results_t - output:\n$output\n");
         return 0;
      }
      log_msg ("D", "insert_rt_data : inserted new rec_id[$new_rec_id] " .
                    "elapsed[$elapsed]");
   }

   return 1;
}

#------------------------------------------------------------------------------#
# Function     : get_pstatus_cmd
#
# Description  : Looks at the Perflib data file to determine what type of data
#                it contains (64-bit or 32-bit)
#
# Input        : fname   Filename to be processed
#
# Output       : None
#
# Return       : "pstatus" or "pstatus64"
#------------------------------------------------------------------------------#
sub get_pstatus_cmd {
   my ($fname) = @_;
   my $line = `head -1 $fname`;
   if ($line =~ /64/) {
      return "./pstatus64"; 
   } else {
      return "./pstatus";
   }
}

#------------------------------------------------------------------------------#
# Function     : is_running
#
# Description  : Function to check whether a particular process is running. It
#                uses the PID and (optionally) a name to check.
#
# Input        : pid    Process ID
#                name   Optional name to check
#
# Output       : None
#
# Return       : 1 if running, 0 if not
#------------------------------------------------------------------------------#
sub is_running {
   my ($pid, $name) = @_;
   my $rv;

   if ($name) {
      $rv = `ps -fp $pid | grep -v "PID" | grep "$name"`;
   } else {
      $rv = `ps -fp $pid | grep -v "PID"`;
   }

   if ($rv) {
      return 1;
   } else {
      return 0;
   }
}

#------------------------------------------------------------------------------#
# Function     : fmt_local_time
#
# Description  : Format a local time stamp (UNIX) into a human-readable time
#                string.
#
# Input        : t       Optional UNIX timestamp (default will be now)
#
# Output       : None
#
# Return       : Formatted date/time string
#------------------------------------------------------------------------------#
sub fmt_local_time {
   my ($t) = @_;
   $t = time() if (!defined($t));
   my ($ss, $mi, $hh, $dd, $mm, $yyyy, $wday, $yday, $isdst) = localtime($t);

   return sprintf "%04d/%02d/%02d %02d:%02d:%02d",
      $yyyy + 1900, $mm+1, $dd, $hh, $mi, $ss;
}
#------------------------------------------------------------------------------#
# Function     : log_msg
#
# Description  : Print message to log file ...
#
# Input        : level    (D)ebug, (E)rror, (I)nformation
#                msg      Message string(s) to print
#
# Output       : None
#
# Return       : None
#------------------------------------------------------------------------------#
sub log_msg {
   my $type = shift;
   return if ($type eq "D" && !$G_DEBUG);

   if (!$G_LOGFILE_OPEN) {
      open (G_LOGFILE, ">>$G_LOGFILE_NAME") or
         abort ("failed opening logfile[$G_LOGFILE_NAME]");
      $G_LOGFILE_OPEN = 1;
      select((select(G_LOGFILE), $|=1)[0]);  # Disable buffering ...
   }
   printf G_LOGFILE "$type %s : $G_CMD\[$$\] : %s\n", fmt_local_time(),
      join (" ", @_);
}

#------------------------------------------------------------------------------#
# Function     : abort
#
# Description  : Prints a message and exits the program ...
#
# Input        : errstr   Message(s) to print
#
# Output       : None
#
# Return       : None
#------------------------------------------------------------------------------#
sub abort {
   log_msg ("E", @_);
   printf STDERR "ERROR: %s\n", join(" ", @_);
   if (defined($G_SQL)) {
      sql_exec ($G_SQL, "rollback;", undef, undef);
      sql_close ($G_SQL);
   }
   exit (1);
}

#------------------------------------------------------------------------------#
# Function     : is_terminal
#
# Description  : Is the STDIN a terminal?
#
# Input        : None
#
# Output       : None
#
# Return       : 1 if a terminal, 0 otherwise
#------------------------------------------------------------------------------#
sub is_terminal {
   `tty -s`;
   return $? == 0 ? 1 : 0;
}

#------------------------------------------------------------------------------#
# Function     : ready_to_process
#
# Description  : Determines whether a file is ready to load (i.e. the end time
#                of the snapshot has been reached).
#
#                NOTE: a log file is of the format -
#
#                      perf_log.4651.20120516_232000.20120516_233000.plog.txt
#
#                      <application>.<pid>.<start_t>.<end_t>.plog.txt
#
#                      or (in the case that file-size limits apply and we
#                      create multiple files for the same period):
#
#                      <application>.<pid>.<start_t>.<end_t>.<tstamp>.plog.txt
#
# Input        : file   Trace file name
#
# Output       : None
#
# Return       : 1 if file ready to process, 0 otherwise
#------------------------------------------------------------------------------#
sub ready_to_process {
   my ($file) = @_;

   $file = basename($file);

   if ($G_NOWAIT) {
      log_msg ("D", "file[$file] is OK to load now - nowait option on");
      return 1;
   }
   my ($ss, $mi, $hh, $dd, $mm, $yyyy, $wday, $yday, $isdst) = localtime();
   my $now = sprintf ("%04d%02d%02d_%02d%02d%02d",
                      $yyyy+1900, $mm+1, $dd, $hh, $mi, $ss);

   my ($start_t, $end_t, $rename_seq);

   if ($file =~ /.*\.\d+\.[^.]+\.[^.]+\.plog.txt/) {
      ($start_t, $end_t) =
         ($file =~ /.*\.\d+\.([^.]+)\.([^.]+)\.plog\.txt/);
   } elsif ($file =~ /.*\.\d+\.[^.]+\.[^.]+\.\d+\.plog.txt/) {
      ($start_t, $end_t, $rename_seq) =
         ($file =~ /.*\.\d+\.([^.]+)\.([^.]+)\.(\d+)\.plog\.txt/);
   } else {
      log_msg ("E", "file[$file] has unrecognizable name");
      return -1;
   }

   if ($now gt $end_t) {
      log_msg ("D", "file[$file] is OK to load now[$now] end_t[$end_t]");
      return 1;
   } else {
      log_msg ("D", "file[$file] is KO for load now[$now] end_t[$end_t]");
      return 0;
   }
}

#------------------------------------------------------------------------------#
# Function     : load_file
#
# Description  : Loads a single logfile.
#
# Input        : file     Filename to process
#                arcdir   Archive directory
#
# Output       : None
#
# Return       : 1 if OK, 0 otherwise
#------------------------------------------------------------------------------#
sub load_file {
   my ($file, $arcdir) = @_;
   my $fname = basename ($file);
   my $tmpf = "$file.$$.tmp";

   #
   # Check the archive directory is OK and create it if necessary ...
   #
   if (! -d $arcdir) {
      if (!mkdir ($arcdir)) {
         log_msg ("E", "failed creating archive directory[$arcdir]");
         return 0;
      }
   }

   #
   # First move the file so that no other processes add any data to it ...
   #
   # IJH XXX - this should really be a program which locks the data file in 
   # the mmap file before loading to avoid a race condition if a CM is writing
   # to the file while we try to load it (also use a move that would work
   # across file systems. TODO.
   #
   if (!rename ($file, "$arcdir/$fname")) {
      log_msg ("E", "failed moving file[$file] to directory[$arcdir]");
      return 0;
   }

   #
   # Load the data into BRM ...
   #
   if (!$G_ARCHIVE_ONLY) {
      my $t = Time::HiRes::time();
      my $loaded = 0;
      if (load_data_into_db ($G_CONN_STR, 0, "$arcdir/$fname", \$loaded)) {
         $t = sprintf ("%.6f", Time::HiRes::time() - $t);
         log_msg ("I", "loaded file[$fname] into BRM database - " .
                  "records[$loaded] elapsed[$t]");
      } else {
         log_msg ("E", "failed loading[$fname] - retained in dir[$arcdir]");
         return 0;
      }
   }

   #
   # Now archive the original file, compressing it... unless we wish to delete
   # it, of course.
   #
   if ($G_DELETE_FILES) {
      if (unlink ("$arcdir/$fname") != 1) {
         log_msg ("E", "failed removing file[$arcdir/$fname] ($!)");
         return 0;
      }
      log_msg ("I", "removed file[$fname] after loading to database");
   } else {
      my ($ss, $mi, $hh, $dd, $mm, $yyyy, $wday, $yday, $isdst) = localtime();
      my $now = sprintf ("%04d%02d%02d_%02d%02d%02d",
                         $yyyy+1900, $mm+1, $dd, $hh, $mi, $ss);
      my $t = Time::HiRes::time();
      `gzip < $arcdir/$fname > $arcdir/$fname.$now.gz`;
      if ($? == 0) {
         $t = sprintf ("%.6f", Time::HiRes::time() - $t);
         my $before = sprintf ("%.2f", (-s "$arcdir/$fname") / 1024.0);
         my $after = sprintf ("%.2f", (-s "$arcdir/$fname.$now.gz") / 1024.0);
         if (unlink ("$arcdir/$fname") != 1) {
            log_msg ("E", "failed to remove file[$arcdir/$fname]");
         } else {
            log_msg ("I", "compressed file[$fname] in directory[$arcdir] - " .
                     "before[${before}Kb] after[${after}Kb] elapsed[$t]");
         }
      } else {
         log_msg ("E", "failed compressing[$fname] in directory[$arcdir]");
         return 0;
      }
   }

   #
   # Do a bit of cleanup on the record Ids hash ... 
   #
   my $cutoff_t = time() + $G_RECID_MAP_CLEANUP_OFFSET;
   foreach my $snap_poid (keys %G_RECID_MAPS) {
      my $to_t = $G_RECID_MAPS{$snap_poid}{to_t};
      if ($to_t < $cutoff_t) {
         log_msg ("D", "cleaned up recid map[$snap_poid] to_t[$to_t]");
         delete $G_RECID_MAPS{$snap_poid};
      }
   }

   return 1;
}

#------------------------------------------------------------------------------#
# Function     : load_data_into_db
#
# Description  : Given a file which is either a batch log file or a real-time
#                data file, retrieve the data and load it into the database.
#
# Input        : connect_str    Database connection string
#                rt_data        Is this RT data? 0 = batch, 1 = rt
#                fname          Filename
#
# Output       : loaded_ref     Number of elements loaded
#
# Return       : 1 if OK, 0 otherwise
#------------------------------------------------------------------------------#
sub load_data_into_db {
   my ($connect_str, $rt_data, $fname, $loaded_ref) = @_;
   my $ok = 1;  # Assume OK

   $$loaded_ref = 0;

   #
   # Open SQL connection if not already open ...
   #
   # Set cursor-sharing = force for this session to avoid generating lots of
   # SQL (as we're not using bind-variables... naughty, but not sure if this is
   # supported in GG/Sqlplus.pm)
   #
   $connect_str = $G_DEF_CONN_STR if (!$connect_str);

   if (!defined($G_SQL)) {
      $G_SQL = sql_open ($connect_str);
      my $output = "";
      sql_exec ($G_SQL, "alter session set cursor_sharing = FORCE;\n",
                \$output, undef);
   }
   if (!defined($G_SQL)) {
      log_msg ("E", "failed connecting to BRM database");
      return 0;
   }

   #
   # Determine what data to handle, RT or batch ...
   #
   # IJH XXX: TODO - split the following 'if' into two additional
   # subroutines to avoid this function being so large and messy.
   #
   if ($rt_data) {
      my $agg_period = "";
      my $agg_unit = "";
      my $start_t = 0;
      my $end_t = 0;
      my @rt_data = ();
      my $g_pid = 0;
      my $g_effective_t = 0;
      my $pcmd = get_pstatus_cmd ($fname);

      get_current_aggregation_period ($G_AGGR_PERIOD, $G_AGGR_UNIT,
                                      \$start_t, \$end_t);

      my $fmt_start_t = fmt_local_time($start_t);
      my $fmt_end_t = fmt_local_time($end_t);

      log_msg ("D", "agg_period[$G_AGGR_PERIOD] agg_unit[$G_AGGR_UNIT] " .
               "start_t[$fmt_start_t] end_t[$fmt_end_t]");

      #
      # Read current data from the mmap'd file and store the details
      # in an array of hashes for processing ...
      #
      if (!open (RTF, "$pcmd -s0 -csponfFLceNtarPUSO -x $fname |")) {
         log_msg ("E", "failed executing[$pcmd] for file[$fname] - $!");
         return 0;
      }
      my $lno = 0;
      while (<RTF>) {
         chomp;
         next if (/^Timestamp,/); # Skip header ...
         $lno++;
         my ($time_str, $program, $opcode, $opname, $opflags, $filename,
             $line_no, $calls, $errors, $records, $elapsed, $avg_elapsed,
             $avg_rate, $pid, $u_cpu, $s_cpu, $obj_type) = split(/,/, $_);

         $g_pid = $pid if ($pid != $g_pid);
         my ($dd, $mm, $yyyy, $hh, $mi, $ss) = split (/[^0-9]+/, $time_str);
         if (!$g_effective_t) {
            $g_effective_t = mktime($ss, $mi, $hh, $dd, $mm-1,
                                    $yyyy-1900, undef, undef, -1) + 0;
         }

         push (@rt_data, { "time_s" => $time_str,
                           "program" => $program,
                           "obj_type" => $obj_type,
                           "opcode" => $opcode,
                           "opname" => $opname,
                           "opflags" => $opflags,
                           "filename" => $filename,
                           "line_no" => $line_no,
                           "calls" => $calls,
                           "errors" => $errors,
                           "records" => $records,
                           "elapsed" => $elapsed,
                           "avg_elapsed" => $avg_elapsed,
                           "avg_rate" => $avg_rate,
                           "pid" => $pid,
                           "u_cpu" => $u_cpu,
                           "s_cpu" => $s_cpu,
                         });
      }
      close (RTF);

      #
      # Sometimes this application can run against a non-initialised Perflib
      # file. If we don't have any data, don't load it. Otherwsie, we find the
      # main /performance_snapshot/realtime object and load it ...
      #
      if (scalar(@rt_data) > 0 && $g_pid > 0) {
         my $tag = ($fname =~ /(.*\/)?([^.]+).*/)[1];
         if (!$tag) {
            log_msg ("E", "could not derive tag name from fname[$fname]");
            return 0;
         }
         log_msg ("D", "tag[$tag] fname[$fname] g_pid[$g_pid] " .
                       "g_effective_t[$g_effective_t] data:" .
                       Data::Dumper->Dump([\@rt_data], ["rt_data"]) . "\n");

         my $snap_poid = get_performance_snapshot ($G_RT_PERF_TYPE, $G_HOSTNAME,
                                                   $tag, $g_pid, $start_t,
                                                   $end_t);
         if (!defined($snap_poid) || $snap_poid <= 0) {
            log_msg ("E", "failed finding/creating $G_RT_PERF_TYPE object");
            return 0;
         }

         #
         # Insert the new records ...
         #
         if (insert_rt_data ($snap_poid, $g_effective_t, \@rt_data)) {
            sql_exec ($G_SQL, "commit;", undef, undef);
            log_msg ("D", "load_data_into_db : successfully loaded $lno " .
                     "RT entries");
            $$loaded_ref = $lno;
         } else {
            sql_exec ($G_SQL, "rollback;", undef, undef);
            log_msg ("E", "load_data_into_db : failed inserting RT data");
         }
      } else {
         log_msg ("W", "load_data_into_db : no real-time data found");
      }
   } else {
      my ($agg_aref, $agg_href) = pre_aggregate_log($fname);
      if (!defined($agg_aref) || !defined($agg_href)) {
         log_msg ("E", "failed reading log file[$fname]");
         return 0;
      }
      my ($tag, $pid, $from_t, $to_t) = parse_fname (basename ($fname));
   
      #
      # Find (or create) the main /performance_snapshot object for this
      # application and time period ...
      #
      my $snap_poid = get_performance_snapshot ($G_PERF_TYPE, $G_HOSTNAME, 
                                                $tag, $pid, $from_t, $to_t);
      if (!defined($snap_poid) || $snap_poid <= 0) {
         log_msg ("E", "load_data_into_db : failed finding/creating " .
                  "/performance_snapshot object");
         $ok = 0;
         goto FINISH;
      }

      #
      # Get the current set of records we're mapping to so we can look
      # them up quickly ... We'll store the time period for this snapshot
      # so that we can implement some cleanup logic to remove old entries
      # once we expect they will no longer be needed.
      #
      if (!defined($G_RECID_MAPS{$snap_poid}{rec_ids})) {
         $G_RECID_MAPS{$snap_poid}{rec_ids} = get_rec_id_map ($snap_poid);
         $G_RECID_MAPS{$snap_poid}{from_t} = $from_t;
         $G_RECID_MAPS{$snap_poid}{to_t} = $to_t;
         $G_RECID_MAPS{$snap_poid}{pid} = $pid;
         $G_RECID_MAPS{$snap_poid}{tag} = $tag;
      }
      my $map_ref = $G_RECID_MAPS{$snap_poid}{rec_ids};
      if (!defined($map_ref)) {
         log_msg ("E", "load_data_into_db : failed building record ID map");
         $ok = 0;
         goto FINISH;
      }
   
      #
      # OK, now process the data we've aggregated ...
      #
      my @rec_ids = ();
      my $rec_id = 0;
      my $use_rec_id = 0;
      my $last_rec_id = 0;
      my $last_level = 0;
      my $num_aggr = scalar(@{$agg_aref});

      foreach my $rref (@{$agg_aref}) {
         my $type = $rref->{type};
         my $srec_ref = $rref->{srec};
         my $frec_ref = $rref->{frec};
   
         # We don't need the virtual time data ...
         next if ($srec_ref->[S_FLD_OPLEVEL] <= 0);
   
         log_msg("D", "load_data_into_db : type[$type] srec[" .
                      join (",", @{$srec_ref}) . "] frec[" .
                      join (",", @{$frec_ref}) . "]") if ($G_DEBUG);

         if ($type eq "S") {
            #
            # We will store 'buckets' as sub-records in the data structure.
            # This should probably be done already in the Perflib, but for now
            # it's not done this way which makes our life a tiny bit more
            # difficult here.
            #  
            if ($srec_ref->[S_FLD_BUCKET_ID] > 0) {
               $use_rec_id = $last_rec_id;
            } else {
               $use_rec_id = $rec_id;
            }
            push (@rec_ids, $rec_id);
            $rec_id = insert_level ($snap_poid, -1, $use_rec_id,
                                    $srec_ref->[S_FLD_OPLEVEL],
                                    $srec_ref->[S_FLD_OPNAME],
                                    $srec_ref->[S_FLD_OPFLAGS],
                                    $srec_ref->[S_FLD_FNAME],
                                    $srec_ref->[S_FLD_LINENO],
                                    $srec_ref->[S_FLD_PROGRAM],
                                    $srec_ref->[S_FLD_OBJ_TYPE],
                                    $srec_ref->[S_FLD_BUCKET_ID],
                                    # NOTE: the following are on the finish
                                    #       record, not the start record
                                    $frec_ref->[F_FLD_BUCKET_START],
                                    $frec_ref->[F_FLD_BUCKET_END],
                                    0, $map_ref);
            if ($rec_id < 0) {
               $ok = 0;
               goto FINISH;
            }
         } elsif ($type eq "F") {
            if (!update_level ($snap_poid, $rec_id,
                               $frec_ref->[F_FLD_REC_COUNT],
                               $frec_ref->[F_FLD_CALLS],
                               $frec_ref->[F_FLD_OPTIME],
                               $frec_ref->[F_FLD_MIN],
                               $frec_ref->[F_FLD_MAX],
                               $frec_ref->[F_FLD_CACHE_CALLS],
                               $frec_ref->[F_FLD_CACHE_TIME],
                               $frec_ref->[F_FLD_ERRORS],
                               $frec_ref->[F_FLD_USER_CPU],
                               $frec_ref->[F_FLD_SYSTEM_CPU]))
            {
               $ok = 0;
               goto FINISH;
            }
   
            # We've finished all buckets for the opcode so reset last_rec_id
            # NOTE: IJH XXX - Not sure that we actually need this ...
            if ($srec_ref->[S_FLD_BUCKET_ID] <= 0) {
               $last_rec_id = $rec_id;
            }
            $rec_id = pop (@rec_ids);
         } else {
            log_msg ("E", "load_data_into_db : bad record type value in " .
                     "aggregation data");
            $ok = 0;
            goto FINISH;
         }
      }

FINISH:
      close (LOGF);
      if ($ok) {
         sql_exec ($G_SQL, "commit;", undef, undef);
         log_msg ("D", "load_data_into_db : ok, commit");
         $$loaded_ref = $num_aggr;
      } else {
         log_msg ("E", "load_data_into_db : failed loading data, rolling back");
         sql_exec ($G_SQL, "rollback;", undef, undef);
      }
   }
   return $ok;
}

#------------------------------------------------------------------------------#
# Function     : load_realtime_data
#
# Description  : Loads realtime data from a mmap data file into the database.
#
# Input        : files    One or more real time data files
#
# Output       : None
#
# Return       : 1 if OK, 0 otherwise
#------------------------------------------------------------------------------#
sub load_realtime_data {
   foreach my $rtf (@_) {
      log_msg ("D", "loading realtime data from file[$rtf] ...");
      my $t = Time::HiRes::time();
      my $loaded = 0;
      if (load_data_into_db ($G_CONN_STR, 1, $rtf, \$loaded)) {
         $t = sprintf ("%.6f", Time::HiRes::time() - $t);
         log_msg ("I", "loaded RT data from[$rtf] into BRM database - " .
                  "records[$loaded] elapsed[$t]");
      } else {
         log_msg ("E", "failed loading realtime data for file[$rtf]");
         return 0;
      }
   }
   return 1;
}

#------------------------------------------------------------------------------#
# Function     : get_from_terminal
#
# Description  : Prompts and reads data from a terminal
#
# Input        : prompt     Prompt text
#                show       Show data entered (Y = echo, N = don't echo)
#
# Output       : None
#
# Return       : Value which is entered (can't be empty)
#------------------------------------------------------------------------------#
sub get_from_terminal {
  my ($prompt, $show) = @_;
  my $val = "";

   while ($val eq "") {
      print STDERR "$prompt : " if (is_terminal());
      `stty -echo 2>/dev/null` if ($show eq "N" && is_terminal());
      $val = <STDIN>;
      `stty echo 2>/dev/null` if ($show eq "N" && is_terminal());
      chomp ($val);
   }
   return $val;
}

#------------------------------------------------------------------------------#
# Function     : check_directories
#
# Description  : checks that a list of directories are valid
#
# Input        : dirs    List of directories
#
# Output       : None
#
# Return       : 1 if OK, 0 otherwise
#------------------------------------------------------------------------------#
sub check_directories {
   foreach my $D (@_) {
      if (! -d $D) {
         log_msg ("E", "value[$D] is not a valid directory");
         return 0;
      }
   }
   return 1;
}

#------------------------------------------------------------------------------#
# Function     : check_realtime_files
#
# Description  : Checks that the specified real time files actually exist.
#
# Input        : files   List of files to check
#
# Output       : None
#
# Return       : 1 if OK, 0 otherwise
#------------------------------------------------------------------------------#
sub check_realtime_files {
   foreach my $F (@_) {
      if (! -r $F) {
         log_msg ("E", "realtime file[$F] is invalid");
         return 0;
      }
   }
   return 1;
}

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
   print  <<"END";
usage : $G_CMD [-h] [-d|-D] [-n] [-a|-A] [-l<logfile>] [-f<freq>] [-F<freq>]
        [-r<rt_file> [-r<rt_file2]] [-s<freq>] <dir> [<dir2> ...]

where : -h             This help message
        -d             Debug - verbose information
        -D             Even more verbose debug (also dumps data structures)
        -n             No wait - load files as soon as they are found rather
                       than waiting for the logging period to expire
        -a             Archive only mode (does not load to database)
        -A             No-archive mode (files are deleted after loading)
        -l<logfile>    Logfile name (default is $DEF_LOGFILE)
        -f<freq>       Frequency with which to check for new files (default
                       is $DEF_FREQUENCY seconds).
        -F<freq>       Frequency with which to load real-time data (default
                       is $DEF_RT_FREQUENCY seconds - used if <freq> is 0). The
                       value may also be qualified with (h)our, (m)inute, or
                       (s)econd to allow "windows" (see -p option which works
                       the same way).
        -s<freq>       Frequency with which to load SQL data (default is
                       $DEF_SQL_FREQUENCY seconds - used if <freq> is 0).
        -r<rt_file>    A real-time data file from which data will be collected
                       and loaded at the frequency specified.
        -p<period>     Period for grouping real-time data [only with -r option].
                       This is specified as <X>M|H|S in the same way as Perflib
                       periods are defined (see the PERFLIB_AGGREGATION_PERIOD
                       variable description in perf.env). E.g. 30m would group
                       data into 30 minute snapshots at 00:00 and 00:30 ..., 2h
                       into 2 hour snapshots (00:00, 02:00, 04:00, 06:00 etc.)
                       The default is $DEF_AGGREGATION_PERIOD.
        -P<age>        Age for purging Perflib data from the database (this
                       includes perfomance snapshots and SQL data. By default
                       no purging is done. The parameter is of the form:
                          -P <x><unit> 
                       Where <unit> may be: (d)ays, (m)inutes, (s)econds. E.g.
                       -P30m would purge data every 30 minues, -P30d would do so
                       every 30 days.

        <dir> ...      List of directories to monitor 
END

   exit (1);
}

#------------------------------------------------------------------------------#
# Function     : batch_process
#
# Description  : Background process for loading batch files. Will repeatedly
#                check the directories for files to load until signalled to
#                terminate.
#
# Input        : None
#
# Output       : None
#
# Return       : 0 if all OK, non-zero otherwise
#------------------------------------------------------------------------------#
sub batch_process {
   #
   # Setup signal handlers ...
   #
   $SIG{HUP} = sub { log_msg ("I", "ignore SIGHUP($!)") };
   $SIG{TERM} = sub { $G_EXIT_REQUESTED = 1 };

   log_msg ("I", "starting batch_process ...");

   #
   # Enter main infinite loop ...
   #
   while (!$G_EXIT_REQUESTED) {
      my $start_t = time();
      #
      # Find files in each directory in turn ...
      #
      foreach my $dir (@G_DIRLIST) {
         my @file_list = split(/\s+/, `ls $dir/*.plog.txt 2>/dev/null`);
         my $nfiles = scalar(@file_list);
         log_msg ("D", "found $nfiles files to process in directory[$dir]");
         my $archive_dir = "$dir/$G_ARCHIVE_DIR";
         foreach my $f (@file_list) {
            if (ready_to_process ($f) > 0) {
               load_file ($f, $archive_dir);
            }
         }
      }

      #
      # Wait, if we need to ...
      #
      my $time_to_start = $start_t + $G_FREQUENCY; 
      my $logged = 0;
      while (!$G_EXIT_REQUESTED && time() < $time_to_start) {
         if (!$logged) {
            my $t = fmt_local_time($time_to_start);
            log_msg ("D", "batch_process sleeping until $t ...");
            $logged = 1;
         }
         sleep (1);
      }
   }

   log_msg ("I", "batch_process terminating ...");
   return 0;
}

#------------------------------------------------------------------------------#
# Function     : realtime_process
#
# Description  : Background process for loading realtime files. Will collect
#                data from realtime files on a regular basis until signalled
#                to stop.
#
# Input        : None
#
# Output       : None
#
# Return       : 0 if OK, non-zero otherwise
#------------------------------------------------------------------------------#
sub realtime_process {
   #
   # Setup signal handlers ...
   #
   $SIG{HUP} = sub { log_msg ("I", "ignore SIGHUP") };
   $SIG{TERM} = sub { $G_EXIT_REQUESTED = 1 };

   log_msg ("I", "starting realtime_process ...");

   my $start_t;
   my $end_t;
   my $formatted_t;

   #
   # Enter the infinite loop ... We'll immediately collect a snapshot and then
   # align ourselves to the configured window ...
   #
   while (!$G_EXIT_REQUESTED) {
      load_realtime_data (@G_RT_FILES);

      get_current_aggregation_period ($G_RT_FREQUENCY, $G_RT_FREQUENCY_UNIT,
                                      \$start_t, \$end_t);

      my $logged = 0;
      while (!$G_EXIT_REQUESTED && time() < $end_t) {
         if (!$logged) {
            $formatted_t = fmt_local_time($end_t);
            log_msg ("D", "realtime_process sleeping until $formatted_t ...");
            $logged = 1;
         }
         sleep (1);
      }
   }

   log_msg ("I", "realtime_process terminating ...");
   return 0;
}

#------------------------------------------------------------------------------#
# Function     : sql_collect_process
#
# Description  : Background process for collecting SQL data from the database.
#                Will collect data from the gv$sql view and store it in
#                /performance_sql_data objects which can later be used to
#                generate reports similar to AWR reports (albeit less complete)
#
# Input        : None
#
# Output       : None
#
# Return       : 0 if OK, non-zero otherwise
#------------------------------------------------------------------------------#
sub sql_collect_process {
   #
   # Setup signal handlers ...
   #
   $SIG{HUP} = sub { log_msg ("I", "ignore SIGHUP") };
   $SIG{TERM} = sub { $G_EXIT_REQUESTED = 1 };

   log_msg ("I", "starting SQL collect process ...");

   #
   # Enter main infinite loop to collect data every so often... We will align
   # based on the aggregation period (the first snapshot will always be taken
   # immediately, though to allow data collection to be started immediately.
   #
   while (!$G_EXIT_REQUESTED) {
      collect_sql_data();

      my $start_t;
      my $end_t;
      my $logged = 0;

      get_current_aggregation_period ($G_SQL_AGGR_PERIOD, $G_SQL_AGGR_UNIT,
                                      \$start_t, \$end_t);

      while (!$G_EXIT_REQUESTED && time() < $end_t) {
         if (!$logged) {
            my $t = fmt_local_time($end_t);
            log_msg ("D", "sql_collect_process sleeping until $t ...");
            $logged = 1;
         }
         sleep (1);
      }
   }

   log_msg ("I", "sql_collect_process terminating ...");
   return 0;
}

#------------------------------------------------------------------------------#
# Function     : collect_sql_data
#
# Description  : Collect SQL data from gv$sql and store it locally (implies
#                that the local connection has select access to gv$sql, of
#                course!)
#
#                If we get a fatal error, signal the main thread to terminate.
#
# Input        : None
#
# Output       : None
#
# Return       : 0 if OK, non-zero otherwise
#------------------------------------------------------------------------------#
sub collect_sql_data {
   #
   # Open SQL connection if not already open ...
#
# IJH XXX - need to check that an open connection is still valid... need to
# have wrapper for sql_open to retry... and if there's a problem we should
# signal the main application to terminate.
#
# my $n = kill('TERM', $G_MAIN_PID);
# log_msg("E", "IJHXXX - kill daemon");
#
   if (!defined($G_SQL)) {
      $G_SQL = sql_open ($G_CONN_STR);
   }
   if (!defined($G_SQL)) {
      log_msg ("E", "failed connecting to BRM database");
      return 1;
   }

   #
   # Select the data and insert it into the /performance_sql_data object. We
   # will do this all in a stored procedure for simplicity.
   #
   my $output;
   my $t = Time::HiRes::time();
   sql_exec ($G_SQL, "execute perflib.get_sql_snapshot('$G_DB_USER');",
             \$output, undef);
   if ($output =~ /ORA-/) {
      log_msg ("E", "failed to collect SQL snapshot data:\n$output\n");
      return 1;
   } else {
      $t = sprintf ("%.6f", Time::HiRes::time() - $t);
      log_msg ("I", "succesfully collected SQL data - elapsed[$t]");
   }
   return 0;
}

#------------------------------------------------------------------------------#
# Function     : purge_data_process
#
# Description  : Background process for purging snapshot data from the database.
#
# Input        : None
#
# Output       : None
#
# Return       : 0 if OK, non-zero otherwise
#------------------------------------------------------------------------------#
sub purge_data_process {
   #
   # Setup signal handlers ...
   #
   $SIG{HUP} = sub { log_msg ("I", "ignore SIGHUP") };
   $SIG{TERM} = sub { $G_EXIT_REQUESTED = 1 };

   log_msg ("I", "starting snapshot purge process ...");

   #
   # Enter main infinite loop to purge data every so often...
   #
   while (!$G_EXIT_REQUESTED) {
      my $start_t = time();

      purge_snapshot_data($G_PURGE_DELAY);

      my $time_to_start = $start_t + $G_PURGE_FREQUENCY; 
      my $logged = 0;
      while (!$G_EXIT_REQUESTED && time() < $time_to_start) {
         if (!$logged) {
            my $t = fmt_local_time($time_to_start);
            log_msg ("D", "purge_data_process sleeping until $t ...");
            $logged = 1;
         }
         sleep (1);
      }
   }

   log_msg ("I", "purge_data_process terminating ...");
   return 0;
}

#------------------------------------------------------------------------------#
# Function     : purge_snapshot_data
#
# Description  : Purge Perflib data that is older than X days/hours/minutes.
#                This will run on a periodic basis and delete data.
#
# Input        : None
#
# Output       : None
#
# Return       : 0 if OK, non-zero otherwise
#------------------------------------------------------------------------------#
sub purge_snapshot_data {
   my ($purge_delay) = @_;
   #
   # Open SQL connection if not already open ...
#
# IJH XXX - need to check that an open connection is still valid... need to
# have wrapper for sql_open to retry... and if there's a problem we should
# signal the main application to terminate.
#
# my $n = kill('TERM', $G_MAIN_PID);
# log_msg("E", "IJHXXX - kill daemon");
#
   if (!defined($G_SQL)) {
      $G_SQL = sql_open ($G_CONN_STR);
   }
   if (!defined($G_SQL)) {
      log_msg ("E", "failed connecting to BRM database");
      return 1;
   }

   #
   # Delete data in performance and sql snapshots where things are older
   # than the particular offset from the current date.
   #
   # We will do this all in a stored procedure for simplicity.
   #
   my $output;
   my $t = Time::HiRes::time();
   sql_exec ($G_SQL, "execute perflib.purge($purge_delay);", \$output, undef);
   if ($output =~ /ORA-/) {
      log_msg ("E", "failed to purge snapshot data:\n$output\n");
      return 1;
   } else {
      $t = sprintf ("%.6f", Time::HiRes::time() - $t);
      log_msg ("I", "successfully purged snapshot data - elapsed[$t]");
   }
   return 0;
}

#------------------------------------------------------------------------------#
# Function     : main_process
#
# Description  : Main process spawned to run in the background. Will spawn
#                background processes for loading batch, realtime and SQL  data
#                and then wait for control signals to terminate.
#
# Input        : None
#
# Output       : None
#
# Return       : 0 if OK, non-zero otherwise
#------------------------------------------------------------------------------#
sub main_process {
   #
   # Setup signal handlers ...
   #
   $SIG{HUP} = sub { log_msg ("ignore SIGHUP($!)") };
   $SIG{TERM} = sub { $G_EXIT_REQUESTED = 1 };
   $G_MAIN_PID = $$;

   #
   # Log initialisation ...
   #
   if (scalar(@G_DIRLIST) > 0) {
      log_msg ("I", "batch logging frequency: $G_FREQUENCY seconds");
      for my $D (@G_DIRLIST) {
         log_msg ("I", "monitoring directory: $D");
      }
   } else {
      log_msg ("I", "batch logging disabled");
   }

   if (scalar(@G_RT_FILES) > 0) {
      log_msg ("I", "realtime logging frequency: $G_RT_FREQUENCY seconds");
      for my $RTF (@G_RT_FILES) {
         log_msg ("I", "monitoring RT file: $RTF");
      }
   } else {
      log_msg ("I", "RT logging disabled");
   }

   if ($G_SQL_COLLECT) {
      log_msg ("I", "SQL collection frequency: $G_SQL_FREQUENCY seconds");
   } else {
      log_msg ("I", "SQL collection disabled");
   }
   log_msg ("I", "archive directory: $G_ARCHIVE_DIR");

   if ($G_PURGE_DELAY > 0) {
      log_msg ("I", "Data purge delay: $G_PURGE_DELAY seconds");
      log_msg ("I", "Data purge frequency: $G_PURGE_FREQUENCY seconds");
   } else {
      log_msg ("I", "Data purge disabled");
   }

   #
   # Create the batch process ...
   #
   my $BATCH_PID;
   if (scalar(@G_DIRLIST) > 0) {
      $BATCH_PID = fork();
      abort ("failed forking batch process - $!") if (!defined($BATCH_PID));
      if ($BATCH_PID == 0) {
         $0 = $G_CMD = "perfd_batch_01";
         exit(batch_process()); # Child, execute batch process ...
      }
   }

   #
   # Create the realtime process ...
   #
   my $RT_PID;
   if (scalar(@G_RT_FILES) > 0) {
      $RT_PID = fork();
      abort ("failed forking realtime process - $!") if (!defined($RT_PID));
      if ($RT_PID == 0) {
         $0 = $G_CMD = "perfd_rt_01";
         exit(realtime_process()); # Child, execute RT process ...
      }
   }

   #
   # Create the SQL process ...
   #
   my $SQL_PID;
   if ($G_SQL_COLLECT) {
      $SQL_PID = fork();
      abort ("failed forking SQL process - $!") if (!defined($SQL_PID));
      if ($SQL_PID == 0) {
         $0 = $G_CMD = "perfd_sql_01";
         exit(sql_collect_process()); # Child, execute SQL process ...
      }
   }

   #
   # Create the purge process ...
   #
   my $PURGE_PID;
   if ($G_PURGE_DELAY > 0) {
      $PURGE_PID = fork();
      abort ("failed forking purge process - $!") if (!defined($PURGE_PID));
      if ($PURGE_PID == 0) {
         $0 = $G_CMD = "perfd_purge_01";
         exit(purge_data_process()); # Child, execute purge process ...
      }
   }

   #
   # Wait for a signal to finish ...
   #
   log_msg ("I", "perfd daemon starting to process ...");
   while (!$G_EXIT_REQUESTED) {
      sleep 1
   }
   log_msg ("I", "perfd daemon shutting down ...");

   #
   # Signal (SIGTERM) and wait for child processes. We will check for any
   # non-zero exit status and, if one is found, we'll exit with that.
   #
   kill (15, $BATCH_PID) if ($BATCH_PID);
   kill (15, $RT_PID) if ($RT_PID);
   kill (15, $SQL_PID) if ($SQL_PID);
   kill (15, $PURGE_PID) if ($PURGE_PID);

   my $exit_status = 0;
   if ($BATCH_PID) {
      my $rv = wait_for_process ($BATCH_PID);
      log_msg ("I", "batch process $BATCH_PID terminated - exit[$rv]");
      $exit_status = $rv if (!$exit_status);
   }

   if ($RT_PID) {
      my $rv = wait_for_process ($RT_PID);
      log_msg ("I", "realtime process $RT_PID terminated - exit[$rv]");
      $exit_status = $rv if (!$exit_status);
   }

   if ($SQL_PID) {
      my $rv = wait_for_process ($SQL_PID);
      log_msg ("I", "SQL snapshot process $SQL_PID terminated - exit[$rv]");
      $exit_status = $rv if (!$exit_status);
   }

   if ($PURGE_PID) {
      my $rv = wait_for_process ($PURGE_PID);
      log_msg ("I", "purge process $PURGE_PID terminated - exit[$rv]");
      $exit_status = $rv if (!$exit_status);
   }

   #
   # OK, we're done ...
   #
   if ($exit_status) {
      log_msg ("E", "perfd terminated with errors, exit_status[$exit_status]");
   } else {
      log_msg ("I", "perfd terminated with no errors ...");
   }
   unlink ($G_PIDFILE);
   close (G_LOGFILE) if ($G_LOGFILE_OPEN);
   return $exit_status;
}

#------------------------------------------------------------------------------#
# Function     : wait_for_process
#
# Description  : Waits for a process to finish and returns the result.
#
# Input        : pid    Process ID
#
# Output       : None
#
# Return       : Process exit value
#------------------------------------------------------------------------------#
sub wait_for_process {
   my ($pid) = @_;
   my $kid;
   my $status = 0;
   while (($kid = waitpid ($pid, 0)) > 0) {
      if ($? & 127) {
         $status = sprintf("signal[%d](%s)",
            $? & 127, $? & 128 ? "core" : "no core");
      } else {
         $status = $? >> 8;
      }
   }
   return $status;
}

#------------------------------------------------------------------------------#
# Function     : main
#
# Description  : Main program entry point ...
#
# Input        : See usage()
#
# Output       : None
#
# Return       : 0 if OK, non-zero otherwise
#------------------------------------------------------------------------------#
#
# Process options ...
#
my $CMDLINE = join(" ", @ARGV);

my %opt = ();
getopts('hdDaAnl:f:F:r:p:s:P:', \%opt) or usage();
if ($opt{h}) { usage() }

usage() if ($opt{h});
$G_DEBUG = 1 if ($opt{d});
$G_DEBUG = 2 if ($opt{D});
$G_ARCHIVE_ONLY = 1 if ($opt{a});
$G_DELETE_FILES = 1 if ($opt{A});
$G_LOGFILE_NAME = $opt{l} if ($opt{l});
$G_FREQUENCY = $opt{f} if ($opt{f});
if ($opt{F}) {
   if (!validate_aggregation_period ($opt{F}, \$G_RT_FREQUENCY,
                                     \$G_RT_FREQUENCY_UNIT))
   {
      abort ("invalid real-time frequency definition[$opt{F}]");
   }
}
$G_NOWAIT = 1 if ($opt{n});
push (@G_RT_FILES, $opt{r}) if ($opt{r});
if ($opt{p}) {
   if (!validate_aggregation_period ($opt{p},
                                     \$G_AGGR_PERIOD, \$G_AGGR_UNIT))
   {
      abort ("invalid aggregation period[$opt{p}]");
   }
}
if ($opt{P}) {
   if ($opt{P} =~ /^(\d+)d$/i) {
      $G_PURGE_DELAY =  $1 * 86400;
   } elsif ($opt{P} =~ /^(\d+)m$/i) {
      $G_PURGE_DELAY =  $1 * 60;
   } elsif ($opt{P} =~ /^(\d+)s$/i) {
      $G_PURGE_DELAY =  $1;
   } else {
      abort ("invalid purge delay[$opt{P}]");
   }
}
if (length($opt{s}) > 0) {
   if ($opt{s}) {
      $G_SQL_FREQUENCY = $opt{s};
   }
   $G_SQL_COLLECT = 1;
}
@G_DIRLIST = @ARGV;

#
# Check options ...
#
if ($G_ARCHIVE_ONLY && $G_DELETE_FILES) {
   abort ("-a and -A options are mutually exclusive");
}

if ($G_SQL_COLLECT) {
   if (!validate_aggregation_period ($G_SQL_FREQUENCY,
                                     \$G_SQL_AGGR_PERIOD,
                                     \$G_SQL_AGGR_UNIT))
   {
      abort ("invalid SQL aggregation period[$G_SQL_FREQUENCY]");
   }
}

#
# Check parameters. If we're doing real-time loading then the directory is
# optional (we support loading only real-time data), otherwise it's mandatory.
#
usage() if (scalar(@G_RT_FILES) == 0 && scalar(@G_DIRLIST) == 0);

if (scalar(@G_DIRLIST) == 0) {
   #
   # Check archive options if no directories specified ...
   #
   if ($G_ARCHIVE_ONLY) {
      abort ("-a (archive-only) not supported if no directories specified!");
   }
   if ($G_DELETE_FILES) {
      abort ("-A (delete files) not supported if no directories specified!");
   }
} else {
   check_directories (@G_DIRLIST) or
      abort ("failed validating directories");
}

#
# Validate real-time data files ...
#
if (scalar(@G_RT_FILES) > 0) {
   check_realtime_files (@G_RT_FILES) or
      abort ("realtime files are invalid");
}

#
# Check another daemon is not already running
#
if (open (F, "<$G_PIDFILE")) {
   my $PID = <F>;
   chomp($PID);
   close (F);
   if ($PID && is_running ($PID)) {
      abort ("perfd daemon is already running (PID[$PID])");
   }
}

#If File is Being Executed from CNBRM then don't ask for USERNAME and PASSWD
if((defined($ENV{'DOCKER'}) && ($ENV{'DOCKER'} eq '1')))
{
$G_DB_ALIAS = "pindb";
$G_DB_USER = "";
$G_DB_PASSWD = "";
}
else{
#
# Read the connection entries from the command-line
#
$G_DB_ALIAS = get_from_terminal ("Enter DB alias", "Y");
$G_DB_USER = get_from_terminal ("Enter user name", "Y");
$G_DB_PASSWD = get_from_terminal ("Enter password", "N");
printf STDERR "\n" if (is_terminal());
my $VERIFY = get_from_terminal ("Verify password", "N");
printf STDERR "\n" if (is_terminal());

if ("$VERIFY" ne "$G_DB_PASSWD") {
   abort ("Sorry, passwords don't match!");
}
}
$G_CONN_STR = "${G_DB_USER}/${G_DB_PASSWD}\@${G_DB_ALIAS}";

#
# Check that we can login to the database using these credentials ...
#
my $output = "";
my $tmp_sql = sql_open ($G_CONN_STR);
if (!defined($tmp_sql)) {
   abort ("DB login credential check failed!");
}
sql_exec ($tmp_sql, "select 'LOGIN_OK' from dual;", \$output, undef);
if ($output ne "LOGIN_OK") {
   abort ("unexpected output[$output] during login verification");
}
sql_close ($tmp_sql);

#
# Launch main processing loop ...
#
log_msg ("I", "starting with command line : $CMDLINE");

my $PID = fork();
abort ("failed forking background process - $!") if (!defined($PID));
if ($PID == 0) {
   $0 = $G_CMD = "perfd_main";
   exit(main_process());
}
open (F, ">$G_PIDFILE");
printf F "$PID\n";
close (F);
printf "process $PID launched in the background (PID file[$G_PIDFILE])\n";
exit 0;
