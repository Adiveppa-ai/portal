// Protect against multiple inclusions and mismatched configurations
#if defined _RW_sync_CONFIG
#  if _RW_sync_CONFIG != 0xc8bffe2b
#    error  Error, two different configurations given for sync-library
#  endif
#else
// Define configuration id
#define _RW_sync_CONFIG 0xc8bffe2b

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_trace.h>
#include <rw/config/rwconfig_threxcept.h>

#define RW_SYNC_VERSION 0x16010000
#define RW_SYNC_DEBUG 1
#define RW_SYNC_DLL 1
/* #define RW_SYNC_MUTEX_USES_CRITICAL_SECTION 0 */
/* #define RW_THR_HAS_TIMED_MUTEX_ACQUIRE 0 */
/* #define RW_SYNC_NO_PTHREAD_RWLOCK 0 */


inline const char * rw_sync_library_id() { return "rw_sync_Edition_2016_1__15d__2017_4_20_10_08_23_559"; }
static const char *  rw_sync_Edition_2016_1__15d__2017_4_20_10_08_23_559 = rw_sync_library_id();

// macros defined by Essential Tools Module

// macros defined by Execution Tracing Library
// /* #define RW_THR_THREAD_API_WIN32 0 */
// /* #define RW_THR_THREAD_API_SOLARIS 0 */
// #define RW_THR_THREAD_API_POSIX 1
// /* #define RW_THR_THREAD_API_POSIX_AIX 0 */
// /* #define RW_THR_THREAD_API_POSIX_HPUX 0 */
// /* #define RW_THR_THREAD_API_POSIX_SUNOS 0 */
// #define RW_THR_THREAD_API_POSIX_LINUX 1

// macros defined by Thread-compatible Exceptions Library
// #define RW_THR_HAS_POSIX_TIME 1

#endif
