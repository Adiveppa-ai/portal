#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#
# Copyright (c) 2000, 2009, Oracle and/or its affiliates. All rights reserved. 
# This material is the confidential property of Oracle Corporation. 
# or its subsidiaries or licensors and may be used, reproduced, stored
# or transmitted only in accordance with a valid Oracle license or 
# sublicense agreement.
#
#######################################################################
# This script opens PCM context to Infranet


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
      print " Connection failed\n"; 
      pcmif::pcm_perl_print_ebuf($ebufp);
      exit(1);
  } else {
     $my_session = pcmif::pcm_perl_get_session($pcm_ctxp);
     $my_userid = pcmif::pcm_perl_get_userid($pcm_ctxp);
     print "    Connection successful\n";
     print "    DEFAULT db is: $db_no \n";
     print "    session poid is: ", $my_session, "\n";
     print "    userid poid is: ", $my_userid, "\n";
  }

#Close the PCM context. Check for errors and print the error report.
  pcmif::pcm_context_close($pcm_ctxp, 0, $ebufp);
  if (pcmif::pcm_perl_is_err($ebufp)) {
     print "BAD close\n",
     pcmif::pcm_perl_ebuf_to_str($ebufp), "\n";
     exit(1);
  }
  exit(0); 
