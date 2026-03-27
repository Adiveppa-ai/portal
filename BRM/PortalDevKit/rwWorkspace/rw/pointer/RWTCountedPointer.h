#ifndef __rw_pointer_RWTCountedPointer_h__
#define __rw_pointer_RWTCountedPointer_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWTCountedPointer.h#1 $
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

#include <rw/pointer/RWTPointer.h>
#include <rw/pointer/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWCountedPointer RWTCountedPointer
#endif

/**
 * \ingroup smart_pointer_package
 *
 * \brief
 * A <em>smart pointer</em> handle to a reference-counting body.
 *
 * RWTCountedPointer is a <em>smart pointer</em> class intended for use as a
 * \e handle to a reference-counting \e body. Each time an instance of this
 * class is bound to a body instance, it increments the reference count
 * maintained by that body. Each time it detaches from a body instance, it
 * decrements the body's reference count; and if the reference count reaches
 * zero, it deletes the body instance. The reference counting relieves
 * clients of the burden of tracking when it is safe to delete a body
 * instance.
 *
 * Any class used for the template parameter \c Body must derive from class
 * RWTCountingBody or provide the following interface:
 *
 * \code
 * class Body
 * {
 * public:
 *
 *     // Increments the reference count by one.
 *     void addReference();
 *
 *     // Decrements the reference count by one.
 *     // Must return 0 after the last reference count is removed,
 *     // indicating that it is safe to deallocate the body instance.
 *     int removeReference();
 * };
 * \endcode
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
 *
 * \sa
 * RWTCountingBody
 */
template< class Body >
class RWTCountedPointer : public RWTPointer<Body>
{

public:

    /**
     * The type of the \c Body.
     */
    typedef Body BodyType;

    /**
     * Special constructor that performs no initialization. Throws no
     * exceptions.
     */
    RWTCountedPointer(RWStaticCtor);

    /**
     * Attaches to and increments the reference count on a body.
     */
    RWTCountedPointer(Body* bodyP = rwnil);

    /**
     * Attaches to and increments the reference count on the body of
     * \a second.
     */
    RWTCountedPointer(const RWTCountedPointer<Body>& second);

    /**
     * Decrements the body's reference count, and deletes it if there are no
     * other references.
     */
    ~RWTCountedPointer(void);

    /**
     * Detaches from the current body (if any), decrements its reference
     * count, and deletes it if there are no other references. It then
     * attaches to the body of \a second, and increments its reference
     * count.
     */
    RWTCountedPointer<Body>&
    operator=(const RWTCountedPointer<Body>& second);

    /**
     * Detaches from the current body (if any), decrements its reference
     * count, and deletes it if there are no other references. It then
     * attaches to pointer body \a ptr, and increments its reference count.
     */
    RWTCountedPointer<Body>&
    operator=(Body* ptr);

    /**
     * Dereferences the handle. Always use this operator to dereference the
     * handle, since it validates the pointer. Throws an RWTHRInvalidPointer
     * exception if invalid.
     */
    Body*
    operator->(void) const;

    /**
     * Dereferences the handle to get a reference to the body. Throws an
     * RWTHRInvalidPointer exception.
     */
    Body&
    operator*(void) const;

    /**
     * Detaches from the current body (if any), decrements its reference
     * count, and deletes it if there are no other references.
     */
    void
    orphan(void);

protected:

    /**
     * Detaches from the current body (if any), decrements its reference
     * count, and deletes it if there are no other references. Then it
     * attaches to the new body, incrementing its reference count.
     */
    void
    transfer(Body* bodyP = rwnil);

};

template< class Body >
inline void
RWTCountedPointer<Body>::orphan(void)
{
    transfer(rwnil);
}

template< class Body >
inline void
RWTCountedPointer<Body>::transfer(Body* bodyP)
{
    if (rwnil != bodyP) {
        bodyP->addReference();
    }

    // nothing below this line should throw. if it does, we are in big trouble!
    Body* body = RWTPointer<Body>::get();

    if (rwnil != body) {
        // We have a body...decrement the reference count to detach
        if (0 == body->removeReference()) {
            // No more references, delete the body
            delete body;
        }
    }

    RWTPointer<Body>::operator=(bodyP);
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/pointer/RWTCountedPointer.cc>
#endif

#endif // __rw_pointer_RWTCountedPointer_h__
