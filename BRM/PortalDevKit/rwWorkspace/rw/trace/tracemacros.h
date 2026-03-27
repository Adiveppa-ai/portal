#ifndef __rw_trace_tracemacros_h__
#define __rw_trace_tracemacros_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/trace/tracemacros.h#1 $
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
 * Extracts the string from an 'ostream' and return it as an 'RWCString'.
 *
 *************************************************************************/

#include <rw/trace/RWTraceEntryExit.h>
#include <rw/trace/RWTraceEvent.h>
#include <rw/trace/RWTraceManagerImp.h>
#include <rw/trace/RWTraceSetState.h>
#include <rw/trace/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/tools/cstrstrm.h>

//--Extracts the string from an 'ostream' and return it as an 'RWCString'.
RWCString RW_TRACE_SYMBOLIC rwExtractString(RWCStringOStream& s);

// The call to ::rwExtractString creates an instance of RWCStringOStream on
// the heap, however it does not delete the RWCStringOStream directly.  The
// responsibility of deleting the RWCStringOStream object is left to the
// body of the rwExtractString object.
//
// This was done to avoid issues regarding passing a temporary as a non-const
// reference.

/**
 * \ingroup execution_tracing_package
 *
 * \headerfileloc{#include <rw/trace/userdefs.h>}
 *
 * Macro for streaming objects into a trace macro's \c message parameter.
 *
 * \example
 * \code
 * RW_TRACE_INFO( "main()", RW_STREAM_TO_STRING("One = " << 1) );
 * \endcode
 * \endexample
 */
#define RW_STREAM_TO_STRING(stream) \
  ::rwExtractString( (RWCStringOStream &)(*(new RWCStringOStream) << stream) )

// No ref doc.
// 'rwTraceMakeId' makes an identifier name, unique within the file,
// by pasting the argument and line number.  The other
// two macros are helpers.
#define _rwTraceConcat(x,y) x##y
#define rwTraceConcat(x,y) _rwTraceConcat(x,y)
#define rwTraceMakeId(x) rwTraceConcat(x, __LINE__)

// No ref doc.
//
// core event set macros that expand into the event set class and its members
//

//Declares a class event set. state_ is set to 0 by the compiler. registerSet() changes
//this value to one of RWTraceSetUndef==1, RWTraceSetOn==2, or RWTraceSetOff==3, thus
//implementing a first-time switch
//TEMPLATE version is for use with template classes
#define RW_TRACE_BEGIN_DECLARE_SET(classname, set, declspec) \
declspec classname##_##set { \
public: \
  static const char* setName(void) { \
    return #set; \
  } \
  static int getSetState(void) { \
    if( state_ == 0 ) \
      state_ = RWTraceManagerImp::instance().registerSet(#set, &getSuperSetState); \
    return state_; \
  } \
  static int state_;

#define RW_TRACE_BEGIN_DECLARE_SET_TEMPLATE(classname, set) \
template <class T> class classname##_##set { \
public: \
  static const char* setName(void) { \
    return #set; \
  } \
  static int getSetState(void) { \
    if( state_ == 0 ) \
      state_ = RWTraceManagerImp::instance().registerSet(#set, &getSuperSetState); \
    return state_; \
  } \
  static int state_;

//--Defines the class event set for tracing.  Must be placed in exactly one source file.
#define RW_TRACE_DEFINE_SET( classname, set) \
  int classname##_##set::state_; // = 0; 

// For templates.  Place in .cc file.
// This macro intentionally expands to nothing.  It used to hold the definition of
// the static variable, but that has been moved to the header macro.
//--Defines the class event set for tracing.  Must be placed in exactly one source file.
#define RW_TRACE_DEFINE_SET_TEMPLATE( classname, set)

// No ref doc.
//
// macros for getsupersets fn
//
#define RW_TRACE_BEGIN_DECLARE_GETSUPERSETS(set) \
  static int getSuperSetState(void) { \
    int superState;

#define RW_TRACE_DECLARE_SCOPED_SUPERSET(name) \
    if ( (superState = name::_RWTraceSet::getSetState()) != RWTraceSetUndef) return superState;

#define RW_TRACE_DECLARE_GLOBAL_SUPERSET(name) \
    if ( (superState = _RWTraceSet_##name::getSetState()) != RWTraceSetUndef) return superState;

#define RW_TRACE_DECLARE_NEAREST_SUPERSET \
    if ( (superState = _RWTraceSet::getSetState()) != RWTraceSetUndef) return superState;

#define RW_TRACE_NO_SUPERSETS \
  static int getSuperSetState(void) { return RWTraceSetUndef; }

#define RW_TRACE_END_DECLARE_GETSUPERSETS \
    return RWTraceSetUndef; \
  }
// No ref doc.
//
// end of getsupersets macros
//

#define RW_TRACE_END_DECLARE_SET \
};
// No ref doc.
//
// end of core macros
//

// No ref doc.
//
// macros for declaring event sets
//

//--Declares a package to be traceable.  This macro should be used in a header file.
//--The set parameter must be a valid C++ identifier.  This identifier is also used
//--as the environment variable to toggle the tracing state of the package.
#define RW_DECLARE_TRACEABLE_PACKAGE(set, declspec) \
declspec _RWTraceSet_##set { \
public: \
  static const char* setName(void); \
  static int getSetState(void); \
  static int getSuperSetState(void); \
  static int registerFunction(const char *rid); \
  static int state_; \
};

//state is set to 0 by the compiler. registerSet() changes this value to one of RWTraceSetUndef==1,
//RWTraceSetOn==2, or RWTraceSetOff==3, thus implementing a first-time switch
//--Defines the package event set for tracing.  Must be placed in exactly one source file.
#define RW_DEFINE_TRACEABLE_PACKAGE(set) \
const char* _RWTraceSet_##set::setName(void) { \
  return #set; \
} \
int _RWTraceSet_##set::getSetState(void) { \
  if( state_ == 0 ) \
    state_ = RWTraceManagerImp::instance().registerSet(#set, &getSuperSetState); \
  return state_; \
} \
int _RWTraceSet_##set::getSuperSetState(void) { \
  return RWTraceSetUndef; \
} \
int _RWTraceSet_##set::registerFunction(const char *rid) { \
  return RWTraceManagerImp::instance().registerSet(rid, &getSetState); \
} \
int _RWTraceSet_##set::state_; // = 0; 

//--Declares a class to be traceable.
//--The class event set is a member of the package event set supplied as the first parameter.
//--The classname parameter is used as the environment variable to toggle
//--the tracing state of the class set.
#define RW_DECLARE_TRACEABLE_CLASS(pkg, MyClass, declspec) \
  RW_TRACE_BEGIN_DECLARE_SET(_RWTraceSet, MyClass, declspec) \
    RW_TRACE_BEGIN_DECLARE_GETSUPERSETS(#MyClass) \
      RW_TRACE_DECLARE_GLOBAL_SUPERSET(pkg) \
    RW_TRACE_END_DECLARE_GETSUPERSETS \
    static int registerMember(const char *rid) { \
       return RWTraceManagerImp::instance().registerSet(rid, &getSetState); \
    } \
  RW_TRACE_END_DECLARE_SET \

//--Defines a traceable class
//--Must be used in exactly one source file
//--The class event set is a member of the package event set supplied as the first parameter.
//--The classname parameter is used as the environment variable to toggle
//--the tracing state of the class set.
#define RW_DEFINE_TRACEABLE_CLASS(pkg, MyClass) \
  RW_TRACE_DEFINE_SET(_RWTraceSet, MyClass)

//--Declares a template class to be traceable.
//--The class event set is a member of the package event set supplied as the first parameter.
//--The classname parameter is used as the environment variable to toggle
//--the tracing state of the class set.
#define RW_DECLARE_TRACEABLE_TEMPLATE_CLASS(pkg, MyClass) \
  RW_TRACE_BEGIN_DECLARE_SET_TEMPLATE(_RWTraceSet, MyClass) \
    RW_TRACE_BEGIN_DECLARE_GETSUPERSETS(#MyClass) \
      RW_TRACE_DECLARE_GLOBAL_SUPERSET(pkg) \
    RW_TRACE_END_DECLARE_GETSUPERSETS \
    static int registerMember(const char *rid) { \
       return RWTraceManagerImp::instance().registerSet(rid, &getSetState); \
    } \
  RW_TRACE_END_DECLARE_SET \
  template <class T> int _RWTraceSet##_##MyClass<T>::state_; // = 0; 

//--Defines a traceable template class
//--Must be used in exactly one source (.cc) file
//--The class event set is a member of the package event set supplied as the first parameter.
//--The classname parameter is used as the environment variable to toggle
//--the tracing state of the class set.
#define RW_DEFINE_TRACEABLE_TEMPLATE_CLASS(pkg, MyClass) \
  RW_TRACE_DEFINE_SET_TEMPLATE(_RWTraceSet, MyClass)

// No ref doc.
// Defines default event set for trace events in this method (fixed class name).
#define _RW_TRACEABLE_MEMBER(rid, MyClass) \
static const char* _rwTraceSetName = rid; \
static int _rwTraceSetState = RWTraceSetFirstTimeSwitchFlag; \
if (RWTraceSetFirstTimeSwitchFlag == _rwTraceSetState) \
    _rwTraceSetState = _RWTraceSet##_##MyClass::registerMember(_rwTraceSetName);

#define _RW_TRACEABLE_INLINE_MEMBER(rid, MyClass) \
static const char* _rwTraceSetName = rid; \
static int _rwTraceSetState = RWTraceSetFirstTimeSwitchFlag; \
if (RWTraceSetFirstTimeSwitchFlag == _rwTraceSetState) \
    _rwTraceSetState = _RWTraceSet##_##MyClass::registerMember(_rwTraceSetName);

#define _RW_TRACEABLE_TEMPLATE_MEMBER(rid, MyClass) \
static const char* _rwTraceSetName = rid; \
static int _rwTraceSetState = RWTraceSetFirstTimeSwitchFlag; \
if (RWTraceSetFirstTimeSwitchFlag == _rwTraceSetState) \
    _rwTraceSetState = _RWTraceSet##_##MyClass<int>::registerMember(_rwTraceSetName);

//--Defines a (non-static) member function to be traceable.
//--The first parameter is a resource identifier string, such
//--as 'Foo::doFoo(int)'.  The second parameter is the class
//--to which the member belongs.
//--This macro also generates an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used in template functions.
#define RW_TRACEABLE_MEMBER(rid, MyClass) \
_RW_TRACEABLE_MEMBER(rid, MyClass) \
RW_TRACE_EVENT_OBJECT_ENTRY(rid)

#define RW_TRACEABLE_TEMPLATE_MEMBER(rid, MyClass) \
_RW_TRACEABLE_TEMPLATE_MEMBER(rid, MyClass) \
RW_TRACE_EVENT_OBJECT_ENTRY(rid)

#define RW_TRACEABLE_INLINE_MEMBER(rid, MyClass) \
_RW_TRACEABLE_INLINE_MEMBER(rid, MyClass) \
RW_TRACE_EVENT_OBJECT_ENTRY(rid)

//--Defines a (non-static) member function to be traceable.
//--The first parameter is a resource identifier string, such
//--as 'Foo::doFoo(int)'.  The second parameter is the class
//--to which the member belongs.
//--This macro does not generate an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used in template functions.
#define RW_TRACEABLE_MEMBER_NO_ENTRY(rid, MyClass) \
_RW_TRACEABLE_MEMBER(rid, MyClass)

#define RW_TRACEABLE_TEMPLATE_MEMBER_NO_ENTRY(rid, MyClass) \
_RW_TRACEABLE_TEMPLATE_MEMBER(rid, MyClass)

#define RW_TRACEABLE_INLINE_MEMBER_NO_ENTRY(rid, MyClass) \
_RW_TRACEABLE_INLINE_MEMBER(rid, MyClass)

//--Defines a static member function to be traceable.
//--The first parameter is a resource identifier string, such
//--as 'Foo::doFoo(int)'. The second parameter is the class
//--to which the member belongs.
//--This macro also generates an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used in template functions.
#define RW_TRACEABLE_STATIC_MEMBER(rid, MyClass) \
_RW_TRACEABLE_MEMBER(rid, MyClass) \
RW_TRACE_EVENT_ENTRY(rid)

#define RW_TRACEABLE_TEMPLATE_STATIC_MEMBER(rid, MyClass) \
_RW_TRACEABLE_TEMPLATE_MEMBER(rid, MyClass) \
RW_TRACE_EVENT_ENTRY(rid)

#define RW_TRACEABLE_INLINE_STATIC_MEMBER(rid, MyClass) \
_RW_TRACEABLE_INLINE_MEMBER(rid, MyClass) \
RW_TRACE_EVENT_ENTRY(rid)

//--Defines a static member function to be traceable.
//--The first parameter is a resource identifier string, such
//--as 'Foo::doFoo(int)'. The second parameter is the class
//--to which the member belongs.
//--This macro does not generate an entry/exit trace event.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used in template functions.
#define RW_TRACEABLE_STATIC_MEMBER_NO_ENTRY(rid, MyClass) \
_RW_TRACEABLE_MEMBER(rid, MyClass)

#define RW_TRACEABLE_TEMPLATE_STATIC_MEMBER_NO_ENTRY(rid, MyClass) \
_RW_TRACEABLE_TEMPLATE_MEMBER(rid, MyClass)

#define RW_TRACEABLE_INLINE_STATIC_MEMBER_NO_ENTRY(rid, MyClass) \
_RW_TRACEABLE_INLINE_MEMBER(rid, MyClass)

// No ref doc.
// Defines default event set for trace events in this function.
// This event set should always be a member of the package event set.
// Invokes 'RW_MYPKG_TRACE_ENTRY()' macro.
//--The INLINE version must be used in inline functions.
//--The TEMPLATE version must be used in template functions.
#define _RW_TRACEABLE_FUNCTION(pkg, rid) \
static const char* _rwTraceSetName = rid; \
static int _rwTraceSetState = RWTraceSetFirstTimeSwitchFlag; \
if (RWTraceSetFirstTimeSwitchFlag == _rwTraceSetState) \
    _rwTraceSetState = _RWTraceSet_##pkg::registerFunction(_rwTraceSetName);

#define _RW_TRACEABLE_INLINE_FUNCTION(pkg, rid) \
static const char* _rwTraceSetName = rid; \
static int _rwTraceSetState = RWTraceSetFirstTimeSwitchFlag; \
if (RWTraceSetFirstTimeSwitchFlag == _rwTraceSetState) \
    _rwTraceSetState = _RWTraceSet_##pkg::registerFunction(_rwTraceSetName);

//--Defines a global function to be traceable.
//--The function\'s event set is a member of package event set supplied as the first parameter.
//--The second parameter is a resource identifier string, such
//--as 'foo(int)'.
//--This macro also generates an entry/exit trace event.
//--The INLINE version must be used in inline functions.
#define RW_TRACEABLE_FUNCTION(pkg, rid) \
_RW_TRACEABLE_FUNCTION(pkg, rid) \
RW_TRACE_EVENT_ENTRY(rid)

#define RW_TRACEABLE_INLINE_FUNCTION(pkg, rid) \
_RW_TRACEABLE_INLINE_FUNCTION(pkg, rid) \
RW_TRACE_EVENT_ENTRY(rid)

//--Defines a global function to be traceable.
//--The function\'s event set is a member of the package event set supplied as the first parameter.
//--The second parameter is a resource identifier string, such
//--as 'foo(int)'.
//--This macro does not generate an entry/exit trace event.
#define RW_TRACEABLE_FUNCTION_NO_ENTRY(pkg, rid) \
_RW_TRACEABLE_FUNCTION(pkg, rid)

#define RW_TRACEABLE_INLINE_FUNCTION_NO_ENTRY(pkg, rid) \
_RW_TRACEABLE_INLINE_FUNCTION(pkg, rid)

// No ref doc.
/////////////////////////////////////////////////
// Core trace macros
/////////////////////////////////////////////////

// No ref doc.
// generic trace macro, looks at nearest (C++ scope-wise) Event class
#define RW_TRACE(level, msg) \
if (_rwTraceSetState == RWTraceSetOn) \
  { \
    RWTraceManager _rwTraceManager; \
    if(_rwTraceManager.getLevel() >= level) { \
      RWTraceEvent _rwTraceEvent(level, _rwTraceSetName, msg, __FILE__, __LINE__, 0); \
      _rwTraceManager.trace(_rwTraceEvent); \
    } \
  }

#define RW_TRACE_OBJECT(level, msg) \
if (_rwTraceSetState == RWTraceSetOn) \
  { \
    RWTraceManager _rwTraceManager; \
    if(_rwTraceManager.getLevel() >= level) { \
      RWTraceEvent _rwTraceEvent(level, _rwTraceSetName, msg, __FILE__, __LINE__, this); \
      _rwTraceManager.trace(_rwTraceEvent); \
    } \
  }

#define RW_TRACE_EVENT_ENTRY(ignore) \
  RWTraceEntryExit _rwTraceEntryExit((RWTraceSetState)_rwTraceSetState, _rwTraceSetName, \
                                     __FILE__, __LINE__, 0);

#define RW_TRACE_EVENT_OBJECT_ENTRY(ignore) \
  RWTraceEntryExit _rwTraceEntryExit((RWTraceSetState)_rwTraceSetState, _rwTraceSetName, \
                                     __FILE__, __LINE__, this);


/////////////////////////////////////////////////
// Tracing macros
/////////////////////////////////////////////////

//--Generates a 'FATAL' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_FATAL(msg) \
  RW_TRACE(RW_TRACE_LEVEL_FATAL, msg)

//--Generates a 'FATAL' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_OBJECT_FATAL(msg) \
  RW_TRACE_OBJECT(RW_TRACE_LEVEL_FATAL, msg)

/////////////////////////////////////////////////

//--Generates an 'ERROR' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_ERROR(msg) \
  RW_TRACE(RW_TRACE_LEVEL_ERROR, msg)

//--Generates an 'ERROR' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_OBJECT_ERROR(msg) \
  RW_TRACE_OBJECT(RW_TRACE_LEVEL_ERROR, msg)

/////////////////////////////////////////////////

//--Generates a 'WARNING' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_WARNING(msg) \
  RW_TRACE(RW_TRACE_LEVEL_WARNING, msg)

//--Generates a 'WARNING' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_OBJECT_WARNING(msg) \
  RW_TRACE_OBJECT(RW_TRACE_LEVEL_WARNING, msg)

/////////////////////////////////////////////////

//--Generates an 'INFO' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_INFO(msg) \
  RW_TRACE(RW_TRACE_LEVEL_INFO, msg)

//--Generates an 'INFO' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_OBJECT_INFO(msg) \
  RW_TRACE_OBJECT(RW_TRACE_LEVEL_INFO, msg)

/////////////////////////////////////////////////

//--Generates a 'TEST' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_TEST(msg) \
  RW_TRACE(RW_TRACE_LEVEL_TEST, msg)

//--Generates a 'TEST' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_OBJECT_TEST(msg) \
  RW_TRACE_OBJECT(RW_TRACE_LEVEL_TEST, msg)

/////////////////////////////////////////////////

//--Generates a 'DEBUG' severity level trace event.
//--For use by global functions and static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_DEBUG(msg) \
  RW_TRACE(RW_TRACE_LEVEL_DEBUG, msg)

//--Generates a 'DEBUG' severity level trace event.
//--For use by non-static member functions.
//--The event becomes a member of the enclosing function\'s set.
#define RW_TRACE_EVENT_OBJECT_DEBUG(msg) \
  RW_TRACE_OBJECT(RW_TRACE_LEVEL_DEBUG, msg)

/////////////////////////////////////////////////

#endif // __rw_trace_tracemacros_h__
