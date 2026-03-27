######################################################################
#
# Copyright (c) 2000, 2009, Oracle and/or its affiliates. All rights reserved. 
#
#       This material is the confidential property of Oracle Corporation.
#       or its subsidiaries or licensors and may be used, reproduced, stored
#       or transmitted only in accordance with a valid Oracle license or
#       sublicense agreement.

######################################################################

# This is a directory makefile

# subdirectories we want to build
SUBDIRS = Java C C++


all:
	-@for dir in $(SUBDIRS); do \
		cd $$dir ;\
		make $@ ;\
		cd .. ;\
	done


clean:
	-@for dir in $(SUBDIRS); do \
		cd $$dir ;\
		make $@ ;\
		cd .. ;\
	done

