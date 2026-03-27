#ifndef __rw_ftp_RWFtpAgent_h__
#define __rw_ftp_RWFtpAgent_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/ftp/RWFtpAgent.h#1 $
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

#include <rw/ftp/RWFtpAgentImp.h>
#include <rw/ftp/pkgdefs.h>
#include <rw/internet/RWAgent.h>
#include <rw/network/RWSocketPortal.h>
#include <rw/itc/RWTIOUResult.h>
#include <rw/cstring.h>

/**
 * \ingroup ftp_package
 * \class RWFtpAgent
 *
 * \brief
 * Provides basic FTP file and directory access, handling more FTP protocol
 * details than RWFtpClient, but without as much flexibility.
 *
 * RWFtpAgent provides basic FTP file and directory access. It handles more
 * of the details of the FTP protocol than the RWFtpClient class, but does
 * not have as much flexibility.
 *
 * RWFtpAgent performs actions in a transaction-based model (in contrast
 * with the connection-based model of the RWFtpClient). The methods interact
 * with the server by connecting, performing the requested action, and
 * disconnecting. Multiple transactions can be performed before an
 * RWFtpAgent object gets destroyed. The destructor cleans up resources.
 *
 * RWFtpAgent objects are lightweight. They are implemented using the
 * interface-implementation idiom. RWFtpAgent itself is a handle to an
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
 * #include <rw/ftp/RWFtpAgent.h>
 * #include <rw/internet/RWDirEntry.h>
 *
 * int
 * main()
 * {
 *     RWWinSockInfo info;
 *
 *     try {
 *         // Create an agent pointing to roguewave's anonymous
 *         // ftp site
 *         RWFtpAgent agent("ftp.roguewave.com",
 *                          "anonymous",
 *                          "me@roguewave.com");
 *
 *         // Force the RWTIOUResult<RWSocketPortal> to redeem
 *         // immediately for our portal and build an input
 *         // stream from it.
 *         RWSocketPortal p = agent.dir();
 *
 *         // Scope the input stream so it won't access the
 *         // portal after we call dataClose
 *         {
 *             RWPortalIStream istrm(p);
 *             RWCString text;
 *             RWDirEntry de;
 *
 *             // Grab each line of text and pass it to the
 *             // RWDirEntry object to parse.
 *             while (!istrm.eof()) {
 *                 text.readLine(istrm);
 *                 de = RWDirEntry(text);
 *
 *                 // If the resulting object is valid and is a
 *                 // directory, output its name and time to
 *                 // the screen.
 *                 if (de.isValid()) {
 *                    if (de.type() == RWDirEntry::DIRECTORY) {
 *                        std::cout << de.name() << de.time()
 *                                               << std::endl;
 *                     }
 *                 }
 *             }
 *         }
 *
 *         // Close up the agent
 *         bool b = agent.dataClose();
 *     }
 *     catch (const RWxmsg& m) {
 *         std::cout << "Error : " << m.why() << std::endl;
 *     }
 *     return 0;
 * }
 * \endcode
 *
 * Program Output:
 *
 * \code
 * bin 01/05/95 12:00:00
 * dev 11/02/94 12:00:00
 * etc 01/23/96 12:00:00
 * incoming 08/02/96 17:26:00
 * pub 06/21/96 21:26:00
 * roguewave 06/10/96 22:21:00
 * user 11/01/94 12:00:00
 * \endcode
 * \endexample
 */
class RW_FTP_SYMBOLIC RWFtpAgent : public RWAgent
{

public:

    /**
     * Enumerates the type of the intended transfer. If the #TransferMode is
     * set to be #tmode_latest, it uses the transfer mode (either
     * #tmode_ascii or #tmode_binary) that was previously set. The
     * RWFtpAgent class sets the transfer mode, if necessary, prior to
     * opening the underlying data channel.
     */
    enum TransferMode {

#if !defined(RW_DISABLE_DEPRECATED)

        /**
         * \deprecated
         * As of SourcePro 1, use \ref RWFtpAgent::tmode_ascii "tmode_ascii"
         * instead.
         */
        RW_DEPRECATE_ENUMERATOR(ASCII, "Use RWFtpAgent::tmode_ascii instead") = 0,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWFtpAgent::tmode_binary "tmode_binary" instead.
         */
        RW_DEPRECATE_ENUMERATOR(BINARY, "Use RWFtpAgent::tmode_binary instead") = 1,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWFtpAgent::tmode_latest "tmode_latest" instead.
         */
        RW_DEPRECATE_ENUMERATOR(LAST_XFER_MODE, "Use RWFtpAgent::tmode_latest instead") = 2,

#endif

        /**
         * ASCII transfer mode.
         */
        tmode_ascii = 0,

        /**
         * Binary transfer mode.
         */
        tmode_binary = 1,

        /**
         * Transfer mode that was previously set (#tmode_ascii or
         * #tmode_binary).
         */
        tmode_latest = 2

    };

    /**
     * Enumerates which peer (client or server) initiates the data channel
     * connection. If #cmode_active is selected, the client becomes active
     * and makes the connection to the listening server. If #cmode_passive
     * is selected, the server initiates a data connection to the passive
     * client.
     */
    enum ConnectMode {

#if !defined(RW_DISABLE_DEPRECATED)

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWFtpAgent::cmode_active "cmode_active" instead.
         */
        RW_DEPRECATE_ENUMERATOR(ACTIVE, "Use RWFtpAgent::cmode_active instead")  = 0,

        /**
         * \deprecated
         * As of SourcePro 1, use
         * \ref RWFtpAgent::cmode_passive "cmode_passive" instead.
         */
        RW_DEPRECATE_ENUMERATOR(PASSIVE, "Use RWFtpAgent::cmode_passive instead") = 1,

#endif

        /**
         * Active client makes connection to the listening server.
         */
        cmode_active  = 0,

        /**
         * Server initiates connection to the passive client.
         */
        cmode_passive = 1

    };

    /**
     * Constructs a default invalid RWFtpAgent object. Redemption of an
     * RWTIOUResult from any call on a default agent throws an exception.
     * Use the assignment operator to initialize a default RWFtpAgent.
     */
    RWFtpAgent(void);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWFtpAgent(const RWSockAddrBase&, const RWCString&, const RWCString&) instead")
    RWFtpAgent(const RWCString& host,
               const RWCString& user,
               const RWCString& password
              );
    // Constructs a valid object ready to use.  Host is domain name of
    // the ftp server of interest.  User is the user name to use when
    // logging in.  Password is the password to use.  For anonymous
    // ftp, use the user name "anonymous" and send a valid email
    // address for the password.
#endif

    /**
     * Constructs an RWFtpAgent that is ready to use in a subsequent,
     * transactional call. The \a address parameter is the FTP server
     * machine to which the agent connects. The \a user and \a password
     * parameters are the username and password that are used during the FTP
     * login negotiation sequence. When connecting to an anonymous FTP
     * server, use "anonymous" for the username and send a valid e-mail
     * address for the password. If the FTP server does not require a
     * password, the provided password will be ignored. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWFtpAgent(const RWSockAddrBase& address,
               const RWCString& user,
               const RWCString& password = RWCString());

    /**
     * Opens a data connection to the FTP server. The \a filepath parameter
     * is a complete path to the file that is to be returned from the
     * server. The \a connMode parameter controls data connection
     * negotiation. Selecting #cmode_active negotiates a client-to-server
     * data connection, and selecting #cmode_passive (the default)
     * negotiates a server-to-client connection. The connection mode is
     * independent of the transfer direction (see the put() and dir()
     * functions). The \a transMode parameter tells the server the type of
     * data transfer to use, either #tmode_ascii or #tmode_binary. If
     * \a transMode is set to #tmode_latest, which is the default, the
     * method uses the transfer mode that was previously set. If this is the
     * initial transaction in a session, #tmode_latest means #tmode_ascii.
     *
     * If successful, this method returns an RWTIOUResult, which is
     * redeemable for an RWSocketPortal. The RWSocketPortal is used to
     * complete the data portion of the protocol transfer. Reading from the
     * portal transfers the data to the client.
     *
     * When all the data has been successfully read, your application must
     * make a call to the dataClose() method. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWTIOUResult<RWSocketPortal>
    get(const RWCString& filepath,
        ConnectMode connMode = RWFtpAgent::cmode_passive,
        TransferMode transMode = RWFtpAgent::tmode_latest
       );

    /**
     * Opens a data connection to the FTP server. The \a filepath parameter
     * is a complete path to the file that is created on the server. The
     * \a connMode parameter controls data connection negotiation. Selecting
     * #cmode_active negotiates a client-to-server data connection, and
     * selecting #cmode_passive (the default) negotiates a server-to-client
     * connection. The connection mode is independent of the transfer
     * direction (see the dir() and get() functions). The \a transMode
     * parameter specifies the type of data transfer: either #tmode_ascii or
     * #tmode_binary. The #tmode_latest setting (the default) uses the
     * transfer mode that was previously set. If this is the initial
     * transaction of a session, #tmode_latest means #tmode_ascii.
     *
     * If successful, this method returns an RWTIOUResult, which is
     * redeemable for an RWSocketPortal. The RWSocketPortal is used to
     * complete the data portion of the protocol transfer. Writing to this
     * portal transfers the data to the server. When a read of length zero
     * is returned, the file transfer is complete.
     *
     * After a successful call to this method, your application must make a
     * call to the dataClose() method. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWTIOUResult<RWSocketPortal>
    put(const RWCString& filepath,
        ConnectMode connMode = RWFtpAgent::cmode_passive,
        TransferMode transMode = RWFtpAgent::tmode_latest
       );

    // A call to the dataClose method must be made after the append method
    // is used.
    /**
     * Opens a data connection to the FTP server. The \a filepath parameter
     * is a complete path to the file that will be appended to on the
     * server. If the file does not exist, most FTP servers will create one.
     * The \a connMode parameter controls data connection negotiation.
     * Selecting #cmode_active negotiates a client-to-server data
     * connection, and selecting #cmode_passive (the default) negotiates a
     * server-to-client connection. The connection mode is independent of
     * the transfer direction (see the dir() and get() functions). The
     * \a transMode parameter specifies the type of data transfer: either
     * #tmode_ascii or #tmode_binary. The #tmode_latest setting (the
     * default) uses the transfer mode that was previously set. If this is
     * the initial transaction of a session, #tmode_latest means
     * #tmode_ascii.
     */
    RWTIOUResult<RWSocketPortal>
    append(const RWCString& filepath,
           ConnectMode connMode = RWFtpAgent::cmode_passive,
           TransferMode transMode = RWFtpAgent::tmode_latest
          );

    /**
     * Opens a data connection to the FTP server. The \a filepath parameter
     * is a complete path to the directory or file that is to be returned
     * from the server. If the path is null (the default), the current
     * directory is presumed. The \a connMode parameter controls data
     * connection negotiation. Selecting #cmode_active negotiates a
     * client-to-server data connection, and selecting #cmode_passive (the
     * default) negotiates a server-to-client connection. The connection
     * mode is independent of the transfer direction (see the put() and
     * get() functions).
     *
     * If successful, this method returns an RWTIOUResult, which is
     * redeemable for an RWSocketPortal. The RWSocketPortal is used to
     * complete the data portion of the protocol transfer. Reading from this
     * portal returns the directory listing data. When a read of zero length
     * is returned, the data transfer is complete.
     *
     * After a successful call to this method, your application must make a
     * call to the dataClose() method. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWTIOUResult<RWSocketPortal>
    dir(const RWCString& filepath = "",
        ConnectMode connMode = RWFtpAgent::cmode_passive
       );

    // Closes the data connection that was opened in the put, append,
    // get, or dir methods. A new put, append, get, or dir transaction
    // may be performed after a call to dataClose. The return value
    // indicates close success or failure.
    /**
     * Returns an RWTIOUResult, which is redeemable for a \c bool. This
     * method closes the data communication channel and negotiates
     * data-channel disconnection with the FTP server. The redeemable
     * \c bool is \c true if the communication channel is successfully
     * closed. After a successful call to this method, another RWFtpAgent
     * transactional method call may be made.
     */
    RWTIOUResult<bool>
    dataClose(void);

    /**
     * Performs a make directory transaction in the current directory. The
     * \a dirName parameter is the name of the directory to be created. If
     * successful, it returns an RWTIOUResult with a \c 2XX reply code. The
     * RWTIOUResult is redeemable for an RWFtpReply. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    mkdir(const RWCString& dirName);

    /**
     * Performs a remove directory transaction of a directory under the
     * current directory with the \a dirName parameter as the name of the
     * directory to be deleted. If successful, it returns an RWTIOUResult
     * with a \c 2XX reply code. The RWTIOUResult is redeemable for an
     * RWFtpReply. The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    rmdir(const RWCString& dirName);

    /**
     * Performs a "change directory" transaction. The \a dirPath parameter
     * is the name of the directory to be changed to. If \a dirPath is
     * <tt>..</tt>, the directory is changed to the parent directory. If
     * successful, it returns an RWTIOUResult with a \c 2XX reply code. The
     * RWTIOUResult is redeemable for an RWFtpReply. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    cd(const RWCString& dirPath);

    /**
     * Performs a current directory transaction. If successful, this method
     * returns an RWTIOUResult, which is redeemable for an RWFtpPwdReply.
     * See the description for RWFtpPwdReply for details about the return
     * value.
     */
    RWTIOUResult<RWFtpPwdReply>
    pwd(void);

    /**
     * Performs a delete file transaction. The \a filePath parameter is the
     * complete path to the file to be deleted. If successful, it returns an
     * RWTIOUResult with a \c 2XX reply code. The RWTIOUResult is redeemable
     * for an RWFtpReply. The RWCString should contain 7-bit US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    del(const RWCString& filePath);

    /**
     * Performs a rename file transaction in the current directory. The
     * \a fileFrom parameter is the name of an existing file, and the
     * \a fileTo parameter is the new name of the file. If successful, it
     * returns an RWTIOUResult with a \c 2XX reply code. The RWTIOUResult is
     * redeemable for an RWFtpReply. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWTIOUResult<RWFtpReply>
    rename(const RWCString& fileFrom, const RWCString& fileTo);

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
    RWFtpAgentImp*
    ftpImpl(void) const;
    // returns the underlying implementation pointer

    RWCString
    transferMode(TransferMode transMode) const;
    // returns transMode as string

    RWCString
    connectMode(ConnectMode connMode) const;
    // returns connMode as string
};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWFtpAgent instead") RWFtpAgent RWIFtpAgent;
#endif

#endif // __rw_ftp_RWFtpAgent_h__
