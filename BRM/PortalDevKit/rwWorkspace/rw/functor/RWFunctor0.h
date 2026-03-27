#ifndef __rw_functor_RWFunctor0_h__
#define __rw_functor_RWFunctor0_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWFunctor0.h#1 $
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
 * The handle class for functor bodies that are invoked without any caller
 * arguments, and whose invocation returns no value.
 *
 *************************************************************************/

#include <rw/functor/RWFunctor0Imp.h>
#include <rw/functor/RWTFunctor.h>
#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

/**
 * \ingroup functor_module
 *
 * \deprecated
 * As of SourcePro 12.5, use RWTFunctor<R(As...)> instead.
 *
 * \brief
 * Deprecated. Represents the group of functors that are invoked without any
 * arguments and whose invocation returns no value.
 *
 * RWFunctor0 represents the group of functors that are invoked without any
 * arguments and whose invocation returns no value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * Instances of class RWFunctor0 act as handles to functor implementations
 * or bodies. Such implementations are created by using either the
 * rwtMakeFunctor0() global functions or macros. Each of these methods
 * creates a new body instance, and returns the handle to that instance. See
 * the example below.
 *
 * Note that although an instance of this class is invoked with no arguments
 * and returns no value, the encapsulated function may have both arguments
 * and a return value.
 *
 * The arguments to be passed to the encapsulated function are provided to
 * the functor at the time of creation. They are stored within the functor
 * object, and are retrieved at the time of invocation.
 *
 * Any function return value is ignored by the functor, and hence not passed
 * back to the user. If you are interested in the function's return value,
 * see the RWTFunctorR0 group of classes.
 *
 * \example
 * \code
 * #include <iostream>
 * #include <rw/functor/functor0.h>
 *
 * // A function to be encapsulated in a functor.
 * void print()
 * {
 *     std::cout << "Hello World" << std::endl;
 * }
 *
 * int main()
 * {
 *     // Create a handle ('functor'), and
 *     // assign a new body to it.
 *     RWFunctor0 functor = rwtMakeFunctor0((void(*)())0, print);
 *
 *     // Invoking the functor will print "Hello World."
 *     functor();
 *
 *     return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * Hello World
 * \endcode
 * \endexample
 *
 * \sa
 * rwtMakeFunctor0()
 */
class RW_DEPRECATE_TYPE("Use RWTFunctor<void()> instead") RW_FUNCTOR_SYMBOLIC RWFunctor0
    : public RWTFunctor<void()>
{

public:

    /**
     * The signature of the functor invocation.
     */
    typedef void (*CallerSignature)(void);

    /**
     * Constructs an empty, invalid, handle instance. To create a viable
     * handle, use the rwtMakeFunctor0() global functions or macros.
     */
    RWFunctor0(void);

    /**
     * Constructs a global static handle instance. The constructor does not
     * reset any values that may have been set in invocations prior to the
     * constructor call.
     */
    RWFunctor0(RWStaticCtor);

    /**
     * Body constructor. Binds a new handle instance to an existing functor
     * body instance.
     */
    RWFunctor0(RWFunctor0Imp* functorImp);

    /**
     * Copy constructor. Binds a new handle instance to the functor body
     * instance, if any, associated with the \a second handle instance.
     */
    RWFunctor0(const RWFunctor0& second);

    /**
     * Conversion constructor. Binds a new handle instance to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWFunctor0(const RWTFunctor<void()>& second);

    //-- Destructor
    //-- Needed mostly to work around optimization problems some
    //-- compilers (e.g. gcc) have when destructor is not provided
    /**
     * Destructor.
     */
    ~RWFunctor0(void);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWFunctor0&
    operator=(const RWFunctor0& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWFunctor0&
    operator=(const RWTFunctor<void()>& second);

    /**
     * Gets a reference for the body instance, if any, otherwise throws an
     * exception.
     *
     * \exception RWTHRInvalidPointer
     * Thrown if the handle has no associated body.
     *
     * \exception std::bad_cast
     * Thrown if the body is not of type RWFunctor0Imp.
     */
    RWFunctor0Imp&
    body(void) const;

};

inline RWFunctor0Imp&
RWFunctor0::body(void) const
{
    return dynamic_cast<RWFunctor0Imp&>(RWHandleBase::body());
}

template <>
struct RWTIsFunctor<void(), RWFunctor0 > {
    static const bool value = true;
};

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWFunctor0_h__
