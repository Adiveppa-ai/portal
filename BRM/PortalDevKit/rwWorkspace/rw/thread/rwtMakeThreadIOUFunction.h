#ifndef __rw_thread_rwtMakeThreadIOUFunction_h__
#define __rw_thread_rwtMakeThreadIOUFunction_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/rwtMakeThreadIOUFunction.h#1 $
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

#include <rw/thread/RWTThreadIOUFunction.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/functorR0.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define rwMakeThreadIOUFunction    rwtMakeThreadIOUFunction
#  define rwMakeThreadIOUFunctionG   rwtMakeThreadIOUFunctionG
#  define rwMakeThreadIOUFunctionGA1 rwtMakeThreadIOUFunctionGA1
#  define rwMakeThreadIOUFunctionGA2 rwtMakeThreadIOUFunctionGA2
#  define rwMakeThreadIOUFunctionGA3 rwtMakeThreadIOUFunctionGA3
#  define rwMakeThreadIOUFunctionM   rwtMakeThreadIOUFunctionM
#  define rwMakeThreadIOUFunctionMA1 rwtMakeThreadIOUFunctionMA1
#  define rwMakeThreadIOUFunctionMA2 rwtMakeThreadIOUFunctionMA2
#  define rwMakeThreadIOUFunctionMA3 rwtMakeThreadIOUFunctionMA3

/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(function)"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call <tt>\a function()</tt>.
 * \a function must have signature <tt>\a R (*)(void)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeThreadIOUFunctionG", "Use RWTThreadIOUFunction<R>::make(...) instead")
#define rwtMakeThreadIOUFunctionG(R,function) \
   RWTThreadIOUFunction<R >::make(RWTFunctorR0GImp<R,R >::make(function))

/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(function)"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call <tt>\a function()</tt>.
 */
template <class R>
RW_DEPRECATE_FUNC("Use RWTThreadIOUFunction<R>::make(...) instead")
inline RWTThreadIOUFunction<R>
rwtMakeThreadIOUFunction(R(*function)(void))
{
    return rwtMakeThreadIOUFunctionG(R, function);
}

/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, a1))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call <tt>\a function(\a a1)</tt>.
 * \a function must have signature <tt>\a R (*)(\a A1)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeThreadIOUFunctionGA1", "Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeThreadIOUFunctionGA1(R,function,A1,a1) \
   RWTThreadIOUFunction<R >::make(RWTFunctorR0GA1Imp<R,R,A1 >::make(function,a1))


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, a1))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call <tt>\a function(\a a1)</tt>.
 * \a a1 must be convertible to an instance of type \c A1.
 */
template <class R, class A1, class AA1>
RW_DEPRECATE_FUNC("Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
inline RWTThreadIOUFunction<R>
rwtMakeThreadIOUFunction(R(*function)(A1),
                         AA1 a1)
{
    return rwtMakeThreadIOUFunctionGA1(R, function, A1, a1);
}


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, a1, a2))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a function(\a a1,\a a2)</tt>. \a function must have signature
 * <tt>\a R (*)(\a A1,\a A2)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeThreadIOUFunctionGA2", "Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeThreadIOUFunctionGA2(R,function,A1,a1,A2,a2) \
   RWTThreadIOUFunction<R >::make(RWTFunctorR0GA2Imp<R,R,A1,A2 >::make(function,a1,a2))


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, a1, a2))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a function(\a a1,\a a2)</tt>. \a a1 and \a a2 must be convertible to
 * instances of types \c A1 and \c A2 respectively.
 */
template <class R, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
inline RWTThreadIOUFunction<R>
rwtMakeThreadIOUFunction(R(*function)(A1, A2),
                         AA1 a1,
                         AA2 a2)
{
    return rwtMakeThreadIOUFunctionGA2(R, function, A1, a1, A2, a2);
}


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, a1, a2, a3))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a function(\a a1,\a a2,\a a3)</tt>. \a function must have signature
 * <tt>\a R (*)(\a A1,\a A2,\a A3)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeThreadIOUFunctionGA3", "Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeThreadIOUFunctionGA3(R,function,A1,a1,A2,a2,A3,a3) \
   RWTThreadIOUFunction<R >::make(RWTFunctorR0GA3Imp<R,R,A1,A2,A3 >::make(function,a1,a2,a3))


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, a1, a2, a3))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a function(\a a1,\a a2,\a a3)</tt>. \a a1, \a a2, and \a a3 must be
 * convertible to instances of types \c A1, \c A2, and \c A3 respectively.
 */
template <class R, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
inline RWTThreadIOUFunction<R>
rwtMakeThreadIOUFunction(R(*function)(A1, A2, A3),
                         AA1 a1,
                         AA2 a2,
                         AA3 a3)
{
    return rwtMakeThreadIOUFunctionGA3(R, function, A1, a1, A2, a2, A3, a3);
}


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, callee))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a callee.\a function()</tt>. \a function must have signature
 * <tt>\a R (Caller::*)(void)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeThreadIOUFunctionM", "Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeThreadIOUFunctionM(Callee,callee,R,function) \
   RWTThreadIOUFunction<R >::make(RWTFunctorR0MImp<R,Callee,R >::make(callee,function))


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, callee))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a callee.\a function()</tt>.
 */
template <class Callee, class R>
RW_DEPRECATE_FUNC("Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
inline RWTThreadIOUFunction<R>
rwtMakeThreadIOUFunction(Callee& callee,
                         R(Callee::*function)(void))
{
    return rwtMakeThreadIOUFunctionM(Callee, callee, R, function);
}


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, callee, a1))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a callee.\a function(\a a1)</tt>. \a function must have signature
 * <tt>\a R (Caller::*)(\a A1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeThreadIOUFunctionMA1", "Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeThreadIOUFunctionMA1(Callee,callee,R,function,A1,a1) \
   RWTThreadIOUFunction<R >::make(RWTFunctorR0MA1Imp<R,Callee,R,A1 >::make(callee,function,a1))


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, callee, a1))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a callee.\a function(\a a1)</tt>. \a a1 must be convertible to an
 * instance of \c A1.
 */
template <class Callee, class R, class A1, class AA1>
RW_DEPRECATE_FUNC("Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
inline RWTThreadIOUFunction<R>
rwtMakeThreadIOUFunction(Callee& callee,
                         R(Callee::*function)(A1),
                         AA1 a1)
{
    return rwtMakeThreadIOUFunctionMA1(Callee, callee, R, function, A1, a1);
}


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, callee, a1, a2))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2)</tt>. \a function must have
 * signature <tt>R (Caller::*)(A1,A2)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeThreadIOUFunctionMA2", "Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeThreadIOUFunctionMA2(Callee,callee,R,function,A1,a1,A2,a2) \
   RWTThreadIOUFunction<R >::make(RWTFunctorR0MA2Imp<R,Callee,R,A1,A2 >::make(callee,function,a1,a2))

/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, callee, a1, a2))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2)</tt>. \a a1 and \a a2 must be
 * convertible to instances of types \c A1 and \c A2 respectively.
 */
template <class Callee, class R, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
inline RWTThreadIOUFunction<R>
rwtMakeThreadIOUFunction(Callee& callee,
                         R(Callee::*function)(A1, A2),
                         AA1 a1,
                         AA2 a2)
{
    return rwtMakeThreadIOUFunctionMA2(Callee, callee, R, function, A1, a1, A2, a2);
}


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, callee, a1, a2, a3))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>. \a function must have
 * signature <tt>\a R (Caller::*)(\a A1,\a A2,\a A3)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeThreadIOUFunctionMA3", "Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeThreadIOUFunctionMA3(Callee,callee,R,function,A1,a1,A2,a2,A3,a3) \
   RWTThreadIOUFunction<R >::make(RWTFunctorR0MA3Imp<R,Callee,R,A1,A2,A3 >::make(callee,function,a1,a2,a3))


/**
 * \ingroup rwtMakeThreadIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTThreadIOUFunction::make() "RWTThreadIOUFunction<R>::make(rwBind(function, callee, a1, a2, a3))"
 * instead.
 *
 * Creates an RWTThreadIOUFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>. \a a1, \a a2, and
 * \a a3 must be convertible to instances of types \c A1, \c A2, and \c A3
 * respectively.
 */
template <class Callee, class R, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use RWTThreadIOUFunction<R>::make(rwBind(...)) instead")
inline RWTThreadIOUFunction<R>
rwtMakeThreadIOUFunction(Callee& callee,
                         R(Callee::*function)(A1, A2, A3),
                         AA1 a1,
                         AA2 a2,
                         AA3 a3)
{
    return rwtMakeThreadIOUFunctionMA3(Callee, callee, R, function, A1, a1, A2, a2, A3, a3);
}
#endif

#endif // __rw_thread_rwtMakeThreadIOUFunction_h__
