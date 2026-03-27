#ifndef __rw_ftp_RWFtpClient_h__
#define __rw_ftp_RWFtpClient_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/ftp/RWFtpClient.h#1 $
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

#include <rw/ftp/RWFtpClientImp.h>
#include <rw/ftp/pkgdefs.h>
#include <rw/itc/RWTIOUResult.h>
#include <rw/cstring.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup ftp_package
 *
 * \brief
 * Provides low-level access to the FTP client-side protocol.
 *
 * RWFtpClient provides low-level access to the FTP client-side protocol. In
 * most cases, the method names parallel the names of the protocol actions.
 * The RWFtpClient class maintains a finite state machine to enforce correct
 * FTP protocol action ordering. In the case of misordered method
 * invocation, an RWProtocolClientCmdSequenceError exception is thrown. All
 * client methods return redeemable RWTIOUResult instances for a particular
 * type of RWFtpReply. RWFtpReply and its subclasses, RWFtpPwdReply and
 * RWFtpDataReply, contain an encapsulation of the standard FTP protocol
 * reply messages. Specific subclasses of RWFtpReply return additional
 * information specific to those types of protocol replies.
 *
 * RWFtpClient objects are lightweight. They are implemented using the
 * interface-implementation idiom. The RWFtpClient itself is a handle to an
 * implementation that performs the protocol interaction.
 *
 * Methods that construct data transfer connections, such as retr(), appe(),
 * stor(), stou(), list() and nlst(), take a \c port parameter. The \c port
 * parameter controls how the data connection is constructed. Its default is
 * \c 0.
 *
 * <table>
 * <tr>
 * <td><b>Value of \c port</b></td>
 * <td><b>Data Connection</b></td>
 * <td><b>Socket Port</b></td>
 * </tr>
 * <tr>
 * <td>\c -1</td>
 * <td><tt>Client -> Server</tt></td>
 * <td><tt>Local port - Auto selected</tt></td>
 * </tr>
 * <tr>
 * <td><tt>0 (default)</tt></td>
 * <td><tt>Server -> Client</tt></td>
 * <td><tt>Local port - Auto selected</tt></td>
 * </tr>
 * <tr>
 * <td>\c >0</td>
 * <td><tt>Server -> Client</tt></td>
 * <td><tt>Local port - Value of port</tt></td>
 * </tr>
 * </table>
 *
 * If the \c port parameter is \c 0, RWFtpClient selects a local port using
 * an internal algorithm. It then negotiates a server-to-client data
 * connection using the internal \c PORT protocol command, which is one of
 * the FTP protocol commands. If \c port is greater than \c 0, RWFtpClient
 * negotiates a server-to-client data connection to the specified port using
 * the internal \c PORT protocol command. If the value of \c port is \c -1,
 * RWFtpClient negotiates a client-to-server data connection to the address
 * and port provided by the FTP server by using the internal \c PASV
 * protocol command.
 *
 * The direction of data connection is independent of direction of the data
 * transfer. If you have a firewall, you may need to use the
 * client-to-server connection strategy. It is not supported by all FTP
 * servers, though. For most applications, the default value of \c 0 is
 * best.
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
 * #include <rw/ftp/RWFtpClient.h>
 *
 * int
 * main()
 * {
 *     RWWinSockInfo info;
 *
 *     try {
 *         // Construct a client to connect an FTP server
 *         RWFtpClient client;
 *         RWFtpReply reply =
 *                     client.connect("ftp.roguewave.com");
 *         std::cout << reply << std::endl;
 *
 *         // Establish a login session
 *         reply = client.user("anonymous");
 *         std::cout << reply << std::endl;
 *         reply = client.pass("me@roguewave.com");
 *         std::cout << reply << std::endl;
 *
 *         // Go to the pub directory
 *         reply = client.cwd("pub");
 *         std::cout << reply << std::endl;
 *
 *         // Find out which directory we're in
 *         reply = client.pwd();
 *         std::cout << reply << std::endl;
 *
 *         // Shut down the connection
 *         reply = client.quit();
 *         std::cout << reply << std::endl;
 *     }
 *     catch (const RWxmsg& m) {
 *         std::cout << "Error : " << m.why() << std::endl;
 *     }
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_FTP_SYMBOLIC RWFtpClient
{

public:

    /**
     * Constructs a default RWFtpClient.
     */
    RWFtpClient(void);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWFtpClient::connect(const RWSockAddrBase&) instead")
    RWTIOUResult<RWFtpReply>
    connect(const RWCString& host, int port = 21);
    // provides connect method, host is expected to
    // be an IP address or host domain name.
    // A successful reply is normally in the 2XX family
    // signifying that a login sequence should be
    // attempted with the 'USER/PASS' methods.
#endif

    /**
     * Enables an FTP client to establish a control-connection session with
     * an FTP server. The \a address parameter must be an address to the FTP
     * server. A successful reply from the server in response to the
     * connection is normally in the \c 2XX family. Your application should
     * then attempt a login sequence with the user() and pass() methods.
     */
    RWTIOUResult<RWFtpReply>
    connect(const RWSockAddrBase& address);

    /**
     * Performs the \c USER (user name) protocol action. This method is the
     * first half of the <tt>USER/PASS</tt> login sequence. If the action is
     * not followed by the \c PASS protocol command, a command sequence
     * exception is thrown. A successful reply is normally in the \c 3XX
     * family. After a successful reply, your application should call
     * \c PASS. The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    user(const RWCString& user);

    /**
     * Performs the \c PASS (password) protocol action. This is the second
     * half of the <tt>USER/PASS</tt> login sequence. If your application
     * does not call the \c USER protocol action first, a command sequence
     * exception is thrown. A successful reply for the command is normally
     * in the \c 2XX family. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    RWTIOUResult<RWFtpReply>
    pass(const RWCString& pass);

    /**
     * Performs the \c CWD (change working directory) protocol action. This
     * action is valid after the <tt>USER/PASS</tt> login negotiation has
     * completed successfully. A successful reply from the command is
     * normally in the \c 2XX family. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    cwd(const RWCString& dir);

    /**
     * Performs the \c CDUP (change to parent directory) protocol action.
     * This action is valid after the <tt>USER/PASS</tt> login negotiation
     * has completed successfully. A successful reply from the command is
     * normally in the \c 2XX family.
     */
    RWTIOUResult<RWFtpReply>
    cdup(void);

    /**
     * Performs the \c PWD (present working directory) protocol action. This
     * action is valid after the <tt>USER/PASS</tt> login negotiation has
     * completed successfully. A successful reply is normally in the \c 2XX
     * family.
     */
    RWTIOUResult<RWFtpPwdReply>
    pwd(void);

    /**
     * Performs the \c RETR (return file) protocol action. The \a fspec
     * parameter is the name of the file to be retrieved.
     *
     * This method opens a data connection. This negotiation is based on the
     * value of the \a port parameter. For more information on the \a port
     * parameter, see the Detailed Description section of RWFtpClient. A
     * successful reply of the data-connection negotiation is normally in
     * the \c 1XX family, indicating that a data connection is open for
     * reading.
     *
     * The method returns an RWTIOUResult, which is redeemable for an
     * RWFtpDataReply. The RWFtpDataReply object contains an RWSocketPortal
     * that is used to complete the data portion of the protocol transfer.
     * The data read from this portal is the contents of the specified file.
     * When a read of zero length is returned, the file transfer is
     * complete.
     *
     * After a successful call to the method, your application must call
     * either dataClose(), dataAbort() or dataUrgentAbort(). The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpDataReply>
    retr(const RWCString& fspec, int port = 0);

    /**
     * Performs the \c APPE (append file) protocol action. The \a fspec is
     * the name of the file to be appended to on the server side (if the
     * file does not exist on the server, most FTP servers will create one).
     * First, the method negotiates how to open a data connection. This
     * negotiation is based on the value of the \a port parameter. For more
     * information on the \a port parameter, see the Detailed Description
     * section of RWFtpClient. A successful data-connection negotiation
     * reply is normally in the \c 1XX family, indicating that a data
     * connection is open for writing.
     *
     * The method returns an RWTIOUResult, which is redeemable for an
     * RWFtpDataReply. The RWFtpDataReply object contains an RWSocketPortal
     * that is used to complete the data portion of the protocol transfer.
     * Writing to this portal transfers file data to the server.
     *
     * After a successful call to the method, your application must call
     * either dataClose(), dataAbort() or dataUrgentAbort(). The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpDataReply>
    appe(const RWCString& fspec, int port = 0);

    /**
     * Performs the \c STOR (store file) protocol action. The \a fspec
     * parameter is the name of the file to be created on the server side.
     * First, the method negotiates how to open a data connection. This
     * negotiation is based on the value of the \a port parameter. For more
     * information on the \a port parameter, see the Detailed Description
     * section of RWFtpClient. A successful data-connection negotiation
     * reply is normally in the \c 1XX family, indicating that a data
     * connection is open for writing.
     *
     * The method returns an RWTIOUResult, which is redeemable for an
     * RWFtpDataReply. The RWFtpDataReply object contains an RWSocketPortal
     * that is used to complete the data portion of the protocol transfer.
     * Writing to this portal transfers file data to the server.
     *
     * After a successful call to the method, your application must call
     * either dataClose(), dataAbort() or dataUrgentAbort(). The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpDataReply>
    stor(const RWCString& fspec, int port = 0);

    /**
     * Performs the \c STOU (store unique) protocol action. First, the
     * method negotiates how to open a data connection. This negotiation is
     * based on the value of the \a port parameter. For more information on
     * the \a port parameter, see the Detailed Description section of
     * RWFtpClient. A successful reply is normally in the \c 1XX family,
     * indicating that a data connection is open for writing.
     *
     * This method returns an RWTIOUResult, which is redeemable for an
     * RWFtpDataReply. The RWFtpDataReply object contains an RWSocketPortal
     * that is used to complete the data portion of the protocol transfer.
     * Writing to this portal transfers file data to the server.
     *
     * After a successful call to the method, your application must call
     * either dataClose(), dataAbort() or dataUrgentAbort(). The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpDataReply>
    stou(const RWCString& fileName, int port = 0);

    /**
     * Performs the \c LIST (list directory) protocol action. The \a path
     * parameter is a path name that specifies a directory or a file. A null
     * parameter (the default) specifies the current working or the default
     * directory.
     *
     * This method opens a data connection. The negotiation is based on the
     * value of the \a port parameter. For more information, see the
     * Detailed Description section of RWFtpClient. A successful reply of
     * data-connection negotiation is normally in the \c 1XX family,
     * indicating that a data connection is open for reading.
     *
     * The method returns an RWTIOUResult, which is redeemable for an
     * RWFtpDataReply. The RWFtpDataReply object contains an RWSocketPortal
     * that is used to complete the data portion of the protocol transfer.
     * Reading from this portal returns the directory or file listing data.
     * When a read of zero length is returned, the directory listing
     * transfer is complete.
     *
     * After a successful call to this method, your application must call
     * either dataClose(), dataAbort() or dataUrgentAbort(). The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpDataReply>
    list(const RWCString& path = "", int port = 0);

    /**
     * Performs the \c FEAT (list all new FTP features that the server
     * supports beyond those described in RFC 959) protocol action.
     *
     * This method opens a data connection. The negotiation is based on the
     * value of the \a port parameter. For more information, see the
     * Detailed Description section of RWFtpClient. A successful reply of
     * data-connection negotiation is normally in the \c 1XX family,
     * indicating that a data connection is open for reading.
     *
     * The method returns an RWTIOUResult, which is redeemable for an
     * RWFtpReply. A successful reply is normally in the \c 2XX family, and
     * it contains the extended protocol actions understood by the server.
     */
    RWTIOUResult<RWFtpReply>
    feat(void);


    /**
     * Performs the \c NLST (name list) protocol action. The \a path
     * parameter is the path name that specifies a directory. A null
     * parameter (the default) indicates the current working or default
     * directory.
     *
     * This method opens a data connection. The negotiation is based on the
     * value of the \a port parameter. For more information, see the
     * Detailed Description section of RWFtpClient. A successful reply for
     * data-connection negotiation is normally in the \c 1XX family,
     * indicating that a data connection is open for reading.
     *
     * The method returns an RWTIOUResult, which is redeemable for an
     * RWFtpDataReply. The RWFtpDataReply object contains an RWSocketPortal
     * that is used to complete the data portion of the protocol transfer.
     * The data read from this portal is the directory name list. When a
     * read of zero length is returned, the directory name list transfer is
     * complete.
     *
     * After a successful call to the method, your application must call
     * either dataClose(), dataAbort() or dataUrgentAbort(). The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpDataReply>
    nlst(const RWCString& path = "", int port = 0);

    /**
     * Performs a close of the data-channel socket. This action is valid
     * only after a successful \c RETR, \c APPE, \c STOR, \c STOU, \c LIST
     * or \c NLST protocol action. A successful reply for the command is
     * normally in the \c 2XX family.
     */
    RWTIOUResult<RWFtpReply>
    dataClose(void);

    /**
     * Performs the \c ABOR (abort) protocol action. This action is valid
     * during \c RETR, \c APPE, \c STOR, \c STOU, \c LIST, or \c NLST
     * protocol actions. This action notifies the server that a data
     * transfer abort is requested. This version of the command is sent as
     * normal (in-band) data.
     *
     * This method takes the place of the dataClose() method, so do not call
     * dataClose() after invoking dataAbort().
     *
     * A successful reply in response to the dataAbort() function is
     * normally in the \c 2XX family. However, the FTP server can be in one
     * of two states upon receiving the dataAbort() command. If the FTP
     * server completed data service, it replies with code \c 226 to
     * indicate the command was successful. If the server received the
     * command while data service was in progress, it replies with one of
     * two codes: \c 426 to indicate that the data service request
     * terminated abnormally, or \c 226 to indicate that the abort command
     * was successful.
     */
    RWTIOUResult<RWFtpReply>
    dataAbort(void);

    /**
     * Performs the \c ABOR (abort) protocol action. This action is valid
     * after an \c RETR, \c APPE, \c STOR, \c STOU, \c LIST or \c NLST
     * protocol action. It notifies the server that a data transfer abort is
     * requested. This version of the command is sent as out-of-band data.
     *
     * \note
     * Use of this command is dangerous because some servers abort the
     * entire session if they receive this action after they have finished
     * sending all their data. Try using the in-band version, dataAbort(),
     * first.
     *
     * This method takes the place of the dataClose() method. Your
     * application should not call dataClose() after invoking
     * dataUrgentAbort().
     *
     * A successful reply from the server is normally in the \c 2XX family.
     * However, an FTP server can be in one of two states when it receives
     * the command. If data service was completed, the reply is code \c 226,
     * which indicates that the abort command was successful. If the server
     * received the command while data service was in progress, it replies
     * with one of two codes: \c 426, which indicates that the data service
     * request terminated abnormally, or \c 226, which indicates that the
     * abort command was successful.
     */
    RWTIOUResult<RWFtpReply>
    dataUrgentAbort(void);

    /**
     * Performs a \c TYPE (transfer type) protocol action. The \a t
     * (transfer mode) parameter may be either \c A for ASCII or \c I for
     * BINARY. This action is valid after the <tt>USER/PASS</tt> login
     * negotiation has completed successfully. A successful reply is
     * normally in the \c 2XX family. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    type(const RWCString& t);

    /**
     * Performs a \c QUIT (quit, disconnect) protocol action. This action is
     * valid after the <tt>USER/PASS</tt> login negotiation has completed
     * successfully. A successful reply is normally in the \c 2XX family.
     * After sending a reply, the server disconnects.
     */
    RWTIOUResult<RWFtpReply>
    quit(void);

    /**
     * Performs an \c MKD (make directory) protocol action. This action is
     * valid after the <tt>USER/PASS</tt> login negotiation has completed
     * successfully. A successful reply is normally in the \c 2XX family.
     * The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    mkd(const RWCString& fspec);

    /**
     * Performs an \c RMD (remove directory) protocol action. This action is
     * valid after the <tt>USER/PASS</tt> login negotiation has completed
     * successfully. A successful reply is normally in the \c 2XX family.
     * The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    rmd(const RWCString& fspec);

    /**
     * Performs an \c DELE (delete file) protocol action. This action is
     * valid after the <tt>USER/PASS</tt> login negotiation has completed
     * successfully. A successful reply is normally in the \c 2XX family.
     * The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    dele(const RWCString& fspec);

    /**
     * Performs an \c RNFR (rename from) protocol action. This action is
     * valid after the <tt>USER/PASS</tt> login negotiation has completed
     * successfully. A successful reply is normally in the \c 3XX family.
     * After a successful reply, your application should call \c RNTO. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    rnfr(const RWCString& fspec);

    /**
     * Performs an \c RNTO (rename to) protocol action. This action is valid
     * after the \c RNFR protocol action has completed successfully. A
     * successful reply is normally in the \c 2XX family. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    rnto(const RWCString& fspec);

    /**
     * Performs a \c NOOP (no operation) protocol action. This action is
     * valid in two situations: after the control-connection has been
     * established successfully with an FTP server; and after the
     * <tt>USER/PASS</tt> login negotiation has completed successfully. A
     * successful reply is normally in the \c 2XX family.
     */
    RWTIOUResult<RWFtpReply>
    noop(void);

    /**
     * Performs the \c SITE (site information) protocol action. This action
     * is valid in two situations: after the control-connection has been
     * established successfully with an FTP server; and after the
     * <tt>USER/PASS</tt> login negotiation has completed successfully. A
     * null parameter (the default) returns general site information. The
     * command with a correct, server-understandable \a specificSiteInfo
     * returns specific information on a specific site topic. A successful
     * reply is normally in the \c 2XX family. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    site(const RWCString& specificSiteInfo = "");

    /**
     * Performs the \c SYST (system information) protocol action. This
     * action is valid in two situations: after the control-connection has
     * been established successfully with an FTP server; and after the
     * <tt>USER/PASS</tt> login negotiation has completed successfully. A
     * successful reply is normally in the \c 2XX family.
     */
    RWTIOUResult<RWFtpReply>
    syst(void);

    /**
     * Performs the \c HELP protocol action. This action is valid in two
     * situations: after the control-connection has been established
     * successfully with an FTP server; and after the <tt>USER/PASS</tt>
     * login negotiation has completed successfully. When the function does
     * not have a parameter (the default), the result is general help
     * information for all FTP commands on the FTP server. When the
     * parameter is a particular FTP command, such as
     * \"<tt>help list</tt>,\" the result contains help information for the
     * given FTP command. A successful reply is normally in the \c 2XX
     * family, and it contains the protocol actions understood by the
     * server. The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    help(const RWCString& specificCmd = "");

    /**
     * Performs a \c REIN (re-initialize) protocol action. This action is
     * valid after the <tt>USER/PASS</tt> login negotiation has completed
     * successfully. A successful reply is normally in the \c 2XX family.
     */
    RWTIOUResult<RWFtpReply>
    rein(void);

    /**
     * Performs a generic protocol command with the \a cmdarg parameter in
     * <tt>command \<parameter list\></tt> format. This method can be used
     * to access nonstandard FTP protocol actions on the server. Actions
     * executed with this method are assumed to be atomic in the FTP
     * client's finite state machine. This action is valid after the
     * <tt>USER/PASS</tt> login negotiation has completed successfully. A
     * successful reply is normally in the \c 2XX family. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    exec(const RWCString& cmdarg);

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

private:

    RWTNetHandle<RWFtpClientImp> impl_;
    // Implementation Handle
};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWFtpClient instead") RWFtpClient RWIFtpClient;
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_ftp_RWFtpClient_h__
