#ifndef __rw_functor_RWTFunctorR1_h__
#define __rw_functor_RWTFunctorR1_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR1.h#1 $
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
 * The handle class for functor bodies which are invoked with one caller
 * argument.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor.h>
#include <rw/functor/RWTFunctorR1Imp.h>

#  define RWFunctorR1 RWTFunctorR1

//--   The handle class for functor bodies that are invoked with one caller
//--   argument and whose invocation returns a value.
//--
//--   A function object, or a functor, is an object that encapsulates a
//--   call to an associated global or member function.  When a functor is
//--   invoked, it calls the associated function.
//--
//--   'RWTFunctorR1' represents the group of functors that are invoked without
//--   any arguments, and whose invocation returns no value.
//--
//--   Instances of the 'RWTFunctorR1' class act as handles to functor
//--   implementations or bodies.  Such implementations are created by
//--   using either the 'rwtMakeFunctorR1()' global functions or macros.
//--   Each of these methods creates a new body instance, and returns the
//--   handle to that instance. See the example below.
//--
//--   Note that although an instance of this class is invoked with one
//--   argument, the encapsulated function may have more arguments.
//--
//--   The additional arguments that will be passed to the encapsulated function
//--   are provided to the functor at the time of creation.  They are
//--   stored within the functor object, and are retrieved at the time
//--   of invocation.
//--
//-- Example:
//--      // A function to be encapsulated in a functor.
//--   int flag;
//--   int setFlag(short f){ return flag=f;  }
//--
//--   int main () {
//--
//--        // Creates a new handle instance ('functor'), and creates and
//--        // assigns a new body instance to it.
//--     RWTFunctorR1 functor = rwtMakeFunctorR1((int(*short))0, setFlag);
//--
//--        // At this time 'functor' contains a viable RWTFunctorR1 instance.
//--
//--        // Invoking the functor with '32' will set the global flag to 32 and
//--        // returns the value '32'
//--     int new value = functor(32);
//--
//--     return 0;
//--   }
//--
//--

/**
 * \ingroup functor_module
 *
 * \deprecated
 * As of SourcePro 12.5, use RWTFunctor<R(As...)> instead.
 *
 * \brief
 * Deprecated. Represents the group of functors that are invoked with one
 * argument, and whose invocation returns a value.
 *
 * RWTFunctorR1 represents the group of functors that are invoked with one
 * argument, and whose invocation returns a value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * Instances of RWTFunctorR1 act as handles to functor implementations or
 * bodies. Such implementations are created by using either the
 * rwtMakeFunctorR1() global functions or macros. Each of these methods
 * creates a new body instance, and returns the handle to that instance. See
 * the example below.
 *
 * Note that although an instance of this class is invoked with one
 * argument, the encapsulated function may have more arguments.
 *
 * The additional arguments to be passed to the encapsulated function are
 * provided to the functor at the time of creation. They are stored within
 * the functor object, and are retrieved at the time of invocation.
 *
 * \example
 * \code
 * #include <rw/functor/functorR1.h>
 * // A function to be encapsulated in a functor.
 * int flag = 0;
 * int setFlag(short f)
 * {
 *     return flag = f;
 * }
 *
 * int main()
 * {
 *     // Create a new handle (functor) and assign a new body to it.
 *     RWTFunctorR1<int, short> functor =
 *         rwtMakeFunctorR1((int(*)(short))0, setFlag);
 *
 *     // Invoking the functor with '32' will set the global flag to
 *     // 32 and return the value '32'
 *     int new_value = functor(32);
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * rwtMakeFunctorR1()
 */
template <class SR, class S1>
class RW_DEPRECATE_TYPE("Use RWTFunctor<SR(S1)> instead") RWTFunctorR1
    : public RWTFunctor<SR(S1)>
{

public:

    /**
     * Destructor.
     */
    ~RWTFunctorR1(void);

    /**
     * The signature of the functor invocation.
     */
    typedef SR(*CallerSignature)(S1);

    /**
     * The type of the functor's return value.
     */
    typedef SR SRType;

    /**
     * The type of the first caller argument.
     */
    typedef S1 S1Type;

    /**
     * Constructs an empty, invalid, handle instance. To create a viable
     * handle, use the rwtMakeFunctor1() global functions or macros.
     */
    RWTFunctorR1(void);

    /**
     * Constructs a global static handle instance. The constructor does not
     * reset any values that may have been set in invocations prior to the
     * constructor call.
     */
    RWTFunctorR1(RWStaticCtor);

    /**
     * Body constructor. Binds a new handle instance to an existing functor
     * body instance.
     */
    RWTFunctorR1(RWTFunctorR1Imp<SR, S1>* functorImp);

    /**
     * Copy constructor. Binds a new handle instance to the functor body
     * instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR1(const RWTFunctorR1<SR, S1>& second);

    /**
     * Conversion constructor. Binds a new handle instance to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR1(const RWTFunctor<SR(S1)>& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR1<SR, S1>&
    operator=(const RWTFunctorR1<SR, S1>& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR1<SR, S1>&
    operator=(const RWTFunctor<SR(S1)>& second);

    /**
     * Gets a reference for the body instance, if any, otherwise throws an
     * exception.
     *
     * \exception RWTHRInvalidPointer
     * Thrown if the handle has no associated body.
     *
     * \exception std::bad_cast
     * Thrown if the body is not of type RWTFunctorR1Imp.
     */
    RWTFunctorR1Imp<SR, S1>&
    body(void) const;

};

template <class SR, class S1>
inline RWTFunctorR1Imp<SR, S1>&
RWTFunctorR1<SR, S1>::body(void) const
{
    // throws RWTHRInvalidPointer if no imp assigned!
    return dynamic_cast<RWTFunctorR1Imp<SR, S1>&>(RWHandleBase::body());
}

template <typename SR, typename S1>
struct RWTIsFunctor<SR(S1), RWTFunctorR1<SR, S1> > {
    static const bool value = true;
};

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR1.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR1_h__
