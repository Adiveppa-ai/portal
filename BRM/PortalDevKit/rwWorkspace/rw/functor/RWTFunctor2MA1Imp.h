#ifndef __rw_functor_RWTFunctor2MA1Imp_h__
#define __rw_functor_RWTFunctor2MA1Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor2MA1Imp.h#1 $
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
 * The body class for functors that are invoked with two caller arguments,
 * and that encapsulate a member function taking one callee argument.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor2.h>
#include <rw/functor/RWTFunctor2Imp.h>

#  define RWFunctor2MA1Imp RWTFunctor2MA1Imp
#  define rwMakeFunctor2MA1 rwtMakeFunctor2MA1

//-- Group: RWTFunctor2Imp
//--   Please see RWTFunctor2Imp for more information on this group of classes.
//--
//-- Example:
//--   class foo{
//--      void bar(int i, short s, float f){ }
//--   };
//--
//--
//--   int main () {
//--
//--     foo f;
//--
//--        // Create an RWTFunctor2 with one callee argument.
//--     RWTFunctor2<int,short> functor =
//--         rwtMakeFunctor2((void(*)(int,short))0, f, &foo::bar, 3.14 );
//--
//--        // Invoking 'functor' will call bar.
//--     functor(14, 2);
//--
//--     return 0;
//--   }
//--

template <class S1, class S2, class Callee, class DR, class D1, class D2, class A1>
class RWTFunctor2MA1Imp : public RWTFunctor2Imp<S1, S2>
{

public:

    // Destructor
    ~RWTFunctor2MA1Imp(void);

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(S1, S2);

    // The signature of the encapsulated method's invocation.
    typedef DR(Callee::*CalleeSignature)(D1, D2, A1);

    // The type of the callee object.
    typedef Callee   CalleeType;

    // The type of the first caller argument.
    typedef S1 S1Type;

    // The type of the second caller argument.
    typedef S2 S2Type;

    // The declared type of the encapsulated method's return value.
    typedef DR DRType;

    // The declared type of the encapsulated method's first argument.
    typedef D1 D1Type;

    // The declared type of the encapsulated method's second argument.
    typedef D2 D2Type;

    // The type of the callee argument.
    typedef A1 A1Type;

    //-- Creates a new RWTFunctor2MA1Imp and returns an appropriate handle.
    static RWTFunctor2<S1, S2>
    make(Callee& callee, CalleeSignature function,
         A1 a1);

    // Invoke the encapsulated function passing in both the
    // caller arguments and the the stored callee argument.
    virtual void
    run(S1 s1, S2 s2) const;

protected:
    // The 'RWTFunctor2MA1Imp' constructor, only for internal use.
    RWTFunctor2MA1Imp(Callee& callee, CalleeSignature function, A1 a1);

private:

    RWTFunctor2MA1Imp(const RWTFunctor2MA1Imp& second);

    RWTFunctor2MA1Imp&
    operator=(const RWTFunctor2MA1Imp& second);


private:
    // The callee object.
    Callee&           callee_;

    // The encapsulated method.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
};


//-- A macro for ease of use in creating new 'RWTFunctor2MA1Imp' bodies.

/**
 * \ingroup functor2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2, a1)" instead.
 *
 * Macro to create an RWTFunctor2 set to call
 * <tt>callee.function(s1,s2,a1)</tt>. \a function must have signature
 * <tt>DR (Caller::*)(D1,D2,A1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor2MA1", "Use rwBind() instead")
#define rwtMakeFunctor2MA1(S1,S2,Callee,callee,DR,function,D1,D2,A1,a1) \
   RWTFunctor2MA1Imp<S1,S2,Callee,DR,D1,D2,A1 >::make(callee,function,a1)

template <class S1, class S2, class Callee, class DR, class D1, class D2, class A1>
inline RWTFunctor2<S1, S2>
RWTFunctor2MA1Imp<S1, S2, Callee, DR, D1, D2, A1>::make(Callee& callee,
        CalleeSignature function,
        A1 a1)
{
    return new RWTFunctor2MA1Imp<S1, S2, Callee, DR, D1, D2, A1>(callee, function, a1);
}

template <class S1, class S2, class Callee, class DR, class D1, class D2, class A1>
inline
RWTFunctor2MA1Imp<S1, S2, Callee, DR, D1, D2, A1>::RWTFunctor2MA1Imp(Callee& callee,
        CalleeSignature function,
        A1 a1)
    : callee_(callee),
      function_(function),
      a1_(a1)
{
}

template <class S1, class S2, class Callee, class DR, class D1, class D2, class A1>
inline
RWTFunctor2MA1Imp<S1, S2, Callee, DR, D1, D2, A1>::~RWTFunctor2MA1Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor2MA1Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_RWTFunctor2MA1Imp_h__
