#ifndef __rw_trace_pkgdefs_h__
#define __rw_trace_pkgdefs_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/pkgdefs.h#1 $
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
 *************************************************************************/

#include <rw/config/rwconfig_trace.h>
#include <rw/defs.h>

/*****************************************************************************

 The following macros must be defined in order to configure a package:

  RW_TRACE_BUILD

  Specifies that the package source is currently being built for inclusion
  in a library.  If this macro is not defined, the package is being used to
  build a client library or application.

  RW_TRACE_DLL

  Specifies that the package is to be built or used as part of a DLL library.

  RW_TRACE_DEBUG

  Specifies that package is being built to include debug assertions.

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Map from RCB style macro to package style.
// Indicate that the library is being built instead of used.
//////////////////////////////////////////////////////////////////////////////
#if defined(_RWBUILD_trace)
#  define RW_TRACE_BUILD
#endif

//////////////////////////////////////////////////////////////////////////////
// Define internal per-package DLL linkage macros
//////////////////////////////////////////////////////////////////////////////

#if defined(RW_TRACE_DLL)
#  if defined(RW_TRACE_BUILD)
#    define RW_TRACE_GLOBAL                           RW_COMPILER_GLOBAL_EXPORT
#    define RW_TRACE_SYMBOLIC                         RW_COMPILER_SYMBOLIC_EXPORT
#    define RW_TRACE_MACRO_DECLSPEC                   RW_COMPILER_GLOBAL_EXPORT
#  else
#    define RW_TRACE_GLOBAL                           RW_COMPILER_GLOBAL_IMPORT
#    define RW_TRACE_SYMBOLIC                         RW_COMPILER_GLOBAL_IMPORT

#    if defined(RW_BUILD_USER_DLL)
#      define RW_TRACE_MACRO_DECLSPEC                     RW_COMPILER_GLOBAL_EXPORT
#    elif defined(RW_USE_USER_DLL)
#      define RW_TRACE_MACRO_DECLSPEC                   RW_COMPILER_GLOBAL_IMPORT
#    else
#      define RW_TRACE_MACRO_DECLSPEC
#    endif
#  endif
#else
#  define RW_TRACE_GLOBAL
#  define RW_TRACE_SYMBOLIC
#  define RW_TRACE_MACRO_DECLSPEC
#endif

//////////////////////////////////////////////////////////////////////////////
// Define package specific enumerations.
//////////////////////////////////////////////////////////////////////////////

/**
 * \ingroup execution_tracing_package
 *
 * \headerfileloc{#include <rw/thr/defs.h>}
 *
 * An enumerated type used to identify static instance constructors.
 */
enum RWStaticCtor {

    /**
     * &nbsp;
     */
    RW_STATIC_CTOR
};


//////////////////////////////////////////////////////////////////////////////
// Define per-package object file ident macros for use with "what" command
//////////////////////////////////////////////////////////////////////////////

#define RW_TRACE_IDENT \
  static const char rw_trace_ident[] = "\"@(#)\trw/trace:" __FILE__ " " __DATE__ " " __TIME__ "\""; \
  inline void rw_use_trace_ident(void) { RW_UNUSED(rw_trace_ident); }

//////////////////////////////////////////////////////////////////////////////
// Platform specific macros
//////////////////////////////////////////////////////////////////////////////

#endif // __rw_trace_pkgdefs_h__
