--
--      @(#) % %
--
-- Copyright (c) 1996, 2010, Oracle and/or its affiliates. 
-- All rights reserved. 
--
--      This material is the confidential property of Oracle Corporation or its
--      licensors and may be used, reproduced, stored or transmitted only in
--      accordance with a valid Oracle license or sublicense agreement.
--

CREATE OR REPLACE PACKAGE pin_load_db AUTHID CURRENT_USER AS
	TYPE LoadInfoTyp IS RECORD (
		num_acnt	NUMBER,		-- number of accounts
		db_id		NUMBER,		-- schema database id 
		brand_db	NUMBER,		-- database id from brand
		logical_partitions	NUMBER,		-- number of logical part
		beg_id0		NUMBER,		-- starting POID_ID0
		brand_id0	NUMBER,		-- current brand POID_ID0
		login_num	NUMBER,		-- starting login number
		encrypt		NUMBER,		-- partitioning code for event
		config_items	NUMBER,		-- 0 or 1 enabled/disabled
		num_services	PLS_INTEGER,	-- number of services to create
		num_products	PLS_INTEGER,	-- number of services to create
		array_size	PLS_INTEGER,	-- number of services to create
		commit_freq	PLS_INTEGER,	-- Commit every n accounts
		user_prefix	VARCHAR2(20),	-- prefix for user login 
		user_passwd	VARCHAR2(20),	-- credentials for user 
                bal_service     PLS_INTEGER,    -- 0 or number of service balances
                credit_prof_id  PLS_INTEGER,    -- credit profile in DB for currency
                credit_prof_id1  PLS_INTEGER,    --credit profile in DB for free res
		debug		BOOLEAN
	);
		
	TYPE InsertInfoTyp IS RECORD (
		date_str	VARCHAR2(60),	-- create date as yymmdd
		gl_segm		VARCHAR2(60),	-- GL Segment             
		brand_perm	VARCHAR2(2),	-- Brand permission
		group_poid	NUMBER,		-- for branding this is group
		rec_id   	NUMBER,		-- starting member number    
		create_t	NUMBER,		-- create_time
		actg_next_t	NUMBER,		-- actg next time
		actg_future_t	NUMBER,		-- actg future time
		actg_cycle	PLS_INTEGER,	-- actg cycle DOM
		deal_id	        DBMS_SQL.NUMBER_TABLE,	-- Deals  Poid ID0
		prod_id	        DBMS_SQL.NUMBER_TABLE,	-- Products  Poid ID0
		prod_type       DBMS_SQL.NUMBER_TABLE,	-- Product Type ( Product or Discount )
                balance_index   DBMS_SQL.NUMBER_TABLE,       -- balance group number for service ( 0 -account level)
                subscription_index   DBMS_SQL.NUMBER_TABLE,  -- subscription group number ( 0 -is not in group)
		plan_id0	NUMBER,		-- Plan Poid ID0
		services        DBMS_SQL.VARCHAR2_TABLE,  -- Service types per prod
		service_type    DBMS_SQL.VARCHAR2_TABLE,  -- Service Types
		cc		NUMBER,		-- Create CC account if 1
		residency	NUMBER,		-- Control object cache flag
		free_time	NUMBER		-- free resources in corresponding units
	);

	-- TODO (jpk) timestamp info to determine the time it takes to run

	PROCEDURE insert_accounts(l_info IN LoadInfoTyp,
				  i_info IN InsertInfoTyp);
END;
/

CREATE OR REPLACE PACKAGE BODY pin_load_db AS
	TYPE CurrAccountInfoTyp IS RECORD (
		acnt_id0	NUMBER,
		db_id		NUMBER,		-- current  logical database id 
		curr_db	        VARCHAR2(20),	-- current  ascii database id
		curr_brand_db   VARCHAR2(20),	-- current  ascii brand database id
                serv_assign     DBMS_SQL.NUMBER_TABLE,
                parent_index     DBMS_SQL.NUMBER_TABLE,
		rec_id  	NUMBER,
		res_currency  	NUMBER,
		res_cnt  	NUMBER,
		res_id  	DBMS_SQL.NUMBER_TABLE,
		login0   	NUMBER,
		bill_id0	NUMBER,
		actg_id0	NUMBER,
		item_id0	NUMBER,
		item2_id0	NUMBER,
		pay_id0		NUMBER,
		ebpc_id0	NUMBER,
		ebcc_id0	NUMBER,
		srv1_id0	NUMBER
	);
	
	-- Forward declaration
	PROCEDURE insert_one_account(l_info IN LoadInfoTyp,
				     i_info IN InsertInfoTyp,
				     cl_info IN CurrAccountInfoTyp);

	
	PROCEDURE debug_print(l_info IN LoadInfoTyp) IS
	BEGIN
		IF l_info.debug THEN	
			Debug.Debug('l_info.num_acnt', 	l_info.num_acnt);
			Debug.Debug('l_info.db_id', 	l_info.db_id);
			Debug.Debug('l_info.beg_id0', 	l_info.beg_id0);
			Debug.Debug('l_info.commit_freq ', l_info.commit_freq);
		END IF;
	END debug_print;

	PROCEDURE debug_print(l_info IN LoadInfoTyp, 
			      i_info IN InsertInfoTyp) IS
	BEGIN
		IF l_info.debug THEN	
			Debug.Debug('i_info.create_t', 	i_info.create_t);
			Debug.Debug('i_info.actg_next_t', i_info.actg_next_t);
			Debug.Debug('i_info.actg_future_t', i_info.actg_future_t);
			Debug.Debug('i_info.actg_cycles', i_info.actg_cycle);
			Debug.Debug('i_info.plan_id0', 	i_info.plan_id0);
	
		END IF;
	END debug_print;

	PROCEDURE debug_print(l_info IN LoadInfoTyp, 
			      cl_info IN CurrAccountInfoTyp) IS
	BEGIN
		IF l_info.debug THEN	
			Debug.Debug('cl_info.acnt_id0', cl_info.acnt_id0);
			Debug.Debug('cl_info.bill_id0', cl_info.bill_id0);
			Debug.Debug('cl_info.actg_id0', cl_info.actg_id0);
			Debug.Debug('cl_info.item_id0', cl_info.item_id0);
			Debug.Debug('cl_info.item2_id0', cl_info.item2_id0);
			Debug.Debug('cl_info.pay_id0', cl_info.pay_id0);
			Debug.Debug('cl_info.ebpc_id0', cl_info.ebpc_id0);
			Debug.Debug('cl_info.ebcc_id0', cl_info.ebcc_id0);
			Debug.Debug('cl_info.srv1_id0', cl_info.srv1_id0);
		END IF;
	END debug_print;

	-- This procedure inserts a given number of accounts
	PROCEDURE insert_accounts(l_info IN LoadInfoTyp,
				  i_info IN InsertInfoTyp) IS
		-- Account number being created. (1 <= CUR_ACNT <= NUM_ACNT)
		cur_acnt	NUMBER;
		cur_partition   NUMBER;
		
		-- Current account's info
		cl_info		CurrAccountInfoTyp;
		
		commit_cnt	NUMBER;
		my_resource	NUMBER;
-- Get the resources from given plan      
cursor plan_limit is
        select rec_id from plan_limit_t
                where obj_id0 = i_info.plan_id0;

-- Get the currency from rate_plan
cursor rate_plan is
        select currency from rate_plan_t 
                where currency < 100000 and currency <> 840 and rownum < 2;
	BEGIN
		-----------------------------------------------------------
		-- Initialize variables
		-----------------------------------------------------------
                -- find which service is parent service for subscription group
                -- create array of types for each parent
                -- subscription index for parent we put in cl_info.parent_index
                 FOR counts IN 1..l_info.num_services LOOP
                 -- searching each group
                  cl_info.parent_index(counts) := 0;
                  FOR counts1 IN 1..l_info.num_services LOOP
                   IF (( i_info.subscription_index(counts1) =  counts ) AND  (( cl_info.parent_index(counts) = 0 ) OR 
                        (cl_info.parent_index(counts) <> 0 AND
                        LENGTH(i_info.service_type(cl_info.parent_index(counts))) > 
                         LENGTH( i_info.service_type(counts1))))) THEN
                      cl_info.parent_index(counts) := counts1;
                   END IF;
                  END LOOP;
                 END LOOP;

                -- we have one deal per service , but few products per deal
                -- so array serv_assign has service number per product
                  cl_info.serv_assign(1) := 1;
                 FOR counts IN 1..l_info.num_products-1 LOOP
		   if ( i_info.services(counts) <>  i_info.services(counts+1) ) THEN
                      cl_info.serv_assign(counts+1) := cl_info.serv_assign(counts) + 1;
                    ELSE
                      cl_info.serv_assign(counts+1) := cl_info.serv_assign(counts);
                    end IF;
                  END LOOP;
                open plan_limit;
                cl_info.res_currency := 0;
                cl_info.res_cnt := 0;
                FOR counts IN 1..l_info.array_size LOOP
                    fetch plan_limit into my_resource;
                    EXIT WHEN plan_limit%NOTFOUND;
                    if ( my_resource < 100000 ) THEN
                         cl_info.res_currency := my_resource;
                    end IF;
                    if ( my_resource > 100000 and i_info.free_time <> 0 ) THEN
                         cl_info.res_cnt := cl_info.res_cnt + 1;
                         cl_info.res_id(cl_info.res_cnt) := my_resource;
                    end IF;
                end LOOP;
                close plan_limit;
                if ( cl_info.res_currency = 0 ) THEN
                  open rate_plan;
                  -- we need to find currency before we assign default
                   fetch rate_plan into cl_info.res_currency;
                   IF ( rate_plan%NOTFOUND ) THEN
                    cl_info.res_currency := 840;
                      END IF;
                  close rate_plan;
                end IF;

		cl_info.acnt_id0	:= l_info.beg_id0;
		cl_info.login0   	:= l_info.login_num;
		cl_info.rec_id   	:= i_info.rec_id;
		cl_info.bill_id0	:= l_info.beg_id0;
		cl_info.actg_id0	:= l_info.beg_id0;
                -- for cumulitive/account item and payment item
                -- account usage item and payment item allocated after service items
                -- but if config_item = 0 we don't allocate service items
                IF ( l_info.config_items = 1 ) THEN
                  cl_info.item_id0        := l_info.beg_id0 + 2*l_info.num_services*l_info.num_acnt;
                ELSE
                  cl_info.item_id0        := l_info.beg_id0 ;
                end IF;
                cl_info.item2_id0       := cl_info.item_id0 + 2*l_info.num_acnt;

		cl_info.pay_id0		:= l_info.beg_id0;
		cl_info.ebpc_id0	:= l_info.beg_id0 + l_info.num_acnt;
                cl_info.ebcc_id0        := cl_info.ebpc_id0 + l_info.num_acnt;
		cl_info.srv1_id0	:= l_info.beg_id0 ;

		debug_print(l_info);
		debug_print(l_info, i_info);
		
		-----------------------------------------------------------
		-- Create l_info.num_acnt accounts and related objects
		-----------------------------------------------------------
	
		commit_cnt := 1;
                -- 4294967295 is 0xFFFFFFFF
                IF ( l_info.brand_db > 4294967295 ) THEN
                    cur_partition := l_info.brand_db / 4294967296;
                ELSE
                    cur_partition := 0;
                END IF;
		cl_info.curr_brand_db	:= '0.' ||TO_CHAR(cur_partition) || '.0.'||TO_CHAR(l_info.db_id) ;
		FOR cur_acnt IN 1..l_info.num_acnt LOOP
                    IF ( l_info.logical_partitions > 1 ) THEN
                        cur_partition		:= MOD(cur_acnt-1,l_info.logical_partitions);
		        cl_info.db_id  		:= l_info.db_id + cur_partition * 4294967296;
		        cl_info.curr_db	:= '0.' ||TO_CHAR(cur_partition) || '.0.'||TO_CHAR(l_info.db_id) ;
                    ELSE
		        cl_info.db_id  		:= l_info.db_id ;
		        cl_info.curr_db	:= '0.0.0.'||TO_CHAR(cl_info.db_id) ;
                    END IF;

--			debug_print(l_info, cl_info);

			insert_one_account(l_info, i_info, cl_info);

			cl_info.acnt_id0	:= cl_info.acnt_id0 + 1;
			cl_info.login0  	:= cl_info.login0 + 1;
			cl_info.rec_id  	:= cl_info.rec_id + 1;
			cl_info.bill_id0	:= cl_info.bill_id0 + 1;
			cl_info.actg_id0	:= cl_info.actg_id0 + 1;
			cl_info.item_id0	:= cl_info.item_id0 + 1;
			cl_info.item2_id0	:= cl_info.item2_id0 + 1;
			cl_info.pay_id0		:= cl_info.pay_id0  + 1;
			cl_info.ebpc_id0	:= cl_info.ebpc_id0  + 1;
			cl_info.ebcc_id0	:= cl_info.ebcc_id0  + 1;
			cl_info.srv1_id0	:= cl_info.srv1_id0 + 1;
			
			IF (commit_cnt = l_info.commit_freq) THEN
				commit_cnt := 0;
				commit;
			END IF;
		
			commit_cnt := commit_cnt + 1;
		END LOOP;

		commit;
	END insert_accounts;


	PROCEDURE insert_one_account(l_info IN LoadInfoTyp,
				     i_info IN InsertInfoTyp,
				     cl_info IN CurrAccountInfoTyp) IS
                cursor1         INTEGER;
		row_num 	NUMBER;
		service_cnt	NUMBER;
		resource_cnt	NUMBER;
		my_service_id	NUMBER;
		my_subscription_id	NUMBER;
		my_subscription_db	NUMBER;
		my_subscription_type	VARCHAR2(100);
		deal_id		NUMBER;
		next_item_id	NUMBER;
		curr_item_id	NUMBER;
		next_bill_id	NUMBER;
		prod_id		NUMBER;
		purchased_id	NUMBER;
		flag   		NUMBER;
		login_num	NUMBER;
		service_type	VARCHAR2(100);
		login_name	VARCHAR2(80);
		service_name	VARCHAR2(80);
		pswd		VARCHAR2(80);
		lineage 	VARCHAR2(80);
                ins_stmt1        VARCHAR2(1000);
                ins_stmt2        VARCHAR2(1000);
                ins_stmt3        VARCHAR2(1000);
                ins_stmt4        VARCHAR2(1000);
                ins_stmt        VARCHAR2(1000);
	BEGIN
                lineage := cl_info.curr_brand_db || ':'||
                           TO_CHAR(l_info.brand_id0) || 'B/' ||
                           cl_info.curr_db || ':' ||
                           TO_CHAR(cl_info.acnt_id0)|| '/';

         ins_stmt1 := 'INSERT INTO service_telco_gsm_t (';
         ins_stmt1 := ins_stmt1 || 'obj_id0, imei, bearer_service';
         ins_stmt1 := ins_stmt1 || ' ) VALUES ( ';
         ins_stmt1 := ins_stmt1 || ':1 ,' || '''' || ' ' || '''' || ',';
         ins_stmt1 := ins_stmt1 || '''' || 'T11' || ''''|| ')';

         ins_stmt2 := 'INSERT INTO service_telco_features_t (';
         ins_stmt2 := ins_stmt2 || 'obj_id0, rec_id, name,status';
         ins_stmt2 := ins_stmt2 || ') VALUES (';
         ins_stmt2 := ins_stmt2 || ':1 ,:2,:3, 1 )';

         ins_stmt3 := 'INSERT INTO service_telco_t (';
         ins_stmt3 := ins_stmt3 || 'obj_id0, primary_number';
         ins_stmt3 := ins_stmt3 || ') VALUES (';
         ins_stmt3 := ins_stmt3 || ':1 ,:2 )';

         ins_stmt4 := 'INSERT INTO service_telco_gsm_t (';
         ins_stmt4 := ins_stmt4 || 'obj_id0, imei, bearer_service';
         ins_stmt4 := ins_stmt4 || ' ) VALUES ( ';
         ins_stmt4 := ins_stmt4 || ':1 ,' || '''' || ' ' || '''' ||',';
         ins_stmt4 := ins_stmt4 || '''' || 'T20' || ''''|| ')';


		INSERT INTO account_t  (
		poid_db, poid_id0, poid_type, poid_rev, 
		name, created_t, mod_t, effective_t, 
		--
		aac_access, aac_source, aac_vendor, aac_package, 
		aac_promo_code, aac_serial_num, 
		status, status_flags, last_status_t, close_when_t, 
		laststat_cmnt, account_no, 
		account_type,gl_segment, 
                --
                read_access, write_access,
		lineage,attribute,
		--
		group_obj_db, group_obj_id0, group_obj_type, 
		bal_grp_obj_db, bal_grp_obj_id0, bal_grp_obj_type, 
		--
		object_cache_type,
		item_poid_list, 
		--
		brand_obj_db, brand_obj_id0, brand_obj_type, brand_obj_rev,
		--
		currency, 
		access_code1, access_code2, internal_notes_size, locale 
		) VALUES (
		cl_info.db_id, cl_info.acnt_id0, '/account', 1,
		'Pin Account', i_info.create_t,i_info.create_t,i_info.create_t, 
		--
		'', '', '', '', 
		'', '',
		10100, 0, i_info.create_t, 0, 
		'',
		 cl_info.curr_db ||'-' || TO_CHAR(cl_info.acnt_id0),
		1,i_info.gl_segm, 
                --
		i_info.brand_perm,i_info.brand_perm,
		lineage,0,
		--
		0, 0, '',
		cl_info.db_id, cl_info.acnt_id0, '/balance_group',
		--
		i_info.residency,
		cl_info.curr_db ||'|/item/misc '||TO_CHAR(cl_info.item_id0)||' 0',
		l_info.brand_db, l_info.brand_id0, '/account',0,
		--
		cl_info.res_currency, 
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
		cl_info.acnt_id0, 1, 
		--
		0, 0, '', 
		--
		'', cl_info.acnt_id0, cl_info.acnt_id0, '', '', 
		'', '', '', 'Portal', '',
		--
		'401 Stevens Blvd', 'Cupertino', 'CA', '95014', 'USA',
		'someone@nowhere.com', ''
		);
		
                -- we create only one billinfo per account now

                INSERT INTO billinfo_t (
		poid_db, poid_id0, poid_type, poid_rev, 
		created_t, mod_t,
		--
                read_access, write_access,
                bill_info_id,
                billing_state,billing_status,billing_status_flags,
		--
                currency, currency_secondary,
                status, status_flags,
		account_obj_db, account_obj_id0, account_obj_type, 
		bal_grp_obj_db, bal_grp_obj_id0, bal_grp_obj_type, 
		--
		actg_next_t, actg_last_t, actg_cycle_dom, 
		actg_future_t, bill_actgcycles_left, bill_when,
                num_suppressed_cycles, actg_type,
                --
                last_bill_t,
                last_bill_obj_db,last_bill_obj_id0,last_bill_obj_type,
                actual_last_bill_t,
                actual_last_bill_obj_db,actual_last_bill_obj_id0,actual_last_bill_obj_type,
                --
                next_bill_t,
                next_bill_obj_db,next_bill_obj_id0,next_bill_obj_type,
                future_bill_t,
                --
		bill_obj_db, bill_obj_id0, bill_obj_type, 
                parent_flags, sponsor_flags, sponsoree_flags,
                pending_recv,
                --
                ar_billinfo_obj_db,ar_billinfo_obj_id0, ar_billinfo_obj_type,
                parent_billinfo_obj_db,parent_billinfo_obj_id0, parent_billinfo_obj_type,
                --
		payinfo_obj_db, payinfo_obj_id0, 
		payinfo_obj_type , object_cache_type,
                pay_type
		) VALUES (
		cl_info.db_id, cl_info.acnt_id0, '/billinfo', 1,
		i_info.create_t, i_info.create_t, 
		--
		i_info.brand_perm,i_info.brand_perm,
                'BillInfo 1',
		0,0,0,
		--
		cl_info.res_currency, 0, 
                10100, 0,
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, cl_info.acnt_id0, '/balance_group',
		--
		i_info.actg_next_t, i_info.create_t, i_info.actg_cycle, 
                -- change to line below if you will never bill
                -- 2147483647 is actually 0x7FFFFFFF
		--2147483647, i_info.create_t, i_info.actg_cycle, 
		i_info.actg_future_t, 1, 1,
                0,2,
                --
                i_info.create_t, 
                0,0,'',
                0, 
                0,0,'',
                --
                i_info.actg_next_t, 
                0,0,'',
		i_info.actg_future_t,
                --
		cl_info.db_id, cl_info.bill_id0, '/bill',
                0,0,0,
                0,
                --
		cl_info.db_id, cl_info.acnt_id0, '/billinfo', 
                0,0,'',
                --
		cl_info.db_id, cl_info.pay_id0, 
		DECODE(i_info.cc, 1, '/payinfo/cc', '/payinfo/invoice'),
                i_info.residency,
		--
                DECODE(i_info.cc, 1, 10003, 2, 10000, 10001)
                );
                 

                -- only one bal_grp_t per account ( account_level )
                -- and number of optional bal groups
                -- we create all groups are identical

           FOR counts IN 0..l_info.bal_service LOOP
		INSERT INTO bal_grp_t  (
		poid_db, poid_id0, poid_type, poid_rev, 
		created_t, mod_t, effective_t,
		--
                read_access, write_access,
                object_cache_type,
		--
		account_obj_db, account_obj_id0, account_obj_type, 
		billinfo_obj_db, billinfo_obj_id0, billinfo_obj_type 
		) VALUES (
		cl_info.db_id, cl_info.acnt_id0+(l_info.num_acnt * counts), '/balance_group', 1,
		i_info.create_t, i_info.create_t, i_info.create_t, 
		--
		i_info.brand_perm,i_info.brand_perm,
                i_info.residency,
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo'
		);
                
		  INSERT INTO bal_grp_sub_bals_t (
		  obj_id0, rec_id, rec_id2,
                  grantor_obj_db,grantor_obj_id0,grantor_obj_type,
                  grantor_obj_rev,
		  --
                  valid_from, valid_to,
                  valid_from_details, valid_to_details,
                  next_bal,delayed_bal,
		  current_bal, contributor, rollover_data
		  ) VALUES (
		  cl_info.acnt_id0+(l_info.num_acnt * counts), 0, cl_info.res_currency,
		  cl_info.db_id, cl_info.acnt_id0, '/purchased_product',
                  l_info.credit_prof_id,
		  --
		  i_info.create_t-86400, 0, 
                  0,0,
                  0,0,
		  19.95, '', 0 
		  );

                  INSERT INTO bal_grp_bals_t (
                   obj_id0, rec_id,
                  --
                  consumption_rule,
                  --
                  credit_profile, next_bal,reserved_amount
                  ) VALUES (
                  cl_info.acnt_id0+(l_info.num_acnt * counts),cl_info.res_currency,
                  --
                  1,
                  --
                  l_info.credit_prof_id, 0, 0 
                  );
		
---             populate free resources in balance group   
                resource_cnt := 1;

           while ( resource_cnt <= cl_info.res_cnt ) LOOP
               -- my_service_id here is an additional resource
		my_service_id := cl_info.res_id(resource_cnt);
                  INSERT INTO bal_grp_bals_t (
                   obj_id0, rec_id,
                  --
                  consumption_rule,
                  --
                  credit_profile, next_bal,reserved_amount
                  ) VALUES (
                  cl_info.acnt_id0+(l_info.num_acnt * counts),my_service_id,
                  --
                  1,
                  --
                  l_info.credit_prof_id1, 0, 0 
                  );

                  INSERT INTO bal_grp_sub_bals_t (
                   obj_id0, rec_id, rec_id2,
                   grantor_obj_db,grantor_obj_id0,grantor_obj_type,
                  grantor_obj_rev,
                  --
                  valid_from, valid_to,
                  valid_from_details, valid_to_details,
                  next_bal,delayed_bal,
                  current_bal, contributor,rollover_data
                  ) VALUES (
                  cl_info.acnt_id0+(l_info.num_acnt * counts), resource_cnt, my_service_id,
		  cl_info.db_id, cl_info.acnt_id0, '/purchased_product',
                  l_info.credit_prof_id1,
                  --
                  i_info.create_t-86400, 0,
                  0,0,
                  0,0,
                  i_info.free_time, '', 0
                  );
                resource_cnt := resource_cnt + 1;
		
	    END LOOP;
	   END LOOP;

		INSERT INTO bill_t (
		poid_db, poid_id0, poid_type, poid_rev, name, 
		created_t, mod_t, bill_no, due_t,
		--
		account_obj_db, account_obj_id0, account_obj_type, 
                billinfo_obj_db, billinfo_obj_id0, billinfo_obj_type,
                ar_billinfo_obj_db, ar_billinfo_obj_id0, ar_billinfo_obj_type,
                parent_billinfo_obj_db, parent_billinfo_obj_id0, parent_billinfo_obj_type,
                --
		invoice_obj_db, invoice_obj_id0, invoice_obj_type, 
		parent_db, parent_id0, parent_type, 
		--
                read_access, write_access,
		--
		start_t, end_t, currency,flags, 
		previous_total, subords_total, current_total, total_due ,
                due, recvd, writeoff, transferred
		) VALUES (
		cl_info.db_id, cl_info.bill_id0, '/bill', 1, 'PIN Bill',
		i_info.create_t, i_info.create_t, '',0,
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
		0, 0, '',
                --
		cl_info.db_id, 0, '/invoice',
		0, 0, '',
		--
		i_info.brand_perm,i_info.brand_perm,
		--
		i_info.create_t, 0, cl_info.res_currency,0,
		0, 0, 0, 0,
                0,0,0,0
		);

		curr_item_id := cl_info.item_id0;
		next_item_id := cl_info.item_id0+l_info.num_acnt;

		INSERT INTO item_t (
		poid_db, poid_id0, poid_type, poid_rev, name, 
		created_t, mod_t,gl_segment,
		--
		effective_t, closed_t, status,
		--
		account_obj_db, account_obj_id0, account_obj_type, 
                bal_grp_obj_db, bal_grp_obj_id0, bal_grp_obj_type,
                billinfo_obj_db, billinfo_obj_id0, billinfo_obj_type,
                ar_billinfo_obj_db, ar_billinfo_obj_id0, ar_billinfo_obj_type,
                --
		bill_obj_db, bill_obj_id0, bill_obj_type, 
		--
		currency, item_total, due, disputed, recvd, adjusted, 
		transfered, writeoff,
		--
                read_access, write_access,
		--
		ar_bill_obj_db, ar_bill_obj_id0, ar_bill_obj_type,
		due_t, item_no
		) VALUES (
		cl_info.db_id, curr_item_id, '/item/misc', 1, 'Usage',
		i_info.create_t, i_info.create_t,i_info.gl_segm,
		--
		0, 0, 1,
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, cl_info.acnt_id0, '/balance_group',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
                --
		cl_info.db_id, cl_info.bill_id0, '/bill',
		--
		cl_info.res_currency, 0, 0, 0, 0, 0, 
		0,0,
		--
		i_info.brand_perm,i_info.brand_perm,
		--
		cl_info.db_id, cl_info.bill_id0, '/bill',
		0, '');

               IF ( l_info.config_items = 1 ) THEN

                next_bill_id := cl_info.bill_id0+l_info.num_acnt;

		INSERT INTO bill_t (
		poid_db, poid_id0, poid_type, poid_rev, name, 
		created_t, mod_t, bill_no, due_t,
		--
		account_obj_db, account_obj_id0, account_obj_type, 
                billinfo_obj_db, billinfo_obj_id0, billinfo_obj_type,
                ar_billinfo_obj_db, ar_billinfo_obj_id0, ar_billinfo_obj_type,
                parent_billinfo_obj_db, parent_billinfo_obj_id0, parent_billinfo_obj_type,
                --
		invoice_obj_db, invoice_obj_id0, invoice_obj_type, 
		parent_db, parent_id0, parent_type, 
		--
                read_access, write_access,
		--
		start_t, end_t, currency,flags, 
		previous_total, subords_total, current_total, total_due, 
                due, recvd, writeoff, transferred
		) VALUES (
		cl_info.db_id, next_bill_id, '/bill', 1, 'PIN Bill',
		i_info.create_t, i_info.create_t, '',0,
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
		0, 0, '',
                --
		cl_info.db_id, 0, '/invoice',
		0, 0, '',
		--
		i_info.brand_perm,i_info.brand_perm,
		--
		i_info.create_t, 0, cl_info.res_currency,0,
		0, 0, 0, 0,
		0, 0, 0, 0
		);

                UPDATE account_t SET next_item_poid_list = 
		cl_info.curr_db ||'|/item/misc '||TO_CHAR(next_item_id)||' 0'
		WHERE poid_id0 =  cl_info.acnt_id0;

                UPDATE billinfo_t SET next_bill_obj_db = cl_info.db_id, 
                next_bill_obj_id0= next_bill_id , next_bill_obj_type = '/bill'
                WHERE poid_id0 =  cl_info.acnt_id0;
               -- create next cumulitive item 


		INSERT INTO item_t (
		poid_db, poid_id0, poid_type, poid_rev, name, 
		created_t, mod_t,gl_segment,
		--
		effective_t, closed_t, status,
		--
		account_obj_db, account_obj_id0, account_obj_type, 
                bal_grp_obj_db, bal_grp_obj_id0, bal_grp_obj_type,
                billinfo_obj_db, billinfo_obj_id0, billinfo_obj_type,
                ar_billinfo_obj_db, ar_billinfo_obj_id0, ar_billinfo_obj_type,
                --
		bill_obj_db, bill_obj_id0, bill_obj_type, 
		--
		currency, item_total, due, disputed, recvd, adjusted, 
		transfered, writeoff,
		--
                read_access, write_access,
		--
		ar_bill_obj_db, ar_bill_obj_id0, ar_bill_obj_type,
		due_t, item_no
		) VALUES (
		cl_info.db_id, next_item_id, '/item/misc', 1, 'Usage',
		i_info.create_t, i_info.create_t,i_info.gl_segm,
		--
		0, 0, 1,
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, cl_info.acnt_id0, '/balance_group',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
                --
		cl_info.db_id, next_bill_id, '/bill',
		--
		cl_info.res_currency, 0, 0, 0, 0, 0, 
		0,0,
		--
		i_info.brand_perm,i_info.brand_perm,
		--
		cl_info.db_id, next_bill_id, '/bill',
		0, '');

             end IF;

                service_cnt := 1;

	while ( service_cnt <= l_info.num_services ) LOOP

		service_type := i_info.service_type(service_cnt);
		my_service_id := cl_info.srv1_id0 + l_info.num_acnt *(service_cnt - 1 );
                if ( service_type = '/service/email' ) THEN
		      service_name := TO_CHAR(cl_info.login0) || '@portal.com';
		      pswd := 'md5|5f4dcc3b5aa765d61d8327deb882cf99'; 
		ELSE
		      service_name := l_info.user_prefix || TO_CHAR(cl_info.login0);
                   IF ( SUBSTR(service_type,1,14) = '/service/telco' ) THEN
		      pswd := 'md5|5f4dcc3b5aa765d61d8327deb882cf99'; 
                   ELSE
		      pswd := 'clear|' || l_info.user_passwd;
		   end IF;
		end IF;

               IF ( l_info.config_items = 1 ) THEN
		 curr_item_id := my_service_id;
                 next_item_id := curr_item_id+l_info.num_services *l_info.num_acnt;
	       end IF;

               -- below piece only for GSM wireless
               IF ( service_type LIKE '%gsm%') THEN
                 login_name := service_name;
                 service_name := login_name || '_service';
                 INSERT INTO service_alias_list_t (
                   obj_id0, rec_id, name
                 ) VALUES (
                   my_service_id, 0, login_name
                 );
               end IF;
  
                 -- try to create subscription group pointer
                 IF ( i_info.subscription_index(service_cnt) = 0 OR
                      i_info.subscription_index(service_cnt) = service_cnt) THEN
                    my_subscription_db := 0;
                    my_subscription_id := 0;
                    my_subscription_type := '';
                 ELSE
                    my_subscription_db := cl_info.db_id;
                    my_subscription_id := cl_info.srv1_id0 + l_info.num_acnt *(cl_info.parent_index(i_info.subscription_index(service_cnt)) - 1 );
                    my_subscription_type := i_info.service_type(cl_info.parent_index(i_info.subscription_index(service_cnt)));
                 END IF;

		INSERT INTO service_t (
		poid_db, poid_id0, poid_type, poid_rev, 
		name, created_t, mod_t, 
		--
		account_obj_db, account_obj_id0, account_obj_type, 
		bal_grp_obj_db, bal_grp_obj_id0, bal_grp_obj_type, 
		subscription_obj_db, subscription_obj_id0, subscription_obj_type, 
		login, passwd, 
		effective_t,
		--
                item_poid_list,
		--
		aac_access, aac_source, aac_vendor, aac_package, 
		aac_promo_code, aac_serial_num, 
		--
                read_access, write_access,
                object_cache_type,
		--
		status, status_flags, last_status_t, close_when_t, 
		laststat_cmnt 
		) VALUES (
		cl_info.db_id, my_service_id, service_type, 1, 
		'PIN Service', i_info.create_t, i_info.create_t,
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, 
                cl_info.acnt_id0+l_info.num_acnt *i_info.balance_index(service_cnt), '/balance_group',
                my_subscription_db,my_subscription_id,my_subscription_type,
		service_name,pswd,
		i_info.create_t,
		--
		cl_info.curr_db ||'|/item/misc '||TO_CHAR(curr_item_id)||' 0',
		--
		'', '', '', '', 
		'', '',
		--
		i_info.brand_perm,i_info.brand_perm,
                i_info.residency,
		--
		10100, 0, i_info.create_t, 0, 
		''
		);


               IF ( l_info.config_items = 1 ) THEN
               -- create item/misc by service

                UPDATE service_t set next_item_poid_list = cl_info.curr_db ||'|/item/misc '||TO_CHAR(next_item_id)||' 0'
                WHERE poid_id0 = my_service_id;

		INSERT INTO item_t (
		poid_db, poid_id0, poid_type, poid_rev, name, 
		created_t, mod_t,gl_segment,
		--
		effective_t, closed_t, status,
		--
		account_obj_db, account_obj_id0, account_obj_type, 
                bal_grp_obj_db, bal_grp_obj_id0, bal_grp_obj_type,
                billinfo_obj_db, billinfo_obj_id0, billinfo_obj_type,
                ar_billinfo_obj_db, ar_billinfo_obj_id0, ar_billinfo_obj_type,
                --
		bill_obj_db, bill_obj_id0, bill_obj_type, 
		service_obj_db, service_obj_id0, service_obj_type, 
		--
		currency, item_total, due, disputed, recvd, adjusted, 
		transfered, writeoff,
		--
                read_access, write_access,
		--
		ar_bill_obj_db, ar_bill_obj_id0, ar_bill_obj_type,
		due_t, item_no
		) VALUES (
		cl_info.db_id, curr_item_id, '/item/misc', 1, 'Usage',
		i_info.create_t, i_info.create_t,i_info.gl_segm,
		--
		0, 0, 1,
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, 
                cl_info.acnt_id0+l_info.num_acnt *i_info.balance_index(service_cnt), '/balance_group',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
                --
		cl_info.db_id, cl_info.bill_id0, '/bill',
		cl_info.db_id, my_service_id, service_type,  
		--
		cl_info.res_currency, 0, 0, 0, 0, 0, 
		0,0,
		--
		i_info.brand_perm,i_info.brand_perm,
		--
		cl_info.db_id, cl_info.bill_id0, '/bill',
		0, '');
                -- insert next item
		INSERT INTO item_t (
		poid_db, poid_id0, poid_type, poid_rev, name, 
		created_t, mod_t,gl_segment,
		--
		effective_t, closed_t, status,
		--
		account_obj_db, account_obj_id0, account_obj_type, 
                bal_grp_obj_db, bal_grp_obj_id0, bal_grp_obj_type,
                billinfo_obj_db, billinfo_obj_id0, billinfo_obj_type,
                ar_billinfo_obj_db, ar_billinfo_obj_id0, ar_billinfo_obj_type,
                --
		bill_obj_db, bill_obj_id0, bill_obj_type, 
		service_obj_db, service_obj_id0, service_obj_type, 
		--
		currency, item_total, due, disputed, recvd, adjusted, 
		transfered, writeoff,
		--
                read_access, write_access,
		--
		ar_bill_obj_db, ar_bill_obj_id0, ar_bill_obj_type,
		due_t, item_no
		) VALUES (
		cl_info.db_id, next_item_id, '/item/misc', 1, 'Usage',
		i_info.create_t, i_info.create_t,i_info.gl_segm,
		--
		0, 0, 1,
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, 
                cl_info.acnt_id0+l_info.num_acnt *i_info.balance_index(service_cnt), '/balance_group',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
		cl_info.db_id, cl_info.acnt_id0, '/billinfo',
                --
		cl_info.db_id, next_bill_id, '/bill',
		cl_info.db_id, my_service_id, service_type,  
		--
		cl_info.res_currency, 0, 0, 0, 0, 0, 
		0,0,
		--
		i_info.brand_perm,i_info.brand_perm,
		--
		cl_info.db_id, next_bill_id, '/bill',
		0, '');
             end IF;

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
		--cl_info.db_id, my_service_id, '/uniqueness', 1, 
		--i_info.create_t, i_info.create_t,
		----
		--cl_info.db_id, cl_info.acnt_id0, '/account',
		--cl_info.db_id, my_service_id, service_type,
		----
		--'G','S',
		--login_name,2,
		--cl_info.curr_db ||'-' || TO_CHAR(cl_info.acnt_id0)
		--);

        if ( service_type = '/service/ip' ) THEN
		INSERT INTO service_ip_t (
		obj_id0, 
		--
		protocol, compression, ipaddr
		) VALUES (
		my_service_id,
		--
		0, 0, '00');
	end IF;


        if ( service_type = '/service/broadband' ) THEN
		INSERT INTO service_broadband_t (
		obj_id0, 
		--
		event_obj_db, event_obj_id0, event_obj_type
		) VALUES (
		my_service_id,
		--
		0, 0, '' 
		);
	end IF;

        if ( service_type = '/service/vpdn' ) THEN
		INSERT INTO service_vpdn_t (
		obj_id0, 
		--
		compression,ipaddr,
		protocol
		) VALUES (
		my_service_id,
		--
		0, '00', 0
		);
	end IF;

        if ( service_type = '/service/email' ) THEN
		INSERT INTO service_email_t (
		obj_id0, 
		--
		mail_server_id, max_mbox_size, max_msg_size, max_msg_cnt, 
		path
		) VALUES (
		my_service_id,
		--
		'00', 0, 0, 0, 
		''
		);
	end IF;


        if ( service_type = '/service/telco/gsm/telephony' ) THEN


         EXECUTE IMMEDIATE ins_stmt1 USING my_service_id ;
         EXECUTE IMMEDIATE ins_stmt3 USING my_service_id , cl_info.login0;

         EXECUTE IMMEDIATE ins_stmt2 USING my_service_id,1,'CLIP' ;
         EXECUTE IMMEDIATE ins_stmt2 USING my_service_id,2,'CW' ;
         EXECUTE IMMEDIATE ins_stmt2 USING my_service_id,3,'VMBOX' ;
        end IF;

        if ( ( service_type = '/service/telco/gsm/sms' ) OR
	     ( service_type = '/service/telco/gsm/fax' ) OR     
	     ( service_type = '/service/telco/gsm/gprs' ) OR     
	     ( service_type = '/service/telco/gsm/wap' ) OR     
	     ( service_type = '/service/telco/gsm/mms' ) OR     
	     ( service_type = '/service/telco/gsm/vpn' ) OR     
	     ( service_type = '/service/telco/gsm' ) OR     
	     ( service_type = '/service/telco/gsm/data' ) ) THEN

         EXECUTE IMMEDIATE ins_stmt4 USING my_service_id ;
         EXECUTE IMMEDIATE ins_stmt3 USING my_service_id , cl_info.login0;

         EXECUTE IMMEDIATE ins_stmt2 USING my_service_id,1,'BAOC' ;
         EXECUTE IMMEDIATE ins_stmt2 USING my_service_id,2,'BICRO' ;

        end IF;

    --    if ( service_type = '/service/telephony' ) THEN
    --            INSERT INTO service_telephony_t (
    --            obj_id0,
                --
    --            max_active_calls, network,
    --            qos, cos
    --            ) VALUES (
    --            my_service_id,
                --
    --            100, '*',
    --            0, 0
    --            );
    --    end IF;

                service_cnt := service_cnt + 1;

         end LOOP;

                service_cnt := 1;
       -- inserting products
       -- we using service_cnt as products_num
       -- note we have here products and discounts

	while ( service_cnt <= l_info.num_products ) LOOP

		service_type := i_info.services(service_cnt);
		deal_id := i_info.deal_id(service_cnt);
		prod_id := i_info.prod_id(service_cnt);
		my_service_id := cl_info.srv1_id0 + ( (cl_info.serv_assign(service_cnt) -1) * l_info.num_acnt);
		purchased_id := cl_info.acnt_id0 + (( service_cnt -1) * l_info.num_acnt);

		flag := 1;  -- charged cycle_forward

	  if ( deal_id != 0 ) THEN
             -- discount or product
	    if ( i_info.prod_type(service_cnt) != 0 ) THEN
		INSERT INTO purchased_discount_t (
                poid_db, poid_id0, poid_type, poid_rev,
                created_t, mod_t,effective_t,
		read_access, write_access,
                object_cache_type,
		--
		account_obj_db, account_obj_id0, account_obj_type,
		service_obj_db, service_obj_id0, service_obj_type,
		discount_obj_db, discount_obj_id0, discount_obj_type, 
                --
		quantity, 
		deal_obj_db, deal_obj_id0, deal_obj_type, 
		plan_obj_db, plan_obj_id0, plan_obj_type, 
		--
		purchase_start_t, purchase_end_t,
		cycle_start_t, cycle_end_t,
		usage_start_t, usage_end_t,
		purchase_start_details, purchase_end_details,
		cycle_start_details, cycle_end_details,
		usage_start_details, usage_end_details,
                instantiated_t,flags,
		status, status_flags,
		node_location
		) VALUES (
		cl_info.db_id, purchased_id, '/purchased_discount',1,
		i_info.create_t,i_info.create_t,i_info.create_t,
		i_info.brand_perm,i_info.brand_perm,
                i_info.residency,
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, my_service_id, service_type,
		l_info.db_id, prod_id, '/discount',
		--
		1,
		l_info.db_id, deal_id, '/deal',
		l_info.db_id, i_info.plan_id0,  '/plan',
		--
		i_info.create_t, 0,
		i_info.create_t, 0,
		i_info.create_t, 0,
                0,0,
                0,0,
                0,0,
		i_info.create_t, 0,
		1, 0,
		'0:0'
		);
            -- update sub balance to point to grantor as discount
            -- we need to change this later to more sophisticated stuff
               update bal_grp_sub_bals_t set grantor_obj_type = '/purchased_discount',
                 grantor_obj_id0 = purchased_id where current_bal < 0 and
                      obj_id0 in ( select poid_id0 from bal_grp_t where account_obj_id0 = cl_info.acnt_id0);
            ELSE 
                -- for cycle_forward
                INSERT INTO purchased_product_cycle_fees_t (
                obj_id0, rec_id,
                --
                charged_from_t, charged_to_t,
                cycle_fee_start_t, cycle_fee_end_t,
                unit, count 
		) VALUES (
		purchased_id, 0, 
		--
		i_info.create_t, i_info.actg_next_t, 
		i_info.actg_next_t, i_info.actg_future_t, 
                0,1
		);
         
		INSERT INTO purchased_product_t (
                poid_db, poid_id0, poid_type, poid_rev,
                created_t, mod_t,effective_t,
		read_access, write_access,
                object_cache_type,
		--
		account_obj_db, account_obj_id0, account_obj_type,
		service_obj_db, service_obj_id0, service_obj_type,
		product_obj_db, product_obj_id0, product_obj_type, 
		sponsor_obj_db, sponsor_obj_id0, sponsor_obj_type, 
                --
		quantity, 
		deal_obj_db, deal_obj_id0, deal_obj_type, 
		plan_obj_db, plan_obj_id0, plan_obj_type, 
		--
		purchase_start_t, purchase_end_t, purchase_fee_amt, 
                purchase_discount, purchase_disc_amt, 
		cycle_start_t, cycle_end_t, cycle_fee_amt,
                cycle_discount, cycle_disc_amt, 
		usage_start_t, usage_end_t, usage_discount,
		purchase_start_details, purchase_end_details,
		cycle_start_details, cycle_end_details,
		usage_start_details, usage_end_details,
                instantiated_t,flags,
		status, status_flags,
		node_location, cycle_fee_flags
		) VALUES (
		cl_info.db_id, purchased_id, '/purchased_product',1,
		i_info.create_t,i_info.create_t,i_info.create_t,
		i_info.brand_perm,i_info.brand_perm,
                i_info.residency,
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, my_service_id, service_type,
		l_info.db_id, prod_id, '/product',
		0,0,'',
                --
		1,
		l_info.db_id, deal_id, '/deal',
		l_info.db_id, i_info.plan_id0,  '/plan',
		--
		i_info.create_t, 0, 10.0,
                0,0,
		i_info.create_t, 0, 12.0,
                0,0,
		i_info.create_t, 0, 0,
                0,0,
                0,0,
                0,0,
		i_info.create_t, 2,
		1, 0,
		'0:0',flag
		);
       	 end IF;
       	end IF;

                service_cnt := service_cnt + 1;
         end LOOP;

		INSERT INTO payinfo_t (
		poid_db, poid_id0, 
		poid_type, poid_rev,
		name, created_t, mod_t, 
		--
                read_access, write_access,
                inv_type,
		--
		account_obj_db, account_obj_id0, account_obj_type,
		invoice_obj_db, invoice_obj_id0, invoice_obj_type,
		due_dom, ach,
		relative_due_t
		) VALUES (
		cl_info.db_id, cl_info.pay_id0, 
		DECODE(i_info.cc, 1, '/payinfo/cc', '/payinfo/invoice'), 1,
		'Pin CC Payinfo', i_info.create_t, i_info.create_t, 
		--
		i_info.brand_perm,i_info.brand_perm,
                0,   -- summary=1, detailed = 0
		--
		cl_info.db_id, cl_info.acnt_id0, '/account',
		cl_info.db_id, -1, '/invoice',
		0, 0,
                30*24*60*60 -- 30 days in seconds
		);

            -- insert in group member of brand

                IF (l_info.brand_id0 <> 1)  THEN
			INSERT INTO group_billing_members_t (
			obj_id0, rec_id,
			--
			object_db, object_id0, object_type, 
			object_rev
			) VALUES (
			i_info.group_poid, cl_info.rec_id,
			--
		        cl_info.db_id, cl_info.acnt_id0, '/account',
			1
			);
                END IF;

		IF (i_info.cc = 1)  THEN
			INSERT INTO payinfo_cc_t (
			obj_id0, rec_id,
			--
			debit_exp, debit_num,
			--
			name, 
			address, city, state, zip, country
			) VALUES (
			cl_info.pay_id0, 0,
			--
			'0999', '4444111122223333',
			--
			cl_info.acnt_id0, 
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
                        bal_grp_obj_db, bal_grp_obj_id0, bal_grp_obj_type,
                        billinfo_obj_db, billinfo_obj_id0, billinfo_obj_type,
                        ar_billinfo_obj_db, ar_billinfo_obj_id0, ar_billinfo_obj_type,
                        --
			bill_obj_db, bill_obj_id0, bill_obj_type, 
			--
			currency, item_total, due, disputed, recvd, adjusted, 
			transfered, writeoff,
			--
                        read_access, write_access,
		        --
			ar_bill_obj_db, ar_bill_obj_id0, ar_bill_obj_type,
			due_t, item_no
			) VALUES (
			cl_info.db_id, cl_info.item2_id0, '/item/payment', 1, 
			'Payment',
			i_info.create_t, i_info.create_t,i_info.gl_segm,
			--
			i_info.create_t, 0, 2,
			--
			cl_info.db_id, cl_info.acnt_id0, '/account',
		        cl_info.db_id, cl_info.acnt_id0, '/balance_group',
		        cl_info.db_id, cl_info.acnt_id0, '/billinfo',
		        cl_info.db_id, cl_info.acnt_id0, '/billinfo',
                        --
			cl_info.db_id, cl_info.bill_id0, '/bill',
			--
			cl_info.res_currency, -1, -1, 0, 0, 0, 
			0,0,
			--
		        i_info.brand_perm,i_info.brand_perm,
		        --
			cl_info.db_id, cl_info.bill_id0, '/bill',
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
			provider_id_db, provider_id_id0, provider_id_type, 
			service_obj_db, service_obj_id0, service_obj_type, 
			session_obj_db, session_obj_id0, session_obj_type, 
			--
                        profile_label_list,
                        read_access, write_access,
		        --
			currency, tax_locales,provider_ipaddr,
			start_t, sys_descr, 
			userid_db, userid_id0, userid_type
			) VALUES (
			cl_info.db_id, cl_info.ebpc_id0+ l_info.encrypt, '/event/billing/payment/cc', 1, 
			'Billing Event Log', i_info.create_t, i_info.create_t, 
			--
			cl_info.db_id, cl_info.acnt_id0, '/account',
			'credit card payment', i_info.create_t, '', 0,
			--
			0, 0, '',
			cl_info.db_id, cl_info.item2_id0, '/item/payment',
			'Automatic Account Creation', 
			0, 0, '',
			0, 0, '',
			0, 0, '',
			--
                        '',
		        i_info.brand_perm,i_info.brand_perm,
		        --
			cl_info.res_currency,'','0',
			i_info.create_t, 'Payment - Thank You',
			l_info.db_id, 1, '/service/pcm_client'
			);

			INSERT INTO event_bal_impacts_t (
			obj_id0, rec_id,
			--
			account_obj_db,account_obj_id0,account_obj_type,
			bal_grp_obj_db,bal_grp_obj_id0,bal_grp_obj_type,
			--
			amount,amount_deferred,discount,
			gl_id,impact_type,
			--
			item_obj_db,item_obj_id0,item_obj_type,
			offering_obj_db,offering_obj_id0,offering_obj_type,
			--
			percent, quantity,
			rate_obj_db,rate_obj_id0,rate_obj_type,
			--
			rate_tag,resource_id,
			tax_code,impact_category
			) VALUES (
			cl_info.ebpc_id0+ l_info.encrypt,0, 
			--
			cl_info.db_id, cl_info.acnt_id0, '/account',
			cl_info.db_id, cl_info.acnt_id0, '/balance_group',
			--
			10,0,0,
			101,1,
			--
			cl_info.db_id, cl_info.item2_id0, '/item/payment',
			0, 0, '',
			--
			0,0,
			0,0,'',
			--
			'',cl_info.res_currency,
			'IP_USAGE','default'
			);

			INSERT INTO event_billing_payment_t (
			obj_id0, 
			--
			amount,currency,
			merchant,pay_type,
			--
			command, trans_id, ach
			) VALUES (
			cl_info.ebpc_id0+ l_info.encrypt, 
			--
			10,cl_info.res_currency,
			'test',10003,
			--
			2, cl_info.acnt_id0,0
			);

			INSERT INTO event_billing_payment_cc_t (
			obj_id0, rec_id,
			--
			auth_code, auth_date, result
			) VALUES (
			cl_info.ebpc_id0+ l_info.encrypt, 0,
			--
			'pinXXX', i_info.date_str, 0
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
			provider_id_db, provider_id_id0, provider_id_type, 
			service_obj_db, service_obj_id0, service_obj_type, 
			session_obj_db, session_obj_id0, session_obj_type, 
			--
                        profile_label_list,
                        read_access, write_access,
		        --
			currency, tax_locales,provider_ipaddr,
			start_t, sys_descr, 
			userid_db, userid_id0, userid_type
			) VALUES (
			cl_info.db_id, cl_info.ebcc_id0+ l_info.encrypt, '/event/billing/charge/cc', 1, 
			'Billing Event Log', i_info.create_t, i_info.create_t, 
			--
			cl_info.db_id, cl_info.acnt_id0, '/account',
			'credit card charge', i_info.create_t, '', 0,
			--
			0, 0, '',
			cl_info.db_id, cl_info.item_id0, '/item',
			'Automatic Account Creation', 
			0, 0, '',
			0, 0, '',
			0, 0, '',
			--
                        '',
		        i_info.brand_perm,i_info.brand_perm,
		        --
			cl_info.res_currency,'','0',
			i_info.create_t, 'Authorization',
			l_info.db_id, 1, '/service/pcm_client'
			);

			INSERT INTO event_bal_impacts_t (
			obj_id0, rec_id,
			--
			account_obj_db,account_obj_id0,account_obj_type,
			bal_grp_obj_db,bal_grp_obj_id0,bal_grp_obj_type,
			--
			amount,amount_deferred,discount,
			gl_id,impact_type,
			--
			item_obj_db,item_obj_id0,item_obj_type,
			offering_obj_db,offering_obj_id0,offering_obj_type,
			--
			percent, quantity,
			rate_obj_db,rate_obj_id0,rate_obj_type,
			--
			rate_tag,resource_id,
			tax_code,impact_category
			) VALUES (
			cl_info.ebcc_id0 +  l_info.encrypt,0, 
			--
			cl_info.db_id, cl_info.acnt_id0, '/account',
			cl_info.db_id, cl_info.acnt_id0, '/balance_group',
			--
			10,0,0,
			101,1,
			--
			cl_info.db_id, cl_info.item_id0, '/item',
			0, 0, '',
			--
			0,0,
			0,0,'',
			--
			'',cl_info.res_currency,
			'','default'
			);

			INSERT INTO event_billing_charge_t (
			obj_id0, 
			--
			bill_obj_db,bill_obj_id0,bill_obj_type,
			--
			amount, pay_type, command, currency, merchant,
			result, trans_id,ach
			) VALUES (
			cl_info.ebcc_id0+ l_info.encrypt,
			--
			0,0,'',
			--
			50, 10003, 2, cl_info.res_currency, 'test',
			0, cl_info.acnt_id0,0
			);

			INSERT INTO event_billing_charge_cc_t (
			obj_id0, rec_id,
			--
			name, address, city, state, country, zip,
			debit_exp, debit_num 
			) VALUES (
			cl_info.ebcc_id0+ l_info.encrypt, 0,
			--
			cl_info.acnt_id0, '', '', '', '', '',
			'0999', '4444111122223333'
			);

		ELSE 

			INSERT INTO payinfo_inv_t (
			obj_id0, rec_id,
			--
			delivery_descr,delivery_prefer, inv_terms, 
			--
			email_addr,
			inv_instr, 
			--
			name, 
			address, city, state, zip, country
			) VALUES (
			cl_info.pay_id0, 0,
			--
			'',0, 0,
			--
			'nobody@portal.com',   
			'instruction',
			--
			'name', 
			'401 Stevens Blvd', 'Cupertino', 'CA', '95014', 'USA'
			);

		END IF;

	END insert_one_account;

	-- This procedure deletes a given number of accounts
--	PROCEDURE delete_accounts(l_info IN LoadInfoTyp) IS
--		beg_acnt_id0	NUMBER;
--		end_acnt_id0	NUMBER;
--		max_acnt_id0	NUMBER;
--	BEGIN
--		-----------------------------------------------------------
--		-- Initialize variables
--		-----------------------------------------------------------
--		
--		beg_acnt_id0	:= l_info.beg_id0;
--		end_acnt_id0	:= beg_acnt_id0;
--		max_acnt_id0	:= beg_acnt_id0 + l_info.num_acnt;
--
--
--		-----------------------------------------------------------
--		-- Now, delete rows from the tables
--		-----------------------------------------------------------
--		
--		WHILE beg_acnt_id0 < max_acnt_id0 LOOP
--
--			beg_acnt_id0 := end_acnt_id0;
--			end_acnt_id0 := LEAST((beg_acnt_id0 + l_info.commit_freq), max_acnt_id0);
--
--			DELETE FROM account_t 
--			WHERE poid_id0 >= beg_acnt_id0 AND
--			      poid_id0 < end_acnt_id0;
--
--			DELETE FROM account_nameinfo_t 
--			WHERE obj_id0 >= beg_acnt_id0 AND
--			      obj_id0 < end_acnt_id0;
--
--			DELETE FROM account_products_t 
--			WHERE obj_id0 >= beg_acnt_id0 AND
--			      obj_id0 < end_acnt_id0;
--
--			DELETE FROM bill_t 
--			WHERE account_obj_id0 >= beg_acnt_id0 AND
--			      account_obj_id0 < end_acnt_id0;
--	
--			DELETE FROM accounting_t 
--			WHERE account_obj_id0 >= beg_acnt_id0 AND
--			      account_obj_id0 < end_acnt_id0;
--
--			DELETE FROM item_t 
--			WHERE account_obj_id0 >= beg_acnt_id0 AND
--			      account_obj_id0 < end_acnt_id0;
--
--			DELETE FROM service_ip_t ip
--			WHERE ip.obj_id0 = 
--			(SELECT poid_id0 FROM service_t s
--				WHERE ip.obj_id0 = s.poid_id0 AND
--				(s.account_obj_id0 >= beg_acnt_id0 AND
--				 s.account_obj_id0 < end_acnt_id0));
--
--			DELETE FROM service_email_t email
--			WHERE email.obj_id0 = 
--			(SELECT poid_id0 FROM service_t s
--				WHERE email.obj_id0 = s.poid_id0 AND
--				(s.account_obj_id0 >= beg_acnt_id0 AND
--				 s.account_obj_id0 < end_acnt_id0));
--
--			DELETE FROM service_t 
--			WHERE account_obj_id0 >= beg_acnt_id0 AND
--			      account_obj_id0 < end_acnt_id0;
--
--			commit;
--		END LOOP;
--		-- TODO (jpk) remove info from other tables (like event)
--
--	END delete_accounts;
	
END pin_load_db;
/






