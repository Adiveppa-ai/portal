// Protect against multiple inclusions and mismatched configurations
#if defined _RW_oci_CONFIG
#  if _RW_oci_CONFIG != 0xf282bc5a
#    error  Error, two different configurations given for oraoci-access-library
#  endif
#else
// Define configuration id
#define _RW_oci_CONFIG 0xf282bc5a

// Characterization Macros
#include <rw/config/rwconfig_tls.h>
#include <rw/config/rwconfig_dbt.h>



inline const char * rw_oci_library_id() { return "rw_oci_Edition_2016_1__12d__2017_4_20_09_43_55_053"; }
static const char *  rw_oci_Edition_2016_1__12d__2017_4_20_09_43_55_053 = rw_oci_library_id();

// macros defined by Essential Tools Module

// macros defined by DB Interface Library

#endif
