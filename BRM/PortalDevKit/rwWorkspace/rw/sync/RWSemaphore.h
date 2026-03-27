#ifndef __rw_sync_RWSemaphore_h__
#define __rw_sync_RWSemaphore_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWSemaphore.h#1 $
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

#include <rw/sync/RWSynchObject.h>
#include <rw/sync/RWTLockGuard.h>
#include <rw/sync/RWTTryLockGuard.h>
#include <rw/sync/RWTUnlockGuard.h>
#include <rw/sync/fwd.h>
#include <rw/sync/pkgdefs.h>

//
//    Define internal semaphore representation, RWSemaphoreRep.
//
//    POSIX and Solaris use internal structure.
//    All other platforms typedef from underlying platform-defined type.
//

#if (defined(RW_MULTI_THREAD) && (defined(RW_THR_THREAD_API_POSIX) || defined(RW_THR_THREAD_API_SOLARIS))) \
      || defined(DOXYGEN)

//    POSIX 1003.4a/1c does not provide a semaphore mechanism.
//    POSIX 1003.1b does provide one, but it is really a process-level
//    mechanism and is subject to several restrictions including kernel limits
//    on the number that may be supported at once.  We don't want to apply
//    these restrictions on thread programmers, so we'll emulate semaphores on
//    POSIX platforms.
//
//    Solaris provides a native semaphore, but it does not allow for an
//    acquire with timeout. We view this as being a vital feature, especially
//    with respect to thread cancellation. We could either remove semaphore
//    acquire-with-timeout functionality from RWSemaphore on all platforms,
//    for the sake of consistency; or we could emulate semaphores on Solaris
//    as well. We decided on the latter. The only issue perhaps is native
//    semaphores on Solaris are said to by async. safe; meaning that they can
//    safely be posted from signal handlers. Our recommendation would be: don't
//    install signal handlers. If you really have to, and you need to post a
//    semaphore, use the raw native semaphore calls.

#  include <rw/sync/RWCondition.h>
#  include <rw/sync/RWMutexLock.h>
#endif

#if (defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32)) \
      || defined(DOXYGEN)
#  define RW_MAX_SEMAPHORE_COUNT 0x7FFFFFFFL

// Use an explicit void* instead of HANDLE to avoid windows.h inclusion
/**
 * \relates RWSemaphore
 *
 * This is the internal semaphore representation.
 *
 * \conditional
 * This type is used for build configurations based on Win32 threads.
 */
typedef void* RWSemaphoreRep;

#endif

#if defined(RW_MULTI_THREAD) && !defined(RW_THR_THREAD_API_WIN32) \
      && !defined(RW_THR_THREAD_API_POSIX) && !defined(RW_THR_THREAD_API_SOLARIS)
#  error RWSemaphoreRep declaration is missing!
#endif

/*****************************************************************************/

/**
 * \ingroup synchronization_package
 *
 * \brief
 * A synchronization object that maintains a non-negative counter.
 *
 * An RWSemaphore is a synchronization object that maintains a non-negative
 * counter. When a semaphore is acquired, the count is decremented. If the
 * count is zero when acquire() is called, then the calling thread is put on
 * a wait queue and blocks. When the thread reaches the head of the queue,
 * it can acquire the semaphore as soon as the counter is incremented. The
 * count is incremented when a thread calls release() on the semaphore. The
 * initial count of a semaphore is set when it is created; it defaults to 0.
 *
 * An important difference between a mutex and a semaphore with a count of 1
 * is that a mutex can be released only by the thread that acquired it. A
 * semaphore can be released by any thread.
 *
 * Among the uses of semaphores are restricting access to some limited
 * resource, and signaling some condition between threads.
 *
 * \example
 * \code
 * // This program simulates a situation where 5 people all want to
 * // take a nap but there are only two pillows. (And no one is
 * // willing to risk a stiff neck by sleeping without one!)
 * // A semaphore with an initial count of 2 is used to coordinate
 * // access to this limited resource. The semaphore ensures that
 * // at most two people are sleeping at any given time.
 *
 * #include <iostream>
 * #include <rw/sync/RWSemaphore.h>
 * #include <rw/sync/RWMutexLock.h>
 * #include <rw/functor/rwBind.h>
 * #include <rw/thread/RWThread.h>
 * #include <rw/thread/RWThreadFunction.h>
 *
 * RWSemaphore sem(2);     // Coordinate pool of 2 pillows
 * RWMutexLock coutLock;   // Coordinate use of cout
 *
 * void print(int id, const char* p)
 * {
 *     RWMutexLock::LockGuard lock(coutLock);
 *     std::cout << "Thread " << id << " " << p << std::endl;
 * }
 *
 * void takeNap(int id)
 * {
 *     print(id, "is waiting for a pillow");
 *     sem.acquire();  // Get one of the two pillows
 *
 *     print(id, "has acquired a pillow and is settling down for a nap");
 *     rwSleep(1000);  // Even a 1 second nap can be very refreshing!
 *
 *     print(id, "is awake and making a pillow available");
 *     sem.release();  // Make a pillow available
 * }
 *
 * int main()
 * {
 *     int i;
 *     RWThread thread[5];
 *
 *     for (i = 0; i < 5; ++i) {
 *         thread[i] = RWThreadFunction::make(rwBind(takeNap, i + 1));
 *         thread[i].start();
 *     }
 *
 *     for (i = 0; i < 5; ++i) {
 *         thread[i].join();
 *     }
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * Thread 1 is waiting for a pillow
 * Thread 1 has acquired a pillow and is settling down for a nap
 * Thread 2 is waiting for a pillow
 * Thread 2 has acquired a pillow and is settling down for a nap
 * Thread 3 is waiting for a pillow
 * Thread 4 is waiting for a pillow
 * Thread 5 is waiting for a pillow
 * Thread 1 is awake and making a pillow available
 * Thread 2 is awake and making a pillow available
 * Thread 3 has acquired a pillow and is settling down for a nap
 * Thread 4 has acquired a pillow and is settling down for a nap
 * Thread 3 is awake and making a pillow available
 * Thread 4 is awake and making a pillow available
 * Thread 5 has acquired a pillow and is settling down for a nap
 * Thread 5 is awake and making a pillow available
 * \endcode
 * \endexample
 *
 * \sa
 * RWSynchObject, RWTLockGuard, RWTTryLockGuard, RWTUnlockGuard
 */
class RW_SYNC_SYMBOLIC RWSemaphore :
    public RWSynchObject
{

protected:

#if !defined(RW_MULTI_THREAD)

    unsigned long count_;

#elif defined(RW_THR_THREAD_API_POSIX) || \
    defined(RW_THR_THREAD_API_SOLARIS)

    //    Emulate semaphores on POSIX and Solaris platforms using a mutex, a
    //    condition variable, and a count.

    RWMutexLock                countLock_;
    RWCondition                nonZero_;
    unsigned long              waitingThreads_;
    unsigned long              count_;

#elif defined(RW_THR_THREAD_API_WIN32)

    RWSemaphoreRep    semaphore_;

#endif

public:


    // Create semaphore with an initial count (default to zero)
    /**
     * Creates a semaphore with an initial counter set to \a count. The
     * thread cancellation state of the object is initialized to \a state.
     * Possible exceptions include RWTHRResourceLimit and
     * RWTHRInternalError.
     */
    RWSemaphore(unsigned count = 0,
                RWCancellationState state = RW_CANCELLATION_DISABLED);


    /**
     * Recovers any system resources used to implement the RWSemaphore.
     * Possible exceptions include RWTHRInternalError.
     */
    ~RWSemaphore();


    /**
     * Acquires the semaphore by attempting to decrement the count. If the
     * semaphore count is zero, the current thread blocks until another
     * thread increments the count by calling release(). Otherwise, the
     * count is decremented and the thread is allowed to proceed. Possible
     * exceptions include RWCancellation, RWTHRResourceLimit, and
     * RWTHRInternalError.
     *
     * This method returns immediately in single-threaded builds. If the
     * resource is unavailable for acquisition, a debug assertion occurs or
     * an RWTHRInternalError is thrown.
     */
    void
    acquire();


    // Decrement (acquire) the semaphore, blocking while zero,
    // until unblocked when another thread increments (releases)
    // the semaphore or until the specified amount of time passes.
    /**
     * Acquires the semaphore by attempting to decrement the count. If the
     * semaphore count is zero, the current thread blocks until another
     * thread increments the count or the specified amount of time expires.
     * If the time has expired, the method returns #RW_THR_TIMEOUT.
     * Otherwise, the count is decremented and the thread is allowed to
     * proceed. Possible exceptions include RWCancellation,
     * RWTHRResourceLimit, and RWTHRInternalError.
     *
     * This method returns immediately in single-threaded builds.
     */
    RWWaitStatus
    acquire(unsigned long milliseconds);

#if defined(RW_MULTI_THREAD) && \
    defined(RW_THR_THREAD_API_WIN32) || defined(DOXYGEN)


    // Give access to the underlying mechanism on platforms that provide one...
    /**
     * Provides access to the underlying mechanism.
     *
     * \conditional
     * This function is available only in build configurations based on
     * Win32 threads.
     */
    RWSemaphoreRep*
    getSemaphoreRep() const;

#endif


    /**
     * Calls acquire(). \c P stands for <em>passeren</em>, which is Dutch
     * for <em>to pass</em>. Provided for those who wish to use this
     * traditional sign handed down from the Dutch inventor of the
     * semaphore, E. W. Dijkstra. Possible exceptions include
     * RWCancellation, RWTHRResourceLimit, and RWTHRInternalError.
     */
    void
    P();


    /**
     * Returns the result of calling
     * \ref acquire(unsigned long milliseconds) "acquire(milliseconds)".
     * \c P stands for \e passeren, which is Dutch for <em>to pass</em>.
     * Provided for those who wish to use this traditional sign handed down
     * from the Dutch inventor of the semaphore, E. W. Dijkstra. Possible
     * exceptions include RWCancellation, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    RWWaitStatus
    P(unsigned long milliseconds);


    // Increment (release) the semaphore and unblock one waiting thread (if any)
    /**
     * Releases the semaphore by incrementing the semaphore count. Possible
     * exceptions include RWTHRInternalError.
     *
     * \note
     * This method always increments the count, even if the count is
     * increased beyond that supplied to the constructor. For instance, the
     * sequence <tt>sem = RWSemaphore(1); sem.release();</tt> increases the
     * sempaphore's count to 2.
     */
    void
    release();


    // Try to decrement (acquire) semaphore without blocking
    // return true for success and false if the semaphore is zero.
    /**
     * Tries to acquire the semaphore by decrementing the count. If
     * successful, returns \c true; otherwise returns \c false. Possible
     * exceptions include RWCancellation and RWTHRInternalError.
     */
    bool
    tryAcquire();


    /**
     * Calls release(). \c V stands for <em>vrygeven</em>, which is Dutch
     * for "to release." Provided for those who wish to use this traditional
     * sign handed down from the Dutch inventor of the semaphore, E. W.
     * Dijkstra. Possible exceptions include RWTHRInternalError.
     *
     * \note
     * This method always increments the count, even if the count is
     * increased beyond that supplied to the constructor. For instance, the
     * sequence <tt>sem = RWSemaphore(1); sem.v();</tt> increases the
     * semaphore's count to 2.
     */
    void
    V();


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWSemaphore>     LockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryLockGuard<RWSemaphore>  TryLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWSemaphore>   UnlockGuard;

#if !defined(RW_DISABLE_DEPRECATED)
    typedef RWTTryLockGuard<RWSemaphore>  TryGuard;
#endif

private:

    /**
     * Copy construction prohibited.
     */
    RWSemaphore(const RWSemaphore& second);


    /**
     * Assignment prohibited.
     */
    RWSemaphore&
    operator=(const RWSemaphore& second);

};

/*****************************************************************************/

#if defined(RW_MULTI_THREAD) && \
    defined(RW_THR_THREAD_API_WIN32)

inline RWSemaphoreRep*
RWSemaphore::getSemaphoreRep() const
{
    return (RWSemaphoreRep*)&semaphore_;
}

#endif

inline void
RWSemaphore::P()
{
    acquire();
}

inline RWWaitStatus
RWSemaphore::P(unsigned long milliseconds)
{
    return acquire(milliseconds);
}

inline void
RWSemaphore::V()
{
    release();
}

/*****************************************************************************/

#endif // __rw_sync_RWSemaphore_h__
