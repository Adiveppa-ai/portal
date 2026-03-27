#ifndef __rw_sync_pkgdefs_h__
#define __rw_sync_pkgdefs_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/pkgdefs.h#1 $
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

#include <rw/config/rwconfig_sync.h>
#include <rw/trace/pkgdefs.h>
#include <rw/defs.h>

/*****************************************************************************

 The following macros must be defined in order to configure a package:

  RW_SYNC_BUILD

  Specifies that the package source is currently being built for inclusion
  in a library.  If this macro is not defined, the package is being used to
  build a client library or application.

  RW_SYNC_DLL

  Specifies that the package is to be built or used as part of a DLL library.

  RW_SYNC_DEBUG

  Specifies that package is being built to include debug assertions.

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Map from RCB style macro to package style.
// Indicate that the library is being built instead of used.
//////////////////////////////////////////////////////////////////////////////
#if defined(_RWBUILD_sync)
#  define RW_SYNC_BUILD
#endif

// Compatibility definitions
#if defined(_WIN32) && defined(RW_SYNC_DLL)
#  if defined(_RWBUILD_sync)
#    define _RWSYNCBUILDDLL
#  endif // _RWBUILD_sync
#endif // _WIN32 && RW_SYNC_DLL

//////////////////////////////////////////////////////////////////////////////
// Define internal per-package DLL linkage macros
//////////////////////////////////////////////////////////////////////////////

#if defined(RW_SYNC_DLL)
#  if defined(RW_SYNC_BUILD)
#    define RW_SYNC_GLOBAL                      RW_COMPILER_GLOBAL_EXPORT
#    define RW_SYNC_SYMBOLIC                    RW_COMPILER_SYMBOLIC_EXPORT
#  else
#    define RW_SYNC_GLOBAL                      RW_COMPILER_GLOBAL_IMPORT
#    define RW_SYNC_SYMBOLIC                    RW_COMPILER_GLOBAL_IMPORT
#  endif
#else
#  define RW_SYNC_GLOBAL
#  define RW_SYNC_SYMBOLIC
#endif


//////////////////////////////////////////////////////////////////////////////
// Inlining for classes which, like RWTMonitor, are instantiated in the library
//////////////////////////////////////////////////////////////////////////////

#if (defined(__linux) && defined(__INTEL_COMPILER) && __INTEL_COMPILER<=800) || \
    (defined(_AIX) && defined (__IBMCPP__)) || \
    (defined(__sun) && defined (__SUNPRO_CC))
#  define RW_SYNC_INLINE_SPECIALIZED_MEMBER
#else
#  define RW_SYNC_INLINE_SPECIALIZED_MEMBER inline
#endif // (__INTEL_COMPILER) && __INTEL_COMPILER <= 800

///////////////////////////////////////////////////////////////////////////////
// Define package level enumerations
///////////////////////////////////////////////////////////////////////////////

// Define an enumerated to identify no initialization constructors

enum RWNoInitialization { RW_NO_INIT };

// Define the status return values for calls that accept a time-out value...

/**
 * \ingroup synchronization_package
 *
 * Defines the status return values for calls that accept a time-out value.
 */
enum RWWaitStatus {

    /**
     * The operation timed-out before completion
     */
    RW_THR_TIMEOUT = 0,

    // Define some interchangeable names for success...
    /**
     * The calling thread was signaled by another thread
     */
    RW_THR_SIGNALED = 1,

    /**
     * The calling thread acquired the resource
     */
    RW_THR_ACQUIRED = 1,

    /**
     * The operation completed
     */
    RW_THR_COMPLETED = 1,

    /**
     * The operation was aborted
     */
    RW_THR_ABORTED = 2
};


///////////////////////////////////////////////////////////////////////////////
// Define per-package assertion macros for use in debugging
///////////////////////////////////////////////////////////////////////////////

// maintained for compatibility only. was previously mentioned in the
// class reference.
#if defined(RW_SYNC_DEBUG)
#  define RW_SYNC_ASSERT(a) RW_ASSERT((a) != 0)
#else
#  define RW_SYNC_ASSERT(a)
#endif

#if defined(RW_THR_ENABLE_SOURCE_INCOMPATIBLE_CHANGES)
#  define RW_SYNC_MUTEX_USES_CRITICAL_SECTION
#endif

///////////////////////////////////////////////////////////////////////////////
// Define per-package object file ident macros for use with "what" command
///////////////////////////////////////////////////////////////////////////////

#define RW_SYNC_IDENT \
  static const char rw_sync_ident[] = "\"@(#)\trw/sync:" __FILE__ " " __DATE__ " " __TIME__ "\""; \
  inline void rw_use_sync_ident(void) { RW_UNUSED(rw_sync_ident); }

//////////////////////////////////////////////////////////////////////////////
// Platform specific macros
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Documentation related
//////////////////////////////////////////////////////////////////////////////

#endif // __rw_sync_pkgdefs_h__
