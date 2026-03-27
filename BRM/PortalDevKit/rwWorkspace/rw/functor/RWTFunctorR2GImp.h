#ifndef __rw_functor_RWTFunctorR2GImp_h__
#define __rw_functor_RWTFunctorR2GImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR2GImp.h#1 $
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
 * is a global that takes no callee arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctorR2.h>
#include <rw/functor/RWTFunctorR2Imp.h>

#  define RWFunctorR2GImp RWTFunctorR2GImp
#  define rwMakeFunctorR2G rwtMakeFunctorR2G

//-- Group: RWTFunctorR2Imp
//--
//-- Example:
//--   int foo(short s, long l){ return s * l; }
//--
//--   int main () {
//--
//--        // Create an RWTFunctorR2 with no callee arguments.
//--     RWTFunctorR2<int,short,long> functor =
//--        rwtMakeFunctorR2((int(*)(short,long))0, foo);
//--
//--        // Invoking 'functor' will call foo.
//--     int return_value = functor(3, 49770);
//--
//--     return 0;
//--   }
//--

template <class SR, class S1, class S2, class DR, class D1, class D2>
class RWTFunctorR2GImp : public RWTFunctorR2Imp<SR, S1, S2>
{

public:

    // Destructor
    ~RWTFunctorR2GImp(void);

    // The signature of the functor invocation.
    typedef SR(*CallerSignature)(S1, S2);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(D1, D2);

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

    //-- Creates a new RWTFunctorR2GImp and returns an appropriate handle.
    static RWTFunctorR2<SR, S1, S2> make(CalleeSignature function);

    // Invoke the encapsulated function, passing in the callee argument.
    virtual SR run(S1 s1, S2 s2) const;

protected:

    // Constructor, only for internal use.
    RWTFunctorR2GImp(CalleeSignature function);

private:

    RWTFunctorR2GImp(const RWTFunctorR2GImp& second);

    RWTFunctorR2GImp&
    operator=(const RWTFunctorR2GImp& second);

private:

    // The encapsulated function.
    CalleeSignature   function_;
};


//-- A macro for ease of use in creating new 'RWTFunctorR2GImp' bodies.

/**
 * \ingroup functorR2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, rw2)"
 * instead.
 *
 * Macro to create an RWTFunctorR2 set to call <tt>function(s1,s2)</tt>.
 * \a function must have signature <tt>DR (*)(D1,D2)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeFunctorR2G", "Use rwBind() instead")
#define rwtMakeFunctorR2G(SR,S1,S2,DR,function,D1,D2) \
   RWTFunctorR2GImp<SR,S1,S2,DR,D1,D2 >::make(function)

template <class SR, class S1, class S2, class DR, class D1, class D2>
inline RWTFunctorR2<SR, S1, S2>
RWTFunctorR2GImp<SR, S1, S2, DR, D1, D2>::make(CalleeSignature function)
{
    return new RWTFunctorR2GImp<SR, S1, S2, DR, D1, D2>(function);
}

template <class SR, class S1, class S2, class DR, class D1, class D2>
inline
RWTFunctorR2GImp<SR, S1, S2, DR, D1, D2>::RWTFunctorR2GImp(CalleeSignature function)
    : function_(function)
{
}

template <class SR, class S1, class S2, class DR, class D1, class D2>
inline
RWTFunctorR2GImp<SR, S1, S2, DR, D1, D2>::~RWTFunctorR2GImp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR2GImp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR2GImp_h__
