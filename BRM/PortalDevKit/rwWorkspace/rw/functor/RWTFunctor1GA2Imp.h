#ifndef __rw_functor_RWTFunctor1GA2Imp_h__
#define __rw_functor_RWTFunctor1GA2Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor1GA2Imp.h#1 $
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
 * The body class for functors that are invoked with one caller argument,
 * and that encapsulate a global function taking two callee arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor1.h>
#include <rw/functor/RWTFunctor1Imp.h>

#  define RWFunctor1GA2Imp RWTFunctor1GA2Imp
#  define rwMakeFunctor1GA2 rwtMakeFunctor1GA2

//-- Group: RWTFunctor1Imp
//--   Please see RWTFunctor1Imp for more information on this group of classes.
//--
//-- Example:
//--   void printNums(int i, float f, short s){
//--      cout << "i is " << i << ", f is " << f << ", s is " << s<< endl;
//--    }
//--
//--   int main () {
//--
//--        // Create an RWTFunctor1 with two callee arguments.
//--     RWTFunctor1<int> functor = rwtMakeFunctor1(
//--            (void(*)(int))0, printNums, 3.14, 7 );
//--
//--        // Invoking 'functor' will print 'i is 14, f is 3.14, s is 7'.
//--     functor(14);
//--
//--     return 0;
//--   }
//--

template <class S1, class DR, class D1, class A1, class A2>
class RWTFunctor1GA2Imp : public RWTFunctor1Imp<S1>
{

public:

    // Destructor
    ~RWTFunctor1GA2Imp(void);

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(S1);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(D1, A1, A2);

    // The type of the caller argument.
    typedef S1 S1Type;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The declared type of the encapsulated function's first argument.
    typedef D1 D1Type;

    // The type of the first callee argument.
    typedef A1 A1Type;

    // The type of the second callee argument.
    typedef A2 A2Type;

    //-- Creates a new RWTFunctor1GA2Imp and returns an appropriate handle.
    static RWTFunctor1<S1>
    make(CalleeSignature function, A1 a1, A2 a2);

    // Invoke the encapsulated function passing it the s1 argument.
    // (caller data) as well as both stored callee arguments.
    virtual void
    run(S1 s1) const;

protected:
    // The RWTFunctor1GA2Imp constructor--only for internal use.
    RWTFunctor1GA2Imp(CalleeSignature function, A1 a1, A2 a2);

private:

    RWTFunctor1GA2Imp(const RWTFunctor1GA2Imp& second);

    RWTFunctor1GA2Imp&
    operator=(const RWTFunctor1GA2Imp& second);

private:
    // The encapsulated function.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
    A2                a2_;
};


//-- A macro for ease of use in creating new 'RWTFunctor1GA2Imp' bodies.

/**
 * \ingroup functor1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, a1, a2)"
 * instead.
 *
 * Macro to create an RWTFunctor1 set to call <tt>function(s,a1,a2)</tt>.
 * \a function must have signature <tt>DR (*)(D1,A1,A2)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor1GA2", "Use rwBind() instead")
#define rwtMakeFunctor1GA2(S1,DR,function,D1,A1,a1,A2,a2) \
   RWTFunctor1GA2Imp<S1,DR,D1,A1,A2 >::make(function,a1,a2)

template <class S1, class DR, class D1, class A1, class A2>
inline RWTFunctor1<S1>
RWTFunctor1GA2Imp<S1, DR, D1, A1, A2>::make(CalleeSignature function,
        A1 a1, A2 a2)
{
    return new RWTFunctor1GA2Imp<S1, DR, D1, A1, A2>(function, a1, a2);
}

template <class S1, class DR, class D1, class A1, class A2>
inline
RWTFunctor1GA2Imp<S1, DR, D1, A1, A2>::RWTFunctor1GA2Imp(CalleeSignature function,
        A1 a1, A2 a2)
    : function_(function),
      a1_(a1),
      a2_(a2)
{
}

template <class S1, class DR, class D1, class A1, class A2>
inline
RWTFunctor1GA2Imp<S1, DR, D1, A1, A2>::~RWTFunctor1GA2Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor1GA2Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_RWTFunctor1GA2Imp_h__
