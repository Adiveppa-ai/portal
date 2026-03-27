#
#	@(#) % %
#       
#       Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#

######################################################################
## ms_subord_cre - creates 1 level of subordinate accounts for SQL server
######################################################################
## Configuration stuff
######################################################################
require "../ms_conf.pm";
#---------------------------------------------------------------------
# pinaft outputs create_t (today), actg_next_t, actg_future_t and 
# actg_dom. Note that if today is 29-31 then actg_dom, actg_next_t and 
# actg_future_t will be auto adjusted to 1st.
#---------------------------------------------------------------------
$PINAFT_OUTPUT=`./pinaft`;
($CONF_CREATE_T,$CONF_ACTG_DOM,$CONF_ACTG_NEXT_T,$CONF_ACTG_FUTURE_T,
   $CONF_DATE_STRG ) = split (' ',$PINAFT_OUTPUT,99);

$CONF_NUM_PARENTS=10; # number of parents, subords evenly divided

$CONF_NUM_ACNT=70;  # number accounts to create per thread
$CONF_BEG_ID0=10000; # first login id to process
$CONF_NUM_THREADS=1;    # leave at 1, NOT design/tested for multithread

$CONF_DEBUG=false;

$CONF_DATE_STR="'$CONF_DATE_STRG'";
#--------------------------------------------
# end of configuration section
#--------------------------------------------

# test if trying to run multithreaded (TBD)
if ($CONF_NUM_THREADS > 1)
{
  print("Exiting: Run with threads=1\n");
  exit(0);
}

# test if more parents than accounts
if ($CONF_NUM_ACNT < $CONF_NUM_PARENTS)
{
  print("Exiting: More parents than accounts\n");
  exit(0);
}

#=============================================================================
# Temporary directory to create files
$PIN_CONF_TEMPDIR     = "C:\\temp";

$current_thread=$CONF_NUM_THREADS;
if ( $CONF_BEG_ID0 > 0 ) { 
$beg_id0=$CONF_BEG_ID0;
} else {
  print("Exiting: Set beginning ID0\n");
  exit(0);
}
$currtime1 = time();

$family_size = int $CONF_NUM_ACNT/$CONF_NUM_PARENTS;

#--------------------------------------
$sqlcommand =<<SQL;
  SET QUOTED_IDENTIFIER ON
  GO
DECLARE \@count int
DECLARE  \@i int
DECLARE  \@db_no int
DECLARE  \@curr_acct_id0 int
DECLARE  \@memb_no int
DECLARE  \@rec_no int
DECLARE  \@par_id0 int
DECLARE  \@item_id0 int
DECLARE  \@chd_count int
DECLARE  \@grp_seq_no int
DECLARE  \@bill_type int
DECLARE  \@payinfo_no int
DECLARE  \@sub_id0 int
DECLARE  \@login1 char(60)
DECLARE  \@item_poidlist char(160)

-- Get the DB no
declare db_id cursor for
	select poid_db from account_t
			where poid_id0 = 1

-- Get the cursor for sequence
declare db_id1 cursor for
	select max(poid_id0) from poid_ids


  open db_id
  fetch next from db_id into \@db_no
  close db_id
  deallocate db_id

  open db_id1
  fetch next from db_id1 into \@grp_seq_no
  close db_id1
  deallocate db_id1

  set \@count = 0

  WHILE ( \@count < ${CONF_NUM_ACNT} )
	BEGIN

    set \@login1 = 'user' + CONVERT ( char(60), ${CONF_BEG_ID0} + \@count )
    BEGIN
    declare login_c cursor for
      SELECT account_obj_id0 FROM service_t where login = \@login1

    open login_c
    fetch next from login_c into \@curr_acct_id0
    close login_c
    deallocate login_c
    END
    set \@memb_no = \@count % ${family_size}
    IF (\@memb_no = 0)
    BEGIN
-- <<start parent account>>
      set \@par_id0 = \@curr_acct_id0
      IF (\@count < (${CONF_NUM_PARENTS} * ${family_size})) 
       BEGIN
--    complete group
	set \@chd_count = ${family_size}-1
       END
      ELSE
       BEGIN
--    partial group
	set \@chd_count = ${CONF_NUM_ACNT} % ${CONF_NUM_PARENTS} - 1
       END

-- get next poid value for new group
      select \@grp_seq_no = \@grp_seq_no + 1

-- Process parent tables:
--
-- create new group for parent
      INSERT INTO group_t (
	POID_DB,POID_ID0,POID_TYPE,POID_REV,
	CREATED_T,MOD_T,"COUNT",
	DESCR,NAME,
	PARENT_DB,PARENT_ID0,PARENT_TYPE,
	STATUS,
	TYPE_STR ) VALUES (
	\@db_no,\@grp_seq_no,'/group/billing',1,
	${CONF_CREATE_T},${CONF_CREATE_T},\@chd_count,
	'','',
	\@db_no,\@curr_acct_id0,'/account',
	0,'Billing Hierarchy')

-- update account as parent
      UPDATE account_t SET
	MOD_T=${CONF_CREATE_T},
	GROUP_OBJ_DB=\@db_no,
	GROUP_OBJ_ID0=\@grp_seq_no,
	GROUP_OBJ_TYPE='/group/billing'
      WHERE POID_ID0=\@curr_acct_id0

-- <<end parent account>>
      END
    ELSE
      BEGIN
-- <<start subordinate account>>

-- Get the cursor for bill_type
      declare db_id2 cursor for
        	SELECT bill_type,payinfo_obj_id0,item_poid_list FROM account_t
			  WHERE poid_id0=\@curr_acct_id0
-- get payinfo poid value for deletion from payinfo_{cc/inv}_t
      open db_id2
      fetch next from db_id2 into \@bill_type, \@payinfo_no ,\@item_poidlist
      close db_id2
      deallocate db_id2

-- set subord payinfo poid entry
     set \@sub_id0 = \@payinfo_no
     set \@rec_no = \@memb_no-1

-- Process child tables:
--
-- add subord to billing group
      INSERT INTO group_billing_members_t (
	OBJ_ID0,REC_ID,
	OBJECT_DB,OBJECT_ID0,OBJECT_TYPE ) VALUES (
	\@grp_seq_no,\@rec_no,
	\@db_no,\@curr_acct_id0,'/account')
       
-- create subord payinfo object
      INSERT INTO payinfo_subord_t (
	OBJ_ID0,REC_ID,
	AR_ACCOUNT_OBJ_DB,AR_ACCOUNT_OBJ_ID0,AR_ACCOUNT_OBJ_TYPE ) VALUES (
	\@sub_id0,0,
	\@db_no,\@par_id0,'/account')

-- delete subord from cc/inv payinfo table
      IF (\@bill_type=10003) 
       BEGIN 
        DELETE FROM payinfo_cc_t WHERE OBJ_ID0=\@payinfo_no
       END 
      ELSE
       BEGIN 
        DELETE FROM payinfo_inv_t WHERE OBJ_ID0=\@payinfo_no
       END 


-- update account as subord
      UPDATE account_t SET
	MOD_T=${CONF_CREATE_T},
	BILL_TYPE=10007,
	PAYINFO_OBJ_TYPE='/payinfo/subord'
      WHERE POID_ID0=\@curr_acct_id0

-- update item_t as subord
-- find item poid from item poid list(hardcoded)
      set \@login1 = RTRIM ( \@item_poidlist)
      set \@item_id0 = DATALENGTH ( \@login1 )
      set \@item_poidlist = RTRIM(SUBSTRING( \@login1, 20, \@item_id0 -21 ))
      set \@item_id0 = CONVERT ( int ,\@item_poidlist )

      UPDATE item_t SET
	AR_ACCOUNT_OBJ_ID0 = \@par_id0,
	AR_BILL_OBJ_ID0 = \@par_id0
      WHERE POID_ID0=\@item_id0

-- update payinfo entry as subord
      UPDATE payinfo_t SET
	POID_TYPE='/payinfo/subord'
      WHERE POID_ID0=\@sub_id0
-- <<end subordinate account>>
    END 

        SELECT \@count        = \@count + 1
	END


	SET IDENTITY_INSERT poid_ids ON
	INSERT into POID_IDS ( poid_id0, text ) values (\@grp_seq_no, 'INFRANET')
	go

SQL
;
##################################################

        open(OFILE, ">exfile") || die "$ME: cannot open $exfile\n";
	printf OFILE "%s", $sqlcommand;
	close(OFILE);

##################################################
#  execute prepared file
#################################################
`isql -n -U $CONF_OWNER -P $CONF_PASSWD -d $CONF_DBNAME -S $CONF_SERVER -i exfile -o outfile`;

$currtime2 = time();
$elapstime = $currtime2 - $currtime1;
$ehours = $elapstime / 3600;
$elapstime = $elapstime % 3600;
$emin = $elapstime / 60;
$esec = $elapstime % 60;
$spares = $CONF_NUM_ACNT%$CONF_NUM_PARENTS;
$family_size = $family_size-1;
print "***************************************************************\n";
printf " $CONF_NUM_PARENTS parent(s) with $family_size children\n";
if ($spares!=0){
$spares=$spares-1;
printf "  plus 1 spare parent with $spares children\n";
}
printf " were created in %d h %d min %d sec.\n",
	   $ehours,$emin,$esec;
print "***************************************************************\n";

1;
