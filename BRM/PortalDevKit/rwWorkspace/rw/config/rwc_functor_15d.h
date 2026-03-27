// Protect against multiple inclusions and mismatched configurations
#if defined _RW_functor_CONFIG
#  if _RW_functor_CONFIG != 0x3b1cf5bb
#    error  Error, two different configurations given for functor-library
#  endif
#else
// Define configuration id
#define _RW_functor_CONFIG 0x3b1cf5bb

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_trace.h>
#include <rw/config/rwconfig_threxcept.h>
#include <rw/config/rwconfig_sync.h>
#include <rw/config/rwconfig_pointer.h>

#define RW_FUNCTOR_VERSION 0x16010000
#define RW_FUNCTOR_DEBUG 1
#define RW_FUNCTOR_DLL 1


inline const char * rw_functor_library_id() { return "rw_functor_Edition_2016_1__15d__2017_4_20_10_08_23_559"; }
static const char *  rw_functor_Edition_2016_1__15d__2017_4_20_10_08_23_559 = rw_functor_library_id();

// macros defined by Essential Tools Module

// macros defined by Execution Tracing Library

// macros defined by Thread-compatible Exceptions Library

// macros defined by Synchronization Library

// macros defined by Smart Pointer Library

#endif
