#ifndef rw_xmlabstractions_pkgdefs_h_
#define rw_xmlabstractions_pkgdefs_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/pkgdefs.h#1 $
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

#include <rw/config/rwconfig_xmlabstractions.h>

// This include file depends on a macro which is defined in this file
// it is now being included near the bottom of this file, but we should
// probably consider either doing this with all other packages, or fixing
// it in a cleaner way.

/*****************************************************************************

 The following macros must be defined in order to configure a package:

  RW_XMLABSTRACTIONS_BUILD

  Specifies that the package source is currently being built for inclusion
  in a library.  If this macro is not defined, the package is being used to
  build a client library or application.

  RW_XMLABSTRACTIONS_DLL

  Specifies that the package is to be built or used as part of a DLL library.

  RW_XMLABSTRACTIONS_DEBUG

  Specifies that package is being built to include debug assertions.

  RW_XMLABSTRACTIONS_TRACE_LEVEL

  Specifies the level of trace event reporting that is to be compiled into
  the package code.  Also used to detect whether package was configured.

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Map from RCB style macro to package style.
// Indicate that the library is being built instead of used.
//////////////////////////////////////////////////////////////////////////////
#if defined(_RWBUILD_xmlabstractions)
#  define RW_XMLABSTRACTIONS_BUILD
#endif

// Compatibility definitions
#if defined(_WIN32) && defined(RW_XMLABSTRACTIONS_DLL)
#  if defined(_RWBUILD_xmlabstractions)
#    define _RWXMLABSTRACTIONSBUILDDLL
#  endif // _RWBUILD_xmlabstractions
#endif // _WIN32 && RW_XMLABSTRACTIONS_DLL

//////////////////////////////////////////////////////////////////////////////
// Define internal per-package DLL linkage macros
//////////////////////////////////////////////////////////////////////////////

#if defined(RW_XMLABSTRACTIONS_DLL)
#  if defined(RW_XMLABSTRACTIONS_BUILD)
#    define RW_XMLABSTRACTIONS_GLOBAL                  RW_COMPILER_GLOBAL_EXPORT
#    define RW_XMLABSTRACTIONS_SYMBOLIC                RW_COMPILER_SYMBOLIC_EXPORT
#  else
#    define RW_XMLABSTRACTIONS_GLOBAL                  RW_COMPILER_GLOBAL_IMPORT
#    define RW_XMLABSTRACTIONS_SYMBOLIC                RW_COMPILER_GLOBAL_IMPORT
#  endif
#else
#  define RW_XMLABSTRACTIONS_GLOBAL
#  define RW_XMLABSTRACTIONS_SYMBOLIC
#endif

///////////////////////////////////////////////////////////////////////////////
// Define per-package object file ident macros for use with "what" command
///////////////////////////////////////////////////////////////////////////////

#define RW_XMLABSTRACTIONS_IDENT \
static char rw_xmlabstractions_ident[] = "\"@(#)\trw/xmlabstractions:" __FILE__ " " __DATE__ " " __TIME__ "\"";

///////////////////////////////////////////////////////////////////////////////
// Package specific macros and defines
///////////////////////////////////////////////////////////////////////////////

#include <rw/defs.h>
#define USE_RWTOOLS 1             // always using tools

// Define compatibility macro
#define RWXMLABSTRACTIONS     RW_XMLABSTRACTIONS_VERSION


inline long getXmlabstractionsVersion()
{
    return RWXMLABSTRACTIONS;
}

#endif // rw_xmlabstractions_pkgdefs_h_
