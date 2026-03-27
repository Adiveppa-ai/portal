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

#################################################################
# $Id: config.inc,v 1.5 2003/03/04 08:11:41 bt Exp $
#
# settings for MAK configurations
##################################################################

##################################################################
# macros for operating system and compiler

OS_COMP_DEFS= -DOS_VER=${OS_VER} -DCPP_VER=${COMP_VER}

##################################################################
# Rogue Wave settings

RW_PATH=${CFG_RW_PATH}

ifdef CFG_RW_NO_SUBDIR
  RW_NO_SUBDIR=${CFG_RW_NO_SUBDIR}
else
  RW_NO_SUBDIR=false
endif

ifdef CFG_RW_NATIVE_STDLIB
  RW_NATIVE_STDLIB=${CFG_RW_NATIVE_STDLIB}
else
  RW_NATIVE_STDLIB=false
endif

ifdef CFG_RW_COMMON_SUBDIR
  RW_COMMON_SUBDIR=${CFG_RW_COMMON_SUBDIR}
else
  RW_COMMON_SUBDIR=false
endif

ifdef debug
    RW_VERSION=15d
else
    RW_VERSION=12d
endif


HOARD_LIB=

##################################################################
# java settings

JDK_PATH=${CFG_JDK_PATH}

##################################################################

CORBA_HOME=${CFG_CORBA_HOME}

CORBA_CXX=${CFG_CORBA_CXX}

CORBA_CXXLIB=${CFG_CORBA_CXXLIB}

CORBA_SHLIB=${CFG_CORBA_SHLIB}

CORBA_DEFLIB=${CFG_CORBA_DEFLIB}

##################################################################
# Oracle settings

ORA_LIB_PATH=${CFG_ORACLE_LIB}

##################################################################
# IBM DB2 settings

DB2_LIB_PATH=${CFG_DB2LIB}

##################################################################
# Infranet SDK settings

PIN_INCDIR=${CFG_PIN_INCDIR}

PIN_LIBDIR=${CFG_PIN_LIBDIR}

##################################################################
# purify and quantify settings

PURE_PATH=${CFG_PURE_PATH}

PURE_VERSION=${CFG_PURE_VERSION}

##################################################################
# InstallAnywhere settings

INST_ANYWHERE_BIN=${CFG_INST_ANYWHERE_BIN}

