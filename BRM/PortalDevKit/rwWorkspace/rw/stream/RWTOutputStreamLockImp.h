#ifndef rw_stream_RWTOutputStreamLockImp_h_
#define rw_stream_RWTOutputStreamLockImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTOutputStreamLockImp.h#1 $
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
 * Implements a simple lock stream that can be used with any kind of output
 * stream.
 *
 * The class RWTOutputStreamLockImp implements a simple lock stream that can
 * be used with any kind of output stream. The stream locks its internal
 * synchronization mechanism before forwarding output requests to its
 * associated sink stream, and then unlock the internal synchronization
 * mechanism upon completion. The stream's internal synchronization
 * mechanism is locked using a guard object, ensuring its proper release in
 * the event that an exception is thrown.
 */
template <class OutputStream, class FilteredOutputStreamImp>
class RWTOutputStreamLockImp : public FilteredOutputStreamImp
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
     * Constructs an RWTOutputStreamLockImp instance that uses \a sinkStream
     * as its sink of elements, and returns a handle to it. Throws no
     * exceptions.
     *
     * \param sinkStream
     * The output stream that will serve as the sink of elements.
     */
    static OutputStream make(const OutputStream& sinkStream)
    {
        return OutputStream(new RWTOutputStreamLockImp(sinkStream));
    }

    //-- Destructor.
    //-- Throws no exceptions.
    /**
     * Destructor.
     */
    virtual ~RWTOutputStreamLockImp();

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
     * Calls close() on the next processing stream.
     */
    virtual void close();

    /**
     * Calls flush() on the next processing stream.
     */
    virtual void flush();

    /**
     * Returns \c true to indicate a loss of integrity resulting from an
     * output operation. Throws no exceptions.
     */
    virtual bool isBad() const;

    /**
     * Returns \c true to indicate that an output operation failed to
     * generate the desired data. Throws no exceptions.
     */
    virtual bool isFail() const;

    /**
     * Returns \c true to indicate a stream in a valid state. Throws no
     * exceptions.
     */
    virtual bool isGood() const;

    /**
     * Acquires the stream's internal synchronization mechanism. The
     * acquire() member function returns a handle to the next processing
     * stream.
     */
    virtual OutputStream acquire();

    /**
     * Releases the stream's internal synchronization mechanism.
     */
    virtual void release();

protected:

    /**
     * Initializes the reference to the output stream that will be used as
     * the sink of elements.
     *
     * \param sinkStream
     * The output stream that will serve as the sink of elements.
     */
    RWTOutputStreamLockImp(const OutputStream& sinkStream);

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

template <class OutputStream, class FilteredOutputStreamImp>
inline RWMutexLock&
RWTOutputStreamLockImp<OutputStream, FilteredOutputStreamImp>::getStreamMutex()
{
    return RW_EXPOSE(mutex_);
}

template <class OutputStream, class FilteredOutputStreamImp>
inline RWMutexLock&
RWTOutputStreamLockImp<OutputStream, FilteredOutputStreamImp>::getStreamMutex() const
{
    return RW_EXPOSE(const_cast<RWMutexLock&>(mutex_));
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/stream/RWTOutputStreamLockImp.cc>
#endif

#endif // rw_stream_RWTOutputStreamLockImp_h_
