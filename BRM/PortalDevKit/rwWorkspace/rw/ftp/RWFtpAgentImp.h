#ifndef __rw_ftp_RWFtpAgentImp_h__
#define __rw_ftp_RWFtpAgentImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/ftp/RWFtpAgentImp.h#1 $
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

#include <rw/ftp/RWFtpClient.h>
#include <rw/ftp/pkgdefs.h>
#include <rw/internet/RWAgentImp.h>
#include <rw/itc/RWTIOUEscrow.h>

#define FTPAI_HOST_KEY              "Host"
#define FTPAI_USER_KEY              "User"
#define FTPAI_PASSWORD_KEY          "Password"
#define FTPAI_FILEPATH_KEY          "FilePath"
#define FTPAI_XFERMODE_KEY          "Mode"
#define FTPAI_DATA_ACTIVE_KEY       "DataActive"
#define FTPAI_FILE_RENAME_FROM_KEY  "RenameFrom"
#define FTPAI_FILE_RENAME_TO_KEY    "RenameTo"
#define FTPAI_VALUE_ACTIVE          "Active"
#define FTPAI_VALUE_PASSIVE         "Passive"
#define FTPAI_VALUE_LAST_XFER_MODE  "LastXferMode"
#define FTPAI_VALUE_ASCII           "A"
#define FTPAI_VALUE_BINARY          "I"

/*
 * RWFtpAgentImp
 *
 * RWFtpAgentImp is an implementation class of its interface counterpart
 * RWFtpAgent. The main functionality of RWFtpAgentImp is to handle
 * all FTP agent commands dispatched from RWFtpAgent.
 *
 */

class RW_FTP_GLOBAL RWFtpAgentImp : public RWAgentImp
{

public:

    RWFtpAgentImp(void);
    // Default Constructor

    virtual ~RWFtpAgentImp(void);
    // Destructor

    void
    init(void);
    // provides the initialization method, informs the simple
    // state machine that basic agent information has been set
    // in the property dictionary.

    void
    put(RWTIOUEscrow<RWSocketPortal> iouEscrow);
    // performs a put transaction, and opens a data connection
    // to the file to be put.
    // NOTE: a call to the dataClose method must follow.

    void
    append(RWTIOUEscrow<RWSocketPortal> iouEscrow);
    // performs an append transaction, and opens a data connection
    // to the file to be appended.
    // NOTE: a call to the dataClose method must follow.


    void
    get(RWTIOUEscrow<RWSocketPortal> iouEscrow);
    // performs a get transaction, and opens a data connection
    // to the requested file.
    // NOTE: a call to the dataClose method must follow.

    void
    dir(RWTIOUEscrow<RWSocketPortal> iouEscrow);
    // performs a dir transaction, and opens a data connection
    // to the requested directory data.
    // NOTE: a call to the dataClose method must follow.

    void
    dataClose(RWTIOUEscrow<bool> iouEscrow);
    // closes the data connection to the server.  This
    // method must be called after a call to get, put, append or
    // dir.  A new get, put, append, dir, or any other transaction
    // can be performed after the dataClose call has been made.

    void
    mkdir(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs a mkdir transaction.

    void
    rmdir(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs a rmdir transaction.

    void
    cd(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs a cd transaction.

    void
    pwd(RWTIOUEscrow<RWFtpPwdReply> iouEscrow);
    // performs a pwd transaction.

    void
    del(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs a delete transaction.

    void
    rename(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs a rename transaction.

    virtual void
    setProperty(const RWCString& p, const RWCString& v);
    // Sets property p with value v

    void
    setTimeout(unsigned long timeout);

    unsigned long
    getTimeout(void) const;

private: // member functions

    void
    connect(void);
    // performs the client connect actions.

    void
    dataTransferMode(void);
    // sets up the data transfer mode on the server.

    int
    port(void);
    // returns the internal port information.

    template<class T>
    void
    validateStateAndConnect(RWTIOUEscrow<T>& iouEscrow);
    // verifys the state machine is in a valid state and connects if necessary

private: // data member

    enum { INIT_ACTION, TRANSFER_ACTION, CLOSE_ACTION };
    // simple internal state machine states.

    RWFtpClient ftpClient_;
    // ftp client class.

    int nextAction_;
    // next action that should be performed.

    bool connected_;
    // flag that contains control connection status;

    RWMutex threadMutex_;
    // exclusive thread access control.
};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWFtpAgentImp instead") RWFtpAgentImp RWIFtpAgentImpl;
#endif

#endif // __rw_ftp_RWFtpAgentImp_h__
