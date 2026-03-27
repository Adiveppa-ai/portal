#
#	@(#) % %
#       
#       Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#

require "..\ms_conf.pm";
######################################################################
## Configuration stuff
######################################################################

#############################
# below is parameters structure
# 1)server where remote db located; 
# 2)name of remote db; 
# 3) starting id for portion of accounts created;
# 4)number accounts created;
############################
@ACCOUNTS= (
	  "intrepid" , "demo", 3000, 25, 
	  );
#--------------------------------------------
# end of configuration section
#--------------------------------------------
#=============================================================================
# Temporary directory to create files
$PIN_CONF_TEMPDIR     = "C:/temp";
#--------------------------------------
#--------------------------------------
$currtime0 = time();

$index = 0;
$total_num_accnts= 0;
while ( $index < @ACCOUNTS ) {

$currtime1 = time();
$db_server = @ACCOUNTS[$index];
$db_name = @ACCOUNTS[$index+1];
$beg_id0 = @ACCOUNTS[$index+2];
$num_accounts = @ACCOUNTS[$index+3];

$index = $index +4;

#########################
# find DB_NO and Service poid from remote DB
########################
$sqlcommand =<<SQLPLUSENDPROC
set NOCOUNT on
set ROWCOUNT 1 
select POID_DB, ACCOUNT_OBJ_ID0 from service_t where LOGIN = 'user' + CONVERT(char(20),$beg_id0)
go
set ROWCOUNT 4 
select POID_ID0, POID_TYPE from service_t where LOGIN = 'user' + CONVERT(char(20),$beg_id0) or LOGIN = CONVERT(char(20),$beg_id0) + '\@portal.com'
go
SQLPLUSENDPROC
;

##################################################
	open(OFILE, ">exfile") || die "$ME: cannot open $exfile\n";
	printf OFILE "%s", $sqlcommand;
	close(OFILE);

##################################################
#  execute prepared file
#################################################
$sqlout = `isql -n -h-1 -U $CONF_OWNER -P $CONF_PASSWD -d $db_name -S $db_server -i exfile `;

$serv_id[0] = 0;
$serv_id[1] = 0;
$serv_id[2] = 0;
$serv_id[3] = 0;

($db_no,$start_acct,$serv_id[0],$serv[0],$serv_id[1],$serv[1],$serv_id[2],$serv[2],$serv_id[3],$serv[3])=split (' ',$sqlout,99);

$num_services = 0;

($db_no != 'no') || die ("Parameters for DB $db_name set improperly \n");

# calculate how many services in this account
while ( $serv_id[$num_services] && $num_services < 4  ) {
$num_services++;
};

$sqlcmnd_array =<<SQLPLUSEND 
DECLARE \@service_type char(255)
DECLARE \@login_name char(255)
DECLARE \@db_id int
DECLARE \@beg_id int      -- uniqueness poid
DECLARE \@counts int
DECLARE \@init_id0 int    -- account_poid
DECLARE \@service_id int    -- service_poid
DECLARE \@user_id0 int    -- login number
DECLARE \@create_t int
DECLARE \@num_accounts_inserted int

-- 
-- set up cursors to fetch some of the configuration stuff from the database.
--
-- Get the DB no
declare db_id0 cursor for 
	select poid_db, created_t from account_t 
		where poid_id0 = 1

-- Get the info from uniqueness_t on primary DB
declare unique_id0 cursor for
	select max(poid_id0) from uniqueness_t

	-- db no
	open db_id0
	fetch next from db_id0 into \@db_id, \@create_t
	close db_id0
	deallocate db_id0

	-- max(poid_id0) from unique_t
	open unique_id0
	fetch next from unique_id0 into \@beg_id
	close unique_id0
	deallocate unique_id0

	set \@num_accounts_inserted = 0
	set \@init_id0 = $start_acct     -- starting poid in account_t
	set \@user_id0 = $beg_id0
        set \@beg_id = \@beg_id +1
	while ( \@num_accounts_inserted < $num_accounts )
	BEGIN
          set \@counts = 1
          WHILE ( \@counts <= $num_services)
	  BEGIN

	   if ( \@counts = 1 )
	   BEGIN
		set \@service_type = '$serv[0]'
	        set \@service_id = $serv_id[0] + \@num_accounts_inserted
	   END     
	   if ( \@counts = 2 )
	   BEGIN
		set \@service_type = '$serv[1]'
	        set \@service_id = $serv_id[1] + \@num_accounts_inserted
	   END     
	   if ( \@counts = 3 )
	   BEGIN
		set \@service_type = '$serv[2]'
	        set \@service_id = $serv_id[2] + \@num_accounts_inserted
	   END     
	   if ( \@counts = 4 )
	   BEGIN
		set \@service_type = '$serv[3]'
	        set \@service_id = $serv_id[3] + \@num_accounts_inserted
	   END     

	   if ( \@service_type = '/service/email' )
	   BEGIN
		set \@login_name = CONVERT(char(30),\@user_id0) + '\@portal.com'
	   END     
           ELSE
	   BEGIN
		set \@login_name = 'user' + CONVERT(char(30),\@user_id0)
	   END     

		INSERT INTO uniqueness_t (
			poid_db, poid_id0, poid_type, poid_rev,
			created_t, mod_t,
			--
			account_obj_db, account_obj_id0, account_obj_type,
			service_obj_db, service_obj_id0, service_obj_type,
			--
			read_access, write_access,
			login,
			status, account_no
		) VALUES (
			\@db_id, \@beg_id, '/uniqueness', 1,
			\@create_t, \@create_t,
			--
			$db_no, \@init_id0, '/account',
			$db_no, \@service_id, \@service_type,
			--
			'G','S',
			\@login_name,2,
			'0.0.0.' + CONVERT(char(2),$db_no) + '-' + CONVERT(char(60),\@user_id0)
			);
		set \@beg_id = \@beg_id + 1
		set \@counts = \@counts + 1

             END
             set \@num_accounts_inserted = \@num_accounts_inserted + 1
             set \@init_id0 = \@init_id0 + 1
	     set \@user_id0 = \@user_id0 + 1
        END 
																 --
GO

SQLPLUSEND
;

##################################################
	open(OFILE, ">exfile") || die "$ME: cannot open $exfile\n";
	printf OFILE "%s", $sqlcmnd_array;
	close(OFILE);

##################################################
#  execute prepared file
#################################################
`isql -U $CONF_OWNER -P $CONF_PASSWD -d $CONF_DBNAME -S $CONF_SERVER -i exfile -o outfile`;


$currtime2 = time();
$elapstime = $currtime2 - $currtime1;
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
$accounts = $num_accounts * $num_services;
$total_num_accnts = $total_num_accnts + $accounts;
print "***************************************************************\n";
printf " $accounts accounts  from db $db_name were processed in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
print "***************************************************************\n";
# go to the next DB from config array
}

$currtime2 = time();
$elapstime = $currtime2 - $currtime0;
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
$accounts = $total_num_accnts;
print "***************************************************************\n";
printf " $accounts accounts were processed in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
print "***************************************************************\n";

1;
