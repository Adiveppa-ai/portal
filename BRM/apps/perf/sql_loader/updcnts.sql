--  Continuus file information --- %full_filespec: updcnts.sql~2:sql:1 %
-- @(#)updcnts.sql 1.0 98/06/05

CREATE OR REPLACE PACKAGE pin_updt_db AUTHID CURRENT_USER AS
	TYPE LoadInfoTyp IS RECORD (
		num_acnt	NUMBER,		-- number of accounts
		db_id		NUMBER,		-- database id
		beg_id0		NUMBER,		-- starting POID_ID0
		commit_freq	PLS_INTEGER,	-- Commit every n accounts
                user_prefix     VARCHAR2(20),   -- prefix for user login
                update_interval PLS_INTEGER,
		debug		BOOLEAN
	);
		
	TYPE InsertInfoTyp IS RECORD (
		date_str	VARCHAR2(60),	-- create date as yymmdd
		create_t	NUMBER,		-- create_time
		actg_next_t	NUMBER,		-- actg next time
		actg_future_t	NUMBER,		-- actg future time
		actg_cycle	PLS_INTEGER	-- actg cycle DOM
	);

	-- TODO (jpk) timestamp info to determine the time it takes to run

	PROCEDURE update_accounts(l_info IN LoadInfoTyp,
				  i_info IN InsertInfoTyp);
END;
/

CREATE OR REPLACE PACKAGE BODY pin_updt_db AS
	TYPE CurrAccountInfoTyp IS RECORD (
		acnt_id0	NUMBER,
		billinfo_id0	NUMBER,
		actg_id0	NUMBER
	);
	
	-- Forward declaration
	PROCEDURE update_one_account(l_info IN LoadInfoTyp,
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
	
		END IF;
	END debug_print;

	PROCEDURE debug_print(l_info IN LoadInfoTyp, 
			      cl_info IN CurrAccountInfoTyp) IS
	BEGIN
		IF l_info.debug THEN	
			Debug.Debug('cl_info.acnt_id0', cl_info.acnt_id0);
			Debug.Debug('cl_info.billinfo_id0', cl_info.billinfo_id0);
			Debug.Debug('cl_info.actg_id0', cl_info.actg_id0);
		END IF;
	END debug_print;

	-- This procedure updates a given number of accounts
	PROCEDURE update_accounts(l_info IN LoadInfoTyp,
				  i_info IN InsertInfoTyp) IS
		-- Account number being created. (1 <= CUR_ACNT <= NUM_ACNT)
		cur_acnt	NUMBER;
		
		-- Current account's info
		cl_info		CurrAccountInfoTyp;
		
		commit_cnt	NUMBER;
                login1          VARCHAR2(100);
	BEGIN
		-----------------------------------------------------------
		-- Initialize variables
		-----------------------------------------------------------
		
		cl_info.acnt_id0	:= l_info.beg_id0;
		cl_info.billinfo_id0	:= l_info.beg_id0;
		cl_info.actg_id0	:= l_info.beg_id0;

		debug_print(l_info);
		debug_print(l_info, i_info);
		
		-----------------------------------------------------------
		-- Create l_info.num_acnt accounts and related objects
		-----------------------------------------------------------
	
		commit_cnt := 1;
		FOR cur_acnt IN 1..l_info.num_acnt LOOP
--			debug_print(l_info, cl_info);

                        login1 := l_info.user_prefix || TO_CHAR(cl_info.acnt_id0);
                        select account_obj_id0 into cl_info.billinfo_id0 from service_t
                          where login = login1 and rownum < 2;
			update_one_account(l_info, i_info, cl_info);

			cl_info.acnt_id0	:= cl_info.acnt_id0 + l_info.update_interval;
			
			IF (commit_cnt = l_info.commit_freq) THEN
				commit_cnt := 0;
				commit;
			END IF;
		
			commit_cnt := commit_cnt + 1;
		END LOOP;

		commit;
	END update_accounts;


	PROCEDURE update_one_account(l_info IN LoadInfoTyp,
				     i_info IN InsertInfoTyp,
				     cl_info IN CurrAccountInfoTyp) IS
	BEGIN
		UPDATE billinfo_t set actg_next_t = i_info.create_t
		 where poid_id0 = cl_info.billinfo_id0; 
		UPDATE account_cycle_fees_t set cycle_fee_start_t = i_info.create_t,
                --   charged_from_t = i_info.create_t, -- leave as is
                   charged_to_t= i_info.create_t,
                   cycle_fee_end_t = i_info.actg_next_t
		 where obj_id0 = cl_info.billinfo_id0; 
	END update_one_account;

END pin_updt_db;
/


