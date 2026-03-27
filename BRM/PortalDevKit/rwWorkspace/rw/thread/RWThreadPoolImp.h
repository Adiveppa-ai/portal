
#ifndef __rw_thread_RWThreadPoolImp_h__
#define __rw_thread_RWThreadPoolImp_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadPoolImp.h#1 $
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

#include <rw/thread/RWThread.h>
#include <rw/thread/RWThreadAttribute.h>
#include <rw/thread/pkgdefs.h>
#include <rw/itc/RWTPCValQueue.h>
#include <rw/functor/RWTFunctor.h>
#include <rw/pointer/RWBodyBase.h>
#include <rw/sync/RWMutexLock.h>
#include <rw/tools/atomic.h>
#include <rw/tvslist.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \relates RWThreadPool
 *
 * Constant to indicate that dynamic thread pools are not enabled.
 */
const size_t RW_THR_NO_DYNAMIC_THREAD_POOL = 0;

/**
 * \relates RWThreadPool
 *
 * Constant to indicate no timeout value.
 */
const unsigned long RW_THR_NO_TIMEOUT = 0UL;

class RW_THREAD_GLOBAL RWThreadPoolImp : public RWBodyBase
{

    friend class RWThreadPool;

protected:

    // Construct a thread pool instance with a pool that contains from
    // minThreads to maxThreads threads. The actual number
    // of threads will grow and shrink between minThreads and
    // maxThreads depending on the work load. minThreads must be >= 1.
    // The timeout determines how long
    // a thread will wait for work before exiting. The timeout is in
    // milliseconds. The thread pool threads are created with default
    // thread attributes.
    RWThreadPoolImp(size_t minThreads,
                    size_t maxThreads = RW_THR_NO_DYNAMIC_THREAD_POOL,
                    unsigned long timeout = RW_THR_NO_TIMEOUT);

    // Construct a thread pool instance with a pool that contains from
    // minThreads to maxThreads threads each created
    // with the specified thread attributes. The actual number
    // of threads will grow and shrink between minThreads and maxThreads
    // depending on the work load. The timeout determines how long
    // a thread will wait for work before exiting. The timeout is in
    // milliseconds.
    RWThreadPoolImp(size_t minThreads,
                    const RWThreadAttribute& poolThreadsAttr,
                    size_t maxThreads = RW_THR_NO_DYNAMIC_THREAD_POOL,
                    unsigned long timeout = RW_THR_NO_TIMEOUT);

    // Thread pool implementation destructor. Prevents further work
    // from being enqueued on the pool and waits for all pool threads
    // to complete current work.
    ~RWThreadPoolImp();

protected:

    // Returns the number of work entries queued in the work queue.
    size_t
    entries() const;

    size_t
    size() const;

    size_t
    minSize() const;

    size_t
    maxSize() const;

    long unsigned int
    timeout() const;

    RWThreadAttribute
    attribute() const;

protected:

    void
    timeout(long unsigned int);

    void
    enqueue(RWTFunctor<void()> const&);

    bool
    resize(size_t minThreads,
           size_t maxThreads = RW_THR_NO_DYNAMIC_THREAD_POOL);

    void
    stop();

private:

    RWThreadPoolImp(const RWThreadPoolImp&);
    RWThreadPoolImp& operator= (const RWThreadPoolImp&);

private:

    // Pool initialization.
    void
    init();

    // The pool thread's function.
    void
    worker();

    // Removes the executing thread from the pool.
    void
    remove();

private:

    // The current number of threads in the pool
    size_t size_;

    // The minimum number of threads in the pool.
    size_t minSize_;

    // The maximum number of threads in the pool.
    size_t maxSize_;

    // The timeout for the dequeuing operation of the work queue.
    long unsigned int timeout_;

    // An atomic counter to count the number of jobs
    // (running threads + work in the queue).
    RWTAtomic<size_t> jobs_;

    // A handle to the thread attribute instance used when creating the
    // threads for the thread pool.  Thread attributes can not be changed
    // once the thread pool is started.
    RWThreadAttribute threadAttribute_;

    // List of all threads in the pool.
    RWTValSlist< RWThread > threadList_;

    // Lock for threadList_
    RWMutexLock poolLock_;

    // PC queue of functors to be executed by threads in the pool.
    RWTPCValQueue< RWTFunctor<void()> > workQueue_;

    // The functor that is the entry point to worker threads
    RWTFunctor<void()> workerFunctor_;

    // True if the pool can grow and shrink
    bool dynamic_;

};

#if defined(_MSC_VER)
#  pragma warning (pop)
#endif

#endif // __rw_thread_RWThreadPoolImp_h__
