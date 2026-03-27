#ifndef __rw_sync_RWTTryReadLockGuard_h__
#define __rw_sync_RWTTryReadLockGuard_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTTryReadLockGuard.h#1 $
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
#  define RWTryReadLockGuard RWTTryReadLockGuard
#endif

#include <rw/sync/RWTReadLockGuardBase.h>
#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Guard class that tries to acquire read access on its resource upon
 * creation and release it upon destruction.
 *
 * RWTTryReadLockGuard is a guard class that tries to acquire read access on
 * its resource upon creation and, if successful, release it upon
 * destruction. Guard objects work in conjunction with block statements to
 * establish an appropriate state upon creation, maintain that state for the
 * duration of the block, and restore the original state upon destruction.
 * For example, a guard may acquire read access on a mutex when created and
 * release it when destructed. The class used as the actual template
 * parameter for \c Resource must be one that provides \c %tryAcquireRead()
 * and \c %release() methods, such as some synchronization classes provided
 * in this module.
 *
 * \example
 * \code
 * #include <rw/sync/RWReadersWriterLock.h>
 * #include <rw/sync/RWTTryReadLockGuard.h>
 *
 * RWReadersWriterLock rwlock;
 *
 * bool foo()
 * {
 *   // ...
 *   {
 *      // try to acquire read access on a readers-writer lock:
 *      RWTTryReadLockGuard<RWReadersWriterLock> lock(rwlock);
 *
 *      // See if the lock was acquired:
 *      if (!lock.isAcquired()) {
 *        return false;  // Can't get lock,
 *                       // give up and return error
 *      }
 *      // ... critical section
 *
 *      // lock will be released in RWTTryReadLockGuard destructor
 *      // before leaving scope, especially important
 *      // if an exception might be thrown!
 *   }
 *
 *   // ...
 *   return true;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWTReadLockGuard
 */
template <class Resource>
class RWTTryReadLockGuard : public RWTReadLockGuardBase<Resource>
{

public:

    /**
     * \internal
     * A typedef for the template parameter.
     */
    typedef  Resource                ResourceType;

public:


    /**
     * Constructs an instance with the given \a resource and attempts to
     * acquire read access on that resource. Uses the inherited isAcquired()
     * member function to see if the acquisition was successful.
     */
    RWTTryReadLockGuard(Resource& resource);


    /**
     * Destructor.
     */
    ~RWTTryReadLockGuard();


    /**
     * Tries again to acquire read access on the resource. Use this function
     * instead of manipulating the resource directly so the guard will
     * automatically release it.
     */
    bool
    tryAcquire();

private:


    /**
     * Copy construction prohibited.
     */
    RWTTryReadLockGuard(const RWTTryReadLockGuard<Resource>& second);

    /**
     * Assignment prohibited.
     */
    RWTTryReadLockGuard<Resource>&
    operator=(const RWTTryReadLockGuard<Resource>& second);

};

/*****************************************************************************/

template <class Resource>
inline
RWTTryReadLockGuard<Resource>::RWTTryReadLockGuard(Resource& res)
    : RWTReadLockGuardBase<Resource>(res, false)
{
    tryAcquire();
}

template <class Resource>
inline
RWTTryReadLockGuard<Resource>::~RWTTryReadLockGuard()
{
}

template <class Resource>
inline bool
RWTTryReadLockGuard<Resource>::tryAcquire()
{
    if (!this->acquired_) {
        this->acquired_ = this->resource_.tryAcquireRead();
    }
    return this->acquired_;
}

#endif // __rw_sync_RWTTryReadLockGuard_h__
