#!__PERL__/bin/perl
# 
# $Header: install_vob/nginstall/components/deInstall.pl /cgbubrm_mainbrm.portalbase/5 2018/09/06 02:21:25 mkothari Exp $
#
# deInstall.pl
# 
# Copyright (c) 2017, 2024, Oracle and/or its affiliates.
#
#    NAME
#      deInstall.pl <path to pin.conf file> <pattern to be searched>
#
#    DESCRIPTION
#	The whole line containing the pattern will be removed
#
#    MODIFIED   (MM/DD/YY)
#    mkothari    04/21/14 - Creation in mainrb1
# 

use File::Find;

if(defined($ARGV[2])) {

sub find_txt {
    my $F = $File::Find::name;

	if ( $F =~ /.GA$/ ) {
		our @a = split('\.GA',$F);
		system(" mv -f $F $a[0] " ) if(!-e "$a[0]");
		# Special case
		if( $F =~ /pin_upgrade_15/) {
			system(" mv -f $F $a[0] " ) if(-e "$a[0]");
		}
	}
        if( $F =~ /.TGA$/ && ( $ARGV[1] eq '0' ) ) {
                our @s = split('\.TGA',$F);
		if(!-e "$s[0]") {
			system(" mv -f $F $s[0] ");
		} else {
			system(" rm -f $F ");
		}
        }
}
find({ wanted => \&find_txt, no_chdir=>1}, $ARGV[2]);

exit;
}

my $find = "$ARGV[1]";

if ((!defined($ARGV[0])) || (!-e "/home/pin/opt/portal/BRM/$ARGV[0]/pin.conf"))
{
exit;
}

open FILE, "/home/pin/opt/portal/BRM/$ARGV[0]/pin.conf"  or die $!;
open FILEDUMP, ">/home/pin/opt/portal/BRM/$ARGV[0]/pin.conf_1"  or die $!;

while(<FILE>)
{
if($_ =~ m/$find/)
{
$_ = s/$_//;
print FILEDUMP "#$_";
}
else
{
print FILEDUMP "$_";
}
}
close(FILEDUMP);
close(FILE);

system("mv /home/pin/opt/portal/BRM/$ARGV[0]/pin.conf_1 /home/pin/opt/portal/BRM/$ARGV[0]/pin.conf ");
