--  Continuus file information --- %full_filespec: ms_updcnts.sql~2:sql:1 %
-- @(#)ms_updcnts.sql 1.1 98/09/29

if EXISTS ( select name from sysobjects
	where name = 'update_accounts' AND type = 'P' )
	DROP procedure update_accounts
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE update_accounts
		@num_accnt int,
		@beg_id0 int,
		@create_t int ,
		@period int
AS

	-- Account number being created. (1 <= CUR_ACNT <= NUM_ACNT)
		DECLARE @acnt_id0 int
		DECLARE @cur_acnt int

	BEGIN
		-----------------------------------------------------------
		-- Initialize variables
		-----------------------------------------------------------
		SELECT @acnt_id0        = @beg_id0
		SELECT @cur_acnt   = 0

		
         -- This is a loop to create given number of accounts

	WHILE @cur_acnt < @num_accnt / @period
	BEGIN
	UPDATE account_t set actg_next_t = @create_t
		 where poid_id0 = @acnt_id0 
--		go

		SELECT @acnt_id0        = @acnt_id0 + @period
		SELECT @cur_acnt        = @cur_acnt + 1
	END 

END 
go

