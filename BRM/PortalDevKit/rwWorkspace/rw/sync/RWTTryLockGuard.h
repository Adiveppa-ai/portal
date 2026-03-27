#ifndef __rw_sync_RWTTryLockGuard_h__
#define __rw_sync_RWTTryLockGuard_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTTryLockGuard.h#1 $
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
#  define RWTryLockGuard RWTTryLockGuard
#endif

#include <rw/sync/RWTLockGuardBase.h>
#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Guard class that tries to acquire its resource upon creation and release
 * it upon destruction.
 *
 * RWTTryLockGuard is a guard class that tries to acquire its resource upon
 * creation and, if successful, release it upon destruction. Guard objects
 * work in conjunction with block statements to establish an appropriate
 * state upon creation, maintain that state for the duration of the block,
 * and restore the original state upon destruction. For example, a guard may
 * acquire a mutex when created and release it when destructed. The class
 * used as the actual template parameter for \c Resource must be one that
 * provides \c %tryAcquire() and \c %release() methods, such as some
 * synchronization classes provided in this module.
 *
 * \example
 * \code
 * #include <rw/sync/RWMutexLock.h>
 * #include <rw/sync/RWTTryLockGuard.h>
 *
 * RWMutexLock mutex;
 *
 * bool foo()
 * {
 *     // ...
 *     {
 *         // try to acquire mutex:
 *         RWTTryLockGuard<RWMutexLock> lock(mutex);
 *
 *         // See if the mutex was acquired:
 *         if (!lock.isAcquired()) {
 *             return false;     // Can't get lock,
 *             // give up and return error
 *         }
 *         // ... critical section
 *
 *         // Mutex will be released in RWTTryLockGuard destructor
 *         // before leaving scope, especially important
 *         // if an exception might be thrown!
 *     }
 *
 *     // ...
 *     return true;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWTLockGuard, RWTUnlockGuard
 */
template <class Resource>
class RWTTryLockGuard: public RWTLockGuardBase<Resource>
{

public:

    /**
     * \internal
     * A typedef for the template parameter.
     */
    typedef Resource   ResourceType;

public:


    /**
     * Constructs an instance with the given \a resource and attempts to
     * acquire that resource. Use the inherited isAcquired() member function
     * to see if the acquisition was successful.
     */
    RWTTryLockGuard(Resource& resource);


    /**
     * Destructor.
     */
    ~RWTTryLockGuard();


    /**
     * Tries again to acquire the resource. Use this function instead of
     * manipulating the resource directly so the guard will automatically
     * release it.
     */
    bool
    tryAcquire();

private:


    /**
     * Copy construction prohibited.
     */
    RWTTryLockGuard(const RWTTryLockGuard<Resource>& second);


    /**
     * Assignment prohibited.
     */
    RWTTryLockGuard<Resource>&
    operator=(const RWTTryLockGuard<Resource>& second);

};

/*****************************************************************************/

template <class Resource>
inline
RWTTryLockGuard<Resource>::RWTTryLockGuard(Resource& res)
    : RWTLockGuardBase<Resource>(res, false)
{
    tryAcquire();
}

template <class Resource>
inline
RWTTryLockGuard<Resource>::~RWTTryLockGuard()
{
}


template <class Resource>
inline bool
RWTTryLockGuard<Resource>::tryAcquire()
{
    if (!this->acquired_) {
        this->acquired_ = this->resource_.tryAcquire();
    }
    return this->acquired_;
}

#endif // __rw_sync_RWTTryLockGuard_h__
