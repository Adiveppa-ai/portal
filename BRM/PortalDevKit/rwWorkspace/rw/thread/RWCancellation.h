#ifndef __rw_thread_RWCancellation_h__
#define __rw_thread_RWCancellation_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWCancellation.h#1 $
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

  RWCancellation - Handle class for thread cancellation object.

  rwServiceCancellation - global function that calls serviceCancellation on
                           the current runnable.

*****************************************************************************/

#include <rw/thread/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>
#include <rw/threxcept/RWTHRxmsg.h>

// create macro to allow cancellation mechanism in the sync package to
// be enabled.  Also ensures backward compatibility.
/**
 * \relates RWSynchObject
 *
 * Flag to specify cancellation state, defined in the Threading package as
 * \ref rwServiceCancellation() "&rwServiceCancellation".
 */
#define RW_CANCELLATION_ENABLED &rwServiceCancellation

class RW_THREAD_GLOBAL RWCancellationImp;
class RW_THREAD_GLOBAL RWRunnableImp;

/**
 * \ingroup threading_package
 *
 * \brief
 * Represents an exception that is thrown to cancel a thread.
 *
 * RWCancellation is an exception that is thrown to cancel a thread. It may
 * be caught by the thread in order to clean up resources or perform final
 * shutdown operations. Thread cancellation allows an application to stop a
 * thread at a safe point in its execution. Thread cancellation is
 * especially useful for stopping threads that are executing in infinite
 * loops.
 *
 * A thread is \e canceled when an external thread calls
 * \ref RWRunnable::requestCancellation() "requestCancellation()" on the
 * RWRunnable object. The thread cancellation starts when
 * RWRunnableSelf::serviceCancellation() is called from within the canceled
 * thread. If cancellation has been requested on that thread via
 * RWRunnable::requestCancellation(), then an RWCancellation exception is
 * thrown out of RWRunnableSelf::serviceCancellation().
 *
 * RWRunnableSelf::serviceCancellation() is also called implicitly from
 * within the acquire() or wait() methods of a synchronization object, when
 * that synchronization object has been initialized with
 * #RW_CANCELLATION_ENABLED. The global function called
 * rwServiceCancellation() may also be used as a substitute for
 * RWRunnableSelf::serviceCancellation() member function.
 *
 * \example
 * \code
 * #include <rw/thread/RWThreadFunction.h>
 * #include <rw/thread/RWRunnableSelf.h>
 * #include <rw/thread/RWCancellation.h>
 * #include <rw/sync/RWMutexLock.h>
 *
 * RWMutexLock cancelEnabledMutex(RW_CANCELLATION_ENABLED);
 * void func(void)
 * {
 *     RWRunnableSelf currentRunnable = ::rwRunnable();
 *     try {
 *         while (1) {
 *             // Check to see if cancellation has been requested.
 *             // If it has, then an RWCancellation exception
 *             // will be thrown.
 *             currentRunnable.serviceCancellation();
 *             // - OR -
 *             cancelEnabledMutex.acquire();
 *             // - OR -
 *             rwServiceCancellation();
 *
 *             // ...
 *         }
 *     }
 *     catch (RWCancellation&) {
 *         // thread canceled, do any necessary clean up
 *
 *         throw;  // rethrow
 *     }
 * }
 *
 * int main()
 * {
 *     RWThread t = RWThreadFunction::make(func);
 *     t.start();
 *     ::rwSleep(100); // wait 100 milliseconds
 *     t.requestCancellation();
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWRunnable, rwServiceCancellation()
 */
class RW_THREAD_GLOBAL RWCancellation :
    public RWTHRxmsg,
    public RWHandleBase
{

    RW_THR_DECLARE_EXCEPTION(RWCancellation)

    friend class RWRunnableImp;

public:


    /**
     * Constructs a cancellation instance that is targeted at the specified
     * runnable.
     */
    RWCancellation(RWRunnableImp* runnableImpP);

    /**
     * Copy constructor. Required for exception propagation.
     */
    RWCancellation(const RWCancellation& second);

    RWCancellation&
    operator=(const RWCancellation& second);

    // Destructor
    ~RWCancellation(void);

protected:

    // Only RWRunnableImp may access these functions...

    // Acknowledge receipt of cancellation to turn-off
    // automated cancellation abort processing.
    void
    acknowledge(void);

    // Acknowledge receipt of cancellation to turn-off
    // automated cancellation abort processing.
    RWRunnableImp*
    target(void) const;

    // Return reference to RWCancellationImp
    RWCancellationImp&
    body(void) const;
};

/*****************************************************************************/


/**
 * \relates RWSynchObject
 *
 * This function determines the calling thread's current runnable, if any,
 * and calls RWRunnableSelf::serviceCancellation() on that runnable. If
 * cancellation has been requested on the runnable object, then an
 * RWCancellation exception is thrown.
 *
 * Note that this function looks up the current runnable every time it is
 * called. If you need to service cancellation repeatedly, e.g., within a
 * loop, it is more efficient to call the global function rwRunnable() to
 * get an RWRunnableSelf handle for the current runnable, and then call
 * RWRunnableSelf::serviceCancellation() directly on this handle instance
 * each time.
 *
 * \sa
 * RWCancellation, RWRunnableSelf, rwRunnable()
 */
extern RW_THREAD_SYMBOLIC
void
rwServiceCancellation(void);

/*****************************************************************************/

inline
RWCancellation::RWCancellation(const RWCancellation& second)
    : RWTHRxmsg(second),
      RWHandleBase(second)
{
}

inline
RWCancellation::~RWCancellation(void)
{
}

#endif // __rw_thread_RWCancellation_h__
