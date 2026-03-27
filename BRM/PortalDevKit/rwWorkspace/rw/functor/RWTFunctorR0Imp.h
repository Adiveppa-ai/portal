#ifndef __rw_functor_RWTFunctorR0Imp_h__
#define __rw_functor_RWTFunctorR0Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR0Imp.h#1 $
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
 * The body class for functors which are invoked with no caller arguments
 * but that do return a value.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor.h>

#  define RWFunctorR0Imp RWTFunctorR0Imp

//-- Group: RWTFunctorR0Imp
//--
//-- Description:
//--   All body classes that take no caller arguments at invocation time, but
//--   that do return a value, are derived from 'RWTFunctorR0Imp'.
//--
//--   Each derived class name has appended to it either a G (for global) or
//--   an M (for member), to indicate whether or not it is invoked upon on
//--   object (static member functions will use the G version since there is no
//--   object associated with the call).
//--
//--   The class name may also have A1, A2 or A3 appended to it, to indicate
//--   that it takes callee arguments at construction time (these arguments
//--   are stored and added to the caller argument at invocation time).
//--
//--   The 8 concrete class names are:
//--      'RWTFunctorR0GImp'        -- no 'this' object, no callee arguments
//--      'RWTFunctorR0GA1Imp'      -- no 'this' object, one callee argument
//--      'RWTFunctorR0GA2Imp'      -- no 'this' object, two callee arguments
//--      'RWTFunctorR0GA2Imp'      -- no 'this' object, three callee arguments
//--      'RWTFunctorR0MImp'        -- has 'this' object, but no callee arguments
//--      'RWTFunctorR0MA1Imp'      -- has 'this' object, and one callee argument
//--      'RWTFunctorR0MA2Imp'      -- has 'this' object, and two callee arguments
//--      'RWTFunctorR0MA2Imp'      -- has 'this' object, and three callee arguments
//--
//--   These concrete classes are templatized on the signature of the
//--   function that is encapsulated, as well as on the signature of the functor
//--   invocation.
//--
//--   The template parameters are:
//--      SR -- the type of the caller return value at invocation
//--      DR -- the declared return type of the encapsulated function
//--      A1 -- the type of the first callee argument
//--      A2 -- the type of the second callee argument
//--
//--
//-- Example:
//--   int base(){ return 10;  }
//--   int mult(int x, int y){ return x + y;  }
//--
//--   int main () {
//--
//--        // Create a RWTFunctorR0 with no callee arguments.
//--     RWTFunctorR0 functor1 = rwtMakeFunctorR0( (int(*)()0, base );
//--
//--        // Create a RWTFunctor1 with 1 callee arg and an ignored return value.
//--     RWTFunctorR0 functor2 = rwtMakeFunctorR0( (void(*)()0, mult, 12, 13);
//--
//--        // Invoking  functor1 will return 10.
//--     int base = functor1();
//--
//--        // Invoking  functor2 will add 12 to 13 and return 25.
//--     int result = functor2();
//--
//--     return 0;
//--   }
//--

/**
 * \ingroup functor_module
 *
 * \deprecated
 * As of SourcePro 12.5, use RWTFunctor<R(As...)> instead.
 *
 * \brief
 * Deprecated. Abstract base class for the family of functor bodies that
 * take no caller arguments at invocation time and return a value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * Class RWTFunctorR0Imp is the abstract base class for the family of
 * functor bodies that take no caller arguments at invocation time and
 * return a value.
 *
 * Each derived class name appends either a <b><em>G</em></b> (for global)
 * or an <b><em>M</em></b> (for member), to indicate whether it is invoked
 * upon an object. Static member functions use the <b><em>G</em></b> version
 * since there is no object associated with the call.
 *
 * The class name may also append <b><em>A1</em></b>, <b><em>A2</em></b>, or
 * <b><em>A3</em></b>, to indicate that it takes callee arguments at
 * construction time. These arguments are stored and added to the caller
 * argument at invocation time.
 *
 * The eight concrete class names are:
 * - \b RWTFunctorR0GImp<SR,DR>
 *   - No \c this object, no callee arguments
 * - \b RWTFunctorR0GA1Imp<SR,DR,A1>
 *   - No \c this object, one callee argument
 * - \b RWTFunctorR0GA2Imp<SR,DR,A1,A2>
 *   - No \c this object, two callee arguments
 * - \b RWTFunctorR0GA3Imp<SR,DR,A1,A2,A3>
 *   - No \c this object, three callee arguments
 * - \b RWTFunctorR0MImp<SR,Callee,DR>
 *   - Has \c this object, no callee arguments
 * - \b RWTFunctorR0MA1Imp<SR,Callee,DR,A1>
 *   - Has \c this object, and one callee argument
 * - \b RWTFunctorR0MA2Imp<SR,Callee,DR,A1,A2>
 *   - Has \c this object, and two callee arguments
 * - \b RWTFunctorR0MA3Imp<SR,Callee,DR,A1,A2,A3>
 *   - Has \c this object, and three callee arguments
 *
 * These concrete classes are templatized on the signature of the function
 * that is encapsulated, as well as on the signature of the functor
 * invocation.
 *
 * The template parameters describe the invocation signature of the functor
 * and the function call it encapsulates. These parameters are:
 *
 * - \c SR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The return type of the functor
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
 * The \c make() function is the only member of these functor classes that
 * is intended to be accessed directly; it is often called through one of
 * the rwtMakeFunctorR0() convenience mechanisms. All other members must be
 * accessed through an RWTFunctorR0 handle.
 *
 * \example
 * \code
 * #include <rw/functor/RWTFunctorR0GA1Imp.h>
 *
 * float foo(int);
 *
 * int main(void)
 * {
 *     // Create a functor that calls foo(7):
 *     RWTFunctorR0<float> func =
 *         RWTFunctorR0GA1Imp<float, float, int>::make(foo, 7);
 *     // Invoke Functor
 *     float result = func();
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * rwtMakeFunctorR0(), RWTFunctorR0
 */
template <class SR>
class RW_DEPRECATE_TYPE("Use RWTFunctor<SR()> instead") RWTFunctorR0Imp
    : public RWTFunctorImpBase0<SR>
{

public:

    // The signature of the functor invocation.
    typedef SR(*CallerSignature)(void);

    // The type of the caller return value.
    typedef SR SRType;

};

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR0Imp_h__
