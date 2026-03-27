##################################################################
# $Id: Makefile,v 1.1 2001/01/17 13:21:06 sd Exp $
#
# Makefile for MAK libxBinDir (one library, multiple binaries)
##################################################################

include ${SETTINGS_PATH}/all.inc

##################################################################
##################################################################
# definitions for the shared library
##################################################################

## library name ########################################

LIB_NAME=EXT_Currency

## library objects #####################################

LIB_OBJS= \
 ${OBJECT_SUBDIR}/EXT_SetExchangeRates.o \
 ${OBJECT_SUBDIR}/EXT_CurrencyConvert.o \
 ${OBJECT_SUBDIR}/EXT_Currency.o

## library include paths ###############################

LIB_INCS= -I..

## library clean target ################################

cleanlib:

##################################################################
##################################################################
# definitions for the binary
##################################################################

## own libary names ####################################

FRAME_LIB_NAMES= \
 BAS \
 FSM \
 SCR

GLOB_LIB_NAMES= \
 ${LIB_NAME}

BIN_LIB_NAMES= \
 ${GLOB_LIB_NAMES} \
 ${FRAME_LIB_NAMES}

## own libary dependencies #############################

BIN_LIB_DEPS= \
 ${GLOB_LIB_NAMES:%=${GLOB_LIB}/${LIB_PREFIX}%${LIB_TYPE}${LIB_SUFFIX}} \
 ${FRAME_LIB_NAMES:%=${FRAMEWORK_LIB}/${LIB_PREFIX}%${LIB_TYPE}${LIB_SUFFIX}}

## binary names ########################################

BIN_NAMES= 

## binary dependencies #################################

${GLOB_BIN}/myBin01${BIN_TYPE}: ${BIN_LIB_DEPS} \
                                ${OBJECT_SUBDIR}/myBin01.o \
                                ${OBJECT_SUBDIR}/myBin01Obj02.o

## binary objects ######################################

BIN_OBJS= ${BIN_NAMES:%=${OBJECT_SUBDIR}/%.o} \
          ${OBJECT_SUBDIR}/myBin01Obj02.o \
          ${OBJECT_SUBDIR}/myBin02Obj02.o

## binary include paths ################################

BIN_INCS=

## binary link libraries ###############################

BIN_LIBS= \
 ${SYSTEM_LIBS} \
 ${RW_THR_LIB} \
 ${RW_MNY_LIB} \
 ${RW_TLS_LIB} \
 ${RW_STD_LIB} \
 ${BIN_LIB_NAMES:%=-l%${LIB_TYPE}}

## binary targets ######################################

TARGET_BINS= ${BIN_NAMES:%=${GLOB_BIN}/%${BIN_TYPE}}

## binary clean target #################################

cleanbin:
	@for i in ${TARGET_BINS} targetDummy ; do \
		if [ -f "$${i}" -a "$${i}" != "targetDummy" ] ; then \
			${ECHO} "${RM} $${i}" ; ${RM} $${i} ; \
		fi ; \
	done

##################################################################
##################################################################
# DO NOT EDIT AFTER THIS LINE
##################################################################

TARGET_BIN=

OBJECTS= ${BIN_OBJS} ${LIB_OBJS}

ifneq (0,${MAKELEVEL})
  ifeq "$(findstring clean,${MAKECMDGOALS})" ""
    OBJECTS= ${LIB_OBJS}
    TARGET_BINS=
  endif
endif

TARGET_LIB= ${GLOB_LIB}/${LIB_PREFIX}${LIB_NAME}${LIB_TYPE}${LIB_SUFFIX}

LOCAL_INCLUDE= ${LIB_INCS} ${BIN_INCS} ${GLOB_INC} ${RW_INC} ${RW_STD_INC}

CFLAGS+= ${LOCAL_INCLUDE}

LDFLAGS+= ${RW_LIBS_PATH} ${GLOB_LIB_PATH}
 
all: ${TARGET_LIB} ${TARGET_BINS}

include ${SETTINGS_PATH}/rules.inc

${TARGET_LIB}: ${LIB_OBJS}
	cd ${OBJECT_SUBDIR}; \
	${LIB_LD} ${SHFLAGS} -o $@ ${notdir ${LIB_OBJS}}

${TARGET_BINS}:
	cd ${OBJECT_SUBDIR}; \
	${BIN_LD} ${LDFLAGS} -o $@ ${filter %.o,${notdir $^}} ${BIN_LIBS}

##################################################################

