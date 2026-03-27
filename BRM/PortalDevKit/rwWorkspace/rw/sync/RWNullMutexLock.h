#ifndef __rw_sync_RWNullMutexLock_h__
#define __rw_sync_RWNullMutexLock_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWNullMutexLock.h#1 $
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

/*****************************************************************************/

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Efficient stand-in for a mutual exclusion lock when synchronization is
 * either unnecessary or not important.
 *
 * An RWNullMutexLock is an efficient stand-in for a mutual exclusion lock,
 * particularly when you know that critical sections of code do not need
 * synchronization. For example, you may know that it is not possible for
 * more than one thread to simultaneously enter a section of code that would
 * otherwise require locking. In such cases, you can use an RWNullMutexLock
 * to eliminate the unnecessary overhead of acquiring and releasing a mutex.
 * This class can also be used to instantiate a single-threaded or
 * non-thread-safe version of the template classes that accept a mutex
 * parameter, such as RWTMonitor.
 *
 * \example
 * \code
 * #include <rw/sync/RWMutexLock.h>
 * #include <rw/sync/RWNullMutexLock.h>
 *
 * int main()
 * {
 *     RWNullMutexLock mutex;
 *
 *     mutex.acquire();  // No cost if synchronization not required
 *     // critical section
 *     mutex.release();
 *
 *     // Same thing, this time using a guard:
 *     {
 *         RWNullMutexLock::Lockguard lock(mutex); // does nothing if
 *                                                 // synchronization not
 *                                                 // required critical section
 *
 *         // If synchronization required, lock will be released
 *         // automatically
 *     }
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWMutexLock, RWTLockGuard, RWTUnlockGuard, RWTTryLockGuard
 */
class RW_SYNC_SYMBOLIC RWNullMutexLock :
    public RWSynchObject
{

public:


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWNullMutexLock>          LockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTReadLockGuard<RWNullMutexLock>      ReadLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTWriteLockGuard<RWNullMutexLock>     WriteLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryLockGuard<RWNullMutexLock>       TryLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryReadLockGuard<RWNullMutexLock>   TryReadLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryWriteLockGuard<RWNullMutexLock>  TryWriteLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWNullMutexLock>        UnlockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTReadUnlockGuard<RWNullMutexLock>    ReadUnlockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTWriteUnlockGuard<RWNullMutexLock>   WriteUnlockGuard;

    /**
     * Constructs a static instance, but does no direct initialization. The
     * RWNullMutexLock is initialized on first use.
     *
     * This constructor must be used only for static instances. Use of this
     * constructor with an automatically or dynamically allocated instance
     * produces errors or other unpredictable behavior.
     *
     * Static instances are zero initialized, which results in an
     * RWNullMutexLock with a cancellation state of
     * RW_CANCELLATION_DISABLED.
     */
    RWNullMutexLock(RWStaticCtor);

    RWNullMutexLock(RWNoInitialization);


    /**
     * Creates an RWNullMutexLock. The parameter \a state is currently
     * ignored.
     */
    RWNullMutexLock(RWCancellationState state = RW_CANCELLATION_DISABLED);


    /**
     * Destructor.
     */
    ~RWNullMutexLock();


    /**
     * Does nothing.
     */
    void
    acquire();


    /**
     * Returns #RW_THR_ACQUIRED.
     */
    RWWaitStatus
    acquire(unsigned long milliseconds);


    /**
     * Does nothing.
     */
    void
    acquireRead();


    // Provide compatibility with read/write locks
    /**
     * Returns #RW_THR_ACQUIRED.
     */
    RWWaitStatus
    acquireRead(unsigned long milliseconds);


    /**
     * Does nothing.
     */
    void
    acquireWrite();


    // Provide compatibility with read/write locks
    /**
     * Returns #RW_THR_ACQUIRED.
     */
    RWWaitStatus
    acquireWrite(unsigned long milliseconds);


#if defined(RW_SYNC_DEBUG) || defined(DOXYGEN)

    // Determine whether calling thread currently owns mutex
    /**
     * Returns \c true.
     *
     * \conditional
     * Available only from the debug version of the Threads Module.
     */
    bool
    isAcquired() const;

#endif


    /**
     * Does nothing.
     */
    void
    release();


    /**
     * Returns \c true.
     */
    bool
    tryAcquire();


    /**
     * Returns \c true.
     */
    bool
    tryAcquireRead();


    /**
     * Returns \c true.
     */
    bool
    tryAcquireWrite();

private:

    // Prohibit automatic compiler generation of these member functions...
    /**
     * Copy construction prohibited.
     */
    RWNullMutexLock(const RWNullMutexLock& second);


    /**
     * Assignment prohibited.
     */
    RWNullMutexLock&
    operator=(const RWNullMutexLock& second);

};

/*****************************************************************************/

// Constructor for use by global static instances. Does not explicitly
// initialize, hence object may be used before constructed. Global
// instances are zero initialized, which will result in an
// RWNullMutexLock with cancellation state of RW_CANCELLATION_DISABLED.
inline
RWNullMutexLock::RWNullMutexLock(RWStaticCtor)
    : RWSynchObject(RW_STATIC_CTOR)
{
}

inline
RWNullMutexLock::RWNullMutexLock(RWNoInitialization)
{
}

inline
RWNullMutexLock::RWNullMutexLock(RWCancellationState state)
    : RWSynchObject(state)
{
}

inline
RWNullMutexLock::~RWNullMutexLock()
{
}

inline void
RWNullMutexLock::acquire()
{
    // check that cancellations are enabled
    testCancellation();
}

inline RWWaitStatus
RWNullMutexLock::acquire(unsigned long)
{
    // check that cancellations are enabled
    testCancellation();

    return RW_THR_ACQUIRED;
}

inline void
RWNullMutexLock::acquireRead()
{
    acquire();
}

inline RWWaitStatus
RWNullMutexLock::acquireRead(unsigned long)
{
    return acquire(0);
}

inline void
RWNullMutexLock::acquireWrite()
{
    acquire();
}

inline RWWaitStatus
RWNullMutexLock::acquireWrite(unsigned long)
{
    return acquire(0);
}

#if defined(RW_SYNC_DEBUG)

inline bool
RWNullMutexLock::isAcquired() const
{
    return true;
}

#endif

inline void
RWNullMutexLock::release()
{
}

inline bool
RWNullMutexLock::tryAcquire()
{
    // check that cancellations are enabled
    testCancellation();

    return true;
}

inline bool
RWNullMutexLock::tryAcquireRead()
{
    return tryAcquire();
}

inline bool
RWNullMutexLock::tryAcquireWrite()
{
    return tryAcquire();
}

#endif // __rw_sync_RWNullMutexLock_h__
