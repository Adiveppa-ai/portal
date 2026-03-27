#!/bin/ksh
# Copyright (c) 2020, Oracle and/or its affiliates. 
#------------------------------------------------------------------------------#
# SCRIPT: stop_perfd.sh
#
# DESCRIPTION:
#
# Script to stop a running perfd.
#
# INFORMATION:
#
# BRM Performance Tools
#
# REVISION:
#
# $Revision: 1.2 $
# $Author: ihargrea $
# $Date: 2016/06/08 10:06:24 $
#------------------------------------------------------------------------------#

#------------------------------------------------------------------------------#
#             C O N S T A N T S   A N D   D E F A U L T S 
#------------------------------------------------------------------------------#
DEF_PIDFILE=perfd.pid

#------------------------------------------------------------------------------#
# Function     : is_running
#
# Description  : Function to check whether a particular process is running. It
#                uses the PID and (optionally) a name to check.
#
# Input        : pid    Process ID
#                name   Optional name to check
#
# Output       : None
#
# Return       : 0 if running, 1 if not
#------------------------------------------------------------------------------#
is_running()
{
typeset pid=$1
typeset name=$2
typeset rv=

   if [ -z "$pid" ]
   then
      return 1
   fi

   if [ -n "$name" ]
   then
      rv=$(ps -fp $pid | head -2 | tail -1 | grep "$name")
   else
      rv=$(ps -fp $pid | head -2 | tail -1)
   fi

   case "$rv" in
   *${pid}*) return 0;; # Running OK
   *)        return 1;; # Not running
   esac
}

#------------------------------------------------------------------------------#
# Main ...
#------------------------------------------------------------------------------#
G_CMD=$(basename $0)
G_PIDFILE=$DEF_PIDFILE

if [ -r $G_PIDFILE ]
then
   PID=$(cat $G_PIDFILE)
   if is_running $PID
   then
      printf "killing PID $PID "
      kill $PID
      while [ -r $G_PIDFILE ] 
      do
         printf "."
         sleep 1
      done
      printf "\n"
   else
      printf "PID $PID is not running - cleanup pidfile '$G_PIDFILE'\n"
      rm -f $G_PIDFILE
   fi
else
   printf "no pidfile '$G_PIDFILE' found\n"
   exit 1
fi
exit 0
