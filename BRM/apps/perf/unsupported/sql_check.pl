#
#	@(#)sql_check.pl 1.0 2000/10/01
#       
# Copyright (c) 1996, 2017, Oracle and/or its affiliates. All rights reserved.
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#
####################################################################
# the script below could be used to find all SQL statements generated
# from application. This is done by checking Oracle system V$ views.
# Script makes snapshot from Oracle area then wait specified time 
# ( assuming that application will work during this waiting period )
# and read information again. The difference between data read first
#  time and second time is result of application work.  
# Script displays : how many time each SQL was executed, how many rows
# were read from DB, how many times rollback was used,...
####################################################################
$SYS_OWNER="system";
$CONF_DBNAME="larry";
$ORACLE_VERSION="Oracle8";
$RUN_TIME=40;      # run time in seconds
### parameters below may be used to limit number of sqls to process
### number of available sqls is count(*) from v$sqlarea
$SQL_NUM = 2000;  # max number of sqls to process
$SQL_STMT = "%";   # pattern for LIKE to select only 
		   # specific interesting sql statements ( <= SQL_NUM)
$ORDER_BY = "executions";  # could be : executions, parse_calls, disk_reads, 
			   # buffer_gets or any column from v$sqlarea
			   # NOTE: this is only for selection from
			   # the system view , result will be displaying always
			   # in descending order of number of executions

#=============================================================================
# check what operation system we are running on
# $^O will return name of OS
if ( $^O =~ /win/i )
{
# NT computer ( actually any windows operation system )
# Command to run sqlplus
$PIN_CONF_SQLPLUS     = "plus80 -s";
# For Windows NT Oracle 8 has a different batch sql processor
if ( $ORACLE_VERSION =~ /^Oracle8i$/i ) {
$PIN_CONF_SQLPLUS     = "sqlplus -s";
}

# Temporary directory to create files
$PIN_CONF_TEMPDIR     = "C:/temp";
$MOVE="move";
}
else
{
# UNIX assignment
# Command to run sqlplus
$PIN_CONF_SQLPLUS       = "sqlplus -s";

# Temporary directory to create files
$PIN_CONF_TEMPDIR       = "/tmp";
$MOVE="mv";
}

$sqlout="";
#--------------------------------------
#--------------------------------------
$sqlcommand =<<ENDSQL
set feed 0
set serveroutput on size  500000
variable temps varchar2(50);
variable old_parse number;
variable old_exec number;
variable old_commit number;
variable old_logic_reads number;
variable old_physic_reads number;
variable old_rollback_reads number;

DECLARE
mycount number;
cursor1 integer;
cursor2 integer;
old_hash_value DBMS_SQL.NUMBER_TABLE;
old_exec DBMS_SQL.NUMBER_TABLE;
old_parse DBMS_SQL.NUMBER_TABLE;
old_disk_reads DBMS_SQL.NUMBER_TABLE;
old_buffer_gets DBMS_SQL.NUMBER_TABLE;
row_count1 number;
select_stmt VARCHAR2(1000);
aux_stmt VARCHAR2(500);
batch_size constant integer:= $SQL_NUM;

BEGIN
--  create temporary table ( drop before )
        cursor2 := DBMS_SQL.OPEN_CURSOR;
    BEGIN
	aux_stmt := 'Drop table v\$sql_temporary';
	DBMS_SQL.PARSE ( cursor2, aux_stmt, DBMS_SQL.V7 );
	row_count1 := DBMS_SQL.EXECUTE(cursor2);
	-- ignore error if table not exist
	EXCEPTION
	 WHEN OTHERS THEN
	  if SQLCODE != -942 THEN
	    RAISE;
	 END IF;
    END;
	aux_stmt := 'Create table v\$sql_temporary (';
	aux_stmt := aux_stmt || 'sqlhash_value number,';
	aux_stmt := aux_stmt || 'sqlexec number,';
	aux_stmt := aux_stmt || 'sqlparse number,';
	aux_stmt := aux_stmt || 'sqlreads number,';
	aux_stmt := aux_stmt || 'sqlgets number)';
	DBMS_SQL.PARSE ( cursor2, aux_stmt, DBMS_SQL.V7 );
	row_count1 := DBMS_SQL.EXECUTE(cursor2);
dbms_output.put_line('   ');
dbms_output.put_line('   System and SQL Statistics in Infranet\n');
dbms_output.put_line('   ');
SELECT to_char(sysdate, 'DD/MM/YYYY HH24:MI:SS') into :temps
   FROM dual ;
dbms_output.put_line('   Begin: ' || :temps );
dbms_output.put_line('   ');

select value into :old_parse from v\$sysstat where name like '%parse count%total%'
;
select value into :old_exec from v\$sysstat where name like '%execute count%';
select value into :old_commit from v\$sysstat where name like '%user%commit%';
select value into :old_physic_reads from v\$sysstat where name = 'physical reads';
select sum (decode ( name, 'consistent gets', value, 0 )) + 
   sum (decode ( name, 'db block gets', value, 0 )) 
	into :old_logic_reads from v\$sysstat;
select sum(gets) into :old_rollback_reads from v\$rollstat;

	select_stmt := 'select hash_value, executions, parse_calls,disk_reads, buffer_gets from v\$sqlarea where rownum <= $SQL_NUM and sql_text like ' ||  '''' || '$SQL_STMT' || '''' || 'AND parsing_user_id != (select user_id from dba_users where username=' || '''' || 'SYSTEM' || '''' || ') AND parsing_user_id != (select user_id from dba_users where username=' || '''' || 'SYS' || '''' || ') order by $ORDER_BY';
        cursor1 := DBMS_SQL.OPEN_CURSOR;
	DBMS_SQL.PARSE ( cursor1, select_stmt, DBMS_SQL.V7 );
	DBMS_SQL.DEFINE_ARRAY(cursor1,1,old_hash_value, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor1,2,old_exec, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor1,3,old_parse, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor1,4,old_disk_reads, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor1,5,old_buffer_gets, batch_size, 1 );
	row_count1 := DBMS_SQL.EXECUTE_AND_FETCH(cursor1,FALSE);
	DBMS_SQL.COLUMN_VALUE(cursor1,1,old_hash_value);
	DBMS_SQL.COLUMN_VALUE(cursor1,2,old_exec);
	DBMS_SQL.COLUMN_VALUE(cursor1,3,old_parse);
	DBMS_SQL.COLUMN_VALUE(cursor1,4,old_disk_reads);
	DBMS_SQL.COLUMN_VALUE(cursor1,5,old_buffer_gets);

	-- insert into temp table
	aux_stmt := 'Insert into v\$sql_temporary VALUES (';
	aux_stmt := aux_stmt || ':sqlhash_value ,';
	aux_stmt := aux_stmt || ':sqlexec ,';
	aux_stmt := aux_stmt || ':sqlparse,';
	aux_stmt := aux_stmt || ':sqlreads,';
	aux_stmt := aux_stmt || ':sqlgets )';
	DBMS_SQL.PARSE ( cursor2, aux_stmt, DBMS_SQL.V7 );
	DBMS_SQL.BIND_ARRAY(cursor2,':sqlhash_value',old_hash_value, 1, row_count1 );
	DBMS_SQL.BIND_ARRAY(cursor2,':sqlexec',old_exec, 1, row_count1 );
	DBMS_SQL.BIND_ARRAY(cursor2,':sqlparse',old_parse, 1, row_count1 );
	DBMS_SQL.BIND_ARRAY(cursor2,':sqlreads',old_disk_reads, 1, row_count1 );
	DBMS_SQL.BIND_ARRAY(cursor2,':sqlgets',old_buffer_gets, 1, row_count1 );
	row_count1 := DBMS_SQL.EXECUTE(cursor2);

	DBMS_SQL.CLOSE_CURSOR(cursor1);
	DBMS_SQL.CLOSE_CURSOR(cursor2);
end;
/
!sleep $RUN_TIME
declare
parse number;
exec number;
commit number;
logic_reads number;
physic_reads number;
rollback_reads number;
flag number;
tmpcount3 number;
cursor1 integer;
cursor2 integer;
old_hash_value DBMS_SQL.NUMBER_TABLE;
old_exec DBMS_SQL.NUMBER_TABLE;
old_parse DBMS_SQL.NUMBER_TABLE;
old_disk_reads DBMS_SQL.NUMBER_TABLE;
old_buffer_gets DBMS_SQL.NUMBER_TABLE;
new_hash_value DBMS_SQL.NUMBER_TABLE;
new_exec DBMS_SQL.NUMBER_TABLE;
new_parse DBMS_SQL.NUMBER_TABLE;
new_disk_reads DBMS_SQL.NUMBER_TABLE;
new_buffer_gets DBMS_SQL.NUMBER_TABLE;
row_count1 number;
row_count2 number;
select_stmt VARCHAR2(1000);
aux_stmt VARCHAR2(500);
sqltmp VARCHAR2(1000);
valuetmp number;
batch_size constant integer:= $SQL_NUM;
cursor sql_cursor is
	select distinct piece, sql_text from v\$sqltext
			where hash_value = valuetmp and rownum < 36 order by piece;

begin
select value into parse from v\$sysstat where name like '%parse count%total%';
select value into exec from v\$sysstat where name like '%execute count%';
select value into commit from v\$sysstat where name like '%user%commit%';
select value into physic_reads from v\$sysstat where name = 'physical reads';
select sum (decode ( name, 'consistent gets', value, 0 )) + 
   sum (decode ( name, 'db block gets', value, 0 )) 
	into logic_reads from v\$sysstat;
select sum(gets) into rollback_reads from v\$rollstat;
dbms_output.put_line('General Statistic: Executions: ' || to_char (exec - :old_exec) || ' Parses: ' || to_char (parse - :old_parse) );
dbms_output.put_line('User Commits: ' || to_char (commit - :old_commit) || ' Disk reads: ' || to_char (physic_reads - :old_physic_reads));
dbms_output.put_line('Logical Reads: ' || to_char (logic_reads - :old_logic_reads) || ' Rollback reads: ' || to_char (rollback_reads - :old_rollback_reads));
dbms_output.put_line('\n-----------------------------------------------------------------------------\n ');
SELECT to_char(sysdate, 'DD/MM/YYYY HH24:MI:SS') into :temps
   FROM dual ;
   
        cursor1 := DBMS_SQL.OPEN_CURSOR;
        cursor2 := DBMS_SQL.OPEN_CURSOR;
	select_stmt := 'select hash_value, executions, parse_calls,disk_reads, buffer_gets from v\$sqlarea where rownum <= $SQL_NUM and sql_text like ' ||  '''' || '$SQL_STMT' || '''' || 'AND parsing_user_id != (select user_id from dba_users where username=' || '''' || 'SYSTEM' || '''' || ') AND parsing_user_id != (select user_id from dba_users where username=' || '''' || 'SYS' || '''' || ') order by $ORDER_BY';
	DBMS_SQL.PARSE ( cursor1, select_stmt, DBMS_SQL.V7 );
	DBMS_SQL.DEFINE_ARRAY(cursor1,1,new_hash_value, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor1,2,new_exec, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor1,3,new_parse, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor1,4,new_disk_reads, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor1,5,new_buffer_gets, batch_size, 1 );
	row_count2 := DBMS_SQL.EXECUTE_AND_FETCH(cursor1,FALSE);
	DBMS_SQL.COLUMN_VALUE(cursor1,1,new_hash_value);
	DBMS_SQL.COLUMN_VALUE(cursor1,2,new_exec);
	DBMS_SQL.COLUMN_VALUE(cursor1,3,new_parse);
	DBMS_SQL.COLUMN_VALUE(cursor1,4,new_disk_reads);
	DBMS_SQL.COLUMN_VALUE(cursor1,5,new_buffer_gets);

----  reading old information from temporary table
	select_stmt := 'select sqlhash_value, sqlexec, sqlparse,sqlreads, sqlgets from v\$sql_temporary';
	DBMS_SQL.PARSE ( cursor2, select_stmt, DBMS_SQL.V7 );
	DBMS_SQL.DEFINE_ARRAY(cursor2,1,old_hash_value, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor2,2,old_exec, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor2,3,old_parse, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor2,4,old_disk_reads, batch_size, 1 );
	DBMS_SQL.DEFINE_ARRAY(cursor2,5,old_buffer_gets, batch_size, 1 );
	row_count1 := DBMS_SQL.EXECUTE_AND_FETCH(cursor2,FALSE);
	DBMS_SQL.COLUMN_VALUE(cursor2,1,old_hash_value);
	DBMS_SQL.COLUMN_VALUE(cursor2,2,old_exec);
	DBMS_SQL.COLUMN_VALUE(cursor2,3,old_parse);
	DBMS_SQL.COLUMN_VALUE(cursor2,4,old_disk_reads);
	DBMS_SQL.COLUMN_VALUE(cursor2,5,old_buffer_gets);

--- calculation of all data for time being running
	FOR tmpcount2 IN 1..row_count2 LOOP
	 FOR tmpcount1 IN 1..row_count1 LOOP
		IF ( new_hash_value(tmpcount2) = old_hash_value(tmpcount1 ) )  THEN
                       new_exec (tmpcount2) :=
			      new_exec (tmpcount2) - old_exec(tmpcount1);
		        new_parse (tmpcount2) := 
			      new_parse (tmpcount2) - old_parse(tmpcount1);
                        new_disk_reads (tmpcount2) := 
			      new_disk_reads (tmpcount2) - old_disk_reads(tmpcount1);
		        new_buffer_gets (tmpcount2) :=
			      new_buffer_gets (tmpcount2) - old_buffer_gets(tmpcount1);
		EXIT ;
		END IF;
           END LOOP;
        END LOOP;
--- sort result ( primitive algorithm )
        LOOP
	flag := 0;
	 FOR tmpcount2 IN 2..row_count2 LOOP
		tmpcount3 := tmpcount2 - 1;
		IF ( new_exec(tmpcount2) > new_exec(tmpcount3 ) )  THEN
		-- exchange records
		valuetmp := new_hash_value(tmpcount2 );
		new_hash_value(tmpcount2) := new_hash_value(tmpcount3 );
		new_hash_value(tmpcount3 ) := valuetmp;
		valuetmp := new_exec(tmpcount2 );
		new_exec(tmpcount2 ) := new_exec(tmpcount3 );
		new_exec(tmpcount3 ) := valuetmp;
		valuetmp := new_parse(tmpcount2 );
		new_parse(tmpcount2 ) := new_parse(tmpcount3 );
		new_parse(tmpcount3 ) := valuetmp;
		valuetmp := new_disk_reads(tmpcount2 );
		new_disk_reads(tmpcount2 ) := new_disk_reads(tmpcount3 );
		new_disk_reads(tmpcount3 ) := valuetmp;
		valuetmp := new_buffer_gets(tmpcount2 );
		new_buffer_gets(tmpcount2 ) := new_buffer_gets(tmpcount3 );
		new_buffer_gets(tmpcount3 ) := valuetmp;
		flag := 1;
		END IF;
           END LOOP;
	   EXIT WHEN ( flag = 0 );
        END LOOP;
--- display resulting data
	FOR tmpcount2 IN 1..row_count2 LOOP
	 IF (  new_exec (tmpcount2) > 0 ) THEN
           dbms_output.put_line( '----------------------------------------------------------\n' );
           valuetmp := new_hash_value(tmpcount2 );
           dbms_output.put_line('SQL statement: \n' );
	   open sql_cursor;
	   LOOP
	   	fetch sql_cursor into flag, sqltmp;
	   	EXIT WHEN sql_cursor%NOTFOUND;
           	dbms_output.put_line(sqltmp);
	   END LOOP;
	   close sql_cursor;
           dbms_output.put_line('\n');
           dbms_output.put_line('SQL Statistic: Executions: ' || to_char (new_exec (tmpcount2) ) || ' Parses: ' || to_char (new_parse (tmpcount2) ) );
           dbms_output.put_line('SQL Statistic: Disk Reads: ' || to_char (new_disk_reads (tmpcount2) ) || ' Buffer Gets: ' || to_char (new_buffer_gets (tmpcount2) ) );
	   END IF;
        END LOOP;

dbms_output.put_line('----------------------------------------------------------------------------- ');
dbms_output.put_line('   ');
dbms_output.put_line('   End: ' || :temps );
dbms_output.put_line('   ');

	DBMS_SQL.CLOSE_CURSOR(cursor1);
	DBMS_SQL.CLOSE_CURSOR(cursor2);

        cursor2 := DBMS_SQL.OPEN_CURSOR;

	aux_stmt := 'Drop table v\$sql_temporary';
	DBMS_SQL.PARSE ( cursor2, aux_stmt, DBMS_SQL.V7 );
	row_count1 := DBMS_SQL.EXECUTE(cursor2);
	-- ignore error if table not exist
	EXCEPTION
	 WHEN OTHERS THEN
	  if SQLCODE != -942 THEN
	    RAISE;
	 END IF;

	DBMS_SQL.CLOSE_CURSOR(cursor2);
END;
/


ENDSQL
;

exec_sqlcommand($CONF_DBNAME,$sqlcommand);

###############################################################################
# 2 functions below I stole from pin_init_utils
###############################################################################
# exec_sqlcommand()
#       input:
#               sql command(s)
###############################################################################
sub exec_sqlcommand {
	local ($db_connect,$cmd) = @_;
	local ($status) = 0;
	local ($exitcode) = 0;
	local ($tmpfile) = "$PIN_CONF_TEMPDIR/pintmp$$.sql";
	# Create a temporary file with the sqlplus input.
	#
	open(TMPFILE, ">$tmpfile") || die "$ME: cannot create $tmpfile\n";
	print TMPFILE "$cmd";
	print TMPFILE "\nexit;\n";
	close(TMPFILE);

	$OWNER="$SYS_OWNER";
	$PASSWD="$SYS_PASSWD";
	
	#
	# Cheese 1: SQLPLUS gives a zero status back if the user/passwd is
	# wrong. So, instead of using system(), we need to capture the output
	# of SQLPLUS and parse it to see if there was an error.
	#
	$sqlout = `$PIN_CONF_SQLPLUS /\@$db_connect < $tmpfile`;
	$exitcode = $?;
	$status = ($? >> 8);

       printout("$sqlout");
        unlink "$tmpfile";

       if ($sqlout =~ m/ERROR: /) {
       printt("$ME: SQLPLUS failed (exitcode = $exitcode)\n");
       exit(1);
       }

       #
       # Cheese 2: on NT, we are getting the exit status as is in $?...
       # so, $status after right shifting becomes 0! So, check for
       # non-zero $? even though it is not "absolutely" right on unix.
       #
       if ($status || $exitcode) {
       print("$ME: $PIN_CONF_SQLPLUS failed with status $status\n");
       exit (1);
       }
}

###############################################################################
# printout
#       input:
#               string to be printed out
###############################################################################
sub printout {
	local ($outstr) = @_;

	syswrite STDOUT, $outstr, length($outstr);
	}

1;


