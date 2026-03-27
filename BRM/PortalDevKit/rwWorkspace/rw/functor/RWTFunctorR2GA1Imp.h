#ifndef __rw_functor_RWTFunctorR2GA1Imp_h__
#define __rw_functor_RWTFunctorR2GA1Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR2GA1Imp.h#1 $
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
 * is a global that takes one callee argument.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctorR2.h>
#include <rw/functor/RWTFunctorR2Imp.h>

#  define RWFunctorR2GA1Imp RWTFunctorR2GA1Imp
#  define rwMakeFunctorR2GA1 rwtMakeFunctorR2GA1

//-- Group: RWTFunctorR21Imp
//--
//-- Example:
//--   int foo(short s, long l, char c){ s *= l; return s *= c; }
//--
//--   int main () {
//--
//--        // Create an RWTFunctorR2 with one callee argument.
//--     RWTFunctorR2<int,short,long> functor =
//--        rwtMakeFunctorR2((int(*)(short,long))0, foo, 't');
//--
//--        // Invoking 'functor' will call foo.
//--     int return_value = functor(3, 8675);
//--
//--     return 0;
//--   }
//--

template <class SR, class S1, class S2, class DR, class D1, class D2, class A1>
class RWTFunctorR2GA1Imp : public RWTFunctorR2Imp<SR, S1, S2>
{

public:

    // Destructor
    ~RWTFunctorR2GA1Imp(void);

    // The signature of the functor invocation.
    typedef SR(*CallerSignature)(S1, S2);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(D1, D2, A1);

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

    // The type of the callee argument.
    typedef A1 A1Type;

    //-- Creates a new RWTFunctorR2GA1Imp and returns an appropriate handle.
    static RWTFunctorR2<SR, S1, S2>
    make(CalleeSignature function, A1 a1);

    // Invoke the encapsulated function, passing in the callee argument.
    virtual SR
    run(S1 s1, S2 s2) const;

protected:

    // Constructor, only for internal use.
    RWTFunctorR2GA1Imp(CalleeSignature function, A1 a1);

private:

    RWTFunctorR2GA1Imp(const RWTFunctorR2GA1Imp& second);

    RWTFunctorR2GA1Imp&
    operator=(const RWTFunctorR2GA1Imp& second);

private:

    // The encapsulated function.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
};


//-- A macro for ease of use in creating new 'RWTFunctorR2GA1Imp' bodies.

/**
 * \ingroup functorR2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, rw2, a1)"
 * instead.
 *
 * Macro to create an RWTFunctorR2 set to call <tt>function(s1,s2,a1)</tt>.
 * \a function must have signature <tt>DR (*)(D1,D2,A1)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeFunctorR2GA1", "Use rwBind() instead")
#define rwtMakeFunctorR2GA1(SR,S1,S2,DR,function,D1,D2,A1,a1) \
   RWTFunctorR2GA1Imp<SR,S1,S2,DR,D1,D2,A1 >::make(function,a1)

template <class SR, class S1, class S2, class DR, class D1, class D2, class A1>
inline RWTFunctorR2<SR, S1, S2>
RWTFunctorR2GA1Imp<SR, S1, S2, DR, D1, D2, A1>::make(CalleeSignature function, A1 a1)
{
    return new RWTFunctorR2GA1Imp<SR, S1, S2, DR, D1, D2, A1>(function, a1);
}

template <class SR, class S1, class S2, class DR, class D1, class D2, class A1>
inline
RWTFunctorR2GA1Imp<SR, S1, S2, DR, D1, D2, A1>::RWTFunctorR2GA1Imp(CalleeSignature function, A1 a1)
    : function_(function),
      a1_(a1)
{
}

template <class SR, class S1, class S2, class DR, class D1, class D2, class A1>
inline
RWTFunctorR2GA1Imp<SR, S1, S2, DR, D1, D2, A1>::~RWTFunctorR2GA1Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR2GA1Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR2GA1Imp_h__
