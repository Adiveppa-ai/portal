--
--	@(#) % %
--    
--	Copyright (c) 1996 - 2006 Oracle. All rights reserved.
--    
--	This material is the confidential property of Oracle Corporation or its
--	licensors and may be used, reproduced, stored or transmitted only in
--	accordance with a valid Oracle license or sublicense agreement.
--

set pagesize 2000
set linesize 132
column table_name format A30
select table_name, num_rows, blocks, avg_space, NVL(pct_free,0), avg_row_len from user_tables;
exit;
