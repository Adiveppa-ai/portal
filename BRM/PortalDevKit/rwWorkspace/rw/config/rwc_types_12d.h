// Protect against multiple inclusions and mismatched configurations
#if defined _RW_types_CONFIG
#  if _RW_types_CONFIG != 0x1b4175ad
#    error  Error, two different configurations given for types-library
#  endif
#else
// Define configuration id
#define _RW_types_CONFIG 0x1b4175ad

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_trace.h>
#include <rw/config/rwconfig_threxcept.h>
#include <rw/config/rwconfig_sync.h>
#include <rw/config/rwconfig_pointer.h>

#define RW_TYPES_VERSION 0x16010000
/* #define RW_TYPES_DEBUG 0 */
#define RW_TYPES_DLL 1


inline const char * rw_types_library_id() { return "rw_types_Edition_2016_1__12d__2017_4_20_09_43_55_053"; }
static const char *  rw_types_Edition_2016_1__12d__2017_4_20_09_43_55_053 = rw_types_library_id();
#define _REENTRANT 1

// macros defined by Essential Tools Module

// macros defined by Execution Tracing Library

// macros defined by Thread-compatible Exceptions Library

// macros defined by Synchronization Library

// macros defined by Smart Pointer Library

#endif
