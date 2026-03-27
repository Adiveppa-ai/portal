#ifndef rw_stream_RWTStreamGuardImp_h_
#define rw_stream_RWTStreamGuardImp_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/stream/RWTStreamGuardImp.h#1 $
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

#include <rw/stream/pkgdefs.h>

class RWCharOutputStream;
class RWByteOutputStream;
class RWDataOutputStream;
class RWUCharOutputStream;
class RWWCharOutputStream;
class RWCharInputStream;
class RWByteInputStream;
class RWDataInputStream;
class RWUCharInputStream;
class RWWCharInputStream;

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup streams_package
 *
 * \brief
 * A simple guard stream that can be used with any kind of input/output
 * stream.
 *
 * The class RWTStreamGuardImp implements a simple guard stream that can be
 * used with any kind of input/output stream. The stream guard acquires the
 * synchronization mechanism provided by its source/sink stream at
 * construction time, and releases it upon destruction. The guard stream
 * doesn't maintain its own synchronization mechanism, but rather uses the
 * one provided by the next processing stream. If the next processing stream
 * doesn't implement any synchronization mechanism, then the stream guard
 * class has no effect. The guard class is generally used in combination
 * with one of the synchronization classes RWSynchronizedByteInputStreamImp,
 * #RWSynchronizedByteOutputStreamImp, RWSynchronizedCharInputStreamImp,
 * #RWSynchronizedCharOutputStreamImp, RWSynchronizedDataInputStreamImp,
 * RWSynchronizedDataOutputStreamImp, RWSynchronizedUCharInputStreamImp,
 * #RWSynchronizedUCharOutputStreamImp, RWSynchronizedWCharInputStreamImp,
 * or #RWSynchronizedWCharOutputStreamImp.
 */
template <class StreamHandle, class FilteredStreamImp>
class RWTStreamGuardImp : public FilteredStreamImp
{

public:

    /**
     * Constructs an RWTStreamGuardImp instance that uses \a stream as its
     * source/sink of elements, and returns a handle to it. Throws no
     * exceptions.
     *
     * \param stream
     * The stream that will serve as the source/sink of elements.
     */
    static StreamHandle make(StreamHandle& stream)
    {
        return StreamHandle(new RWTStreamGuardImp<StreamHandle, FilteredStreamImp>(stream));
    }

    /**
     * Destructor. Releases the lock acquired in the guard stream
     * constructor. If the next processing stream doesn't provide a
     * synchronization mechanism, then the destructor has no effect. Throws
     * no exceptions.
     */
    virtual ~RWTStreamGuardImp();

protected:

    /**
     * Initializes the reference to the stream that will be used as
     * source/sink of elements. Acquires the synchronization mechanism
     * provided by \a stream if any.
     *
     * \param stream
     * The stream that will serve as the source/sink of elements.
     */
    RWTStreamGuardImp(StreamHandle& stream);

    /**
     * Returns a handle to the next processing stream. Throw no exceptions.
     */
    inline StreamHandle& getNextStream();

    /**
     * \copydoc getNextStream()
     */
    inline const StreamHandle& getNextStream() const;

private:

    StreamHandle nextStream_;

};

template <class StreamHandle, class FilteredStreamImp>
inline StreamHandle&
RWTStreamGuardImp<StreamHandle, FilteredStreamImp>::getNextStream()
{
    return RW_EXPOSE(nextStream_);
}

template <class StreamHandle, class FilteredStreamImp>
inline const StreamHandle&
RWTStreamGuardImp<StreamHandle, FilteredStreamImp>::getNextStream() const
{
    return nextStream_;
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/stream/RWTStreamGuardImp.cc>
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_stream_RWTStreamGuardImp_h_
