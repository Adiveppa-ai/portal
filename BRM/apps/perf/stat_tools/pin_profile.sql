--
--	@(#) % %
--	
--	Copyright (c) 1996 - 2006 Oracle. All rights reserved.
--	
--	This material is the confidential property of Oracle Corporation or its
--	licensors and may be used, reproduced, stored or transmitted only in
--	accordance with a valid Oracle license or sublicense agreement.
--
--
--  This SQL*Plus command script will profile a pin database;
--  must "grant execute on dbms_sql to pin;" for this to work
--  for user pin.
--

--  Drop (if necessary) and then create the table_data table;
--
drop table pin_user_data;

create table pin_user_data (name   varchar2(30),
			    count  integer);

------------------------------------------------------------------------------
--
--  PL/SQL routine
--
------------------------------------------------------------------------------

DECLARE

    v_Table	user_tables.table_name%type;	-- table_name from user_tables;
    v_Dummy	INTEGER;

    CURSOR c_Tables IS
	SELECT table_name FROM user_tables;

    --------------------------------------------------------------------------
    --
    --  Dynamic SQL routine
    --
    --------------------------------------------------------------------------

    PROCEDURE UserTableSelect (

	--
	--
	p_Table	  user_tables.table_name%type) AS

	--  Variable declarations
	--
	v_SelectStmt	VARCHAR2(500);
	v_CursorID	INTEGER;
	v_Count		INTEGER;
	v_Dummy		INTEGER;

    BEGIN
	--  Open the cursor for processing
	--
	v_CursorID := DBMS_SQL.OPEN_CURSOR;

	--  Create the query string; user_tables is a catalog.sql view.
	--
	v_SelectStmt := 'SELECT count(*) FROM ' || p_Table;

	--  Parse the query.
	--
	DBMS_SQL.PARSE(v_CursorID, v_SelectStmt, DBMS_SQL.V7);

	--  Define the output variables.
	--
	DBMS_SQL.DEFINE_COLUMN(v_CursorID, 1, v_Count);

	--  Execute the statement.  We don't care about the return
	--  value, but we do need to declare a variable for it.
	--
	v_Dummy := DBMS_SQL.EXECUTE(v_CursorID);

	--  This is the fetch loop
	--
	LOOP
	    --  Fetch the rows into the buffer, and also check for the exit
	    --  condition from the loop.
	    --
	    IF DBMS_SQL.FETCH_ROWS(v_CursorID) = 0 THEN
		EXIT;
	    END IF;

	    --  Retrieve the rows from the buffer into PL/SQL variables
	    --
	    DBMS_SQL.COLUMN_VALUE(v_CursorID, 1, v_Count);

	    INSERT INTO pin_user_data (name, count)
	    VALUES (p_Table, v_Count);

	END LOOP;

	--  Close the cursor.
	--
	DBMS_SQL.CLOSE_CURSOR(v_CursorID);

	--  Commit our work.
	--
	COMMIT;

    EXCEPTION

	WHEN OTHERS THEN

	    --  Close the cursor, then raise the error again.
	    --
	    DBMS_SQL.CLOSE_CURSOR(v_CursorID);
	    RAISE;

    END UserTableSelect;


BEGIN

    --  Open cursor for processing
    --
    OPEN c_Tables;

    --  Loop through each record
    --
    LOOP

	--  Put table into temporary variable; call stored procedure
	--  to count the number of records, whatever...
	--
	FETCH c_Tables INTO v_Table;

	    UserTableSelect(v_Table);

	EXIT WHEN c_Tables%NOTFOUND;

    END LOOP;

    --  Close cursor before exiting
    --
    CLOSE c_Tables;

END;


--  The slash below will execute the command script; keep it at the end
--
/

--  Change the output pagesize
--
set pagesize 200

--  Select all data from the newly created and populated table
--
select * from pin_user_data;

--  Spaten time :-)
--
exit;
