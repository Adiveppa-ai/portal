#ifndef __rw_functor_RWTFunctorR0GA1Imp_h__
#define __rw_functor_RWTFunctorR0GA1Imp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR0GA1Imp.h#1 $
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
 * that use a return value, and whose encapsulated function is global,
 * taking one callee argument.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctorR0.h>
#include <rw/functor/RWTFunctorR0Imp.h>

#  define RWFunctorR0GA1Imp RWTFunctorR0GA1Imp
#  define rwMakeFunctorR0GA1 rwtMakeFunctorR0GA1

//-- Group: RWTFunctorR0Imp
//--
//-- Example:
//--   int flag = 0;
//--   int getAndSetFlag(short s) { return flag=s; }
//--
//--   int main () {
//--
//--        // Create an RWTFunctorR0 with one callee argument.
//--     RWTFunctorR0<int> functor = rwtMakeFunctorR0( (int(*)())0, getAndSetFlag, 12 );
//--
//--        // Invoking 'functor' will set the global flag to 12.
//--     int return_value = functor();
//--
//--     return 0;
//--   }
//--

template <class SR, class DR, class A1>
class RWTFunctorR0GA1Imp : public RWTFunctorR0Imp<SR>
{

public:

    // Destructor
    ~RWTFunctorR0GA1Imp(void);

    // The signature of the functor invocation.
    typedef SR(*CallerSignature)(void);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(A1);

    // The return value of the functor.
    typedef SR SRType;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The type of the callee argument.
    typedef A1 A1Type;

    //-- Creates a new RWTFunctorR0GA1Imp and returns an appropriate handle.
    static RWTFunctorR0<SR>
    make(CalleeSignature function, A1 a1);

    // Invoke the encapsulated function, passing in the callee argument.
    virtual SR
    run(void) const;

protected:

    // The RWTFunctorR0GA1Imp constructor, only for internal use.
    RWTFunctorR0GA1Imp(CalleeSignature function, A1 a1);

private:

    RWTFunctorR0GA1Imp(const RWTFunctorR0GA1Imp& second);

    RWTFunctorR0GA1Imp&
    operator=(const RWTFunctorR0GA1Imp& second);


private:

    // The encapsulated function.
    CalleeSignature   function_;

    // The callee data.
    A1                a1_;
};


//-- A macro for ease of use in creating new 'RWTFunctorR0GA1Imp' bodies.

/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1)" instead.
 *
 * Macro to create an RWTFunctorR0 set to call <tt>function(a1)</tt>.
 * \a function must have signature <tt>DR (*)(A1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctorR0GA1", "Use rwBind() instead")
#define rwtMakeFunctorR0GA1(SR,DR,function,A1,a1) \
   RWTFunctorR0GA1Imp<SR,DR,A1 >::make(function,a1)

template <class SR, class DR, class A1>
inline RWTFunctorR0<SR>
RWTFunctorR0GA1Imp<SR, DR, A1>::make(CalleeSignature function, A1 a1)
{
    return new RWTFunctorR0GA1Imp<SR, DR, A1>(function, a1);
}

template <class SR, class DR, class A1>
inline
RWTFunctorR0GA1Imp<SR, DR, A1>::RWTFunctorR0GA1Imp(CalleeSignature function, A1 a1)
    : function_(function),
      a1_(a1)
{
}

template <class SR, class DR, class A1>
inline
RWTFunctorR0GA1Imp<SR, DR, A1>::~RWTFunctorR0GA1Imp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR0GA1Imp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR0GA1Imp_h__
