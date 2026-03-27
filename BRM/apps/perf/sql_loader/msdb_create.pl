#
#	@(#) % %
#       
#       Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#

require "../ms_conf.pm";
######################################################################
## Configuration stuff
######################################################################

$CONF_BEG_ID0=100000;   # starting number for login
$CONF_NUM_THREADS=1;      # how many parallel processes we are going to use
$BRAND_LOGIN = "'root.0.0.0.1'"; # login root.0.0.0.1 is for no brand
$BRAND_PERMISSION = "'L'";

$CONF_COMMIT_FREQ=10;

$CONF_DEBUG=false;
$CONF_COMMIT_FREQ=10;
$FREE_TIME=0;         # free time in hours
#############################
# below is parameters structure
# 1)plan;
# 2)number accounts to create per thread;
# 3)type:invoice = 0, cc = 1
# 4) GL segment
############################
@ACCOUNTS= (
	"'Bench_Basic'" , 300, 0,"'.'",
	"'Bench_Power'" , 50, 0,"'.'",
	"'Bench_Power'" , 200, 1,"'Portal'",
	  );

#---------------------------------------------------------------------
# pinaft outputs create_t (today), actg_next_t, actg_future_t and 
# actg_dom. Note that if today is 29-31 then actg_dom, actg_next_t and 
# actg_future_t will be auto adjusted to 1st.
#---------------------------------------------------------------------
$PINAFT_OUTPUT=`./pinaft`;
($CONF_CREATE_T,$CONF_ACTG_DOM,$CONF_ACTG_NEXT_T,$CONF_ACTG_FUTURE_T,
   $CONF_DATE_STRG ) = split (' ',$PINAFT_OUTPUT,99);

$CONF_DATE_STR="'$CONF_DATE_STRG'";
$CONF_DEBUG=0;
#--------------------------------------------
# end of configuration section
#--------------------------------------------
#=============================================================================
# Temporary directory to create files
$PIN_CONF_TEMPDIR     = "C:\\temp";

# create procedure to load accounts
`isql -U $CONF_OWNER -P $CONF_PASSWD -d $CONF_DBNAME -S $CONF_SERVER -i ms_ldacnts.sql -o outfile1`;

${start_log_no} = $CONF_BEG_ID0;

$currtime0 = time();

$index = 0;
$total_num_accnts= 0;
while ( $index < @ACCOUNTS ) {

$currtime1 = time();
$plan = @ACCOUNTS[$index];
$num_accounts = @ACCOUNTS[$index+1];
$account_type = @ACCOUNTS[$index+2];
$gl_segment   = @ACCOUNTS[$index+3];

$index = $index +4;

#--------------------------------------
$sqlcmnd_array =<<SQLPLUSEND 
DECLARE \@num_accnt int, \@db_id int, \@beg_id0 int
DECLARE \@commit_freq int , \@debug int
DECLARE \@login_num int , \@num_services int
DECLARE \@date_str char(60)
DECLARE \@gl_segm char(60)
DECLARE \@create_t int , \@actg_next_t int, \@actg_future_t int
DECLARE \@actg_cycle int, \@cc int ,\@free_time int
DECLARE \@deal1_id0 int, \@deal2_id0 int, \@deal3_id0 int, \@deal4_id0 int
DECLARE \@plan_id0 int
DECLARE \@prd1_id0 int, \@prd2_id0 int, \@prd3_id0 int, \@prd4_id0 int
DECLARE \@service1 char(60), \@service2 char(60),\@service3 char(60),\@service4 char(60)
DECLARE \@serv_type1 char(60), \@serv_type2 char(60)
DECLARE \@serv_type3 char(60),\@serv_type4 char(60)

DECLARE \@deal int, \@counts int
DECLARE \@product int, \@num_products int
DECLARE \@group_poid int, \@brand_id0 int, \@rec_id int
DECLARE \@brand_perm char(2)
DECLARE \@permitted char(100)
DECLARE \@service_type char(100)
--
-- set up cursors to fetch some of the configuration stuff from the database.
--
-- Get the DB no
declare db_id cursor for 
	select poid_db from account_t 
		where poid_id0 = 1
-- Get the plan id for, say, 'Power' plan
declare  plan_id0 cursor for 
	select poid_id0 from plan_t 
		where name = $plan 

declare db_seq cursor for 
	select max(poid_id0) from poid_ids

-- get brand information from group table
declare  brand_c cursor for 
	select g.account_obj_id0,g.poid_id0 from group_t g, service_t s
	  where s.login = $BRAND_LOGIN and s.poid_type = '/service/admin_client'
            and s.account_obj_id0 = g.account_obj_id0 and 
                  g.account_obj_id0=g.parent_id0 

	-- (CONFIGURE) -- number of accounts
	set \@num_accnt 	= $num_accounts

	-- db no
	open db_id
	fetch next from db_id into \@db_id
	close db_id
	deallocate db_id

        print ' got db_id = ' + CONVERT(char(10),\@db_id)
	set \@login_num	= ${start_log_no}
	open db_seq
	fetch next from db_seq into \@beg_id0
	close db_seq
	deallocate db_seq

        -- get branding information
	open brand_c
	fetch next from brand_c into \@brand_id0, \@group_poid
	close brand_c
	deallocate brand_c
        set \@brand_perm = ${BRAND_PERMISSION}
	IF ( \@brand_id0 > \@beg_id0 )
	BEGIN
		set \@beg_id0 = \@brand_id0 + 10000
	END
	BEGIN
-- get max number of billing group
declare  group_c cursor for 
        select max(rec_id) from group_billing_members_t where obj_id0 = \@group_poid

	open group_c
	fetch next from group_c into \@rec_id
	close group_c
	deallocate group_c
	set \@rec_id = \@rec_id + 1
	END

	-- (CONFIGURE) commit frequency
	set  \@commit_freq 	= ${CONF_COMMIT_FREQ}

	-- (CONFIGURE) print debug info
	set   \@debug	= ${CONF_DEBUG}

	-- (CONFIGURE) current time in unix time format
	set     \@create_t	= ${CONF_CREATE_T}

	--  next time accouting should run (usually a month from now)

	set    \@actg_next_t	= ${CONF_ACTG_NEXT_T}

	-- (CONFIGURE) a month from actg_next_t (for example Sept 5 midnight)
	set   \@actg_future_t	= ${CONF_ACTG_FUTURE_T}

	-- (CONFIGURE) day on which accounting is done (For example, 5)
	set \@actg_cycle	= ${CONF_ACTG_DOM}

	-- (CONFIGURE) creditcard/invoice account?
	set \@cc		= $account_type

	-- (CONFIGURE) free time per account
	set \@free_time		= ${FREE_TIME} * (-1)

	-- (CONFIGURE) AUTH date used for the cc payment event
	set \@date_str	=  ${CONF_DATE_STR}

	-- (CONFIGURE) AUTH date used for the cc payment event
	set \@gl_segm	=  ${gl_segment}

        set \@deal1_id0 = 0
        set \@deal2_id0 = 0
        set \@deal3_id0 = 0
        set \@deal4_id0 = 0
 
	-- Use the defined cursors to fetch the plan/deal/product ids.
	open plan_id0
	fetch next from plan_id0 into \@plan_id0
	close plan_id0
	deallocate plan_id0

        print ' got plan_id0 = ' + CONVERT(char(10),\@plan_id0)

      IF ( \@plan_id0 != 0 )
      BEGIN
-- Get the deal,services using plan
	declare service_id0 cursor for 
        	select deal_obj_id0,service_obj_type from plan_services_t
			where obj_id0 = \@plan_id0
	open service_id0
	set \@num_products = 1
	set \@counts = 1
	set \@num_services = 0
	fetch next from service_id0 into \@deal,\@service_type
	WHILE ( \@counts < 5 AND \@\@FETCH_STATUS = 0 )
	BEGIN
-- Get the product     using deal
		declare deal_id0 cursor for 
			select product_obj_id0 from deal_products_t
				where obj_id0 = \@deal
		set \@num_services = \@counts
		open deal_id0
		fetch next from deal_id0 into \@product
		while ( \@num_products < 5 AND \@\@FETCH_STATUS = 0)
		BEGIN
-- Get the service assigned
			declare prod_id0 cursor for 
				select permitted from product_t
					where poid_id0 = \@product
			set \@permitted = '?'
			open prod_id0
			fetch next from prod_id0 into \@permitted
			close prod_id0
			deallocate prod_id0
		IF ( \@service_type = \@permitted )
		BEGIN
		    IF ( \@num_products = 1 )
		    BEGIN
			set \@prd1_id0 = \@product
			set \@service1 = \@service_type
			set \@deal1_id0 = \@deal
		    END
		    IF ( \@num_products = 2 )
		    BEGIN
			set \@prd2_id0 = \@product
			set \@service2 = \@service_type
			set \@deal2_id0 = \@deal
		    END
		    IF ( \@num_products = 3 )
		    BEGIN
			set \@prd3_id0 = \@product
			set \@service3 = \@service_type
			set \@deal3_id0 = \@deal
		    END
		    IF ( \@num_products = 4 )
		    BEGIN
			set \@prd4_id0 = \@product
			set \@service4 = \@service_type
			set \@deal4_id0 = \@deal
		    END
		    IF ( \@counts = 1 )
		    BEGIN
			set \@serv_type1 = \@service_type
		    END
		    IF ( \@counts = 2 )
		    BEGIN
			set \@serv_type2 = \@service_type
		    END
		    IF ( \@counts = 3 )
		    BEGIN
			set \@serv_type3 = \@service_type
		    END
		    IF ( \@counts = 4 )
		    BEGIN
			set \@serv_type4 = \@service_type
		    END
		    set \@num_products = \@num_products + 1
		 END
		fetch next from deal_id0 into \@product
		END   -- end of while loop by products
		set \@counts = \@counts + 1
	        fetch next from service_id0 into \@deal,\@service_type
		close deal_id0
		deallocate deal_id0
	END      -- end of while by services
	close service_id0 
	deallocate service_id0
      END   -- if plan exists?
	--
	-- Call insert_accounts to actually create the accounts
	--
	EXEC 	insert_accounts    \@num_accnt, \@db_id,\@beg_id0,
			\@login_num, \@num_services,
			\@commit_freq, \@debug,
				--
			\@date_str, \@gl_segm, \@create_t, \@actg_next_t,
			\@actg_future_t, \@actg_cycle, \@cc, \@free_time,
			\@plan_id0,
				--
			\@group_poid,\@brand_id0,\@rec_id,\@brand_perm,
				--
			\@deal1_id0, \@deal2_id0, \@deal3_id0,\@deal4_id0,
			\@service1, \@service2, \@service3,\@service4,
			\@serv_type1, \@serv_type2, \@serv_type3,\@serv_type4,
			\@prd1_id0, \@prd2_id0,\@prd3_id0, \@prd4_id0
	go
	-- adjusting sequence number
	--
	DECLARE \@new_value int
	DECLARE \@new_value1 int
	declare cursor2 cursor for
		select max(poid_id0)+10000 from event_t
	declare cursor1 cursor for
		select max(poid_id0)+10000 from service_t

        OPEN cursor1
	FETCH NEXT FROM cursor1 
	INTO \@new_value
        CLOSE cursor1
	DEALLOCATE cursor1

        OPEN cursor2
	FETCH NEXT FROM cursor2 
	INTO \@new_value1
        CLOSE cursor2
	DEALLOCATE cursor2

        if ( \@new_value1 > \@new_value )
	BEGIN
	   set \@new_value = \@new_value1
	END

	SET IDENTITY_INSERT $CONF_DBNAME.dbo.poid_ids ON
	INSERT into POID_IDS ( poid_id0, text ) values (\@new_value, 'INFRANET')
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
$accounts = $num_accounts ;
$total_num_accnts = $total_num_accnts + $accounts;
print "***************************************************************\n";
printf " $accounts accounts  plan $plan were created in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
	   print "***************************************************************\n";
# go to the next plan from config array
}

$currtime2 = time();
$elapstime = $currtime2 - $currtime0;
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
$accounts = $total_num_accnts;
print "***************************************************************\n";
printf " $accounts accounts were created in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
print "***************************************************************\n";


1;

