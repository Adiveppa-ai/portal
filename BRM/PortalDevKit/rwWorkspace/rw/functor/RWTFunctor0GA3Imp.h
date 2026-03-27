#ifndef __rw_functor_RWTFunctor0GA3Imp_h__
#define __rw_functor_RWTFunctor0GA3Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor0GA3Imp.h#1 $
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
 * The body class for functors that take no caller arguments, and
 * encapsulate a global function that takes three callee arguments; the
 * return value of these functors can be ignored.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWFunctor0.h>
#include <rw/functor/RWFunctor0Imp.h>

#  define RWFunctor0GA3Imp RWTFunctor0GA3Imp
#  define rwMakeFunctor0GA3 rwtMakeFunctor0GA3

//-- Group: RWTFunctor0Imp
//--
//-- Example:
//--   long sum = 0;
//--   void addToSum(int x, short y, long z) { sum += x; sum += y; sum += z; }
//--
//--   int main () {
//--
//--        // Create an RWTFunctor0 with three callee arguments.
//--     RWFunctor0 functor = rwtMakeFunctor0( 0, addToSum, 8, 67, 5309 );
//--
//--        // Invoking 'functor' will add 8, 67 and 5309 to the current sum.
//--     functor();
//--
//--     return 0;
//--   }
//--

template <class DR, class A1, class A2, class A3>
class RWTFunctor0GA3Imp : public RWFunctor0Imp
{

public:

    // Destructor
    ~RWTFunctor0GA3Imp(void);

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(void);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(A1, A2, A3);

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The type of the first callee argument.
    typedef A1 A1Type;

    // The type of the second callee argument.
    typedef A2 A2Type;

    // The type of the third callee argument.
    typedef A3 A3Type;

    // Dynamically construct an instance of RWTFunctor0GA3Imp and bind it to
    // the returned RWFunctor0 handle instance.
    static RWFunctor0
    make(CalleeSignature function, A1 a1, A2 a2, A3 a3);

    // Invoke the encapsulated function passing in the callee arguments.
    virtual void
    run(void) const;

protected:
    // The 'RWTFunctor0GA3Imp' constructor, only for internal use.
    RWTFunctor0GA3Imp(CalleeSignature function, A1 a1, A2 a2, A3 a3);

private:

    RWTFunctor0GA3Imp(const RWTFunctor0GA3Imp& second);

    RWTFunctor0GA3Imp&
    operator=(const RWTFunctor0GA3Imp& second);

private:
    // The encapsulated function.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
    A2                a2_;
    A3                a3_;
};


//-- A macro for ease of use in creating new 'RWTFunctor0GA3Imp' bodies.

/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2, a3)"
 * instead.
 *
 * Macro to create an RWFunctor0 set to call <tt>function(a1,a2,a3)</tt>.
 * \a function must have signature <tt>DR (*)(A1,A2,A3)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor0GA3", "Use rwBind() instead")
#define rwtMakeFunctor0GA3(DR,function,A1,a1,A2,a2,A3,a3) \
   RWTFunctor0GA3Imp<DR,A1,A2,A3 >::make(function,a1,a2,a3)

template <class DR, class A1, class A2, class A3>
inline RWFunctor0
RWTFunctor0GA3Imp<DR, A1, A2, A3>::make(CalleeSignature function, A1 a1, A2 a2, A3 a3)
{
    return new RWTFunctor0GA3Imp<DR, A1, A2, A3>(function, a1, a2, a3);
}

template <class DR, class A1, class A2, class A3>
inline
RWTFunctor0GA3Imp<DR, A1, A2, A3>::RWTFunctor0GA3Imp(CalleeSignature function,
        A1 a1, A2 a2, A3 a3)
    : function_(function),
      a1_(a1),
      a2_(a2),
      a3_(a3)
{
}

template <class DR, class A1, class A2, class A3>
inline
RWTFunctor0GA3Imp<DR, A1, A2, A3>::~RWTFunctor0GA3Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor0GA3Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctor0GA3Imp_h__
