#ifndef __rw_thread_RWServerPoolImp_h__
#define __rw_thread_RWServerPoolImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWServerPoolImp.h#1 $
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


/*****************************************************************************

  RWServerPoolImp - Thread runnable object that acts as a multithread-server
                    for other runnable objects.

******************************************************************************/

#include <rw/thread/RWRunnableServer.h>
#include <rw/thread/RWRunnableServerImp.h>
#include <rw/thread/pkgdefs.h>
#include <rw/itc/RWTPCValQueue.h>
#include <rw/functor/RWTFunctor.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

class RW_THREAD_GLOBAL RWServerPoolImp :
    public RWRunnableServerImp
{

    friend class RWServerPool;

public:

    ~RWServerPoolImp(void);

private:

    // The current number of runnable server instances in the pool.
    size_t   currentThreadCount_;

    // The desired number of runnable server instances in the pool.
    size_t   targetThreadCount_;

    // A handle to the thread attribute instance used when creating the
    // runnable server instances for the thread pool.  This value is
    // copied when the pool server is started, so changes to the thread
    // attribute instance, or specification of a new thread attribute
    // instance will have no affect on new pool threads unless the
    // server pool is stopped and restarted.
    RWThreadAttribute initialPoolAttribute_;

    // Local copy of the initial pool attribute instance
    RWThreadAttribute currentPoolAttribute_;

    // Handle for the callback functor that is registered with all
    // runnable server instances in the pool.
    RWTFunctor<void(const RWRunnable&, RWExecutionState)>  callbackFunctor_;

    // List of all runnable server instances in the pool.
    RWTValSlist<RWRunnableServer>    pool_;

    // Queue of runnable servers that are ready and waiting to
    // execute another runnable.
    RWTPCValQueue<RWRunnableServer>   ready_;

protected:

    // Construct a server pool instance with a pool that contains the specified
    // number of threads.  The server pool's main thread and its pool threads
    // will be created with default thread attributes.
    RWServerPoolImp(size_t numThreads);

    // Construct a server pool instance whose pool will contain the specified
    // number of threads, and whose input queue will have its capacity for
    // holding unprocessed runnables limited to the specified maximum.
    // The server pool's main thread and its pool threads will be created
    // with default thread attributes.
    RWServerPoolImp(size_t numThreads,
                    size_t maxCapacity);

    // Construct a server pool instance whose main thread will be created with
    // the specified thread attributes and whose pool will contain the
    // specified number of threads, each created with a default set of
    // thread attributes
    RWServerPoolImp(const RWThreadAttribute& serverThreadAttr,
                    size_t numThreads);

    // Construct a server pool instance whose main thread will be created with
    // the specified thread attributes, and whose pool will contain the
    // specified number of threads, and whose input queue will have its
    // capacity for holding unprocessed runnables limited to the specified
    // maximum.
    RWServerPoolImp(const RWThreadAttribute& serverThreadAttr,
                    size_t numThreads,
                    size_t maxCapacity);

    // Construct a server pool instance whose main thread will be created with
    // default thread attributes, and whose pool will contain the specified
    // number of threads, each created with the specified set of
    // thread attributes.
    RWServerPoolImp(size_t numThreads,
                    const RWThreadAttribute& poolThreadsAttr);

    // Construct a server pool instance whose main thread will be created with
    // default thread attributes, whose pool will contain the specified
    // number of threads, each created with the specified thread attributes,
    // and whose input queue will have its capacity for holding unprocessed
    // runnables limited to the specified maximum.
    RWServerPoolImp(size_t numThreads,
                    const RWThreadAttribute& poolThreadsAttr,
                    size_t maxCapacity);

    // Construct a server pool instance whose main thread will be created with
    // the specified thread attributes, whose pool will contain the specified
    // number of threads, each created with the specified thread attributes.
    RWServerPoolImp(const RWThreadAttribute& serverThreadAttr,
                    size_t numThreads,
                    const RWThreadAttribute& poolThreadsAttr);

    // Construct a server pool instance whose main thread will be created with
    // the specified thread attributes, and whose pool will contain the specified
    // number of threads, each created with the specified thread attributes, and
    // whose input queue will have its capacity for holding unprocessed
    // runnables limited to the specified maximum.
    RWServerPoolImp(const RWThreadAttribute& serverThreadAttr,
                    size_t numThreads,
                    const RWThreadAttribute& poolThreadsAttr,
                    size_t maxCapacity);

    // Virtual method called by requestCancellation() members. Allows
    // this class to define behavior to support cancellation requests.
    // The RWRunnable monitor mutex will be LOCKED upon entry.
    void
    _checkCancellation(void);

    // Virtual method called by requestInterrupt() members. Allows
    // this class to define behavior to support interrupt requests.
    // The RWRunnable monitor mutex will be LOCKED upon entry.
    void
    _checkInterrupt(void);

    // Get a handle to the thread attribute instance specified during
    // server pool construction or the instance specified in the last call
    // to setPoolAttribute().
    RWThreadAttribute
    getPoolAttribute(void);

    // Override the internal _requestCancellation methods
    // in order to first try and cancel the individual pool threads
    // before canceling self.
    virtual
    RWWaitStatus
    _requestCancellation(unsigned long milliseconds);

    virtual
    RWWaitStatus
    _requestCancellation(void);

    // Changes the number of threads within the thread pool.  If the new
    // thread pool size is less than the current size, then a sufficient
    // number of threads will destroyed but only if after they have
    // completed execution of any assigned runnable object.  If the size is
    // greater than the current size, then the pool server thread will
    // create a  sufficient number of new threads and add them to the pool.
    void
    resize(size_t size);

    // Overrides the run() member to provide for the dispatching of enqueued
    // runnables to the runnable servers in the pool.
    virtual
    void
    run(void);

    // Change the thread attribute instance to be used when creating the
    // runnable server instances for the thread pool.  The pool attribute
    // instance is copied when the pool server is started, so changes to
    // the original thread attribute instance, or specification of a new
    // thread attribute instance will have no affect on new pool threads
    // unless the server pool is stopped and restarted.
    void
    setPoolAttribute(const RWThreadAttribute& runnablesServersAttr);

    // Returns the target size for the thread pool.  May be less than or greater
    // than the actual number of runnable server instances in the pool, since the
    // pool server thread may not yet have completed a previously requested
    // expansion or contraction of the thread pool.
    size_t
    size(void) const;

private:

    // Don't allow direct copy construction or assignment

    RWServerPoolImp(const RWServerPoolImp&);

    RWServerPoolImp&
    operator=(const RWServerPoolImp&);

    // Shrink or expand the server pool as required to
    // satisfy the current thread count target.
    void
    adjustPool(void);

    // Cancel the runnable server threads in the pool
    void
    cancelPool(void);

    // Cancel the runnable server threads in the pool
    RWWaitStatus
    cancelPool(unsigned long);

    // Reduce the number of runnable servers in the thread pool
    void
    contract(void);

    // Increase the number of runnable servers in the thread pool
    void
    expand(void);

    // Initialize the server pool instance
    void
    init(void);

    // Get the next runnable server that is ready to execute another runnable,
    // and if no servers are available, blocking in a wait until a server does
    // become available.
    RWRunnableServer
    nextServer(void);

    // Remove a runnable server instance from the pool;
    // Removes instance from internal list, and removes callback from instance.
    void
    remove(RWRunnableServer& server);

    // Add a runnable server to the available-server queue.  This function
    // is called by a functor that is registered as a callback on each
    // runnable server instance in the pool.
    void
    serverReadyCallback(const RWRunnable& server, RWExecutionState state);

    // Method that unblocks the server pool thread so that it might process
    // other requests. The RWRunnable monitor mutex will be LOCKED upon entry.
    void
    _wakeup(void);

};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_thread_RWServerPoolImp_h__
