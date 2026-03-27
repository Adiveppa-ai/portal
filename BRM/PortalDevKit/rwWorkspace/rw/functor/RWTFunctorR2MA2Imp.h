#ifndef __rw_functor_RWTFunctorR2MA2Imp_h__
#define __rw_functor_RWTFunctorR2MA2Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR2MA2Imp.h#1 $
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
 * The body class for functors which are invoked with two caller arguments,
 * which have a return value that is used, and whose encapsulated function
 * is a member that takes two callee arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctorR2.h>
#include <rw/functor/RWTFunctorR2Imp.h>

#  define RWFunctorR2MA2Imp RWTFunctorR2MA2Imp
#  define rwMakeFunctorR2MA2 rwtMakeFunctorR2MA2

//-- Group: RWTFunctorR21Imp
//--
//-- Example:
//--
//--   class Foo{
//--      int bar(short s, long l, char c, float f){ return s; }
//--   };
//--
//--   int main () {
//--
//--        // Create callee object
//--     Foo f;
//--
//--        // Create an RWTFunctorR2 with two callee argument.
//--     RWTFunctorR2<int,short,long> functor =
//--        rwtMakeFunctorR2((int(*)(short,long))0, f, Foo::bar, 't', 3.14);
//--
//--        // Invoking 'functor' will call bar.
//--     int return_value = functor(3, 54321);
//--
//--     return 0;
//--   }
//--

template <class SR, class S1, class S2, class Callee, class DR, class D1, class D2, class A1, class A2>
class RWTFunctorR2MA2Imp : public RWTFunctorR2Imp<SR, S1, S2>
{

public:

    // Destructor
    ~RWTFunctorR2MA2Imp(void);

    // The signature of the functor invocation.
    typedef SR(*CallerSignature)(S1, S2);

    // The signature of the encapsulated function's invocation.
    typedef DR(Callee::*CalleeSignature)(D1, D2, A1, A2);

    // The type of the callee object.
    typedef Callee   CalleeType;

    // The return value of the functor.
    typedef SR SRType;

    // The type of the first caller argument.
    typedef S1 S1Type;

    // The type of the second caller argument.
    typedef S2 S2Type;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The declared type of the encapsulated function's first argument.
    typedef D1 D1Type;

    // The declared type of the encapsulated function's second argument.
    typedef D2 D2Type;

    // The type of the first callee argument.
    typedef A1 A1Type;

    // The type of the second callee argument.
    typedef A2 A2Type;

    //-- Creates a new RWTFunctorR2MA2Imp and returns an appropriate handle.
    static RWTFunctorR2<SR, S1, S2>
    make(Callee& callee, CalleeSignature function, A1 a1, A2 a2);

    // Invoke the encapsulated function, passing in the callee argument.
    virtual SR
    run(S1 s1, S2 s2) const;

protected:

    // Constructor, only for internal use.
    RWTFunctorR2MA2Imp(Callee& callee, CalleeSignature function, A1 a1, A2 a2);

private:

    RWTFunctorR2MA2Imp(const RWTFunctorR2MA2Imp& second);

    RWTFunctorR2MA2Imp&
    operator=(const RWTFunctorR2MA2Imp& second);

private:
    // The callee.
    Callee&           callee_;

    // The encapsulated function.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
    A2                a2_;
};


//-- A macro for ease of use in creating new 'RWTFunctorR2MA2Imp' bodies.

/**
 * \ingroup functorR2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2, a1, a2)" instead.
 *
 * Macro to create an RWTFunctorR2 set to call
 * <tt>callee.function(s1,s2,a1,a2)</tt>. \a function must have signature
 * <tt>DR (Caller::*)(D1,D2,A1,A2)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeFunctorR2MA2", "Use rwBind() instead")
#define rwtMakeFunctorR2MA2(SR,S1,S2,Callee,callee,DR,function,D1,D2,A1,a1,A2,a2) \
   RWTFunctorR2MA2Imp<SR,S1,S2,Callee,DR,D1,D2,A1,A2 >::make(callee,function,a1,a2)

template <class SR, class S1, class S2, class Callee, class DR, class D1, class D2, class A1, class A2>
inline RWTFunctorR2<SR, S1, S2>
RWTFunctorR2MA2Imp<SR, S1, S2, Callee, DR, D1, D2, A1, A2>::make(Callee& callee, CalleeSignature function,
        A1 a1, A2 a2)
{
    return new RWTFunctorR2MA2Imp<SR, S1, S2, Callee, DR, D1, D2, A1, A2>(callee, function, a1, a2);
}

template <class SR, class S1, class S2, class Callee, class DR, class D1, class D2, class A1, class A2>
inline
RWTFunctorR2MA2Imp<SR, S1, S2, Callee, DR, D1, D2, A1, A2>::RWTFunctorR2MA2Imp(Callee& callee,
        CalleeSignature function,
        A1 a1, A2 a2)
    : callee_(callee),
      function_(function),
      a1_(a1),
      a2_(a2)
{
}

template <class SR, class S1, class S2, class Callee, class DR, class D1, class D2, class A1, class A2>
inline
RWTFunctorR2MA2Imp<SR, S1, S2, Callee, DR, D1, D2, A1, A2>::~RWTFunctorR2MA2Imp(void)
{
}


#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR2MA2Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR2MA2Imp_h__
