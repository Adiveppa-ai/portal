#ifndef __rw_functor_RWTFunctor0MA3Imp_h__
#define __rw_functor_RWTFunctor0MA3Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor0MA3Imp.h#1 $
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
 * on a callee object, with three additional callee arguments, and whose
 * return value can be ignored.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWFunctor0.h>
#include <rw/functor/RWFunctor0Imp.h>

#  define RWFunctor0MA3Imp RWTFunctor0MA3Imp
#  define rwMakeFunctor0MA3 rwtMakeFunctor0MA3

//-- Group: RWTFunctor0Imp
//--
//-- Example:
//--   class triangle{
//--     public:
//--      triangle(int x, int y, int z): side1_(x), side2_(y), side3_(z){}
//--      setSides(int x, int y, int z) {
//--         side1_=x; side2_=y; side3_=z;
//--         x *= y; return x*= z;}
//--     private:
//--      int side1_;
//--      int side2_;
//--      int side3_;
//--
//--   };
//--
//--
//--   int main () {
//--
//--     triangle t(3,4,5);
//--
//--        // Create an RWTFunctor0 with three callee arguments.
//--     RWFunctor0 functor = rwtMakeFunctor0( 0, t, &triangle::setSides, 5, 12, 13 );
//--
//--        // Invoking 'functor' will resize triangle \'t\' to have sides of
//--        // lengths 5, 12 and 13.
//--     functor();
//--
//--     return 0;
//--   }
//--

template <class Callee, class DR, class A1, class A2, class A3>
class RWTFunctor0MA3Imp : public RWFunctor0Imp
{

public:

    // Destructor
    ~RWTFunctor0MA3Imp(void);

    //-- The signature of the functor invocation.
    typedef void (*CallerSignature)(void);

    //-- The signature of the encapsulated method's invocation.
    typedef DR(Callee::*CalleeSignature)(A1, A2, A3);

    //-- The type of the object that the method will be invoked upon.
    typedef Callee   CalleeType;

    //-- The declared type of the encapsulated method's return value.
    typedef DR DRType;

    //-- The type of the first callee argument.
    typedef A1 A1Type;

    //-- The type of the second callee argument.
    typedef A2 A2Type;

    //-- The type of the third callee argument.
    typedef A3 A3Type;


    // Dynamically construct an instance of RWTFunctor0MA3Imp and bind it to
    // the returned RWFunctor0 handle instance.
    static RWFunctor0
    make(Callee& callee, CalleeSignature function, A1 a1, A2 a2, A3 a3);

    // Invoke the encapsulated method on the callee object,
    // passing in the additional callee arguments.
    virtual void
    run(void) const;

protected:
    // The 'RWTFunctor0MA3Imp' constructor, only for internal use.
    RWTFunctor0MA3Imp(Callee& callee, CalleeSignature function,
                      A1 a1, A2 a2, A3 a3);

private:

    RWTFunctor0MA3Imp(const RWTFunctor0MA3Imp& second);

    RWTFunctor0MA3Imp&
    operator=(const RWTFunctor0MA3Imp& second);

private:
    // The object on which the method will be invoked.
    Callee&           callee_;

    // The encapsulated method.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
    A2                a2_;
    A3                a3_;
};



//-- A macro for ease of use in creating new 'RWTFunctor0MA3Imp' bodies.

/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, a1, a2, a3)" instead.
 *
 * Macro to create an RWFunctor0 set to call
 * <tt>callee.function(a1,a2,a3)</tt>. \a function must have signature
 * <tt>DR (Caller::*)(A1,A2,A3)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor0MA3", "Use rwBind() instead")
#define rwtMakeFunctor0MA3(Callee,callee,DR,function,A1,a1,A2,a2,A3,a3) \
   RWTFunctor0MA3Imp<Callee,DR,A1,A2,A3 >::make(callee,function,a1,a2,a3)

template <class Callee, class DR, class A1, class A2, class A3>
inline RWFunctor0
RWTFunctor0MA3Imp<Callee, DR, A1, A2, A3>::make(Callee& callee,
        CalleeSignature function,
        A1 a1, A2 a2, A3 a3)
{
    return new RWTFunctor0MA3Imp<Callee, DR, A1, A2, A3>(callee, function, a1, a2, a3);
}

template <class Callee, class DR, class A1, class A2, class A3>
inline
RWTFunctor0MA3Imp<Callee, DR, A1, A2, A3>::RWTFunctor0MA3Imp(Callee& callee,
        CalleeSignature function,
        A1 a1, A2 a2, A3 a3)
    : callee_(callee),
      function_(function),
      a1_(a1),
      a2_(a2),
      a3_(a3)
{
}

template <class Callee, class DR, class A1, class A2, class A3>
inline
RWTFunctor0MA3Imp<Callee, DR, A1, A2, A3>::~RWTFunctor0MA3Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor0MA3Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctor0MA3Imp_h__
