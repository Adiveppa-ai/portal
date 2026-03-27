/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTInputStreamBufferImp.cc#1 $
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

template <class InputStream, class FilteredInputStreamImp>
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::RWTInputStreamBufferImp(const InputStream& sourceStream)
    : FilteredInputStreamImp(sourceStream)
    , shouldFree_(true)
    , isFail_(false)
    , gbeg_(0)
    , gnext_(0)
    , gend_(0)
    , bufEnd_(0)
{

    if (!RW_STREAM_BUFFER_SIZE) {
        throw RWExternalStreamException("RWTInputStreamBufferImp::RWTInputStreamBufferImp(InputStream& sourceStream): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[RW_STREAM_BUFFER_SIZE];
    if (!tmp_) {
        throw RWExternalStreamException("RWTInputStreamBufferImp::RWTInputStreamBufferImp(InputStream& sourceStream): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setBufferEnd(tmp_ + RW_STREAM_BUFFER_SIZE);
    this->setg(tmp_, tmp_, tmp_);
}

template <class InputStream, class FilteredInputStreamImp>
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::RWTInputStreamBufferImp(const InputStream& sourceStream,
        RWSize bufSize)
    : FilteredInputStreamImp(sourceStream)
    , shouldFree_(true)
    , isFail_(false)
    , gbeg_(0)
    , gnext_(0)
    , gend_(0)
    , bufEnd_(0)
{
    if (!bufSize) {
        throw RWExternalStreamException("RWTInputStreamBufferImp::RWTInputStreamBufferImp(InputStream& sourceStream, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[bufSize];
    if (!tmp_) {
        throw RWExternalStreamException("RWTInputStreamBufferImp::RWTInputStreamBufferImp(InputStream& sourceStream, RWSize bufSize): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setBufferEnd(tmp_ + bufSize);
    this->setg(tmp_, tmp_, tmp_);
}

template <class InputStream, class FilteredInputStreamImp>
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::RWTInputStreamBufferImp(const InputStream& sourceStream,
        element_type* buffer,
        RWSize bufSize)
    : FilteredInputStreamImp(sourceStream)
    , shouldFree_(false)
    , isFail_(false)
    , gbeg_(0)
    , gnext_(0)
    , gend_(0)
    , bufEnd_(0)
{
    if (!bufSize) {
        throw RWExternalStreamException("RWTInputStreamBufferImp::RWTInputStreamBufferImp(InputStream& sourceStream, element_type* buffer, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    if (!buffer) {
        throw RWExternalStreamException("RWTInputStreamBufferImp::RWTInputStreamBufferImp(InputStream& sourceStream, element_type* buffer, RWSize bufSize): The buffer cannot be a nul pointer.", RWExternalStreamException::invalidParameter);
    }
    this->setBufferEnd(buffer + bufSize);
    this->setg(buffer, buffer, buffer);
}

template <class InputStream, class FilteredInputStreamImp>
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::~RWTInputStreamBufferImp()
{
    this->freeBuffer();
}

template <class InputStream, class FilteredInputStreamImp>
void
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::freeBuffer()
{
    if (shouldFree_ && this->eback()) {
        delete[] gbeg_;
    }
}

template <class InputStream, class FilteredInputStreamImp>
bool
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::underflow()
{

    if (this->gptr() != this->egptr()) {
        return true;
    }

    RWSize read_ = this->getSourceStream().read(this->eback(), static_cast<RWSize>(this->ebuf() - this->eback()));

    if (read_ > 0) {
        this->setg(this->eback(), this->eback(), this->eback() + read_);
    }
    else {
        return false;
    }

    return true;
}

template <class InputStream, class FilteredInputStreamImp>
RWSize
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::available() const
{
    return (static_cast<RWSize>(this->egptr() - this->gptr()) + this->getSourceStream().available());
}

template <class InputStream, class FilteredInputStreamImp>
RWSize
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::skip(RWSize numUnits)
{
    isFail_ = false;
    if (numUnits <= static_cast<RWSize>(this->egptr() - this->gptr())) {
        this->gbump(numUnits);
        return numUnits;
    }
    else {
        RWSize skiped_ = RWSize(this->egptr() - this->gptr());
        this->gbump(skiped_);
        skiped_ += this->getSourceStream().skip(numUnits - skiped_);
        if (skiped_ != numUnits) {
            isFail_ = true;
        }
        return skiped_;
    }
}

template <class InputStream, class FilteredInputStreamImp>
#if defined(__hpux)
typename InputStream::element_type
#else
typename RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::element_type
#endif
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::read()
{
    isFail_ = false;
    if (this->gptr() != this->egptr()) {
        this->gbump(1);
        return *(this->gptr() - 1);
    }
    else if (this->underflow()) {
        this->gbump(1);
        return *(this->gptr() - 1);
    }
    else {
        isFail_ = true;
        throw RWExternalStreamException("element_type RWTInputStreamBufferImp::read(): No element available",
                                        RWExternalStreamException::read);
    }
}

template <class InputStream, class FilteredInputStreamImp>
RWSize
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::read(element_type* array,
        RWSize num)
{
    isFail_ = false;
    size_t buf_size = num * sizeof(element_type);
    if (num <= static_cast<RWSize>(this->egptr() - this->gptr())) {
        rw_memcpy_s(array, buf_size, this->gptr(), buf_size);
        this->gbump(num);
        return num;
    }
    else {
        RWSize read_ = RWSize(this->egptr() - this->gptr());
        size_t readSize = read_ * sizeof(element_type);
        rw_memcpy_s(array, buf_size, this->gptr(), readSize);
        this->gbump(read_);
        // we still need to read some more, but less than the content of one full
        // buffer
        if ((num - read_) < static_cast<RWSize>(this->ebuf() - this->eback())) {
            if (this->underflow()) {
                // we have read enough elements to satisfy the request
                if ((num - read_) <= static_cast<RWSize>(this->egptr() - this->gptr())) {
                    rw_memcpy_s(array + read_, buf_size - readSize, this->gptr(), (num - read_) * sizeof(element_type));
                    this->gbump(num - read_);
                    return num;
                }
                // we couldn't read enough elements
                else {
                    rw_memcpy_s(array + read_, buf_size - readSize, this->gptr(), (this->egptr() - this->gptr()) * sizeof(element_type));
                    read_ += static_cast<RWSize>(this->egptr() - this->gptr());
                    this->gbump(RWSize(this->egptr() - this->gptr()));
                    isFail_ = true;
                    return read_;
                }
            } // end if(underflow())
            isFail_ = true;
            return read_;
        }
        // we need to read more than the content of one buffer, forget about the
        // buffering
        else {
            read_ += this->getSourceStream().read(array + read_, num - read_);
            if (read_ != num) {
                isFail_ = true;
            }
            return read_;
        }
    } // end else we have enough in the current buffer
}

template <class InputStream, class FilteredInputStreamImp>
RWSize
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::readUntil(element_type* array,
        RWSize maxSize,
        element_type delim)
{
    element_type tmp = element_type(~delim);
    RWSize i;
    isFail_ = false;
    for (i = 0; i < maxSize; i++) {
        if (this->gptr() != this->egptr()) {
            tmp = *this->gptr();
            this->gbump(1);
        }
        else {
            if (this->underflow()) {
                tmp = *this->gptr();
                this->gbump(1);
            }
            else {
                isFail_ = true;
                return i;
            }
        } // end else if(this->gptr()!=this->egptr())
        if (tmp == delim) {
            break;
        }
        else {
            array[i] = tmp;
        }
    } // end for
    if (tmp != delim) {
        isFail_ = true;
    }
    return i;
}

template <class InputStream, class FilteredInputStreamImp>
bool
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::isFail() const
{
    return isFail_;
}

template <class InputStream, class FilteredInputStreamImp>
bool
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::isEof() const
{
    if (this->egptr() != this->gptr()) {
        return false;
    }
    else {
        return this->getSourceStream().isEof();
    }
}

template <class InputStream, class FilteredInputStreamImp>
bool
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::isBad() const
{
    if (this->egptr() != this->gptr()) {
        return false;
    }
    else {
        return this->isFail();
    }
}

template <class InputStream, class FilteredInputStreamImp>
bool
RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>::isGood() const
{
    return !(this->isFail() || this->isBad());
}
