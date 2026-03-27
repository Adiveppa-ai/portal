/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTTransformInputStreamImp.cc#1 $
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

#include <rw/stream/RWExternalStreamException.h>
#include <rw/stream/RWTStreambufFromByteCharInputStream.h>
#include <rw/tools/string.h>

template <class InputStream, class FilteredInputStreamImp, class Transform>
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::RWTTransformInputStreamImp(const InputStream& sourceStream,
        Transform transform)
    : FilteredInputStreamImp(sourceStream)
    , shouldFree_(true)
    , isFail_(false)
    , gbeg_(0)
    , gnext_(0)
    , gend_(0)
    , bufEnd_(0)
    , transform_(transform)
{

    if (!RW_STREAM_BUFFER_SIZE) {
        throw RWExternalStreamException("RWTTransformInputStreamImp::RWTTransformInputStreamImp(InputStream& sourceStream): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[RW_STREAM_BUFFER_SIZE];
    if (!tmp_) {
        throw RWExternalStreamException("RWTTransformInputStreamImp::RWTTransformInputStreamImp(InputStream& sourceStream): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setBufferEnd(tmp_ + RW_STREAM_BUFFER_SIZE);
    this->setg(tmp_, tmp_, tmp_);
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::RWTTransformInputStreamImp(const InputStream& sourceStream,
        Transform transform,
        RWSize bufSize)
    : FilteredInputStreamImp(sourceStream)
    , shouldFree_(true)
    , isFail_(false)
    , gbeg_(0)
    , gnext_(0)
    , gend_(0)
    , bufEnd_(0)
    , transform_(transform)
{

    if (!bufSize) {
        throw RWExternalStreamException("RWTTransformInputStreamImp::RWTTransformInputStreamImp(InputStream& sourceStream, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[bufSize];
    if (!tmp_) {
        throw RWExternalStreamException("RWTTransformInputStreamImp::RWTTransformInputStreamImp(InputStream& sourceStream, RWSize bufSize): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setBufferEnd(tmp_ + bufSize);
    this->setg(tmp_, tmp_, tmp_);
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::RWTTransformInputStreamImp(const InputStream& sourceStream,
        Transform transform,
        element_type* buffer,
        RWSize bufSize)
    : FilteredInputStreamImp(sourceStream)
    , shouldFree_(false)
    , isFail_(false)
    , gbeg_(0)
    , gnext_(0)
    , gend_(0)
    , bufEnd_(0)
    , transform_(transform)
{

    if (!bufSize) {
        throw RWExternalStreamException("RWTTransformInputStreamImp::RWTTransformInputStreamImp(InputStream& sourceStream, element_type* buffer, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    if (!buffer) {
        throw RWExternalStreamException("RWTTransformInputStreamImp::RWTTransformInputStreamImp(InputStream& sourceStream, element_type* buffer, RWSize bufSize): The buffer cannot be a nul pointer.", RWExternalStreamException::invalidParameter);
    }
    this->setBufferEnd(buffer + bufSize);
    this->setg(buffer, buffer, buffer);
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::~RWTTransformInputStreamImp()
{
    this->freeBuffer();
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
void
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::freeBuffer()
{
    if (shouldFree_ && this->eback()) {
        delete[] gbeg_;
    }
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
bool
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::underflow()
{
    if (this->gptr() != this->egptr()) {
        return true;
    }

    std::basic_ostringstream<element_type, std::char_traits<element_type>, std::allocator<element_type> > sbuffer;
    transform(sbuffer);

    typename std::basic_string<element_type>::size_type len = sbuffer.str().length();
    if (len > 0) {
        element_type* newbuf = new element_type[len];
        rw_memcpy_s(newbuf, len, sbuffer.str().data(), len);

        freeBuffer();

        this->setg(newbuf, newbuf, newbuf + len);
        shouldFree_ = true;
    }
    else {
        return false;
    }

    return true;
}


template <class InputStream, class FilteredInputStreamImp, class Transform>
void
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::transform(std::basic_ostringstream<element_type, std::char_traits<element_type>, std::allocator<element_type> >& sbuffer)
{
    if (!this->getSourceStream().isGood() || this->getSourceStream().isEof()) {
        return;
    }
    RWTStreambufFromByteCharInputStream<InputStream> sb(this->getSourceStream());
    std::basic_istream<char, std::char_traits<char> > is(&sb);
    transform_.transform(is, sbuffer);
}


template <class InputStream, class FilteredInputStreamImp, class Transform>
RWSize
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::available() const
{
    return (static_cast<RWSize>(this->egptr() - this->gptr()) + this->getSourceStream().available());
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
RWSize
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::skip(RWSize numUnits)
{
    isFail_ = false;
    if (numUnits <= static_cast<RWSize>(this->egptr() - this->gptr())) {
        this->gbump(numUnits);
        return numUnits;
    }
    else {
        RWSize skiped_ = static_cast<RWSize>(this->egptr() - this->gptr());
        this->gbump(skiped_);
        skiped_ += this->getSourceStream().skip(numUnits - skiped_);
        if (skiped_ != numUnits) {
            isFail_ = true;
        }
        return skiped_;
    }
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
#if defined(__hpux)
typename InputStream::element_type
#else
typename RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::element_type
#endif
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::read()
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
        throw RWExternalStreamException("element_type RWTTransformInputStreamImp::read(): No element available",
                                        RWExternalStreamException::read);
    }
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
RWSize
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::read(element_type* array,
        RWSize num)
{
    isFail_ = false;
    RWSize arraySize = static_cast<RWSize>(num * sizeof(element_type));
    if (num <= static_cast<RWSize>(this->egptr() - this->gptr())) {
        rw_memcpy_s(array, arraySize, this->gptr(), num * sizeof(element_type));
        this->gbump(num);
        return num;
    }
    else {
        RWSize read_ = static_cast<RWSize>(this->egptr() - this->gptr());
        RWSize readSize = static_cast<RWSize>(read_ * sizeof(element_type));
        rw_memcpy_s(array, arraySize, this->gptr(), readSize);
        this->gbump(read_);
        // we still need to read some more, but less than the content of one full
        // buffer
        if ((num - read_) < static_cast<RWSize>(this->ebuf() - this->eback())) {
            if (this->underflow()) {
                // we have read enough elements to satisfy the request
                if ((num - read_) <= static_cast<RWSize>(this->egptr() - this->gptr())) {
                    rw_memcpy_s(array + read_, arraySize - readSize, this->gptr(), (num - read_)*sizeof(element_type));
                    this->gbump(num - read_);
                    return num;
                }
                // we couldn't read enough elements
                else {
                    rw_memcpy_s(array + read_, arraySize - readSize, this->gptr(), (this->egptr() - this->gptr())*sizeof(element_type));
                    read_ += static_cast<RWSize>(this->egptr() - this->gptr());
                    this->gbump(static_cast<RWSize>(this->egptr() - this->gptr()));
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

template <class InputStream, class FilteredInputStreamImp, class Transform>
RWSize
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::readUntil(element_type* array,
        RWSize maxSize,
        element_type delim)
{
    element_type tmp = element_type();
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

template <class InputStream, class FilteredInputStreamImp, class Transform>
bool
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::isFail() const
{
    return isFail_;
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
bool
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::isEof() const
{
    if (this->egptr() != this->gptr()) {
        return false;
    }
    else {
        return this->getSourceStream().isEof();
    }
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
bool
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::isBad() const
{
    if (this->egptr() != this->gptr()) {
        return false;
    }
    else {
        return this->isFail();
    }
}

template <class InputStream, class FilteredInputStreamImp, class Transform>
bool
RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>::isGood() const
{
    return !(this->isFail() || this->isBad());
}
