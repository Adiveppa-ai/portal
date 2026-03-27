#ifndef __rw_functor_RWTFunctor0MImp_h__
#define __rw_functor_RWTFunctor0MImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWTFunctor0MImp.h#1 $
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
 * and whose encapsulated function is a member that takes no callee
 * arguments.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWFunctor0.h>
#include <rw/functor/RWFunctor0Imp.h>

#  define RWFunctor0MImp RWTFunctor0MImp
#  define rwMakeFunctor0M rwtMakeFunctor0M

//-- Group: RWTFunctor0Imp
//--
//-- Example:
//--   class star{
//--     public:
//--      void draw() { cout << "drawing a star " << endl; }
//--   };
//--
//--
//--   int main () {
//--
//--     star s;
//--
//--        // Create an RWTFunctor0 with no callee arguments.
//--     RWFunctor0 functor = rwtMakeFunctor0( 0, s, &star::draw );
//--
//--        // Invoking 'functor' will draw the star \'s\'.
//--     functor();
//--
//--     return 0;
//--   }
//--

template <class Callee, class DR>
class RWTFunctor0MImp : public RWFunctor0Imp
{

public:

    // Destructor
    ~RWTFunctor0MImp(void);

    // The signature of the functor invocation.
    typedef void (*CallerSignature)(void);

    // The signature of the encapsulated function's invocation.
    typedef DR(Callee::*CalleeSignature)(void);

    // The type of the object that the method will be invoked upon.
    typedef Callee   CalleeType;

    // The declared type of the encapsulated function's return value.
    typedef DR DRType;

    // Dynamically construct an instance of RWTFunctor0MImp and bind it to
    // the returned RWFunctor0 handle instance.
    static RWFunctor0
    make(Callee& callee, CalleeSignature function);

    // Invoke the encapsulated function passing in the callee argument.
    virtual void
    run(void) const;

protected:

    // The RWTFunctor0MImp constructor, only for internal use.
    RWTFunctor0MImp(Callee& callee, CalleeSignature function);

private:

    RWTFunctor0MImp(const RWTFunctor0MImp& second);

    RWTFunctor0MImp&
    operator=(const RWTFunctor0MImp& second);

private:
    // The object on which the method will be invoked.
    Callee&           callee_;

    // The encapsulated function.
    CalleeSignature   function_;

};



//-- A macro for ease of use in creating new 'RWTFunctor0MImp' bodies.

/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee)"
 * instead.
 *
 * Macro to create an RWFunctor0 set to call <tt>callee.function()</tt>.
 * \a function must have signature <tt>DR (Caller::*)(void)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeFunctor0M", "Use rwBind() instead")
#define rwtMakeFunctor0M(Callee,callee,DR,function) \
   RWTFunctor0MImp<Callee,DR >::make(callee,function)

template <class Callee, class DR>
inline RWFunctor0
RWTFunctor0MImp<Callee, DR>::make(Callee& callee, CalleeSignature function)
{
    return new RWTFunctor0MImp<Callee, DR>(callee, function);
}

template <class Callee, class DR>
inline
RWTFunctor0MImp<Callee, DR>::RWTFunctor0MImp(Callee& callee, CalleeSignature function)
    : callee_(callee),
      function_(function)
{
}

template <class Callee, class DR>
inline
RWTFunctor0MImp<Callee, DR>::~RWTFunctor0MImp(void)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/RWTFunctor0MImp.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_RWTFunctor0MImp_h__
