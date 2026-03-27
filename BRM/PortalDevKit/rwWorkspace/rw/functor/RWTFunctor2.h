#ifndef __rw_functor_RWTFunctor2_h__
#define __rw_functor_RWTFunctor2_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor2.h#1 $
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
 * The handle class for functor bodies that are invoked with two caller
 * arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor.h>
#include <rw/functor/RWTFunctor2Imp.h>

#  define RWFunctor2 RWTFunctor2

//--   The handle class for functor bodies that are invoked with two caller
//--   arguments.
//--
//--   A function object, or a functor, is an object that encapsulates a
//--   call to an associated global or member function.  When a functor is
//--   invoked, it calls the associated function.
//--
//--   'RWTFunctor2' represents the group of functors that are invoked with
//--   two arguments, and whose invocation returns no value.
//--
//--   Instances of the 'RWTFunctor2' class act as handles to functor
//--   implementations or bodies.  Such implementations are created by
//--   using either the 'rwtMakeFunctor2()' global functions or macros.
//--   Each of these methods creates a new body instance, and returns the
//--   handle to that instance. See the example below.
//--
//--   Note that although an instance of this class is invoked with two
//--   arguments, and returns no value, the encapsulated function may
//--   have more arguments and a return value.
//--
//--   The additional arguments that will be passed to the encapsulated function
//--   are provided to the functor at the time of creation.  They are
//--   stored within the functor object, and are retrieved at the time
//--   of invocation.
//--
//--   Any return value that the function may have will be ignored by the
//--   functor, and hence not passed back to the user. (If you are interested
//--   in the function's return value, you should probably be using the
//--   'RWTFunctorR1' group of classes.)
//--
//--
//-- Example:
//--   void foo(int x, short y){ cout << "x is " << x << ", y is " << y << endl;  }
//--
//--   int main () {
//--
//--     // Create a new handle, and create and assign a new body to it.
//--     RWTFunctor2<int,short> functor = rwtMakeFunctor2( (void(*)(int,short))0, foo );
//--
//--     // Invoke the functor with two caller arguments.
//--     functor(42,3);
//--
//--     return 0;
//--   }
//--

/**
 * \ingroup functor_module
 *
 * \deprecated
 * As of SourcePro 12.5, use RWTFunctor<void(S1, S2)> instead.
 *
 * \brief
 * Deprecated. A functor that is invoked with two arguments, and whose
 * invocation returns no value.
 *
 * RWTFunctor2 represents the group of functors that are invoked with two
 * arguments, and whose invocation returns no value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * Instances of class RWTFunctor2 act as handles to functor implementations
 * or bodies. Such implementations are created by using either the
 * rwtMakeFunctor2() global functions or macros. Each of these methods
 * creates a new body instance, and returns the handle to that instance. See
 * the example below.
 *
 * Note that although an instance of this class is invoked with two
 * arguments and returns no value, the encapsulated function may have more
 * arguments and a return value.
 *
 * The additional arguments to be passed to the encapsulated function are
 * provided to the functor at the time of creation. They are stored within
 * the functor object, and are retrieved at the time of invocation.
 *
 * Any return value that the function may have is ignored by the functor,
 * and hence not passed back to the user. (If you are interested in the
 * function's return value, consider the RWTFunctorR1 group of classes.)
 *
 * \example
 * \code
 * #include <iostream>
 * #include <rw/functor/functor2.h>
 *
 * void foo(int x, short y){
 *     std::cout << "x is " << x << ", y is " << y << std::endl;
 * }
 *
 * int main () {
 *    // Create a handle and assign a new body to it.
 *    RWTFunctor2<int,short> functor = rwtMakeFunctor2( (void(*)(int,short))0, foo );
 *
 *    // Invoke the functor with two caller arguments.
 *    functor(42,3);
 *
 *    return 0;
 * }
 * \endcode
 *
 * OUTPUT:
 * \code
 * x is 42, y is 3
 * \endcode
 * \endexample
 *
 * \sa
 * rwtMakeFunctor2()
 */
template <class S1, class S2>
class RW_DEPRECATE_TYPE("Use RWTFunctor<void(S1, S2)> instead") RWTFunctor2
    : public RWTFunctor<void(S1, S2)>
{

public:

    /**
     * Destructor.
     */
    ~RWTFunctor2(void);

    /**
     * The signature of the functor invocation.
     */
    typedef void (*CallerSignature)(S1, S2);

    /**
     * The type of the first caller argument.
     */
    typedef S1 S1Type;

    /**
     * The type of the second caller argument.
     */
    typedef S2 S2Type;

    /**
     * Constructs an empty, invalid, handle instance. To create a viable
     * handle, use the rwtMakeFunctor2() global function or macros.
     */
    RWTFunctor2(void);

    /**
     * Constructs a global static handle instance. Constructor does not
     * reset any values that may have been set in invocations prior to the
     * constructor call.
     */
    RWTFunctor2(RWStaticCtor);

    /**
     * Body constructor. Constructs a new RWTFunctor2 handle from an
     * existing body.
     */
    RWTFunctor2(RWTFunctor2Imp<S1, S2>* functorImp);

    /**
     * Copy constructor. Binds a new handle instance to the functor body
     * instance, if any, associated with the \a second handle instance.
     */
    RWTFunctor2(const RWTFunctor2<S1, S2>& second);

    /**
     * Conversion constructor. Binds a new handle instance to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctor2(const RWTFunctor<void(S1, S2)>& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctor2<S1, S2>&
    operator=(const RWTFunctor2<S1, S2>& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctor2<S1, S2>&
    operator=(const RWTFunctor<void(S1, S2)>& second);

    /**
     * Gets a reference for the body instance, if any, otherwise throws an
     * exception.
     *
     * \exception RWTHRInvalidPointer
     * Thrown if the handle has no associated body.
     *
     * \exception std::bad_cast
     * Thrown if the body is not of type RWTFunctor2Imp.
     */
    RWTFunctor2Imp<S1, S2>&
    body(void) const;
};

template <class S1, class S2>
inline RWTFunctor2Imp<S1, S2>&
RWTFunctor2<S1, S2>::body(void) const
{
    return dynamic_cast<RWTFunctor2Imp<S1, S2>&>(RWHandleBase::body());
}

template <typename S1, typename S2>
struct RWTIsFunctor<void(S1, S2), RWTFunctor2<S1, S2> > {
    static const bool value = true;
};

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor2.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_RWTFunctor2_h__
