// Protect against multiple inclusions and mismatched configurations
#if defined _RW_mny_CONFIG
#  if _RW_mny_CONFIG != 0x4525bf6d
#    error  Error, two different configurations given for currency-library
#  endif
#else
// Define configuration id
#define _RW_mny_CONFIG 0x4525bf6d

// Characterization Macros
#include <rw/config/rwconfig_tls.h>

#define RW_CURRENCY_VERSION 0x16010000
#define RWSTDLIBTYPE 2
/* #define RWSTD_NO_NAMESPACE 0 */
#define RW_LARGEST_LDOUBLE 18446744073709551615.0
/* #define RWMNY_NO_LONG_DOUBLE_MATH 0 */
/* #define RW_MNY_NO_RINT 0 */


inline const char * rw_mny_library_id() { return "rw_mny_Edition_2016_1__12d__2017_4_20_09_43_55_053"; }
static const char *  rw_mny_Edition_2016_1__12d__2017_4_20_09_43_55_053 = rw_mny_library_id();

// macros defined by Essential Tools Module
// #define RW_MULTI_THREAD 1
// /* #define RW_NO_NEW_TEMPLATE_SYNTAX 0 */
// #define RW_NO_LIBC_IN_STD 1

#endif
