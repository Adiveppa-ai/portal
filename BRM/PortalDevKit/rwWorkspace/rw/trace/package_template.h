#ifndef __package_name_pkgdefs_h__
#define __package_name_pkgdefs_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/package_template.h#1 $
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

 This file is a template for defining your own package level tracing macros.
 See the User's Guide section "Using Package Level Tracing" for more
 information.

 To use this file, make a copy of it an change all instances of "PACKAGE_NAME"
 to your package name (upper case) and change all instances of "package_name"
 to your package name (lower case). If you have many packages, you will want
 to change the include guard macro to something appropriate.  Use these macros
 just as you would use the corresponding RW_USER macro.

 The following sed script will perform the changes for you assuming a package
 name of foo:

 s/PACKAGE_NAME/FOO/g
 s/package_name/foo/g

*****************************************************************************/


/*****************************************************************************

 The following macros must be defined in order to configure a package:

  PACKAGE_NAME_TRACE_LEVEL

  Specifies the level of trace event reporting that is to be compiled into
  the package code.  Also used to detect whether package was configured.

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Define package_name trace macros
//////////////////////////////////////////////////////////////////////////////

// If the PACKAGE_NAME_TRACE_LEVEL macro is not defined, we should
// assume that the user does not want tracing enabled.

#include <rw/trace/userdefs.h>

#if !defined(PACKAGE_NAME_TRACE_LEVEL)
#  define PACKAGE_NAME_TRACE_LEVEL 0
#endif

#include <rw/trace/tracemacros.h>

//--Declares/defines a traceable package
//--Must be used at namespace (including global) scope level
//--The pkg parameter is used as the environment variable to toggle
//--the tracing state of the package set.
#define PACKAGE_NAME_DECLARE_TRACEABLE_PACKAGE(pkg) RW_DECLARE_TRACEABLE_PACKAGE(pkg, class RW_TRACE_MACRO_DECLSPEC)
#define PACKAGE_NAME_DEFINE_TRACEABLE_PACKAGE(pkg)  RW_DEFINE_TRACEABLE_PACKAGE(pkg)

//--Declares a class to be traceable.
//--Must be used at namespace (including global) scope level
//--The classname parameter is used as the environment variable to toggle
//--the tracing state of the class set.
//--The TEMPLATE version must be used for template classes
#define PACKAGE_NAME_DECLARE_TRACEABLE_CLASS(MyClass) RW_DECLARE_TRACEABLE_CLASS(package_name, MyClass, class RW_TRACE_MACRO_DECLSPEC )
#define PACKAGE_NAME_DECLARE_TRACEABLE_TEMPLATE_CLASS(MyClass) RW_DECLARE_TRACEABLE_TEMPLATE_CLASS(package_name, MyClass)

//--Definition for traceable class.
//--Must be used in exactly one source file.
//--Must be used at same (namespace) scope level as PACKAGE_NAME_DECLARE_TRACEABLE_CLASS macro.
//--The classname parameter is used as the environment variable to toggle
//--the tracing state of the class set.
//--The TEMPLATE version must be used for template classes
#define PACKAGE_NAME_DEFINE_TRACEABLE_CLASS(MyClass) RW_DEFINE_TRACEABLE_CLASS(package_name, MyClass)
#define PACKAGE_NAME_DEFINE_TRACEABLE_TEMPLATE_CLASS(MyClass) RW_DEFINE_TRACEABLE_TEMPLATE_CLASS(package_name, MyClass)

//--Defines a (non-static) member function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'Foo_doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the member function. The second parameter is the class to which the member belongs.
//--This macro does not generate an entry/exit trace event.
//--The INLINE version must be used in inline functions
//--The TEMPLATE version must be used for member functions in a template class
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class
#define PACKAGE_NAME_TRACEABLE_MEMBER_NO_ENTRY(rid, class)                 RW_TRACEABLE_MEMBER_NO_ENTRY(rid, class)
#define PACKAGE_NAME_TRACEABLE_INLINE_MEMBER_NO_ENTRY(rid, class)          RW_TRACEABLE_INLINE_MEMBER_NO_ENTRY(rid, class)
#define PACKAGE_NAME_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)        RW_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)
#define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_MEMBER_NO_ENTRY(rid, class) RW_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)

//--Defines a static member function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'Foo_doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the member function. The second parameter is the class to which the static member belongs.
//--This macro does not generate an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for member functions in a template class.
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class.
#define PACKAGE_NAME_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)                 RW_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)
#define PACKAGE_NAME_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)          RW_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)
#define PACKAGE_NAME_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)        RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class) RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)

//--Defines a friend function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the friend function. The second parameter is the class to which the friend belongs.
//--This macro does not generate an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for member functions in a template class.
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class.
#define PACKAGE_NAME_TRACEABLE_FRIEND_NO_ENTRY(rid, class)                 RW_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)
#define PACKAGE_NAME_TRACEABLE_INLINE_FRIEND_NO_ENTRY(rid, class)          RW_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)
#define PACKAGE_NAME_TRACEABLE_TEMPLATE_FRIEND_NO_ENTRY(rid, class)        RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FRIEND_NO_ENTRY(rid, class) RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)

//--Defines a global function to be traceable.
//--The parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'myGlobalFunc'. This identifier is used as the environment variable to toggle the tracing state
//--of the global function.
//--This macro does not generate an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for global template functions.
//--THE INLINE_TEMPLATE version must be use for global inline template functions.
#define PACKAGE_NAME_TRACEABLE_FUNCTION_NO_ENTRY(rid)                 RW_TRACEABLE_FUNCTION_NO_ENTRY(package_name, rid)
#define PACKAGE_NAME_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(rid)          RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(package_name, rid)
#define PACKAGE_NAME_TRACEABLE_TEMPLATE_FUNCTION_NO_ENTRY(rid)        RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(package_name, rid)
#define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FUNCTION_NO_ENTRY(rid) RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(package_name, rid)


#if ( PACKAGE_NAME_TRACE_LEVEL >= 2 )
// These should only generate an entry/exit event if PACKAGE_NAME_TRACE_LEVEL >= 8
#  define PACKAGE_NAME_TRACEABLE_MEMBER(rid, class)        RW_TRACEABLE_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_STATIC_MEMBER(rid, class) RW_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_FRIEND(rid, class)        RW_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_FUNCTION(rid)             RW_TRACEABLE_FUNCTION_NO_ENTRY(package_name, rid)

#  define PACKAGE_NAME_TRACEABLE_INLINE_MEMBER(rid, class)        RW_TRACEABLE_INLINE_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_STATIC_MEMBER(rid, class) RW_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_FRIEND(rid, class)        RW_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_FUNCTION(rid)             RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(package_name, rid)

#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_MEMBER(rid, class)        RW_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, class) RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_FRIEND(rid, class)        RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_FUNCTION(rid)             RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(package_name, rid)

#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_MEMBER(rid, class)                 RW_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER(rid, class)          RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FRIEND(rid, class)                 RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FUNCTION(rid)                      RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(package_name, rid)

//--Generates a 'FATAL' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_FATAL(msg) RW_TRACE_EVENT_FATAL(msg)

//--Generates a 'FATAL' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_OBJECT_FATAL(msg) RW_TRACE_EVENT_OBJECT_FATAL(msg)
#else
#  define PACKAGE_NAME_TRACE_FATAL(msg)
#  define PACKAGE_NAME_TRACE_OBJECT_FATAL(msg)

// PACKAGE_NAME_TRACE_LEVEL < 2 so compile out all trace macros.

#  undef PACKAGE_NAME_DECLARE_TRACEABLE_PACKAGE
#  undef PACKAGE_NAME_DEFINE_TRACEABLE_PACKAGE
#  undef PACKAGE_NAME_DECLARE_TRACEABLE_CLASS
#  undef PACKAGE_NAME_DEFINE_TRACEABLE_CLASS
#  undef PACKAGE_NAME_DECLARE_TRACEABLE_TEMPLATE_CLASS
#  undef PACKAGE_NAME_DEFINE_TRACEABLE_TEMPLATE_CLASS
#  undef PACKAGE_NAME_TRACEABLE_MEMBER_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_STATIC_MEMBER_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_FRIEND_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_FUNCTION_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_INLINE_MEMBER_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_INLINE_FRIEND_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_INLINE_FUNCTION_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_TEMPLATE_FRIEND_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_TEMPLATE_FUNCTION_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_MEMBER_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FRIEND_NO_ENTRY
#  undef PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FUNCTION_NO_ENTRY

#  define PACKAGE_NAME_DECLARE_TRACEABLE_PACKAGE(pkg)
#  define PACKAGE_NAME_DEFINE_TRACEABLE_PACKAGE(pkg)  PACKAGE_NAME_EXPORT void* __##pkg##_dummy_;
#  define PACKAGE_NAME_DECLARE_TRACEABLE_CLASS(MyClass)
#  define PACKAGE_NAME_DEFINE_TRACEABLE_CLASS(MyClass)
#  define PACKAGE_NAME_DECLARE_TRACEABLE_TEMPLATE_CLASS(MyClass)
#  define PACKAGE_NAME_DEFINE_TRACEABLE_TEMPLATE_CLASS(MyClass)
#  define PACKAGE_NAME_TRACEABLE_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_STATIC_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_FRIEND(rid, class)
#  define PACKAGE_NAME_TRACEABLE_FUNCTION(rid)
#  define PACKAGE_NAME_TRACEABLE_INLINE_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_FRIEND(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_FUNCTION(rid)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_FRIEND(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_FUNCTION(rid)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FRIEND(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FUNCTION(rid)
#  define PACKAGE_NAME_TRACEABLE_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_FRIEND_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_FUNCTION_NO_ENTRY(rid)
#  define PACKAGE_NAME_TRACEABLE_INLINE_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_FRIEND_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(rid)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_FRIEND_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_FUNCTION_NO_ENTRY(rid)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FRIEND_NO_ENTRY(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FUNCTION_NO_ENTRY(rid)
#endif

#if ( PACKAGE_NAME_TRACE_LEVEL >= 3 )

//--Generates an 'ERROR' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function's set.
#  define PACKAGE_NAME_TRACE_ERROR(msg) RW_TRACE_EVENT_ERROR(msg)

//--Generates an 'ERROR' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_OBJECT_ERROR(msg) RW_TRACE_EVENT_OBJECT_ERROR(msg)

#else
#  define PACKAGE_NAME_TRACE_ERROR(msg)
#  define PACKAGE_NAME_TRACE_OBJECT_ERROR(msg)
#endif

#if ( PACKAGE_NAME_TRACE_LEVEL >= 4 )
//--Generates a 'WARNING' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_WARNING(msg) RW_TRACE_EVENT_WARNING(msg)

//--Generates a 'WARNING' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_OBJECT_WARNING(msg) RW_TRACE_EVENT_OBJECT_WARNING(msg)

#else
#  define PACKAGE_NAME_TRACE_WARNING(msg)
#  define PACKAGE_NAME_TRACE_OBJECT_WARNING(msg)
#endif

#if ( PACKAGE_NAME_TRACE_LEVEL >= 5 )
//--Generates an 'INFO' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_INFO(msg) RW_TRACE_EVENT_INFO(msg)

//--Generates an 'INFO' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_OBJECT_INFO(msg) RW_TRACE_EVENT_OBJECT_INFO(msg)

#else
#  define PACKAGE_NAME_TRACE_INFO(msg)
#  define PACKAGE_NAME_TRACE_OBJECT_INFO(msg)
#endif

#if ( PACKAGE_NAME_TRACE_LEVEL >= 6 )
//--Generates a 'TEST' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_TEST(msg) RW_TRACE_EVENT_TEST(msg)

//--Generates a 'TEST' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_OBJECT_TEST(msg) RW_TRACE_EVENT_OBJECT_TEST(msg)

#else
#  define PACKAGE_NAME_TRACE_TEST(msg)
#  define PACKAGE_NAME_TRACE_OBJECT_TEST(msg)
#endif

#if ( PACKAGE_NAME_TRACE_LEVEL >= 7 )
//--Generates a 'DEBUG' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_DEBUG(msg) RW_TRACE_EVENT_DEBUG(msg)

//--Generates a 'DEBUG' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#  define PACKAGE_NAME_TRACE_OBJECT_DEBUG(msg) RW_TRACE_EVENT_OBJECT_DEBUG(msg)

#else
#  define PACKAGE_NAME_TRACE_DEBUG(msg)
#  define PACKAGE_NAME_TRACE_OBJECT_DEBUG(msg)
#endif

#if ( PACKAGE_NAME_TRACE_LEVEL >= 8 )
#  undef PACKAGE_NAME_TRACEABLE_MEMBER
#  undef PACKAGE_NAME_TRACEABLE_INLINE_MEMBER
#  undef PACKAGE_NAME_TRACEABLE_TEMPLATE_MEMBER
#  undef PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_MEMBER
//--Defines a (non-static) member function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'Foo_doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the member function. The second parameter is the class to which the member belongs.
//--This macro generates an entry/exit trace event.
//--The INLINE version must be used in inline functions
//--The TEMPLATE version must be used for member functions in a template class
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class
#  define PACKAGE_NAME_TRACEABLE_MEMBER(rid, class)                 RW_TRACEABLE_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_MEMBER(rid, class)          RW_TRACEABLE_INLINE_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_MEMBER(rid, class)        RW_TRACEABLE_TEMPLATE_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_MEMBER(rid, class) RW_TRACEABLE_TEMPLATE_MEMBER(rid, class)

#  undef PACKAGE_NAME_TRACEABLE_STATIC_MEMBER
#  undef PACKAGE_NAME_TRACEABLE_INLINE_STATIC_MEMBER
#  undef PACKAGE_NAME_TRACEABLE_TEMPLATE_STATIC_MEMBER
#  undef PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER
//--Defines a static member function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'Foo_doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the member function. The second parameter is the class to which the static member belongs.
//--This macro generates an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for member functions in a template class.
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class.
#  define PACKAGE_NAME_TRACEABLE_STATIC_MEMBER(rid, class)                 RW_TRACEABLE_STATIC_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)          RW_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, class)        RW_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_STATIC_MEMBER(rid, class) RW_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, class)

#  undef PACKAGE_NAME_TRACEABLE_FRIEND
#  undef PACKAGE_NAME_TRACEABLE_INLINE_FRIEND
#  undef PACKAGE_NAME_TRACEABLE_TEMPLATE_FRIEND
#  undef PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FRIEND
//--Defines a friend function to be traceable.
//--The first parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'doFoo'. This identifier is used as the environment variable to toggle the tracing state
//--of the friend function. The second parameter is the class to which the friend belongs.
//--This macro generates an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for member functions in a template class.
//--THE INLINE_TEMPLATE version must be use for inline member functions in a template class.
#  define PACKAGE_NAME_TRACEABLE_FRIEND(rid, class)                 RW_TRACEABLE_STATIC_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_FRIEND(rid, class)          RW_TRACEABLE_INLINE_STATIC_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_FRIEND(rid, class)        RW_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, class)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FRIEND(rid, class) RW_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, class)

#  undef PACKAGE_NAME_TRACEABLE_FUNCTION
#  undef PACKAGE_NAME_TRACEABLE_INLINE_FUNCTION
#  undef PACKAGE_NAME_TRACEABLE_TEMPLATE_FUNCTION
#  undef PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FUNCTION
//--Defines a global function to be traceable.
//--The parameter is a resource identifier string (which must be a valid C++ identifier), such
//--as 'myGlobalFunc'. This identifier is used as the environment variable to toggle the tracing state
//--of the global function.
//--This macro generates an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used for global template functions.
//--THE INLINE_TEMPLATE version must be use for global inline template functions.
#  define PACKAGE_NAME_TRACEABLE_FUNCTION(rid)                 RW_TRACEABLE_FUNCTION(package_name, rid)
#  define PACKAGE_NAME_TRACEABLE_INLINE_FUNCTION(rid)          RW_TRACEABLE_INLINE_FUNCTION(package_name, rid)
#  define PACKAGE_NAME_TRACEABLE_TEMPLATE_FUNCTION(rid)        RW_TRACEABLE_INLINE_FUNCTION(package_name, rid)
#  define PACKAGE_NAME_TRACEABLE_INLINE_TEMPLATE_FUNCTION(rid) RW_TRACEABLE_INLINE_FUNCTION(package_name, rid)
#endif

RW_TRACE_DECLARE_TRACEABLE_PACKAGE(package_name)

// Don't forget to put the macro RW_TRACE_DECLARE_TRACEABLE_PACKAGE(package_name)
// in exactly one implementation (.cpp) file that includes this file.


#endif // __package_name_pkgdefs_h__
