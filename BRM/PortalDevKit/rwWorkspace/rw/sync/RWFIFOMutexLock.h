#ifndef __rw_sync_RWFIFOMutexLock_h__
#define __rw_sync_RWFIFOMutexLock_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWFIFOMutexLock.h#1 $
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

#include <rw/sync/RWCondition.h>
#include <rw/sync/RWCriticalSection.h>
#include <rw/sync/RWMutexLock.h>
#include <rw/sync/RWSynchObject.h>
#include <rw/sync/RWThreadId.h>
#include <rw/sync/fwd.h>
#include <rw/sync/pkgdefs.h>
#include <rw/idlist.h>
#include <rw/tvslist.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Guarantees that blocking threads acquire the mutex in the same order that
 * they called the acquire() member function.
 *
 * An RWFIFOMutexLock can be used to guarantee that blocking threads acquire
 * the mutex in the same order that they called the acquire() member
 * function. On certain systems, thread attributes such as thread priority
 * may be a factor in determining the order in which threads blocking on the
 * same mutex acquire that mutex when it is finally released. Class
 * RWFIFOMutexLock eliminates any other factors and considers only the order
 * of requests for acquisition.
 *
 * \example
 * \code
 * #include <rw/sync/RWFIFOMutexLock.h>
 *
 * int main()
 * {
 *     RWFIFOMutexLock fifomutex;
 *     fifomutex.acquire();
 *     // critical section
 *     fifomutex.release();
 *
 *     // Same thing, this time using a guard:
 *     {
 *         RWFIFOMutexLock::LockGuard lock(fifomutex);
 *         // critical section
 *
 *         // Mutex will be released in RWFIFOMutexLock::LockGuard
 *         // destructor before leaving scope, especially important
 *         // if an exception is thrown!
 *     }
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWMutexLock, RWTRecursiveLock
 */
class RW_SYNC_SYMBOLIC RWFIFOMutexLock :
    public RWSynchObject
{

private:

#if !defined(RW_MULTI_THREAD)
    RWMutexLock                lock_;
#elif defined(RW_THR_THREAD_API_WIN32)
    RWCriticalSection          lock_;
    RWIsvDlist                 queue_;
    RWThreadId                 owner_;
#else
    RWMutexLock                lock_;
    RWCondition                waiters_;
    RWTValSlist<RWThreadId>    queue_;
#endif

    // Member Functions
public:

    /**
     * Creates and initializes an RWFIFOMutexLock. The thread cancellation
     * state of the object is initialized to \a state.
     */
    RWFIFOMutexLock(RWCancellationState state = RW_CANCELLATION_DISABLED);

    // NOTE: Due to presence of data members - queue_ and waiters_ in
    // multithreaded builds, this constructor can prevent initialization of
    // data members only in single-threaded builds. Hence, this constructor
    // will function correctly only in single-threaded builds.
    /**
     * Constructs a static instance, but does no direct initialization. The
     * RWFIFOMutexLock is initialized on first use.
     *
     * This constructor must be used only for static instances. Use of this
     * constructor with an automatically or dynamically allocated instance
     * produces errors or other unpredictable behavior.
     *
     * Static instances are zero initialized, which results in an
     * RWFIFOMutexLock with cancellation state of RW_CANCELLATION_DISABLED.
     *
     * \note
     * This constructor functions correctly only in single-threaded builds,
     * due to the presence of some data members that do not implement a
     * constructor with an RWStaticCtor argument.
     */
    RWFIFOMutexLock(RWStaticCtor);

    RWFIFOMutexLock(RWNoInitialization);


    /**
     * Recovers any system resources used to implement the RWFIFOMutexLock.
     */
    ~RWFIFOMutexLock();

    /**
     * Causes the current thread to block until the mutex is released, at
     * which time the thread acquires the mutex and continues. If other
     * threads are blocked waiting for this same mutex, the first thread
     * that called this member function acquires the mutex and continues.
     * Possible exceptions include RWCancellation and RWTHRInternalError.
     *
     * In single-threaded builds, this method does not block. On success, it
     * returns immediately; otherwise it fails with a debug assertion in
     * debug mode, or a thrown RWTHRInternalError in release builds.
     */
    void
    acquire();


    /**
     * Blocks at least for the specified number of milliseconds, or until
     * the mutex is released, whichever comes first. If the mutex is
     * released within the specified time, acquires it and continues. If the
     * mutex is \e not released, returns #RW_THR_TIMEOUT. Possible
     * exceptions include RWCancellation and RWTHRInternalError.
     *
     * In single-threaded builds, this method immediately returns
     * #RW_THR_ACQUIRED if the resource is currently available, otherwise
     * returns #RW_THR_TIMEOUT.
     */
    RWWaitStatus
    acquire(unsigned long milliseconds);

#if defined(RW_SYNC_DEBUG) || defined(DOXYGEN)

    // Members used to specify debug-mode assertions in other classes.

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
     * Calls acquire(). Provided for compatibility with Read/Write locks.
     * Possible exceptions include RWCancellation and RWTHRInternalError.
     */
    void
    acquireRead();

    /**
     * Calls acquire(). Provided for compatibility with Read/Write locks.
     * Possible exceptions include RWCancellation and RWTHRInternalError.
     */
    void
    acquireWrite();

    /**
     * Calls
     * \ref acquire(unsigned long milliseconds) "acquire(milliseconds)".
     * Provided for compatibility with Read/Write locks. Possible exceptions
     * include RWCancellation and RWTHRInternalError.
     */
    RWWaitStatus
    acquireRead(unsigned long milliseconds);

    /**
     * Calls
     * \ref acquire(unsigned long milliseconds) "acquire(milliseconds)".
     * Provided for compatibility with Read/Write locks. Possible exceptions
     * include RWCancellation and RWTHRInternalError.
     */
    RWWaitStatus
    acquireWrite(unsigned long milliseconds);

    /**
     * Tries to acquire mutex without blocking. Returns \c true if
     * successful, otherwise \c false. Possible exceptions include
     * RWCancellation and RWTHRInternalError.
     */
    bool
    tryAcquire();

    /**
     * Calls tryAcquire(). Provided for compatibility with Read/Write locks.
     * Possible exceptions include RWCancellation and RWTHRInternalError.
     */
    bool
    tryAcquireRead();

    /**
     * Calls tryAcquire(). Provided for compatibility with Read/Write locks.
     * Possible exceptions include RWCancellation and RWTHRInternalError.
     */
    bool
    tryAcquireWrite();

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWFIFOMutexLock>        LockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWFIFOMutexLock>        ReadLockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWFIFOMutexLock>        WriteLockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryLockGuard<RWFIFOMutexLock>     TryLockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryLockGuard<RWFIFOMutexLock>     TryReadLockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryLockGuard<RWFIFOMutexLock>     TryWriteLockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWFIFOMutexLock>      UnlockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWFIFOMutexLock>      ReadUnlockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWFIFOMutexLock>      WriteUnlockGuard;

private:

    /**
     * Copy construction prohibited.
     */
    RWFIFOMutexLock(const RWFIFOMutexLock& second);

    /**
     * Assignment prohibited.
     */
    RWFIFOMutexLock&
    operator=(const RWFIFOMutexLock& second);

};

/*****************************************************************************/

inline
RWFIFOMutexLock::RWFIFOMutexLock(RWCancellationState state)
    : RWSynchObject(state)
#if defined(RW_MULTI_THREAD) && !defined(RW_THR_THREAD_API_WIN32)
    , waiters_(lock_)
#endif
{
}

// Constructor for use by global static instances. Does not explicitly
// initialize, hence object may be used before constructed. Global
// instances are zero initialized, which will result in an
// RWFIFOMutexLock with cancellation state of RW_CANCELLATION_DISABLED.
//
// NOTE: Due to presence of data members - queue_ and waiters_ in
// multithreaded builds, this constructor can prevent initialization of data
// members only in single-threaded builds. Hence, this constructor will
// function correctly only in single-threaded builds.
inline
RWFIFOMutexLock::RWFIFOMutexLock(RWStaticCtor)
    : RWSynchObject(RW_STATIC_CTOR)
    , lock_(RW_STATIC_CTOR)
#if defined(RW_MULTI_THREAD)
#  if defined(RW_THR_THREAD_API_WIN32)
    , owner_(RW_STATIC_CTOR)
#  else
    , waiters_(lock_)
#  endif
#endif
{
}

inline
RWFIFOMutexLock::RWFIFOMutexLock(RWNoInitialization)
    : RWSynchObject(RW_CANCELLATION_DISABLED)
    , lock_(RW_NO_INIT)
#if defined(RW_MULTI_THREAD) && !defined(RW_THR_THREAD_API_WIN32)
    , waiters_(lock_)
#endif
{
}

inline
RWFIFOMutexLock::~RWFIFOMutexLock()
{
}

inline void
RWFIFOMutexLock::acquireRead()
{
    acquire();
}

inline void
RWFIFOMutexLock::acquireWrite()
{
    acquire();
}

inline RWWaitStatus
RWFIFOMutexLock::acquireRead(unsigned long milliseconds)
{
    return acquire(milliseconds);
}

inline RWWaitStatus
RWFIFOMutexLock::acquireWrite(unsigned long milliseconds)
{
    return acquire(milliseconds);
}

inline bool
RWFIFOMutexLock::tryAcquireRead()
{
    return tryAcquire();
}

inline bool
RWFIFOMutexLock::tryAcquireWrite()
{
    return tryAcquire();
}

/*****************************************************************************/

#endif // __rw_sync_RWFIFOMutexLock_h__
