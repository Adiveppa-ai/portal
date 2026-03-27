#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl -w
# 
# $Header: install_vob/nginstall/components/postInstallReplace.pl /cgbubrm_mainbrm.portalbase/16 2018/04/04 04:29:50 mkothari Exp $
#
# postInstallReplace.pl
# 
# Copyright (c) 2023, Oracle and/or its affiliates.
#
#    NAME
#      postInstallReplace.pl - <one-line expansion of the name>
#
#    DESCRIPTION
#      <short description of component this file declares/defines>
#
#    NOTES
#      <other useful comments, qualifications, etc.>
#
#    MODIFIED   (MM/DD/YY)
#    mkothari    11/28/16 - Creation
#    suyayada	 07/27/23 - Updated ( CM Auth role changes )
# 
#

sub replaceVar {
my ($file) = shift;
#print $file;
my $perl_home = "/home/pin/opt/portal/Thirdparty/perl-5.38.2";
my $perl;
if ( -e $perl_home ) {
	$perl = $perl_home;
}
if ( -e "${perl_home}/perl" ) {
	$perl = "${perl_home}/perl";
}
if ( -e "${perl_home}/bin/perl" ) {
	$perl = "${perl_home}/bin/perl";
}
open (IN,$file) || die "unable to open $file";
@lines=<IN>;
close(IN);
$file =~ s/\s+$//;
open(OUT,">",$file) || die "unable to open $file";
        foreach my $line (@lines){
                $line =~ s/__PERL__/${perl}/g;
                $line =~ s/__PIN_HOME__/\/home\/pin\/opt\/portal\/BRM/g;
                $line =~ s/__PIN_LOG_DIR__/\/home\/pin\/opt\/portal\/BRM\/var/g;
                $line =~ s/BRM_JRE/JAVA_HOME/g;
                $line =~ s/__VERSION__/7.5/g;
                print OUT $line;
        }
close(OUT);

}

if(!defined($ARGV[1])) {
	my @file_name = `find /home/pin/opt/portal/BRM -type f -exec egrep -l "__PERL__|__PIN_LOG_DIR__|__PIN_HOME__|BRM_JRE" {} \\; |grep -v postInstallReplace`;
	foreach my $file (@file_name){
		replaceVar($file);
	}
}

=for comment
@listRemove =(
'pin_ctl',
'pin_bus_params',
'pin_configure_ha',
'opgen',
'pin_load_template',
'OODHandler',
'load_suspended_batch_info',
'pin_load_invoice_events',
'pin_wsdl_generator',
'fldgen',
'splitPinlog',
'BillHandler',
'pin_opspec_to_schema',
'pin_load_invoice_template',
'pin_dd_to_schema'
);

if(!defined($ARGV[1])) {
	for $ls (@listRemove) {
		if(-e "\/home\/pin\/opt\/portal\/BRM/bin/$ls" && !-e "\/home\/pin\/opt\/portal\/BRM/bin/$ls.baK") {
			system(" /home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl -i.baK -ne 'print if 2..eof' \/home\/pin\/opt\/portal\/BRM/bin/$ls ");
		}
	}
}
=cut

# Pipeline folder
if(-d "/home/pin/opt/portal/ifw") {
       if(!defined($ARGV[1])) {
		my @file_name1 = `find /home/pin/opt/portal/ifw -type f -exec egrep -l "__PERL__|__PIN_LOG_DIR__|__PIN_HOME__|BRM_JRE" {} \\; |grep -v postInstallReplace`;
       		 foreach my $file (@file_name1){
                        replaceVar($file);
                }
        }
}

sub updateDBFPath {
	my $db = $_[0];
	my $sys_pw = $_[1];
	my $is_sysdba = `echo 'select 1 from dual;' | sqlplus -s null/__SYS_PASSWD__\@BRM as sysdba|/bin/sed '/^\$/d' |/usr/bin/tail -1`;
	chomp($is_sysdba);
	$is_sysdba=~ s/^\s+|\s+$//g;
	if($is_sysdba eq "1"){
		$is_sysdba="as sysdba";
	}else{
		$is_sysdba = `echo 'select 1 from dual;' | sqlplus -s null/__SYS_PASSWD__\@BRM as sysdba|/bin/sed '/^\$/d' |/usr/bin/tail -1`;
		chomp($is_sysdba);
		$is_sysdba=~ s/^\s+|\s+$//g;
		if($is_sysdba eq "1"){
			$is_sysdba="";
		}else{
			$is_sysdba="as sysdba";
		}
	}

        if( -e $db) {
		my $new_db = "$db.new";
		my $data_file_path = `echo 'select file_name from dba_data_files;' | sqlplus null/__SYS_PASSWD__\@BRM $is_sysdba | /bin/sed -n 's|[^\\/][^\\/]*\.[Dd][Bb][Ff]\$\||p' | /usr/bin/tail -1`;
		chomp($data_file_path);

                open(FILE    , "<", $db) or die "cannot open file: $db.";
                open(FILEDUMP, ">", $new_db)  or die "cannot open file: $new_db\.pwd.";
                while(<FILE>){
                        if($_ =~ m/__DBF_PATH__/ ) {
                                $_ =~ s/__DBF_PATH__/$data_file_path/g;
                                print FILEDUMP "$_";
                        } else {
                                print FILEDUMP "$_";
                        }
                }
                close(FILE);
                close(FILEDUMP);
                system("mv $new_db $db");
        }
}

	if(defined($ARGV[0]) && defined($ARGV[1])) {
		my $db1;
		if($ARGV[0] eq "dbf") {
			$db1 = "/home/pin/opt/portal/BRM/setup/scripts/createDBUser.sql";
		}
		if($ARGV[0] eq "ifw") {
			$db1 = "/home/pin/opt/portal/ifw/database/Oracle/Scripts/createDBUser.sql";
		}
		updateDBFPath($db1,$ARGV[1]);
	}

# Support for MD5 Encryption
if(defined($ARGV[0]) && $ARGV[0] ne "dbf" && $ARGV[0] ne "ifw") {
	my $brm_root_pw='$ARGV[0]';
	my $brm_role_pw='$ARGV[0]';
	my $root_hashed = `\/home\/pin\/opt\/portal\/BRM/bin/pbkdf2_encode '$brm_root_pw'`;
	my $role_hashed = `\/home\/pin\/opt\/portal\/BRM/bin/pbkdf2_encode '$brm_role_pw'`;

	my $find = "md5";
	my $find1 = "rolePassword";
	my $pre = '0 PIN_FLD_PASSWD          STR [0] "';

	open FILE, "\/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_objects.source"  or die "cannot open file \/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_objects.source: $!";
	open FILEDUMP, ">\/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_objects.mod"  or die "cannot open file \/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_objects.mod: $!";
	
	while(<FILE>) {
		if($_ =~ m/$find/ && $_ !~ m/$root_hashed/ ) {
			print FILEDUMP "$pre$root_hashed\"\n";
		} elsif($_ =~ m/$find1/ && $_ !~ m/$role_hashed/){
			print FILEDUMP "$pre$role_hashed\"\n";
		} else {
			print FILEDUMP "$_";
		}
	}
	close(FILEDUMP);
	close(FILE);
	system("mv \/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_objects.mod \/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_objects.source");

	if(-e "\/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_service_objects_15.source" ) {
		
		open FILE, "\/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_service_objects_15.source"  or die "cannot open file \/home\/pin\/opt\/portal\/BRM/sys/dd/data/	init_service_objects_15.source: $!";
		open FILEDUMP, ">\/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_service_objects_15.mod"  or die "cannot open file \/home\/pin\/opt\/portal\/BRM/sys/dd/data/	init_service_objects_15.mod: $!";

		while(<FILE>) {
			if($_ =~ m/$find1/ && $_ !~ m/$role_hashed/){
				print FILEDUMP "$pre$role_hashed\"\n";
			} else {
				print FILEDUMP "$_";
			}
		}
		close(FILEDUMP);
		close(FILE);
		system("mv \/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_service_objects_15.mod \/home\/pin\/opt\/portal\/BRM/sys/dd/data/init_service_objects_15.source");
	}

}
