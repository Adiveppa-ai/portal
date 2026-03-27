// Protect against multiple inclusions and mismatched configurations
#if defined _RW_xmlstreams_CONFIG
#  if _RW_xmlstreams_CONFIG != 0x308071b2
#    error  Error, two different configurations given for xmlstreams-source
#  endif
#else
// Define configuration id
#define _RW_xmlstreams_CONFIG 0x308071b2

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_xmlabstractions.h>

#define RW_XMLSTREAMS_VERSION 0x16010000
/* #define RW_XMLSTREAMS_DEBUG 0 */
#define RW_XMLSTREAMS_DLL 1


inline const char * rw_xmlstreams_library_id() { return "rw_xmlstreams_Edition_2016_1__12d__2017_4_20_09_43_55_053"; }
static const char *  rw_xmlstreams_Edition_2016_1__12d__2017_4_20_09_43_55_053 = rw_xmlstreams_library_id();
#define _REENTRANT 1

// macros defined by Essential Tools Module

// macros defined by XML Abstractions Package

#endif
