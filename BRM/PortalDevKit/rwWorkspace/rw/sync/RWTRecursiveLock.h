#ifndef __rw_sync_RWTRecursiveLock_h__
#define __rw_sync_RWTRecursiveLock_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTRecursiveLock.h#1 $
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

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWRecursiveLock RWTRecursiveLock
#endif

#include <rw/sync/RWMutexLock.h>
#include <rw/sync/RWSynchObject.h>
#include <rw/sync/RWThreadId.h>
#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Supports recursive acquisition of a mutex.
 *
 * The RWMutexLock and RWFIFOMutexLock classes do not allow a thread to
 * acquire the mutex if it already owns it. Attempts to do so result in an
 * assertion and abort in the debug version of the module, and may result in
 * deadlock in the release version.
 *
 * RWTRecursiveLock can be used to add <em>recursive acquisition</em>
 * semantics to an existing mutex class such as RWMutexLock or
 * RWFIFOMutexLock.
 *
 * This class allows the thread that owns a mutex to reacquire the mutex any
 * number of times before ever releasing it. For each acquisition, however,
 * the thread must release the mutex the same number of times before the
 * resource can become available to another thread.
 *
 * \example
 * \code
 * #include <rw/sync/RWMutexLock.h>
 * #include <rw/sync/RWTRecursiveLock.h>
 *
 * void func1();
 * void func2();
 *
 * RWTRecursiveLock<RWMutexLock> lock;
 * // For this example, assume that the lock is first acquired
 * // in func1():
 * void func1()
 * {
 *   lock.acquire();  // acquire mutex and set count set to 1
 *   // critical section
 *   func2();
 *   lock.release();  // decrement count to 0 and release
 *                    // underlying mutex
 * }
 * void func2()
 * {
 *   lock.acquire();  // OK if called from func1(),
 *                    // increment count to 2
 *   // critical section
 *   lock.release();  // decrement count to 1,
 *                    // thread still owns mutex
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWMutexLock, RWFIFOMutexLock
 */
template <class Mutex>
class RWTRecursiveLock :
    public RWSynchObject
{

    // Member Variables
protected:

    // The actual recursive lock (protected to allow access by derived classes)
    Mutex          lock_;

private:

    // The current owner of the lock. Only modified by thread that owns lock_.
    RWThreadId     threadId_;

    // The recursive nesting level. Only modified by thread that owns lock_.
    int            level_;

public:

    /**
     * Creates and initializes an RWTRecursiveLock. The thread cancellation
     * state of the object is initialized to \a state. Possible exceptions
     * include RWTHRResourceLimit and RWTHRInternalError.
     */
    RWTRecursiveLock(RWCancellationState state = RW_CANCELLATION_DISABLED);

    /**
     * Recovers the system resource used to implement the RWTRecursiveLock.
     * Possible exceptions include RWTHRInternalError.
     */
    ~RWTRecursiveLock();


    /**
     * Acquires the recursive lock, incrementing the nesting level for each
     * time the lock owner calls this method.
     *
     * This function will throw an RWCancellation object if the mutex has
     * cancellation detection enabled and a runnable containing the calling
     * thread has been canceled. Other possible exceptions include
     * RWTHRInternalError.
     */
    void
    acquire();


    /**
     * Acquires the recursive lock, incrementing the nesting level for each
     * time the lock owner calls this method, but timing out if forced to
     * wait for the mutex longer than the specified number of milliseconds.
     * If the call times out, the function returns #RW_THR_TIMEOUT.
     *
     * This function will throw an RWCancellation object if the mutex has
     * cancellation detection enabled and a runnable containing the calling
     * thread has been canceled. Other possible exceptions include
     * RWTHRInternalError.
     */
    RWWaitStatus
    acquire(unsigned long milliseconds);


    /**
     * Calls acquire(). Provided for compatibility with Read/Write locks.
     * Possible exceptions include RWCancellation and RWTHRInternalError.
     */
    void
    acquireRead();


    /**
     * Calls \ref acquire(unsigned long) "acquire(milliseconds)". Provided
     * for compatibility with Read/Write locks. Possible exceptions include
     * RWCancellation and RWTHRInternalError.
     */
    RWWaitStatus
    acquireRead(unsigned long milliseconds);


    /**
     * Calls acquire(). Provided for compatibility with Read/Write locks.
     * Possible exceptions include RWCancellation and RWTHRInternalError.
     */
    void
    acquireWrite();


    /**
     * Calls \ref acquire(unsigned long) "acquire(milliseconds)". Provided
     * for compatibility with Read/Write locks. Possible exceptions include
     * RWCancellation and RWTHRInternalError.
     */
    RWWaitStatus
    acquireWrite(unsigned long milliseconds);

#if defined(RW_SYNC_DEBUG) || defined(DOXYGEN)
    /**
     * Determines whether the calling thread currently owns the mutex.
     *
     * \conditional
     * Only available from the debug version of the Threads Module.
     */
    bool
    isAcquired() const;
#endif


    /**
     * Releases the recursive lock, decrementing the nesting level each time
     * the lock owner calls this method, and releasing the actual lock when
     * the level reaches zero. Possible exceptions include RWTHRIllegalUsage
     * and RWTHRInternalError.
     */
    void
    release();


    /**
     * Conditionally acquires the recursive lock, incrementing the nesting
     * level for each time the lock owner calls this method. This method
     * returns immediately if the lock is unavailable. Returns \c true if
     * the lock is successfully acquired. Possible exceptions include
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
    typedef RWTLockGuard< RWTRecursiveLock< Mutex > >          LockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTReadLockGuard< RWTRecursiveLock< Mutex > >      ReadLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTWriteLockGuard< RWTRecursiveLock< Mutex > >     WriteLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryLockGuard< RWTRecursiveLock< Mutex > >       TryLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryReadLockGuard< RWTRecursiveLock< Mutex > >   TryReadLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryWriteLockGuard< RWTRecursiveLock< Mutex > >  TryWriteLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard< RWTRecursiveLock< Mutex > >        UnlockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTReadUnlockGuard< RWTRecursiveLock< Mutex > >    ReadUnlockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTWriteUnlockGuard< RWTRecursiveLock< Mutex > >   WriteUnlockGuard;

#if !defined(RW_DISABLE_DEPRECATED)
    // These typedefs came with the first release of the SourcePro
    // Core - Threads Module but they do not follow the naming convention
    // for similar typedefs in the other synchronization classes.
    // Therefore these names are now deprecated.
    typedef RWTTryLockGuard< RWTRecursiveLock< Mutex > >       TryGuard;
    typedef RWTTryReadLockGuard< RWTRecursiveLock< Mutex > >   TryReadGuard;
    typedef RWTTryWriteLockGuard< RWTRecursiveLock< Mutex > >  TryWriteGuard;
#endif

private:


    /**
     * Copy construction prohibited.
     */
    RWTRecursiveLock(const RWTRecursiveLock<Mutex>& second);


    /**
     * Assignment prohibited.
     */
    RWTRecursiveLock<Mutex>&
    operator=(const RWTRecursiveLock<Mutex>& second);

};

/*****************************************************************************/

template <class Mutex>
inline
RWTRecursiveLock<Mutex>::~RWTRecursiveLock()
{
}

// Provide compatibility with Read/Write locks
template <class Mutex>
inline void
RWTRecursiveLock<Mutex>::acquireRead()
{
    acquire();
}

// Provide compatibility with Read/Write locks
template <class Mutex>
inline RWWaitStatus
RWTRecursiveLock<Mutex>::acquireRead(unsigned long milliseconds)
{
    return acquire(milliseconds);
}

// Provide compatibility with Read/Write locks
template <class Mutex>
inline void
RWTRecursiveLock<Mutex>::acquireWrite()
{
    acquire();
}

// Provide compatibility with Read/Write locks
template <class Mutex>
inline RWWaitStatus
RWTRecursiveLock<Mutex>::acquireWrite(unsigned long milliseconds)
{
    return acquire(milliseconds);
}

// Provide compatibility with Read/Write locks
template <class Mutex>
inline bool
RWTRecursiveLock<Mutex>::tryAcquireRead()
{
    return tryAcquire();
}

// Provide compatibility with Read/Write locks
template <class Mutex>
inline bool
RWTRecursiveLock<Mutex>::tryAcquireWrite()
{
    return tryAcquire();
}

/*****************************************************************************/

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/sync/RWTRecursiveLock.cc>
#endif

#endif // __rw_sync_RWTRecursiveLock_h__
