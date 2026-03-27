#ifndef __rw_functor_rwtMakeFunctor2_h__
#define __rw_functor_rwtMakeFunctor2_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/rwtMakeFunctor2.h#1 $
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
 *
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor2GA1Imp.h>
#include <rw/functor/RWTFunctor2GA2Imp.h>
#include <rw/functor/RWTFunctor2GImp.h>
#include <rw/functor/RWTFunctor2MA1Imp.h>
#include <rw/functor/RWTFunctor2MA2Imp.h>
#include <rw/functor/RWTFunctor2MImp.h>

#  define rwMakeFunctor2 rwtMakeFunctor2

//--   The functions for creating new 'RWTFunctor2Imp' bodies.
//--
//--   A 'RWTFunctor2' handle can be attached to any body which derives from
//--   'RWTFunctor2Imp'.  These classes vary in the number of callee arguments
//--   that they handle, and in whether they are invoked on an object or not.
//--   (see 'RWTFunctor2Imp' for more information on this).
//--
//--   The 'rwtMakeFunctor2()' functions are overloaded on the number of arguments,
//--   and template parameters that they take.  The user provides the name of the
//--   function or method that they wish to wrap, along with any callee data that
//--   they wish to store inside the object.  The compiler then extracts the
//--   necessary information to create the functor body.
//--
//--   Once the correct type of functor body has been created, a handle to this
//--   body is returned to the user.


//--    This version of 'rwtMakeFunctor2()' takes no callee arguments and
//--    returns no value.
//--
//--    It can wrap any function that takes two arguments, which are to be provided
//--    by the caller.
//--
//-- Example:
//--   void foo(int i, short s){}
//--
//--   int main () {
//--     RWTFunctor2<int,short> functor = rwtMakeFunctor2((void(*)(int,short))0, foo);
//--   }

/**
 * \ingroup functor2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, rw2)"
 * instead.
 *
 * Template function to create an RWTFunctor2 set to call
 * <tt>\a callee(s1,s2)</tt>.
 *
 * \note
 * - \c s1 and \c s2 refer to the arguments passed when invoking the functor
 * via <tt>RWTFunctor2<S1,S2>::operator()(S1,S2)</tt>. The arguments will be
 * passed through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * types \c S1 and \c S2. You may use any function with an appropriate
 * signature or simply pass a \c NULL pointer cast to the appropriate type
 * as done in the example above.
 * - Types \c S1 and \c S2 must be convertible to \c D1 and \c D2
 * respectively.
 */
template <class S1, class S2, class DR, class D1, class D2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<S1, S2>
rwtMakeFunctor2(void (*caller)(S1, S2), DR(*callee)(D1, D2))
{
    RW_UNUSED(caller);
    return rwtMakeFunctor2G(S1, S2, DR, callee, D1, D2);
}


//--    This version of 'rwtMakeFunctor2()' takes one callee argument and
//--    returns no value.
//--
//--    It can wrap any function that takes three arguments--two provided
//--    by the caller, and one provided by the callee.
//--
//-- Example:
//--   void foo(int i, float f, short s){}
//--
//--   int main () {
//--     RWTFunctor2<int,float> functor = rwtMakeFunctor2((void(*)(int,float))0, foo, 2);
//--   }
//--

/**
 * \ingroup functor2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, rw2, a1)"
 * instead.
 *
 * Template function to create an RWTFunctor2 set to call
 * <tt>\a callee(s1,s2,\a a1)</tt>.
 *
 * \note
 * - \c s1 and \c s2 refer to the arguments passed when invoking the functor
 * via <tt>RWTFunctor2<S1,S2>::operator()(S1,S2)</tt>. The arguments will be
 * passed through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * types \c S1 and \c S2. You may use any function with an appropriate
 * signature or simply pass a \c NULL pointer cast to the appropriate type
 * as done in the example above.
 * - Types \c S1 and \c S2 must be convertible to \c D1 and \c D2
 * respectively.
 * - \a a1 must be convertible to instance of types \c A1.
 */
template <class S1, class S2, class DR, class D1, class D2, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<S1, S2>
rwtMakeFunctor2(void (*caller)(S1, S2), DR(*callee)(D1, D2, A1), AA1 a1)
{
    RW_UNUSED(caller);
    return rwtMakeFunctor2GA1(S1, S2, DR, callee, D1, D2, A1, a1);
}


//--    This version of 'rwtMakeFunctor2()' takes two callee arguments and
//--    returns no value.
//--
//--    It can wrap any function that takes four arguments--two provided
//--    by the caller, and two provided by the callee.
//--
//-- Example:
//--   void foo(int i, float f, char c, short s){}
//--
//--   int main () {
//--     RWTFunctor1<int, float> functor = rwtMakeFunctor2((void(*)(int, float))0, foo, 's', 2);
//--   }
//--

/**
 * \ingroup functor2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, rw1, rw2, a1, a2)" instead.
 *
 * Template function to create an RWTFunctor2 set to call
 * <tt>\a callee(s1,s2,\a a1,\a a2)</tt>.
 *
 * \note
 * - \c s1 and \c s2 refer to the arguments passed when invoking the functor
 * via <tt>RWTFunctor2<S1,S2>::operator()(S1,S2)</tt>. The arguments will be
 * passed through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * types \c S1 and \c S2. You may use any function with an appropriate
 * signature or simply pass a \c NULL pointer cast to the appropriate type
 * as done in the example above.
 * - Types \c S1 and \c S2 must be convertible to \c D1 and \c D2
 * respectively.
 * - \a a1 and \a a2 must be convertible to instances of types \c A1 and
 * \c A2 respectively.
 */
template <class S1, class S2, class DR, class D1, class D2, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<S1, S2>
rwtMakeFunctor2(void (*caller)(S1, S2), DR(*callee)(D1, D2, A1, A2), AA1 a1, AA2 a2)
{
    RW_UNUSED(caller);
    return rwtMakeFunctor2GA2(S1, S2, DR, callee, D1, D2, A1, a1, A2, a2);
}


//--    This version of 'rwtMakeFunctor1()' takes a callee object but no callee
//--    arguments.  It returns no value.
//--
//--    It can wrap any method that takes two arguments in addition to the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--      bar(int i, short s){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWTFunctor2<int,short> functor = rwtMakeFunctor2((void(*)(int,short))0, f, bar);
//--   }
//--

/**
 * \ingroup functor2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2)" instead.
 *
 * Template function to create an RWTFunctor2 set to call
 * <tt>\a callee.\a function(s1,s2)</tt>.
 *
 * \note
 * - \c s1 and \c s2 refer to the arguments passed when invoking the functor
 * via <tt>RWTFunctor2<S1,S2>::operator()(S1,S2)</tt>. The arguments will be
 * passed through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * types \c S1 and \c S2. You may use any function with an appropriate
 * signature or simply pass a \c NULL pointer cast to the appropriate type
 * as done in the example above.
 * - Types \c S1 and \c S2 must be convertible to \c D1 and \c D2
 * respectively.
 */
template <class S1, class S2, class Callee, class DR, class D1, class D2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<S1, S2>
rwtMakeFunctor2(void (*caller)(S1, S2), Callee& callee, DR(Callee::*function)(D1, D2))
{
    RW_UNUSED(caller);
    return rwtMakeFunctor2M(S1, S2, Callee, callee, DR, function, D1, D2);
}


//--    This version of 'rwtMakeFunctor2()' takes a callee object and one callee
//--    argument.  It returns no value.
//--
//--    It can wrap any method that takes three arguments in addition to the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--      bar(int i, float f, short s){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWTFunctor2<int,float> functor = rwtMakeFunctor2((void(*)(int,float))0, f, bar, 4);
//--   }
//--

/**
 * \ingroup functor2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2, a1)" instead.
 *
 * Template function to create an RWTFunctor2 set to call
 * <tt>\a callee.\a function(s1,s2,\a a1)</tt>.
 *
 * \note
 * - \c s1 and \c s2 refer to the arguments passed when invoking the functor
 * via <tt>RWTFunctor2<S1,S2>::operator()(S1,S2)</tt>. The arguments will be
 * passed through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * types \c S1 and \c S2. You may use any function with an appropriate
 * signature or simply pass a \c NULL pointer cast to the appropriate type
 * as done in the example above.
 * - Types \c S1 and \c S2 must be convertible to \c D1 and \c D2
 * respectively.
 * - \a a1 must be convertible to instance of type \c A1.
 */
template <class S1, class S2, class Callee, class DR, class D1, class D2, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<S1, S2>
rwtMakeFunctor2(void (*caller)(S1, S2), Callee& callee, DR(Callee::*function)(D1, D2, A1), AA1 a1)
{
    RW_UNUSED(caller);
    return rwtMakeFunctor2MA1(S1, S2, Callee, callee, DR, function, D1, D2, A1, a1);
}


//--    This version of 'rwtMakeFunctor2()' takes a callee object and two callee
//--    arguments.  It returns no value.
//--
//--    It can wrap any method that takes four arguments in addition to the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--      bar(int i, float f, char 'c', short s){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWTFunctor2<int,float> functor = rwtMakeFunctor2((void(*)(int,float))0, f, bar, 'd',3);
//--   }
//--

/**
 * \ingroup functor2_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, rw2, a1, a2)" instead.
 *
 * Template function to create an RWTFunctor2 set to call
 * <tt>\a callee.\a function(s1,s2,\a a1,\a a2)</tt>.
 *
 * \note
 * - \c s1 and \c s2 refer to the arguments passed when invoking the functor
 * via <tt>RWTFunctor2<S1,S2>::operator()(S1,S2)</tt>. The arguments will be
 * passed through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * types \c S1 and \c S2. You may use any function with an appropriate
 * signature or simply pass a \c NULL pointer cast to the appropriate type
 * as done in the example above.
 * - Types \c S1 and \c S2 must be convertible to \c D1 and \c D2
 * respectively.
 * - \a a1 and \a a2 must be convertible to instances of types \c A1 and
 * \c A2 respectively.
 */
template <class S1, class S2, class Callee, class DR, class D1, class D2, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctor2<S1, S2>
rwtMakeFunctor2(void (*caller)(S1, S2), Callee& callee, DR(Callee::*function)(D1, D2, A1, A2), AA1 a1, AA2 a2)
{
    RW_UNUSED(caller);
    return rwtMakeFunctor2MA2(S1, S2, Callee, callee, DR, function, D1, D2, A1, a1, A2, a2);
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_rwtMakeFunctor2_h__
