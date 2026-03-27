#ifndef __rw_functor_rwtMakeFunctorR0_h__
#define __rw_functor_rwtMakeFunctorR0_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/rwtMakeFunctorR0.h#1 $
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
 * This file provides all of the 'rwtMakeFunctorR0()' definitions.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctorR0GA1Imp.h>
#include <rw/functor/RWTFunctorR0GA2Imp.h>
#include <rw/functor/RWTFunctorR0GA3Imp.h>
#include <rw/functor/RWTFunctorR0GImp.h>
#include <rw/functor/RWTFunctorR0MA1Imp.h>
#include <rw/functor/RWTFunctorR0MA2Imp.h>
#include <rw/functor/RWTFunctorR0MA3Imp.h>
#include <rw/functor/RWTFunctorR0MImp.h>

#  define rwMakeFunctorR0 rwtMakeFunctorR0


//--   The functions for creating new 'RWFunctorR0Imp' bodies.
//--
//--   A 'RWFunctorR0' handle can be attached to any body that derives from
//--   'RWFunctorR0Imp'.  These classes vary in the number of callee arguments
//--   that they handle, and in whether they are invoked on an object or not.
//--   (See 'RWFunctorR0Imp' for more information on this.)
//--
//--   The 'rwtMakeFunctorR0()' functions are overloaded on the number of arguments,
//--   and template parameters that they take.  The user provides the name of the
//--   function or method that they wish to wrap, along with any callee data that
//--   they wish to store inside the object.  The compiler then extracts the
//--   necessary information to create the functor body.
//--
//--   Once the correct type of functor body has been created, a handle to this
//--   body is returned to the user.

//--    This version of 'rwtMakeFunctorR0()' takes no callee arguments and
//--    returns a value.
//--
//--    It can wrap any function that takes no arguments and returns a value.
//--
//-- Example:
//--   int foo(){}
//--
//--   int main () {
//--     RWTFunctorR0<int> functor = rwtMakeFunctorR0((int(*)(void))0, foo);
//--   }
//--
//--

/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function)" instead.
 *
 * Template function to create an RWTFunctorR0 set to call
 * <tt>\a callee()</tt>.
 *
 * \note
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 */
template <class SR, class DR>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR0<SR>
rwtMakeFunctorR0(SR(*caller)(void), DR(*callee)(void))
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR0G(SR, DR, callee);
}


//--    This version of 'rwtMakeFunctorR0()' takes one callee argument and
//--    returns a value.
//--
//--    It can wrap any function that takes one argument.
//--
//-- Example:
//--   short foo(int i){}
//--
//--   int main () {
//--     RWTFunctorR0<short> functor = rwtMakeFunctorR0((short(*)(void)0, foo, 3);
//--   }
//--
/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1)" instead.
 *
 * Template function to create an RWTFunctorR0 set to call
 * <tt>\a callee(\a a1)</tt>.
 *
 * \note
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - \a a1 must be convertible to instance of type \c A1.
 */
template <class SR, class DR, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR0<SR>
rwtMakeFunctorR0(SR(*caller)(void), DR(*callee)(A1), AA1 a1)
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR0GA1(SR, DR, callee, A1, a1);
}


//--    This version of 'rwtMakeFunctorR0()' takes two callee arguments and
//--    returns a value.
//--
//--    It can wrap any function that takes two arguments.
//--
//-- Example:
//--   short foo(int i, float f){}
//--
//--   int main () {
//--     RWTFunctorR0<short> functor = rwtMakeFunctorR0((short(*)(void))0, foo, 3, 2.22);
//--   }
//--

/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2)"
 * instead.
 *
 * Template function to create an RWTFunctorR0 set to call
 * <tt>\a callee(\a a1, \a a2)</tt>.
 *
 * \note
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - \a a1 and \a a2 must be convertible to instances of types \c A1 and
 * \c A2 respectively.
 */
template <class SR, class DR, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR0<SR>
rwtMakeFunctorR0(SR(*caller)(void), DR(*callee)(A1, A2), AA1 a1, AA2 a2)
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR0GA2(SR, DR, callee, A1, a1, A2, a2);
}

//--    This version of 'rwtMakeFunctorR0()' takes three callee arguments and
//--    returns a value.
//--
//--    It can wrap any function that takes three arguments.
//--
//-- Example:
//--   short foo(int i, float f, char c){}
//--
//--   int main () {
//--     RWTFunctorR0<short> functor = rwtMakeFunctorR0((short(*void))0, foo, 3, 2.22, 's');
//--   }
//--

/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2, a3)"
 * instead.
 *
 * Template function to create an RWTFunctorR0 set to call
 * <tt>\a callee(\a a1, \a a2, \a a3)</tt>.
 *
 * \note
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - \a a1, \a a2 and \a a3 must be convertible to instances of types \c A1,
 * \c A2 and \c A3 respectively.
 */
template <class SR, class DR, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR0<SR>
rwtMakeFunctorR0(SR(*caller)(void), DR(*callee)(A1, A2, A3), AA1 a1, AA2 a2, AA3 a3)
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR0GA3(SR, DR, callee, A1, a1, A2, a2, A3, a3);
}


//--    This version of 'rwtMakeFunctorR0()' takes a callee object but no callee
//--    arguments.  It returns a value.
//--
//--    It can wrap any method that takes no arguments aside from the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--     short bar(){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWTFunctorR0<short> functor = rwtMakeFunctorR0((short(*)(void))0, f, bar);
//--   }
//--


/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee)"
 * instead.
 *
 * Template function to create an RWTFunctorR0 set to call
 * <tt>\a callee.\a function()</tt>.
 *
 * \note
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 */
template <class SR, class Callee, class DR>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR0<SR>
rwtMakeFunctorR0(SR(*caller)(void), Callee& callee, DR(Callee::*function)(void))
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR0M(SR, Callee, callee, DR, function);
}


//--    This version of 'rwtMakeFunctorR0()' takes a callee object and one callee
//--    argument.  It returns a value.
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
//--     RWTFunctorR0<short> functor = rwtMakeFunctorR0((short(*)(void))0, f, bar, 3);
//--   }
//--

/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee, a1)"
 * instead.
 *
 * Template function to create an RWTFunctorR0 set to call
 * <tt>\a callee.\a function(\a a1)</tt>.
 *
 * \note
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - \a a1 must be convertible to instance of type \c A1.
 */
template <class SR, class Callee, class DR, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR0<SR>
rwtMakeFunctorR0(SR(*caller)(void), Callee& callee, DR(Callee::*function)(A1), AA1 a1)
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR0MA1(SR, Callee, callee, DR, function, A1, a1);
}


//--    This version of 'rwtMakeFunctorR0()' takes a callee object and two callee
//--    arguments.  It returns a value.
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
//--     RWTFunctorR0<short> functor = rwtMakeFunctorR0((short(*)(void))0, f, bar, 3, 4.56);
//--   }
//--

/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, a1, a2)" instead.
 *
 * Template function to create an RWTFunctorR0 set to call
 * <tt>\a callee.\a function(\a a1, \a a2)</tt>.
 *
 * \note
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - \a a1 and \a a2 must be convertible to instances of types \c A1 and
 * \c A2 respectively.
 */
template <class SR, class Callee, class DR, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR0<SR>
rwtMakeFunctorR0(SR(*caller)(void), Callee& callee, DR(Callee::*function)(A1, A2), AA1 a1, AA2 a2)
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR0MA2(SR, Callee, callee, DR, function, A1, a1, A2, a2);
}


//--    This version of 'rwtMakeFunctorR0()' takes a callee object and three callee
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
//--     RWTFunctorR0<short> functor = rwtMakeFunctorR0((short(*)(void))0, f, bar, 3, 4.56, 'd');
//--   }
//--

/**
 * \ingroup functorR0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, a1, a2, a3)" instead.
 *
 * Template function to create an RWTFunctorR0 set to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>.
 *
 * \note
 * - The \a caller parameter is used only to allow the compiler to deduce
 * type \c SR. You may use any function with an appropriate signature or
 * simply pass a \c NULL pointer cast to the appropriate type as done in the
 * example above.
 * - \c DR must be convertible to \c SR.
 * - \a a1, \a a2 and \a a3 must be convertible to instances of types \c A1,
 * \c A2 and \c A3 respectively.
 */
template <class SR, class Callee, class DR, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWTFunctorR0<SR>
rwtMakeFunctorR0(SR(*caller)(void), Callee& callee, DR(Callee::*function)(A1, A2, A3), AA1 a1, AA2 a2, AA3 a3)
{
    RW_UNUSED(caller);
    return rwtMakeFunctorR0MA3(SR, Callee, callee, DR, function, A1, a1, A2, a2, A3, a3);
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_rwtMakeFunctorR0_h__
