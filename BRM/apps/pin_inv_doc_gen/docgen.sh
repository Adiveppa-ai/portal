#!/bin/sh
#
# Copyright (c) 2010, 2023, Oracle and/or its affiliates.
#
# This material is the confidential property of Oracle Corporation or its
# licensors and may be used, reproduced, stored or transmitted only in
# accordance with a valid Oracle license or sublicense agreement.
#


DOC_GEN_HOME=__DOC_GEN_HOME__
export DOC_GEN_HOME

DG_LIB="$DOC_GEN_HOME/pin_inv_doc_gen.jar:$DOC_GEN_HOME/lib/xmlp/bip_jaxws_client.jar"
PCM_LIB="$PIN_HOME/jars/pcm.jar:$PIN_HOME/jars/pcmext.jar:$PIN_HOME/jars/oraclepki.jar:$PIN_HOME/jars/osdt_cert.jar:$PIN_HOME/jars/osdt_core.jar"
WL_LIB="$ORACLE_HOME/jdbc/lib/ojdbc8.jar:$DOC_GEN_HOME/lib/wls/com.oracle.webservices.wls.jaxws-wlswss-client.jar"
COMMONS_LOGGING_JAR_FILE="commons-logging-1.2-0a2317f.jar"

XMLP_LIB="$DOC_GEN_HOME/lib/xmlp/xdo-core.jar"
XMLP_LIB="$XMLP_LIB:$PIN_HOME/jars/$COMMONS_LOGGING_JAR_FILE"
XMLP_LIB="$XMLP_LIB:$DOC_GEN_HOME/lib/xmlp/jaxrpc.jar"
XMLP_LIB="$XMLP_LIB:$DOC_GEN_HOME/lib/xmlp/orawsdl_12.2.1.2.0.jar"
XMLP_LIB="$XMLP_LIB:$DOC_GEN_HOME/lib/xmlp/mail.jar"
XMLP_LIB="$XMLP_LIB:$DOC_GEN_HOME/lib/xmlp/xmlef.jar"
#XMLP_LIB="$XMLP_LIB:$DOC_GEN_HOME/lib/xmlp/xmlparserv2.jar"
XMLP_LIB="$XMLP_LIB:$DOC_GEN_HOME/lib/xmlp/xdo-server.jar"
UCP_LIB="$ORACLE_HOME/ucp/lib/ucp.jar"

CLASSPATH="$WL_LIB:$XMLP_LIB:.:$PCM_LIB:$DG_LIB:$UCP_LIB"
export CLASSPATH

# echo CLASSPATH = $CLASSPATH

echo
echo "Executing " $JAVA_HOME/bin/java invoicedocgen.pin_inv_doc_gen -status pending "$@"
$JAVA_HOME/bin/java invoicedocgen.pin_inv_doc_gen -status pending "$@" 

