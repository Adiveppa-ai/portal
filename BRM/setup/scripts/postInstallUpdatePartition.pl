#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl -w
# 
# $Header: install_vob/nginstall/components/postInstallUpdatePartition.pl /cgbubrm_mainbrm.portalbase/4 2017/09/24 23:04:07 mkothari Exp $
#
# postInstallUpdatePartition.pl
# 
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#
#    NAME
#      postInstallUpdatePartition.pl - <one-line expansion of the name>
#
#    DESCRIPTION
#      <short description of component this file declares/defines>
#
#    NOTES
#      <other useful comments, qualifications, etc.>
#
#    MODIFIED   (MM/DD/YY)
#    mkothari    11/28/16 - Creation
# 
my $findr = '@CLASSES_TO_BE_PARTITIONED';
my $file_mod="/home/pin/opt/portal/BRM/setup/pin_setup.values_modify";
my $file_org="/home/pin/opt/portal/BRM/setup/pin_setup.values";
my $component = $ARGV[0];
my $comp;

my @c = split(',',"$component");
$component =~ s/,/:local","\//g;
        $comp = "$component";

open FILE, "$file_org"  or die "cannot open dir $file_org: $!";
open(OUT,">",$file_mod) || die "unable to open $file_mod";
while(<FILE>) {
        if($_ =~ m/$findr/) {
                print OUT "\@CLASSES_TO_BE_PARTITIONED = (\"\");";
        } else {
                print OUT $_;
        }
}
close(OUT);
close(FILE);

system("mv $file_mod $file_org");

if(!$component) {
	exit;
}

open FILE, "$file_org"  or die "cannot open dir $file_org: $!";
open(OUT,">",$file_mod) || die "unable to open $file_mod";

while(<FILE>) {
	if($_ =~ m/$findr/) {
		my @values = split('\(',$_);
		my @valueNext = split('\)',$values[1]);
		if ($valueNext[0] =~ "\"/${comp}:local\"" ) {
			print OUT $_;
		} else {
                        #if($comp =~ m/journal/) {
			print OUT "\@CLASSES_TO_BE_PARTITIONED = ("."\"/${comp}:local\");\n";
                        #} else {
			#	print OUT "\@CLASSES_TO_BE_PARTITIONED = ("."$valueNext[0]".","."\"/${comp}:local\");\n";
			#}
		}	

	}	
	else
	{
        print OUT $_;
	}
}
close(OUT);
close(FILE);

system("mv $file_mod $file_org");
