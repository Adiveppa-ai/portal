#ifndef __rw_thread_RWGuardedRunnableQueue_h__
#define __rw_thread_RWGuardedRunnableQueue_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWGuardedRunnableQueue.h#1 $
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

  RWGuardedRunnableQueue - An RWGuardedRunnable  producer-consumer queue.

  RWGuardedRunnableQueue is a producer-consumer queue specialized for
  Runnables. It will only deque an RWRunnable if it has an
  associated guard that evaluates to true, or if there is no associated
  guard.

  These classes are used in the implementation of RWRunnableServer. They
  are not otherwise documented.

******************************************************************************/

#include <rw/thread/RWGuardedRunnable.h>
#include <rw/thread/pkgdefs.h>
#include <rw/itc/RWTPCValQueue.h>

#if defined(RW_DISABLE_DEPRECATED)
#  error RWGuardedRunnable and RWGuardedRunnableQueue are deprecated, \
use the RWTPCValQueue heirarchy classes instead.
#endif

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#  pragma warning(disable : 4275)
#endif


class RW_THREAD_SYMBOLIC RWGuardedRunnableQueue :
    public RWTPCValQueue<RWGuardedRunnable>
{

protected:

    bool guards_;  // true if any guards set

public:

    // Construct an RWGuardedRunnableQueue
    RWGuardedRunnableQueue(size_t maxEntries = 0);

    // Destructor
    ~RWGuardedRunnableQueue(void);

    // Dequeue the next runnable, regardless of whether it is ready
    // to run not.
    RWRunnable
    readRunnable(void);

    // Dequeue the next runnable that is ready for execution.
    RWRunnable
    readReadyRunnable(void);

    // Write a runnable with no guard into the queue. The absence of
    // a guard means that the guard for that runnable always
    // evaluates to true.
    void
    writeRunnable(const RWRunnable& r);

    // Write a runnable and guard into the queue. The guard is a
    // functor which is called to determine whether a runnable is
    // ready to execute.
    void
    writeRunnable(const RWRunnable& r, const RWRunnableGuard& g);

private:

    RWGuardedRunnableQueue(const RWGuardedRunnableQueue& second);

    RWGuardedRunnableQueue&
    operator=(const RWGuardedRunnableQueue& second);

};

/****************************************************************************/

inline
RWGuardedRunnableQueue::RWGuardedRunnableQueue(size_t maxEntries)
    :
    RWTPCValQueue<RWGuardedRunnable>(maxEntries),
    guards_(false)
{
}

inline
RWGuardedRunnableQueue::~RWGuardedRunnableQueue(void)
{
}

inline void
RWGuardedRunnableQueue::writeRunnable(const RWRunnable& r)
{
    RWTPCValQueue<RWGuardedRunnable>::write(RWGuardedRunnable(r));
}

inline void
RWGuardedRunnableQueue::writeRunnable(const RWRunnable& r, const RWRunnableGuard& g)
{
    RW_ASSERT(g.isValid());
    guards_ = true;
    RWTPCValQueue<RWGuardedRunnable>::write(RWGuardedRunnable(r, g));
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_thread_RWGuardedRunnableQueue_h__
