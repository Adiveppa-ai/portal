#ifndef __RWDB_BUFFER_H__
#define __RWDB_BUFFER_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/buffer.h#1 $
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
 * Classes RWDBSimpleBuffer, RWDBBuffer and RWDBVariableWidthBuffer
 *
 **************************************************************************/

#include <rw/db/adapter.h>
#include <rw/db/column.h>
#include <rw/db/defs.h>
#include <rw/db/multirow.h>
#include <rw/tpdlist.h>


///////////////////////////////////////////////////////////////////////////
//
// class RWDBCType
//
// Information about a C data type, used by buffers and adapters to manage
// and convert data.  Each buffer has a type, stored as RWDBCType.
//
///////////////////////////////////////////////////////////////////////////
class RWDB_SYMBOLIC RWDBCType
{
public:
    typedef size_t TypeCode;

    RWDBCType(TypeCode typeCode, size_t elementSize);

    RWDBCType(const RWDBCType& cType);

    TypeCode typeCode() const
    {
        return typeCode_;
    }
    size_t   elementSize() const
    {
        return elementSize_;
    }

private:
    TypeCode typeCode_;
    size_t elementSize_;
};

class RWDB_GLOBAL RWDBSimpleBuffer
{
public:
    RWDBSimpleBuffer(void* data, const RWDBCType& typeInfo, size_t entries,
                     size_t width);

    virtual ~RWDBSimpleBuffer();

    RWDBCType typeInfo() const
    {
        return typeInfo_;
    }
    void* data() const
    {
        return (void*)data_;
    }

    size_t entries() const
    {
        return entries_;
    }
    size_t width() const
    {
        return width_;
    }

protected:
    void* data_;
    RWDBCType typeInfo_;
    size_t entries_;
    size_t width_;
};


/**
 * \ingroup db_open_sql_group
 *
 * \brief
 * Encapsulates a buffer of data, including its indicator array.
 *
 * RWDBAbstractBuffer is an encapsulation of a buffer of data, including its
 * indicator array. RWDBTBuffer derives from this class.
 */
class RWDB_GLOBAL RWDBBuffer : public RWDBSimpleBuffer
{
public:
    typedef void* (*DataAllocator)(size_t /*entries*/, size_t /*width*/);
    typedef void(*DataDeallocator)(void* /*data*/, size_t /*entries*/);

    // Automatically allocates data, null indicator.
    RWDBBuffer(const RWDBCType& typeInfo, DataAllocator allocator,
               DataDeallocator deallocator, size_t entries);

    // Automatically allocates null indicator only.
    RWDBBuffer(void* data, const RWDBCType& typeInfo, size_t entries);

    // Does not allocate data or indicator.
    RWDBBuffer(void* data, RWDBNullIndicator* indicator,
               const RWDBCType& typeInfo, size_t entries);

    virtual ~RWDBBuffer();

    bool operator==(const RWDBBuffer& rhs) const
    {
        return this == &rhs;
    }
    bool operator<(const RWDBBuffer& rhs) const
    {
        return this < &rhs;
    }

    // Returns a reference to the held RWDBColumn
    RWDBColumn& column();

    // Replaces self's column information with col
    void column(const RWDBColumn& col);

    // Returns true if we have column information
    bool hasColumnInformation() const
    {
        return bool(column_);
    }

    // name, paramType methods provided for backward compatibility,
    // you can just use the column() methods now.
    void name(const RWCString& name)
    {
        column().name(name);
    }
    RWCString name() const
    {
        if (hasColumnInformation()) {
            // Really, name() should be const, right?
            return ((RWDBBuffer*)this)->column().name();
        }
        else {
            return RWCString();
        }
    }

    void paramType(RWDBColumn::ParamType newType)
    {
        column().paramType(newType);
    }

    RWDBColumn::ParamType paramType() const
    {
        if (hasColumnInformation()) {
            // Really, name() should be const, right?
            return ((RWDBBuffer*)this)->column().paramType();
        }
        else {
            return RWDBColumn::inParameter;
        }
    }

    // Finds adapter created with f, and returns it.
    RWDBAdapter& findAdapter(RWDBAdapterFactory& f);

    void clearFactoryAdapters(RWDBAdapterFactory* f)
    {
        //  remove adapter from adapterStack if the factory
        //  passed in created the adapter
        RWTPtrDlist<RWDBAdapter>::iterator itr = adapterStack_.begin();
        while (itr != adapterStack_.end()) {
            RWDBAdapter* temp = *itr;
            if (*temp == *f) {
                itr = adapterStack_.erase(itr);
                delete temp;
            }
            else {
                ++itr;
            }
        }
    };

    virtual bool isNull(size_t index) const;

    virtual void setNull();
    virtual void setNull(size_t index);

    virtual void unsetNull();
    virtual void unsetNull(size_t index);

    bool ownsIndicator() const
    {
        return ownsIndicator_;
    }

    // RWDBValue interaction methods.
    virtual RWDBValue value(size_t index) const;
    virtual void value(size_t index, const RWDBValue& v);
    virtual RWDBValue::ValueType valueType() const;

protected:
    // Does not allocate data or indicator.
    RWDBBuffer(const RWDBCType& typeInfo, size_t entries);

    DataDeallocator deallocator_;
    RWDBNullIndicator* indicator_;
    bool ownsIndicator_;
    RWTScopedPointer<RWDBColumn> column_;
    // DList used because the Tools dlist implementation
    // is faster even for slist-style operations(!)
    RWTPtrDlist<RWDBAdapter> adapterStack_;

private:
    //Private copy constructor/assignment operator -- forbidden!
    RWDBBuffer(const RWDBBuffer&);
    RWDBBuffer& operator=(const RWDBBuffer&);
};

typedef RWDBBuffer RWDBAbstractBuffer;



///////////////////////////////////////////////////////////////////////////
//
// class RWDBVariableWidthBuffer : public RWDBBuffer
//
// A buffer that includes methods for managing the effective v.s. real
// length of individual elements.  RWDBTBuffer<char> and
// RWDBTBuffer<unsigned char> derive from this class.
//
///////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBVariableWidthBuffer : public RWDBBuffer
{
public:
    // Automatically allocates data, null indicator.
    RWDBVariableWidthBuffer(const RWDBCType& typeInfo,
                            DataAllocator allocator,
                            DataDeallocator deallocator, size_t entries, size_t width,
                            bool nullTerminated = false);

    // Automatically allocates null indicator only.
    RWDBVariableWidthBuffer(void* data,
                            const RWDBCType& typeInfo, size_t entries, size_t width,
                            bool nullTerminated = false);

    // Does not allocate data or indicator.
    RWDBVariableWidthBuffer(void* data, RWDBNullIndicator* indicator,
                            const RWDBCType& typeInfo, size_t entries, size_t width,
                            bool nullTerminated = false);

    virtual ~RWDBVariableWidthBuffer();

    // Sets the width of element 'index' to width 'width'.
    void setWidth(size_t index, size_t width);

    size_t width() const
    {
        return width_;
    }

    // Returns the width of element 'index'.
    size_t width(size_t index) const
    {
        RW_ASSERT(lengthIndicator_);
        RW_ASSERT(index < entries_);
        return lengthIndicator_[index];
    }

    // Returns the maximum of the actual data widths.
    // Also updates the internal length indicator from the data,
    // if the data is null-terminated.
    size_t computeWidths();

    // RWDBValue interaction methods.
    virtual RWDBValue value(size_t index) const;
    virtual void value(size_t index, const RWDBValue& v);
    virtual RWDBValue::ValueType valueType() const;

protected:
    bool nullTerminated_;
    size_t* lengthIndicator_;

private:
    //Private copy constructor/assignment operator -- forbidden!
    RWDBVariableWidthBuffer(const RWDBVariableWidthBuffer&);
    RWDBVariableWidthBuffer operator=(const RWDBVariableWidthBuffer&);
};

///////////////////////////////////////////////////////////////////////////
//
// rwdbFindMaximumOf<T>
//
// Finds the maximum length'ed T in the passed in buffer.  Assumes T
// has a .length() method.  2nd parameter unused, just there to help the
// compiler choose the right template instantiation.
//
///////////////////////////////////////////////////////////////////////////
// Helper function, returns maximum length of elements...
template <class T>
size_t
rwdbFindMaximumOf(RWDBBuffer* b, T*)
{
    size_t max = 0;
    size_t count = b->entries();
    T* buffdata = static_cast<T*>(b->data());
    for (size_t i = 0; i < count; ++i) {
        max = rwdbmax((buffdata + i)->length(), max);
    }
    return max;
}

///////////////////////////////////////////////////////////////////////////
//
// Simple wrapper for RWDBDataCallback
//
///////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBCallbackBuffer : public RWDBBuffer
{
public:
    RWDBCallbackBuffer(RWDBDataCallback* cb, bool ownsUserCallback = false);

    ~RWDBCallbackBuffer();

    // calls RWDBDataCallback::onFetch
    bool onFetch(size_t rownum, void* theData, size_t length,
                 RWDBNullIndicator ni, bool& lastPiece);

    // calls RWDBDataCallback::onSend
    bool onSend(size_t rownum, void* theData, size_t& length,
                RWDBNullIndicator& ni, bool& lastPiece);

    size_t getLength(size_t rownum) const;

    // RWDBValue interaction methods. Overridden from base class
    // because they don't make sense for a callback buffer
    virtual RWDBValue value(size_t) const
    {
        return RWDBValue();
    }

    virtual void value(size_t, const RWDBValue&)
    {
        // no-op
        ;
    }

    virtual RWDBValue::ValueType valueType() const;


    virtual bool isNull(size_t) const
    {
        return false;
    }

    virtual void setNull()
    {
        // no-op
    }

    virtual void setNull(size_t)
    {
        // no-op
    }

    virtual void unsetNull()
    {
        // no-op
    }

    virtual void unsetNull(size_t)
    {
        // no-op
    }

private:
    // not implemented
    RWDBCallbackBuffer(const RWDBCallbackBuffer&);
    RWDBCallbackBuffer& operator=(const RWDBCallbackBuffer&);

    bool ownsCallback_;
    RWDBDataCallback* callb_;
};

#endif // __RWDB_BUFFER_H__
