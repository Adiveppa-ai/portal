#ifndef __rw_thread_RWServerPool_h__
#define __rw_thread_RWServerPool_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWServerPool.h#1 $
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

#include <rw/thread/RWRunnableServer.h>
#include <rw/thread/RWServerPoolImp.h>
#include <rw/thread/pkgdefs.h>

/**
 * \ingroup threading_package
 *
 * \brief
 * Manages a pool of RWRunnableServer instances used to start runnable
 * objects submitted for execution by other threads.
 *
 * The RWServerPool object is an RWRunnableServer that manages a "pool" of
 * other RWRunnableServer instances that are used to start runnable objects
 * submitted for execution by other threads. A server pool object, when
 * started, waits for other threads to enqueue runnable objects for
 * execution. Each runnable object that the server finds in its internal
 * queue is dequeued and passed to the next available runnable server from
 * the pool. This process continues until the server pool object is
 * interrupted, canceled, or stopped.
 *
 * Runnables may be enqueued with a guard functor, or a priority value, or
 * both.
 *
 * The guard functor is used by the server to determine whether the
 * associated runnable is currently eligible for retrieval and execution. A
 * guarded runnable is not retrieved by the server until that runnable is
 * the first runnable in the queue whose guard evaluates to \c true. Using
 * guards to block runnable execution is important when implementing active
 * objects; guards can be used to ensure that the active object maintains
 * consistent state and preserves any necessary invariants.
 *
 * The priority value is used during write operations to determine a
 * runnable's insertion point within the server's input queue, such that the
 * set of unprocessed and eligible runnables are retrieved in priority order
 * by the server.
 *
 * The number of runnable servers to create for the internal pool may be
 * specified when the server pool instance is created. A server pool
 * instance does not create the RWRunnableServer instances for the pool, and
 * does not process any enqueued runnables until the start() member is
 * called. No runnables may be enqueued until the server pool is started.
 *
 * The size of the runnable server pool may be adjusted after construction
 * using the resize() member.
 *
 * The stop() member is used to initiate server pool shutdown. The server
 * pool continues to dispatch any runnables already enqueued when stop() is
 * called, but no additional runnables may be enqueued after that point.
 * Once the pending runnables have been dispatched, the server pool thread
 * stops and joins with the runnable servers in the pool and then exits. The
 * stop function does not wait for the server to stop; to wait for the
 * server pool thread to complete its shutdown exit, use the join()
 * function.
 *
 * The RWRunnable::requestCancellation() function should be used if the
 * server thread is to stop execution as soon as possible without dequeuing
 * and dispatching any additional runnables.
 *
 * The RWRunnable::requestInterrupt() function can be used to temporarily
 * suspend execution of the server thread.
 *
 * \example
 * \code
 * #include <rw/thread/RWServerPool.h>
 * #include <rw/thread/RWRunnable.h>
 *
 * RWServerPool serverPool(RWServerPool::make(4));
 * serverPool.start();
 * RWRunnable runnable = RWRunnableFunction::make(function);
 * serverPool.enqueue(runnable);
 * // ...
 * serverPool.stop();
 * serverPool.join();
 *
 * // See the servpool.cpp example program for details
 * \endcode
 * \endexample
 *
 * \sa
 * RWRunnable, RWThread, RWRunnableServer, RWThreadAttribute
 */
class RW_THREAD_GLOBAL RWServerPool :
    public RWRunnableServer
{

    friend class RWServerPoolImp;

public:

    /**
     * Constructs an empty (invalid) handle.
     */
    RWServerPool();


    /**
     * Constructs an external interface handle to the server pool object
     * pointed to by a second handle \a second (if any).
     */
    RWServerPool(const RWServerPool& second);


    /**
     * Destructor.
     */
    ~RWServerPool();


    /**
     * Binds this external interface handle to the server pool object, if
     * any, pointed to by a second handle \a second.
     */
    RWServerPool&
    operator=(const RWServerPool& second);


    /**
     * Gets a handle to the thread attribute instance specified during
     * server pool construction or the instance specified in the last call
     * to setPoolAttribute(). May raise RWTHRInvalidPointer or
     * RWTHRInternalError.
     */
    RWThreadAttribute
    getPoolAttribute();


    /**
     * Makes a runnable server pool instance with the specified number of
     * pool threads. The server pool's main thread and its pool threads are
     * created with default thread attributes.
     */
    static
    RWServerPool
    make(size_t numThreads);


    /**
     * Makes a runnable server pool instance with the specified number of
     * pool threads and whose input queue has the specified maximum
     * capacity. The server pool's main thread and its pool threads are
     * created with default thread attributes.
     */
    static
    RWServerPool
    make(size_t numThreads,
         size_t maxCapacity);


    /**
     * Makes a server pool instance whose main thread has the specified
     * thread attributes, and whose pool contains \a numThreads threads,
     * each with a default set of thread attributes.
     */
    static
    RWServerPool
    make(const RWThreadAttribute& serverThreadAttr,
         size_t numThreads);


    /**
     * Makes a server pool instance whose main thread has the specified
     * thread attributes; whose pool contains \a numThreads threads, each
     * with a default set of thread attributes; and whose input queue has
     * the specified maximum capacity.
     */
    static
    RWServerPool
    make(const RWThreadAttribute& serverThreadAttr,
         size_t numThreads,
         size_t maxCapacity);


    /**
     * Makes a server pool instance whose main thread has the default thread
     * attributes, and whose pool contains \a numThreads threads, each with
     * the specified set of thread attributes.
     */
    static
    RWServerPool
    make(size_t numThreads,
         const RWThreadAttribute& poolThreadsAttr);


    /**
     * Makes a server pool instance whose main thread has the default thread
     * attributes; whose pool contains \a numThreads threads, each created
     * with the specified set of thread attributes; and whose input queue
     * has the specified maximum capacity.
     */
    static
    RWServerPool
    make(size_t numThreads,
         const RWThreadAttribute& poolThreadAttr,
         size_t maxCapacity);


    /**
     * Makes a server pool instance whose main thread has the thread
     * attributes specified by the thread attribute object
     * \a serverThreadAttr, and whose pool contains \a numThreads threads,
     * each created with the thread attributes specified by the thread
     * attribute object \a poolThreadsAttr.
     */
    static
    RWServerPool
    make(const RWThreadAttribute& serverThreadAttr,
         size_t numThreads,
         const RWThreadAttribute& poolThreadsAttr);


    /**
     * Makes a server pool instance whose main thread has the thread
     * attributes specified by the thread attribute object
     * \a serverThreadAttr; whose pool contains \a numThreads threads, each
     * created with the thread attributes specified by the thread attribute
     * object \a poolThreadsAttr; and whose input queue has the specified
     * maximum capacity.
     */
    static
    RWServerPool
    make(const RWThreadAttribute& serverThreadAttr,
         size_t numThreads,
         const RWThreadAttribute& poolThreadsAttr,
         size_t maxCapacity);


    /**
     * Changes the number of threads within the thread pool. If the new
     * thread pool size is less than the current size, then a sufficient
     * number of threads are destroyed, but only after they have completed
     * execution of any assigned runnable object. If the size is greater
     * than the current size, the pool server thread creates a sufficient
     * number of new threads and adds them to the pool. May raise
     * RWTHRInvalidPointer or RWTHRInternalError.
     */
    void
    resize(size_t size);


    /**
     * Changes the thread attribute instance used to initialize new runnable
     * server objects as they are created for the thread pool. Changing the
     * pool thread attributes after the server has started will affect only
     * new threads started by the pool server in response to a request for a
     * larger pool size; existing threads continue with their original
     * attributes. May raise RWTHRInvalidPointer or RWTHRInternalError.
     */
    void
    setPoolAttribute(const RWThreadAttribute& poolThreadsAttr);


    /**
     * Returns the target size for the thread pool. May be less than or
     * greater than the actual number of runnable server instances in the
     * pool, since the pool server thread may not yet have completed a
     * previously requested expansion or contraction of the thread pool. May
     * raise RWTHRInvalidPointer or RWTHRInternalError.
     */
    size_t
    size() const;

protected:

    // Construct an external interface handle to a RWServerPoolImp instance
    RWServerPool(RWServerPoolImp* threadImpP);

    // Override the parent class body() function to provide
    // version that casts to this handle's body class
    RWServerPoolImp&
    body(void) const;
};

/*****************************************************************************/

inline
RWServerPool::RWServerPool()
{
}

inline
RWServerPool::RWServerPool(RWServerPoolImp* imp)
    :
    RWRunnableServer(imp)
{
}

inline
RWServerPool::RWServerPool(const RWServerPool& second)
    :
    RWRunnableServer(second)
{
}

inline
RWServerPool::~RWServerPool()
{
}

inline RWServerPool&
RWServerPool::operator=(const RWServerPool& second)
{
    if (&second != this) {
        RWRunnableServer::operator=(second);
    }
    return *this;
}

#endif // __rw_thread_RWServerPool_h__
