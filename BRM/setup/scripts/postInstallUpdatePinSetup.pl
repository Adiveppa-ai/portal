#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
# 
# $Header: install_vob/nginstall/components/postInstallUpdatePinSetup.pl /cgbubrm_mainbrm.portalbase/3 2017/10/04 02:52:28 mkothari Exp $
#
# postInstallUpdatePinSetup.pl
# 
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#
#    NAME
#      postInstallUpdatePinSetup.pl - <one-line expansion of the name>
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

# Perl trim function to remove whitespace from the start and end of the string
sub trim($) {
	my $string = shift;
	$string =~ s/^\s+//;
	$string =~ s/\s+$//;
	return $string;
}

sub update_pin_setup_values {
	$file = $_[0];
	$component = $_[1];
	$product = $_[2];
	open (IN,$file) || die "unable to open $prpFile";
	@lines=<IN>;
	close(IN);
	open(OUT,">",$file) || die "unable to open $prpFile";
	#print " file "pin_setup.values""."\n";
	foreach my $line (@lines){
		if ($line =~ /^#/) {
			print OUT $line;
			next;
		}
		if ($line =~ /\@COMPONENT_LIST/) {
			if (trim($component) eq "" ) {
				print OUT "\@COMPONENT_LIST= ( \" \" );\n";
			}
			else {
				my @values = split('\(',$line);
				my @valueNext = split('\)',$values[1]);
				if ($valueNext[0] =~ "\"${component}\"" ) {
					print OUT $line;
				} else {
			 		print OUT "\@COMPONENT_LIST= ("."$valueNext[0]".","."\"${component}\");\n";
				}
			}
			next;
		}
                if ($line =~ /\@PRODUCT_LIST/) {
                        if (trim($product) eq "" ) {
                                print OUT "\@PRODUCT_LIST=( \n";
                        }
                        else {
                                my @values = split('\(',$line);
                                if ($values[1] =~ "\"${product}\"" ) {
                                        print OUT $line;
                                } else {
					if ( $values[1] !~ "\"" ) {
                                                print OUT "\@PRODUCT_LIST=("."\"${product}\"\n";
                                        } else {
                                                print OUT "\@PRODUCT_LIST=("."\"${product}\"".","."$values[1]\n";
                                        }

                                }
                        }
                        next;
                }
		print OUT $line;
	}
	close(OUT);
}
update_pin_setup_values($ARGV[0], $ARGV[1], $ARGV[2]);
