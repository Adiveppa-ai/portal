#ifndef __rw_thread_rwtMakeThreadFunction_h__
#define __rw_thread_rwtMakeThreadFunction_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/rwtMakeThreadFunction.h#1 $
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

#include <rw/thread/RWThreadFunction.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/functor0.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define rwMakeThreadFunction    rwtMakeThreadFunction
#  define rwMakeThreadFunctionG   rwtMakeThreadFunctionG
#  define rwMakeThreadFunctionGA1 rwtMakeThreadFunctionGA1
#  define rwMakeThreadFunctionGA2 rwtMakeThreadFunctionGA2
#  define rwMakeThreadFunctionGA3 rwtMakeThreadFunctionGA3
#  define rwMakeThreadFunctionM   rwtMakeThreadFunctionM
#  define rwMakeThreadFunctionMA1 rwtMakeThreadFunctionMA1
#  define rwMakeThreadFunctionMA2 rwtMakeThreadFunctionMA2
#  define rwMakeThreadFunctionMA3 rwtMakeThreadFunctionMA3

RW_SUPPRESS_DEPRECATED_WARNINGS

/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(function)" instead.
 *
 * Creates an RWThreadFunction set to call <tt>\a function()</tt>.
 * \a function must have signature <tt>\a R (*)(void)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeThreadFunctionG", "Use RWThreadFunction::make(...) instead")
#define rwtMakeThreadFunctionG(R,function) \
   RWThreadFunction::make(RWTFunctor0GImp<R >::make(function))

/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(function)" instead.
 *
 * Creates an RWThreadFunction set to call <tt>\a function()</tt>.
 */
template <class R>
RW_DEPRECATE_FUNC("Use RWThreadFunction::make(...) instead")
inline RWThreadFunction
rwtMakeThreadFunction(R(*function)(void))
{
    return rwtMakeThreadFunctionG(R, function);
}


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, a1))"
 * instead.
 *
 * Creates an RWThreadFunction set to call <tt>\a function(\a a1)</tt>.
 * \a function must have signature <tt>\a R (*)(\a A1)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeThreadFunctionGA1", "Use RWThreadFunction::make(rwBind(...)) instead")
#define rwtMakeThreadFunctionGA1(R,function,A1,a1) \
   RWThreadFunction::make(RWTFunctor0GA1Imp<R,A1  >::make(function,a1))


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, a1))"
 * instead.
 *
 * Creates an RWThreadFunction set to call <tt>\a function(\a a1)</tt>.
 * \a a1 must be convertible to an instance of type \c A1.
 */
template <class R, class A1, class AA1>
RW_DEPRECATE_FUNC("Use RWThreadFunction::make(rwBind(...)) instead")
inline RWThreadFunction
rwtMakeThreadFunction(R(*function)(A1),
                      AA1 a1)
{
    return rwtMakeThreadFunctionGA1(R, function, A1, a1);
}


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, a1, a2))"
 * instead.
 *
 * Creates an RWThreadFunction set to call
 * <tt>\a function(\a a1,\a a2)</tt>. \a function must have signature
 * <tt>\a R (*)(\a A1,\a A2)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeThreadFunctionGA2", "Use RWThreadFunction::make(rwBind(...)) instead")
#define rwtMakeThreadFunctionGA2(R,function,A1,a1,A2,a2) \
   RWThreadFunction::make(RWTFunctor0GA2Imp<R,A1,A2  >::make(function,a1,a2))


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, a1, a2))"
 * instead.
 *
 * Creates an RWThreadFunction set to call
 * <tt>\a function(\a a1,\a a2)</tt>. \a a1 and \a a2 must be convertible to
 * instances of types \c A1 and \c A2 respectively.
 */
template <class R, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use RWThreadFunction::make(rwBind(...)) instead")
inline RWThreadFunction
rwtMakeThreadFunction(R(*function)(A1, A2),
                      AA1 a1,
                      AA2 a2)
{
    return rwtMakeThreadFunctionGA2(R, function, A1, a1, A2, a2);
}


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, a1, a2, a3))"
 * instead.
 *
 * Creates an RWThreadFunction set to call
 * <tt>\a function(\a a1,\a a2,\a a3)</tt>. \a function must have signature
 * <tt>\a R (*)(\a A1,\a A2,\a A3)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeThreadFunctionGA3", "Use RWThreadFunction::make(rwBind(...)) instead")
#define rwtMakeThreadFunctionGA3(R,function,A1,a1,A2,a2,A3,a3) \
   RWThreadFunction::make(RWTFunctor0GA3Imp<R,A1,A2,A3 >::make(function,a1,a2,a3))


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, a1, a2, a3))"
 * instead.
 *
 * Creates an RWThreadFunction set to call
 * <tt>\a function(\a a1,\a a2,\a a3)</tt>. \a a1, \c a2, and \a a3 must be
 * convertible to instances of types \c A1, \c A2, and \c A3 respectively.
 */
template <class R, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use RWThreadFunction::make(rwBind(...)) instead")
inline RWThreadFunction
rwtMakeThreadFunction(R(*function)(A1, A2, A3),
                      AA1 a1,
                      AA2 a2,
                      AA3 a3)
{
    return rwtMakeThreadFunctionGA3(R, function, A1, a1, A2, a2, A3, a3);
}


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, callee))"
 * instead.
 *
 * Creates an RWThreadFunction set to call <tt>\a callee.\a function()</tt>.
 * \a function must have signature <tt>\a R (Caller::*)(void)</tt>
 */
RW_DEPRECATE_MACRO("rwtMakeThreadFunctionM", "Use RWThreadFunction::make(rwBind(...)) instead")
#define rwtMakeThreadFunctionM(Callee,callee,R,function) \
   RWThreadFunction::make(RWTFunctor0MImp<Callee,R >::make(callee,function))


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, callee))"
 * instead.
 *
 * Creates an RWThreadFunction set to call <tt>\a callee.\a function()</tt>.
 */
template <class Callee, class R>
RW_DEPRECATE_FUNC("Use RWThreadFunction::make(rwBind(...)) instead")
inline RWThreadFunction
rwtMakeThreadFunction(Callee& callee,
                      R(Callee::*function)(void))
{
    return rwtMakeThreadFunctionM(Callee, callee, R, function);
}


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, callee, a1))"
 * instead.
 *
 * Creates an RWThreadFunction set to call
 * <tt>\a callee.\a function(\a a1)</tt>. \a function must have signature
 * <tt>R (Caller::*)(A1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeThreadFunctionMA1", "Use RWThreadFunction::make(rwBind(...)) instead")
#define rwtMakeThreadFunctionMA1(Callee,callee,R,function,A1,a1) \
   RWThreadFunction::make(RWTFunctor0MA1Imp<Callee,R,A1 >::make(callee,function,a1))


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, callee, a1))"
 * instead.
 *
 * Creates an RWThreadFunction set to call
 * <tt>\a callee.\a function(\a a1)</tt>. \a a1 must be convertible to an
 * instance of \c A1.
 */
template <class Callee, class R, class A1, class AA1>
RW_DEPRECATE_FUNC("Use RWThreadFunction::make(rwBind(...)) instead")
inline RWThreadFunction
rwtMakeThreadFunction(Callee& callee,
                      R(Callee::*function)(A1),
                      AA1 a1)
{
    return rwtMakeThreadFunctionMA1(Callee, callee, R, function, A1, a1);
}


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, callee, a1, a2))"
 * instead.
 *
 * Creates an RWThreadFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2)</tt>. \a function must have
 * signature <tt>\a R (Caller::*)(\a A1,\a A2)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeThreadFunctionMA2", "Use RWThreadFunction::make(rwBind(...)) instead")
#define rwtMakeThreadFunctionMA2(Callee,callee,R,function,A1,a1,A2,a2) \
   RWThreadFunction::make(RWTFunctor0MA2Imp<Callee,R,A1,A2 >::make(callee,function,a1,a2))


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, callee, a1, a2))"
 * instead.
 *
 * Creates an RWThreadFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2)</tt>. \a a1 and \a a2 must be
 * convertible to instances of types \c A1 and \c A2 respectively.
 */
template <class Callee, class R, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use RWThreadFunction::make(rwBind(...)) instead")
inline RWThreadFunction
rwtMakeThreadFunction(Callee& callee,
                      R(Callee::*function)(A1, A2),
                      AA1 a1,
                      AA2 a2)
{
    return rwtMakeThreadFunctionMA2(Callee, callee, R, function, A1, a1, A2, a2);
}

/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, callee, a1, a2, a3))"
 * instead.
 *
 * Creates an RWThreadFunction set to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>. \a function must have
 * signature <tt>\a R (Caller::*)(\a A1,\a A2,\a A3)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeThreadFunctionMA3", "Use RWThreadFunction::make(rwBind(...)) instead")
#define rwtMakeThreadFunctionMA3(Callee,callee,R,function,A1,a1,A2,a2,A3,a3) \
   RWThreadFunction::make(RWTFunctor0MA3Imp<Callee,R,A1,A2,A3 >::make(callee,function,a1,a2,a3))


/**
 * \ingroup rwtMakeThreadFunction
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref RWThreadFunction::make() "RWThreadFunction::make(rwBind(function, callee, a1, a2, a3))"
 * instead.
 *
 * Creates an RWThreadFunction set to call
 * <tt>\a callee.function(\a a1,\a a2,\a a3)</tt>. \a a1, \c a2, and \a a3
 * must be convertible to instances of types \c A1, \c A2, and \c A3
 * respectively.
 */
template <class Callee, class R, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use RWThreadFunction::make(rwBind(...)) instead")
inline RWThreadFunction
rwtMakeThreadFunction(Callee& callee,
                      R(Callee::*function)(A1, A2, A3),
                      AA1 a1,
                      AA2 a2,
                      AA3 a3)
{
    return rwtMakeThreadFunctionMA3(Callee, callee, R, function, A1, a1, A2, a2, A3, a3);
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_thread_rwtMakeThreadFunction_h__
