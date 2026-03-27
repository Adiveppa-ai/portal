// Protect against multiple inclusions and mismatched configurations
#if defined _RW_pointer_CONFIG
#  if _RW_pointer_CONFIG != 0xd6521071
#    error  Error, two different configurations given for pointer-library
#  endif
#else
// Define configuration id
#define _RW_pointer_CONFIG 0xd6521071

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_trace.h>
#include <rw/config/rwconfig_threxcept.h>
#include <rw/config/rwconfig_sync.h>

#define RW_POINTER_VERSION 0x16010000
/* #define RW_POINTER_DEBUG 0 */
#define RW_POINTER_DLL 1


inline const char * rw_pointer_library_id() { return "rw_pointer_Edition_2016_1__12d__2017_4_20_09_43_55_053"; }
static const char *  rw_pointer_Edition_2016_1__12d__2017_4_20_09_43_55_053 = rw_pointer_library_id();

// macros defined by Essential Tools Module

// macros defined by Execution Tracing Library

// macros defined by Thread-compatible Exceptions Library

// macros defined by Synchronization Library

#endif
