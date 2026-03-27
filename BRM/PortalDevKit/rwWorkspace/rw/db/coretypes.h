#ifndef __RWDB_CORETYPES_H__
#define __RWDB_CORETYPES_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/coretypes.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 **************************************************************************
 * #defines for the core datatype codes, and helper templates for
 * RWDBTBuffer.
 *
 **************************************************************************/

#include <rw/db/buffer.h>
#include <new>

// Type codes
// STOP!! Before changing these, make sure the valueTypeTranslator in
// buffer.cpp reflects your changes.
#define RWDB_TYPE_UNUSED                0
#define RWDB_TYPE_SHORT                 1
#define RWDB_TYPE_UNSIGNED_SHORT        2
#define RWDB_TYPE_INT                   3
#define RWDB_TYPE_UNSIGNED_INT          4
#define RWDB_TYPE_LONG                  5
#define RWDB_TYPE_UNSIGNED_LONG         6
#define RWDB_TYPE_FLOAT                 7
#define RWDB_TYPE_DOUBLE                8
#define RWDB_TYPE_CHAR                  9
#define RWDB_TYPE_UNSIGNED_CHAR         10
#define RWDB_TYPE_DECIMALPORTABLE       11

#if !defined(RW_DISABLE_DEPRECATED)
#define RWDB_TYPE_DATETIME              12
#endif

#define RWDB_TYPE_DURATION              13
#define RWDB_TYPE_CSTRING               14
#define RWDB_TYPE_BLOB                  15
#define RWDB_TYPE_DATE                  16
#define RWDB_TYPE_WCHAR_T               17
#define RWDB_TYPE_WSTRING               18
#define RWDB_TYPE_MBSTRING              19

#define RWDB_TYPE_RWDATETIME            20
#define RWDB_TYPE_NATIVETYPE1           21
#define RWDB_TYPE_USTRING               22

#define RWDB_TYPE_LONGLONG              23
#define RWDB_TYPE_UNSIGNED_LONGLONG     24
#define RWDB_TYPE_LONGDOUBLE            25

#define RWDB_TYPE_CHAR_CALLBACK         26
#define RWDB_TYPE_BINARY_CALLBACK       27
#define RWDB_TYPE_UCHAR16_CALLBACK      28

#define RWDB_TYPE_TIMETUPLE             29
#define RWDB_TYPE_TIMETUPLEOFFSET       30

// Since you will probably type this a lot, we've included it here for your
// copy-and-paste pleasure:
/*
case RWDB_TYPE_UNUSED:
    break;
case RWDB_TYPE_SHORT:
    break;
case RWDB_TYPE_UNSIGNED_SHORT:
    break;
case RWDB_TYPE_INT:
    break;
case RWDB_TYPE_UNSIGNED_INT:
    break;
case RWDB_TYPE_LONG:
    break;
case RWDB_TYPE_UNSIGNED_LONG:
    break;
case RWDB_TYPE_FLOAT:
    break;
case RWDB_TYPE_DOUBLE:
    break;
case RWDB_TYPE_CHAR:
    break;
case RWDB_TYPE_UNSIGNED_CHAR:
    break;
case RWDB_TYPE_DECIMALPORTABLE:
    break;

#if !defined(RW_DISABLE_DEPRECATED)
case RWDB_TYPE_DATETIME:
    break;
#endif

case RWDB_TYPE_DURATION:
    break;
case RWDB_TYPE_CSTRING:
    break;
case RWDB_TYPE_BLOB:
    break;
case RWDB_TYPE_DATE:
    break;
case RWDB_TYPE_WCHAR_T:
    break;
case RWDB_TYPE_WSTRING:
    break;
case RWDB_TYPE_MBSTRING:
    break;
case RWDB_TYPE_RWDATETIME:
    break;
case RWDB_TYPE_NATIVETYPE1:
    break;
case RWDB_TYPE_USTRING:
    break;
case RWDB_TYPE_LONGLONG:
    break;
case RWDB_TYPE_UNSIGNED_LONGLONG:
    break;
case RWDB_TYPE_LONGDOUBLE:
    break;
case RWDB_TYPE_CHAR_CALLBACK:
    break;
case RWDB_TYPE_BINARY_CALLBACK:
    break;
case RWDB_TYPE_UCHAR16_CALLBACK:
    break;
case RWDB_TYPE_TIMETUPLE:
    break;
case RWDB_TYPE_TIMETUPLEOFFSET:
    break;
*/

#define RWDB_START_TYPE_ODBC            0x100
#define RWDB_START_TYPE_INFORMIX        0x200
#define RWDB_START_TYPE_ORACLE          0x300
#define RWDB_START_TYPE_ORACLE8         0x400
#define RWDB_START_TYPE_SYBASECT        0x500
#define RWDB_START_TYPE_DB2             0x600
#define RWDB_START_TYPE_MSSQL           0x700
#define RWDB_START_TYPE_OCI             0x800
#define RWDB_START_TYPE_PGS             0x900
#define RWDB_START_TYPE_MYSQL           0xA00
#define RWDB_START_TYPE_UNUSED          0xB00

// Template helpers to make typecodes, allocators, deallocators

// RWDBCTypeStockMemoryManager is a template that makes allocators
// and deallocators for us.
template<class T>
class RWDBCTypeStockMemoryManager
{
public:
    static void* allocator(size_t entries, size_t width = 1)
    {
#ifdef RW_DEBUG
        T* d = new T[entries * width];
        RW_ASSERT(d);
        return (void*)d;
#else
        return (void*)(new T[entries * width]);
#endif
    }

    static void deallocator(void* data, size_t /*entries*/)
    {
        delete []((T*)data);
    }
};

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

////////////////////////////////////////////////////////////////////////////////
//
// template class RWDBCTypeStockMemoryManager<T>,
//                specialization < RWDBDateTime >
//
// Specialized on RWDBDateTime for performance.
//
////////////////////////////////////////////////////////////////////////////////
// AIX's compiler has a problem with complete specialized templates, so
// for AIX we will use partial template specialization
////////////////////////////////////////////////////////////////////////////////
#if defined(_AIX)

RWDBTEMPLATESPECDECL
void* RWDBCTypeStockMemoryManager< RWDBDateTime >::allocator(size_t entries,
        size_t /*width*/)
{
    char* d = new char[entries * sizeof(RWDBDateTime)] ;
#  ifdef RW_DEBUG
    RW_ASSERT(d);
#  endif
    RWDBDateTime temp ;
    for (size_t x = 0 ; x < entries ; ++x) {
        new(d + (x * sizeof(RWDBDateTime))) RWDBDateTime(temp);
    }
    return (void*)d;
}

RWDBTEMPLATESPECDECL
void RWDBCTypeStockMemoryManager< RWDBDateTime >::deallocator(void* data,
        size_t entries)
{
    // Call RWDBDateTime destructor explicitly before freeing the memory.
    RWDBDateTime* dtp = static_cast<RWDBDateTime*>(data);
    for (size_t x = 0 ; x < entries ; ++x) {
        (dtp++)->~RWDBDateTime();
    }
    delete []((char*)data);
}

#else /* if !defined( _AIX ) */

RWDBTEMPLATESPECDECL
class RWDBCTypeStockMemoryManager < RWDBDateTime >
{
public:
    static void* allocator(size_t entries, size_t /*width*/)
    {
        char* d = new char[entries * sizeof(RWDBDateTime)] ;
#  ifdef RW_DEBUG
        RW_ASSERT(d);
#  endif
        RWDBDateTime temp ;
        for (size_t x = 0 ; x < entries ; ++x) {
            new(d + (x * sizeof(RWDBDateTime))) RWDBDateTime(temp);
        }
        return (void*)d;
    }

    static void deallocator(void* data, size_t entries)
    {
        // Call RWDBDateTime destructor explicitly before freeing the memory.
        RWDBDateTime* dtp = static_cast<RWDBDateTime*>(data);
        for (size_t x = 0 ; x < entries ; ++x) {
            (dtp++)->~RWDBDateTime();
        }
        delete []((char*)data);
    }
} ;

#endif /* if defined( _AIX ) */

RW_RESTORE_DEPRECATED_WARNINGS
#endif // ! RW_DISABLE_DEPRECATED

////////////////////////////////////////////////////////////////////////////////
//
// template class RWDBCTypeStockMemoryManager<T>,
//                specialization < RWDate >
//
// Specialized on RWDate for performance.
//
////////////////////////////////////////////////////////////////////////////////
#if defined(_AIX)

RWDBTEMPLATESPECDECL
void* RWDBCTypeStockMemoryManager< RWDate >::allocator(size_t entries,
        size_t /*width*/)
{
    char* d = new char[entries * sizeof(RWDate)] ;
#  ifdef RW_DEBUG
    RW_ASSERT(d);
#  endif
    RWDate temp ;
    for (size_t x = 0 ; x < entries ; ++x) {
        new(d + (x * sizeof(RWDate))) RWDate(temp);
    }
    return (void*)d;
}

RWDBTEMPLATESPECDECL
void RWDBCTypeStockMemoryManager< RWDate >::deallocator(void* data,
        size_t entries)
{
    // Call RWDate destructor explicitly before freeing the memory.
    RWDate* datep = static_cast<RWDate*>(data);
    for (size_t x = 0 ; x < entries ; ++x) {
        (datep++)->~RWDate();
    }
    delete []((char*)data);
}

#else /* if !defined( _AIX ) */

RWDBTEMPLATESPECDECL
class RWDBCTypeStockMemoryManager < RWDate >
{
public:
    static void* allocator(size_t entries, size_t /*width*/)
    {
        char* d = new char[entries * sizeof(RWDate)] ;
#  ifdef RW_DEBUG
        RW_ASSERT(d);
#  endif
        RWDate temp ;
        for (size_t x = 0 ; x < entries ; ++x) {
            new(d + (x * sizeof(RWDate))) RWDate(temp);
        }
        return (void*)d;
    }

    static void deallocator(void* data, size_t entries)
    {
        // Call RWDate destructor explicitly before freeing the memory.
        RWDate* datep = static_cast<RWDate*>(data);
        for (size_t x = 0 ; x < entries ; ++x) {
            (datep++)->~RWDate();
        }
        delete []((char*)data);
    }
} ;

#endif /* if defined( _AIX ) */

// RWDBCTypeOf is a template specialized to allow typecodes
// to essentially be found at compile time based on the data type.
template<class T>
class RWDBCTypeOf : public RWDBCType
{
public:
    RWDBCTypeOf() : RWDBCType(RWDB_TYPE_UNUSED, 0)
    {
        // You got here because a template was instantiated on a type
        // for which no typecode has been associated.  Use
        // RWDB_ASSOCIATE_TYPE to set up a typecode for this type.
        assert(false);
    }
};

#define RWDB_ASSOCIATE_TYPE(c,t)               \
RWDBTEMPLATESPECDECL                           \
class RWDBCTypeOf<t> : public RWDBCType {      \
    public:                                    \
    RWDBCTypeOf() : RWDBCType(c, sizeof(t)) {} \
};

// The RWDB_ASSOCIATE_TYPEs for the supported core types are in
// tbuffer.h, to reduce compile times for translation units that don't
// use RWDBTBuffer<T>.

#endif // __RWDB_CORETYPES_H__
