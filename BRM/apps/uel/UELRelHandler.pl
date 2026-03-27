#!__PERL_HOME
#
# $Header: client_vob/universal_event_loader/UELHandler/UELRelHandler.pl /cgbubrm_omc.19.main.portalbase/1 2019/03/26 13:00:29 arcmisra Exp $
#
# Copyright (c) 2015, 2019, Oracle and/or its affiliates. All rights reserved.
#
# @(#)%Portal Version: UELRelHandler.pl:UelEaiVelocityInt:4:2006-Sep-19 10:15:33 %
# Copyright (c) 2000, 2019, Oracle and/or its affiliates. All rights reserved.
#      This material is the confidential property of Oracle Corporation
#      or its licensors and may be used, reproduced, stored
#      or transmitted only in accordance with a valid Oracle license
#      or sublicense agreement.
#
# File:  UELRelHandler.pl
# Title: UELRel batch handler script
#
# Description:
#	This script is responsible for:
#	- calling the batch application to process the input files, and
#	- moving the input and output files to the appropriate
#	  directories based on the return value of the batch application.
#
#=============================================================


require "./UELHandler_config.values";
require "getopts.pl";

use pcmif;
use Sys::Hostname;
use File::Copy;
use File::Basename;
use File::Path;
use Fcntl qw (:flock);


#
# Define the UELRel Handler status variables that return
# to the database.
$HANDLER_STARTED = 1;			# Handler started properly.
$COMPLETED_NO_ERROR = 19;		# The file was processed by the batch
					# application with no error.
$DEAD_STATUS = 100;			# Status of a previously failed handler.
$WITH_ERROR = 101;			# The file was processed by the batch
					# application with error.
$REJECTED = 102;			# The file was rejected by the batch
					# application.
$PILOT_ERROR = 103;			# Batch application failed with
					# pilot error.
$NO_FILE_TYPE = 104;			# File does not exist.
$FAIL_TO_MOVE_FILE = 105;		# Failed to move the file to the
					# processing directory.
$NO_UEL_EXEC = 106;			# Batch application executable does
					# not exit.
$FAIL_TO_START_UEL = 107;		# Failed to start batch application.

#
# Value to massage negative batch application exit codes under Unix.
$UNIX_SHIFT = 8;


#
# Define the batch application exit code values.
$NO_ERROR = 0;
$FILE_CHECK_ERROR = -1;
$MEMORY_ERROR = -2;
$DISK_SPACE_ERROR = -3;
$TEMPLATE_ERROR = -4;
$BAD_INF_CONNECTION = -100;
$FIELD_PARSE_ERROR = 1;
$ACCT_FORMAT_ERROR = 2;
$LOAD_FORMAT_ERROR = 3;
$PREV_PARSE_ERROR = 4;
$TOO_MANY_LOAD_ERROR = 5;
$COMMAND_LINE_ARG_ERROR = 10;
$FILE_NOT_FOUND_ERROR = 11;
$ACCT_OPCODE_ERROR = 100 ;
$LOAD_OPCODE_ERROR = 101;


#
# Get the current time.
$localtime = localtime();


#
# Command line argument.
&Getopts('p:d:') || &usage;

if (!defined $opt_p) {
	&usage;
}
$current_poid = $opt_p;

#
# Check if there is a log file associated with the handler
open(LOG, ">>$LOGFILE");


#
# Get the current handler process id (PID)
$PID = $$;


#
# Log a debugging message in the handler log file
        $localtime = localtime();
if ($DEBUG) {
	print LOG "Handler associated with '$current_poid' started\n";
	print LOG "at $localtime with PID = $PID.\n";
}

# call function to parse UEL Infranet.properties
&parseInfranetProperties();

#
# setup and connect
my $db_no;
$ebufp = pcmif::pcm_perl_new_ebuf();
$pcm_ctxp = pcmif::pcm_perl_connect($db_no, $ebufp);
$DB_NO = $db_no;
if (pcmif::pcm_perl_is_err($ebufp)) {
	pcmif::pcm_perl_print_ebuf($ebufp);
	clean_exit(1);
} else {
	$my_session = pcmif::pcm_perl_get_session($pcm_ctxp);
	if ($DEBUG) {
		print LOG "$PID: Default DB is: $db_no\n";
		print LOG "$PID: Session poid is: ", $my_session, "\n";
	}
}


#
# Create the input Flist to update object status to STARTED.
$T_time = pcmif::pin_perl_time();
$hostname = hostname();
$f1 = << "END"
0 PIN_FLD_POID				     POID [0] $current_poid
0 PIN_FLD_START_T			   TSTAMP [0] ($T_time)
0 PIN_FLD_HOSTNAME			      STR [0] "$hostname"
0 PIN_FLD_PID				      INT [0] $$
0 PIN_FLD_STATUS			     ENUM [0] $HANDLER_STARTED
END
;


#
# Convert the flist string into an actual FList
$flistp = pcmif::pin_perl_str_to_flist($f1, $db_no, $ebufp);
if (pcmif::pcm_perl_is_err($ebufp)) {
	print LOG "$PID: Flist conversion failed:\n$f1\n";
	pcmif::pcm_perl_print_ebuf($ebufp);
	clean_exit(1);
}


#
# Call opcode to set status to STARTED.
$out_flistp = pcmif::pcm_perl_op($pcm_ctxp, "PCM_OP_WRITE_FLDS",
				     0, $flistp, $ebufp);


#
# If there is an error, log a message and die.
if (pcmif::pcm_perl_is_err($ebufp)) {
	print LOG "$PID: Failed to update handler object.\n";
	pcmif::pcm_perl_print_ebuf($ebufp);
	pcmif::pin_flist_destroy($flistp);
	pcmif::pin_flist_destroy($out_flistp);
	clean_exit(1);
}


#
# Upon success, destroy the input and return flists.
pcmif::pin_flist_destroy($flistp);
pcmif::pin_flist_destroy($out_flistp);


#
# Perform housekeeping tasks if the -d commandline option was used.
if (defined $opt_d) {
	$dead_poid = $opt_d;
	print LOG "$PID: Previously started handler associated with "
			. "$dead_poid has died.\n";

	#
	# Update the handler status of that handler's object to DEAD.
	$T_time = pcmif::pin_perl_time();
	$f1 = << "END"
	0 PIN_FLD_POID				     POID [0] $dead_poid
	0 PIN_FLD_END_T				   TSTAMP [0] ($T_time)
	0 PIN_FLD_STATUS			     ENUM [0] $DEAD_STATUS
END
;


	#
	# Convert the flist string into an actual FList
	$flistp = pcmif::pin_perl_str_to_flist($f1, $db_no, $ebufp);
	if (pcmif::pcm_perl_is_err($ebufp)) {
		print LOG "$PID: Flist conversion failed:\n$f1\n";
		pcmif::pcm_perl_print_ebuf($ebufp);
		clean_exit(1);
	}


	#
	# Call the opcode PCM_OP_WRITE_FLDS to update status.
	$out_flistp = pcmif::pcm_perl_op($pcm_ctxp,
			"PCM_OP_WRITE_FLDS", 0, $flistp, $ebufp);

	#
	# If there is an error, print a message and die.
	if (pcmif::pcm_perl_is_err($ebufp)) {
		print LOG "$PID: PCM_OP_WRITE_FLDS failed.\n";
		pcmif::pcm_perl_print_ebuf($ebufp);
		$out = pcmif::pin_perl_flist_to_str($out_flistp, $ebufp);
		clean_exit(1);
	}

	#
	# Destroy the input and return flists.
	pcmif::pin_flist_destroy($flistp);
	pcmif::pin_flist_destroy($out_flistp);
}


#
# Find input file associated with the handler.
#

#
# Get the list of files in the staging directory; skip all beginning with '.'
opendir STAGING_DIR, "$STAGING" or die "$PID: Cannot open directory $STAGING";
@allfiles = grep !/^$STAGING\/\./, map "$STAGING/$_", readdir(STAGING_DIR);
closedir(STAGING_DIR);

#
# Ensure the user is not passing the directory path name
# within the file type.
$FILETYPE = basename ($FILETYPE);

#
# Find files matching specified pattern in the staging dir.
#$FILETYPE =~ s/\./\\\./g;
#$FILETYPE =~ s/\*/\.*/g;
@file_type = grep /^$STAGING/, @allfiles;
$numelements = @file_type;
if ($numelements <= 0) {
	print LOG "$PID: No files to process, exiting.\n";
	&HandlerDie($NO_FILE_TYPE, $current_poid);
}


#
# Sort matching files based on creation date.
foreach $file(@file_type){
	$age{$file} = -M$file;
}
@sorted_allfiles = sort byage @file_type;

#
# Reformat directory path name based on operating system type.
if ($pinUELDir =~ /\\/) {
	$pinUELDir =~ s/\\/\//g;
}

#
# Which operating system are we on?
if ($^O =~/win/i) {
	$pinUELDir =~ s/\//\\/g;
}

#
# Prepare input files for processing.
$moved_a_file = 0; # Set to 1 when a file is successfully moved.
&buildFilePatternTemplateNameHash ;
foreach $file(@sorted_allfiles) {
	# Uncompress file if necessary,
	# reset variable to uncompressed file name.
	if ($file =~ /.Z$/) {
		# foo.Z -> foo
		system "uncompress $file";
		$file =~ s/\.Z$//;
	}
	if ($file =~ /.gz$/) {
		# foo.gz -> foo
		system "gunzip $file";
		$file =~ s/\.gz$//;
	}
	
	#
	# Move file from the staging directory to the processing directory.
	my $lock_File = $PROCESSING . "/" . basename($file) . ".lock";
	if( ! -e $lock_File) {
		open(LOCK,">$lock_File");
		if (flock(LOCK,LOCK_EX | LOCK_NB)) {
			$retval = &callTheMoveToProcessing($file);
		
			if (!$retval) {
				# The directory does not exist or some other error.
				&HandlerDie($FAIL_TO_MOVE_FILE, $current_poid);
			} elsif ($retval == -1) {
				#
				# If the move failed on a 'file not found' error, it means
				# another parallel handler took that file.  This handler
				# will try to get another file.
				next;
			}

			$moved_a_file = 1;
			if ($DEBUG) {
	                        $localtime = localtime();
				print LOG "$PID: File $file moved to the "
					. "processing directory at $localtime.\n";
			}
		} else {
			if ($DEBUG) {
				print LOG "$PID: $lock_file already locked, moving to next file\n";
			}
			close LOCK;
			next;
		}
	} else {
		if ($DEBUG) {
			print LOG "$PID: File already processed by another batch handler. \n";
		}
		next;
	}

	#
	# Check to see if the batch executable exists.
	if (! -e $pinUEL) {
		print LOG "$PID: Executable for batch application does "
			. "not exist\n";
		&HandlerDie($NO_UEL_EXEC, $current_poid);
	}

	#
	# Start the batch application.
	#

	#
	# Use the base filename.
	$basefile = basename ($file);

	$template = &getTemplateNamefromFileName ($basefile) ;
	if ($template eq "") {
		print LOG "$PID: File $basefile doesn't have a matching template, skipping...\n" ;
		next ;
	}
	# If running under MSWindows...
	if ($^O =~ /win/i) {
		require Win32::Process;
		$cmd = $ENV{"COMSPEC"};
		$args = "$cmd /c \"cd $pinUELDir && $cmd /c "
			. basename($pinUEL) . " -t " . $template
			. " " . $basefile . "\"";
		my $process;
		Win32::Process::Create($process,
			$cmd,
			$args,
			0,
			DETACHED_PROCESS,
			'.') || die "$$: Unable to start batch application.";

		# Record PID of batch application in the database.
		&UpdatePIDBatchApplication(0, $current_poid);

		# Wait for the batch application to finish.
		$process->Wait(INFINITE);

		# Get the exit code and convert to a signed number.
		$process->GetExitCode($exitcode);
		my ($uelstatus) = &convertUnsignedToSignedInt($exitcode);
	}

	#
	# Else if running under some other operating system like Unix...
	else {
		$uelCmd = basename($pinUEL) . " -t "
			  . $template . " " . $basefile;
		my $uelpid;
		if (!defined($uelpid = fork())) {
			die "$$: Cannot start batch application: $!";
		} elsif ($uelpid == 0) {
			$Command = "cd $pinUELDir; $uelCmd";
			exec($Command);
			die "$$: Cannot execute batch application: $!";
		} else {
			# Record PID of batch application in the database.
			&UpdatePIDBatchApplication($uelpid, $current_poid);

			# Wait for the batch application to finish.
			waitpid($uelpid,0);

			# Get the exit code and convert to a signed number.
			$exitcode = ($? >> $UNIX_SHIFT);
			my ($uelstatus) = &convertUnsignedToSignedInt($exitcode);
		}
	}


	#
	# Log a debugging message in the handler log file.
	$localtime = localtime();
	if ($DEBUG) {
		print LOG "$PID: The batch application returned $uelstatus at $localtime.\n";
	}
	#
	# Remove the lock file 
	#
	close(LOCK);
	unlink $lock_File;


	#
	# Move files based on the return status.
	#

	# Form full pathname of file to be moved.
	$procfile = $PROCESSING . "/" . $basefile;
        $errXmlBase = $basefile . "_lerr.xml";

	$localtime = localtime();
	if ($uelstatus == $NO_ERROR) {
		if ($DEBUG) {
			print LOG "$PID: File ". basename ($procfile)." "
				. "processed successfully by the "
				. "batch application at $localtime.\n";
		}
		&callTheMoveToArchive($procfile);
                &deleteProcessingXMLFiles($basefile);
		&HandlerDie($COMPLETED_NO_ERROR, $current_poid);
	}

	elsif ($uelstatus == $FILE_CHECK_ERROR) {
		print LOG "$PID: File ". basename ($procfile)." was rejected "
			. "by the batch application at $localtime.\n";
		&callTheMoveToReject($procfile);
		&callTheCopyToReject($errXmlBase);
                &deleteProcessingXMLFiles($basefile);
		&HandlerDie($REJECTED, $current_poid);
	}

	elsif ($uelstatus == $FIELD_PARSE_ERROR
		|| $uelstatus == $ACCT_FORMAT_ERROR
		|| $uelstatus == $LOAD_FORMAT_ERROR
		|| $uelstatus == $PREV_PARSE_ERROR
		|| $uelstatus == $TOO_MANY_LOAD_ERROR
		|| $uelstatus == $ACCT_OPCODE_ERROR
		|| $uelstatus == $LOAD_OPCODE_ERROR) {
		if ($DEBUG) {
			print LOG "$PID: File ". basename ($procfile)." was "
				. "processed by the batch application at "
				. "$localtime with errors.\n";
		}
		&callTheMoveToReject($procfile);
		&callTheCopyToReject($errXmlBase);
                &deleteProcessingXMLFiles($basefile);
		&HandlerDie($WITH_ERROR, $current_poid);
	}

	elsif ($uelstatus == $MEMORY_ERROR
		|| $uelstatus == $DISK_SPACE_ERROR
		|| $uelstatus == $TEMPLATE_ERROR
		|| $uelstatus == $COMMAND_LINE_ARG_ERROR
		|| $uelstatus == $FILE_NOT_FOUND_ERROR
		|| $uelstatus == $BAD_INF_CONNECTION) {
		print LOG "$PID: The file ". basename ($procfile)." was "
			. "not processed by the batch application at "
			. "$localtime.\n";
		&callTheMoveToStaging($procfile);
                &deleteProcessingXMLFiles($basefile);
		&HandlerDie($PILOT_ERROR, $current_poid);
	}

	else {
		print LOG "$PID: Failed to start the batch application "
			. "at $localtime\n";
		print LOG "$PID: Unexpected uel exit code: $uelstatus.\n";
		&callTheMoveToReject($procfile);
		&callTheCopyToReject($errXmlBase);
                &deleteProcessingXMLFiles($basefile);
		&HandlerDie($FAIL_TO_START_UEL, $current_poid);
	}

	#
	# Break the foreach loop
	last;
}

# Make sure a file was moved.
if ($moved_a_file != 1)
{
	&HandlerDie($FAIL_TO_MOVE_FILE, $current_poid);
}

#
# This point should not be reached...
clean_exit(0);


#
#------------------------------------------------------------------
# callTheMoveToProcessing - move the file from the staging directory to
# the processing directory.
#
# Parameter: the file name in the staging directory
#
# Returns: file not found or move failed = -1, any other failure = 0, success = 1
#
sub callTheMoveToProcessing {
	local($processingFile) = @_;
	if (! -e $processingFile) {
		print LOG "$PID: $processingFile does not exist.\n";
		return (-1);
	}
	if (! -d $PROCESSING) {
		print LOG "$PID: Processing directory $PROCESSING does "
			. "not exist.\n";
		return (0);
	}
	$ret = move "$processingFile", "$PROCESSING/$_";
	if ($ret != 1) {
		print LOG "$PID: Failed to move $processingFile to "
			. "$PROCESSING.\n";
		return (-1); # Could have been moved by another handler
			     # since these ops are non-atomic;
			     # this would not occur with other move subroutines
			     # since they have a known file in use.
	}
	if ($DEBUG) {
		print LOG "$PID: Moved $processingFile to $PROCESSING.\n";
	}
	return (1);
}


#
#------------------------------------------------------------------
# callTheMoveToArchive - move the file from the processing directory to
# the archive directory.
#
# Parameter: the file name in the processing directory
#
# Returns: failure = 0 and success = 1
#
sub callTheMoveToArchive {
	local($archiveFile) = @_;
	if (! -e $archiveFile) {
		print LOG "$PID: $archiveFile does not exist.\n";
		return (0);
	}
	if (! -d $ARCHIVE) {
		if (!createPath($ARCHIVE, 0, 0755)) {
			print LOG "$PID: Failed to create archive directory "
				. "$ARCHIVE: $!\n";
			return (0);
		}
	}
	$ret = move "$archiveFile", "$ARCHIVE/$_";
	if ($ret != 1){
		print LOG "$PID: Failed to move $archiveFile to $ARCHIVE.\n";
		return (0);
	}
	$localtime = localtime();
	if ($DEBUG){
		print LOG "$PID: Moved $archiveFile to $ARCHIVE at $localtime.\n";
	}
	return (1);
}


#
#------------------------------------------------------------------
# callTheMoveToReject - move the file from the processing directory to
# the reject directory.
#
# Parameter: the file name in the processing directory
#
# Returns: failure = 0 and success = 1
#
sub callTheMoveToReject {
	local($rejectFile) = @_;
	if (! -e $rejectFile) {
		print LOG "$PID: $rejectFile does not exist.\n";
		return (0);
	}
	if (! -d $REJECT) {
		if (!createPath($REJECT, 0, 0755)) {
			print LOG "$PID: Failed to create reject directory "
				. "$REJECT: $!\n";
			return (0);
		}
	}
	$ret = move "$rejectFile", "$REJECT/$_";
	if ($ret != 1) {
		print LOG "$PID: Failed to move $rejectFile to $REJECT.\n";
		return (0);
	}
	$localtime = localtime();
	if ($DEBUG) {
		print LOG "$PID: Moved $rejectFile to $REJECT at $localtime.\n";
	}
	return (1);
}

sub callTheCopyToReject {
	local($rejectBase) = @_;
	if (! defined($INFRANET_UEL_LOAD_ERROR_FILE_LOCATION)) {
		print LOG "$PID: Cannot copy $rejectBase, UELHandler_config.values does not specify INFRANET_UEL_LOAD_ERROR_FILE_LOCATION\n";
		return (0);
	}
	if (! -d $INFRANET_UEL_LOAD_ERROR_FILE_LOCATION) {
		print LOG "$PID: ERROR, \$INFRANET_UEL_LOAD_ERROR_FILE_LOCATION=$INFRANET_UEL_LOAD_ERROR_FILE_LOCATION does not exist.\n";
		return (0);
	}
	$rejectFile="${INFRANET_UEL_LOAD_ERROR_FILE_LOCATION}/$rejectBase";
	if (! -e $rejectFile) {
		print LOG "$PID: $rejectFile does not exist.\n";
		return (0);
	}
	if (! -d $REJECT) {
		if (!createPath($REJECT, 0, 0755)) {
			print LOG "$PID: Failed to create reject directory "
				. "$REJECT: $!\n";
			return (0);
		}
	}
	$ret = copy "$rejectFile", "$REJECT";
	if ($ret != 1) {
		print LOG "$PID: Failed to copy $rejectFile to $REJECT.\n";
		return (0);
	}
	$localtime = localtime();
	if ($DEBUG) {
		print LOG "$PID: Copied $rejectFile to $REJECT at $localtime.\n";
	}
	return (1);
}

#
#------------------------------------------------------------------
# callTheMoveToStaging - move the file from the processing directory to
# the staging directory.
#
# Parameter: the file name in the processing directory
#
# Returns: failure = 0 and success = 1
#
sub callTheMoveToStaging {
	local($stagingFile) = @_;
	if (! -e $stagingFile) {
		print LOG "$PID: $stagingFile does not exist.\n";
		return (0);
	}
	if (! -d $STAGING) {
		print LOG "$PID: $STAGING does not exist.\n";
		return (0);
	}
	if (! -d $PROCESSING) {
		print LOG "$PID: $PROCESSING does not exist.\n";
		return (0);
	}
	if (!copy ($stagingFile, "$STAGING/$_")) {
		print LOG "$PID: Failed to copy $stagingFile to "
			. "the staging directory: $!\n";
		&HandlerDie($PILOT_ERROR, $current_poid);
	}
	if (!unlink($stagingFile, "$PROCESSING/$_")) {
		print LOG "$PID: Failed to unlink $stagingFile from "
			. "the processing directory: $!\n";
		&HandlerDie($PILOT_ERROR, $current_poid);
	}
	$localtime = localtime();
	if ($DEBUG) {
		print LOG "$PID: Moved $stagingFile to $STAGING at $localtime.\n";
	}
	return (1);
}

#
#
#------------------------------------------------------------------
# createPath - create the directory specified by the path arg, including
#	       all intermediate directories.
#
# Parameters:
#	$paths   -- either a path string or ref to list of paths
#	$verbose -- optional print "mkdir $path" for each directory created
#	$mode    -- optional permissions, defaults to 0777
#
# Returns: failure = 0 and success = 1
#
sub createPath {
	my($paths, $verbose, $mode) = @_;
	local($")="/";
	$mode = 0777 unless defined($mode);
	$paths = [$paths] unless ref $paths;
	my(@created,$path);
	foreach $path (@$paths) {
		next if -d $path;
		# Logic wants Unix paths, so go with the flow.
		$path = VMS::Filespec::unixify($path) if $Is_VMS;
		my $parent = File::Basename::dirname($path);
		push(@created, createPath($parent, $verbose, $mode))
			unless (-d $parent);
		print "mkdir $path\n" if $verbose;
		mkdir($path,$mode) || return 0;
		push(@created, $path);
	}
	@created;
}

#
#------------------------------------------------------------------
# HandlerDie - update the status object and exit.
#
sub HandlerDie() {
	$T_time = pcmif::pin_perl_time();
	local($status, $POID) = @_;

	# Create the flist to update the status to the passed arg.
	$f1 = << "END"
	0 PIN_FLD_POID				     POID [0] $POID
	0 PIN_FLD_END_T				   TSTAMP [0] ($T_time)
	0 PIN_FLD_STATUS			     ENUM [0] $status
END
;

	# Convert the flist string into the input flist
	$flistp = pcmif::pin_perl_str_to_flist($f1, $db_no, $ebufp);
	if (pcmif::pcm_perl_is_err($ebufp)) {
		print LOG "$PID: Flist conversion failed:\n$f1\n";
		pcmif::pcm_perl_print_ebuf($ebufp);
		clean_exit(1);
	}

	# Call opcode to set the status.
	$out_flistp = pcmif::pcm_perl_op($pcm_ctxp,
			"PCM_OP_WRITE_FLDS", 0, $flistp, $ebufp);

	# If there is an error, log a message and terminate.
	if (pcmif::pcm_perl_is_err($ebufp)) {
		print LOG "$PID: Failed to update handler object.\n";
		pcmif::pcm_perl_print_ebuf($ebufp);
		$out = pcmif::pin_perl_flist_to_str($out_flistp, $ebufp);
		pcmif::pin_flist_destroy($flistp);
		pcmif::pin_flist_destroy($out_flistp);
		clean_exit(1);
	}

	# These are the UELRelHandler exit codes.
	if ($status == $COMPLETED_NO_ERROR) {
		$exitval = 0;
	}
	elsif ($status == $WITH_ERROR) {
		$exitval = 2;
	}
	elsif ($status == $REJECTED) {
		$exitval = 3;
	}
	elsif ($status == $PILOT_ERROR) {
		$exitval = 4;
	}
	elsif ($status == $NO_FILE_TYPE) {
		$exitval = 5;
	}
	elsif ($status == $FAIL_TO_MOVE_FILE) {
		$exitval = 6;
	}
	elsif ($status == $NO_UEL_EXEC) {
		$exitval = 7;
	}

	# Destroy the input and return flists.
	pcmif::pin_flist_destroy($flistp);
	pcmif::pin_flist_destroy($out_flistp);

	# Close the connection to the CM.
	pcmif::pcm_context_close($pcm_ctxp, 0, $ebufp);
	if (pcmif::pcm_perl_is_err($ebufp)) {
		print LOG "$PID: Error while closing CM connection.\n";
		pcmif::pcm_perl_print_ebuf($ebufp);
		clean_exit($exitval);
	}

	# Terminate this handler application.
	if ($DEBUG) {
		print LOG "$PID: Handler completed operations, exiting...\n";
	}
	clean_exit($exitval);
}


#
#------------------------------------------------------------------
# UpdatePIDBatchApplication - store the batch application PID in the database.
#
sub UpdatePIDBatchApplication() {
	$T_time = pcmif::pin_perl_time();
	local($PID, $POID) = @_;

	# Create the flist to store the PID value.
	$f1 = << "END"
	0 PIN_FLD_POID				     POID [0] $POID
	0 PIN_FLD_BATCH_HANDLER_INFO		SUBSTRUCT [0]
	1   PIN_FLD_BATCH_APPLICATION_PID	      INT [0] $PID
END
;

	# Convert the flist string into the input flist.
	$flistp = pcmif::pin_perl_str_to_flist($f1, $db_no, $ebufp);
	if (pcmif::pcm_perl_is_err($ebufp)) {
		print LOG "$PID: Flist conversion failed:\n$f1\n";
		pcmif::pcm_perl_print_ebuf($ebufp);
		clean_exit(1);
	}

	# Call opcode to set the PID.
	$out_flistp = pcmif::pcm_perl_op($pcm_ctxp,
			"PCM_OP_WRITE_FLDS", 0, $flistp, $ebufp);

	# If there is an error, log a message and terminate.
	if (pcmif::pcm_perl_is_err($ebufp)) {
		print LOG "$PID: PCM_OP_WRITE_FLDS failed.\n";
		pcmif::pcm_perl_print_ebuf($ebufp);
		$out = pcmif::pin_perl_flist_to_str($out_flistp, $ebufp);
		pcmif::pin_flist_destroy($flistp);
		pcmif::pin_flist_destroy($out_flistp);
		clean_exit(1);
	}

	# Destroy the input and return flists.
	pcmif::pin_flist_destroy($flistp);
	pcmif::pin_flist_destroy($out_flistp);

	return(1);
}

#
#------------------------------------------------------------------
# Usage: Print usage message and exit.
sub usage {
	print STDERR "Usage: $0 -p <hander_poid> { -d <dead_handler_poid> }\n";
	clean_exit(-1);
}

#
#------------------------------------------------------------------
# We don't want to leave any open files laying around,
# so close them here.
#
sub clean_exit {
        local($exitcode) = @_;
        close(LOG); # doesn't matter if it was opened or not.
        exit($exitcode);
}

#
#------------------------------------------------------------------
# Find the oldest file.
#
sub byage {
	$age{$b}<=>$age{$a}
}

#
#------------------------------------------------------------------
# Convert the unsigned int to signed value.
#
sub convertUnsignedToSignedInt {
	local($exitcode) = @_;

	if ($^O =~/win/i) {
		# Number of bits in NT other than the sign bit
		$valueBitLength = 31;
		# Decimal for binary 1 followed by 31 zeroes
		$decrementValue = 4294967296;
	}
	else {
		# Number of bits in Unix other than the sign bit
		$valueBitLength = 7;
		# Decimal for binary 1 followed by 7 zeroes
		$decrementValue = 256;
	}

	$lastBit = $exitcode >> $valueBitLength;
	if ($lastBit == 1) {
		$uelstatus = ($exitcode - $decrementValue);
	}
	else {
		$uelstatus = $exitcode;
	}
	return ($uelstatus);
}

sub buildFilePatternTemplateNameHash {
	%filenametemplatenamehash = () ;
	my $searchQuery="select X from /config/gel/template where F1.type = V1 " ;
	my $templateSearchString = <<"END"
		0 PIN_FLD_POID				POID [0] $DB_NO /search -1 0
		0 PIN_FLD_FLAGS				INT [0] 0
		0 PIN_FLD_TEMPLATE			STR [0] "$searchQuery"
		0 PIN_FLD_ARGS				ARRAY [1] allocated 1, used 1
		1		PIN_FLD_POID		POID [0] $DB_NO /config/gel/template -1 0
		0 PIN_FLD_RESULTS			ARRAY [*] allocated 2, used 2
		1	PIN_FLD_NAME			STR [0] ""
		1	PIN_FLD_GEL_TEMPLATE_INFO	SUBSTRUCT [0] allocated 1, used 1
		2	PIN_FLD_FORMAT_STR		STR [0] ""
END
;
	my $template_search_flistp = pcmif::pin_perl_str_to_flist($templateSearchString, $db_no, $ebufp);
	if (pcmif::pcm_perl_is_err($ebufp)) {
		print LOG "$PID: Flist conversion failed:\n$templateSearchString\n";
		pcmif::pcm_perl_print_ebuf($ebufp);
		clean_exit(1);
	}
	# Call opcode to search for the give file pattern
	my $template_result_flistp = pcmif::pcm_perl_op($pcm_ctxp, "PCM_OP_SEARCH",
				     0, $template_search_flistp, $ebufp);
	# If there is an error, log a message and die.
	if (pcmif::pcm_perl_is_err($ebufp)) {
		print LOG "$PID: Failed to retrieve filename pattern - gel template mapping from /config/gel/template\n" ;
		pcmif::pcm_perl_print_ebuf($ebufp);
		pcmif::pin_flist_destroy($template_search_flistp);
		pcmif::pin_flist_destroy($template_result_flistp);
		clean_exit(1);
	}

	my $templateResultString = pcmif::pin_perl_flist_to_str($template_result_flistp, $ebufp);
	if (pcmif::pcm_perl_is_err($ebufp)) {
		print LOG "$PID: Flist to string conversion failed:\n$template_result_flistp\n";
		pcmif::pcm_perl_print_ebuf($ebufp);
		clean_exit(1);
	}
	
	my @lines = split /\n/, $templateResultString ;
	my $templateName = "" ;
	my $filenamePattern = "" ;
	foreach my $line (@lines) {
        	if ($line =~ /PIN_FLD_RESULTS/) {
			if ($templateName ne "" && $filenamePattern ne "") {
				# Insert into map
				$filenametemplatenamehash {$filenamePattern} = $templateName ;
				$templateName = "" ;
				$filenamePattern = "" ;
			}
			else {
				next ;
			}
        	}
		elsif ($line =~ /PIN_FLD_NAME/) {
			$templateName = (split / / , $line) [-1];
		}
		elsif ($line =~ /PIN_FLD_FORMAT_STR/) {
			$filenamePattern = (split / / , $line) [-1];
		}
		else {
			next ;
		}
	}
	if ($templateName ne "" && $filenamePattern ne "") {
		$filenametemplatenamehash {$filenamePattern} = $templateName ;
	}
	
	if ($DEBUG) {
		my @hash_keys = keys %filenametemplatenamehash ;
		foreach my $filePattern (@hash_keys) {
			print LOG "$PID: Key : $filePattern and Value : $filenametemplatenamehash{$filePattern}\n" ;
		}
	}
}

sub getTemplateNamefromFileName {
	@parameters = @_ ;
	my $filename = $parameters[0] ;
	my $templateName = "" ;
	my @hash_keys = keys %filenametemplatenamehash ;
	foreach my $filePattern (@hash_keys) {
		my $re = $filePattern ;
		$filePattern =~ s/^"(.*)"$/$1/;
		if ($filename =~ /$filePattern/){
			$templateName = $filenametemplatenamehash {$re} ;
			last ;
		}
	}
	return $templateName ;
}

# The function parses the UEL Infranet.properties to get processing file locations
sub parseInfranetProperties {

  open(INF,"<${pinUELDir}/Infranet.properties") or die "Cannot open file ${pinUELDir}/Infranet.properties ";

  while(<INF>) {
     if(/^infranet.uel.cache_file_location=(\S+)/) {
       $INFRANET_UEL_CACHE_FILE_LOCATION=$1;
     }
     if(/^infranet.uel.filter_log_file_location=(\S+)/) {
      $INFRANET_UEL_FILTER_LOG_FILE_LOCATION=$1;
     }
     if(/^infranet.uel.load_error_file_location=(\S+)/) {
      $INFRANET_UEL_LOAD_ERROR_FILE_LOCATION=$1;
     }
     if(/^infranet.uel.load_success_file_location=(\S+)/) {
      $INFRANET_UEL_LOAD_SUCCESS_FILE_LOCATION=$1;
     }
  }

  close(INF);
  
  if (! defined($INFRANET_UEL_CACHE_FILE_LOCATION)) {
    print LOG "ERROR: UELHandler_config.values does not specify INFRANET_UEL_CACHE_FILE_LOCATION\n";
    clean_exit(1);
  }
  if (! defined($INFRANET_UEL_FILTER_LOG_FILE_LOCATION)) {
    print LOG "ERROR: UELHandler_config.values does not specify INFRANET_UEL_FILTER_LOG_FILE_LOCATION\n";
    clean_exit(1);
  }
  if (! defined($INFRANET_UEL_LOAD_ERROR_FILE_LOCATION)) {
    print LOG "ERROR: UELHandler_config.values does not specify INFRANET_UEL_LOAD_ERROR_FILE_LOCATION\n";
    clean_exit(1);
  }
  if (! defined($INFRANET_UEL_LOAD_SUCCESS_FILE_LOCATION)) {
    print LOG "ERROR: UELHandler_config.values does not specify INFRANET_UEL_LOAD_SUCCESS_FILE_LOCATION\n";
    clean_exit(1);
  }
  
}

# The function deletes all the processing XML files once the UEL input file is processed
# either successfully or could have been rejected
sub deleteProcessingXMLFiles {

  local($baseFilename) = @_;
  
  if( ! &deleteFile($INFRANET_UEL_LOAD_SUCCESS_FILE_LOCATION, $baseFilename . "_lsucc.xml")) {
     return(0);
  }
  
  if( ! &deleteFile($INFRANET_UEL_LOAD_ERROR_FILE_LOCATION, $baseFilename . "_lerr.xml")) {
     return(0);
  }

  if( ! &deleteFile($INFRANET_UEL_FILTER_LOG_FILE_LOCATION, $baseFilename . "_filtered.xml")) {
     return(0);
  }

  if( ! &deleteFile($INFRANET_UEL_CACHE_FILE_LOCATION, $baseFilename . "_cache.xml")) {
     return(0);
  }
  
  return(1);

}

# This is general function to delete a file from the processing directory
sub deleteFile {

   local($processingDir, $file) = @_;

   if (! -d $processingDir) {
        print LOG "$PID: ERROR : $processingDir does not exist.\n";
        return (0);
   }

  $processingFileName = "$processingDir/$file";

  if ( -e $processingFileName ) {
      if (!unlink($processingFileName)) {
        print LOG "$PID: Failed to delete $file in the directory $processingDir.\n";
        return (0);
      }

      $localtime = localtime();
      if ($DEBUG) {
        print LOG "$PID: Deleted $file from the directory $processingDir at $localtime.\n";
      }
  }

  return (1);
}

