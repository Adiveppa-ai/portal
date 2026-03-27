# ---------------------------------------------------------------------------------
#      
#      Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#      
#      This material is the confidential property of Oracle Corporation or its
#      licensors and may be used, reproduced, stored or transmitted only in
#      accordance with a valid Oracle license or sublicense agreement.
#
# ---------------------------------------------------------------------------------
#      This file contains a library of functions used by the pin_setup utility
# ---------------------------------------------------------------------------------
package functions;
%Configvar;
@aSteps;

#-----------------------------------------------------------------------------------
#      Function Name : configinit()
#      Arguments     : None
#      Return Values : None
#      Description   : This function opens the config file,and loads the values into 
#                      an associative array %ConfigVar,and these can be accessed as a (name,value) pair.
#-----------------------------------------------------------------------------------
sub configinit
{
open(CFG,"pin_setup.values");
map { chomp($_);
      if((substr($_,0,1) ne "#") &&(length($_)>0)){
          my $key=substr($_,0,rindex($_,"="));
          $key =~ s/\s//;
          my $value=substr($_,rindex($_,"=")+1,length($_));
          $value =~ s/^\s*//;
	  $Configvar{$key}=$value;}} <CFG>;
 close(CFG);
}

#-----------------------------------------------------------------------------------
#      Function Name : returnval($inpkey)
#      Arguments     : $inpkey
#      Return Values : $outval
#      Description   : This function uses a name(input parameter-$inpkey) to index into the %Configvar array and
#                      then returns the corresponding value.
#-----------------------------------------------------------------------------------
sub returnval
{
  my $inpkey=@_[0];
  my $outval=$Configvar{$inpkey};
  return $outval;
}

#-----------------------------------------------------------------------------------
#      Function Name : createlog()
#      Arguments     : None
#      Return Values : None
#      Description   : This function creates a log file,which can be used to store debug 
#                      values for pin_setup.
#-----------------------------------------------------------------------------------
sub createlog
{
  open (logfile,">".$ENV{"cwd"}."debug.log");
  close(logfile);
}

#-----------------------------------------------------------------------------------
#      Function Name : lprint($x,$y)
#      Arguments     : $x,$y
#      Return Values : None
#      Description   : This function will print the two input parameters $x,$y 
#                      in the form $x=$y to the debug log file.
#-----------------------------------------------------------------------------------
sub lprint {
my $dir=">>".$ENV{"cwd"}."debug.log";
open(logfile,$dir);
my($x,$y)=@_;
print logfile "################# \n";
print logfile $x;
print logfile "=> " , $y , "\n";
close(logfile);
} 

#-----------------------------------------------------------------------------------
#      Function Name : stopbgproc($sig)
#      Arguments     : $sig
#      Return Values : None
#      Description   : This function will kill the process passed to it as an 
#                      input parameter.
#-----------------------------------------------------------------------------------
 sub stopbgproc{
  my $sig=shift || 16; #USR1
  unlink($teetrackfile);
  if( @BGPROC ){
    #print "stopping background processes: ",join(',',@BGPROC),"...";
    sleep 1; #just a little while
    kill $sig, @BGPROC; 
    sleep 1; #just a little while
    }
  @BGPROC=();
  wait(); #be nice about it
  }

#-----------------------------------------------------------------------------------
#      Function Name : ostype()
#      Arguments     : None
#      Return Values : $platform
#      Description   : This function will return platform type.
#
#-----------------------------------------------------------------------------------

sub ostype{
  use POSIX qw(uname);
  my ($uname_s, $uname_r) = (POSIX::uname())[0,2];
  my $platform = substr($uname_s, 0, 7);
  return $platform;
}

#-----------------------------------------------------------------------------------
#      Function Name : fulldie($string)
#      Arguments     : $string
#      Return Values : None
#      Description   : This function will print a error message and then call stopbgproc() 
#                     
#-----------------------------------------------------------------------------------
sub fulldie {
  print "\n$zeroprog: ",@_,"\n$zeroprog: ABORTING... ";
  #hm... double kill?
  print "\n$zeroprog: EXITING\n";
  stopbgproc($userdie);
  #hm?
  $SIG{HUP}= $SIG{INT}= undef; #just in case
  kill 2, -getpgrp() if $userdie;
  exit 77;
  }

#-----------------------------------------------------------------------------------
#      Function Name : teelog($fname,$log)
#      Arguments     : $fname,$log
#      Return Values : None
#      Description   : This function will redirect all error messages to a log file $fname 
#                      if $log parameter is set to 1
#-----------------------------------------------------------------------------------

sub teelog {
  #redirect stderr/stdout to a file, periodically printing any new contents.
  #we do this in perl so we avoid the tee daemon jammup issue.
  #notice that we append. unlink($fname) if you don't want it.

  my ($fname)=shift(@_);
  my($log)=shift(@_);
  open(LOGF,">$fname") or fulldie "ERROR: cannot open logfile \"$fname\"";
  my $lfsize=(stat(LOGF))[7];

  #an old trick, revisited
  open(JUNKF,">$teetrackfile");
  close(JUNKF);

  my $procid;
  if( $log ){
    #now monitor it.
    $procid=fork();
    fulldie "ERROR: tee-fork() failed" unless defined $procid;
    if( defined $procid && !$procid ){
      #ah! here's our cup of tee.
      @BGPROC=();
      my $ppid=getppid();

      my $getout=0;
      $SIG{HUP}= $SIG{INT}=sub {
        $SIG{HUP}= $SIG{INT}=sub {}; #ignore further efforts
        if( !$getout) { $getout=1; kill 1, $ppid; }
        }; #pass the trouble along
      $SIG{16}=sub { $getout=1; }; #nice request from parent

      close(LOGF);
      close(STDIN); #don't need it
      open(LOGF,"<$fname") or fulldie "CANNOT OPEN LOGFILE FOR TEE; HIT CONTROL-C TO CANCEL FOREGROUND PROCESS";
      close(STDERR);

      my ($rin, $win, $ein);
      my ($rout, $wout, $eout, $sif);
      $rin = $win = $ein = '';
      vec($rin,$sif=fileno(LOGF),1) = 1;

      #be nice
      eval "setpriority( 0, 0, 10 + getpriority( 0, 0))";

      sysseek(LOGF,$lfsize,0);
      my $iobuf;
      while(1){
        sleep 1; #just a little slower, please; otherwise, too much cpu time

        #full lines should be printed *IF* they actually exist in the AUTOINSTALL.LOG file
        while(sysread(LOGF,$iobuf,128)){ syswrite(STDOUT,$iobuf,128); $iobuf=""; }
        syswrite(STDOUT,$iobuf,128) if length($iobuf);

        #again, for the astute unix person: see perl manpages for interrupted sysread (/syswrite?) issues.
        #(just in case shutdown is in progress)
        while(sysread(LOGF,$iobuf,128)){ syswrite(STDOUT,$iobuf,128); } #on EOF, this will drop out to the select()
        syswrite(STDOUT,$iobuf,128) if length($iobuf);

        #the wise man will notice the many race conditions here, but we don't care too much
        last unless -e $teetrackfile;
        last unless kill 0, $ppid; #this should just check if parent okay
        last if $getout;
        }
      exit 0;
      }
    }

  #the kid plays while the parents talk
  open(STDOUT,">&LOGF") or fulldie "ERROR: STDOUT redirect failed";
  select(LOGF); $|=1;
  push @BGPROC, $procid if defined $procid; #just in case I turn this off

  return $procid; #now be sure to kill it before you exit, eh?
  }

#-----------------------------------------------------------------------------------
#      Function Name : LoadSteps()
#      Arguments     : None
#      Return Values : None
#      Description   : This function will search the Steps dir for all sub directories named 
#                      in the StepDirs parameter in the pin_setup.value file,and order all files 
#                      found in these step directories ,in an alphabetic order.                      
#-----------------------------------------------------------------------------------

  sub LoadSteps{
          $instalDir = returnval("InstallDir");
	  my $steproot=$instalDir."/setup/Steps/";
          my $StepDirs=functions::returnval("StepDirs");
	  print "StepDir= ",$StepDirs,"\n";
	  my @SubDir=split /,/,$StepDirs;
          my $len=@SubDir;
          print "length= ",$len,"\n";	  
	  my $track=0;
	  my @aTmp;
	  while($track<$len)
	  {
	           $dir=$steproot.@SubDir[$track];
	           opendir(fDir,$dir) || functions::fulldie "ERROR: could not opendir($dir)";
		   push @aTmp,grep !/\.\.?$/, map "$dir/$_",readdir fDir;
		   $track++;
	  }
  	    @aSteps=sort{substr("/$a",rindex("/$a","/")) cmp substr("/$b",rindex("/$b","/"))}(@aTmp);
  }
#-----------------------------------------------------------------------------------
#      Function Name : GetStep($index)
#      Arguments     : $index
#      Return Values : $step
#      Description   : This function will return the step located at $aSteps[$index] 
#                      
#                      
#-----------------------------------------------------------------------------------
  
  sub GetStep{
	  my $index=@_[0];
	  my $step=@aSteps[$index];
	  return $step;
  }

#-----------------------------------------------------------------------------------
#      Function Name : RetLength()
#      Arguments     : None
#      Return Values : $length
#      Description   : This function will return the length of the array aSteps; 
#                      
#                      
#-----------------------------------------------------------------------------------

  sub RetLength{
	  my $length=@aSteps;
	  return $length;
  }

#-----------------------------------------------------------------------------------
#      Function Name : writeinput(username,password,sid)
#      Arguments     : username,password,sid
#      Return Values : None
#      Description   : This function will write the db username,password and sid  
#                      to the file input.txt
#                      
#-----------------------------------------------------------------------------------


sub writeinput{
open("INP",">input.txt");
print INP shift(@_),"\n";
print INP shift(@_),"\n";
print INP shift(@_),"\n";
print INP "Y","\n";
close(INP);
}

#-----------------------------------------------------------------------------------
#      Function Name : readencryptedpassword()
#      Arguments     : None
#      Return Values : $dbpasswd
#      Description   : This function will read and return the encrypted password from the   
#                      file output.txt
#                      
#-----------------------------------------------------------------------------------

sub readencryptedpasswd{
open(OUT,"<output.txt");
my $dbpasswd;
while(<OUT>)
{
  chomp($_);
  if(/^Encrypted/)
    {
      $dbpasswd=substr($_,index($_,":")+2,length($_));
      break;
    }
}
return $dbpasswd;
}

#-----------------------------------------------------------------------------------
#      Function Name : calldbpasswd()
#      Arguments     : None
#      Return Values : None
#      Description   : This function will call the dbPasswd utility,passing it the input parameters
#                      and writing the output from dbPasswd to output.txt
#                      
#-----------------------------------------------------------------------------------

sub calldbPasswd{
$user =  shift(@_);
$passwd= shift(@_);
$cnfPasswd = shift(@_);
$upper = "Y";
$EncryptionLogic = "Y";
$exe="$ENV{'INSTALL_DIR'}/bin/dbPasswd  $user $passwd $cnfPasswd $upper $EncryptionLogic > output.txt";
system($exe);
}

 
1;
