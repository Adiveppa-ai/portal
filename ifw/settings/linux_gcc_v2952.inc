##################################################################
# $Id: linux_gcc_v2952.inc,v 1.6 2001/09/04 09:28:14 bt Exp $
#
# settings for gcc-2.95.2 under linux
##################################################################

##################################################################
# compiler flags for gcc (gcc-2.95.2)

ifdef COMP_EXE
  CC=${COMP_EXE}
else
  CC=gcc
endif

RWDB_CCOPTS=

CPPDEPOPTS= -M -DINC_TEMPL_DEFS=1 ${OS_COMP_DEFS}

CC_OPTS_01= -ftemplate-depth-27
CC_OPTS_02= -DINC_TEMPL_DEFS=1 ${OS_COMP_DEFS}
CC_OPTS_03= -fPIC --pedantic -Wall -W -Wno-long-long

LD_OPTS=

SH_OPTS= -shared

COMP_DEB_FLAG= -g
DEB_FLAG= ${COMP_DEB_FLAG}

COMP_OPT_FLAG= -O1
OPT_FLAG= ${COMP_OPT_FLAG}

##################################################################
# library settings

LIB_PREFIX=lib
LIB_SUFFIX=.so

SYSTEM_LIBS=-lpthread -lnsl -ldl -lm -lnsl

ORACLE_LIBS=

SH_LIBS=

##################################################################
# compiler and linker settings

CPP=${CC}
BIN_LD=${CC}
LIB_LD=${CC}

