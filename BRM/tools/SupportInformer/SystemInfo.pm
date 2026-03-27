#===============================================================================
# @(#)%Portal Version: SystemInfo.pm:PlatformR2Int:1:2006-Jul-04 11:25:37 %
#
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
#   Perl-Package to collect the system informations.
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
# $RCSfile: SystemInfo.pm,v $
# $Revision: 1.6 $
# $Author: jkeckst $
# $Date: 2001/11/14 07:04:22 $
# $Locker:  $
#-------------------------------------------------------------------------------
#
# $Log: SystemInfo.pm,v $
# Revision 1.6  2001/11/14 07:04:22  jkeckst
# PETS 41529: change all copyright informations from Solution42 to portal
#
# Revision 1.5  2001/09/04 11:28:24  mgresens
# PETS #37341
# Registry reader changed to parse v4-30 registries.
#
# Revision 1.4  2000/08/18 09:15:41  mgresens
# Checking the right return-code (=0) of 'integRate -v'.
# bzip2-compression supported.
# Redundance of format-descs removed.
# Collecting only 10 newest stream-logs.
# -> SOLUTION42 AG
#
# Revision 1.3  2000/07/28 11:11:03  mgresens
# Packages in same dir like the script.
#
# Revision 1.1  2000/07/25 08:03:05  mgresens
# Shell-Scripts -> sh
# Perl-Packages -> pm
#
# Revision 1.1  2000/07/25 07:07:02  mgresens
# Good work, mike!
#
#===============================================================================

package SystemInfo;
use strict;

my @commands =
(
  "ulimit -a",
  "df -k",
  "env"
);

my @fileNames =
(
  "/user_limit.txt",
  "/disk_space.txt",
  "/environment.txt"
);

#-------------------------------------------------------------------------------
# collect the sys-infos
#-------------------------------------------------------------------------------
sub getSystemInfos($)
{
  my $filePath = shift(@_);
  main::printLog("\nCollecting system informations ...\n");
  main::printLog("  Get the user limits -> ");
  getSystemInfo($commands[0], $filePath . $fileNames[0]);
  main::printLog("  Get the disk spaces -> ");
  getSystemInfo($commands[1], $filePath . $fileNames[1]);
  main::printLog("  Get the environment -> ");
  getSystemInfo($commands[2], $filePath . $fileNames[2]);
  main::printLog("Collecting done ...\n");
}

sub getSystemInfo($$)
{
  my $command = shift(@_);
  my $fileName = shift(@_);

  open(CMD, $command . " > " . $fileName . "|");
  close(CMD);
  if (($? >> 8) == 0)
  {
    main::printLog($fileName . "\n");
  }
  else
  {
    main::printLog("failed\n");
  }
}

1;
