#ifndef __rw_thread_RWRunnableHandle_h__
#define __rw_thread_RWRunnableHandle_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnableHandle.h#1 $
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

  RWRunnableHandle - Base class for runnable handle classes

  A base "handle" class whose instances may be bound to RWRunnableImp
  instances.  The RWRunnableHandle class provides access to those runnable
  functions that may be called any thread.

*****************************************************************************/

#include <rw/thread/pkgdefs.h>
#include <rw/functor/RWCallbackScope.h>
#include <rw/functor/RWTFunctor.h>
#include <rw/pointer/RWHandleBase.h>
#include <rw/sync/fwd.h>


/**
 * \ingroup threading_package
 *
 * #RWExecutionState values describe the execution states of a runnable
 * object. These values are returned by the getExecutionState() member
 * functions of all runnable handles. A newly constructed runnable starts in
 * #RW_THR_INITIAL. After the application calls RWRunnable::start() on the
 * runnable handle, but before the target executable code is executed, the
 * runnable is in #RW_THR_STARTING. While the runnable is executing its
 * executable code, the runnable is in #RW_THR_RUNNING. After the runnable
 * finishes, it returns to #RW_THR_INITIAL.
 *
 * The other #RWExecutionState values correspond to operations made through
 * the runnable's handle. A runnable enters the #RW_THR_YIELDING or
 * #RW_THR_SLEEPING states only if the runnable handle's methods are called
 * to yield or sleep. The global functions rwYield() or rwSleep() do not
 * change the state of the runnable.
 */
enum RWExecutionState {

    /**
     * Constructed; waiting for start or restart
     */
    RW_THR_INITIAL        = 0x0001,

    /**
     * Runnable started, but has not started executing yet
     */
    RW_THR_STARTING       = 0x0002,

    /**
     * Active, executing
     */
    RW_THR_RUNNING        = 0x0004,

    /**
     * Active; Waiting for RWRunnable::releaseInterrupt()
     */
    RW_THR_INTERRUPTED    = 0x0008,

    /**
     * Active; Waiting for RWThread::resume()
     */
    RW_THR_SUSPENDED      = 0x0010,

    /**
     * Active; Waiting for expiration of sleep period
     */
    RW_THR_SLEEPING       = 0x0020,

    /**
     * Active; Yielded execution to other runnables, waiting for execution
     */
    RW_THR_YIELDING       = 0x0040,

    /**
     * Active; Runnable cancellation in progress (CANCELING replaces
     * RUNNING)
     */
    RW_THR_CANCELING      = 0x0080,

    /**
     * Active; Aborting cancellation (ABORTING replaces CANCELING)
     */
    RW_THR_ABORTING       = 0x0100,

    /**
     * Active; Terminating an RWThread runnable
     */
    RW_THR_TERMINATING    = 0x0200,

    /**
     * Active; Exiting with an exception
     */
    RW_THR_EXCEPTION      = 0x0400,

    /**
     * Active; Server waiting for another runnable to execute
     */
    RW_THR_SERVER_WAIT    = 0x0800,

    // Reserved for future use by Rogue Wave Software
    RW_THR_RESERVED1      = 0x1000,

    // Reserved for future use by Rogue Wave Software
    RW_THR_RESERVED2      = 0x2000,

    // Active; User code called enterUser1() (USER1 replaces RUNNING)
    RW_THR_USER1          = 0x4000,

    // Active; User code called enterUser2() (USER2 replaces RUNNING)
    RW_THR_USER2          = 0x8000,

    // Mask value for all states but initial and starting, used to test
    // for successful startup
    RW_THR_ACTIVE         = 0xFFFC
};

/**
 * \ingroup threading_package
 *
 * #RWCompletionState values describe the completion state of a runnable
 * object. These values are returned by the
 * \ref RWRunnableHandle::getCompletionState() "getCompletionState()" member
 * functions of all runnable handles.
 */
enum RWCompletionState {

    /**
     * Runnable has not yet exited because it has not been started or is
     * still active
     */
    RW_THR_PENDING,

    /**
     * Exited normally with optional exit code
     */
    RW_THR_NORMAL,

    /**
     * Exited with exception
     */
    RW_THR_FAILED,

    /**
     * Exited in response to request for cancellation
     */
    RW_THR_CANCELED,

    /**
     * Exited in response to external termination with optional exit code
     */
    RW_THR_TERMINATED,

    /**
     * Exiting due to unhandled exception or signal (currently shutting down
     * process)
     */
    RW_THR_UNEXPECTED
};

// Forward declarations...
class RW_THREAD_GLOBAL RWRunnableImp;
class RW_THREAD_GLOBAL RWRunnable;

/**
 * \ingroup threading_package
 *
 * \brief
 * Base class from which all \e runnable object handles derive.
 *
 * The RWRunnableHandle class is the base class for all \e runnable object
 * handles.
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
 * The RWRunnableHandle class defines those functions that may be accessed
 * from either inside or outside of a runnable. The RWRunnable class
 * provides an interface for threads executing outside of a runnable. It
 * defines the runnable member functions that may be executed only by an
 * external thread. The thread executing inside of a runnable should access
 * the runnable using the RWRunnableSelf handle class.
 *
 * \sa
 * RWRunnable, RWRunnableSelf
 */
class RW_THREAD_GLOBAL RWRunnableHandle :
    public RWHandleBase
{

public:

    /////////////////////////////////////////////////////////////////////////
    //  The following functions may be called by any thread
    /////////////////////////////////////////////////////////////////////////

    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * Adds a callback to the end of the state-change callback list. The
     * mask parameter \a stateMask is used to choose the runnable state or
     * states for which the callback is to be executed (see
     * #RWExecutionState). The \a scope argument determines whether the
     * callback is called just once or repeatedly. Callbacks are called in
     * FIFO order. Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    void
    addCallback(const RWTFunctor<void(const RWRunnable&, RWExecutionState)>& functor,
                unsigned long stateMask,
                RWCallbackScope scope = RW_CALL_REPEATEDLY);

    RW_RESTORE_DEPRECATED_WARNINGS

    /**
     * Queries the completion state of the runnable. Possible exceptions
     * include RWTHRInvalidPointer and RWTHRInternalError.
     */
    RWCompletionState
    getCompletionState() const;


    /**
     * Queries the current execution state of the runnable. Possible
     * exceptions include RWTHRInvalidPointer and RWTHRInternalError.
     */
    RWExecutionState
    getExecutionState() const;


    /**
     * Queries the runnable to determine whether the runnable has an
     * outstanding interrupt request. Possible exceptions include
     * RWTHRInvalidPointer and RWTHRInternalError.
     */
    bool
    isInterruptRequested() const;


    /**
     * Indicates whether the calling thread is the same thread that is
     * currently executing within this runnable. Possible exceptions include
     * RWTHRInvalidPointer and RWTHRInternalError.
     */
    bool
    isSelf() const;


    /**
     * Indicates whether the specified thread ID \a id refers to the thread
     * that is currently executing within this runnable. Possible exceptions
     * include RWTHRInvalidPointer and RWTHRInternalError.
     */
    bool
    isSelf(const RWThreadId& id) const;


    /**
     * Removes all previously added callback entries that call the specified
     * \a functor. This function locks the runnable object while removing
     * the callback, and unlocks it when done. Possible exceptions include
     * RWTHRInvalidPointer and RWTHRInternalError.
     */
    void
    removeCallback(const RWTFunctor<void(const RWRunnable&, RWExecutionState)>& functor);

    /**
     * Queries for the ID of the thread currently active within the
     * runnable. The exception RWTHRThreadNotActive is thrown if there is no
     * thread executing within the runnable. Possible exceptions include
     * RWTHRInvalidPointer, RWTHRThreadNotActive, and RWTHRInternalError.
     */
    RWThreadId
    threadId() const;

protected:


    /**
     * Constructs an empty (invalid) handle instance.
     */
    RWRunnableHandle();


    /**
     * Constructs a global static handle instance (may be used before
     * constructed).
     */
    RWRunnableHandle(RWStaticCtor);


    /**
     * Constructs a runnable handle with the given implementation.
     */
    RWRunnableHandle(RWRunnableImp* runnableImpP);


    // Bind a new handle instance to the runnable instance, if any,
    // pointed-to by another handle instance
    /**
     * Copy constructor.
     */
    RWRunnableHandle(const RWRunnableHandle& second);


    /**
     * Destructor.
     */
    ~RWRunnableHandle();


#if (RW_THR_COMPILER_VERSION_HP_CPP == 0x00101100)

    // HP cfront-base compiler incorrectly complains about access
    // to the operator= member!  So make it public as workaround...
public:


    // Bind this handle instance to the runnable instance, if any,
    // pointed-to by another handle instance
    RWRunnableHandle&
    operator=(const RWRunnableHandle& second);

protected:

#endif

#if (RW_THR_COMPILER_VERSION_HP_CPP != 0x00101100)

    // Bind this handle instance to the runnable instance, if any,
    // pointed-to by another handle instance
    /**
     * Assignment operator.
     */
    RWRunnableHandle&
    operator=(const RWRunnableHandle& second);

#endif

    // Get a reference to the runnable instance, if any,
    // pointed-to by this handle instance
    RWRunnableImp&
    body(void) const;

};

/*****************************************************************************/

inline
RWRunnableHandle::RWRunnableHandle()
{
}

inline
RWRunnableHandle::RWRunnableHandle(RWStaticCtor)
    :
    RWHandleBase(RW_STATIC_CTOR)
{
}

inline
RWRunnableHandle::RWRunnableHandle(const RWRunnableHandle& second)
    :
    RWHandleBase(second)
{
}

inline
RWRunnableHandle::~RWRunnableHandle()
{
}

inline RWRunnableHandle&
RWRunnableHandle::operator=(const RWRunnableHandle& second)
{
    if (&second != this) {
        RWHandleBase::operator=(second);
    }
    return *this;
}

#endif // __rw_thread_RWRunnableHandle_h__
