#ifndef __rw_sync_RWReadersWriterLock_h__
#define __rw_sync_RWReadersWriterLock_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWReadersWriterLock.h#1 $
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

#if defined(RW_MULTI_THREAD)
#  include <rw/sync/RWCondition.h>
#  if defined(RW_SYNC_DEBUG)
#    include <rw/sync/RWThreadId.h>
#    include <rw/tvslist.h>
#  endif // RW_SYNC_DEBUG
#endif // RW_MULTI_THREAD

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup synchronization_package
 *
 * \brief
 * A synchronization lock that allows concurrent access to multiple readers,
 * but limits access to a single writer.
 *
 * RWReadersWriterLock is a multiple-readers, single-writer synchronization
 * lock. With this type of lock, multiple readers are allowed concurrent
 * access to the protected critical section. However, exclusive access is
 * granted to writers: a reader and a writer cannot both enter the critical
 * section, and only one writer at a time is granted access. A writer that
 * attempts to acquire the lock blocks waiting for readers to exit the
 * critical section. Note that because this lock favors writers over
 * readers, the writer gets priority over any readers that try to access the
 * lock after the time that the writer attempts to acquire it. A reader
 * attempting to access the lock acquires it only after all writers
 * attempting access have acquired and released the lock.
 *
 * \example
 * \code
 * #include <iostream>
 * #include <rw/sync/RWReadersWriterLock.h>
 *
 * // Class Ratio maintains the ratio x : y.  Once x and y
 * // are set in the constructor, any change to either x
 * // or y causes the other to change such that the
 * // ratio is maintained.
 * //
 * // It is important that modifications of x and y occur
 * // as an atomic operation since, during the brief period
 * // between modifying one and then the other, the object is
 * // in an inconsistent state.
 *
 * class Ratio
 * {
 * private:
 *     typedef RWReadersWriterLock::ReadLockGuard  ReadGuard;
 *     typedef RWReadersWriterLock::WriteLockGuard WriteGuard;
 *     double x_;
 *     double y_;
 *     RWReadersWriterLock  rdwrLock_;
 *
 * public:
 *
 *     Ratio(double x, double y) : x_(x), y_(y) { }
 *
 *     // The read locks in ratio() and getXandY()
 *     // ensure that x_ and y_ can be accessed without
 *     // worrying that the object is in a state where
 *     // one has been modified without the other.
 *     // However, because they are read locks, there is
 *     // no limit to the number of threads that can
 *     // be running in either of these two member functions
 *     // simultaneously.  Thus there is no unnecessary
 *     // blocking when multiple threads wish only to read
 *     // the data without modifying it.
 *
 *     double ratio() {
 *         ReadGuard readlock(rdwrLock_);
 *         return (double)x_ / (double)y_;
 *     }
 *
 *     void getXandY(double& x, double& y) {
 *         ReadGuard readlock(rdwrLock_);
 *         x = x_;
 *         y = y_;
 *     }
 *
 *     // The write locks in setX() and setY() ensure that
 *     // x_ and y_ are updated atomically so that the integrity
 *     // of the ratio is always maintained.  These methods
 *     // obtain exclusive access to rdwrLock. All other
 *     // threads will block upon trying to enter any of the
 *     // four methods shown for this class.
 *
 *     void setX(int i) {
 *         WriteGuard writelock(rdwrLock_);
 *         double r = x_ / y_;
 *         x_ = i;
 *         y_ = x_ / r;
 *     }
 *
 *     void setY(int i) {
 *         WriteGuard writelock(rdwrLock_);
 *         double r = x_ / y_;
 *         y_ = i;
 *         x_ = y_ * r;
 *     }
 * };
 * \endcode
 * \endexample
 *
 * \sa
 * RWTReadLockGuard, RWTTryReadLockGuard, RWTReadUnlockGuard,
 * RWTWriteLockGuard, RWTTryWriteLockGuard, RWTWriteUnlockGuard
 */
class RW_SYNC_SYMBOLIC RWReadersWriterLock
    : public RWSynchObject
{
private:

#if !defined(RW_MULTI_THREAD)

    RWMutexLock lock_;

#elif !defined(RW_SYNC_NO_PTHREAD_RWLOCK)

    pthread_rwlock_t lock_;

#else // RW_SYNC_NO_PTHREAD_RWLOCK

    RWMutexLock lock_;
    RWCondition readers_;
    RWCondition writers_;

    int numReaders_;
    int numWriters_;
    int count_;

#  if defined(RW_SYNC_DEBUG)
    RWTValSlist<RWThreadId> threadIds_;
#  endif // RW_SYNC_DEBUG 

#endif // RW_SYNC_NO_PTHREAD_RWLOCK 

public:


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWReadersWriterLock>         LockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTReadLockGuard<RWReadersWriterLock>     ReadLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTWriteLockGuard<RWReadersWriterLock>    WriteLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryLockGuard<RWReadersWriterLock>      TryLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryReadLockGuard<RWReadersWriterLock>  TryReadLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryWriteLockGuard<RWReadersWriterLock> TryWriteLockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWReadersWriterLock>       UnlockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTReadUnlockGuard<RWReadersWriterLock>   ReadUnlockGuard;


    /**
     * Predefined type for compatible guard.
     */
    typedef RWTWriteUnlockGuard<RWReadersWriterLock>  WriteUnlockGuard;


    /**
     * Creates and initializes an RWReadersWriterLock. The thread
     * cancellation state of the object is initialized to \a state. Can
     * throw RWTHRInternalError.
     */
    RWReadersWriterLock(RWCancellationState state = RW_CANCELLATION_DISABLED);


    /**
     * Recovers any system resources used to implement the
     * RWReadersWriterLock. Can throw RWTHRInternalError.
     */
    ~RWReadersWriterLock();


    // Provide compatibility with simple mutex locks
    /**
     * Calls acquireWrite(). Provided for compatibility with simple mutex
     * locks. Possible exceptions include RWCancellation and
     * RWTHRInternalError.
     */
    void
    acquire();


    /**
     * Acquires the lock as a reader. If there are writers waiting for the
     * lock, the calling thread blocks until all readers currently in the
     * protected code exit and until all waiting writers have acquired and
     * left the protected code. At that time, the thread is given access to
     * the protected code concurrently with other readers waiting on the
     * lock.
     *
     * This function throws an RWCancellation object if the lock has
     * cancellation detection enabled and a runnable containing the calling
     * thread has been canceled. Other possible exceptions include
     * RWTHRInternalError.
     *
     * This method returns immediately on success for single-threaded
     * builds. A debug assertion occurs or an RWTHRInternalError is thrown
     * on failure.
     */
    void
    acquireRead();


    /**
     * Acquires the lock as a writer. The calling thread is given priority
     * access to the lock over all readers which have not yet acquired the
     * lock. If readers already have acquired the lock, but have not
     * released it, or another writer owns the lock, the call blocks until
     * the lock is available. This function throws an RWCancellation object
     * if the lock has cancellation detection enabled and a runnable
     * containing the calling thread has been canceled. Other possible
     * exceptions include RWTHRInternalError.
     *
     * This method returns immediately on success for single-threaded
     * builds. A debug assertion occurs or an RWTHRInternalError is thrown
     * on failure.
     */
    void
    acquireWrite();


    // Provide compatibility with simple mutex locks
    /**
     * Returns the result of calling
     * \ref acquireWrite(unsigned long milliseconds) "acquireWrite(milliseconds)".
     * Provided for compatibility with simple mutex locks. Possible
     * exceptions include RWCancellation and RWTHRInternalError.
     */
    RWWaitStatus
    acquire(unsigned long /* ms */);


    /**
     * Attempts to acquire the lock as a reader. If there are writers
     * waiting for the lock, the calling thread blocks until all readers
     * currently in the protected code exit and until all waiting writers
     * have acquired and left the protected code. At that time, the thread
     * is given access to the protected code concurrently with other readers
     * waiting on the lock.
     *
     * If the lock cannot be acquired within the time specified, the
     * function returns #RW_THR_TIMEOUT.
     *
     * This function throws an RWCancellation object if the lock has
     * cancellation detection enabled and a runnable containing the calling
     * thread has been canceled. Other possible exceptions include
     * RWTHRInternalError.
     *
     * This method returns immediately in single-threaded builds.
     */
    RWWaitStatus
    acquireRead(unsigned long /* ms */);


    /**
     * Attempts to acquire the lock as a writer. The calling thread isgiven
     * priority access to the lock over all readers which have not yet
     * acquired the lock. If readers already have acquired the lock, but
     * have not released it, or another writer owns the lock, the call
     * blocks until the lock is available. If the lock cannot be acquired
     * within the time specified, the function returns #RW_THR_TIMEOUT.
     *
     * This function throws an RWCancellation object if the lock has
     * cancellation detection enabled and a runnable containing the calling
     * thread has been canceled. Other possible exceptions include
     * RWTHRInternalError.
     *
     * This method returns immediately in single-threaded builds.
     */
    RWWaitStatus
    acquireWrite(unsigned long /* ms */);


    // Provide compatibility with simple mutex locks
    /**
     * Calls tryAcquireWrite(). Provided for compatibility with the
     * interface used by simple mutex locks. Possible exceptions include
     * RWCancellation and RWTHRInternalError.
     */
    bool
    tryAcquire();


    /**
     * Attempts to acquire the lock as a reader. If there are no writers
     * either waiting for or owning the lock, the calling thread acquires
     * the lock, and this function returns \c true. Otherwise, this function
     * returns \c false without acquiring the lock. Possible exceptions
     * include RWCancellation and RWTHRInternalError.
     */
    bool
    tryAcquireRead();


    /**
     * Attempts to acquire the lock as a writer. If no thread currently owns
     * the lock, the calling thread is given ownership of the lock and this
     * function returns \c true. Otherwise, this function returns \c false
     * without acquiring the lock. Possible exceptions include
     * RWCancellation and RWTHRInternalError.
     */
    bool
    tryAcquireWrite();


    /**
     * Releases the lock to one writer waiting to access the protected code.
     * If there are no writers blocked waiting for the lock, all readers
     * blocked on the lock are given concurrent access to the protected
     * code. Possible exceptions include RWTHRInternalError.
     */
    void
    release();

private:


    /**
     * Copy construction prohibited.
     */
    RWReadersWriterLock(const RWReadersWriterLock&);


    /**
     * Assignment prohibited.
     */
    RWReadersWriterLock& operator=(const RWReadersWriterLock&);
};

/*****************************************************************************/

inline void
RWReadersWriterLock::acquire()
{
    acquireWrite();
}

inline RWWaitStatus
RWReadersWriterLock::acquire(unsigned long milliseconds)
{
    return acquireWrite(milliseconds);
}

inline bool
RWReadersWriterLock::tryAcquire()
{
    return tryAcquireWrite();
}

#if defined(_MSC_VER)
#  pragma warning (pop)
#endif

#endif // __rw_sync_RWReadersWriterLock_h__ 
