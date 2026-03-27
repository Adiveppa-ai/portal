#ifndef __rw_pop3_RWPop3AgentImp_h__
#define __rw_pop3_RWPop3AgentImp_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pop3/RWPop3AgentImp.h#1 $
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

#include <rw/pop3/RWPop3Client.h>
#include <rw/pop3/pkgdefs.h>
#include <rw/internet/RWAgentImp.h>
#include <rw/itc/RWTIOUEscrow.h>

#define POP3AI_POPHOST_KEY "Host"
#define POP3AI_USER_KEY    "User"
#define POP3AI_PASS_KEY    "Pass"
#define POP3AI_INDEX_KEY   "Index"

/*
 * RWPop3AgentImp
 *
 * RWPop3AgentImp is an implementation class of its interface counterpart
 * RWPop3Agent. The main functionality of RWPop3AgentImp is to handle
 * all POP3 agent commands dispatched from RWPop3Agent.
 *
 */

class RW_POP3_GLOBAL RWPop3AgentImp : public RWAgentImp
{

public:

    RWPop3AgentImp(void);
    // Default constructor

    virtual ~RWPop3AgentImp(void);
    // Destructor

    void
    init(void);
    // informs that stat machine that initial data
    // has been set in the property dictionary.

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3AgentImp::getMessageCount() instead")
    void
    messages(RWTIOUEscrow<int> iouEscrow);
#endif
    void
    getMessageCount(RWTIOUEscrow<int> iouEscrow);
    // connects to the pop3 server (if not already
    // connected) and asks for the number of messages
    // being held for the user.

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3AgentImp::getMessage() instead")
    void
    get(RWTIOUEscrow<RWSocketPortal> iouEscrow);
#endif
    void
    getMessage(RWTIOUEscrow<RWSocketPortal> iouEscrow);
    // opens a data connection to the specified mail
    // message.

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3AgentImp::removeMessage() instead")
    void
    remove(RWTIOUEscrow<RWPop3Reply> iouEscrow);
#endif
    void
    removeMessage(RWTIOUEscrow<RWPop3Reply> iouEscrow);
    // removes a message from the mail drop

    virtual void
    setProperty(const RWCString& p, const RWCString& v);
    // sets properties

    void
    setTimeout(unsigned long timeout);
    // sets network timeout in milliseconds

    unsigned long
    getTimeout(void) const;

private:

    enum { INIT_ACTION, DATA_ACTION };
    // states used by the simple state machine

    void
    connect(void);
    // negotiates a connection with
    // the pop3 server.

private:

    RWPop3Client pop3Client_;
    // The pop3Client that does all the work for us.

    int nextAction_;
    // The next valid action to be performed.

    bool connected_;
    // Flag that contains connected status.

    RWMutex threadMutex_;
    // controls thread access to the implementation.
};

#if !defined(RW_DISABLE_DEPRECATED)
inline void
RWPop3AgentImp::messages(RWTIOUEscrow<int> iouEscrow)
{
    getMessageCount(iouEscrow);
}

inline void
RWPop3AgentImp::get(RWTIOUEscrow<RWSocketPortal> iouEscrow)
{
    getMessage(iouEscrow);
}

inline void
RWPop3AgentImp::remove(RWTIOUEscrow<RWPop3Reply> iouEscrow)
{
    removeMessage(iouEscrow);
}

typedef RW_DEPRECATE_TYPE("Use RWPop3AgentImp instead") RWPop3AgentImp RWIPop3AgentImpl;
#endif

#endif // __rw_pop3_RWPop3AgentImp_h__
