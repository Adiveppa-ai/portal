setenv PIN_HOME /home/pin/opt/portal/BRM
setenv PIN_LOG_DIR /home/pin/opt/portal/BRM/var
setenv PIN_LOG /home/pin/opt/portal/BRM/var
setenv LIBRARYEXTENSION __LIBEXTN__
setenv LIBRARYPREFIX lib
setenv BRM_WALLET /home/pin/opt/portal/BRM/wallet/client
setenv BRM_CONF_WALLET /home/pin/opt/portal/BRM/wallet/client

set TPSOURCE=/home/pin/opt/portal/Thirdparty/perl-5.38.2

set PERL_VERSION =  5.38.2
setenv BRM_VERSION 15.0.1.0.0
set OSNAME = `uname`
setenv PERFLIB_HOME $PIN_HOME/apps/perflib
setenv PERFLIB_LOG_DIR $PIN_LOG_DIR/perflib
if ( ! -d $PERFLIB_LOG_DIR ) then
  mkdir -p $PERFLIB_LOG_DIR
endif

setenv BRM_SERVICE_MONITOR_LOG_DIR $PIN_LOG_DIR/brm_service_monitor
if ( ! -d $BRM_SERVICE_MONITOR_LOG_DIR ) then
  mkdir -p $BRM_SERVICE_MONITOR_LOG_DIR
endif

if ( ${?PERL5LIB} ) then
  setenv PERL5LIB $PERL_HOME/lib:$PERL_HOME/lib/${PERL_VERSION}:$PERL_HOME/lib/site_perl:$PIN_HOME/lib:$TPSOURCE/lib:$TPSOURCE/lib/${PERL_VERSION}:$TPSOURCE/lib/site_perl:$PIN_HOME/tools/PerlLib:$PIN_HOME/tools/SupportInformer:${PERFLIB_HOME}:$PERL5LIB
else
  setenv PERL5LIB $PERL_HOME/lib:$PERL_HOME/lib/${PERL_VERSION}:$PERL_HOME/lib/site_perl:$PIN_HOME/lib:$TPSOURCE/lib:$TPSOURCE/lib/${PERL_VERSION}:$TPSOURCE/lib/site_perl:$PIN_HOME/tools/PerlLib:$PIN_HOME/tools/SupportInformer:${PERFLIB_HOME}
endif
if ( ${?PATH} ) then
  setenv PATH $PERL_HOME/bin:$PIN_HOME/bin:$PIN_HOME/lib:$PATH
else
  setenv PATH $PERL_HOME/bin:$PIN_HOME/bin:$PIN_HOME/lib
endif
if ( ${?LD_LIBRARY_PATH} ) then
  setenv LD_LIBRARY_PATH $PERL_HOME/lib:$PIN_HOME/lib64:$PIN_HOME/lib:${PERFLIB_HOME}:$LD_LIBRARY_PATH
else
  setenv LD_LIBRARY_PATH $PERL_HOME/lib:$PIN_HOME/lib64:$PIN_HOME/lib:${PERFLIB_HOME}
endif
if ( ${?LD_LIBRARY_PATH_64} ) then
  setenv LD_LIBRARY_PATH_64 $PIN_HOME/lib:$PIN_HOME/lib64:${PERFLIB_HOME}:$LD_LIBRARY_PATH_64
else
  setenv LD_LIBRARY_PATH_64 $PIN_HOME/lib:$PIN_HOME/lib64:${PERFLIB_HOME}
endif
if ( ${?SHLIB_PATH} ) then
  setenv SHLIB_PATH $PIN_HOME/lib:$PIN_HOME/lib64:$SHLIB_PATH
else
  setenv SHLIB_PATH $PIN_HOME/lib:$PIN_HOME/lib64
endif
if ( ${?LIBPATH} ) then
  setenv LIBPATH $TPSOURCE/bin:$PIN_HOME/bin:$PIN_HOME/lib:$PIN_HOME/lib64:$LIBPATH
else
  setenv LIBPATH $TPSOURCE/bin:$PIN_HOME/bin:$PIN_HOME/lib:$PIN_HOME/lib64
endif

if ( -f $PIN_HOME/ttsource.me.csh) then
   source $PIN_HOME/ttsource.me.csh
endif

set OSNAME = `uname`
if($OSNAME == 'SunOS') then
  setenv LD_LIBRARY_PATH /usr/sfw/lib:$LD_LIBRARY_PATH
endif


if ( -f $PIN_HOME/bin/start_service_monitor) then
    alias start_service_monitor '$PIN_HOME/bin/start_service_monitor &'
endif

if ( -f $PIN_HOME/bin/start_memory_monitor) then
    alias start_memory_monitor '$PIN_HOME/bin/start_memory_monitor &'
endif
