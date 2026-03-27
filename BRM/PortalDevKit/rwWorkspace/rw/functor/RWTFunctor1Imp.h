#ifndef __rw_functor_RWTFunctor1Imp_h__
#define __rw_functor_RWTFunctor1Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor1Imp.h#1 $
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
 * The body class for functors that are invoked with one caller argument.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor.h>

#  define RWFunctor1Imp RWTFunctor1Imp

//-- Group: RWTFunctor1Imp
//--
//--   The  body classes for functors which are invoked with one caller argument.
//--
//--   All body classes which take one caller argument at invocation time are
//--   derived from 'RWTFunctor1Imp'.
//--
//--   Each derived class name has appended to it either a G (for global) or
//--   an M (for member), to indicate whether or not it is invoked upon on
//--   object (static member functions will use the G version since there is no
//--   object associated with the call).
//--
//--   The class name may also have A1 or A2 appended to it, to indicate
//--   that it takes callee arguments at construction time (these arguments
//--   are stored in the functor body and then added to the caller argument
//--   at invocation time).
//--
//--   The 6 concrete class names are:
//--      'RWTFunctor1GImp'          -- no 'this' object, no callee arguments
//--      'RWTFunctor1GA1Imp'        -- no 'this' object, one callee argument
//--      'RWTFunctor1GA2Imp'        -- no 'this' object, two callee arguments
//--      'RWTFunctor1MImp'          -- has 'this' object, but no callee arguments
//--      'RWTFunctor1MA1Imp'        -- has 'this' object, and one callee argument
//--      'RWTFunctor1MA2Imp'        -- has 'this' object, and two callee arguments
//--
//--
//--   These concrete classes are templatized on the signature of the
//--   function, which is encapsulated, as well as on the signature of
//--   the functor invocation.
//--
//--   The template parameters are:
//--      S1 -- The type of the caller argument passed to the functor at the time
//--            of invocation.
//--      DR -- The declared return type of the encapsulated function (a function
//--            with a return value may be encapsulated in a 'RWTFunctor1Imp',
//--            but when invoked, the return value will be ignored.  If the return
//--            value of the function is important, look at the 'RWTFunctorR1' group
//--            group of classes.
//--      D1 -- The declared type of the encapsulated function's first argument.
//--      A1 -- The type of the first stored callee argument (the function's second
//--            declared argument).
//--      A2 -- The type of the second stored callee argument (the function's third
//--            declared argument).
//--

/**
 * \ingroup functor_module
 *
 * \deprecated
 * As of SourcePro 12.5, use RWTFunctor<void(S1)> instead.
 *
 * \brief
 * Deprecated. Abstract base class for the family of functor bodies that are
 * invoked with one argument and return no value.
 *
 * A function object, or a functor, encapsulates a call to an associated
 * global or member function. When a functor is invoked, it calls the
 * associated function.
 *
 * RWTFunctor1Imp is the abstract base class for the family of functor
 * bodies that are invoked with one argument and return no value.
 *
 * Each derived class name appends either a <b><em>G</em></b> (for global)
 * or an <b><em>M</em></b> (for member), to indicate whether it is invoked
 * upon an object. Static member functions use the <b><em>G</em></b> version
 * since there is no object associated with the call.
 *
 * The class name may also append <b><em>A1</em></b> or <b><em>A2</em></b>,
 * to indicate at construction that it takes callee arguments. These
 * arguments are stored in the functor body and then added to the caller
 * argument at invocation time.
 *
 * The six concrete class names are:
 *
 * - \b RWTFunctor1GImp<S1,DR,D1>
 *   - No \c this object, no callee arguments
 *
 * - \b RWTFunctor1GA1Imp<S1,DR,D1,A1>
 *   - No \c this object, one callee argument
 *
 * - \b RWTFunctor1GA2Imp<S1,DR,D1,A1,A2>
 *   - No \c this object, one callee argument
 *
 * - \b RWTFunctor1MImp<S1,Callee,DR,D1>
 *   - Has \c this object, but no callee arguments
 *
 * - \b RWTFunctor1MA1Imp<S1,Callee,D1,DR,A1>
 *   - Has \c this object, and one callee argument
 *
 * - \b RWTFunctor1MA2Imp<S1,Callee,DR,D1,A1,A2>
 *   - Has \c this object, and two callee arguments
 *
 * These concrete classes are templatized on the signature of the function
 * that is encapsulated, as well as on the signature of the functor
 * invocation.
 *
 * The template parameters describe the invocation signature of the functor
 * and the function call it encapsulates. These parameters are:
 *
 * - \c S1&nbsp; The type of the first functor signature argument
 *
 * - \c Callee&nbsp; The class type that declares a member function
 *
 * - \c DR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The return type of the function
 *
 * - \c D1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the first function
 * signature argument; the compiler must be able to convert to this from the
 * \c S1 type.
 *
 * - \c A1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the first client data
 * argument
 *
 * - \c A2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The type of the second client data
 * argument
 *
 * The \c make() function is the only member of these functor classes that
 * is intended to be accessed directly; it is often called through one of
 * the rwtMakeFunctor1() convenience mechanisms. All other members must be
 * accessed through an RWTFunctor1 handle.
 *
 * \example
 * \code
 * #include <rw/functor/RWTFunctor1GImp.h>
 *
 * void foo(int);
 *
 * int main(void)
 * {
 *     // Create a functor that calls foo():
 *     RWTFunctor1<int> func = RWTFunctor1GImp<int, void, int>::make(foo);
 *     // Invoke Functor
 *     func(7);
 *
 *     return 0;
 * }
 * \endcode
 * \endexample
 *
 * \sa
 * rwtMakeFunctor1(), RWTFunctor1
 */
template <class S1>
class RW_DEPRECATE_TYPE("Use RWTFunctor<void(S1)> instead") RWTFunctor1Imp
    : public RWTFunctorImpBase1<void, S1>
{

public:

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(S1);

    // The type of the caller argument.
    typedef S1 S1Type;

};

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_RWTFunctor1Imp_h__
