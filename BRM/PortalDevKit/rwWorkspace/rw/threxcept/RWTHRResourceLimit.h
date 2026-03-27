#ifndef __rw_threxcept_RWTHRResourceLimit_h__
#define __rw_threxcept_RWTHRResourceLimit_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/threxcept/RWTHRResourceLimit.h#1 $
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

#include <rw/threxcept/RWTHRxmsg.h>
#include <rw/threxcept/pkgdefs.h>

/**
 * \ingroup thread_compatible_exceptions_package
 *
 * \brief
 * Exception thrown when an operation cannot be performed due to memory or
 * system resource constraints.
 *
 * An RWTHRResourceLimit exception is thrown when an operation cannot be
 * performed because of memory or system resource constraints.
 */
class RW_THREXCEPT_GLOBAL RWTHRResourceLimit :
    public RWTHRxmsg
{

    RW_THR_DECLARE_EXCEPTION(RWTHRResourceLimit)

public:

    /**
     * Constructs an exception with a default message.
     */
    RWTHRResourceLimit();

    /**
     * Constructs an exception with the message string set to \a reason.
     */
    RWTHRResourceLimit(const RWCString& reason);
    RWTHRResourceLimit(const RWTHRResourceLimit& second);
    RWTHRResourceLimit& operator=(const RWTHRResourceLimit& second);
    ~RWTHRResourceLimit(void);

};

#endif // __rw_threxcept_RWTHRResourceLimit_h__
