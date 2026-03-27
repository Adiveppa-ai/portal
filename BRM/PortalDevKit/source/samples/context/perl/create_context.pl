#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#
# Copyright (c) 2000, 2009, Oracle and/or its affiliates. All rights reserved. 
# This material is the confidential property of Oracle Corporation. 
# or its subsidiaries or licensors and may be used, reproduced, stored
# or transmitted only in accordance with a valid Oracle license or 
# sublicense agreement.
#
#######################################################################

## Note the pin.conf file (pin.conf on NT) must reside in "." 
## The .pm files are (should be) located in this directory.
## On NT it looks into current directory and then looks into Windows Directory

# pcmif is the perl pcm library
use pcmif;


# Config section
#Uses pcm_context_open(), so requires pin.conf with userid only
#Set the login information.

 $LOGIN_DB = "0.0.0.1";
 $LOGIN_NAME = "root.0.0.0.1";
 $LOGIN_PASSWD = "password";
# give the host name to be connected to
 $CM_HOST = "<some_host>"; 
          
## note the "pcmif::" prefix - this is a class prefix, meaning that the
## function "pcm_perl_new_ebuf()" is from the package/class "pcmif".
##
## first thing,create an ebuf for error reporting.

 $ebufp = pcmif::pcm_perl_new_ebuf();

 #Use a "here" document to assign an flist string to a variable. 
  
  $f1 = <<"XXX"
  0 PIN_FLD_POID POID [0] $LOGIN_DB /service/pcm_client 1 0
  0 PIN_FLD_TYPE ENUM [0] 1
  0 PIN_FLD_LOGIN STR [0] "$LOGIN_NAME"
  0 PIN_FLD_PASSWD_CLEAR    STR [0] "$LOGIN_PASSWD"
  0 PIN_FLD_CM_PTR     STR [0] "ip $CM_HOST 11960"
XXX
;

#Use the string-to-flist conversion function to parse the flist string  
#that contains the login information and use it to open a PCM #context. 

$login_flistp = pcmif::pin_perl_str_to_flist($f1, 
                                            $LOGIN_DB, $ebufp);

#Check for errors and print the error report.
          if (pcmif::pcm_perl_is_err($ebufp)) {
              print "flist conversion failed\n";
              pcmif::pcm_perl_print_ebuf($ebufp);
              exit(1);
              }
#Open a PCM context.
$pcm_ctxp = pcmif::pcm_perl_context_open($login_flistp, 
                                         $db_no, $ebufp);
#Check for errors and print the the status of the action.

  if (pcmif::pcm_perl_is_err($ebufp)) {
      print "Connection failed.\n";
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
   
      
