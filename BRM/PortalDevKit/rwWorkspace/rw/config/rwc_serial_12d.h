// Protect against multiple inclusions and mismatched configurations
#if defined _RW_serial_CONFIG
#  if _RW_serial_CONFIG != 0xa074ba58
#    error  Error, two different configurations given for serial-library
#  endif
#else
// Define configuration id
#define _RW_serial_CONFIG 0xa074ba58

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_trace.h>
#include <rw/config/rwconfig_threxcept.h>
#include <rw/config/rwconfig_sync.h>
#include <rw/config/rwconfig_pointer.h>
#include <rw/config/rwconfig_types.h>
#include <rw/config/rwconfig_functor.h>
#include <rw/config/rwconfig_factory.h>
#include <rw/config/rwconfig_streams.h>

#define RW_SERIAL_VERSION 0x16010000
/* #define RW_SERIAL_DEBUG 0 */
#define RW_SERIAL_DLL 1


inline const char * rw_serial_library_id() { return "rw_serial_Edition_2016_1__12d__2017_4_20_09_43_55_053"; }
static const char *  rw_serial_Edition_2016_1__12d__2017_4_20_09_43_55_053 = rw_serial_library_id();

// macros defined by Essential Tools Module

// macros defined by Execution Tracing Library

// macros defined by Thread-compatible Exceptions Library

// macros defined by Synchronization Library

// macros defined by Smart Pointer Library

// macros defined by Data Types Library
// #define _REENTRANT 1

// macros defined by Functor Library

// macros defined by Factory Library

// macros defined by Streams Library

#endif
