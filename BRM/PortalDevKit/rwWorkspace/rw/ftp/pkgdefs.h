#ifndef __rw_ftp_pkgdefs_h__
#define __rw_ftp_pkgdefs_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/ftp/pkgdefs.h#1 $
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

#include <rw/config/rwconfig_ftp.h>

// This include file depends on a macro which is defined in this file
// it is now being included near the bottom of this file, but we should
// probably consider either doing this with all other packages, or fixing
// it in a cleaner way.
//#include <rw/ftp/defs.h>

//////////////////////////////////////////////////////////////////////////////
// We are still dependent on rw/defs.h for some macros
//////////////////////////////////////////////////////////////////////////////

#include <rw/network/pkgdefs.h>
#include <rw/trace/pkgdefs.h>

/*****************************************************************************

 The following macros must be defined in order to configure a package:

  RW_FTP_BUILD

  Specifies that the package source is currently being built for inclusion
  in a library.  If this macro is not defined, the package is being used to
  build a client library or application.

  RW_FTP_DLL

  Specifies that the package is to be built or used as part of a DLL library.

  RW_FTP_DEBUG

  Specifies that package is being built to include debug assertions.

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Map from RCB style macro to package style.
// Indicate that the library is being built instead of used.
//////////////////////////////////////////////////////////////////////////////
#if defined(_RWBUILD_ftp)
#  define RW_FTP_BUILD
#endif

//////////////////////////////////////////////////////////////////////////////
// Define internal per-package DLL linkage macros
//////////////////////////////////////////////////////////////////////////////

#if defined(RW_SHARED)
#  if defined(RW_FTP_BUILD)
#    define RW_FTP_GLOBAL                      RW_COMPILER_GLOBAL_EXPORT
#    define RW_FTP_SYMBOLIC                    RW_COMPILER_SYMBOLIC_EXPORT
#  else
#    define RW_FTP_GLOBAL                      RW_COMPILER_GLOBAL_IMPORT
#    define RW_FTP_SYMBOLIC                    RW_COMPILER_GLOBAL_IMPORT
#  endif
#else
#  define RW_FTP_GLOBAL
#  define RW_FTP_SYMBOLIC
#endif

///////////////////////////////////////////////////////////////////////////////
// Define per-package object file ident macros for use with "what" command
///////////////////////////////////////////////////////////////////////////////

#define RW_FTP_IDENT \
  static const char rw_ftp_ident[] = "\"@(#)\trw/ftp:" __FILE__ " " __DATE__ " " __TIME__ "\""; \
  inline void rw_use_ftp_ident(void) { RW_UNUSED(rw_ftp_ident); }

///////////////////////////////////////////////////////////////////////////////
// Package specific macros and defines
///////////////////////////////////////////////////////////////////////////////

#include <rw/defs.h>

#define USE_RWTOOLS 1             // always using tools

#define RWINET_IGNORE_OPERATION_ABORT_THROW(xx) \
   try { xx; } catch (const RWTHROperationAborted&) {}

#include <rw/ftp/defs.h>

//////////////////////////////////////////////////////////////////////////////
// Documentation related
//////////////////////////////////////////////////////////////////////////////

#endif // __rw_ftp_pkgdefs_h__
