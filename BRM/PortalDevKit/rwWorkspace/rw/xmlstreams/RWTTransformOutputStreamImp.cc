/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTTransformOutputStreamImp.cc#1 $
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

#include <rw/stream/RWTStreambufToByteCharOutputStream.h>
#include <rw/tools/string.h>

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::RWTTransformOutputStreamImp(const OutputStream& sinkStream,
        Transform transform)
    : FilteredOutputStreamImp(sinkStream)
    , shouldFree_(true)
    , pbeg_(0)
    , pnext_(0)
    , pend_(0)
    , transform_(transform)
{

    if (!RW_STREAM_BUFFER_SIZE) {
        throw RWExternalStreamException("RWTTransformOutputStreamImp::RWTTransformOutputStreamImp(const OutputStream& sinkStream): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[RW_STREAM_BUFFER_SIZE];
    if (!tmp_) {
        throw RWExternalStreamException("RWTTransformOutputStreamImp::RWTTransformOutputStreamImp(const OutputStream& sinkStream): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setp(tmp_, tmp_ + RW_STREAM_BUFFER_SIZE);
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::RWTTransformOutputStreamImp(const OutputStream& sinkStream,
        Transform transform,
        RWSize bufSize)
    : FilteredOutputStreamImp(sinkStream)
    , shouldFree_(true)
    , pbeg_(0)
    , pnext_(0)
    , pend_(0)
    , transform_(transform)
{

    if (!bufSize) {
        throw RWExternalStreamException("RWTTransformOutputStreamImp::RWTTransformOutputStreamImp(const OutputStream& sinkStream, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[bufSize];
    if (!tmp_) {
        throw RWExternalStreamException("RWTTransformOutputStreamImp::RWTTransformOutputStreamImp(const OutputStream& sinkStream, RWSize bufSize): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setp(tmp_, tmp_ + bufSize);
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::RWTTransformOutputStreamImp(const OutputStream& sinkStream,
        Transform transform,
        element_type* buffer,
        RWSize bufSize)
    : FilteredOutputStreamImp(sinkStream)
    , shouldFree_(false)
    , pbeg_(0)
    , pnext_(0)
    , pend_(0)
    , transform_(transform)
{

    if (!bufSize) {
        throw RWExternalStreamException("RWTTransformOutputStreamImp::RWTTransformOutputStreamImp(const OutputStream& sinkStream, element_type* buffer, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    if (!buffer) {
        throw RWExternalStreamException("RWTTransformOutputStreamImp::RWTTransformOutputStreamImp(const OutputStream& sinkStream, element_type* buffer, RWSize bufSize): The buffer cannot be a nul pointer.", RWExternalStreamException::invalidParameter);
    }
    this->setp(buffer, buffer + bufSize);
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::~RWTTransformOutputStreamImp()
{
    this->flush();
    this->freeBuffer();
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
void
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::freeBuffer()
{
    if (shouldFree_ && this->pbase()) {
        delete[] pbeg_;
    }
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
void
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::flush()
{
    if (this->pptr() - this->pbase()) {

        transform();

        this->setp(this->pbase(), this->epptr());
    }

    this->getSinkStream().flush();
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
void
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::transform()
{
    const string_type tmp(this->pbase(), static_cast<typename string_type::size_type>(this->pptr() - this->pbase()));
    std::basic_istringstream<element_type, std::char_traits<element_type>, std::allocator<element_type> > in(tmp);
    RWTStreambufToByteCharOutputStream<OutputStream> sb(this->getSinkStream());
    std::basic_ostream<element_type, std::char_traits<element_type> > osb(&sb);
    transform_.transform(in, osb);
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
void
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::close()
{
    this->flush();
    this->getSinkStream().close();
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
void
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::setBuffer(RWSize bufSize)
{
    RWSize curSize = static_cast<RWSize>(this->pptr() - this->pbase());
    element_type* prevBuffer = pbeg_;
    element_type* tmp_ = new element_type[bufSize];
    if (!tmp_) {
        throw RWExternalStreamException("RWTTransformOutputStreamImp::RWTTransformOutputStreamImp(const OutputStream& sinkStream, RWSize bufSize): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setp(tmp_, tmp_ + bufSize);
    if (prevBuffer) {
        rw_memcpy_s(this->pptr(), bufSize, prevBuffer, curSize * sizeof(element_type));
        pbump(curSize);
        if (shouldFree_) {
            delete[] prevBuffer;
        }
    }
}


template <class OutputStream, class FilteredOutputStreamImp, class Transform>
void
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::write(element_type value)
{
    if (this->pptr() != this->epptr()) {
        *this->pptr() = value;
        this->pbump(1);
    }
    else {
        setBuffer(static_cast<RWSize>(this->pptr() - this->pbase()) + RW_STREAM_BUFFER_SIZE);
        *this->pptr() = value;
        this->pbump(1);
    }
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
void
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::write(const element_type* array,
        RWSize numElements)
{
    if (static_cast<RWSize>(this->epptr() - this->pptr()) >= numElements) {
        // we have enough space in the buffer to insert the array of elements
        RWSize bufSize = static_cast<RWSize>((this->epptr() - this->pptr()) * sizeof(element_type));
        rw_memcpy_s(this->pptr(), bufSize, array, numElements * sizeof(element_type));
        this->pbump(numElements);
    }
    else {
        // resize buffer
        RWSize curSize = static_cast<RWSize>(this->pptr() - this->pbase());
        RWSize newSize = static_cast<RWSize>(curSize + numElements * sizeof(element_type) + RW_STREAM_BUFFER_SIZE);
        setBuffer(newSize);
        rw_memcpy_s(this->pptr(), newSize, array, numElements * sizeof(element_type));
        this->pbump(numElements);
    } // end else
}
