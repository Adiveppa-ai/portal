#
#	@(#) % %
#       
#       Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#

require "..\ms_conf.pm";
######################################################################
## Configuration stuff
######################################################################

#---------------------------------------------------------------------
# pinaft outputs create_t (today), actg_next_t, actg_future_t and 
# actg_dom. Note that if today is 29-31 then actg_dom, actg_next_t and 
# actg_future_t will be auto adjusted to 1st.
#---------------------------------------------------------------------
$PINAFT_OUTPUT=`./pinaft`;
($CONF_CREATE_T,$CONF_ACTG_DOM,$CONF_ACTG_NEXT_T,$CONF_ACTG_FUTURE_T,
   $CONF_DATE_STRG ) = split (' ',$PINAFT_OUTPUT,99);

$CONF_NUM_ACNT=1000;   # number accounts to update per thread
$CONF_BEG_ID0=5000; 
$CONF_NUM_THREADS=1;      # this value alwaus should be 1    
$CONF_PERIODS=1;	# size of step for next account

$CONF_TABLESPACE = "pinx00";  # filegroup for index i_account_acctgnext
$CONF_DEBUG=false;
$CONF_COMMIT_FREQ=10;

#--------------------------------------------
# parameters below are not used and could be any value
$CONF_PLAN="'Basic'";
$CONF_DEAL1="'IP Basic'";
$CONF_DEAL2="'IP Basic'";
$CONF_PROD1="'IP async measured'";
$CONF_PROD2="'IP async measured'";
$CONF_DATE_STR="'$CONF_DATE_STRG'";
#--------------------------------------------
# end of configuration section
#--------------------------------------------
#=============================================================================

# Temporary directory to create files
$PIN_CONF_TEMPDIR     = "C:\\temp";

# create procedure to load accounts
`isql -U $CONF_OWNER -P $CONF_PASSWD -d $CONF_DBNAME -S $CONF_SERVER -i ms_updcnts.sql -o outfile1`;

$start_seq_no=$CONF_BEG_ID0;
$currtime1 = time();

#--------------------------------------
$sqlcmnd_array =<<SQLPLUSEND 
drop index account_t.i_account_actgnextt__id
go
DECLARE \@num_accnt int, \@beg_id0 int
DECLARE \@create_t int 
DECLARE \@period int


	set \@beg_id0   = ${start_seq_no}
	-- (CONFIGURE) -- number of accounts
	set \@num_accnt         = ${CONF_NUM_ACNT}

	-- (CONFIGURE) current time in unix time format
	set     \@create_t      = ${CONF_CREATE_T}

        -- (CONFIGURE) creditcard/invoice account?
	set \@period             = ${CONF_PERIODS}

	--
	-- Call update_accounts to actually update the accounts
	--
	EXEC    update_accounts    \@num_accnt, \@beg_id0,
				\@create_t, \@period
	go

SQLPLUSEND
;
##################################################
	open(OFILE, ">exfile") || die "$ME: cannot open $exfile\n";
	printf OFILE "%s", $sqlcmnd_array;
	close(OFILE);

##################################################
#  execute prepared file
#################################################
`isql -U $CONF_OWNER -P $CONF_PASSWD -d $CONF_DBNAME -S $CONF_SERVER -i exfile -o outfile`;


$currtime2 = time();
$elapstime = $currtime2 - $currtime1;
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
$accounts = ( $CONF_NUM_ACNT ) /$CONF_PERIODS;
print "***************************************************************\n";
printf " %d accounts were updated in %d h %d min %d sec.\n",
	   $accounts, $ehours,$emin,$esec;
print "***************************************************************\n";

# update index by actg_next_t
$sqlcommand =<<SQLPLUSEND2
create index i_account_actgnextt__id on account_t ( actg_next_t )  on $CONF_TABLESPACE
go
SQLPLUSEND2
;

##################################################
	open(OFILE, ">exfile1") || die "$ME: cannot open $exfile1\n";
	printf OFILE "%s", $sqlcommand;
	close(OFILE);

##################################################
`isql -U $CONF_OWNER -P $CONF_PASSWD -d $CONF_DBNAME -S $CONF_SERVER -i exfile1 -o outfile3`;

1;
