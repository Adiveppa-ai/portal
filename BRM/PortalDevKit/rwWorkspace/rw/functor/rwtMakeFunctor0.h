#ifndef __rw_functor_rwtMakeFunctor0_h__
#define __rw_functor_rwtMakeFunctor0_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/rwtMakeFunctor0.h#1 $
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
 * This file provides all of the 'rwtMakeFunctor0()' definitions.
 *
 *************************************************************************/

#include <rw/functor/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWTFunctor0GA1Imp.h>
#include <rw/functor/RWTFunctor0GA2Imp.h>
#include <rw/functor/RWTFunctor0GA3Imp.h>
#include <rw/functor/RWTFunctor0GImp.h>
#include <rw/functor/RWTFunctor0MA1Imp.h>
#include <rw/functor/RWTFunctor0MA2Imp.h>
#include <rw/functor/RWTFunctor0MA3Imp.h>
#include <rw/functor/RWTFunctor0MImp.h>

#  define rwMakeFunctor0 rwtMakeFunctor0

//--   The functions for creating new 'RWFunctor0Imp' bodies.
//--
//--   A 'RWFunctor0' handle can be attached to any body that derives from
//--   'RWFunctor0Imp'.  These classes vary in the number of callee arguments
//--   that they handle, and in whether they are invoked on an object or not.
//--   (See 'RWFunctor0Imp' for more information on this.)
//--
//--   The 'rwtMakeFunctor0()' functions are overloaded on the number of arguments,
//--   and template parameters that they take.  The user provides the name of the
//--   function or method that they wish to wrap, along with any callee data that
//--   they wish to store inside the object.  The compiler then extracts the
//--   necessary information to create the functor body.
//--
//--   Once the correct type of functor body has been created, a handle to this
//--   body is returned to the user.

//--    This version of 'rwtMakeFunctor0()' takes no callee arguments and
//--    returns no value.
//--
//--    It can wrap any function that takes no arguments.
//--
//-- Example:
//--
//--   void foo(){}
//--
//--   int main () {
//--     RWFunctor0 functor = rwtMakeFunctor0((void(*)(void))0, foo);
//--   }
//--
//--

/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function)" instead.
 *
 * Template function to create an RWFunctor0 set to call
 * <tt>\a callee()</tt>.
 *
 * \note
 * - The \a caller argument is not used at this time and should be passed as
 * \c NULL.
 */
template <class DR>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWFunctor0
rwtMakeFunctor0(void (*caller)(void), DR(*callee)(void))
{
    RW_UNUSED(caller);
    return rwtMakeFunctor0G(DR, callee);
}

//--    This version of 'rwtMakeFunctor0()' takes one callee argument and
//--    returns no value.
//--
//--    It can wrap any function that takes one argument.
//--
//-- Example:
//--   void foo(int i){}
//--
//--   int main () {
//--     RWFunctor0 functor = rwtMakeFunctor0((void(*)(void)0, foo, 3);
//--   }
//--

/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1)" instead.
 *
 * Template function to create an RWFunctor0 set to call
 * <tt>\a callee(\a a1)</tt>.
 *
 * \note
 * - The \a caller argument is not used at this time and should be passed as
 * \c NULL.
 * - \a a1 must be convertible to instance of type \c A1.
 */
template <class DR, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWFunctor0
rwtMakeFunctor0(void (*caller)(void), DR(*callee)(A1), AA1 a1)
{
    RW_UNUSED(caller);
    return rwtMakeFunctor0GA1(DR, callee, A1, a1);
}


//--    This version of 'rwtMakeFunctor0()' takes two callee arguments and
//--    returns no value.
//--
//--    It can wrap any function that takes two arguments.
//--
//-- Example:
//--   void foo(int i, float f){}
//--
//--   int main () {
//--
//--     RWFunctor0 functor = rwtMakeFunctor0((void(*)(void))0, foo, 3, 2.22);
//--
//--   }
//--

/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2)"
 * instead.
 *
 * Template function to create an RWFunctor0 set to call
 * <tt>\a callee(\a a1,\a a2)</tt>.
 *
 * \note
 * - The \a caller argument is not used at this time and should be passed as
 * \c NULL.
 * - \a a1 and \a a2 must be convertible to instances of types \c A1, and
 * \c A2 respectively.
 */
template <class DR, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWFunctor0
rwtMakeFunctor0(void (*caller)(void), DR(*callee)(A1, A2), AA1 a1, AA2 a2)
{
    RW_UNUSED(caller);
    return rwtMakeFunctor0GA2(DR, callee, A1, a1, A2, a2);
}


//--    This version of 'rwtMakeFunctor0()' takes three callee arguments and
//--    returns no value.
//--
//--    It can wrap any function that takes three arguments.
//--
//-- Example:
//--   void foo(int i, float f, char c){}
//--
//--   int main () {
//--     RWFunctor0 functor = rwtMakeFunctor0((void(*void))0, foo, 3, 2.22, 's');
//--   }
//--
/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, a1, a2, a3)"
 * instead.
 *
 * Template function to create an RWFunctor0 set to call
 * <tt>\a callee(\a a1,\a a2,\a a3)</tt>.
 *
 * \note
 * - The \a caller argument is not used at this time and should be passed as
 * \c NULL.
 * - \a a1, \a a2 and \a a3 must be convertible to instances of types \c A1,
 * \c A2 and \c A3 respectively.
 */
template <class DR, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWFunctor0
rwtMakeFunctor0(void (*caller)(void), DR(*callee)(A1, A2, A3), AA1 a1, AA2 a2, AA3 a3)
{
    RW_UNUSED(caller);
    return rwtMakeFunctor0GA3(DR, callee, A1, a1, A2, a2, A3, a3);
}


//--    This version of 'rwtMakeFunctor0()' takes a callee object but no callee
//--    arguments.  It returns no value.
//--
//--    It can wrap any method that takes no arguments aside from the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--      bar(){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWFunctor0 functor = rwtMakeFunctor0((void(*)(void))0, f, bar);
//--   }
//--

/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee)"
 * instead.
 *
 * Template function to create an RWFunctor0 set to call
 * <tt>\a callee.\a function()</tt>.
 *
 * \note
 * - The \a caller argument is not used at this time and should be passed as
 * \c NULL.
 */
template <class Callee, class DR>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWFunctor0
rwtMakeFunctor0(void (*caller)(void), Callee& callee, DR(Callee::*function)(void))
{
    RW_UNUSED(caller);
    return rwtMakeFunctor0M(Callee, callee, DR, function);
}


//--    This version of 'rwtMakeFunctor0()' takes a callee object and one callee
//--    argument.  It returns no value.
//--
//--    It can wrap any method that takes one argument in addition to the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--      bar(int i){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWFunctor0 functor = rwtMakeFunctor0((void(*)(void))0, f, bar, 3);
//--   }
//--
/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use \ref rwBind() "rwBind(function, callee, a1)"
 * instead.
 *
 * Template function to create an RWFunctor0 set to call
 * <tt>\a callee.\a function(\a a1)</tt>.
 *
 * \note
 * - The \a caller argument is not used at this time and should be passed as
 * \c NULL.
 * - \a a1 must be convertible to instance of type \c A1.
 */
template <class Callee, class DR, class A1, class AA1>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWFunctor0
rwtMakeFunctor0(void (*caller)(void), Callee& callee, DR(Callee::*function)(A1), AA1 a1)
{
    RW_UNUSED(caller);
    return rwtMakeFunctor0MA1(Callee, callee, DR, function, A1, a1);
}


//--    This version of 'rwtMakeFunctor0()' takes a callee object and two callee
//--    arguments.  It returns no value.
//--
//--    It can wrap any method that takes two arguments in addition to the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--      bar(int i, float f){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWFunctor0 functor = rwtMakeFunctor0((void(*)(void))0, f, bar, 3, 4.56);
//--   }
//--
/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, a1, a2)" instead.
 *
 * Template function to create an RWFunctor0 set to call
 * <tt>\a callee.function(\a a1,\a a2)</tt>.
 *
 * \note
 * - The \a caller argument is not used at this time and should be passed as
 * \c NULL.
 * - \a a1 and \a a2 must be convertible to instances of types \c A1 and
 * \c A2 respectively.
 */
template <class Callee, class DR, class A1, class A2, class AA1, class AA2>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWFunctor0
rwtMakeFunctor0(void (*caller)(void), Callee& callee, DR(Callee::*function)(A1, A2), AA1 a1, AA2 a2)
{
    RW_UNUSED(caller);
    return rwtMakeFunctor0MA2(Callee, callee, DR, function, A1, a1, A2, a2);
}


//--    This version of 'rwtMakeFunctor0()' takes a callee object and three callee
//--    arguments.  It returns no value.
//--
//--    It can wrap any method that takes three arguments in addition to the object on
//--    which it is invoked.
//--
//-- Example:
//--   class foo{
//--      bar(int i, float f, char 'c'){}
//--   }
//--
//--   int main () {
//--     foo f;
//--     RWFunctor0 functor = rwtMakeFunctor0((void(*)(void))0, f, bar, 3, 4.56, 'd');
//--   }
//--
/**
 * \ingroup functor0_group
 *
 * \deprecated
 * As of SourcePro 12.5, use
 * \ref rwBind() "rwBind(function, callee, a1, a2, a3)" instead.
 *
 * Template function to create an RWFunctor0 set to call
 * <tt>\a callee.\a function(\a a1,\a a2,\a a3)</tt>
 *
 * \note
 * - The \a caller argument is not used at this time and should be passed as
 * \c NULL.
 * - \a a1, \a a2 and \a a3 must be convertible to instances of types \c A1,
 * \c A2 and \c A3 respectively.
 */
template <class Callee, class DR, class A1, class A2, class A3, class AA1, class AA2, class AA3>
RW_DEPRECATE_FUNC("Use rwBind(...) instead")
RWFunctor0
rwtMakeFunctor0(void (*caller)(void), Callee& callee, DR(Callee::*function)(A1, A2, A3), AA1 a1, AA2 a2, AA3 a3)
{
    RW_UNUSED(caller);
    return rwtMakeFunctor0MA3(Callee, callee, DR, function, A1, a1, A2, a2, A3, a3);
}

RW_RESTORE_DEPRECATED_WARNINGS
#endif

#endif // __rw_functor_rwtMakeFunctor0_h__
