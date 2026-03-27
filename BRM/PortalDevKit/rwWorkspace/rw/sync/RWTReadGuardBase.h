#ifndef __rw_sync_RWTReadGuardBase_h__
#define __rw_sync_RWTReadGuardBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWTReadGuardBase.h#1 $
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
#  define RWReadGuardBase RWTReadGuardBase
#endif

#include <rw/sync/pkgdefs.h>

/**
 * \ingroup synchronization_package
 *
 * \brief
 * Base class for guard classes that support read access to a given section
 * of code.
 *
 * RWTReadGuardBase is a base class for \e guard classes that support read
 * access to a given section of code.
 *
 * Guard objects work in conjunction with block statements to establish an
 * appropriate state upon creation, maintain that state for the duration of
 * the block, and restore the original state upon destruction. For example,
 * a guard may acquire a mutex for reading upon creation and release it when
 * destructed. The class used as the template parameter \c Resource must be
 * one that provides \b %acquireRead() and \b %release() methods, such as
 * the synchronization classes provided in this module.
 *
 * \sa
 * RWTReadLockGuardBase, RWTReadUnlockGuard
 */
template <class Resource>
class RWTReadGuardBase
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
    ~RWTReadGuardBase();


    /**
     * Acquires read access on the resource held by the guard unless access
     * has already been acquired. Use this function rather than manipulating
     * the resource directly so the guard will automatically release or
     * acquire access (as appropriate).
     */
    void
    acquire();


    /**
     * Returns \c true if the resource is currently acquired.
     */
    bool
    isAcquired() const;


    /**
     * Releases the resource held by the guard if it has been acquired. Use
     * this function rather than manipulating the resource directly so the
     * guard will automatically release or acquire access (as appropriate).
     */
    void
    release();

protected:


#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 13, use RWTReadGuardBase(Resource&, bool) instead.
     *
     * Constructs an instance with the given \a resource.
     */
    RWTReadGuardBase(Resource& resource);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif


    /**
     * Constructs an instance with the given \a resource. If \a acquired is
     * \c true, the resource is assumed to be owned by the caller.
     */
    RWTReadGuardBase(Resource& resource, bool acquired);


    /**
     * Returns a reference to the resource currently held by the guard.
     */
    Resource&
    resource() const;

private:


    /**
     * Copy construction prohibited.
     */
    RWTReadGuardBase(const RWTReadGuardBase<Resource>& second);


    /**
     * Assignment prohibited.
     */
    RWTReadGuardBase<Resource>&
    operator=(const RWTReadGuardBase<Resource>& second);

};

/*****************************************************************************/

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

template <class Resource>
inline
RWTReadGuardBase<Resource>::RWTReadGuardBase(Resource& ref)
    : resource_(ref)
{
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif

template <class Resource>
inline
RWTReadGuardBase<Resource>::RWTReadGuardBase(Resource& ref, bool acquired)
    : resource_(ref), acquired_(acquired)
{
}

template <class Resource>
RWTReadGuardBase<Resource>::~RWTReadGuardBase()
{
}

template <class Resource>
inline void
RWTReadGuardBase<Resource>::acquire()
{
    if (false == acquired_) {
        resource_.acquireRead();
        acquired_ = true;
    }
}

template <class Resource>
inline bool
RWTReadGuardBase<Resource>::isAcquired() const
{
    return acquired_;
}

template <class Resource>
inline void
RWTReadGuardBase<Resource>::release()
{
    if (true == acquired_) {
        resource_.release();
        acquired_ = false;
    }
}

template <class Resource>
inline Resource&
RWTReadGuardBase<Resource>::resource() const
{
    return (Resource&)resource_;
}

#endif // __rw_sync_RWTReadGuardBase_h__
