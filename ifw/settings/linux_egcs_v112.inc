##################################################################
# $Id: linux_egcs_v112.inc,v 1.10 2001/09/04 09:28:14 bt Exp $
#
# settings for egcs-1.1.2 under linux
##################################################################

##################################################################
# compiler flags for g++ (egcs-1.1.2)

ifdef COMP_EXE
  CC=${COMP_EXE}
else
  CC=g++
endif

RWDB_CCOPTS=

CPPDEPOPTS= -MM -DINC_TEMPL_DEFS=1 ${OS_COMP_DEFS}

CC_OPTS_01= -ftemplate-depth-27
CC_OPTS_02= -DINC_TEMPL_DEFS=1 ${OS_COMP_DEFS}
CC_OPTS_03= -fPIC

LD_OPTS=

SH_OPTS= -shared

COMP_DEB_FLAG= -g
DEB_FLAG= ${COMP_DEB_FLAG}

COMP_OPT_FLAG= -O2
OPT_FLAG= ${COMP_OPT_FLAG}

##################################################################
# library settings

LIB_PREFIX=lib
LIB_SUFFIX=.so

SYSTEM_LIBS=-lpthread -lnsl -ldl -lm -lnsl -lintl

ORACLE_LIBS=

SH_LIBS=

##################################################################
# compiler and linker settings

CPP=${CC}
BIN_LD=${CC}
LIB_LD=${CC}

