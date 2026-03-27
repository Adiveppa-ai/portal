setenv PKG_HOME /home/pin/opt/portal/ifw
setenv IFW_HOME __IFW_HOME__
setenv NLS_LANG AMERICAN_AMERICA.AL32UTF8
setenv INT_PERL_LIB $PKG_HOME/tools/PerlLib
setenv INT_BROWSER_HOME $PKG_HOME/tools/Browser

if ( ${?PATH} ) then
  setenv PATH $PKG_HOME/bin:$PATH
else
  setenv PATH $PKG_HOME/bin
endif
if ( ${?LD_LIBRARY_PATH} ) then
  setenv LD_LIBRARY_PATH $PKG_HOME/lib:$LD_LIBRARY_PATH
else
  setenv LD_LIBRARY_PATH $PKG_HOME/lib
endif
if ( ${?LD_LIBRARY_PATH_64} ) then
  setenv LD_LIBRARY_PATH_64 $PKG_HOME/lib:$LD_LIBRARY_PATH_64
endif
if ( ${?SHLIB_PATH} ) then
  setenv SHLIB_PATH $PKG_HOME/lib:$SHLIB_PATH
else
  setenv SHLIB_PATH $PKG_HOME/lib
endif
if ( ${?LIBPATH} ) then
  setenv LIBPATH $PKG_HOME/lib:$LIBPATH
else
  setenv LIBPATH $PKG_HOME/lib
endif
