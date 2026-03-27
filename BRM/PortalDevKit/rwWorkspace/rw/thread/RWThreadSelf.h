#ifndef __rw_thread_RWThreadSelf_h__
#define __rw_thread_RWThreadSelf_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/RWThreadSelf.h#1 $
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

#include <rw/thread/RWRunnableSelf.h>
#include <rw/thread/RWThread.h>
#include <rw/thread/fwd.h>
#include <rw/thread/pkgdefs.h>

#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)
struct RWTLDBase;
#endif

/**
 * \ingroup threading_package
 *
 * \brief
 * Handle class for a threaded runnable object.
 *
 * The RWThreadSelf class is a handle class for a <em>threaded runnable</em>
 * object, providing an interface for threads that execute inside the
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
 * The RWThreadSelf class provides an interface for the thread executing
 * \e inside of a threaded runnable. It defines the member functions that
 * may only be executed only by the \e internal thread. Threads executing
 * \e outside of a threaded runnable should access the runnable using the
 * RWThread handle class. Functions available from either inside or outside
 * of a threaded runnable are defined in both handle classes.
 *
 * To retrieve an RWThreadSelf handle instance for the current threaded
 * runnable, use the rwThread() function. You may also convert an RWThread
 * handle to an RWThreadSelf handle by calling the
 * RWThread::getRWThreadSelf() member, but any attempt to violate the thread
 * access restrictions imposed by the separate interfaces generally results
 * in an RWTHRIllegalAccess exception.
 *
 * \sa
 * RWThread, RWRunnableSelf, RWRunnableHandle, RWThreadAttribute
 */
class RW_THREAD_GLOBAL RWThreadSelf :
    public RWRunnableSelf
{

    friend class RWThreadImp;
    friend class RWThread;

public:

    /**
     * Creates an empty RWThreadSelf handle. Until this object is bound to a
     * threaded runnable, its isValid() member returns \c false.
     */
    RWThreadSelf();


    /**
     * Constructs a global static handle instance, that may be assigned to
     * before construction. The static constructor does not change the
     * instance state.
     */
    RWThreadSelf(RWStaticCtor);


    /**
     * Copy constructor. Creates an RWThreadSelf object associated with the
     * same thread (if any) associated with \a second.
     */
    RWThreadSelf(const RWThreadSelf& second);


    /**
     * Destructor.
     */
    ~RWThreadSelf();


    /**
     * Assignment operator. Binds the handle to the same threaded runnable,
     * if any, pointed-to by \a second.
     */
    RWThreadSelf&
    operator=(const RWThreadSelf& second);


    /**
     * Returns an external thread interface associated with the same thread,
     * if any, associated with self.
     */
    RWThread
    getRWThread() const;


    /**
     * Returns a handle to the thread attribute object used to initialize
     * any threads created by future calls to RWThread::start(). Use
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
     * created by future calls to RWThread::start(). Changing a thread's
     * attribute object after the thread has been started does not affect
     * its current thread.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    void
    setAttribute(const RWThreadAttribute& second);


    /**
     * Returns a handle to the thread attribute instance used to initialize
     * the most recently created thread. If a thread has not yet been
     * created, this function simply returns a copy of a default thread
     * attribute instance.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    RWThreadAttribute
    getActiveAttribute() const;


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
     * Each \c "canGetXxx" function returns \c true if the corresponding
     * attribute is supported in the current environment and if the
     * corresponding \c "getXxx" function can return a legal value under the
     * current circumstances.
     *
     * For example, canGetPriority() returns \c true only if
     * \c RW_THR_HAS_PRIORITY is defined and calling related functions such
     * as getPriority() and getMaxPriority() can return a legal value under
     * the current circumstances.
     *
     * Possible exceptions include RWTHRInvalidPointer and
     * RWTHRInternalError.
     */
    bool
    canGetPriority() const;

    /**
     * \copydoc RWThreadSelf::canGetPriority() const
     */
    bool
    canGetProcessScopePriority() const;

    /**
     * \copydoc RWThreadSelf::canGetPriority() const
     */
    bool
    canGetSchedulingPolicy() const;

    /**
     * \copydoc RWThreadSelf::canGetPriority() const
     */
    bool
    canGetSystemScopePriority() const;

    /**
     * \copydoc RWThreadSelf::canGetPriority() const
     */
    bool
    canGetTimeSliceQuantum() const;


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
     * Each \c "canSetXxx()" function returns \c true if the corresponding
     * attribute is supported in the current environment and if the
     * corresponding \c "setXxx()" function is callable under the current
     * circumstances.
     *
     * For example, canSetPriority() returns \c true only if
     * \c RW_THR_HAS_PRIORITY is defined and calling setPriority() is
     * supported under the current options. In addition, the function
     * returns \c true only if both the calling thread and process have
     * sufficient privileges to perform the requested operation.
     */
    bool
    canSetPriority() const;

    /**
     * \copydoc RWThreadSelf::canSetPriority() const
     */
    bool
    canSetProcessScopePriority() const;

    /**
     * \copydoc RWThreadSelf::canSetPriority() const
     */
    bool
    canSetSchedulingPolicy(RWSchedulingPolicy policy) const;

    /**
     * \copydoc RWThreadSelf::canSetPriority() const
     */
    bool
    canSetSystemScopePriority() const;

    /**
     * \copydoc RWThreadSelf::canSetPriority() const
     */
    bool
    canSetTimeSliceQuantum() const;


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
     * RWThread::resume() members functions, otherwise \c false.
     */
    static
    bool
    canSuspendResume();

    // Feature Tests: RW_THR_HAS_SUSPEND_RESUME,
    //                canSuspendResume()
    /**
     * Suspends the execution of the thread associated with self until a
     * matching RWThread::resume() operation is performed.
     *
     * \warning Use of this function may produce unexpected deadlock (see
     * the <em>Threads User's Guide</em> for more information). For
     * deadlock-safe suspension, use RWThread::requestInterrupt() and
     * serviceInterrupt() instead.
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

#if !defined(RW_THR_CAN_RECOVER_THREAD_LOCALS)
    void
    appendTLD(RWTLDBase*);

    void
    removeTLD(RWTLDBase*);
#endif

protected:

    // Construct an internal interface handle to the RWThreadImp
    // instance pointed-to by an external interface handle
    // (used by the RWThread::getThreadSelf() member.
    /**
     * Conversion constructor.
     */
    RWThreadSelf(const RWThread& second);

    // Override the parent class body() function to provide
    // version that casts to this handle's body class
    RWThreadImp&
    body(void) const;

};

/*****************************************************************************/

inline
RWThreadSelf::RWThreadSelf()
{
}

inline
RWThreadSelf::RWThreadSelf(RWStaticCtor)
    :
    RWRunnableSelf(RW_STATIC_CTOR)
{
}

inline
RWThreadSelf::RWThreadSelf(const RWThreadSelf& second)
    :
    RWRunnableSelf(second)
{
}

inline
RWThreadSelf::~RWThreadSelf()
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
inline RWThreadSelf&
RWThreadSelf::operator=(const RWThreadSelf& second)
{
    RWRunnableSelf::operator=(second);
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING

#endif // __rw_thread_RWThreadSelf_h__
