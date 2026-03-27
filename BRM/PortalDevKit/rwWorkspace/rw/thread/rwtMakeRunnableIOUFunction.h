#ifndef __rw_thread_rwtMakeRunnableIOUFunction_h__
#define __rw_thread_rwtMakeRunnableIOUFunction_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/rwtMakeRunnableIOUFunction.h#1 $
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

#include <rw/thread/RWTRunnableIOUFunction.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/functorR0.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define rwMakeRunnableIOUFunction    rwtMakeRunnableIOUFunction
#  define rwMakeRunnableIOUFunctionG   rwtMakeRunnableIOUFunctionG
#  define rwMakeRunnableIOUFunctionGA1 rwtMakeRunnableIOUFunctionGA1
#  define rwMakeRunnableIOUFunctionGA2 rwtMakeRunnableIOUFunctionGA2
#  define rwMakeRunnableIOUFunctionGA3 rwtMakeRunnableIOUFunctionGA3
#  define rwMakeRunnableIOUFunctionM   rwtMakeRunnableIOUFunctionM
#  define rwMakeRunnableIOUFunctionMA1 rwtMakeRunnableIOUFunctionMA1
#  define rwMakeRunnableIOUFunctionMA2 rwtMakeRunnableIOUFunctionMA2
#  define rwMakeRunnableIOUFuncitonMA3 rwtMakeRunnableIOUFunctionMA3

/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(function)"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call <tt>\a function()</tt>.
 * \a function must have signature <tt>\a R (*)(void)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableIOUFunctionG", "Use RWTRunnableIOUFunction<R>::make(...) instead")
#define rwtMakeRunnableIOUFunctionG(R,function) \
   RWTRunnableIOUFunction<R >::make(RWTFunctorR0GImp<R,R >::make(function))


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(function)"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call <tt>\a function()</tt>.
 * \a function must have signature <tt>R (*)(void)</tt>
 */
template <class R>
RW_DEPRECATE_FUNC("Use RWTRunnableIOUFunction<R>::make(...) instead")
inline RWTRunnableIOUFunction<R>
rwtMakeRunnableIOUFunction(R(*function)(void))
{
    return rwtMakeRunnableIOUFunctionG(R, function);
}


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, a1))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a function(\a a1)</tt>. \a function must have signature
 * <tt>\a R (*)(A1)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableIOUFunctionGA1", "Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeRunnableIOUFunctionGA1(R,function,A1,a1) \
   RWTRunnableIOUFunction<R >::make(RWTFunctorR0GA1Imp<R,R,A1 >::make(function,a1))

/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, a1))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a function(\a a1)</tt>. \a a1 must be convertible to an instance of
 * type \c A1.
 */
template <class R, class A1, class AA1>
RW_DEPRECATE_FUNC("Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
inline RWTRunnableIOUFunction<R>
rwtMakeRunnableIOUFunction(R(*function)(A1),
                           AA1 a1)
{
    return rwtMakeRunnableIOUFunctionGA1(R, function, A1, a1);
}

/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, a1, a2))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a function(\a a1,\a a2)</tt>. \a function must have signature
 * <tt>\a R (*)(\a A1,\a A2)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableIOUFunctionGA2", "Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeRunnableIOUFunctionGA2(R,function,A1,a1,A2,a2) \
   RWTRunnableIOUFunction<R >::make(RWTFunctorR0GA2Imp<R,R,A1,A2 >::make(function,a1,a2))

/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, a1, a2))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a function(\a a1,\a a2)</tt>. \a a1 and \a a2 must be convertible to
 * instances of types \c A1 and \c A2 respectively.
 */
template <class R, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
inline RWTRunnableIOUFunction<R>
rwtMakeRunnableIOUFunction(R(*function)(A1, A2),
                           AA1 a1,
                           AA2 a2)
{
    return rwtMakeRunnableIOUFunctionGA2(R, function, A1, a1, A2, a2);
}


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, a1, a2, a3))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a function(\a a1,\a a2,\a a3)</tt>. \a function must have signature
 * <tt>\a R (*)(\a A1,\a A2,\a A3)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableIOUFunctionGA3", "Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeRunnableIOUFunctionGA3(R,function,A1,a1,A2,a2,A3,a3) \
   RWTRunnableIOUFunction<R >::make(RWTFunctorR0GA3Imp<R,R,A1,A2,A3 >::make(function,a1,a2,a3))


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, a1, a2, a3))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a function(\a a1,\a a2,\a a3)</tt>. \a a1, \a a2, and \a a3 must be
 * convertible to instances of types \c A1, \c A2, and \c A3 respectively.
 */
template <class R, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
inline RWTRunnableIOUFunction<R>
rwtMakeRunnableIOUFunction(R(*function)(A1, A2, A3),
                           AA1 a1,
                           AA2 a2,
                           AA3 a3)
{
    return rwtMakeRunnableIOUFunctionGA3(R, function, A1, a1, A2, a2, A3, a3);
}


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, callee))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a callee.\a function()</tt>. \a function must have signature
 * <tt>\a R (Caller::*)(void)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableIOUFunctionM", "Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeRunnableIOUFunctionM(Callee,callee,R,function) \
   RWTRunnableIOUFunction<R >::make(RWTFunctorR0MImp<R,Callee,R >::make(callee,function))


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, callee))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a callee.\a function()</tt>.
 */
template <class Callee, class R>
RW_DEPRECATE_FUNC("Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
inline RWTRunnableIOUFunction<R>
rwtMakeRunnableIOUFunction(Callee& callee,
                           R(Callee::*function)(void))
{
    return rwtMakeRunnableIOUFunctionM(Callee, callee, R, function);
}


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, callee, a1))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a callee.\a function(\a a1)</tt>. \a function must have signature
 * <tt>\a R (Caller::*)(\a A1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableIOUFunctionMA1", "Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeRunnableIOUFunctionMA1(Callee,callee,R,function,A1,a1) \
   RWTRunnableIOUFunction<R >::make(RWTFunctorR0MA1Imp<R,Callee,R,A1 >::make(callee,function,a1))


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, callee, a1))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a callee.\a function(\a a1)</tt>. \a a1 must be convertible to an
 * instance of \c A1.
 */
template <class Callee, class R, class A1, class AA1>
RW_DEPRECATE_FUNC("Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
inline RWTRunnableIOUFunction<R>
rwtMakeRunnableIOUFunction(Callee& callee,
                           R(Callee::*function)(A1),
                           AA1 a1)
{
    return rwtMakeRunnableIOUFunctionMA1(Callee, callee, R, function, A1, a1);
}


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, callee, a1, a2))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2)</tt>. \a function must have
 * signature <tt>\a R (Caller::*)(\a A1,\a A2)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableIOUFunctionMA2", "Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeRunnableIOUFunctionMA2(Callee,callee,R,function,A1,a1,A2,a2) \
   RWTRunnableIOUFunction<R >::make(RWTFunctorR0MA2Imp<R,Callee,R,A1,A2 >::make(callee,function,a1,a2))


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, callee, a1, a2))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2)</tt>. \a a1 and \a a2 must be
 * convertible to instances of types \c A1 and \c A2 respectively.
 */
template <class Callee, class R, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
inline RWTRunnableIOUFunction<R>
rwtMakeRunnableIOUFunction(Callee& callee,
                           R(Callee::*function)(A1, A2),
                           AA1 a1,
                           AA2 a2)
{
    return rwtMakeRunnableIOUFunctionMA2(Callee, callee, R, function, A1, a1, A2, a2);
}


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, callee, a1, a2, a3))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>. \a function must have
 * signature <tt>\a R (Caller::*)(\a A1,\a A2,\a A3)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableIOUFunctionMA3", "Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
#define rwtMakeRunnableIOUFunctionMA3(Callee,callee,R,function,A1,a1,A2,a2,A3,a3) \
   RWTRunnableIOUFunction<R >::make(RWTFunctorR0MA3Imp<R,Callee,R,A1,A2,A3 >::make(callee,function,a1,a2,a3))


/**
 * \ingroup rwtMakeRunnableIOUFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWTRunnableIOUFunction::make() "RWTRunnableIOUFunction<R>::make(rwBind(function, callee, a1, a2, a3))"
 * instead.
 *
 * Creates an RWTRunnableIOUFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>. \a a1, \c a2, and
 * \a a3 must be convertible to instances of types \c A1, \c A2, and \c A3
 * respectively.
 */
template <class Callee, class R, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use RWTRunnableIOUFunction<R>::make(rwBind(...)) instead")
inline RWTRunnableIOUFunction<R>
rwtMakeRunnableIOUFunction(Callee& callee,
                           R(Callee::*function)(A1, A2, A3),
                           AA1 a1,
                           AA2 a2,
                           AA3 a3)
{
    return rwtMakeRunnableIOUFunctionMA3(Callee, callee, R, function, A1, a1, A2, a2, A3, a3);
}
#endif

#endif // __rw_thread_rwtMakeRunnableIOUFunction_h__
