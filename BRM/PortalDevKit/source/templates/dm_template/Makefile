#
#
# Copyright (c) 2000, 2024, Oracle and/or its affiliates.
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
LDFLAGS = $(LDFLAGS_$(OS)) -L$(LIBDIR) -ldmpin

SL_EXT_linux= so
SL_EXT= $(SL_EXT_$(OS))

OS_LIBS_linux= -lm
OS_LIBS= $(OS_LIBS_$(OS))

INCFILES= $(INCDIR)/pcm.h $(INCDIR)/pin_errs.h $(INCDIR)/pinlog.h \
          $(INCDIR)/dm_sm.h $(INCDIR)/dm_debug.h 

##########

FILES= dm_generic.c

OBJECTS= dm_generic.o

DM_SAMPLE=dm_generic.$(SL_EXT)

DEP_linux=$(FILES)
DEP=$(DEP_$(OS))
##########

all: $(DM_SAMPLE)

clean:
	rm -f $(OBJECTS) core

clobber: clean
	rm -f $(DM_SAMPLE)

lint:
	$(LINT) $(CPPFLAGS) $(FILES)

tags: FRC

##########

$(DM_SAMPLE): $(OBJECTS) $(INCFILES) Makefile
	$(LD) -o $(DM_SAMPLE) $(LDFLAGS) $(OBJECTS) $(OS_LIBS)

$(OBJECTS): $(INCFILES) Makefile $(DEP)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $*.c 

##########

FRC:
