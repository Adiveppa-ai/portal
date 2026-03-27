#ifndef __rw_thread_RWRunnableSelf_h__
#define __rw_thread_RWRunnableSelf_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWRunnableSelf.h#1 $
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

  rwRunnable() - Retrieves the current runnable object, if any, that
              the calling thread is executing within.

  RWRunnableSelf - Runnable handle with "internal" runnable interface

  A "handle" class whose instances may be bound to RWRunnableImp instances.
  A RWRunnableSelf instance is used by the thread executing "inside" a
  RWRunnableImp instance to access and manipulate that instance.  Only
  those RWRunnableImp functions that are safe for use by the internal
  thread are made available in the interface of this class.

  rwSleep - puts calling thread to sleep for specified time period.
  rwYield - causes calling thread to yield execution to another thread.
  rwThread - Returns a handle of type RWThreadSelf to the thread object
               associated with the current thread (if any).  The thread handle
               returned should be tested for validity before using if the code
          calling the function does not know if it is running in
          a thread started by one of the library's thread objects.

*****************************************************************************/

#include <rw/thread/RWRunnableHandle.h>
#include <rw/thread/pkgdefs.h>

#if defined(RW_THR_THREAD_API_POSIX)
#  if defined(RW_THR_OS_VERSION_AIX)
#    include <sys/sched.h>
#  else
#    include <sched.h>
#  endif
#endif

#if defined(RW_THR_THREAD_API_POSIX) || \
    defined(RW_THR_THREAD_API_SOLARIS)
#  include <rw/sync/RWCondition.h>
#  include <rw/sync/RWMutexLock.h>
#endif

#if defined(RW_THR_THREAD_API_SOLARIS)
#  include <thread.h>
#endif

#if defined(RW_THR_THREAD_API_WIN32)
extern "C" {

    // Explicit forward declaration of Sleep method to avoid inclusion of
    // windows.h header file.
    __declspec(dllimport) void __stdcall
    Sleep(unsigned long);

}   // extern "C"
#endif

// Forward declarations...
class RW_THREAD_GLOBAL RWThreadSelf;

// RWRunnableSelf is used to reference and access RWRunnableImp instances.
// It provides access to those runnable functions that may be accessed by
// the thread executing "inside" of the runnable instance.
// An RWTHRIllegalAccess exception will be produced if the thread executing
// "outside" a runnable object uses this interface to access its own runnable
// instance.

/**
 * \ingroup threading_package
 *
 * \brief
 * Handle class for a \e runnable object.
 *
 * The RWRunnableSelf class is a handle class for a \e runnable object.
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
 * a runnable will produce an RWTHRInvalidPointer exception.
 *
 * The RWRunnableSelf class provides an interface for the thread executing
 * inside of a runnable. It defines the runnable member functions that may
 * only be executed by the internal thread. Threads executing outside of a
 * runnable should access the runnable using the RWRunnable handle class.
 * The RWRunnableHandle class defines those functions that may be accessed
 * from either inside or outside of a runnable.
 *
 * To retrieve an RWRunnableSelf handle instance for the current runnable,
 * use the rwRunnable() function. You may also convert an RWRunnable handle
 * to an RWRunnableSelf handle by calling the member
 * RWRunnable::getRWRunnableSelf(), but any attempt to violate the thread
 * access restrictions imposed by the separate interfaces will generally
 * result in an RWTHRIllegalAccess exception.
 *
 * \sa
 * RWRunnable, RWRunnableFunction, RWTRunnableIOUFunction, RWRunnableServer,
 * RWServerPool, RWThread, RWThreadFunction, RWTThreadIOUFunction
 */
class RW_THREAD_GLOBAL RWRunnableSelf :
    public RWRunnableHandle
{

    friend class RWRunnableImp; // Give access to protected constructor.
    friend class RWRunnable; // Give access to protected constructor.

public:

    /**
     * Constructs an empty (invalid) handle instance.
     */
    RWRunnableSelf();


    /**
     * Constructs a global static handle instance (may be assigned before it
     * is constructed).
     */
    RWRunnableSelf(RWStaticCtor);


    /**
     * Copy constructor.
     */
    RWRunnableSelf(const RWRunnableSelf& second);

    /**
     * Destructor.
     */
    ~RWRunnableSelf();

    /**
     * Assignment operator.
     */
    RWRunnableSelf&
    operator=(const RWRunnableSelf& second);


    /**
     * Returns an external interface handle bound to the same runnable
     * instance (if any) pointed to by this handle.
     */
    RWRunnable
    getRWRunnable() const;

    /////////////////////////////////////////////////////////////////////////
    //  The following functions may be called by an internal thread only
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
    RWRunnableSelf
    getNestedRunnable() const;


    /**
     * Interrupts the calling thread executing within the runnable until the
     * runnable is released by another thread. Changes execution state to
     * #RW_THR_INTERRUPTED. Possible exceptions include RWTHRInvalidPointer,
     * RWTHRInternalError, and RWTHRIllegalAccess.
     */
    void
    interrupt();


    /**
     * Checks for cancellation requests, throwing an RWCancellation object
     * if cancellation has been requested, and returning otherwise. May
     * result in a change of execution state to #RW_THR_CANCELING. Other
     * possible exceptions include RWTHRInvalidPointer, RWTHRInternalError,
     * and RWTHRIllegalAccess.
     */
    void
    serviceCancellation();


    /**
     * Checks for interrupt requests, blocking the calling thread if an
     * interrupt has been requested and returning immediately if no
     * interrupt requests are pending. May result in a change of execution
     * state to #RW_THR_INTERRUPTED. This function may only be called by an
     * internal thread. Possible exceptions include RWTHRInvalidPointer,
     * RWTHRInternalError, and RWTHRIllegalAccess.
     */
    bool
    serviceInterrupt();

    /**
     * Causes the calling thread, executing within the runnable, to sleep
     * for the specified time period yielding execution to other threads.
     * Temporarily changes the execution state to #RW_THR_SLEEPING while
     * sleeping, then restores the previous execution state. The global
     * function rwSleep() may be used instead of this function, but
     * rwSleep() does not produce any execution state changes in a runnable
     * instance while this member does. Possible exceptions include
     * RWTHRInvalidPointer, RWTHRInternalError, and RWTHRIllegalAccess.
     */
    void
    sleep(unsigned long milliseconds);


    /**
     * Causes the calling thread, executing within the runnable, to yield
     * execution to other threads. Temporarily changes the execution state
     * to #RW_THR_YIELDING, and then restores the previous execution state.
     * The global function rwYield() may be used instead of this function,
     * but rwYield() does not produce any execution state changes in a
     * runnable instance while this member does. Possible exceptions include
     * RWTHRInvalidPointer, RWTHRInternalError, and RWTHRIllegalAccess.
     */
    void
    yield();

    // Puts calling thread to sleep for specified length of time.
    static inline
    void
    systemSleep(unsigned long milliseconds);

    // Causes calling thread to yield execution to another thread.
    static inline
    void
    systemYield(void);

    // Returns a handle of type RWThreadSelf to the thread object associated
    // with the current thread/
    static inline
    RWThreadSelf
    systemThread(void);

protected:

    // Bind a new internal interface handle instance to the runnable
    // object, if any, pointed-to by an external handle instance.
    // This is used by RWRunnable to implement getRWRunnableSelf().
    /**
     * RWRunnableSelf conversion constructor. Constructs a new RWRunnable
     * handle pointed to by \a second.
     */
    RWRunnableSelf(const RWRunnable& second);

    // Register a "nested" runnable object so that it might be notified
    // and serviced during cancellation.  This is done automatically when
    // a runnable is started by a thread created by a RWThreadImp or
    // derived class instance. A runnable is "nested" if its active thread
    // originated or is already executing within another runnable instance.
    bool
    setNestedRunnable(const RWRunnable& runnable) const;

};

/*****************************************************************************/

/**
 * \relates RWRunnableSelf
 *
 * Use this function to put the calling thread to sleep for the specified
 * number of milliseconds (thousandths of a second). Calling this function
 * from within a thread created using the Threads Module will not change the
 * execution state of any runnable associated with that thread. To cause the
 * thread to register a runnable state change for the sleep operation, use
 * the RWRunnableSelf::sleep() member function of the current runnable.
 *
 * \sa
 * RWRunnableSelf::sleep()
 */
extern RW_THREAD_SYMBOLIC
void
rwSleep(unsigned long milliseconds);


/**
 * \relates RWRunnableSelf
 *
 * This function causes the calling thread to yield execution to another
 * thread waiting to be scheduled. The calling thread will be placed back on
 * the queue of runnable threads until the scheduler decides to run it
 * again. Calling this function from within a thread created using the
 * Threads Module will not change the execution state of any runnable
 * associated with that thread. To cause the Threads Module thread to
 * register a runnable state change for the yield operation, use the
 * RWRunnableSelf::yield() member function of the runnable handle.
 */
extern RW_THREAD_SYMBOLIC
void
rwYield();

/**
 * \relates RWThreadSelf
 *
 * This function returns the internal thread handle, of type RWThreadSelf,
 * associated with the current thread (if any). It will return an empty
 * RWThreadSelf handle if the current thread was not started by a Threads
 * Module threaded runnable object. The returned thread handle should be
 * tested for validity, by using the
 * \ref RWThreadSelf::isValid() "isValid()" member, if the code calling the
 * function does not know that it is running in a thread started by a
 * Threads Module thread object.
 *
 * \sa
 * RWThreadSelf
 */
extern RW_THREAD_SYMBOLIC
RWThreadSelf
rwThread();


/**
 * \relates RWRunnableSelf
 *
 * Retrieves an RWRunnableSelf handle for the current runnable object
 * associated with the calling thread. If the calling thread was created by
 * some means other than those provided by the Threads Module, then this
 * function will return an empty runnable handle. If the thread was created
 * by a Threads Module runnable class, then the runnable returned will be
 * the current, inner-most nested runnable. If the code calling this
 * function cannot be sure of the source of the calling thread, then it
 * should test the validity of the returned handle, before using it, by
 * testing the result of a call to the \c isValid() member of the handle.
 *
 * \sa
 * RWRunnableSelf, RWRunnableHandle::isValid()
 */
extern RW_THREAD_SYMBOLIC
RWRunnableSelf
rwRunnable();

/*****************************************************************************/

//static inline
inline void
RWRunnableSelf::systemSleep(unsigned long milliseconds)
{
#if defined(RW_THR_THREAD_API_POSIX) || \
    defined(RW_THR_THREAD_API_SOLARIS)

    try {
        RWMutexLock    dummyMutex;
        RWCondition    dummyCondition(dummyMutex);
        RWCondition::LockGuard guard(dummyCondition);
        dummyCondition.wait(milliseconds);
    }
    catch (...) {
        RW_THREAD_RETHROW_UNKNOWN();

    }

#elif defined(RW_THR_THREAD_API_WIN32)
    ::Sleep(milliseconds);
#endif

}

// static inline
inline void
RWRunnableSelf::systemYield(void)
{
#if defined(RW_THR_THREAD_API_POSIX)
    ::sched_yield();

#elif defined(RW_THR_THREAD_API_SOLARIS)
    ::thr_yield();

#elif defined(RW_THR_THREAD_API_WIN32)
    ::Sleep(0);

#endif

}

/*****************************************************************************/

inline
RWRunnableSelf::RWRunnableSelf()
{
}

inline
RWRunnableSelf::RWRunnableSelf(RWStaticCtor)
    :
    RWRunnableHandle(RW_STATIC_CTOR)
{
}

inline
RWRunnableSelf::RWRunnableSelf(const RWRunnableSelf& second)
    :
    RWRunnableHandle(second)
{
}

inline
RWRunnableSelf::~RWRunnableSelf()
{
}

inline RWRunnableSelf&
RWRunnableSelf::operator=(const RWRunnableSelf& second)
{
    if (&second != this) {
        RWRunnableHandle::operator=(second);
    }
    return *this;
}

#endif // __rw_thread_RWRunnableSelf_h__
