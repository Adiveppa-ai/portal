#ifndef rw_xmlabstractions_RWXmlStringWriter_h_
#define rw_xmlabstractions_RWXmlStringWriter_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlabstractions/RWXmlStringWriter.h#1 $
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

#include <rw/xmlabstractions/RWXmlWriter.h>
#include <rw/xmlabstractions/pkgdefs.h>
#include <rw/tools/string.h>
#include <string.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

static const size_t RW_STR_WRITER_BUFFER_SIZE = 4096;

/*
 * RWXmlStringWriter is a undocumented utility class that provides a string
 * buffer based implementation of the RWXmlWriter interface to aid in writing
 * XML content to a string.
 */
class RW_XMLABSTRACTIONS_GLOBAL RWXmlStringWriter : public RWXmlWriter
{
public:
    RWXmlStringWriter(size_t = RW_STR_WRITER_BUFFER_SIZE);
    virtual ~RWXmlStringWriter();

    inline size_t    getLength() const;
    inline size_t    getBufferLength() const;

    inline RWCString getString() const;

    //Flush is a no-op for string writer.
    inline void     flush();

    inline void     writeToSink(const RWCString&);
    inline void     writeToSink(const char*, size_t);
    inline void     writeToSink(char);

    inline void     removeLastCharFromSink(char);

    // allowing for the resize of the buffer
    inline void     resize(size_t);

private:
    RWTScopedPointer<char[]> data_;
    size_t  position_;
    size_t  length_;

}; //RWXmlStringWriter

////////////////////////////////////////////////////////////////////////////
//
// Inline Definitions
//
////////////////////////////////////////////////////////////////////////////

inline void
RWXmlStringWriter::flush()
{
}

inline void
RWXmlStringWriter::writeToSink(const RWCString& text)
{
    writeToSink(text.data(), text.length());
}

inline void
RWXmlStringWriter::writeToSink(const char* str, size_t len)
{
    // empty/null strings handling
    if (str == 0 || len == 0) {
        return;
    }

    if (len + position_ <= length_) {
        rw_memcpy_s(data_.get() + position_, length_ - position_, str, len);
        position_ += len;
    }
    else {
        size_t newsize = (len + length_) * 2;
        newsize =
            newsize > RW_STR_WRITER_BUFFER_SIZE ?
            newsize :
            RW_STR_WRITER_BUFFER_SIZE;

        resize(newsize);

        rw_memcpy_s(data_.get() + position_, length_ - position_, str, len);
        position_ += len;
    }
}

inline void
RWXmlStringWriter::writeToSink(char c)
{
    if (position_ + 1 <= length_) {
        data_[position_++] = c;
    }
    else {
        size_t newsize = length_ * 2;
        newsize =
            newsize > RW_STR_WRITER_BUFFER_SIZE ?
            newsize :
            RW_STR_WRITER_BUFFER_SIZE;

        resize(newsize);
        data_[position_++] = c;
    }
}

inline void
RWXmlStringWriter::removeLastCharFromSink(char c)
{
    if (position_ > 0) {
        if (data_[position_ - 1] == c) {
            position_--;
        }
    }
}

inline size_t
RWXmlStringWriter::getLength() const
{
    return position_;
}

inline size_t
RWXmlStringWriter::getBufferLength() const
{
    return length_;
}

inline RWCString
RWXmlStringWriter::getString() const
{
    if (data_) {
        return RWCString(data_.get(), position_);
    }
    else {
        return RWCString();
    }
}

inline void
RWXmlStringWriter::resize(size_t newsize)
{
    // resize to zero, wipes out the buffer
    if (newsize == 0) {
        data_.reset(0);
        length_   = 0;
        position_ = 0;

        return;
    }

    RWTScopedPointer<char[]> data(new char [newsize]);

    // copy the min of new size and data_'s position_
    if (data_ && position_)
        rw_memcpy_s(data.get(), newsize, data_.get(),
                    newsize < position_ ? newsize : position_);

    // adjust members
    position_ = newsize < position_ ? newsize : position_;
    length_   = newsize;
    rw_swap(data_, data);
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_xmlabstractions_RWXmlStringWriter_h_
