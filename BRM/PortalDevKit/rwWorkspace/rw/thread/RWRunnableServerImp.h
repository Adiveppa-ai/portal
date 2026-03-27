#ifndef __rw_thread_RWRunnableServerImp_h__
#define __rw_thread_RWRunnableServerImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnableServerImp.h#1 $
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

  RWRunnableServerImp - Thread runnable object that acts as a server for
                         other runnable objects.

******************************************************************************/

#include <rw/thread/RWRunnable.h>
#include <rw/thread/RWRunnableGuard.h>
#include <rw/thread/RWThreadImp.h>
#include <rw/thread/pkgdefs.h>
#include <rw/itc/RWTPCValQueueGuardedPrioritized.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

class RW_THREAD_GLOBAL RWRunnableServerImp :
    public RWThreadImp
{

    friend class RWRunnableServer;

protected:

    // Guarded, Prioritized Queue with Producer-Consumer Synchronization Semantics
    RWTPCValQueueGuardedPrioritized<RWRunnable>   queue_;

    // Construct a server instance with default thread attributes.
    RWRunnableServerImp(void);

    // Construct a server instance with an input queue whose capacity for
    // holding unprocessed runnables is limited to the specified maximum
    // capacity (unlimited by default).
    RWRunnableServerImp(size_t maxCapacity);

    // Construct a server instance with the specified thread attributes
    // and an input queue whose capacity for holding unprocessed runnables
    // is limited to the specified capacity (unlimited by default).
    RWRunnableServerImp(const RWThreadAttribute& serverThreadAttr,
                        size_t maxCapacity = 0);

    // Destructor
    ~RWRunnableServerImp(void);

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

    // Get the next runnable off of the input queue, and if the queue
    // is empty, block until a runnable is queued.
    RWRunnable
    dequeue(void);

    // Define class-specific start behavior
    // (Flushes runnable queue and calls RWThreadImp::_dispathExec())
    virtual
    void
    _dispatchExec(void);

    void
    enqueue(const RWRunnable& runnable);

    RWWaitStatus
    enqueue(const RWRunnable& runnable, unsigned long milliseconds);

    void
    enqueue(const RWRunnable& runnable, const RWRunnableGuard& guard);

    RWWaitStatus
    enqueue(const RWRunnable& runnable, const RWRunnableGuard& guard, unsigned long milliseconds);

    void
    enqueue(long priority, const RWRunnable& runnable);

    RWWaitStatus
    enqueue(long priority, const RWRunnable& runnable, unsigned long milliseconds);

    void
    enqueue(long priority, const RWRunnable& runnable, const RWRunnableGuard& guard);

    RWWaitStatus
    enqueue(long priority, const RWRunnable& runnable, const RWRunnableGuard& guard, unsigned long milliseconds);

    // Releases waiting readers to check the status of
    // guarded runnables in the queue.
    void
    checkGuards(void);

    // Returns the maximum capacity of the runnable input queue.
    // A value of zero indicates that the queue has no capacity limit.
    size_t
    getCapacity(void) const;

    // Get the next runnable to start.
    // This implementation simply calls dequeue resulting in FIFO
    // execution.  Derived classes may wish to override this member
    // to implement other scheduling mechanisms
    virtual
    RWRunnable
    nextRunnable(void);

    // Override the run() member to provide for
    // execution of queued runnables.
    virtual
    void
    run(void);

    // Sets the maximum capacity of the buffer.
    // Accepts a size_t value that specifies the maximum number of
    // unprocessed entries to allow to accumulate within the input queue.
    // Once the number of entries equals or exceeds this number, any
    // thread attempting to enqueue an additional entry will be blocked
    // until an entry is removed by the server thread, or until the
    // capacity is increased.  A value of zero is used to indicate
    // that the queue has no capacity limit, and that all enqueue
    // operations should complete without blocking.
    // Return a size_t value representing the maximum capacity
    // that existed at the time this method was called.
    size_t
    setCapacity(size_t maxCapacity);

    // Request that the server stop execution after it executes
    // the runnables that are currently enqueued...
    void
    stop(void);

private:

    // Prohibit automatic compiler generation of these members

    RWRunnableServerImp(const RWRunnableServerImp&);

    RWRunnableServerImp&
    operator=(const RWRunnableServerImp&);

    // Method that unblocks the server pool thread so that it might process
    // other requests. The RWRunnable monitor mutex will be LOCKED upon entry.
    void
    _wakeup(void);

};

/*****************************************************************************/

inline
RWRunnableServerImp::~RWRunnableServerImp(void)
{
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_thread_RWRunnableServerImp_h__
