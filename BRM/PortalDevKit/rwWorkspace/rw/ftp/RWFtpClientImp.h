#ifndef __rw_ftp_RWFtpClientImp_h__
#define __rw_ftp_RWFtpClientImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/ftp/RWFtpClientImp.h#1 $
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

#include <rw/ftp/RWFtpDataReply.h>
#include <rw/ftp/RWFtpPwdReply.h>
#include <rw/ftp/RWFtpReply.h>
#include <rw/ftp/pkgdefs.h>
#include <rw/network/RWTNetHandle.h>
#include <rw/thread/RWThreadPool.h>
#include <rw/itc/RWTIOUEscrow.h>
#include <rw/cstring.h>

// forward declaration
class RWFtpFSM;
class RWFtpClient;
class RWFtpClientImp;

/*
 * RWFtpClientImp
 *
 * RWFtpClientImp is an implementation class of its interface counterpart
 * RWFtpClient. The main functionality of RWFtpClientImp is to handle
 * all FTP commands dispatched from RWFtpClient.
 *
 * RWFtpClientImp also provides lock mechanisms for its interface to
 * have synchronization control in a multithreaded environment.
 *
 */

class RW_FTP_SYMBOLIC RWFtpClientImp
{

    friend class RWFtpClient;
    friend class RWTNetHandle<RWFtpClientImp>;

private:

    RWFtpClientImp(void);
    // Default constructor

    ~RWFtpClientImp(void);
    // destructor

    void
    addFunctor(const RWTFunctor<void()>& functor);
    // add a functor to the work queue

    void
    setTimeout(unsigned long timeout);
    // set network timeout in milliseconds

    unsigned long
    getTimeout(void) const;
    // get network timeout in milliseconds

    void
    connect(RWTIOUEscrow<RWFtpReply> iouEscrow,
            RWCString host);
    // performs the connect action

    void
    user(RWTIOUEscrow<RWFtpReply> iouEscrow,
         RWCString user);
    // performs the user action

    void
    pass(RWTIOUEscrow<RWFtpReply> iouEscrow,
         RWCString pass);
    // performs the pass action

    void
    pwd(RWTIOUEscrow<RWFtpPwdReply> iouEscrow);
    // performs the pwd action

    void
    retr(RWTIOUEscrow<RWFtpDataReply> iouEscrow,
         RWCString fspec);
    // opens a read data connection

    void
    appe(RWTIOUEscrow<RWFtpDataReply> iouEscrow,
         RWCString fspec);
    // opens a write data connection

    void
    stor(RWTIOUEscrow<RWFtpDataReply> iouEscrow,
         RWCString fspec);
    // opens a write data connection

    void
    stou(RWTIOUEscrow<RWFtpDataReply> iouEscrow,
         RWCString fspec);
    // opens a write data connection

    void
    list(RWTIOUEscrow<RWFtpDataReply> iouEscrow,
         RWCString fspec);
    // opens a listing data connection

    void
    feat(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // opens a feature data connection

    void
    nlst(RWTIOUEscrow<RWFtpDataReply> iouEscrow,
         RWCString fspec);
    // opens a listing data connection

    void
    dataClose(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // closes the read data connection

    void
    dataAbort(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs an abort data connection command,
    // using in-band data.

    void
    dataUrgentAbort(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs an abort data connection command.
    // using out-of-band data.

    void
    rnfr(RWTIOUEscrow<RWFtpReply> iouEscrow,
         RWCString fspec);
    // performs first half of rename

    void
    rnto(RWTIOUEscrow<RWFtpReply> iouEscrow,
         RWCString fspec);
    // performs second half or rename

    void
    quit(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs the quit action

    void
    noop(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs the noop action

    void
    site(RWTIOUEscrow<RWFtpReply> iouEscrow,
         RWCString specific);
    // performs the site action

    void
    help(RWTIOUEscrow<RWFtpReply> iouEscrow,
         RWCString cmd);
    // performs the help action

    void
    syst(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs the syst action

    void
    rein(RWTIOUEscrow<RWFtpReply> iouEscrow);
    // performs the rein action

    void
    exec(RWTIOUEscrow<RWFtpReply> iouEscrow,
         RWCString cmd);
    // performs a generic protocol action

private:

    RWFtpClientImp(const RWFtpClientImp&);

    RWFtpClientImp&
    operator=(const RWFtpClientImp&);

private:

    RWFtpFSM* sm_;
    RWThreadPool pool_;
    //    RWMutexLock lock_;

};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWFtpClientImp instead") RWFtpClientImp RWIFtpClientImpl;
#endif

#endif // __rw_ftp_RWFtpClientImp_h__
