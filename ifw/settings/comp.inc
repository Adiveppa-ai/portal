##################################################################
# $Id: comp.inc,v 1.30 2001/09/18 08:23:25 bt Exp $
#
# compiler & linker settings
##################################################################

BIN_TYPE=
LIB_TYPE=
GLOB_INC=-I/tools/opt/include

PURIFY_CACHE= ${BUILD_ROOT}/cache/purify
PURIFY_OPTS= -cache-dir=${PURIFY_CACHE}
PURIFY_OPTS+= -always-use-cache-dir=yes -max_threads=40 -best-effort
PURIFY_OPTS+= -lazy-load=no
PURIFY_BIN= ${PURE_PATH}/purify${PURE_VERSION}/purify

QUANTIFY_CACHE= ${BUILD_ROOT}/cache/quantify
QUANTIFY_OPTS= -cache-dir=${QUANTIFY_CACHE}
QUANTIFY_OPTS+= -always-use-cache-dir=yes -max_threads=40
QUANTIFY_OPTS+= -best-effort -record-system-calls=no
QUANTIFY_PATH= ${PURE_PATH}/quantify${PURE_VERSION}
QUANTIFY_BIN= ${QUANTIFY_PATH}/quantify

ifdef purify
   BIN_LD=${PURIFY_BIN} ${PURIFY_OPTS} ${CC}
   BIN_TYPE=.purify
else
   ifdef quantify
      BIN_LD=${QUANTIFY_BIN} ${QUANTIFY_OPTS} ${CC}
      BIN_TYPE=.quantify
      GLOB_INC= -I${QUANTIFY_PATH} 
   else
      ifdef debug
        BIN_TYPE=.debug
      endif
   endif
endif

ifdef debug
   OBJECT_SUBDIR=DEBUG

   LIB_TYPE=${RW_VERSION}

   CFLAGS= ${CC_OPTS_01} ${COMP_DEB_FLAG} ${CC_OPTS_02}
   CFLAGS+= -DTRACE -D_REENTRANT ${CC_OPTS_03} -DPIN_USE_ANSI_HDRS
   CFLAGS+= -DRWDEBUG=1 -D_PIN_DEBUG -D_DEBUG
   CFLAGS+= -DRW_MULTI_THREAD -DRWSTD_MULTI_THREAD
   CFLAGS+= -DRWTRACE=0 -DRW_USER_TRACE_LEVEL=0
   CFLAGS+= -DRWLIBVERSION='"${LIB_TYPE}"'
   CFLAGS+= -DMODULE_START='${LIB_NAME}ModuleStart'
   CFLAGS+= -DLIBNAME='"${LIB_NAME}"'
   CFLAGS+= -D_RWCONFIG_${RW_VERSION}


   LDFLAGS= ${CC_OPTS_01} ${DEB_FLAG} ${LD_OPTS}

   SHFLAGS= ${CC_OPTS_04} ${DEB_FLAG} ${SH_OPTS}
else
   ifdef quantify
     OBJECT_SUBDIR=QUANTIFY

     LIB_TYPE=${RW_VERSION}.quantify

     CFLAGS= ${CC_OPTS_01} ${COMP_DEB_FLAG} ${CC_OPTS_02}
     CFLAGS+= -D_REENTRANT ${CC_OPTS_03} -DPIN_USE_ANSI_HDRS
     CFLAGS+= -DRW_MULTI_THREAD -DRWSTD_MULTI_THREAD
     CFLAGS+= -DRWTRACE=0 -DRW_USER_TRACE_LEVEL=0
     CFLAGS+= -DRWLIBVERSION='"${LIB_TYPE}"'
     CFLAGS+= -DMODULE_START='${LIB_NAME}ModuleStart'
     CFLAGS+= -DLIBNAME='"${LIB_NAME}"'
     CFLAGS+= -D_RWCONFIG_${RW_VERSION}
     CFLAGS+= -DQUANTIFY

     CFLAGS+= -DIT_HAS_NEW_IOSTREAM=1 -DIT_HAS_NAMESPACE_STD=1

     LDFLAGS= ${CC_OPTS_01} ${DEB_FLAG} ${LD_OPTS} 

     SHFLAGS= ${CC_OPTS_04} ${DEB_FLAG} ${SH_OPTS}
   else
     OBJECT_SUBDIR=OPTIMIZE

     LIB_TYPE=${RW_VERSION}

     CFLAGS= ${CC_OPTS_01} ${CC_OPTS_02} ${COMP_OPT_FLAG}
     CFLAGS+= -D_REENTRANT ${CC_OPTS_03}
     CFLAGS+= -DRW_MULTI_THREAD -DRWSTD_MULTI_THREAD
     CFLAGS+= -DRWTRACE=0 -DRW_USER_TRACE_LEVEL=0
     CFLAGS+= -DRWLIBVERSION='"${LIB_TYPE}"'
     CFLAGS+= -DMODULE_START='${LIB_NAME}ModuleStart'
     CFLAGS+= -DLIBNAME='"${LIB_NAME}"'
     CFLAGS+= -D_RWCONFIG_${RW_VERSION}


     LDFLAGS= ${CC_OPTS_01} ${LD_OPTS} ${OPT_FLAG}

     SHFLAGS= ${CC_OPTS_04} ${SH_OPTS} ${OPT_FLAG}
   endif
endif

ifdef purify
    CFLAGS+= -DPURIFY
    GLOB_INC= -I${PURE_PATH}/purify${PURE_VERSION}
endif

ifndef IDLCOMP
   IDLCOMP=${CORBA_HOME}/bin/idl
endif

ECHO=echo

D2U=d2u

RM=rm -rf

CP=cp

MV=mv

CHMOD=chmod

TOUCH=touch

