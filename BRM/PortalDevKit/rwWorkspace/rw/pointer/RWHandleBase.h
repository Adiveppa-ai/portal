#ifndef __rw_pointer_RWHandleBase_h__
#define __rw_pointer_RWHandleBase_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWHandleBase.h#1 $
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

#include <rw/pointer/RWBodyBase.h>
#include <rw/pointer/RWTCountedPointer.h>
#include <rw/pointer/pkgdefs.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

#if defined(RW_GCC_VERSION) && (RW_GCC_VERSION >= 40100 && RW_GCC_VERSION < 40200) && \
    !defined(RW_MULTI_THREAD)
#  define RW_RESTRICTED_INLINE __attribute__((noinline))
#else
#  define RW_RESTRICTED_INLINE inline
#endif

/**
 * \ingroup smart_pointer_package
 *
 * \brief
 * Base class for all handle classes. Increments a reference count for each
 * class instance that is bound to an instance of the RWBodyBase class.
 *
 * Base class for handle classes. Each time an instance of this class is
 * bound to an instance of the RWBodyBase class, it increments the reference
 * count maintained by that body. Each time an instance of this class
 * detaches from a body instance, it decrements the body's reference count,
 * until the last handle detaches, reaching zero, whereupon it deletes the
 * body instance. The reference counting relieves clients of the burden of
 * keeping track of when it is safe to delete a body instance.
 *
 * When a handle is copy-constructed, the new handle attaches to the same
 * body as the original. When one handle is assigned to another handle, the
 * handle on the left side detaches from its current body and attaches to
 * the body pointed to by the handle on the right side.
 *
 * \example
 * See \c HandleBodyEx1.cpp and \c HandleBodyEx2.cpp, located in the
 * \c examples directory.
 * \endexample
 */
class RW_POINTER_SYMBOLIC RWHandleBase
{

public:

    /**
     * Returns \c true if the handle points to the same body instance, if
     * any, as pointed to by a second handle \a second, and otherwise
     * returns \c false. Two empty handles are equal. Throws no exceptions.
     */
    bool
    operator==(const RWHandleBase& second) const;

    /**
     * Required for collections based on C++ Standard Library collections.
     * (Redefine this operator in derived classes, as necessary.) Throws no
     * exceptions.
     */
    bool
    operator<(const RWHandleBase& second) const;

    /**
     * Returns \c true if the handle points to different body instance, if
     * any, than pointed to by a second handle \a second, and otherwise
     * returns \c false. Throws no exceptions.
     */
    bool
    operator!=(const RWHandleBase& second) const;

    /**
     * Returns \c true if this handle points to a valid body instance, and
     * \c false otherwise. Throws no exceptions.
     */
    bool
    isValid(void) const;

protected:

    /**
     * Default constructor. Constructs an empty, invalid, handle instance.
     * Throws no exceptions.
     */
    RWHandleBase(void);

    /**
     * Constructs a global static handle instance (may be used prior to
     * construction). Throws no exceptions.
     */
    RWHandleBase(RWStaticCtor);

    /**
     * Binds a new handle instance to a body instance.
     */
    RWHandleBase(RWBodyBase* body);

    /**
     * Binds a new handle instance to the same body instance, if any, that
     * is pointed to by a second handle instance \a second.
     */
    RW_RESTRICTED_INLINE RWHandleBase(const RWHandleBase& second)
        : body_(second.body_)
    {
    }


    //--Destructor -- needed to work around gcc optimization problem
    /**
     * Destructor.
     */
    ~RWHandleBase(void);

    /**
     * Binds this handle instance to the same body instance, if any, that is
     * pointed to by a second handle instance \a second.
     */
    RW_RESTRICTED_INLINE RWHandleBase&
    operator=(const RWHandleBase& second)
    {
        if (&second != this) {
            body_ = second.body_;
        }
        return *this;
    }


    /**
     * Gets a reference for the body instance, if any.
     *
     * \exception RWTHRInvalidPointer
     * Thrown if this handle is not attached to a body.
     */
    RWBodyBase&
    body(void) const;

protected:

    RWTCountedPointer<RWBodyBase>  body_;

};

/****************************************************************************/

inline
RWHandleBase::RWHandleBase(void)
{
}

inline
RWHandleBase::RWHandleBase(RWStaticCtor)
    :
    body_(RW_STATIC_CTOR)
{
}

inline
RWHandleBase::RWHandleBase(RWBodyBase* ptr)
    :
    body_(ptr)
{
}

inline
RWHandleBase::~RWHandleBase(void)
{
}

inline bool
RWHandleBase::operator==(const RWHandleBase& second) const
{
    return body_ == second.body_;
}

inline bool
RWHandleBase::operator<(const RWHandleBase&) const
{
    // Return something (looks like equality)
    return false;
}

inline bool
RWHandleBase::operator!=(const RWHandleBase& second) const
{
    return body_ != second.body_;
}

inline RWBodyBase&
RWHandleBase::body(void) const
{
    return (*body_);
}

inline bool
RWHandleBase::isValid(void) const
{
    return body_.isValid();
}

#if !defined(RW_DISABLE_DEPRECATED)
typedef RWHandleBase RWTHRHandle;
#endif

#undef RW_RESTRICTED_INLINE

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_pointer_RWHandleBase_h__
