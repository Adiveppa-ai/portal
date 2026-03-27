// Protect against multiple inclusions and mismatched configurations
#if defined _RW_pointer_CONFIG
#  if _RW_pointer_CONFIG != 0xbe7e6630
#    error  Error, two different configurations given for pointer-library
#  endif
#else
// Define configuration id
#define _RW_pointer_CONFIG 0xbe7e6630

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_trace.h>
#include <rw/config/rwconfig_threxcept.h>
#include <rw/config/rwconfig_sync.h>

#define RW_POINTER_VERSION 0x16010000
#define RW_POINTER_DEBUG 1
#define RW_POINTER_DLL 1


inline const char * rw_pointer_library_id() { return "rw_pointer_Edition_2016_1__15d__2017_4_20_10_08_23_559"; }
static const char *  rw_pointer_Edition_2016_1__15d__2017_4_20_10_08_23_559 = rw_pointer_library_id();

// macros defined by Essential Tools Module

// macros defined by Execution Tracing Library

// macros defined by Thread-compatible Exceptions Library

// macros defined by Synchronization Library

#endif
