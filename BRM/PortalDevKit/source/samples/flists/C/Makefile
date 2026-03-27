######################################################################
#
# Copyright (c) 2000, 2009, Oracle and/or its affiliates. All rights reserved. 
#
#      This material is the exclusive property and trade secret of
#      Oracle Corporation. No part may be reproduced,
#      disclosed, stored in a retrieval system, or otherwise
#      transmitted in any form or by any means, electronic,
#      mechanical, photocopying, optical, magnetic, chemical,
#      biological, or otherwise, without prior written permission
#      of Oracle Corporation.
#
######################################################################

include ../../env.unix
include ../../Make.include.unix

PINDIR=../../../..
INCDIR=$(PINDIR)/include
LIBDIR=$(PINDIR)/lib

APPS= simple_flist flists_with_arrays flists_with_substructs

all: $(APPS)

$(APPS): simple_flist.c flists_with_arrays.c flists_with_substructs.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $@.c $(LDLIBS)

clean:
	rm -f $(OBJECTS) $(APPS) core

