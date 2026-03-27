#ifndef __rw_sync_RWCriticalSection_h__
#define __rw_sync_RWCriticalSection_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWCriticalSection.h#1 $
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
#include <rw/sync/pkgdefs.h>

#if !defined(RW_MULTI_THREAD) || defined(RW_THR_THREAD_API_POSIX) || defined(RW_THR_THREAD_API_SOLARIS)

#  include <rw/sync/RWMutexLock.h>
/**
 * \relates RWCriticalSection
 *
 * Typedef for the internal critical section.
 *
 * \conditional
 * This type is used for build configurations based on POSIX or Solaris
 * threads.
 */
typedef RWMutexLock RWCriticalSectionRep;
#endif

#if defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32) || defined(DOXYGEN)

#  include <rw/sync/RWTLockGuard.h>
#  include <rw/sync/RWTUnlockGuard.h>
#  include <rw/mutex.h>

/**
 * \relates RWCriticalSection
 *
 * Typedef for the internal critical section.
 *
 * \conditional
 * This type is used for build configurations based on Win32 threads.
 */
typedef RW_MUTEX_T RWCriticalSectionRep;

#endif

/*************************************************************************/

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Provides mutual exclusion for a critical section of code in which only
 * one thread should execute at a time.
 *
 * An RWCriticalSection object is used to provide mutual exclusion for a
 * critical section of code, i.e. code in which only one thread should
 * execute at a time. This lock operates in a manner that is identical to
 * RWMutexLock except that on certain platforms, for example Win32, it may
 * yield superior performance when there is minimal contention for the lock.
 *
 * \example
 * \code
 * #include <rw/sync/RWCriticalSection.h>
 *
 * void foo()
 * {
 *     static RWCriticalSection outputCritsec(RW_STATIC_CTOR);
 *
 *     // ...
 *
 *     int i;
 *
 *     // ...
 *
 *     // Protect output from multiple threads
 *     // using cout at the same time:
 *     outputCritsec.acquire();
 *     std::cout << "The value of i is " << i << std::endl;
 *     outputCritsec.release();
 *
 *     // Same thing, this time using a guard:
 *     {
 *         RWCriticalSection::LockGuard lock(outputCritsec);
 *         std::cout << "The value of i is " << i << std::endl;
 *     }
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWMutexLock
 */
class RW_SYNC_SYMBOLIC RWCriticalSection : public RWSynchObject
{
protected:

#if defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32)
    volatile RWTAtomic<unsigned char> init_;
#endif

    RWCriticalSectionRep lock_;

public:

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWCriticalSection>     LockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWCriticalSection>     ReadLockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard<RWCriticalSection>     WriteLockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWCriticalSection>   UnlockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWCriticalSection>   ReadUnlockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard<RWCriticalSection>   WriteUnlockGuard;

    /**
     * Constructs a static instance, but does no direct initialization. The
     * RWCriticalSection is initialized on first use.
     *
     * This constructor must be used only for static instances. Use of this
     * constructor with automatically or dynamically allocated instances
     * produces errors or other unpredictable behavior.
     *
     * Static instances are zero initialized, which results in an
     * RWCriticalSection with cancellation state of
     * #RW_CANCELLATION_DISABLED.
     */
    RWCriticalSection(RWStaticCtor);

    RWCriticalSection(RWNoInitialization);


    /**
     * Creates and initializes the critical section. Possible exceptions
     * include RWTHRInternalError.
     */
    RWCriticalSection(RWCancellationState state = RW_CANCELLATION_DISABLED);


    /**
     * Default destructor.
     */
    ~RWCriticalSection();


    /**
     * Provides access to the underlying platform-specific critical section
     * implementation.
     */
    RWCriticalSectionRep*
    getCriticalSectionRep() const;


    /**
     * Blocks until the critical section is available. Possible exceptions
     * include RWCancellation and RWTHRInternalError.
     *
     * In single-threaded builds, this method returns immediately. If the
     * section is unavailable, a debug assertion will occur, or an
     * RWTHRInternalError will be thrown.
     */
    void
    acquire();


    /**
     * Releases the critical section. Possible exceptions include
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

private:

    /**
     * Copy construction prohibited.
     */
    RWCriticalSection(const RWCriticalSection&);


    /**
     * Assignment prohibited.
     */
    RWCriticalSection&
    operator=(const RWCriticalSection&);

    void
    init();

};

/*****************************************************************************/

// Constructor for use by global static instances. Does not explicitly
// initialize, hence object may be used before constructed. Global
// instances are zero initialized, which will result in an
// RWCriticalSection with cancellation state of #RW_CANCELLATION_DISABLED.
inline
RWCriticalSection::RWCriticalSection(RWStaticCtor)
    : RWSynchObject(RW_STATIC_CTOR)
#if !defined(RW_THR_THREAD_API_WIN32)
    , lock_(RW_STATIC_CTOR)
#endif // !RW_THR_THREAD_API_WIN32
{
}

inline
RWCriticalSection::RWCriticalSection(RWNoInitialization)
#if defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32)
    : init_()
#endif // RW_MULTI_THREAD && RW_THR_THREAD_API_WIN32
{
}

inline void
RWCriticalSection::init()
{
#if defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32)

    unsigned char expected = 0;
    if (init_.load(rw_mem_order_acquire) != 2) {
        // If init_ has not been previously set, set it and invoke
        // the users function.
        if (init_.compareAndSwap(expected, 1)) {
            InitializeCriticalSection(reinterpret_cast<_RTL_CRITICAL_SECTION*>(&lock_));
            // Indicate initialization is complete.
            init_.store(2, rw_mem_order_release);
        }
        // Check if the updated value indicates initialization has
        // already completed.
        else if (expected == 2) {
            // do nothing.
        }
        // Otherwise wait for initialization to complete.
        else {
            while (init_.load(rw_mem_order_acquire) != 2) {}
        }
    }

#endif
}

inline
RWCriticalSection::RWCriticalSection(RWCancellationState state)
    :
#if defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32)
    init_(),
#endif // RW_MULTI_THREAD && RW_THR_THREAD_API_WIN32
    RWSynchObject(state)
{
    init();
}

inline
RWCriticalSection::~RWCriticalSection()
{
#if defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32)
    // Test for initialization
    if (0 == init_) {
        return;
    }

    DeleteCriticalSection(reinterpret_cast<_RTL_CRITICAL_SECTION*>(&lock_));

    // Atomically set init_ to 0
    init_ = 0;
#endif
}

inline void
RWCriticalSection::acquire()
{
    testCancellation();

    init();

#if defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32)
    EnterCriticalSection(reinterpret_cast<_RTL_CRITICAL_SECTION*>(&lock_));
#else
    lock_.acquire();
#endif
}

inline void
RWCriticalSection::release()
{
#if defined(RW_MULTI_THREAD) && defined(RW_THR_THREAD_API_WIN32)
    RW_ASSERT(init_);
    LeaveCriticalSection(reinterpret_cast<_RTL_CRITICAL_SECTION*>(&lock_));
#else
    lock_.release();
#endif
}

inline RWCriticalSectionRep*
RWCriticalSection::getCriticalSectionRep() const
{
    return const_cast<RWCriticalSectionRep*>(&RW_EXPOSE(lock_));
}

inline void
RWCriticalSection::acquireRead()
{
    acquire();
}

inline void
RWCriticalSection::acquireWrite()
{
    acquire();
}

/*****************************************************************************/

#endif // __rw_sync_RWCriticalSection_h__
