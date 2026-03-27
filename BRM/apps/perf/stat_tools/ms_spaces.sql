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

--DECLARE @t_groupid int, @t_size int
DECLARE @t_groupid char(5), @t_size char(9),@t_growth char (10)
DECLARE @t_filename char(30),@t_groupname char(10)
DECLARE c_Tables CURSOR  FOR
	SELECT a.groupid, b.groupname, a.size, a.growth, a.filename FROM 
	   sysfiles a, sysfilegroups b
	     WHERE a.groupid = b.groupid
	
OPEN c_Tables

FETCH NEXT FROM c_Tables
INTO @t_groupid, @t_groupname, @t_size, @t_growth, @t_filename

PRINT '====================================================================='
PRINT ' GroupId: Group Name:    Size   :  Growth   :  File Name             :'
PRINT '====================================================================='
WHILE @@FETCH_STATUS = 0
BEGIN

 PRINT '    ' + @t_groupid + ' ' + @t_groupname + '   ' + @t_size + ' ' + @t_growth + ' ' + @t_filename
 FETCH NEXT FROM c_Tables
 INTO @t_groupid, @t_groupname, @t_size, @t_growth, @t_filename

END

	--  Close the cursor.
	--
CLOSE c_Tables
DEALLOCATE c_Tables
GO
--

