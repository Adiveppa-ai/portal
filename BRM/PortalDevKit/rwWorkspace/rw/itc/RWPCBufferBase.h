#ifndef __rw_itc_RWPCBufferBase_h__
#define __rw_itc_RWPCBufferBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWPCBufferBase.h#1 $
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
 *************************************************************************/

#include <rw/itc/pkgdefs.h>
#include <rw/functor/RWTFunctor.h>
#include <rw/sync/RWCondition.h>
#include <rw/sync/RWMutexLock.h>
#include <rw/sync/RWTMonitor.h>
#include <rw/sync/fwd.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4275)
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * Base class for the family of classes that provide buffered
 * producer-consumer synchronization semantics for exchanging data between
 * cooperating threads.
 *
 * RWPCBufferBase is the base class for the family of classes that provide
 * buffered producer-consumer synchronization semantics for exchanging data
 * between cooperating threads.
 *
 * In the producer-consumer synchronization model, reader threads
 * (consumers) are blocked while a buffer is empty, and writer threads
 * (producers) are blocked while a buffer is full. A buffer is considered
 * full when the number of unread entries equals or exceeds a specified
 * maximum capacity.
 *
 * Limit the maximum capacity of a buffer through either a constructor
 * argument or the setCapacity() function. A maximum capacity value of zero
 * results in a buffer that imposes no limit on the number of unread entries
 * that may be inserted.
 *
 * This class provides functions for \e opening and \e closing a buffer
 * instance. By default, buffer instances are constructed in the open state.
 * Any number of threads may read from, or write to, the buffer while the
 * buffer is in the open state. Once closed, any entries that remain in the
 * buffer may be safely read from the buffer, but any attempts to read from
 * the buffer once it is empty, or any attempts to write to the buffer while
 * it is closed, result in an exception being thrown.
 *
 * A closed buffer may be reopened at any time. Attempts to close a buffer
 * that is already closed, or to open a buffer that is already open, are
 * ignored.
 *
 * Single functors may be registered and invoked as \e callback objects for
 * the following buffer events:
 *
 * - \b on-empty A thread calls a read or peek function and finds that it is
 * the first reader to discover that the buffer is empty.
 * - \b on-full A thread calls a write function and finds that it is the
 * first writer to discover that the buffer is full.
 * - \b on-close A thread closes an open buffer.
 * - \b on-open A thread opens a closed buffer.
 *
 * The public functions of this class are internally synchronized, and
 * instances of this class are safe for use in the presence of multiple
 * threads.
 */
class RW_ITC_GLOBAL RWPCBufferBase : public RWTMonitor<RWMutexLock>
{

    // Member Variables
protected:

    size_t maxEntries_;
    size_t waitingReaders_;
    size_t waitingWriters_;

    RWCondition notEmpty_;
    RWCondition notFull_;

    bool hasInvokedEmptyCallback_;
    RWTFunctor<void()> onEmptyCallback_;

    bool hasInvokedFullCallback_;
    RWTFunctor<void()> onFullCallback_;

    bool isOpen_;
    RWTFunctor<void()> onOpenCallback_;
    RWTFunctor<void()> onCloseCallback_;

public:
    /**
     * Sets the maximum capacity of the buffer. The parameter \a maxCapacity
     * is a \c size_t value that specifies the maximum number of unread
     * entries allowed to accumulate within the buffer. Once the number of
     * entries equals or exceeds this number, any thread attempting to write
     * an additional entry is blocked until an entry is removed by a read
     * operation, or until the capacity is increased. A value of zero
     * indicates that the buffer has no capacity limit, and that all write
     * operations should complete without blocking. This function returns a
     * \c size_t value representing the maximum capacity that existed at the
     * time it was called.
     */
    size_t
    setCapacity(size_t maxCapacity);

    /**
     * Returns a \c size_t value representing the current maximum capacity
     * of the buffer. A value of zero indicates that the buffer has no
     * capacity limit.
     */
    size_t
    getCapacity(void) const;

    /**
     * Opens the buffer to allow data transfers. If this function is called
     * on a buffer that is closed, the on-open callback functor is invoked
     * within the calling thread.
     */
    void
    open(void);

    /**
     * Indicates whether the buffer is currently open for reading and
     * writing. Returns a bool value where:
     *
     * - \c true indicates that the buffer is open.
     * - \c false indicates that the buffer is closed.
     */
    bool
    isOpen(void) const;

    /**
     * Closes the buffer to prohibit future data transfers. Any attempt to
     * write to a closed buffer, or to read from a closed buffer that is
     * already empty, produces an exception. Any entries already stored
     * within the buffer at the time of its closing may still be read from
     * without producing an exception.
     *
     * If the buffer is empty and there are threads waiting to peek or to
     * read from the buffer, this function unblocks these threads, and each
     * thread exits its peek or read function with an exception. If the
     * buffer is full and there are threads waiting to write to the buffer,
     * this function unblocks these threads and each exits its write
     * function with an exception.
     */
    void
    close(void);

    /**
     * Removes all entries currently stored in the buffer. If the buffer is
     * full and there are threads waiting to write to the buffer, this
     * function signals these threads that they may now attempt to write.
     */
    void
    flush(void);

    /**
     * Indicates whether or not the buffer contains any entries that may be
     * read. Returns a bool value where:
     *
     * - \c true indicates that the calling thread may read a value from the
     * buffer without blocking, provided no other threads empty the buffer
     * before the caller's attempt to read.
     * - \c false indicates that there are currently no values that may be
     * read from the buffer. If the calling thread attempts to read from the
     * buffer, it is blocked unless another thread writes a readable value
     * into the buffer before the caller's attempt to read.
     */
    bool
    canRead(void) const;

    /**
     * Indicates whether or not the buffer is open and has enough room in
     * which to write another entry. Returns a bool value where:
     *
     * - \c true indicates that the calling thread may write a value to the
     * buffer without blocking, provided no other threads fill the buffer or
     * decrease the maximum capacity of the buffer before the caller's
     * attempt to write.
     * - \c false indicates that the number of entries already equals or
     * exceeds the maximum capacity of the buffer. Any attempt to write to
     * the buffer blocks the writer thread, unless another thread removes
     * one or more readable values from the buffer, or increases the maximum
     * capacity of the buffer before the caller's attempt to write.
     */
    bool
    canWrite(void) const;

    /**
     * Returns a \c size_t value representing the number of entries
     * currently contained in the buffer.
     */
    size_t
    entries(void) const;

    /**
     * Returns the current on-empty callback functor instance, if any. This
     * is an RWTFunctor<void()> handle instance identifying the functor that
     * is invoked when the buffer enters the empty state.
     */
    RWTFunctor<void()>
    getEmptyCallback(void) const;

    /**
     * Registers a callback-functor that is invoked by the first thread that
     * attempts a read or peek operation after the last buffer entry is
     * read, or by a thread that was already waiting within a read or peek
     * operation at the time the callback was registered. Once a
     * callback-functor is invoked by a reader thread, it is not invoked
     * again until there is at least one intervening write operation to take
     * the buffer out of the empty state.
     *
     * The functor instance passed as an argument to this function replaces
     * any previously registered functor instance.
     *
     * The parameter \a onEmptyCallback is an RWTFunctor<void()> handle
     * reference that identifies the functor to be invoked when the buffer
     * enters the empty state.
     */
    void
    setEmptyCallback(const RWTFunctor<void()>& onEmptyCallback);

    /**
     * Returns the current on-full callback functor instance, if any. This
     * is an RWTFunctor<void()> handle instance that identifies the functor
     * to be invoked when the buffer enters the full state.
     */
    RWTFunctor<void()>
    getFullCallback(void) const;

    /**
     * Registers a callback-functor to be invoked by the first thread that
     * attempts a write operation after the buffer reaches its maximum
     * capacity, or by a thread that was already waiting within a write
     * operation at the time the callback was registered. Once a
     * callback-functor is invoked by a writer thread, it is not invoked
     * again until there is at least one intervening read operation to take
     * the buffer out of the full state.
     *
     * The functor instance passed as an argument to this function replaces
     * any previously registered functor instance.
     *
     * The parameter \a onFullCallback is an RWTFunctor<void()> handle
     * reference that identifies the functor to be invoked when the buffer
     * enters the full state.
     */
    void
    setFullCallback(const RWTFunctor<void()>& onFullCallback);

    /**
     * Returns the current on-open callback functor instance, if any. This
     * is an RWTFunctor<void()> handle instance that identifies the functor
     * to be invoked when the buffer is changed from the closed to the
     * opened state. The initial value of this callback-functor is an empty
     * handle instance.
     */
    RWTFunctor<void()>
    getOpenCallback(void) const;

    /**
     * Replaces the callback-functor, if any, to be invoked within the first
     * thread to call open() on the closed buffer instance. Subsequent calls
     * to open() without any intervening calls to close() will not result in
     * the invocation of the functor.
     *
     * The functor instance passed as an argument to this function replaces
     * any previously registered functor instance.
     *
     * The parameter \a onOpenCallback is an RWTFunctor<void()> handle
     * reference that identifies the functor to be invoked when the buffer
     * is changed from the closed to the open state.
     */
    void
    setOpenCallback(const RWTFunctor<void()>& onOpenCallback);

    /**
     * Returns the current on-close callback functor instance, if any. This
     * is an RWTFunctor<void()> handle instance that identifies the functor
     * to be invoked when the buffer is changed from the open to the closed
     * state. The initial value of this callback-functor is an empty handle
     * instance.
     */
    RWTFunctor<void()>
    getCloseCallback(void) const;

    /**
     * Replaces the callback-functor, if any, to be invoked within the first
     * thread to call close() on the open buffer instance. Subsequent calls
     * to close() without any intervening calls to open() will not result in
     * the invocation of the functor.
     *
     * The functor instance passed as an argument to this function replaces
     * any previously registered functor instance.
     *
     * The parameter \a onCloseCallback is an RWTFunctor<void()> handle
     * reference that identifies the functor to be invoked when the buffer
     * is changed from the open to the closed state.
     */
    void
    setCloseCallback(const RWTFunctor<void()>& onCloseCallback);

    /**
     * Virtual destructor.
     */
    virtual
    ~RWPCBufferBase(void);

protected:

    RWPCBufferBase(void);

    RWPCBufferBase(size_t maxCapacity);

    RWPCBufferBase(size_t maxCapacity, bool isOpen);

#if !defined(RW_DISABLE_DEPRECATED)
    bool
    isWriteable(void) const;

    bool
    isReadable(void) const;
#endif

    virtual void
    _flush(void) = 0;

    virtual size_t
    _entries(void) const  = 0;

    virtual bool
    _canRead(void) const;

    virtual bool
    _canWrite(void) const;

};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_itc_RWPCBufferBase_h__
