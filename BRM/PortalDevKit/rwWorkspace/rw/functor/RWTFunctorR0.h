#ifndef __rw_functor_RWTFunctorR0_h__
#define __rw_functor_RWTFunctorR0_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR0.h#1 $
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
#include <rw/functor/RWTFunctorR0Imp.h>

#  define RWFunctorR0 RWTFunctorR0


//--   The handle class for functor bodies that are invoked without any caller
//--   arguments and whose invocation returns a value.
//--
//--   A function object, or a functor, is an object that encapsulates a
//--   call to an associated global or member function.  When a functor is
//--   invoked, it calls the associated function.
//--
//--   'RWTFunctorR0' represents the group of functors that are invoked without
//--   any arguments, and whose invocation returns a value.
//--
//--   Instances of the 'RWTFunctorR0' class act as handles to functor
//--   implementations or bodies.  Such implementations are created by
//--   using either the 'rwtMakeFunctorR0()' global functions or macros.
//--   Each of these methods creates a new body instance, and returns the
//--   handle to that instance. See the example below.
//--
//--   Note that although an instance of this class is invoked with no
//--   arguments, the encapsulated function may have up to 3 arguments.
//--
//--   The arguments that will be passed to the encapsulated function
//--   are provided to the functor at the time of creation.  They are
//--   stored within the functor object, and are retrieved at the time
//--   of invocation.
//--
//--
//-- Example:
//--      // A function to be encapsulated in a functor.
//--   int flag;
//--   int getFlag(){ return flag; }
//--
//--   int main () {
//--
//--        // Creates a new handle instance ('functor'), and creates and
//--        // assigns a new body instance to it.
//--     RWTFunctorR0 functor = rwtMakeFunctorR0((int(*void))0, getFlag);
//--
//--        // At this time 'functor' contains a viable RWTFunctorR0 instance.
//--
//--        // Invoking the functor will return the value of flag
//--     int flag_value = functor();
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
 * Deprecated. A functor that is invoked without any arguments and whose
 * invocation returns a value.
 *
 * RWTFunctorR0 represents the group of functors that are invoked without
 * any arguments, and whose invocation returns a value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * Instances of RWTFunctorR0 act as handles to functor implementations or
 * bodies. Such implementations are created by using either the
 * rwtMakeFunctorR0() global functions or macros. Each of these methods
 * creates a new body instance, and returns the handle to that instance. See
 * the example below.
 *
 * Note that although an instance of this class is invoked with no
 * arguments, the encapsulated function may have up to three arguments.
 *
 * The arguments to be passed to the encapsulated function are provided to
 * the functor at the time of creation. They are stored within the functor
 * object, and are retrieved at the time of invocation.
 *
 * \example
 * \code
 * #include <rw/functor/functorR0.h>
 *
 * // A function to be encapsulated in a functor.
 * int flag = 0;
 * int getFlag()
 * {
 *     return flag;
 * }
 *
 * int main()
 * {
 *     // Create a handle ('functor'), and assign a body to it.
 *     RWTFunctorR0<int> functor =
 *         rwtMakeFunctorR0((int(*)(void))0, getFlag);
 *
 *     // Invoking the functor will return the value of flag
 *     int flag_value = functor();
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * rwtMakeFunctorR0()
 */
template <class SR>
class RW_DEPRECATE_TYPE("Use RWTFunctor<SR()> instead") RWTFunctorR0
    : public RWTFunctor<SR()>
{

public:

    /**
     * The signature of the functor invocation.
     */
    typedef SR(*CallerSignature)(void);

    /**
     * The return type of the functor.
     */
    typedef SR SRType;

    /**
     * Constructs an empty, invalid, handle instance. To create a viable
     * handle use the rwtMakeFunctorR0() global functions or macros.
     */
    RWTFunctorR0(void);

    /**
     * Constructs a global static handle instance. The constructor does not
     * reset any values that may have been set in invocations prior to the
     * constructor call.
     */
    RWTFunctorR0(RWStaticCtor);

    /**
     * Destructor.
     */
    ~RWTFunctorR0(void);

    /**
     * Body constructor. Binds a new handle instance to an existing functor
     * body instance.
     */
    RWTFunctorR0(RWTFunctorR0Imp<SR>* functorImp);

    /**
     * Copy constructor. Binds a new handle instance to the functor body
     * instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR0(const RWTFunctorR0<SR>& second);

    /**
     * Conversion constructor. Binds a new handle instance to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR0(const RWTFunctor<SR()>& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR0<SR>&
    operator=(const RWTFunctorR0<SR>& second);

    /**
     * Assignment operator. Detaches this handle instance from any functor
     * body instance it currently references, and binds it to the functor
     * body instance, if any, associated with the \a second handle instance.
     */
    RWTFunctorR0<SR>&
    operator=(const RWTFunctor<SR()>& second);

    /**
     * Gets a reference for the body instance, if any, otherwise throws an
     * exception.
     *
     * \exception RWTHRInvalidPointer
     * Thrown if the handle has no associated body.
     *
     * \exception std::bad_cast
     * Thrown if the body is not of type RWTFunctorR0Imp.
     */
    RWTFunctorR0Imp<SR>&
    body(void) const;

};

template <class SR>
inline RWTFunctorR0Imp<SR>&
RWTFunctorR0<SR>::body(void) const
{
    // Throws RWTHRInvalidPointer if no imp assigned!
    return dynamic_cast<RWTFunctorR0Imp<SR>&>(RWHandleBase::body());
}

template <typename SR>
struct RWTIsFunctor<SR(), RWTFunctorR0<SR> > {
    static const bool value = true;
};

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR0.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR0_h__
