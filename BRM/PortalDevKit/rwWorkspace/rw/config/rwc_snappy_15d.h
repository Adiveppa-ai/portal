// Protect against multiple inclusions and mismatched configurations
#if defined _RW_snappy_CONFIG
#  if _RW_snappy_CONFIG != 0xb1116e1c
#    error  Error, two different configurations given for snappy-library
#  endif
#else
// Define configuration id
#define _RW_snappy_CONFIG 0xb1116e1c

// Characterization Macros
#include <rw/config/rwconfig_tls.h>

#define RW_SNAPPY_VERSION 0x16010000
#define RW_SNAPPY_DEBUG 1
#define RW_SNAPPY_DLL 1


inline const char * rw_snappy_library_id() { return "rw_snappy_Edition_2016_1__15d__2017_4_20_10_08_23_559"; }
static const char *  rw_snappy_Edition_2016_1__15d__2017_4_20_10_08_23_559 = rw_snappy_library_id();

// macros defined by Essential Tools Module

#endif
