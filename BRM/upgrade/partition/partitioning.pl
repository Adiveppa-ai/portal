#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
# 
# @(#)$Id: partitioning.pl /cgbubrm_mainbrm.portalbase/5 2022/12/08 02:42:07 rbogulla Exp $
#
# Copyright (c) 2005, 2023, Oracle and/or its affiliates.
#
#      This material is the confidential property of Oracle Corporation or
#      its licensors and may be used, reproduced, stored or transmitted only
#      in accordance with a valid Oracle license or sublicense agreement.
#
#
# Driving script for the upgrade.
#=============================================================
require "./upg_oracle_functions.pl";

$argn = @ARGV;

$cne = $ENV{'DOCKER'};
local ($config_file) = "./partition.cfg";
local ($tmpfile) = "$config_file.tmp";

if( $cne == 1 ){
	use File::Copy;
	if( $argn == 0 ){
		print "no arguments.\n";
		exit 0;
	}
	$files_for_partition = "";
	$file_count = 0;
	foreach $arg (@ARGV){
		local $fileExt = "_tables_tobe_partitioned.sql";
		local $obj = substr( $arg, 1);
		$file_name = $obj.$fileExt;
		if( $file_count == 0){
			$files_for_partition = $files_for_partition."\\\"${file_name}\\\"";
		}
		else{
			$files_for_partition = $files_for_partition.",\\\"${file_name}\\\"";
		}
		$file_count = $file_count + 1;
	}
	$files_for_partition = $files_for_partition."";
	copy("${config_file}", "${tmpfile}") or die "copy failed: $!";;
	`sed -e 's#__FILES_FOR_PARTITION__#'${files_for_partition}'#g' ${tmpfile} > ${config_file}`;
	$argn = 0;
}

require "./partition.cfg";

if ($argn > 1 && $cne == 0 )
{
        print "\nUSAGE: perl partition.pl [ filename ] \n";
        print "\nwhere filename is an upgrade sql script \n";
        exit 0;
}

#
# Create the PARTITION_LOG_DIR if it doesn't exist.
#

if  ( ! -e $PARTITION_LOG_DIR ) 
{
	mkdir ("$PARTITION_LOG_DIR", 0777) || die "Unable to create $PARTITION_LOG_DIR directory";
	print "Creating log directory $PARTITION_LOG_DIR \n";
}

#
# Create the upgrade.log file to append all the messages from upgrade
#

open (MAINLOG, ">>$PARTITION_LOG_DIR/partition.log") || die "Unable to create file $PARTITION_LOG_DIR/partition.log";

#
# Here we can execute the PL/SQL script by name if a name was given
# or all the scripts in the list.  If all, we execute the scripts 
# one at a time. The file list is defined in the upgrade.cfg file.
#   
if( $cne == 1 ){
    foreach $arg (@ARGV){
        print "Processing object $arg\n";
        if($arg =~ /invoice/){
            next;
        }
        else{
            process_object($arg);
        }   
    }
}


if ($argn == 0)
{
	print "Running all the scripts \n";
	print MAINLOG ("Running all the scripts \n");


	#
	# Check to make sure all the files in our list exist.
	#

	foreach $file (@ALL_SCRIPTS)
	{
		if ( ! -e "$UPG_DIR/$file" )
		{
			print "$UPG_DIR/$file not found \n";
			print MAINLOG ( "$UPG_DIR/$file not found \n" ); 
			exit 1;
		}
	}

	#
	# Now run the scripts in order 
	#

	foreach $file (@ALL_SCRIPTS)
	{
		$time_stamp = "Started $file at " . localtime(time());
		print MAINLOG ("$time_stamp \n"); 
		print "$time_stamp \n";

      		parse_exec_file($OWNER, $PASSWD, $DBNAME, "$file", 1);
       		$step_name = substr ($file, 0, rindex ($file, "."));
		crt_pinlog_file($step_name, 0);

		$error_in_logfile = find_oracle_error("$PARTITION_LOG_DIR/$file.log");
		$error_in_pinlogfile = find_oracle_error("$PARTITION_LOG_DIR/$file.pinlog");

		if ( $error_in_logfile || $error_in_pinlogfile )
		{
			print "Error executing $file \n";
			print MAINLOG ("Error executing $file \n");
			if( $cne == 1 ) {
				if( $error_in_logfile == 1 ){
					print `cat $PARTITION_LOG_DIR/$file.log`;
				}
				if( $error_in_pinlogfile == 1 ){
					print `cat $PARTITION_LOG_DIR/$file.pinlog`;
				}
				exit(1);
			}

			print ("Continue? (Y/N) ");
			print MAINLOG ("Continue? (Y/N) ");
			$continue = <STDIN>;
			chop($continue);

			while (uc($continue) ne "Y" && uc($continue) ne "N")
			{
			        print ("Improper command. Enter Y/N ");
			        print MAINLOG ("Improper command. Enter Y/N");
			        $continue = <STDIN>;
			        chop ($continue);
			}

			if (uc($continue) eq "Y")
			{
			        print ("Continuing from error \n");
			        print MAINLOG ("Continuing from error \n");
			        print ("Run $file again after fixing the errors \n");
			        print MAINLOG ("Run $file again after fixing the errors \n");
			}
			else
			{
			        print ("Aborting upgrade. Please fix errors and restart \n");
			        print ("Aborting upgrade. Please fix errors and restart \n");

				exit (1);
			}
		}
	}
}

#============================
# Handle single script 
#============================

else
{
        $file = @ARGV[0];

	$time_stamp = "Started $file at " . localtime(time());
	print MAINLOG ("$time_stamp \n"); 
	print "$time_stamp \n";

       	parse_exec_file($OWNER, $PASSWD, $DBNAME, "$file", 1);
       	$step_name = substr ($file, 0, rindex ($file, "."));
	crt_pinlog_file($step_name, 0);

       	$error_in_logfile = find_oracle_error("$PARTITION_LOG_DIR/$file.log");
       	$error_in_pinlogfile = find_oracle_error("$PARTITION_LOG_DIR/$file.pinlog");

	if ( $error_in_logfile || $error_in_pinlogfile )
	{
		print "\nError executing $file \n";
		print MAINLOG ("\nError executing $file \n");

		print ("Please run this script again after fixing the errors \n");
		print MAINLOG ("Please run this script again after fixing the errors \n"); 

		exit (1);
	}
}


print ( "\n" );
print MAINLOG ( "\n" );
print "Scripts completed successfully \n";
print MAINLOG ("Scripts completed successfully \n");

if ( $cne == 1 ) { 
	copy("${tmpfile}", "$config_file") or die "copy failed: $!";;
	unlink("${tmpfile}");
}

close(MAINLOG);

exit (0);
