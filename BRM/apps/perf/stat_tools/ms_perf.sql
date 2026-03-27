--
--	@(#) % %
--	
--	Copyright (c) 1996 - 2006 Oracle. All rights reserved.
--	
--	This material is the confidential property of Oracle Corporation or its
--	licensors and may be used, reproduced, stored or transmitted only in
--	accordance with a valid Oracle license or sublicense agreement.
--

PRINT ' Performance report ' + RTRIM(Convert(varchar(30),GETDATE()))
PRINT ' '
go

sp_spaceused
go
--
PRINT '  User report '
PRINT ' '
go
sp_who
go
--
PRINT ' Locking  in DB'
PRINT ' '
go
sp_lock
go
--
SELECT @@CONNECTIONS as 'Login attempts', @@CPU_BUSY as '  CPU (ms)', @@IDLE/1000 as 'Server Idle(sec)'
go
--
SELECT @@TOTAL_READ  as 'Total Reads ',@@TOTAL_WRITE as 'Total Writes ', @@TOTAL_ERRORS as 'Total Errors '
go
--
SELECT @@PACK_RECEIVED as 'Packet Received ', @@PACK_SENT as 'Packet Sent ', @@PACKET_ERRORS as 'Packet Errors '
go
--

