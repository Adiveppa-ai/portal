##!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
## @(#): convert_taxcode.pl /cgbubrm_mainbrm.portalbase/0 2021/11/11 02:42:04 vanmahaj Exp $
## Copyright (c) 2022, Oracle and/or its affiliates. All rights reserved.
##
## This material is the confidential property of Oracle Corporation
## or its licensors and may be used, reproduced, stored
## or transmitted only in accordance with a valid Oracle license or
## sublicense agreement.
##
#=============================================================
# Perl script for converting taxcode_map file into a XML file
# Usage:
#	 perl convert_taxcode.pl input_filename <output_filename>
#	 
#	 Input taxcode_map to be coverted
#	 	default file location: $PIN_HOME/sys/cm/taxcodes_map
#
#	 Output file is optional, if not provided, default file 
#	 	config_taxcodes_map.xml will be generated.
#
# Note: Copy Generated output file to $PIN_HOME/sys/data/config/config_taxcodes_map.xml
#
# And load using load_config using below command from $PIN_HOME/apps/load_config/
#
# load_config -M $PIN_HOME/sys/data/config/config_taxcodes_map.xml
#
#=============================================================

use strict;
use warnings;

#Validate that only 2 parameters should be passed.
if ($#ARGV > 1 ) {
        print "Error: only 2 parameters should be passed.\n";
        exit;
}

#checking if input filename is passed or not,
#if not passed exit
if(!defined($ARGV[0]) || $ARGV[0] eq '--help' || $ARGV[0] eq '-h') {

        print "\nUsage : perl $0 input_filename <output_filename>\n\n",
		"Note: output file is optional, ", 
		"default file config_taxcodes_map.xml will be generated\n\n";
        exit;
}

#default outputfile name
my $output_file = "config_taxcodes_map.xml" ;

#if outputfile name passed use that
if (defined($ARGV[1])){	

	$output_file = $ARGV[1];
} 

#opening inputfile, if any error exit 
open (FH, '<', $ARGV[0])
	or die "Can't open $ARGV[0]: $! \n";

#opening outputfile, if any error exit 
open(DATA, '>', $output_file)
	or die "Can't open $output_file: $! \n";

my $elem_id = 1;

print DATA "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n",
		"<ObjectList\n",
		"  xmlns=\"http://www.oracle.com/schemas/BusinessConfig\"\n",
		"  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n",
		"  xsi:schemaLocation=\"http://www.oracle.com/schemas/BusinessConfig",
			" ../../../xsd/config_object.xsd\">\n\n",
		"  <ConfigObject configName=\"/config/taxcodes_map\" configMode=\"recreate\">\n",
		"    <DESCR>Taxcodes Map Configuration</DESCR>\n",
		"    <NAME>taxcodes_map</NAME>\n";

# Reading the file line by line till FH reaches EOF
while (<FH>) {

	#ignore commented lines and empty lines
	if ($_ !~ /^#|^\s*$/ ) {

		#Split the line based on ':'
		my @spl = split(':', $_);
		foreach my $i (@spl) {

			$i = trim ($i);
			$i = check_special_char($i);
		}
		
		my $size = @spl;

		if ($size < 3){

			print "\nInvalid data : $_ \n";
			ending();
			print "Exiting \n";
			exit;
		}
		if ($size > 3 && $spl[1] eq 'U' ) {

			#Sample
			#usage: U : 4.0 : 02/01/01 : 01/31/20 : Fed : US : USF : Std
			user_code(@spl);
		} elsif ($size == 3 && $spl[1] eq 'U' ){

			#Sample
			#user_code       :  U  :  10.0
			user_vertex(@spl);
		} elsif ($spl[1] eq 'C' || $spl[1] eq 'Q') {

			#Sample
			#qt_usage        :  Q  :    01 :    01 :  S
			vertex(@spl);
		} else {

			print "\nInvalid data : $_ \n";
			ending();
			print "Exiting \n";
			exit;
		}
	}
}

ending();
print "\n\tFile Generated: $output_file\n\n";

sub trim {

	my $string = shift;
	$string =~ s/^\s+|\s+$//g; 
	return $string;
}

sub check_special_char {

	my $string = shift;
	$string =~ s/&/&amp;/g; 
	return $string;
}

sub user_code {

	print DATA "	<TAXES elem=\"$elem_id\">\n";
	print DATA "	  <TAX_CODE>$_[0]</TAX_CODE>\n";
	print DATA "	  <TAXPKG_TAX_CODE>$_[1]</TAXPKG_TAX_CODE>\n";
	print DATA "	  <PERCENT>$_[2]</PERCENT>\n";
	print DATA "	  <VALID_FROM_STR>$_[3]</VALID_FROM_STR>\n";
	print DATA "	  <VALID_TO_STR>$_[4]</VALID_TO_STR>\n";
	print DATA "	  <TAX_JURISDICTION>$_[5]</TAX_JURISDICTION>\n";
	print DATA "	  <TAX_JURISDICTION_LIST>$_[6]</TAX_JURISDICTION_LIST>\n";
	print DATA "	  <DESCR>$_[7]</DESCR>\n";
	print DATA "	  <RULE_TYPE>$_[8]</RULE_TYPE>\n";
	print DATA "	</TAXES>\n";
	$elem_id++;
}

sub user_vertex {

	print DATA "	<TAXES elem=\"$elem_id\">\n";
	print DATA "	  <TAX_CODE>$_[0]</TAX_CODE>\n";
	print DATA "	  <TAXPKG_TAX_CODE>$_[1]</TAXPKG_TAX_CODE>\n";
	print DATA "	  <CODE1>$_[2]</CODE1>\n";
	print DATA "	</TAXES>\n";
	$elem_id++;
}

sub vertex {

	print DATA "	<TAXES elem=\"$elem_id\">\n";
	print DATA "	  <TAX_CODE>$_[0]</TAX_CODE>\n";
	print DATA "	  <TAXPKG_TAX_CODE>$_[1]</TAXPKG_TAX_CODE>\n";
	print DATA "	  <CODE1>$_[2]</CODE1>\n";
	print DATA "	  <CODE2>$_[3]</CODE2>\n";
	if ($_[4] eq ""){
		print DATA "	  <SALES_INDICATOR>S</SALES_INDICATOR>\n";
	} else {
		print DATA "	  <SALES_INDICATOR>$_[4]</SALES_INDICATOR>\n";
	}
	print DATA "	</TAXES>\n";
	$elem_id++;
}

sub ending {

	print DATA "  </ConfigObject>\n",
			"</ObjectList>";
	close (FH);
	close (DATA);
}
