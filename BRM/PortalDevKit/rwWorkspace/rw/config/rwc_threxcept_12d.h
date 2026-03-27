// Protect against multiple inclusions and mismatched configurations
#if defined _RW_threxcept_CONFIG
#  if _RW_threxcept_CONFIG != 0x54740b77
#    error  Error, two different configurations given for threxcept-library
#  endif
#else
// Define configuration id
#define _RW_threxcept_CONFIG 0x54740b77

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_trace.h>

#define RW_THREXCEPT_VERSION 0x16010000
/* #define RW_THREXCEPT_DEBUG 0 */
#define RW_THREXCEPT_DLL 1
#define RW_THR_HAS_POSIX_TIME 1


inline const char * rw_threxcept_library_id() { return "rw_threxcept_Edition_2016_1__12d__2017_4_20_09_43_55_053"; }
static const char *  rw_threxcept_Edition_2016_1__12d__2017_4_20_09_43_55_053 = rw_threxcept_library_id();

// macros defined by Essential Tools Module

// macros defined by Execution Tracing Library
// /* #define RW_THR_THREAD_API_WIN32 0 */
// /* #define RW_THR_THREAD_API_SOLARIS 0 */
// #define RW_THR_THREAD_API_POSIX 1

#endif
