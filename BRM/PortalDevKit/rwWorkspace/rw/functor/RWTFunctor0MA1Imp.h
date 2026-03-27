#ifndef __rw_functor_RWTFunctor0MA1Imp_h__
#define __rw_functor_RWTFunctor0MA1Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor0MA1Imp.h#1 $
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
 * The body class for functors that take no caller arguments, are invoked
 * on a callee object, with one additional callee argument, and whose
 * return value can be ignored.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWFunctor0.h>
#include <rw/functor/RWFunctor0Imp.h>

#  define RWFunctor0MA1Imp RWTFunctor0MA1Imp
#  define rwMakeFunctor0MA1 rwtMakeFunctor0MA1

//-- Group: RWTFunctor0Imp
//--
//-- Example:
//--   class circle{
//--     public:
//--      circle(int r):radius_(r){}
//--      void setRadius(int r) { radius_ = r; }
//--    private:
//--      int radius_;
//--   };
//--
//--
//--   int main () {
//--
//--     circle c(10);
//--
//--        // Create an RWTFunctor0 with one callee argument.
//--     RWFunctor0 functor = rwtMakeFunctor0( 0, c, &circle::setRadius, 12 );
//--
//--        // Invoking 'functor' will set the radius of circle \'c\' to 12.
//--     functor();
//--
//--     return 0;
//--   }
//--

template <class Callee, class DR, class A1>
class RWTFunctor0MA1Imp : public RWFunctor0Imp
{

public:

    // Destructor
    ~RWTFunctor0MA1Imp(void);

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(void);

    // The signature of the encapsulated method's invocation.
    typedef DR(Callee::*CalleeSignature)(A1);

    // The type of the object that the method will be invoked upon.
    typedef Callee   CalleeType;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The type of the callee argument.
    typedef A1 A1Type;

    // Dynamically construct an instance of RWTFunctor0MA1Imp and bind it to
    // the returned RWFunctor0 handle instance.
    static RWFunctor0
    make(Callee& callee, CalleeSignature function, A1 a1);

    // Invoke the encapsulated method on the callee object,
    // passing in the additional callee argument.
    virtual void
    run(void) const;

protected:
    // The 'RWTFunctor0MA1Imp' constructor, only for internal use.
    RWTFunctor0MA1Imp(Callee& callee, CalleeSignature function, A1 a1);

private:

    RWTFunctor0MA1Imp(const RWTFunctor0MA1Imp& second);

    RWTFunctor0MA1Imp&
    operator=(const RWTFunctor0MA1Imp& second);

private:
    // The object on which the method will be invoked.
    Callee&           callee_;

    // The encapsulated method.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
};


//-- A macro for ease of use in creating new 'RWTFunctor0MA1Imp' bodies.

/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee, a1)"
 * instead.
 *
 * Macro to create an RWFunctor0 set to call <tt>callee.function(a1)</tt>.
 * \a function must have signature <tt>DR (Caller::*)(A1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor0MA1", "Use rwBind() instead")
#define rwtMakeFunctor0MA1(Callee,callee,DR,function,A1,a1) \
   RWTFunctor0MA1Imp<Callee,DR,A1 >::make(callee,function,a1)

template <class Callee, class DR, class A1>
inline RWFunctor0
RWTFunctor0MA1Imp<Callee, DR, A1>::make(Callee& callee,
                                        CalleeSignature function, A1 a1)
{
    return new RWTFunctor0MA1Imp<Callee, DR, A1>(callee, function, a1);
}

template <class Callee, class DR, class A1>
inline
RWTFunctor0MA1Imp<Callee, DR, A1>::RWTFunctor0MA1Imp(Callee& callee,
        CalleeSignature function, A1 a1)
    : callee_(callee),
      function_(function),
      a1_(a1)
{
}

template <class Callee, class DR, class A1>
inline
RWTFunctor0MA1Imp<Callee, DR, A1>::~RWTFunctor0MA1Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor0MA1Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctor0MA1Imp_h__
