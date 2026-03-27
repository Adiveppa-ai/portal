#ifndef __rw_functor_RWTFunctorR0GImp_h__
#define __rw_functor_RWTFunctorR0GImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctorR0GImp.h#1 $
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
 * taking no callee arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctorR0.h>
#include <rw/functor/RWTFunctorR0Imp.h>

#  define RWFunctorR0GImp RWTFunctorR0GImp
#  define rwMakeFunctorR0G rwtMakeFunctorR0G

//-- Group: RWTFunctorR0Imp
//--
//-- Example:
//--   int flag = 0;
//--   int getFlag() { return flag; }
//--
//--   int main () {
//--
//--        // Create an RWTFunctorR0 with no callee arguments.
//--     RWTFunctorR0<int> functor = rwtMakeFunctorR0( (int(*)())0, getFlag );
//--
//--        // Invoking 'functor' will return the value of 'flag'
//--     int return_value = functor();
//--
//--     return 0;
//--   }
//--

template <class SR, class DR>
class RWTFunctorR0GImp : public RWTFunctorR0Imp<SR>
{

public:

    // Destructor
    ~RWTFunctorR0GImp(void);

    // The signature of the functor invocation.
    typedef SR(*CallerSignature)(void);

    // The signature of the encapsulated function's invocation.
    typedef DR(*CalleeSignature)(void);

    // The return value of the functor.
    typedef SR SRType;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    //-- Creates a new RWTFunctorR0GImp and returns an appropriate handle.
    static RWTFunctorR0<SR>
    make(CalleeSignature function);

    // Invoke the encapsulated function, passing in the callee argument.
    virtual SR
    run(void) const;

protected:

    // The RWTFunctorR0GA1Imp constructor, only for internal use.
    RWTFunctorR0GImp(CalleeSignature function);

private:

    RWTFunctorR0GImp(const RWTFunctorR0GImp& second);

    RWTFunctorR0GImp&
    operator=(const RWTFunctorR0GImp& second);

private:

    // The encapsulated function.
    CalleeSignature   function_;
};


//-- A macro for ease of use in creating new 'RWTFunctorR0GImp' bodies.

/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function)" instead.
 *
 * Macro to create an RWTFunctorR0 set to call <tt>function()</tt>.
 * \a function must have signature <tt>DR (*)(void)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctorR0G", "Use rwBind() instead")
#define rwtMakeFunctorR0G(SR,DR,function) \
   RWTFunctorR0GImp<SR,DR >::make(function)

template <class SR, class DR>
inline RWTFunctorR0<SR>
RWTFunctorR0GImp<SR, DR>::make(CalleeSignature function)
{
    return new RWTFunctorR0GImp<SR, DR>(function);
}

template <class SR, class DR>
inline
RWTFunctorR0GImp<SR, DR>::RWTFunctorR0GImp(CalleeSignature function)
    : function_(function)
{
}

template <class SR, class DR>
inline
RWTFunctorR0GImp<SR, DR>::~RWTFunctorR0GImp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctorR0GImp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctorR0GImp_h__
