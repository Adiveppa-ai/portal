// Protect against multiple inclusions and mismatched configurations
#if defined _RW_pop3_CONFIG
#  if _RW_pop3_CONFIG != 0xa6933f
#    error  Error, two different configurations given for pop3-library
#  endif
#else
// Define configuration id
#define _RW_pop3_CONFIG 0xa6933f

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_network.h>
#include <rw/config/rwconfig_trace.h>
#include <rw/config/rwconfig_threxcept.h>
#include <rw/config/rwconfig_sync.h>
#include <rw/config/rwconfig_pointer.h>
#include <rw/config/rwconfig_functor.h>
#include <rw/config/rwconfig_itc.h>
#include <rw/config/rwconfig_thread.h>
#include <rw/config/rwconfig_internet.h>

#define RW_POP3_VERSION 0x16010000
#define RW_POP3_DEBUG 1
#define RW_POP3_DLL 1


inline const char * rw_pop3_library_id() { return "rw_pop3_Edition_2016_1__15d__2017_4_20_10_08_23_559"; }
static const char *  rw_pop3_Edition_2016_1__15d__2017_4_20_10_08_23_559 = rw_pop3_library_id();

// macros defined by Essential Tools Module

// macros defined by Networking Library

// macros defined by Execution Tracing Library

// macros defined by Thread-compatible Exceptions Library

// macros defined by Synchronization Library

// macros defined by Smart Pointer Library

// macros defined by Functor Library

// macros defined by Interthread Communication Library

// macros defined by Threading Library

// macros defined by Internet Basics Library

#endif
