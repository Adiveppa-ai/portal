#ifndef __rw_pop3_RWPop3Agent_h__
#define __rw_pop3_RWPop3Agent_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pop3/RWPop3Agent.h#1 $
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

#include <rw/pop3/RWPop3AgentImp.h>
#include <rw/pop3/pkgdefs.h>
#include <rw/internet/RWAgent.h>
#include <rw/network/RWSocketPortal.h>
#include <rw/itc/RWTIOUResult.h>

class RWCString;

/**
 * \ingroup pop3_package
 *
 * \brief
 * Enables basic POP3 mail access, with more details of the POP3 protocol
 * than the RWPop3Client class, but less flexibility.
 *
 * RWPop3Agent enables basic POP3 mail access. It includes more of the
 * details of the POP3 protocol than the RWPop3Client class, but has less
 * flexibility.
 *
 * RWPop3Agent performs actions in a transaction-based model (contrast with
 * the connection-based model of the RWPop3Client). Its methods interact
 * with the server by connecting (if not already connected) and then
 * performing the requested actions. Unlike other thread-hot Internet agent
 * classes, such as RWFtpAgent, class RWPop3Agent remains connected between
 * transactions because POP3 relies on transient, connection-based
 * information. Multiple transactions may be performed before the object is
 * destroyed. The destructor of the agent disconnects from the server and
 * cleans up its own data.
 *
 * RWPop3Agent objects are lightweight. They are implemented using the
 * interface-implementation idiom. The RWPop3Agent is a handle to an
 * implementation that performs the protocol interaction.
 *
 * \example
 * \code
 * #include <rw/rstream.h>
 * #include <rw/cstring.h>
 *
 * #include <rw/network/RWSocketPortal.h>
 * #include <rw/network/RWPortalIStream.h>
 * #include <rw/network/RWWinSockInfo.h>
 *
 * #include <rw/pop3/util.h>
 * #include <rw/pop3/RWPop3Agent.h>
 *
 * int
 * main()
 * {
 *     RWWinSockInfo info;
 *
 *     try {
 *         // Create an agent to talk with our POP3 server.
 *         RWPop3Agent agent("mail.roguewave.com",
 *                           "account",
 *                           "password");
 *
 *         // Get the number of messages in our POP3 mail drop
 *         int n = agent.messages();
 *
 *         // If we have at least one, then go get it and
 *         // display on the screen.
 *         if (n>0) {
 *             // Force the RWTIOUResult<RWSocketPortal> to redeem
 *             // immediately for our portal.
 *             RWSocketPortal p = agent.get(1);
 *
 *             {
 *                  RWPortalIStream istrm(p);
 *                  RWCString text;
 *                  bool endOfMessage = false;
 *
 *                  // Read the lines in the message until
 *                  // the end of message marker
 *                  // <period><cr><lf>
 *                  do {
 *                     // Let RWCString do the hard work
 *                     text.readLine(istrm);
 *
 *                     // Remove <cr><lf>
 *                     text = rwNormalizeLine(text);
 *                     if (text==".")
 *                        endOfMessage = true;
 *                     else
 *                        std::cout << text << std::endl;
 *                 } while (!endOfMessage);
 *
 *             } // stream scope
 *         }
 *     }
 *     catch (const RWxmsg& m) {
 *         std::cout << "Error : " << m.why() << std::endl;
 *     }
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_POP3_SYMBOLIC RWPop3Agent : public RWAgent
{

public:

    /**
     * Constructs a default invalid RWPop3Agent. Redemption of an
     * RWTIOUResult from any call on a default agent throws an exception.
     * Use the assignment operator to initialize a default RWPop3Agent
     * object.
     */
    RWPop3Agent(void);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3Agent(const RWSockAddrBase&, const RWCString&, const RWCString&) instead")
    RWPop3Agent(const RWCString& host, const RWCString& user, const RWCString& password);
    // Constructor.  'host' is a host name or ip address of the pop3 server
    // machine.  'user' is the user name (mailbox) name we are interested in
    // and 'password' is the password to use to gain access to the mailbox.
#endif

    /**
     * Constructs an RWPop3Agent that is ready to use in subsequent,
     * transactional calls. The \a address argument is the address of the
     * POP3 server. The \a user and \a password arguments are the user and
     * password to use during the POP3 login negotiation sequence. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    RWPop3Agent(const RWSockAddrBase& address, const RWCString& user, const RWCString& password);

    /**
     * Sets the network timeout value (in milliseconds).
     */
    void
    setTimeout(unsigned long timeout);

    /**
     * Retrieves the current network timeout value (in milliseconds).
     */
    unsigned long
    getTimeout(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3Agent::getMessageCount() instead")
    RWTIOUResult<int>
    messages(void);
#endif

    /**
     * Returns an RWTIOUResult with a redeemable \c int. The \c int that is
     * returned is a count of the waiting messages in the specified mail
     * drop.
     */
    RWTIOUResult<int>
    getMessageCount(void);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3Agent::getMessage() instead")
    RWTIOUResult<RWSocketPortal>
    get(int messageIndex);
#endif

    /**
     * Opens a data connection to a specified message on the POP3 server. It
     * returns an RWTIOUResult with a redeemable RWSocketPortal. The
     * RWSocketPortal that is returned is a socket portal to the data
     * communication channel used to complete the data (message retrieval)
     * portion of the protocol transfer. The \a messageIndex argument is the
     * message number of the requested message.
     */
    RWTIOUResult<RWSocketPortal>
    getMessage(int messageIndex);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3Agent::removeMessage() instead")
    RWTIOUResult<RWPop3Reply>
    remove(int messageIndex);
#endif

    /**
     * Returns an RWTIOUResult with a redeemable RWPop3Reply that contains
     * an error if the method failed. The method deletes a message whose
     * index is \a messageIndex. Your application should not use
     * \a messageIndex again.
     */
    RWTIOUResult<RWPop3Reply>
    removeMessage(int messageIndex);

private:

    RWPop3AgentImp*
    pop3Impl(void) const;
    // returns native pointer to the smtp agent implementation.
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWTIOUResult<int>
RWPop3Agent::messages(void)
{
    return getMessageCount();
}

inline RWTIOUResult<RWSocketPortal>
RWPop3Agent::get(int messageIndex)
{
    return getMessage(messageIndex);
}

inline RWTIOUResult<RWPop3Reply>
RWPop3Agent::remove(int messageIndex)
{
    return removeMessage(messageIndex);
}

typedef RW_DEPRECATE_TYPE("Use RWPop3Agent instead") RWPop3Agent RWIPop3Agent;
#endif

#endif // __rw_pop3_RWPop3Agent_h__
