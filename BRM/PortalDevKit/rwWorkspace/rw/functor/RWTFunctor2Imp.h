#ifndef __rw_functor_RWTFunctor2Imp_h__
#define __rw_functor_RWTFunctor2Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor2Imp.h#1 $
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
 * The body class for functors that are invoked with two caller arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor.h>

#  define RWFunctor2Imp RWTFunctor2Imp

//-- Group: RWTFunctor2Imp
//--
//--   The body classes for functors that are invoked with two caller arguments.
//--
//--   All body classes that take two caller arguments at invocation time are
//--   derived from 'RWTFunctor2Imp'.
//--
//--   Each derived class name has appended to it either a G (for global) or
//--   an M (for member), to indicate whether or not it is invoked upon on
//--   object. (Static member functions will use the G version since there is no
//--   object associated with the call.)
//--
//--   The class name may also have A1 or A2 appended to it, to indicate
//--   that it takes callee arguments at construction time (these arguments
//--   are stored and added to the caller arguments at invocation time).
//--
//--   The 6 concrete class names are:
//--      'RWTFunctor1GImp'          -- no 'this' object, no callee arguments
//--      'RWTFunctor1GA1Imp'        -- no 'this' object, one callee argument
//--      'RWTFunctor1GA2Imp'        -- no 'this' object, two callee arguments
//--      'RWTFunctor1MImp'          -- has 'this' object, but no callee arguments
//--      'RWTFunctor1MA1Imp'        -- has 'this' object, and one callee argument
//--      'RWTFunctor1MA2Imp'        -- has 'this' object, and two callee arguments
//--
//--   These concrete classes are templatized on the signature of the
//--   function which is encapsulated, as well as the signature of the functor
//--   invocation.
//--
//--   The template parameters are:
//--      S1 -- the type of the first caller argument at invocation.
//--      S1 -- the type of the second caller argument at invocation.
//--      DR -- the declared return type of the encapsulated function (ignored).
//--      D1 -- the declared type of the encapsulated function's first argument.
//--      D2 -- the declared type of the encapsulated function's second argument.
//--      A1 -- the type of the first callee argument (the function's third
//--            declared argument.
//--      A2 -- the type of the second callee argument (the function's fourth
//--            declared argument.
//--
//--
//-- Example:
//--   void print(int x, int y){ cout << "x is " << x  << " y is " << y << endl; }
//--   float math(int x, int y, float z ){ return x + y * z;  }
//--
//--   int main () {
//--
//--        // Create an RWTFunctor2 with no callee arguments and no return value.
//--     RWTFunctor2 functor1 = rwtMakeFunctor2( (void(*)(int, int)0, print );
//--
//--        // Create an RWTFunctor1 with 1 callee argument and an ignored return value.
//--     RWTFunctor2 functor2 = rwtMakeFunctor2( (void(*)(int,int)0,
//--                                             math, 12.4 );
//--
//--        // invoking  functor1 will print 42 and 64
//--     functor1(42, 64);
//--
//--        // invoking  functor2 will add 12 to 36 and multiply by 12.4
//--     functor2(12,36);
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
 * Deprecated. Abstract base class for the family of functor bodies that are
 * invoked with two caller arguments and whose invocation returns no value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * RWTFunctor2Imp is the abstract base class for the family of functor
 * bodies that are invoked with two caller arguments, and whose invocation
 * returns no value.
 *
 * Each derived class name appends either a <b><em>G</em></b> (for global)
 * or an <b><em>M</em></b> (for member), to indicate whether it is invoked
 * upon an object. Static member functions use the <b><em>G</em></b> version
 * since there is no object associated with the call.
 *
 * The class name may also append <b><em>A1</em></b> or <b><em>A2</em></b>,
 * to indicate at construction that it takes callee arguments. These
 * arguments are stored and added to the caller arguments at invocation
 * time.
 *
 * The six concrete class names are:
 *
 * - \b RWTFunctor2GImp<S1,S2,DR,D1,D2>
 *   - No \c this object, no callee arguments
 *
 * - \b RWTFunctor2GA1Imp<S1,S2,DR,D1,D2,A1>
 *   - No \c this object, one callee argument
 *
 * - \b RWTFunctor2GA2Imp<S1,S2,DR,D1,D2,A1,A2>
 *   - No \c this object, two callee arguments
 *
 * - \b RWTFunctor2MImp<S1,S2,Callee,DR,D1,D2>
 *   - Has \c this object, but no callee arguments
 *
 * - \b RWTFunctor2MA1Imp<S1,S2,Callee,D1,D2,DR,A1>
 *   - Has \c this object, one callee arguments
 *
 * - \b RWTFunctor2MA2Imp<S1,S2,Callee,DR,D1,D2,A1,A2>
 *   - Has \c this object, two callee arguments These concrete classes are
 *   templatized on the signature of the function that is encapsulated, as
 *   well as the signature of the functor invocation.
 *
 * The template parameters describe the invocation signature of the functor
 * and the function call it encapsulates. These parameters are:
 *
 * - \c S1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the first functor
 * signature argument
 *
 * - \c S2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the second functor
 * signature argument
 *
 * - \c Callee&nbsp; The class type that declares a member function
 *
 * - \c DR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The return type of the function
 *
 * - \c D1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the first function
 * signature argument; the compiler must be able to convert to this from the
 * \c S1 type.
 *
 * - \c D2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the second function
 * signature argument; the compiler must be able to convert to this from the
 * \c S2 type.
 *
 * - \c A1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the first client data
 * argument
 *
 * - \c A2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the second client data
 * argument
 *
 * The \c make() function is the only member of these functor classes that
 * is intended to be accessed directly; it is often called through one of
 * the rwtMakeFunctor2() convenience mechanisms. All other members must be
 * accessed through an RWTFunctor2 handle.
 *
 * \example
 * \code
 * #include <rw/functor/RWTFunctor2GImp.h>
 *
 * void foo(int, float);
 *
 * int main(void)
 * {
 *     // Create a functor that calls foo():
 *     RWTFunctor2<int, float> func =
 *         RWTFunctor2GImp<int, float, void, int, float>::make(foo);
 *     // Invoke functor
 *     func(7, 1.0);
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * rwtMakeFunctor2(), RWTFunctor2
 */
template <class S1, class S2>
class RW_DEPRECATE_TYPE("Use RWTFunctor<void(S1, S2)> instead") RWTFunctor2Imp
    : public RWTFunctorImpBase2<void, S1, S2>
{

public:

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(S1, S2);

    // The type of the first caller argument.
    typedef S1 S1Type;

    // The type of the second caller argument.
    typedef S2 S2Type;
};

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_RWTFunctor2Imp_h__
