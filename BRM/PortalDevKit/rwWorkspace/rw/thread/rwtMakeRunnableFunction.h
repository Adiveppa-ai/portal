#ifndef __rw_thread_rwtMakeRunnableFunction_h__
#define __rw_thread_rwtMakeRunnableFunction_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/rwtMakeRunnableFunction.h#1 $
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

#include <rw/thread/RWRunnableFunction.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/functor0.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define rwMakeRunnableFunction    rwtMakeRunnableFunction
#  define rwMakeRunnableFunctionG   rwtMakeRunnableFunctionG
#  define rwMakeRunnableFunctionGA1 rwtMakeRunnableFunctionGA1
#  define rwMakeRunnableFunctionGA2 rwtMakeRunnableFunctionGA2
#  define rwMakeRunnableFunctionGA3 rwtMakeRunnableFunctionGA3
#  define rwMakeRunnableFunctionM   rwtMakeRunnableFunctionM
#  define rwMakeRunnableFunctionMA1 rwtMakeRunnableFunctionMA1
#  define rwMakeRunnableFunctionMA2 rwtMakeRunnableFunctionMA2
#  define rwMakeRunnableFunctionMA3 rwtMakeRunnableFunctionMA3

/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(function)"
 * instead.
 *
 * Creates an RWRunnableFunction set to call <tt>\a function()</tt>.
 * \a function must have signature <tt>\a R (*)(void)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableFunctionG", "Use RWRunnableFunction::make(...) instead")
#define rwtMakeRunnableFunctionG(R,function) \
   RWRunnableFunction::make(RWTFunctor0GImp<R >::make(function))


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(function)"
 * instead.
 *
 * Creates an RWRunnableFunction set to call <tt>\a function()</tt>.
 */
template <class R>
RW_DEPRECATE_FUNC("Use RWRunnableFunction::make(...) instead")
RWRunnableFunction
rwtMakeRunnableFunction(R(*function)(void))
{
    return rwtMakeRunnableFunctionG(R, function);
}


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, a1))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call <tt>\a function(\a a1)</tt>.
 * \a function must have signature <tt>\a R (*)(\a A1)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableFunctionGA1", "Use RWRunnableFunction::make(rwBind(...)) instead")
#define rwtMakeRunnableFunctionGA1(R,function,A1,a1) \
   RWRunnableFunction::make(RWTFunctor0GA1Imp<R,A1 >::make(function,a1))


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, a1))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call <tt>\a function(\a a1)</tt>.
 * Parameter \a a1 must be convertible to an instance of type \c A1.
 */
template <class R, class A1, class AA1>
RW_DEPRECATE_FUNC("Use RWRunnableFunction::make(rwBind(...)) instead")
inline RWRunnableFunction
rwtMakeRunnableFunction(R(*function)(A1),
                        AA1 a1)
{
    return rwtMakeRunnableFunctionGA1(R, function, A1, a1);
}


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, a1, a2))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a function(\a a1,\a a2)</tt>. \a function must have signature
 * <tt>\a R (*)(\a A1,\a A2)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableFunctionGA2", "Use RWRunnableFunction::make(rwBind(...)) instead")
#define rwtMakeRunnableFunctionGA2(R,function,A1,a1,A2,a2) \
   RWRunnableFunction::make(RWTFunctor0GA2Imp<R,A1,A2 >::make(function,a1,a2))


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, a1, a2))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a function(\a a1,\a a2)</tt>. Parameters \a a1 and \a a2 must be
 * convertible to instances of types \c A1 and \c A2 respectively.
 */
template <class R, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use RWRunnableFunction::make(rwBind(...)) instead")
inline RWRunnableFunction
rwtMakeRunnableFunction(R(*function)(A1, A2),
                        AA1 a1,
                        AA2 a2)
{
    return rwtMakeRunnableFunctionGA2(R, function, A1, a1, A2, a2);
}


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, a1, a2, a3))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a function(\a a1,\a a2,\a a3)</tt>. \a function must have signature
 * <tt>\a R (*)(\a A1,\a A2,\a A3)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableFunctionGA3", "Use RWRunnableFunction::make(rwBind(...)) instead")
#define rwtMakeRunnableFunctionGA3(R,function,A1,a1,A2,a2,A3,a3) \
   RWRunnableFunction::make(RWTFunctor0GA3Imp<R,A1,A2,A3 >::make(function,a1,a2,a3))


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, a1, a2, a3))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a function(\a a1,\a a2,\a a3)</tt>. Parameters \a a1, \c a2, and
 * \a a3 must be convertible to instances of types \c A1, \c A2, and \c A3
 * respectively.
 */
template <class R, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use RWRunnableFunction::make(rwBind(...)) instead")
inline RWRunnableFunction
rwtMakeRunnableFunction(R(*function)(A1, A2, A3),
                        AA1 a1,
                        AA2 a2,
                        AA3 a3)
{
    return rwtMakeRunnableFunctionGA3(R, function, A1, a1, A2, a2, A3, a3);
}


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, callee))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a callee.\a function()</tt>. \a function must have signature
 * <tt>\a R (Caller::*)(void)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableFunctionM", "Use RWRunnableFunction::make(rwBind(...)) instead")
#define rwtMakeRunnableFunctionM(Callee,callee,R,function) \
   RWRunnableFunction::make(RWTFunctor0MImp<Callee,R >::make(callee,function))


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, callee))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a callee.\a function()</tt>.
 */
template <class Callee, class R>
RW_DEPRECATE_FUNC("Use RWRunnableFunction::make(rwBind(...)) instead")
inline RWRunnableFunction
rwtMakeRunnableFunction(Callee& callee,
                        R(Callee::*function)(void))
{
    return rwtMakeRunnableFunctionM(Callee, callee, R, function);
}


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, callee, a1))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a callee.\a function(\a a1)</tt>. \a function must have signature
 * <tt>\a R (Caller::*)(\a A1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableFunctionMA1", "Use RWRunnableFunction::make(rwBind(...)) instead")
#define rwtMakeRunnableFunctionMA1(Callee,callee,R,function,A1,a1) \
   RWRunnableFunction::make(RWTFunctor0MA1Imp<Callee,R,A1 >::make(callee,function,a1))


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, callee, a1))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a callee.\a function(\a a1)</tt>. Parameter \a a1 must be
 * convertible to an instance of \c A1.
 */
template <class Callee, class R, class A1, class AA1>
RW_DEPRECATE_FUNC("Use RWRunnableFunction::make(rwBind(...)) instead")
inline RWRunnableFunction
rwtMakeRunnableFunction(Callee& callee,
                        R(Callee::*function)(A1),
                        AA1 a1)
{
    return rwtMakeRunnableFunctionMA1(Callee, callee, R, function, A1, a1);
}


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, callee, a1, a2))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2)</tt>. \a function must have
 * signature <tt>\a R (Caller::*)(\a A1,\a A2)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableFunctionMA2", "Use RWRunnableFunction::make(rwBind(...)) instead")
#define rwtMakeRunnableFunctionMA2(Callee,callee,R,function,A1,a1,A2,a2) \
   RWRunnableFunction::make(RWTFunctor0MA2Imp<Callee,R,A1,A2 >::make(callee,function,a1,a2))


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, callee, a1, a2))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2)</tt>. Parameters \a a1 and \a a2
 * must be convertible to instances of types \c A1 and \c A2 respectively.
 */
template <class Callee, class R, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use RWRunnableFunction::make(rwBind(...)) instead")
inline RWRunnableFunction
rwtMakeRunnableFunction(Callee& callee,
                        R(Callee::*function)(A1, A2),
                        AA1 a1,
                        AA2 a2)
{
    return rwtMakeRunnableFunctionMA2(Callee, callee, R, function, A1, a1, A2, a2);
}


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, callee, a1, a2, a3))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>. \a function must have
 * signature <tt>\a R (Caller::*)(\a A1,\a A2,\a A3)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableFunctionMA3", "Use RWRunnableFunction::make(rwBind(...)) instead")
#define rwtMakeRunnableFunctionMA3(Callee,callee,R,function,A1,a1,A2,a2,A3,a3) \
   RWRunnableFunction::make(RWTFunctor0MA3Imp<Callee,R,A1,A2,A3 >::make(callee,function,a1,a2,a3))


/**
 * \ingroup rwtMakeRunnableFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWRunnableFunction::make() "RWRunnableFunction::make(rwBind(function, callee, a1, a2, a3))"
 * instead.
 *
 * Creates an RWRunnableFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>. Parameters \a a1,
 * \a a2, and \a a3 must be convertible to instances of types \c A1, \c A2,
 * and \c A3 respectively.
 */
template <class Callee, class R, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use RWRunnableFunction::make(rwBind(...)) instead")
inline RWRunnableFunction
rwtMakeRunnableFunction(Callee& callee,
                        R(Callee::*function)(A1, A2, A3),
                        AA1 a1,
                        AA2 a2,
                        AA3 a3)
{
    return rwtMakeRunnableFunctionMA3(Callee, callee, R, function, A1, a1, A2, a2, A3, a3);
}
#endif

#endif // __rw_thread_rwtMakeRunnableFunction_h__
