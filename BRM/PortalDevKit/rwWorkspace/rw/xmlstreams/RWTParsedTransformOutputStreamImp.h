#ifndef rw_xmlstreams_RWTParsedTransformOutputStreamImp_h_
#define rw_xmlstreams_RWTParsedTransformOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTParsedTransformOutputStreamImp.h#1 $
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

#include <rw/xmlstreams/RWXmlStreamElement.h>
#include <rw/xmlstreams/pkgdefs.h>
#include <rw/stream/RWExternalStreamException.h>
#include <sstream>
#include <string>
#include <memory.h>

//-- The class 'RWTParsedTransformOutputStreamImp' implements a buffer that can be used with any kind of output
//-- stream. The size of the buffer is specified in its static member 'make()' function, which is
//-- used to create it.
/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Implements a buffer that can be used with any kind of output stream.
 *
 * The class RWTParsedTransformOutputStreamImp implements a buffer that can
 * be used with any kind of output stream. The size of the buffer is
 * specified as a parameter to the static make() function that is used to
 * create it. If the buffer as initialized is not large enough to contain
 * the entire XML document, it grows as needed to be able to do so. It is
 * more efficient, though, to allocate a buffer of sufficient size
 * initially.
 *
 * RWTParsedTransformOutputStreamImp is a class template that is derived
 * from one of its own template parameters.
 *
 * The class is defined as
 *
 * \code
 * template <class OutputStream, class FilteredOutputStreamImp,
 *           class Transform, class Traits>
 *
 * class RWTParsedTransformOutputStreamImp :
 *   public FilteredOutputStreamImp { ...}
 * \endcode
 */
template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
class RWTParsedTransformOutputStreamImp : public FilteredOutputStreamImp
{

public:
    /**
     * A typedef for the template parameter \c OutputStream which will be
     * used as the sink for elements.
     */
    typedef OutputStream RWOutputStream_type;

    /**
     * A typedef for the type of element to be written to
     * #RWOutputStream_type.
     */
    typedef typename OutputStream::element_type element_type;

    /**
     * A typedef for a string of elements.
     */
    typedef RWCString string_type;

    //-- Constructs an 'RWTParsedTransformOutputStreamImp' instance that uses 'sinkStream'
    //-- as its sink of elements, and returns a handle to it.
    //-- The internal buffer is dynamically allocated to be of size RW_STREAM_BUFFER_SIZE.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    /**
     * Constructs an RWTParsedTransformOutputStreamImp instance that uses
     * \a sinkStream as its sink of elements, and returns a handle to it.
     * The internal buffer is initialized to be of size
     * #RW_STREAM_BUFFER_SIZE, which is defined as \c 512 bytes. The buffer
     * grows as needed to contain the entire XML document.
     *
     * The parameter \a sinkStream is the output stream that serves as the
     * sink of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of transform(RWXmlStreamElement&).
     */
    static OutputStream make(const OutputStream& sinkStream, Transform transform)
    {
        return OutputStream(new RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>(sinkStream, transform));
    }

    //-- Constructs an 'RWTParsedTransformOutputStreamImp' instance that uses 'sinkStream'
    //-- as its sink of elements, and returns a handle to it.
    //-- The internal buffer is dynamically allocated to be of size 'bufSize'.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Constructs an RWTParsedTransformOutputStreamImp instance that uses
     * \a sinkStream as its sink of elements, and returns a handle to it.
     * The internal buffer is initialized to be of size \a bufSize. The
     * buffer grows as needed to contain the entire XML document.
     *
     * The parameter \a sinkStream is the output stream that serves as the
     * sink of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of transform(RWXmlStreamElement&).
     *
     * The parameter \a bufSize the buffer capacity in number of elements
     */
    static OutputStream make(const OutputStream& sinkStream, Transform transform, RWSize bufSize)
    {
        return OutputStream(new RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>(sinkStream, transform, bufSize));
    }

    //-- Constructs an 'RWTParsedTransformOutputStreamImp' instance that uses 'sinkStream'
    //-- as its sink of elements, and returns a handle to it.
    //-- The internal buffer is initialized using the pre-allocated element's array of
    //-- size 'bufSize'.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    //--   'buffer': A pre-allocated buffer of size 'bufSize' to be used
    //--             internally by the constructed RWTParsedTransformOutputStreamImp object.
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Constructs an RWTParsedTransformOutputStreamImp instance that uses
     * \a sinkStream as its sink of elements, and returns a handle to it.
     * The internal buffer is initialized using a pre-allocated element's
     * array of size \a bufSize. The buffer grows as needed to contain the
     * entire XML document.
     *
     * The parameter \a sinkStream is the output stream that serves as the
     * sink of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of transform(RWXmlStreamElement&).
     *
     * The parameter \a buffer is a pre-allocated buffer of size \a bufSize
     * to be used internally by the constructed
     * RWTParsedTransformOutputStreamImp object.
     *
     * The parameter \a bufSize is the buffer capacity in number of elements
     */
    static OutputStream make(const OutputStream& sinkStream, Transform transform, element_type* buffer, RWSize bufSize)
    {
        return OutputStream(new RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>(sinkStream, transform, buffer, bufSize));
    }

    /**
     * Virtual destructor. Throws no exceptions.
     */
    virtual ~RWTParsedTransformOutputStreamImp();

    //-- Writes a single element to the stream.
    //--
    //-- Parameters:
    //--
    //--   'value': The element to be written to the stream.
    //--
    /**
     * Writes a single element to the stream. The parameter \a value is the
     * element to be written to the stream.
     */
    virtual void write(element_type value);

    //-- Writes an array of element(s) to the stream.
    //--
    //-- Parameters:
    //--
    //--   'array': A pointer to the first element of the array.
    //--
    //--   'numElements': The number of element(s) to be written to the
    //--   stream.
    //--
    /**
     * Writes a character array of size \a numElements to the stream. The
     * parameter \a array is a pointer to the first element in the array.
     */
    virtual void write(const element_type* array, RWSize numElements);

    //-- Calls 'flush()', then calls 'close()' on the next processing stream.
    /**
     * Calls flush() and then calls close() on the next processing stream.
     */
    virtual void close();

    //-- Flushes the buffer by forwarding its content to the next processing stream.
    /**
     * Flushes the buffer by forwarding its content to the next processing
     * stream.
     */
    virtual void flush();

protected:

    //-- Initializes the reference to the output stream that will be used as the sink
    //-- of elements, as well as the internal buffer capacity, which will be equal to
    //-- RW_STREAM_BUFFER_SIZE.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    /**
     * Initializes the reference to the output stream used as the sink of
     * elements, as well as the internal buffer, whose capacity is set to
     * #RW_STREAM_BUFFER_SIZE, defined as \c 512 bytes.
     *
     * The parameter \a sinkStream is the output stream that serves as the
     * sink of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of transform(RWXmlStreamElement&).
     */
    RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream, Transform transform);

    //-- Initializes the reference to the output stream that will be used as the sink
    //-- of elements, as well as the buffer capacity.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Initializes the reference to the output stream used as the sink of
     * elements, and the internal buffer capacity, which is set to
     * \a bufSize.
     *
     * \a sinkStream is the output stream that serves as the sink of
     * elements.
     *
     * \a transform is the transformation object and must provide a public
     * interface of transform(RWXmlStreamElement&).
     *
     * \a bufSize the buffer capacity in number of elements
     */
    RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream, Transform transform, RWSize bufSize);

    //-- Initializes the reference to the output stream that will be used as the sink
    //-- of elements, as well as the internal buffer.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    //--   'buffer': A pre-allocated buffer of size 'bufSize' to be used
    //--             internally by the constructed RWTParsedTransformOutputStreamImp object.
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Initializes the reference to the output stream used as the sink of
     * elements, and the internal buffer, which is initialized using a
     * pre-allocated element's array of size \a bufSize.
     *
     * The parameter \a sinkStream is the output stream that serves as the
     * sink of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of transform(RWXmlStreamElement&).
     *
     * The parameter \a buffer a pre-allocated buffer of size \a bufSize to
     * be used internally by the constructed
     * RWTParsedTransformOutputStreamImp object
     *
     * The parameter \a bufSize is the buffer capacity in number of
     * elements.
     */
    RWTParsedTransformOutputStreamImp(const OutputStream& sinkStream, Transform transform, element_type* buffer, RWSize bufSize);

    /**
     * Returns a pointer to the first element in the buffer. Throws no
     * exceptions.
     */
    inline element_type* pbase() const
    {
        return pbeg_;
    }

    /**
     * Returns a pointer to the current position in the buffer. Throws no
     * exceptions.
     */
    inline element_type* pptr() const
    {
        return pnext_;
    }

    /**
     * Returns a pointer one position past the last element in the output
     * sequence. Throws no exceptions.
     */
    inline element_type* epptr() const
    {
        return pend_;
    }

    //-- Sets the buffer's pointers.
    //--
    //-- Parameters:
    //--
    //--   'pbeg_arg': The value to be set in pbeg_ and pnext_.
    //--
    //--   'pend_arg': The value to be set in pend_.
    //--   Throws no exceptions.
    //--
    /**
     * Sets the buffer's pointers. Assigns the first parameter value to
     * \c pbeg_ and \c pnext_, and the second parameter value to \c pend_.
     * These data members represent the beginning of the buffer array, the
     * current position in the array, and the end of the array.
     */
    inline void setp(element_type* pbeg_arg, element_type* pend_arg);

    //-- Moves the current put pointer 'n' position forward.
    //--
    //-- Parameters:
    //--
    //--   'n': The number of elements the current put pointer should be advanced.
    //-- Throws no exceptions.
    //--
    /**
     * Moves the output buffer array pointer \a n positions forward. The
     * array position now pointed to is the one returned by pptr(). Throws
     * no exceptions.
     */
    inline void pbump(RWSize n);

    /**
     * Frees the memory allocated to the internal buffer, if necessary.
     * Throws no exceptions.
     */
    void freeBuffer();

    /**
     * Sets the buffer size to \a bufsize elements.
     */
    void setBuffer(RWSize bufsize);

    //--
    //-- Parse the XML input and apply the transformation
    //--
    //-- Parameter 'buffer' the transformed document in parameter
    //--
    void transform(std::basic_ostringstream<element_type>& buffer);

    //--
    //-- Read the next XML element
    //--
    //-- Parameter 'ptr' points to the current read position
    //-- parameter will contain the subsequent read position
    //-- Parameter 'parent' holds the current element (the parent of the one to read)
    //-- Returns the parsed element
    //--
    /**
     * Reads the next XML element. The parameter \a ptr points to the
     * current read position. The parameter \a next contains the subsequent
     * read position. The parameter \a parent holds the current element (the
     * parent of the one to read). Returns the parsed element.
     */
    RWXmlStreamElement* readNextElement(element_type* ptr, element_type*& next, const RWXmlStreamElement& parent);

    //--
    //-- Read a token
    //--
    //-- Parameter 'ptr' holds the current read position
    //-- Parameter 'token' will be returned with the token
    //-- Returns the subsequent read position
    //--
    /**
     * Reads a token. The parameter \a ptr points to the current read
     * position. The parameter \a token is returned with the token. Returns
     * the subsequent read position.
     */
    element_type* readToken(element_type* ptr, string_type& token);

    //--
    //-- Read past the closing tag of the current element
    //--
    //-- Parameter 'ptr' holds the current read position
    //-- Parameter 'token' will contain any data read before the closing tag
    //-- Returns the subsequent read position
    //--
    /**
     * Reads past the closing tag of the current element. The parameter
     * \a ptr points to the current read position. The parameter \a token
     * contains any data read before the closing tag. Returns the subsequent
     * read position.
     */
    element_type* readToClose(element_type* ptr, string_type& token);

    //--
    //-- Read everything to the next '>' character
    //--
    //-- Parameter 'ptr' holds the current read position
    //-- Parameter 'token' will contain any data read before the '>' character
    //-- Returns the subsequent read position
    //--
    /**
     * Reads everything to the next \c > character. The parameter \a ptr
     * points to the current read position. The parameter \a token contains
     * any data read before the \c > character. Returns the subsequent read
     * position.
     */
    element_type* readWholeName(element_type* ptr, string_type& token);

    //--
    //-- Read in an entire attribute (name and value)
    //--
    //-- Parameter 'ptr' holds the current read position
    //-- Parameter 'token' will contain the attribute string or RWCString() if
    //--           no attribute is available.
    //-- Returns the subsequent read position
    //--
    /**
     * Reads the entire attribute (name and value). The parameter \a ptr
     * points to the current read position. The parameter \a token contains
     * the attribute string, or \ref RWCString::RWCString() "RWCString()" if
     * no attribute is available. Returns the subsequent read position.
     */
    element_type* readAttribute(element_type* ptr, string_type& token);

    //--
    //-- Read in an attribute value
    //--
    //-- Parameter 'ptr' holds the current read position
    //-- Parameter 'token' will contain the value without quotes or RWCString() if
    //--           no value is available.
    //-- Returns the subsequent read position
    //--
    /**
     * Reads an attribute value. The parameter \a ptr points to the current
     * read position. The parameter \a token contains the without quotes, or
     * \ref RWCString::RWCString() "RWCString()" if no value is available.
     * Returns the subsequent read position.
     */
    element_type* readAttributeValue(element_type* ptr, string_type& token);

    //--
    //-- Read all attributes in an element
    //--
    //-- Parameter 'ptr' holds the current read position
    //-- Parameter 'element' will have the attributes added to it.
    //-- Returns the subsequent read position
    //--
    /**
     * Reads all the attributes in an element. The parameter \a ptr points
     * to the current read position. The parameter \a element will have the
     * attributes added to it. Returns the subsequent read position.
     */
    element_type* readAttributes(element_type* ptr, RWXmlStreamElement& element);
    //--
    //-- Read all attributes in an element
    //--
    //-- Parameter 'ptr' holds the current read position
    //-- Parameter 'element' will have the value added to it
    //--           (including nested elements).
    //-- Returns the subsequent read position
    //--
    /**
     * Reads all values in an element. The parameter \a ptr points to the
     * current read position. The parameter \a element will have the value
     * added to it, including the nested elements. Returns the subsequent
     * read position.
     */
    element_type* readValue(element_type* ptr, RWXmlStreamElement& element);

private:

    bool shouldFree_;

    element_type* pbeg_;
    element_type* pnext_;
    element_type* pend_;

    Transform transform_;

};

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
inline void
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::setp(element_type* pbeg_arg,
        element_type* pend_arg)
{
    pbeg_ = pnext_ = pbeg_arg;
    pend_ = pend_arg;
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform, class Traits>
inline void
RWTParsedTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform, Traits>::pbump(RWSize n)
{
    pnext_ += n;
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/xmlstreams/RWTParsedTransformOutputStreamImp.cc>
#endif

#endif // rw_xmlstreams_RWTParsedTransformOutputStreamImp_h_
