#!/bin/bash
ORACLE_DB_PRIMARY_USER=
ORACLE_DB_PRIMARY_PASSWD=
ORACLE_DB_PRIMARY_SID=
ORACLE_DB_SECONDARY_USER=
ORACLE_DB_SECONDARY_PASSWD=
ORACLE_DB_SECONDARY_SID=

TMPSTR2=

testDatabaseConnectivity () {
  tnsping $3 > /dev/null
  if [ $? -ne 0 ]
  then 
    echo -e "ERROR: Could not connect to the provided Oracle Database Server instance $3. Please make sure that all the provided values are correct."
    return 1
  fi
  
  {
  sqlplus $1/$2@$3 $LOGIN_OPTION_<<EOF
EOF
  } | grep -A1 "ERROR:"
  if [ $? -eq 0 ]
  then
    echo -e "ERROR: Could not login to the provided Oracle Database Server instance $3. Please make sure that all the provided values are correct."
    return 1
  fi

  return 0
}

loadFixScript () {
  echo -e "Load Fix PL/SQL For Oracle Database Schema $1...." >> fix_multi_schema.log

  {
  sqlplus $1/$2@$3<<EOF
@fix_data_dictionary.sql
EOF
  } > tmp.log

  cat tmp.log >> fix_multi_schema.log

  grep "ORA-" tmp.log
  if [ $? -eq 0 ]
  then
    echo -e "ERROR: Errors encountered during load fix script."
    echo -e "ERROR: Errors encountered during load fix script." >> fix_multi_schema.log
    exit 1
  fi

  echo -e "Done With Load...." >> fix_multi_schema.log
  echo

  return 0
}

grantPermToSecondary () {
  echo -e "Granting Permission On Primary DD Tables To Secondary User $1...." >> fix_multi_schema.log

  {
  sqlplus $ORACLE_DB_PRIMARY_USER/$ORACLE_DB_PRIMARY_PASSWD@$ORACLE_DB_PRIMARY_SID<<EOF
SET SERVEROUTPUT ON; 
SET LINESIZE 2000;
EXEC DBMS_OUTPUT.ENABLE(2000000);
EXEC PIN_FIX_DD.GRANT_DD('$1'); 
EOF
  } > tmp.log

  cat tmp.log >> fix_multi_schema.log

  grep "ORA-" tmp.log > /dev/null
  if [ $? -eq 0 ]
  then
    echo -e "ERROR: Errors encountered during grant."
    echo -e "ERROR: Errors encountered during grant." >> fix_multi_schema.log
    exit 1
  fi

  echo -e "Done With Grant...." >> fix_multi_schema.log
  echo

  return 0
}

fixDataDictionary () {
  echo -e "Fix DD Tables For Secondary User $1...." >> fix_multi_schema.log

  {
  sqlplus $1/$2@$3<<EOF
SET SERVEROUTPUT ON; 
SET LINESIZE 2000;
EXEC DBMS_OUTPUT.ENABLE(2000000);
EXEC PIN_FIX_DD.UPDATE_DD('$ORACLE_DB_PRIMARY_USER'); 
EOF
  } > tmp.log

  cat tmp.log >> fix_multi_schema.log

  grep "ORA-" tmp.log > /dev/null
  if [ $? -eq 0 ]
  then
    echo -e "ERROR: Errors encountered during fix dd."
    echo -e "ERROR: Errors encountered during fix dd." >> fix_multi_schema.log
    exit 1
  fi

  echo -e "Done With Fix DD For Secondary...." >> fix_multi_schema.log
  echo

  return 0
}

fixEvtData () {
  echo -e "Fix Event Data For Secondary User $1...." >> fix_multi_schema.log

  {
  sqlplus $1/$2@$3<<EOF
SET SERVEROUTPUT ON; 
SET LINESIZE 2000;
EXEC DBMS_OUTPUT.ENABLE(2000000);
EXEC PIN_FIX_DD.UPDATE_EVENTS(200); 
EOF
  } > tmp.log

  cat tmp.log >> fix_multi_schema.log

  grep "ORA-" tmp.log > /dev/null
  if [ $? -eq 0 ]
  then
    echo -e "ERROR: Errors encountered during fix event data."
    echo -e "ERROR: Errors encountered during fix event data." >> fix_multi_schema.log
    exit 1
  fi

  echo -e "Done With Fix Event Data For Secondary...." >> fix_multi_schema.log
  echo

  return 0
}

fixVirtData () {
  echo -e "Fix Virtual Column Data For Secondary User $1...." >> fix_multi_schema.log

  {
  sqlplus $1/$2@$3<<EOF
SET SERVEROUTPUT ON; 
SET LINESIZE 2000;
EXEC DBMS_OUTPUT.ENABLE(2000000);
EXEC PIN_FIX_DD.UPDATE_VIRTUAL_COLUMNS; 
EOF
  } > tmp.log

  cat tmp.log >> fix_multi_schema.log

  grep "ORA-" tmp.log > /dev/null
  if [ $? -eq 0 ]
  then
    echo -e "ERROR: Errors encountered during fix virtual column data."
    echo -e "ERROR: Errors encountered during fix virtual column data." >> fix_multi_schema.log
    exit 1
  fi

  echo -e "Done With Fix Virtual Column Data For Secondary...." >> fix_multi_schema.log
  echo

  return 0
}

fixSecondary () {
  echo -e "Fix DD Tables/Data For Secondary User $1...." >> fix_multi_schema.log

  {
  sqlplus $1/$2@$3<<EOF
SET SERVEROUTPUT ON; 
SET LINESIZE 2000;
EXEC DBMS_OUTPUT.ENABLE(2000000);
EXEC PIN_FIX_DD.VALIDATE_DD('$ORACLE_DB_PRIMARY_USER'); 
EOF
  } > tmp.log

  cat tmp.log >> fix_multi_schema.log

  grep "ORA-" tmp.log > /dev/null
  if [ $? -eq 0 ]
  then
    echo -e "ERROR: Errors encountered during validate dd"
    echo -e "ERROR: Errors encountered during validate dd." >> fix_multi_schema.log
    exit 1
  fi

  grep "VIRT FIX NEEDED -- Yes" tmp.log > /dev/null
  VIRT_FIX=$?
  grep "ESSENTIALS FIX NEEDED -- Yes" tmp.log > /dev/null
  ESSENTIALS_FIX=$?

  if [ $VIRT_FIX -eq 0 -o $ESSENTIALS_FIX -eq 0 ]
  then
    fixDataDictionary "$1" "$2" "$3"
  fi

  if [ $VIRT_FIX -eq 0 ]
  then
    fixVirtData "$1" "$2" "$3"
  fi

  if [ $ESSENTIALS_FIX -eq 0 ]
  then
    fixEvtData "$1" "$2" "$3"
  fi

  echo -e "Done With Fix Secondary...." >> fix_multi_schema.log
  echo

  return 0
}

fixBRMMultiSchema () {

  echo "Starting Script #################" >> fix_multi_schema.log
  echo `date` >> fix_multi_schema.log
  echo

  echo -e "Prompting Oracle Database Info For Primary Schema...."
  echo -e "Oracle Database Primary Schema User: \c "
  read ORACLE_DB_PRIMARY_USER
  echo

  echo -e "Oracle Database Primary Schema Password: \c "
  stty -echo
  read ORACLE_DB_PRIMARY_PASSWD
  stty echo
  echo

  echo -e "Oracle Database Primary Schema SID: \c "
  read ORACLE_DB_PRIMARY_SID
  echo
  echo -e "Done With Oracle Database Info For Primary Schema...."
  echo
  
  testDatabaseConnectivity "$ORACLE_DB_PRIMARY_USER" "$ORACLE_DB_PRIMARY_PASSWD" "$ORACLE_DB_PRIMARY_SID" || { echo -e "ERROR: Could not login using $ORACLE_DB_PRIMARY_USER User."; return 1; }

  loadFixScript "$ORACLE_DB_PRIMARY_USER" "$ORACLE_DB_PRIMARY_PASSWD" "$ORACLE_DB_PRIMARY_SID"

  while true
  do
    echo -e "Do you have secondary schema to process (ENTER Y/y or N/n): \c "
    stty -echo; read TMPSTR1; stty echo; echo
    TMPSTR1=`echo "$TMPSTR1" | tr '[a-z]' '[A-Z]'`

    if [ "$TMPSTR1" = "N" ]
    then
      break
    else
      echo -e "Prompting Oracle Database Info For Secondary Schema...."
      echo -e "Oracle Database Secondary Schema User: \c "
      read ORACLE_DB_SECONDARY_USER
      echo

      echo -e "Oracle Database Secondary Schema Password: \c "
      stty -echo
      read ORACLE_DB_SECONDARY_PASSWD
      stty echo
      echo

      echo -e "Oracle Database Secondary Schema SID: \c "
      read ORACLE_DB_SECONDARY_SID
      echo
      echo -e "Done With Oracle Database Info For Secondary Schema...."
      echo

      testDatabaseConnectivity "$ORACLE_DB_SECONDARY_USER" "$ORACLE_DB_SECONDARY_PASSWD" "$ORACLE_DB_SECONDARY_SID" || { echo -e "ERROR: Could not login using ORACLE_DB_SECONDARY_USER User."; return 1; }

      loadFixScript "$ORACLE_DB_SECONDARY_USER" "$ORACLE_DB_SECONDARY_PASSWD" "$ORACLE_DB_SECONDARY_SID"

      grantPermToSecondary "$ORACLE_DB_SECONDARY_USER"

      fixSecondary "$ORACLE_DB_SECONDARY_USER" "$ORACLE_DB_SECONDARY_PASSWD" "$ORACLE_DB_SECONDARY_SID"

    fi
  done

  echo "Finished Script #################" >> fix_multi_schema.log
  echo `date` >> fix_multi_schema.log
  echo
  
  return 0
}

fixBRMMultiSchema

echo "ALL DONE."
