#ifndef __rw_functor_RWTFunctor1GImp_h__
#define __rw_functor_RWTFunctor1GImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor1GImp.h#1 $
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
 * The body class for functors that are invoked with one caller argument,
 * and encapsulate a global function taking no callee arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor1.h>
#include <rw/functor/RWTFunctor1Imp.h>

#  define RWFunctor1GImp RWTFunctor1GImp
#  define rwMakeFunctor1G rwtMakeFunctor1G

//-- Group: RWTFunctor1Imp
//--   Please see RWTFunctor1Imp for more information on this group of classes.
//--
//-- Example:
//--   bool flag;
//--   void setFlag(bool newValue){ flag = newValue;}
//--
//--   int main () {
//--
//--        // Create an RWTFunctor1 with no callee arguments.
//--     RWTFunctor1<bool> functor = rwtMakeFunctor1((void(*)(bool))0, setFlag);
//--
//--        // Invoking 'functor' will set the flag to true.
//--     functor(true);
//--
//--     return 0;
//--   }
//--

template <class S1, class DR, class D1>
class RWTFunctor1GImp : public RWTFunctor1Imp<S1>
{

public:

    // Destructor
    ~RWTFunctor1GImp(void);

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(S1);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(D1);

    // The type of the caller argument.
    typedef S1 S1Type;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // The declared type of the encapsulated function's first argument.
    typedef D1 D1Type;

    //-- Creates a new RWTFunctor1GImp and returns an appropriate handle.
    static RWTFunctor1<S1>
    make(CalleeSignature function);

    // Invoke the encapsulated function passing it the caller data (s1).
    virtual void
    run(S1 s1) const;

protected:

    // The 'RWTFunctor1GImp' constructor--only for internal use.
    RWTFunctor1GImp(CalleeSignature function);

private:

    RWTFunctor1GImp(const RWTFunctor1GImp& second);

    RWTFunctor1GImp&
    operator=(const RWTFunctor1GImp& second);

private:

    // The encapsulated function.
    CalleeSignature   function_;
};


/**
 * \ingroup functor1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1)" instead.
 *
 * Macro to create an RWTFunctor1 set to call <tt>function(s)</tt>.
 * \a function must have signature <tt>DR (*)(D1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor1G", "Use rwBind() instead")
#define rwtMakeFunctor1G(S1,DR,function,D1) \
   RWTFunctor1GImp<S1,DR,D1 >::make(function)

template <class S1, class DR, class D1>
inline RWTFunctor1<S1>
RWTFunctor1GImp<S1, DR, D1>::make(CalleeSignature function)
{
    return new RWTFunctor1GImp<S1, DR, D1>(function);
}

template <class S1, class DR, class D1>
inline
RWTFunctor1GImp<S1, DR, D1>::RWTFunctor1GImp(CalleeSignature function)
    : function_(function)
{
}

template <class S1, class DR, class D1>
inline
RWTFunctor1GImp<S1, DR, D1>::~RWTFunctor1GImp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor1GImp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_RWTFunctor1GImp_h__
