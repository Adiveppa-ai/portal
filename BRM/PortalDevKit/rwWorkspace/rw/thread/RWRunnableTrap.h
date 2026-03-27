#ifndef __rw_thread_RWRunnableTrap_h__
#define __rw_thread_RWRunnableTrap_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnableTrap.h#1 $
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

  RWRunnableTrap - Handle class for runnable trap.

******************************************************************************/

#include <rw/thread/RWRunnable.h>
#include <rw/functor/RWCallbackScope.h>
#include <rw/pointer/RWHandleBase.h>

class RW_THREAD_GLOBAL RWRunnableTrapImp;

struct RWRunnableExecutionStatePair {

    RWRunnable runnable;
    RWExecutionState state;
    bool operator==(const RWRunnableExecutionStatePair& second) const
    {
        return runnable == second.runnable && state == second.state;
    }
    // Required for stdlib version of RWTValSlist.
    bool operator<(const RWRunnableExecutionStatePair& second) const
    {
        return state < second.state;
    }

};

/**
 * \ingroup threading_package
 *
 * \brief
 * Waits for a number of runnables or threads to reach a certain execution
 * state.
 *
 * RWRunnableTrap allows you to wait for a number of runnables or threads to
 * reach a certain execution state. When you create an RWRunnableTrap you
 * specify the target execution state. This causes any runnable that the
 * trap has been set on to catch the runnable when it reaches the given
 * execution state.
 *
 * Another thread can get each runnable as it reaches the target execution
 * state by calling the getNext() function of the runnable trap. A runnable
 * may be caught by the trap by calling setTrap() and passing in the target
 * runnable. By default the runnable is caught only once, the first time
 * that it enters the execution state. When you set the trap on a runnable
 * you may specify that the runnable be caught repeatedly, each time that it
 * enters the execution state.
 *
 * A common usage of an RWRunnableTrap is to wait for a number of threads to
 * complete execution. This allows you to launch and wait for multiple
 * threads without having to keep track of those threads in an array or
 * other data structure. After a thread is created, but before it is
 * started, it can be added to a runnable trap.
 *
 * The default target execution state is #RW_THR_INITIAL which is the state
 * that a runnable reaches when it completes execution.
 *
 * \example
 * \code
 * #include <rw/thread/RWRunnableTrap.h>
 * #include <rw/thread/RWRunnable.h>
 * #include <rw/thread/RWThreadFunction.h>
 *
 * void function(void);
 *
 * int main()
 * {
 *     RWRunnableTrap rnblTrap = RWRunnableTrap::make();
 *     int i;
 *
 *     for (i = 0; i < 10; i++) {
 *         RWThread thread = RWThreadFunction::make(function);
 *         rnblTrap.setTrap(thread);  // before starting thread!
 *         thread.start();
 *     }
 *
 *     for (i = 0; i < 10; i++) {
 *         RWRunnable rnbl = rnblTrap.getNext();
 *         rnbl.join();
 *     }
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWRunnable
 */
class RW_THREAD_GLOBAL RWRunnableTrap :
    public RWHandleBase
{

public:


    /**
     * Constructs an invalid RWRunnableTrap. If the runnable trap is used
     * without having being initialized, an invalid pointer exception is
     * thrown.
     */
    RWRunnableTrap();


    /**
     * Constructs a static RWRunnableTrap.
     */
    RWRunnableTrap(RWStaticCtor);


    /**
     * Copy constructor.
     */
    RWRunnableTrap(const RWRunnableTrap& second);


    /**
     * Default destructor.
     */
    ~RWRunnableTrap();


    /**
     * Assignment operator.
     */
    RWRunnableTrap&
    operator=(const RWRunnableTrap& second);


    /**
     * Constructs a runnable trap to catch runnables as they reach the given
     * execution state(s). The default is to wait until a runnable finishes
     * execution and returns to its initial state. (See #RWExecutionState.)
     */
    static
    RWRunnableTrap
    make(unsigned long executionStateMask = RW_THR_INITIAL);


    /**
     * Returns \c true if the queue is empty, otherwise \c false.
     */
    bool
    isEmpty(void) const;

    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * Traps the given runnable when it enters #RWExecutionState (specified
     * when the runnable trap was created.) An #RWCallbackScope may be
     * specified as either #RW_CALL_ONCE or #RW_CALL_REPEATEDLY. This
     * determines whether the runnable should enter the trap only once when
     * it enters the target execution state, or repeatedly, each time it
     * enters that state.
     */
    void
    setTrap(RWRunnable runnable, RWCallbackScope scope = RW_CALL_ONCE);

    RW_RESTORE_DEPRECATED_WARNINGS

    /**
     * Gets the next RWRunnable that has entered #RWExecutionState. Blocks
     * if no RWRunnable is trapped.
     */
    RWRunnable
    getNext();


    /**
     * Gets the next RWRunnable that has entered #RWExecutionState. Times
     * out after given \a milliseconds if no RWRunnable is trapped. Returns
     * either #RW_THR_TIMEOUT or #RW_THR_COMPLETED.
     */
    RWWaitStatus
    getNext(RWRunnable& r, unsigned long milliseconds);


    /**
     * Gets the next trapped RWRunnable and the execution state that caused
     * it to be trapped.
     */
    void
    getNext(RWRunnable& r, RWExecutionState& es);


    /**
     * Gets the next trapped RWRunnable and the execution state that caused
     * it to be trapped. Times out after given \a milliseconds if no
     * RWRunnable is trapped. Returns either #RW_THR_TIMEOUT or
     * #RW_THR_COMPLETED.
     */
    RWWaitStatus
    getNext(RWRunnable& r, RWExecutionState& es, unsigned long milliseconds);


    /**
     * Gets the next runnable to reach the target execution state, if one is
     * available. Returns \c true and sets the \a runnable parameter if one
     * could be read, otherwise returns \c false.
     */
    bool
    tryGetNext(RWRunnable& runnable);


    /**
     * Gets the next runnable to reach the target execution state, if one is
     * available. Returns \c true and sets the \a runnable parameter if one
     * could be read, otherwise returns \c false. Sets \a es to the
     * execution state that tripped the trap.
     */
    bool
    tryGetNext(RWRunnable& runnable, RWExecutionState& es);

protected:


    /**
     * \internal
     *
     * Constructs a handle from an \c RWRunnableTrapImp*.
     */
    RWRunnableTrap(RWRunnableTrapImp* runnableTrapImpP);

    // Returns a reference to the body
    RWRunnableTrapImp&
    body(void) const;

};

/*****************************************************************************/

// Helper function for creating RWRunnableTrap.
inline RWRunnableTrap
rwMakeRunnableTrap(unsigned long executionStateMask = RW_THR_INITIAL)
{
    return RWRunnableTrap::make(executionStateMask);
}

/*****************************************************************************/

inline
RWRunnableTrap::RWRunnableTrap(void)
{
}

inline
RWRunnableTrap::RWRunnableTrap(RWStaticCtor)
    :
    RWHandleBase(RW_STATIC_CTOR)
{
}

inline
RWRunnableTrap::RWRunnableTrap(const RWRunnableTrap& second)
    :
    RWHandleBase(second)
{
}

inline
RWRunnableTrap::~RWRunnableTrap(void)
{
}

inline RWRunnableTrap&
RWRunnableTrap::operator=(const RWRunnableTrap& second)
{
    if (&second != this) {
        RWHandleBase::operator=(second);
    }
    return *this;
}

#endif // __rw_thread_RWRunnableTrap_h__
