#ifndef __rw_thread_RWThreadPool_h__
#define __rw_thread_RWThreadPool_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadPool.h#1 $
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

#include <rw/thread/RWThreadPoolImp.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/fwd.h>
#include <rw/pointer/RWHandleBase.h>

class RW_THREAD_GLOBAL RWThreadPoolImp;
class RW_THREAD_GLOBAL RWThreadPool;

/**
 * \ingroup threading_package
 *
 * \brief
 * Manages a pool of RWThread instances used to execute work encapsulated as
 * RWTFunctor<void()> functors.
 *
 * The RWThreadPool object manages a pool of RWThread instances that are
 * used to execute work encapsulated as RWTFunctor<void()> functors. A
 * thread pool object, when started, waits for other threads to enqueue work
 * functors for execution.
 *
 * Pool threads dequeue functors and execute them to completion. This
 * process continues until the thread pool object passes out of scope, its
 * destructor is called, or the stop() member function is called.
 *
 * A thread pool can have a fixed number of threads, or its size may grow
 * and shrink dynamically, according to load. The dynamic nature of the pool
 * is controlled by parameters in the make() member function.
 *
 * \example
 * \code
 * #include <iostream>
 * #include <rw/sync/RWMutexLock.h>
 * #include <rw/functor/RWTFunctor.h>
 * #include <rw/thread/RWThreadPool.h>
 *
 * RWMutexLock coutLock;
 *
 * void work()
 * {
 *     RWMutexLock::LockGuard guard(coutLock);
 *     std::cout << "Hi-ho, hi-ho, it's off to work we go" << std::endl;
 * }
 *
 * void play()
 * {
 *     RWMutexLock::LockGuard guard(coutLock);
 *     std::cout << "Catch a wave and you're sittin' on top of the world"
 *               << std::endl;
 * }
 *
 * int main()
 * {
 *     RWThreadPool thrPool = RWThreadPool::make(5);
 *
 *     RWTFunctor<void()> workFunc = work;
 *     RWTFunctor<void()> playFunc = play;
 *
 *     thrPool.enqueue(workFunc);
 *     thrPool.enqueue(playFunc);
 *
 *     // stop after all enqueued functors complete:
 *     thrPool.stop();
 *     return 0;
 * };
 * \endcode
 * \endexample
 *
 * \sa
 * RWThread, RWTFunctor, RWHandleBase::isValid()
 */
class RW_THREAD_GLOBAL RWThreadPool :
    public RWHandleBase
{

    friend class RWThreadPoolImp;

public:

    /**
     * Constructs an empty (invalid) handle.
     */
    RWThreadPool();


    /**
     * Constructs a new external interface handle to the thread pool object
     * that is pointed to by a \a second handle (if any).
     */
    RWThreadPool(const RWThreadPool& second);


    /**
     * Destructor.
     */
    ~RWThreadPool();


    /**
     * Binds this external interface handle to the thread pool object that
     * is pointed to by a \a second handle (if any).
     */
    RWThreadPool&
    operator=(const RWThreadPool& second);


    /**
     * Enqueues a piece of work in the \a functor onto the thread pool. All
     * \c functors must be valid; that is,
     * \ref RWHandleBase::isValid() "functor.isValid()" must return \c true.
     * All exceptions that might be thrown within \a functor must be handled
     * within \a functor.
     *
     * Invalid \c functors and exceptions thrown by \c functors but not
     * caught by \c functors are ignored in the release version of the
     * compiled source code. During initial development, therefore, you
     * should compile source code in debug mode, which throws assertions
     * when invalid \c functors are found or uncaught exceptions are thrown.
     */
    void
    enqueue(const RWTFunctor<void()>& functor);


    /**
     * Returns the number of work entries queued in the thread pool.
     */
    size_t
    entries() const;


    /**
     * Gets a handle to the thread attribute instance specified during
     * thread pool construction.
     */
    RWThreadAttribute
    getPoolAttribute();

    /**
     * Makes a thread pool instance that contains a number of threads from
     * \a minThreads to \a maxThreads, each with the default thread
     * attributes. The actual number of threads grows and shrinks between
     * \a minThreads to \a maxThreads depending on work load. A thread
     * awaits work for at least \a timeout milliseconds before exiting.
     */
    static
    RWThreadPool
    make(size_t minThreads,
         size_t maxThreads = RW_THR_NO_DYNAMIC_THREAD_POOL,
         unsigned long timeout = RW_THR_NO_TIMEOUT);


    /**
     * Makes a thread pool instance that contains a number of threads from
     * \a minThreads to \a maxThreads, each with the specified thread
     * attributes. The actual number of threads grows and shrinks between
     * \a minThreads and \a maxThreads, depending on the work load. A thread
     * awaits work for at least \a timeout milliseconds before exiting.
     *
     * You are responsible for ensuring the suitability of thread pool
     * attributes. For example, a \a poolThreadsAttri start policy of
     * #RW_THR_START_INTERRUPTED would cause RWThreadPool to hang because
     * all of the threads in the thread pool would be waiting for
     * RWRunnable::releaseInterrupt() calls.
     */
    static
    RWThreadPool
    make(size_t minThreads,
         const RWThreadAttribute& poolThreadsAttr,
         size_t maxThreads = RW_THR_NO_DYNAMIC_THREAD_POOL,
         unsigned long timeout = RW_THR_NO_TIMEOUT);


    /**
     * Resizes the thread pool so that it contains at least \a minThreads
     * and at most \a maxThreads. This function fails if \a maxThreads is
     * larger than the number of worker threads (i.e. the value returned by
     * entries()). Otherwise, idle threads are created or destroyed as
     * necessary. Returns \c true if the resize was successful, otherwise
     * \c false.
     */
    bool
    resize(size_t minThreads,
           size_t maxThreads = RW_THR_NO_DYNAMIC_THREAD_POOL);


    /**
     * Returns the size of the thread pool, that is, the number of threads
     * currently in the pool.
     */
    size_t
    size() const;

    // Returns the min size of the thread pool.
    size_t
    minSize(void) const;

    // Returns the min size of the thread pool.
    size_t
    maxSize(void) const;

    long unsigned int
    timeout() const;

    void
    timeout(long unsigned int);

    /**
     * Stops work execution after the thread pool executes all the work that
     * is currently enqueued. No additional work is enqueued after stop() is
     * called.
     */
    void
    stop();

protected:

    // Construct an external interface handle to a RWThreadPoolImp instance
    RWThreadPool(RWThreadPoolImp* threadImpP);

    // Override the parent class body(void) function to provide
    // version that casts to this handle's body class
    RWThreadPoolImp&
    body(void) const;

};

/*****************************************************************************/

inline
RWThreadPool::RWThreadPool()
{
}

inline
RWThreadPool::RWThreadPool(RWThreadPoolImp* imp)
    :
    RWHandleBase(imp)
{
}

inline
RWThreadPool::RWThreadPool(const RWThreadPool& second)
    :
    RWHandleBase(second)
{
}

inline
RWThreadPool::~RWThreadPool()
{
}

inline RWThreadPool&
RWThreadPool::operator=(const RWThreadPool& second)
{
    if (&second != this) {
        RWHandleBase::operator=(second);
    }
    return *this;
}

#endif // __rw_thread_RWThreadPool_h__
