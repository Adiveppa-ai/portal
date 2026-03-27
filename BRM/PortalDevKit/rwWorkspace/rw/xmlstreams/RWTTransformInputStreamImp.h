#ifndef rw_xmlstreams_RWTTransformInputStreamImp_h_
#define rw_xmlstreams_RWTTransformInputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTTransformInputStreamImp.h#1 $
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

#include <rw/xmlstreams/pkgdefs.h>
#include <rw/stream/RWExternalStreamException.h>
#include <sstream>
#include <string>
#include <memory.h>

//-- The class 'RWTTransformInputStreamImp' implements a buffer that can be used with any kind of input
//-- stream. The size of the buffer is specified in its static member 'make()' function, which is
//-- used to create it.
/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Implements a buffered \c char or \c byte input character stream that
 * includes a transformation.
 *
 * The class RWTTransformInputStreamImp implements a buffered \c char or
 * \c byte input character stream that includes a transformation. The size
 * of the buffer is specified as a parameter to the static make() function
 * that is used to create it. If the buffer as initialized is not large
 * enough to contain the entire XML document, it grows as needed to be able
 * to do so. It is more efficient, though, to allocate a buffer of
 * sufficient size initially.
 *
 * RWTTransformInputStreamImp is a class template that is derived from one
 * of its own template parameters.
 *
 * The class is defined as
 *
 * \code
 * template <class InputStream, class FilteredInputStreamImp,
 *           class Transform>
 *
 * class RWTTransformInputStreamImp :
 *   public FilteredInputStreamImp { ...}
 * \endcode
 *
 * When the read() or readUntil() is first called on this class, the
 * transform() method of the transformation object passed into the
 * constructor gets called. The transform() method reads from the source,
 * applies the transformation defined by the method, and stores the result
 * in the buffer. Once the buffer contains the entire transformed document,
 * the call to read() or readUntil() is completed by reading from the
 * buffer.
 */
template <class InputStream, class FilteredInputStreamImp, class Transform>
class RWTTransformInputStreamImp : public FilteredInputStreamImp
{

public:

    /**
     * In keeping with the pattern for all filtered input streams, the type
     * of character contained by the stream is referred to as the
     * <tt>"element_type"</tt>. Characters in the stream are called
     * "elements" (not to be confused with XML "elements").
     *
     * \note
     * Be aware that characters in the stream are called "elements," which
     * have no connection to XML "elements."
     */
    typedef typename InputStream::element_type element_type;

    typedef std::basic_string<element_type, std::char_traits<element_type> > string_type;

    //-- Constructs an 'RWTTransformInputStreamImp' instance that uses 'sourceStream'
    //-- as its source of elements, and returns a handle to it.
    //-- The internal buffer is dynamically allocated to be of size RW_STREAM_BUFFER_SIZE.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(basic_istream<element_type>, char_traits<element_type> >&,
    //--                           basic_ostream<element_type>, char_traits<element_type> >&)
    //--
    /**
     * Constructs an RWTTransformInputStreamImp instance that uses
     * \a sourceStream as its source of elements, and returns a handle to
     * it. The internal buffer is initialized to be of size
     * #RW_STREAM_BUFFER_SIZE. The buffer grows as needed to contain the
     * entire XML document.
     *
     * The parameter \a sourceStream represents the input stream that serves
     * as the source of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >&,
     *           basic_ostream<element_type, char_traits<element_type> >&)
     * \endcode
     */
    static InputStream make(const InputStream& sourceStream, Transform transform)
    {
        return InputStream(new RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>(sourceStream, transform));
    }

    //-- Constructs an 'RWTTransformInputStreamImp' instance that uses 'sourceStream'
    //-- as its source of elements, and returns a handle to it.
    //-- The internal buffer is dynamically allocated to be of size 'bufSize'.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(basic_istream<element_type>, char_traits<element_type> >&,
    //--                           basic_ostream<element_type>, char_traits<element_type> >&)
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    /**
     * Constructs an RWTTransformInputStreamImp instance that uses
     * \a sourceStream as its source of elements, and returns a handle to
     * it. The internal buffer is initialized to be of size \a bufSize. The
     * buffer grows as needed to contain the entire XML document.
     *
     * The parameter \a sourceStream represents the input stream that serves
     * as the source of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >&,
     *           basic_ostream<element_type, char_traits<element_type> >&)
     * \endcode
     *
     * The parameter \a bufSize represents the initial buffer capacity in
     * number of elements.
     */
    static InputStream make(const InputStream& sourceStream, Transform transform, RWSize bufSize)
    {
        return InputStream(new RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>(sourceStream, transform, bufSize));
    }

    //-- Constructs an 'RWTTransformInputStreamImp' instance that uses 'sourceStream'
    //-- as its source of elements, and returns a handle to it.
    //-- The internal buffer is initialized using the pre-allocated element's array of
    //-- size 'bufSize'.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(basic_istream<element_type>, char_traits<element_type> >&,
    //--                           basic_ostream<element_type>, char_traits<element_type> >&)
    //--
    //--   'buffer': A pre-allocated buffer of size 'bufSize' to be used
    //--   internally by the constructed RWTTransformInputStreamImp object.
    /**
     * Constructs an RWTTransformInputStreamImp instance that uses
     * \a sourceStream as its source of elements, and returns a handle to
     * it. The internal buffer is initialized using a pre-allocated
     * element's array of size \a bufSize. The buffer grows as needed to
     * contain the entire XML document.
     *
     * The parameter \a sourceStream represents the input stream that serves
     * as the source of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >&,
     *           basic_ostream<element_type, char_traits<element_type> >&)
     * \endcode
     *
     * The parameter \a buffer represents a pre-allocated buffer of size
     * \a bufSize to be used internally by the constructed
     * RWTTransformInputStreamImp object.
     */
    static InputStream make(const InputStream& sourceStream, Transform transform, element_type* buffer, RWSize bufSize)
    {
        return InputStream(new RWTTransformInputStreamImp<InputStream, FilteredInputStreamImp, Transform>(sourceStream, transform, buffer, bufSize));
    }

    /**
     * Virtual destructor. Throws no exceptions.
     */
    virtual ~RWTTransformInputStreamImp();

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
     * Returns \c true if the stream is in a bad state, otherwise \c false.
     * Throws no exceptions.
     */
    virtual bool isBad() const;

    //-- If the stream is in fail state, then this function returns 'true', otherwise
    //-- it returns 'false'.
    //-- Throws no exceptions.
    /**
     * Returns \c true if the stream is in fail state, otherwise \c false.
     * Throws no exceptions.
     */
    virtual bool isFail() const;

    //-- If the stream is in fail or bad state, then this function returns 'false', otherwise
    //-- it returns 'true'.
    //-- Throws no exceptions.
    /**
     * Returns \c false if the stream is in fail or bad state, otherwise
     * \c true. Throws no exceptions.
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
     * The parameter \a array represents a pointer to the beginning of the
     * element array used to store the input. The array must have been
     * pre-allocated to contain at least \a num elements. The parameter
     * \a num represents the number of elements to be read from the stream.
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
     * The parameter \a array represents a pointer to the beginning of the
     * element array holding the elements extracted from the stream.
     *
     * The parameter \a maxSize represents the maximum number of elements to
     * be read.
     *
     * The parameter \a delim represents the element value used as the
     * delimiter.
     */
    virtual RWSize readUntil(element_type* array, RWSize maxSize, element_type delim);

    /**
     * Returns the number of elements that can be read from the stream
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
    //--                 transform(basic_istream<element_type>, char_traits<element_type> >&,
    //--                           basic_ostream<element_type>, char_traits<element_type> >&)
    //--
    /**
     * Initializes the reference to the input stream used as the source of
     * elements, and the internal buffer, whose capacity is set equal to
     * #RW_STREAM_BUFFER_SIZE.
     *
     * The parameter \a sourceStream represents the input stream that serves
     * as the source of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >&,
     *           basic_ostream<element_type, char_traits<element_type> >&)
     * \endcode
     */
    RWTTransformInputStreamImp(const InputStream& sourceStream, Transform transform);

    //-- Initializes the reference to the input stream, that will be used as the source
    //-- of elements, as well as the buffer capacity.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(basic_istream<element_type>, char_traits<element_type> >&,
    //--                           basic_ostream<element_type>, char_traits<element_type> >&)
    //--//--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Initializes the reference to the input stream used as the source of
     * elements, and the internal buffer, whose capacity is set to
     * \a bufSize.
     *
     * The parameter \a sourceStream represents the input stream that serves
     * as the source of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >&,
     *           basic_ostream<element_type, char_traits<element_type> >&)
     * \endcode
     *
     * The parameter \a bufSize represents the buffer capacity in number of
     * elements.
     */
    RWTTransformInputStreamImp(const InputStream& sourceStream, Transform transform, RWSize bufSize);

    //-- Initializes the reference to the input stream, that will be used as the source
    //-- of elements, as well as the internal buffer.
    //--
    //-- Parameters:
    //--
    //--   'sourceStream': The input stream that will serve as the source of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(basic_istream<element_type>, char_traits<element_type> >&,
    //--                           basic_ostream<element_type>, char_traits<element_type> >&)
    //--
    //--   'buffer': A pre-allocated buffer of size 'bufSize' to be used
    //--   internally by the constructed RWTTransformInputStreamImp object.
    //--
    /**
     * Initializes the reference to the input stream used as the source of
     * elements, and the internal buffer, which is initialized using a
     * pre-allocated element's array of size \a bufSize.
     *
     * The parameter \a sourceStream represents the input stream that serves
     * as the source of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >&,
     *           basic_ostream<element_type, char_traits<element_type> >&)
     * \endcode
     *
     * The parameter \a buffer represents a pre-allocated buffer of size
     * \a bufSize to be used internally by the constructed
     * RWTTransformInputStreamImp object.
     */
    RWTTransformInputStreamImp(const InputStream& sourceStream, Transform transform, element_type* buffer, RWSize bufSize);

    /**
     * Returns a pointer to the first element in the input buffer array.
     * Throws no exceptions.
     */
    inline element_type* eback() const
    {
        return gbeg_;
    }

    //-- Returns a pointer to the input sequence current position.
    //-- Throws no exceptions.
    /**
     * Returns a pointer to the current position in the buffered input
     * sequence. Throws no exceptions.
     */
    inline element_type* gptr() const
    {
        return gnext_;
    }

    //-- Returns a pointer one position past the input sequence last element.
    //-- Throws no exceptions.
    /**
     * Returns a pointer one position past the last element in the input
     * sequence. Throws no exceptions.
     */
    inline element_type* egptr() const
    {
        return gend_;
    }

    //-- Returns a pointer one position past the end of the buffer.
    //-- Throws no exceptions.
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
     * array.
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
     * Sets the buffer's end pointer. Assigns the parameter value
     * \c bufEnd_. Throws no exceptions.
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
     * Fills the input buffer. Returns \c true if there are elements
     * available, otherwise \c false.
     */
    bool underflow();
    void transform(std::basic_ostringstream<element_type, std::char_traits<element_type>, std::allocator<element_type> >& sbuffer);

private:

    bool shouldFree_;

    bool isFail_;

    element_type* gbeg_;
    element_type* gnext_;
    element_type* gend_;
    element_type* bufEnd_;

    Transform transform_;
};

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/xmlstreams/RWTTransformInputStreamImp.cc>
#endif

#endif // rw_xmlstreams_RWTTransformInputStreamImp_h_
