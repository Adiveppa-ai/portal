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

--  Drop (if necessary) and then create the table_data table;
--

DECLARE @t_name sysname
DECLARE c_Tables CURSOR  FOR
	SELECT name FROM sysobjects WHERE xtype = 'U'
	
OPEN c_Tables

FETCH NEXT FROM c_Tables
INTO @t_name

PRINT '========================================================='
PRINT '    Table Name                    :  Number of Rows     :'
PRINT '========================================================='
WHILE @@FETCH_STATUS = 0
BEGIN

  EXEC ( 'select CAST("'+ @t_name +'" AS CHAR(35) ), count (*) from ' + @t_name  + ' with ( nolock )')

 FETCH NEXT FROM c_Tables
 INTO @t_name

END

	--  Close the cursor.
	--
CLOSE c_Tables
DEALLOCATE c_Tables
GO
--

