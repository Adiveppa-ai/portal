#ifndef rw_types_pkgdefs_h_
#define rw_types_pkgdefs_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/types/pkgdefs.h#1 $
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

#include <rw/config/rwconfig_types.h>

/*****************************************************************************

 The following macros must be defined in order to configure a package:

  RW_TYPES_BUILD

  Specifies that the package source is currently being built for inclusion
  in a library.  If this macro is not defined, the package is being used to
  build a client library or application.

  RW_TYPES_DLL

  Specifies that the package is to be built or used as part of a DLL library.

  RW_TYPES_DEBUG

  Specifies that package is being built to include debug assertions.

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Map from RCB style macro to package style.
// Indicate that the library is being built instead of used.
//////////////////////////////////////////////////////////////////////////////
#if defined(_RWBUILD_types)
#  define RW_TYPES_BUILD
#endif

// Compatibility definitions
#if defined(_WIN32) && defined(RW_TYPES_DLL)
#  if defined(_RWBUILD_types)
#    define _RWTYPESBUILDDLL
#  endif // _RWBUILD_types
#endif // _WIN32 && RW_TYPES_DLL

//////////////////////////////////////////////////////////////////////////////
// Define internal per-package DLL linkage macros
//////////////////////////////////////////////////////////////////////////////

#if defined(RW_TYPES_DLL)
#  if defined(RW_TYPES_BUILD)
#    define RW_TYPES_GLOBAL                      RW_COMPILER_GLOBAL_EXPORT
#    define RW_TYPES_SYMBOLIC                    RW_COMPILER_SYMBOLIC_EXPORT
#  else
#    define RW_TYPES_GLOBAL                      RW_COMPILER_GLOBAL_IMPORT
#    define RW_TYPES_SYMBOLIC                    RW_COMPILER_GLOBAL_IMPORT
#  endif
#else
#  define RW_TYPES_GLOBAL
#  define RW_TYPES_SYMBOLIC
#endif

///////////////////////////////////////////////////////////////////////////////
// Define per-package object file ident macros for use with "what" command
///////////////////////////////////////////////////////////////////////////////

#define RW_TYPES_IDENT \
static char rw_types_ident[] = "\"@(#)\trw/types:" __FILE__ " " __DATE__ " " __TIME__ "\"";

#endif // rw_types_pkgdefs_h_
