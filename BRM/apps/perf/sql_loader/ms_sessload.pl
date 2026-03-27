#!/usr/local/bin/perl
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
require "../ms_conf.pm";
######################################################################
## Configuration stuff
######################################################################
$CONF_BEG_ID0=200096;   # starting number for login 
$CONF_NUM_THREADS=1;      # how many parallel processes we are going to use
$NUM_ACCOUNTS=4;    # num accounts to process per thread
$NUM_EVENTS= 10;		# num events per account

$CONF_DEBUG=0;   # false
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
if EXISTS ( select name from sysobjects
        where name = 'insert_sessions' AND type = 'P' )
        DROP procedure insert_sessions
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE insert_sessions
        \@num_accnt int,
        \@db_id int, \@beg_id0 int,
        \@commit_freq int , \@debug int,
        \@login_num int, \@num_events int, \@create_t int
AS

                -- Account number being created. (1 <= CUR_ACNT <= NUM_ACNT)
                DECLARE \@cur_acnt       int
                DECLARE \@cur_event       int
                DECLARE \@commit_cnt     int

                -- Current account's info
                DECLARE \@account_id0 int
                DECLARE \@login0 int
                DECLARE \@amount float
                DECLARE \@login1 char(60)
                DECLARE \@invoice_descr varchar(500)
                DECLARE \@invoice_descr1 varchar
                DECLARE \@event_id0 int
                DECLARE \@service_id0 int
                DECLARE \@item_id0 int

	BEGIN
			
		select \@commit_cnt = 0
		SELECT \@cur_acnt   = 0
		SELECT \@login0 = \@login_num;
		SELECT \@event_id0 = \@beg_id0

	WHILE \@cur_acnt < \@num_accnt
        BEGIN

	--
	-- read account information
	--
		set \@login1 = 'user' + CONVERT(char(60),\@login0)
            BEGIN
	    declare service cursor for
        	select poid_id0 , account_obj_id0 from service_t
        	   where login = \@login1

		open service
		fetch next from service into \@service_id0, \@account_id0
		close service
	 	deallocate service
             END
            BEGIN
            declare item cursor for
                select i.poid_id0  from item_t i, account_t a
                   where a.poid_id0 = \@account_id0 and i.bill_obj_id0 =
                   a.bill_obj_id0 and i.poid_type = '/item/misc';

        	select poid_id0  from item_t
        	   where account_obj_id0 = \@account_id0 and
		   poid_type = '/item/misc'

		open item
		fetch next from item into \@item_id0
		close item
	 	deallocate item
             END

                set \@amount = ( 1 + \@num_events) * \@num_events * 0.05;

		UPDATE item_t SET
		due = due + \@amount,
		item_total = item_total + \@amount
		WHERE
		poid_id0 = \@item_id0;

		UPDATE account_balances_t SET
		current_bal = current_bal + \@amount
		WHERE
		obj_id0 = \@account_id0 AND
		rec_id = 840;

		SELECT \@cur_event   = 0
	WHILE \@cur_event < \@num_events
        BEGIN

                select \@amount = \@cur_event * 0.1

		set \@invoice_descr = '0 256 9 0' + CAST(0x0A0D as varchar) +
                        '1 834 1 0 840' + CAST(0x0A0D as varchar) +
			'1 58 14 0 19740.0' + CAST(0x0A0D as varchar) +
			'1 1206 5 0 "' +
			CONVERT(varchar, 'IP Dialup Session"')+ 
			CAST(0x0A0D as varchar) +
			'1 107 7 0 0.0.0.' + CONVERT(char(2),\@db_id)
			 + ' /item/misc ' + CONVERT(varchar,\@item_id0) + 
			' 0' + CAST(0x0A0D as varchar) +
			'1 57 14 0 ' + CONVERT(varchar,\@amount)

		INSERT INTO event_t (
		poid_db, poid_id0, poid_type, poid_rev,
		name, created_t, mod_t, 
		--
		account_obj_db, account_obj_id0, account_obj_type, 
		descr, end_t, event_no, flags,
		--
		group_obj_db, group_obj_id0, group_obj_type, 
		item_obj_db, item_obj_id0, item_obj_type, 
		program_name,
		provider_id_db, provider_id_id0, provider_id_type, 
		service_obj_db, service_obj_id0, service_obj_type, 
		session_obj_db, session_obj_id0, session_obj_type, 
		--
		invoice_data,
		--
		currency, tax_locales,
		start_t, sys_descr, 
		userid_db, userid_id0, userid_type
		) VALUES (
		\@db_id, \@event_id0, '/event/session/dialup', 1, 
		'Dialup Event', \@create_t, \@create_t, 
		--
		\@db_id, \@account_id0, '/account',
		'usage', \@create_t, '', 0,
		--
		0, 0, '',
		\@db_id, \@item_id0, '/item/misc',
		'Automatic Session Creation', 
		0, 0, '',
		\@db_id, \@service_id0, '/service/ip',
		0, 0, '',
		--
		\@invoice_descr,
		--
		840,'',
		\@create_t, 'Session - Dialup',
		\@db_id, 1, '/service/pcm_client'
		);

		INSERT INTO event_total_t (
		obj_id0, rec_id,amount
		) VALUES (
		\@event_id0,840, \@amount 
		);

		INSERT INTO event_session_dialup_t (
		obj_id0, bytes_in,bytes_out,
		trans_id,ipaddr,login,
		--
		PACKETS_IN,PACKETS_OUT,
		SPEED,status,TERMSERV_ID,TERMSERV_PORT,
		timezone,type
		) VALUES (
		\@event_id0,1200, 1500,
		\@login1, 0x00, \@login1,
		--
		140,150,
		0,1,'0.0.0.1','',
		0,0
		);

		INSERT INTO event_bal_impacts_t (
		obj_id0, rec_id,
		--
		account_obj_db,account_obj_id0,account_obj_type,
		--
		amount,amount_deferred,discount,
		gl_id,impact_type,
		--
		item_obj_db,item_obj_id0,item_obj_type,
		--
		"percent", quantity,
		rate_obj_db,rate_obj_id0,rate_obj_type,
		--
		rate_tag,resource_id,
		tax_code,impact_category,node_location
		) VALUES (
		\@event_id0,0, 
		--
		\@db_id, \@account_id0, '/account',
		--
		\@amount,0,0,
		104,1,
		--
		\@db_id, \@item_id0, '/item/misc',
		--
		0,0,
		0,0,'',
		--
		'IP Async Dialup Session',840,
		'','default','0:0'
		);

			SELECT \@event_id0 = \@event_id0 + 1
			SELECT \@cur_event = \@cur_event + 1
	      END -- event loop
		select \@login0 = \@login0 + 1
		SELECT \@cur_acnt = \@cur_acnt + 1
	END -- accounts loop
      END

GO

ENDSQL
;

##################################################
        open(OFILE, ">exfile") || die "$ME: cannot open $exfile\n";
        printf OFILE "%s", $sqlcommand;
        close(OFILE);

##################################################
#  execute prepared file
#################################################
`isql -U $CONF_OWNER -P $CONF_PASSWD -d $CONF_DBNAME -S $CONF_SERVER -i exfile -o outfile`;

${start_log_no} = $CONF_BEG_ID0;

$currtime0 = time();

$currtime1 = time();

#--------------------------------------
$sqlcmnd_array =<<SQLPLUSEND 
DECLARE \@num_accnt int, \@db_id	int, \@beg_id0 int
DECLARE \@commit_freq int , \@debug int
DECLARE \@create_t int , \@num_events int, \@login_num int

-- 
-- set up cursors to fetch some of the configuration stuff from the database.
--
-- Get the DB no
declare db_id cursor for
        select poid_db from account_t
                where poid_id0 = 1

declare db_seq cursor for
        select max(poid_id0) from poid_ids

	-- (CONFIGURE) -- number of accounts
	set \@num_accnt 	= ${NUM_ACCOUNTS}
	-- (CONFIGURE) -- number of events
	set \@num_events 	= ${NUM_EVENTS}

	-- db no
	open db_id
	fetch next from db_id into \@db_id
	close db_id
	deallocate db_id

	set \@login_num	= ${start_log_no}

        open db_seq
	fetch next from db_seq into \@beg_id0
	close db_seq
	deallocate db_seq

	-- (CONFIGURE) commit frequency
	set \@commit_freq 	= ${CONF_COMMIT_FREQ}

	-- (CONFIGURE) print debug info
	set \@debug	= ${CONF_DEBUG}

	-- (CONFIGURE) current time in unix time format
	set \@create_t	= ${CONF_CREATE_T}

	-- Call insert_sessions to actually populate events
	
	EXEC      insert_sessions \@num_accnt, \@db_id,\@beg_id0,
				\@commit_freq, \@debug,
				--
				\@login_num, \@num_events, \@create_t

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

	SET IDENTITY_INSERT poid_ids ON
	INSERT into POID_IDS ( poid_id0, text ) values (\@new_value, 'INFRANET')
	go

SQLPLUSEND
;
##################################################
        open(OFILE, ">exfile1") || die "$ME: cannot open $exfile\n";
        printf OFILE "%s", $sqlcmnd_array;
        close(OFILE);

##################################################
#  execute prepared file
#################################################
`isql -U $CONF_OWNER -P $CONF_PASSWD -d $CONF_DBNAME -S $CONF_SERVER -i exfile1 -o outfile1`;

$currtime2 = time();
$elapstime = $currtime2 - $currtime1;
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
$accounts = $NUM_ACCOUNTS;
$events = $NUM_EVENTS;
print "***************************************************************\n";
printf " $accounts accounts  were populated with $events in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
print "***************************************************************\n";

1;

