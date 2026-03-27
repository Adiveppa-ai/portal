#------------------------------------------------------------------------------#
# SCRIPT: Sqlplus.pm
#
# DESCRIPTION:
#
# Simple SQL helper class for performing SQL operations in Perl without having
# to go to the trouble of installing the Perl DBI or equivalent.
#
# INFORMATION:
#
# BRM Performance Tools ... Thanks to G.Gallo for the original.
#
# REVISION:
#
# $Revision: 1.3 $
# $Author: pin $
# $Date: 2015/02/10 00:20:54 $
#------------------------------------------------------------------------------#

=head1 NAME

GG::Sqlplus - Helper functions for using SQL through a SQL*Plus instance.

=head1 SYNOPSIS

use GG::Sqlplus;

$sql_h = sql_open($connection_string);

$sql_h = sql_open($userid, $password, $alias);

sql_close($sql_h);

sql_exec($sql_h, $sql, \$output, \$elapsed);

sql_query($sql_h, $sql_body, \%fields, $separator, $no_fields,
          \$elapsed);

sql_set_debug($bool_debug);
sql_set_feedback($bool_feedback);

=head1 DESCRIPTION

This module allows you to:

=over 4

=item *

Open a SQL*Plus connection

=item *

Close a SQL*Plus connection

=item *

Execute a SQL statement using a SQL*Plus connection

=item *

Execute a SQL query using a SQL*Plus connection

=item *

Activate/deactivate the debug mode for package

=item *

Activate/deactivate the feedback mode for this package

=back

=cut

#------------------------------------------------------------------------------#
#                     M O D U L E   I N C L U S I O N
#------------------------------------------------------------------------------#
package GG::Sqlplus;

use strict;
use warnings;
our(@ISA, @EXPORT, $VERSION);
require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(sql_open sql_close sql_exec sql_query sql_set_debug
             sql_set_feedback);
$VERSION = "1.00";

BEGIN {
   use Exporter ();
   use IPC::Open2;
   use FileHandle;
   use Time::HiRes qw ( time );

   our ($VERSION, @ISA, @EXPORT, @EXPORT_OK, %EXPORT_TAGS);

   # set the version for version checking
   $VERSION = 1.00;

   @ISA = qw(Exporter);
   @EXPORT = qw(sql_open sql_close sql_exec sql_query sql_set_debug
                sql_set_feedback);
   %EXPORT_TAGS = ();

   # Exported package globals and optionally exported functions
   @EXPORT_OK = ();
}
our @EXPORT_OK;

#------------------------------------------------------------------------------#
#                     G L O B A L   V A R I A B L E S
#------------------------------------------------------------------------------#
my $DEBUG = 0;
my $FEEDBACK = 0;

=head1 METHODS

The following section briefly lists the available methods in this package.

=cut

#------------------------------------------------------------------------------#
#                            S Q L _ O P E N
#------------------------------------------------------------------------------#

=head2 sql_open

The C<sql_open()> routine opens a SQL connection by using SQL*Plus and the
supplied connection parameters. It returns the SQL handle to be used for
accessing the connection or undef in case of any error.

   $sql_h = sql_open($connection_string);
   $sql_h = sql_open($userid, $password, $alias);

The SQL*Plus session is initialized with the following settings:
  set head off
  set trims on
  set trim on
  set pagesize 0
  set linesize 10000
  set feedback off
  set echo off
  set verify off

PARAMETERS:
  $connection_string : The connection string to the database in
                       the format <userid>/<password>@<alias>
  $userid            : The user ID to be used for establishing
                       the connection to the database
  $password          : The password to be used for establishing
                       the connection to the database
  $alias             : The alias to be used for establishing the
                       connection to the database

RETURNS:
  The handle of a SQL connection that can be used with C<sql_close()>,
  C<sql_exec()> and C<sql_query()>. Returns undef in case of any error.

NOTES:
  Affected by the feedback mode.

=cut

sub sql_open {
   my ($userid, $password, $alias);

   if ((scalar @_) == 1) {
     if( !(defined($ENV{'DOCKER'}))  || (defined($ENV{'DOCKER'}) && ($ENV{'DOCKER'} eq '0'))){
      die "ERROR: Invalid connection string '$_[0]'. Expected something " .
          "like 'user/passwd\@alias'" unless $_[0] =~ m!(\w+)/(\w+)\@(.+)!;
      ($userid, $password, $alias) = $_[0] =~ m!(\w+)/(\w+)\@(.+)!;
     }
   } else {
      ($userid, $password, $alias) = @_;
   }

   my $sql_h = { reader => FileHandle->new(), writer => FileHandle->new(),
                 userid => $userid, password => $password, alias => $alias };

   print "Opening SQL*Plus connection to " .
         "'$userid/XXXX\@$alias'...\n" if $FEEDBACK;

   $$sql_h{pid} = open2($$sql_h{reader}, $$sql_h{writer},
                        "sqlplus", "-s", "/nolog");

   # Return undef if it was not possible to create the child process
   return undef unless $$sql_h{pid};

   $$sql_h{reader}->autoflush(1);
   $$sql_h{writer}->autoflush(1);

   # Init SQL*Plus parameters
   $$sql_h{writer}->print("set head off\n");
   $$sql_h{writer}->print("set trims on\n");
   $$sql_h{writer}->print("set trim on\n");
   $$sql_h{writer}->print("set pagesize 0\n");
   $$sql_h{writer}->print("set linesize 10000\n");
   #$$sql_h{writer}->print("set serverout on size unl\n");
   $$sql_h{writer}->print("set feedback off\n");
   $$sql_h{writer}->print("set echo off\n");
   $$sql_h{writer}->print("set verify off\n");

   # Connect ...
   if( !(defined($ENV{'DOCKER'}))  || (defined($ENV{'DOCKER'}) && ($ENV{'DOCKER'} eq '0'))){
  	 $$sql_h{writer}->print("conn $userid/$password\@$ENV{'ORACLE_SID'}\n");
   }
   else
   {
        $$sql_h{writer}->print("conn /\@pindb\n");
   }
   $$sql_h{writer}->print("select 'CONN_OK' from dual;\n");

   # Make sure the connection to the DB was successful
   my $error = 1;
   my $line;
   while ($line = $$sql_h{reader}->getline) {
     if($line =~ /^CONN_OK$/) {
        $error = 0;
        last;
     } elsif ($line =~ /ORA-/) {
        last;
     }
   }

   if ($error) {
      $$sql_h{writer}->print("\nexit;\n");
      kill 9, $$sql_h{pid};
      return undef;
   }

   return $sql_h;
}

#------------------------------------------------------------------------------#
#                            S Q L _ C L O S E
#------------------------------------------------------------------------------#

=head2 sql_close

The C<sql_close()> routine closes the SQL connection associated with the
SQL handle passed in input. It does nothing if $sql_h is undef.

  sql_close($sql_h);

PARAMETERS:
  $sql_h    : The handle of a SQL connection opened using
              C<sql_open()>

RETURNS:
  None

NOTES:
  Affected by the feedback mode.

=cut

sub sql_close {
   my ($sql_h) = @_;

   return unless defined $sql_h;

   print "Closing SQL*Plus connection to " .
         "$$sql_h{userid}/XXXXX\@$$sql_h{alias}...\n" if $FEEDBACK;

   $$sql_h{writer}->print("\nexit\n");
   $$sql_h{reader}->close();
   $$sql_h{writer}->close();
   waitpid $$sql_h{pid}, 0;
}

#------------------------------------------------------------------------------#
#                            S Q L _ E X E C
#------------------------------------------------------------------------------#

=head2 sql_exec

The C<sql_exec()> routine executes the SQL statement $sql using the
SQL connection associated with the SQL handle $sql_h.
The output is stored in the string $output (unless it is undef).
If \$elapsed is not undef, the total execution time in seconds is stored in
$elapsed.

    sql_exec($sql_h, $sql, \$output, \$elapsed);

PARAMETERS:
  $sql_h     : The handle of a SQL connection opened using
               C<sql_open()>
  $sql       : The SQL statement to be executed
  \$output   : The reference to the variable that will be filled
               with the results of the SQL statement. If it is not
               defined, the results will not be stored anywhere.
  \$elapsed  : If defined, the variable that will be populated with
               the number of seconds elapsed during the execution of
               the SQL statement

RETURNS:
  None

NOTES:
  Affected by the debug mode.

=cut

sub sql_exec {
   my ($sql_h, $sql, $out_string_ref, $elapsed_ref) = @_;

   # The statement must be terminated by only one ";" or "/"
   my $sql_stmt = $sql;
   $sql_stmt =~ s/[\n;\s]+$//;
   if (substr($sql_stmt, -1, 1) ne "/") {
      $sql_stmt .= ";\n";
   }

   print "DEBUG: executing SQL\n$sql_stmt\n" if $DEBUG;

   my $ts = time();
   my $line;
   $$sql_h{writer}->print("prompt <sql_exec(): START ($ts)>\n");
   $$sql_h{writer}->print("\n$sql_stmt\n");
   $$sql_h{writer}->print("prompt <sql_exec(): END ($ts)>\n");

   # Wait for the START tag
   while ($line = $$sql_h{reader}->getline) {
      chomp($line);
      print "DEBUG SQL output: $line\n" if $DEBUG;
      last if $line eq "<sql_exec(): START ($ts)>";
   }

   # Collect the output until the END tag is found
   $$out_string_ref = "" if defined $out_string_ref;
   while ($line = $$sql_h{reader}->getline) {
      chomp($line);
      print "DEBUG SQL output: $line\n" if $DEBUG;
      next if $line =~ /^$/;
      last if $line eq "<sql_exec(): END ($ts)>";
      $$out_string_ref .= "$line\n" if defined $out_string_ref;
   }
   chomp($$out_string_ref) if defined $out_string_ref;
   my $time_end = time();

   $$elapsed_ref = sprintf ("%.6f", $time_end - $ts) if (defined $elapsed_ref);
}

#------------------------------------------------------------------------------#
#                            S Q L _ Q U E R Y
#------------------------------------------------------------------------------#

=head2 sql_query

The C<sql_query()> routine this subroutine can be used to execute a query
and store the results in an array of hashtables.

  sql_query($sql_h, $sql_body, \%fields, $separator,
            $no_fields, \$elapsed);


The array of hashtables in output will have the same keys as the hashtable
%fields (so they are merely a symbolic way to reference each field in output).
The corresponding values are used to build the fields list in the SELECT
statement. The $sql_body is what is appended to the fields list.
The character $separator will be used for concatenating all required fields.
The resulting statement is executed using the SQL connection associated with
the SQL handle $sql_h.
If \$elapsed is not undef, the total execution time in seconds is stored in
$elapsed.
If $no_fields is true, the list of fields will not be set in the SQL statement
(this cen be used for instance when parsing the output of a PL/SQL block).
Returns the reference to the array of hashtables containing the results, or
undef in case of any error.

PARAMETERS:
  $sql_h     : The handle of a SQL connection opened using
               C<sql_open()>
  $sql_body  : The body of the SQL statement to be executed.
               Typically it is the part of a SELECT statement
               starting from the "FROM" keyword (the "SELECT"
               keyword and the list of fields will be added
               automatically, unless $no_fields is true).
  \%fields   : The reference to a hash with the fields returned
               by the SQL statement. The keys of the hash are the
               symbolic name of each field. The corresponding values
               represent what needs to be actually written in the
               SELECT statement. If a value is undef, it will be
               assumed being equal to the corresponding key.
  $separator : The character that will be used for separating the
               values of the fields returned by the SQL statement.
               It must be a character not present in the results
               themselves.
  $no_fields : If defined and true, the keyword "SELECT" and the
               list of fields will not be added at the beginning
               of the $sql_body. This is useful if the SQL statement
               is actually a PL/SQL block that uses the DBMS_OUTPUT
               in order to return the results (they must be correctly
               formatted and the fields must be separated using the
               $separator character).
  \$elapsed  : If defined, the variable that will be populated with
               the number of seconds elapsed during the execution of
               the SQL statement

RETURNS:
  The reference to an array of hash references containing the results
  of the SQL statement. Each hash has the same keys of %fields and the
  corresponding values are filled with the results of the SQL
  statement.

NOTES:
  Affected by the debug mode.

EXAMPLE:
  my (%fields) = ( acc_poid_id0 => 'a.poid_id0',
                   account_no   => 'a.account_no',
                   svc_poid_id0 => 's.poid_id0',
                   svc_type     => 's.poid_type' );
  my $sql_body = "from account_t a, service_t s " .
                 "where a.poid_id0 = s.account_obj_id0";
  my $elapsed;
  my $results = &sql_query($sql_h, $sql_body, \%fields, "|", 0, \$elapsed);

  The SQL statement actually executed will be:
     SELECT a.poid_id0 || '|' || a.account_no || '|' ||
            s.poid_id0 || '|' || s.poid_type
     FROM account_t a,
          service_t s
     WHERE a.poid_id0 = s.account_obj_id0

  $result will be something like:
  [
    { acc_poid_id0=>1    , account_no=>'ROOT'         , svc_poid_id0=>1    , svc_type=>'/service/pcm_client' },
    { acc_poid_id0=>1    , account_no=>'ROOT'         , svc_poid_id0=>2    , svc_type=>'/service/admin_client' },
    { acc_poid_id0=>12341, account_no=>'0.0.0.1-12341', svc_poid_id0=>15669, svc_type=>'/service/ip' },
    { acc_poid_id0=>14999, account_no=>'0.0.0.1-14999', svc_poid_id0=>12375, svc_type=>'/service/ip' },
    { acc_poid_id0=>13655, account_no=>'0.0.0.1-13655', svc_poid_id0=>15063, svc_type=>'/service/ip' },
    { acc_poid_id0=>16343, account_no=>'0.0.0.1-16343', svc_poid_id0=>13623, svc_type=>'/service/ip' },
    { acc_poid_id0=>19045, account_no=>'0.0.0.1-19045', svc_poid_id0=>16613, svc_type=>'/service/ip' },
    { acc_poid_id0=>18717, account_no=>'0.0.0.1-18717', svc_poid_id0=>17565, svc_type=>'/service/ip' },
    { acc_poid_id0=>19357, account_no=>'0.0.0.1-19357', svc_poid_id0=>16733, svc_type=>'/service/ip' },
    { acc_poid_id0=>22468, account_no=>'0.0.0.1-22468', svc_poid_id0=>24100, svc_type=>'/service/ip' },
    { acc_poid_id0=>23174, account_no=>'0.0.0.1-23174', svc_poid_id0=>22406, svc_type=>'/service/ip' }
  ]

=cut

sub sql_query {
   my ($sql_h, $sql_body, $fields_ref, $separator, $no_fields,
       $elapsed_ref) = @_;
   my ($results, $output) = ([], "");

   my (@keys) = sort keys %{$fields_ref};

   # The statement must be terminated by only one ";" or "/"
   my $sql_stmt = $sql_body;
   $sql_stmt =~ s/[\n;\s]+$//;
   if (substr($sql_stmt, -1, 1) ne "/") {
      $sql_stmt .= ";\n";
   }

   # Build the fields list in the select statement unless explicitly told not
   # to do it
   unless ($no_fields) {
      # Modify $fields_ref: copy the value from the key if the value is
      # undefined
      foreach (@keys) {
         $$fields_ref{$_} = $_ unless defined($$fields_ref{$_});
      }

      $sql_stmt = "select ";
      foreach (@keys) {
         $sql_stmt .= "$$fields_ref{$_}||'$separator'||";
      }

      $sql_stmt = substr($sql_stmt, 0, rindex($sql_stmt, "||'$separator'||"));
      $sql_stmt .= " $sql_body\n;\n";
   }

   # Execute the query
   &sql_exec($sql_h, $sql_stmt, \$output, $elapsed_ref);

   # Parse the results
   $separator = "\\$separator";
   my ($line, $index, $values);
   foreach $line (split("\n", $output)) {
      print "DEBUG: $line\n" if $DEBUG;
      $values = {};
      $index = 0;
      foreach (split($separator, $line)) {
         print "DEBUG: field $index = $_\n" if $DEBUG;
         $$values{$keys[$index++]} = $_;
      }
      push @{$results}, $values;
   }

   return $results;
}

#------------------------------------------------------------------------------#
#                         S Q L _ F E E D B A C K
#------------------------------------------------------------------------------#

=head2 sql_set_feedback

The C<sql_set_feedback()> routine enables or disables the feedback mode for the
routines in this package.
It the expression $bool_feedback is true, the feedback mode is enabled.
If the expression $bool_feedback is true, the feedback mode is disabled.

  sql_set_feedback($bool_feedback);

When feedback mode is enabled, a message will be printed on the standard output
while opening/closing a SQL*Plus connection.  The feedback mode is off by
default.

The functions affected by the feedback mode are:
  sql_open()
  sql_close()

PARAMETERS:
  $bool_feedback: boolean condition to enable/disable the feedback mode

RETURNS:
  None

=cut

sub sql_set_feedback {
   $FEEDBACK = ($_[0]) ? 1 : 0;
}

#------------------------------------------------------------------------------#
#                        S Q L _ S E T _ D E B U G
#------------------------------------------------------------------------------#

=head2 sql_set_debug

The C<sql_set_debug()> routine enables or disables the debug mode for the
routines in this package.
It the expression $bool_debug is true, the debug mode is enabled.
If the expression $bool_debug is true, the debug mode is disabled.

  sql_set_debug($bool_debug);

When debug mode is enabled, detailed messages related to the SQL statement
executed and the raw output returned by SQL*Plus are printed on the
standard output. The debug mode is off by default.

The functions affected by the debug mode are:
  sql_open()
  sql_close()

PARAMETERS:
  $bool_debug: boolean condition to enable/disable the debug mode

RETURNS:
  None

=cut

sub sql_set_debug {
   $DEBUG = ($_[0]) ? 1 : 0;
}

1;
