#ifndef __rw_sync_RWTLockGuard_h__
#define __rw_sync_RWTLockGuard_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTLockGuard.h#1 $
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
#  define RWLockGuard RWTLockGuard
#endif

#include <rw/sync/RWTLockGuardBase.h>
#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * A guard that acquires its resource upon creation and releases it upon
 * destruction.
 *
 * RWTLockGuard is a \e guard class that acquires its resource upon creation
 * and releases it upon destruction. Guard objects work in conjunction with
 * block statements to establish an appropriate state upon creation,
 * maintain that state for the duration of the block, and restore the
 * original state upon destruction. For example, a guard may acquire a mutex
 * upon creation and release it when destructed. The class used as the
 * actual template parameter for \c Resource must be one that provides
 * \c acquire() and \c release() methods, such as provided by the Threads
 * Module synchronization classes.
 *
 * \example
 * \code
 * #include <rw/sync/RWMutexLock.h>
 * #include <rw/sync/RWTLockGuard.h>
 *
 * // ...
 * RWMutexLock mutex;
 *
 * void foo()
 * {
 *     RWTLockGuard<RWMutexLock> lock(mutex);  // acquires mutex
 *
 *     // ... critical section
 *
 *     // Mutex will be released in RWTLockGuard destructor
 *     // before leaving scope, especially important if an exception
 *     // might be thrown!
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWTTryLockGuard, RWTUnlockGuard
 */
template <class Resource>
class RWTLockGuard : public RWTLockGuardBase<Resource>
{

public:

    /**
     * \internal
     * A typedef for the template parameter.
     */
    typedef Resource ResourceType;

public:

    // Acquire the resource
    /**
     * Constructs a guard instance with the given resource and acquires that
     * resource. The resource is released in the destructor of the base
     * class.
     */
    RWTLockGuard(Resource& resource);


    /**
     * Destructor.
     */
    ~RWTLockGuard();

private:

    /**
     * Copy construction prohibited.
     */
    RWTLockGuard(const RWTLockGuard<Resource>& second);


    /**
     * Assignment prohibited.
     */
    RWTLockGuard<Resource>&
    operator=(const RWTLockGuard<Resource>& second);

};

/*****************************************************************************/

template <class Resource>
inline
RWTLockGuard<Resource>::RWTLockGuard(Resource& res)
    : RWTLockGuardBase<Resource>(res, false)
{
    this->acquire();
}

template <class Resource>
inline
RWTLockGuard<Resource>::~RWTLockGuard()
{
}

#endif  // __rw_sync_RWTLockGuard_h__
