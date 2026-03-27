#ifndef __rw_smtp_RWSmtpAgentImp_h__
#define __rw_smtp_RWSmtpAgentImp_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/smtp/RWSmtpAgentImp.h#1 $
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

#include <rw/smtp/RWSmtpClient.h>
#include <rw/smtp/pkgdefs.h>
#include <rw/internet/RWAgentImp.h>
#include <rw/itc/RWTIOUEscrow.h>

#define SMTPAI_SMTPHOST_KEY   "Host"
#define SMTPAI_LOCALHOST_KEY  "LocalHost"
#define SMTPAI_TO_KEY         "To"
#define SMTPAI_FROM_KEY       "From"
#define SMTPAI_HEADER_KEY     "Headers"

#define SMTPAI_ARG_LOCALHOST  "localhost"
#define SMTPAI_ARG_DEFHEADERS "defaultHeaders"
#define SMTPAI_ARG_NOHEADERS  "noHeaders"

/*
 * RWSmtpAgentImp
 *
 * RWSmtpAgentImp is an implementation class of its interface counterpart
 * RWSmtpAgent. The main functionality of RWSmtpAgentImp is to handle
 * all SMTP agent commands dispatched from RWSmtpAgent.
 *
 */

class RW_SMTP_GLOBAL RWSmtpAgentImp : public RWAgentImp
{

public:

    RWSmtpAgentImp(void);
    // Default constructor

    virtual ~RWSmtpAgentImp(void);
    // Destructor

    void
    init(void);
    // provides an initialization method used to signal
    // initial setup of property dictionary.

    void
    send(RWTIOUEscrow<RWSocketPortal> iouEscrow);
    // performs an agent send transaction.  This involves
    // login negotiation with the SMTP server and
    // opens a data connection to a new mail message.
    // A call to dataClose must follow this method.

    void
    dataClose(RWTIOUEscrow<bool> iouEscrow);
    // closes the mail message opened with the send
    // method.  This method must be called after a
    // call to send.  Once dataClose has been called
    // a new transaction may be made by calling send.

    virtual void setProperty(const RWCString& p, const RWCString& v);
    // Sets property p to value v.

    void
    setTimeout(unsigned long timeout);
    // sets network timeout in milliseconds

    unsigned long
    getTimeout(void) const;

private: // member functions

    void
    connect(void);

private: // data members

    enum { INIT_ACTION, SEND_ACTION, CLOSE_ACTION };
    // internal simple state machine states.

    RWSmtpClient smtpClient_;
    // smtp client that performs the work.

    int nextAction_;
    // next action that should be performed.

    bool connected_;
    // flag that contains control connection status.

    RWMutex threadMutex_;
    // exclusive thread access control.

    static const RWCString CRLF;
    // used in calls which must be terminated with CRLF
};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWSmtpAgentImp instead") RWSmtpAgentImp RWISmtpAgentImpl;
#endif

#endif // __rw_smtp_RWSmtpAgentImp_h__
