#ifndef __rw_sync_RWTTryWriteLockGuard_h__
#define __rw_sync_RWTTryWriteLockGuard_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTTryWriteLockGuard.h#1 $
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
#  define RWTryWriteLockGuard RWTTryWriteLockGuard
#endif

#include <rw/sync/RWTWriteLockGuardBase.h>
#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Guard class that tries to acquire write access on its resource upon
 * creation and release it upon destruction.
 *
 * RWTTryWriteLockGuard is a guard class that tries to acquire write access
 * on its resource upon creation and, if successful, release it upon
 * destruction. Guard objects work in conjunction with block statements to
 * establish an appropriate state upon creation, maintain that state for the
 * duration of the block, and restore the original state upon destruction.
 * For example, a guard may acquire write access on a mutex when created and
 * release it when destructed. The class used as the actual template
 * parameter for \c Resource must be one that provides \c %tryAcquireWrite()
 * and \c %release() methods, such as some synchronization classes provided
 * in this module.
 *
 * \example
 * \code
 * #include <rw/sync/RWReadersWriterLock.h>
 * #include <rw/sync/RWTTryWriteLockGuard.h>
 *
 * RWReadersWriterLock rwlock;
 *
 * bool foo()
 * {
 *   // ...
 *   {
 *      // try to acquire write access on a readers-writer lock:
 *      RWTTryWriteLockGuard<RWReadersWriterLock> lock(rwlock);
 *
 *      // See if the lock was acquired:
 *      if (!lock.isAcquired()) {
 *        return false;  // Can't get lock, give up and
 *                       // return error
 *      }
 *
 *      // ... critical section
 *
 *      // lock will be released in RWTTryWriteLockGuard destructor
 *      // before leaving scope, especially important if
 *      // an exception might be thrown!
 *   }
 *
 *   // ...
 *   return true;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWTWriteLockGuard
 */
template <class Resource>
class RWTTryWriteLockGuard : public RWTWriteLockGuardBase<Resource>
{

public:

    /**
     * \internal
     * A typedef for the template parameter.
     */
    typedef Resource ResourceType;

public:


    /**
     * Constructs an instance with the given \a resource and attempts to
     * acquire write access on that resource. Uses the inherited
     * isAcquired() member function to see if the acquisition was
     * successful.
     */
    RWTTryWriteLockGuard(Resource& resource);


    /**
     * Destructor.
     */
    ~RWTTryWriteLockGuard();


    /**
     * Tries again to acquire write access on the resource. Uses this
     * function instead of manipulating the resource directly so the guard
     * will automatically release it.
     */
    bool
    tryAcquire();

private:


    /**
     * Copy construction prohibited.
     */
    RWTTryWriteLockGuard(const RWTTryWriteLockGuard<Resource>& second);


    /**
     * Assignment prohibited.
     */
    RWTTryWriteLockGuard<Resource>&
    operator=(const RWTTryWriteLockGuard<Resource>& second);

};

/*****************************************************************************/

template <class Resource>
inline
RWTTryWriteLockGuard<Resource>::RWTTryWriteLockGuard(Resource& res)
    : RWTWriteLockGuardBase<Resource>(res, false)
{
    tryAcquire();
}

template <class Resource>
inline
RWTTryWriteLockGuard<Resource>::~RWTTryWriteLockGuard()
{
}

template <class Resource>
inline bool
RWTTryWriteLockGuard<Resource>::tryAcquire()
{
    if (!this->acquired_) {
        this->acquired_ = this->resource_.tryAcquireWrite();
    }
    return this->acquired_;
}

#endif // __rw_sync_RWTTryWriteLockGuard_h__
