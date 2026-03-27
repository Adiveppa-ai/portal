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

--

DECLARE @t_name sysname
DECLARE c_Tables CURSOR  FOR
	SELECT name FROM sysobjects WHERE xtype = 'U'
	
OPEN c_Tables

FETCH NEXT FROM c_Tables
INTO @t_name

PRINT '============================================================================================================================'
PRINT '              Table   Name           :   Rows     : Reserved  :        data          :   index_size   :      unused         '
PRINT '============================================================================================================================'
WHILE @@FETCH_STATUS = 0
BEGIN

  EXEC ( 'sp_spaceused '+ @t_name )

 FETCH NEXT FROM c_Tables
 INTO @t_name

END

	--  Close the cursor.
	--
CLOSE c_Tables
DEALLOCATE c_Tables
GO

