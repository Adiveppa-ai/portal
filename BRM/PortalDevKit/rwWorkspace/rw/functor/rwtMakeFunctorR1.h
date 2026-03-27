#ifndef __rw_functor_rwtMakeFunctorR1_h__
#define __rw_functor_rwtMakeFunctorR1_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/rwtMakeFunctorR1.h#1 $
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
 * The overloaded rwtMakeFunctorR1() global functions.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctorR1GA1Imp.h>
#include <rw/functor/RWTFunctorR1GA2Imp.h>
#include <rw/functor/RWTFunctorR1GImp.h>
#include <rw/functor/RWTFunctorR1MA1Imp.h>
#include <rw/functor/RWTFunctorR1MA2Imp.h>
#include <rw/functor/RWTFunctorR1MImp.h>

#  define rwMakeFunctorR1 rwtMakeFunctorR1

//--   The functions for creating new 'RWTFunctorR1Imp' bodies.
//--
//--   A RWTFunctorR1 handle can be attached to any body which derives from
//--   'RWTFunctorR1Imp'.  These classes vary in the number of callee arguments
//--   that they handle, and in whether they are invoked on an object or not.
//--   (see RWTFunctorR1Imp for more information on this).
//--
//--   The 'rwtMakeFunctorR1()' functions are overloaded on the number of arguments,
//--   and template parameters that they take.  The user provides the name of the
//--   function or method that they wish to wrap, along with any callee data that
//--   they wish to store inside the object.  The compiler then extracts the
//--   necessary information to create the functor body.
//--
//--   Once the correct type of functor body has been created, a handle to this
//--   body is returned to the user.


//--    This version of 'rwtMakeFunctorR1()' takes no callee arguments and
//--    returns a value.
//--
//--    It can wrap any function that takes one argument, which is to be provided
//--    by the caller.
//--
//-- Example:
//--   short foo(int i){}
//--
//--   int main () {
//--     RWTFunctorR1<short,int> functor = rwtMakeFunctorR1((short(*)(int))0, foo);
//--   }

/**
 * \ingroup functorR1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1)" instead.
 *
 * Template function to create an RWTFunctorR1 set to call
 * <tt>\a callee(s)</tt>.
 *
 * \note
 * - \c s refers to the argument passed when invoking the functor via
 * <tt>RWTFunctorR1<SR,S1>::operator()(S1)</tt>. The argument will be passed
 * through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - Type \c S1 must be convertible to \c D1.
 */
template <class SR, class S1, class DR, class D1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR1<SR, S1>
rwtMakeFunctorR1(SR(*caller)(S1), DR(*callee)(D1))
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR1G(SR, S1, DR, callee, D1);
}


//--    This version of 'rwtMakeFunctorR1()' takes one callee argument and
//--    returns a value.
//--
//--    It can wrap any function that takes two arguments--one provided
//--    by the caller, and one provided by the callee.
//--
//-- Example:
//--   short foo(int i, float f){}
//--
//--   int main () {
//--     RWTFunctorR1<short,int> functor = rwtMakeFunctorR1((short(*)(int))0, foo, 2.22);
//--   }
//--

/**
 * \ingroup functorR1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, a1)"
 * instead.
 *
 * Template function to create an RWTFunctorR1 set to call
 * <tt>\a callee(s,\a a1)</tt>.
 *
 * \note
 * - \c s refers to the argument passed when invoking the functor via
 * <tt>RWTFunctorR1<SR,S1>::operator()(S1)</tt>. The argument will be passed
 * through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - Type \c S1 must be convertible to \c D1.
 * - \a a1 must be convertible to instance of type \c A1.
 */
template <class SR, class S1, class DR, class D1, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR1<SR, S1>
rwtMakeFunctorR1(SR(*caller)(S1), DR(*callee)(D1, A1), AA1 a1)
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR1GA1(SR, S1, DR, callee, D1, A1, a1);
}


//--    This version of 'rwtMakeFunctorR1()' takes two callee arguments and
//--    returns a value.
//--
//--    It can wrap any function that takes three arguments--one provided
//--    by the caller, and two provided by the callee.
//--
//-- Example:
//--   short foo(int i, float f, char c){}
//--
//--   int main () {
//--     RWTFunctorR1<short,int> functor = rwtMakeFunctorR1((short(*)(int))0, foo, 2.22, 's');
//--   }
//--

/**
 * \ingroup functorR1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, rw1, a1, a2)"
 * instead.
 *
 * Template function to create an RWTFunctorR1 set to call
 * <tt>\a callee(s,\a a1,\a a2)</tt>.
 *
 * \note
 * - \c s refers to the argument passed when invoking the functor via
 * <tt>RWTFunctorR1<SR,S1>::operator()(S1)</tt>. The argument will be passed
 * through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - Type \c S1 must be convertible to \c D1.
 * - \a a1 and \a a2 must be convertible to instances of types \c A1 and
 * \c A2 respectively.
 */
template <class SR, class S1, class DR, class D1, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR1<SR, S1>
rwtMakeFunctorR1(SR(*caller)(S1), DR(*callee)(D1, A1, A2), AA1 a1, AA2 a2)
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR1GA2(SR, S1, DR, callee, D1, A1, a1, A2, a2);
}


//--    This version of 'rwtMakeFunctorR1()' takes a callee object but no callee
//--    arguments.  It returns a value.
//--
//--    It can wrap any method that takes one argument in addition to the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--      short bar(int i){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWTFunctorR1<short,int> functor = rwtMakeFunctorR1((short(*)(int))0, f, bar);
//--   }
//--

/**
 * \ingroup functorR1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee, rw1)"
 * instead.
 *
 * Template function to create an RWTFunctorR1 set to call
 * <tt>\a callee.\a function(s)</tt>.
 *
 * \note
 * - \c s refers to the argument passed when invoking the functor via
 * <tt>RWTFunctorR1<SR,S1>::operator()(S1)</tt>. The argument will be passed
 * through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - Type \c S1 must be convertible to \c D1.
 */
template <class SR, class S1, class Callee, class DR, class D1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR1<SR, S1>
rwtMakeFunctorR1(SR(*caller)(S1), Callee& callee, DR(Callee::*function)(D1))
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR1M(SR, S1, Callee, callee, DR, function, D1);
}


//--    This version of 'rwtMakeFunctorR1()' takes a callee object and one callee
//--    argument.  It returns a value.
//--
//--    It can wrap any method that takes two arguments in addition to the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--      short bar(int i, float f){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWTFunctorR1<short,int> functor = rwtMakeFunctorR1((short(*)(int))0, f, bar, 4.56);
//--   }
//--

/**
 * \ingroup functorR1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, a1)" instead.
 *
 * Template function to create an RWTFunctorR1 set to call
 * <tt>\a callee.\a function(s, \a a1)</tt>.
 *
 * \note
 * - \c s refers to the argument passed when invoking the functor via
 * <tt>RWTFunctorR1<SR,S1>::operator()(S1)</tt>. The argument will be passed
 * through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - Type \c S1 must be convertible to \c D1.
 * - \a a1 must be convertible to instance of type \c A1.
 */
template <class SR, class S1, class Callee, class DR, class D1, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR1<SR, S1>
rwtMakeFunctorR1(SR(*caller)(S1), Callee& callee, DR(Callee::*function)(D1, A1), AA1 a1)
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR1MA1(SR, S1, Callee, callee, DR, function, D1, A1, a1);
}


//--    This version of 'rwtMakeFunctorR1()' takes a callee object and two callee
//--    arguments.  It returns a value.
//--
//--    It can wrap any method that takes three arguments in addition to the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--      short bar(int i, float f, char 'c'){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWTFunctorR1<short,int> functor = rwtMakeFunctorR1((short(*)(int))0, f, bar, 4.56, 'd');
//--   }
//--

/**
 * \ingroup functorR1_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, rw1, a1, a2)" instead.
 *
 * Template function to create an RWTFunctorR1 set to call
 * <tt>\a callee.\a function(s,\a a1,\a a2)</tt>.
 *
 * \note
 * - \c s refers to the argument passed when invoking the functor via
 * <tt>RWTFunctorR1<SR,S1>::operator()(S1)</tt>. The argument will be passed
 * through to the associated function.
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - Type \c S1 must be convertible to \c D1.
 * - \a a1 and \a a2 must be convertible to instances of types \c A1 and
 * \c A2 respectively.
 */
template <class SR, class S1, class Callee, class DR, class D1, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR1<SR, S1>
rwtMakeFunctorR1(SR(*caller)(S1), Callee& callee, DR(Callee::*function)(D1, A1, A2), AA1 a1, AA2 a2)
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR1MA2(SR, S1, Callee, callee, DR, function, D1, A1, a1, A2, a2);
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_rwtMakeFunctorR1_h__
