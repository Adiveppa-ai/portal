#ifndef __rw_sync_RWTWriteLockGuard_h__
#define __rw_sync_RWTWriteLockGuard_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTWriteLockGuard.h#1 $
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
#  define RWWriteLockGuard RWTWriteLockGuard
#endif

#include <rw/sync/RWTWriteLockGuardBase.h>
#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * A guard class that acquires write access to its resource upon creation
 * and releases it upon destruction.
 *
 * RWTWriteLockGuard is a guard class that acquires write access on its
 * resource upon creation and releases it upon destruction. Guard objects
 * work in conjunction with block statements to establish an appropriate
 * state upon creation, maintain that state for the duration of the block,
 * and restore the original state upon destruction. For example, a guard may
 * acquire write access on a mutex when created and release it when
 * destructed.
 *
 * The class used as the actual template parameter for \c Resource must
 * provide \c %acquireWrite() and \c %release() methods, such as the
 * synchronization classes in this module.
 *
 * \example
 * \code
 * #include <rw/sync/RWReadersWriterLock.h>
 * #include <rw/sync/RWTWriteLockGuard.h>
 *
 * // ...
 * RWReadersWriterLock rwlock;
 *
 * void foo()
 * {
 *     // acquire write access:
 *     RWTWriteLockGuard<RWReadersWriterLock> lock(rwlock);
 *
 *     // ... critical section
 *
 *     // lock will be released in RWTWriteLockGuard destructor
 *     // before leaving scope, especially important if an exception
 *     // might be thrown!
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWTTryWriteLockGuard, RWTWriteUnlockGuard
 */
template <class Resource>
class RWTWriteLockGuard : public RWTWriteLockGuardBase<Resource>
{

public:

    /**
     * \internal
     * A typedef for the template parameter.
     */
    typedef Resource ResourceType;

public:


    /**
     * Destructor.
     */
    ~RWTWriteLockGuard();


    /**
     * Constructs an instance with the given \a resource and acquires write
     * access on that resource. The resource is released in the destructor
     * of the base class.
     */
    RWTWriteLockGuard(Resource& resource);

private:


    /**
     * Copy constructor prohibited.
     */
    RWTWriteLockGuard(const RWTWriteLockGuard<Resource>& second);

    /**
     * Assignment prohibited.
     */
    RWTWriteLockGuard<Resource>&
    operator=(const RWTWriteLockGuard<Resource>& second);

};

/*****************************************************************************/

template <class Resource>
inline
RWTWriteLockGuard<Resource>::RWTWriteLockGuard(Resource& res)
    : RWTWriteLockGuardBase<Resource>(res, false)
{
    this->acquire();
}

template <class Resource>
inline
RWTWriteLockGuard<Resource>::~RWTWriteLockGuard()
{
}

#endif // __rw_sync_RWTWriteLockGuard_h__
