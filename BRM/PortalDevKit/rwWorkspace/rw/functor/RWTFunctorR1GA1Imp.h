#ifndef __rw_functor_RWTFunctorR1GA1Imp_h__
#define __rw_functor_RWTFunctorR1GA1Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR1GA1Imp.h#1 $
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
 * The body class for functors which are invoked with one caller argument,
 * which have a return value that is used, and whose encapsulated function
 * is a global that takes one callee argument.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctorR1.h>
#include <rw/functor/RWTFunctorR1Imp.h>

#  define RWFunctorR1GA1Imp RWTFunctorR1GA1Imp
#  define rwMakeFunctorR1GA1 rwtMakeFunctorR1GA1

//-- Group: RWTFunctorR1Imp
//--
//-- Example:
//--   int foo(short s, long l){ return s * l; }
//--
//--   int main () {
//--
//--        // Create an RWTFunctorR1 with one callee argument.
//--     RWTFunctorR1<int,short> functor = rwtMakeFunctorR1((int(*)(short))0, foo, 1234);
//--
//--        // Invoking 'functor' will call foo.
//--     int return_value = functor(3);
//--
//--     return 0;
//--   }
//--

template <class SR, class S1, class DR, class D1, class A1>
class RWTFunctorR1GA1Imp : public RWTFunctorR1Imp<SR, S1>
{

public:

    // Destructor
    ~RWTFunctorR1GA1Imp(void);

    // The signature of the functor invocation.
    typedef SR(*CallerSignature)(S1);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(D1, A1);

    // The return value of the functor.
    typedef SR SRType;

    // The type of the caller argument.
    typedef S1 S1Type;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The declared type of the encapsulated function's first argument.
    typedef D1 D1Type;

    // The type of the callee argument.
    typedef A1 A1Type;

    //-- Creates a new RWTFunctorR1GA1Imp and returns an appropriate handle.
    static RWTFunctorR1<SR, S1>
    make(CalleeSignature function, A1 a1);

    // Invoke the encapsulated function, passing in the callee argument.
    virtual SR
    run(S1 s1) const;

protected:

    // Constructor, only for internal use.
    RWTFunctorR1GA1Imp(CalleeSignature function, A1 a1);

private:

    RWTFunctorR1GA1Imp(const RWTFunctorR1GA1Imp& second);

    RWTFunctorR1GA1Imp&
    operator=(const RWTFunctorR1GA1Imp& second);

private:

    // The encapsulated function.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
};


//-- A macro for ease of use in creating new 'RWTFunctorR1GA1Imp' bodies.

/**
 * \ingroup functorR1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, a1)"
 * instead.
 *
 * Macro to create an RWTFunctorR1 set to call <tt>function(s,a1)</tt>.
 * \a function must have signature <tt>DR (*)(D1,A1)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeFunctorR1GA1", "Use rwBind() instead")
#define rwtMakeFunctorR1GA1(SR,S1,DR,function,D1,A1,a1) \
   RWTFunctorR1GA1Imp<SR,S1,DR,D1,A1 >::make(function,a1)

template <class SR, class S1, class DR, class D1, class A1>
inline RWTFunctorR1<SR, S1>
RWTFunctorR1GA1Imp<SR, S1, DR, D1, A1>::make(CalleeSignature function, A1 a1)
{
    return new RWTFunctorR1GA1Imp<SR, S1, DR, D1, A1>(function, a1);
}

template <class SR, class S1, class DR, class D1, class A1>
inline
RWTFunctorR1GA1Imp<SR, S1, DR, D1, A1>::RWTFunctorR1GA1Imp(CalleeSignature function, A1 a1)
    : function_(function),
      a1_(a1)
{
}

template <class SR, class S1, class DR, class D1, class A1>
inline
RWTFunctorR1GA1Imp<SR, S1, DR, D1, A1>::~RWTFunctorR1GA1Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR1GA1Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR1GA1Imp_h__
