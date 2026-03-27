#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl

###############################################################################
#
#       Copyright (c) 2006 Oracle. All rights reserved.
#
#       This material is the confidential property of Oracle Corporation
#       or its licensors and may be used, reproduced, stored or transmitted
#       only in accordance with a valid Oracle license or sublicense agreement.
#
####################################################################################
# Description: This script is used to move the output TAP file from out dir to
# some other temp dir as well as copy to the in directory of the outcollect 
# settlement pipeline
####################################################################################

use File::Copy;

my $COPY_DIR = "$ENV{IFW_HOME}/data/outcollect/tapout/common";
my $MOVE_DIR = "$ENV{IFW_HOME}/data/outcollect/settlement/in";

if($#ARGV < 0)
{
    print "\nUSAGE: $0  <OUT_FILE>\n\n";
    exit();
}

$out_file = $ARGV[0];
my $actual_file = $ARGV[0];

###################
# Strip "/" part
###################

$out_file =~ s|.*/([^/]*)$|$1|;
$tmp_input_file = 'temp'.$out_file;

#####################################
# Copy and Move will be done below.
#####################################

copy("$actual_file","$COPY_DIR/$tmp_input_file");
move("$COPY_DIR/$tmp_input_file","$COPY_DIR/$out_file");
move("$actual_file","$MOVE_DIR/$out_file");
