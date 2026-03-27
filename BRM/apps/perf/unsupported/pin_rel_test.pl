#!/opt/portal/6.7/bin/perl
#
#	@(#) % %
#	
# Copyright (c) 1996, 2017, Oracle and/or its affiliates. All rights reserved.
#	
#	This material is the confidential property of Oracle Corporation or its
#	licensors and may be used, reproduced, stored or transmitted only in
#	accordance with a valid Oracle license or sublicense agreement.
#

# this script generates CDR file by simulating output from Integrate. 
#So using this simulator we can test performance of fastload without 
#having install Integrate. pin_irel_test will
# create sunchronous with DB CDR file which should match data in DB. 
# pin_irel_test actually is Perl script which contains of 2 pieces:
#    1. Creates pool of real poids in DB;
#    2. Creates CDR file(s) of given size.
#
#
#  Script can accept the following arguments:
#       -U < pattern>    - pattern for login in DB in printf format;
#       -I  <number>    -  first ID number of accounts , used in conjuction 
#                           with -U to generate "login",
#                           for example, -U user%d -I 5  will generate first
#                           login as user5, and next user6,...
#      -n < number>    - number accounts in DB beginning with -I to process;
#      -p  <name>      - name of pool of poids file;
#      -s   N1,N2, ...,Nn  - sizes of CDR files ( will generate n files).
#      -f  < name>    -  prefix for output file ( CDRs file will generated 
#                        with names <name>.0, <name>.1,....).
#      -o                   - option which force script to skip first step 
#                        and immediately using pool of poids start generate
#                         CDR file.
#       -w   - wait untill output cdrs file will be loaded in
#              DB , intend to work  in conjuction with Batch_controller.
#
#      Normally this script should run one time with full set of arguments 
#      to generate pool of poids and thereafter just using -o option to 
#      generate as many CDRs  files as needed.
#
#       Examples:
#         1. perl pin_rel_test.pl -U user%d -I 1 -n 1000000 -p patty -f beata -s
# 1000
#
#             will generate 2 files: patty - pool of poids;
#                                           beata.0 - CDR file of 1000 cdrs.
#
#         2.  perl pin_rel_test.pl -p patty -f beata -s 10000,100000,300000 -o
#                will generate 3 files: beata.0 - with 10000 cdrs;
#                                              beata.1 - with 100000 cdrs;
#                                              beata.2 - with 300000 cdrs.
#
#          3.   perl pin_rel_test.pl -p patty -f beata
#-s 10000,100000,300000 -o -w
#                doing the same thing as above but wait untill all files will be
#loaded in DB and display performance.
# Pool should be regenerated after some major changes done on DB ( recreation of
#used accounts, billing,...).
#
#        There are few configuration parameters in the beginning of script, 
# which you can adjust to make script work properly:
#          $CONF_OWNER,$CONF_PASSWD,$CONF_DBNAME  - parameters to properly 
# connect to DB ( used only in first step);
#          @RESOURCE_ID - resources in account balances, by default we use 840 -
#                         USA dollars.
#
#          $RELDIR_ARCHIVE  - path to directory where processed file will be
#                              located. Same as parameter $ARCHIVE in 
#                             RelHandler_config.values.
#            To run test with batch_controller make sure that parameters:
#               $STAGING and $FILETYPE  in RelHandler_config.values are the same
#                    as  cdrFileEvent.file.location and 
#                    cdrFileEvent.file.pattern in Infranet.properties for Batch_controller.
#
#             To test standalone performance of pin_irel_test after creating 
#             cdrs file the following command should be executed:
#
#                   date; pin_rel  <CDR namefile>; date
#
#

use Getopt::Std;
use File::Basename;

######################################################################
## Configuration stuff
######################################################################

$CONF_DBNAME="pindb2";
$ORACLE_VERSION="Oracle8";  # Oracle8 and up

$CONF_DB = 1;     # DB number
                  # RELDIR_ARCHIVE - where processed file moved
		  # RELDIR_ARCHIVE/../reject - will be place where rejected file moved
$RELDIR_ARCHIVE = "/opt/portal/6.7/apps/pin_rel/archive";
#########################################################
# for very big DB make number of threads much bigger
########################################################
$CONF_NUM_THREADS = 1; # number of threads to create pool file
# 3 parameters below should correspond each other
$BASIC_SERVICE_TYPE="TEL";
$SERVICE_TYPE="/service/telco/gsm/telephony";
$EVENT_TYPE="/event/delayed/session/telco/gsm";
#@RESOURCE_ID=(840,500);      #could be list of resources
#@RESOURCE_ID=(978,1000001);      #could be list of resources
@RESOURCE_ID=(978);      #could be list of resources
$NUM_OF_DISCOUNTS=1;   # applied to first resource only
$SIZE_OF_FILE=5000;  # how many records we dump in one serveroutput
$RECORD_TYPE=520;  # 520-GSM(SMS,DAT), 540-GPRS, 570- WAP
$INVOICE_DATA_OPTION = 0; # 0- empty, 1 - some data for invoicing

$DELIMITER="	";    # TAB + SPACE

#=============================================================================
# check what operation system we are running on
# $^O will return name of OS
if ( $^O =~ /win/i )
{
# NT computer ( actually any windows operation system )
# Command to run sqlplus
$PIN_CONF_SQLPLUS     = "plus80 -s";
# For Windows NT Oracle 8 has a different batch sql processor
if ( $ORACLE_VERSION =~ /^Oracle8i$/i ) {
$PIN_CONF_SQLPLUS     = "sqlplus -s";
}

# Temporary directory to create files
$PIN_CONF_TEMPDIR     = "C:/temp";
$MOVE="move";
}
else
{
# UNIX assignment
# Command to run sqlplus
$PIN_CONF_SQLPLUS       = "sqlplus -s";

# Temporary directory to create files
$PIN_CONF_TEMPDIR       = "/tmp";
$MOVE="mv";
}

($ME = $0) =~ s,.*/,,;

#
# Parse command line flags.
# U - pattern to create login name
# I - starting id to create login
# n - number of accounts in DB
# o - skip step to create POID pool
# f - path and name for creating cdr.dat
# p - path and name for pool of poids
# s - sizes of files in format "<size1>,<size2>,...<sizeN>"
# w - wait until last file will be processed
# h - print help (usage)
#
getopts('howU:I:n:f:p:s:') || &usage("");
if (defined $opt_h) {
	&usage("");
}


if (!defined $opt_o) {
	if (!(defined $opt_U && defined $opt_I && defined $opt_n &&defined $opt_f && defined $opt_p && defined $opt_s)) {
        	&usage("");
        }
# create poid pool first
srand ($$);
$currtime1 = time();
create_pool( $opt_U,$opt_I,$opt_n ,$opt_p );

$currtime2 = time();
$elapstime = $currtime2 - $currtime1;
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
$accounts = $opt_n;
print "***************************************************************\n";
printf " Poid pool for $accounts accounts was  created in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
print "***************************************************************\n";
}

	if (!(defined $opt_f && defined $opt_p && defined $opt_s)) {
        	&usage("");
        }
$currtime0 = time();
@sizes=split(',',$opt_s,99);
#generates files
$num = 0;
$cdrs = 0;
while ( $num < @sizes ) {

$file_result = $opt_f.".".$num;
create_cdr_file( $file_result ,$opt_p ,@sizes[$num]);
if ( $num == 0 ) {
# after creating first file we will start timer
$currtime1 = time();
}
$cdrs = $cdrs + @sizes[$num];
$num += 1;
}

if (!defined $opt_w) {
$currtime2 = time();
$elapstime = $currtime2 - $currtime0;
if ( $elapstime == 0 ) {
$perform = 0;
} else {
$perform = $cdrs / $elapstime;
}
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
print "***************************************************************\n";
printf " $cdrs cdrs were created  in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
print "***************************************************************\n";
} 
else {
# wait for finishing all loaders
wait_complete ($file_result);

$currtime2 = time();
$elapstime = $currtime2 - $currtime1;
if ( $elapstime == 0 ) {
$perform = 0;
} else {
$perform = $cdrs / $elapstime;
}
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
print "***************************************************************\n";
printf " $cdrs cdrs were loaded in DB in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
printf " FastLoad Performance obtained - $perform cdrs/sec \n";
print "***************************************************************\n";
}


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
		"    -o       skip step to create POID pool\n");
	print(<STDERR>,
		"    -f       path and name for resulting cdr file(s)\n");
	print(<STDERR>,
                "    -w       wait until last file will be processed\n");
	print(<STDERR>,
		"    -p       path and name for pool of poids\n");
	print(<STDERR>,
		"    -s       sizes of files in format <size1>,<size2>,...<sizeN>\n");

	exit 1;
	}

###############################################################
# subfunction create file pool of poids
###############################################################
sub create_pool {
 local ( $pattern, $offset, $accounts, $config_file) = @_;

 local($num) = 1;

$how_many_left = $accounts;
$start_id = $offset ;
@login_prefix=split ('%',$pattern);

while ( $how_many_left > 0 ) {
$fsize_all = $SIZE_OF_FILE*$CONF_NUM_THREADS;  # how many records we dump 
			 # in serveroutput for all threads
if ( $how_many_left <= $fsize_all ) {
$fsize_all = $how_many_left;
}
$how_many_left = $how_many_left - $fsize_all;
$fsize = $fsize_all / $CONF_NUM_THREADS;


$current_thread=$CONF_NUM_THREADS;

while ( $current_thread > 0 ) {

$start_id_current = $start_id + ( $CONF_NUM_THREADS - $current_thread) * $fsize;
$login_name =@login_prefix[0].$start_id_current;
$login_name1 =@login_prefix[0].($start_id_current+$fsize);

$sql_cmnd[$current_thread] =<<SQLPLUSEND 
spool $PIN_CONF_TEMPDIR/data$num.$current_thread.lst;
set serveroutput on SIZE 1000000

DECLARE
item_poid NUMBER;
bal_grp_poid NUMBER;
CURSOR service_cur IS
	SELECT poid_id0,account_obj_id0 FROM service_t
		WHERE poid_type = '$SERVICE_TYPE' and login >= '$login_name' and login < '$login_name1';

BEGIN
     FOR service_rec IN service_cur LOOP
	     select i.poid_id0, i.bal_grp_obj_id0  into item_poid, bal_grp_poid 
               from item_t i, billinfo_t b where
		b.account_obj_id0 = service_rec.account_obj_id0 and rownum < 2 and 
		i.bill_obj_id0 = b.bill_obj_id0 and i.poid_type = '/item/misc';

	     dbms_output.put_line(service_rec.poid_id0 || ' ' || service_rec.account_obj_id0 || ' ' || item_poid || ' ' || bal_grp_poid);
	    END LOOP;

END;
/

SQLPLUSEND
;
$current_thread=$current_thread - 1;
}
#  end of while for creating array
##################################################
$current_thread = 1;
while ( $current_thread <= $CONF_NUM_THREADS )
{
if ( $^O =~ /win/i )
{
# special code for Windows
	exec_sqlcommand($sql_cmnd[$current_thread]);
}
else
{
$procid[$current_thread] = fork();
#--------------------------------------
#  child process
#--------------------------------------
if ( $procid[$current_thread] == 0 ) {
	exec_sqlcommand($sql_cmnd[$current_thread]);
	# cocatenate result for each thread
        if ( $num != 1 ) {
          `$MOVE $PIN_CONF_TEMPDIR/data1.$current_thread.lst $PIN_CONF_TEMPDIR/data0.$current_thread.lst`;
          `cat   $PIN_CONF_TEMPDIR/data0.$current_thread.lst $PIN_CONF_TEMPDIR/data$num.$current_thread.lst > $PIN_CONF_TEMPDIR/data1.$current_thread.lst`;
        }

exit;    # this terminates child process

}
# this is a parent process
}

$current_thread=$current_thread + 1;
}
#
# waiting while all processes were completed
#
$current_thread = 1;
while ( $current_thread <= $CONF_NUM_THREADS )
 {
   if (!( $^O =~ /win/i ))
   {
      waitpid ($procid[$current_thread], 0 );
   }
     $current_thread=$current_thread + 1;
 }

$num = $num +1;
$start_id = $start_id + $fsize_all;
}

# final concatenation between thread
$current_thread = 1;
while ( $current_thread <= $CONF_NUM_THREADS )
 {
   if ( $current_thread == 1 ) {
      `$MOVE $PIN_CONF_TEMPDIR/data1.$current_thread.lst $config_file`;
   }
   else {
      `$MOVE $config_file $PIN_CONF_TEMPDIR/data0.$current_thread.lst`;
      `cat   $PIN_CONF_TEMPDIR/data0.$current_thread.lst $PIN_CONF_TEMPDIR/data1.$current_thread.lst > $config_file`;
   }
     $current_thread=$current_thread + 1;
 }
} # end of creating pool

###############################################################
# subfunction create cdr file
###############################################################
sub create_cdr_file {
   local ( $outfile, $infile, $size ) = @_;
   local ( $num );
   local ( $rec_id );
   local ( $cdrs );

   $outfile1 = "tempfile";
   if  ( -e "./pinaft" ) {
       $PINAFT_OUTPUT=`./pinaft`;
   }
   else {
   #  just fixed values
       $PINAFT_OUTPUT="1001538092 26 1004079600 1006761600 1010926";
       printf ("WARNING: pinaft is missing take default time\n");
   }
   ($CONF_CREATE_T,$CONF_ACTG_DOM,$CONF_ACTG_NEXT_T,$CONF_ACTG_FUTURE_T,
      $CONF_DATE_STRG ) = split (' ',$PINAFT_OUTPUT,99);

	open(IFILE, "<$infile") || die "$ME: cannot open $infile\n";

	# create cache in memory
$num = 0;
line:   while (<IFILE>) {
	($serv_poid,$acct_poid,$item_poid,$balgrp_poid) = split(' ', $_, 9999);
	  if ($serv_poid !~ /^[0-9]/) {
		next line;
          }
	  @serv_poid_pool[$num]=$serv_poid;
	  @acct_poid_pool[$num]=$acct_poid;
	  @item_poid_pool[$num]=$item_poid;
	  @balgrp_poid_pool[$num]=$balgrp_poid;
	  $num +=1;
	}

	close(IFILE);
        open(OFILE, ">$outfile1") || die "$ME: cannot create $outfile\n";
	# create header to imitate Solution 42
	printf OFILE "010%s1%sD00D1%sDBTEL%s48",
	    $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	printf OFILE "%s1%s%d%s%d%s%d%s",
	    $DELIMITER, $DELIMITER, $CONF_CREATE_T,$DELIMITER, $CONF_CREATE_T,$DELIMITER,$CONF_CREATE_T,$DELIMITER;
         printf OFILE "+0100%s4%s11%s0044%s0044%s",
             $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER,$DELIMITER;
	 printf OFILE "T%s00%s49%s",
	     $DELIMITER, $DELIMITER, $DELIMITER;
	 printf OFILE "RATING_PIPELINE%s10000%s%s\n",
	     $DELIMITER, $DELIMITER, $EVENT_TYPE, $DELIMITER;
$cdrs = 0;
$record = 2;
        while ( $cdrs < $size ) {
	   $index = pin_rand ( $num );
	   ############################################################
	   # create main event record
	   ############################################################
	   printf OFILE "020%s%d%s",
	       $DELIMITER, $record,$DELIMITER ;
	   printf OFILE "3%s4%s5%s6%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "7%s8%s9%s10%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "11%s12%sMSISDN%s14%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "15%s16%s17%sdescr%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "19%s20%s21%s22%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "23%s24%s25%s%s%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $BASIC_SERVICE_TYPE,$DELIMITER;
	   printf OFILE "27%s28%s00%sS%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "%d%s%d%s%s%s111%s",
	       $CONF_CREATE_T,$DELIMITER, $CONF_CREATE_T,$DELIMITER, "+0100",$DELIMITER, $DELIMITER;
	   printf OFILE "SEC%s36%sBYT%s38%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "BYT%s40%sNational%sGSM%s0.5%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER,$DELIMITER;
	   printf OFILE "EUR%sY%s1600%s",
	       $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "8001%s0.0%sEUR%sN%s0%s",
	      $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "%s%s%s",
	      $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "007800%s81%s00780%s00000%s",
	      $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "%s2%s3%s",
	      $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "0%s8%s80%s00%s1%s2%sROUT\n",
	      $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER,$DELIMITER;

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
	   printf OFILE "%s0\n",
	       $DELIMITER;
	   }
	   if ( $RECORD_TYPE == 540 ) {
	   ############################################################
	   #create session record GPRS
	   ###############################################################
	   printf OFILE "540%s%d%sIMSI%s",
	       $DELIMITER, $record,$DELIMITER, $DELIMITER;
	   printf OFILE "IMEI%s5%s6%s7%s",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	   printf OFILE "8%s9%s",
	       $DELIMITER, $DELIMITER;
           printf OFILE "10%sROUNTIN_A%sLOC_AREA_C%s11%s",
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
	   $record += 1;
	   ###############################################################
	   #create balance record ( could be a few 600 records)
	   # and one header balance 900
	   ################################################################
	   if ( $INVOICE_DATA_OPTION == 0 ) {
	     $invoice_data = "";
	   } else {
              $login_name =@login_prefix[0].$index;
              $login_name1 =@login_prefix[0].($index+1);
	     $invoice_data = "\@INTEGRATE,$login_name,$login_name1,0,12,30.0,00780,1234TEEW,{";
	     $rec_id = 0;
             while ( $rec_id < @RESOURCE_ID ) {
	      $invoice_data =$invoice_data."|@RESOURCE_ID[$rec_id],15.0";
	      $rec_id += 1;
	     }
             $poid=@item_poid_pool[$index];
	     $invoice_data =$invoice_data."},{|0,0.0.0.$CONF_DB\\ /item/misc\\ $poid\\ 0,@RESOURCE_ID[0],30.0,WEEKDAY_RATE,111.0}"

	   }
	     printf OFILE "900%s%d%s%1d /account %d 0",
	       $DELIMITER, $record,$DELIMITER, $CONF_DB, @acct_poid_pool[$index];
	     printf OFILE "%s%1d %s %d 0",
	           $DELIMITER, $CONF_DB, $SERVICE_TYPE, @serv_poid_pool[$index];
	     printf OFILE "%s%1d /item/misc %d 0",
	           $DELIMITER, $CONF_DB, @item_poid_pool[$index];
	     printf OFILE "%s0  0 0",
		   $DELIMITER;
	     printf OFILE "%sTAX_LOCALES%s%s%s1",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	     printf OFILE "\n",
	       $invoice_data;
	   $record += 1;
	   $rec_id = 0;
	   while ( $rec_id < @RESOURCE_ID ) {
	     printf OFILE "600%s%d%s",
	       $DELIMITER, $record,$DELIMITER;
	     printf OFILE "%1d /account %d 0%s",
	       $CONF_DB, @acct_poid_pool[$index],$DELIMITER;
	     printf OFILE "%1d /balance_group %d 0%s",
	           $CONF_DB, @balgrp_poid_pool[$index],$DELIMITER;
	     printf OFILE "%1d /item/misc %d 0%s",
	           $CONF_DB, @item_poid_pool[$index],$DELIMITER;
	     printf OFILE "%d%sGSM%s1",
	       @RESOURCE_ID[$rec_id],$DELIMITER,$DELIMITER;
	     printf OFILE "%s%1d /product/telephony 123456 0%s102%s",
	           $DELIMITER, $CONF_DB, $DELIMITER, $DELIMITER;
	     printf OFILE "tax%sFlat_Rate%sgm_gsm%s0:0%s10.0",
	       $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	     printf OFILE "%s30.0%s20.0%s0%sDISCOUNT_INFO\n",
	       $DELIMITER, $DELIMITER,$DELIMITER,$DELIMITER;

            if ( $rec_id == 0 ) {   # all discounts only for 1st resource
	       $dsc_id = 0;
	       $record += 1;
	       while ( $dsc_id < $NUM_OF_DISCOUNTS ) {
                 $dsc_id++;
	         printf OFILE "600%s%d%s",
	           $DELIMITER, $record,$DELIMITER;
	         printf OFILE "%1d /account %d 0%s",
	           $CONF_DB, @acct_poid_pool[$index],$DELIMITER;
	         printf OFILE "%1d /balance_group %d 0%s",
	               $CONF_DB, @balgrp_poid_pool[$index],$DELIMITER;
	         printf OFILE "%1d /item/misc %d 0%s",
	               $CONF_DB, @item_poid_pool[$index],$DELIMITER;
	         printf OFILE "%d%sGSM%s1",
	           @RESOURCE_ID[$rec_id],$DELIMITER,$DELIMITER;
	         printf OFILE "%s%1d /discount %d 0%s102%s",
	               $DELIMITER, $CONF_DB, $dsc_id, $DELIMITER, $DELIMITER;
	         printf OFILE "tax%sFlat_Rate%sgm_gsm%s0:0%s10.0",
	           $DELIMITER, $DELIMITER, $DELIMITER, $DELIMITER;
	         printf OFILE "%s-5.0%s-3.0%s0%sDISCOUNT_INFO\n",
	           $DELIMITER, $DELIMITER,$DELIMITER,$DELIMITER;
                 }
               }

             printf OFILE "605%s%d%s",
               $DELIMITER, $rec_id,$DELIMITER;
	     printf OFILE "%1d /balance_group %d 0%s",
	           $CONF_DB, @balgrp_poid_pool[$index],$DELIMITER;
	     printf OFILE "%d\n",
	       @RESOURCE_ID[$rec_id],$DELIMITER;

             printf OFILE "607%s%d%s",
               $DELIMITER, $rec_id,$DELIMITER;
	     printf OFILE "15.0%s",
	           $DELIMITER;
             printf OFILE "10600%s111111111%s",
               $DELIMITER, $DELIMITER;
	     printf OFILE "marina\n";

	     $rec_id += 1;
	   }
	   $cdrs += 1;
	   $new_poid += 1;
        }
	#create trailer with # cdrs
	 printf OFILE "090%s%d%sD00D1%sDBTEL%s0",
	       $DELIMITER, $record,$DELIMITER, $DELIMITER, $DELIMITER;
	 printf OFILE "%s0%s%d%s%d%s+0100%s%d%s+0100",
	      $DELIMITER,$DELIMITER, $size,$DELIMITER,  $CONF_CREATE_T,$DELIMITER, $DELIMITER, $CONF_CREATE_T, $DELIMITER;
	 printf OFILE "%s4.0%s0.0\n",
	       $DELIMITER, $DELIMITER;

	close(OFILE);
	`mv $outfile1 $outfile`;

}

###############################################################
# subfunction waiting until given file was processed 
# by pin_rel_test
###############################################################
sub wait_complete {
   local ( $infile) = @_;

   $filename = basename($infile);
   while ( !( -e "$RELDIR_ARCHIVE/$filename" ) &&
	!( -e "$RELDIR_ARCHIVE/../reject/$filename" ) ) {
       sleep (1);
   }
}

###############################################################################
# exec_sqlcommand()
#       input:
#               sql command(s)
###############################################################################
sub exec_sqlcommand {
	local ($cmd) = @_;
	local ($status) = 0;
	local ($exitcode) = 0;
	local ($tmpfile) = "$PIN_CONF_TEMPDIR/pintmp$$.sql";
	# Create a temporary file with the sqlplus input.
	#
	open(TMPFILE, ">$tmpfile") || die "$ME: cannot create $tmpfile\n";
	print TMPFILE "$cmd";
	print TMPFILE "\nexit;\n";
	close(TMPFILE);

	$sqlout = `$PIN_CONF_SQLPLUS /\@$CONF_DBNAME < $tmpfile`;
	$exitcode = $?;
	$status = ($? >> 8);

       unlink "$tmpfile";

       if ($sqlout =~ m/ERROR: /) {
       print("$sqlout");
       print("$ME: SQLPLUS failed (exitcode = $exitcode)\n");
       exit(1);
       }

       #
       if ($status || $exitcode) {
       print("$ME: SQLPLUS failed with status $status\n");
       exit (1);
       }
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






