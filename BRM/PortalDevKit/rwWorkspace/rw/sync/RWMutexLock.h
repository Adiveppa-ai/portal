#ifndef __rw_sync_RWMutexLock_h__
#define __rw_sync_RWMutexLock_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWMutexLock.h#1 $
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
#include <rw/sync/RWTGuardBase.h>
#include <rw/sync/RWTLockGuard.h>
#include <rw/sync/RWTLockGuardBase.h>
#include <rw/sync/RWTReadLockGuard.h>
#include <rw/sync/RWTReadUnlockGuard.h>
#include <rw/sync/RWTTryLockGuard.h>
#include <rw/sync/RWTTryReadLockGuard.h>
#include <rw/sync/RWTTryWriteLockGuard.h>
#include <rw/sync/RWTUnlockGuard.h>
#include <rw/sync/RWTWriteLockGuard.h>
#include <rw/sync/RWTWriteUnlockGuard.h>
#include <rw/sync/pkgdefs.h>
#include <rw/mutex.h>
#include <rw/tools/atomic.h>


#if defined(RW_SYNC_DEBUG) && \
    defined(RW_MULTI_THREAD)
#  include <rw/sync/RWThreadId.h>
#endif

#if !defined(RW_MULTI_THREAD)
/**
 * \relates RWMutexLock
 *
 * Typedef for the internal mutex lock.
 *
 * \conditional
 * This type is used for single-threaded build configurations.
 */
typedef bool RWMutexLockRep;
#endif

#if (defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_POSIX)) \
      || defined(DOXYGEN)
/**
 * \relates RWMutexLock
 *
 * Typedef for the internal mutex lock.
 *
 * \conditional
 * This type is used for build configurations based on POSIX threads.
 */
typedef pthread_mutex_t RWMutexLockRep;
#endif

#if (defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_SOLARIS)) \
      || defined(DOXYGEN)
#  include <synch.h>
/**
 * \relates RWMutexLock
 *
 * Typedef for the internal mutex lock.
 *
 * \conditional
 * This type is used for build configurations based on Solaris threads.
 */
typedef mutex_t RWMutexLockRep;
#endif

#if (defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32) \
      && defined(RW_SYNC_MUTEX_USES_CRITICAL_SECTION)) || defined(DOXYGEN)
/**
 * \relates RWMutexLock
 *
 * Typedef for the internal mutex lock.
 *
 * \conditional
 * This type is used for build configurations based on Win32 threads when
 * the macro \c RW_SYNC_MUTEX_USES_CRITICAL_SECTION is defined.
 */
typedef RW_MUTEX_T RWMutexLockRep;
#endif

#if (defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32) \
      && !defined(RW_SYNC_MUTEX_USES_CRITICAL_SECTION)) || defined(DOXYGEN)
// Use an explicit void* instead of HANDLE to avoid windows.h inclusion
/**
 * \relates RWMutexLock
 *
 * Typedef for the internal mutex lock.
 *
 * \conditional
 * This type is used for build configurations based on Win32 threads when
 * the macro \c RW_SYNC_MUTEX_USES_CRITICAL_SECTION is not defined.
 */
typedef void* RWMutexLockRep;
#endif

#if defined(RW_MULTI_THREAD) && !defined(RW_THR_THREAD_API_POSIX) \
      && !defined(RW_THR_THREAD_API_SOLARIS) && !defined(RW_THR_THREAD_API_WIN32)
#  error RWMutexLockRep declaration is missing!
#endif

// forward declare friend class
class RWIdUnlockGuard;

/*************************************************************************/

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Implements a \e mutex, or mutual exclusion lock.
 *
 * RWMutexLock implements a \e mutex or mutual exclusion lock. It can be
 * used to permit only one thread at a time to access a section of code that
 * is to be treated as a single atomic operation. Mutexes are typically used
 * to protect sections of code that access shared resources or data. The
 * sensitive area of code, or critical section, is bracketed by calls to
 * acquire() and release() on the mutex.
 *
 * All operations on the mutex, except initialization, are themselves
 * guaranteed to be atomic in order to prevent race conditions from
 * destroying the integrity of the lock. However, there is no reliable
 * mechanism to guarantee that a race condition will not occur during
 * initialization of a mutex lock. Generally, the application can ensure
 * this by creating and initializing all mutexes in a primary thread of
 * execution, before other threads are spawned. However, in the common case,
 * when a mutex is used to protect static global data, there is no portable
 * way to atomically initialize the mutex because C++ defines the order of
 * initialization of static variables to be implementation-specific.
 *
 * RWMutexLock provides some protection against race conditions during
 * initialization of static global mutexes through a special constructor
 * that does no initialization. When this constructor is used,
 * initialization is postponed until the first attempt to acquire the lock.
 * In order to prevent race conditions during mutex initialization by using
 * this constructor, the application must still make sure the first acquire
 * operation on such a mutex is not attempted concurrently by two or more
 * threads.
 *
 * This class is primarily a portable object wrapper for platform-specific
 * mutex implementations. For example, RWMutexLock uses an instance of
 * \c pthread_mutex_t for POSIX conforming environments, \c mutex_t on
 * Solaris platforms, and a mutex represented by a \c HANDLE under Win32.
 *
 * If the Threads Module is built with the "Implement RWMutexLock with a
 * Critical Section" option enabled, the underlying implementation of the
 * class is altered to use a \c CRITICAL_SECTION under Win32 systems instead
 * of a \c HANDLE. This provides a significant performance boost in many
 * cases at the cost of some portability and functionality.
 *
 * \example
 * \code
 * #include <rw/sync/RWMutexLock.h>
 * #include <rw/sync/RWTLockGuard.h>
 *
 * class SavingsAccount {
 * public:
 *    SavingsAccount(int initialBalance);
 *    void deposit(int amount);
 *    void withdraw(int amount);
 *    int balance(void);
 *    static void decreaseInterestRate(double decrement);
 *    static double getInterestRate(void);
 *
 * private:
 *    int balance_;
 *    static double interestRate_;
 *    RWMutexLock objectMutex_;       // mutex to protect
 *                                    // instance data
 * };
 *
 * void SavingsAccount::deposit(int amount)
 * {
 *    // Acquire mutex so that only one thread can access the
 *    // state. Normally you should use a LockGuard to acquire a
 *    // mutex that is to be released at the end of a scope. We
 *    // show the explicit form here for completeness. The
 *    // preferred form is shown below.
 *
 *    objectMutex_.acquire();
 *    balance_ += amount;
 *    objectMutex_.release();
 *
 * }
 *
 * void SavingsAccount::withdraw(int amount)
 * {
 *    // An RWTLockGuard acquires a synchronization object
 *    // in its constructor and releases it in its destructor.
 *    // Using this class is preferred over direct calls to acquire
 *    // and release the mutex because:
 *    // 1) you will never forget to do the release
 *    // 2) if an exception is thrown from somewhere in your
 *    //    function, the lock will always be released because all
 *    //    objects on the stack will have their destructors called
 *    //    as the stack is unwound.
 *
 *    // calls objectMutex_.acquire():
 *    RWTLockGuard<RWMutexLock> lock(objectMutex_);
 *    balance_ -= amount;
 *
 *    // objectMutex released in lock destructor.
 * }
 *
 * int SavingsAccount::balance(void)
 * {
 *    // RWMutexLock::LockGuard is a typedef of
 *    // RWTLockGuard<RWMutexLock>. It has the same effect
 *    // as above. This is the form that we prefer
 *    // for purely aesthetic reasons:
 *
 *    RWMutexLock::LockGuard lock(objectMutex_);
 *    return balance_;
 *
 *    // objectMutex released in lock destructor.
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWNullMutexLock, RWTLockGuard, RWTTryLockGuard
 */
class RW_SYNC_SYMBOLIC RWMutexLock : public RWSynchObject
{
private:

    RWMutexLockRep lock_;

#if defined(RW_SYNC_DEBUG) && defined(RW_MULTI_THREAD)
    RWThreadId threadId_;
#endif

    // Zero initialized during static initialization
    volatile RWTAtomic<unsigned char> init_;

public:

    /**
     * Creates an RWMutexLock but does no direct initialization. The mutex
     * will be initialized upon first use.
     *
     * The RWMutexLock static constructor must be used only for global
     * static instances. Use of this constructor with an automatically or
     * dynamically allocated instance produces errors or other unpredictable
     * behavior.
     *
     * The initialization of a global static mutex is not thread-safe. It is
     * conceivable that two threads can attempt to acquire and initialize a
     * mutex simultaneously, resulting in a race condition. When designing
     * your application, take care to avoid such a possibility.
     */
    RWMutexLock(RWStaticCtor);

    RWMutexLock(RWNoInitialization);


    /**
     * Creates and initializes an RWMutexLock. The thread cancellation state
     * of the object is initialized to \a state. Possible exceptions include
     * RWTHRResourceLimit and RWTHRInternalError.
     */
    RWMutexLock(RWCancellationState state = RW_CANCELLATION_DISABLED);


    /**
     * Recovers the system resource used to implement the RWMutexLock.
     * Possible exceptions include RWTHRInternalError.
     */
    ~RWMutexLock();


    /**
     * Causes the current thread to block until the mutex is released, at
     * which time the thread acquires the mutex and continues. In the debug
     * version of the Threads Module, this function will produce an
     * assertion and abort if a thread attempts to recursively acquire the
     * same mutex. Possible exceptions include RWCancellation,
     * RWTHRResourceLimit, and RWTHRInternalError.
     *
     * This function throws an RWCancellation object if the mutex has
     * cancellation detection enabled and a runnable containing the calling
     * thread has been canceled.
     *
     * In single-threaded builds, this method returns immediately. If the
     * mutex was unavailable for acquisition, a debug assertion occurs or an
     * RWTHRInternalError is thrown.
     */
    void
    acquire();


    /**
     * Blocks at least for the specified number of milliseconds, or until
     * the mutex is released, whichever comes first. If the mutex is
     * released within the specified time, acquires it, and continues. If
     * the mutex is \e not released, returns #RW_THR_TIMEOUT. In the debug
     * version of the Threads Module, this function produces an assertion
     * and aborts if a thread attempts to recursively acquire the same
     * mutex.
     *
     * Note that true timed-acquisition is not supported on all platforms.
     * For platforms without true timed-acquisition support, the function
     * simply returns #RW_THR_TIMEOUT if the mutex cannot be acquired
     * immediately, Timed mutex acquisition is available if the macro
     * \c RW_THR_HAS_TIMED_MUTEX_ACQUIRE is defined.
     *
     * This function throws an RWCancellation object if the mutex has
     * cancellation detection enabled and a runnable containing the calling
     * thread has been canceled. Other possible exceptions include
     * RWTHRResourceLimit and RWTHRInternalError.
     *
     * This method returns immediately in single-threaded builds.
     */
    RWWaitStatus
    acquire(unsigned long milliseconds);


    /**
     * Calls acquire(). Provided for compatibility with read/write locks.
     * Possible exceptions include RWCancellation, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    void
    acquireRead();


    /**
     * Calls
     * \ref acquire(unsigned long milliseconds) "acquire(milliseconds)".
     * Provided for compatibility with read/write locks. Possible exceptions
     * include RWCancellation, RWTHRResourceLimit, and RWTHRInternalError.
     */
    RWWaitStatus
    acquireRead(unsigned long milliseconds);


    /**
     * Calls acquire(). Provided for compatibility with read/write locks.
     * Possible exceptions include RWCancellation, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    void
    acquireWrite();


    /**
     * Calls
     * \ref acquire(unsigned long milliseconds) "acquire(milliseconds)".
     * Provided for compatibility with read/write locks. Possible exceptions
     * include RWCancellation, RWTHRResourceLimit, and RWTHRInternalError.
     */
    RWWaitStatus
    acquireWrite(unsigned long milliseconds);


    /**
     * Provides access to the underlying platform-specific mutex
     * implementation.
     */
    RWMutexLockRep*
    getMutexLockRep() const;

#if defined(RW_SYNC_DEBUG) || defined(DOXYGEN)

    /**
     * Determines whether the calling thread currently owns the mutex.
     *
     * \conditional
     * Available only from the debug version of the Threads Module.
     */
    bool
    isAcquired() const;

#endif

    /**
     * Releases the mutex, making it available. Possible exceptions include
     * RWTHRInternalError.
     */
    void
    release();


    /**
     * Tries to acquire the mutex without blocking. Returns \c true if the
     * mutex is acquired, and \c false if the mutex is not acquired.
     *
     * Possible exceptions include RWCancellation, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    bool
    tryAcquire();


    /**
     * Calls tryAcquire(). Provided for compatibility with read/write locks.
     * Possible exceptions include RWCancellation, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    bool
    tryAcquireRead();


    /**
     * Calls tryAcquire(). Provided for compatibility with read/write locks.
     * Possible exceptions include RWCancellation, RWTHRResourceLimit, and
     * RWTHRInternalError.
     */
    bool
    tryAcquireWrite();


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWMutexLock>          LockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTReadLockGuard<RWMutexLock>      ReadLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTWriteLockGuard<RWMutexLock>     WriteLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryLockGuard<RWMutexLock>       TryLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryReadLockGuard<RWMutexLock>   TryReadLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryWriteLockGuard<RWMutexLock>  TryWriteLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWMutexLock>        UnlockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTReadUnlockGuard<RWMutexLock>    ReadUnlockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTWriteUnlockGuard<RWMutexLock>   WriteUnlockGuard;

private:

    void init();
    void do_init();

#if defined(RW_SYNC_DEBUG) && \
   (defined(RW_THR_THREAD_API_SOLARIS) || defined(RW_THR_THREAD_API_POSIX))

    // Give access to acquireId and releaseId debug members:
    friend class RWIdUnlockGuard;

    void
    acquireId();

    void
    releaseId();

#endif

    /**
     * Copy construction prohibited.
     */
    RWMutexLock(const RWMutexLock& second);

    /**
     * Assignment prohibited.
     */
    RWMutexLock&
    operator=(const RWMutexLock& second);

};

/*****************************************************************************/

inline void
RWMutexLock::acquireRead()
{
    acquire();
}

inline void
RWMutexLock::acquireWrite()
{
    acquire();
}

inline RWWaitStatus
RWMutexLock::acquireRead(unsigned long milliseconds)
{
    return acquire(milliseconds);
}

inline RWWaitStatus
RWMutexLock::acquireWrite(unsigned long milliseconds)
{
    return acquire(milliseconds);
}

inline bool
RWMutexLock::tryAcquireRead()
{
    return tryAcquire();
}

inline bool
RWMutexLock::tryAcquireWrite()
{
    return tryAcquire();
}

inline RWMutexLockRep*
RWMutexLock::getMutexLockRep() const
{
    return const_cast<RWMutexLockRep*>(&RW_EXPOSE(lock_));
}

/*************************************************************************/

#endif // __rw_sync_RWMutexLock_h__
