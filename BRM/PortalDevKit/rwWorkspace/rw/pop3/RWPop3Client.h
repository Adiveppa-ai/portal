#ifndef __rw_pop3_RWPop3Client_h__
#define __rw_pop3_RWPop3Client_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pop3/RWPop3Client.h#1 $
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

#include <rw/pop3/RWPop3ClientImp.h>
#include <rw/pop3/pkgdefs.h>
#include <rw/itc/RWTIOUResult.h>

class RWCString;

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#  pragma warning(disable : 4275)
#endif

/**
 * \ingroup pop3_package
 *
 * \brief
 * Enables low-level access to the POP3 client-side protocol.
 *
 * RWPop3Client enables low-level access to the POP3 client-side protocol.
 * The names of its methods parallel the names of the protocol commands. The
 * RWPop3Client class maintains a finite state machine to enforce correct
 * POP3 protocol action ordering. In the case of misordered method
 * invocation, an RWProtocolClientCmdSequenceError exception is thrown.
 *
 * Each client method returns an RWTIOUResult whose redeemable is a
 * particular type of RWPop3Reply. RWPop3Reply and its subclasses --
 * RWPop3ConnReply, RWPop3StatReply, and RWPop3DataReply -- contain
 * encapsulations of standard POP3 protocol reply messages. The derived
 * classes of RWPop3Reply return additional information specific to that
 * type of protocol reply.
 *
 * All multi-line POP3 responses are provided on a portal returned from
 * RWPop3DataReply::getPortal(). These lines are bounded by the octet pair
 * \c \<cr\>\<lf\>. The final line of a multi-line response consists of the
 * triplet \c \<period\>\<cr\>\<lf\>.
 *
 * RWPop3Client objects are lightweight. They are implemented using the
 * interface-implementation idiom. The RWPop3Client is a handle to an
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
 * #include <rw/pop3/RWPop3Client.h>
 *
 * #include <rw/internet/util.h>
 *
 * int main()
 * {
 *     RWWinSockInfo info;
 *
 *     RWPop3Client client;
 *     RWPop3ConnReply cReply;  // connection reply
 *     RWPop3Reply reply;       // general reply
 *     RWPop3StatReply sReply;  // status reply
 *     RWPop3DataReply dReply;  // data reply
 *
 *     try {
 *         // Establish a connection to our POP3 server
 *         cReply = client.connect("mail.roguewave.com");
 *
 *         // create a login session
 *         reply = client.user("account");
 *         reply = client.pass("password");
 *
 *         // scan the first 10 lines of each message in the
 *         // mail box
 *         sReply = client.stat();
 *         int n = sReply.messages();
 *         if(n > 0) {
 *             for (int I=0; I<n; I++) {
 *                 dReply = client.top(I+1, 10);
 *                 RWPortalIStream istrm(dReply.getPortal());
 *                 RWCString text;
 *                 do {
 *                    text =rwNormalizeLine(text.readLine(istrm));
 *                    if (text != ".") std::cout << text << std::endl;
 *                 } while (text != ".");
 *             }
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
class RW_POP3_SYMBOLIC RWPop3Client
{

public:

    /**
     * Constructs a default RWPop3Client.
     */
    RWPop3Client(void);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWPop3Client::connect(const RWSockAddrBase&) instead")
    RWTIOUResult<RWPop3ConnReply>
    connect(const RWCString& host, int port = 110);
    // provides a connect method, host is expected to
    // an IP address or host domain name.
#endif

    /**
     * Establishes a connection to a POP3 server. The \a address argument is
     * the address of the POP3 server. A successful reply is normally
     * \c +OK. An application usually calls the user() action next. If the
     * method fails, it throws an RWProtocolClientError exception.
     */
    RWTIOUResult<RWPop3ConnReply>
    connect(const RWSockAddrBase& address);

    /**
     * Invokes the \c USER command on an open POP3 mail account. It informs
     * the POP3 server of the name of the mail drop to access. A successful
     * reply is normally \c +OK. An application usually invokes the \c PASS
     * action next. The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWPop3Reply>
    user(const RWCString& user);

    /**
     * Invokes the \c PASS command on an open POP3 mail account. It informs
     * the POP3 server of the mail drop's password. A \a password is
     * required to access the mail drop. A successful reply is normally
     * \c +OK. An application would usually call the \c STAT, \c LIST,
     * \c RETR, \c DELE, \c TOP, or \c NOOP actions next. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWPop3Reply>
    pass(const RWCString& password);

    /**
     * Invokes the \c STAT command on an open POP3 mail account. It returns
     * the number of messages contained in the mail drop and the total
     * number of octets that the mail messages consume. A successful reply
     * is normally \c +OK.
     *
     * The method returns an RWTIOUResult, which is redeemable for an
     * RWPop3StatReply. RWPop3StatReply includes the
     * \ref RWPop3StatReply::getMessageCount() "getMessageCount()" method,
     * which returns the number of messages in the mail drop, and the
     * \ref RWPop3StatReply::getOctets() "getOctets()" method, which returns
     * the total number of octets.
     */
    RWTIOUResult<RWPop3StatReply>
    stat(void);

    /**
     * Invokes the \c LIST command on an open POP3 mail account. Returns an
     * RWTIOUResult with a redeemable RWPop3DataReply. The RWTIOUResult is
     * set invalid if the call is unsuccessful.
     *
     * This method has two modes, and they determine the behavior of the
     * socket portal associated with the redeemable return value:
     *
     * - The default mode, where the argument is zero, returns a list of all
     * messages on the socket portal. The server returns one scan listing
     * per message in the mail box. Each scan listing contains a message
     * index field, a size field, an optional further information field
     * (deprecated in the POP3 RFC), and a trailing \c \<cr\>\<lf\> to mark
     * the end of the individual scan listing line. The fields are separated
     * by a space. The message index is a string containing the base 10
     * representation of the index, and the size field is a string
     * containing the base 10 representation of the number of octets
     * contained in the message. The last line available from the socket
     * portal consists of \c \<period\>\<cr\>\<lf\>.
     * - The second mode, where the argument is a legal message index,
     * returns a single POP3 scan listing. The message id and size in
     * octets, formatted as for the multiple list command, are available by
     * calling \ref RWPop3DataReply::getText() "getText()" on the redeemable
     * returned by the command. No data is available at the socket portal.
     *
     * If you attempt to read from the portal when no data is available, the
     * reading thread blocks indefinitely.
     */
    RWTIOUResult<RWPop3DataReply>
    list(int message = 0);

    /**
     * Invokes the \c RETR command on an open POP3 mail account. It requests
     * that a data connection be opened to the message indexed by
     * \a message.
     *
     * The method returns an RWTIOUResult with a redeemable RWPop3DataReply.
     * An RWPop3DataReply object contains a socket portal that your
     * application can use to complete the data portion of the protocol
     * transfer. Reading from this portal returns the message data. POP3
     * mail messages are terminated by the data sequence
     * \c \<period\>\<cr\>\<lf\> contained on a line by itself. A successful
     * reply is normally \c +OK.
     */
    RWTIOUResult<RWPop3DataReply>
    retr(int message);

    /**
     * Invokes the \c DELE command on an open POP3 mail drop, and marks the
     * message as deleted. The message is not actually removed until a
     * normal \c QUIT action is performed. However, the message is no longer
     * available for use. A successful reply is normally \c +OK.
     */
    RWTIOUResult<RWPop3Reply>
    dele(int message);
    // Deletes a message on the server.  The message
    // number must not be referred to again.

    /**
     * Invokes the \c NOOP command on an open POP3 mail account. A
     * successful reply is normally \c +OK.
     */
    RWTIOUResult<RWPop3Reply>
    noop(void);

    /**
     * Invokes the \c TOP command on an open POP3 mail account. It requests
     * that a data connection be opened to the message indexed by
     * \a message, and it requests that \a lines number of message lines be
     * returned. If the total number of lines in the message is fewer than
     * \a lines, only the actual number of lines in the message are
     * available.
     *
     * The method returns an RWTIOUResult with a redeemable RWPop3DataReply.
     * An RWPop3DataReply object contains a socket portal that is used to
     * complete the data portion of the protocol transfer. Reading from this
     * portal returns the message data. POP3 mail messages are terminated by
     * the data sequence \c \<period\>\<cr\>\<lf\> contained on a line by
     * itself. When this sequence is received, the message is complete. A
     * successful reply is normally \c +OK.
     */
    RWTIOUResult<RWPop3DataReply>
    top(int message, int lines);

    /**
     * Invokes the \c UIDL command on an open POP3 mail account. When
     * \a message is zero (the default), it requests that unique message IDs
     * be returned for all messages. When \a message is an index, it
     * requests that a unique message ID be returned for a particular
     * message.
     *
     * The default mode returns data on the socket portal. The server
     * provides the socket portal with one scan listing per message in the
     * mail box. Each scan listing contains the message ID and a trailing
     * \c \<cr\>\<lf\> to mark the end of the individual scan listing line.
     * The last line available from the socket portal consists of
     * \c \<period\>\<cr\>\<lf\>.
     *
     * When requesting a unique message ID for an individual message, data
     * is returned directly and not provided to the portal. A single POP3
     * scan listing is returned. The message ID, formatted as for the
     * multiple list command, is available by calling
     * \ref RWPop3DataReply::getText() "getText()" on the redeemable
     * returned by the command. No data is available at the socket portal.
     *
     * If you attempt to read from the portal when no data is available, the
     * reading thread blocks indefinitely.
     */
    RWTIOUResult<RWPop3DataReply>
    uidl(int message = 0);

    /**
     * Invokes the \c RSET command on an open POP3 mail account, which
     * unmarks all messages marked as deleted. A successful reply is
     * normally \c +OK.
     */
    RWTIOUResult<RWPop3Reply>
    rset(void);

    /**
     * Invokes the \c QUIT command on an open POP3 mail account, which shuts
     * down the connection to the POP3 server. A successful reply is
     * normally \c +OK.
     */
    RWTIOUResult<RWPop3Reply>
    quit(void);

    /**
     * Sets the network timeout value (in milliseconds).
     */
    void
    setTimeout(unsigned long timeout);
    // The timeout will be set after all pending requests have been
    // satisfied. All requests submitted after a call to setTimeout
    // will use the timeout specified.

    /**
     * Retrieves the current network timeout value (in milliseconds).
     */
    unsigned long
    getTimeout(void) const;

private:

    // Implementation Handle
    RWTNetHandle<RWPop3ClientImp> impl_;

};

/*
 * parameters:
 *   buffer - contains a null terminated string
 *
 * returns:
 *   If buffer == ".", then false is returned.
 */
/**
 * \relates RWPop3Client
 *
 * Recognizes an end-of-data condition, which is \c \<period\>\<cr\>\<lf\>,
 * on an POP3 input stream. It can be passed as the \c filter argument to
 * RWStreamCoupler::operator()() which takes a customized filter where it
 * assists in coupling a POP3 message to an output stream. The RWCString
 * should contain 7-bit US-ASCII data.
 */
RW_POP3_SYMBOLIC bool
pop3StreamFilter(const RWCString& buffer);

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWPop3Client instead") RWPop3Client RWIPop3Client;
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_pop3_RWPop3Client_h__
