#ifndef __rw_thread_RWRunnableTrapImp_h__
#define __rw_thread_RWRunnableTrapImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnableTrapImp.h#1 $
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

  RWRunnableTrapImp - Body class for runnable trap.

******************************************************************************/

#include <rw/thread/RWRunnableTrap.h>
#include <rw/thread/pkgdefs.h>
#include <rw/itc/RWTPCValQueue.h>
#include <rw/functor/RWCallbackScope.h>
#include <rw/pointer/RWBodyBase.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

class RW_THREAD_GLOBAL RWRunnableTrapImp :
    public RWBodyBase
{

protected:

    RWTPCValQueue< RWRunnableExecutionStatePair > runnableQueue_;
    unsigned long executionStateMask_;

public:

    // Construct Runnable trap to catch runnables as they reach the
    // given execution state(s). The default is to wait until a
    // runnable finishes execution and returns to its initial
    // state. (See the RWExecutionState enum in runnable.h.)
    RWRunnableTrapImp(unsigned long executionStateMask = RW_THR_INITIAL);

    // Destructor
    ~RWRunnableTrapImp(void);

    // Is the queue empty.
    bool
    isEmpty(void) const;

    RW_SUPPRESS_DEPRECATED_WARNINGS

    // Trap the given runnable when it enters executionState_.
    // An RWCallbackScope may be specified as either RW_CALL_ONCE
    // or RW_CALL_REPEATEDLY. This determines whether the
    // runnable should enter the trap only once, when it enters
    // the target execution state, or repeatedly each time it
    // enters that state.
    void
    setTrap(RWRunnable& runnable, RWCallbackScope scope = RW_CALL_ONCE);

    RW_RESTORE_DEPRECATED_WARNINGS

    // Get next RWRunnable that has entered executionState_.
    // Blocks if no RWRunnable trapped.
    RWRunnable
    getNext(void);

    // Get next RWRunnable that has entered executionState_.
    // Times-out after given milliseconds if no RWRunnable trapped.
    // Returns either RW_THR_TIMEOUT or RW_THR_COMPLETED.
    RWWaitStatus
    getNext(RWRunnable& r, unsigned long milliseconds);

    // Get next RWRunnable that has entered executionState_.
    // Blocks if no RWRunnable trapped. Sets "es" to the
    // execution state that triggered the trap.
    void
    getNext(RWRunnable& r, RWExecutionState& es);

    // Get next trapped RWRunnable and the execution state that caused for
    // it to be trapped. Times-out after given milliseconds if no RWRunnable
    // trapped. Returns either RW_THR_TIMEOUT or RW_THR_COMPLETED.
    RWWaitStatus
    getNext(RWRunnable& r, RWExecutionState& es, unsigned long milliseconds);

    // Get next runnable to reach the target execution state, if one
    // is available. Returns true and sets the runnable parameter if one
    // could be read, otherwise returns false
    bool
    tryGetNext(RWRunnable& runnable);

    // Get next runnable to reach the target execution state, if one
    // is available. Returns true and sets the runnable parameter if one
    // could be read, otherwise returns false. Sets "es" to execution
    // state that triggered the trap.
    bool
    tryGetNext(RWRunnable& runnable, RWExecutionState& es);

private:

    RWRunnableTrapImp(const RWRunnableTrapImp& second);

    RWRunnableTrapImp&
    operator=(const RWRunnableTrapImp& second);

    // Callback function which is called by the runnable when it
    // enters the target state. It "trips" the trap.
    void
    trip(const RWRunnable& r, RWExecutionState es);

};

inline
RWRunnableTrapImp::~RWRunnableTrapImp(void)
{
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_thread_RWRunnableTrapImp_h__
