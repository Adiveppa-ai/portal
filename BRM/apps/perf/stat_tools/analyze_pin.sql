--
--      @(#) % %
--     
--      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
--     
--      This material is the confidential property of Oracle Corporation or its
--      licensors and may be used, reproduced, stored or transmitted only in
--      accordance with a valid Oracle license or sublicense agreement.
--

--
--  This SQL*Plus command script will analyze a pin database;
--  must "grant execute on dbms_sql to pin;" for this to work
--  for user pin.
--

------------------------------------------------------------------------------
--
--  PL/SQL routine
--
------------------------------------------------------------------------------

DECLARE

    v_Table         user_tables.table_name%TYPE;    -- table_name from user_tables;
    Object_Type     VARCHAR2(500);
    Stats_Method    VARCHAR2(500);
    Schema          VARCHAR2(500);

    CURSOR c_Tables IS
    SELECT table_name FROM user_tables;

BEGIN

    Object_Type := 'TABLE';
    Stats_Method := 'COMPUTE';
    Schema := 'PIN';

    --  Open cursor for processing
    --
    OPEN c_Tables;

    --  Loop through each record
    --
    LOOP

        --  Put table into temporary variable;
        --  Analyze the table...
        --
        FETCH c_Tables INTO v_Table;

        DBMS_DDL.ANALYZE_OBJECT(Object_Type, Schema, v_Table, Stats_Method,NULL,NULL);

        EXIT WHEN c_Tables%NOTFOUND;

    END LOOP;

    --  Close cursor before exiting
    --
    CLOSE c_Tables;

END;
/*
  The slash below will execute the command script; keep it at the end */

/
exit;
