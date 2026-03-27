#ifndef __rw_sync_RWCondition_h__
#define __rw_sync_RWCondition_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWCondition.h#1 $
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

#include <rw/sync/RWMutexLock.h>
#include <rw/sync/RWSynchObject.h>
#include <rw/sync/fwd.h>
#include <rw/sync/pkgdefs.h>


#if (defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32))

#  include <rw/idlist.h>

#endif

#if (defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_POSIX)) || defined(DOXYGEN)
/**
 * \relates RWCondition
 *
 * Typedef for the internal condition variable.
 *
 * \conditional
 * This type is used for build configurations based on POSIX threads.
 */
typedef pthread_cond_t RWConditionRep;
#endif

#if (defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_SOLARIS)) || defined(DOXYGEN)
#  include <synch.h>

/**
 * \relates RWCondition
 *
 * Typedef for the internal condition variable.
 *
 * \conditional
 * This type is used for build configurations based on Solaris threads.
 */
typedef cond_t RWConditionRep;
#endif

#if defined(RW_MULTI_THREAD) && !defined(RW_THR_THREAD_API_SOLARIS) \
      && !defined(RW_THR_THREAD_API_POSIX) && !defined(RW_THR_THREAD_API_WIN32)
#  error Class RWCondition is not supported in this environment!
#endif

/*****************************************************************************/

/**
 * \ingroup synchronization_package
 *
 * \brief
 * A condition variable used to delay and reawaken a thread based on program
 * state.
 *
 * An RWCondition object is a condition variable that can be used to delay a
 * thread until the program state satisfies some boolean condition, and to
 * awaken that thread once the condition becomes true.
 *
 * The name <em>condition variable</em> is perhaps a misnomer. The name
 * seems to imply that a condition variable encapsulates a condition. This
 * is not the case. A condition variable is \e associated with some
 * arbitrary condition in a program. It simply provides a mechanism for
 * threads to wait and signal. It is up to the application to wait at the
 * appropriate point of execution when the condition is false, and to signal
 * appropriately when the condition becomes true.
 *
 * A condition variable must be initialized with a mutex. The mutex must be
 * the same instance that is used to protect the program state involved in
 * the condition test. To delay on a condition variable, a thread calls the
 * wait() function which atomically releases the lock and logically adds the
 * thread to a list of threads that are waiting on the same condition.
 * Another thread can unblock one waiting thread, if there are any, by
 * calling the signal() member function. All waiting threads can be awakened
 * at once by calling the signalAll() member function. For each awakened
 * thread, the wait() function reacquires the lock and returns control to
 * the calling routine.
 *
 * To use an RWCondition object, a thread evaluates a boolean expression
 * under the protection of a mutex lock. When the expression is \c false,
 * the thread blocks on the condition variable, and the mutex is released.
 * Later, when another thread changes the state of the conditional
 * expression under protection of the mutex lock, it then signals that the
 * condition state has changed. This causes one or all of the threads,
 * depending on whether signal() or signalAll() is used, to block on the
 * condition to awaken and to try to reacquire the lock.
 *
 * A thread should always retest the condition when it is awakened, as the
 * condition might have changed before the thread can reacquire the
 * condition mutex. This is typically done in a loop:
 *
 * \code
 * while (!my_boolean_expression)
 *     cv.wait();
 * \endcode
 *
 * When using RWCondition in a class inheriting from RWTMonitor, it is not
 * uncommon to initialize the RWCondition with the monitor's mutex.
 *
 * \example
 * \code
 * #include <rw/sync/RWCondition.h>
 * #include <rw/sync/RWTMonitor.h>
 * #include <rw/sync/RWMutexLock.h>
 * #include <rw/tvslist.h>
 *
 * // Producer Consumer queue example
 * template <class T>
 * class PCBuffer
 *     : RWTMonitor<RWMutexLock>
 * {
 * private:
 *     RWCondition roomInBuffer_;
 *     RWCondition elementAvailable_;
 *     RWTValSlist<T> buffer_;
 *     size_t maxEntries_;
 * public:
 *     PCBuffer(size_t maxEntries)
 *         : maxEntries_(maxEntries),
 *           roomInBuffer_(mutex()),    // init with monitor mutex
 *           elementAvailable_(mutex()) // init with monitor mutex
 *     {}
 *
 *     void put(T t) {
 *         LockGuard lock(monitor()); // acquire monitor mutex
 *         while (!(buffer_.entries() < maxEntries_)) {
 *             roomInBuffer_.wait();   // mutex released automatically
 *             // thread must have been signaled AND
 *             // mutex reacquired to reach here
 *         }
 *         buffer_.append(t);
 *         elementAvailable_.signal();
 *         // mutex automatically released in LockGuard destructor
 *     }
 *
 *     T get(void) {
 *         LockGuard lock(monitor());   // acquire monitor mutex
 *         while (!(buffer_.entries() > 0)) {
 *             elementAvailable_.wait(); // mutex released
 *             //automatically
 *             // thread must have been signalled AND
 *             // mutex reacquired to reach here
 *         }
 *         T val = buffer_.removeFirst();
 *         roomInBuffer_.signal();
 *         return val;
 *         // mutex automatically released in LockGuard destructor
 *     }
 * };
 * \endcode
 * \endexample
 */
class RW_SYNC_SYMBOLIC RWCondition :
    public RWSynchObject
{

protected:

#if !defined(RW_MULTI_THREAD)
    // No internal implementation necessary

#elif defined(RW_THR_THREAD_API_WIN32)

    // Win32 does not provide a condition variable mechanism
    // the SourcePro Core - Threads Module uses a list of per-thread
    // semaphores to implement...
    RWIsvDlist waiters_;

#elif defined(RW_THR_THREAD_API_POSIX) || \
        defined(RW_THR_THREAD_API_SOLARIS)

    RWConditionRep condition_;

#endif

    // Reference to mutex used to protect condition.
    // The mutex is provided by the condition variable's owner, and must
    // already be acquired when wait(), signal(), and signalAll() is called.
    RWMutexLock&   mutex_;

    // Member Functions
public:


    /**
     * Creates a condition variable that is protected by the supplied
     * \a mutex instance. The provided \a mutex must exist as long as the
     * condition variable exists. Possible exceptions include
     * RWTHRResourceLimit and RWTHRInternalError.
     */
    RWCondition(RWMutexLock& mutex,
                RWCancellationState state = RW_CANCELLATION_DISABLED);


    /**
     * Default destructor.
     */
    ~RWCondition();


    /**
     * Blocks until the condition's mutex is released, acquires it, and
     * continues. This function is provided as a convenience; you may also
     * call the mutex acquire() function directly. Possible exceptions
     * include RWCancellation, RWTHRResourceLimit, and RWTHRInternalError.
     *
     * This function does not block in single-threaded builds. The
     * underlying mutex acquire returns immediately to indicate success. If
     * the mutex was unavailable for acquisition, a debug assertion will
     * result or an RWTHRInternalError will be thrown.
     */
    void
    acquire();


    /**
     * Acquires the mutex associated with the condition variable. If the
     * mutex is not available, blocks at least for the specified number of
     * milliseconds, or until the mutex is released, whichever comes first.
     * If the mutex is released within the specified time, the function
     * acquires it and continues. If the mutex is \e not released, the
     * function returns the time-out indication #RW_THR_TIMEOUT. This
     * function is provided as a convenience; you may also call the mutex
     * timed acquire() function directly. Possible exceptions include
     * RWCancellation, RWTHRResourceLimit, and RWTHRInternalError.
     *
     * This function does not block in single-threaded builds. The
     * underlying mutex acquire returns immediately.
     */
    RWWaitStatus
    acquire(unsigned long milliseconds);

#if defined(RW_THR_THREAD_API_POSIX) || \
    defined(RW_THR_THREAD_API_SOLARIS) || defined(DOXYGEN)

    /**
     * Provides access to the underlying mechanism.
     *
     * \conditional
     * This function is available only in build configurations based on
     * POSIX or Solaris threads.
     */
    RWConditionRep*
    getConditionRep() const;

#endif

    /**
     * Releases the mutex associated with the condition variable. This
     * function is provided as a convenience; you may also call the mutex
     * release() function directly. Possible exceptions include
     * RWTHRInternalError.
     */
    void
    release();


    /**
     * Signals one waiting thread that the condition associated with the
     * condition variable has changed. Possible exceptions include
     * RWTHRInternalError.
     *
     * This function is a no-op in single-threaded builds.
     */
    void
    signal();


    /**
     * Signals all waiting threads that the condition associated with the
     * condition variable has changed. Possible exceptions include
     * RWTHRInternalError.
     *
     * This function is a no-op in single-threaded builds.
     */
    void
    signalAll();

    /**
     * Tries to acquire the condition's mutex (without blocking). Returns
     * \c true if acquired, or \c false if the mutex is already owned by
     * another thread. This function is provided as a convenience; you may
     * also call the mutex tryAcquire() function directly. Possible
     * exceptions include RWCancellation, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    bool
    tryAcquire();


    /**
     * Releases the condition mutex, then waits for a thread to signal that
     * the state condition associated with the condition variable has
     * changed. When a thread has been awakened, the condition mutex is
     * automatically reacquired. If another thread holds the mutex when the
     * thread awakes, then the thread must wait until it can acquire the
     * mutex before proceeding. Possible exceptions include RWCancellation
     * and RWTHRInternalError.
     *
     * Calling this function produces an assertion in single-threaded debug
     * mode builds, and an RWTHRInternalError is thrown in release builds.
     */
    void
    wait();


    /**
     * This function is similar to wait(), but returns #RW_THR_TIMEOUT if
     * the specified amount of time elapses before the thread signals.
     * Otherwise, returns #RW_THR_SIGNALED when the thread is signaled that
     * the state condition has changed. Note that if the wait times out, the
     * function won't return until the condition mutex can be reacquired.
     * Possible exceptions include RWCancellation and RWTHRInternalError.
     *
     * This function immediately returns #RW_THR_TIMEOUT in single-threaded
     * builds.
     */
    RWWaitStatus
    wait(unsigned long milliseconds);


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWCondition>     LockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryLockGuard<RWCondition>  TryLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWCondition>   UnlockGuard;

#if !defined(RW_DISABLE_DEPRECATED)
    typedef RWTUnlockGuard<RWCondition>         UnLockGuard;
#endif

protected:


    /**
     * Returns a reference to the mutex associated with this condition
     * variable.
     */
    RWMutexLock&
    mutex() const;

private:


    /**
     * Assignment prohibited.
     */
    RWCondition(const RWCondition& second);


    /**
     * Copy construction prohibited.
     */
    RWCondition& operator=(const RWCondition& second);

};

/*****************************************************************************/

inline void
RWCondition::acquire()
{
    mutex_.acquire();
}

inline RWWaitStatus
RWCondition::acquire(unsigned long milliseconds)
{
    return mutex_.acquire(milliseconds);
}

#if defined(RW_THR_THREAD_API_POSIX) || \
    defined(RW_THR_THREAD_API_SOLARIS)

// Give access to underlying mechanism on platforms that have one...
inline RWConditionRep*
RWCondition::getConditionRep() const
{
    return const_cast<RWConditionRep*>(&RW_EXPOSE(condition_));
}

#endif

inline void
RWCondition::release()
{
    mutex_.release();
}

inline bool
RWCondition::tryAcquire()
{
    return mutex_.tryAcquire();
}

// Return reference to the mutex associated with this condition variable
inline RWMutexLock&
RWCondition::mutex() const
{
    return (RWMutexLock&)mutex_;
}

/*****************************************************************************/

#endif // __rw_sync_RWCondition_h__
