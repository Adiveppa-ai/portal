TPSOURCE=/home/pin/opt/portal/Thirdparty/perl-5.38.2
PIN_HOME=/home/pin/opt/portal/BRM
PIN_LOG_DIR=/home/pin/opt/portal/BRM/var
PIN_LOG=/home/pin/opt/portal/BRM/var
LIBRARYEXTENSION=.so
LIBRARYPREFIX=lib
BRM_WALLET=/home/pin/opt/portal/BRM/wallet/client
BRM_CONF_WALLET=/home/pin/opt/portal/BRM/wallet/client

OS=`uname`
PERL_VERSION=5.38.2
BRM_VERSION=15.0.1.0.0
PERFLIB_HOME=$PIN_HOME/apps/perflib
PERFLIB_LOG_DIR=$PIN_LOG_DIR/perflib
if [ ! -d $PERFLIB_LOG_DIR ]
then
  mkdir -p $PERFLIB_LOG_DIR
fi

BRM_SERVICE_MONITOR_LOG_DIR=$PIN_LOG_DIR/brm_service_monitor
if [ ! -d $BRM_SERVICE_MONITOR_LOG_DIR ]
then
  mkdir -p $BRM_SERVICE_MONITOR_LOG_DIR
fi

if [ "$PERL5LIB" = "" ]
then
  PERL5LIB=$PERL_HOME/lib:$PERL_HOME/lib/$PERL_VERSION:$PERL_HOME/lib/site_perl:$PIN_HOME/lib:$TPSOURCE/lib:$TPSOURCE/lib/$PERL_VERSION:$TPSOURCE/lib/site_perl:$PIN_HOME/tools/PerlLib:$PIN_HOME/tools/SupportInformer:$PERFLIB_HOME
else
  PERL5LIB=$PERL_HOME/lib:$PERL_HOME/lib/$PERL_VERSION:$PERL_HOME/lib/site_perl:$PIN_HOME/lib:$TPSOURCE/lib:$TPSOURCE/lib/$PERL_VERSION:$TPSOURCE/lib/site_perl:$PIN_HOME/tools/PerlLib:$PIN_HOME/tools/SupportInformer:$PERFLIB_HOME:$PERL5LIB
fi
if [ "$PATH" = "" ]
then
  PATH=$PERL_HOME/bin:$PIN_HOME/lib:$PIN_HOME/bin
else
  PATH=$PERL_HOME/bin:$PIN_HOME/bin:$PIN_HOME/lib:$PATH
fi
if [ "$LD_LIBRARY_PATH" = "" ]
then
  LD_LIBRARY_PATH=$PERL_HOME/lib:$PIN_HOME/lib:$PIN_HOME/lib64:$PERFLIB_HOME
else
  LD_LIBRARY_PATH=$PERL_HOME/lib:$PIN_HOME/lib:$PIN_HOME/lib64:$PERFLIB_HOME:$LD_LIBRARY_PATH
fi
if [ "$LD_LIBRARY_PATH_64" = "" ]
then
  LD_LIBRARY_PATH_64=$PIN_HOME/lib:$PIN_HOME/lib64:$PERFLIB_HOME
else
  LD_LIBRARY_PATH_64=$PIN_HOME/lib:$PIN_HOME/lib64:$PERFLIB_HOME:$LD_LIBRARY_PATH_64
fi
if [ "$SHLIB_PATH" = "" ]
then
  SHLIB_PATH=$PIN_HOME/lib:$PIN_HOME/lib64
else
  SHLIB_PATH=$PIN_HOME/lib:$PIN_HOME/lib64:$SHLIB_PATH
fi
if [ "$LIBPATH" = "" ]
then
  LIBPATH=$PERL_HOME/bin:$TPSOURCE/bin:$PIN_HOME/bin:$PIN_HOME/lib:$PIN_HOME/lib64
else
  LIBPATH=$PERL_HOME/bin:$TPSOURCE/bin:$PIN_HOME/bin:$PIN_HOME/lib:$PIN_HOME/lib64:$LIBPATH
fi

if [ -f $PIN_HOME/ttsource.me.sh ]
then
. $PIN_HOME/ttsource.me.sh
fi

OS=`uname`
if [ $OS = "SunOS" ]
then
  LD_LIBRARY_PATH=/usr/sfw/lib:$LD_LIBRARY_PATH
fi
export PIN_HOME PIN_LOG_DIR PIN_LOG LIBRARYEXTENSION LIBRARYPREFIX BRM_WALLET BRM_CONF_WALLET
export PERL5LIB PATH LD_LIBRARY_PATH SHLIB_PATH LIBPATH PERFLIB_HOME PERFLIB_LOG_DIR

if [[ -f $PIN_HOME/bin/start_service_monitor ]]
then
    alias start_service_monitor='start_service_monitor &'
fi

if [[ -f $PIN_HOME/bin/start_memory_monitor ]]
then
    alias start_memory_monitor='start_memory_monitor &'
fi
