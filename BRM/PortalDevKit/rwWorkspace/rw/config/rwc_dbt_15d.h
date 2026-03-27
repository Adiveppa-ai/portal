// Protect against multiple inclusions and mismatched configurations
#if defined _RW_dbt_CONFIG
#  if _RW_dbt_CONFIG != 0xb652c8be
#    error  Error, two different configurations given for dbcore-library
#  endif
#else
// Define configuration id
#define _RW_dbt_CONFIG 0xb652c8be

// Characterization Macros
#include <rw/config/rwconfig_tls.h>

#define RW_DBCORE_VERSION 0x16010000
/* #define RWDB_RESTRICT_DEFINED 0 */
#define RWSTDLIBTYPE 2


inline const char * rw_dbt_library_id() { return "rw_dbt_Edition_2016_1__15d__2017_4_20_10_08_23_559"; }
static const char *  rw_dbt_Edition_2016_1__15d__2017_4_20_10_08_23_559 = rw_dbt_library_id();

// macros defined by Essential Tools Module

#endif
