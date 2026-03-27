// Protect against multiple inclusions and mismatched configurations
#if defined _RW_trace_CONFIG
#  if _RW_trace_CONFIG != 0x3a43296c
#    error  Error, two different configurations given for trace-library
#  endif
#else
// Define configuration id
#define _RW_trace_CONFIG 0x3a43296c

// Characterization Macros
#include <rw/config/rwconfig_tls.h>

#define RW_TRACE_VERSION 0x16010000
#define RW_TRACE_DEBUG 1
#define RW_TRACE_DLL 1
/* #define RW_USER_TRACE_LEVEL 0 */
/* #define RW_THR_THREAD_API_WIN32 0 */
/* #define RW_THR_THREAD_API_SOLARIS 0 */
#define RW_THR_THREAD_API_POSIX 1
/* #define RW_THR_THREAD_API_POSIX_AIX 0 */
/* #define RW_THR_THREAD_API_POSIX_HPUX 0 */
/* #define RW_THR_THREAD_API_POSIX_SUNOS 0 */
#define RW_THR_THREAD_API_POSIX_LINUX 1
#define RW_THR_NO_GETENV_S 1


inline const char * rw_trace_library_id() { return "rw_trace_Edition_2016_1__15d__2017_4_20_10_08_23_559"; }
static const char *  rw_trace_Edition_2016_1__15d__2017_4_20_10_08_23_559 = rw_trace_library_id();

// macros defined by Essential Tools Module

#endif
