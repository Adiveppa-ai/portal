!mkdir -p /oracle/oradata/demo
!setenv ORACLE_SID demo
!echo Add this entry in the oratab: demo:/oracle/920:N
!rm -f /oracle/920/dbs/orapwdemo
!/oracle/920/bin/orapwd file=/oracle/920/dbs/orapwdemo password=sys

connect SYS/change_on_install as SYSDBA
set echo on
spool /oracle/admin/demo/create/CreateDB.log
startup nomount pfile="/oracle/admin/demo/pfile/initdemo.ora";
CREATE DATABASE demo
MAXINSTANCES 1
MAXLOGHISTORY 1
MAXLOGFILES 16
MAXLOGMEMBERS 3
MAXDATAFILES 256
DATAFILE '/oracle/oradata/demo/system' SIZE 512m REUSE EXTENT MANAGEMENT LOCAL
DEFAULT TEMPORARY TABLESPACE TEMP TEMPFILE 
'/oracle/oradata/demo/temp' SIZE 256m REUSE 
UNDO TABLESPACE "UNDOTBS1" DATAFILE 
'/oracle/oradata/demo/rbs1' SIZE 256m REUSE
CHARACTER SET UTF8
NATIONAL CHARACTER SET UTF8
LOGFILE GROUP 1 ('/oracle/oradata/demo/redo1') SIZE 256m,
GROUP 2 ('/oracle/oradata/demo/redo2') SIZE 256m;
spool off

spool /oracle/admin/demo/create/CreateDBCatalog.log
@/oracle/920/rdbms/admin/catalog.sql;
@/oracle/920/rdbms/admin/catrep.sql;
@/oracle/920/rdbms/admin/catproc.sql;
@/oracle/920/rdbms/admin/catexp7.sql;
@/oracle/920/rdbms/admin/catblock.sql;
connect SYSTEM/manager
@/oracle/920/sqlplus/admin/pupbld.sql;
spool off

connect SYS/change_on_install as SYSDBA
set echo on
spool /oracle/admin/demo/create/postDBCreation.log1
@/oracle/920/rdbms/admin/utlrp.sql;
shutdown ;
connect SYS/change_on_install as SYSDBA
set echo on
spool /oracle/admin/demo/create/postDBCreation.log2
create spfile='/oracle/920/dbs/spfiledemo.ora' FROM pfile='/oracle/admin/demo/pfile/initdemo.ora';
startup ;

create tablespace PIN00 datafile '/oracle/oradata/demo/pin00.dbf' size 2000m REUSE EXTENT MANAGEMENT LOCAL UNIFORM SIZE 1M SEGMENT SPACE MANAGEMENT AUTO;

create tablespace PINX00 datafile '/oracle/oradata/demo/pinx00.dbf' size 2000m REUSE EXTENT MANAGEMENT LOCAL UNIFORM SIZE 1M SEGMENT SPACE MANAGEMENT AUTO;

create user pin identified by pin default tablespace pin00 temporary tablespace temp;
grant resource,connect to pin;
grant create table, create view, create snapshot, create any snapshot, create trigger to pin;
grant execute on dbms_aq to pin;
grant execute on dbms_aqadm to pin;
grant execute on dbms_lock to pin;

exit;
