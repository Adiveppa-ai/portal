#ifndef rw_stream_RWTInputStreamLockImp_h_
#define rw_stream_RWTInputStreamLockImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTInputStreamLockImp.h#1 $
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
#include <rw/sync/RWMutexLock.h>
#include <rw/sync/RWTLockGuard.h>

/**
 * \ingroup streams_package
 *
 * \brief
 * Implements a simple lock stream that can be used with any kind of input
 * stream.
 *
 * The class RWTInputStreamLockImp implements a simple lock stream that can
 * be used with any kind of input stream. The stream locks its internal
 * synchronization mechanism, before forwarding input requests to its
 * associated source stream, and then unlocks the internal synchronization
 * mechanism upon completion. The stream's internal synchronization
 * mechanism is locked using a guard object, ensuring its proper release in
 * the event that an exception is thrown.
 */
template <class InputStream, class FilteredInputStreamImp>
class RWTInputStreamLockImp : public FilteredInputStreamImp
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
     * Constructs an RWTInputStreamLockImp instance that uses
     * \a sourceStream as its source of elements, and returns a handle to
     * it. Throws no exceptions.
     *
     * \param sourceStream
     * The output stream that will serve as the source of elements.
     */
    static InputStream make(const InputStream& sourceStream)
    {
        return InputStream(new RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>(sourceStream));
    }

    //-- Destructor.
    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWTInputStreamLockImp();

    /**
     * Calls close on the next processing stream.
     */
    virtual void close();

    /**
     * If no data can be obtained from the input sequence, this function
     * returns \c true, otherwise it returns \c false. Throws no exceptions.
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

    /**
     * Acquires the stream's internal synchronization mechanism. The
     * acquire() member function returns a handle to the next processing
     * stream.
     */
    virtual InputStream acquire();

    /**
     * Releases the stream's internal synchronization mechanism.
     */
    virtual void release();

protected:

    /**
     * Initializes the reference to the input stream that will be used as
     * the source of elements.
     *
     * \param sourceStream
     * The input stream that will serve as the source of elements.
     */
    RWTInputStreamLockImp(const InputStream& sourceStream);

    /**
     * These functions return the stream's internal synchronization
     * mechanism. They throw no exceptions.
     */
    inline RWMutexLock& getStreamMutex();

    /**
     * \copydoc getStreamMutex()
     */
    inline RWMutexLock& getStreamMutex() const;

private:

    // this should come from the synchronization package
    RWMutexLock mutex_;

};

template <class InputStream, class FilteredInputStreamImp>
inline RWMutexLock&
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::getStreamMutex()
{
    return RW_EXPOSE(mutex_);
}

template <class InputStream, class FilteredInputStreamImp>
inline RWMutexLock&
RWTInputStreamLockImp<InputStream, FilteredInputStreamImp>::getStreamMutex() const
{
    return const_cast<RWMutexLock&>(mutex_);
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/stream/RWTInputStreamLockImp.cc>
#endif

#endif // rw_stream_RWTInputStreamLockImp_h_
