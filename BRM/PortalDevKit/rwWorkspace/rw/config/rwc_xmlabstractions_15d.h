// Protect against multiple inclusions and mismatched configurations
#if defined _RW_xmlabstractions_CONFIG
#  if _RW_xmlabstractions_CONFIG != 0x3eda5fa0
#    error  Error, two different configurations given for xmlabstractions-headers
#  endif
#else
// Define configuration id
#define _RW_xmlabstractions_CONFIG 0x3eda5fa0

// Characterization Macros

#define RW_XMLABSTRACTIONS_VERSION 0x16010000
#define RW_XMLABSTRACTIONS_DEBUG 1
#define RW_XMLABSTRACTIONS_DLL 1
/* #define RW_XMLABSTRACTIONS_HAS_I18N 0 */

#endif
