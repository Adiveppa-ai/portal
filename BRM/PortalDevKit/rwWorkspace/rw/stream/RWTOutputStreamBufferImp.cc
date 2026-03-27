/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTOutputStreamBufferImp.cc#1 $
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

#include <rw/tools/string.h>

template <class OutputStream, class FilteredOutputStreamImp>
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::RWTOutputStreamBufferImp(const OutputStream& sinkStream)
    : FilteredOutputStreamImp(sinkStream)
    , shouldFree_(true)
    , pbeg_(0)
    , pnext_(0)
    , pend_(0)
{
    if (!RW_STREAM_BUFFER_SIZE) {
        throw RWExternalStreamException("RWTOutputStreamBufferImp::RWTOutputStreamBufferImp(const OutputStream& sinkStream): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[RW_STREAM_BUFFER_SIZE];
    if (!tmp_) {
        throw RWExternalStreamException("RWTOutputStreamBufferImp::RWTOutputStreamBufferImp(const OutputStream& sinkStream): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setp(tmp_, tmp_ + RW_STREAM_BUFFER_SIZE);
}

template <class OutputStream, class FilteredOutputStreamImp>
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::RWTOutputStreamBufferImp(const OutputStream& sinkStream,
        RWSize bufSize)
    : FilteredOutputStreamImp(sinkStream)
    , shouldFree_(true)
    , pbeg_(0)
    , pnext_(0)
    , pend_(0)
{
    if (!bufSize) {
        throw RWExternalStreamException("RWTOutputStreamBufferImp::RWTOutputStreamBufferImp(const OutputStream& sinkStream, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[bufSize];
    if (!tmp_) {
        throw RWExternalStreamException("RWTOutputStreamBufferImp::RWTOutputStreamBufferImp(const OutputStream& sinkStream, RWSize bufSize): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setp(tmp_, tmp_ + bufSize);
}

template <class OutputStream, class FilteredOutputStreamImp>
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::RWTOutputStreamBufferImp(const OutputStream& sinkStream,
        element_type* buffer,
        RWSize bufSize)
    : FilteredOutputStreamImp(sinkStream)
    , shouldFree_(false)
    , pbeg_(0)
    , pnext_(0)
    , pend_(0)
{
    if (!bufSize) {
        throw RWExternalStreamException("RWTOutputStreamBufferImp::RWTOutputStreamBufferImp(const OutputStream& sinkStream, element_type* buffer, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    if (!buffer) {
        throw RWExternalStreamException("RWTOutputStreamBufferImp::RWTOutputStreamBufferImp(const OutputStream& sinkStream, element_type* buffer, RWSize bufSize): The buffer cannot be a nul pointer.", RWExternalStreamException::invalidParameter);
    }
    this->setp(buffer, buffer + bufSize);
}

template <class OutputStream, class FilteredOutputStreamImp>
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::~RWTOutputStreamBufferImp()
{
    this->flush();
    this->freeBuffer();
}

template <class OutputStream, class FilteredOutputStreamImp>
void
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::freeBuffer()
{
    if (shouldFree_ && this->pbase()) {
        delete[] pbeg_;
    }
}

template <class OutputStream, class FilteredOutputStreamImp>
void
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::flush()
{
    if (this->pptr() - this->pbase()) {
        this->getSinkStream().write(this->pbase(),
                                    static_cast<RWSize>(this->pptr() - this->pbase()));
        this->setp(this->pbase(), this->epptr());
    }
    this->getSinkStream().flush();
}

template <class OutputStream, class FilteredOutputStreamImp>
void
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::close()
{
    this->flush();
    this->getSinkStream().close();
}

template <class OutputStream, class FilteredOutputStreamImp>
void
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::write(element_type value)
{
    if (this->pptr() != this->epptr()) {
        *this->pptr() = value;
        this->pbump(1);
    }
    else {
        this->flush();
        *this->pptr() = value;
        this->pbump(1);
    }
}

template <class OutputStream, class FilteredOutputStreamImp>
void
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::write(const element_type* array,
        RWSize numElements)
{
    size_t buf_size = (this->epptr() - this->pptr()) * sizeof(element_type);
    if (static_cast<RWSize>(this->epptr() - this->pptr()) >= numElements) {
        // we have enough space in the buffer to insert the array of elements
        rw_memcpy_s(this->pptr(), buf_size, array, numElements * sizeof(element_type));
        this->pbump(numElements);
    }
    else {
        if (numElements >= static_cast<RWSize>(this->epptr() - this->pbase())) {
            // the array of elements is bigger than the buffer, therefore
            // forget about putting it into the buffer
            this->flush();
            this->getSinkStream().write(array, numElements);
        }
        else {
            // fill the buffer then flush, then insert the rest of the array
            RWSize freeSpaceInBuffer = static_cast<RWSize>(this->epptr() - this->pptr());
            rw_memcpy_s(this->pptr(), buf_size, array, freeSpaceInBuffer * sizeof(element_type));
            this->pbump(freeSpaceInBuffer);
            this->flush();
            buf_size = (this->epptr() - this->pptr()) * sizeof(element_type);
            rw_memcpy_s(this->pptr(), buf_size, array + freeSpaceInBuffer, (numElements - freeSpaceInBuffer) * sizeof(element_type));
            this->pbump(numElements - freeSpaceInBuffer);
        } // end else
    } // end else
}
