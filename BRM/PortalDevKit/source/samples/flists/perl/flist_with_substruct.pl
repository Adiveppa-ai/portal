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
#Uses pcm_connect(), so requires pin.conf with necessary information to connect
#Infranet

## note the "pcmif::" prefix - this is a class prefix, meaning that the
## function "pcm_perl_new_ebuf()" is from the package/class "pcmif".
##
## first thing,create an ebuf for error reporting.

#Create an ebuf for error reporting.

$ebufp = pcmif::pcm_perl_new_ebuf();

$LOGIN_DB="0.0.0.1";

#Use a "here" document to assign an flist string to a variable. 
  
$f1 = <<"XXX"
 0 PIN_FLD_PROGRAM_NAME    STR [0] "Admin Manager"
 0 PIN_FLD_PAYINFO       ARRAY [1] 
 1     PIN_FLD_POID           POID [0] 0.0.0.1 /payinfo/cc -1 0
 1     PIN_FLD_INHERITED_INFO SUBSTRUCT [0] 
 2         PIN_FLD_CC_INFO       ARRAY [0] 
 3             PIN_FLD_DEBIT_EXP       STR [0] "0905"
 3             PIN_FLD_DEBIT_NUM       STR [0] "4444111122223333"
 3             PIN_FLD_NAME            STR [0] "Joe Smith"
XXX
;


#Use the string-to-flist conversion function to parse the flist string  
#that contains the login information and use it to open a PCM #context. 

$login_flistp = pcmif::pin_perl_str_to_flist($f1, 
                                            $LOGIN_DB, $ebufp);

#Check for errors and print the error report.
if (pcmif::pcm_perl_is_err($ebufp)) {
    print "Error creating flist\n";
    pcmif::pcm_perl_print_ebuf($ebufp);
    exit(1);
}
# print the Flist
#Convert the flist to a printable string and print it. 

$out = pcmif::pin_perl_flist_to_str($login_flistp, $ebufp);
          print "In flist is:\n";
          print $out;
exit(0);

