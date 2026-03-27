#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl
#       
#       Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#       
#       This material is the confidential property of Oracle Corporation or its
#       licensors and may be used, reproduced, stored or transmitted only in
#       accordance with a valid Oracle license or sublicense agreement.
#################################################################################
#This is to update the source.me.csh file with master directory path
#################################################################################
$filePath=$ENV{"INT_HOME"};
my $fileName;
my $origFile;
$command;

$bkupFile=$filePath . "/source.me.csh.ORIG";
if($ENV{'OS_TYPE'} ne "Windows") {
  $fileName= "/source.me.csh";
  $origFile=$filePath . $fileName;
  $command="cp $origFile" . " " . "$bkupFile";
}
else {
  $fileName= "\\source.me.csh";
  $origFile=$filePath . $fileName;
  $command="copy \"$origFile\" " . " " . " \"$bkupFile \" ";
}
system($command);

$tempFile="./source.me.csh.tmp";


open IN1, "$origFile" || die "ERROR : cannot open for reading ";
open OUT1, "> $tempFile" || die "GERROR : Unable to create temporary file for writing ";

while(<IN1>)
{
	if(/\s*setenv\s+IFW_HOME\s*/)
	{
		my $infpath = $ENV{"INT_HOME"};
		print OUT1 "setenv IFW_HOME $infpath\n";
	}
  
	elsif(/\s*setenv\s+PKG_HOME\s*/)
	{
		my $infpath = $ENV{"INT_HOME"};
		print OUT1 "setenv PKG_HOME $infpath\n";
	}

 
	else
	{
		print OUT1 $_;
	}
}
close IN1;
close OUT1;

if($ENV{'OS_TYPE'} ne "Windows") {
  $command = "mv $tempFile" . " " . "$origFile";
}
else {
  $command = "move /Y \"$tempFile\"" . " " . "\"$origFile\"";
}
$ret=system( $command ); 

################################################################################
#This segment is to modify the contents of source.me.sh file of master directory
################################################################################

$filePath=$ENV{"INT_HOME"};
$bkupFile=$filePath . "/source.me.sh.ORIG";
if($ENV{'OS_TYPE'} ne "Windows") {
  $fileName= "/source.me.csh";
  $origFile=$filePath . $fileName;
  $command="cp $origFile" . " " . "$bkupFile";
}
else {
  $fileName= "\\source.me.csh";
  $origFile=$filePath . $fileName;
  $command="copy \"$origFile\" " . " " . " \"$bkupFile \" ";
}
system($command);

$tempFile="./source.me.sh.tmp";

open IN1, "$origFile" || die "ERROR : cannot open for reading ";
open OUT1, "> $tempFile" || die "GERROR : Unable to create temporary file for writing ";

while(<IN1>)
{
	if(/\s*\IFW_HOME=\s*/)
	{
		my $infpath = $ENV{"INT_HOME"};
		print OUT1 "IFW_HOME=$infpath\n";
	}
	elsif(/\s*PKG_HOME=\s*/)
	{
        my $infpath = $ENV{"INT_HOME"};
        print OUT1 "PKG_HOME=$infpath\n";
	}
	else
	{
		print OUT1 $_;
	}
}
close IN1;
close OUT1;

if($ENV{'OS_TYPE'} ne "Windows") {
  $command = "mv $tempFile" . " " . "$origFile";
}
else {
  $command = "move /Y $tempFile" . " " . "\"$origFile\"";
}
$ret=system( $command );

