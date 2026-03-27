#ifndef __rw_sync_RWTUnlockGuard_h__
#define __rw_sync_RWTUnlockGuard_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTUnlockGuard.h#1 $
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
#  define RWUnlockGuard RWTUnlockGuard
#endif

#include <rw/sync/RWTGuardBase.h>
#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Guard class that releases its resource upon creation and acquires it upon
 * destruction.
 *
 * RWTUnlockGuard is a guard class that releases its resource upon creation
 * and acquires it upon destruction. Guard objects work in conjunction with
 * block statements to establish an appropriate state upon creation,
 * maintain that state for the duration of the block, and restore the
 * original state upon destruction. For example, a guard may release a mutex
 * when created and reacquire it when destructed. The class used as the
 * actual template parameter for \c Resource must be one that provides
 * \c %acquire() and \c %release() methods, such as the synchronization
 * classes provided in this module.
 *
 * \example
 * \code
 * #include <rw/sync/RWMutexLock.h>
 * #include <rw/sync/RWTUnlockGuard.h>
 *
 * // ...
 * RWMutexLock mutex;
 *
 * void foo()
 * {
 *    mutex.acquire();
 *
 *    // ... critical code
 *
 *    // temporarily release mutex for the duration of block:
 *    {
 *       RWTUnlockGuard<RWMutexLock> lock(mutex); // releases mutex
 *
 *       // ... anti-critical section
 *
 *       // Mutex will be reacquired in RWTUnlockGuard destructor.
 *    }
 *
 *    // ... more critical code
 *
 *    mutex.release();
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWTLockGuard
 */
template <class Resource>
class RWTUnlockGuard : public RWTGuardBase<Resource>
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
    RWTUnlockGuard(Resource& resource);


    /**
     * Reacquires the resource.
     */
    ~RWTUnlockGuard();

private:


    /**
     * Copy construction prohibited.
     */
    RWTUnlockGuard(const RWTUnlockGuard<Resource>& second);

    /**
     * Assignment prohibited.
     */
    RWTUnlockGuard<Resource>&
    operator=(const RWTUnlockGuard<Resource>& second);

};

/*****************************************************************************/

template <class Resource>
inline
RWTUnlockGuard<Resource>::RWTUnlockGuard(Resource& res)
    : RWTGuardBase<Resource>(res, true)
{
    this->release();
}

template <class Resource>
inline
RWTUnlockGuard<Resource>::~RWTUnlockGuard()
{
    this->acquire();
}

#endif // __rw_sync_RWTUnlockGuard_h__
