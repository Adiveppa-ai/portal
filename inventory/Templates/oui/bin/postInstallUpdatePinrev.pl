#!__PERL_HOME__/bin/perl -w
# 
# $Header: install_vob/nginstall/components/postInstallUpdatePinrev.pl /cgbubrm_mainbrm.portalbase/4 2018/05/02 22:28:17 mkothari Exp $
#
# postInstallUpdatePinrev.pl
# 
# Copyright (c) 2016, 2018, Oracle and/or its affiliates. All rights reserved.
#
#    NAME
#      postInstallUpdatePinrev.pl - <one-line expansion of the name>
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

use Time::Local;
use File::Basename;
use Fcntl qw(SEEK_SET);
my $comp_name = qr/^\s*<COMP\s*NAME=\"(\w+)\".*/;
my $build_no = qr/\s*BUILD_NUMBER=\"(\w+)\".*/;
my $install_time = qr/\s*INSTALL_TIME=\"(\d+).(\w+).(\d+)\s*(\d+):(\d+):(\d+)\s*(\w+)\".*/;
my $date="";
my $index = 0;
my $NumberOfPS=0; # this variable tells numbers of patchsets, so that so many times loop will run to get BRM modules version of each PS
my $fileLocation = "/home/pin/opt/portal/inventory/inis/";
my $source = "$fileLocation/*.ini";

if(defined($ARGV[0])) {
open FILE, "/home/pin/opt/portal/inventory/ContentsXML/comps.xml"  or die $!;
#glob reads all ini files in increasing order
@list = glob($source);
#This loop reads ini files and copies on ExtractedFileName. At the last iteration the ini file for latest BRM version is read.
foreach $fileName (@list)
{
  $ExtractedFileName = basename($fileName);
# fileLocationFinal will contain the path to latest ini file 
my $fileLocationFinal = $fileLocation.$ExtractedFileName;
open FILEI, "$fileLocationFinal"  or die $!;
	while(<FILEI>) {
		if($_ =~ /BUILD_NUMBER/) {
		 # Split and get the 2nd element 
                 $extractedDateVal = (split '=',$_)[1];
                 push(@valueOfBuildDates,$extractedDateVal);
                 push(@valueOfPS,$ExtractedFileName);
                 $NumberOfPS++;
		}
	}
close(FILEI);
}
} else {
$NumberOfPS=1;
open FILE, "__BRM_HOME__/inventory/ContentsXML/comps.xml"  or die $!;
}

open PINREV, ">/home/pin/opt/portal/oui/bin/pinrev.dat"  or die $!;

while( $NumberOfPS)
{
#This writes ini file name, before writing BRM module versions. This helps to separate different patch set versions
    if(defined($ARGV[0]))
    {
      my $BRM_Version = substr($valueOfPS[$index],0,-4);
      print PINREV " BRM Version = $BRM_Version\n";
    }
    while(<FILE>) {
	if(/$comp_name/) {
		# Skip the following Component List from pinrev output
		if($1 !~ "CORE" && $1 !~ "DataManager" && $1 !~ "ConnectionManager" && $1 !~ "BRMOptionalManagers" && $1 !~ "BRMServer" && $1 !~ "common" && $1 !~ "CMCommon" && $1 !~ "Optional_Mgr_Reports" && $1 !~ "BRMReports" && $1 !~ "BRMInvoices") {
			print PINREV "========================================================================\n";
			print PINREV "==================================INSTALLED============================\n";
			print PINREV  "COMPONENT NAME = $1 \n ";
			if($_ =~ /$build_no/) {
				if(not defined($ARGV[0]))
                                {
				  $date = $1;
			        }
              #fetch BuidNumber values which were stored after extracting from ini files.
                                else
                                {
                                   $date = $valueOfBuildDates[$index];
                                }
				my @d = split('',$date);
				my $yy = "$d[0]"."$d[1]";
				my $mm = "$d[2]"."$d[3]";
				my $dd = "$d[4]"."$d[5]";
				my $hh = "$d[6]"."$d[7]";
				my $min = "$d[8]"."$d[9]";
				my $timet = timelocal(0, "$min","$hh", "$dd", "$mm"-1, "$yy");
				my $ltime = localtime($timet);

				#my $ltime = "$mm-$dd-20$yy $hh:$min:0";

				print PINREV "BUILD_NUMBER = $ltime \n";
			}
			# Install Time handling for OUI-12C
			if(not defined($ARGV[0])) {
                                if($_ =~ /$install_time/) {
                                        print PINREV "INSTALL_TIME = $1.$2.$3 $4.$5.$6 $7 \n";
                                }
                        } else {
                               print PINREV "INSTALL_TIME = ". `date`;
                        }

			print PINREV "========================================================================\n";
		}
	}
}
seek FILE, 0, SEEK_SET;
--$NumberOfPS;
++$index;
}
close(FILE);
close(PINREV);
system("cat /home/pin/opt/portal/oui/bin/pinrev.dat");
system("/home/pin/opt/portal/OPatch/opatch lsinv -OH /home/pin/opt/portal");
