#ifndef __rw_smtp_RWSmtpReply_h__
#define __rw_smtp_RWSmtpReply_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/smtp/RWSmtpReply.h#1 $
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

#include <rw/smtp/pkgdefs.h>
#include <rw/internet/RWNumReply.h>

class RWSmtpFSM;

/**
 * \ingroup smtp_package
 *
 * \brief
 * Base class for all SMTP protocol reply messages.
 *
 * RWSmtpReply is the base class for all SMTP protocol reply messages. It is
 * a subclass of RWNumReply and does not add additional methods.
 */
class RW_SMTP_GLOBAL RWSmtpReply : public RWNumReply
{

    friend class RWSmtpFSM;

public:

    /**
     * Default constructor.
     */
    RWSmtpReply(void);

};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWSmtpReply instead") RWSmtpReply RWISmtpReply;
#endif

#endif // __rw_smtp_RWSmtpReply_h__
