//This file has all the macros defined over the RoguwWave code.
//Since from 9.1 we have been using these macros in pur code.
//But since they are no more available in RogueWave11.1,
//we have defined them here without distrubing the source code.
 
#ifndef _RWRTTI_H_INCLUDED
#define _RWRTTI_H_INCLUDED
// Macro for casting, using either the "old" method
// or the new C++ cast system
#ifndef _RWSTD_NO_STATIC_CAST
#  define _RWSTD_STATIC_CAST(T, x)      static_cast< T >(x)
#  define _RWSTD_REINTERPRET_CAST(T, x) reinterpret_cast< T >(x)
#  define _RWSTD_CONST_CAST(T, x)       const_cast< T >(x)
#else   // if defined (_RWSTD_NO_STATIC_CAST)
#  define _RWSTD_STATIC_CAST(T, x)      ((T)x)
#  define _RWSTD_REINTERPRET_CAST(T, x) ((T)x)
#  define _RWSTD_CONST_CAST(T, x)       ((T)x)
#endif   // _RWSTD_NO_STATIC_CAST

#ifndef _RWSTD_NO_DYNAMIC_CAST
#  define _RWSTD_DYNAMIC_CAST(T, x)      dynamic_cast< T >(x)
#else   // if defined (_RWSTD_NO_DYNAMIC_CAST)
#  define _RWSTD_DYNAMIC_CAST(T, x)      ((T)x)
#endif   // _RWSTD_NO_DYNAMIC_CAST
#endif
