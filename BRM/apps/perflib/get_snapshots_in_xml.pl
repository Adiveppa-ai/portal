# Copyright (c) 2020, Oracle and/or its affiliates. 
#------------------------------------------------------------------------------#
# SCRIPT: get_snapshots_in_xml.pl
#
# DESCRIPTION:
#
# Retrieves one or more /performance_snapshot objects and converts them into
# an XML file.
#
# INFORMATION:
#
# BRM Performance Tools ...
#
# REVISION:
#
# $Revision: 1.3 $
# $Author: pin $
# $Date: 2012/08/30 21:21:58 $
#------------------------------------------------------------------------------#

#------------------------------------------------------------------------------#
#                     M O D U L E   I N C L U S I O N
#------------------------------------------------------------------------------#
use strict;
use FileHandle;
use IPC::Open2;
use File::Basename;
use POSIX qw(mktime);
use Getopt::Std;

#------------------------------------------------------------------------------#
#                     G L O B A L   V A R I A B L E S
#------------------------------------------------------------------------------#
use vars qw($G_VERSION $G_CMD $G_DEBUG);

$G_VERSION = do {my $v = '$Revision: 1.3 $'; $v =~ s/[^\d\.]//g; $v};
$G_DEBUG = 0;
$G_CMD = basename ($0);

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
   print STDERR <<XXX;
usage : $G_CMD [-h]
        $G_CMD [-d] [-l<level>] [-n<name>] [-f<from>] [-t<to>]
        $G_CMD [-d] [-l<level>] <poid>

where : -h         This message
        -d         Debug mode
        -l<level>  Max level of 'depth' for reports
        -n<name>   Name to filter by
        -f<from>   From time for searching snapshots (YYYYMMDD[_HHMISS])
        -t<to>     To time for searching snapshots (YYYYMMDD[_HHMISS])

        <poid>     If poid_id0 is provided, retrieve only this snapshot
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
my %opt = ();
my $max_level = 0;
my $from = 0;
my $to = 0;
my $name = "";

#
# Check options ...
#
getopts('hdl:c:n:f:t:', \%opt) or usage();
if ($opt{h}) { usage() }
if ($opt{d}) { $G_DEBUG = 1 }
if ($opt{l}) {
   $max_level = $opt{l};
   abort ("bad -l option value - must be >= 1") if ($max_level < 1);
}
if ($opt{n}) { $name = $opt{n} }
if ($opt{f}) {
   $from = yyyymmdd_hhmiss_to_unix($opt{f});
   usage() if ($from < 0);
}
if ($opt{t}) {
   $to = yyyymmdd_hhmiss_to_unix($opt{t});
   usage() if ($to < 0);
}

my $args = scalar(@ARGV);
my $poid_id0 = -1;
usage if ($args < 0 || $args > 1);
if ($args == 1) {
   $poid_id0 = $ARGV[0]; 
   usage if ($opt{n} or $opt{f} or $opt{t});  
}

#
# Build testnap script ...
#
my $poid_str = "0.0.0.1 /performance_snapshot $poid_id0 0";
my $nap_script = "r << XXX 1\n";
$nap_script .= "0 PIN_FLD_POID POID [0] $poid_str\n";
if ($poid_id0 == -1) {
   $nap_script .= "0 PIN_FLD_START_T TSTAMP [0] ($from)\n" if ($from);
   $nap_script .= "0 PIN_FLD_END_T TSTAMP [0] ($to)\n" if ($to);
   $nap_script .= "0 PIN_FLD_NAME STR [0] \"$name\"\n" if ($name);
}
$nap_script .= "0 PIN_FLD_ITEM_LEVEL INT [0] $max_level\n" if ($max_level);
$nap_script .= "0 PIN_FLD_FLAGS INT [0] 4112\n";
$nap_script .= "XXX\n";
$nap_script .= "xop PCM_OP_PERFLIB_GET_SNAPSHOT 0x0 1\n";
$nap_script .= "q\n";

#
# Start testnap, execute operation and retrieve results ...
#
my $r = FileHandle->new();
my $w = FileHandle->new();
my $pid = open2($r, $w, "testnap 2>&1");
if (!defined($pid)) {
   printf STDERR "failed starting testnap\n";
   exit(1);
}
$w->print($nap_script);
my $line = "";

my $data = "";
while ($line = $r->getline) {
   next if ($line !~ /^0/);
   $data .= $line;
}
$r->close;
$w->close;

#
# Inefficiently post-process the data ...
#
$data =~ s/0 PIN_FLD_POID.*\n0\s+PIN_FLD_STRING\s+STR \[0\] "//m;
$data =~ s/\\t/  /g;
$data =~ s/\\n/\n/g;
$data =~ s/\\"/"/g;
$data =~ s/\\\?/\?/g;
chop $data;
chop $data;

print $data;
