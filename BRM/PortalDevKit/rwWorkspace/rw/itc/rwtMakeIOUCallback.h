#ifndef __rw_itc_rwtMakeIOUCallback_h__
#define __rw_itc_rwtMakeIOUCallback_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/rwtMakeIOUCallback.h#1 $
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


/******************************************************************************

  Template functions and macros for creating IOU callback functors:
  rwtMakeIOUCallback*()

******************************************************************************/

#include <rw/itc/RWTEscrowHandle.h>
#include <rw/itc/RWTIOUResult.h>
#include <rw/itc/pkgdefs.h>
#include <rw/functor/functor1.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define rwMakeIOUCallback    rwtMakeIOUCallback
#  define rwMakeIOUCallbackG   rwtMakeIOUCallbackG
#  define rwMakeIOUCallbackGA1 rwtMakeIOUCallbackGA1
#  define rwMakeIOUCallbackGA2 rwtMakeIOUCallbackGA2
#  define rwMakeIOUCallbackM   rwtMakeIOUCallbackM
#  define rwMakeIOUCallbackMA1 rwtMakeIOUCallbackMA1
#  define rwMakeIOUCallbackMA2 rwtMakeIOUCallbackMA2

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1)" instead.
 *
 * The rwtMakeIOUCallback() helper functions and macros create functors that
 * may be passed to the addCallback() method of an RWTIOUResult. The functor
 * may be created from functions that accept a first argument that is
 * compatible with an RWTIOUResult.
 *
 * Since not all compilers are able to handle templates to the degree
 * required by the rwtMakeIOUCallback() functions, we also provide a
 * corresponding set of macros.
 *
 * The template functions are slightly easier to use and you only have to
 * remember one name. The macros are more portable but they do require more
 * arguments; and because we cannot overload macros, each must have a unique
 * name.
 *
 * Creates an IOU callback functor from a global function, function().
 * \a function must have signature <tt>void(*)(RWTIOUResult )</tt>
 *
 * Macro arguments:
 *
 * <table>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\a Redeemable</td>
 * <td>The redeemable type of the RWTIOUResult.</td>
 * </tr>
 * </table>
 *
 * \example
 * \code
 * void function(RWTIOUResult<int> result);
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallbackG(function, int));
 * \endcode
 * \endexample
 */
RW_DEPRECATE_MACRO("rwtMakeIOUCallbackG", "Use rwBind(...) instead")
#define rwtMakeIOUCallbackG(function, Redeemable)  \
   RWTFunctor1GImp< RWTEscrowHandle<Redeemable >,   \
                   void, RWTIOUResult<Redeemable > >::make(function)

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1)" instead.
 *
 * The rwtMakeIOUCallback() helper functions create functors that may be
 * passed to the addCallback() method of an RWTIOUResult. The functor may be
 * created from functions that accept a first argument that is compatible
 * with an RWTIOUResult.
 *
 * Template function to create an IOU callback functor from a global
 * function, function(), which takes an RWTIOUResult as its only argument.
 *
 * \example
 * \code
 * void function(RWTIOUResult<int> result);
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallback(function));
 * \endcode
 * \endexample
 */
template <class Redeemable>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
inline RWTFunctor1< RWTEscrowHandle<Redeemable> >
rwtMakeIOUCallback(void (*function)(RWTIOUResult<Redeemable>))
{
    return rwtMakeIOUCallbackG(function, Redeemable);
}

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee, rw1)"
 * instead.
 *
 * The rwtMakeIOUCallback() helper functions and macros create functors that
 * may be passed to the addCallback() method of an RWTIOUResult. The functor
 * may be created from functions that accept a first argument that is
 * compatible with an RWTIOUResult.
 *
 * Since not all compilers are able to handle templates to the degree
 * required by the rwtMakeIOUCallback() functions, we also provide a
 * corresponding set of macros.
 *
 * The template functions are slightly easier to use and you only have to
 * remember one name. The macros are more portable but they do require more
 * arguments; and because we cannot overload macros, each must have a unique
 * name.
 *
 * Creates an IOU callback functor from a member function,
 * <tt>\a callee.\a function()</tt>. \a function must have signature
 * <tt>void (Caller::*)(RWTIOUResult)</tt>.
 *
 * Macro Arguments:
 * <table>
 * <tr>
 * <td>\a Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\a Redeemable</td>
 * <td>The redeemable type of the RWTIOUResult.</td>
 * </tr>
 * </table>
 *
 * \example
 * \code
 * class A {
 * public:
 *   void function(RWTIOUResult<int>);  // Member function with no arguments
 * };
 *
 * A a;
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallbackM(A, a, &A::function, int));
 * \endcode
 * \endexample
 */
RW_DEPRECATE_MACRO("rwtMakeIOUCallbackM", "Use rwBind(...) instead")
#define rwtMakeIOUCallbackM(Callee,callee,function,Redeemable)  \
   RWTFunctor1MImp<RWTEscrowHandle<Redeemable >,                \
                  Callee, void,                                 \
                  RWTIOUResult<Redeemable > >::make(callee, function)

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee, rw1)"
 * instead.
 *
 * The rwtMakeIOUCallback() helper functions create functors that may be
 * passed to the addCallback() method of an RWTIOUResult. The functor may be
 * created from functions that accept a first argument that is compatible
 * with an RWTIOUResult.
 *
 * Template function to create an IOU callback functor from a member
 * function, callee.function(), which takes an RWTIOUResult as its only
 * argument.
 *
 * \example
 * \code
 * class A {
 * public:
 *   void function(RWTIOUResult<int> result);  // Member function with no arguments
 * };
 *
 * A a;
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallback(a, &A::function));
 * \endcode
 * \endexample
 */
template <class Redeemable, class Callee>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
inline RWTFunctor1< RWTEscrowHandle<Redeemable> >
rwtMakeIOUCallback(Callee& callee,
                   void (Callee::*function)(RWTIOUResult<Redeemable>))
{
    return rwtMakeIOUCallbackM(Callee, callee, function, Redeemable);
}

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, a1)"
 * instead.
 *
 * The rwtMakeIOUCallback() helper functions and macros create functors that
 * may be passed to the addCallback() method of an RWTIOUResult. The functor
 * may be created from functions that accept a first argument that is
 * compatible with an RWTIOUResult.
 *
 * Since not all compilers are able to handle templates to the degree
 * required by the rwtMakeIOUCallback() functions, we also provide a
 * corresponding set of macros.
 *
 * The template functions are slightly easier to use and you only have to
 * remember one name. The macros are more portable but they do require more
 * arguments; and because we cannot overload macros, each must have a unique
 * name.
 *
 * Creates an IOU callback functor from a global function,
 * function(Redeemable,a1). \a function must have signature
 * <tt>void (*)(RWTIOUResult,A1)</tt>.
 *
 * Macro Arguments:
 * <table>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\a Redeemable</td>
 * <td>The redeemable type of the RWTIOUResult.</td>
 * </tr>
 * <tr>
 * <td>\a A1</td>
 * <td>Type name of the first additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of A1.</td>
 * </tr>
 * </table>
 *
 * \example
 * \code
 * void function(RWTIOUResult<int> result, A1 a1);
 *
 * A1 a1;
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallbackGA1(function, int, A1, a1));
 * \endcode
 * \endexample
 */
RW_DEPRECATE_MACRO("rwtMakeIOUCallbackGA1", "Use rwBind(...) instead")
#define rwtMakeIOUCallbackGA1(function, Redeemable, A1, a1)  \
   RWTFunctor1GA1Imp<RWTEscrowHandle<Redeemable >, void,     \
                    RWTIOUResult<Redeemable >, A1 >::make(function, a1)

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, a1)"
 * instead.
 *
 * The rwtMakeIOUCallback() helper functions create functors that may be
 * passed to the addCallback() method of an RWTIOUResult. The functor may be
 * created from functions that accept a first argument that is compatible
 * with an RWTIOUResult.
 *
 * Template function to create an IOU callback functor from a global
 * function, <tt>\a function(\a a1)</tt>, which takes an RWTIOUResult and
 * one additional argument.
 *
 * \example
 * \code
 * void function(RWTIOUResult<int>, A1);
 *
 * A1 a1;
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallback(function, a1));
 * \endcode
 * \endexample
 */
template<class Redeemable, class A1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
inline RWTFunctor1< RWTEscrowHandle<Redeemable> >
rwtMakeIOUCallback(void (*function)(RWTIOUResult<Redeemable>, A1),
                   A1 a1)
{
    return rwtMakeIOUCallbackGA1(function, Redeemable, A1, a1);
}

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, a1)" instead.
 *
 * The rwtMakeIOUCallback() helper functions and macros create functors that
 * may be passed to the addCallback() method of an RWTIOUResult. The functor
 * may be created from functions that accept a first argument that is
 * compatible with an RWTIOUResult.
 *
 * Since not all compilers are able to handle templates to the degree
 * required by the rwtMakeIOUCallback() functions, we also provide a
 * corresponding set of macros.
 *
 * The template functions are slightly easier to use and you only have to
 * remember one name. The macros are more portable but they do require more
 * arguments; and because we cannot overload macros, each must have a unique
 * name.
 *
 * Creates an IOU callback functor from a member function,
 * callee.function(a1). \a function must have signature
 * <tt>void (Caller::*)(RWTIOUResult,A1)</tt>.
 *
 * Macro Arguments:
 *
 * <table>
 * <tr>
 * <td>\a Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\a Redeemable</td>
 * <td>The redeemable type of the RWTIOUResult.</td>
 * </tr>
 * <tr>
 * <td>\a A1</td>
 * <td>Type name of the first additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of A1.</td>
 * </tr>
 * </table>
 *
 * \example
 * \code
 * class A {
 * public:
 *   void function(RWTIOUResult<int>, A1);  // Member function with 1 argument
 * };
 *
 * A a;
 * A1 a1;
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallbackMA1(A, a, &A::function, int, A1, a1));
 * \endcode
 * \endexample
 */
RW_DEPRECATE_MACRO("rwtMakeIOUCallbackMA1", "Use rwBind(...) instead")
#define rwtMakeIOUCallbackMA1(Callee,callee,function,Redeemable,A1,a1)  \
   RWTFunctor1MA1Imp<RWTEscrowHandle<Redeemable >, Callee, void,        \
                    RWTIOUResult<Redeemable >, A1 >::make(callee, function, a1)

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, a1)" instead.
 *
 * The rwtMakeIOUCallback() helper functions create functors that may be
 * passed to the addCallback() method of an RWTIOUResult. The functor may be
 * created from functions that accept a first argument that is compatible
 * with an RWTIOUResult.
 *
 * Template function to create an IOU callback functor from a member
 * function, <tt>callee.function(a1)</tt>, which takes an RWTIOUResult and
 * one additional argument.
 *
 * \example
 * \code
 * class A {
 * public:
 *   void function(RWTIOUResult<int>, A1);  // Member function with 1 argument
 * };
 *
 * A a;
 * A1 a1;
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallback(a, &A::function, a1));
 * \endcode
 * \endexample
 */
template <class Redeemable, class Callee, class A1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
inline RWTFunctor1< RWTEscrowHandle<Redeemable> >
rwtMakeIOUCallback(Callee& callee,
                   void (Callee::*function)(RWTIOUResult<Redeemable>, A1),
                   A1 a1)
{
    return rwtMakeIOUCallbackMA1(Callee, callee, function, Redeemable, A1, a1);
}

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, a1, a2)"
 * instead.
 *
 * The rwtMakeIOUCallback() helper functions and macros create functors that
 * may be passed to the addCallback() method of an RWTIOUResult. The functor
 * may be created from functions that accept a first argument that is
 * compatible with an RWTIOUResult.
 *
 * Since not all compilers are able to handle templates to the degree
 * required by the rwtMakeIOUCallback() functions, we also provide a
 * corresponding set of macros.
 *
 * The template functions are slightly easier to use and you only have to
 * remember one name. The macros are more portable but they do require more
 * arguments; and because we cannot overload macros, each must have a unique
 * name.
 *
 * Creates an IOU callback functor from a global function, function(a1,a2).
 * \a function must have signature <tt>void (*)(RWTIOUResult,A1,A2)</tt>.
 *
 * Macro Arguments:
 * <table>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\a Redeemable</td>
 * <td>The redeemable type of the RWTIOUResult.</td>
 * </tr>
 * <tr>
 * <td>\a A1</td>
 * <td>Type name of the first additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of A1.</td>
 * </tr>
 * <tr>
 * <td>\a A2</td>
 * <td>Type name of the second additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of A2.</td>
 * </tr>
 * </table>
 *
 * \example
 * \code
 * void function(RWTIOUResult<int>, A1, A2);
 *
 * A1 a1;
 * A2 a2;
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallbackGA2(function, int, A1, a1, A2, a2));
 * \endcode
 * \endexample
 */
RW_DEPRECATE_MACRO("rwtMakeIOUCallbackGA2", "Use rwBind(...) instead")
#define rwtMakeIOUCallbackGA2(function, Redeemable, A1, a1, A2, a2) \
   RWTFunctor1GA2Imp<RWTEscrowHandle<Redeemable >, void,             \
                    RWTIOUResult<Redeemable >, A1, A2 >::make(function, a1, a2)

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, a1, a2)"
 * instead.
 *
 * The rwtMakeIOUCallback() helper functions create functors that may be
 * passed to the addCallback() method of an RWTIOUResult. The functor may be
 * created from functions that accept a first argument that is compatible
 * with an RWTIOUResult.
 *
 * Template function to create an IOU callback functor from a global
 * function, <tt>\a function(\a a1,\a a2)</tt>, which takes an RWTIOUResult
 * and two additional arguments.
 *
 * \example
 * \code
 * void function(RWTIOUResult<int>, A1, A2);
 *
 * A1 a1;
 * A2 a2;
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallback(function, a1, a2));
 * \endcode
 * \endexample
 */
template<class Redeemable, class A1, class A2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
inline RWTFunctor1< RWTEscrowHandle<Redeemable> >
rwtMakeIOUCallback(void (*function)(RWTIOUResult<Redeemable>, A1, A2),
                   A1 a1,
                   A2 a2)
{
    return rwtMakeIOUCallbackGA2(function, Redeemable, A1, a1, A2, a2);
}

// Macro and template function to create an IOU callback functor from a member
// function which takes an RWTIOUResult<R>, and two additional arguments as
// parameters.
/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, a1, a2)" instead.
 *
 * The rwtMakeIOUCallback() helper functions and macros create functors that
 * may be passed to the addCallback() method of an RWTIOUResult. The functor
 * may be created from functions that accept a first argument that is
 * compatible with an RWTIOUResult.
 *
 * Since not all compilers are able to handle templates to the degree
 * required by the rwtMakeIOUCallback() functions, we also provide a
 * corresponding set of macros.
 *
 * The template functions are slightly easier to use and you only have to
 * remember one name. The macros are more portable but they do require more
 * arguments; and because we cannot overload macros, each must have a unique
 * name.
 *
 * Macro Arguments:
 *
 * <table>
 * <tr>
 * <td>\a Callee</td>
 * <td>Type name of the function's class.</td>
 * </tr>
 * <tr>
 * <td>\a callee</td>
 * <td>Expression that results in a reference to a Callee instance.</td>
 * </tr>
 * <tr>
 * <td>\a function</td>
 * <td>Global function pointer.</td>
 * </tr>
 * <tr>
 * <td>\a Redeemable</td>
 * <td>The redeemable type of the RWTIOUResult.</td>
 * </tr>
 * <tr>
 * <td>\a A1</td>
 * <td>Type name of the first additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a1</td>
 * <td>Expression that can be converted to an instance of A1.</td>
 * </tr>
 * <tr>
 * <td>\a A2</td>
 * <td>Type name of the second additional argument.</td>
 * </tr>
 * <tr>
 * <td>\a a2</td>
 * <td>Expression that can be converted to an instance of A2.</td>
 * </tr>
 * </table>
 *
 * Creates an IOU callback functor from a member function,
 * callee.function(a1,a2). \a function must have signature
 * <tt>void (Caller::*)(RWTIOUResult,A1,A2)</tt>.
 *
 * \example
 * \code
 * class A {
 * public:
 *   void function(RWTIOUResult<int>, A1, A2);  // Member function with 2 arguments
 * };
 *
 * A a;
 * A1 a1;
 * A2 a2;
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallbackMA2(A, a, &A::function, int, A1, a1, A2, a2));
 * \endcode
 * \endexample
 */
RW_DEPRECATE_MACRO("rwtMakeIOUCallbackMA2", "Use rwBind(...) instead")
#define rwtMakeIOUCallbackMA2(Callee,callee,function,Redeemable,A1,a1,A2,a2) \
   RWTFunctor1MA2Imp<RWTEscrowHandle<Redeemable >, Callee, void,             \
                    RWTIOUResult<Redeemable >,                               \
                    A1, A2 >::make(callee, function, a1, a2)

/**
 * \relates RWTIOUResult
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, a1, a2)" instead.
 *
 * The rwtMakeIOUCallback() helper functions create functors that may be
 * passed to the addCallback() method of an RWTIOUResult. The functor may be
 * created from functions that accept a first argument that is compatible
 * with an RWTIOUResult.
 *
 * Template function to create an IOU callback functor from a member
 * function, <tt>callee.function(a1,a2)</tt>, which takes an RWTIOUResult
 * and two additional arguments.
 *
 * \example
 * \code
 * class A {
 * public:
 *   void function(RWTIOUResult<int>, A1, A2);  // Member function with 2 arguments
 * };
 *
 * A a;
 * A1 a1;
 * A2 a2;
 * RWTIOUResult<int> iouResult = ...;
 * iouResult.addCallback(rwtMakeIOUCallback(a, function, a1, a2));
 * \endcode
 * \endexample
 */
template <class Redeemable, class Callee, class A1, class A2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
inline RWTFunctor1< RWTEscrowHandle<Redeemable> >
rwtMakeIOUCallback(Callee& callee,
                   void (Callee::*function)(RWTIOUResult<Redeemable>, A1, A2),
                   A1 a1,
                   A2 a2)
{
    return rwtMakeIOUCallbackMA2(Callee, callee, function, Redeemable, A1, a1, A2, a2);
}
#endif

#endif // __rw_itc_rwtMakeIOUCallback_h__
