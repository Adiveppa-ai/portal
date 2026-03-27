#ifndef __rw_sync_RWTMonitor_h__
#define __rw_sync_RWTMonitor_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTMonitor.h#1 $
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

#include <rw/sync/fwd.h>
#include <rw/sync/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWMonitor RWTMonitor
#endif

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Supplies the mutual exclusion and guard mechanisms for synchronizing
 * member functions.
 *
 * Subclassing from RWTMonitor provides a convenient way to synchronize the
 * member functions used to access the data or resources encapsulated by a
 * class. RWTMonitor supplies the mutual exclusion and guard mechanisms for
 * synchronizing member functions. Functions that need to be synchronized
 * use the supplied guard type to lock the monitor upon entry and unlock it
 * upon exit from the function.
 *
 * This class provides an alternative to directly inheriting from or
 * including a synchronization class to achieve the same purpose. If you use
 * your own mutex for synchronization, you must cast away the
 * <tt>const</tt>-ness of \c this in \c const member functions before
 * acquiring or releasing the mutex.
 *
 * By using this class, you have access to the monitor() function,
 * eliminates the above inconvenience by always returning a non-\c const
 * instance of the monitor. The reference returned by monitor() can be used
 * to initialize any of the public guard types defined by the RWTMonitor
 * class.
 *
 * \example
 * \code
 * #include <rw/sync/RWTMonitor.h>
 * #include <rw/sync/RWMutexLock.h>
 *
 * class MyClass : public RWTMonitor<RWMutexLock>
 * {
 * public:
 *     void myFunc1(void);         // Synchronized Function
 *     // (Non-atomic)
 *     void myFunc2(void) const;   // Synchronized Function
 *     // (Atomic)
 * private:
 *     void helper(void) const;    // Assumes lock is already
 *     // acquired!
 * };
 *
 * void MyClass::myFunc1(void)
 * {
 *     // Use a guard to lock the monitor (and automatically unlock it)
 *
 *     LockGuard lock(monitor());
 *
 *     // Do something useful...
 *
 *     {
 *         // Temporarily unlock the monitor so you can call another
 *         // synchronized function
 *
 *         UnlockGuard unlock(monitor());
 *
 *         // Call another synchronized function
 *
 *         myFunc2();
 *
 *         // Monitor automatically re-locked upon exit from block
 *     }
 *
 *     // Do some more stuff
 * }
 *
 * void MyClass::myFunc2(void) const
 * {
 *     // Use a guard to lock the monitor (and automatically unlock it)
 *
 *     LockGuard lock(monitor());
 *
 *     // Call a private helper function
 *
 *     helper();
 * }
 *
 * void MyClass::helper(void) const
 * {
 *     // Debug Mode - Make sure the monitor is acquired by this thread!
 *
 *     RW_ASSERT(monitor().isAcquired());
 *
 *     // Do something useful...
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWMutexLock, RWTLockGuard, RWTUnlockGuard, RWTTryLockGuard
 */
template <class Mutex>
class RWTMonitor
{
public:

    typedef Mutex  MutexType;

protected:

    Mutex          mutex_;

protected:


    /**
     * Constructs a default monitor instance, initializing the mutex.
     */
    RWTMonitor();


    /**
     * Constructs a static monitor instance. This constructor <em>does
     * not</em> initialize the mutex; rather, the mutex is initialized the
     * first time it is accessed.
     */
    RWTMonitor(RWStaticCtor);

    // Construct an instance that will be initialized on first use
    RWTMonitor(RWNoInitialization);

    /**
     * This copy constructor does not actually copy anything (mutexes
     * generally cannot be copied). It is provided so you can define a copy
     * constructor in your derived class.
     */
    RWTMonitor(const RWTMonitor<Mutex>& second);


    /**
     * Destructor.
     */
    ~RWTMonitor();

    /**
     * This assignment operator does not actually assign anything (mutexes
     * generally cannot be assigned). It is provided so you can define an
     * assignment operator in your derived class.
     */
    RWTMonitor<Mutex>&
    operator=(const RWTMonitor<Mutex>&);


    /**
     * Locks the monitor by acquiring the monitor's mutex.
     */
    void
    acquire();

#if defined(RW_SYNC_DEBUG) || defined(DOXYGEN)


    /**
     * Determines whether the calling thread currently owns the monitor.
     *
     * This function is primarily intended for use in precondition
     * assertions, and is only available when you build the debug version of
     * the module.
     */
    bool
    isAcquired() const;

#endif


    /**
     * Casts away \c const and returns a reference to self. This allows you
     * to avoid explicitly casting away \c const on the \c this pointer in
     * every \c const member function that needs to lock the monitor.
     */
    RWTMonitor<Mutex>&
    monitor() const;


    /**
     * Returns the monitor's mutex.
     */
    Mutex&
    mutex();


    /**
     * Unlocks the monitor by releasing the monitor's mutex.
     */
    void
    release();


    /**
     * Conditionally locks the monitor if the monitor can be locked without
     * blocking.
     */
    bool
    tryAcquire();

#if defined(RW_NO_SELF_REFERENCING_FRIEND_DECLARATIONS) || defined(DOXYGEN)
    // Predefine guards for use with monitors.


    /**
     * Predefined guard for use with the monitor.
     */
    typedef RWTLockGuard< RWTMonitor< Mutex > >     LockGuard;


    /**
     * Predefined unlock guard for use with the monitor.
     */
    typedef RWTUnlockGuard< RWTMonitor< Mutex > >   UnlockGuard;


    /**
     * Predefined try lock guard for use with the monitor.
     */
    typedef RWTTryLockGuard< RWTMonitor< Mutex > >  TryLockGuard;

private:
    // Additional typedefs required for friend declarations
    typedef RWTGuardBase< RWTMonitor< Mutex > >     GuardBase;
    typedef RWTLockGuardBase< RWTMonitor< Mutex > > LockGuardBase;

    // Give the guard classes access to the acquire and release members.
    friend class GuardBase;
    friend class LockGuardBase;
    friend class LockGuard;
    friend class UnlockGuard;
    friend class TryLockGuard;
#else
    // Give the guard classes access to the acquire and release members.
    friend class RWTGuardBase< RWTMonitor< Mutex > >;
    friend class RWTLockGuardBase< RWTMonitor< Mutex > >;
    friend class RWTLockGuard< RWTMonitor< Mutex > >;
    friend class RWTTryLockGuard< RWTMonitor< Mutex > >;
    friend class RWTUnlockGuard< RWTMonitor< Mutex > >;

    // Predefine guards for use with monitors.
    typedef RWTLockGuard< RWTMonitor< Mutex > >     LockGuard;
    typedef RWTUnlockGuard< RWTMonitor< Mutex > >   UnlockGuard;
    typedef RWTTryLockGuard< RWTMonitor< Mutex > >  TryLockGuard;
#endif

};

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
RWTMonitor<Mutex>::RWTMonitor()
{
}

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
RWTMonitor<Mutex>::RWTMonitor(RWStaticCtor)
    : mutex_(RW_STATIC_CTOR)
{
}

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
RWTMonitor<Mutex>::RWTMonitor(RWNoInitialization)
    : mutex_(RW_NO_INIT)
{
}

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
RWTMonitor<Mutex>::RWTMonitor(const RWTMonitor<Mutex>&)
{
    // Don't copy anything
}

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
RWTMonitor<Mutex>::~RWTMonitor()
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
RWTMonitor<Mutex>&
RWTMonitor<Mutex>::operator=(const RWTMonitor<Mutex>&)
{
    // Don't assign anything
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
void
RWTMonitor<Mutex>::acquire()
{
    mutex_.acquire();
}

#if defined(RW_SYNC_DEBUG)

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
bool
RWTMonitor<Mutex>::isAcquired() const
{
    return mutex_.isAcquired();
}

#endif

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
RWTMonitor<Mutex>&
RWTMonitor<Mutex>::monitor() const
{
    return *const_cast< RWTMonitor< Mutex >* >(this);
}

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
Mutex&
RWTMonitor<Mutex>::mutex()
{
    return mutex_;
}

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
void
RWTMonitor<Mutex>::release()
{
    mutex_.release();
}

template <class Mutex>
RW_SYNC_INLINE_SPECIALIZED_MEMBER
bool
RWTMonitor<Mutex>::tryAcquire()
{
    return mutex_.tryAcquire();
}

/*****************************************************************************/

// Template instantiation magic
#include <rw/sync/instance.h>


#endif // __rw_sync_RWTMonitor_h__
