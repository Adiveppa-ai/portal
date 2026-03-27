#ifndef __RWDB_TBUFFER_H__
#define __RWDB_TBUFFER_H__

/*************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/tbuffer.h#1 $
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
 * Declaration of class RWDBTBuffer<T>
 *
 * Provides an object that represents a generic buffer.
 *
 *************************************************************************/

#include <rw/db/buffer.h>
#include <rw/db/column.h>
#include <rw/db/coretypes.h>
#include <rw/db/value.h>
#include <rw/tools/bustring.h>

// Associations of typecodes to C++ types for core-supported types.
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_SHORT, short)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_UNSIGNED_SHORT, unsigned short)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_INT, int)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_UNSIGNED_INT, unsigned int)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_LONG, long)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_UNSIGNED_LONG, unsigned long)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_LONGLONG, long long)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_UNSIGNED_LONGLONG, unsigned long long)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_FLOAT, float)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_DOUBLE, double)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_LONGDOUBLE, long double)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_CHAR, char)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_UNSIGNED_CHAR, unsigned char)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_DECIMALPORTABLE, RWDecimalPortable)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_RWDATETIME, RWDateTime)

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

RWDB_ASSOCIATE_TYPE(RWDB_TYPE_DATETIME, RWDBDateTime)

RW_RESTORE_DEPRECATED_WARNINGS
#endif

RWDB_ASSOCIATE_TYPE(RWDB_TYPE_DURATION, RWDBDuration)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_CSTRING, RWCString)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_BLOB, RWDBBlob)

RWDB_ASSOCIATE_TYPE(RWDB_TYPE_DATE, RWDate)

RWDB_ASSOCIATE_TYPE(RWDB_TYPE_USTRING, RWBasicUString)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_WCHAR_T, wchar_t)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_WSTRING, RWWString)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_MBSTRING, RWDBMBString)

RWDB_ASSOCIATE_TYPE(RWDB_TYPE_NATIVETYPE1, RWDBNativeType1)

RWDB_ASSOCIATE_TYPE(RWDB_TYPE_TIMETUPLE, RWTimeTuple)
RWDB_ASSOCIATE_TYPE(RWDB_TYPE_TIMETUPLEOFFSET, RWTimeTupleOffset)


///////////////////////////////////////////////////////////////////////////
//
// template class RWDBTBuffer<T>
//
// A templatized buffer of data.  Being a template, it offers an easier-
// to-use, richer interface than RWDBBuffer, at the price of possibly
// bloating one's code a little.
//
///////////////////////////////////////////////////////////////////////////
/**
 * \ingroup db_open_sql_group
 *
 * \brief
 * Template class that encapsulates a fixed-sized array of elements of type
 * T.
 *
 * Class RWDBTBuffer encapsulates a fixed-sized array of elements of type
 * \c T. Memory for these type \c T elements can be managed explicitly in
 * your applications, or by an RWDBTBuffer itself. In addition, this class
 * keeps a null indicator vector that indicates whether any item in the
 * array is \c NULL. The class also provides mechanisms for converting
 * buffer items to and from RWDBValue objects, if the chosen type \c T can
 * be converted.
 *
 * The parameter \c T represents the type of object to be inserted into the
 * array, either a class or a fundamental data type. The class \c T must
 * have:
 *
 * - Well-defined <em>copy semantics</em>, meaning <tt>T::T(const T&)</tt>
 * or the equivalent
 * - Well-defined <em>assignment semantics</em>, meaning
 * <tt>T::operator=(const T&)</tt> or the equivalent
 *
 * \note
 * To create an instance of RWDBTBuffer with the data type RWUString from
 * the Internationalization Module, you must include the header file
 * <tt><rw/db/tbuffer_ustr.h></tt> instead of <tt><rw/db/tbuffer.h></tt>.
 *
 * \synopsis
 * #include <rw/db/tbuffer.h>
 * \endsynopsis
 *
 * \example
 * Please see <b>Example 1</b> in the entry for RWDBOSql.
 * \endexample
 */
template<class T>
class RWDBTBuffer :  public RWDBBuffer
{
public:
    /**
     * Constructs an RWDBTBuffer with \a entries entries, and width
     * \a width. Allocates the array of element-type \c T of length
     * \a entries, whose memory is managed by self. \a entries must be
     * greater than or equal to \c 1. Allocates the array of null
     * indicators, of length \a entries, and sets them to \c false. Memory
     * for the null indicator array is managed by self. If \a width
     * <tt>= 0</tt>, the object uses the default width for type \c T.
     */
    RWDBTBuffer(RWSize_T entries = 1, RWSize_T width = 0)
        : RWDBBuffer(RWDBCTypeOf<T>(),
                     RWDBCTypeStockMemoryManager<T>::allocator,
                     RWDBCTypeStockMemoryManager<T>::deallocator,
                     entries.value())
    {
        // Width may be used as a hint...
        if (width.value() > 1) {
            RW_ASSERT(width.value() <= RW_LONG_MAX);
            this->column().storageLength(static_cast<long>(width.value()));
            this->column().paramType(RWDBColumn::inParameter);
        }
    }

    /**
     * Same as RWDBTBuffer(RWSize_T,RWSize_T), but the RWDBTBuffer uses
     * \a data and does \e not allocate or manage memory for the array.
     * Also, the null indicator array is set to \c false, and its memory is
     * managed by self.
     */
    RWDBTBuffer(T* data, RWSize_T entries = 1, RWSize_T width = 0)
        : RWDBBuffer(data, RWDBCTypeOf<T>(), entries.value())
    {
        // Width may be used as a hint...
        if (width.value() > 1) {
            RW_ASSERT(width.value() <= RW_LONG_MAX);
            this->column().storageLength(static_cast<long>(width.value()));
            this->column().paramType(RWDBColumn::inParameter);
        }
    }

    /**
     * Same as RWDBTBuffer(T*,RWSize_T,RWSize_T), but the RWDBTBuffer uses
     * the null indicator array passed as \a indicator, and does not
     * allocate or manage memory for the null indicator array.
     */
    RWDBTBuffer(T* data,
                RWDBNullIndicator* indicator,
                RWSize_T entries = 1,
                RWSize_T width = 0)
        : RWDBBuffer(data, indicator, RWDBCTypeOf<T>(), entries.value())
    {
        // Width may be used as a hint...
        if (width.value() > 1) {
            RW_ASSERT(width.value() <= RW_LONG_MAX);
            this->column().storageLength(static_cast<long>(width.value()));
            this->column().paramType(RWDBColumn::inParameter);
        }
    }

    /**
     * Deletes all data owned by self.
     */
    virtual ~RWDBTBuffer()
    {
    }

    /**
     * Performs a bounds check on \a index in debug mode. Returns the entry
     * at \a index in the array by value. The returned reference may be used
     * as an \c rvalue.
     */
    const T& operator[](size_t index) const
    {
        RW_ASSERT(index < this->entries_);
        return ((T*)(this->data_))[index * this->width_];
    }

    /**
     * Performs a bounds check on \a index in debug mode. Returns a
     * reference to the entry at \a index in the array. The returned
     * reference may be used as an \c lvalue. If using this method to assign
     * a new value to this entry, an explicit call to unsetNull(size_t)
     * using \a index is needed.
     */
    T& operator[](size_t index)
    {
        RW_ASSERT(index < this->entries_);
        return ((T*)(this->data_))[index * this->width_];
    }

    /**
     * Sets all the contents of the array to be \a newData. Unsets \c NULL
     * for each entry.
     */
    void setData(const T& newData)
    {
        // Variable-width buffers must be specialized to do this differently.
        RW_ASSERT(width_ == 1);
        unsetNull();
        for (size_t i = 0; i < this->entries_ ; i++) {
            ((T*)(this->data_))[i] = newData;
        }
    }

    /**
     * Sets the entry at \a index of the array to be \a newData. Unsets
     * \c NULL for the entry at \a index.
     */
    void setData(size_t index, const T& newData)
    {
        // Variable-width buffers must be specialized to do this differently.
        RW_ASSERT(width_ == 1);
        RW_ASSERT(index < this->entries_);
        unsetNull(index);
        ((T*)(this->data_))[index] = newData;
    }

    /**
     * Returns the number of entries.
     */
    size_t entries() const
    {
        return RWDBBuffer::entries();
    }

    /**
     * Changes the \c paramType attribute of self to \a newType. By default,
     * the \c paramType is set to \c RWDBColumn::inParameter. Note that this
     * does not change the definition of the parameter in the database.
     */
    void paramType(RWDBColumn::ParamType newType)
    {
        RWDBBuffer::paramType(newType);
    }

    /**
     * Returns a value indicating the parameter type of the column.
     */
    RWDBColumn::ParamType paramType() const
    {
        return RWDBBuffer::paramType();
    }

    /**
     * Performs a bounds check on \a index in debug mode. Returns \c true if
     * the entry at \a index is \c NULL.
     */
    bool isNull(size_t index) const
    {
        return RWDBBuffer::isNull(index);
    }

    /**
     * Sets \c NULL for all entries.
     */
    void setNull()
    {
        RWDBBuffer::setNull();
    }

    /**
     * Sets \c NULL for the entry at \a index.
     */
    void setNull(size_t index)
    {
        RWDBBuffer::setNull(index);
    }

    /**
     * Unsets \c NULL for all entries.
     */
    void unsetNull()
    {
        RWDBBuffer::unsetNull();
    }

    /**
     * Unsets \c NULL for the entry at \a index.
     */
    void unsetNull(size_t index)
    {
        RWDBBuffer::unsetNull(index);
    }

private:
    //Private copy constructor/assignment operator -- forbidden!
    RWDBTBuffer(const RWDBTBuffer<T>&);
    RWDBTBuffer<T>& operator=(const RWDBTBuffer<T>&);
};

///////////////////////////////////////////////////////////////////////////
//
// template class RWDBTBuffer<T>, specialization <char>
//
// Specialized on char to derive from the RWDBVariableWidthBuffer, who provides
// us with the width management functions we need.
//
///////////////////////////////////////////////////////////////////////////
RWDBTEMPLATESPECDECL
class RWDBTBuffer<char> :  public RWDBVariableWidthBuffer
{
public:
    RWDBTBuffer(RWSize_T entries = 1, RWSize_T width = 1,
                bool assumeDataIsNullTerminated = false)
        : RWDBVariableWidthBuffer(RWDBCTypeOf<char>(),
                                  RWDBCTypeStockMemoryManager<char>::allocator,
                                  RWDBCTypeStockMemoryManager<char>::deallocator,
                                  entries.value(), width.value(),
                                  assumeDataIsNullTerminated)
    {
    }

    RWDBTBuffer(char* data, RWSize_T entries = 1, RWSize_T width = 1,
                bool assumeDataIsNullTerminated = false)
        : RWDBVariableWidthBuffer(data, RWDBCTypeOf<char>(), entries.value(), width.value(),
                                  assumeDataIsNullTerminated)
    {
    }

    RWDBTBuffer(char* data,
                RWDBNullIndicator* indicator,
                RWSize_T entries = 1,
                RWSize_T width = 1, bool assumeDataIsNullTerminated = false)
        : RWDBVariableWidthBuffer(data, indicator, RWDBCTypeOf<char>(),
                                  entries.value(), width.value(),
                                  assumeDataIsNullTerminated)
    {
    }

    virtual ~RWDBTBuffer()
    {
    }

    const char& operator[](size_t index) const
    {
        RW_ASSERT(index < this->entries_);
        return ((char*)(this->data_))[index * this->width_];
    }

    char& operator[](size_t index)
    {
        RW_ASSERT(index < this->entries_);
        return ((char*)(this->data_))[index * this->width_];
    }

    void setData(const char& newData)
    {
        unsetNull();
        for (size_t i = 0; i < this->entries_ * width_ ; i++) {
            ((char*)(this->data_))[i] = newData;
        }
    }

    void setData(size_t index, const char& newData)
    {
        RW_ASSERT(index < this->entries_);
        unsetNull(index);
        for (size_t i = index * width_; i < (index + 1)*width_; i++) {
            ((char*)(this->data_))[i] = newData;
        }
    }

private:
    //Private copy constructor/assignment operator -- forbidden!
    RWDBTBuffer(const RWDBTBuffer<char>&);
    RWDBTBuffer<char>& operator=(const RWDBTBuffer<char>&);
};

///////////////////////////////////////////////////////////////////////////
//
// template class RWDBTBuffer<T>, specialization <unsigned char>
//
// Specialized on unsigned char to derive from the RWDBVariableWidthBuffer, who
// provides us with the width management functions we need.
//
///////////////////////////////////////////////////////////////////////////
RWDBTEMPLATESPECDECL
class RWDBTBuffer<unsigned char> :  public RWDBVariableWidthBuffer
{
public:
    RWDBTBuffer(RWSize_T entries = 1, RWSize_T width = 1)
        : RWDBVariableWidthBuffer(RWDBCTypeOf<unsigned char>(),
                                  RWDBCTypeStockMemoryManager<unsigned char>::allocator,
                                  RWDBCTypeStockMemoryManager<unsigned char>::deallocator,
                                  entries.value(), width.value())
    {
    }

    RWDBTBuffer(unsigned char* data, RWSize_T entries = 1, RWSize_T width = 1)
        : RWDBVariableWidthBuffer(data, RWDBCTypeOf<unsigned char>(), entries.value(), width.value())
    {
    }

    RWDBTBuffer(unsigned char* data,
                RWDBNullIndicator* indicator,
                RWSize_T entries = 1,
                RWSize_T width = 1)
        : RWDBVariableWidthBuffer(data, indicator, RWDBCTypeOf<unsigned char>(), entries.value(), width.value())
    {
    }

    virtual ~RWDBTBuffer()
    {
    }

    const unsigned char& operator[](size_t index) const
    {
        RW_ASSERT(index < this->entries_);
        return ((unsigned char*)(this->data_))[index * this->width_];
    }

    unsigned char& operator[](size_t index)
    {
        RW_ASSERT(index < this->entries_);
        return ((unsigned char*)(this->data_))[index * this->width_];
    }

    void setData(const unsigned char& newData)
    {
        unsetNull();
        for (size_t i = 0; i < this->entries_ * width_ ; i++) {
            ((unsigned char*)(this->data_))[i] = newData;
        }
    }

    void setData(size_t index, const unsigned char& newData)
    {
        RW_ASSERT(index < this->entries_);
        unsetNull(index);
        for (size_t i = index * width_; i < (index + 1)*width_; i++) {
            ((unsigned char*)(this->data_))[i] = newData;
        }
    }

private:
    //Private copy constructor/assignment operator -- forbidden!
    RWDBTBuffer(const RWDBTBuffer<unsigned char>&);
    RWDBTBuffer<unsigned char>& operator=(const RWDBTBuffer<unsigned char>&);
};

///////////////////////////////////////////////////////////////////////////
//
// template class RWDBTBuffer<T>, specialization <wchar_t>
//
// Specialized on wchar_t to derive from the RWDBVariableWidthBuffer, who
// provides us with the width management functions we need.
//
///////////////////////////////////////////////////////////////////////////
RWDBTEMPLATESPECDECL
class RWDBTBuffer<wchar_t> :  public RWDBVariableWidthBuffer
{
public:
    RWDBTBuffer(RWSize_T entries = 1, RWSize_T width = 1)
        : RWDBVariableWidthBuffer(RWDBCTypeOf<wchar_t>(),
                                  RWDBCTypeStockMemoryManager<wchar_t>::allocator,
                                  RWDBCTypeStockMemoryManager<wchar_t>::deallocator,
                                  entries.value(), width.value())
    {
    }

    RWDBTBuffer(wchar_t* data, RWSize_T entries = 1, RWSize_T width = 1)
        : RWDBVariableWidthBuffer(data, RWDBCTypeOf<wchar_t>(), entries.value(), width.value())
    {
    }

    RWDBTBuffer(wchar_t* data,
                RWDBNullIndicator* indicator,
                RWSize_T entries = 1,
                RWSize_T width = 1)
        : RWDBVariableWidthBuffer(data, indicator, RWDBCTypeOf<wchar_t>(), entries.value(), width.value())
    {
    }

    virtual ~RWDBTBuffer()
    {
    }

    const wchar_t& operator[](size_t index) const
    {
        RW_ASSERT(index < this->entries_);
        return ((wchar_t*)(this->data_))[index * this->width_];
    }

    wchar_t& operator[](size_t index)
    {
        RW_ASSERT(index < this->entries_);
        return ((wchar_t*)(this->data_))[index * this->width_];
    }

    void setData(const wchar_t& newData)
    {
        unsetNull();
        for (size_t i = 0; i < this->entries_ * width_ ; i++) {
            ((wchar_t*)(this->data_))[i] = newData;
        }
    }

    void setData(size_t index, const wchar_t& newData)
    {
        RW_ASSERT(index < this->entries_);
        unsetNull(index);
        for (size_t i = index * width_; i < (index + 1)*width_; i++) {
            ((wchar_t*)(this->data_))[i] = newData;
        }
    }

private:
    //Private copy constructor/assignment operator -- forbidden!
    RWDBTBuffer(const RWDBTBuffer<wchar_t>&);
    RWDBTBuffer<wchar_t>& operator=(const RWDBTBuffer<wchar_t>&);
};

#endif // __RWDB_TBUFFER_H__
