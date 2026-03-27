#ifndef __rw_functor_RWTFunctor1_h__
#define __rw_functor_RWTFunctor1_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor1.h#1 $
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

/**************************************************************************
 *
 * Description:
 *
 * The handle class for functor bodies that are invoked with one caller
 * argument.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor.h>
#include <rw/functor/RWTFunctor1Imp.h>

#  define RWFunctor1 RWTFunctor1

/**
 * \ingroup functor_module
 *
 * \deprecated
 * As of SourcePro 12.5, use RWTFunctor<R(As...)> instead.
 *
 * \brief
 * Deprecated. A functor that is invoked with one argument, and whose
 * invocation returns no value.
 *
 * RWTFunctor1 represents the group of functors that are invoked with one
 * argument, and whose invocation returns no value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * Instances of class RWTFunctor1 act as handles to functor implementations
 * or bodies. Such implementations are created by using either the
 * rwtMakeFunctor1() global functions or macros. Each of these methods
 * creates a new body instance, and returns the handle to that instance. See
 * the example below.
 *
 * Note that although an instance of this class is invoked with one argument
 * and returns no value, the encapsulated function may have more arguments
 * and a return value.
 *
 * The additional arguments to be passed to the encapsulated function are
 * provided to the functor at the time of creation. They are stored within
 * the functor object, and are retrieved at the time of invocation.
 *
 * Any return value that the function may have is ignored by the functor,
 * and hence not passed back to the user. If you are interested in the
 * function's return value, see the RWTFunctorR2 group of classes.
 *
 * \example
 * \code
 * #include <iostream>
 * #include <rw/functor/functor1.h>
 *
 * void foo(int x)
 * {
 *     std::cout << "x is " << x << std::endl;
 * }
 *
 * int main()
 * {
 *     // Create a handle, and assign a new body to it.
 *     RWTFunctor1<int> functor =
 *         rwtMakeFunctor1((void(*)(int))0, foo);
 *
 *     // Invoke the functor with one caller argument.
 *     functor(42);
 *
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * x is 42
 * \endcode
 * \endexample
 *
 * \sa
 * rwtMakeFunctor1()
 */
template <class S1>
class RW_DEPRECATE_TYPE("Use RWTFunctor<void(S1)> instead") RWTFunctor1
    : public RWTFunctor<void(S1)>
{

public:

    /**
     * Destructor.
     */
    ~RWTFunctor1(void);

    /**
     * The signature of the functor invocation.
     */
    typedef void (*CallerSignature)(S1);

    /**
     * The type of the caller argument.
     */
    typedef S1 S1Type;

    /**
     * Constructs an empty, invalid, handle instance. To create a viable
     * handle, use the rwtMakeFunctor1() global functions or macros.
     */
    RWTFunctor1(void);

    /**
     * Constructs a global static handle instance. Constructor does not
     * reset any values that may have been set in invocations prior to the
     * constructor call.
     */
    RWTFunctor1(RWStaticCtor);

    /**
     * Body constructor. Constructs a new RWTFunctor1 handle from an
     * existing body.
     */
    RWTFunctor1(RWTFunctor1Imp<S1>* functorImp);

    /**
     * Copy constructor. Binds a new handle instance to the functor body
     * instance, if any, associated with the \a second handle instance.
     */
    RWTFunctor1(const RWTFunctor1<S1>& second);

    /**
     * Conversion constructor. Binds a new handle instance to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctor1(const RWTFunctor<void(S1)>& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctor1<S1>&
    operator=(const RWTFunctor1<S1>& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctor1<S1>&
    operator=(const RWTFunctor<void(S1)>& second);

    /**
     * Gets a reference for the body instance, if any, otherwise throws an
     * exception.
     *
     * \exception RWTHRInvalidPointer
     * Thrown if the handle has no associated body.
     *
     * \exception std::bad_cast
     * Thrown if the body is not of type RWTFunctor1Imp.
     */
    RWTFunctor1Imp<S1>&
    body(void) const;
};

template <class S1>
inline RWTFunctor1Imp<S1>&
RWTFunctor1<S1>::body(void) const
{
    return dynamic_cast<RWTFunctor1Imp<S1>&>(RWHandleBase::body());
}

template <typename S1>
struct RWTIsFunctor<void(S1), RWTFunctor1<S1> > {
    static const bool value = true;
};


#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor1.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_RWTFunctor1_h__
