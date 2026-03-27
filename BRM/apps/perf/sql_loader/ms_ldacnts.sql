--
--	@(#) % %
--      
--      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
--      
--      This material is the confidential property of Oracle Corporation or its
--      licensors and may be used, reproduced, stored or transmitted only in
--      accordance with a valid Oracle license or sublicense agreement.
--

if EXISTS ( select name from sysobjects
	where name = 'insert_accounts' AND type = 'P' )
	DROP procedure insert_accounts
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE insert_accounts
	@num_accnt int,
	@db_id int, @beg_id0 int,
	@login_num int, @num_services int,
	@commit_freq int , @debug int,
	--
	@date_str char(60),
	@gl_segm char(60),
	@create_t int , @actg_next_t int, @actg_future_t int,
	@actg_cycle int, @cc int, @free_time int,
	@plan_id0 int, 
        --
        @group_poid int,@brand_id0 int,@rec_id int,@brand_perm char(2),
        --
	@deal1_id0 int, @deal2_id0 int,@deal3_id0 int, @deal4_id0 int,
	@service1 char(60), @service2 char(60),
	@service3 char(60),@service4 char(60),
	@serv_type1 char(60), @serv_type2 char(60),
	@serv_type3 char(60),@serv_type4 char(60),
	@prd1_id0 int, @prd2_id0 int,@prd3_id0 int, @prd4_id0 int
AS

		-- Account number being created. (1 <= CUR_ACNT <= NUM_ACNT)
		DECLARE @cur_acnt	int
		DECLARE @commit_cnt	int
		
		-- Current account's info
		DECLARE @acnt_id0 int
		DECLARE @login0 int
		DECLARE @bill_id0 int
		DECLARE @actg_id0 int
		DECLARE @item_id0 int
		DECLARE @item2_id0 int
		DECLARE @pay_id0	 int
		DECLARE @ebpc_id0 int
		DECLARE @ebcc_id0 int
		DECLARE @srv1_id0 int

		DECLARE @cc_code int
		DECLARE @cc_string char(60)
		DECLARE @service_cnt int
		DECLARE @service_id int
		DECLARE @deal_id int
		DECLARE @prod_id int
		DECLARE @flag int
		DECLARE @service_type char(60)
		DECLARE @login_name char(60)
		DECLARE @password char(60)
		DECLARE @lineage char(100)
		DECLARE @rec_num int
	BEGIN
		-----------------------------------------------------------
		-- Initialize variables
		-----------------------------------------------------------
		
		SELECT @acnt_id0	= @beg_id0
		SELECT @login0		= @login_num
		SELECT @bill_id0	= @beg_id0
		SELECT @actg_id0	= @beg_id0
		SELECT @item_id0	= @beg_id0 + @num_accnt
		SELECT @item2_id0 	= @item_id0 + @num_accnt
		SELECT @pay_id0		= @beg_id0
		SELECT @ebpc_id0	= @beg_id0 + @num_accnt
		SELECT @ebcc_id0	= @item_id0 + @num_accnt
		SELECT @srv1_id0	= @beg_id0 + @num_accnt

		SELECT @cur_acnt   = 0
		SELECT @rec_num   = @rec_id

		IF (@cc = 1)
		 BEGIN
		  SET @cc_string = '/payinfo/cc'
		  SET @cc_code = 10003
		 END
		ELSE
		 BEGIN
		  SET @cc_string = '/payinfo/invoice'
		  SET @cc_code = 10001
		 END

               -- update count of children for branded accounts
		IF (@brand_id0 <> 1)
		 BEGIN
			update group_t set "count" = "count" +  @num_accnt where poid_id0 = @group_poid
		 END

		-- This is a loop to create given number of accounts

             WHILE @cur_acnt < @num_accnt
	     BEGIN

                SET @lineage = '/0.0.0.' + CONVERT(varchar,@db_id) + ':'+
                            CONVERT(varchar,@brand_id0) + 'B/0.0.0.' +
                            CONVERT(varchar,@db_id) + ':' +
                            CONVERT(varchar,@acnt_id0) + '/'

		INSERT INTO account_t  (
		poid_db, poid_id0, poid_type, poid_rev, 
		name, created_t, mod_t, 
		--
		aac_access, aac_source, aac_vendor, aac_package, 
		aac_promo_code, aac_serial_num, 
		status, status_flags, last_status_t, close_when_t, 
		laststat_cmnt, account_no, merchant, bill_mode, 
		bill_type,gl_segment, 
		--
                read_access, write_access,
                lineage, attribute,
		--
		parent_db, parent_id0, parent_type, 
		group_obj_db, group_obj_id0, group_obj_type, 
		next_bill_t, last_bill_t, 
		last_bill_obj_db, last_bill_obj_id0, last_bill_obj_type, 
		--
		actg_type, actg_next_t, actg_last_t, actg_cycle_dom, 
		actg_future_t, bill_actgcycles_left, 
		item_poid_list,
		bill_obj_db, bill_obj_id0, bill_obj_type, 
		payinfo_obj_db, payinfo_obj_id0, 
		payinfo_obj_type, 
		--
		brand_obj_db, brand_obj_id0, brand_obj_type, brand_obj_rev,
		--
		pending_recv, currency, bill_when, 
		access_code1, access_code2, internal_notes_size, locale 
		) VALUES (
		@db_id, @acnt_id0, '/account', 1,
		'Pin Account', @create_t, @create_t, 
		--
		'', '', '', '', 
		'', '',
		10100, 0, @create_t, 0, 
		'', '0.0.0.' + CONVERT(char(2),@db_id) + '-' + ltrim(rtrim(CONVERT(char(25),@acnt_id0))), 'test', '',
		@cc_code,@gl_segm,
		--
		@brand_perm,@brand_perm,
		@lineage, 0, 
		--
		0, 0, '',
		0, 0, '',
		@actg_next_t, @create_t,
		0, 0, '',
		--
		2, @actg_next_t, @create_t, @actg_cycle, 
		@actg_future_t, 1, 
		'0.0.0.' + CONVERT(char(2),@db_id) + '|/item/misc ' +  ltrim(rtrim(CONVERT(char(25),@item_id0))) + ' 0',
		@db_id, @bill_id0, '/bill',
		@db_id, @pay_id0, 
		@cc_string,
		--
		@db_id, @brand_id0, '/account',0,
		--
		0, 840, 1, 
		'', '', 0, 'en_US'
		);


		INSERT INTO account_nameinfo_t  (
		obj_id0, rec_id,
		--
		service_obj_db, service_obj_id0, service_obj_type, 
		--
		salutation, last_name, last_canon, first_name, first_canon, 
		middle_name, middle_canon, title, company, canon_company,
		--
		address, city, state, zip, country, 
		email_addr, contact_type
		) VALUES (
		@acnt_id0, 1, 
		--
		0, 0, '', 
		--
		'', @acnt_id0, @acnt_id0, '', '', 
		'', '', '', 'Portal', '',
		--
		'401 Stevens Blvd', 'Cupertino', 'CA', '95014', 'USA',
		'someone@nowhere.com', ''
		);
		
		INSERT INTO account_balances_t (
		obj_id0, rec_id,
		--
		open_bal, current_bal, credit_limit,flags,
		credit_thresholds, credit_floor, next_bal
		) VALUES (
		@acnt_id0, 840,0, 
		--
		19.95, 1000000, 100, 
		0, 0, 0
		);
		
	    if ( @service_cnt = 1 )
	    BEGIN
		INSERT INTO account_balances_t (
		obj_id0, rec_id,
		--
		open_bal, current_bal, credit_limit,flags,
		credit_thresholds, credit_floor
		) VALUES (
		@acnt_id0, 1000001,0, 
		--
		@free_time, 0, 0, 
		0, 0
		);
	    END
		
		INSERT INTO bill_t (
		poid_db, poid_id0, poid_type, poid_rev, name, 
		created_t, mod_t, bill_no, 
		--
		account_obj_db, account_obj_id0, account_obj_type, 
		invoice_obj_db, invoice_obj_id0, invoice_obj_type, 
		parent_db, parent_id0, parent_type, 
		--
                read_access, write_access,
		--
		start_t, end_t, currency, 
		previous_total, subords_total, current_total, total_due 
		) VALUES (
		@db_id, @bill_id0, '/bill', 1, 'PIN Bill',
		@create_t, @create_t, '',
		--
		@db_id, @acnt_id0, '/account',
		@db_id, 0, '/invoice',
		0, 0, '',
		--
		@brand_perm,@brand_perm,
		--
		@create_t, 0, 840,
		0, 0, 0, 0
		);


		INSERT INTO item_t (
		poid_db, poid_id0, poid_type, poid_rev, name, 
		created_t, mod_t,gl_segment,
		--
		effective_t, closed_t, status,
		--
		account_obj_db, account_obj_id0, account_obj_type, 
		bill_obj_db, bill_obj_id0, bill_obj_type, 
		--
		currency, item_total, due, disputed, recvd, adjusted, 
		transfered, writeoff,
		--
                read_access, write_access,
		--
		ar_account_obj_db, ar_account_obj_id0, ar_account_obj_type,
		ar_bill_obj_db, ar_bill_obj_id0, ar_bill_obj_type,
		due_t, item_no
		) VALUES (
		@db_id, @item_id0, ltrim(rtrim('/item/misc')), 1, 'Usage',
		@create_t, @create_t,@gl_segm,
		--
		0, 0, 1,
		--
		@db_id, @acnt_id0, '/account',
		@db_id, @bill_id0, '/bill',
		--
		840, 0, 0, 0, 0, 0, 
		0,0,
		--
		@brand_perm,@brand_perm,
		--
		@db_id, @acnt_id0, '/account',
		@db_id, @bill_id0, '/bill',
		0, '');

	        set @service_cnt = 1

	     while ( @service_cnt <= @num_services )
	     BEGIN
		if ( @service_cnt = 1 )
		BEGIN
		    set @service_type = @serv_type1
		    set @service_id = @srv1_id0
	        END 
		if ( @service_cnt = 2 )
		BEGIN
		    set @service_type = @serv_type2
		    set @service_id = @srv1_id0 + @num_accnt
	        END 
		if ( @service_cnt = 3 )
		BEGIN
		    set @service_type = @serv_type3
		    set @service_id = @srv1_id0 + ( 2 * @num_accnt)
	        END 
		if ( @service_cnt = 4 )
		BEGIN
		    set @service_type = @serv_type4
		    set @service_id = @srv1_id0 + ( 3 * @num_accnt)
	        END 

		if ( @service_type = '/service/email' )
		BEGIN
	            set @login_name =  ltrim(rtrim(CONVERT(char(60),@login0))) + '@portal.com'
		    set @password = 'md5|5f4dcc3b5aa765d61d8327deb882cf99'
		END
	        ELSE 
		BEGIN
		    set @login_name = 'user' + ltrim(rtrim( CONVERT(char(60),@login0)))
		    set @password = 'clear|password'
	        END 
		
		INSERT INTO service_t (
		poid_db, poid_id0, poid_type, poid_rev, 
		name, created_t, mod_t, 
		--
		account_obj_db, account_obj_id0, account_obj_type, 
		login, passwd, 
		--
		aac_access, aac_source, aac_vendor, aac_package, 
		aac_promo_code, aac_serial_num, 
		--
                read_access, write_access,
		--
		status, status_flags, last_status_t, close_when_t, 
		laststat_cmnt 
		) VALUES (
		@db_id, @service_id, ltrim(rtrim(@service_type)), 1, 
		'PIN Service', @create_t, @create_t,
		--
		@db_id, @acnt_id0, '/account',
		ltrim(rtrim(@login_name)), ltrim(rtrim(@password)),
		--
		'', '', '', '', 
		'', '',
		--
		@brand_perm,@brand_perm,
		--
		10100, 0, @create_t, 0, 
		''
		);
		-- included here just for debug purposes
		--INSERT INTO uniqueness_t (
		--poid_db, poid_id0, poid_type, poid_rev,
		--created_t, mod_t,
		----
		--account_obj_db, account_obj_id0, account_obj_type,
		--service_obj_db, service_obj_id0, service_obj_type,
		----
		--read_access, write_access,
		--login, status, account_no
		--) VALUES (
		--@db_id, @service_id, '/uniqueness', 1,
		--@create_t, @create_t,
		----
                --@db_id, @acnt_id0, '/account',
		--@db_id, @service_id, @service_type,
		----
		--'G','S',
		--@login_name,2,
		--'0.0.0.' + CONVERT(char(2),@db_id) + '-' + CONVERT(char(25),@acnt_id0)
		--);

            if ( @service_type = '/service/ip' ) 
	    BEGIN
		INSERT INTO service_ip_t (
		obj_id0, 
		--
		protocol, compression, ipaddr
		) VALUES (
		@service_id, 
		--
		0, 0, 0x00);
	    END
            if ( @service_type = '/service/broadband' ) 
	    BEGIN
		INSERT INTO service_broadband_t (
		obj_id0, 
		--
		event_obj_db, event_obj_id0, event_obj_type
		) VALUES (
		@service_id, 
		--
		0, 0, '');
	    END
            if ( @service_type = '/service/vpdn' ) 
	    BEGIN
		INSERT INTO service_vpdn_t (
		obj_id0, 
		--
		protocol, compression, ipaddr
		) VALUES (
		@service_id, 
		--
		0, 0, 0x00);
	    END
            if ( @service_type = '/service/email' ) 
	    BEGIN
		INSERT INTO service_email_t (
		obj_id0, 
		--
		mail_server_id, max_mbox_size, max_msg_size, max_msg_cnt, 
		path
		) VALUES (
		@service_id,
		--
		0, 0, 0, 0, 
		''
		)
	    END

            if ( @service_type = '/service/telephony' ) 
	    BEGIN
		INSERT INTO service_telephony_t (
		obj_id0, 
		--
		max_active_calls, network,
		qos, cos
		) VALUES (
		@service_id,
		--
		100, '*',
		0, 0 
		)

	    END

               set @service_cnt = @service_cnt + 1
	 END    -- end loop by services

                set @service_cnt = 1

	     while ( @service_cnt <= 4 )
	     BEGIN
		if ( @service_cnt = 1 )
		BEGIN
		    set @service_type = @service1
		    set @service_id = @srv1_id0
		    set @deal_id = @deal1_id0
		    set @prod_id = @prd1_id0
	        END 
		if ( @service_cnt = 2 )
		BEGIN
		    set @service_type = @service2
		    set @service_id = @srv1_id0 + @num_accnt
		    set @deal_id = @deal2_id0
		    set @prod_id = @prd2_id0
	        END 
		if ( @service_cnt = 3 )
		BEGIN
		    set @service_type = @service3
		    set @service_id = @srv1_id0 + ( 2 * @num_accnt)
		    set @deal_id = @deal3_id0
		    set @prod_id = @prd3_id0
	        END 
		if ( @service_cnt = 4 )
		BEGIN
		    set @service_type = @service4
		    set @service_id = @srv1_id0 + ( 3 * @num_accnt)
		    set @deal_id = @deal4_id0
		    set @prod_id = @prd4_id0
	        END 
		if ( @service_type = '/service/email' )
		BEGIN
		   set @flag = 1
		END
		ELSE
		BEGIN
		   set @flag = 3
		END


	    if ( @deal_id  != 0 )
	    BEGIN
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
		cycle_start_t, cycle_end_t, cycle_discount, 
		usage_start_t, usage_end_t, usage_discount,
		smc_start_t, smc_end_t,
		flags, status, status_flags,
		node_location, cycle_fee_flags
		) VALUES (
		@acnt_id0, @service_cnt,
		--
		@db_id, @service_id, ltrim(rtrim(@service_type)),
		@db_id, @prod_id, '/product',
		0,0,'',
		1,
		@db_id, @deal_id, '/deal',
		@db_id, @plan_id0,  '/plan',
		@create_t,
		--
		@create_t, 0, 0,
		@create_t, 0, 0,
		@create_t, 0, 0,
		@create_t,@actg_next_t, 
		@flag, 1, 0,
		'0:0',0
		);
            END
		set @service_cnt = @service_cnt + 1
	END  -- end of loop by products


		INSERT INTO payinfo_t (
		poid_db, poid_id0, 
		poid_type, poid_rev,
		name, created_t, mod_t, 
		--
                read_access, write_access,
		--
		account_obj_db, account_obj_id0, account_obj_type,
		invoice_obj_db, invoice_obj_id0, invoice_obj_type, 
		due_dom, relative_due_t
		) VALUES (
		@db_id, @pay_id0, 
		@cc_string,1,
		'Pin CC Payinfo', @create_t, @create_t, 
		--
		@brand_perm,@brand_perm,
		--
		@db_id, @acnt_id0, '/account',
		@db_id, -1, '/invoice',
		0, 30*24*60*60 -- 30 days in seconds
		)

             -- insert in group member of brand
 
                IF (@brand_id0 <> 1)
		BEGIN
                       INSERT INTO group_billing_members_t (
                       obj_id0, rec_id,
                       --
                       object_db, object_id0, object_type, 
                       object_rev
                       ) VALUES (
                       @group_poid, @rec_num,
                       --
                       @db_id, @acnt_id0, '/account', 1
                       );
                 END 

		IF (@cc = 1)
		BEGIN
			INSERT INTO payinfo_cc_t (
			obj_id0, rec_id,
			--
			debit_exp, debit_num,
			--
			name, 
			address, city, state, zip, country
			) VALUES (
			@pay_id0, 0,
			--
			'0999', '4444111122223333',
			--
			@acnt_id0, 
			'401 Stevens Blvd', 'Cupertino', 'CA', '95014', 'USA'
			);

			-- create an /item/payment object to hold the 
			-- payment event.
			INSERT INTO item_t (
			poid_db, poid_id0, poid_type, poid_rev, 
			name, 
			created_t, mod_t,gl_segment,
			--	
			effective_t, closed_t, status,
			--
			account_obj_db, account_obj_id0, account_obj_type, 
			bill_obj_db, bill_obj_id0, bill_obj_type, 
			--
			currency, item_total, due, disputed, recvd, adjusted, 
			transfered, writeoff,
		        --
                        read_access, write_access,
			--
			ar_account_obj_db, ar_account_obj_id0, 
			ar_account_obj_type,
			ar_bill_obj_db, ar_bill_obj_id0, ar_bill_obj_type,
			due_t, item_no
			) VALUES (
			@db_id, @item2_id0, '/item/payment', 1, 
			'Payment',
			@create_t, @create_t,@gl_segm,
			--
			@create_t, 0, 2,
			--
			@db_id, @acnt_id0, '/account',
			@db_id, @bill_id0, '/bill',
		        --
			840, -1, -1, 0, 0, 0, 
			0,0,
			--
		        @brand_perm,@brand_perm,
			--
			@db_id, @acnt_id0, '/account',
			@db_id, @bill_id0, '/bill',
			0, '');

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
			--
			provider_ipaddr,
			--
                        read_access, write_access,
			--
			currency, tax_locales,
			start_t, sys_descr, 
			userid_db, userid_id0, userid_type
			) VALUES (
			@db_id, @ebpc_id0, ltrim(rtrim('/event/billing/payment/cc')), 1, 
			'Billing Event Log', @create_t, @create_t, 
			--
			@db_id, @acnt_id0, '/account',
			'credit card payment', @create_t, '', 0,
			--
			0, 0, '',
			@db_id, @item2_id0, '/item/payment',
			'Automatic Account Creation', 
			--
			0x00,
			--
		        @brand_perm,@brand_perm,
			--
			840,'',
			@create_t, 'Payment - Thank You',
			@db_id, 1, '/service/pcm_client'
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
			tax_code, impact_category
			) VALUES (
			@ebpc_id0,0, 
			--
			@db_id, @acnt_id0, '/account',
			--
			10,0,0,
			101,1,
			--
			@db_id, @item2_id0, '/item/payment',
			--
			0,0,
			0,0,'',
			--
			'',840,
			'IP_USAGE','default'
			);

			INSERT INTO event_billing_payment_t (
			obj_id0, 
			--
			amount,currency,
			merchant,bill_type,
			--
			command, trans_id
			) VALUES (
			@ebpc_id0, 
			--
			10,840,
			'test',10003,
			--
			2, @acnt_id0
			);

			INSERT INTO event_billing_payment_cc_t (
			obj_id0, rec_id,
			--
			auth_code, auth_date, result
			) VALUES (
			@ebpc_id0, 0,
			--
			'pinXXX', @date_str, 0
			);

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
			--
			provider_ipaddr,
			--
                        read_access, write_access,
			--
			currency, tax_locales,
			start_t, sys_descr, 
			userid_db, userid_id0, userid_type
			) VALUES (
			@db_id, @ebcc_id0, ltrim(rtrim('/event/billing/charge/cc')), 1, 
			'Billing Event Log', @create_t, @create_t, 
			--
			@db_id, @acnt_id0, '/account',
			'credit card charge', @create_t, '', 0,
			--
			0, 0, '',
			@db_id, @item_id0, '/item',
			'Automatic Account Creation', 
			--
			0x00,
			--
		        @brand_perm,@brand_perm,
			--
			840,'',
			@create_t, 'Authorization',
			@db_id, 1, '/service/pcm_client'
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
			tax_code, impact_category
			) VALUES (
			@ebpc_id0,0, 
			--
			@db_id, @acnt_id0, '/account',
			--
			10,0,0,
			101,1,
			--
			@db_id, @item_id0, '/item',
			--
			0,0,
			0,0,'',
			--
			'',840,
			'','default'
			);

			INSERT INTO event_billing_charge_t (
			obj_id0, 
			--
			bill_obj_db,bill_obj_id0,bill_obj_type,
			--
			amount, bill_type, command, currency, merchant,
			result, trans_id
			) VALUES (
			@ebcc_id0,
			--
			0,0,'',
			--
			50, 10003, 2, 840, 'test',
			0, @acnt_id0
			);

			INSERT INTO event_billing_charge_cc_t (
			obj_id0, rec_id,
			--
			name, address, city, state, country, zip,
			debit_exp, debit_num
			) VALUES (
			@ebcc_id0, 0,
			--
			@acnt_id0, '', '', '', '', '',
			'0999', '4444111122223333'
			)
	          END

		ELSE 
		BEGIN

			INSERT INTO payinfo_inv_t (
			obj_id0, rec_id,
			--
			delivery_descr,delivery_prefer, inv_terms, 
			po_amount, po_bal_threshold,po_exp,
			--
			po_exp_threshold,po_options,
			po_order_no,po_terms,po_type,
			inv_instr, status,
			--
			name, 
			address, city, state, zip, country
			) VALUES (
			@pay_id0, 0,
			--
			'',0, 0,
			0, 0, @create_t,
			--
			@create_t, 0,
			'', '',0,
			'', 0,
			--
			@acnt_id0, 
			'401 Stevens Blvd', 'Cupertino', 'CA', '95014', 'USA'
			)

		END 

			SELECT @acnt_id0	= @acnt_id0 + 1
			SELECT @login0		= @login0 + 1
			SELECT @bill_id0	= @bill_id0 + 1
			SELECT @actg_id0	= @actg_id0 + 1
			SELECT @item_id0	= @item_id0 + 1
			SELECT @item2_id0	= @item2_id0 + 1
			SELECT @pay_id0		= @pay_id0  + 1
			SELECT @ebpc_id0	= @ebpc_id0  + 1
			SELECT @ebcc_id0	= @ebcc_id0  + 1
			SELECT @srv1_id0	= @srv1_id0 + 1
			SELECT @rec_num	        = @rec_num + 1

			SELECT @cur_acnt	= @cur_acnt + 1
	  END  -- end of loop 
	END 
			
GO

