###############################################################################
##
## 
## Copyright (c) 1996 - 2006 Oracle. All rights reserved.
## 
## This material is the confidential property of Oracle Corporation or its
## licensors and may be used, reproduced, stored or transmitted only in
## accordance with a valid Oracle license or sublicense agreement.
##
###############################################################################

##################################################################
# $Id: all.inc,v 1.20 2003/03/20 09:39:51 cdiab Exp $
#
# file to include all of the usual *.inc files
##################################################################

include ${SETTINGS_PATH}/buildroot.inc


ifndef INTEGRATE
  INTEGRATE=1
endif

ifndef FRAMEWORK_ROOT
  FRAMEWORK_ROOT=${BUILD_ROOT}
endif

ifdef SOLARIS
  ifeq (${SOLARIS},58)
########################
# We support compilation with only CC 5.5 
########################
    ifeq (${SUNPRO64},55)
      OS_COMP_INCL=solaris58_sunpro64_v55.inc
    endif
  endif
else
ifdef HPUX
  ifeq (${HPUX},B1111)
    ifeq (${ACC64},A0357)
      OS_COMP_INCL=hpux_aCC64_v0357.inc
    endif
  else
    ifeq (${HPUX},B1123)
      ifeq (${ACC64},A0360)
        OS_COMP_INCL=hpux_aCC64_v0360.inc
      endif
    endif
  endif
else
ifdef AIX
  ifeq (${IBMCC64}, 600)
    OS_COMP_INCL=aix_xlC_v600_64.inc
  else
    ifeq (${IBMCC},600)
      OS_COMP_INCL=aix_xlC_v600.inc
    else
      ifeq (${IBMCC},366)
        OS_COMP_INCL=aix_xlC_v366.inc
      endif
    endif
  endif
endif
endif
endif

ifndef OS_COMP_INCL
  nodep=1
  oscomperr:
	@${ECHO} "unsupported operating system '${OS_NAME} ${OS_VERSION}'" \
	         "or compiler version '${COMP_NAME} ${COMP_VER}' !!!" \
                 "check for correct compiler path in PATH environment variable."
	exit 1
endif

firsttarget: all

include ${SETTINGS_PATH}/config.inc

ifdef OS_COMP_INCL
  include ${SETTINGS_PATH}/${OS_COMP_INCL}
endif

include ${SETTINGS_PATH}/comp.inc
include ${SETTINGS_PATH}/incs.inc
include ${SETTINGS_PATH}/libs.inc
include ${SETTINGS_PATH}/pkg.inc

#########
# We no more build doc in the PDK
# Removed the doc section from here
#########
