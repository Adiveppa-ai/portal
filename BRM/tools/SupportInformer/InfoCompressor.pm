#===============================================================================
# @(#)%Portal Version: InfoCompressor.pm:PlatformR2Int:1:2006-Jul-04 11:25:49 %
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
#   Perl-Package to compress the informations.
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
# $RCSfile: InfoCompressor.pm,v $
# $Revision: 1.6 $
# $Author: jkeckst $
# $Date: 2001/11/14 07:04:22 $
# $Locker:  $
#-------------------------------------------------------------------------------
#
# $Log: InfoCompressor.pm,v $
# Revision 1.6  2001/11/14 07:04:22  jkeckst
# PETS 41529: change all copyright informations from Solution42 to portal
#
# Revision 1.5  2001/09/04 11:28:24  mgresens
# PETS #37341
# Registry reader changed to parse v4-30 registries.
#
# Revision 1.4  2000/08/18 09:15:40  mgresens
# Checking the right return-code (=0) of 'integRate -v'.
# bzip2-compression supported.
# Redundance of format-descs removed.
# Collecting only 10 newest stream-logs.
# -> SOLUTION42 AG
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

package InfoCompressor;
use strict;

#-------------------------------------------------------------------------------
# compress the infos
#-------------------------------------------------------------------------------
sub compressInfos($)
{
  my $filePath = shift(@_);

  main::printLog("\nCompressing the support informations ...\n");
  close(main::logfile);
  tarWithBZIP2($filePath);
  print("Compression done ...\n");
}

sub tarWithBZIP2($)
{
  my $filePath = shift(@_);
  my $fileName = $filePath . ".tar.bz2";
  print("  'tar -cIf' -> ");
  if (system("tar", "-cIf", $fileName, $filePath) == 0)
  {
    print($fileName . "\n");
  }
  else
  {
    print("failed\n");
    tarWithGZIP($filePath);
  }
}

sub tarWithGZIP($)
{
  my $filePath = shift(@_);
  my $fileName = $filePath . ".tar.gz";
  print("  'tar -czf' -> ");
  if (system("tar", "-czf", $fileName, $filePath) == 0)
  {
    print($fileName . "\n");
  }
  else
  {
    print("failed\n");
    tarWithout($filePath);
  }
}

sub tarWithout($)
{
  my $filePath = shift(@_);
  my $fileName = $filePath . ".tar";
  print("  'tar -cf' -> ");
  if (system("tar", "-cf", $fileName, $filePath) == 0)
  {
    print($fileName . "\n");
    gzip($fileName);
  }
  else
  {
    print("failed\n");
  }
}

sub gzip($)
{
  my $fileName = shift(@_);
  print("  'gzip' -> ");
  if (system("gzip", $fileName) == 0)
  {
    print($fileName . ".gz\n");
  }
  else
  {
    print("failed\n");
    compress($fileName);
  }
}

sub compress($)
{
  my $fileName = shift(@_);
  print("  'compress' -> ");
  if (system("compress", $fileName) == 0)
  {
    print($fileName . ".Z\n");
  }
  else
  {
    print("failed\n");
  }
}

1;
