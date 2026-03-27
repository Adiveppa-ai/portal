/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTParsedTransformInputStreamImp.cc#1 $
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

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::RWTParsedTransformInputStreamImp(const InputStream& sourceStream,
        Transform transform)
    : FilteredInputStreamImp(sourceStream)
    , shouldFree_(true)
    , isFail_(false)
    , gbeg_(0)
    , gnext_(0)
    , gend_(0)
    , bufEnd_(0)
    , putBack_(false)
    , transform_(transform)
{

    if (!RW_STREAM_BUFFER_SIZE) {
        throw RWExternalStreamException("RWTParsedTransformInputStreamImp::RWTParsedTransformInputStreamImp(InputStream& sourceStream): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[RW_STREAM_BUFFER_SIZE];
    if (!tmp_) {
        throw RWExternalStreamException("RWTParsedTransformInputStreamImp::RWTParsedTransformInputStreamImp(InputStream& sourceStream): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setBufferEnd(tmp_ + RW_STREAM_BUFFER_SIZE);
    this->setg(tmp_, tmp_, tmp_);
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::RWTParsedTransformInputStreamImp(const InputStream& sourceStream,
        Transform transform,
        RWSize bufSize)
    : FilteredInputStreamImp(sourceStream)
    , shouldFree_(true)
    , isFail_(false)
    , gbeg_(0)
    , gnext_(0)
    , gend_(0)
    , bufEnd_(0)
    , putBack_(false)
    , transform_(transform)
{

    if (!bufSize) {
        throw RWExternalStreamException("RWTParsedTransformInputStreamImp::RWTParsedTransformInputStreamImp(InputStream& sourceStream, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[bufSize];
    if (!tmp_) {
        throw RWExternalStreamException("RWTParsedTransformInputStreamImp::RWTParsedTransformInputStreamImp(InputStream& sourceStream, RWSize bufSize): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setBufferEnd(tmp_ + bufSize);
    this->setg(tmp_, tmp_, tmp_);
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::RWTParsedTransformInputStreamImp(const InputStream& sourceStream,
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
    , putBack_(false)
    , transform_(transform)
{

    if (!bufSize) {
        throw RWExternalStreamException("RWTParsedTransformInputStreamImp::RWTParsedTransformInputStreamImp(InputStream& sourceStream, element_type* buffer, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    if (!buffer) {
        throw RWExternalStreamException("RWTParsedTransformInputStreamImp::RWTParsedTransformInputStreamImp(InputStream& sourceStream, element_type* buffer, RWSize bufSize): The buffer cannot be a nul pointer.", RWExternalStreamException::invalidParameter);
    }
    this->setBufferEnd(buffer + bufSize);
    this->setg(buffer, buffer, buffer);
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::~RWTParsedTransformInputStreamImp()
{
    this->freeBuffer();
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
void
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::freeBuffer()
{
    if (shouldFree_ && this->eback()) {
        delete[] gbeg_;
    }
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
bool
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::underflow()
{

    if (this->gptr() != this->egptr()) {
        return true;
    }

    freeBuffer();
    tbuffer_.resize(0);
    this->setg(const_cast<element_type*>(tbuffer_.data()), const_cast<element_type*>(tbuffer_.data()), const_cast<element_type*>(tbuffer_.data()));
    shouldFree_ = false;

    transform();

    if (tbuffer_.length() > 0) {
        freeBuffer();
        this->setg(const_cast<element_type*>(tbuffer_.data()), const_cast<element_type*>(tbuffer_.data()), const_cast<element_type*>(tbuffer_.data() + tbuffer_.length()));
        shouldFree_ = false;
    }
    else {
        return false;
    }

    return true;
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
typename RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::element_type
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::readOne()
{
    if (putBack_) {
        putBack_ = false;
        return putBackChar_;
    }
    else if (this->getSourceStream().isGood() && !this->getSourceStream().isEof()) {
        return this->getSourceStream().read();
    }
    return -1;
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
void
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::putBack(element_type cur)
{
    putBack_ = true;
    putBackChar_ = cur;
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
void
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::transform()
{
    if (!this->getSourceStream().isGood() || this->getSourceStream().isEof()) {
        return;
    }


    element_type cur = readOne();
    string_type  notXml;
    notXml += cur;
    while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && cur != Traits::lt) {
        cur = readOne();
        notXml += cur;
    }
    RWXmlStreamElement root;
    if (!this->getSourceStream().isGood() || this->getSourceStream().isEof()) {
        root.setValue(notXml);
        root.setName(RWCString("rw:primitive"));
    }
    else {
        root = readNextElement(cur, RWXmlStreamElement());
    }
    std::basic_ostringstream<element_type> buffer;
    transform_.transform(root);
    root.write(buffer);
    tbuffer_ = buffer.str();
}


template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
RWXmlStreamElement RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::readNextElement(element_type& cur, const RWXmlStreamElement& parent)
{
    string_type token;
    while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && cur != Traits::lt) {
        cur = readOne();
    }
    cur = readOne();
    if (cur == Traits::bang || cur == Traits::question) {
        string_type dummy;
        cur = readWholeName(cur, dummy);
        return readNextElement(cur, parent);
    }
    cur = readToken(cur, token);
    RWXmlStreamElement element(parent.getNamespaces());
    cur = readAttributes(cur, element);
    size_t pos = token.firstOf(Traits::colon);
    string_type prefix;
    if (pos != RW_NPOS) {
        prefix = token(0, pos);
    }
    else {
        prefix = token;
    }
    if (pos != RW_NPOS) {
        element.setName(RWXmlName(token(pos + 1, token.length() - (pos + 1)), element.findNamespaceURI(prefix)));
    }
    else {
        element.setName(RWXmlName(token));
    }
    cur = readValue(cur, element);
    return element;
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
typename RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::element_type
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::readToken(element_type cur, string_type& token)
{
    while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && (cur == Traits::space || cur == Traits::newline || cur == Traits::tab)) {
        cur = readOne();
    }
    while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && cur != Traits::lt && cur != Traits::gt && cur != Traits::space && cur != Traits::newline && cur != Traits::tab && cur != Traits::equal && cur != Traits::slash) {
        token += cur;
        cur = readOne();
    }
    return cur;
}


template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
typename RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::element_type
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::readToClose(element_type cur, string_type& token)
{
    while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && cur != Traits::lt) {
        token += cur;
        cur = readOne();
    }
    while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && cur != Traits::gt) {
        cur = readOne();
    }
    try {
        cur = readOne();
    }
    catch (...) {}
    return cur;
}


template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
typename RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::element_type
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::readWholeName(element_type cur, string_type& token)
{
    while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && cur != Traits::gt) {
        token += cur;
        cur = readOne();
    }

    return cur;
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
typename RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::element_type
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::readAttributeValue(element_type cur, string_type& token)
{
    while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && (cur == Traits::space || cur == Traits::newline || cur == Traits::tab)) {
        cur = readOne();
    }
    element_type delim = cur;
    if (delim != Traits::quote && delim != Traits::apostrophe) {
        return readToken(cur, token);
    }
    token += delim;
    cur = readOne();
    while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && cur != delim) {
        token += cur;
        cur = readOne();
    }
    token += cur;
    return readOne();
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
typename RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::element_type
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::readAttribute(element_type cur, string_type& token)
{
    string_type temp;
    cur = readToken(cur, token);
    if (this->getSourceStream().isGood() && token.length() != 0) {
        cur = readToken(cur, temp);
        token += cur;
        cur = readOne();
        cur = readAttributeValue(cur, temp);
        token += temp;
    }
    return cur;
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
typename RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::element_type
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::readAttributes(element_type cur, RWXmlStreamElement& element)
{
    string_type token;
    cur = readAttribute(cur, token);
    while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && token.length() != 0) {
        size_t pos = token.firstOf(Traits::equal);
        if (pos == RW_NPOS) {
            break;
        }
        string_type prefix = token(0, pos);
        size_t namepos = prefix.firstOf(Traits::colon);
        RWXmlAttribute a;
        if (namepos != RW_NPOS) {
            string_type nm = prefix(0, namepos);
            string_type value = token.length() > pos + 3 ? token(pos + 2, token.length() - (pos + 3)) : string_type();
            string_type name = prefix(namepos + 1, prefix.length() - (namepos + 1));
            element.addAttribute(RWXmlAttribute(RWXmlName(name, element.findNamespaceURI(nm)), value));
            if (nm == Traits::namespacePrefix) {
                element.addNamespace(name, RWXmlNamespace(name, value));
            }
        }
        else {
            string_type value = token(pos + 2, token.length() > pos + 3 ? token.length() - (pos + 3) : 0);
            element.addAttribute(RWXmlAttribute(RWXmlName(prefix), value));
            if (prefix == Traits::namespacePrefix) {
                element.addNamespace(string_type(), RWXmlNamespace(string_type(), value));
            }
        }
        token.resize(0);
        cur = readAttribute(cur, token);
    }
    element.resolveNamespaces();

    if (cur != Traits::slash) {
        cur =  readOne();
    }
    return cur;
}


template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
typename RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::element_type
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::readValue(element_type cur, RWXmlStreamElement& element)
{
    string_type token;
    cur = readToken(cur, token);
    if (token.length() == 0 && this->getSourceStream().isGood() && (cur == Traits::lt || cur == Traits::slash)) {
        // Either an empty element or at least one nested element
        //  (Just white space taken as empty element for now)
        while (token.length() == 0 && this->getSourceStream().isGood() && !this->getSourceStream().isEof() && (cur == Traits::lt || cur == Traits::slash)) {
            element_type prev = cur;
            if (prev == Traits::slash) {
                // Something of the form <foo/>
                while (this->getSourceStream().isGood() && !this->getSourceStream().isEof() && cur != Traits::gt) {
                    cur = readOne();
                }
                try {
                    cur = readOne();
                }
                catch (...) {}
                break;
            }
            else if ((cur = readOne()) == Traits::slash) {
                // Empty element, read close name and break out
                putBack(cur);
                string_type dummy;
                cur = readToClose(prev, dummy);
                break;
            }
            else {
                // Nested Element, recursion is called for
                putBack(cur);
                element.addElement(readNextElement(prev, element));
                cur = readToken(prev, token);
            }
        }
    }
    else {
        // Not a nested element and not empty, just read the value
        string_type token2;
        cur = readToClose(cur, token2);
        element.setValue(token + token2);
    }
    return cur;
}


template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
RWSize
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::available() const
{
    return (static_cast<RWSize>(this->egptr() - this->gptr()) + this->getSourceStream().available());
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
RWSize
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::skip(RWSize numUnits)
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

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
#if defined(__hpux)
typename InputStream::element_type
#else
typename RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::element_type
#endif
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::read()
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
        throw RWExternalStreamException("element_type RWTParsedTransformInputStreamImp::read(): No element available",
                                        RWExternalStreamException::read);
    }
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
RWSize
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::read(element_type* array,
        RWSize num)
{
    isFail_ = false;
    RWSize arraySize = static_cast<RWSize>(num * sizeof(element_type));
    if (num <= static_cast<RWSize>(this->egptr() - this->gptr())) {
        rw_memcpy_s(array, arraySize, this->gptr(), arraySize);
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

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
RWSize
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::readUntil(element_type* array,
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

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
bool
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::isFail() const
{
    return isFail_;
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
bool
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::isEof() const
{
    if (this->egptr() != this->gptr()) {
        return false;
    }
    else {
        return this->getSourceStream().isEof();
    }
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
bool
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::isBad() const
{
    if (this->egptr() != this->gptr()) {
        return false;
    }
    else {
        return this->isFail();
    }
}

template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
bool
RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>::isGood() const
{
    return !(this->isFail() || this->isBad());
}
