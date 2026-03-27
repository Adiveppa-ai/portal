#ifndef __rw_pointer_RWTCountingPointer_h__
#define __rw_pointer_RWTCountingPointer_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWTCountingPointer.h#1 $
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
#include <rw/pointer/RWTPointer.h>
#include <rw/pointer/pkgdefs.h>

/**
 * \ingroup smart_pointer_package
 *
 * \brief
 * Defines a reference-counted pointer that provides reference counting
 * semantics for types that do not directly support reference counting.
 *
 * Defines a reference-counted pointer that provides reference counting
 * semantics for types that do not directly support reference counting.
 * \c Body, the first template parameter, can be any type. For the second
 * template parameter, \c Counter, you will generally use RWAtomicCounter.
 *
 * A user-defined counter class must provide the following interface:
 *
 * \code
 * class Counter
 * {
 * public:
 *     // Constructs a counter instance with an initial count of x.
 *     Counter(int x);
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
 * #include <rw/pointer/RWTCountingPointer.h>
 *
 * int main()
 * {
 *     RWTCountingPointer<int> pointer = new int(10);
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * RWAtomicCounter
 */
template <class Body, class Counter = RWAtomicCounter>
class RWTCountingPointer : public RWTPointer<Body>
{
public:

    typedef Counter  CounterType;
    typedef Body     BodyType;

    /**
     * Special constructor that performs no initialization.
     */
    RWTCountingPointer(RWStaticCtor);

    /**
     * Constructs a pointer instance that manages references for the
     * specified \c Body instance. Parameter \a bodyP is the \c Body
     * instance to be managed by this pointer.
     */
    RWTCountingPointer(Body* bodyP = rwnil);

    /**
     * Constructs a pointer instance that can access the body instance
     * associated with another pointer instance, incrementing the underlying
     * reference count for that instance by one.
     */
    RWTCountingPointer(const RWTCountingPointer<Body, Counter>& second);

    /**
     * Decrements the reference counter and deletes the body instance, if
     * there are no other references.
     */
    ~RWTCountingPointer(void);

    /**
     * Detaches from the current body (if any), decrements its associated
     * reference count, and deletes it if there are no other associated
     * references. It then attaches to \a second 's body, and increments its
     * associated reference count.
     */
    RWTCountingPointer<Body, Counter>&
    operator=(const RWTCountingPointer<Body, Counter>& second);

    /**
     * Detaches from the current body (if any), decrements its associated
     * reference count, and deletes it if there are no other associated
     * references. It then attaches to the pointer \a bodyP, and increments
     * its associated reference count. The new attached pointer must point
     * to the dynamically allocated object. Throws no exceptions.
     */
    RWTCountingPointer<Body, Counter>&
    operator=(Body* bodyP);

#ifndef RW_NO_NONCLASS_ARROW_RETURN

    // Disable this operator if your compiler doesn't allow it
    // in a template class where the template type is a non-class type,
    // if the operator is not referenced.
    /**
     * Dereferencing operator. This operator should always be used to
     * dereference the handle as it will validate the pointer, throwing an
     * exception if it is not valid. Returns a pointer to the body instance
     * attached to this handle. Throws exception RWTHRInvalidPointer if no
     * body instance has been attached to this handle instance.
     */
    Body*
    operator->(void) const;

#endif // RW_NO_NONCLASS_ARROW_RETURN

    /**
     * Dereferences the handle to get a reference to the body. Throws
     * exception RWTHRInvalidPointer if pointer is invalid.
     */
    Body&
    operator*(void) const;

private:

    void free(void);

private:

    CounterType* counterP_;
};

template <class Body, class Counter>
inline void
RWTCountingPointer<Body, Counter>::free(void)
{
    if ((rwnil != counterP_) && (0 == counterP_->removeReference())) {
        delete RWTPointer<Body>::get();
        RWTPointer<Body>::operator=(rwnil);
        delete counterP_;
        counterP_ = rwnil;
    }
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/pointer/RWTCountingPointer.cc>
#endif

#endif // __rw_pointer_RWTCountingPointer_h__
