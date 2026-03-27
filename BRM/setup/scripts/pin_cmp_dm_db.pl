#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#=============================================================
# @(#)$Id: pin_cmp_dm_db.pl /portalbase/6 2023/02/20 17:13:54 shishrey Exp $
# 
# Copyright (c) 2000, 2024 Oracle and/or its affiliates.
#
#    This material is the confidential property of Oracle Corporation
#    or its licensors and may be used, reproduced, stored
#    or transmitted only in accordance with a valid Oracle license or
#    sublicense agreement.
#
# Portal installation for the database DM Component
#=============================================================


use pcmif;
use pcmdd;
use Digest::MD5 qw(md5_hex);

1;

my $cn = 0;
if(defined($ENV{'DOCKER'}) && ($ENV{'DOCKER'} eq '1')) {
        $cn = 1;
}
our $logging;
our $walletRolePass;
# 
# This function should be called before launching the DM (this will
# populate the DM with the minimum amount of data it needs to start
# up ) This assumes we've already verified the login
#
# Arguments:
#   %DB - associative array pointing to a database
#
sub pin_pre_init {
   local ( %DB ) = @_;

   # Need to add error checking and clean up !!!!

   $CREATE_DD_FILE = "create_dd_$DM{'sm_charset'}.source";
   &ExecuteSQL_Statement_From_File( "$DM{'location'}/data/$CREATE_DD_FILE",
                                    TRUE, 
                                    TRUE, 
                                    %DB );
   if ( $DM{'db_num'} ne "0.0.0.1") {
           &create_metatables_views( %{$DM_ORACLE{"db"}} );
   }
}

sub create_metatables_views
{
    local ( %DB ) = @_;
    if ( -e "$DM{'location'}/data/create_dd_views.source") {
            &ExecuteSQL_Statement_From_File("$DM{'location'}/data/create_dd_views.source",TRUE,TRUE,%DB);
            my $dml_sql = "EXEC create_dd_views('" . $PRIMARY_DB_USER . "' );";
            &ExecuteSQL_Statement($dml_sql,TRUE,TRUE,%DB);
    }
    if ( -e "$DM{'location'}/data/create_view_secondary_schema.source" ) {
           &ExecuteSQL_Statement_From_File("$DM{'location'}/data/create_view_secondary_schema.source",TRUE,TRUE,%DB);
    }
}

sub load_init_config_data
{
    &parse_execute_opcode_file( "$DD{'location'}/init_objects_global.source" );
    &parse_execute_opcode_file( "$DD{'location'}/init_objects_config_maxlength.source" );
    &parse_execute_opcode_file( "$DD{'location'}/init_objects_config_role.source" );
}

#
# This function is called when installing a modular product
# which needs to update the existing Portal database.
#
# Arguments:
#   %DB - associative array pointing to a database
#
sub pin_pre_modular {
local ( %DM ) =  @_;
  if ( $DM{'vendor'} !~ /^db2$/ )
  {    
        &ExecuteSQL_Statement_From_File( "$DD{'location'}/pre_modular_"."$DM{'vendor'}".".sql",
                                    TRUE,
                                    TRUE,
                                    %DM );
  }
  else
  {
        &ExecuteSQL_Statement_From_File_with_delimiter( "$DD{'location'}/pre_modular_"."$DM{'vendor'}".".sql",
                                    TRUE,
                                    TRUE,
                                    %DM );
  }

}


#
# This function displays an error message, and then exits.
#
sub exit_with_error
{
    local ( $MessageText, $MessageArg ) =  @_; 
    local ( $TmpInput );

    &Output( SAVEOUT, $MessageText, $MessageArg ); 
    if ( $^O =~ /win/i )
    {
      &Output( SAVEOUT, "\nPress enter to continue " );
      $TmpInput = <STDIN>;
    }
    exit( 1 );
}

#
# This Function Compares the Login passwords from 
# Wallet and Password stored in service Table.
#
sub pin_check_password {
  local( $inputFile ) = shift( @_ );
  local ( $alias ) = shift( @_ );
  local ( %DM ) = @_;
  local ( $ebufp );
  local ( $pcm_contextp );
  local ( $opcodeName );
  local ( $opcodeFlags );
  local ( $flist );
  local ( $junk1, $junk2 );
  local ( $inputFlist, $outputFlist );
  local ( $PIN_CONF_DB_NO ) = $DM{'db_num'};
  local ( $NumTries ) = 0;
  local ( $Connected ) = 0;
  local ( $WalletDBPass );
  local ( $WalletDBPassFile );
  local ( $ServiceDBPass );
  local ( $ServiceDBSalt );
  local ( $IsPassValid ) = 0;
  local ( @FileReadIn );

  #Check if inputfile needs to be created, create it.
  if($alias eq "roleC") {
    $alias = $alias . $PIN_CONF_DB_NO;
    open(my $fh, '>', $inputFile) or die "Could not open file '$inputFile' $!";
    print $fh <<EOF;
<PCM_OP \$PIN_OPNAME=PCM_OP_READ_FLDS; \$PIN_OPFLAGS=0>
# number of field entries allocated 20, used 1
0 PIN_FLD_POID                      POID [0] \$PIN_CONF_DB_NO /service/pcm_client 409
0 PIN_FLD_PASSWD                     STR [0] ""
</PCM_OP>
EOF
    close $fh;
  }

  $ebufp = pcmif::pcm_perl_new_ebuf();

 # initialize the opcode list
 @opcode_list = ();

  &Start ( $ServiceName{'dm_'.$DM{'db'}->{'vendor'}} );

  while ( ( $NumTries < 30 ) && ($Connected == 0) ) {
    $pcm_contextp = pcmdd::pcmdd_connect( $DM{'hostname'},
                                        $DM{'port'},
                                        $DM{'db_num'},
                                        $ebufp );
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
        $Connected = pcmif::pcm_perl_ebuf_to_str( $ebufp );
        print $Connected."\n";
        if ( $Connected =~ /PIN_ERR_DM_CONNECT_FAILED/ ) {
                $NumTries = $NumTries + 1;
                $Connected = 0;
                sleep( 10 );
        } else {
             open( STDOUT, ">".$logging);
             open( STDERR, ">".$logging);
             pcmif::pcm_perl_print_ebuf( $ebufp );
             &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
        }
    } else {
      $Connected = 1;
    }
  }
  
  if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
      open( STDOUT, ">".$logging);
      open( STDERR, ">".$logging);
      pcmif::pcm_perl_print_ebuf( $ebufp );
      &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
  }

  &parse_execute_opcode_file( "$inputFile" );
  $opcodeNumber = 1;
  foreach $op ( @opcode_list ) {
    #
    # Split the list back to opcode/flags/flist
    #
    ( $opcodeName, $opcodeFlags, $flist ) = split( ',', $op, 3 );

    #
    # Get the PIN_FLD_POID from the flist
    #

    ($junk1, $poid, $junk2 ) =
      $flist =~ m/(^|\n)0\s+PIN_FLD_POID\s+POID\s+\[0\]\s+([\w\s\/\.]+)(\n|$)/;
    chomp( $poid );

    &Output( $logging, " %3d %-26s %2d   %s\n", $opcodeNumber, $opcodeName, $opcodeFlags, $poid );
    &Output( $logging, "$ME: $flist" );
    &Output( $logging, "...\n" );

    #
    # Generate the input flist.
    #
    $inputFlist = pcmif::pin_perl_str_to_flist( $flist, $PIN_CONF_DB_NO, $ebufp );
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
      open( STDOUT, ">".$logging);
      open( STDERR, ">".$logging);
      pcmif::pcm_perl_print_ebuf( $ebufp );
      &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
    }

    #
    # Call the opcode and get the output flist
    #
    $outputFlist = pcmif::pcm_perl_op( $pcm_contextp,
                                       $opcodeName,
                                       $opcodeFlags,
                                       $inputFlist,
                                       $ebufp );
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
      open( STDOUT, ">".$logging);
      open( STDERR, ">".$logging);
      pcmif::pcm_perl_print_ebuf( $ebufp );
      &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
    }

    $out = pcmif::pin_perl_flist_to_str( $outputFlist, $ebufp );
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
      open( STDOUT, ">".$logging);
      open( STDERR, ">".$logging);
      pcmif::pcm_perl_print_ebuf( $ebufp );
      &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
    }
    pcmif::pin_flist_destroy( $inputFlist );
    pcmif::pin_flist_destroy( $outputFlist );

    $opnum++;
  }

  pcmif::pcm_context_close( $pcm_contextp, 0, $ebufp );
  if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
      open( STDOUT, ">".$logging);
      open( STDERR, ">".$logging);
      pcmif::pcm_perl_print_ebuf( $ebufp );
      &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
  }

  if($alias eq "exeC") {
    return ;
  }
  system("java -cp /home/pin/opt/portal/BRM/jars/oraclepki.jar:/home/pin/opt/portal/setup/BRMActions.jar com.oracle.installer.brm.BRMInstallHelper 7 $BRM_CONF_WALLET $alias");
  if (-e "$BRM_CONF_WALLET/.wp") {
       open( TEMPFILE, "$BRM_CONF_WALLET/.wp" );
       @FileReadIn = <TEMPFILE>;
       close( TEMPFILE );
       $WalletDBPassFile = join( "", @FileReadIn );
 
       $WalletDBPass = substr($WalletDBPassFile , (index ($WalletDBPassFile,'='))+1);
       chomp($WalletDBPass);
       unlink("$BRM_CONF_WALLET/.wp");
  } else {
       exit;
  }

  chomp($WalletDBPass);
  chomp($out);

  $walletRolePass = $WalletDBPass;
  if (index($out, 'md5') != -1) {
      $ServiceDBPass = substr($out , (index ($out,'md5')+4), -1);
      $WalletDBPass = md5_hex("$WalletDBPass");
  }

  if (index($out, 'sha1') != -1) {
      $ServiceDBPass = substr($out , (index ($out,'sha1')), -1);
      $ServiceDBSalt = substr($ServiceDBPass,rindex($ServiceDBPass,'|')+1);
      $WalletDBPass = `/home/pin/opt/portal/BRM/bin/sha1_encode $WalletDBPass $ServiceDBSalt`;
  }

  if (index($out, 'pbkdf2') != -1) {
      $ServiceDBPass = substr($out , (index ($out,'pbkdf2')), -1);
      $ServiceDBSalt = substr($ServiceDBPass,rindex($ServiceDBPass,'|')+1);
      $WalletDBPass = `/home/pin/opt/portal/BRM/bin/pbkdf2_encode $WalletDBPass $ServiceDBSalt`;
  }

  if ($WalletDBPass eq $ServiceDBPass) { $IsPassValid = 1; }
  if($alias =~ /roleC/) {
    system("rm $inputFile");
  }

  return $IsPassValid;

}

#
# This function will restart the dm_oracle service
#
# Arguments:
#   %DB - associative array pointing to a database
#
sub pin_dm_restart {
  local ( %DM ) = @_;
  local ( $ebufp );
  local ( $pcm_contextp );
  local ( $NumTries ) = 0;
  local ( $Connected ) = 0;
  $ebufp = pcmif::pcm_perl_new_ebuf();

  &Stop ( $ServiceName{'dm_'.$DM{'db'}->{'vendor'}} );
  sleep( 20 );

  &Start ( $ServiceName{'dm_'.$DM{'db'}->{'vendor'}} );

  while ( ( $NumTries < 30 ) && ($Connected == 0) ) {
    $pcm_contextp = pcmdd::pcmdd_connect( $DM{'hostname'},
                                        $DM{'port'},
                                        $DM{'db_num'},
                                        $ebufp );
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
        $Connected = pcmif::pcm_perl_ebuf_to_str( $ebufp );
        if ( $Connected =~ /PIN_ERR_DM_CONNECT_FAILED/ ) {
                $NumTries = $NumTries + 1;
                $Connected = 0;
                sleep( 10 );
        } else {
             open( STDOUT, ">&fpLogFile");
             open( STDERR, ">&fpLogFile");
             pcmif::pcm_perl_print_ebuf( $ebufp );
             &exit_with_error ( $IDS_PIN_INIT_FAILED, $SETUP_LOG_FILENAME );
        }
    } else {
      $Connected = 1;
    }
  }
}


# 
#  This function populates the database by going through
#  the DM (in contrast to pin_pre_init, which goes directly
#  to the database, and therefore, is database dependent )
#
#  Arguments:
#    %DM - associative array pointing to a DM
#
sub pin_init {
  local ( %DM ) = @_;
  local ( $ebufp );
  local ( $pcm_contextp );
  local ( $opcodeName );
  local ( $opcodeFlags );
  local ( $flist );
  local ( $junk1, $junk2 );
  local ( $inputFlist, $outputFlist );
  local ( $PIN_CONF_DB_NO ) = $DM{'db_num'};
  local ( $NumTries ) = 0;
  local ( $Connected ) = 0;
  $ebufp = pcmif::pcm_perl_new_ebuf();
  
  # Display a message of dd objects are loading
  &Output( $logging, $IDS_DD_OBJECTS_LOADING,
                       $SPECIAL_DD_FILE ); 
 
 # initialize the opcode list
 @opcode_list = ();

  &Start ( $ServiceName{'dm_'.$DM{'db'}->{'vendor'}} );

  while ( ( $NumTries < 30 ) && ($Connected == 0) ) {
    $pcm_contextp = pcmdd::pcmdd_connect( $DM{'hostname'}, 
                                        $DM{'port'},
                                        $DM{'db_num'}, 
                                        $ebufp );
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
	$Connected = pcmif::pcm_perl_ebuf_to_str( $ebufp );
	print $Connected."\n";
	if ( $Connected =~ /PIN_ERR_DM_CONNECT_FAILED/ ) {      
		$NumTries = $NumTries + 1;
	        $Connected = 0;
                sleep( 10 );
	} else {	
 	     open( STDOUT, ">".$logging);
  	     open( STDERR, ">".$logging);
	     pcmif::pcm_perl_print_ebuf( $ebufp );
	     &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
        }     
    } else {
      $Connected = 1;
    }
  }

  if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
      open( STDOUT, ">".$logging);
      open( STDERR, ">".$logging);
      pcmif::pcm_perl_print_ebuf( $ebufp );
      &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
  }

  if( $ENABLE_PARTITION =~ /^Yes$/i ) {
    if ( $USE_SPECIAL_DD_FILE !~ /^YES$/i ) {
 
	&process_for_partition_classes("$DD{'location'}/dd_objects.source" );
      &parse_execute_opcode_file( "$DD{'location'}/dd_objects.source.upd" );

      if ( $SKIP_INIT_OBJECTS !~ /^YES$/i ) {
        &parse_execute_opcode_file( "$DD{'location'}/init_objects.source" );
         if ($DM{'db_num'} eq "0.0.0.1") {
             &load_init_config_data();
         }
      }
    } else {
	&process_for_partition_classes("$SPECIAL_DD_FILE");
      &parse_execute_opcode_file( "$SPECIAL_DD_FILE.upd" );
      if ( $SKIP_INIT_OBJECTS !~ /^YES$/i ) {
        &parse_execute_opcode_file( "$SPECIAL_DD_INIT_FILE" );
      }
    }
  } else {

    if ( $USE_SPECIAL_DD_FILE !~ /^YES$/i ) {
      &process_for_partition("$DD{'location'}/dd_objects.source" );
      &parse_execute_opcode_file( "$DD{'location'}/dd_objects.source.upd" );

      if ( $SKIP_INIT_OBJECTS !~ /^YES$/i ) {
         if ($DM{'db_num'} eq "0.0.0.1") {
              &parse_execute_opcode_file( "$DD{'location'}/init_objects.source" );
              &load_init_config_data();
         }
      }
    } else {
      &process_for_partition("$SPECIAL_DD_FILE");
      &parse_execute_opcode_file( "$SPECIAL_DD_FILE.upd" );
      if ( $SKIP_INIT_OBJECTS !~ /^YES$/i ) {
        &parse_execute_opcode_file( "$SPECIAL_DD_INIT_FILE" );
      }
    }
  }
  $opcodeNumber = 1;
  foreach $op ( @opcode_list ) {
    #
    # Split the list back to opcode/flags/flist
    #
    ( $opcodeName, $opcodeFlags, $flist ) = split( ',', $op, 3 );

    #
    # Get the PIN_FLD_POID from the flist
    #

    ($junk1, $poid, $junk2 ) = 
      $flist =~ m/(^|\n)0\s+PIN_FLD_POID\s+POID\s+\[0\]\s+([\w\s\/\.]+)(\n|$)/;
    chomp( $poid );

    &Output( $logging, " %3d %-26s %2d   %s\n", $opcodeNumber, $opcodeName, $opcodeFlags, $poid );
    &Output( $logging, "$ME: $flist" );
    &Output( $logging, "...\n" );
  
    # 
    # Generate the input flist.
    #                                                                
    $inputFlist = pcmif::pin_perl_str_to_flist( $flist, $PIN_CONF_DB_NO, $ebufp );
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
      open( STDOUT, ">".$logging);
      open( STDERR, ">".$logging);
      pcmif::pcm_perl_print_ebuf( $ebufp );
      &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
    }

    #
    # Call the opcode and get the output flist
    #
    $outputFlist = pcmif::pcm_perl_op( $pcm_contextp, 
                                       $opcodeName, 
                                       $opcodeFlags, 
                                       $inputFlist, 
                                       $ebufp );
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
      open( STDOUT, ">".$logging);
      open( STDERR, ">".$logging);
      pcmif::pcm_perl_print_ebuf( $ebufp );
      &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
    }

    $out = pcmif::pin_perl_flist_to_str( $outputFlist, $ebufp );
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
      open( STDOUT, ">".$logging);
      open( STDERR, ">".$logging);
      pcmif::pcm_perl_print_ebuf( $ebufp );
      &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
    }
   
    pcmif::pin_flist_destroy( $inputFlist );
    pcmif::pin_flist_destroy( $outputFlist );

    $opnum++;
  }

  pcmif::pcm_context_close( $pcm_contextp, 0, $ebufp );
  if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
      open( STDOUT, ">".$logging);
      open( STDERR, ">".$logging);
      pcmif::pcm_perl_print_ebuf( $ebufp );
      &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
  }

}

# 
#  This function creates the indexes and procedures used
#  by Portal. 
#  
#  Arguments:
#    %DM - Associative array to DM
sub pin_post_init {
  local ( %DM ) =  @_;

  ##
  ## Reset the sequence 
  ##
  &ResetSequence( "100000", %{$DM{'db'}} );

  &ExecuteSQL_Statement_From_File( "$DM{'location'}/data/create_indexes.source", 
                                   TRUE, 
                                   TRUE, 
                                   %{$DM{'db'}} );

  if ($DM{'db_num'} eq "0.0.0.1") {
      &ExecuteSQL_Statement_From_File( "$DM{'location'}/data/create_global_class_indexes.source",
                                       TRUE,
                                       TRUE,
                                       %{$DM{'db'}} );

  }
 
  #
  # Create the indexes for the base audit tables for Oracle and SQL Server. 
  # Currently the file is built and packaged only for Oracle.
  #                               
  if ( -f "$DM{'location'}/data/create_indexes_base_audit_tables_"."$DM{'db'}->{'vendor'}".".source" )  {  
    &ExecuteSQL_Statement_From_File( "$DM{'location'}/data/create_indexes_base_audit_tables_"."$DM{'db'}->{'vendor'}".".source", 
                                   TRUE, 
                                   TRUE, 
                                   %{$DM{'db'}} );	
  }

  #
  # Create the indexes for the audit tables for Oracle
  #
  if ( -f "$DM{'location'}/data/create_indexes_audit_tables_"."$DM{'db'}->{'vendor'}".".source" )  {
    &ExecuteSQL_Statement_From_File( "$DM{'location'}/data/create_indexes_audit_tables_"."$DM{'db'}->{'vendor'}".".source",
                                   TRUE,
                                   TRUE,
                                   %{$DM{'db'}} );
  }
    
  #
  # Set name for the create procedures based on Database
  #
  if ( $DM{'db'}->{'vendor'} =~ /^oracle$/ ) {
	$CREATE_PROCEDURES_FILE = "create_procedures_$DM{'sm_charset'}.plb";
	$CREATE_JOURNAL_PROCEDURES_FILE = "create_pkg_journal_$DM{'sm_charset'}.plb";
  }
  else{
        $CREATE_PROCEDURES_FILE = "create_procedures_$DM{'sm_charset'}.source";
  }
  
  #
  # The stored procedures for each DB is loaded differently. 
  # Oracle has a plb file and DB2 has a delimiter. Hence each is 
  # loaded differently.
  #
  if ( $DM{'db'}->{'vendor'} =~ /^odbc$/ ) {
    &ExecuteSQL_Statement_From_File( "$DM{'location'}/data/$CREATE_PROCEDURES_FILE", 
                                     TRUE, 
                                     TRUE, 
                                     %{$DM{'db'}} );
      
    &ExecutePLB_file ( "$DM{'location'}/data/$CREATE_JOURNAL_PROCEDURES_FILE",
  		      "Portal Journal Stored Procedures",
  		      %DM );	      

  }
  elsif ( $DM{'db'}->{'vendor'} =~ /^oracle$/ ){
    &ExecutePLB_file ( "$DM{'location'}/data/$CREATE_PROCEDURES_FILE",
		      "Portal Stored Procedures",
		      %DM );

    &ExecutePLB_file ( "$DM{'location'}/data/$CREATE_JOURNAL_PROCEDURES_FILE",
  		      "Portal Journal Stored Procedures",
  		      %DM );	      
  }
  elsif ( $DM{'db'}->{'vendor'} =~ /^db2$/ )
  {
    &ExecuteSQL_Statement_From_File_with_delimiter( "$DM{'location'}/data/$CREATE_PROCEDURES_FILE", 
                                     TRUE, 
                                     TRUE, 
                                     %{$DM{'db'}} );
  }

  #
  # Load create_analytics_procedures_AL32UTF8.plb
  #
  $CREATE_ANALYTICS_PROCEDURES_FILE = "create_analytics_procedures_$DM{'sm_charset'}.plb";
    &ExecutePLB_file ( "$DM{'location'}/data/$CREATE_ANALYTICS_PROCEDURES_FILE",
                                     "Analytical Stored Procedures",
                                     %DM);
}

# 
#  This function creates the event_essentials_t table for event storage reduction 
#  by Portal. 
#  
#  Arguments:
#    %DM - Associative array to DM
sub pin_create_event_essential {
  local ( %DM ) =  @_;

# Call create event essential based on the ENABLE_PARTITION/PIN_CONF_SQL_PLATFORM variable
  if ($MAIN_DM{'db'}->{'vendor'} =~ /^odbc$/i) {
    &ExecuteSQL_Statement_From_File( "$DM{'location'}/data/create_event_essential_sql.source", 
                                   TRUE, 
                                   TRUE, 
                                   %{$DM{'db'}} );
  }
  elsif ($MAIN_DM{'db'}->{'vendor'} =~ /^oracle$/i) {
	        if ($ENABLE_PARTITION =~/Yes/i ) {
            &ExecuteSQL_Statement_From_File( "$DM{'location'}/data/create_event_essential_partition.source", 
                                   TRUE, 
                                   TRUE, 
                                   %{$DM{'db'}} );
            }
            else {
            &ExecuteSQL_Statement_From_File( "$DM{'location'}/data/create_event_essential_nonpartition.source", 
                                   TRUE, 
                                   TRUE, 
                                   %{$DM{'db'}} );
            }

  }
}



#
# This function is called when installing a modular product
# which needs to update the existing Portal database.
#
#  Arguments:
#    %DM - Associative array to DM
#
sub pin_post_modular {
  local ( %DM ) =  @_;
  if ( $DM{'delimiter'} =~ /^$/ )
  {
  	&ExecuteSQL_Statement_From_File( "$DD{'location'}/post_modular_"."$DM{'db'}->{'vendor'}".".sql",
                                    TRUE,
                                    TRUE,
                                    %{$DM{'db'}} );
  }
  else
  {
  	&ExecuteSQL_Statement_From_File_with_delimiter( "$DD{'location'}/post_modular_"."$DM{'db'}->{'vendor'}".".sql",
                                    TRUE,
                                    TRUE,
                                    %{$DM{'db'}} );
  }

}
#
# This function is called when we decide not to install partitioning.
# We will process the dd_objects[...].source and generate
# dd_object[...].source.upd file so the new file will not have the
# partitioning clause.
#  
sub process_for_partition {
  local ($DD_FILE) = @_;

  open(INFILE, "$DD_FILE");
  open(TEMPFILE, ">$DD_FILE.upd");

  $line = <INFILE>;
  print TEMPFILE "$line" if($cn == 1);

  while (!eof(INFILE)) {
    $line = <INFILE>;
    
    # 
    # Remove the partition related information from the DD FILE.
    #
    next if ($line =~ /PIN_FLD_IS_PARTITIONED/ || $line =~ /PIN_FLD_PARTITION_MODE/ );

    print TEMPFILE "$line" ;
  }
  close TEMPFILE;
  close INFILE;
}

#
# This function is called when we decide to install partitioning.
# We will process the dd_objects[...].source and generate
# dd_object[...].source.upd file so the new file will have the
# partitioning clause for the classes which are mentioned in
# CLASSES_TO_BE_PARTITIONED array.
# 
sub process_for_partition_classes {
	local ($DD_FILE) = @_;
	local $obj_found = 0;
	local $class_name;
	local $class_from_line;
	local $partition_class;
	local $add_line = "1     PIN_FLD_IS_PARTITIONED    INT [0] 1\n".
			  "1     PIN_FLD_PARTITION_MODE    STR [0] \"Finite\"\n";

	open(INFILE, "$DD_FILE");
	open(TEMPFILE, ">$DD_FILE.upd");

	$line = <INFILE>;

	while (!eof(INFILE)) {
		$line = <INFILE>;
		print TEMPFILE "$line" ;
		#
		# If the class is matched with the classes given in @CLASSES_TO_BE_PARTITIONED
		# then add PIN_FLD_IS_PARTITIONED to this.
		#
		if (($obj_found == 1) && ($line =~ /PIN_FLD_NAME/) ) {
			#
			# Get the class name from the line
			#
			$class_from_line = substr($line, index($line, "\"") + 1);
			foreach $partition_class (@CLASSES_TO_BE_PARTITIONED) {
				$class_name = substr(lc($partition_class), 0, index($partition_class, ":"));
				if (index($class_from_line, $class_name) == 0 ) {
                                   if($class_name =~ "/bill" && $class_from_line =~ "/billinfo" ) {
                                   }
                                   else {
					print TEMPFILE "$add_line";
					last;
                                   }
				}
			}
			$obj_found = 0;
		}
		if ($line =~ /0 PIN_FLD_OBJ_DESC/ ) {
			$obj_found = 1;
		}

	}
	close TEMPFILE;
	close INFILE;
}

sub pin_init_non_partition {
    local ( %DM ) = @_;
    local ( $ebufp );
    local ( $pcm_contextp );
    local ( $opcodeName );
    local ( $opcodeFlags );
    local ( $flist );
    local ( $junk1, $junk2 );
    local ( $inputFlist, $outputFlist );
    local ( $PIN_CONF_DB_NO ) = $DM{'db_num'};
    local ( $NumTries ) = 0;
    local ( $Connected ) = 0;
    $ebufp = pcmif::pcm_perl_new_ebuf();
  
    # Display a message of dd objects are loading
    &Output( $logging, $IDS_DD_OBJECTS_LOADING,
                         $SPECIAL_DD_FILE );
  
   # initialize the opcode list
   @opcode_list = ();

   &Start ( $ServiceName{'dm_'.$DM{'db'}->{'vendor'}} );

    while ( ( $NumTries < 30 ) && ($Connected == 0) ) {
      $pcm_contextp = pcmdd::pcmdd_connect( $DM{'hostname'},
                                          $DM{'port'},
                                          $DM{'db_num'},
                                          $ebufp );
      if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
          $Connected = pcmif::pcm_perl_ebuf_to_str( $ebufp );
          print $Connected."\n";
          if ( $Connected =~ /PIN_ERR_DM_CONNECT_FAILED/ ) {
                  $NumTries = $NumTries + 1;
                  $Connected = 0;
                  sleep( 10 );
          } else {
               open( STDOUT, ">".$logging);
               open( STDERR, ">".$logging);
               pcmif::pcm_perl_print_ebuf( $ebufp );
               &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
          }
      } else {
        $Connected = 1;
      }
    }
  
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
        open( STDOUT, ">".$logging);
        open( STDERR, ">".$logging);
        pcmif::pcm_perl_print_ebuf( $ebufp );
        &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
    }
  
    # Not calling "process_for_partition_classes", so that partition related fields will not be added to the input flist.
      if ( $USE_SPECIAL_DD_FILE !~ /^YES$/i ) {
        &parse_execute_opcode_file( "$DD{'location'}/dd_objects.source" );
  
        if ( $SKIP_INIT_OBJECTS !~ /^YES$/i ) {
         &parse_execute_opcode_file( "$DD{'location'}/init_objects.source" );
         if ($DM{'db_num'} eq "0.0.0.1") {
             &load_init_config_data();
         }
        }
      } else {
        &process_for_partition("$SPECIAL_DD_FILE");
        &parse_execute_opcode_file( "$SPECIAL_DD_FILE.upd" );
        if ( $SKIP_INIT_OBJECTS !~ /^YES$/i ) {
          &parse_execute_opcode_file( "$SPECIAL_DD_INIT_FILE" );
        }
      }
    
    $opcodeNumber = 1;
    foreach $op ( @opcode_list ) {
      #
      # Split the list back to opcode/flags/flist
      #
      ( $opcodeName, $opcodeFlags, $flist ) = split( ',', $op, 3 );
  
      #
      # Get the PIN_FLD_POID from the flist
      #
  
      ($junk1, $poid, $junk2 ) =
        $flist =~ m/(^|\n)0\s+PIN_FLD_POID\s+POID\s+\[0\]\s+([\w\s\/\.]+)(\n|$)/;
      chomp( $poid );
  
      &Output( $logging, " %3d %-26s %2d   %s\n", $opcodeNumber, $opcodeName, $opcodeFlags, $poid );
      &Output( $logging, "$ME: $flist" );
      &Output( $logging, "...\n" ); 

      #
      # Generate the input flist.
      #
      $inputFlist = pcmif::pin_perl_str_to_flist( $flist, $PIN_CONF_DB_NO, $ebufp );
      if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
        open( STDOUT, ">".$logging);
        open( STDERR, ">".$logging);
        pcmif::pcm_perl_print_ebuf( $ebufp );
        &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
      }
  
      #
      # Call the opcode and get the output flist
      #
      $outputFlist = pcmif::pcm_perl_op( $pcm_contextp,
                                         $opcodeName,
                                         $opcodeFlags,
                                         $inputFlist,
                                         $ebufp );
      if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
        open( STDOUT, ">".$logging);
        open( STDERR, ">".$logging);
        pcmif::pcm_perl_print_ebuf( $ebufp );
        &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
      }
  
      $out = pcmif::pin_perl_flist_to_str( $outputFlist, $ebufp );
      if($opcodeName =~ /search/i && $cn) {
              open (FLIST, ">out.flist") || die "$ME: Could not open out.flist file\n";
              print FLIST $out;
              close (FLIST);
      }

      if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
        open( STDOUT, ">".$logging);
        open( STDERR, ">".$logging);
        pcmif::pcm_perl_print_ebuf( $ebufp );
        &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
      }
  
      pcmif::pin_flist_destroy( $inputFlist );
      pcmif::pin_flist_destroy( $outputFlist );
  
      $opnum++;
    }
  
    pcmif::pcm_context_close( $pcm_contextp, 0, $ebufp );
    if ( pcmif::pcm_perl_is_err( $ebufp ) ) {
        open( STDOUT, ">".$logging);
        open( STDERR, ">".$logging);
        pcmif::pcm_perl_print_ebuf( $ebufp );
        &exit_with_error ( $IDS_PIN_INIT_FAILED, $logging );
    }
  
}

# 
#  This function loads the plb file and parses
# the output file for errors. 
#  
#    $inputFile - String containing the input file
#    $pkgName - String containing the name of the package used for logging
#    %DM- Associative array for DM
#
sub ExecutePLB_file {
  local( $inputFile ) = shift( @_ );
  local( $pkgName ) = shift( @_ );
  local ( %DM ) = @_;
  local $Logfile = "$PIN_TEMP_DIR/tmp.out";
  local $bErrors = FALSE;

  #
  # Compile the package into the Oracle database.
  #

  &Output( $logging, "Loading $pkgName\n" );

  if ( -f "$inputFile" )
  {
	&ExecuteSQL_Statement("\@$inputFile",TRUE,TRUE,%{$DM{'db'}});
  }
  
  # Parse the output file to see if the pkg was loaded successfully  
  open( LOGFILE, "<$Logfile " );
  while( $ReadString = <LOGFILE> ){	
	if ( $ReadString =~ /created with compilation errors/ ||$ReadString =~ /unable to open file*/){
		$bErrors=TRUE;
	}		
  }
  close( LOGFILE );
  
  if ( $bErrors eq TRUE ){
  &Output( STDOUT, "$pkgName loading failed. Please check pin_setup.log for error details\n" );
	&Output( $logging, "$pkgName loading failed\n");
        if ($inputFile !~ /create_pricing_tailormadeplan_procedures.plb/ && $inputFile !~ /create_procedures_AL32UTF8.plb/) {
	   exit -1;
	}
  }
  else{
    &Output( $logging, "$pkgName loaded successfully\n" );
  }
  
}

sub updateRolePasswordsInDB {

  #create source file for updating passwords
  createSourceFile();

  #pbkdf2 hashed password
  my $walletRolePassHash =  `/home/pin/opt/portal/BRM/bin/pbkdf2_encode $walletRolePass`;
  my $scmd = qq{sed -i 's/rolePassword/$walletRolePassHash/g' /home/pin/opt/portal/BRM/sys/dd/data/update_role_password_db.source};
  system($scmd);

  #using pin_check_password to execute the source file and update the role passwords in db.
  pin_check_password("/home/pin/opt/portal/BRM/sys/dd/data/update_role_password_db.source", "exeC", %DM);
  system("rm /home/pin/opt/portal/BRM/sys/dd/data/update_role_password_db.source ");

}

sub createSourceFile {
  my @pcm_client_ids = (3, 402, 403, 404, 405, 406, 407, 408, 409, 411, 412, 413, 414, 421);
  my @admin_client_ids = (4, 410, 415, 416, 417, 418, 419, 420);
  $filename = "/home/pin/opt/portal/BRM/sys/dd/data/update_role_password_db.source";
    
  open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";
    
  foreach my $id (@pcm_client_ids) {
  print $fh <<EOF;
<PCM_OP \$PIN_OPNAME=PCM_OP_WRITE_FLDS; \$PIN_OPFLAGS=0>
# number of field entries allocated 20, used 1
0 PIN_FLD_POID           POID [0] \$PIN_CONF_DB_NO /service/pcm_client $id 1
0 PIN_FLD_PASSWD          STR [0] "rolePassword"
</PCM_OP>
EOF
  }

  foreach my $id (@admin_client_ids) {
  print $fh <<EOF;
<PCM_OP \$PIN_OPNAME=PCM_OP_WRITE_FLDS; \$PIN_OPFLAGS=0>
# number of field entries allocated 20, used 1
0 PIN_FLD_POID           POID [0] \$PIN_CONF_DB_NO /service/admin_client $id 1
0 PIN_FLD_PASSWD          STR [0] "rolePassword"
</PCM_OP>
EOF
  }
  close $fh;
}
1;
