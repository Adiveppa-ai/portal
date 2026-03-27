#ifndef rw_xmlstreams_RWTParsedTransformInputStreamImp_h_
#define rw_xmlstreams_RWTParsedTransformInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTParsedTransformInputStreamImp.h#1 $
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
#include <memory.h>

//-- The class 'RWTParsedTransformInputStreamImp' implements a buffer that can be used with any kind of input
//-- stream. The size of the buffer is specified in its static member 'make()' function, which is
//-- used to create it.
/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Implements a buffer that can be used with any kind of input stream.
 *
 * The class RWTParsedTransformInputStreamImp implements a buffer that can
 * be used with any kind of input stream. The size of the buffer is
 * specified as a parameter to the static make() function that is used to
 * create it. If the buffer as initialized is not large enough to contain
 * the entire XML document, it grows as needed to be able to do so. It is
 * more efficient, though, to allocate a buffer of sufficient size
 * initially.
 *
 * RWTParsedTransformInputStreamImp is a class template that is derived from
 * one of its own template parameters.
 *
 * The class is defined as
 *
 * \code
 * template <class InputStream, class FilteredInputStreamImp,
 *           class Transform, class Traits>
 *
 * class RWTParsedTransformInputStreamImp :
 *   public FilteredInputStreamImp { ... };
 * \endcode
 */
template <class InputStream, class FilteredInputStreamImp, class Transform, class Traits>
class RWTParsedTransformInputStreamImp : public FilteredInputStreamImp
{
public:
    /**
     * A typedef for the template parameter \c InputStream which will be
     * used as the source of elements.
     */
    typedef InputStream RWInputStream_type;

    /**
     * A typedef for the type of element to be read from
     * #RWInputStream_type.
     */
    typedef typename InputStream::element_type element_type;

    /**
     * A typedef for a string of elements.
     */
    typedef RWCString string_type;

    //-- Constructs an 'RWTParsedTransformInputStreamImp' instance that uses 'sourceStream'
    //-- as its source of elements, and returns a handle to it.
    //-- The internal buffer is dynamically allocated to be of size RW_STREAM_BUFFER_SIZE.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    /**
     * Constructs an RWTParsedTransformInputStreamImp instance that uses
     * \a sourceStream as its source of elements, and returns a handle to
     * it. The internal buffer is initialized to be of size
     * #RW_STREAM_BUFFER_SIZE, which is defined as \c 512 bytes. The buffer
     * grows as needed to contain the entire XML document.
     *
     * The parameter \a sourceStream is the input stream that serves as the
     * source of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of
     * <tt>transform(RWXmlStreamElement&)</tt>.
     */
    static InputStream make(const InputStream& sourceStream, Transform transform)
    {
        return InputStream(new RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>(sourceStream, transform));
    }

    //-- Constructs an 'RWTParsedTransformInputStreamImp' instance that uses 'sourceStream'
    //-- as its source of elements, and returns a handle to it.
    //-- The internal buffer is dynamically allocated to be of size 'bufSize'.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Constructs an RWTParsedTransformInputStreamImp instance that uses
     * \a sourceStream as its source of elements, and returns a handle to
     * it. The internal buffer is initialized to be of size \a bufSize. The
     * buffer grows as needed to contain the entire XML document.
     *
     * The parameter \a sourceStream is the input stream that serves as the
     * source of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of
     * <tt>transform(RWXmlStreamElement&)</tt>.
     *
     * The parameter \a bufSize is the initial buffer capacity in number of
     * elements.
     */
    static InputStream make(const InputStream& sourceStream, Transform transform, RWSize bufSize)
    {
        return InputStream(new RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>(sourceStream, transform, bufSize));
    }

    //-- Constructs an 'RWTParsedTransformInputStreamImp' instance that uses 'sourceStream'
    //-- as its source of elements, and returns a handle to it.
    //-- The internal buffer is initialized using the pre-allocated element's array of
    //-- size 'bufSize'.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    //--   'buffer': A pre-allocated buffer of size 'bufSize' to be used
    //--             internally by the constructed RWTParsedTransformInputStreamImp object.
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Constructs an RWTParsedTransformInputStreamImp instance that uses
     * \a sourceStream as its source of elements, and returns a handle to
     * it. The internal buffer is initialized using a pre-allocated element
     * array of size \a bufSize. The buffer grows as needed to contain the
     * entire XML document.
     *
     * The parameter \a sourceStream is the input stream that serves as the
     * source of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of
     * <tt>transform(RWXmlStreamElement&)</tt>.
     *
     * The parameter \a buffer is a pre-allocated buffer of size \a bufSize
     * to be used internally by the constructed
     * RWTParsedTransformInputStreamImp object.
     *
     * The parameter \a bufSize is the initial buffer capacity in number of
     * elements.
     */
    static InputStream make(const InputStream& sourceStream, Transform transform, element_type* buffer, RWSize bufSize)
    {
        return InputStream(new RWTParsedTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform, Traits>(sourceStream, transform, buffer, bufSize));
    }

    /**
     * Virtual destructor. Throws no exceptions.
     */
    virtual ~RWTParsedTransformInputStreamImp();

    //-- If no character can be obtained from the input sequence, this function returns
    //-- 'true', otherwise it returns 'false'.
    //-- Throws no exceptions.
    /**
     * Returns \c true if no character can be obtained from the input
     * sequence, otherwise \c false. Throws no exceptions.
     */
    virtual bool isEof() const;

    //-- If the stream is in bad state, then this function returns 'true', otherwise
    //-- it returns 'false'.
    //-- Throws no exceptions.
    /**
     * Returns \c true if the input stream is in bad state, otherwise
     * \c false. Throws no exceptions.
     */
    virtual bool isBad() const;

    //-- If the stream is in fail state, then this function returns 'true', otherwise
    //-- it returns 'false'.
    //-- Throws no exceptions.
    /**
     * Returns \c true if the input stream is in fail state, otherwise
     * \c false. Throws no exceptions.
     */
    virtual bool isFail() const;

    //-- If the stream is in fail or bad state, then this function returns 'false', otherwise
    //-- it returns 'true'.
    //-- Throws no exceptions.
    /**
     * Returns \c false if the input stream is in fail or bad state,
     * otherwise \c true. Throws no exceptions.
     */
    virtual bool isGood() const;

    /**
     * Reads a single element from the input stream.
     */
    virtual element_type read();

    //-- Reads an array of element(s). The function returns the actual number of
    //-- element(s) read.
    //--
    //-- Parameters:
    //--
    //--   'array': A pointer to the first element of the array. The
    //-- array must have been pre-allocated to contain at least 'num'
    //-- elements.
    //--
    //--   'num': The number of element(s) to be read from the stream.
    //--
    /**
     * Reads an array of elements from the input stream. Returns the actual
     * number of elements read.
     *
     * The parameter \a array is a pointer to the beginning of the array
     * used to store the input. The array must have been pre-allocated to
     * contain at least num elements.
     *
     * The parameter \a num is the number of elements to be read from the
     * stream
     */
    virtual RWSize read(element_type* array, RWSize num);

    //-- Reads element(s) until the last element read is equal to 'delim',
    //-- or 'maxSize' element(s) have been read, or the end of the input sequence
    //-- is reached. The element(s) read are stored in 'array'. The function returns
    //-- the actual number of element(s) read from the stream.
    //--
    //-- Parameters:
    //--
    //--   'array': A pointer to the array receiving the element(s) extracted
    //-- from the stream.
    //--
    //--   'maxSize': The maximum number of elements(s) to be read.
    //--
    //--   'delim': The element value used as a delimiter.
    //--
    /**
     * Reads elements until the last element read is equivalent to \a delim,
     * \a maxSize elements have been read, or the end of the input sequence
     * is reached. The elements read are stored in \a array. The function
     * returns the actual number of elements read from the stream.
     *
     * The parameter \a array is a pointer to the beginning of the element
     * array holding the elements extracted from the stream.
     *
     * The parameter \a maxSize is the maximum number of elements to be
     * read.
     *
     * The parameter \a delim is the element value used as the delimiter.
     */
    virtual RWSize readUntil(element_type* array, RWSize maxSize, element_type delim);

    //-- Returns the number of element(s) that can be read from the stream without blocking.
    //-- Throws no exceptions.
    /**
     * Returns the number of characters that can be read from the stream
     * without blocking. Throws no exceptions.
     */
    virtual RWSize available() const;

    //-- Skips 'numUnits' element(s) from the input sequence if possible.
    //-- The function returns the actual number of element(s) skipped, which can be any
    //-- value between 0 and 'numUnits'.
    //--
    //-- Parameters:
    //--
    //--   'numUnits': The number of element(s) to be skipped.
    //--
    /**
     * Skips \a numUnits elements from the input sequence if possible. The
     * function returns the actual number of elements skipped, which can be
     * any value between 0 and \a numUnits.
     */
    virtual RWSize skip(RWSize numUnits);


protected:

    //-- Initializes the reference to the input stream that will be used as the source
    //-- of elements, as well as the internal buffer capacity, which will be equal to
    //-- RW_STREAM_BUFFER_SIZE.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    /**
     * Initializes the reference to the input stream used as the source of
     * elements, as well as the internal buffer, whose capacity is set equal
     * to #RW_STREAM_BUFFER_SIZE, defined as \c 512 bytes.
     *
     * The parameter \a sourceStream is the input stream that serves as the
     * source of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of
     * <tt>transform(RWXmlStreamElement&)</tt>.
     */
    RWTParsedTransformInputStreamImp(const InputStream& sourceStream, Transform transform);

    //-- Initializes the reference to the input stream, that will be used as the source
    //-- of elements, as well as the buffer capacity.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Initializes the reference to the input stream used as the source of
     * elements, and the internal buffer, whose capacity is set to
     * \a bufSize.
     *
     * The parameter \a sourceStream is the input stream that serves as the
     * source of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of
     * <tt>transform(RWXmlStreamElement&)</tt>.
     *
     * The parameter \a bufSize is the buffer capacity in number of
     * elements.
     */
    RWTParsedTransformInputStreamImp(const InputStream& sourceStream, Transform transform, RWSize bufSize);

    //-- Initializes the reference to the input stream, that will be used as the source
    //-- of elements, as well as the internal buffer.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(RWXmlStreamElement&)
    //--
    //--   'buffer': A pre-allocated buffer of size 'bufSize' to be used
    //--             internally by the constructed RWTParsedTransformInputStreamImp object.
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Initializes the reference to the input stream used as the source of
     * elements, and the internal buffer, which is initialized using a
     * pre-allocated element's array of size \a bufSize.
     *
     * The parameter \a sourceStream is the input stream that serves as the
     * source of elements.
     *
     * The parameter \a transform is the transformation object and must
     * provide a public interface of
     * <tt>transform(RWXmlStreamElement&)</tt>.
     *
     * The parameter \a buffer is a pre-allocated buffer of size \a bufSize
     * to be used internally by the constructed
     * RWTParsedTransformInputStreamImp object.
     *
     * The parameter \a bufSize is the buffer capacity in number of
     * elements.
     */
    RWTParsedTransformInputStreamImp(const InputStream& sourceStream, Transform transform, element_type* buffer, RWSize bufSize);

    /**
     * Returns a pointer to the first element in the input buffer array.
     * Throws no exceptions.
     */
    inline element_type* eback() const
    {
        return gbeg_;
    }

    /**
     * Returns a pointer to the current position in the buffered input
     * sequence. Throws no exceptions.
     */
    inline element_type* gptr() const
    {
        return gnext_;
    }

    /**
     * Returns a pointer one position past the last element in the input
     * sequence. Throws no exceptions.
     */
    inline element_type* egptr() const
    {
        return gend_;
    }

    /**
     * Returns a pointer one position past the end of the input buffer
     * array. Throws no exceptions.
     */
    inline element_type* ebuf() const
    {
        return bufEnd_;
    }

    //-- Sets the buffer's pointers.
    //--
    //-- Parameters:
    //--
    //--   'gbeg_arg': The value to be set in gbeg_.
    //--
    //--   'gcur_arg': The value to be set in gnext_.
    //--
    //--   'gend_arg': The value to be set in gend_.
    //--   Throws no exceptions.
    //--
    /**
     * Assigns the parameter values to \c gbeg_, \c gnext_, and \c gend_
     * respectively. These data members represent the beginning of the
     * buffer array, the current position in the array, and the end of the
     * array. Throws no exceptions.
     */
    inline void setg(element_type* gbeg_arg, element_type* gcur_arg, element_type* gend_arg)
    {
        gbeg_ = gbeg_arg;
        gnext_ = gcur_arg;
        gend_ = gend_arg;
    }

    //-- Sets the buffer's end pointer.
    //--
    //-- Parameters:
    //--
    //--   'gend_arg': The value to be set in bufEnd_.
    //--   Throws no exceptions.
    //--
    /**
     * Sets the buffer's end pointer. Assigns the parameter value to
     * \c gend_. Throws no exceptions.
     */
    inline void setBufferEnd(element_type* gend_arg)
    {
        bufEnd_ = gend_arg;
    }

    //-- Move the current get pointer 'n' position forward.
    //--
    //-- Parameters:
    //--
    //--   'n': The number of elements the current get pointer should be advanced.
    //--   Throws no exceptions.
    //--
    /**
     * Moves the input buffer array pointer \a n positions forward. The
     * array position now pointed to is the one returned by gptr(). Throws
     * no exceptions.
     */
    inline void gbump(RWSize n)
    {
        gnext_ += n;
    }

    /**
     * Frees the memory allocated to the internal buffer, if necessary.
     * Throws no exceptions.
     */
    void freeBuffer();

    //-- Fill up the buffer. Returns 'true' if there are elements available, otherwise
    //-- returns 'false'.
    //-- Throws no exceptions.
    /**
     * Fills the input buffer. Throws no exceptions.
     *
     * Returns \c true if there are elements available, otherwise \c false.
     */
    bool underflow();

    /**
     * Parses the XML input and applies the transformation.
     */
    void transform();

    //-- Read one character from the input
    //--
    //-- Returns the next character
    //--
    /**
     * Reads one character from the input and returns the next character.
     */
    element_type readOne();

    //--
    //-- Put back one character so it will be available for the next read
    //--
    //-- Parameter 'cur' is the character to put back.
    //--
    /**
     * Puts back one element, so it will be available for the next read. The
     * parameter \a cur is the element to be put back.
     */
    void putBack(element_type cur);

    //--
    //-- Read the next XML element
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'parent' holds the current element (the parent of the one to read)
    //-- Returns the parsed element
    //--
    /**
     * Reads the next XML element. The parameter \a cur holds the current
     * character. The parameter \a parent holds the current element (the
     * parent of the one to read). Returns the parsed element.
     */
    RWXmlStreamElement readNextElement(element_type& cur, const RWXmlStreamElement& parent);

    //--
    //-- Read a token
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'token' will be returned with the token
    //-- Returns the last character read
    //--
    /**
     * Reads a token. The parameter \a cur holds the current character. The
     * parameter \a token will be returned with the token. Returns the last
     * character read.
     */
    element_type readToken(element_type cur, string_type& token);

    //--
    //-- Read past the closing tag of the current element
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'token' will contain any data read before the closing tag
    //-- Returns the last character read
    //--
    /**
     * Reads past the closing tag of the current element. The parameter
     * \a cur holds the current character. The parameter \a token will
     * contain any data read before the closing tag. Returns the last
     * character read.
     */
    element_type readToClose(element_type cur, string_type& token);

    //--
    //-- Read everything to the next '>' character
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'token' will contain any data read before the '>' character
    //-- Returns the last character read
    //--
    /**
     * Reads everything to the next \c > character. The parameter \a cur
     * holds the current character. The parameter \a token will contain any
     * data read before the \c > character. Returns the last character read.
     */
    element_type readWholeName(element_type cur, string_type& token);

    //--
    //-- Read in an entire attribute (name and value)
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'token' will contain the attribute string or RWCString() if
    //--           no attribute is available.
    //-- Returns the last character read
    //--
    /**
     * Reads in an entire attribute (name and value). The parameter \a cur
     * holds the current character. The parameter \a token will contain the
     * attribute string, or an empty string if no attribute is available.
     * Returns the last character read.
     */
    element_type readAttribute(element_type cur, string_type& token);

    //--
    //-- Read in an attribute value
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'token' will contain the value without quotes or RWCString() if
    //--           no value is available.
    //-- Returns the last character read
    //--
    /**
     * Reads in an attribute value. The parameter \a cur holds the current
     * character. The parameter \a token will contain the value without
     * quotes, or an empty string if no value is available. Returns the last
     * character read.
     */
    element_type readAttributeValue(element_type cur, string_type& token);

    //--
    //-- Read all attributes in an element
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'element' will have the attributes added to it.
    //-- Returns the last character read
    //--
    /**
     * Reads all attributes in an element. The parameter \a cur holds the
     * current character. The parameter \a element will have the attributes
     * added to it. Returns the last character read.
     */
    element_type readAttributes(element_type cur, RWXmlStreamElement& element);

    //--
    //-- Read all attributes in an element
    //--
    //-- Parameter 'cur' holds the current character
    //-- Parameter 'element' will have the value added to it
    //--           (including nested elements).
    //-- Returns the last character read
    //--
    /**
     * Reads all values in an element. The parameter \a cur holds the
     * current character. The parameter \a element will have the values
     * added to it, including nested elements. Returns the last character
     * read.
     */
    element_type readValue(element_type cur, RWXmlStreamElement& element);

private:

    bool shouldFree_;

    bool isFail_;

    element_type* gbeg_;
    element_type* gnext_;
    element_type* gend_;
    element_type* bufEnd_;

    std::basic_string<element_type>  tbuffer_;
    element_type putBackChar_;
    bool putBack_;

    Transform transform_;

    friend class RWBufferedCharInputStreamImp;

};

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/xmlstreams/RWTParsedTransformInputStreamImp.cc>
#endif

#endif // rw_xmlstreams_RWTParsedTransformInputStreamImp_h_
