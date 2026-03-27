/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/threxcept/RWTTHRCompatibleException.cc#1 $
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

  RWTTHRCompatibleException<Exception> - wrapper class to convert template
  parameter type to a RWTHRxmsg exception.

*****************************************************************************/

#include <rw/threxcept/RWTTHRCompatibleException.h>

template <class Exception>
RWTTHRCompatibleException<Exception>::RWTTHRCompatibleException(const Exception& exception)
    : exception_(exception)
{
}

template <class Exception>
RWTTHRCompatibleException<Exception>::RWTTHRCompatibleException(const RWTTHRCompatibleException<Exception>& second)
    : RWTHRxmsg(second),
      exception_(second.exception_)
{
}

template <class Exception>
RWTTHRCompatibleException<Exception>::~RWTTHRCompatibleException(void)
{
}

template <class Exception>
RWTTHRCompatibleException<Exception>::operator Exception(void) const
{
    return exception_;
}

template <class Exception>
RWTTHRCompatibleException<Exception>&
RWTTHRCompatibleException<Exception>::operator=(const RWTTHRCompatibleException<Exception>& second)
{
    if (&second != this) {
        exception_ = second.exception_;
    }
    return *this;
}

template <class Exception>
void
RWTTHRCompatibleException<Exception>::raise(void) const
{
    // xlC differentiates between throwing a "const Exception" and throwing an "Exception".
    // We want to throw the latter, hence the cast:
    throw const_cast< Exception& >(exception_);
}

template <class Exception>
RWTHRxmsg*
RWTTHRCompatibleException<Exception>::clone(void) const
{
    return new RWTTHRCompatibleException<Exception>(*this);
}
