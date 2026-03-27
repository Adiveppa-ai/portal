#ifndef __rw_functor_RWTFunctor1MImp_h__
#define __rw_functor_RWTFunctor1MImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor1MImp.h#1 $
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
 * The body class for functors that are invoked on a callee object with 1
 * caller argument and no callee arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor1.h>
#include <rw/functor/RWTFunctor1Imp.h>

#  define RWFunctor1MImp RWTFunctor1MImp
#  define rwMakeFunctor1M rwtMakeFunctor1M

//-- Group: RWTFunctor1Imp
//--   Please see RWTFunctor1Imp for more information on this group of classes.
//--
//-- Example:
//--   class Circle{
//--      void draw(int size);
//--    };
//--   void Circle::draw(int size){
//--    cout << "Drawing a circle that is " << size << "inches" << endl;
//--   }
//--
//--   int main () {
//--
//--        // Create the callee object
//--     Circle c;
//--
//--        // Create an RWTFunctor1 with no callee arguments.
//--     RWTFunctor1<int> functor = rwtMakeFunctor1(
//--            (void(*)(int))0, c, &Circle::draw );
//--
//--        // Invoking 'functor' will call draw.
//--     functor(14);
//--
//--     return 0;
//--   }
//--

template <class S1, class Callee, class DR, class D1>
class RWTFunctor1MImp : public RWTFunctor1Imp<S1>
{

public:

    // Destructor
    ~RWTFunctor1MImp(void);

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(S1);

    // The signature of the encapsulated function's invocation.
    typedef DR(Callee::*CalleeSignature)(D1);

    // The type of the callee object.
    typedef Callee   CalleeType;

    // The type of the caller argument.
    typedef S1 S1Type;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The declared type of the encapsulated function's first argument.
    typedef D1 D1Type;

    // The RWTFunctor1MImp constructor--only for internal use.

    //-- Creates a new RWTFunctor1MImp and returns an appropriate handle.
    static RWTFunctor1<S1>
    make(Callee& callee, CalleeSignature function);

    // Invoke the encapsulated method on the callee object, passing to it
    // the caller argument.
    virtual void
    run(S1 s1) const;

protected:
    // The 'RWTFunctor1MImp' constructor--only for internal use.
    RWTFunctor1MImp(Callee& callee, CalleeSignature function);

private:

    RWTFunctor1MImp(const RWTFunctor1MImp& second);

    RWTFunctor1MImp&
    operator=(const RWTFunctor1MImp& second);

private:
    // The callee object.
    Callee&           callee_;

    // The encapsulated function.
    CalleeSignature   function_;
};


/**
 * \ingroup functor1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee, rw1)"
 * instead.
 *
 * Macro to create an RWTFunctor1 set to call <tt>callee.function(s)</tt>.
 * \a function must have signature <tt>DR (Caller::*)(D1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor1M", "Use rwBind() instead")
#define rwtMakeFunctor1M(S1,Callee,callee,DR,function,D1) \
   RWTFunctor1MImp<S1,Callee,DR,D1 >::make(callee,function)

template <class S1, class Callee, class DR, class D1>
inline RWTFunctor1<S1>
RWTFunctor1MImp<S1, Callee, DR, D1>::make(Callee& callee,
        CalleeSignature function)
{
    return new RWTFunctor1MImp<S1, Callee, DR, D1>(callee, function);
}

template <class S1, class Callee, class DR, class D1>
inline
RWTFunctor1MImp<S1, Callee, DR, D1>::RWTFunctor1MImp(Callee& callee,
        CalleeSignature function)
    : callee_(callee),
      function_(function)
{
}

template <class S1, class Callee, class DR, class D1>
inline
RWTFunctor1MImp<S1, Callee, DR, D1>::~RWTFunctor1MImp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor1MImp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_RWTFunctor1MImp_h__
