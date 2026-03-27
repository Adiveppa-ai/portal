// Protect against multiple inclusions and mismatched configurations
#if defined _RW_thread_CONFIG
#  if _RW_thread_CONFIG != 0xdc9aaf64
#    error  Error, two different configurations given for thread-library
#  endif
#else
// Define configuration id
#define _RW_thread_CONFIG 0xdc9aaf64

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_trace.h>
#include <rw/config/rwconfig_threxcept.h>
#include <rw/config/rwconfig_sync.h>
#include <rw/config/rwconfig_pointer.h>
#include <rw/config/rwconfig_functor.h>
#include <rw/config/rwconfig_itc.h>

#define RW_THREAD_VERSION 0x16010000
/* #define RW_THREAD_DEBUG 0 */
#define RW_THREAD_DLL 1
#define RW_THR_PRODUCT_MAJOR_VERSION ""
#define RW_THR_PRODUCT_MINOR_VERSION ""
#define RW_THR_PRODUCT_MAINTENANCE_VERSION ""
#define RW_THR_OS_NAME "Linux"
#define RW_THR_OS_VENDOR "(various)"
#define RW_THR_OS_VERSION 0x02609
#define RW_THR_OS_VERSION_NAME ""
#define RW_THR_COMPILER_NAME "GCC"
#define RW_THR_COMPILER_VENDOR "GNU"
#define RW_THR_COMPILER_VERSION 0x00040800
#define RW_THR_COMPILER_VERSION_NAME "4.8"
#define RW_THR_THREAD_API "LinuxThreads IEEE POSIX 1003.1c Final"
/* #define RW_THR_USER_STACK_TAKES_HIGH_ADDRESS 0 */
/* #define RW_THR_NO_NESTED_CLASS_FRIEND_ACCESS 0 */


inline const char * rw_thread_library_id() { return "rw_thread_Edition_2016_1__12d__2017_4_20_09_43_55_053"; }
static const char *  rw_thread_Edition_2016_1__12d__2017_4_20_09_43_55_053 = rw_thread_library_id();

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

// macros defined by Synchronization Library

// macros defined by Smart Pointer Library

// macros defined by Functor Library

// macros defined by Interthread Communication Library

#endif
