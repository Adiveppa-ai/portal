#ifndef __rw_smtp_RWSmtpClient_h__
#define __rw_smtp_RWSmtpClient_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/smtp/RWSmtpClient.h#1 $
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

#include <rw/smtp/RWSmtpClientImp.h>
#include <rw/smtp/pkgdefs.h>
#include <rw/network/RWTNetHandle.h>
#include <rw/itc/RWTIOUResult.h>

class RWCString;

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup smtp_package
 * \class RWSmtpClient
 *
 * \brief
 * Enables low-level access to the SMTP client-side protocol.
 *
 * RWSmtpClient enables low-level access to the SMTP client-side protocol.
 * The names of the methods parallel the names of the protocol actions. An
 * RWSmtpClient object maintains a finite state machine to enforce correct
 * SMTP protocol action ordering. In the case of misordered method
 * invocation, an RWProtocolClientCmdSequenceError exception is thrown.
 *
 * All client methods return RWTIOUResult instances that are redeemable for
 * a particular type of RWSmtpReply. RWSmtpReply and its subclass
 * RWSmtpDataReply contain an encapsulation of standard SMTP protocol reply
 * messages. RWSmtpDataReply returns additional data-related information.
 *
 * RWSmtpClient objects are lightweight. They are implemented using the
 * interface-implementation idiom. The RWSmtpClient is a handle to an
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
 * #include <rw/smtp/RWSmtpClient.h>
 *
 * int main()
 * {
 *     RWWinSockInfo info;
 *
 *     RWSmtpClient client;    // SMTP client object
 *     RWSmtpReply reply;      // SMTP general reply
 *     RWSmtpDataReply dReply; // SMTP data reply
 *
 *     try {
 *         // Connect to our SMTP server
 *         reply = client.connect("smtp.roguewave.com");
 *
 *         // Say hello from the local machine
 *         reply = client.helo("tsunami");
 *
 *         // Mail From: and To:
 *         reply = client.mail("customer.roguewave.com");
 *         reply = client.rcpt("support.roguewave.com");
 *
 *         // Send a help message
 *         dReply = client.dataOpen();
 *         dReply.getPortal().sendAtLeast("We've got a problem... \n");
 *         dReply.getPortal().sendAtLeast("Please help immediately");
 *
 *         // Indicate it's the end of the message
 *         reply = client.dataClose();
 *
 *         // Send more messages, if you like
 *
 *         // Finally shut down the connection
 *         reply = client.quit();
 *     }
 *     catch (const RWxmsg& m) {
 *         std::cout << "Error : " << m.why() << std::endl;
 *     }
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_SMTP_SYMBOLIC RWSmtpClient
{
public:

    /**
     * SMTP authentication method.
     */
    enum authenticationType {

        /**
         * Use the CRAM-MD5 authentication mechanism (see RFC 2195)
         */
        CRAM_MD5 = 1
    };

public:

    /**
     * Default constructor.
     */
    RWSmtpClient(void);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWSmtpClient::connect(const RWSockAddrBase&) instead")
    RWTIOUResult<RWSmtpReply>
    connect(const RWCString& host, int port = 25);
    // provides a connect method, host is expected to
    // an IP address or host domain name.
#endif

    /**
     * Establishes a connection with an SMTP server. The \a address argument
     * is the address of the SMTP server. A successful reply is normally in
     * the \c 2XX family.
     */
    RWTIOUResult<RWSmtpReply>
    connect(const RWSockAddrBase& address);

    /**
     * Performs the protocol \c HELO action. The \c HELO action informs the
     * SMTP server of the name of the client machine sending the mail,
     * specified as the \a localMachine argument. A successful reply is
     * normally in the \c 2XX family. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWTIOUResult<RWSmtpReply>
    helo(const RWCString& localMachine);

    /**
     * Performs the protocol \c EHLO action, which is just like \c HELP, but
     * the server's response text provides computer-readable information
     * about the server's abilities. A successful reply is normally in the
     * \c 2XX family. The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWSmtpReply>
    ehlo(const RWCString& localMachine);

    /**
     * Performs authentication according to RFC 2554 and RFC 4422. The only
     * authentication mechanism supported is CRAM-MD5 (see RFC 2195).
     */
    RWTIOUResult<RWSmtpReply>
    auth(RWCString const& user,
         RWCString const& passwd,
         authenticationType);

    /**
     * Performs the protocol \c MAIL action. The \a from argument is the
     * email address of the mail sender. The \c MAIL action sends the email
     * address to the SMTP server. A successful reply is normally in the
     * \c 2XX family. The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWSmtpReply>
    mail(const RWCString& from);

    /**
     * Performs the protocol \c RCPT action. The \a to argument is the email
     * address of the recipient. The \c RCPT action sends the email address
     * to the SMTP server. A successful reply is normally in the \c 2XX
     * family. The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWSmtpReply>
    rcpt(const RWCString& to);

    /**
     * Performs the protocol \c RSET action that takes the internal state
     * machine and connection back to the initially connected state. Your
     * application should call the \c HELO action next. A successful reply
     * is normally in the \c 2XX family.
     */
    RWTIOUResult<RWSmtpReply>
    rset(void);

    /**
     * Performs the protocol \c VRFY action. The \a who argument specifies
     * the email recipient. The \c VRFY action requests confirmation of the
     * validity of the email recipient without sending a message. A
     * successful reply is normally in the \c 2XX family if the email
     * address is known by the destination. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWTIOUResult<RWSmtpReply>
    vrfy(const RWCString& who);

    /**
     * Performs the protocol \c EXPN action. The \c EXPN action is similar
     * to the \c VRFY action, except that some servers expand the email
     * address if it is a mailing list. The \a who argument is the email
     * address of the mail recipient. A successful reply is normally in the
     * \c 2XX family if the email address is known by the destination. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWSmtpReply>
    expn(const RWCString& who);

    /**
     * Performs the protocol \c DATA action. The \c DATA action informs the
     * SMTP server that the following data should be considered the body of
     * the message. By definition, the body of the message is terminated by
     * a line containing only \c \<period\>\<cr\>\<lf\>. The dataClose()
     * method inserts this sequence into the data stream, so it is your
     * responsibility to ensure that the data termination sequence is not
     * contained within the body of the message.
     *
     * You can use the global function rwAddPeriods() to help you format the
     * message. For more information, see rwAddPeriods(). A successful reply
     * is normally in the \c 3XX family.
     *
     * The method returns an RWTIOUResult with a redeemable RWSmtpReply.
     * Data (message body) can then be written to the socket portal that is
     * returned from the RWSmtpDataReply
     * \ref RWSmtpDataReply::getPortal() "getPortal()" method.
     */
    RWTIOUResult<RWSmtpDataReply>
    dataOpen(void);

    /**
     * Closes the body of the mail message opened with dataOpen(). This
     * method writes the body termination sequence
     * \c \<period\>\<cr\>\<lf\>.
     */
    RWTIOUResult<RWSmtpReply>
    dataClose(void);

    /**
     * Closes the connection to the SMTP server.
     */
    RWTIOUResult<RWSmtpReply>
    quit(void);

    /**
     * Performs the protocol \c NOOP action. The \c NOOP action is often
     * used to test whether the established connection to the SMTP server is
     * still valid before the client sends a message. A successful reply is
     * normally in the \c 2XX family.
     */
    RWTIOUResult<RWSmtpReply>
    noop(void);

    /**
     * Sets the network timeout value (in milliseconds).
     */
    void
    setTimeout(unsigned long timeout);
    // the timeout will not be in effect until all previous
    // requests have been satisfied. all requests submitted
    // after a timeout has been set will use that timeout
    // value, until the timeout is set again.

    /**
     * Retrieves the current network timeout value (in milliseconds).
     */
    unsigned long
    getTimeout(void) const;

private:

    // Implementation Handle
    RWTNetHandle<RWSmtpClientImp> impl_;

};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWSmtpClient instead") RWSmtpClient RWISmtpClient;
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_smtp_RWSmtpClient_h__
