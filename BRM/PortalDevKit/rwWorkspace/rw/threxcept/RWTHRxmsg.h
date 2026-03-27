#ifndef __rw_threxcept_RWTHRxmsg_h__
#define __rw_threxcept_RWTHRxmsg_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/threxcept/RWTHRxmsg.h#1 $
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

  RWTHRxmsg class - Base class for thread-compatible exceptions.

  rwToRWCString - convert integer value to RWCString.

  rwGetLastErrorMsg - function to retrieve last Win32 error number.
  rwErrorMsg - function to retrieve message for specified error number.
  rwErrnoMsg - function to retrieve message for current errno value.

  A thread compatible exception possesses clone() and raise() members that
  allow the exception to be copied and stored so that it may be rethrown in
  the future.  This capability allows these exceptions to be passed across
  thread boundaries.

  The RW_THR_DECLARE_EXCEPTION(name) and RW_THR_IMPLEMENT_EXCEPTION(name)
  macros may be used to define the raise and clone members in user-defined
  exceptions.

*****************************************************************************/

#include <rw/threxcept/pkgdefs.h>
#include <rw/threxcept/thrmsg.h>
#include <rw/cstring.h>
#include <rw/rwerr.h>

RW_THREXCEPT_SYMBOLIC RWCString rwToRWCString(int i);
RW_THREXCEPT_SYMBOLIC RWCString rwGetLastErrorMsg(void);
RW_THREXCEPT_SYMBOLIC RWCString rwErrorMsg(int error);
RW_THREXCEPT_SYMBOLIC RWCString rwErrnoMsg(void);

/**
 * \ingroup thread_compatible_exceptions_package
 * Declares the functions necessary to pass RWTHRxmsg-derived exception
 * objects across thread boundaries. This macro must be placed inside your
 * class declaration.
 */
#define RW_THR_DECLARE_EXCEPTION(Name)                      \
   public:                                                  \
      /* Throw the derived exception type! */               \
      virtual                                               \
      void                                                  \
      raise(void) const;                                    \
                                                            \
      virtual                                               \
      RWTHRxmsg*                                            \
      clone(void) const;

/**
 * \ingroup thread_compatible_exceptions_package
 * Similar to RW_THR_DECLARE_EXCEPTION, instead declaring and defining the
 * necessary functions inline. Do not use either of
 * RW_THR_IMPLEMENT_EXCEPTION or RW_THR_IMPLEMENT_TRACEABLE_EXCEPTION macros
 * if you use this macro.
 */
#define RW_THR_DECLARE_INLINE_EXCEPTION(Name)               \
   public:                                                  \
      /* Throw the derived exception type! */               \
      virtual                                               \
      void                                                  \
      raise(void) const                                     \
      {                                                     \
         throw Name(*this);                                 \
      }                                                     \
                                                            \
      virtual                                               \
      RWTHRxmsg*                                            \
      clone(void) const                                     \
      {                                                     \
         return new Name(*this);                            \
      }

/**
 * \ingroup thread_compatible_exceptions_package
 * Defines the functions necessary to pass RWTHRxmsg-derived exception
 * objects across thread boundaries.
 */
#define RW_THR_IMPLEMENT_EXCEPTION(Name)                    \
/* virtual */                                               \
void                                                        \
Name::raise(void) const                                     \
{                                                           \
   throw Name(*this);                                       \
}                                                           \
                                                            \
/* virtual */                                               \
RWTHRxmsg*                                                  \
Name::clone(void) const                                     \
{                                                           \
   return new Name(*this);                                  \
}

/**
 * \ingroup thread_compatible_exceptions_package
 * Defines the functions necessary to pass RWTHRxmsg-derived exception
 * objects across thread boundaries. It is intended to be used for classes
 * that provide tracing support.
 */
#define RW_THR_IMPLEMENT_TRACEABLE_EXCEPTION(Name)          \
/* virtual */                                               \
void                                                        \
Name::raise(void) const                                     \
{                                                           \
   RW_THREXCEPT_TRACEABLE_MEMBER(#Name"_raise", Name)       \
   throw Name(*this);                                       \
}                                                           \
                                                            \
/* virtual */                                               \
RWTHRxmsg*                                                  \
Name::clone(void) const                                     \
{                                                           \
   RW_THREXCEPT_TRACEABLE_MEMBER(#Name"_clone", Name)       \
   return new Name(*this);                                  \
}


#define RW_THR_IMPLEMENT_EXCEPTION_T1(Name,TP1)             \
template <class TP1>                                        \
/* virtual */                                               \
void                                                        \
Name::raise(void) const                                     \
{                                                           \
   throw Name(*this);                                       \
}                                                           \
                                                            \
template <class TP1>                                        \
/* virtual */                                               \
RWTHRxmsg*                                                  \
Name::clone(void) const                                     \
{                                                           \
   return new Name(*this);                                  \
}

#define RW_THR_IMPLEMENT_TRACEABLE_EXCEPTION_T1(Name,TP1)   \
template <class TP1>                                        \
/* virtual */                                               \
void                                                        \
Name::raise(void) const                                     \
{                                                           \
   RW_THREXCEPT_TRACEABLE_TEMPLATE_MEMBER(#Name"_raise", Name) \
   throw Name(*this);                                       \
}                                                           \
                                                            \
template <class TP1>                                        \
/* virtual */                                               \
RWTHRxmsg*                                                  \
Name::clone(void) const                                     \
{                                                           \
   RW_THREXCEPT_TRACEABLE_TEMPLATE_MEMBER(#Name"_clone", Name) \
   return new Name(*this);                                  \
}

/**
 * \ingroup thread_compatible_exceptions_package
 *
 * \brief
 * Base class for thread-compatible exceptions.
 *
 * RWTHRxmsg is the base class for <em>thread-compatible</em> exceptions. A
 * thread-compatible exception has clone() and raise() members that allow
 * the exception to be copied and stored so that it may be rethrown in the
 * future. These capabilities allow derived exceptions to be passed across
 * thread boundaries.
 */
class RW_THREXCEPT_GLOBAL RWTHRxmsg :
    public RWxmsg
{

public:

    /**
     * Throws an exception of the runtime (derived) type of self.
     */
    virtual void raise(void) const;

    /**
     * Calls the copy constructor of the runtime (derived) type of self and
     * returns the result.
     */
    virtual RWTHRxmsg* clone(void) const;

public:

    /**
     * Constructs an exception with an empty message string.
     */
    RWTHRxmsg(void);

    /**
     * Constructs an exception with the specified message string.
     */
    RWTHRxmsg(const RWCString& msg);

    // Construct an exception initializing its message string
    // using the message string value of another exception
    /**
     * Copy constructor.
     */
    RWTHRxmsg(const RWTHRxmsg& second);

    // This function has virtual members, so it needs
    // a virtual destructor...
    /**
     * Virtual destructor.
     */
    virtual
    ~RWTHRxmsg(void);

};

#endif  // __rw_threxcept_RWTHRxmsg_h__
