#ifndef rw_stream_RWTInputStreamBufferImp_h_
#define rw_stream_RWTInputStreamBufferImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTInputStreamBufferImp.h#1 $
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
 * Implements a buffer that can be used with any kind of input stream.
 *
 * The class RWTInputStreamBufferImp implements a buffer that can be used
 * with any kind of input stream. The size of the buffer is specified in its
 * static member make() function, which is used to create it.
 */
template <class InputStream, class FilteredInputStreamImp>
class RWTInputStreamBufferImp : public FilteredInputStreamImp
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
     * Constructs an RWTInputStreamBufferImp instance that uses
     * \a sourceStream as its source of elements, and returns a handle to
     * it. The internal buffer is dynamically allocated to be of size
     * #RW_STREAM_BUFFER_SIZE.
     *
     * \param sourceStream
     * The input stream that will serve as the source of elements
     */
    static InputStream make(const InputStream& sourceStream)
    {
        return InputStream(new RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>(sourceStream));
    }

    /**
     * Constructs an RWTInputStreamBufferImp instance that uses
     * \a sourceStream as its source of elements, and returns a handle to
     * it. The internal buffer is dynamically allocated to be of size
     * \a bufSize.
     *
     * \param sourceStream
     * The input stream that will serve as the source of elements.
     *
     * \param bufSize
     * The buffer capacity in number of elements.
     */
    static InputStream make(const InputStream& sourceStream, RWSize bufSize)
    {
        return InputStream(new RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>(sourceStream, bufSize));
    }

    /**
     * Constructs an RWTInputStreamBufferImp instance that uses
     * \a sourceStream as its source of elements, and returns a handle to
     * it. The internal buffer is initialized using the pre-allocated
     * element's array of size \a bufSize.
     *
     * \param sourceStream
     * The input stream that will serve as the source of elements.
     *
     * \param buffer
     * A pre-allocated buffer of size \a bufSize to be used internally by
     * the constructed RWTInputStreamBufferImp object.
     *
     * \param bufSize
     * The buffer capacity in number of elements.
     */
    static InputStream make(const InputStream& sourceStream, element_type* buffer, RWSize bufSize)
    {
        return InputStream(new RWTInputStreamBufferImp<InputStream, FilteredInputStreamImp>(sourceStream, buffer, bufSize));
    }

    //-- Destructor.
    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWTInputStreamBufferImp();

    /**
     * If no character can be obtained from the input sequence, this
     * function returns \c true, otherwise it returns \c false. Throws no
     * exceptions.
     */
    virtual bool isEof() const;

    /**
     * If the stream is in bad state, then this function returns \c true,
     * otherwise it returns \c false. Throws no exceptions.
     */
    virtual bool isBad() const;

    /**
     * If the stream is in fail state, then this function returns \c true,
     * otherwise it returns \c false. Throws no exceptions.
     */
    virtual bool isFail() const;

    /**
     * If the stream is in fail or bad state, then this function returns
     * \c false, otherwise it returns \c true. Throws no exceptions.
     */
    virtual bool isGood() const;

    /**
     * Reads a single element.
     */
    virtual element_type read();

    /**
     * Reads an array of elements. The function returns the actual number of
     * elements read.
     *
     * \param array
     * A pointer to the first element of the array. The array must have been
     * pre-allocated to contain at least \a num elements.
     *
     * \param num
     * The number of elements to be read from the stream.
     */
    virtual RWSize read(element_type* array, RWSize num);

    /**
     * Reads elements until the last element read is equal to \a delim, or
     * \a maxSize elements have been read, or the end of the input sequence
     * is reached. The elements read are stored in \a array. The function
     * returns the actual number of elements read from the stream.
     *
     * \param array
     * A pointer to the array receiving the elements extracted from the
     * stream.
     *
     * \param maxSize
     * The maximum number of elements to be read.
     *
     * \param delim
     * The element value used as a delimiter.
     */
    virtual RWSize readUntil(element_type* array, RWSize maxSize, element_type delim);

    /**
     * Returns the number of elements that can be read from the stream
     * without blocking. Throws no exceptions.
     */
    virtual RWSize available() const;

    /**
     * Skips \a numUnits elements from the input sequence if possible. The
     * function returns the actual number of elements skipped, which can be
     * any value between 0 and \a numUnits.
     *
     * \param numUnits
     * The number of elements to be skipped.
     */
    virtual RWSize skip(RWSize numUnits);


protected:

    /**
     * Initializes the reference to the input stream that will be used as
     * the source of elements, as well as the internal buffer capacity,
     * which will be equal to #RW_STREAM_BUFFER_SIZE.
     *
     * \param sourceStream
     * The input stream that will serve as the source of elements.
     */
    RWTInputStreamBufferImp(const InputStream& sourceStream);

    /**
     * Initializes the reference to the input stream that will be used as
     * the source of elements, as well as the buffer capacity.
     *
     * \param sourceStream
     * The input stream that will serve as the source of elements.
     *
     * \param bufSize
     * The buffer capacity in number of elements.
     */
    RWTInputStreamBufferImp(const InputStream& sourceStream, RWSize bufSize);

    /**
     * Initializes the reference to the input stream that will be used as
     * the source of elements, as well as the internal buffer.
     *
     * \param sourceStream
     * The input stream that will serve as the source of elements.
     *
     * \param buffer
     * A pre-allocated buffer of size \a bufSize to be used internally by
     * the constructed RWTInputStreamBufferImp object.
     *
     * \param bufSize
     * The buffer capacity in number of elements.
     */
    RWTInputStreamBufferImp(const InputStream& sourceStream, element_type* buffer, RWSize bufSize);

    /**
     * Returns a pointer to the buffer first element. Throws no exceptions.
     */
    inline element_type* eback() const
    {
        return gbeg_;
    }

    /**
     * Returns a pointer to the input sequence current position. Throws no
     * exceptions.
     */
    inline element_type* gptr() const
    {
        return gnext_;
    }

    /**
     * Returns a pointer one position past the input sequence last element.
     * Throws no exceptions.
     */
    inline element_type* egptr() const
    {
        return gend_;
    }

    /**
     * Returns a pointer one position past the end of the buffer. Throws no
     * exceptions.
     */
    inline element_type* ebuf() const
    {
        return bufEnd_;
    }

    /**
     * Sets the buffer's pointers. Throws no exceptions.
     *
     * \param gbeg_arg
     * The value to be set in \c gbeg_.
     *
     * \param gcur_arg
     * The value to be set in \c gnext_.
     *
     * \param gend_arg
     * The value to be set in \c gend_.
     */
    inline void setg(element_type* gbeg_arg, element_type* gcur_arg, element_type* gend_arg)
    {
        gbeg_ = gbeg_arg;
        gnext_ = gcur_arg;
        gend_ = gend_arg;
    }

    /**
     * Sets the buffer's end pointer. Throws no exceptions.
     *
     * \param gend_arg
     * The value to be set in \c bufEnd_.
     */
    inline void setBufferEnd(element_type* gend_arg)
    {
        bufEnd_ = gend_arg;
    }

    /**
     * Moves the current get pointer \a n positions forward. Throws no
     * exceptions.
     *
     * \param n
     * The number of elements the current get pointer should be advanced.
     */
    inline void gbump(RWSize n)
    {
        gnext_ += n;
    }

    /**
     * Frees the memory associated with the internal buffer if necessary.
     * Throws no exceptions.
     */
    void freeBuffer();

    /**
     * Fills up the buffer. Returns \c true if there are elements available,
     * otherwise returns \c false. Throws no exceptions.
     */
    bool underflow();

private:

    bool shouldFree_;

    bool isFail_;

    element_type* gbeg_;
    element_type* gnext_;
    element_type* gend_;
    element_type* bufEnd_;

    friend class RWBufferedCharInputStreamImp;
};

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/stream/RWTInputStreamBufferImp.cc>
#endif

#endif // rw_stream_RWTInputStreamBufferImp_h_
