#ifndef __rw_pop3_RWPop3DataReply_h__
#define __rw_pop3_RWPop3DataReply_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pop3/RWPop3DataReply.h#1 $
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

#include <rw/pop3/RWPop3Reply.h>
#include <rw/pop3/pkgdefs.h>
#include <rw/network/RWSocketPortal.h>
#include <rw/cstring.h>

class RWPop3FSM;

/**
 * \ingroup pop3_package
 *
 * \brief
 * Encapsulates an RWSocketPortal that receives the data portion of a
 * message.
 *
 * RWPop3DataReply is derived from RWPop3Reply. RWPop3DataReply includes an
 * RWSocketPortal that receives the data portion of the message. You should
 * not close this socket portal. Take care to read data only up to the end
 * of the message marker \c \<period\>\<cr\>\<lf\> contained on a line by
 * itself.
 */
class RW_POP3_GLOBAL RWPop3DataReply : public RWPop3Reply
{

    friend class RWPop3FSM;

public:

    /**
     * Uses the assignment operator to initialize the default
     * RWPop3DataReply object.
     */
    RWPop3DataReply(void);
    // Default constructor

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3DataReply::getPortal() instead")
    RWSocketPortal portal(void) const;
#endif

    /**
     * Returns the connected data portal to read data from the underlying
     * socket.
     */
    RWSocketPortal getPortal(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3DataReply::getText() instead")
    RWCString additionalData(void) const;
#endif

    /**
     * Returns additional information available on the POP3 reply line. If
     * no additional data is available following either \c +OK or \c -ERR,
     * then the method returns a null string. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWCString getText(void) const;

private:

    /**
     * \relates RWPop3DataReply
     *
     * Outputs an RWPop3DataReply object to an \b std::ostream.
     *
     * \note
     * RWPop3DataReply does not have an extraction (>>) operator.
     */
    friend RW_POP3_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWPop3DataReply& r);

private:

    /**
     * Performs an extended parse to obtain the additional text that follows
     * either \c +OK or \c -ERR on the reply line.
     */
    virtual void parse(void);

    void setPortal(const RWSocketPortal& portal);
    // sets the data portal that will be contained within the
    // reply.

    RWSocketPortal  portal_;
    RWCString text_;
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWSocketPortal
RWPop3DataReply::portal(void) const
{
    return getPortal();
}

inline RWCString
RWPop3DataReply::additionalData(void) const
{
    return getText();
}

typedef RW_DEPRECATE_TYPE("Use RWPop3DataReply instead") RWPop3DataReply RWIPop3DataReply;
#endif

#endif // __rw_pop3_RWPop3DataReply_h__
