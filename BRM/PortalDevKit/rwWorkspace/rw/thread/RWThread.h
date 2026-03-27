#ifndef __rw_thread_RWThread_h__
#define __rw_thread_RWThread_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThread.h#1 $
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

#include <rw/thread/RWRunnable.h>
#include <rw/thread/RWThreadAttribute.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>

#if defined(RW_THR_THREAD_API_SOLARIS)
//    signal.h is required to define signal value to be used in terminating Solaris threads.
#  include <signal.h>
#  define RW_THR_TERMINATE_SIGNAL  SIGPWR
#endif

#if defined(RW_THR_THREAD_API_SOLARIS) || defined(RW_THR_THREAD_API_POSIX_SUNOS)
#  include <sys/lwp.h>
#endif

#if defined(RW_THR_HAS_SUSPEND_RESUME)
#  include <rw/sync/RWCondition.h>
#endif

/**
 * \ingroup threading_package
 *
 * \brief
 * Handle class for a threaded runnable object.
 *
 * The RWThread class is a handle class for a <em>threaded runnable</em>
 * object, providing an interface for threads that execute outside the
 * threaded runnable.
 *
 * A threaded runnable object provides the basic mechanisms used to create,
 * control, and monitor the threads of execution within your application.
 * Threaded runnables create their own thread to perform some task or
 * activity.
 *
 * Each threaded runnable object is reference-counted; a threaded runnable
 * body instance keeps a count of the number of handles that currently
 * reference it. A runnable object is deleted when the last handle that
 * references the body is deleted.
 *
 * A threaded runnable handle class instance may be empty. Any attempt to
 * use an empty handle to access a threaded runnable produces an
 * RWTHRInvalidPointer exception.
 *
 * The public interface for a threaded runnable is provided by its handle
 * classes. Many of the public functions in a handle simply forward control
 * to a corresponding protected function in the body class.
 *
 * The RWThread class provides an interface for threads executing \e outside
 * of a threaded runnable, defining member functions that may be executed
 * only by an \e external thread. The threads executing \e inside of a
 * threaded runnable should access the runnable using the RWThreadSelf
 * handle class. Functions available from either inside or outside of a
 * threaded runnable are defined in both handle classes.
 *
 * You may also convert an RWThreadSelf handle to an RWThread handle by
 * calling the RWThreadSelf::getRWThread() member, but any attempt to
 * violate the thread access restrictions imposed by the separate interfaces
 * results in an RWTHRIllegalAccess exception.
 *
 * \sa
 * RWThreadSelf, RWRunnable, RWRunnableHandle, RWThreadFunction,
 * RWTThreadIOUFunction, RWRunnableServer, RWServerPool, RWThreadAttribute
 */
class RW_THREAD_GLOBAL RWThread :
    public RWRunnable
{

    friend class RWThreadImp;
    friend class RWThreadSelf;
    friend class RWThreadManagerImp;

public:


    /**
     * Creates an empty RWThread handle. Until this object is bound to a
     * threaded runnable, its \c isValid() member returns \c false.
     */
    RWThread();


    /**
     * Constructor that creates a global static RWThread handle object that
     * may be assigned to before construction. This constructor does not
     * change the static instance.
     */
    RWThread(RWStaticCtor);


    /**
     * Copy constructor. Creates an RWThread object and binds it to the same
     * threaded runnable, if any, pointed to by \a second.
     */
    RWThread(const RWThread& second);


    /**
     * Destructor.
     */
    ~RWThread();


    /**
     * Assignment operator. Binds the handle to the same threaded runnable,
     * if any, pointed to by \a second.
     */
    RWThread&
    operator=(const RWThread& second);


    /**
     * Returns an internal thread interface associated with the thread, if
     * any, associated with self.
     */
    RWThreadSelf
    getRWThreadSelf() const;


    /**
     * Returns a handle to the thread attribute instance used to initialize
     * any threads created by future calls to start(). Use
     * getActiveAttribute() to get a copy of the attribute instance actually
     * used to initialize the most recently started thread.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    RWThreadAttribute
    getAttribute() const;


    /**
     * Replaces the thread attribute instance used to initialize any threads
     * created by future calls to start(). Changing a thread's attribute
     * instance after the thread has been started does not affect its
     * current thread.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    void
    setAttribute(const RWThreadAttribute& second);


    /**
     * Returns a handle to the thread attribute instance used to initialize
     * the most recently created thread. If a thread has not yet been
     * created, returns a copy of a default thread attribute instance.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    RWThreadAttribute
    getActiveAttribute() const;


    // Feature Tests: RW_THR_HAS_PRIORITY,
    //                canGetPriority()
    /**
     * Returns the maximum priority value that may be specified for this
     * thread. At runtime, use canGetPriority() to determine the
     * availability of this feature. At compile time, check to see if
     * \c RW_THR_HAS_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError.
     */
    RWPriority
    getMaxPriority() const;


    // Feature Tests: RW_THR_HAS_PROCESS_SCOPE_PRIORITY,
    //                canGetProcessScopePriority()
    /**
     * Returns the maximum process-scope priority value that may be
     * specified for this thread. At runtime, use
     * canGetProcessScopePriority() to determine the availability of this
     * feature. At compile time, check to see if
     * \c RW_THR_HAS_PROCESS_SCOPE_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError.
     */
    RWPriority
    getMaxProcessScopePriority() const;


    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canGetSystemScopePriority()
    /**
     * Returns the maximum system-scope priority value that may be specified
     * for this thread. At runtime, use canGetSystemScopePriority() to
     * determine the availability of this feature. At compile time, check to
     * see if \c RW_THR_HAS_SYSTEM_SCOPE_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError.
     */
    RWPriority
    getMaxSystemScopePriority() const;


    // Feature Tests: RW_THR_HAS_TIME_SLICE_QUANTUM,
    //                canGetTimeSliceQuantum()
    /**
     * Returns the maximum time-slice quantum value that may be specified
     * for this thread. At runtime, use canGetTimeSliceQuantum() to
     * determine the availability of this feature. At compile time, check to
     * see if \c RW_THR_HAS_TIME_SLICE_QUANTUM is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError.
     */
    unsigned long
    getMaxTimeSliceQuantum() const;


    // Feature Tests: RW_THR_HAS_PRIORITY,
    //                canGetPriority()
    /**
     * Returns the minimum priority value that may be specified for this
     * thread. At runtime, use canGetPriority() to determine the
     * availability of this feature. At compile time, check to see if
     * \c RW_THR_HAS_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError.
     */
    RWPriority
    getMinPriority() const;

    // Feature Tests: RW_THR_HAS_PROCESS_SCOPE_PRIORITY,
    //                canGetProcessScopePriority()
    /**
     * Returns the minimum process-scope priority value that may be
     * specified for this thread. At runtime, use
     * canGetProcessScopePriority() to determine the availability of this
     * feature. At compile time, check to see if
     * \c RW_THR_HAS_PROCESS_SCOPE_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError.
     */
    RWPriority
    getMinProcessScopePriority() const;


    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canGetSystemScopePriority()
    /**
     * Returns the minimum system-scope priority value that may be specified
     * for this thread. At runtime, use canGetSystemScopePriority() to
     * determine the availability of this feature. At compile time, check to
     * see if \c RW_THR_HAS_SYSTEM_SCOPE_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError. and RWTHRInternalError.
     */
    RWPriority
    getMinSystemScopePriority() const;


    // Feature Tests: RW_THR_HAS_TIME_SLICE_QUANTUM,
    //                canGetTimeSliceQuantum()
    /**
     * Returns the minimum time-slice quantum value that may be specified
     * for this thread. At runtime, use canGetTimeSliceQuantum() to
     * determine the availability of this feature. At compile time, check to
     * see if \c RW_THR_HAS_TIME_SLICE_QUANTUM is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError.
     */
    unsigned long
    getMinTimeSliceQuantum() const;


    /**
     * Returns \c true if the getMaxThreads() function is supported in the
     * current environment, otherwise \c false.
     */
    static
    bool
    canGetMaxThreads();


    /**
     * Returns the maximum number of threads that may be created in this
     * environment. This function is not supported in all environments. At
     * runtime, use canGetMaxThreads() to determine whether this feature is
     * available. At compile time, check to see if \c RW_THR_HAS_MAX_THREADS
     * is defined.
     *
     * Possible exceptions include RWTHROperationNotSupported.
     */
    static
    size_t
    getMaxThreads();


    /**
     * Returns \c true if the priority attribute is supported in the current
     * environment and if the getPriority() function can return a legal
     * value under the current circumstances. For example, returns \c true
     * only if \c RW_THR_HAS_PRIORITY is defined and calling functions such
     * as getPriority() and getMaxPriority() can return a legal value under
     * the current circumstances.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    bool
    canGetPriority() const;

    /**
     * Returns \c true if the process-scope priority attribute is supported
     * in the current environment and if the getProcessScopePriority()
     * function can return a legal value under the current circumstances.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    bool
    canGetProcessScopePriority() const;

    /**
     * Returns \c true if the scheduling policy attribute is supported in
     * the current environment and if the getSchedulingPolicy() function can
     * return a legal value under the current circumstances.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    bool
    canGetSchedulingPolicy() const;

    /**
     * Returns \c true if the system-scope priority attribute is supported
     * in the current environment and if the getSystemScopePriority()
     * function can return a legal value under the current circumstances.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    bool
    canGetSystemScopePriority() const;

    /**
     * Returns \c true if the time-slice quantum attribute is supported in
     * the current environment and if the getTimeSliceQuantum() function can
     * return a legal value under the current circumstances.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    bool
    canGetTimeSliceQuantum() const;


    // Feature Tests: RW_THR_HAS_PRIORITY,
    //                canGetPriority()
    /**
     * Returns the current priority for the active thread associated with
     * self. At runtime, use canGetPriority() to determine the availability
     * of this feature. At compile time, check to see if
     * \c RW_THR_HAS_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHRThreadNotActive, and
     * RWTHRInternalError.
     */
    RWPriority
    getPriority() const;


    // Feature Tests: RW_THR_HAS_PROCESS_SCOPE_PRIORITY,
    //                canGetProcessScopePriority()
    /**
     * Returns the current process-scope priority for the active thread
     * associated with self. At runtime, use canGetProcessScopePriority() to
     * determine the availability of this feature. At compile time, check to
     * see if \c RW_THR_HAS_PROCESS_SCOPE_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError.
     */
    RWPriority
    getProcessScopePriority() const;


    // Feature Tests: RW_THR_HAS_SCHEDULING_POLICY,
    //                canGetSchedulingPolicy()
    /**
     * Returns the current scheduling policy for the active thread
     * associated with self. At runtime, use canGetSchedulingPolicy() to
     * determine the availability of this feature. At compile time, check to
     * see if \c RW_THR_HAS_SCHEDULING_POLICY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHRThreadNotActive, and
     * RWTHRInternalError.
     */
    RWSchedulingPolicy
    getSchedulingPolicy() const;


    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canGetSystemScopePriority()
    /**
     * Returns the current system-scope priority for the active thread
     * associated with self. At runtime, use canGetSystemScopePriority() to
     * determine the availability of this feature. At compile time, check to
     * see if \c RW_THR_HAS_SYSTEM_SCOPE_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError.
     */
    RWPriority
    getSystemScopePriority() const;


    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canGetSystemScopePriority()
    /**
     * Returns the current time-slice quantum value for the active thread
     * associated with self. At runtime, use canGetTimeSliceQuantum() to
     * determine the availability of this feature. At compile time, check to
     * see if \c RW_THR_HAS_TIME_SLICE_QUANTUM is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, and RWTHRInternalError.
     */
    unsigned long
    getTimeSliceQuantum() const;


    /**
     * Returns \c true if the priority attribute is supported in the current
     * environment and if the function setPriority() is callable under the
     * current circumstances. For example, returns \c true only if
     * \c RW_THR_HAS_PRIORITY is defined and calling setPriority() is
     * supported under the current options. In addition, the function
     * returns \c true only if both the calling thread and process have
     * sufficient privileges to perform the requested operation.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    bool
    canSetPriority() const;

    /**
     * Returns \c true if the process-scope priority attribute is supported
     * in the current environment and if the function
     * setProcessScopePriority() is callable under the current
     * circumstances. For example, returns \c true only if
     * \c RW_THR_HAS_PROCESS_SCOPE_PRIORITY is defined and calling
     * setProcessScopePriority() is supported under the current options. In
     * addition, the function returns \c true only if both the calling
     * thread and process have sufficient privileges to perform the
     * requested operation.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    bool
    canSetProcessScopePriority() const;

    /**
     * Returns \c true if the scheduling-policy attribute is supported in
     * the current environment and if the function setSchedulingPolicy() is
     * callable under the current circumstances. For example, returns
     * \c true only if \c RW_THR_HAS_SCHEDULING_POLICY is defined and
     * calling setSchedulingPolicy() is supported under the current options.
     * In addition, the function returns \c true only if both the calling
     * thread and process have sufficient privileges to perform the
     * requested operation.
     *
     * Possible exceptions include RWTHRInvalidPointer, RWTHRInternalError,
     * and RWTHRBoundsError.
     */
    bool
    canSetSchedulingPolicy(RWSchedulingPolicy policy) const;

    /**
     * Returns \c true if the system-scope priority attribute is supported
     * in the current environment and if the function
     * setSystemScopePriority() is callable under the current circumstances.
     * For example, returns \c true only if
     * \c RW_THR_HAS_SYSTEM_SCOPE_PRIORITY is defined and calling
     * setSystemScopePriority() is supported under the current options. In
     * addition, the function returns \c true only if both the calling
     * thread and process have sufficient privileges to perform the
     * requested operation.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    bool
    canSetSystemScopePriority() const;

    /**
     * Returns \c true if the time-slice quantum attribute is supported in
     * the current environment and if the function setTimeSliceQuantum() is
     * callable under the current circumstances. For example, returns
     * \c true only if \c RW_THR_HAS_TIME_SLICE_QUANTUM is defined and
     * calling setTimeSliceQuantum() is supported under the current options.
     * In addition, the function returns \c true only if both the calling
     * thread and process have sufficient privileges to perform the
     * requested operation.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    bool
    canSetTimeSliceQuantum() const;


    // Feature Tests: RW_THR_HAS_PRIORITY,
    //                canSetPriority()
    /**
     * Changes the priority of thread associated with self. At runtime, use
     * canSetPriority() to determine the availability of this feature. At
     * compile time, check to see if \c RW_THR_HAS_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, RWTHRBoundsError, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    void
    setPriority(RWPriority priority);


    // Feature Tests: RW_THR_HAS_PROCESS_SCOPE_PRIORITY,
    //                canSetProcessScopePriority()
    /**
     * Changes the process-scope priority of the thread associated with
     * self. At runtime, use canSetProcessScopePriority() to determine the
     * availability of this feature. At compile time, check to see if
     * \c RW_THR_HAS_PROCESS_SCOPE_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, RWTHRBoundsError, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    void
    setProcessScopePriority(RWPriority priority);


    // Feature Tests: RW_THR_HAS_SCHEDULING_POLICY,
    //                canSetSchedulingPolicy()
    /**
     * Changes the scheduling policy of the thread associated with self. At
     * runtime, use canSetSchedulingPolicy%(\a policy) to determine the
     * availability of this feature. At compile time check to see if
     * \c RW_THR_HAS_SCHEDULING_POLICY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, RWTHRBoundsError, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    void
    setSchedulingPolicy(RWSchedulingPolicy policy);


    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canSetSystemScopePriority()
    /**
     * Changes the system-scope priority of the thread associated with self.
     * At runtime, use canSetSystemScopePriority() to determine the
     * availability of this feature. At compile time, check to see if
     * \c RW_THR_HAS_SYSTEM_SCOPE_PRIORITY is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, RWTHRBoundsError, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    void
    setSystemScopePriority(RWPriority priority);


    // Feature Tests: RW_THR_HAS_TIME_SLICE_QUANTUM,
    //                canSetTimeSliceQuantum()
    /**
     * Changes the time-slice quantum value of the thread associated with
     * self. At runtime, use canSetTimeSliceQuantum() to determine the
     * availability of this feature. At compile time, check to see if
     * \c RW_THR_HAS_TIME_SLICE_QUANTUM is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHROperationNotAvailable,
     * RWTHRThreadNotActive, RWTHRBoundsError, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    void
    setTimeSliceQuantum(unsigned long milliseconds);


    /**
     * Returns \c true if the current environment supports the suspend() and
     * resume() members functions, otherwise \c false.
     */
    static
    bool
    canSuspendResume();


    // Feature Tests: RW_THR_HAS_SUSPEND_RESUME,
    //                canSuspendResume()
    /**
     * Suspends the execution of the thread associated with self until a
     * matching resume() operation is performed.
     *
     * \warning Use of this function may produce unexpected deadlock (see
     * the <em>Threads User's Guide</em> for more information). For
     * deadlock-safe suspension, use
     * \ref RWRunnable::requestInterrupt() "requestInterrupt()" and
     * \ref RWRunnableSelf::serviceInterrupt() "serviceInterrupt()" instead.
     *
     * At runtime, use canSuspendResume() to determine the availability of
     * this feature. At compile time, check to see if
     * \c RW_THR_HAS_SUSPEND_RESUME is defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHRThreadNotActive, and
     * RWTHRInternalError.
     */
    unsigned
    suspend();

    /////////////////////////////////////////////////////////////////////////
    // External thread functions - May only be access through this handle!
    /////////////////////////////////////////////////////////////////////////

    // Feature Tests: RW_THR_HAS_SUSPEND_RESUME,
    //                canSuspendResume()
    /**
     * Resumes this thread after it has been suspended. At runtime, use
     * canSuspendResume() to determine the availability of this feature. At
     * compile time, check to see if \c RW_THR_HAS_SUSPEND_RESUME is
     * defined.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, RWTHRIllegalAccess, RWTHRThreadNotActive,
     * and RWTHRInternalError.
     */
    unsigned
    resume();


    // Feature Tests: RW_THR_HAS_SUSPEND_RESUME,
    //                canSuspendResume()
    /**
     * Returns the number of times this thread has been suspended without
     * being released. A return value of zero indicates that the thread is
     * not currently suspended.
     *
     * Possible exceptions include RWTHRInvalidPointer,
     * RWTHROperationNotSupported, and RWTHRInternalError.
     */
    unsigned
    getSuspendCount() const;

#if !defined(RW_DISABLE_DEPRECATED)
    // CAUTION: This operation kills the thread object's thread without giving
    //          it a chance to release locks, unwind the stack, or recover
    //          resources!
    //                      *** Use only as a last resort! ***
    //          Note that thread object storage cannot be recovered once
    //          terminate is used; each thread object creates a automatic
    //          reference to itself while executing within its started
    //          thread, and since termination does not unwind the stack,
    //          this reference will never be destroyed, leaving the thread
    //          object with a reference count that can never return to zero.
    /**
     * \deprecated
     * As of SourcePro 13. Explicit thread termination should be avoided.
     *
     * Terminates execution of this thread.
     *
     * \warning This operation kills the associated thread without giving it
     * a chance to release locks, unwind the stack, or recover resources.
     * Use only as a last resort.
     *
     * Possible exceptions include RWTHRInvalidPointer, RWTHRIllegalAccess,
     * RWTHRThreadNotActive, RWTHRThreadActive, and RWTHRInternalError.
     */
    RW_DEPRECATE_FUNC("")
    void
    terminate();
#endif

protected:

    /**
     * Associates a new thread with self.
     */
    RWThread(RWThreadImp* threadImpP);

    // Construct an external interface handle to the RWThreadImp
    // instance pointed-to by an internal interface handle
    // (used by the RWThreadSelf::getRWThread() member.
    RWThread(const RWThreadSelf& second);

    // Override the parent class body() function to provide
    // version that casts to this handle's body class
    RWThreadImp&
    body(void) const;

};

/*****************************************************************************/

inline
RWThread::RWThread()
{
}

inline
RWThread::RWThread(RWStaticCtor)
    :
    RWRunnable(RW_STATIC_CTOR)
{
}

inline
RWThread::RWThread(const RWThread& second)
    :
    RWRunnable(second)
{
}

inline
RWThread::~RWThread()
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
inline RWThread&
RWThread::operator=(const RWThread& second)
{
    RWRunnable::operator=(second);
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING

#endif // __rw_thread_RWThread_h__
