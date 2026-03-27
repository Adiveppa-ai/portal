#!/opt/portal/6.7/bin/perl
#
#	@(#) % %
#	
# Copyright (c) 1996, 2015, Oracle and/or its affiliates. All rights reserved.
#	
#	This material is the confidential property of Oracle Corporation or its
#	licensors and may be used, reproduced, stored or transmitted only in
#	accordance with a valid Oracle license or sublicense agreement.
#

# this script generates CDR file by simulating input for Integrate. 
#
#
#  Script can accept the following arguments:
#       -U < pattern>    - pattern for login in DB in printf format;
#       -I  <number>    -  first ID number of accounts , used in conjuction 
#                           with -U to generate "login",
#                           for example, -U user%d -I 5  will generate first
#                           login as user5, and next user6,...
#      -n < number>    - number accounts in DB beginning with -I to process;
#      -s   N1,N2, ...,Nn  - sizes of CDR files ( will generate n files).
#      -f  < name>    -  prefix for output file ( CDRs file will generated 
#                        with names <name>.0, <name>.1,....).
#
#       Examples:
#         1. perl pin_integrate_cdr.pl -U 004417%d -I 1 -n 1000000  -f beta -s
# 1000
#
#                           creates         beta.0 - EDR file of 1000 cdrs.
#
#
#          2.    perl pin_integrate_cdr.pl   -U 004417%d -I 1 -n 1000000  -f beta -s 10000,100000,300000 
# creates 3 files beta.0 with 10000 cdrs, beta.1 with 100000 cdrs and beta.2 with 300000 cdrs
#

use Getopt::Std;
use File::Basename;

######################################################################
## Configuration stuff
######################################################################

$CURRENCY="EUR";
$SERVICE = 1;   # service code -> 1 -GSM, 2-GPRS, 3- SMS, 4-DATA, 5-WAP
$DELIMITER="	";    # TAB + SPACE
$TIMESTAMP=0;   # 0 - fixed timestamp calculated during start 
                # 1 - variable timestamps to prevent duplicate cdrs
                # other - take this value as fixed timestamp
$COMPLETION=0;  # 0 - all cdrs completed
                # 1 - only started cdrs ( need assembly )
                # 2 - only ended cdrs
                # 3 - only intermediate cdrs

#=============================================================================
@SERV_TABLE=( 1, 520, "TEL",
	      2, 540, "GP",
	      3, 540, "SMS",
	      4, 540, "DAT",
	      5, 570, "WAP" );

#===========================================================================
($ME = $0) =~ s,.*/,,;

$index = 0;

#default values
#
$RECORD_TYPE=@SERV_TABLE[1];    # 520 - is gsm/telephony
                     # 570 - wap type
		     # 540 - is GPRS type
$SERVICE_CODE = @SERV_TABLE[2];

while ( $index < @SERV_TABLE ) {
  if ( @SERV_TABLE[$index] == $SERVICE ) {
    $RECORD_TYPE=@SERV_TABLE[$index+1];  
    $SERVICE_CODE = @SERV_TABLE[$index+2];
    last;
  }
  $index = $index + 3;
}
#
# Parse command line flags.
# U - pattern to create login name
# I - starting id to create login
# n - number of accounts in DB
# f - path and name for creating cdr.dat
# s - sizes of files in format "<size1>,<size2>,...<sizeN>"
# c - start number for chain reference ( default-same as -I, used for call assembly)
# o - option ( 0 -sequentially all, 1 - randonly national, 
#     2-randomly international(default))
# h - print help (usage)
#
getopts('hU:I:n:f:o:s:c:') || &usage("");
if (defined $opt_h) {
	&usage("");
}


	if (!(defined $opt_f && defined $opt_I && defined $opt_U && defined $opt_n && defined $opt_s)) {
        	&usage("");
        }
$currtime0 = time();
@sizes=split(',',$opt_s,99);
$option = 2;  #default option
if (defined $opt_o) {
    $option = $opt_o;
}
$chain_start = $opt_I;
if (defined $opt_c) {
    $chain_start = $opt_c;
}
#generates files
srand ($$);
$num = 0;
$cdrs = 0;
while ( $num < @sizes ) {

$file_result = $opt_f.".".$num;
create_cdr_file( $file_result ,@sizes[$num]);
if ( $num == 0 ) {
# after creating first file we will start timer
$currtime1 = time();
}
$cdrs = $cdrs + @sizes[$num];
$num += 1;
}

$currtime2 = time();
$elapstime = $currtime2 - $currtime0;
if ( $elapstime > 0 ) {
$perform = $cdrs / $elapstime;
} else {
$perform = 0;
}
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
print "***************************************************************\n";
printf " $cdrs cdrs were created  in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
print "***************************************************************\n";

################################################################################
# usage:  Print usage message and exit.
#
################################################################################
sub usage {
	print(<STDERR>,
		@_);

	print(<STDERR>,
		"Usage: $ME [options] \n");
	print(<STDERR>,
		"    -U       pattern to create login name\n");
	print(<STDERR>,
		"    -I       starting id to create login\n");
	print(<STDERR>,
		"    -n       number of accounts in DB\n");
	print(<STDERR>,
		"    -f       path and name for resulting cdr file(s)\n");
	print(<STDERR>,
		"    -o       option (0-sequentially  all accounts)  \n");
	print(<STDERR>,
		"                    (1-(national)no changes in prefix)  \n");
	print(<STDERR>,
		"                    (2-country will be selected randomly(default)) \n");
	print(<STDERR>,
		"    -s       sizes of files in format <size1>,<size2>,...<sizeN>\n");

	exit 1;
	}

###############################################################
# subfunction create cdr file
###############################################################
sub create_cdr_file {
   local ( $outfile, $size ) = @_;
   local ( $num );
   local ( $cdrs );

   $completion_code = "S";
   @login_prefix=split ('%',$opt_U );
   if  ( -e "./pinaft" ) {
       $PINAFT_OUTPUT=`./pinaft`;
   }
   else {
   #  just fixed values
       printf ("WARNING: pinaft is missing take default time\n");
       $PINAFT_OUTPUT="1001538092 26 1004079600 1006761600 1010926";
   }
   ($CONF_CREATE_T,$CONF_ACTG_DOM,$CONF_ACTG_NEXT_T,$CONF_ACTG_FUTURE_T,
      $CONF_DATE_STRG ) = split (' ',$PINAFT_OUTPUT,99);
	$CONF_CREATE_T=$CONF_CREATE_T;

        if ( $TIMESTAMP == 0 ) { 
          $create_t = $CONF_CREATE_T+30000;
        }
        elsif ( $TIMESTAMP == 1 ) {
          $create_t = $CONF_CREATE_T;
        }
        else {
          $CONF_CREATE_T = $TIMESTAMP;
          $create_t = $CONF_CREATE_T;
        }
        $num = $opt_n;

        open(OFILE, ">$outfile") || die "$ME: cannot create $outfile\n";
	# create header to imitate Solution 42
	printf OFILE "010%s1%sD00D1%sDBTEL%s48",
	    $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	printf OFILE "%s1%s%d%s%d%s%d%s",
	    $DELIMITER, $DELIMITER, $CONF_CREATE_T,$DELIMITER, $CONF_CREATE_T,$DELIMITER, $CONF_CREATE_T,$DELIMITER;
	printf OFILE "+0100%s4%s11%s0044%s0044%s",
	    $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER,$DELIMITER;
	printf OFILE "T%s00%s49%s00%s00%s+100\n",
	    $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
$cdrs = 0;
$record = 2;
        while ( $cdrs < $size ) {
           if ( $TIMESTAMP != 1 ) {
                 $CONF_CREATE_T =  $create_t ;
           }
           else {
                 $kk = $cdrs % 100;
                 $adjustment = $kk * 105;
                 $CONF_CREATE_T =  $create_t - $adjustment;
           }
	   if ( $option == 0 ) {
	        $index = $opt_I + $cdrs ;
	        $login_name =@login_prefix[0].int($index);
	        if ( ($cdrs +1) == $size ) {
	               $login_name1 =@login_prefix[0].(int($index) - 1);
	        } else {
	               $login_name1 =@login_prefix[0].(int($index) + 1);
	        }
	   } elsif ( $option == 1 ) {
	        $index = $opt_I + pin_rand ( $num );
	        $login_name =@login_prefix[0].int($index);
	        if ( int($index +1) == $size ) {
	               $login_name1 =@login_prefix[0].(int($index) - 1);
	        } else {
	               $login_name1 =@login_prefix[0].(int($index) + 1);
	        }
	   } else {
	    $index = $opt_I + pin_rand ( $num );
	    $login_name =@login_prefix[0].int($index);
	    $login_name1 ='00'.int(rand(99)).int($index*1000);
	   }
	   ############################################################
	   # create main event record
	   ############################################################
           $chain_ref=$chain_start+$cdrs;
           if ( $COMPLETION == 0 ) {
                $completion_code = "S";
           }
           elsif ( $COMPLETION == 1 ) {
                $completion_code = "F";
           }
           elsif ( $COMPLETION == 2 ) {
                $completion_code = "L";
           }
           elsif ( $COMPLETION == 3 ) {
                $completion_code = "I";
           }
	   printf OFILE "020%s%d%s",
	       $DELIMITER, $record,$DELIMITER ;
	   printf OFILE "0%s%010d%sG%s26201%s",
	       $DELIMITER, $chain_ref,$DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "Z%s8%sS%s00%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "0%s0%s%s%s00%s",
	       $DELIMITER, $DELIMITER, $login_name,$DELIMITER, $DELIMITER;
	   printf OFILE "0%s%s%s%sinternet.t-d1.de%s",
	       $DELIMITER, $DELIMITER, $login_name1,$DELIMITER, $DELIMITER;
	   printf OFILE "19%s20%s21%s22%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "%s02%s01%s$SERVICE_CODE%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "27%s28%sC%s%s%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $completion_code,$DELIMITER;
	   printf OFILE "%d%s%d%s%s%s111%s",
	       $CONF_CREATE_T,$DELIMITER, $CONF_CREATE_T,$DELIMITER, "+0100",$DELIMITER, $DELIMITER;
	   printf OFILE "SEC%s36%sBYT%s38%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "BYT%s40%sNational%sGSM%s0.5%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER ,  $DELIMITER;
	   printf OFILE "$CURRENCY%sY%s1600%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "8001%s0.0%s$CURRENCY%sN%s0%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "CUP%s0%s004417%s",
	       $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "007800%s81%s00780%s00000%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "%s2%s",
	       $DELIMITER, $DELIMITER;
	   printf OFILE "+100%s%d%s+100%s%d%s",
	       $DELIMITER, $CONF_CREATE_T,$DELIMITER, $DELIMITER,$CONF_CREATE_T,$DELIMITER;
	   printf OFILE "+100%s2%s3\n",
	       $DELIMITER, $DELIMITER;
	   $record += 1;
	   if ( $RECORD_TYPE == 520 ) {
	   ############################################################
	   #create session record GSM
	   ###############################################################
           printf OFILE "520%s%d%s%s",
               $DELIMITER, $record,$DELIMITER, $DELIMITER;
           printf OFILE "4%s5%s6%s7%s",
               $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
           printf OFILE "8%s1234TEEW%s1234TEEW%sVME465%s",
               $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
           printf OFILE "VM356%sDEF%sGD231%s1%s",
               $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
           printf OFILE "0%s0.0%s18%s0.0%s",
               $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
           printf OFILE "%s0%s11%s22\n",
               $DELIMITER,$DELIMITER,$DELIMITER,$DELIMITER;
	   }
	   if ( $RECORD_TYPE == 540 ) {
	   ############################################################
	   #create session record GPRS
	   ###############################################################
	   printf OFILE "540%s%d%sIMSI%s",
		  $DELIMITER, $record,$DELIMITER, $DELIMITER;
	   printf OFILE "IMEI%s5%s6%s7%s",
	          $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "8%sROUNTIN_A%sLOC_AREA_C%s11%s",
	           $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "SGSN_ADDRESS%sGGSN_ADDRESS%sAPN%sNODE_ID%s",
	           $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
           printf OFILE "TRANS_ID%sSUB_TRANS_ID%s18%sPT%s",
		  $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "PDP_ADDRESS%sPDP_RADDRESS%s22%sDIAGNOSTICS%s",
	          $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
   	   printf OFILE "CELL_ID%s25%s26%s27%s",
	          $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "28%s29%s30%s31%s",
		  $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
           printf OFILE "32%s33%s34%s35%s",
                  $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "NET_CAP%s37\n",
	          $DELIMITER;
	   }
	   ###############################################################
	   $record += 1;
	   $cdrs += 1;
	   $new_poid += 1;
        }
	#create trailer with # cdrs
	 printf OFILE "090%s%d%sD00D1%sDBTEL%s0",
	       $DELIMITER, $record,$DELIMITER, $DELIMITER, $DELIMITER;
	 printf OFILE "%s0%s%d%s%d%s0%s%d%s0",
	       $DELIMITER,$DELIMITER, $size,$DELIMITER,  $CONF_CREATE_T,$DELIMITER, $DELIMITER, $CONF_CREATE_T, $DELIMITER;
	 printf OFILE "%s4.0%s0.0\n",
	       $DELIMITER, $DELIMITER;


	close(OFILE);

}
################################################
# pin_rand is improved function for perl rand
#################################################
 sub pin_rand {
   local ( $range ) = @_;
   local ($value,$value1,$value2);

    $value = int(rand($range));
    if ( $range > 32000 ) {
       $value2 = int ($range/32000);
       $value1 = int(rand ($value2) );
       $value = ($value+$value1);
       if ( $value >= $range ) { $value = $range-1;}
     }

   return ( $value );
}

1;




