#ifndef __rw_pointer_RWBodyBase_h__
#define __rw_pointer_RWBodyBase_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWBodyBase.h#1 $
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

#include <rw/pointer/RWTCountedPointer.h>
#include <rw/pointer/RWTCountingBody.h>
#include <rw/pointer/pkgdefs.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4275)
#endif

/**
 * \ingroup smart_pointer_package
 *
 * \brief
 * Base class for body classes.
 *
 * Base class for body classes. Each time an RWHandleBase instance is bound
 * to an instance of this class, the handle instance increments the
 * reference count inherited by the body instance. Each time a handle
 * instance detaches from an instance of this class, the handle decrements
 * the reference count. If the reference count reaches zero, the handle
 * deletes the body instance. The reference counting relieves clients of the
 * burden of having to keep track of when it is safe to delete a body
 * instance.
 *
 * \example
 * See \c HandlebodyEx1.cpp and \c HandlebodyEx2.cpp, located in the
 * \c examples directory.
 * \endexample
 */
class RW_POINTER_GLOBAL RWBodyBase
    : protected RWTCountingBody<RWMutexLock>
{

    // Give RWTCountedPointer access to protected members...
    friend class RWTCountedPointer<RWBodyBase>;

public:

    // must match template type from base class...
    typedef RWMutexLock MutexType;

protected:

    /**
     * Default constructor. Constructs a default body instance where the
     * reference count starts at zero.
     */
    RWBodyBase(void);

    /**
     * Constructs a static body instance where the reference count starts at
     * one, to prevent deletion by handles.
     */
    RWBodyBase(RWStaticCtor);

    //We don't want to copy the reference count during copy-construction
    /**
     * Copy constructor.
     */
    RWBodyBase(const RWBodyBase& second);

    //Makes the destructor virtual so that 'RWHandleBase' will call the proper
    //destructor for classes derived from 'RWBodyBase'.
    /**
     * Destructor. Throws no exceptions.
     */
    virtual
    ~RWBodyBase(void);

    //We don't want to copy the reference count during assignment.
    /**
     * Assignment operator. Throws no exceptions.
     */
    RWBodyBase&
    operator=(const RWBodyBase& second);

    // Increments the internal reference count by 1.
    // Documented in the base class.
    unsigned
    addReference(void);

    // Decrements the internal reference count by 1.
    // Documented in the base class.
    unsigned
    removeReference(void);

    // returns the current reference count.
    // Documented in the base class.
    unsigned
    references(void) const;

};

/*****************************************************************************/

// Construct a default body instance
// (reference count starts at zero)
inline
RWBodyBase::RWBodyBase(void)
    : RWTCountingBody<MutexType>()
{
}

// Construct a static body instance
// (reference count starts at one to prevent deletion by handles)
inline
RWBodyBase::RWBodyBase(RWStaticCtor)
    : RWTCountingBody<MutexType>(RW_STATIC_CTOR)
{
}

// We don't want to copy the reference count during copy-construction,
// so this member calls the RWTCountingBody copy constructor which copies
// nothing...
inline
RWBodyBase::RWBodyBase(const RWBodyBase&)
    : RWTCountingBody<MutexType>()
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
inline RWBodyBase&
RWBodyBase::operator=(const RWBodyBase&)
{
    // Don't assign anything
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING

inline unsigned
RWBodyBase::addReference(void)
{
    return RWTCountingBody<MutexType>::addReference();
}

inline unsigned
RWBodyBase::removeReference(void)
{
    return RWTCountingBody<MutexType>::removeReference();
}

inline unsigned
RWBodyBase::references(void) const
{
    return RWTCountingBody<MutexType>::references();
}

#if !defined(RW_DISABLE_DEPRECATED)
typedef RWBodyBase RWTHRBody;
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_pointer_RWBodyBase_h__
