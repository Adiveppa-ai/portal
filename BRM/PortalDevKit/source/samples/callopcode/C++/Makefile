############################################################################
#
# Copyright (c) 2000, 2017, Oracle and/or its affiliates. All rights reserved.
#       This material is the confidential property of Oracle Corporation. 
#       or its subsidiaries or licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or 
#       sublicense agreement.
#
#       @(#) %full_filespec: Makefile~2:makefile:507 %
############################################################################

include ../../env.unix
include ../../Make.include.unix

PINDIR=../../../..
INCDIR=$(PINDIR)/include
LIBDIR=$(PINDIR)/lib

APPS= test_loopback

all: $(APPS)

$(APPS): test_loopback.cpp
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -lstdc++ -o $@ $@.cpp $(CPPLDLIBS)


clean:
	rm -f $(OBJECTS) $(APPS) core

