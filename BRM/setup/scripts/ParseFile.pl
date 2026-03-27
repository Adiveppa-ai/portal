#!__PERL_HOME__/bin/perl 
#
# $Header: install_vob/nginstall/ParseFile.pl /cgbubrm_mainbrm.portalbase/7 2018/09/06 02:21:25 mkothari Exp $
#
# ParseFile.pl
#
# Copyright (c) 2018, Oracle and/or its affiliates. All rights reserved.
#
#    NAME
#      ParseFile.pl - To parse file diff.lst and take back-up
#
#    MODIFIED   (MM/DD/YY)
#    mkothari    05/02/18 - Creation
#

use File::Find;
sub trim;

if(defined($ARGV[2])) {
        my $changeTo = '__PERL_HOME__/bin/perl';
        open PH,"<$ARGV[0]/BRM/setup/scripts/pin_setup.pl";
        my $changeFrom1 = trim(<PH>);
        @changeFrom = split('!',$changeFrom1);
        $ch = '\#\!'.$changeFrom[1];
        @list =  `find $ARGV[0] -type f -exec egrep -l "$ch" {} \\; |grep -v ParseFile`;
        foreach $file (@list) {
                if($file !~ /\.GA/) {
                        open (IN,$file) || die "unable to open $file";
                        @lines=<IN>;
                        close(IN);
                        $file =~ s/\s+$//;
                        open(OUT,">",$file) || die "unable to open $file";
                                foreach my $line (@lines){
                                        $line =~ s/$changeFrom[1]/$changeTo/g;
                                        print OUT $line;
                                }
                        system(" chmod 755 $file ");
                        close(OUT);
                }
        }
        close PH;
	exit;
}

our @list=();

if(-e "$ARGV[1]/diff.lst") {
	exit if(-e "$ARGV[0]/BRM/lib/fm_subscription.so.GA"); 
	open FH,"$ARGV[1]/diff.lst";
	while(<FH>) {
		next if /^\s*#/; 
		if($_ !~ /Component/ && $_ !~ /------/ && $_ !~ /NEW FILE/ ) {
			push(@list,trim($_));
		} 
	}
	close FH;
}

unlink("$ARGV[0]/log.txt") if(-e "$ARGV[0]/log.txt");

open LOGFILE, ">$ARGV[0]/log.txt" or die "Unable to open the log file",$!;

foreach $list (@list) {
	my @a = `find $ARGV[0] -name $list | grep -v Templates`;
	foreach $sub_list (@a) {
		$sub_list = trim($sub_list);
		if(-e "$sub_list" && !-e "$sub_list.GA" && $sub_list !~ /.GA/) {
			next if($sub_list eq "deInstall.pl");
			next if(-d "$sub_list");
			system(" cp -rf $sub_list $sub_list.GA ");
			print LOGFILE "creating GA : $sub_list \n";
		} else {
			print LOGFILE "Skip : $sub_list\n";
		}
	}
}

sub find_txt {

my $F = $File::Find::name;
        next if(-d $F);
        if($F !~ /.GA$/ && !-e "$F.GA" && $F !~ /_1$/ && $F !~ /inventory/ && $F !~ /oracle_common/ && $F !~ /plugins/ && $F !~ /OPatch/ && $F !~ /user_projects/) {
		next if($F =~ /log.txt/);
		next if($F =~ /libssl/);
		next if($F =~ /libcrypto/);
		next if($F =~ /xalan/);
		print LOGFILE "TGA : $F \n";
                system("cp -rf $F $F.TGA ");
        }

}
find({ wanted => \&find_txt, no_chdir=>1}, $ARGV[0]);

sub trim($) {
        my $string = shift;
        $string =~ s/^\s+//;
        $string =~ s/\s+$//;
        return $string;
}

close(LOGFILE);

