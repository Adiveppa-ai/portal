#ifndef rw_stream_RWTOutputStreamBufferImp_h_
#define rw_stream_RWTOutputStreamBufferImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTOutputStreamBufferImp.h#1 $
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
#include <rw/stream/pkgdefs.h>
#include <memory.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Implements a buffer that can be used with any kind of output stream.
 *
 * The class RWTOutputStreamBufferImp implements a buffer that can be used
 * with any kind of output stream. The size of the buffer is specified in
 * its static member make() function, which is used to create it. The
 * buffer's role is to store elements up to its maximum capacity, and then
 * to forward them to its associated sink stream. The buffer flushes itself
 * upon destruction.
 */
template <class OutputStream, class FilteredOutputStreamImp>
class RWTOutputStreamBufferImp : public FilteredOutputStreamImp
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
     * Constructs an RWTOutputStreamBufferImp instance that uses
     * \a sinkStream as its sink of elements, and returns a handle to it.
     * The internal buffer is dynamically allocated to be of size
     * #RW_STREAM_BUFFER_SIZE.
     *
     * \param sinkStream
     * The output stream that will serve as the sink of elements.
     */
    static OutputStream make(const OutputStream& sinkStream)
    {
        return OutputStream(new RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>(sinkStream));
    }

    /**
     * Constructs an RWTOutputStreamBufferImp instance that uses
     * \a sinkStream as its sink of elements, and returns a handle to it.
     * The internal buffer is dynamically allocated to be of size
     * \a bufSize.
     *
     * \param sinkStream
     * The output stream that will serve as the sink of elements.
     *
     * \param bufSize
     * The buffer capacity in number of elements.
     */
    static OutputStream make(const OutputStream& sinkStream, RWSize bufSize)
    {
        return OutputStream(new RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>(sinkStream, bufSize));
    }

    /**
     * Constructs an RWTOutputStreamBufferImp instance that uses
     * \a sinkStream as its sink of elements, and returns a handle to it.
     * The internal buffer is initialized using the pre-allocated element's
     * array of size \a bufSize.
     *
     * \param sinkStream
     * The output stream that will serve as the sink of elements.
     *
     * \param buffer
     * A pre-allocated buffer of size \a bufSize to be used internally by
     * the constructed RWTOutputStreamBufferImp object.
     *
     * \param bufSize
     * The buffer capacity in number of elements.
     */
    static OutputStream make(const OutputStream& sinkStream, element_type* buffer, RWSize bufSize)
    {
        return OutputStream(new RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>(sinkStream, buffer, bufSize));
    }

    //-- Destructor.
    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWTOutputStreamBufferImp();

    /**
     * Writes a single element to the stream.
     *
     * \param value
     * The element to be written to the stream.
     */
    virtual void write(element_type value);

    /**
     * Writes an array of elements to the stream.
     *
     * \param array
     * A pointer to the first element of the array.
     *
     * \param numElements
     * The number of elements to be written to the stream.
     */
    virtual void write(const element_type* array, RWSize numElements);

    /**
     * Calls flush(), then calls close() on the next processing stream.
     */
    virtual void close();

    /**
     * Flushes the buffer by forwarding its content to the next processing
     * stream.
     */
    virtual void flush();

protected:

    /**
     * Initializes the reference to the output stream that will be used as
     * the sink of elements, as well as the internal buffer capacity, which
     * will be equal to #RW_STREAM_BUFFER_SIZE.
     *
     * \param sinkStream
     * The output stream that will serve as the sink of elements.
     */
    RWTOutputStreamBufferImp(const OutputStream& sinkStream);

    /**
     * Initializes the reference to the output stream that will be used as
     * the sink of elements, as well as the buffer capacity.
     *
     * \param sinkStream
     * The output stream that will serve as the sink of elements.
     *
     * \param bufSize
     * The buffer capacity in number of elements.
     */
    RWTOutputStreamBufferImp(const OutputStream& sinkStream, RWSize bufSize);

    /**
     * Initializes the reference to the output stream that will be used as
     * the sink of elements, as well as the internal buffer.
     *
     * \param sinkStream
     * The output stream that will serve as the sink of elements.
     *
     * \param buffer
     * A pre-allocated buffer of size \a bufSize used internally by the
     * constructed RWTOutputStreamBufferImp object.
     *
     * \param bufSize
     * The buffer capacity in number of elements.
     */
    RWTOutputStreamBufferImp(const OutputStream& sinkStream, element_type* buffer, RWSize bufSize);

    /**
     * Returns a pointer to the buffer's first element. Throws no
     * exceptions.
     */
    inline element_type* pbase() const
    {
        return pbeg_;
    }

    /**
     * Returns a pointer to the buffer's current position. Throws no
     * exceptions.
     */
    inline element_type* pptr() const
    {
        return pnext_;
    }

    /**
     * Returns a pointer one position past the buffer's last element. Throws
     * no exceptions.
     */
    inline element_type* epptr() const
    {
        return pend_;
    }

    /**
     * Sets the buffer's pointers. Throws no exceptions.
     *
     * \param pbeg_arg
     * The value to be set in \c pbeg_ and \c pnext_.
     *
     * \param pend_arg
     * The value to be set in \c pend_.
     */
    inline void setp(element_type* pbeg_arg, element_type* pend_arg);

    /**
     * Moves the current put pointer \a n position forward. Throws no
     * exceptions.
     *
     * \param n
     * The number of elements the current put pointer should be advanced.
     */
    inline void pbump(RWSize n);

    /**
     * Frees the memory associated with the internal buffer if necessary.
     * Throws no exceptions.
     */
    void freeBuffer();

private:

    bool shouldFree_;

    element_type* pbeg_;
    element_type* pnext_;
    element_type* pend_;

};

template <class OutputStream, class FilteredOutputStreamImp>
inline void
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::setp(element_type* pbeg_arg,
        element_type* pend_arg)
{
    pbeg_ = pnext_ = pbeg_arg;
    pend_ = pend_arg;
}

template <class OutputStream, class FilteredOutputStreamImp>
inline void
RWTOutputStreamBufferImp<OutputStream, FilteredOutputStreamImp>::pbump(RWSize n)
{
    pnext_ += n;
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/stream/RWTOutputStreamBufferImp.cc>
#endif

#endif // rw_stream_RWTOutputStreamBufferImp_h_
