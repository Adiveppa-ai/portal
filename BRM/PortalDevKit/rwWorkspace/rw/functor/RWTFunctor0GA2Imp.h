#ifndef __rw_functor_RWTFunctor0GA2Imp_h__
#define __rw_functor_RWTFunctor0GA2Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor0GA2Imp.h#1 $
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
 * encapsulate a global function that takes two callee arguments; the
 * return value of these functors can be ignored.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWFunctor0.h>
#include <rw/functor/RWFunctor0Imp.h>

#  define RWFunctor0GA2Imp RWTFunctor0GA2Imp
#  define rwMakeFunctor0GA2 rwtMakeFunctor0GA2

//-- Group: RWTFunctor0Imp
//--
//-- Example:
//--   void printNums(int x, long y) { cout << "x is " << x << ", y is " << y << endl; }
//--
//--   int main () {
//--
//--        // Create an RWFunctor0 with two callee arguments.
//--     RWFunctor0 functor = rwtMakeFunctor0( 0, printNums, 12, 456 );
//--
//--        // Invoking 'functor' will print 'x is 12, y is 456'.
//--     functor();
//--
//--     return 0;
//--   }
//--

template <class DR, class A1, class A2>
class RWTFunctor0GA2Imp : public RWFunctor0Imp
{

public:

    // Destructor
    ~RWTFunctor0GA2Imp(void);

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(void);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(A1, A2);

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The type of the first callee argument.
    typedef A1 A1Type;

    // The type of the second callee argument.
    typedef A2 A2Type;

    // Dynamically construct an instance of RWTFunctor0GA2Imp and bind it to
    // the returned RWFunctor0 handle instance.
    static RWFunctor0
    make(CalleeSignature function, A1 a1, A2 a2);

    // Invoke the encapsulated function passing in the callee arguments.
    virtual void
    run(void) const;

protected:
    // The RWTFunctor0GA2Imp constructor--only for internal use.
    RWTFunctor0GA2Imp(CalleeSignature function, A1 a1, A2 a2);

private:

    RWTFunctor0GA2Imp(const RWTFunctor0GA2Imp& second);

    RWTFunctor0GA2Imp&
    operator=(const RWTFunctor0GA2Imp& second);


private:
    // The encapsulated function.
    CalleeSignature   function_;

    // The Callee data.
    A1                a1_;
    A2                a2_;
};


//-- A macro for ease of use in creating new 'RWTFunctor0GA2Imp' bodies.

/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2)"
 * instead.
 *
 * Macro to create an RWFunctor0 set to call <tt>function(a1,a2)</tt>.
 * \a function must have signature <tt>DR (*)(A1,A2)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor0GA2", "Use rwBind() instead")
#define rwtMakeFunctor0GA2(DR,function,A1,a1,A2,a2) \
   RWTFunctor0GA2Imp<DR,A1,A2 >::make(function,a1,a2)

template <class DR, class A1, class A2>
inline RWFunctor0
RWTFunctor0GA2Imp<DR, A1, A2>::make(CalleeSignature function, A1 a1, A2 a2)
{
    return new RWTFunctor0GA2Imp<DR, A1, A2>(function, a1, a2);
}

template <class DR, class A1, class A2>
inline
RWTFunctor0GA2Imp<DR, A1, A2>::RWTFunctor0GA2Imp(CalleeSignature function, A1 a1, A2 a2)
    : function_(function),
      a1_(a1),
      a2_(a2)
{
}

template <class DR, class A1, class A2>
inline
RWTFunctor0GA2Imp<DR, A1, A2>::~RWTFunctor0GA2Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor0GA2Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctor0GA2Imp_h__
