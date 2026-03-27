/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTParsedTransformOutputStreamImp.cc#1 $
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

#include <rw/xmlstreams/RWXmlStreamComment.h>
#include <rw/xmlstreams/RWXmlStreamProlog.h>
#include <rw/tools/string.h>

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream,
        Transform transform)
    : FilteredOutputStreamImp(sinkStream)
    , shouldFree_(true)
    , pbeg_(0)
    , pnext_(0)
    , pend_(0)
    , transform_(transform)
{

    if (!RW_STREAM_BUFFER_SIZE) {
        throw RWExternalStreamException("RWTParsedTransformOutputStreamImp::RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[RW_STREAM_BUFFER_SIZE];
    if (!tmp_) {
        throw RWExternalStreamException("RWTParsedTransformOutputStreamImp::RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setp(tmp_, tmp_ + RW_STREAM_BUFFER_SIZE);
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream,
        Transform transform,
        RWSize bufSize)
    : FilteredOutputStreamImp(sinkStream)
    , pbeg_(0)
    , pnext_(0)
    , pend_(0)
    , shouldFree_(true)
    , transform_(transform)
{

    if (!bufSize) {
        throw RWExternalStreamException("RWTParsedTransformOutputStreamImp::RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    element_type* tmp_ = new element_type[bufSize];
    if (!tmp_) {
        throw RWExternalStreamException("RWTParsedTransformOutputStreamImp::RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream, RWSize bufSize): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setp(tmp_, tmp_ + bufSize);
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream,
        Transform transform,
        element_type* buffer,
        RWSize bufSize)
    : FilteredOutputStreamImp(sinkStream)
    , pbeg_(0)
    , pnext_(0)
    , pend_(0)
    , shouldFree_(false)
    , transform_(transform)
{

    if (!bufSize) {
        throw RWExternalStreamException("RWTParsedTransformOutputStreamImp::RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream, element_type* buffer, RWSize bufSize): The buffer size cannot be 0.", RWExternalStreamException::invalidParameter);
    }
    if (!buffer) {
        throw RWExternalStreamException("RWTParsedTransformOutputStreamImp::RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream, element_type* buffer, RWSize bufSize): The buffer cannot be a nul pointer.", RWExternalStreamException::invalidParameter);
    }
    this->setp(buffer, buffer + bufSize);
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::~RWTParsedTransformOutputStreamImp()
{
    this->flush();
    this->freeBuffer();
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
void
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::freeBuffer()
{
    if (shouldFree_ && this->pbase()) {
        delete[] pbeg_;
    }
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
void
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::flush()
{
    if (this->pptr() - this->pbase()) {

        std::basic_ostringstream<element_type> buffer;
        transform(buffer);
        this->getSinkStream().write(buffer.str().data(), static_cast<RWSize>(buffer.str().length()));

        this->setp(this->pbase(), this->epptr());
    }
    this->getSinkStream().flush();
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
//std::basic_string<RWTParsedTransformOutputStreamImp<OutputStream,FilteredOutputStreamImp,Transform,Traits>::element_type>
void
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::transform(std::basic_ostringstream<typename RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::element_type>& buffer)
{
    element_type* ptr = this->pptr();
    RWTScopedPointer<RWXmlStreamElement> root(readNextElement(this->pbase(), ptr, RWXmlStreamElement()));
    transform_.transform(*root);
    root->write(buffer);
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
RWXmlStreamElement* RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::readNextElement(element_type* ptr,
        element_type*& ret,
        const RWXmlStreamElement& parent)
{
    string_type token;
    element_type* cur = ptr;

    while (cur != this->pptr() && *cur != Traits::lt) {
        ++cur;
    }
    ++cur;
    RWTScopedPointer<RWXmlStreamElement> element(new RWXmlStreamElement(parent.getNamespaces()));
    if (*cur == Traits::question || *cur == Traits::bang) {
        //    ++cur; ++cur; ++cur; ++cur;
        string_type value;
        RWTScopedPointer<RWXmlStreamElement> pi;
        if (*cur == Traits::bang) {
            pi.reset(new RWXmlStreamComment);
        }
        else {
            pi.reset(new RWXmlStreamProlog);
        }
        //    cur = readAttributes(cur,*pi);
        cur = readWholeName(cur, value);
        pi->setValue(value);
        element->addElement(pi.get());
        pi.release();
        element->addElement(readNextElement(cur, cur, *element));
    }
    /*  else if (*cur == Traits::bang)
      {
        string_type value;
        ++cur; ++cur; ++cur;
        RWTScopedPointer<RWXmlStreamComment> comment(new RWXmlStreamComment);
        comment->setValue(value);
        element->addElement(comment.get());
        comment.release();
        cur = readWholeName(cur,value);
        element->addElement(readNextElement(cur,cur,*element));
      }*/
    else {
        cur = readToken(cur, token);
        cur = readAttributes(cur, *element);
        size_t pos = token.firstOf(Traits::colon);
        if (pos != RW_NPOS) {
            string_type prefix = token(0, pos);
            element->setName(RWXmlName(token(pos + 1, token.length() - (pos + 1)), element->findNamespaceURI(prefix)));
        }
        else {
            element->setName(RWXmlName(token));
        }
        cur = readValue(cur, *element);
    }
    ret = cur;
    return element.release();
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
typename RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::element_type*
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::readToken(element_type* ptr, string_type& token)
{
    while (ptr != this->pptr() && (*ptr == Traits::space || *ptr == Traits::newline || *ptr == Traits::tab)) {
        ++ptr;
    }
    while (ptr != this->pptr() && *ptr != Traits::lt && *ptr != Traits::gt && *ptr != Traits::space && *ptr != Traits::newline && *ptr != Traits::tab && *ptr != Traits::equal && *ptr != Traits::slash) {
        token += *ptr;
        ++ptr;
    }
    return ptr;
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
typename RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::element_type*
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::readToClose(element_type* ptr, string_type& token)
{
    while (ptr != this->pptr() && *ptr != Traits::lt) {
        token += *ptr;
        ++ptr;
    }

    while (ptr != this->pptr() && *ptr != Traits::gt) {
        ++ptr;
    }

    return ++ptr;
}


template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
typename RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::element_type*
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::readWholeName(element_type* ptr, string_type& token)
{
    while (ptr != this->pptr() && *ptr != Traits::gt) {
        token += *ptr++;
    }
    return ptr;
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
typename RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::element_type*
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::readAttributeValue(element_type* ptr, string_type& token)
{
    while (ptr != this->pptr() && (*ptr == Traits::space || *ptr == Traits::newline || *ptr == Traits::tab)) {
        ++ptr;
    }
    element_type delim = *ptr;
    if (delim != Traits::quote && delim != Traits::apostrophe) {
        return readToken(ptr, token);
    }
    token += *ptr++;
    while (ptr != this->pptr() && *ptr != delim) {
        token += *ptr;
        ptr++;
    }
    token += *ptr;
    return ++ptr;
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
typename RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::element_type*
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::readAttribute(element_type* ptr, string_type& token)
{
    string_type temp;
    element_type* cur = ptr;
    cur = readToken(cur, token);
    if (token.length() != 0 && *cur != Traits::gt) {
        cur = readToken(cur, temp);
        token += *cur++;
        cur = readAttributeValue(cur, temp);
        token += temp;
    }
    else {
        token = "";
    }
    return cur;
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
typename RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::element_type*
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::readAttributes(element_type* ptr, RWXmlStreamElement& element)
{
    string_type token;
    element_type* cur = ptr;
    cur = readAttribute(cur, token);
    while (token.length() != 0) {
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
            element.addAttribute(RWXmlAttribute(RWXmlName(prefix), token(pos + 2, token.length() > pos + 3 ? token.length() - (pos + 3) : 0)));
        }
        token.resize(0);
        cur = readAttribute(cur, token);
    }
    element.resolveNamespaces();
    if (*cur != Traits::slash) {
        ++cur;
    }
    return cur;
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
typename RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::element_type*
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::readValue(element_type* ptr, RWXmlStreamElement& element)
{
    string_type token;
    element_type* cur = ptr;
    cur = readToken(cur, token);
    if (token.length() == 0 && cur != this->pptr() && (*cur == Traits::lt || *cur == Traits::slash)) {
        // Either an empty element or at least one nested element
        //  (Just white space taken as empty element for now)
        while (token.length() == 0 && cur != this->pptr() && (*cur == Traits::lt || *cur == Traits::slash)) {
            element_type* next = cur;
            if (*next == Traits::slash) {
                // Something of the form <foo/>
                while (ptr != this->pptr() && *ptr != Traits::gt) {
                    ++ptr;
                }
                return ++ptr;
                break;
            }
            else if (*(++next) == Traits::slash) {
                // Empty element, read close name and break out
                string_type dummy;
                cur = readToClose(cur, dummy);
                break;
            }
            else {
                // Nested Element, recursion is called for
                element.addElement(readNextElement(cur, cur, element));
                cur = readToken(cur, token);
            }
        }
    }
    else {
        // Not a nested element and not empty, just read the value
        token.resize(0);
        cur = readToClose(ptr, token);
        element.setValue(token);
    }
    return cur;
}


template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
void
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::close()
{
    this->flush();
    this->getSinkStream().close();
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
void
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::setBuffer(RWSize bufSize)
{
    RWSize curSize = static_cast<RWSize>(this->pptr() - this->pbase());
    element_type* prevBuffer = pbeg_;
    element_type* tmp_ = new element_type[bufSize];
    if (!tmp_) {
        throw RWExternalStreamException("RWTParsedTransformOutputStreamImp::RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream, RWSize bufSize): The memory allocation request for the buffer failed", RWExternalStreamException::outOfMemory);
    }
    this->setp(tmp_, tmp_ + bufSize);
    if (prevBuffer) {
        rw_memcpy_s(this->pptr(), bufSize,  prevBuffer, curSize * sizeof(element_type));
        pbump(curSize);
        if (shouldFree_) {
            delete[] prevBuffer;
        }
    }
}


template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
void
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::write(element_type value)
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

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
void
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::write(const element_type* array,
        RWSize numElements)
{
    RWSize buffSize = static_cast<RWSize>((this->epptr() - this->pptr()) * sizeof(element_type));
    RWSize arraySize = static_cast<RWSize>(numElements * sizeof(element_type));
    if (buffSize >= arraySize) {
        // we have enough space in the buffer to insert the array of elements
        rw_memcpy_s(this->pptr(), buffSize, array, arraySize);
        this->pbump(numElements);
    }
    else {
        // resize buffer
        RWSize newSize = static_cast<RWSize>((this->pptr() - this->pbase() + numElements) * sizeof(element_type) + RW_STREAM_BUFFER_SIZE);
        setBuffer(newSize);
        rw_memcpy_s(this->pptr(), newSize, array, numElements * sizeof(element_type));
        this->pbump(numElements);
    } // end else
}
