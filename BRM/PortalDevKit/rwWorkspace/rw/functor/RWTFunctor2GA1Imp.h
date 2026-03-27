#ifndef __rw_functor_RWTFunctor2GA1Imp_h__
#define __rw_functor_RWTFunctor2GA1Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor2GA1Imp.h#1 $
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
 * and that encapsulate a global function taking one callee argument; the
 * return value of these functors can be ignored.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor2.h>
#include <rw/functor/RWTFunctor2Imp.h>

#  define  RWFunctor2GA1Imp RWTFunctor2GA1Imp
#  define  rwMakeFunctor2GA1 rwtMakeFunctor2GA1

//-- Group: RWTFunctor2Imp
//--   Please see RWTFunctor2Imp for more information on this group of classes.
//--
//-- Example:
//--   void printNums(int i,short s,float f )
//--      { cout << "i is " << i << ", s is " << s << ", f is " << f << endl; }
//--
//--   int main () {
//--
//--        // Create an RWTFunctor2 with one callee argument.
//--     RWTFunctor2<int,short> functor = rwtMakeFunctor2((void(*)(int,short))0, printNums, 3.14 );
//--
//--        // Invoking 'functor' will print 'i is 14, s is 2, f is 3.14'.
//--     functor(14,2);
//--
//--     return 0;
//--   }
//--

template <class S1, class S2, class DR, class D1, class D2, class A1>
class RWTFunctor2GA1Imp : public RWTFunctor2Imp<S1, S2>
{

public:

    // Destructor
    ~RWTFunctor2GA1Imp(void);

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(S1, S2);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(D1, D2, A1);

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

    //-- Constructs a new instance of the corresponding body class
    //-- and binds it to a RWTFunctor2 handle which is then returned.
    static RWTFunctor2<S1, S2>
    make(CalleeSignature function, A1 a1);

    // Invoke the encapsulated function passing in both the
    // caller arguments and the the stored callee argument.
    virtual void
    run(S1 s1, S2 s2) const;

protected:
    // The 'RWTFunctor2GA1Imp' constructor--only for internal use.
    RWTFunctor2GA1Imp(CalleeSignature function, A1 a1);

private:

    RWTFunctor2GA1Imp(const RWTFunctor2GA1Imp& second);

    RWTFunctor2GA1Imp&
    operator=(const RWTFunctor2GA1Imp& second);

private:
    // The encapsulated function.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
};


/**
 * \ingroup functor2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, rw2, a1)"
 * instead.
 *
 * Macro to create an RWTFunctor2 set to call <tt>function(s1,s2,a1)</tt>.
 * \a function must have signature <tt>DR (*)(D1,D2,A1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor2GA1", "Use rwBind() instead")
#define rwtMakeFunctor2GA1(S1,S2,DR,function,D1,D2,A1,a1) \
   RWTFunctor2GA1Imp<S1,S2,DR,D1,D2,A1 >::make(function,a1)

template <class S1, class S2, class DR, class D1, class D2, class A1>
inline RWTFunctor2<S1, S2>
RWTFunctor2GA1Imp<S1, S2, DR, D1, D2, A1>::make(CalleeSignature function, A1 a1)
{
    return new RWTFunctor2GA1Imp<S1, S2, DR, D1, D2, A1>(function, a1);
}

template <class S1, class S2, class DR, class D1, class D2, class A1>
inline
RWTFunctor2GA1Imp<S1, S2, DR, D1, D2, A1>::RWTFunctor2GA1Imp(CalleeSignature function, A1 a1)
    : function_(function),
      a1_(a1)
{
}

template <class S1, class S2, class DR, class D1, class D2, class A1>
inline
RWTFunctor2GA1Imp<S1, S2, DR, D1, D2, A1>::~RWTFunctor2GA1Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor2GA1Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_RWTFunctor2GA1Imp_h__
