#!/bin/sh
##==============================================================================
##
##      Copyright (c) 2009 Oracle. All rights reserved.
##      
##      This material is the confidential property of Oracle Corporation or its
##      licensors and may be used, reproduced, stored or transmitted only in
##      accordance with a valid Oracle license or sublicense agreement.
##
##------------------------------------------------------------------------------
##      Module Description:
##      Splits SOL42 files to contain a maximum of 1000 records per file
##
##==============================================================================


if [ $# -ne 2 ]
then
  echo "Usage: splitSol42.sh <sourceDir> <targetDir>"
  exit 1
else
  if [ ! -d $1 -o ! -d $2 ]
  then
    echo "Error: Both $1 and $2 must be directories."
    exit 2
  fi
fi

os=`uname`
sourceDir=$1
targetDir=$2
MAX=1000

for i in `ls $sourceDir`
do
  if [ ! -f $sourceDir/$i ]
  then
    continue
  fi

  nDetails=`egrep -c -e "^(02[0-9]|03[0-1]|04[0-9]|050|060|070|080|12[0-8]|13[0-1]|220.*)" $sourceDir/$i`
  if [ $nDetails -le $MAX ]
  then
    mv $sourceDir/$i $targetDir/$i
  else
    lineNums=`egrep -n -e "^(02[0-9]|03[0-1]|04[0-9]|050|060|070|080|12[0-8]|13[0-1]|220|090.*)" $sourceDir/$i | cut -d ":" -f1`
  
    outFile=""
    startLine=0
    endLine=0
    fp=0
    n=0

    for j in `echo $lineNums`
    do
      if [ $startLine -le 0 ]
      then
        startLine=$j
      fi

      n=`expr $n + 1`
      if [ $n -le $MAX ]
      then
        continue
      else
        fp=`expr $fp + 1`
        n=1
        endLine=$j
      fi

      outFile=$i.$fp

      nLines=`expr $endLine - $startLine`
      head -1 $sourceDir/$i > $targetDir/$outFile
      if [ $os = "Linux" ]
      then
        tail -n +$startLine $sourceDir/$i | head -$nLines >> $targetDir/$outFile
      else
        tail +$startLine $sourceDir/$i | head -$nLines >> $targetDir/$outFile
      fi
      xx=`tail -2 $sourceDir/$i | egrep -e "^090.*" | tr '\t' ',' | cut -d ',' -f1-6`
      yy=`tail -2 $sourceDir/$i | egrep -e "^090.*" | tr '\t' ',' | cut -d ',' -f8-`
      echo $xx,$MAX,$yy | tr "," "\t" >> $targetDir/$outFile
      startLine=$endLine
    done

   if [ $n -gt 1 ]
   then
     fp=`expr $fp + 1`
     endLine=$j
     outFile=$i.$fp

     nLines=`expr $endLine - $startLine`
     head -1 $sourceDir/$i > $targetDir/$outFile
     if [ $os = "Linux" ]
     then
       tail -n +$startLine $sourceDir/$i | head -$nLines >> $targetDir/$outFile
     else
       tail +$startLine $sourceDir/$i | head -$nLines >> $targetDir/$outFile
     fi
     xx=`tail -2 $sourceDir/$i | egrep -e "^090.*" | tr '\t' ',' | cut -d ',' -f1-6`
     yy=`tail -2 $sourceDir/$i | egrep -e "^090.*" | tr '\t' ',' | cut -d ',' -f8-`
     n=`expr $n - 1`
     echo $xx,$n,$yy | tr "," "\t" >> $targetDir/$outFile
   fi

  fi
done

