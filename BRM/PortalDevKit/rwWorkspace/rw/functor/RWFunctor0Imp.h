#ifndef __rw_functor_RWFunctor0Imp_h__
#define __rw_functor_RWFunctor0Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWFunctor0Imp.h#1 $
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
 * The body class for functors that are invoked without any caller
 * arguments, and whose invocation returns no value.
 *
 *************************************************************************/

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
 * Deprecated. Abstract base class for functor body classes that are invoked
 * with no caller arguments and return no value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * Class RWFunctor0Imp is the abstract base class for functor bodies that
 * are invoked with no caller arguments and return no value. These functor
 * classes can accept up to three client data arguments at construction
 * time, which are passed to the function each time the functor is invoked.
 *
 * Each derived class name appends either a <b><em>G</em></b> (for global)
 * or an <b><em>M</em></b> (for member), to indicate whether it is invoked
 * upon an object. Static member functions use the <b><em>G</em></b> version
 * since there is no object associated with the call.
 *
 * The class name may also append <b><em>A1</em></b>, <b><em>A2</em></b>, or
 * <b><em>A3</em></b>, to indicate that it takes callee arguments at
 * construction time. These arguments are stored in the functor body and
 * passed to the function at invocation time.
 *
 * The eight concrete class names are:
 * - \b RWTFunctor0GImp<DR>
 *   - No \c this object, no callee arguments
 * - \b RWTFunctor0GA1Imp<DR,A1>
 *    - No \c this object, one callee argument
 * - \b RWTFunctor0GA2Imp<DR,A1,A2>
 *    - No \c this object, two callee arguments
 * - \b RWTFunctor0GA3Imp<DR,A1,A2,A3>
 *   - No \c this object, three callee arguments
 * - \b RWTFunctor0MImp<Callee,DR>
 *   - Has \c this object, but no callee arguments
 * - \b RWTFunctor0MA1Imp<Callee,DR,A1>
 *   - Has \c this object, and one callee argument
 * - \b RWTFunctor0MA2Imp<Callee,DR,A1,A2>
 *   - Has \c this object, and two callee arguments
 * - \b RWTFunctor0MA3Imp<Callee,DR,A1,A2,A3>
 *   - Has \c this object, and three callee arguments
 *
 * These concrete classes are templatized on the signature of the function
 * that is encapsulated, as well as on the signature of the functor
 * invocation.
 *
 * The template parameters describe the invocation signature of the functor
 * and the function call it encapsulates. These parameters are:
 *
 * - \c Callee&nbsp; The class type that declares a member function
 *
 * - \c DR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The return type of the function
 *
 * - \c A1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the first client data
 * argument
 *
 * - \c A2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the second client data
 * argument
 *
 * - \c A3&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the third client data
 * argument
 *
 * The \c make() function is the only member of these classes that is
 * intended to be accessed directly; it is often called through one of the
 * rwtMakeFunctor0() convenience mechanisms. All other members must be
 * accessed through an RWFunctor0 handle.
 *
 * \example
 * \code
 * #include <rw/functor/RWTFunctor0GA1Imp.h>
 *
 * void foo(int);
 *
 * int main(void)
 * {
 *     // Create a functor that calls foo(7):
 *     RWFunctor0 func = RWTFunctor0GA1Imp<void, int>::make(foo, 7);
 *     // Invoke Functor
 *     func();
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_DEPRECATE_TYPE("Use RWTFunctor<void()> instead") RW_FUNCTOR_GLOBAL RWFunctor0Imp: public RWTFunctorImpBase0<void>
{

public:

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(void);

};

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWFunctor0Imp_h__
