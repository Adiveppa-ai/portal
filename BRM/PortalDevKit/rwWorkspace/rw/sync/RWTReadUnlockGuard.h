#ifndef __rw_sync_RWTReadUnlockGuard_h__
#define __rw_sync_RWTReadUnlockGuard_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTReadUnlockGuard.h#1 $
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
#  define RWReadUnlockGuard RWTReadUnlockGuard
#endif

#include <rw/sync/RWTReadGuardBase.h>
#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * A guard class that releases its resource upon creation and acquires read
 * access to its resource upon destruction.
 *
 * RWTReadUnlockGuard is a \e guard class that releases its resource upon
 * creation and acquires read access to its resource upon destruction. Guard
 * objects work in conjunction with block statements. The guard objects
 * establish an appropriate state upon creation, maintain that state for the
 * duration of the block, and restore the original state upon destruction.
 * For example,a guard may release read access on a mutex upon creation and
 * reacquire read access on that mutex when destructed. The class used as
 * the template parameter \c Resource must be one that provides
 * \b %acquireRead() and \b %release() methods, such as the synchronization
 * classes provided in this module.
 *
 * \example
 * \code
 * #include <rw/sync/RWReadersWriterLock.h>
 * #include <rw/sync/RWTReadUnlockGuard.h>
 *
 * // ...
 * RWReadersWriterLock rwlock;
 *
 * void foo()
 * {
 *     rwlock.acquireRead();
 *     // ... critical code
 *
 *     // temporarily release readers-writer lock
 *     // for duration of block:
 *     {
 *         // constructor releases lock:
 *         RWTReadUnlockGuard<RWReadersWriterLock> lock(rwlock);
 *
 *         // ... anti-critical section
 *         // lock will be reacquired for reading in
 *         //   RWTReadUnlockGuard destructor.
 *     }
 *     // ... more critical code
 *     rwlock.release();
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWTReadLockGuard, RWTTryReadLockGuard
 */
template <class Resource>
class RWTReadUnlockGuard : public RWTReadGuardBase<Resource>
{

public:

    /**
     * \internal
     * A typedef for the template parameter.
     */
    typedef Resource ResourceType;

public:


    /**
     * Releases the resource.
     */
    RWTReadUnlockGuard(Resource& resource);


    /**
     * Reacquires read access on the resource.
     */
    ~RWTReadUnlockGuard();

private:


    /**
     * Copy construction prohibited.
     */
    RWTReadUnlockGuard(const RWTReadUnlockGuard<Resource>& second);

    /**
     * Assignment prohibited.
     */
    RWTReadUnlockGuard<Resource>&
    operator=(const RWTReadUnlockGuard<Resource>& second);

};

/*****************************************************************************/

template <class Resource>
inline
RWTReadUnlockGuard<Resource>::RWTReadUnlockGuard(Resource& res)
    : RWTReadGuardBase<Resource>(res, true)
{
    this->release();
}

template <class Resource>
inline
RWTReadUnlockGuard<Resource>::~RWTReadUnlockGuard()
{
    this->acquire();
}

#endif // __rw_sync_RWTReadUnlockGuard_h__
