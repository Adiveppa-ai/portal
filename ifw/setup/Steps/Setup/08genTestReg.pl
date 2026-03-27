#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl

#	
#	Copyright (c) 1996 - 2006 Oracle. All rights reserved.
#	
#	This material is the confidential property of Oracle Corporation or its
#	licensors and may be used, reproduced, stored or transmitted only in
#	accordance with a valid Oracle license or sublicense agreement.

# this file will convert a production registry file to a debug registry for
# test purposes. It will insert EDR dumps after every function plugin and
# will turn on the LogEvents Parameter.

# Setup files
#my $fname = $ARGV[0];
my $fname = $ENV{"REGISTRY_PATH"};
my $outfile = "$fname.debug";
 
open(FPTR, "$fname") ||
        die("\n\cGERROR : cannot open \'${fname}\': $!\n");
open(FOUTPUT, ">$outfile") ||
        die("\n\cGERROR : cannot open \'${outfile}\': $!\n");
 
#Setup variables
my $pool_start=0;
my $open_pool_brace=0;
my $open_curly_brace=0;
my $close_curly_brace=0;
my $mod_start=0;
my $file_count=0;
my $indentation=0;
my @mod_name=0;
 
while (<FPTR>) {

    # Search for LogEvents and set it to True
    if (/LogEvents/) {
       s/LogEvents\s*=\s*(?i)False/LogEvents = True/;
    }


   # write the line to file 
    my $line = $_;
    printf FOUTPUT ("$line");
 
    if (/([ ]*)FunctionPool/){
        $pool_start=1;
        $indentation = $1;
        $indentation.="  ";
    }
 
    if (/{/) {
        if ($pool_start==1){
            if ($open_curly_brace ==0) {
              $open_pool_brace = 1;
            }
            $open_curly_brace++;
        }
    }
 
    if (/}/) {
        if ($pool_start==1){
            $open_curly_brace--;
        }
    }
 
    if (/ModuleName/){
        chop;
        @mod_name = split(/= /,$line);
        $mod_name[1] =~ s/\s+$//;  #remove whitespace at end of string
        if ($pool_start==1){
            $mod_start=1;
        }
    }

    if ($open_curly_brace==1){
        if ($mod_start==1){
            printf FOUTPUT ("%s#--------------------------------------------------\n",$indentation);
            printf FOUTPUT ("%s# EDR Dump\n",$indentation);
            printf FOUTPUT ("%s#--------------------------------------------------\n",$indentation);
            printf FOUTPUT ("%sEdrDump_$mod_name[1]\n",$indentation);
            printf FOUTPUT ("%s{\n",$indentation);
            printf FOUTPUT ("%s  ModuleName = FCT_EdrDump\n",$indentation);
            printf FOUTPUT ("%s  Module\n",$indentation);
            printf FOUTPUT ("%s  {\n",$indentation);
            printf FOUTPUT ("%s     Active = True\n",$indentation);
            printf FOUTPUT ("%s     FileName = ./data/dump/$mod_name[1]_dump.txt\n",$indentation);
            printf FOUTPUT ("%s  }\n",$indentation);
            printf FOUTPUT ("%s}\n",$indentation);
            $mod_start=0;
            $file_count++;
        }
    }
 
    if (($open_curly_brace==0) && ($open_pool_brace==1) && ($pool_start==1)){
        $pool_start=0;
        $open_pool_brace =0;
    }
 
}
 
close(FOUTPUT ) ||
        die("\n\cGERROR : cannot close \'${outfile}\': $!\n");  
