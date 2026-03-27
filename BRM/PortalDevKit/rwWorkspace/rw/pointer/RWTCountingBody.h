#ifndef __rw_pointer_RWTCountingBody_h__
#define __rw_pointer_RWTCountingBody_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWTCountingBody.h#1 $
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

#include <rw/pointer/RWAtomicCounter.h>
#include <rw/pointer/pkgdefs.h>
#include <rw/sync/RWTMonitor.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWCountingBody RWTCountingBody
#endif

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4231)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup smart_pointer_package
 *
 * \brief
 * Base class for classes that must maintain a reference count.
 *
 * RWTCountingBody is a base class for classes that must maintain a
 * reference count. It can be safely used in a multithreaded environment.
 *
 * \example
 * \code
 * #include <rw/pointer/RWTCountedPointer.h>
 * #include <rw/pointer/RWTCountingBody.h>
 * #include <rw/sync/RWMutexLock.h>
 * #include <iostream>
 *
 * class Foo : public RWTCountingBody<RWMutexLock>
 * {
 * public:
 *     void bar(void) {
 *         std::cout << "I'm a foo example" << std::endl;
 *     }
 * };
 *
 * typedef RWTCountedPointer<Foo> FooPointer;
 *
 * int main(void)
 * {
 *     try {
 *         FooPointer p1(new Foo);
 *         p1->bar();
 *     }
 *     catch (const RWxmsg& msg) {
 *         std::cout << msg.why() << std::endl;
 *     }
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
template <class Mutex>
class RWTCountingBody : public RWTMonitor<Mutex>
{

public:

    /**
     * Destructor.
     */
    ~RWTCountingBody(void);

    /**
     * Queries the current reference count. Throws no exceptions.
     */
    unsigned
    references(void) const;

    /**
     * Increments the reference count and then returns the previous value
     * minus one.
     */
    unsigned
    addReference(void);

    /**
     * Decrements the reference count and then returns the previous value
     * minus one.
     */
    unsigned
    removeReference(void);

protected:

    /**
     * Constructs a default instance (initializes the reference count).
     * Throws no exceptions.
     */
    RWTCountingBody(unsigned initCount = 0);

    /**
     * Constructs a static instance (does not initialize the reference
     * count). Throws no exceptions.
     */
    RWTCountingBody(RWStaticCtor);

    //--Defines copy constructor so that derived classes can copy-construct,
    //--but it initializes the reference count; don't copy it.
    //--Throws no exceptions.
    /**
     * Defines a copy constructor that creates a new instance and
     * initializes the reference count. This constructor does not actually
     * create a copy, but allows derived classes to provide a meaningful
     * copy constructor. Throws no exceptions.
     */
    RWTCountingBody(const RWTCountingBody<Mutex>& second);

    /**
     * Defines an assignment operator, allowing derived classes to do
     * assignments. Don't assign the reference count. Throws no exceptions.
     */
    RWTCountingBody<Mutex>&
    operator=(const RWTCountingBody<Mutex>& second);

    //Predefine guards for use with counting body.
#if !defined(RW_DISABLE_DEPRECATED)
    typedef RWTLockGuard   < RWTMonitor<Mutex> >  Guard;
#endif

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTLockGuard   < RWTMonitor<Mutex> >  LockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTUnlockGuard < RWTMonitor<Mutex> >  UnlockGuard;

    /**
     * Predefined type for compatible guard.
     */
    typedef RWTTryLockGuard< RWTMonitor<Mutex> >  TryLockGuard;

private:

    RWAtomicCounter counter_;
};

/*****************************************************************************/

template <class Mutex>
RW_POINTER_INLINE_SPECIALIZED_MEMBER
RWTCountingBody<Mutex>::RWTCountingBody(unsigned initCount)
    : RWTMonitor<Mutex>()
    , counter_(unsigned(initCount - 1))
{
}

template <class Mutex>
RW_POINTER_INLINE_SPECIALIZED_MEMBER
RWTCountingBody<Mutex>::RWTCountingBody(RWStaticCtor)
    : RWTMonitor<Mutex>(RW_STATIC_CTOR)
    , counter_(RW_STATIC_CTOR)
{
    // Leave refs_ alone for initial static instances.
    // The storage where static objects are constructed is
    // initialized with zero, and refs_ = 0 indicates a
    // reference count of 1. This prevents double destruction
    // of the static body that would normally occur when the
    // last handle was destroyed.
}

template <class Mutex>
RW_POINTER_INLINE_SPECIALIZED_MEMBER
RWTCountingBody<Mutex>::RWTCountingBody(const RWTCountingBody<Mutex>&)
    : RWTMonitor<Mutex>(),
      counter_((unsigned) - 1)
{
    // Don't copy anything
}

template <class Mutex>
RW_POINTER_INLINE_SPECIALIZED_MEMBER
RWTCountingBody<Mutex>::~RWTCountingBody(void)
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
template <class Mutex>
RW_POINTER_INLINE_SPECIALIZED_MEMBER
RWTCountingBody<Mutex>&
RWTCountingBody<Mutex>::operator=(const RWTCountingBody<Mutex>&)
{
    // Don't assign anything
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING


/*****************************************************************************/

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/pointer/RWTCountingBody.cc>
#endif

// Template instantiation magic
#include <rw/pointer/instance.h>

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_pointer_RWTCountingBody_h__
