#ifndef __rw_thread_rwtMakeRunnableGuard_h__
#define __rw_thread_rwtMakeRunnableGuard_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/rwtMakeRunnableGuard.h#1 $
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


/*****************************************************************************

  rwtMakeRunnableGuard - Make functions for creating runnable guard functors

******************************************************************************/

#include <rw/thread/RWRunnableGuard.h>
#include <rw/thread/pkgdefs.h>
#include <rw/functor/functorR0.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define rwMakeRunnableGuard    rwtMakeRunnableGuard
#  define rwMakeRunnableGuardG   rwtMakeRunnableGuardG
#  define rwMakeRunnableGuardGA1 rwtMakeRunnableGuardGA1
#  define rwMakeRunnableGuardGA2 rwtMakeRunnableGuardGA2
#  define rwMakeRunnableGuardGA3 rwtMakeRunnableGuardGA3
#  define rwMakeRunnableGuardM   rwtMakeRunnableGuardM
#  define rwMakeRunnableGuardMA1 rwtMakeRunnableGuardMA1
#  define rwMakeRunnableGuardMA2 rwtMakeRunnableGuardMA2
#  define rwMakeRunnableGuardMA3 rwtMakeRunnableGuardMA3

/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function)" instead.
 *
 * Creates an RWRunnableGuard set to call <tt>\a function()</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableGuardG", "Use rwBind(...) instead")
#define rwtMakeRunnableGuardG(DR,function) \
   rwtMakeFunctorR0G(bool,DR,function)


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function)" instead.
 *
 * Creates an RWRunnableGuard to call <tt>\a function()</tt>, which returns
 * \c DR.
 */
template <class DR>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWRunnableGuard
rwtMakeRunnableGuard(DR(*function)(void))
{
    return rwtMakeFunctorR0G(bool, DR, function);
}


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1)" instead.
 *
 * Creates an RWRunnableGuard set to call <tt>\a function(\a a1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableGuardGA1", "Use rwBind(...) instead")
#define rwtMakeRunnableGuardGA1(DR,function,A1,a1) \
   rwtMakeFunctorR0GA1(bool,DR,function,A1,a1)


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1)" instead.
 *
 * Creates an RWRunnableGuard to call <tt>\a function(\a a1)</tt>, which
 * returns \c DR.
 */
template <class DR, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWRunnableGuard
rwtMakeRunnableGuard(DR(*function)(A1), AA1 a1)
{
    return rwtMakeFunctorR0GA1(bool, DR, function, A1, a1);
}


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2)"
 * instead.
 *
 * Creates an RWRunnableGuard set to call <tt>\a function(\a a1,\a a2)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableGuardGA2", "Use rwBind(...) instead")
#define rwtMakeRunnableGuardGA2(DR,function,A1,a1,A2,a2) \
   rwtMakeFunctorR0GA2(bool,DR,function,A1,a1,A2,a2)


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2)"
 * instead.
 *
 * Creates an RWRunnableGuard to call <tt>\a function(\a a1,\a a2)</tt>,
 * which returns \c DR.
 */
template <class DR, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWRunnableGuard
rwtMakeRunnableGuard(DR(*function)(A1, A2), AA1 a1, AA2 a2)
{
    return rwtMakeFunctorR0GA2(bool, DR, function, A1, a1, A2, a2);
}


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2, a3)"
 * instead.
 *
 * Creates an RWRunnableGuard set to call
 * <tt>\a function(\a a1,\a a2,\a a3)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableGuardGA3", "Use rwBind(...) instead")
#define rwtMakeRunnableGuardGA3(DR,function,A1,a1,A2,a2,A3,a3) \
   rwtMakeFunctorR0GA3(bool,DR,function,A1,a1,A2,a2,A3,a3)


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2, a3)"
 * instead.
 *
 * Creates an RWRunnableGuard to call
 * <tt>\a function(\a a1,\a a2,\a a3)</tt>, which returns \c DR.
 */
template <class DR, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWRunnableGuard
rwtMakeRunnableGuard(DR(*function)(A1, A2, A3), AA1 a1, AA2 a2, AA3 a3)
{
    return rwtMakeFunctorR0GA3(bool, DR, function, A1, a1, A2, a2, A3, a3);
}


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee)"
 * instead.
 *
 * Creates an RWRunnableGuard set to call <tt>\a callee.\a function()</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableGuardM", "Use rwBind(...) instead")
#define rwtMakeRunnableGuardM(Callee,callee,DR,function) \
   rwtMakeFunctorR0M(bool,Callee,callee,DR,function)


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee)"
 * instead.
 *
 * Creates an RWRunnableGuard to call <tt>\a callee.\a function()</tt>,
 * which returns \c DR.
 */
template <class Callee, class DR>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWRunnableGuard
rwtMakeRunnableGuard(Callee& callee, DR(Callee::*function)(void))
{
    return rwtMakeFunctorR0M(bool, Callee, callee, DR, function);
}


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee, a1)"
 * instead.
 *
 * Creates an RWRunnableGuard set to call
 * <tt>\a callee.\a function(\a a1)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableGuardMA1", "Use rwBind(...) instead")
#define rwtMakeRunnableGuardMA1(Callee,callee,DR,function,A1,a1) \
   rwtMakeFunctorR0MA1(bool,Callee,callee,DR,function,A1,a1)

/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee, a1)"
 * instead.
 *
 * Creates an RWRunnableGuard to call <tt>\a callee.\a function(\a a1)</tt>,
 * which returns \c DR.
 */
template <class Callee, class DR, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWRunnableGuard
rwtMakeRunnableGuard(Callee& callee, DR(Callee::*function)(A1), AA1 a1)
{
    return rwtMakeFunctorR0MA1(bool, Callee, callee, DR, function, A1, a1);
}


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, a1, a2)" instead.
 *
 * Creates an RWRunnableGuard set to call
 * <tt>\a callee.\a function(\a a1,\a a2)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableGuardMA2", "Use rwBind(...) instead")
#define rwtMakeRunnableGuardMA2(Callee,callee,DR,function,A1,a1,A2,a2) \
   rwtMakeFunctorR0MA2(bool,Callee,callee,DR,function,A1,a1,A2,a2)


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, a1, a2)" instead.
 *
 * Creates an RWRunnableGuard to call
 * <tt>\a callee.\a function(\a a1,\a a2)</tt>, which returns \c DR.
 */
template <class Callee, class DR, class A1, class AA1, class A2, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWRunnableGuard
rwtMakeRunnableGuard(Callee& callee, DR(Callee::*function)(A1, A2), AA1 a1, AA2 a2)
{
    return rwtMakeFunctorR0MA2(bool, Callee, callee, DR, function, A1, a1, A2, a2);
}


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, a1, a2, a3)" instead.
 *
 * Creates an RWRunnableGuard set to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>.
 */
RW_DEPRECATE_MACRO("rwtMakeRunnableGuardMA3", "Use rwBind(...) instead")
#define rwtMakeRunnableGuardMA3(Callee,callee,DR,function,A1,a1,A2,a2,A3,a3) \
   rwtMakeFunctorR0MA3(bool,Callee,callee,DR,function,A1,a1,A2,a2,A3,a3)


/**
 * \ingroup rwtMakeRunnableGuard
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, a1, a2, a3)" instead.
 *
 * Creates an RWRunnableGuard to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>, which returns \c DR.
 */
template <class Callee, class DR, class A1, class AA1, class A2, class AA2, class A3, class AA3>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWRunnableGuard
rwtMakeRunnableGuard(Callee& callee, DR(Callee::*function)(A1, A2, A3), AA1 a1, AA2 a2, AA3 a3)
{
    return rwtMakeFunctorR0MA3(bool, Callee, callee, DR, function, A1, a1, A2, a2, A3, a3);
}
#endif

#endif // __rw_thread_rwtMakeRunnableGuard_h__
