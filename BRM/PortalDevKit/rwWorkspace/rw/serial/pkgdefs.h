#ifndef rw_serial_pkgdefs_h_
#define rw_serial_pkgdefs_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/pkgdefs.h#1 $
 *
 * Copyright (c) 1996-2016 Rogue Wave Software, Inc.  All Rights Reserved.
 * 
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software, Inc.
 * pursuant to a written license agreement and may be used, copied, transmitted,
 * and stored only in accordance with the terms of such license agreement and
 * with the inclusion of the above copyright notice.  This computer software or
 * any other copies thereof may not be provided or otherwise made available to
 * any other person.
 * 
 * U.S. Government Restricted Rights.  This computer software: (a) was
 * developed at private expense and is in all respects the proprietary
 * information of Rogue Wave Software, Inc.; (b) was not developed with
 * government funds; (c) is a trade secret of Rogue Wave Software, Inc. for all
 * purposes of the Freedom of Information Act; and (d) is a commercial item and
 * thus, pursuant to Section 12.212 of the Federal Acquisition Regulations (FAR)
 * and DFAR Supplement Section 227.7202, Government's use, duplication or
 * disclosure of the computer software is subject to the restrictions set forth
 * by Rogue Wave Software, Inc.
 *
 ********************************************************************/

#include <rw/config/rwconfig_serial.h>

/*****************************************************************************

 The following macros must be defined in order to configure a package:

  RW_SERIAL_BUILD

  Specifies that the package source is currently being built for inclusion
  in a library.  If this macro is not defined, the package is being used to
  build a client library or application.

  RW_SERIAL_DLL

  Specifies that the package is to be built or used as part of a DLL library.

  RW_SERIAL_DEBUG

  Specifies that package is being built to include debug assertions.

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Map from RCB style macro to package style.
// Indicate that the library is being built instead of used.
//////////////////////////////////////////////////////////////////////////////
#if defined(_RWBUILD_serial)
#  define RW_SERIAL_BUILD
#endif

// Compatibility definitions
#if defined(_WIN32) && defined(RW_SERIAL_DLL)
#  if defined(_RWBUILD_serial)
#    define _RWSERIALBUILDDLL
#  endif // _RWBUILD_serial
#endif // _WIN32 && RW_SERIAL_DLL

#  define RW_SERIAL_SPECIALIZATION_TEMPLATE_HEADER

//////////////////////////////////////////////////////////////////////////////
// Define internal per-package DLL linkage macros
//////////////////////////////////////////////////////////////////////////////

#if defined(RW_SERIAL_DLL)
#  if defined(RW_SERIAL_SOURCE)
#    define RW_SERIAL_GLOBAL     RW_COMPILER_GLOBAL_EXPORT
#    define RW_SERIAL_SYMBOLIC   RW_COMPILER_SYMBOLIC_EXPORT
#  else
#    define RW_SERIAL_GLOBAL     RW_COMPILER_GLOBAL_IMPORT
#    define RW_SERIAL_SYMBOLIC   RW_COMPILER_GLOBAL_IMPORT
#  endif
#else
#  define RW_SERIAL_GLOBAL
#  define RW_SERIAL_SYMBOLIC
#endif

#if (__SUNPRO_CC >= 590) && defined(RW_SERIAL_DLL)
#  if defined(RW_SERIAL_SOURCE)
#    define RW_SERIAL_SUN_GLOBAL     RW_COMPILER_GLOBAL_EXPORT
#    define RW_SERIAL_SUN_SYMBOLIC   RW_COMPILER_SYMBOLIC_EXPORT
#  else
#    define RW_SERIAL_SUN_GLOBAL     RW_COMPILER_GLOBAL_IMPORT
#    define RW_SERIAL_SUN_SYMBOLIC   RW_COMPILER_GLOBAL_IMPORT
#  endif
#else
#  define RW_SERIAL_SUN_GLOBAL
#  define RW_SERIAL_SUN_SYMBOLIC
#endif

////////////////////////////////////////////////////////////////////////////
// Template instantiation inside serial library
////////////////////////////////////////////////////////////////////////////

// For compilers that do not understand "extern template" directive we
// will employ a [reliable] technique: instantiate explicitly the template
// in the library and in the user code *declare* an explicit specialization;
// thus the compiler will not instantiate the template in user code but
// instead will look for the specialization code in the library.
#if     defined(RW_SERIAL_INSTANTIATE_TEMPLATES) \
    && !defined (RW_SERIAL_NO_EXPLICIT_INSTANTIATION)

#  define RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(Class)                 \
          template class RW_SERIAL_GLOBAL RWTStreamingFactory< Class >

#  if defined(_MSC_VER) || defined(__IBMCPP__)
#    define RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(Type1,Type2)   \
            template class RW_SERIAL_GLOBAL                             \
            RWTPseudoMethodRegistryImp< RWTFunctor<void(Type1,Type2)> >
#  else
#    define RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(ign1,ign2)
#  endif

#else

#  if defined(_MSC_VER)
#    pragma warning (disable: 4231)
#  endif // _MSC_VER

#  if  defined(__SUNPRO_CC) || defined(__IBMCPP__) || \
       defined (RW_SERIAL_NO_EXPLICIT_INSTANTIATION)
// Declare a specialization of the class for the specified type, however do
// not provide a definition for any of the members. When the linker
// attempts to resolve these symbols, it will find the instantiations of the
// base template in the library and use those definitions.
#    define RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(Class)              \
template <>                                                             \
class RWTStreamingFactory< Class >                                      \
{                                                                       \
                                                                        \
public:                                                                 \
                                                                        \
    typedef RWSymbol                                 key_type;          \
                                                                        \
    typedef RWTFactory0<Class, RWSymbol>            factory_type;       \
    typedef RWTFactory0<Class, RWSymbol>*           factory_type_ptr;   \
                                                                        \
    typedef factory_type::RWRegistration  Registration;                 \
                                                                        \
    static factory_type_ptr getFactory();                               \
                                                                        \
    void* operator()(RWSymbol s) const;                                 \
                                                                        \
private:                                                                \
                                                                        \
    class DefaultMethod {                                               \
    public:                                                             \
        Class operator()() const;                                       \
    };                                                                  \
}

#    if defined(_MSC_VER) || defined(__IBMCPP__)
#      define RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(Type1,Type2) \
template <>                                                             \
struct RWTPseudoMethodRegistryImp< RWTFunctor<void(Type1,Type2)> >      \
{                                                                       \
    typedef RWTFunctor<void(Type1,Type2)> method_type;                  \
    typedef RWTypeInfo key_type;                                        \
    typedef                                                             \
    RWTValHashDictionary<key_type, method_type >                        \
    registry_type;                                                      \
                                                                        \
    static void init ();                                                \
    static registry_type* registry ();                                  \
}
#    else
#      define RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(ign1,ign2)
#    endif


#  else

#    if defined(_RWBUILD_serial)
#      define RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(Class)  \
          extern template                                     \
          class RWTStreamingFactory< Class >
#    else
#      define RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(Class)  \
          extern template                                     \
          class RW_SERIAL_GLOBAL RWTStreamingFactory< Class >
#    endif

#    if defined(_MSC_VER) || defined(__IBMCPP__)
#      if defined(_RWBUILD_serial)
#        define RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(Type1,Type2) \
            extern template class                                         \
            RWTPseudoMethodRegistryImp< RWTFunctor<void(Type1,Type2)> >
#      else
#        define RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(Type1,Type2) \
            extern template class RW_SERIAL_GLOBAL                        \
            RWTPseudoMethodRegistryImp< RWTFunctor<void(Type1,Type2)> >
#      endif // _RWBUILD_serial
#    else
#      define RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(ign1,ign2)
#    endif

#  endif
#endif   // .._INSTANTIATE_TEMPLATES && !..._NO_EXPLICIT_INSTANTIATION

///////////////////////////////////////////////////////////////////////////////
// Define per-package object file ident macros for use with "what" command
///////////////////////////////////////////////////////////////////////////////

#define RW_SERIAL_IDENT \
static char rw_serial_ident[] = "\"@(#)\trw/serial:" __FILE__ " " __DATE__ " " __TIME__ "\"";

// Supply missing definition for type_info::operator== if necessary:
#if defined(_MSC_VER) && defined(_RWSTD_VER) && _RWSTD_VER <= 0x02020400
#  include <typeinfo>
inline bool type_info::operator== (const type_info& __rhs) const
{
    const char* __s1 = name();
    const char* __s2 = __rhs.name();

    return (0 == strcmp(__s1 ? __s1 : "", __s2 ? __s2 : ""));
}
#endif

#endif // rw_serial_pkgdefs_h_
