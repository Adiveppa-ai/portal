#ifndef __rw_sync_RWTReadLockGuardBase_h__
#define __rw_sync_RWTReadLockGuardBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTReadLockGuardBase.h#1 $
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
#  define RWReadLockGuardBase RWTReadLockGuardBase
#endif

#include <rw/sync/RWTReadGuardBase.h>
#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Base class for guard classes that acquire read access to a resource upon
 * creation and release it upon destruction.
 *
 * RWTReadLockGuardBase is a base class for guard classes that acquire read
 * access on a resource upon creation and release it upon destruction. Guard
 * objects work in conjunction with block statements to establish an
 * appropriate state upon creation, maintain that state for the duration of
 * the block, and restore the original state upon destruction. For example,
 * a guard may acquire read access on a mutex upon creation and release it
 * when destructed. The class used as the template parameter \c Resource
 * must be one that provides \b %acquireRead() and \b %release() methods,
 * such as the synchronization classes provided in this module.
 *
 * \sa
 * RWTReadLockGuard, RWTTryReadLockGuard, RWTReadUnlockGuard
 */
template <class Resource>
class RWTReadLockGuardBase : public RWTReadGuardBase<Resource>
{

public:

    /**
     * \internal
     * A typedef for the template parameter.
     */
    typedef Resource ResourceType;

public:


    /**
     * Releases the resource if it has been acquired.
     */
    ~RWTReadLockGuardBase();

protected:

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 13, use RWTReadLockGuardBase(Resource&, bool)
     * instead.
     *
     * Constructs a guard instance with the given resource. Note that this
     * constructor does \b not attempt to acquire the resource. That is the
     * responsibility of the derived class.
     */
    RWTReadLockGuardBase(Resource& resource);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif


    /**
     * Constructs a guard instance with the given resource. If \a acquired
     * is \c true, the resource is assumed to be owned by the caller. Note
     * that this constructor does \b not attempt to acquire the resource.
     * That is the responsibility of the derived class.
     */
    RWTReadLockGuardBase(Resource& resource, bool acquired);


private:

    /**
     * Copy construction prohibited.
     */
    RWTReadLockGuardBase(const RWTReadLockGuardBase<Resource>& second);

    /**
     * Assignment prohibited.
     */
    RWTReadLockGuardBase<Resource>&
    operator=(const RWTReadLockGuardBase<Resource>& second);

};

/*****************************************************************************/

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

template <class Resource>
inline
RWTReadLockGuardBase<Resource>::RWTReadLockGuardBase(Resource& ref)
    : RWTReadGuardBase<Resource>(ref)
{
    // Don't do anything here - RWTReadLockGuard and RWTTryReadLockGuard
    // constructors will do the right thing...
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif

template <class Resource>
inline
RWTReadLockGuardBase<Resource>::RWTReadLockGuardBase(Resource& ref, bool acquired)
    : RWTReadGuardBase<Resource>(ref, acquired)
{
    // Don't do anything here - RWTReadLockGuard and RWTTryReadLockGuard
    // constructors will do the right thing...
}

template <class Resource>
inline
RWTReadLockGuardBase<Resource>::~RWTReadLockGuardBase()
{
    this->release();
}

#endif // __rw_sync_RWTReadLockGuardBase_h__
