#ifndef __rw_sync_RWTGuardBase_h__
#define __rw_sync_RWTGuardBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTGuardBase.h#1 $
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
#  define RWGuardBase RWTGuardBase
#endif

#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Base class for guard classes.
 *
 * RWTGuardBase is intended as a base class for guard classes. Guard objects
 * work in conjunction with block statements to establish an appropriate
 * state upon creation, maintain that state for the duration of the block,
 * and restore the original state upon destruction. For example, a guard may
 * acquire a mutex when created and release it when destructed. The class
 * used as the actual template parameter for \c Resource must be one that
 * provides \c %acquire() and \c %release() methods, such as the
 * synchronization classes in this module.
 *
 * \sa
 * RWTLockGuardBase, RWTLockGuard, RWTTryLockGuard, RWTUnlockGuard
 */
template <class Resource>
class RWTGuardBase
{

public:

    /**
     * \internal
     * A typedef for the template parameter.
     */
    typedef Resource ResourceType;

protected:

    Resource& resource_;
    bool acquired_;

public:


    /**
     * Destructor.
     */
    ~RWTGuardBase();


    /**
     * Acquires the resource held by the guard unless it has already been
     * acquired. Use this function instead of directly manipulating the
     * resource so that the guard will automatically release or acquire it
     * (as appropriate).
     */
    void
    acquire();


    /**
     * Returns \c true if the resource is currently acquired, otherwise
     * \c false.
     */
    bool
    isAcquired() const;


    /**
     * Releases the resource held by the guard if it has been acquired. Use
     * this function instead of directly manipulating the resource so that
     * the guard will automatically release or acquire it (as appropriate).
     */
    void
    release();

protected:

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 13, use RWTGuardBase(Resource&, bool) instead.
     *
     * Constructs an instance with the given \a resource.
     */
    RWTGuardBase(Resource& resource);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif


    /**
     * Constructs an instance with the given \a resource. If \a acquired is
     * \c true, the resource is assumed to be owned by the caller.
     */
    RWTGuardBase(Resource& resource, bool acquired);


    /**
     * Returns a reference to the resource currently held by the guard.
     */
    Resource&
    resource() const;

private:


    /**
     * Dummy copy constructor, required by derived class copy constructors.
     * The copy constructor does not attempt to copy the resource.
     */
    RWTGuardBase(const RWTGuardBase<Resource>& second);


    /**
     * Assignment prohibited.
     */
    RWTGuardBase& operator=(const RWTGuardBase<Resource>& second);

};


/*****************************************************************************/

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

template <class Resource>
inline
RWTGuardBase<Resource>::RWTGuardBase(Resource& ref)
    : resource_(ref)
{
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif

template <class Resource>
inline
RWTGuardBase<Resource>::RWTGuardBase(Resource& ref, bool acquired)
    : resource_(ref), acquired_(acquired)
{
}

template <class Resource>
inline
RWTGuardBase<Resource>::~RWTGuardBase()
{
}

template <class Resource>
inline void
RWTGuardBase<Resource>::acquire()
{
    if (!acquired_) {
        resource_.acquire();
        acquired_ = true;
    }
}

template <class Resource>
inline bool
RWTGuardBase<Resource>::isAcquired() const
{
    return acquired_;
}

template <class Resource>
inline void
RWTGuardBase<Resource>::release()
{
    if (acquired_) {
        resource_.release();
        acquired_ = false;
    }
}

template <class Resource>
inline Resource&
RWTGuardBase<Resource>::resource() const
{
    return (Resource&)resource_;
}

#endif // __rw_sync_RWTGuardBase_h__
