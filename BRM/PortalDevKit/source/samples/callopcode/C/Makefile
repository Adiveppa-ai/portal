#######################################################################
#
# Copyright (c) 1999, 2009, Oracle and/or its affiliates. All rights reserved. 
# 
#	This material is the exclusive property and trade secret of
#	Oracle Corporation. No part may be reproduced,
#	disclosed, stored in a retrieval system, or otherwise
#	transmitted in any form or by any means, electronic,
#	mechanical, photocopying, optical, magnetic, chemical,
#	biological, or otherwise, without prior written permission
#	of Oracle Corporation.
#
#######################################################################

include ../../env.unix
include ../../Make.include.unix

PINDIR=../../../..
INCDIR=$(PINDIR)/include
LIBDIR=$(PINDIR)/lib

APPS= test_loopback

all: $(APPS)

$(APPS): test_loopback.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $@.c $(LDLIBS)

clean:
	rm -f $(OBJECTS) $(APPS) core

