#ifndef __rw_smtp_RWSmtpAgent_h__
#define __rw_smtp_RWSmtpAgent_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/smtp/RWSmtpAgent.h#1 $
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

#include <rw/smtp/RWSmtpAgentImp.h>
#include <rw/smtp/pkgdefs.h>
#include <rw/internet/RWAgent.h>
#include <rw/network/RWSocketPortal.h>
#include <rw/itc/RWTIOUResult.h>
#include <rw/cstring.h>

/**
 * \ingroup smtp_package
 * \class RWSmtpAgent
 *
 * \brief
 * Sends data to a server via the SMTP protocol.
 *
 * RWSmtpAgent sends data to a server via the SMTP protocol. It includes
 * more of the details of the SMTP protocol than the RWSmtpClient class, but
 * has less flexibility.
 *
 * RWSmtpAgent performs actions in a transaction-based model rather than the
 * connection-based model of the RWSmtpClient. Its methods interact with an
 * SMTP server by connecting, performing the requested action, and
 * disconnecting. Multiple transactions may be performed before the agent
 * object is destroyed. The destructor cleans up resources.
 *
 * RWSmtpAgent objects are lightweight. They are implemented using the
 * interface-implementation idiom. The RWSmtpAgent is a handle to an
 * implementation that performs the protocol interaction.
 *
 * \example
 * \code
 * #include <rw/rstream.h>
 * #include <rw/cstring.h>
 *
 * #include <rw/network/RWSocketPortal.h>
 * #include <rw/network/RWWinSockInfo.h>
 *
 * #include <rw/smtp/RWSmtpAgent.h>
 *
 * int main()
 * {
 *     RWWinSockInfo info;
 *
 *     try {
 *         // Construct an agent to talk with our known
 *         // SMTP server
 *         RWSmtpAgent agent("smtp.roguewave.com");
 *
 *         // Force the RWTIOUResult<RWSocketPortal> to redeem
 *         // immediately for our portal.
 *         RWSocketPortal portal =
 *            agent.send("fred@roguewave.com",
 *                       "bill@anywhere.com");
 *
 *         // Send our one line message, on the way out.
 *         portal.sendAtLeast("I've gone to the beach.");
 *
 *         // Close up the agent and go to the beach...
 *         // Force the RWTIOUResult<bool> to
 *         // redeem immediately
 *         // for the result.
 *         bool result = agent.dataClose();
 *     }
 *     catch (const RWxmsg& m) {
 *         std::cout << "Error : " << m.why() << std::endl;
 *     }
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_SMTP_SYMBOLIC RWSmtpAgent : public RWAgent
{

public:

    /**
     * Enumerates whether or not default header information should be
     * included in a mail message.
     */
    enum headerMode {

        /**
         * Includes the \c To and \c From headers in the header section of
         * the message.
         */
        DEFAULT_HEADERS,

        /**
         * Does not include the \c To and \c From headers in the header
         * section of the message. Almost all SMTP servers include the
         * \c From header automatically. Applications can include the
         * information at the beginning of a mail message.
         */
        NO_HEADERS
    };

    /**
     * Constructs a default invalid RWSmtpAgent object. Redemption of an
     * RWTIOUResult from any call on a default agent throws an exception.
     * Use the assignment operator to initialize a default RWSmtpAgent.
     */
    RWSmtpAgent(void);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWSmtpAgent(const RWSockAddrBase&, const RWCString&) instead")
    RWSmtpAgent(const RWCString& smtpHost, const RWCString& localHost = "localhost");
    // Constructor.  smtpHost is a host name or ip address of the smtp server
    // machine.  localHost is the client host.
#endif

    /**
     * Constructs an RWSmtpAgent object that is ready to use in a subsequent
     * call to the send() method. The \a address parameter is the address of
     * the SMTP server. The \a localHost argument is the name of the client
     * host used to greet the SMTP server. Generally this is the name of the
     * local host, which is the default. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWSmtpAgent(const RWSockAddrBase& address, const RWCString& localHost = "localhost");

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

    /**
     * Returns an RWTIOUResult with a redeemable RWSocketPortal. You can use
     * the RWSocketPortal that is returned to complete the data portion of
     * the protocol transfer. The \a from argument is a string representing
     * the RFC822-compliant email address of the sender. The \a to argument
     * is a string representing the RFC822-compliant e-mail address of the
     * recipient. The \a h argument controls the inclusion of default header
     * information in the message. If this value is the default
     * #DEFAULT_HEADERS, then \c To: and \c From: headers are included
     * automatically in the data stream before the portal becomes available.
     * Almost all SMTP servers include the \c From header in the email.
     *
     * Including default headers does not prevent the application from
     * including other headers (for example, a subject header), but it is an
     * easy way to include the minimum customary header information.
     *
     * The message sent through the socket portal must be formatted
     * according to the SMTP specification: Leading periods on a line must
     * be doubled except for the "end of message" signal, which is handled
     * by the dataClose() method. You can use the global function
     * rwAddPeriods() to help you format the message. For more information,
     * see rwAddPeriods().
     *
     * After a successful data transfer using the returned RWSocketPortal,
     * your application must call the dataClose() method to complete the
     * body of the mail message. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    RWTIOUResult<RWSocketPortal>
    send(const RWCString& from, const RWCString& to, headerMode h = RWSmtpAgent::DEFAULT_HEADERS);

    /**
     * Closes the body of a mail message opened with the send() method. This
     * method writes the body termination sequence \c \<period\>\<cr\>\<lf\>
     * to the available data socket portal to indicate the end of the
     * message.
     */
    RWTIOUResult<bool>
    dataClose(void);

private:

    RWSmtpAgentImp*
    smtpImpl(void) const;
    // native pointer to the smtp agent implementation.
};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWSmtpAgent instead") RWSmtpAgent RWISmtpAgent;
#endif

#endif // __rw_smtp_RWSmtpAgent_h__
