/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTRecursiveLock.cc#1 $
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

#include <rw/sync/RWTRecursiveLock.h>

template <class Mutex>
RWTRecursiveLock<Mutex>::RWTRecursiveLock(RWCancellationState state)
    : RWSynchObject(state),
      level_(0)
{
    threadId_.clear();
}

template <class Mutex>
void
RWTRecursiveLock<Mutex>::acquire(void)
{
    // Test for cancellation if enabled...
    testCancellation();

    if (rwIsSelf(threadId_)) {
        ++level_;
    }
    else {
        lock_.acquire();
        threadId_ = rwThreadId();
        level_ = 0;
    }
}

template <class Mutex>
RWWaitStatus
RWTRecursiveLock<Mutex>::acquire(unsigned long milliseconds)
{
    // Test for cancellation if enabled...
    testCancellation();

    RWWaitStatus status = RW_THR_ACQUIRED;

    if (rwIsSelf(threadId_)) {
        ++level_;
    }
    else {
        if (RW_THR_ACQUIRED == (status = lock_.acquire(milliseconds))) {
            threadId_ = rwThreadId();
            level_ = 0;
        }
    }

    return status;
}

#if defined(RW_SYNC_DEBUG)
template <class Mutex>
bool
RWTRecursiveLock<Mutex>::isAcquired(void) const
{
    return ::rwIsSelf(threadId_);
}
#endif

template <class Mutex>
bool
RWTRecursiveLock<Mutex>::tryAcquire(void)
{
    // Test for cancellation if enabled...
    testCancellation();

    bool result = true;

    if (rwIsSelf(threadId_)) {
        ++level_;
    }
    else {
        if (true == (result = lock_.tryAcquire())) {
            threadId_ = rwThreadId();
            level_ = 0;
        }
    }

    return result;
}

template <class Mutex>
void
RWTRecursiveLock<Mutex>::release(void)
{
    static const char msgHeader[] = "RWTRecursiveLock::release - ";

    // Only perform release if owned by thread...
    if (rwIsSelf(threadId_)) {
        if (level_ > 0) {
            --level_;
        }
        else {
            threadId_.clear();
            lock_.release();
        }
    }
    else {
        // USAGE ERROR
        // Failure indicates attempt to release lock that was not
        // acquired by current thread.
        RW_ASSERT(0);
        RWCString msg(msgHeader, sizeof(msgHeader) - 1);
        msg.append(RW_THR_Not_Owner);
        throw RWTHRIllegalUsage(msg);
    }
}
