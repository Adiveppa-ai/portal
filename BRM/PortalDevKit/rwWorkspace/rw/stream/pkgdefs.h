#ifndef rw_stream_pkgdefs_h_
#define rw_stream_pkgdefs_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/pkgdefs.h#1 $
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

#include <rw/config/rwconfig_streams.h>
#include <rw/stream/types.h>
#include <rw/defs.h>

#if !defined(RW_STREAM_BUFFER_SIZE) || defined(DOXYGEN)
/**
 * \ingroup xmlstreams_package
 * The default size, in bytes, for dynamically allocated internal buffers.
 * The value of this constant is 512, but can be overridden by defining the
 * macro as part of a build configuration.
 */
#  define RW_STREAM_BUFFER_SIZE 512
#endif


///////////////////////////////////////////////////////////////////////////////
// Define per-platform specific shortcomings/workarounds
///////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && (__GNUG__ < 3) && !defined(RW_STDLIB_VER)
#  define RW_NO_STD_WSTRING
#endif

/*****************************************************************************

 The following macros must be defined in order to configure a package:

  RW_STREAM_BUILD

  Specifies that the package source is currently being built for inclusion
  in a library.  If this macro is not defined, the package is being used to
  build a client library or application.

  RW_STREAM_DLL

  Specifies that the package is to be built or used as part of a DLL library.

  RW_STREAM_DEBUG

  Specifies that package is being built to include debug assertions.

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Map from RCB style macro to package style.
// Indicate that the library is being built instead of used.
//////////////////////////////////////////////////////////////////////////////
#if defined(_RWBUILD_streams)
#  define RW_STREAM_BUILD
#endif

// Compatibility definitions
#if defined(_WIN32) && defined(RW_STREAM_DLL)
#  if defined(_RWBUILD_streams)
#    define _RWSTREAMSBUILDDLL
#  endif // _RWBUILD_streams
#endif // _WIN32 && RW_STREAM_DLL

//////////////////////////////////////////////////////////////////////////////
// Define internal per-package DLL linkage macros
//////////////////////////////////////////////////////////////////////////////

#if defined(RW_STREAM_DLL)
#  if defined(RW_STREAM_BUILD)
#    define RW_STREAM_GLOBAL                      RW_COMPILER_GLOBAL_EXPORT
#    define RW_STREAM_SYMBOLIC                    RW_COMPILER_SYMBOLIC_EXPORT
#  else
#    define RW_STREAM_GLOBAL                      RW_COMPILER_GLOBAL_IMPORT
#    define RW_STREAM_SYMBOLIC                    RW_COMPILER_GLOBAL_IMPORT
#  endif
#else
#  define RW_STREAM_GLOBAL
#  define RW_STREAM_SYMBOLIC
#endif

///////////////////////////////////////////////////////////////////////////////
// Define per-package object file ident macros for use with "what" command
///////////////////////////////////////////////////////////////////////////////

#define RW_STREAM_IDENT \
static char rw_stream_ident[] = "\"@(#)\trw/stream:" __FILE__ " " __DATE__ " " __TIME__ "\"";

//////////////////////////////////////////////////////////////////////////////
// Platform specific macros
//////////////////////////////////////////////////////////////////////////////

#endif // rw_stream_pkgdefs_h_
