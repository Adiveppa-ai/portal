#ifndef __rw_pointer_RWTOnlyPointer_h__
#define __rw_pointer_RWTOnlyPointer_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pointer/RWTOnlyPointer.h#1 $
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
#  define RWOnlyPointer RWTOnlyPointer
#endif

/**
 * \ingroup smart_pointer_package
 *
 * \brief
 * Simplifies the use of pointers that refer to objects on the heap,
 * automatically destroying the object when the pointer object is itself
 * destroyed.
 *
 * RWTOnlyPointer is an abstraction that simplifies the use of pointers
 * referring to objects (that is, bodies) on the heap. It doesn't do
 * reference counting on the body; rather, it is based on the idea of strict
 * ownership semantics. Strict ownership means that if the assignment
 * operator or the copy constructor is called, then the right-hand instance
 * is invalidated (its body pointer is set to #rwnil), and the left-hand
 * instance assumes responsibility for deleting the body.
 *
 * This class is useful for ensuring the recovery of dynamically allocated
 * memory, especially in the presence of exceptions. This class provides
 * functionality equivalent to that provided by the C++ Standard Library
 * class \b std::auto_ptr.
 *
 * \example
 * \code
 * #include <rw/pointer/RWTOnlyPointer.h>
 *
 * class A { };
 *
 * class B {
 * public:
 *     // The instance of A allocated here is automatically
 *     // deleted if an exception occurs in the initialize()
 *     // function.
 *     B()
 *     {
 *       p_ = new A;
 *       initialize();
 *     }
 *
 * private:
 *     RWTOnlyPointer<A> p_;
 *     void initialize(void);
 * };
 * \endcode
 * \endexample
 */
template< class Body >
class RWTOnlyPointer : public RWTPointer<Body>
{
public:

    /**
     * The type of the body.
     */
    typedef Body BodyType;  // Can't depend on inheritance!

    /**
     * Special constructor that performs no initialization. Throws no
     * exceptions.
     */
    RWTOnlyPointer(RWStaticCtor);

    /**
     * Assumes responsibility for a new body. This pointer manages an
     * instance parameter \a bodyP. Throws no exceptions.
     */
    RWTOnlyPointer(Body* bodyP = rwnil);

    //--Assumes responsibility for another handle's body.
    //--Even though we will orphan the body from 'second', we must
    //--declare 'second' 'const' to allow assignment from temporaries!
    /**
     * Assumes responsibility for another handle's body.
     */
    RWTOnlyPointer(const RWTOnlyPointer<Body>& second);

    /**
     * Deletes the current body.
     */
    ~RWTOnlyPointer(void);

    //--Assumes responsibility for another handle's body. Even though we
    //--will orphan the body from 'second', we must declare 'second'
    //--'const' to allow assignment from temporaries!
    /**
     * Assumes responsibility for another handle's body.
     */
    RWTOnlyPointer<Body>&
    operator=(const RWTOnlyPointer<Body>& second);

    /**
     * Assigns a new pointer value to the handle (required for handle
     * conversions). Throws no exceptions.
     */
    RWTOnlyPointer<Body>&
    operator=(Body* ptr);

#ifndef RW_NO_NONCLASS_ARROW_RETURN

    /**
     * Pointer dereference operator. This operator should always be used to
     * dereference the handle as it first validates the pointer. If the
     * pointer is not valid, throws an RWTHRInvalidPointer exception.
     */
    Body*
    operator->(void) const;

#endif

    /**
     * Pointer dereference operator. Dereferences the handle to get a
     * reference to the body. Throws the exception RWTHRInvalidPointer if
     * the pointer is not valid.
     */
    Body&
    operator*(void) const;

    /**
     * Body pointer conversion operator for the handle (required for handle
     * conversions). Gives up responsibility for deleting the body.
     */
    operator Body* (void);

protected:

    /**
     * Relinquishes control over the current body (if any).
     */
    Body*
    orphan(void);

    /**
     * Deletes the current body (if any), and assumes control of another
     * body (if any).
     */
    void
    transfer(Body* bodyP = rwnil);
};

template< class Body >
inline
RWTOnlyPointer<Body>::RWTOnlyPointer(RWStaticCtor)
    :
    RWTPointer<Body>(RW_STATIC_CTOR)
{
}

template< class Body >
inline
RWTOnlyPointer<Body>::RWTOnlyPointer(Body* bodyP)
    :
    RWTPointer<Body>(bodyP)
{
}

template< class Body >
inline
RWTOnlyPointer<Body>::RWTOnlyPointer(RWTOnlyPointer<Body> const& ref)
    : RWTPointer< Body > (const_cast< RWTOnlyPointer< Body >& >(ref).orphan())
{
}


template< class Body >
inline
RWTOnlyPointer<Body>::~RWTOnlyPointer(void)
{
    // Always delete the body when the handle destructs...
    transfer(rwnil); // delete and invalidate pointer
}

template< class Body >
inline RWTOnlyPointer<Body>&
RWTOnlyPointer<Body>::operator=(const RWTOnlyPointer<Body>& second)
{
    if (&second != this) {
        // Detach the second handle from the body and attach this one to the body
        // This is very bad. Breach of contract
        transfer(const_cast< RWTOnlyPointer<Body>& >(second).orphan());
    }
    return *this;
}

template< class Body >
inline RWTOnlyPointer<Body>&
RWTOnlyPointer<Body>::operator=(Body* ptr)
{
    if (ptr != this->bodyP_) {
        transfer(ptr);
    }
    return *this;
}

#ifndef RW_NO_NONCLASS_ARROW_RETURN

template< class Body >
inline Body*
RWTOnlyPointer<Body>::operator->(void) const
{
    RWTPointer<Body>::validate();
    return RWTPointer<Body>::get();
}

#endif

template< class Body >
inline Body&
RWTOnlyPointer<Body>::operator*(void) const
{
    RWTPointer<Body>::validate();
    return *(RWTPointer<Body>::get());
}

template< class Body >
inline
RWTOnlyPointer<Body>::operator Body* (void)
{
    return orphan();
}

template< class Body >
inline Body*
RWTOnlyPointer<Body>::orphan(void)
{
    // Detach from the body
    Body* temp = RWTPointer<Body>::get();
    RWTPointer<Body>::operator=(rwnil);
    return temp;
}

template< class Body >
inline void
RWTOnlyPointer<Body>::transfer(Body* bodyP)
{
    // Delete this handle's current body (if any)
    delete RWTPointer<Body>::get();
    // And attach to the new one...
    RWTPointer<Body>::operator=(bodyP);
}

#endif // __rw_pointer_RWTOnlyPointer_h__
