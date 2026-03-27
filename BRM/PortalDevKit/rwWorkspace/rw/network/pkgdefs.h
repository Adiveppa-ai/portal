#ifndef __rw_network_pkgdefs_h__
#define __rw_network_pkgdefs_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/pkgdefs.h#1 $
 *
 * Copyright (c) 1995-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

#include <rw/config/rwconfig_network.h>
#include <rw/defs.h>

#if !defined(RWNET_WINSOCK)
#  include <netinet/in.h>
#  include <sys/socket.h>
#  include <sys/types.h>
#elif defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)
// If winsock.h has been included (by itself or via windows.h) the
// build will fail. This is a known issue discussed endlessly in
// Onyx incidents. Users should either define WIN32_LEAN_AND_MEAN
// or include winsock2.h before including windows.h.
#  error Winsock v1 not supported with SourcePro
#else
#  include <winsock2.h>
#  include <ws2tcpip.h>
#endif // _WINSOCKAPI_ && !_WINSOCK2API_

/*
 * Convenience macros to replace direct calls to ntohs/htons/ntohl/htonl
 * if being compiled for a little endian platform, it make little sense
 * to include the function call (as it's a essentially a noop)
 * Historically, builds with __HP_aCC < 53600 also nooped the function, but
 * this behavior has been removed.
 * Certain compilers (icc) don't allow statements in the initializer list,
 * and function expands to a statement, the so we have to work around that.
 */

#undef RW_NTOHS
#undef RW_HTONS
#undef RW_NTOHL
#undef RW_HTONL

#if defined(RW_USE_LITTLE_ENDIAN)
#  define RW_NTOHS(x) ntohs(x)
#  define RW_HTONS(x) htons(x)
#  define RW_NTOHL(x) ntohl(x)
#  define RW_HTONL(x) htonl(x)
#else //RW_USE_LITTLE_ENDIAN
#  define RW_NTOHS(x) (x)
#  define RW_HTONS(x) (x)
#  define RW_NTOHL(x) (x)
#  define RW_HTONL(x) (x)
#endif//RW_USE_LITTLE_ENDIAN

#  if defined(DOXYGEN)
/**
 * \ingroup networking_module
 *
 * An unspecified integer type that represents a socket address length.
 */
typedef unspecified_type RWSockLenType;
#  else
// Do socket system calls take a int or a size_t for socket addrlen
typedef RW_SOCKLEN_TYPE RWSockLenType;
#  endif

#  ifndef RW_GETXBYY_BUFFER_SIZE
#    define RW_GETXBYY_BUFFER_SIZE 8192
#  endif

// The buffer length to use when receiving data into an RWCString.
#  ifndef RWSOCKET_RECVBUF_LEN
#    define RWSOCKET_RECVBUF_LEN 4096
#  endif

// The buffer length to use when receiving data into an RWCString.
#  ifndef RWPORTAL_RECVBUF_LEN
#    define RWPORTAL_RECVBUF_LEN 4096
#  endif

// The send/recv buffer length to use with Portal streams
#  ifndef RWNET_PORTAL_BUFFER_SIZE
#    define RWNET_PORTAL_BUFFER_SIZE 1024
#  endif

// Set which socket address types this platform knows about
#  define RWNET_HAS_INET_SOCKETS 1
// #define RWNET_HAS_UNIX_SOCKETS 1

/*****************************************************************************

 The following macros must be defined in order to configure a package:

  RW_NETWORK_BUILD

  Specifies that the package source is currently being built for inclusion
  in a library.  If this macro is not defined, the package is being used to
  build a client library or application.

  RW_NETWORK_DLL

  Specifies that the package is to be built or used as part of a DLL library.

  RW_NETWORK_DEBUG

  Specifies that package is being built to include debug assertions.

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Address missing in_port_t typedef on Windows
//////////////////////////////////////////////////////////////////////////////
#  if defined(_MSC_VER)
// Microsoft neither defines in_port_t, nor in_addr_t; while we could devise
// a solution to auto-detect the missing typedef and then auto-detect the type
// of struct member, and then create our own typedef to stand for the type of
// sin6_port, it seems it is much simpler to just simply detect Windows and
// define both in_addr_t and in_port_t as per POSIX, i.e. as uint16_t and
// uint32_t respectively, but using Microsoft's own typedefs.
typedef u_short in_port_t;
typedef u_long  in_addr_t;
#  endif // _MSC_VER

//////////////////////////////////////////////////////////////////////////////
// Map from RCB style macro to package style.
// Indicate that the library is being built instead of used.
//////////////////////////////////////////////////////////////////////////////
#  if defined(_RWBUILD_network)
#    define RW_NETWORK_BUILD
#  endif

// Compatibility definitions
#  if defined(_WIN32) && defined(RW_NETWORK_DLL)
#    if defined(_RWBUILD_network)
#      define _RWNETWORKBUILDDLL
#    endif // _RWBUILD_network
#  endif // _WIN32 && RW_NETWORK_DLL

//////////////////////////////////////////////////////////////////////////////
// Define internal per-package DLL linkage macros
//////////////////////////////////////////////////////////////////////////////

#  if defined(RW_NETWORK_DLL)
#    if defined(RW_NETWORK_BUILD)
#      define RW_NETWORK_GLOBAL                     RW_COMPILER_GLOBAL_EXPORT
#      define RW_NETWORK_SYMBOLIC                   RW_COMPILER_SYMBOLIC_EXPORT
#    else
#      define RW_NETWORK_GLOBAL                     RW_COMPILER_GLOBAL_IMPORT
#      define RW_NETWORK_SYMBOLIC                   RW_COMPILER_GLOBAL_IMPORT
#    endif // RW_NETWORK_BUILD
#  else
#    define RW_NETWORK_GLOBAL
#    define RW_NETWORK_SYMBOLIC
#  endif // Windows && DLL

///////////////////////////////////////////////////////////////////////////////
// Undefine closesocket and ioctlsocket if they are defined.
// Some third-party libraries define these to close() and ioctl() respectively.
// These #defines are incompatible with the network library.
///////////////////////////////////////////////////////////////////////////////

#  if defined(closesocket)
#    undef closesocket
#  endif
#  if defined(ioctlsocket)
#    undef ioctlsocket
#  endif

///////////////////////////////////////////////////////////////////////////////
// Define per-package object file ident macros for use with "what" command
///////////////////////////////////////////////////////////////////////////////

#  define RW_NETWORK_IDENT                                                \
    static const char                                                   \
    rw_network_ident[] =                                                \
    "\"@(#)\trw/network:" __FILE__ " " __DATE__ " " __TIME__ "\"";      \
                                                                        \
    inline void                                                         \
    rw_use_network_ident(void) { RW_UNUSED(rw_network_ident); }

//////////////////////////////////////////////////////////////////////////////
// Platform specific macros
//////////////////////////////////////////////////////////////////////////////

#endif // __rw_network_pkgdefs_h__
