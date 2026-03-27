#
# $Id: pkg.inc,v 1.6 2000/07/20 09:22:22 bt Exp $
#
# Defines for packages

PKG_ROOT=${BUILD_ROOT}/pkgs

PKG_TARGET=${PKG_ROOT}/assembled

PKG_TAG_NAME:=$(shell grep -h "Framework Version.*$$\Name:" \
                      ${FRAMEWORK_ROOT}/Framework/BAS/*pp 2>/dev/null | \
                      sed -e 's/^[^\\$$]*\(".*"\).*/\1/' | \
                      sed -e 's/\//\\\//g' | tr -d "$$ \"" | \
                      sed -e 's/Name://' | grep -v "Framework Version")

PKG_DATE:=$(shell date)
PKG_UNAME:=$(shell uname -nsr)
PKG_PSTAMP:="${PKG_UNAME} ${PKG_DATE}"

