#
# Oracle upgrade helper functions
#

###############################################################################
# parse_exec_file()
#       input:
#	        Oracle username
#	        Oracle password
#		Oracle database alias 
#               filename to be parsed
#               should the perl variable be substituted(1 = yes, 0 = no) 
###############################################################################
sub parse_exec_file {
        local ($userid, $password, $connect_string, $FILE, $evaluate) = @_;
        local $cmd;
        local $evalcmd;
        local $sqlout;
        local ($status) = 0;
        local ($exitcode) = 0;
        local ($sqlshell) = "";
        local ($tmpfile) = "$FILE.tmp";
        local ($logfile) = "$PARTITION_LOG_DIR/$FILE.log";

        open(FILE, "$FILE") || die "Unable to open file '$FILE': $!\n";
        while (<FILE>) {
                $cmd .= $_;
        }

        close (FILE);

        if ($evaluate == 1) {
                $evalcmd = eval "qq!$cmd!";
        } else {
                $evalcmd = $cmd;
        }

        $sqlshell = "$SQLPLUS -s "."/@"."$connect_string";

        #=======================================================
        # Create a temporary file with the sql input.
        #========================================================

        open(TMPFILE, ">$tmpfile") || die "Cannot create $tmpfile\n";

        print TMPFILE "$evalcmd";
        print TMPFILE "\nexit;\n";
        close(TMPFILE);

        $sqlout = `$sqlshell < $tmpfile`;
        $exitcode = $?;

	if (uc($DELETE_TEMP_SQL_FILES) eq "Y") {
        	unlink "$tmpfile";
	}

        open (LOGFILE, ">$logfile") || die "Cannot create $logfile \n";
        print LOGFILE ("$sqlout");
        close(LOGFILE);

        if ($exitcode != 0) {
                print("Error executing file $FILE. \n");
                exit(1);
        }

	return $sqlout;
}

###############################################################################
# find_oracle_error()
#
# Search the given file for Oracle errors 
###############################################################################

sub find_oracle_error {
        local ($FILE) = @_;

        local $contents = "";
        local $err_found = 0;

        open (ERRFILE, $FILE) || die " Unable to open $FILE ";

        while (<ERRFILE>) {
                $contents .= $_;
        }

        close (ERRFILE);

	#
	# Search for the word ERROR, if it is part of any other word ignore.
	#

        if ($contents =~ m/\bERROR\b/)
        {
                $err_found = 1;
        }

        if ($contents =~ m/ORA-/)
        {
                $err_found = 1;
        }

	return $err_found;
}


###############################################################################
# crt_pinlog_file()
#
# Create the pinlog file for the given script(step) 
#
# Input:
#      $display: Should the contents of the pinlog file be displayed in STDOUT?
#		 (1 = yes, 0 = no)
#
###############################################################################

sub crt_pinlog_file {
	local ($step_name, $display) = @_;

	local $pinlog_file = "$PARTITION_LOG_DIR/$step_name.sql.pinlog";

	# Use the parse_exec_function to create the .log file and rename it to .pinlog.

        parse_exec_file($OWNER, $PASSWD, $DBNAME, "crt_pinlog.sql", 1);

	rename("$PARTITION_LOG_DIR/crt_pinlog.sql.log", "$pinlog_file") || die "Unable to create pinlog file";

	if ($display == 1) {
        	open(PINLOG, "$pinlog_file") || die "Unable to open file $pinlog_file. \n";

        	while (<PINLOG>) {
                	print ($_)
        	}

        	close (PINLOG);
	}
}


###############################################################################
## get_table_name()
##
## Retrive the table name for give object.
##
## Input:
##      $obj: Object name whose table is to be fetched. 
##		Ex: account, balance_group.
##
################################################################################
sub get_table_name{
        local ($obj) = @_;
        open (GET_TABLE_SCRIPT, ">partition_get_table.sql") || die "Cannot create temporary file partition_get_table.sql \n";
        print GET_TABLE_SCRIPT "set pagesize 1000 \n";
        print GET_TABLE_SCRIPT "SELECT sm_item_name FROM dd_objects_fields_t ,dd_objects_t WHERE dd_objects_t.obj_id0=dd_objects_fields_t.obj_id0 and dd_objects_t.name='$obj' and dd_objects_fields_t.field_type=11; \n";
        close(GET_TABLE_SCRIPT);
        parse_exec_file($OWNER, $PASSWD, $DBNAME, "partition_get_table.sql", 1);
        open(TMPFILE, "$PARTITION_LOG_DIR/partition_get_table.sql.log") || die "Unable to open file $PARTITION_LOG_DIR/partition_report.sql.log. \n";
	close(TMPFILE);
	unlink("partition_get_table.sql");
        local $result=`tail -n 2 $PARTITION_LOG_DIR/partition_get_table.sql.log`;
	$result =~ s/\n//g;
        return $result;
}

###############################################################################
### process_object()
###
### Processing the object. Involves creating .sql files required for partition.
###
### Input:
###      $obj: Object name which is to be processed.
###              Ex: /account, /balance_group.
###
#################################################################################
sub process_object{
        local ($obj) = @_;
        local $template_file = "./invoice_tables_tobe_partitioned.sql";
        local $file = "";
        local $fileExt = "_tables_tobe_partitioned.sql";
        local $index = index($obj, "/");
        local $no_rows = "no rows";
        if( $index != 0 ) {
                print "invalid object passed. please check input.\n";
		exit 0;
        }
        local $object = substr( $obj, 1);
        $index = index($object, "/");
        if( $index != -1 ) {
                print "invalid object passed. please check input.\n";
		exit 0;
        }
        local $table = get_table_name($obj);
        if( substr($table, 0, length($no_rows)) eq $no_rows ) {
                print "table associated with object not found. please check input.\n";
                exit 0;
        }
	if( $object ne "invoice" ) {
        	local $table_uc = uc($table);
        	$file = $object.$fileExt;
        	`sed -e 's#invoice#'${object}'#g' -e 's#INVOICE_T#'${table_uc}'#g' ${template_file} > ${file}`;
	}
}

##############################################
# Need to return for the "require" statement
##############################################

1;

