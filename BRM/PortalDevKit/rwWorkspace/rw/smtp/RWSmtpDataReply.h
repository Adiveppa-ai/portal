#ifndef __rw_smtp_RWSmtpDataReply_h__
#define __rw_smtp_RWSmtpDataReply_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/smtp/RWSmtpDataReply.h#1 $
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

#include <rw/smtp/RWSmtpReply.h>
#include <rw/smtp/pkgdefs.h>
#include <rw/network/RWSocketPortal.h>

class RWSmtpFSM;

/**
 * \ingroup smtp_package
 *
 * \brief
 * Encapsulates an RWSocketPortal that writes the body of a mail message.
 *
 * RWSmtpDataReply is a specialization class of RWSmtpReply. It contains an
 * RWSocketPortal that writes the body of a mail message.
 */
class RW_SMTP_GLOBAL RWSmtpDataReply : public RWSmtpReply
{

    friend class RWSmtpFSM;

public:

    /**
     * Constructs a default invalid RWSmtpDataReply object. You need to use
     * the assignment operator to initialize it.
     */
    RWSmtpDataReply(void);

    /**
     * Copy constructor.
     */
    RWSmtpDataReply(const RWSmtpDataReply& reply);

    /**
     * Assignment operator. Sets self to the contents of \a reply. The
     * previous contents of self are lost.
     */
    RWSmtpDataReply&
    operator=(const RWSmtpDataReply& reply);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWSmtpDataReply::getPortal() instead")
    RWSocketPortal portal(void) const;
#endif

    /**
     * Returns the underlying socket portal. This portal is used to transfer
     * the body portion of the mail message.
     */
    RWSocketPortal getPortal(void) const;

private:

    void setPortal(const RWSocketPortal& portal);
    // sets the data portal that will be contained within the
    // reply set.

    RWSocketPortal portal_;
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWSocketPortal
RWSmtpDataReply::portal(void) const
{
    return getPortal();
}

typedef RW_DEPRECATE_TYPE("Use RWSmtpDataReply instead") RWSmtpDataReply RWISmtpDataReply;
#endif

#endif // __rw_smtp_RWSmtpDataReply_h__
