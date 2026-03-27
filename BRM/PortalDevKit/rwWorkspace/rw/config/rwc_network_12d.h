// Protect against multiple inclusions and mismatched configurations
#if defined _RW_network_CONFIG
#  if _RW_network_CONFIG != 0xad574719
#    error  Error, two different configurations given for network-library
#  endif
#else
// Define configuration id
#define _RW_network_CONFIG 0xad574719

// Characterization Macros
#include <rw/config/rwconfig_tls.h>

#define RW_NETWORK_VERSION 0x16010000
/* #define RW_NETWORK_DEBUG 0 */
#define RW_NETWORK_DLL 1
/* #define RWNET_WINSOCK 0 */
#define RW_SOCKLEN_TYPE socklen_t
/* #define RW_MUST_CALL_BIND_EARLY 0 */
/* #define RW_SOCKETS_ARE_ALWAYS_INET 0 */
#define RW_GETXBYY_REENTRANT_API 3
#define RW_INADDR_TYPE in_addr_t
/* #define RWNET_NO_SHUTDOWN 0 */
/* #define RWNET_NO_MSGHDR 0 */
#define RW_NO_SYS_FILIO_H 1
/* #define RW_DISABLE_IPV4_MAPPED_ADDRESSES 0 */


inline const char * rw_network_library_id() { return "rw_network_Edition_2016_1__12d__2017_4_20_09_43_55_053"; }
static const char *  rw_network_Edition_2016_1__12d__2017_4_20_09_43_55_053 = rw_network_library_id();

// macros defined by Essential Tools Module

#endif
