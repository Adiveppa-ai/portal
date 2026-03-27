#ifndef __rw_functor_RWTFunctorR1MImp_h__
#define __rw_functor_RWTFunctorR1MImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR1MImp.h#1 $
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
 * is a member that takes no callee arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctorR1.h>
#include <rw/functor/RWTFunctorR1Imp.h>

#  define RWFunctorR1MImp RWTFunctorR1MImp
#  define rwMakeFunctorR1M rwtMakeFunctorR1M

//-- Group: RWTFunctorR1Imp
//--
//-- Example:
//--   class Foo{
//--      int bar(short s){ return s; }
//--   };
//--
//--   int main () {
//--
//--         // Create the callee object
//--    Foo f;
//--
//--        // Create an RWTFunctorR1 with no callee arguments.
//--     RWTFunctorR1<int,short> functor =
//--        rwtMakeFunctorR1((int(*)(short))0, f, &Foo::bar);
//--
//--        // Invoking 'functor' will call bar.
//--     int return_value = functor(3);
//--
//--     return 0;
//--   }
//--

template <class SR, class S1, class Callee, class DR, class D1>
class RWTFunctorR1MImp : public RWTFunctorR1Imp<SR, S1>
{

public:

    // Destructor
    ~RWTFunctorR1MImp(void);

    // The signature of the functor invocation.
    typedef SR(*CallerSignature)(S1);

    // The signature of the encapsulated function's invocation.
    typedef DR(Callee::*CalleeSignature)(D1);

    // The type of the callee object.
    typedef Callee   CalleeType;

    // The return value of the functor.
    typedef SR SRType;

    // The type of the caller argument.
    typedef S1 S1Type;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The declared type of the encapsulated function's first argument.
    typedef D1 D1Type;

    //-- Creates a new RWTFunctorR1MImp and returns an appropriate handle.
    static RWTFunctorR1<SR, S1>
    make(Callee& callee, CalleeSignature function);

    // Invoke the encapsulated function, passing in the callee argument.
    virtual SR
    run(S1 s1) const;

protected:

    // Constructor, only for internal use.
    RWTFunctorR1MImp(Callee& callee, CalleeSignature function);

private:

    RWTFunctorR1MImp(const RWTFunctorR1MImp& second);

    RWTFunctorR1MImp&
    operator=(const RWTFunctorR1MImp& second);

private:
    // The callee.
    Callee&           callee_;

    // The encapsulated function.
    CalleeSignature   function_;
};


//-- A macro for ease of use in creating new 'RWTFunctorR1MImp' bodies.

/**
 * \ingroup functorR1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee, rw1)"
 * instead.
 *
 * Macro to create an RWTFunctorR1 set to call <tt>callee.function(s)</tt>.
 * \a function must have signature <tt>DR (Caller::*)(D1)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeFunctorR1M", "Use rwBind() instead")
#define rwtMakeFunctorR1M(SR,S1,Callee,callee,DR,function,D1) \
   RWTFunctorR1MImp<SR,S1,Callee,DR,D1 >::make(callee,function)

template <class SR, class S1, class Callee, class DR, class D1>
inline RWTFunctorR1<SR, S1>
RWTFunctorR1MImp<SR, S1, Callee, DR, D1>::make(Callee& callee, CalleeSignature function)
{
    return new RWTFunctorR1MImp<SR, S1, Callee, DR, D1>(callee, function);
}

template <class SR, class S1, class Callee, class DR, class D1>
inline
RWTFunctorR1MImp<SR, S1, Callee, DR, D1>::RWTFunctorR1MImp(Callee& callee,
        CalleeSignature function)
    : callee_(callee),
      function_(function)
{
}

template <class SR, class S1, class Callee, class DR, class D1>
inline
RWTFunctorR1MImp<SR, S1, Callee, DR, D1>::~RWTFunctorR1MImp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR1MImp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR1MImp_h__
