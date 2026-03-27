#ifndef __rw_functor_RWTFunctor1MA2Imp_h__
#define __rw_functor_RWTFunctor1MA2Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor1MA2Imp.h#1 $
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
 * The body class for functors that are invoked on a callee object with one
 * caller and 2 callee arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor1.h>
#include <rw/functor/RWTFunctor1Imp.h>

#  define RWFunctor1MA2Imp RWTFunctor1MA2Imp
#  define rwMakeFunctor1MA2 rwtMakeFunctor1MA2

//-- Group: RWTFunctor1Imp
//--   Please see RWTFunctor1Imp for more information on this group of classes.
//--
//-- Example:
//--   class coloredPoint{
//--      void draw(RWCString color, int x, int y);
//--    };
//--
//--    void coloredPoint::draw(RWCString color, int x, int y){
//--      cout << "drawing a " << color << " point at " << x << "," << y << endl;}
//--
//--   int main(){
//--
//--       coloredPoint p;
//--
//--           // Create an RWTFunctor1 with 2 callee arguments.
//--        RWTFunctor1<RWCString> functor =
//--            rwtMakeFunctor1((void(*)(RWCString))0, p, &coloredPoint::draw, 4, 5);
//--
//--           // Invoking 'functor' will draw a Red point at (4,5).
//--        functor("Red");
//--
//--        return 0;
//--    }
//--

template <class S1, class Callee, class DR, class D1, class A1, class A2>
class RWTFunctor1MA2Imp : public RWTFunctor1Imp<S1>
{

public:

    // Destructor
    ~RWTFunctor1MA2Imp(void);

    //-- The signature of the functor invocation.
    typedef void (*CallerSignature)(S1);

    //-- The signature of the encapsulated function's invocation.
    typedef DR(Callee::*CalleeSignature)(D1, A1, A2);

    //-- The type of the callee object.
    typedef Callee   CalleeType;

    //-- The type of the caller argument.
    typedef S1 S1Type;

    //-- The declared type of the encapsulated function's return value.
    typedef DR DRType;

    //-- The declared type of the encapsulated function's first argument.
    typedef D1 D1Type;

    //-- The type of the first callee argument.
    typedef A1 A1Type;

    //-- The type of the second callee argument.
    typedef A2 A2Type;

    //-- Creates a new RWTFunctor1MA2Imp and returns an appropriate handle.
    static RWTFunctor1<S1>
    make(Callee& callee, CalleeSignature function, A1 a1, A2 a2);

    // Invoke the encapsulated method on the callee object, passing
    // the provided caller argument and the stored callee arguments.
    virtual void
    run(S1 s1) const;

protected:
    // The 'RWTFunctor1MA2Imp' constructor, only for internal use
    RWTFunctor1MA2Imp(Callee& callee, CalleeSignature function,
                      A1 a1, A2 a2);

private:

    RWTFunctor1MA2Imp(const RWTFunctor1MA2Imp& second);

    RWTFunctor1MA2Imp&
    operator=(const RWTFunctor1MA2Imp& second);

private:
    // The callee object.
    Callee&           callee_;

    // The encapsulated function.
    CalleeSignature   function_;

    // The callee arguments.
    A1                a1_;
    A2                a2_;
};


/**
 * \ingroup functor1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, a1, a2)" instead.
 *
 * Macro to create an RWTFunctor1 set to call
 * <tt>callee.function(s,a1,a2)</tt>. \a function must have signature
 * <tt>DR (Caller::*)(D1,A1,A2)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor1MA2", "Use rwBind() instead")
#define rwtMakeFunctor1MA2(S1,Callee,callee,DR,function,D1,A1,a1,A2,a2) \
   RWTFunctor1MA2Imp<S1,Callee,DR,D1,A1,A2 >::make(callee,function,a1,a2)

template <class S1, class Callee, class DR, class D1, class A1, class A2>
inline RWTFunctor1<S1>
RWTFunctor1MA2Imp<S1, Callee, DR, D1, A1, A2>::make(Callee& callee,
        CalleeSignature function,
        A1 a1, A2 a2)
{
    return new RWTFunctor1MA2Imp<S1, Callee, DR, D1, A1, A2>(callee, function, a1, a2);
}

template <class S1, class Callee, class DR, class D1, class A1, class A2>
inline
RWTFunctor1MA2Imp<S1, Callee, DR, D1, A1, A2>::RWTFunctor1MA2Imp(Callee& callee,
        CalleeSignature function,
        A1 a1, A2 a2)
    : callee_(callee),
      function_(function),
      a1_(a1),
      a2_(a2)
{
}

template <class S1, class Callee, class DR, class D1, class A1, class A2>
inline
RWTFunctor1MA2Imp<S1, Callee, DR, D1, A1, A2>::~RWTFunctor1MA2Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor1MA2Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_RWTFunctor1MA2Imp_h__
