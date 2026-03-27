#
# @(#)$Id: Make.user /cgbubrm_7.5.0.portalbase/1 2015/11/27 04:05:21 nishahan Exp $
#
# Copyright (c) 2000, 2023, Oracle and/or its affiliates.
#
#      This material is the confidential property of Oracle Corporation or
#      its licensors and may be used, reproduced, stored or transmitted only
#      in accordance with a valid Oracle license or sublicense agreement.
#

OS=linux
PIN_VERSION=15.0

##########

PINDIR=../../../..
INCDIR=$(PINDIR)/include
LIBDIR=$(PINDIR)/lib

###########

CFLAGS_linux= -fPIC
CFLAGS= $(CFLAGS_$(OS))

CPPFLAGS = -I$(INCDIR)

LDFLAGS_linux= -shared
LDFLAGS = $(LDFLAGS_$(OS)) -L$(LIBDIR) -lcmpin

SL_EXT_linux= so
SL_EXT= $(SL_EXT_$(OS))

OS_LIBS_linux= -lm
OS_LIBS= $(OS_LIBS_$(OS))

##########

INCFILES= $(INCDIR)/pin_cust.h $(INCDIR)/pcm.h \
	$(INCDIR)/pin_errs.h $(INCDIR)/pinlog.h \
        $(INCDIR)/cm_fm.h op_define.h

FILES= fm_generic_config.c \
	fm_generic_opcode.c

OBJECTS= fm_generic_config.o \
	fm_generic_opcode.o 

DEP_linux=$(FILES)
DEP=$(DEP_$(OS))
LIBFM=fm_generic.$(SL_EXT)

###########

all: $(LIBFM)

clean:
	rm -f $(OBJECTS) core

clobber: clean
	rm -f $(LIBFM)

lint:
	lint $(CPPFLAGS) $(FILES)

tags: FRC

###########

$(LIBFM): $(OBJECTS) $(INCFILES) Makefile
	$(LD) -o $(LIBFM) $(LDFLAGS) $(OBJECTS) $(OS_LIBS)

$(OBJECTS): $(INCFILES) Makefile $(DEP)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $*.c


FRC:




