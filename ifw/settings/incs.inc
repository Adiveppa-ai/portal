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
# $Id: incs.inc,v 1.26 2003/03/20 12:37:12 mliebmann Exp $
#
# Global includes, hard paths
##################################################################

ifeq "${RW_NO_SUBDIR}" "true"
  RW_INC=-I${RW_PATH}
else
  RW_INC=-I${RW_PATH}/${RW_VERSION}
endif

ifeq "${RW_NATIVE_STDLIB}" "true"
  RW_STD_INC=
else
  ifeq "${RW_COMMON_SUBDIR}" "true"
    # I need to use RW_PATH instead of RW_INC because I am going to change RW_INC
    # and that will make RW_STD_INC to be re-evaluated to the wrong value.
    ifdef AIX
      RW_STD_INC=-I${RW_PATH}/../common/include -I${RW_PATH}/../common/include/ansi -I${RW_PATH}/include -I${RW_PATH}/include/ansi
    else
      RW_STD_INC=-I${RW_PATH}/../common/include -I${RW_PATH}/include 
    endif
    RW_INC+= -I${RW_PATH}/../common
  else
    ifdef AIX
      RW_STD_INC=${RW_INC}/include ${RW_INC}/include/ansi
    else
      RW_STD_INC=${RW_INC}/include
    endif
  endif
endif

ifeq "${CFG_ORBIX_USED}" "true"
  CORBA_INC=-I${CORBA_CXX}/include
else
  CORBA_INC=${CFG_TAO_INC_PATHS}
endif

PIN_INC=-I${PIN_INCDIR}

GLOB_INC+= \
 -I${FRAMEWORK_ROOT}/Framework \
 -I${PIN_INCDIR}
