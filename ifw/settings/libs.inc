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
# $Id: libs.inc,v 1.18 2001/08/14 12:57:02 mliebmann Exp $
#
# Global libs
##################################################################

ifeq "${RW_NO_SUBDIR}" "true"
  RW_LIBS_PATH=-L${RW_PATH}/lib
  REAL_RW_LIBS_PATH=${RW_PATH}/lib
else
  RW_LIBS_PATH=-L${RW_PATH}/${RW_VERSION}/lib
  REAL_RW_LIBS_PATH=${RW_PATH}/${RW_VERSION}/lib
endif

ifdef SOLARIS
  SHLIB_EXT = so
else
  ifdef AIX
    SHLIB_EXT = a
  else
    ifdef HPUX
      SHLIB_EXT = sl
    endif
  endif
endif

ORACLE_LIBS_PATH=-L$(ORA_LIB_PATH)

CORBA_LIBS_PATH=-L$(CORBA_CXXLIB) -L${CORBA_SHLIB} -L${CORBA_DEFLIB}

GLOB_LIB=${BUILD_ROOT}/lib

FRAMEWORK_LIB=${FRAMEWORK_ROOT}/lib

ifeq "${FRAMEWORK_ROOT}" "${BUILD_ROOT}"
  GLOB_LIB_PATH=-L${FRAMEWORK_LIB}
else
  GLOB_LIB_PATH=-L${FRAMEWORK_LIB} -L${GLOB_LIB}
endif

ifeq "${RW_NATIVE_STDLIB}" "true"
  RW_STD_LIB=
  RW_STREAM_LIB= 
else
  RW_STD_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libstd*$(RW_VERSION).$(SHLIB_EXT)))))
  RW_STREAM_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard  $(REAL_RW_LIBS_PATH)/libstreams*$(RW_VERSION).$(SHLIB_EXT)))))
  RW_STD_LIB+= $(RW_STREAM_LIB)
endif

RW_TLS_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libtls*$(RW_VERSION).$(SHLIB_EXT)))))

RW_DBT_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libdbt*$(RW_VERSION).$(SHLIB_EXT)))))
RW_ORA_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libora*$(RW_VERSION).$(SHLIB_EXT)))))
RW_OR8_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libor8*$(RW_VERSION).$(SHLIB_EXT)))))
RW_OR9_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libor9*$(RW_VERSION).$(SHLIB_EXT)))))
  
RW_MNY_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libmny*$(RW_VERSION).$(SHLIB_EXT)))))
RW_MTH_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libmth*$(RW_VERSION).$(SHLIB_EXT)))))
RW_BLA_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libbla*$(RW_VERSION).$(SHLIB_EXT)))))
  
RW_THREAD_LIB      =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libthread*$(RW_VERSION).$(SHLIB_EXT)))))
RW_ITC_LIB         =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libitc*$(RW_VERSION).$(SHLIB_EXT)))))
RW_MIME_LIB         =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libmime*$(RW_VERSION).$(SHLIB_EXT)))))
# The following get functor, functor_map and functor_list
RW_FUNCTOR_LIB    =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libfunctor*$(RW_VERSION).$(SHLIB_EXT)))))
RW_FUNCTOR_MAP_LIB =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libfunctor_map*$(RW_VERSION).$(SHLIB_EXT)))))
RW_FUNCTOR_LIST_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libfunctor_list*$(RW_VERSION).$(SHLIB_EXT)))))
RW_POINTER_LIB     =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libpointer*$(RW_VERSION).$(SHLIB_EXT)))))
RW_SYNC_LIB        =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libsync*$(RW_VERSION).$(SHLIB_EXT)))))
RW_THREXCEPT_LIB   =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libthrexcept*$(RW_VERSION).$(SHLIB_EXT)))))
RW_TRACE_LIB       =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libtrace*$(RW_VERSION).$(SHLIB_EXT)))))

RW_THR_LIB=${RW_THREAD_LIB}
RW_THR_LIB+= ${RW_ITC_LIB}
RW_THR_LIB+= ${RW_FUNCTOR_LIBS}
RW_THR_LIB+= ${RW_POINTER_LIB}
RW_THR_LIB+= ${RW_SYNC_LIB}
RW_THR_LIB+= ${RW_THREXCEPT_LIB}
RW_THR_LIB+= ${RW_TRACE_LIB}
  
RW_NET_LIB=$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libnetwork*$(RW_VERSION).$(SHLIB_EXT)))))
  
RW_INTERNET_LIB    =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libinternet*$(RW_VERSION).$(SHLIB_EXT)))))
RW_FTP_LIB         =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libftp*$(RW_VERSION).$(SHLIB_EXT)))))
RW_HTTP_LIB        =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libhttp*$(RW_VERSION).$(SHLIB_EXT)))))
RW_POP3_LIB        =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libpop3*$(RW_VERSION).$(SHLIB_EXT)))))
RW_SMPT_LIB        =$(patsubst lib%,-l%,$(basename $(notdir $(wildcard $(REAL_RW_LIBS_PATH)/libsmtp*$(RW_VERSION).$(SHLIB_EXT)))))

RW_INT_LIB=${RW_INTERNET_LIB}
RW_INT_LIB+= ${RW_FTP_LIB}
RW_INT_LIB+= ${RW_HTTP_LIB}
RW_INT_LIB+= ${RW_POP3_LIB}
RW_INT_LIB+= ${RW_SMPT_LIB}

ifeq "${CFG_ORBIX_USED}" "true"
  CORBA_LIBS=-lit_poa -lit_naming -lit_art -lit_ifc
else
  CORBA_LIBS=-lTAO -lACE -lTAO_PortableServer -lTAO_CosNaming
endif


ifdef AIX 
  PIN_LIBS=${PIN_LIBDIR}/libpcm.so ${PIN_LIBDIR}/libpinlog.so
else
  PIN_LIBS=${PIN_LIBDIR}/libpcm.a ${PIN_LIBDIR}/libpinlog.a
endif

GLOB_BIN=${BUILD_ROOT}/bin

FRAMEWORK_BIN=${FRAMEWORK_ROOT}/bin

