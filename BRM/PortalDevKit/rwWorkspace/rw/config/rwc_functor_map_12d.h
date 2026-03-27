// Protect against multiple inclusions and mismatched configurations
#if defined _RW_functor_map_CONFIG
#  if _RW_functor_map_CONFIG != 0x380ed733
#    error  Error, two different configurations given for functor-map-library
#  endif
#else
// Define configuration id
#define _RW_functor_map_CONFIG 0x380ed733

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_trace.h>
#include <rw/config/rwconfig_threxcept.h>
#include <rw/config/rwconfig_sync.h>
#include <rw/config/rwconfig_pointer.h>
#include <rw/config/rwconfig_functor.h>

#define RW_FUNCTOR_MAP_VERSION 0x16010000
/* #define RW_FUNCTOR_MAP_DEBUG 0 */
#define RW_FUNCTOR_MAP_DLL 1


inline const char * rw_functor_map_library_id() { return "rw_functor_map_Edition_2016_1__12d__2017_4_20_09_43_55_053"; }
static const char *  rw_functor_map_Edition_2016_1__12d__2017_4_20_09_43_55_053 = rw_functor_map_library_id();

// macros defined by Essential Tools Module

// macros defined by Execution Tracing Library

// macros defined by Thread-compatible Exceptions Library

// macros defined by Synchronization Library

// macros defined by Smart Pointer Library

// macros defined by Functor Library

#endif
