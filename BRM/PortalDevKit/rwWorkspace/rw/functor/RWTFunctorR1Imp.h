#ifndef __rw_functor_RWTFunctorR1Imp_h__
#define __rw_functor_RWTFunctorR1Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR1Imp.h#1 $
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
 * The body class for functors that are invoked with one caller argument
 * and return a value
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor.h>

#  define RWFunctorR1Imp RWTFunctorR1Imp

//-- Group: RWTFunctorR1Imp
//--
//-- Description:
//--   All body classes that take one caller argument at invocation time and
//--   return a value are derived from 'RWTFunctorR1Imp'.
//--
//--   Each derived class name has appended to it either a G (for global) or
//--   an M (for member), to indicate whether or not it is invoked upon on
//--   object (static member functions will use the G version since there is no
//--   object associated with the call).
//--
//--   The class name may also have A1 or A2 appended to it, to indicate
//--   that it takes callee arguments at construction time (these arguments
//--   are stored and added to the caller argument at invocation time).
//--
//--   The 6 concrete class names are:
//--      'RWTFunctorR1GImp'          -- no 'this' object, no callee arguments
//--      'RWTFunctorR1GA1Imp'        -- no 'this' object, one callee argument
//--      'RWTFunctorR1GA2Imp'        -- no 'this' object, two callee arguments
//--      'RWTFunctorR1MImp'          -- has 'this' object, but no callee arguments
//--      'RWTFunctorR1MA1Imp'        -- has 'this' object, and one callee argument
//--      'RWTFunctorR1MA2Imp'        -- has 'this' object, and two callee arguments
//--
//--   These concrete classes are templatized on the signature of the
//--   function that is encapsulated, as well as on the signature of the functor
//--   invocation.
//--
//--   The template parameters are:
//--      SR -- the type of the caller return value at invocation
//--      S1 -- the type of the caller argument at invocation
//--      DR -- the declared return type of the encapsulated function
//--      D1 -- the declared type of the encapsulated function's first argument.
//--      A1 -- the type of the first callee argument (the function's second
//--            declared argument).
//--      A2 -- the type of the second callee argument (the function's third
//--            declared argument).
//--
//--
//-- Example:
//--   int next(int x){ return x++;  }
//--   int add(int x, int y, int z){ return x + y + z;  }
//--
//--   int main () {
//--
//--        // Create a RWTFunctorR1 with one callee argument and a return value.
//--     RWTFunctorR1 functor1 = rwtMakeFunctorR1( (int(*)(int)0, next );
//--
//--        // Create a RWTFunctorR1 with one callee argument and a return value.
//--     RWTFunctorR1 functor2 = rwtMakeFunctorR1( (int(*)(int)0, add, 12, 13);
//--
//--        // Invoking  functor1 will return 43.
//--     int next_value = functor1(42);
//--
//--        // Invoking  functor2 will add 12 to 13 to 36.
//--     int result = functor2(36);
//--
//--     return 0;
//--   }
//--

/**
 * \ingroup functor_module
 *
 * \deprecated
 * As of SourcePro 12.5, use RWTFunctor<SR(S1)> instead.
 *
 * \brief
 * Deprecated. Abstract base class for the family of functor bodies that are
 * invoked with one caller argument and return a value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * RWTFunctorR1Imp is the abstract base class for the family of functor
 * bodies that take one caller argument at invocation time and return a
 * value.
 *
 * Each derived class name appends either a<b><em>G</em></b> (for global) or
 * an <b><em>M</em></b> (for member), to indicate whether it is invoked upon
 * an object. Static member functions use the <b><em>G</em></b> version
 * since there is no object associated with the call.
 *
 * The class name may also append <b><em>A1</em></b> or <b><em>A2</em></b>
 * to indicate that it takes callee arguments at construction time. These
 * arguments are stored and added to the caller argument at invocation time.
 *
 * The six concrete class names are:
 *
 * - \b RWTFunctorR1GImp<SR,S1,DR,D1>
 *   - No \c this object, no callee arguments
 *
 * - \b RWTFunctorR1GA1Imp<SR,S1,DR,D1,A1>
 *   - No \c this object, one callee argument
 *
 * - \b RWTFunctorR1GA2Imp<SR,S1,DR,D1,A1,A2>
 *   - No \c this object, two callee arguments
 *
 * - \b RWTFunctorR1MImp<SR,S1,Callee,DR,D1>
 *   - Has \c this object, but no callee arguments
 *
 * - \b RWTFunctorR1MA1Imp<SR,S1,Callee,D1,DR,A1>
 *   - Has \c this object, and one callee argument
 *
 * - \b RWTFunctorR1MA2Imp<SR,S1,Callee,DR,D1,A1,A2>
 *   - Has \c this object, and two callee arguments
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
 * - \c S1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the first functor
 * signature argument
 *
 * - \c Callee&nbsp; The class type that declares a member function
 *
 * - \c DR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The return type of the function;
 * the compiler must be able to convert this to the \c SR type
 *
 * - \c D1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the first function
 * signature argument; the compiler must be able to convert to this from the
 * \c S1 type
 *
 * - \c A1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the first client data
 * argument
 *
 * - \c A2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the second client data
 * argument
 *
 * The \c make() function is the only member of these functor classes that
 * is intended to be accessed directly; it is often called through one of
 * the rwtMakeFunctorR1() convenience mechanisms. All other members must be
 * accessed through an RWTFunctorR1 handle.
 *
 * \example
 * \code
 * #include <rw/functor/RWTFunctorR1GImp.h>
 * int foo(float);
 *
 * int main(void)
 * {
 *     // Create a functor that calls foo():
 *     RWTFunctorR1<int, float> func;
 *     func = RWTFunctorR1GImp<int, float, int, float>::make(foo);
 *     // Invoke Functor
 *     int result = func(7.0);
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * rwtMakeFunctorR1(), RWTFunctorR1
 */
template <class SR, class S1>
class RW_DEPRECATE_TYPE("Use RWTFunctor<SR(S1)> instead") RWTFunctorR1Imp
    : public RWTFunctorImpBase1<SR, S1>
{

public:

    // The signature of the functor invocation.
    typedef SR(*CallerSignature)(S1);

    // The type of the caller return value.
    typedef SR SRType;

    // The type of the caller argument.
    typedef S1 S1Type;
};

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR1Imp_h__
