#ifndef __rw_functor_RWTFunctorR0GA3Imp_h__
#define __rw_functor_RWTFunctorR0GA3Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR0GA3Imp.h#1 $
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
 * The body class for functors that are invoked with no caller arguments,
 * that have a return value that is used, and whose encapsulated function
 * is global, taking three callee arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctorR0.h>
#include <rw/functor/RWTFunctorR0Imp.h>

#  define RWFunctorR0GA3Imp RWTFunctorR0GA3Imp
#  define rwMakeFunctorR0GA3 rwtMakeFunctorR0GA3

//-- Group: RWTFunctorR0Imp
//--
//-- Example:
//--   int flag = 0;
//--   int getAndSetFlag(short s, int i, char c) { flag += s; flag+=i; return flag + c; }
//--
//--   int main () {
//--
//--        // Create an RWTFunctorR0 with three callee arguments.
//--     RWTFunctorR0<int> functor = rwtMakeFunctorR0( (int(*)())0, getAndSetFlag, 12, 2, 1 );
//--
//--        // Invoking 'functor' will set the global flag to 15.
//--     int return_value = functor();
//--
//--     return 0;
//--   }
//--

template <class SR, class DR, class A1, class A2, class A3>
class RWTFunctorR0GA3Imp : public RWTFunctorR0Imp<SR>
{

public:

    // Destructor
    ~RWTFunctorR0GA3Imp(void);

    // The signature of the functor invocation.
    typedef SR(*CallerSignature)(void);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(A1, A2, A3);

    // The return value of the functor.
    typedef SR SRType;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The type of the first callee argument.
    typedef A1 A1Type;

    // The type of the second callee argument.
    typedef A2 A2Type;

    // The type of the third callee argument.
    typedef A3 A3Type;

    //-- Creates a new RWTFunctorR0GA3Imp and returns an appropriate handle.
    static RWTFunctorR0<SR>
    make(CalleeSignature function, A1 a1, A2 a2, A3 a3);

    // Invoke the encapsulated function, passing in the callee argument.
    virtual SR
    run(void) const;

protected:

    // The RWTFunctorR0GA1Imp constructor, only for internal use.
    RWTFunctorR0GA3Imp(CalleeSignature function, A1 a1, A2 a2, A3 a3);

private:

    RWTFunctorR0GA3Imp(const RWTFunctorR0GA3Imp& second);

    RWTFunctorR0GA3Imp&
    operator=(const RWTFunctorR0GA3Imp& second);

private:

    // The encapsulated function.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
    A2                a2_;
    A3                a3_;
};


//-- A macro for ease of use in creating new 'RWTFunctorR0GA3Imp' bodies.

/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2, a3)"
 * instead.
 *
 * Macro to create an RWTFunctorR0 set to call <tt>function(a1,a2,a3)</tt>.
 * \a function must have signature <tt>DR (*)(A1,A2,A3)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctorR0GA3", "Use rwBind() instead")
#define rwtMakeFunctorR0GA3(SR,DR,function,A1,a1,A2,a2,A3,a3) \
   RWTFunctorR0GA3Imp<SR,DR,A1,A2,A3 >::make(function,a1,a2,a3)

template <class SR, class DR, class A1, class A2, class A3>
inline RWTFunctorR0<SR>
RWTFunctorR0GA3Imp<SR, DR, A1, A2, A3>::make(CalleeSignature function, A1 a1, A2 a2, A3 a3)
{
    return new RWTFunctorR0GA3Imp<SR, DR, A1, A2, A3>(function, a1, a2, a3);
}

template <class SR, class DR, class A1, class A2, class A3>
inline
RWTFunctorR0GA3Imp<SR, DR, A1, A2, A3>::RWTFunctorR0GA3Imp(CalleeSignature function,
        A1 a1, A2 a2, A3 a3)
    : function_(function),
      a1_(a1),
      a2_(a2),
      a3_(a3)
{
}

template <class SR, class DR, class A1, class A2, class A3>
inline
RWTFunctorR0GA3Imp<SR, DR, A1, A2, A3>::~RWTFunctorR0GA3Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR0GA3Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR0GA3Imp_h__
