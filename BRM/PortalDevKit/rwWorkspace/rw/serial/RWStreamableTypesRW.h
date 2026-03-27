#ifndef rw_serial_RWStreamableTypesRW_h_
#define rw_serial_RWStreamableTypesRW_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWStreamableTypesRW.h#1 $
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
#include <rw/colldate.h>
#include <rw/collint.h>
#include <rw/collstr.h>
#include <rw/decport.h>
#include <rw/rwdate.h>
#include <rw/rwint.h>
#include <rw/tools/bustring.h>
#include <rw/tools/datetime.h>
#include <rw/wstring.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  include <rw/rwtime.h>
#endif


// Instantiation of RWTPseudoMethodRegistryImp to avoid ODR
// violations with both MSVC (6.0/7.1) and Visual Age for C++
// (6.x and 7.x)
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWCollectable*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWCollectable*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWCollectableString*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWCollectableString*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWCollectableWString*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWCollectableWString*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWCollectableInt*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWCollectableInt*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWCollectableDate*, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWCollectableDate*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWBasicUString*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWBasicUString, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWCString*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWCString, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWDate*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWDate, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWDateTime*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWDateTime, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWDecimalPortable*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWDecimalPortable, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWInteger*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWInteger, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWSymbol*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWSymbol, RWObjectInputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(const RWWString*, RWObjectOutputStream&);
RW_SERIAL_INSTANTIATE_PSEUDO_METHOD_REGISTRY(RWWString, RWObjectInputStream&);

/**************************************************************************/

RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWCString*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWWString*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWBasicUString*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWSymbol*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWDate*);

#if !defined(RW_DISABLE_DEPRECATED)

RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWTime*);

#endif

RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWDateTime*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWDecimalPortable*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWInteger*);

RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWCollectable*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWCollectableString*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWCollectableInt*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWCollectableDate*);
RW_SERIAL_INSTANTIATE_STREAMING_FACTORY(RWCollectableWString*);

/**************************************************************************/

RW_DECLARE_STREAMABLE_LIBRARY_POINTER(RWBasicUString)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(RWCString)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(RWDate)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(RWDateTime)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(RWDecimalPortable)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(RWInteger)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(RWSymbol)
RW_DECLARE_STREAMABLE_LIBRARY_POINTER(RWWString)

RW_DECLARE_STREAMABLE_COLLECTABLE

RW_DECLARE_STREAMABLE_DERIVED_COLLECTABLE(RWCollectableInt, RWInteger)
RW_DECLARE_STREAMABLE_DERIVED_COLLECTABLE(RWCollectableDate, RWDate)
RW_DECLARE_STREAMABLE_DERIVED_COLLECTABLE(RWCollectableString, RWCString)
RW_DECLARE_STREAMABLE_DERIVED_COLLECTABLE(RWCollectableWString, RWWString)

#endif
