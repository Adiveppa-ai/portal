#ifndef __RWDB_BUFFERFACTORY_H__
#define __RWDB_BUFFERFACTORY_H__

/*************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/rwdbbufferfactory.h#1 $
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
 *
 * Declaration of class RWDBBufferFactory
 *
 * Provides an object that represents a generic type conversion info.
 *
 *************************************************************************/

#include <rw/db/buffer.h>
#include <rw/db/coretypes.h>
#include <rw/tools/bustring.h>

class RWDBBufferFactory
{
public:
    virtual ~RWDBBufferFactory() {}
    virtual RWDBAbstractBuffer* make(RWDBValue::ValueType type,
                                     size_t rows,
                                     size_t storageLength) const = 0;
};

class RWDBGenericBufferFactory
    : public RWDBBufferFactory
{
public:
    virtual ~RWDBGenericBufferFactory() {}

    // This method makes the most generic of buffers.
    //  These are the most commonly produced, and assume
    //  the binding locations are going to be owned by
    //  the DB Interface Module.
    virtual RWDBAbstractBuffer* make(RWDBValue::ValueType type,
                                     size_t rows,
                                     size_t storageLength) const
    {
        switch (type) {
            case RWDBValue::Char:
            case RWDBValue::Tiny:
            case RWDBValue::Short:
            case RWDBValue::Int:
            case RWDBValue::Long:
                return new RWDBBuffer(RWDBCType(RWDB_TYPE_LONG, sizeof(long)),
                                      RWDBCTypeStockMemoryManager<long>::allocator,
                                      RWDBCTypeStockMemoryManager<long>::deallocator,
                                      rows);
            case RWDBValue::LongLong:
                return new RWDBBuffer(RWDBCType(RWDB_TYPE_LONGLONG, sizeof(long long)),
                                      RWDBCTypeStockMemoryManager<long long>::allocator,
                                      RWDBCTypeStockMemoryManager<long long>::deallocator,
                                      rows);
            case RWDBValue::UnsignedChar:
            case RWDBValue::UnsignedTiny:
            case RWDBValue::UnsignedShort:
            case RWDBValue::UnsignedInt:
            case RWDBValue::UnsignedLong:
                return new RWDBBuffer(RWDBCType(RWDB_TYPE_UNSIGNED_LONG,
                                                sizeof(unsigned long)),
                                      RWDBCTypeStockMemoryManager<unsigned long>::allocator,
                                      RWDBCTypeStockMemoryManager<unsigned long>::deallocator,
                                      rows);
            case RWDBValue::UnsignedLongLong:
                return new RWDBBuffer(RWDBCType(RWDB_TYPE_UNSIGNED_LONGLONG,
                                                sizeof(unsigned long long)),
                                      RWDBCTypeStockMemoryManager<unsigned long long>::allocator,
                                      RWDBCTypeStockMemoryManager<unsigned long long>::deallocator,
                                      rows);
            case RWDBValue::Float:
            case RWDBValue::Double:
                return new RWDBBuffer(RWDBCType(RWDB_TYPE_DOUBLE,
                                                sizeof(double)),
                                      RWDBCTypeStockMemoryManager<double>::allocator,
                                      RWDBCTypeStockMemoryManager<double>::deallocator,
                                      rows);
            case RWDBValue::LongDouble:
                return new RWDBBuffer(RWDBCType(RWDB_TYPE_LONGDOUBLE,
                                                sizeof(long double)),
                                      RWDBCTypeStockMemoryManager<long double>::allocator,
                                      RWDBCTypeStockMemoryManager<long double>::deallocator,
                                      rows);
            case RWDBValue::Decimal:
                return new RWDBBuffer(RWDBCType(RWDB_TYPE_DECIMALPORTABLE,
                                                sizeof(RWDecimalPortable)),
                                      RWDBCTypeStockMemoryManager<RWDecimalPortable>::allocator,
                                      RWDBCTypeStockMemoryManager<RWDecimalPortable>::deallocator,
                                      rows);
            case RWDBValue::Date:
            case RWDBValue::DateTime: {
                RWTScopedPointer<RWDBBuffer> b(new RWDBBuffer(RWDBCType(RWDB_TYPE_RWDATETIME,
                                               sizeof(RWDateTime)),
                                               RWDBCTypeStockMemoryManager<RWDateTime>::allocator,
                                               RWDBCTypeStockMemoryManager<RWDateTime>::deallocator,
                                               rows));
                RW_ASSERT(storageLength <= RW_LONG_MAX);
                b->column().storageLength(static_cast<long>(storageLength));
                return b.release();
            }
            case RWDBValue::TimeTuple: {
                RWTScopedPointer<RWDBBuffer> b(new RWDBBuffer(RWDBCType(RWDB_TYPE_TIMETUPLE,
                                               sizeof(RWTimeTuple)),
                                               RWDBCTypeStockMemoryManager<RWTimeTuple>::allocator,
                                               RWDBCTypeStockMemoryManager<RWTimeTuple>::deallocator,
                                               rows));
                RW_ASSERT(storageLength <= RW_LONG_MAX);
                b->column().storageLength(static_cast<long>(storageLength));
                return b.release();
            }
            case RWDBValue::TimeTupleOffset: {
                RWTScopedPointer<RWDBBuffer> b(new RWDBBuffer(RWDBCType(RWDB_TYPE_TIMETUPLEOFFSET,
                                               sizeof(RWTimeTupleOffset)),
                                               RWDBCTypeStockMemoryManager<RWTimeTupleOffset>::allocator,
                                               RWDBCTypeStockMemoryManager<RWTimeTupleOffset>::deallocator,
                                               rows));
                RW_ASSERT(storageLength <= RW_LONG_MAX);
                b->column().storageLength(static_cast<long>(storageLength));
                return b.release();
            }
            case RWDBValue::Duration: {
                RWTScopedPointer<RWDBBuffer> b(new RWDBBuffer(RWDBCType(RWDB_TYPE_DURATION,
                                               sizeof(RWDBDuration)),
                                               RWDBCTypeStockMemoryManager<RWDBDuration>::allocator,
                                               RWDBCTypeStockMemoryManager<RWDBDuration>::deallocator,
                                               rows));
                RW_ASSERT(storageLength <= RW_LONG_MAX);
                b->column().storageLength(static_cast<long>(storageLength));
                return b.release();
            }
            case RWDBValue::String: {
                RWTScopedPointer<RWDBBuffer> b(new RWDBBuffer(RWDBCType(RWDB_TYPE_CSTRING,
                                               sizeof(RWCString)),
                                               RWDBCTypeStockMemoryManager<RWCString>::allocator,
                                               RWDBCTypeStockMemoryManager<RWCString>::deallocator,
                                               rows));
                RW_ASSERT(storageLength <= RW_LONG_MAX);
                b->column().storageLength(static_cast<long>(storageLength));
                return b.release();
            }
            case RWDBValue::MBString: {
                RWTScopedPointer<RWDBBuffer> b(new RWDBBuffer(RWDBCType(RWDB_TYPE_MBSTRING,
                                               sizeof(RWDBMBString)),
                                               RWDBCTypeStockMemoryManager<RWDBMBString>::allocator,
                                               RWDBCTypeStockMemoryManager<RWDBMBString>::deallocator,
                                               rows));
                RW_ASSERT(storageLength <= RW_LONG_MAX);
                b->column().storageLength(static_cast<long>(storageLength));
                return b.release();
            }
            case RWDBValue::UString: {
                RWTScopedPointer<RWDBBuffer> b(new RWDBBuffer(RWDBCType(RWDB_TYPE_USTRING,
                                               sizeof(RWBasicUString)),
                                               RWDBCTypeStockMemoryManager<RWBasicUString>::allocator,
                                               RWDBCTypeStockMemoryManager<RWBasicUString>::deallocator,
                                               rows));
                RW_ASSERT(storageLength <= RW_LONG_MAX);
                b->column().storageLength(static_cast<long>(storageLength));
                return b.release();
            }
            case RWDBValue::Blob: {
                RWTScopedPointer<RWDBBuffer> b(new RWDBBuffer(RWDBCType(RWDB_TYPE_BLOB,
                                               sizeof(RWDBBlob)),
                                               RWDBCTypeStockMemoryManager<RWDBBlob>::allocator,
                                               RWDBCTypeStockMemoryManager<RWDBBlob>::deallocator,
                                               rows));
                RW_ASSERT(storageLength <= RW_LONG_MAX);
                b->column().storageLength(static_cast<long>(storageLength));
                return b.release();
            }
            case RWDBValue::WString: {
                RWTScopedPointer<RWDBBuffer> b(new RWDBBuffer(RWDBCType(RWDB_TYPE_WSTRING,
                                               sizeof(RWWString)),
                                               RWDBCTypeStockMemoryManager<RWWString>::allocator,
                                               RWDBCTypeStockMemoryManager<RWWString>::deallocator,
                                               rows));
                RW_ASSERT(storageLength <= RW_LONG_MAX);
                b->column().storageLength(static_cast<long>(storageLength));
                return b.release();
            }
            case RWDBValue::NoType:
            default:
                RW_ASSERT(false);
        }
        return NULL;
    }

};

#endif
