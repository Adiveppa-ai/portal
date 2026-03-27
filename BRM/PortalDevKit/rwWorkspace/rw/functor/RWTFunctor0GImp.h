#ifndef __rw_functor_RWTFunctor0GImp_h__
#define __rw_functor_RWTFunctor0GImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor0GImp.h#1 $
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
 * The body class for functors that are invoked without caller arguments,
 * and whose encapsulated function is global, taking no callee arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWFunctor0.h>
#include <rw/functor/RWFunctor0Imp.h>

#  define RWFunctor0GImp RWTFunctor0GImp
#  define rwMakeFunctor0G rwtMakeFunctor0G

//-- Group:  RWTFunctor0Imp
//--
//-- Example:
//--   void Hello(void){ cout << "Hello World!" << endl;};
//--
//--   int main () {
//--
//--        // Create an RWTFunctor0 with no callee arguments.
//--     RWFunctor0 functor = rwtMakeFunctor0( 0, Hello );
//--
//--        // Invoking 'functor' will print 'Hello World'.
//--     functor();
//--
//--     return 0;
//--   }
//--

template <class DR>
class RWTFunctor0GImp : public RWFunctor0Imp
{

public:

    // Destructor
    ~RWTFunctor0GImp(void);

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(void);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(void);

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;


    // Dynamically construct an instance of RWTFunctor0GImp and bind it to
    // the returned RWFunctor0 handle instance.
    static RWFunctor0
    make(CalleeSignature function);

    // Invoke the encapsulated function, passing in the callee argument.
    virtual void
    run(void) const;

protected:
    // The RWTFunctor0GA0Imp constructor--only for internal use.
    RWTFunctor0GImp(CalleeSignature function);

private:

    RWTFunctor0GImp(const RWTFunctor0GImp& second);

    RWTFunctor0GImp&
    operator=(const RWTFunctor0GImp& second);

private:
    // The encapsulated function.
    CalleeSignature   function_;
};


//-- A macro for ease of use in creating new 'RWTFunctor0GImp' bodies.

/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function)" instead.
 *
 * Macro to create an RWFunctor0 set to call <tt>function()</tt>.
 * \a function must have signature <tt>DR (*)(void)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor0G", "Use rwBind() instead")
#define rwtMakeFunctor0G(DR,function) \
   RWTFunctor0GImp<DR >::make(function)

template <class DR>
inline RWFunctor0
RWTFunctor0GImp<DR>::make(CalleeSignature function)
{
    return new RWTFunctor0GImp<DR>(function);
}

template <class DR>
inline
RWTFunctor0GImp<DR>::RWTFunctor0GImp(CalleeSignature function)
    : function_(function)
{
}

template <class DR>
inline
RWTFunctor0GImp<DR>::~RWTFunctor0GImp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor0GImp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctor0GImp_h__
