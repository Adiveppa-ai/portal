##################################################################
# $Id: Makefile,v 1.1 2001/09/05 12:39:54 mliebmann Exp $
#
# Makefile for DAT_ExchangeRate libDir
##################################################################

include ${SETTINGS_PATH}/all.inc

##################################################################
##################################################################
# definitions for the shared library
##################################################################

LIB_NAME=DAT_Sample


LIB_OBJS= \
 ${OBJECT_SUBDIR}/SamplePlugIn.o

LIB_INCS= -I..  

cleanlib:

##################################################################
##################################################################
# definitions for the binary
##################################################################

BIN_NAME=

BIN_OBJS= \
 ${OBJECT_SUBDIR}/${BIN_NAME}.o

BIN_INCS=

FRAME_LIB_NAMES= \
 BAS \
 PBC \
 STR_Base \
 PLG_Base \
 FSM \
 PLG \
 EDR \
 LOG_Base \
 STR \
 PLI \
 DBC \
 SCR \
 TAM_Base \
 TAM

GLOB_LIB_NAMES= \
 ${LIB_NAME}

BIN_LIB_NAMES= \
 ${GLOB_LIB_NAMES} \
 ${FRAME_LIB_NAMES}

BIN_LIBS= \
 ${SYSTEM_LIBS} \
 ${RW_THR_LIB} \
 ${RW_DBT_LIB} \
 ${RW_MNY_LIB} \
 ${RW_TLS_LIB} \
 ${RW_STD_LIB} \
 ${ORACLE_LIBS} \
 ${BIN_LIB_NAMES:%=-l%${LIB_TYPE}}

BIN_LIB_DEPS= \
 ${GLOB_LIB_NAMES:%=${GLOB_LIB}/${LIB_PREFIX}%${LIB_TYPE}${LIB_SUFFIX}} \
 ${FRAME_LIB_NAMES:%=${FRAMEWORK_LIB}/${LIB_PREFIX}%${LIB_TYPE}${LIB_SUFFIX}}

cleanbin:

##################################################################
##################################################################
# DO NOT EDIT AFTER THIS LINE
##################################################################

TARGET_BIN= ${GLOB_BIN}/${BIN_NAME}${BIN_TYPE}

ifneq (0,${MAKELEVEL})
  ifeq "$(findstring clean,${MAKECMDGOALS})" ""
    OBJECTS= ${LIB_OBJS}
    TARGET_BIN=
  endif
endif

OBJECTS= ${LIB_OBJS}

TARGET_LIB= ${GLOB_LIB}/${LIB_PREFIX}${LIB_NAME}${LIB_SUFFIX}

LOCAL_INCLUDE= ${LIB_INCS} ${BIN_INCS} ${GLOB_INC} ${RW_INC} ${RW_STD_INC} 

CFLAGS+= ${LOCAL_INCLUDE}
C++Flags += -DMODULE_START="DAT_SampleModuleStart"

LDFLAGS+= ${RW_LIBS_PATH} ${GLOB_LIB_PATH}
 
all: ${TARGET_LIB}

include ${SETTINGS_PATH}/rules.inc

${TARGET_LIB}: ${LIB_OBJS}
	cd ${OBJECT_SUBDIR}; \
	${LIB_LD} ${SHFLAGS} -o $@ ${notdir ${LIB_OBJS}} ${RW_LIBS} ${SYSTEM_LIBS}

${TARGET_BIN}: ${BIN_OBJS} ${BIN_LIB_DEPS}
	cd ${OBJECT_SUBDIR}; \
	${BIN_LD} ${LDFLAGS} -o $@ ${notdir ${BIN_OBJS}} ${BIN_LIBS}
##################################################################

