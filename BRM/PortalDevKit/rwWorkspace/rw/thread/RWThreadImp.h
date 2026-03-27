#ifndef __rw_thread_RWThreadImp_h__
#define __rw_thread_RWThreadImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadImp.h#1 $
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

  RWThreadImp - Internal thread runnable implementation.

******************************************************************************/

#include <rw/thread/RWRunnableImp.h>
#include <rw/thread/RWTThreadLocal.h>
#include <rw/thread/RWThreadAttribute.h>
#include <rw/thread/RWThreadManager.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>
#include <rw/sync/RWCondition.h>
#include <rw/sync/RWThreadId.h>
#include <rw/tpslist.h>

#if defined(RW_THR_THREAD_API_SOLARIS) || \
    defined(RW_THR_THREAD_API_POSIX_SUNOS)
#  include <sys/lwp.h>
#endif

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

class RW_THREAD_GLOBAL RWThreadImp :
    public RWRunnableImp
{

    friend class RWThread;
    friend class RWThreadSelf;

protected:

    // thread manager for insuring shutdown.
    RWThreadManager threadManager_;

    RWThreadAttribute initialAttributes_; // May be shared with other threads
    RWThreadAttribute currentAttributes_; // Copied from initial - Not shared

#if defined(RW_THR_THREAD_API_WIN32)
    // Use void* instead of DWORD to avoid including windows headers
    void* hThread_;
#endif

#if defined(RW_THR_HAS_SUSPEND_RESUME)
    unsigned suspendCount_;

    //This pointer will only be valid while the thread is in the
    //process of suspending itself, or has suspended itself but has
    //not completed being resumed
    RWTOnlyPointer<RWCondition> suspendSelfWaiter_;
#endif

#if defined(RW_THR_THREAD_API_SOLARIS) || \
    defined(RW_THR_THREAD_API_POSIX_SUNOS)
    lwpid_t threadLWPId_;
#endif

#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)

public:

    // Win32 does not provide a mechanism for automatically
    // destroying instances of thread-local objects when a thread exits,
    // so the SourcePro Core - Threads Module keeps track of each
    // thread-local instance within the RWThreadImp instance associated
    // with the thread that created the thread-local instance, so that
    // these thread-local instances may be destroyed at thread exit.
    // Thread-local instances that are created by threads started
    // outside of the Threads Module library are not deleted until the
    // thread-local object itself is deleted.

    // TLD_Base is a helper class of RWTThreadLocal,
    // and is used to register each thread-local instance for automatic
    // destruction when the thread associated with a RWThreadImp instance
    // completes its execution and exits.

    RWTPtrSlist< RWTLDBase >*  cleanup_;

    // Allows TThreadLocal objects to register instances that need to
    // be destroyed when this thread exits.
    void
    appendTLD(RWTLDBase* base);

    // Allows TThreadLocal to remove thread local data on behalf of the
    // user. Caller is responsible for deleting base.
    void
    removeTLD(RWTLDBase* base);

    void
    setTLD(RWTPtrSlist<RWTLDBase>* dest);

#endif

public:

    // Destroys RWThreadImp instance.
    virtual
    ~RWThreadImp(void);

protected:

    // Default constructor used by derived classes when default thread
    // attributes are to be used, or when an attribute instance will be
    // specified after construction.
    RWThreadImp(void);

    // Constructor used by derived classes when an attribute instance is
    // specified at construction time.
    RWThreadImp(const RWThreadAttribute& attr);

    // Construct a new instance but don't copy any members
    RWThreadImp(const RWThreadImp& second);

    // Assignment operator that doesn't assign any members
    RWThreadImp&
    operator=(const RWThreadImp& second);

    /////////////////////////////////////////////////////////////////////////
    // Common thread functions - May only accessed through either handle!
    /////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////
    // This function gets a handle to the thread attribute instance that will
    // be used to initialize any threads created by future calls to the this
    // runnable's start() member.  If the thread attribute has not yet been
    // set on the current threaded runnable instance, this function simply
    // returns a handle to the default thread attribute instance created when
    // the threaded runnable was constructed.  This internal instance may be
    // manipulated through the returned handle.
    //
    // The attribute instance returned may not have the same attribute values
    // as the thread attribute instance used to create any existing thread,
    // since a private copy of the current thread attribute object is made
    // each time a thread is started.  Use the getActiveAttribute() function
    // to get a copy of the attribute instance actual used to initialize the
    // most recently created thread.
    //
    // This function will throw an RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWThreadAttribute
    getAttribute(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This function replaces the thread attribute instance that will
    // be used to initialize any threads created by future calls to this
    // runnable's start() member.  Changing a thread runnable's attribute
    // object after the runnable has already been started will not affect its
    // current thread; it can only affect the thread created the next time
    // the runnable is started.
    //
    // This function will throw an RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    void
    setAttribute(const RWThreadAttribute& second);

    /////////////////////////////////////////////////////////////////////////
    // The following function may be used to get a handle to a copy of the
    // thread attribute instance used to initialize the most recently created
    // thread.  If a thread has not yet been created, this function will
    // simply return a copy of a default thread attribute instance.
    //
    // This function will throw an RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////
    RWThreadAttribute
    getActiveAttribute(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The following functions may be used to determine the legal range
    // of values for various active thread attributes.
    //
    // These functions return a maximum or minimum value for a particular
    // active thread attribute.
    //
    // These functions will throw an RWTHROperationNotSupported exception
    // if the corresponding attribute is not supported. This exception can be
    // avoided by testing to see if the corresponding feature test macro is
    // currently defined (see each function below for the macro).
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope and scheduling policy do not
    // use or support the priority attribute.
    //
    // These functions will throw a RWTHRThreadNotActive exception if the
    // threaded runnable does not have an active thread (either because
    // the thread was not started, or the thread has exited for some reason).
    //
    // All of the exceptions listed above can be avoided by using an
    // appropriate "can get" function to test for availability prior to
    // calling the "get min/max" function.  You must understand that even if
    // you get a return value of true from these test functions, the
    // "get min/max" function may still produce several of these exceptions
    // if other threads are simultaneously manipulating the thread
    // attributes, or if the target thread exits before the "get min/max"
    // function can be called.
    //
    // These functions will throw an RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    // Get the maximum priority value that may be specified for this thread.
    // Feature Tests: RW_THR_HAS_PRIORITY,
    //                canGetPriority()
    RWPriority
    getMaxPriority(void) const;

    // Get the maximum process-scope priority value that may be
    // specified for this thread.
    // Feature Tests: RW_THR_HAS_PROCESS_SCOPE_PRIORITY,
    //                canGetProcessScopePriority()
    RWPriority
    getMaxProcessScopePriority(void) const;

    // Get the maximum system-scope priority value that may be
    // specified for this thread.
    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canGetSystemScopePriority()
    RWPriority
    getMaxSystemScopePriority(void) const;

    // Get the maximum time-slice quantum value that may be
    // specified for this thread.
    // Feature Tests: RW_THR_HAS_TIME_SLICE_QUANTUM,
    //                canGetTimeSliceQuantum()
    unsigned long
    getMaxTimeSliceQuantum(void) const;

    // Get the minimum priority value that may be specified for this thread.
    // Feature Tests: RW_THR_HAS_PRIORITY,
    //                canGetPriority()
    RWPriority
    getMinPriority(void) const;

    // Get the maximum process-scope priority value that may be
    // specified for this thread.
    // Feature Tests: RW_THR_HAS_PROCESS_SCOPE_PRIORITY,
    //                canGetProcessScopePriority()
    RWPriority
    getMinProcessScopePriority(void) const;

    // Get the maximum system-scope priority value that may be
    // specified for this thread.
    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canGetSystemScopePriority()
    RWPriority
    getMinSystemScopePriority(void) const;

    // Get the minimum time-slice quantum value that may be
    // specified for this thread.
    // Feature Tests: RW_THR_HAS_TIME_SLICE_QUANTUM,
    //                canGetTimeSliceQuantum()
    unsigned long
    getMinTimeSliceQuantum(void) const;

    /////////////////////////////////////////////////////////////////////////
    // This static function returns true if the getMaxThreads() function is
    // supported in the current environment, and returns false if not.
    /////////////////////////////////////////////////////////////////////////
    static
    bool
    canGetMaxThreads(void);

    /////////////////////////////////////////////////////////////////////////
    // This static function returns the maximum number of threads that may be
    // created in this environment.  This function is not supported in all
    // environments.  Use the feature test macro RW_THR_HAS_MAX_THREADS or the
    // feature test function canGetMaxThreads() to test for availability.
    //
    // This function throws an RWTHROperationNotSupported exception if not
    // supported in the current environment.
    /////////////////////////////////////////////////////////////////////////
    static
    size_t
    getMaxThreads(void);

    /////////////////////////////////////////////////////////////////////////
    // The "can get" test functions below can be used to determine at
    // run-time whether the corresponding attribute value may be read.
    //
    // Each of these functions returns false if the corresponding attribute
    // is NOT supported in the current environment or if the corresponding
    // "get" function CANNOT return a legal value under current circumstances.
    //
    // Each of these functions returns true if the corresponding attribute IS
    // supported in the current environment and the corresponding "get"
    // function CAN return a legal value under current circumstances.
    //
    // These functions will throw an RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    canGetPriority(void) const;

    bool
    canGetProcessScopePriority(void) const;

    bool
    canGetSchedulingPolicy(void) const;

    bool
    canGetSystemScopePriority(void) const;

    bool
    canGetTimeSliceQuantum(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The "get" functions below can be used to query the corresponding
    // attribute.
    //
    // These functions will throw an RWTHROperationNotSupported exception if
    // the attribute is not supported in the current environment.
    //
    // These functions will throw an RWTHROperationNotAvailable exception if
    // the corresponding attribute is supported, but the value is not
    // supported or cannot be queried under under the current circumstances.
    //
    // These functions will throw an RWTHRThreadNotActive exception if the
    // threaded runnable does not have an active thread (either because
    // the thread was not started, or the thread has exited for some reason).
    //
    // Some of these functions will throw an RWTHRResourceLimit exception if
    // the operation could not be performed due to memory or system resource
    // constraints.  The exception message will give the specific reason.
    //
    // All of the exceptions above can be avoided by using the appropriate
    // "can get" function to test for availability prior to calling the "get"
    // function.  You must understand that even if you get a return value of
    // true from these test functions, a "get" function may still produce
    // several of these exceptions of if other threads are simultaneously
    // manipulating the same attributes, or if the target thread exits before
    // the "get" function can be called.
    //
    // These functions will throw an RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    // Get the current priority for the active thread.
    // Feature Tests: RW_THR_HAS_PRIORITY,
    //                canGetPriority()
    RWPriority
    getPriority(void) const;

    // Get the current process-scope priority for the active thread.
    // Feature Tests: RW_THR_HAS_PROCESS_SCOPE_PRIORITY,
    //                canGetProcessScopePriority()
    RWPriority
    getProcessScopePriority(void) const;

    // Get the current scheduling policy for the active thread.
    // Feature Tests: RW_THR_HAS_SCHEDULING_POLICY,
    //                canGetSchedulingPolicy()
    RWSchedulingPolicy
    getSchedulingPolicy(void) const;

    // Get the current system-scope priority for the active thread.
    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canGetSystemScopePriority()
    RWPriority
    getSystemScopePriority(void) const;

    // Get the current system-scope priority for the active thread.
    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canGetSystemScopePriority()
    unsigned long
    getTimeSliceQuantum(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The public "can set" test functions below can be used to determine, at
    // run-time, whether the corresponding attribute value may be set.
    //
    // Each of these functions returns false if the corresponding attribute
    // is NOT supported in the current environment or if the specified
    // policy, if any, is not supported under the current circumstances.
    // either because the specified value is not supported under the current
    // scheduling options or because the calling thread or process does not
    // possess sufficient privileges to perform the requested operation.
    //
    // Each of these functions returns true if the corresponding attribute IS
    // supported in the current environment and the specified policy is legal
    // under the current circumstances.
    //
    // Some of these functions will produce a RWTHRBoundsError exception if
    // the specified value is not a legal policy value for that attribute.
    // This exception can be avoided by making sure that you are using the
    // appropriate value names for enumerated attributes.
    //
    // Some of these functions will throw an RWTHRInternalError exception
    // if some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    canSetPriority(void) const;

    bool
    canSetProcessScopePriority(void) const;

    bool
    canSetSchedulingPolicy(RWSchedulingPolicy policy) const;

    bool
    canSetSystemScopePriority(void) const;

    bool
    canSetTimeSliceQuantum(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The "set" functions below can be used to change the corresponding
    // attribute.
    //
    // These functions will throw an RWTHROperationNotSupported exception if
    // the attribute is not supported in the current environment.
    //
    // These functions will throw an RWTHROperationNotAvailable exception if
    // the corresponding attribute is supported, but the specified value is
    // not supported under the current circumstances, either because the
    // specified value is not supported under the current scheduling options
    // or because the calling thread or process does not possess sufficient
    // privileges to perform the requested operation.
    //
    // These functions will throw an RWTHRBoundsError exception if the
    // specified value is invalid or falls outside the current legal range
    // for that attribute.
    //
    // These functions will throw an RWTHRThreadNotActive exception if the
    // threaded runnable does not have an active thread (either because
    // the thread was not started, or the thread has exited for some reason).
    //
    // Some of these functions will throw an RWTHRResourceLimit exception if
    // the operation could not be performed due to memory or system resource
    // constraints.  The exception message will give the specific reason.
    //
    // All of the exceptions above can be avoided by using the appropriate
    // "can set" function to test for availability prior to calling the "set"
    // function.  You must understand that even if you get a return value of
    // true from these test functions, a "set" function may still produce
    // several of these exceptions of if other threads are simultaneously
    // manipulating the same attributes, or if the target thread exits before
    // the "set" function can be called.
    //
    // These functions will throw an RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    // Change the priority of this runnable's thread.
    // Feature Tests: RW_THR_HAS_PRIORITY,
    //                canSetPriority()
    void
    setPriority(RWPriority priority);

    // Change the process scope priority of this runnable's thread.
    // Feature Tests: RW_THR_HAS_PROCESS_SCOPE_PRIORITY,
    //                canSetProcessScopePriority()
    void
    setProcessScopePriority(RWPriority priority);

    // Change the scheduling policy currently applied to this runnable's
    // thread.
    // Feature Tests: RW_THR_HAS_SCHEDULING_POLICY,
    //                canSetSchedulingPolicy()
    void
    setSchedulingPolicy(RWSchedulingPolicy policy);

    // Change the system scope priority of this runnable's thread.
    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canSetSystemScopePriority()
    void
    setSystemScopePriority(RWPriority priority);

    // Change the system scope priority of this runnable's thread.
    // Feature Tests: RW_THR_HAS_TIME_SLICE_QUANTUM,
    //                canSetTimeSliceQuantum()
    void
    setTimeSliceQuantum(unsigned long milliseconds);

    /////////////////////////////////////////////////////////////////////////
    // This function returns true if the current environment supports the
    // suspend() and resume() functions, false if otherwise
    /////////////////////////////////////////////////////////////////////////
    static
    bool
    canSuspendResume(void);

    /////////////////////////////////////////////////////////////////////////
    // Suspend the execution of this runnable's thread until a matching resume
    // operation is performed.  May only be invoked from a different thread.
    // Feature Tests: RW_THR_HAS_SUSPEND_RESUME,
    //                canSuspendResume()
    // CAUTION: Use of this function may produce unexpected deadlock! See the
    //          User's Guide for explanation.  Use requestInterrupt() and
    //          serviceInterrupt() for dead-lock safe suspension!
    /////////////////////////////////////////////////////////////////////////
    unsigned
    suspendOther(void);

    /////////////////////////////////////////////////////////////////////////
    // Suspend the execution of this runnable's thread until a matching resume
    // operation is performed.  May only be invoked from this runnable's thread
    // using an RWThreadSelf handle.
    // Feature Tests: RW_THR_HAS_SUSPEND_RESUME,
    //                canSuspendResume()
    // CAUTION: Use of this function may produce unexpected deadlock! See the
    //          User's Guide for explanation.  Use requestInterrupt() and
    //          serviceInterrupt() for dead-lock safe suspension!
    /////////////////////////////////////////////////////////////////////////
    unsigned
    suspendSelf(void);

    /////////////////////////////////////////////////////////////////////////
    // External thread functions - May only be access through this handle!
    /////////////////////////////////////////////////////////////////////////

    // Resume this thread after it has been suspended.
    // Feature Tests: RW_THR_HAS_SUSPEND_RESUME,
    //                canSuspendResume()
    unsigned
    resume(void);

    // Get the number of times this thread has been suspended without being
    // released.  A return value of zero indicates that the thread is not
    // currently suspended or is inactive.
    // Feature Tests: RW_THR_HAS_SUSPEND_RESUME, canSuspendResume()
    unsigned
    getSuspendCount(void) const;


#if !defined(RW_DISABLE_DEPRECATED)
    // Terminate the execution of this runnable's thread.
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
    RW_DEPRECATE_FUNC("")
    void
    terminate(void);
#endif

protected:

    // Calls _createThread() to create a thread and then sets
    // the initial priority and scheduling policy for the newly
    // created thread.
    virtual
    void
    _dispatchExec(void);
    // Actual exceptions thrown are as follows:
    //    RWTHRThreadActive - An illegal attempt was made to start the thread while it was already active.
    //    RWTHRResourceLimit - There was insufficient memory or system resources to create thread.
    //    RWTHRInternalError - An unexpected exception or error condition occurred.

    // Perform setup prior execution of the virtual run() member.
    // Thread mutex must be locked prior to calling this member
    // This function expects the RWThreadImp monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    virtual
    void
    _runProlog(void);

    // Perform cleanup following execution of the virtual run() member.
    // Runnable mutex must be locked prior to calling this member
    // This function expects the RWThreadImp monitor mutex to be LOCKED
    // upon entry, and will unlock and re-lock the mutex internally and
    // is therefore, NOT ATOMIC.
    virtual
    void
    _runEpilog(void);

    // this is public to allow access by the RWThreadImp_entry global
    // in RWThreadImp.cpp
public:

    // Overrides the RWRunnableImp::exec() member to wrap RWThreadImp-
    // specific initialization and clean-up operations around a call
    // to the RWRunnableImp::exec() member.
    void
    exec(void);

private:

    // Initialize and create a thread that when started executes
    // the RWThreadImp_entry() which calls RWThreadImp::exec().
    void
    _createThread(void);

    // Common initialization for thread object construction
    void
    init(void);

    // RWThreadImp_entry() is actual thread entry point
    // POSIX/SOLARIS Threads require extern "C" linkage for the entry point function!
    // The function is not declared in this header because it is private to the implementation.
    // See RWThreadImp_entry() definition in RWThreadImp.cpp...

    /////////////////////////////////////////////////////////////////////////
    // The following private functions are used internally to determine the
    // legal range of values for various active thread attributes.
    //
    // These functions return a maximum or minimum value for a particular
    // active thread attribute.
    //
    // These functions will throw an RWTHROperationNotSupported exception
    // if the corresponding attribute is not supported. This exception can be
    // avoided by testing to see if the corresponding feature test macro is
    // currently defined (see each function below for the macro).
    //
    // This function will throw an RWTHROperationNotAvailable exception if
    // the current contention scope and scheduling policy do not
    // use or support the priority attribute.
    //
    // These functions will throw a RWTHRThreadNotActive exception if the
    // threaded runnable does not have an active thread (either because
    // the thread was not started, or the thread has exited for some reason).
    //
    // All of the exceptions listed above can be avoided by using an
    // appropriate "can get" function to test for availability prior to
    // calling the "get min/max" function.  You must understand that even if
    // you get a return value of true from these test functions, the
    // "get min/max" function may still produce several of these exceptions
    // if other threads are simultaneously manipulating the thread
    // attributes, or if the target thread exits before the "get min/max"
    // function can be called.
    //
    // These functions will throw an RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    // Get the maximum priority value that may be specified for this thread.
    RWPriority
    _getMaxPriority(void) const;

    // Get the maximum process-scope priority value that may be
    // specified for this thread.
    RWPriority
    _getMaxProcessScopePriority(void) const;

    // Get the maximum system-scope priority value that may be
    // specified for this thread.
    RWPriority
    _getMaxSystemScopePriority(void) const;

    // Get the maximum time-slice quantum value that may be
    // specified for this thread.
    unsigned long
    _getMaxTimeSliceQuantum(void) const;

    // Get the minimum priority value that may be specified for this thread.
    RWPriority
    _getMinPriority(void) const;

    // Get the maximum process-scope priority value that may be
    // specified for this thread.
    RWPriority
    _getMinProcessScopePriority(void) const;

    // Get the maximum system-scope priority value that may be
    // specified for this thread.
    RWPriority
    _getMinSystemScopePriority(void) const;

    // Get the minimum time-slice quantum value that may be
    // specified for this thread.
    unsigned long
    _getMinTimeSliceQuantum(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The "can get" test functions below can be used to determine at
    // run-time whether the corresponding attribute value may be read.
    //
    // Each of these functions returns false if the corresponding attribute
    // is NOT supported in the current environment or if the corresponding
    // "get" function CANNOT return a legal value under current circumstances.
    //
    // Each of these functions returns true if the corresponding attribute IS
    // supported in the current environment and the corresponding "get"
    // function CAN return a legal value under current circumstances.
    //
    // These functions will throw the RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    _canGetPriority(void) const;

    bool
    _canGetProcessScopePriority(void) const;

    bool
    _canGetSchedulingPolicy(void) const;

    bool
    _canGetSystemScopePriority(void) const;

    bool
    _canGetTimeSliceQuantum(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The "get" functions below can be used to query the corresponding
    // attribute.
    //
    // These functions will throw an RWTHROperationNotSupported exception if
    // the attribute is not supported in the current environment.
    //
    // These functions will throw an RWTHROperationNotAvailable exception if
    // the corresponding attribute is supported, but the value is not
    // supported or cannot be queried under under the current circumstances.
    //
    // These functions will throw an RWTHRThreadNotActive exception if the
    // threaded runnable does not have an active thread (either because
    // the thread was not started, or the thread has exited for some reason).
    //
    // Some of these functions will throw an RWTHRResourceLimit exception if
    // the operation could not be performed due to memory or system resource
    // constraints.  The exception message will give the specific reason.
    //
    // All of the exceptions above can be avoided by using the appropriate
    // "can get" function to test for availability prior to calling the "get"
    // function.  You must understand that even if you get a return value of
    // true from these test functions, a "get" function may still produce
    // several of these exceptions of if other threads are simultaneously
    // manipulating the same attributes, or if the target thread exits before
    // the "get" function can be called.
    //
    // These functions will throw an RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    // Get the current priority for the active thread.
    RWPriority
    _getPriority(void) const;

    // Get the current process-scope priority for the active thread.
    RWPriority
    _getProcessScopePriority(void) const;

    // Get the current scheduling policy for the active thread.
    RWSchedulingPolicy
    _getSchedulingPolicy(void) const;

    // Get the current system-scope priority for the active thread.
    RWPriority
    _getSystemScopePriority(void) const;

    // Get the current system-scope priority for the active thread.
    unsigned long
    _getTimeSliceQuantum(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The public "can set" test functions below can be used to determine, at
    // run-time, whether the corresponding attribute value may be set.
    //
    // Each of these functions returns false if the corresponding attribute
    // is NOT supported in the current environment or if the specified
    // policy, if any, is not supported under the current circumstances.
    // either because the specified value is not supported under the current
    // scheduling options or because the calling thread or process does not
    // possess sufficient privileges to perform the requested operation.
    //
    // Each of these functions returns true if the corresponding attribute IS
    // supported in the current environment and the specified policy is legal
    // under the current circumstances.
    //
    // Some of these functions will produce a RWTHRBoundsError exception if
    // the specified value is not a legal policy value for that attribute.
    // This exception can be avoided by making sure that you are using the
    // appropriate value names for enumerated attributes.
    //
    // Some of these functions will throw the RWTHRInternalError exception
    // if some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    _canSetPriority(void) const;

    bool
    _canSetProcessScopePriority(void) const;

    bool
    _canSetSchedulingPolicy(RWSchedulingPolicy policy) const;

    bool
    _canSetSystemScopePriority(void) const;

    bool
    _canSetTimeSliceQuantum(void) const;

    /////////////////////////////////////////////////////////////////////////
    // The private "validate" functions below are used internally to validate
    // a candidate value for the corresponding attribute
    //
    // These functions return true if the attribute is supported, and the
    // value is a legal value for the attribute.
    //
    // These functions return false if the attribute is supported, but the
    // value is not a legal value for the attribute.
    //
    // These functions will throw an RWTHROperationNotAvailable exception
    // if the corresponding attribute is supported, but the specified value
    // is not supported under the current circumstances.
    //
    // These functions will throw an RWTHROperationNotSupported exception
    // if the attribute is not supported in the current environment.
    //
    // Some of these functions will throw an RWTHRInternalError exception
    // if some unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    bool
    _validatePriority(RWPriority priority) const;

    bool
    _validateProcessScopePriority(RWPriority priority) const;

    bool
    _validateSchedulingPolicy(RWSchedulingPolicy policy) const;

    bool
    _validateSystemScopePriority(RWPriority priority) const;

    bool
    _validateTimeSliceQuantum(unsigned long milliseconds) const;

    /////////////////////////////////////////////////////////////////////////
    // The private "set" functions below are used internally to change the
    // corresponding thread attribute.
    //
    // These functions will throw an RWTHROperationNotSupported exception if
    // the attribute is not supported in the current environment.
    //
    // These functions will throw an RWTHROperationNotAvailable exception if
    // the corresponding attribute is supported, but the specified value is
    // not supported under the current circumstances, either because the
    // specified value is not supported under the current scheduling options
    // or because the calling thread or process does not possess sufficient
    // privileges to perform the requested operation.
    //
    // These functions will throw an RWTHRBoundsError exception if the
    // specified value is invalid or falls outside the current legal range
    // for that attribute.
    //
    // These functions will throw an RWTHRThreadNotActive exception if the
    // threaded runnable does not have an active thread (either because
    // the thread was not started, or the thread has exited for some reason).
    //
    // Some of these functions will throw an RWTHRResourceLimit exception if
    // the operation could not be performed due to memory or system resource
    // constraints.  The exception message will give the specific reason.
    //
    // All of the exceptions above can be avoided by using the appropriate
    // "can set" function to test for availability prior to calling the "set"
    // function.  You must understand that even if you get a return value of
    // true from these test functions, a "set" function may still produce
    // several of these exceptions of if other threads are simultaneously
    // manipulating the same attributes, or if the target thread exits before
    // the "set" function can be called.
    //
    // These functions will throw an RWTHRInternalError exception if some
    // unexpected error or exception occurs within the library code.
    /////////////////////////////////////////////////////////////////////////

    // Change the priority of this runnable's thread.
    // Feature Tests: RW_THR_HAS_PRIORITY,
    //                canSetPriority()
    void
    _setPriority(RWPriority priority);

    // Change the process scope priority of this runnable's thread.
    // Feature Tests: RW_THR_HAS_PROCESS_SCOPE_PRIORITY,
    //                canSetProcessScopePriority()
    void
    _setProcessScopePriority(RWPriority priority);

    // Change the scheduling policy currently applied to this runnable's
    // thread.
    // Feature Tests: RW_THR_HAS_SCHEDULING_POLICY,
    //                canSetSchedulingPolicy()
    void
    _setSchedulingPolicy(RWSchedulingPolicy policy);

    // Change the system scope priority of this runnable's thread.
    // Feature Tests: RW_THR_HAS_SYSTEM_SCOPE_PRIORITY,
    //                canSetSystemScopePriority()
    void
    _setSystemScopePriority(RWPriority priority);

    // Change the system scope priority of this runnable's thread.
    // Feature Tests: RW_THR_HAS_TIME_SLICE_QUANTUM,
    //                canSetTimeSliceQuantum()
    void
    _setTimeSliceQuantum(unsigned long milliseconds);

};

/***********************************************************************/

inline
RWThreadImp::RWThreadImp(const RWThreadImp& second)
    : RWRunnableImp(second)
#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)
    , cleanup_(0)
#endif
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
inline RWThreadImp&
RWThreadImp::operator=(const RWThreadImp& second)
{
    RWRunnableImp::operator=(second);
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING

#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)
inline void
RWThreadImp::appendTLD(RWTLDBase* base)
{
    LockGuard guard(monitor());
    cleanup_->append(base);
}

inline void
RWThreadImp::removeTLD(RWTLDBase* base)
{
    LockGuard guard(monitor());
    cleanup_->remove(base);
}

inline void
RWThreadImp::setTLD(RWTPtrSlist<RWTLDBase>* dest)
{
    LockGuard guard(monitor());
    cleanup_ = dest;
}
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_thread_RWThreadImp_h__
