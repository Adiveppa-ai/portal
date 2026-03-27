#ifndef __rw_trace_userdefs_h__
#define __rw_trace_userdefs_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/userdefs.h#1 $
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

 The following macros must be defined in order to configure a package:

  RW_USER_TRACE_LEVEL

  Specifies the level of trace event reporting that is to be compiled into
  the package code.  Also used to detect whether package was configured.

*****************************************************************************/

#include <rw/trace/pkgdefs.h>

#if !defined(RW_USER_TRACE_LEVEL)
#  define RW_USER_TRACE_LEVEL 0
#endif

#include <rw/trace/tracemacros.h>

#ifdef DOXYGEN
/**
 * \ingroup execution_tracing_package
 *
 * Declares a traceable package. \a packageName, to specifies the name of
 * the package to be traced. The \a packageName must be a valid C++
 * identifier. This macro is normally placed at the end of the header file
 * that defines the trace macros for that package. For an example, see the
 * trace header file \c userdefs.h or the \c pkgdefs.h file for any other
 * package in the Threads Module.
 */
#  define RW_TRACE_DECLARE_TRACEABLE_PACKAGE(packageName)

/**
 * \ingroup execution_tracing_package
 *
 * Provides a definition for a static variable defined by the matching
 * #RW_TRACE_DECLARE_TRACEABLE_PACKAGE macro. This macro must be placed in
 * some implementation file (.cpp) for your application. For an example, see
 * the trace source file \c userdefs.cpp or the \c pkgdefs.cpp file in any
 * of the other packages in the Threads Module.
 */
#  define RW_TRACE_DEFINE_TRACEABLE_PACKAGE(packageName)

/**
 * \ingroup execution_tracing_package
 *
 * Declares a non-template class as traceable. \a className specifies the
 * name of the class to be traced. The \a className must be a valid C++
 * identifier. This macro must be placed in the header file for a class
 * before the class declaration. Otherwise, it generates an
 * <tt>undefined symbol</tt> compile error.
 */
#  define RW_USER_DECLARE_TRACEABLE_CLASS(className)

/**
 * \ingroup execution_tracing_package
 *
 * Provides a definition for a static variable defined by the matching
 * #RW_USER_DECLARE_TRACEABLE_CLASS macro. This macro must be placed in the
 * implementation (\c .cpp) file for the class.
 */
#  define RW_USER_DEFINE_TRACEABLE_CLASS(className)

/**
 * \ingroup execution_tracing_package
 *
 * Declares a template class as traceable. \a className specifies the name
 * of the class to be traced. The \a className must be a valid C++
 * identifier. This macro must be placed in the header file for a class
 * before the class declaration. Otherwise, it generates an
 * <tt>undefined symbol</tt> compile error.
 */
#  define RW_USER_DECLARE_TRACEABLE_TEMPLATE_CLASS(className)

/**
 * \ingroup execution_tracing_package
 *
 * Provides a definition for a static variable defined by the matching
 * #RW_USER_DECLARE_TRACEABLE_TEMPLATE_CLASS macro. This macro must be
 * placed in the implementation file (typically a \c .cc file) for the
 * template class.
 */
#  define RW_USER_DEFINE_TRACEABLE_TEMPLATE_CLASS(className)

/**
 * \ingroup execution_tracing_package
 *
 * Defines a member function to be traceable. \a functionTag is used as the
 * environment variable to control trace event generation for this function.
 * It also appears in the trace output. The \a functionTag parameter must be
 * a valid C++ identifier, and it must be enclosed in quotation marks, as a
 * string. The \a functionTag parameter is usually a string of the form
 * \c "ClassName_functionName". \a className specifies the name of the class
 * to which the member or friend function belongs. It must match the
 * \a className used in the #RW_USER_DECLARE_TRACEABLE_CLASS macro for the
 * class.
 */
#  define RW_USER_TRACEABLE_MEMBER(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * Defines a static member function to be traceable. \a functionTag is used
 * as the environment variable to control trace event generation for this
 * function. It also appears in the trace output. The \a functionTag
 * parameter must be a valid C++ identifier, and it must be enclosed in
 * quotation marks, as a string. The \a functionTag parameter is usually a
 * string of the form \c "ClassName_functionName". \a className specifies
 * the name of the class to which the member or friend function belongs. It
 * must match the \a className used in the #RW_USER_DECLARE_TRACEABLE_CLASS
 * macro for the class.
 */
#  define RW_USER_TRACEABLE_STATIC_MEMBER(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * Defines a friend function to be traceable. \a functionTag is used as the
 * environment variable to control trace event generation for this function.
 * It also appears in the trace output. The \a functionTag parameter must be
 * a valid C++ identifier, and it must be enclosed in quotation marks, as a
 * string. \a className specifies the name of the class to which the member
 * or friend function belongs. It must match the \a className used in the
 * #RW_USER_DECLARE_TRACEABLE_CLASS macro for the class. The \a functionTag
 * parameter is usually the function name.
 *
 * \note
 * Each function in an application may be traceable as a friend to only one
 * class. Friend functions can also be traced as global functions.
 */
#  define RW_USER_TRACEABLE_FRIEND(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * Defines a global function to be traceable. \a functionTag is used as the
 * environment variable to control trace event generation for this function.
 * It also appears in the trace output. The \a functionTag parameter must be
 * a valid C++ identifier, and it must be enclosed in quotation marks, as a
 * string. The \a functionTag parameter is usually the function name.
 */
#  define RW_USER_TRACEABLE_FUNCTION(functionTag)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_MEMBER
 */
#  define RW_USER_TRACEABLE_INLINE_MEMBER(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_STATIC_MEMBER
 */
#  define RW_USER_TRACEABLE_INLINE_STATIC_MEMBER(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_FRIEND
 */
#  define RW_USER_TRACEABLE_INLINE_FRIEND(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_FUNCTION
 */
#  define RW_USER_TRACEABLE_INLINE_FUNCTION(functionTag)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_MEMBER
 */
#  define RW_USER_TRACEABLE_TEMPLATE_MEMBER(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_STATIC_MEMBER
 */
#  define RW_USER_TRACEABLE_TEMPLATE_STATIC_MEMBER(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_FRIEND
 */
#  define RW_USER_TRACEABLE_TEMPLATE_FRIEND(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_FUNCTION
 */
#  define RW_USER_TRACEABLE_TEMPLATE_FUNCTION(functionTag)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_MEMBER
 */
#  define RW_USER_TRACEABLE_INLINE_TEMPLATE_MEMBER(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_STATIC_MEMBER
 */
#  define RW_USER_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_FRIEND
 */
#  define RW_USER_TRACEABLE_INLINE_TEMPLATE_FRIEND(functionTag, className)

/**
 * \ingroup execution_tracing_package
 *
 * \copydoc RW_USER_TRACEABLE_FUNCTION
 */
#  define RW_USER_TRACEABLE_INLINE_TEMPLATE_FUNCTION(functionTag)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'FATAL' severity level trace event. For use by static member
 * functions, friend functions, or global functions.
 */
#  define RW_USER_TRACE_FATAL(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'FATAL' severity level trace event. For use in member
 * functions.
 */
#  define RW_USER_TRACE_OBJECT_FATAL(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'ERROR' severity level trace event. For use by static member
 * functions, friend functions, or global functions.
 */
#  define RW_USER_TRACE_ERROR(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'ERROR' severity level trace event. For use in member
 * functions.
 */
#  define RW_USER_TRACE_OBJECT_ERROR(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'WARNING' severity level trace event. For use by static
 * member functions, friend functions, or global functions.
 */
#  define RW_USER_TRACE_WARNING(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'WARNING' severity level trace event. For use in member
 * functions.
 */
#  define RW_USER_TRACE_OBJECT_WARNING(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'INFO' severity level trace event. For use by static member
 * functions, friend functions, or global functions.
 */
#  define RW_USER_TRACE_INFO(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'INFO' severity level trace event. For use in member
 * functions.
 */
#  define RW_USER_TRACE_OBJECT_INFO(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'TEST' severity level trace event. For use by static member
 * functions, friend functions, or global functions.
 */
#  define RW_USER_TRACE_TEST(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'TEST' severity level trace event. For use in member
 * functions.
 */
#  define RW_USER_TRACE_OBJECT_TEST(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'DEBUG' severity level trace event. For use by static member
 * functions, friend functions, or global functions.
 */
#  define RW_USER_TRACE_DEBUG(msg)

/**
 * \ingroup execution_tracing_package
 *
 * Generates a 'DEBUG' severity level trace event. For use in member
 * functions.
 */
#  define RW_USER_TRACE_OBJECT_DEBUG(msg)

#else

///////////////////////////////////////////////////////////////////////////////
// Define class/function macros with user specified parent package
///////////////////////////////////////////////////////////////////////////////

//No Ref Doc
//Declares the class MyClass to be traceable with the package pkg as it's parent
#  define RW_DECLARE_TRACEABLE_CLASS_IN_PACKAGE(pkg, MyClass) RW_DECLARE_TRACEABLE_CLASS(pkg, MyClass)

//No Ref Doc
//Defines a traceable class with the package pkg as it's parent
//Must be used in exactly one source file
#  define RW_DEFINE_TRACEABLE_CLASS_IN_PACKAGE(pkg, MyClass) RW_DEFINE_TRACEABLE_CLASS(pkg, MyClass)

//No Ref Doc
//Defines a traceable function with a user specified parent package
#  define RW_TRACEABLE_FUNCTION_IN_PACKAGE_NO_ENTRY(pkg, rid)                 RW_TRACEABLE_FUNCTION_NO_ENTRY(pkg, rid)
#  define RW_TRACEABLE_INLINE_FUNCTION_IN_PACKAGE_NO_ENTRY(pkg, rid)          RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(pkg, rid)
#  define RW_TRACEABLE_TEMPLATE_FUNCTION_IN_PACKAGE_NO_ENTRY(pkg, rid)        RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(pkg, rid)
#  define RW_TRACEABLE_INLINE_TEMPLATE_FUNCTION_IN_PACKAGE_NO_ENTRY(pkg, rid) RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(pkg, rid)

///////////////////////////////////////////////////////////////////////////////
// Define user trace macros
///////////////////////////////////////////////////////////////////////////////

//--Declares/defines a traceable package
//--Must be used at namespace (including global) scope level
//--The pkg parameter is used as the environment variable to toggle
//--the tracing state of the package set.
#  define RW_TRACE_DECLARE_TRACEABLE_PACKAGE(pkg) RW_DECLARE_TRACEABLE_PACKAGE(pkg, class RW_TRACE_MACRO_DECLSPEC)
#  define RW_TRACE_DEFINE_TRACEABLE_PACKAGE(pkg)  RW_DEFINE_TRACEABLE_PACKAGE(pkg)

//--Declares a class to be traceable.
//--Must be used at namespace (including global) scope level
//--The classname parameter is used as the environment variable to toggle
//--the tracing state of the class set.
//--The TEMPLATE version must be used for template classes
#  define RW_USER_DECLARE_TRACEABLE_CLASS(MyClass) RW_DECLARE_TRACEABLE_CLASS(rw_user, MyClass, class RW_TRACE_MACRO_DECLSPEC)
#  define RW_USER_DECLARE_TRACEABLE_TEMPLATE_CLASS(MyClass) RW_DECLARE_TRACEABLE_TEMPLATE_CLASS(rw_user, MyClass)

//--Definition for traceable class.
//--Must be used in exactly one source file.
//--Must be used at same (namespace) scope level as RW_USER_DECLARE_TRACEABLE_CLASS macro.
//--The classname parameter is used as the environment variable to toggle
//--the tracing state of the class set.
//--The TEMPLATE version must be used for template classes
#  define RW_USER_DEFINE_TRACEABLE_CLASS(MyClass) RW_DEFINE_TRACEABLE_CLASS(rw_user, MyClass)
#  define RW_USER_DEFINE_TRACEABLE_TEMPLATE_CLASS(MyClass) RW_DEFINE_TRACEABLE_TEMPLATE_CLASS(rw_user, MyClass)

//--Defines a (non-static) member function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'Foo_doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the member function. The second parameter is the class to which the member belongs.
//--This macro does not generate an entry/exit trace event.
//--The INLINE version must be used in inline functions
//--The TEMPLATE version must be used for member functions in a template class
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class
#  define RW_USER_TRACEABLE_MEMBER_NO_ENTRY(rid, class)                 RW_TRACEABLE_MEMBER_NO_ENTRY(rid, class)
#  define RW_USER_TRACEABLE_INLINE_MEMBER_NO_ENTRY(rid, class)          RW_TRACEABLE_INLINE_MEMBER_NO_ENTRY(rid, class)
#  define RW_USER_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)        RW_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)
#  define RW_USER_TRACEABLE_INLINE_TEMPLATE_MEMBER_NO_ENTRY(rid, class) RW_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)

//--Defines a friend function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the member function. The second parameter is the class to which the member belongs.
//--This macro does not generate an entry/exit trace event.
//--The INLINE version must be used in inline functions
//--The TEMPLATE version must be used for member functions in a template class
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class
#  define RW_USER_TRACEABLE_FRIEND_NO_ENTRY(rid, class)                 RW_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define RW_USER_TRACEABLE_INLINE_FRIEND_NO_ENTRY(rid, class)          RW_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define RW_USER_TRACEABLE_TEMPLATE_FRIEND_NO_ENTRY(rid, class)        RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define RW_USER_TRACEABLE_INLINE_TEMPLATE_FRIEND_NO_ENTRY(rid, class) RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)

//--Defines a static member function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'Foo_doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the member function. The second parameter is the class to which the static member belongs.
//--This macro does not generate an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for member functions in a template class.
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class.
#  define RW_USER_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)                 RW_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define RW_USER_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)          RW_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define RW_USER_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)        RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define RW_USER_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class) RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)

//--Defines a global function to be traceable.
//--The parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'myGlobalFunc'. This identifier is used as the environment variable to toggle the tracing state
//--of the global function.
//--This macro does not generate an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for global template functions.
//--THE INLINE_TEMPLATE version must be use for global inline template functions.
#  define RW_USER_TRACEABLE_FUNCTION_NO_ENTRY(rid)                 RW_TRACEABLE_FUNCTION_NO_ENTRY(rw_user, rid)
#  define RW_USER_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(rid)          RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(rw_user, rid)
#  define RW_USER_TRACEABLE_TEMPLATE_FUNCTION_NO_ENTRY(rid)        RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(rw_user, rid)
#  define RW_USER_TRACEABLE_INLINE_TEMPLATE_FUNCTION_NO_ENTRY(rid) RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(rw_user, rid)


#  if ( RW_USER_TRACE_LEVEL >= 2 )
// These should only generate an entry/exit event if RW_USER_TRACE_LEVEL >= 8
#    define RW_USER_TRACEABLE_MEMBER(rid, class)        RW_TRACEABLE_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_STATIC_MEMBER(rid, class) RW_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_FRIEND(rid, class)        RW_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_FUNCTION(rid)             RW_TRACEABLE_FUNCTION_NO_ENTRY(rw_user, rid)

#    define RW_USER_TRACEABLE_INLINE_MEMBER(rid, class)        RW_TRACEABLE_INLINE_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_STATIC_MEMBER(rid, class) RW_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_FRIEND(rid, class)        RW_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_FUNCTION(rid)             RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(rw_user, rid)

#    define RW_USER_TRACEABLE_TEMPLATE_MEMBER(rid, class)        RW_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, class) RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_FRIEND(rid, class)        RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_FUNCTION(rid)             RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(rw_user, rid)

#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_MEMBER(rid, class)                 RW_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER(rid, class)          RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_FRIEND(rid, class)                 RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_FUNCTION(rid)                      RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(rw_user, rid)

#    define RW_TRACEABLE_FUNCTION_IN_PACKAGE(pkg, rid)                 RW_TRACEABLE_FUNCTION_NO_ENTRY(pkg, rid)
#    define RW_TRACEABLE_INLINE_FUNCTION_IN_PACKAGE(pkg, rid)          RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(pkg, rid)
#    define RW_TRACEABLE_TEMPLATE_FUNCTION_IN_PACKAGE(pkg, rid)        RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(pkg, rid)
#    define RW_TRACEABLE_INLINE_TEMPLATE_FUNCTION_IN_PACKAGE(pkg, rid) RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(pkg, rid)

//--Generates a 'FATAL' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_FATAL(msg) RW_TRACE_EVENT_FATAL(msg)

//--Generates a 'FATAL' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_OBJECT_FATAL(msg) RW_TRACE_EVENT_OBJECT_FATAL(msg)
#  else
#    define RW_USER_TRACE_FATAL(msg)
#    define RW_USER_TRACE_OBJECT_FATAL(msg)

// RW_USER_TRACE_LEVEL < 2 so compile out all trace macros.

#    undef RW_TRACE_DECLARE_TRACEABLE_PACKAGE
#    undef RW_TRACE_DEFINE_TRACEABLE_PACKAGE
#    undef RW_DECLARE_TRACEABLE_CLASS_IN_PACKAGE
#    undef RW_DEFINE_TRACEABLE_CLASS_IN_PACKAGE
#    undef RW_USER_DECLARE_TRACEABLE_CLASS
#    undef RW_USER_DEFINE_TRACEABLE_CLASS
#    undef RW_USER_TRACEABLE_MEMBER_NO_ENTRY
#    undef RW_USER_TRACEABLE_STATIC_MEMBER_NO_ENTRY
#    undef RW_USER_TRACEABLE_FRIEND_NO_ENTRY
#    undef RW_USER_TRACEABLE_FUNCTION_NO_ENTRY
#    undef RW_USER_TRACEABLE_INLINE_MEMBER_NO_ENTRY
#    undef RW_USER_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY
#    undef RW_USER_TRACEABLE_INLINE_FRIEND_NO_ENTRY
#    undef RW_USER_TRACEABLE_INLINE_FUNCTION_NO_ENTRY
#    undef RW_USER_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY
#    undef RW_USER_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY
#    undef RW_USER_TRACEABLE_TEMPLATE_FRIEND_NO_ENTRY
#    undef RW_USER_TRACEABLE_TEMPLATE_FUNCTION_NO_ENTRY
#    undef RW_USER_TRACEABLE_INLINE_TEMPLATE_MEMBER_NO_ENTRY
#    undef RW_USER_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER_NO_ENTRY
#    undef RW_USER_TRACEABLE_INLINE_TEMPLATE_FRIEND_NO_ENTRY
#    undef RW_USER_TRACEABLE_INLINE_TEMPLATE_FUNCTION_NO_ENTRY
#    undef RW_TRACEABLE_FUNCTION_IN_PACKAGE
#    undef RW_TRACEABLE_INLINE_FUNCTION_IN_PACKAGE
#    undef RW_TRACEABLE_TEMPLATE_FUNCTION_IN_PACKAGE
#    undef RW_TRACEABLE_INLINE_TEMPLATE_FUNCTION_IN_PACKAGE
#    undef RW_TRACEABLE_FUNCTION_IN_PACKAGE_NO_ENTRY
#    undef RW_TRACEABLE_INLINE_FUNCTION_IN_PACKAGE_NO_ENTRY
#    undef RW_TRACEABLE_TEMPLATE_FUNCTION_IN_PACKAGE_NO_ENTRY
#    undef RW_TRACEABLE_INLINE_TEMPLATE_FUNCTION_IN_PACKAGE_NO_ENTRY

#    define RW_TRACE_DECLARE_TRACEABLE_PACKAGE(pkg)
#    define RW_TRACE_DEFINE_TRACEABLE_PACKAGE(pkg)
#    define RW_DECLARE_TRACEABLE_CLASS_IN_PACKAGE(pkg, MyClass)
#    define RW_DEFINE_TRACEABLE_CLASS_IN_PACKAGE(pkg, MyClass)
#    define RW_USER_DECLARE_TRACEABLE_CLASS(MyClass)
#    define RW_USER_DEFINE_TRACEABLE_CLASS(MyClass)
#    define RW_USER_TRACEABLE_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_STATIC_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_FRIEND(rid, class)
#    define RW_USER_TRACEABLE_FUNCTION(rid)
#    define RW_USER_TRACEABLE_INLINE_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_INLINE_FRIEND(rid, class)
#    define RW_USER_TRACEABLE_INLINE_FUNCTION(rid)
#    define RW_USER_TRACEABLE_TEMPLATE_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_FRIEND(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_FUNCTION(rid)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_FRIEND(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_FUNCTION(rid)
#    define RW_USER_TRACEABLE_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_FRIEND_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_FUNCTION_NO_ENTRY(rid)
#    define RW_USER_TRACEABLE_INLINE_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_FRIEND_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(rid)
#    define RW_USER_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_FRIEND_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_FUNCTION_NO_ENTRY(rid)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_FRIEND_NO_ENTRY(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_FUNCTION_NO_ENTRY(rid)
#    define RW_TRACEABLE_FUNCTION_IN_PACKAGE(pkg, rid)
#    define RW_TRACEABLE_INLINE_FUNCTION_IN_PACKAGE(pkg, rid)
#    define RW_TRACEABLE_TEMPLATE_FUNCTION_IN_PACKAGE(pkg, rid)
#    define RW_TRACEABLE_INLINE_TEMPLATE_FUNCTION_IN_PACKAGE(pkg, rid)
#    define RW_TRACEABLE_FUNCTION_IN_PACKAGE_NO_ENTRY(pkg, rid)
#    define RW_TRACEABLE_INLINE_FUNCTION_IN_PACKAGE_NO_ENTRY(pkg, rid)
#    define RW_TRACEABLE_TEMPLATE_FUNCTION_IN_PACKAGE_NO_ENTRY(pkg, rid)
#    define RW_TRACEABLE_INLINE_TEMPLATE_FUNCTION_IN_PACKAGE_NO_ENTRY(pkg, rid)
#  endif

#  if ( RW_USER_TRACE_LEVEL >= 3 )

//--Generates an 'ERROR' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function's set.
#    define RW_USER_TRACE_ERROR(msg) RW_TRACE_EVENT_ERROR(msg)

//--Generates an 'ERROR' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_OBJECT_ERROR(msg) RW_TRACE_EVENT_OBJECT_ERROR(msg)

#  else
#    define RW_USER_TRACE_ERROR(msg)
#    define RW_USER_TRACE_OBJECT_ERROR(msg)
#  endif

#  if ( RW_USER_TRACE_LEVEL >= 4 )
//--Generates a 'WARNING' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_WARNING(msg) RW_TRACE_EVENT_WARNING(msg)

//--Generates a 'WARNING' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_OBJECT_WARNING(msg) RW_TRACE_EVENT_OBJECT_WARNING(msg)

#  else
#    define RW_USER_TRACE_WARNING(msg)
#    define RW_USER_TRACE_OBJECT_WARNING(msg)
#  endif

#  if ( RW_USER_TRACE_LEVEL >= 5 )
//--Generates an 'INFO' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_INFO(msg) RW_TRACE_EVENT_INFO(msg)

//--Generates an 'INFO' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_OBJECT_INFO(msg) RW_TRACE_EVENT_OBJECT_INFO(msg)

#  else
#    define RW_USER_TRACE_INFO(msg)
#    define RW_USER_TRACE_OBJECT_INFO(msg)
#  endif

#  if ( RW_USER_TRACE_LEVEL >= 6 )
//--Generates a 'TEST' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_TEST(msg) RW_TRACE_EVENT_TEST(msg)

//--Generates a 'TEST' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_OBJECT_TEST(msg) RW_TRACE_EVENT_OBJECT_TEST(msg)

#  else
#    define RW_USER_TRACE_TEST(msg)
#    define RW_USER_TRACE_OBJECT_TEST(msg)
#  endif

#  if ( RW_USER_TRACE_LEVEL >= 7 )
//--Generates a 'DEBUG' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_DEBUG(msg) RW_TRACE_EVENT_DEBUG(msg)

//--Generates a 'DEBUG' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#    define RW_USER_TRACE_OBJECT_DEBUG(msg) RW_TRACE_EVENT_OBJECT_DEBUG(msg)

#  else
#    define RW_USER_TRACE_DEBUG(msg)
#    define RW_USER_TRACE_OBJECT_DEBUG(msg)
#  endif

#  if ( RW_USER_TRACE_LEVEL >= 8 )
#    undef RW_USER_TRACEABLE_MEMBER
#    undef RW_USER_TRACEABLE_INLINE_MEMBER
#    undef RW_USER_TRACEABLE_TEMPLATE_MEMBER
#    undef RW_USER_TRACEABLE_INLINE_TEMPLATE_MEMBER
//--Defines a (non-static) member function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'Foo_doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the member function. The second parameter is the class to which the member belongs.
//--This macro generates an entry/exit trace event.
//--The INLINE version must be used in inline functions
//--The TEMPLATE version must be used for member functions in a template class
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class
#    define RW_USER_TRACEABLE_MEMBER(rid, class)                 RW_TRACEABLE_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_INLINE_MEMBER(rid, class)          RW_TRACEABLE_INLINE_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_MEMBER(rid, class)        RW_TRACEABLE_TEMPLATE_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_MEMBER(rid, class) RW_TRACEABLE_TEMPLATE_MEMBER(rid, class)

#    undef RW_USER_TRACEABLE_STATIC_MEMBER
#    undef RW_USER_TRACEABLE_INLINE_STATIC_MEMBER
#    undef RW_USER_TRACEABLE_TEMPLATE_STATIC_MEMBER
#    undef RW_USER_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER
//--Defines a static member function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'Foo_doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the member function. The second parameter is the class to which the static member belongs.
//--This macro generates an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for member functions in a template class.
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class.
#    define RW_USER_TRACEABLE_STATIC_MEMBER(rid, class)                 RW_TRACEABLE_STATIC_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)          RW_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, class)        RW_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER(rid, class) RW_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)

#    undef RW_USER_TRACEABLE_FRIEND
#    undef RW_USER_TRACEABLE_INLINE_FRIEND
#    undef RW_USER_TRACEABLE_TEMPLATE_FRIEND
#    undef RW_USER_TRACEABLE_INLINE_TEMPLATE_FRIEND
//--Defines a friend function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'Foo_doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the member function. The second parameter is the class to which the static member belongs.
//--This macro generates an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for member functions in a template class.
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class.
#    define RW_USER_TRACEABLE_FRIEND(rid, class)                 RW_TRACEABLE_STATIC_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_INLINE_FRIEND(rid, class)          RW_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_TEMPLATE_FRIEND(rid, class)        RW_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_FRIEND(rid, class) RW_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)

#    undef RW_USER_TRACEABLE_FUNCTION
#    undef RW_USER_TRACEABLE_INLINE_FUNCTION
#    undef RW_USER_TRACEABLE_TEMPLATE_FUNCTION
#    undef RW_USER_TRACEABLE_INLINE_TEMPLATE_FUNCTION
//--Defines a global function to be traceable.
//--The parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'myGlobalFunc'. This identifier is used as the environment variable to toggle the tracing state
//--of the global function.
//--This macro generates an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for global template functions.
//--THE INLINE_TEMPLATE version must be use for global inline template functions.
#    define RW_USER_TRACEABLE_FUNCTION(rid)                 RW_TRACEABLE_FUNCTION(rw_user, rid)
#    define RW_USER_TRACEABLE_INLINE_FUNCTION(rid)          RW_TRACEABLE_INLINE_FUNCTION(rw_user, rid)
#    define RW_USER_TRACEABLE_TEMPLATE_FUNCTION(rid)        RW_TRACEABLE_INLINE_FUNCTION(rw_user, rid)
#    define RW_USER_TRACEABLE_INLINE_TEMPLATE_FUNCTION(rid) RW_TRACEABLE_INLINE_FUNCTION(rw_user, rid)


// No Ref Doc
// Defines a traceable function with a user supplied parent package
#    undef RW_TRACEABLE_FUNCTION_IN_PACKAGE
#    undef RW_TRACEABLE_INLINE_FUNCTION_IN_PACKAGE
#    undef RW_TRACEABLE_TEMPLATE_FUNCTION_IN_PACKAGE
#    undef RW_TRACEABLE_INLINE_TEMPLATE_FUNCTION_IN_PACKAGE
#    define RW_TRACEABLE_FUNCTION_IN_PACKAGE(pkg, rid)                 RW_TRACEABLE_FUNCTION(pkg, rid)
#    define RW_TRACEABLE_INLINE_FUNCTION_IN_PACKAGE(pkg, rid)          RW_TRACEABLE_INLINE_FUNCTION(pkg, rid)
#    define RW_TRACEABLE_TEMPLATE_FUNCTION_IN_PACKAGE(pkg, rid)        RW_TRACEABLE_INLINE_FUNCTION(pkg, rid)
#    define RW_TRACEABLE_INLINE_TEMPLATE_FUNCTION_IN_PACKAGE(pkg, rid) RW_TRACEABLE_INLINE_FUNCTION(pkg, rid)
#  endif

RW_TRACE_DECLARE_TRACEABLE_PACKAGE(rw_user)

#endif
#endif // __rw_trace_userdefs_h__
