--  Continuus file information --- %full_filespec: space_report.sql~2:sql:1 %
SET ECHO off 
REM ------------------------------------------------------------------------- 
REM REQUIREMENTS: 
REM   DBA Role 
REM  
REM ------------------------------------------------------------------------- 
REM We assume here that all Infranet tablespaces begin with "PIN"             
REM  and indexes tablespaces begin with "PINX"             
REM ------------------------------------------------------------------------- 
 
 
break on today 
column today noprint new_value xdate 
select substr(to_char(sysdate,'fmMonth DD, YYYY HH:MI:SS P.M.'),1,35) today 
from dual; 
column name noprint new_value dbname 
select name from v$database; 
 
set heading on 
set feedback off 
 
spool dbspaces.lst 
 
prompt ********************************************************** 
prompt *****            Database Information                ***** 
prompt ********************************************************** 
ttitle left "DATABASE:  "dbname"    (AS OF:  "xdate" )" 
select name, created, log_mode from v$database; 
prompt 
prompt ********************************************************** 
ttitle off 
 
rem ------------------------------------------------------------- 
rem		Tablespace Usage 
rem ------------------------------------------------------------- 
 
set pagesize 66 
set line 132 
 
clear breaks 
clear computes 
 
column "Tablespace Name" format  A15
column "Total Bytes" format 99,999,999,999 
column "Bytes Free" format 99,999,999,999 
column "Bytes Used" format 99,999,999,999 
column "% Used" format 9999.999 
break on report 
compute sum of "Total Bytes" on report 
compute sum of "Bytes Free" on report 
compute sum of "Bytes Used" on report 
--compute avg of "% Used" on report 
 
TTitle left "***   Database:  "dbname", Tablespace Usage ( As of:  "xdate" )   *******" skip 1 
 
select  substr(fs.FILE_ID,1,3) "ID#", 
        fs.tablespace_name "Tablespace Name", 
        df.bytes "Total Bytes", 
        sum(fs.bytes) "Bytes Free", 
        df.bytes-sum(fs.bytes) "Bytes Used", 
    (100*((df.bytes-sum(fs.bytes))/df.bytes)) "% Used" 
from sys.dba_data_files df, sys.dba_free_space fs 
where df.file_id(+) = fs.file_id  and
 substr(fs.tablespace_name,1,3) = 'PIN' and
 substr(fs.tablespace_name,1,4) != 'PINX'
group by fs.FILE_ID, fs.tablespace_name, df.bytes, df.blocks 
order by fs.tablespace_name; 
 
ttitle off 
 
clear breaks
clear computes

column "Tablespace Name" format  A15
column "Total Bytes" format 99,999,999,999
column "Bytes Free" format 99,999,999,999
column "Bytes Used" format 99,999,999,999
column "% Used" format 9999.999
break on report
compute sum of "Total Bytes" on report
compute sum of "Bytes Free" on report
compute sum of "Bytes Used" on report
--compute avg of "% Used" on report

TTitle left "***   Database:  "dbname", Tablespace Usage ( As of:  "xdate" )   *******" skip 1

select  substr(fs.FILE_ID,1,3) "ID#",
        fs.tablespace_name "Tablespace Name",
        df.bytes "Total Bytes",
        sum(fs.bytes) "Bytes Free",
        df.bytes-sum(fs.bytes) "Bytes Used",
    (100*((df.bytes-sum(fs.bytes))/df.bytes)) "% Used"
from sys.dba_data_files df, sys.dba_free_space fs
where df.file_id(+) = fs.file_id  and
 substr(fs.tablespace_name,1,4) = 'PINX'
group by fs.FILE_ID, fs.tablespace_name, df.bytes, df.blocks
order by fs.tablespace_name;

ttitle off

clear breaks
clear computes

column "Tablespace Name" format  A15
column "Total Bytes" format 99,999,999,999
column "Bytes Free" format 99,999,999,999
column "Bytes Used" format 99,999,999,999
column "% Used" format 9999.999
break on report
compute sum of "Total Bytes" on report
compute sum of "Bytes Free" on report
compute sum of "Bytes Used" on report
--compute avg of "% Used" on report

TTitle left "***   Database:  "dbname", Tablespace Usage ( As of:  "xdate" )   *******" skip 1

select  substr(fs.FILE_ID,1,3) "ID#",
        fs.tablespace_name "Tablespace Name",
        df.bytes "Total Bytes",
        sum(fs.bytes) "Bytes Free",
        df.bytes-sum(fs.bytes) "Bytes Used",
    (100*((df.bytes-sum(fs.bytes))/df.bytes)) "% Used"
from sys.dba_data_files df, sys.dba_free_space fs
where df.file_id(+) = fs.file_id  and
 substr(fs.tablespace_name,1,3) != 'PIN'
group by fs.FILE_ID, fs.tablespace_name, df.bytes, df.blocks
order by fs.tablespace_name;

ttitle off

rem ------------------------------------------------------------- 
rem ------------------------------------------------------------- 
 
spool off 
set feedback on 
-- exit 
 
