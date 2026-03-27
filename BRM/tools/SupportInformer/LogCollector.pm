#===============================================================================
# @(#)%Portal Version: LogCollector.pm:PlatformR2Int:1:2006-Jul-04 11:25:46 %
#       Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#      
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#
#-------------------------------------------------------------------------------
# Block: TLS
#-------------------------------------------------------------------------------
# Module Description:
#   Perl-Package to collect the filenames of all logs.
#
# Open Points:
#   none
#
# Review Status:
#   <in-work>
#
#-------------------------------------------------------------------------------
# Responsible: Mike Gresens
#
# $RCSfile: LogCollector.pm,v $
# $Revision: 1.7 $
# $Author: jkeckst $
# $Date: 2001/11/14 07:04:22 $
# $Locker:  $
#-------------------------------------------------------------------------------
#
# $Log: LogCollector.pm,v $
# Revision 1.7  2001/11/14 07:04:22  jkeckst
# PETS 41529: change all copyright informations from Solution42 to portal
#
# Revision 1.6  2001/09/04 11:28:24  mgresens
# PETS #37341
# Registry reader changed to parse v4-30 registries.
#
# Revision 1.5  2000/08/18 09:15:40  mgresens
# Checking the right return-code (=0) of 'integRate -v'.
# bzip2-compression supported.
# Redundance of format-descs removed.
# Collecting only 10 newest stream-logs.
# -> SOLUTION42 AG
#
# Revision 1.4  2000/08/08 07:12:53  mgresens
# Added: Collecting Alias/Format-Descriptions.
#
# Revision 1.3  2000/07/28 11:11:03  mgresens
# Packages in same dir like the script.
#
# Revision 1.2  2000/07/28 07:40:12  mgresens
# sh/collectStreamLogs.sh replaced by function in pm/LogCollector.pm
#
# Revision 1.1  2000/07/25 08:03:05  mgresens
# Shell-Scripts -> sh
# Perl-Packages -> pm
#
# Revision 1.1  2000/07/25 07:07:02  mgresens
# Good work, mike!
#
# Revision 1.1  2000/07/21 14:24:05  mgresens
# Collecting the system-environment added.
# Compression added.
#
#===============================================================================

package LogCollector;
use strict;

#-------------------------------------------------------------------------------
# Collects all log-filenames and proovs their existence
#-------------------------------------------------------------------------------
sub getLogFileNames($)
{
  my $info = shift(@_);
  my @list;

  #ProcessLog
  my $name = info2Str($info->{Process});
  if (open(LOGFILE, "<" . $name))
  {
    push(@list, $name);
    close(LOGFILE);
  }

  #FormatLogs
  foreach my $format (@{$info->{FormatLogs}})
  {
    my $name = info2Str($format);
    if (open(LOGFILE, "<" . $name))
    {
      push(@list, $name);
      close(LOGFILE);
    }
  }

  #StreamLogs
  foreach my $stream (@{$info->{StreamLogs}})
  {
    push(@list, getStreamFileNames($stream));
  }

  #Print Logs found
  foreach my $name (@list)
  {
    main::printLog("  " . $name . "\n");
  }

  return @list;
}

#-------------------------------------------------------------------------------
#Collects all streamlog-filenames
#-------------------------------------------------------------------------------
sub getStreamFileNames($)
{
  my $info = shift(@_);
  my @list;

  open(LS, "ls -t " . $info->{Path} . "/" . $info->{Prefix} . "*" . $info->{Suffix} . "|");
  for (my $i = 0; ($i < 10) and (defined(my $entry = <LS>)); $i++)
  {
    # Remove CR
    $entry = substr($entry, 0, length($entry) - 1);
    # Insert into list
    push(@list, $entry);
  }
  close(LS);
  return @list;
}

sub info2Str($)
{
  my $info = shift(@_);
  return $info->{Path} . "/" . $info->{Prefix} . $info->{Name} . $info->{Suffix};
}

1;
