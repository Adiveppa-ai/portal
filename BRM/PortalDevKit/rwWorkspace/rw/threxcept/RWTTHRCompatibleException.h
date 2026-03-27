#ifndef __rw_threxcept_RWTTHRCompatibleException_h__
#define __rw_threxcept_RWTTHRCompatibleException_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/threxcept/RWTTHRCompatibleException.h#1 $
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

  RWTTHRCompatibleException<Exception> - A template class that can be used
  to create a thread-compatible exception from an existing exception class.
  A thread-compatible exception is derived from RWTHRxmsg, and possesses
  clone() and raise() members that allow for a copy of the exception to be
  stored so that it may be rethrown in the future.  This allows exceptions
  to be passed across thread boundaries.

*****************************************************************************/

#include <rw/threxcept/RWTHRxmsg.h>
#include <rw/threxcept/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWTHRCompatibleException RWTTHRCompatibleException
#endif

/**
 * \ingroup thread_compatible_exceptions_package
 *
 * \brief
 * Template class for creating a thread-compatible exception from an
 * existing exception class.
 *
 * RWTTHRCompatibleException<Exception> is a template class that can be used
 * to create a thread-compatible exception from an existing exception class.
 * A thread-compatible exception is derived from RWTHRxmsg, and possesses
 * clone() and raise() members that allow for a copy of the exception to be
 * stored so that it may be rethrown in the future. The ability to rethrow
 * exceptions in the future allows exceptions to be passed across thread
 * boundaries.
 *
 * \synopsis
 * #include <rw/threxcept/RWTTHRCompatibleException.h>
 *
 * class MyException {};
 * throw RWTTHRCompatibleException<MyException>(MyException());
 * \endsynopsis
 */
template <class Exception>
class RWTTHRCompatibleException :
    public RWTHRxmsg
{

protected:

    Exception   exception_;

public:

    /**
     * Constructs a new instance, initializing the internal exception
     * instance to \a exception.
     */
    RWTTHRCompatibleException(const Exception& exception);

    /**
     * Copy constructor. Constructs a new instance whose exception value is
     * initialized from the exception within \a second.
     */
    RWTTHRCompatibleException(const RWTTHRCompatibleException<Exception>& second);

    /**
     * Destructor.
     */
    ~RWTTHRCompatibleException(void);

    /**
     * Cast operator. Returns internal \c Exception instance.
     */
    operator Exception(void) const;

    /**
     * Copies the internal exception within \a second to self.
     */
    RWTTHRCompatibleException<Exception>&
    operator=(const RWTTHRCompatibleException<Exception>& second);

    /**
     * Makes a copy of this so it can be stored.
     */
    virtual
    RWTHRxmsg*
    clone(void) const;

    /**
     * Throws the exception stored in this.
     */
    virtual
    void
    raise(void) const;

};

/*****************************************************************************/

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/threxcept/RWTTHRCompatibleException.cc>
#endif

#endif // __rw_threxcept_RWTTHRCompatibleException_h__
