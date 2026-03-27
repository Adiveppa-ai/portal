#!/usr/local/bin/perl
###########
#
#	@(#) % %
#       
#       Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#
###########
require "../db_conf.pm";
######################################################################
## Configuration stuff
## sqlpurchase script will add $NUM_PRODUCTS to each account
## which login name start with "user$CONF_BEG_ID0"
## number accounts to process is $CONF_NUM_THREADS * $NUM_ACCOUNTS
######################################################################
$CONF_BEG_ID0=1000000;   # starting number for login 
$CONF_NUM_THREADS=1;      # how many parallel processes we are going to use
$NUM_ACCOUNTS=12;    # num accounts to process per thread
$NUM_PRODUCTS= 20;		# num products per account

$CONF_DEBUG=false;
$CONF_COMMIT_FREQ=10;
#---------------------------------------------------------------------
# pinaft outputs create_t (today), actg_next_t, actg_future_t and 
# actg_dom. Note that if today is 29-31 then actg_dom, actg_next_t and 
# actg_future_t will be auto adjusted to 1st.
#---------------------------------------------------------------------
$PINAFT_OUTPUT=`./pinaft`;
($CONF_CREATE_T,$CONF_ACTG_DOM,$CONF_ACTG_NEXT_T,$CONF_ACTG_FUTURE_T,
   $CONF_DATE_STRG ) = split (' ',$PINAFT_OUTPUT,99);

$CONF_DATE_STR="'$CONF_DATE_STRG'";
#--------------------------------------------
# end of configuration section
#--------------------------------------------
#=============================================================================

$sqlout="";
#--------------------------------------
#--------------------------------------
$sqlcommand =<<ENDSQL
set serveroutput on
CREATE OR REPLACE PACKAGE sess_load_db AS
	TYPE SessInfoTyp IS RECORD (
		num_acnt	NUMBER,		-- number of accounts
		db_id		NUMBER,		-- database id
		login_num	NUMBER,		-- starting login number
		num_products	PLS_INTEGER,	-- number of products to create
		create_t	NUMBER,		-- create_time
		commit_freq	PLS_INTEGER,	-- Commit every n accounts
		debug		BOOLEAN
	);
	-- This procedure inserts a given number of accounts
	PROCEDURE insert_products(l_info IN SessInfoTyp) ;
END;
/

CREATE OR REPLACE PACKAGE BODY sess_load_db AS
	TYPE CurrAccountInfoTyp IS RECORD (
		cur_acnt	NUMBER,
		cur_product	NUMBER
		);

	PROCEDURE insert_products(l_info IN SessInfoTyp) IS

        cl_info         CurrAccountInfoTyp;

	commit_cnt	NUMBER;
	login0          NUMBER;
	login1          VARCHAR(60);
	service_type    VARCHAR(60);
	curr_rec_id  	NUMBER;
	plan_id 	NUMBER;
	deal_id 	NUMBER;
	prod_id 	NUMBER;
	service_id0	NUMBER;
	service_id1	NUMBER;
	account_id0	NUMBER;
	v_create_t	NUMBER;		-- create_time
	pr_create_t	NUMBER;		-- create_time
	pr_end_t	NUMBER;		-- next_time
	pr_flag		NUMBER;		-- cycle flag
	pr_rec		NUMBER;	
	pr_charge_from	NUMBER;	
	pr_charge_to	NUMBER;	

       cursor service is
        	select poid_id0 , account_obj_id0 from service_t
        	   where login = login1;
       cursor products is
        	select service_obj_id0,service_obj_type,plan_obj_id0, deal_obj_id0, 
                  product_obj_id0, cycle_fee_flags , cycle_start_t from account_products_t
        	   where obj_id0 = account_id0 and rec_id = curr_rec_id;
	BEGIN
			
		commit_cnt := 1;
		login0 := l_info.login_num;

	   FOR cur_acnt IN 1..l_info.num_acnt LOOP

	--
	-- read account information
	--
		login1 := 'user' || TO_CHAR(login0);
		open service;
		fetch service into service_id0, account_id0;
		close service;

                select max(rec_id) into curr_rec_id from account_products_t where obj_id0 = account_id0 ;

		open products;
		fetch products into service_id1,service_type,plan_id, deal_id, prod_id, pr_flag,v_create_t;
		close products;
                select cycle_fee_start_t, cycle_fee_end_t, charged_from_t, charged_to_t,rec_id2 
                   into pr_create_t, pr_end_t,pr_charge_from,pr_charge_to, pr_rec
                      from account_cycle_fees_t 
                      where obj_id0 = account_id0 and rec_id = curr_rec_id;

	       FOR cur_product IN 1..l_info.num_products LOOP

		curr_rec_id := curr_rec_id + 1;

                INSERT INTO account_cycle_fees_t (
                obj_id0, rec_id,rec_id2,
                --
                charged_from_t, charged_to_t,
                cycle_fee_start_t, cycle_fee_end_t,
                unit, count
                ) VALUES (
		account_id0, curr_rec_id, curr_rec_id,
                --
                pr_charge_from,pr_charge_to,
                pr_create_t, pr_end_t,
                0,1
                );

		INSERT INTO account_products_t (
		obj_id0, rec_id,
		--
		service_obj_db, service_obj_id0, service_obj_type,
		product_obj_db, product_obj_id0, product_obj_type,
		sponsor_obj_db, sponsor_obj_id0, sponsor_obj_type,
		quantity,
		deal_obj_db, deal_obj_id0, deal_obj_type,
		plan_obj_db, plan_obj_id0, plan_obj_type,
		created_t,
		--
		purchase_start_t, purchase_end_t, purchase_discount,
		cycle_start_t, cycle_end_t, cycle_disc_amt,
		usage_start_t, usage_end_t, usage_discount,
		flags, status, status_flags,
		node_location, cycle_fee_flags
		) VALUES (
		account_id0, curr_rec_id,
		--
		l_info.db_id, service_id1, service_type,
		l_info.db_id, prod_id, '/product',
		0,0,'',
		1,
		l_info.db_id, deal_id, '/deal',
		l_info.db_id, plan_id,  '/plan',
		v_create_t,
		--
		v_create_t, 0, 0,
		v_create_t, 0, 0,
		v_create_t, 0, 0,
		2, 1, 0,
		'0:0',pr_flag
		);



		IF (commit_cnt = l_info.commit_freq) THEN
			commit_cnt := 0;
			commit;
		END IF;
		
			commit_cnt := commit_cnt + 1;
	      END LOOP;
		login0 := login0 + 1;
	END LOOP;

		commit;
	END insert_products;
END sess_load_db;
/

ENDSQL
;

exec_sqlcommand('pin',$CONF_DBNAME,$sqlcommand);
${start_log_no} = $CONF_BEG_ID0;

$currtime0 = time();

$currtime1 = time();

$current_thread=$CONF_NUM_THREADS;

while ( $current_thread > 0 ) {
#--------------------------------------
$sqlcmnd_array[$current_thread] =<<SQLPLUSEND 
DECLARE
mysessinfo	sess_load_db.SessInfoTyp;
service_type VARCHAR2(255);
deal INTEGER;
counts INTEGER;
product INTEGER;
num_products INTEGER;
permitted VARCHAR2(255);

-- 
-- set up cursors to fetch some of the configuration stuff from the database.
--
-- Get the DB no
cursor db_id is 
	select poid_db from account_t 
		where poid_id0 = 1;

BEGIN
	-- (CONFIGURE) -- number of accounts
	mysessinfo.num_acnt 	:= ${NUM_ACCOUNTS};
	-- (CONFIGURE) -- number of products
	mysessinfo.num_products 	:= ${NUM_PRODUCTS};

	-- db no
	open db_id;
	fetch db_id into mysessinfo.db_id;
	close db_id;

	mysessinfo.login_num	:= ${start_log_no};

	-- (CONFIGURE) commit frequency
	mysessinfo.commit_freq 	:= ${CONF_COMMIT_FREQ};

	-- (CONFIGURE) print debug info
	mysessinfo.debug	:= ${CONF_DEBUG};

	-- (CONFIGURE) current time in unix time format
	mysessinfo.create_t	:= ${CONF_CREATE_T};

	-- Call insert_products to actually populate products
	--
	sess_load_db.insert_products(mysessinfo);


END;
/

SQLPLUSEND
;
$current_thread=$current_thread - 1;
$start_log_no=$start_log_no + $NUM_ACCOUNTS;
# end of while
}

#  end of while
##################################################
$current_thread = 1;
while ( $current_thread <= $CONF_NUM_THREADS )
{
if ( $^O =~ /win/i )
{
# special code for Windows 
	exec_sqlcommand('pin',$CONF_DBNAME,$sqlcmnd_array[$current_thread]);
	print $sqlout;
}
else
{
$procid[$current_thread] = fork();
#--------------------------------------
#  child process
#--------------------------------------
if ( $procid[$current_thread] == 0 ) {
	exec_sqlcommand('pin',$CONF_DBNAME,$sqlcmnd_array[$current_thread]);

print $sqlout;
exit;    # this terminates child process
}
# this is a parent process
}

$current_thread=$current_thread + 1;
}
if (!( $^O =~ /win/i ))
{
#
# waiting while all processes were completed
#
$current_thread = 1;
while ( $current_thread <= $CONF_NUM_THREADS )
 {
  waitpid ($procid[$current_thread], 0 );
  $current_thread=$current_thread + 1;
 }
}
$currtime2 = time();
$elapstime = $currtime2 - $currtime1;
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
$accounts = $NUM_ACCOUNTS * $CONF_NUM_THREADS;
$products = $NUM_PRODUCTS;
print "***************************************************************\n";
printf " $accounts accounts  were populated with $products in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
print "***************************************************************\n";

1;



