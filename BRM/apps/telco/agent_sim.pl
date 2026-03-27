#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
###########
#
# @(#)$Id: agent_sim.pl /cgbubrm_mainbrm.portalbase/1 2018/02/26 22:37:45 anirbisw Exp $
#
# Copyright (c) 2001, 2018, Oracle and/or its affiliates. All rights reserved.
#
# This material is the confidential property of Oracle Corporation or its 
# licensors and may be used, reproduced, stored or transmitted only in 
# accordance with a valid Oracle license or sublicense agreement.
#
###########

# Simulator for Infranet agent, for testing dm_provision.  When running
# this simulator on Windows, run dm_provision with one back-end, because
# on Windows this simulator handles one connection at a time.  When running
# this simulator on Unix, you can have multiple back-ends in dm_provision,
# because it forks for each connection.
#
# Parameters:
#    -p <port>
#        Port number on which the simulator listens.  Default is 20000.
#    -r <response code>
#        A decimal number (1 or 2 digits) that is the response code returned
#        for each request.   Default is 0 (ack).
#    -s <status>
#        Service status to be sent back in the Provisioning response (confirmed mode).
#    -f <status flags>
#        Status flag to be sent back in the Provisioning response (confirmed mode).
#    -t <feature status>
#        Feature status to be sent back in the Provisioning response (confirmed mode).
#    -m <status message>
#        Status message to be sent back in the Provisioning response (confirmed mode). 
#    -d <delay>
#        Number of seconds to delay before sending a response.  Default is zero.
#        This option is useful for testing the timeout in dm_provision.
#    -i
#        User interactive mode for getting the Provisioning response from the user
#        and sending back the Provisioning response in case of confirmed mode.

use strict;
use Socket;
use Getopt::Std;
require "./PerlParser.pm";


use vars qw($port $opt_p $rsp $opt_r $delay $opt_d $opt_s $opt_f $opt_t $opt_m $opt_i);

# Variables declared to handle confirmed mode response.
my $currentTag = ();
my $flag = "START_TAG";
my $status = 0;
my $status_flags = 0;
my $status_msg = "Provisioning is successful";
my $param_index = 0;
my $name = "";
my $action = "";
my $param_name = "";
my $param_action = "";
my $param_value = "";
my $add_ext_info_flag = 0;
my $feature_status = 0;
my $prov_status = "";
my $svc_order_info = 0;
my $in_param_tag = 0;
my $poid = "";
my $flist_str = "";
my $interactive_mode = 0;

########################
# Main:

getopts 'p:r:d:s:f:t:m:i' and (@ARGV == 0) or 
	die
		"Usage: $0 [-p <port>] [-r <response code>] ",
		"[-s <status>] [-f <status_flags>] ",
		"[-t <feature_status>] [-m <status_msg>] ",
		"[-d <delay response>] [-i] User interactive mode\n";

# port:
!$opt_p or $opt_p !~ /\D/ or
	die "$0: invalid port ($opt_p).\n";
$port = $opt_p || 20000;

# response code:
!$opt_r or (length($opt_r) <= 2 and $opt_r !~ /\D/) or
	die "$0: invalid response code ($opt_r).\n";
$rsp = $opt_r || "0";

# status:
!$opt_s or $opt_s !~ /\D/ or
	die "$0: invalid status ($opt_s).\n";
$status = $opt_s || 0;

# status_flags:
!$opt_f or $opt_f !~ /\D/ or
	die "$0: invalid status_flags ($opt_f).\n";
$status_flags = $opt_f || 0;

# feature_status:
!$opt_t or $opt_t !~ /\D/ or
	die "$0: invalid feature_status ($opt_t).\n";
$feature_status = $opt_t || 0;

# status_msg:
$status_msg = $opt_m || "";

# delay:
!$opt_d or $opt_d !~ /\D/ or
	die "$0: invalid delay ($opt_d).\n";
$delay = $opt_d || 0;

# interactive_mode:
$interactive_mode = $opt_i || 0;

# Setup signal handler that collects zombie processes.
sub Reaper {
	wait;
	$SIG{CHLD} = \&Reaper; # Some OSs require re-installing handler.
}
$SIG{CHLD} = \&Reaper;

# Set up socket and listen on port.
my $proto = getprotobyname 'tcp';
socket SERVER, PF_INET, SOCK_STREAM, $proto or
	die "$0: error creating socket: $!\n";
setsockopt SERVER, SOL_SOCKET, SO_REUSEADDR, pack("l", 1) or
	die "$0: error in setsockopt: $!\n";
bind SERVER, sockaddr_in($port, INADDR_ANY) or 
	die "$0: error binding socket: $!\n";
listen SERVER, SOMAXCONN;

print "Listening on port $port\n";

while (1) {
	print "Awaiting connection...\n";
	my $paddr = accept CLIENT, SERVER;
	my ($cl_port, $iaddr) = sockaddr_in $paddr;
	my $name = gethostbyaddr $iaddr, AF_INET;
	print
		"Connection opened by $name [",
		inet_ntoa($iaddr),
		"], port $port\n";
	if ($^O =~ /win/i) {
		# Windows.  No fork.
		&HandleConnection;
	}
	else {
		# Not windows.  Assume we can fork.
		FORK: {
			my $pid = fork;
			if ($pid) {
				# Parent process.
				print "Forked process ($pid).\n";
			}
			elsif (defined $pid) {
				# Child process.
				&HandleConnection;
				exit 0;
			}
			elsif ($! =~ /No more process/) {
				# Recoverable fork error.
				print
					"Transient error forking process.\n",
					"Waiting 5 seconds and retrying...";
				sleep 5;
				redo FORK;
			}
			else {
				die "Error forking process.\n";
			}
		}
	}
}

sub HandleConnection
{
	my $client_err = 0;
	until ($client_err) {
		$client_err = &HandleReq;
		# Keep connection alive for more requests.
	}
	close CLIENT;
	print "Closed connection to client\n",
}


print "$0: exiting.\n";

exit 0;

sub HandleReq
 {
	my ($length, $code, $contents, $out_buf, $rsp_data,$x,$dir,$file_path,$pos_start,$pos_stop,$str,$status,$cmd,$file_dir);
	print "++++++++++++++++++++++++++++++++++\n";
	# Length: 6 bytes
	$length = &ReadFromClient(6);
	defined $length or return 1;
	print "Request: Length: $length  ";
	$length >= 2 or
		print "\nInvalid req. length.\n" and
		return 1;

	# Request code: 2 bytes
	$code = &ReadFromClient(2);
	defined $code or return 1;
	print "Code: $code\n";

	# Additional data:
	$length -= 2;
	if ($length) {
		$contents = &ReadFromClient($length);
		defined $contents or return 1;
		print "Data:\n$contents\n";

	##     File name
	$x="SvcOrder_";

	#Added to get the unique id for event object to be appended to XML file name

	$pos_start=index($contents,"<EVENT_OBJ>") ;
	if($pos_start =~ -1){
		print "Warning : No tag <EVENT_OBJ> found in i/p xml." ;
	}
	$pos_stop=index($contents,"</EVENT_OBJ>") ;
	if($pos_stop =~ -1){
		print "Warning : No tag </EVENT_OBJ> found in i/p xml." ;
	}


	$str=substr($contents,$pos_start,($pos_stop - $pos_start)) ;
	if(length($str) =~ 0) {
                print "Warning : Not able to get required values" ;
        }	

	$pos_start=index($str," ",index($str," ")+1) ;
	if($pos_start =~ -1) {
                print "Warning : Not able to get required position" ;
        }

	$str=substr($str,$pos_start +1 ,(rindex($str," ") - ($pos_start+1))) ;
	if(length($str) =~ 0) {
                print "Warning : Not able to get required values" ;
        }

	#append unique id for event object to filename
	substr($x,length($x),0)=$str ;
	#append extension to file name
	substr($x,length($x),0)=".xml" ;


	##     Directory path
	$dir=$ENV{'PIN_HOME'} ;
	if(length($dir) == 0) { 
		print "Warning : No PIN_HOME set, creating xml file in current folder..." ;
		$file_path=$x;
	}
	else {
		# default directory for XML files is $PIN_HOME/apps/telco/service_orders

		$file_dir=$dir.'/apps/telco/service_orders' ;
		
		# checking if the folder $PIN_HOME/apps/telco/service_orders exists

		if (! -d $file_dir)
		{
  			print "Warning : $file_dir does not exist, creating xml file in current folder...\n" ;
			$file_path=$x ;
		}
		else {	
			$file_path=$dir.'/apps/telco/service_orders/'.$x;
		}

	}
	##     Create the file for writing.
	$status=open(F,">$file_path") ;
	if($status =~ 1){
		binmode(F);
		print F $contents;     ##     Write the string to this file
		close(F);
	}
	else {
		print "Error : Not able to create file $x for writing..." ;
	}


	}


	if ($delay) {
		print "Delaying $delay seconds...\n";
		sleep $delay;
	}

	print ("Code->$code, Response code->$rsp\n");

	# Send response:
	if ($code == 0 && $rsp == 0) {

		print "Inside confirmed mode response..\n";
		#=============================================
		# Create the XML parser object
		#=============================================
		my $Parser = XML::PerlParser->new;

		#=============================================
		# Set all the callback handlers we are
		# interested in being notified of.
		#=============================================
		$Parser->setHandlers( Start => \&StartHandler
				 ,End   => \&EndHandler
				 ,Char  => \&CharHandler
				);

		print "Starting xml parser...\n\n";

		#=============================================
		# Parse directly from file.
		#
		# Note:  This is an event driven XML parser.
		# As pieces of the XML document are discovered,
		# different events will be fired.  It is our
		# job to be listening for the events we want
		# to be notified of and then act accordingly.
		#=============================================

		$Parser->parse_xml_file($file_path);

		# Confirmed order.  Response includes
		# flist string if response is ack.
		$rsp_data = $flist_str;
	}
	else {
		$rsp_data = "";
	}
	$length = 2 + length($rsp_data);
	$out_buf = sprintf "%06s%02s", $length, $rsp;
	&SendToClient($out_buf) or return 1;
	(&SendToClient($rsp_data) or return 1) if $rsp_data;
	print "Response: Length: $length,  Code: $rsp\n";
	print "Data:\n$rsp_data\n" if $rsp_data;
	return 0;
 }

sub ReadFromClient
{
	my $nbytes = shift;
	my $buf;
	my $res = recv CLIENT, $buf, $nbytes, 0;
	defined $res or
		print "Error ($!) reading from client\n" and
		return undef;
	my $bytes_read = length($buf);
	$bytes_read == $nbytes or
		print "Read $bytes_read bytes instead of $nbytes\n" and
		return undef;
	return $buf;
}
		
sub SendToClient
{
	my $buf = shift;
	my $res = send CLIENT, $buf, 0;
	defined $res or
		print "Error ($!) sending to client\n" and
		return 0;
	return 1;
}

##########################################################################
# Sub          : StartHandler
# Description  : Handler for XML Start Tags.  Called when an XML start tag
#              :  is found.
#--------------+----------------------------------------------------------
# In           : XML tag name
# In           : An array of attributes, if any, for this Start tag.
#--------------+----------------------------------------------------------
# Returns      : None
##########################################################################
sub StartHandler
{
    $currentTag = shift;
    my @atts = @_;

    $flag = "START_TAG";

    if ($currentTag eq "order") {
	$flist_str = "";
	$param_index = 0;
	$add_ext_info_flag = 0;
    }

    if ($currentTag eq "SERVICE_ORDER_INFO") {
        $svc_order_info = 1;
        $name = "";
        $action = "";
        $poid = "";
    }

    if ($currentTag eq "PARAMS") {
        if ($add_ext_info_flag eq 0) {
            $flist_str = $flist_str."0 PIN_FLD_EXTENDED_INFO SUBSTRUCT [0] allocated 20, used 4\n";
            $add_ext_info_flag = 1;
        }
        $in_param_tag = 1;
        $param_name = "";
        $param_action = "";
        $param_value = "";
    }

}

##########################################################################
# Sub          : CharHandler
# Description  : Handler for XML data.  Called when any text is found
#              :  inside an XML tag set.
#--------------+----------------------------------------------------------
# In           : XML text
#--------------+----------------------------------------------------------
# Returns      : None
##########################################################################
sub CharHandler
{
    my $text = shift;

    return if($flag eq "END_TAG");
    #----------------------------
    # Strip out spaces and remove
    # quotes (") on the borders.
    #----------------------------

    $text =~ s/^\s*"\s*//g;
    $text =~ s/\s*"\s*$//g;

    if ($currentTag eq "EVENT_OBJ") {
        $flist_str = $flist_str."0 PIN_FLD_POID POID [0] ";
        $flist_str = $flist_str.$text;
        $flist_str = $flist_str."\n";

    }
    if ($currentTag eq "NAME") {
        if ($in_param_tag eq 1) {
            $param_name = $text;
        }
        else {
            $name = $text;
       }
    }
    if ($currentTag eq "ACTION") {
        if ($in_param_tag eq 1) {
            $param_action = $text;
        }
        else {
            $action = $text;
        }
    }
    if ($currentTag eq "POID" and $svc_order_info eq 1) {
        $poid = $text;
    }
    if ($currentTag eq "VALUE") {
        $param_value = $text;
    }
}

##########################################################################
# Sub          : EndHandler
# Description  : Handler for XML End Tags.  Called when an XML end tag
#              :  is found.
#--------------+----------------------------------------------------------
# In           : XML tag name
#--------------+----------------------------------------------------------
# Returns      : None
##########################################################################
sub EndHandler
{
    my $endTag = shift;
    $flag = "END_TAG";

    if ($endTag eq "PARAMS") {
        $flist_str = $flist_str."1    PIN_FLD_PARAMS ARRAY [".$param_index."] allocated 20, used 4\n";
        $param_index = $param_index + 1;

        $flist_str = $flist_str."2       PIN_FLD_NAME STR [0] ";
        $flist_str = $flist_str."\"".$param_name."\"";
        $flist_str = $flist_str."\n";

        $flist_str = $flist_str."2       PIN_FLD_ACTION STR [0] ";
        $flist_str = $flist_str."\"".$param_action."\"";
        $flist_str = $flist_str."\n";

        $flist_str = $flist_str."2       PIN_FLD_VALUE STR [0] ";
        $flist_str = $flist_str."\"".$param_value."\"";
        $flist_str = $flist_str."\n";

	if ($interactive_mode eq 1) {
		print ("You are trying to Provision the following service attributes\n\n");
		print ("Name->\"$param_name\"\nAction->\"$param_action\"\nValue->\"$param_value\"\n\n");
		print ("Do you want to provision [Y/N]");
		$prov_status = <STDIN>;
		chop($prov_status);

		if ($prov_status eq "Y" or $prov_status eq "y") { $feature_status = 1 ; }
		if ($prov_status eq "N" or $prov_status eq "n") { $feature_status = 0 ; }
	}

        $flist_str = $flist_str."2       PIN_FLD_STATUS ENUM [0] ";
        $flist_str = $flist_str.$feature_status;
        $flist_str = $flist_str."\n";
    }

    if ($endTag eq "SERVICE_ORDER_INFO") {
        $svc_order_info = 0;
	if ($interactive_mode eq 1) {
		print ("\n\nService order info POID -> \"$poid\"\n\n");
		print ("Service order info Action -> \"$action\"\n\n");
		print ("Service order info Name -> \"$name\"\n\n");
	}
    }

    if ($endTag eq "PARAMS") {
        $in_param_tag = 0;
    }
    if ($endTag eq "order") {

	if ($interactive_mode eq 1) {
		print ("\n\n\nDo you want to activate this main service [Y/N]");
		$prov_status = <STDIN>;
		chop($prov_status);

		if ($prov_status eq "Y" or $prov_status eq "y") { $status = 1 ; }
		if ($prov_status eq "N" or $prov_status eq "n") { $status = 0 ; }
	}

        $flist_str = $flist_str."0 PIN_FLD_STATUS ENUM [0] ";
        $flist_str = $flist_str.$status;
        $flist_str = $flist_str."\n";

	if ($interactive_mode eq 1) {
		print ("\n\nEnter the status flag to be sent back in Provisioning response:");
		$status_flags = <STDIN>;
		chop($status_flags);
	}

        $flist_str = $flist_str."0 PIN_FLD_STATUS_FLAGS INT [0] ";
        $flist_str = $flist_str.$status_flags;
        $flist_str = $flist_str."\n";

	if ($interactive_mode eq 1) {
		print ("\n\nEnter the status message to be sent back in Provisioning response:");
		$status_msg = <STDIN>;
		chop($status_msg);
	}

        $flist_str = $flist_str."0 PIN_FLD_STATUS_MSG STR [0] ";
        $flist_str = $flist_str."\"".$status_msg."\"";
        $flist_str = $flist_str."\n";
    }

}

