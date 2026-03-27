#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl

###############################################################################
#
#       Copyright (c) 2006 Oracle. All rights reserved.
#
#       This material is the confidential property of Oracle Corporation
#       or its licensors and may be used, reproduced, stored or transmitted
#       only in accordance with a valid Oracle license or sublicense agreement.
#
#########################################################################
# Description: This script is used to move the TAP file from common dir to
# final sent dir
#########################################################################

use File::Copy;

my $IN_DIR = "$ENV{IFW_HOME}/data/outcollect/tapout/common";
my $MOVE_DIR = "$ENV{IFW_HOME}/data/outcollect/tapout/sent";

if($#ARGV < 0)
{
    print "\nUSAGE: $0  <OUT_FILE>\n\n";
    exit();
}
open (F1,">perl_error.log") or die "Couldn't open perl_error.log.\n\n";
print F1 "Running move_inputfile.pl\n";

$out_file = $ARGV[0];

###################
# Strip out .out.
###################

$out_file =~ s|.*/([^/]*)$|$1|;
$out_file =~ s!^test_gsm_!!i;
$out_file =~ s/\.out$//;
$input_file = 'CD'.$out_file;

#####################
# Open the input dir.
#####################

opendir(IN, $IN_DIR) or die "Can't open $IN_DIR: $!";

my $found = 0;
while ( defined ($file = readdir IN) )
{
    next if $file =~ /^\.\.?$/;     # skip . and ..

    if($file eq $input_file)
    {
        $found =1;
        last;
    }
}

###############################
# If input file is found. move
# it otherwise print error.
###############################

if($found == 1)
{
    move("${IN_DIR}/$input_file", "$MOVE_DIR");
}
else
{
    print F1 "\nERROR: No $input_file found in $IN_DIR directory.!!\n\n";
}
