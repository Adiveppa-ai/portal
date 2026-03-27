#ifndef rw_serial_RWStreamableTypesBuiltin_h_
#define rw_serial_RWStreamableTypesBuiltin_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWStreamableTypesBuiltin.h#1 $
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

// Disable VC++ 'nonstandard extension used' warning
#if defined(_MSC_VER)
#  pragma warning (disable: 4231)
#endif

// Hack to prevent the tons of warnings poured by
// GCC when encountering the extern template extension
#if __GNUG__ >= 3
#  pragma GCC system_header
#endif   // gcc >= 3

#include <rw/serial/RWObjectStreamMacros.h>
#include <rw/serial/RWTStreamingFactory.h>
#include <rw/serial/pkgdefs.h>
#include <rw/types/types.h>

typedef signed char    rwsignedchar;
typedef unsigned char  rwunsignedchar;
typedef long double    rwlongdouble;
typedef unsigned int   rwunsignedint;
typedef unsigned long  rwunsignedlong;
typedef unsigned short rwunsignedshort;

RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const bool*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(bool*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const char*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(char*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const double*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(double*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const float*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(float*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const int*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(int*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const long*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(long*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const rwlongdouble*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(rwlongdouble*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const long long*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(long long*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const unsigned long long*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(unsigned long long*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const rwsignedchar*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(rwsignedchar*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const rwunsignedchar*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(rwunsignedchar*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const rwunsignedint*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(rwunsignedint*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const rwunsignedlong*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(rwunsignedlong*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const rwunsignedshort*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(rwunsignedshort*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const short*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(short*, RWObjectInputStream&);


#if !defined(_WIN32)
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const wchar_t*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(wchar_t*, RWObjectInputStream&);

#endif

/**************************************************************************/

RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(bool*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(char*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(double*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(float*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(int*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(long*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(rwlongdouble*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(rwsignedchar*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(long long*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(unsigned long long*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(rwunsignedchar*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(rwunsignedint*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(rwunsignedlong*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(rwunsignedshort*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(short*);

#if !defined(_WIN32)
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(wchar_t*);
#endif

/**************************************************************************/

RW_DECLARE_STREAMABLE_LIBRARY_POINTER(bool)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(char)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(rwsignedchar)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(rwunsignedchar)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(wchar_t)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(double)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(rwlongdouble)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(float)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(int)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(rwunsignedint)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(long)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(rwunsignedlong)

RW_DECLARE_STREAMABLE_LIBRARY_POINTER(long long)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(unsigned long long)

RW_DECLARE_STREAMABLE_LIBRARY_POINTER(short)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(rwunsignedshort)

#endif
