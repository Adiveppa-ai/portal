#ifndef __rw_thread_RWRunnable_h__
#define __rw_thread_RWRunnable_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnable.h#1 $
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

  RWRunnable - Runnable handle with "external" runnable interface

  A "handle" class whose instances may be bound to RWRunnableImp instances.
  A RWRunnable instance is used by threads executing "outside" of a
  RWRunnableImp instance to access and manipulate that instance.  Only
  those RWRunnableImp functions that are safe for use by external threads
  are made available in the interface of this class.

*****************************************************************************/

#include <rw/thread/RWRunnableHandle.h>
#include <rw/thread/RWRunnableSelf.h>
#include <rw/thread/pkgdefs.h>

// RWRunnable is used to reference and access RWRunnableImp instances.
// It provides access to those runnable functions that may be
// accessed by any threads executing "outside" of the runnable
// that is pointed-to by the handle.  An RWTHRIllegalAccess exception
// will be produced if the thread executing "inside" a runnable
// object uses this interface to access its own runnable object.

/**
 * \ingroup threading_package
 *
 * \brief
 * Handle class for a \e runnable object, i.e. one that controls an
 * application's threads of execution.
 *
 * The RWRunnable class is a handle class for a \e runnable object.
 *
 * A runnable object provides the basic mechanisms used to create, control,
 * and monitor the threads of execution within your application. Runnables
 * are used to define the task or activity to be performed by a thread.
 *
 * Each runnable object is reference-counted; a runnable body instance keeps
 * a count of the number of handles that currently reference it. A runnable
 * object is deleted when the last handle that references the body is
 * deleted.
 *
 * The public interface for a runnable is provided by its handle classes.
 * Many of the public functions in a handle simply forward control to a
 * corresponding protected function in the body class. A runnable handle
 * class instance may be empty. Any attempt to use an empty handle to access
 * a runnable produces an RWTHRInvalidPointer exception.
 *
 * The RWRunnable class provides an interface for threads executing outside
 * a runnable. It defines the runnable member functions that may be executed
 * only by an external thread. The thread executing inside of a runnable
 * should access the runnable using the RWRunnableSelf handle class. The
 * RWRunnableHandle class defines those functions that may be accessed from
 * either inside or outside of a runnable.
 *
 * You may convert an RWRunnableSelf handle into an RWRunnable handle by
 * calling the RWRunnableSelf::getRWRunnable() member, but any attempt to
 * violate the thread access restrictions imposed by the separate interfaces
 * will generally result in an RWTHRIllegalAccess exception.
 *
 * The runnable object represented by an RWRunnable is executed by calling
 * start(). A protected virtual \b run() member defines the work or activity
 * to be performed by the runnable object. The start() member defines the
 * form of dispatching to be used in executing the \b run() member,
 * synchronous or asynchronous. Regardless of the dispatching mechanism, the
 * \b run() member is always executed as a consequence of calling start().
 *
 * In a \e synchronous runnable, the thread that calls start() is the same
 * thread that executes \b run(); the flow of control is simply passed
 * internally from the start() member to the \b run() member. By the time
 * the start() function returns, the runnable will have completed, or at
 * least attempted, to perform its specified task.
 *
 * In an \e asynchronous, or \e threaded runnable, a call to start() results
 * in the creation of a new thread of execution. Following creation, this
 * new thread proceeds to execute the \b run() member, freeing the thread
 * that called start() to move on to other things.
 *
 * Only one thread can execute within a runnable at any time. Any attempt to
 * call start() while a thread is executing within the runnable will result
 * in an RWTHRThreadActive exception in the scope of the caller.
 *
 * Once a runnable has been started, any thread can wait for that runnable
 * object to finish by calling the runnable's join() member.
 *
 * If an exception occurs and is propagated out of a runnable's \b run()
 * member, the runnable will catch the exception and store it. Clients of
 * the RWRunnable class can rethrow this exception using the raise() member.
 *
 * Clients of RWRunnable can request cancellation of an active runnable or
 * interrupt the runnable's execution. RWRunnable also provides wait
 * functions that allow another thread to block until the runnable enters an
 * execution state of interest.
 */
class RW_THREAD_GLOBAL RWRunnable :
    public RWRunnableHandle
{

    friend class RWRunnableImp; // Give access to protected constructor.
    friend class RWRunnableSelf; // Give access to protected constructor.

public:


    /**
     * Constructs an empty (invalid) handle.
     */
    RWRunnable();


    /**
     * Constructs a global static handle instance that may be assigned to
     * before construction. The static constructor does not change the
     * instance state.
     */
    RWRunnable(RWStaticCtor);


    /**
     * Binds a new handle to the runnable instance, if any, pointed to by
     * the handle \a second.
     */
    RWRunnable(const RWRunnable& second);


    /**
     * Destructor.
     */
    ~RWRunnable();

    /**
     * Binds \c this to the runnable instance, if any, pointed to by the
     * RWRunnable handle \a second.
     */
    RWRunnable&
    operator=(const RWRunnable& second);


    /**
     * Returns an internal interface bound to the same runnable instance, if
     * any, pointed to by self.
     */
    RWRunnableSelf
    getRWRunnableSelf() const;

    /////////////////////////////////////////////////////////////////////////
    //  The following functions may be called by external threads only
    /////////////////////////////////////////////////////////////////////////

    // Query for an active nested runnable (if any).
    // This function returns a reference to the runnable
    // object this runnable's thread is currently executing within.
    // If thread is only active within the current runnable,
    // then the handle returned will not point to any runnable
    // and will return false if tested by calling the isValid() member.

    /**
     * Returns a handle to the nested runnable object, if any. Possible
     * exceptions include RWTHRInvalidPointer and RWTHRInternalError.
     */
    RWRunnable
    getNestedRunnable() const;


    /**
     * Waits for this runnable to complete execution. Returns immediately if
     * the runnable has already been started, has completed, and is
     * currently inactive. Waits for the runnable to start and then complete
     * if it has not been started. If the runnable object is going to be
     * restarted, this function should be used with care by threads other
     * than the thread starting the runnable; application code will need to
     * synchronize the threads \e starting the runnable with the threads
     * \e joining the runnable so that joining threads know which iteration
     * they are joining. Possible exceptions include RWTHRInvalidPointer,
     * RWTHRIllegalAccess, and RWTHRInternalError.
     */
    void
    join(void);


    /**
     * Waits for this runnable to complete execution or until expiration of
     * the specified timeout period provided by \a milliseconds. Returns
     * immediately if the runnable has already been started, has completed,
     * and is currently inactive. Waits for the runnable to start and then
     * complete if it has not been started. If the runnable object is going
     * to be restarted, this function should be used with care by threads
     * other than the thread starting the runnable, so that joining threads
     * will know which start operation they are joining. Possible exceptions
     * include RWTHRInvalidPointer, RWTHRIllegalAccess, and
     * RWTHRInternalError.
     */
    RWWaitStatus
    join(unsigned long milliseconds);

    /**
     * Throws the exception, if any, stored by the runnable during execution
     * of the associated code. This function simply returns, if no exception
     * was produced during the most recently completed execution of this
     * runnable.
     */
    void
    raise() const;

    // Release the thread executing with the runnable from an interrupt.
    // Changes the execution state to the state assumed by the runnable
    // prior to its entering the interrupted state (typically this state
    // will be RW_THR_RUNNING or one of the user defined states).
    /**
     * Reactivates a thread executing within the runnable which had been
     * interrupted via requestInterrupt(). This function restores the
     * execution state of the runnable to the state it was in prior to being
     * interrupted. Possible exceptions include RWTHRInvalidPointer,
     * RWTHRIllegalAccess, RWTHRThreadActive, and RWTHRInternalError.
     */
    void
    releaseInterrupt();

    // This member checks for a
    // cancellation request, and if found, throws a special exception
    // object called RWCancellation.  This object notifies the runnable
    // instance when it is created and when it is destroyed so that the
    // thread requesting cancellation can be notified of the success or
    // failure of the cancellation attempt.

    // If the cancellation is successful, then this function will have
    // produced a sequence of events that result in the runnable execution
    // changing to RW_THR_CANCELING and then to RW_THR_INITIAL.
    // If the cancellation was aborted, the state will have changed from
    // its current state to RW_THR_CANCELING, then to RW_THR_ABORTING, and
    // will eventually change back to RW_THR_RUNNING.

    // Cancellation starts when the thread running within the runnable
    // instance calls serviceCancellation(). See
    // RWRunnableImp::serviceCancellation()
    /**
     * Requests and waits for the runnable to cancel itself.
     *
     * This function returns #RW_THR_COMPLETED to indicate that the runnable
     * was canceled, exited, or was not active; or returns #RW_THR_ABORTED
     * to indicate that cancellation started but did not complete. Possible
     * exceptions include RWTHRInvalidPointer, RWTHRIllegalAccess, and
     * RWTHRInternalError.
     *
     * A cancellation request cannot be withdrawn; a runnable stays marked
     * as canceled until the next time start() is called.
     */
    RWWaitStatus
    requestCancellation();

    // If the cancellation is successful, then this function will have
    // produced a sequence of events that result in the runnable execution
    // changing to RW_THR_CANCELING and then to RW_THR_INITIAL.
    // If the cancellation was aborted, the state will have changed from
    // its current state to RW_THR_CANCELING, then to RW_THR_ABORTING, and
    // will eventually change back to RW_THR_RUNNING.
    /**
     * Requests and waits for the runnable to cancel itself or until the
     * specified \a milliseconds has passed. This function returns
     * #RW_THR_COMPLETED to indicate that the runnable was canceled, exited,
     * or was not active; #RW_THR_ABORTED to indicate that cancellation
     * started but did not complete (the cancellation exception was caught
     * and destroyed in a catch-block); or #RW_THR_TIMEOUT to indicate that
     * the time-out period elapsed before the runnable completed
     * cancellation.
     *
     * If the cancellation request times out, then the execution state may
     * not have changed at all, or may have changed to #RW_THR_CANCELING, in
     * which case cancellation has already started, and may yet abort or
     * succeed. A cancellation request cannot be withdrawn; a runnable stays
     * marked as canceled until the next time start() is called.
     *
     * Possible exceptions include RWTHRInvalidPointer, RWTHRIllegalAccess,
     * and RWTHRInternalError.
     */
    RWWaitStatus
    requestCancellation(unsigned long milliseconds);


    /**
     * Requests the thread executing within the runnable to interrupt and
     * waits until that request is serviced. To respond to the request for
     * an interrupt, the thread executing within the runnable must call
     * RWRunnableSelf::serviceInterrupt(). The interrupted thread is blocked
     * inside the RWRunnableSelf::serviceInterrupt() call until some other
     * thread releases the interrupt by calling releaseInterrupt().
     *
     * This function returns #RW_THR_ABORTED if the runnable is not active
     * when the call is made, and returns #RW_THR_ACQUIRED if the runnable
     * was successfully interrupted. A return value of #RW_THR_ACQUIRED does
     * not guarantee that the runnable will be in an interrupted state at
     * the point of return. Since any thread may release a runnable from an
     * interrupt, it is possible for a different thread to release the
     * interrupt before this function returns. If the interrupt is serviced,
     * the execution state changes to #RW_THR_INTERRUPTED until the
     * interrupt is released.
     *
     * Possible exceptions include RWTHRInvalidPointer, RWTHRIllegalAccess,
     * and RWTHRInternalError.
     */
    RWWaitStatus
    requestInterrupt();


    /**
     * This function is the same as requestInterrupt(), but allows the
     * application to limit the time the calling thread will wait by
     * specifying \a milliseconds. If the specified interval expires before
     * the interrupt is serviced, this function returns #RW_THR_TIMEOUT.
     * Possible exceptions include RWTHRInvalidPointer, RWTHRIllegalAccess,
     * and RWTHRInternalError.
     */
    RWWaitStatus
    requestInterrupt(unsigned long milliseconds);


    // For RWRunnableImp instances, this causes the calling thread to
    // execute synchronously "within" the runnable object.  For RWThreadImp
    // instances, start() results in the creation of a new thread of
    // execution that will execute "within" the runnable object.
    /**
     * Starts execution of the runnable object. For synchronous
     * implementations (for example, RWRunnableFunction) the associated code
     * executes synchronously within the runnable object, and this function
     * waits for the associated code to complete before returning. For
     * asynchronous implementations (for example, RWThreadFunction) the
     * associated code runs asynchronously within the runnable, and this
     * function returns immediately.
     *
     * Calling start() changes the execution state to #RW_THR_STARTING, and
     * then for synchronous runnables, changes it next to #RW_THR_RUNNING.
     * Asynchronous runnables enter the #RW_THR_INTERRUPTED state shortly
     * before starting, and are then automatically or manually released to
     * #RW_THR_RUNNING.
     *
     * Possible exceptions include RWTHRInvalidPointer, RWTHRThreadActive,
     * RWTHRResourceLimit, and RWTHRInternalError.
     */
    RWCompletionState
    start();


    /**
     * Waits until the runnable object enters an execution state referenced
     * by the mask \a stateMask. The mask is a union of states that causes
     * wait() to unblock and return. The value returned is the execution
     * state value that satisfied the specified mask. Possible exceptions
     * include RWTHRInvalidPointer, RWTHRIllegalAccess, and
     * RWTHRInternalError.
     */
    RWExecutionState
    wait(unsigned long stateMask);


    /**
     * Waits until the runnable object enters a state contained in the mask
     * \a stateMask, or until the time-out period of \a milliseconds has
     * elapsed. The mask is a union of states that causes wait() to unblock
     * and return. If a masked state is entered prior to the expiration of
     * the time-out period, this function writes the state value that
     * satisfied the wait in the state argument location (if not #rwnil),
     * and returns a value of #RW_THR_SIGNALED. If the time-out period
     * elapses without a state change that satisfies the mask, then the
     * function returns #RW_THR_TIMEOUT without changing the storage
     * specified by the \a state argument.
     *
     * Possible exceptions include RWTHRInvalidPointer, RWTHRIllegalAccess,
     * and RWTHRInternalError.
     */
    RWWaitStatus
    wait(unsigned long stateMask,
         RWExecutionState* state,
         unsigned long milliseconds);

protected:

    // Construct an external interface handle to a RWRunnableImp instance
    // Used by derived classes during make operations.
    RWRunnable(RWRunnableImp* runnableImpP);

    // Construct an external interface handle to the runnable
    // object (if any) pointed-to by the internal handle.
    // This is used by RWRunnableSelf to implement getRWRunnable().
    /**
     * RWRunnableSelf conversion constructor. Constructs a new RWRunnable
     * handle pointed to by \a second.
     */
    RWRunnable(const RWRunnableSelf& second);

};

/*****************************************************************************/

inline
RWRunnable::RWRunnable()
{
}

inline
RWRunnable::RWRunnable(RWStaticCtor)
    :
    RWRunnableHandle(RW_STATIC_CTOR)
{
}

inline
RWRunnable::RWRunnable(RWRunnableImp* runnableImpP)
    :
    RWRunnableHandle(runnableImpP)
{
}

inline
RWRunnable::RWRunnable(const RWRunnable& second)
    :
    RWRunnableHandle(second)
{
}

inline
RWRunnable::RWRunnable(const RWRunnableSelf& second)
    :
    RWRunnableHandle(second)
{
}

inline
RWRunnable::~RWRunnable()
{
}

inline RWRunnable&
RWRunnable::operator=(const RWRunnable& second)
{
    if (&second != this) {
        RWRunnableHandle::operator=(second);
    }
    return *this;
}

#endif // __rw_thread_RWRunnable_h__
