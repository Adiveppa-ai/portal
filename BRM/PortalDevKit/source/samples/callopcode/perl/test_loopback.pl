#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#
# Copyright (c) 2000, 2009, Oracle and/or its affiliates. All rights reserved. 
# This material is the confidential property of Oracle Corporation. 
# or its subsidiaries or licensors and may be used, reproduced, stored
# or transmitted only in accordance with a valid Oracle license or 
# sublicense agreement.
#
#######################################################################

# This sample demonstrates how to call PCM_OP_TEST_LOOPBACK 
# opcode. The opcode simply echos back to the caller the flist
# that was passed to it.
#

## Note the pin.conf file (pin.conf on NT) must reside in "." 
## The .pm files are (should be) located in this directory.
## On NT it looks into current directory and then looks into Windows Directory


# pcmif is the perl pcm library
use pcmif;

# Config section
#Uses pcm_connect(), so requires pin.conf with necessary information to connect
#Infranet

## note the "pcmif::" prefix - this is a class prefix, meaning that the
## function "pcm_perl_new_ebuf()" is from the package/class "pcmif".
##
## first thing,create an ebuf for error reporting.
 $ebufp = pcmif::pcm_perl_new_ebuf();


#Open a PCM context.
$pcm_ctxp = pcmif::pcm_perl_connect($db_no, $ebufp);
#Check for errors and print the the status of the action.

  if (pcmif::pcm_perl_is_err($ebufp)) {
      pcmif::pcm_perl_print_ebuf($ebufp);
      exit(1);
  } 


# Create an input flist to execute the opcode

$f1 = <<"XXX"
0 PIN_FLD_POID           POID [0] 0.0.0.1 -1 0
0 PIN_FLD_LAST_NAME     STR [0] "Mouse"
0 PIN_FLD_FIRST_NAME     STR [0] "Mickey"
XXX
;

$flistp = pcmif::pin_perl_str_to_flist($f1, $db_no, $ebufp);
if (pcmif::pcm_perl_is_err($ebufp)) {
	 print "flist conversion failed\n";
	 pcmif::pcm_perl_print_ebuf($ebufp);
	 exit(1);
}
$out_flistp = pcmif::pcm_perl_op($pcm_ctxp, "PCM_OP_TEST_LOOPBACK", 0, $flistp, $ebufp);
if (pcmif::pcm_perl_is_err($ebufp)) {
	 print "Opcode execution failed \n";
	 pcmif::pcm_perl_print_ebuf($ebufp);
	 exit(1);
}

# print the output list
#
$out = pcmif::pin_perl_flist_to_str($out_flistp, $ebufp);
if (pcmif::pcm_perl_is_err($ebufp)) {
	 print "Flist conversion failed\n";
	 pcmif::pcm_perl_print_ebuf($ebufp);
	 exit(1);
}
print $out;

## destroy the flist
pcmif::pin_flist_destroy($flistp);
pcmif::pin_flist_destroy($out_flistp);

## close the pcm context
pcmif::pcm_context_close($pcm_ctxp, 0,$ebufp);

exit(0);

