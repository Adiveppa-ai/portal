#!/usr/local/bin/perl
#
# Copyright (c) 1997, 2023, Oracle and/or its affiliates.
#

( $me = $0 ) =~ s,.*/,,;
$DEBUG = $ENV{"DEBUG"} || 0;

#
# Parse command line flags.
#
use Getopt::Std;

#
# Walk through the list of files passed in
#
$elemid = 0;
$maxnum = 0;

open( ROUT, ">src/main/resources/com/portal/pcm/fields/fields.properties" );

# Check if the special "-" syntax is used to specify the Publish
# directory. If found, then I will replace it with the value of the
# environment variable PINBUILD_PUBLISH_DIR.  This will allow the
# Makefiles to use commands that are the same between different views
# and allow winkins to work.
#
@new_argv;
while (@ARGV) {
    if ( $ARGV[0] =~ /^-/ ) {

        # Replace a file name that starts with "-"
        $ARGV[0] =~ s/^-/$ENV{PINBUILD_PUBLISH_DIR}/;
    }

    # Don't allow wildcards
    # See if the file exists, if it doesn't then die
    if ( !-e "$ARGV[0]" ) {
        print "File $ARGV[0] doesn't exist. Terminating.\n";
        exit 1;
    }
    push @new_argv, $ARGV[0];
    shift @ARGV;
}
@ARGV = @new_argv;

while (<>) {
    #
    # Accept lines matching #define XXX PIN_MAKE_FLD(PIN_FLDT_*, nnn)
    #
    if (/^#\s*define\s+(\w+)\s+PIN_MAKE_FLD\s*\(\s*(PIN_FLDT_\w+)\s*,\s*(\d+)\s*\).*$/) {
        $fldname = $1;
        $fldnum = $3;
        print ROUT "pin.field.$fldnum=$fldname\n";
    }
}

close(ROUT);
