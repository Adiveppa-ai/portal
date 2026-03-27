#!/bin/sh

CMD=getProperty.sh

USAGE="Usage: $CMD <VARIABLE_NAME>"

# fail if executed as ". getProperty.sh"
b=`basename "$0" 2>/dev/null`
if [ "$b" != "$CMD" ] ; then
  echo "$USAGE"
  exit 1
fi

# Determine GLCM Home
if [ -z "$GLCM_HOME" ]; then
  # Determine from "/u01/glcm.config/odp.properties"
  if [ -f /u01/glcm.config/odp.properties ]; then
    GLCM_HOME=`grep "glcmOH" /u01/glcm.config/odp.properties|cut -d'=' -f2`
  fi
  #If still not found use default
  if [ -z "$GLCM_HOME" ]; then
    GLCM_HOME=/opt/facs/casrepos/glcm
  fi
fi

# Check if the $GLCM_HOME existing
if [ -d "$GLCM_HOME" ]; then
  PROPERTY_VALUE=`$GLCM_HOME/bin/getProperty.sh "$1"`
  #Fallback to oui env inside GLCM_HOME in case variable is not set there
  if [[ -z "$PROPERTY_VALUE" ]] || [[ ! -d "$PROPERTY_VALUE" && "$1" = "JAVA_HOME" ]]; then
    PROPERTY_VALUE=`$GLCM_HOME/oui/bin/getProperty.sh "$1"`
  fi
fi
if [[ -z "$PROPERTY_VALUE" ]] || [[ ! -d "$PROPERTY_VALUE" && "$1" = "JAVA_HOME" ]]; then
  SCRIPT_PATH=`dirname "$0"`

  #Parse arguments
  upper=`echo $1|tr '[a-z]' '[A-Z]'`

  if [ -z "$1" -o x"$upper" = "x-HELP" ] ; then
    echo "$USAGE"
    exit 1
  else
    VARIABLE_NAME=$1
  fi

  #Get properties file directory path
  PROPERTIES_FILE="${SCRIPT_PATH}/../.globalEnv.properties"

  PROPERTY_VALUE=`grep "^${VARIABLE_NAME}=" "${PROPERTIES_FILE}" | cut -d = -f 2 | sed s,'\\\\\\\\',/,g | sed s,'\\\\:',:,g`
fi
echo "${PROPERTY_VALUE}"
