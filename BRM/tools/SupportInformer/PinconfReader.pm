#
# @(#)%Portal Version: PinconfReader.pm:PlatformR2Int:1:2006-Jul-04 11:25:30 %
#
#       Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#      
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#

use strict;
use FileSystem;

package PinconfReader;

#
# Global variables
#
my $pin_home_path;
my $pin_log_path;
my $sup_inf_path = "";
my @elements = ();
my @exclude_comp = ("dd", "config", "data", "msgs");
my @exclude_apps = ();

###############################################################################
# This module checks whether PIN_HOME and PIN_LIB environment variables are set
###############################################################################
sub check_portal_env_variables
# Arg 1: contains the destination path used to store the collected files
{
	$sup_inf_path = shift(@_);
	if (defined $ENV{PIN_HOME}) {
		$pin_home_path = $ENV{PIN_HOME};
	} else {
		print "PIN_HOME is not set\n";
		exit(1);
	}
	if (defined $ENV{PIN_LOG}) {
		$pin_log_path = $ENV{PIN_LOG};
	} else {
		print "PIN_LOG is not set\n";
		exit(1);
	}
}

###############################################################################
# Populates all the components into element array used to collect logs
###############################################################################
sub find_elements
# Arg 1: Element type
{
	my $elem_type	= shift(@_);
	my $elem_path;
	my $filename	=	"elementslist.txt";
	my $line;
	my $command;
	my @elemlist = ();
	my $no_of_elem = 0;
	#Initialise elements array
	@elements = ();

	if ($elem_type == 0) {
		$elem_path = $pin_home_path."/sys";
	} else {
		$elem_path = $pin_home_path."/apps";
	}
	opendir MYDIR, "$elem_path";
	@elemlist = grep { !/^\.\.?$/ && -d "$elem_path/$_" } readdir MYDIR;
	closedir MYDIR;
	$no_of_elem = @elemlist;
	if ($no_of_elem > 0) {
		main::printLog("Elements List:\n\n");
		foreach $line(@elemlist) {
			chomp($line);
			if (evaluate_element($elem_type, $line) == 0) {
				push(@elements, $line);
				main::printLog($line."\n");
			}
		}
	} else {
		main::printLog("There are no elements available in $elem_path\n");
	}
}

###############################################################################
# Create directories for all the components in elements array
###############################################################################
sub create_directories
{
	my $elem_name;
	my $file_path;
	foreach $elem_name (@elements) {
		$file_path = $sup_inf_path."/".$elem_name;
		FileSystem::createDir($file_path);
	}
}

###############################################################################
# Validates the given element
###############################################################################
sub evaluate_element
# Arg 1: Contains element type
#		0 - for sys components
#		1 - for apps components
# Arg 2: Element name
# Returns: 0 - for valid element
#	   1 - for invalid element
{
	my $elem_type = shift(@_);
	my $element = shift(@_);
	my $found = 0;
	if ($elem_type == 0) {
		foreach (@exclude_comp) {
			if ($element eq $_) {
				$found = 1;
				last;
			}
		}
	} else {
		foreach (@exclude_apps) {
			if ($element eq $_) {
				$found = 1;
				last;
			}
		}
	}
	return $found;
}

###############################################################################
# Evaluates the input variable
###############################################################################
sub evaluate_env_variable
# Arg 1: Assume to be environment variable
# Exits if given variable is not set
# Returns: Value set for the input variable
{
	my $input_str = shift(@_);
	my $result_str = "";
	if (defined($ENV{"$input_str"})) {
		$result_str = $ENV{"$input_str"};
	} else {
		print "Environment variable $input_str is not defined\n";
		exit(1);
	}
	return $result_str;
}

###############################################################################
# Evaluates the environment variables for the given path
###############################################################################
sub evaluate_path
# Arg 1: path to be evaluated
# Returns: evaluated path
{
	my $input_str = shift(@_);
	my $dolar_pred;
	my $dolar_succ;
	my $slash_position;
	my $evaluated_str;
	my $slash_succ;
	my $position;
	my $final_str = "";
	while (1) {
		$position = index($input_str, "\$");
		if ($position == -1) {
			$final_str = $final_str.$input_str;
			last;
		} else {
			$dolar_pred = substr($input_str, 0, $position);
			$dolar_succ = substr($input_str, $position + 1);
			# remove_braces_if_any
			$dolar_succ =~ s/{//g;
			$dolar_succ =~ s/}//g;
			$slash_position = index($dolar_succ, "/");
			if ($slash_position == -1) {
				$evaluated_str = evaluate_env_variable($dolar_succ);
			} else {
				$evaluated_str = evaluate_env_variable(substr($dolar_succ, 0, $slash_position));
				$slash_succ = substr($dolar_succ, $slash_position);
			}
			$final_str = $final_str.$dolar_pred.$evaluated_str;
			$input_str = $slash_succ;
		}
	}
	return $final_str;
}

###############################################################################
# Sends SIGUSR1 signal to dm_oracle and cm processes
###############################################################################
sub send_sigusr1
# Arg 1: Component name
{
	my $command;
	my $comp_name = shift(@_);
	my $process_id;
	my $filename;
	my $no_of_rows;
	#get process_id from PID_FILE
	$filename = "$pin_log_path/$comp_name/$comp_name.pid";
	open(CMD, "$filename") ||
		die "cannot open $filename\n";
	$process_id = <CMD>;
	close(CMD);
	chomp($process_id);
	# Please look on this command, use ps -ef
	$command = "ps -p ".$process_id;
	#check whether process is running
	$filename = "psp.txt";
	open(CMD, $command . " > " . $filename . "|");
	close(CMD);
	if (($? >> 8) == 0) {
		open(CMD, "$filename")	||
			die "cannot open $filename\n";
		my @startlist = <CMD>;
		close(CMD);
		$no_of_rows = @startlist;
		if ($no_of_rows == 2) {
			#process is in running state, so send SIGUSR1
			if (kill USR1=> $process_id) {
			    main::printLog("Successfully sent the signal SIGUSR1 $process_id\n");
			} else {
			    main::printLog("Failed to send signal SIGUSR1 $process_id\n");
			}
		} else {
			main::printLog("$comp_name Process is not in running state\n");
		}
	}
	unlink "$filename";
}

###############################################################################
# Collects log and pinlog files
###############################################################################
sub copy_log_files
# Arg 1: Component name
# Arg 2: working directory path
# Arg 3: file to be search
# Arg 4: search string
# Returns: Whether logs are copied or not
{
	my ($elem_name, $working_path, $filename, $search_str) = @_;
	my $dest_path = $sup_inf_path."/".$elem_name;
	my $line;
	my $position;
	my $found = 0;
	my $pinlog_str;
	my $final_str = "";
	my $dolar_pred;
	my $dolar_succ;
	my $slash_position;
	my $evaluated_str;
	my $slash_succ;
	my $log_found = 0;
	my $log_file;
	my $log_file_path;

	# read start script
	open(CMD, $working_path.$filename) ||
		die "cannot open $filename\n";
	my @lines = <CMD>;
	close(CMD);
	foreach $line (@lines) {
		chomp($line);
		if (($line !~ /^#/) and ($position = index($line, $search_str)) != -1) {
			$pinlog_str = substr($line, $position + length($search_str) + 1);
			chomp($pinlog_str);
			$final_str = evaluate_path($pinlog_str);
			# check whether pinlog file has path, if not then assume to be working dir
			if ($final_str !~ /\//) {
				$final_str = $working_path.$final_str;
			} elsif ($final_str =~ m/^\.\//) {
				$final_str = $working_path.substr($final_str, 2);
			}
			if (FileSystem::file_exists($final_str)) {	
				FileSystem::tail($dest_path, $final_str);
				$log_found++;
			}
		}
	}
	if ($elem_name eq "batch_controller") {
		$log_file = "BatchController.log";
	} else {
		$log_file = "$elem_name.log";
	}
	# Copy log file if exists
	$log_file_path = "$pin_log_path/$elem_name/";
	if (FileSystem::file_exists($log_file_path.$log_file)) {
		FileSystem::tail($dest_path, $log_file_path.$log_file);
		$log_found++;
	} else {
		# log file may exists in working_path
		$log_file_path = "$working_path";
		if (FileSystem::file_exists($log_file_path.$log_file)) {
			FileSystem::tail($dest_path, $log_file_path.$log_file);
			$log_found++;
		}
	}

	return $log_found;
}

###############################################################################
# Main module that is used to collect logs for each component
###############################################################################
sub process_element
# Arg 1: Component name
# Arg 2: Component type
{
	my ($elem_name, $elem_type) = @_;
	my $dest_path = $sup_inf_path."/".$elem_name;
	my $working_path = "";
	my $log_found = 0;
	my $filename = "pin.conf";
	my $search_str = "logfile";
	my @sub_folders = ();

	# Check whether the element is component or application
	# and set working path accordingly
	if ($elem_type == 0) {
		$working_path = "$pin_home_path/sys/$elem_name/";
	} else {
		$working_path = "$pin_home_path/apps/$elem_name/";
	}

	# Check whether pin.conf exists
	if (FileSystem::file_exists($working_path.$filename)) {
		# Copy pinlog and log files
		$log_found = copy_log_files($elem_name, $working_path, $filename, $search_str);
		if ($log_found > 0) {
			# copy pin.conf file
			FileSystem::copy($dest_path, $working_path.$filename);
		}
	}

	# Check for Infranet.properties only for applications
		$log_found = 0;
		$filename = "Infranet.properties";
		$search_str = "infranet\.log\.file";
		# Check whether Infranet.properties exists
		if (FileSystem::file_exists($working_path.$filename)) {
			# Copy pinlog and log files
			$log_found = copy_log_files($elem_name, $working_path, $filename, $search_str);
			if ($log_found > 0) {
				# copy Infranet.properties file
				FileSystem::copy($dest_path, $working_path.$filename);
			}
		}

	# Copy if default.pinlog or core exists
	if (FileSystem::file_exists($working_path."default.pinlog")) {
		FileSystem::tail($dest_path, $working_path."default.pinlog");
		if ($elem_name eq "test") {
			FileSystem::copy($dest_path, $working_path."pin.conf");
		}
	}
	FileSystem::copy($dest_path, $working_path."core");
}

###############################################################################
# Processes all the sys components
###############################################################################
sub process_all_components
{
	my $comp_name;
	# get the components list
	find_elements(0);
	# create directories for each component
	create_directories();
	foreach $comp_name (@elements) {
		if ($comp_name =~ m/^dm_oracle/ || $comp_name eq "cm") {
			# Send SIGUSR1 signal to this process -- Only for Unix platforms
			send_sigusr1($comp_name);
			# For the time being -- do what for the libraries is not doing
		}
		process_element($comp_name, 0);
	}
}

###############################################################################
# Processes all the apps components
###############################################################################
sub process_all_applications
{
	my $apps_name;
	# get the applications list
	find_elements(1);
	# create directories for each application
	create_directories();
	foreach $apps_name (@elements) {
		process_element($apps_name, 1);
	}
}
1;
