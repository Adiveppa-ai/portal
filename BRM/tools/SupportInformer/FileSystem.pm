#===============================================================================
# @(#)%Portal Version: FileSystem.pm:PlatformR2Int:1:2006-Jul-04 11:25:34 %
#       Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#      
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#
#
#-------------------------------------------------------------------------------
# Block: TLS
#-------------------------------------------------------------------------------
# Module Description:
#   Perl-Package with some file-system functions.
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
# $RCSfile: FileSystem.pm,v $
# $Revision: 1.8 $
# $Author: jkeckst $
# $Date: 2001/11/14 07:04:22 $
# $Locker:  $
#-------------------------------------------------------------------------------
#
# $Log: FileSystem.pm,v $
# Revision 1.8  2001/11/14 07:04:22  jkeckst
# PETS 41529: change all copyright informations from Solution42 to portal
#
# Revision 1.7  2001/09/04 11:28:24  mgresens
# PETS #37341
# Registry reader changed to parse v4-30 registries.
#
# Revision 1.6  2001/09/04 10:40:53  mgresens
# PETS #38840
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
# Revision 1.2  2000/07/25 13:51:40  mgresens
# First release version.
#
# Revision 1.1  2000/07/25 08:03:05  mgresens
# Shell-Scripts -> sh
# Perl-Packages -> pm
#
# Revision 1.1  2000/07/25 07:07:02  mgresens
# Good work, mike!
#
#===============================================================================

package FileSystem;
use strict;

#-------------------------------------------------------------------------------
# makeDir
#-------------------------------------------------------------------------------
sub makeDir($)
{
  my $path = shift(@_);
  if (system("mkdir", $path) == 0) { return 0; }
  else { return 1; }
}

#-------------------------------------------------------------------------------
# copy
#-------------------------------------------------------------------------------
sub copy($$)
{
  my $path = shift(@_);
  my $regFrom = shift(@_);
  my $regTo = $path . "/" . fullPath2FileName($regFrom);

  if (!(-e $regFrom))
  {
    return;
  }
  if (system("cp", $regFrom, $regTo) == 0)
  {
    main::printLog("  " . $regFrom . " -> " . $regTo . "\n");
  }
  else
  {
    main::printLog("  " . $regFrom . " -> failed\n");
  }
}

#-------------------------------------------------------------------------------
# tail
#-------------------------------------------------------------------------------
sub tail($$)
{
  my $path = shift(@_);
  my $logFrom = shift(@_);
  my $logTo = $path . "/" . fullPath2FileName($logFrom);

  open(TAIL, "tail -n 5000 " . $logFrom . " > " . $logTo . "|");
  close(TAIL);

  if (($? >> 8) == 0)
  {
    main::printLog("  " . $logFrom . " -> " . $logTo . "\n");
  }
  else
  {
    main::printLog("  " . $logFrom . " -> failed\n");
  }
}

#-------------------------------------------------------------------------------
# copyTraceFiles
#-------------------------------------------------------------------------------
sub copyTraceFiles($)
{
  my $path = shift(@_);
  main::printLog("\nCopying trace-files ...\n");

  open(CP, "cp -v *trace* " . $path . "|");
  while(defined(my $entry = <CP>))
  {
    #Remove CR
    $entry = substr($entry, 0, length($entry) - 1);
    main::printLog("  " . $entry . "\n");
  }
  close(CP);

  main::printLog("Copying done ...\n");
}

#-------------------------------------------------------------------------------
# Filenames with full path -> filenames only
#-------------------------------------------------------------------------------
sub fullPath2FileName($)
{
  my @tokens = split("/", shift(@_));
  while (($tokens[0] eq ".") or ($tokens[0] eq ".."))
  {
    shift(@tokens)
  }
  return join("_", @tokens);
}

#-------------------------------------------------------------------------------
# File exists
# Returns 1 on success and 0 on failure
#-------------------------------------------------------------------------------
sub file_exists
{
	my $file_name = shift(@_);
	if ( -e $file_name) {
		return 1;
	} else {
		return 0;
	}
}
# This is just wrapper on makeDir
# Exits if it fails to create directory
sub createDir
{
	my $file_path = shift(@_);
	if (makeDir($file_path) == 1) {
		main::printLog("Failed to create directory $file_path\n");
		exit(1);
	}
}
1;
