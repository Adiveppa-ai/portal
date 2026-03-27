##################################################################
# $Id: smacc.inc,v 1.4 2000/07/20 16:24:04 bt Exp $
#
# smacc settings
##################################################################

JAVA_PATH=${JDK_PATH}

ifdef AIX
JAVA=$(JAVA_PATH)/jre/sh/java
JAVAC=$(JAVA_PATH)/sh/javac
JAVAJAR=$(JAVA_PATH)/sh/jar
else
JAVA=$(JAVA_PATH)/bin/java
JAVAC=$(JAVA_PATH)/bin/javac
JAVAJAR=$(JAVA_PATH)/bin/jar
endif

JAVA_BIN_PAT=${subst /,\/,/usr/java1.2/bin/java}
JAVA_BIN_REPL=${subst /,\/,${JAVA}}

CLASS_PATH=./classes
DEST_PATH=./install

ORB_PROPERTIES= -Dorg.omg.CORBA.ORBClass=com.visigenic.vbroker.orb.ORB -Dorg.omg.CORBA.ORBSingletonClass=com.visigenic.vbroker.orb.ORB

OPTIONS= -O

