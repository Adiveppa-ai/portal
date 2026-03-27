#ifndef rw_xmlstreams_RWTTransformOutputStreamImp_h_
#define rw_xmlstreams_RWTTransformOutputStreamImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/xmlstreams/RWTTransformOutputStreamImp.h#1 $
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

//-- The class 'RWTTransformOutputStreamImp' implements a buffer that can be used with any kind of output
//-- stream. The size of the buffer is specified in its static member 'make()' function, which is
//-- used to create it. The buffer's role is to store elements up to its maximum capacity, and
//-- then to forward them to its associated sink stream. The buffer flushes itself upon destruction.
/**
 * \ingroup xmlstreams_package
 *
 * \brief
 * Implements a buffered \c char or \c byte output stream that includes a
 * transformation.
 *
 * The class RWTTransformOutputStreamImp implements a buffered \c char or
 * \c byte output stream that includes a transformation. The size of the
 * buffer is specified as a parameter to the static make() function that is
 * used to create it. If the buffer as initialized is not large enough to
 * contain the entire XML document, it grows as needed to be able to do so.
 * It is more efficient, though, to allocate a buffer of sufficient size
 * initially.
 *
 * RWTTransformOutputStreamImp is a class template that is derived from one
 * of its own template parameters.
 *
 * The class is defined as
 *
 * \code
 * template <class OutputStream, class FilteredOutputStreamImp,
 *           class Transform>
 *
 * class RWTTransformOutputStreamImp :
 *   public FilteredOutputStreamImp { ...}
 * \endcode
 *
 * The write() method of this class gets called until the entire output
 * stream has been written to the buffer. Then the flush() method gets
 * called, either directly or when the destructor is called. The flush()
 * method calls the transform() method of the transformation object passed
 * into the constructor. The transform() method reads the output stream
 * flushed from the buffer, applies the transformation defined by the
 * method, and writes the result to the sink stream.
 */
template <class OutputStream, class FilteredOutputStreamImp, class Transform>
class RWTTransformOutputStreamImp : public FilteredOutputStreamImp
{

public:
    /**
     * A typedef for the template parameter \c OutputStream which will be
     * used as the sink for elements.
     */
    typedef OutputStream RWOutputStream_type;

    /**
     * In keeping with the pattern for all filtered input streams, the type
     * of character contained by the stream is referred to as the
     * \"#element_type\". Characters in the stream are called "elements"
     * (not to be confused with XML "elements").
     *
     * \note
     * Be aware that characters in the stream are called "elements," which
     * have no connection to XML "elements."
     */
    typedef typename OutputStream::element_type element_type;
    typedef std::basic_string<element_type, std::char_traits<element_type> > string_type;

    //-- Constructs an 'RWTTransformOutputStreamImp' instance that uses 'sinkStream'
    //-- as its sink of elements, and returns a handle to it.
    //-- The internal buffer is dynamically allocated to be of size RW_STREAM_BUFFER_SIZE.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(basic_istream<element_type,char_traits<element_type> >,
    //--                           basic_ostream<element_type>,char_traits<element_type> >&)
    //--
    /**
     * Constructs an RWTTransformOutputStreamImp instance that uses
     * \a sinkStream as its sink of elements, and returns a handle to it.
     * The internal buffer is initialized to be of size
     * #RW_STREAM_BUFFER_SIZE, which is defined as \c 512 bytes. The buffer
     * grows as needed to contain the entire XML document.
     *
     * The parameter \a sinkStream represents the output stream that serves
     * as the sink of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >,
     *           basic_ostream<element_type, char_traits<element_type> >)
     * \endcode
     */
    static OutputStream make(const OutputStream& sinkStream, Transform transform)
    {
        return OutputStream(new RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>(sinkStream, transform));
    }

    //-- Constructs an 'RWTTransformOutputStreamImp' instance that uses 'sinkStream'
    //-- as its sink of elements, and returns a handle to it.
    //-- The internal buffer is dynamically allocated to be of size 'bufSize'.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(basic_istream<element_type,char_traits<element_type> >,
    //--                           basic_ostream<element_type>,char_traits<element_type> >&)
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Constructs an RWTTransformOutputStreamImp instance that uses
     * \a sinkStream as its sink of elements, and returns a handle to it.
     * The internal buffer is initialized to be of size \a bufSize. The
     * buffer grows as needed to contain the entire XML document.
     *
     * The parameter \a sinkStream represents the output stream that serves
     * as the sink of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >,
     *           basic_ostream<element_type, char_traits<element_type> >)
     * \endcode
     *
     * The parameter \a bufSize represents the buffer capacity in number of
     * elements.
     */
    static OutputStream make(const OutputStream& sinkStream, Transform transform, RWSize bufSize)
    {
        return OutputStream(new RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>(sinkStream, transform, bufSize));
    }

    //-- Constructs an 'RWTTransformOutputStreamImp' instance that uses 'sinkStream'
    //-- as its sink of elements, and returns a handle to it.
    //-- The internal buffer is initialized using the pre-allocated element's array of
    //-- size 'bufSize'.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(basic_istream<element_type,char_traits<element_type> >,
    //--                           basic_ostream<element_type>,char_traits<element_type> >&)
    //--
    //--   'buffer': A pre-allocated buffer of size 'bufSize' to be used
    //--   internally by the constructed RWTTransformOutputStreamImp object.
    //--
    /**
     * Constructs an RWTTransformOutputStreamImp instance that uses
     * \a sinkStream as its sink of elements, and returns a handle to it.
     * The internal buffer is initialized using a pre-allocated element's
     * array of size \a bufSize. The buffer grows as needed to contain the
     * entire XML document.
     *
     * The parameter \a sinkStream represents the output stream that serves
     * as the sink of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >,
     *           basic_ostream<element_type, char_traits<element_type> >)
     * \endcode
     *
     * The parameter \a buffer represents a pre-allocated buffer of size
     * \a bufSize to be used internally by the constructed
     * RWTTransformOutputStreamImp object.
     */
    static OutputStream make(const OutputStream& sinkStream, Transform transform, element_type* buffer, RWSize bufSize)
    {
        return OutputStream(new RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>(sinkStream, transform, buffer, bufSize));
    }

    /**
     * Virtual destructor. Throws no exceptions.
     */
    virtual ~RWTTransformOutputStreamImp();

    //-- Writes a single element to the stream.
    //--
    //-- Parameters:
    //--
    //--   'value': The element to be written to the stream.
    //--
    /**
     * Writes a single element to the stream.
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
     * Writes an element array of size \a numElements to the stream. The
     * parameter \a array is a pointer to the first element in the array.
     */
    virtual void write(const element_type* array, RWSize numElements);

    //-- Calls 'flush()', then calls 'close()' on the next processing stream.
    /**
     * Calls flush() and then calls close() on the next processing stream.
     */
    virtual void close();

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
    //--                 transform(basic_istream<element_type,char_traits<element_type> >,
    //--                           basic_ostream<element_type>,char_traits<element_type> >&)
    //--
    /**
     * Initializes the reference to the output stream used as the sink of
     * elements, and the internal buffer, whose capacity is set to
     * #RW_STREAM_BUFFER_SIZE, defined as \c 512 bytes.
     *
     * The parameter \a sinkStream represents the output stream that serves
     * as the sink of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >,
     *           basic_ostream<element_type, char_traits<element_type> >)
     * \endcode
     */
    RWTTransformOutputStreamImp(const OutputStream& sinkStream, Transform transform);

    //-- Initializes the reference to the output stream that will be used as the sink
    //-- of elements, as well as the buffer capacity.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(basic_istream<element_type,char_traits<element_type> >,
    //--                           basic_ostream<element_type>,char_traits<element_type> >&)
    //--
    //--   'bufSize': The buffer capacity in number of elements.
    //--
    /**
     * Initializes the reference to the output stream used as the sink of
     * elements, and the internal buffer capacity, which is set to
     * \a bufSize.
     *
     * The parameter \a sinkStream represents the output stream that serves
     * as the sink of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >,
     *           basic_ostream<element_type, char_traits<element_type> >)
     * \endcode
     *
     * The parameter \a bufSize represents the buffer capacity in number of
     * elements.
     */
    RWTTransformOutputStreamImp(const OutputStream& sinkStream, Transform transform, RWSize bufSize);

    //-- Initializes the reference to the output stream that will be used as the sink
    //-- of elements, as well as the internal buffer.
    //--
    //-- Parameters:
    //--
    //--   'sinkStream': The output stream that will serve as the sink of elements.
    //--
    //--   'transform': The transformation object.  Must provide a public interface of
    //--                 transform(basic_istream<element_type,char_traits<element_type> >,
    //--                           basic_ostream<element_type>,char_traits<element_type> >&)
    //--
    //--   'buffer': A pre-allocated buffer of size 'bufSize' to be used
    //--   internally by the constructed RWTTransformOutputStreamImp object.
    //--
    /**
     * Initializes the reference to the output stream used as the sink of
     * elements, and the internal buffer, which is initialized using a
     * pre-allocated element's array of size \a bufSize.
     *
     * The parameter \a sinkStream represents the output stream that serves
     * as the sink of elements.
     *
     * The parameter \a transform represents the transformation object and
     * must provide a public interface of:
     *
     * \code
     * transform(basic_istream<element_type, char_traits<element_type> >,
     *           basic_ostream<element_type, char_traits<element_type> >)
     * \endcode
     *
     * The parameter \a buffer represents a pre-allocated buffer of size
     * \a bufSize to be used internally by the constructed
     * RWTTransformOutputStreamImp object.
     */
    RWTTransformOutputStreamImp(const OutputStream& sinkStream, Transform transform, element_type* buffer, RWSize bufSize);

    //-- Returns a pointer to the buffer's first element.
    //-- Throws no exceptions.
    /**
     * Returns a pointer to the first element in the output buffer array.
     * Throws no exceptions.
     */
    inline element_type* pbase() const
    {
        return pbeg_;
    }

    //-- Returns a pointer to the buffer's current position.
    //-- Throws no exceptions.
    /**
     * Returns a pointer to the current position in the buffered output
     * sequence. Throws no exceptions.
     */
    inline element_type* pptr() const
    {
        return pnext_;
    }

    //-- Returns a pointer one position past the buffer's last element.
    //-- Throws no exceptions.
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
     * Assigns the first parameter value to \c pbeg_ and \c pnext_, and the
     * second parameter value to \c gend_. These data members represent the
     * beginning of the buffer array, the current position in the array, and
     * the end of the array.
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
     * array position now pointed to is the one returned by pptr().
     */
    inline void pbump(RWSize n);

    //-- Frees the memory associated with the internal buffer if necessary.
    //-- Throws no exceptions.
    /**
     * Frees the memory allocated to the internal buffer, if necessary.
     */
    void freeBuffer();

    /**
     * Sets the buffer size to \a bufsize.
     */
    void setBuffer(RWSize bufsize);

    /**
     * Internal transform function, which gets called by flush() and which
     * then calls the transform() function of the transform object passed in
     * to the constructor.
     */
    virtual void transform();

private:

    bool shouldFree_;

    element_type* pbeg_;
    element_type* pnext_;
    element_type* pend_;

    Transform transform_;

};

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
inline void
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::setp(element_type* pbeg_arg,
        element_type* pend_arg)
{
    pbeg_ = pnext_ = pbeg_arg;
    pend_ = pend_arg;
}

template <class OutputStream, class FilteredOutputStreamImp, class Transform>
inline void
RWTTransformOutputStreamImp<OutputStream, FilteredOutputStreamImp, Transform>::pbump(RWSize n)
{
    pnext_ += n;
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/xmlstreams/RWTTransformOutputStreamImp.cc>
#endif

#endif // rw_xmlstreams_RWTTransformOutputStreamImp_h_
