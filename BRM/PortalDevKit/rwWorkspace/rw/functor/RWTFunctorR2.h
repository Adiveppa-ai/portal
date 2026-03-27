#ifndef __rw_functor_RWTFunctorR2_h__
#define __rw_functor_RWTFunctorR2_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR2.h#1 $
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
 * The handle class for functor bodies which are invoked with two caller
 * arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor.h>
#include <rw/functor/RWTFunctorR2Imp.h>

#  define RWFunctorR2 RWTFunctorR2

//--   The handle class for functor bodies that are invoked with two caller
//--   arguments and whose invocation returns a value.
//--
//--   A function object, or a functor, is an object that encapsulates a
//--   call to an associated global or member function.  When a functor is
//--   invoked, it calls the associated function.
//--
//--   'RWTFunctorR2' represents the group of functors that are invoked with
//--   two arguments, and whose invocation returns a value.
//--
//--   Instances of the 'RWTFunctorR2' class act as handles to functor
//--   implementations or bodies.  Such implementations are created by
//--   using either the 'rwtMakeFunctorR2()' global functions or macros.
//--   Each of these methods creates a new body instance, and returns the
//--   handle to that instance. See the example below.
//--
//--   Note that although an instance of this class is invoked with two
//--   arguments, the encapsulated function may have more arguments.
//--
//--   The additional arguments that will be passed to the encapsulated function
//--   are provided to the functor at the time of creation.  They are
//--   stored within the functor object, and are retrieved at the time
//--   of invocation.
//--
//-- Example:
//--   long foo(int i, short s){ return i+s;  }
//--
//--   int main () {
//--
//--     // Create a new handle, and create and assign a new body to it.
//--     RWTFunctorR2<long,int,short> functor = rwtMakeFunctorR2( (long(*)(int,short))0, foo );
//--
//--     // Invoke the functor with two caller arguments.
//--     long return_value = functor(42,3);
//--
//--     return 0;
//--   }
//--

/**
 * \ingroup functor_module
 *
 * \deprecated
 * As of SourcePro 12.5, use RWTFunctor<SR(S1, S2)> instead.
 *
 * \brief
 * Deprecated. Represents the group of functors that are invoked with two
 * arguments, and whose invocation returns a value.
 *
 * RWTFunctorR2 represents the group of functors that are invoked with two
 * arguments, and whose invocation returns a value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * Instances of RWTFunctorR2 act as handles to functor implementations or
 * bodies. Such implementations are created by using either the
 * rwtMakeFunctorR2() global functions or macros. Each of these methods
 * creates a new body instance, and returns the handle to that instance. See
 * the example below.
 *
 * Note that although an instance of this class is invoked with two
 * arguments, the encapsulated function may have more arguments.
 *
 * The additional arguments to be passed to the encapsulated function are
 * provided to the functor at the time of creation. They are stored within
 * the functor object, and are retrieved at the time of invocation.
 *
 * \example
 * \code
 * #include <rw/functor/functorR2.h>
 *
 * long foo(int i, short s)
 * {
 *     return (long)i + s;
 * }
 *
 * int main()
 * {
 *     // Create a handle, and assign a new body to it.
 *     RWTFunctorR2<long, int, short> functor =
 *         rwtMakeFunctorR2((long(*)(int, short))0, foo);
 *
 *     // Invoke the functor with two caller arguments.
 *     long return_value = functor(42, 3);
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * rwtMakeFunctorR2()
 */
template <class SR, class S1, class S2>
class RW_DEPRECATE_TYPE("Use RWTFunctor<SR(S1, S2)> instead") RWTFunctorR2
    : public RWTFunctor<SR(S1, S2)>
{

public:

    /**
     * Destructor.
     */
    ~RWTFunctorR2(void);

    /**
     * The signature of the functor invocation.
     */
    typedef SR(*CallerSignature)(S1, S2);

    /**
     * The type of the functor's return value.
     */
    typedef SR SRType;

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
     * handle, use the rwtMakeFunctor1() global functions or macros.
     */
    RWTFunctorR2(void);

    /**
     * Constructs a global static handle instance. Constructor does not
     * reset any values that may have been set in invocations prior to the
     * constructor call.
     */
    RWTFunctorR2(RWStaticCtor);

    /**
     * Body constructor. Binds a new handle instance to an existing functor
     * body instance.
     */
    RWTFunctorR2(RWTFunctorR2Imp<SR, S1, S2>* functorImp);

    /**
     * Copy constructor. Binds a new handle instance to the functor body
     * instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR2(const RWTFunctorR2<SR, S1, S2>& second);

    /**
     * Conversion constructor. Binds a new handle instance to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR2(const RWTFunctor<SR(S1, S2)>& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR2<SR, S1, S2>&
    operator=(const RWTFunctorR2<SR, S1, S2>& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR2<SR, S1, S2>&
    operator=(const RWTFunctor<SR(S1, S2)>& second);

    /**
     * Gets a reference for the body instance, if any, otherwise throws an
     * exception.
     *
     * \exception RWTHRInvalidPointer
     * Thrown if the handle has no associated body.
     *
     * \exception std::bad_cast
     * Thrown if the body is not of type RWTFunctorR2Imp.
     */
    RWTFunctorR2Imp<SR, S1, S2>&
    body(void) const;
};

template <class SR, class S1, class S2>
inline RWTFunctorR2Imp<SR, S1, S2>&
RWTFunctorR2<SR, S1, S2>::body(void) const
{
    // throws RWTHRInvalidPointer if no imp assigned!
    return dynamic_cast<RWTFunctorR2Imp<SR, S1, S2>&>(RWHandleBase::body());
}

template <typename SR, typename S1, typename S2>
struct RWTIsFunctor<SR(S1, S2), RWTFunctorR2<SR, S1, S2> > {
    static const bool value = true;
};

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR2.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR2_h__
