#ifndef __rw_smtp_RWSmtpClientImp_h__
#define __rw_smtp_RWSmtpClientImp_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/smtp/RWSmtpClientImp.h#1 $
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

#include <rw/smtp/RWSmtpDataReply.h>
#include <rw/smtp/RWSmtpReply.h>
#include <rw/smtp/pkgdefs.h>
#include <rw/network/RWTNetHandle.h>
#include <rw/thread/RWThreadPool.h>
#include <rw/itc/RWTIOUEscrow.h>
#include <rw/cstring.h>


// forward declaration
class RWSmtpFSM;
class RWSmtpClient;
class RWSmtpClientImp;

/*
 * RWSmtpClientImp
 *
 * RWSmtpClientImp is an implementation class of its interface counterpart
 * RWSmtpClient. The main functionality of RWSmtpClientImp is to handle
 * all SMTP commands dispatched from RWSmtpClient.
 *
 * RWSmtpClientImp also provides lock mechanisms for its interface to
 * have synchronization control in a multithreaded environment.
 *
 */

class RW_SMTP_SYMBOLIC RWSmtpClientImp
{

    friend class RWSmtpClient;
    friend class RWTNetHandle<RWSmtpClientImp>;

private:

    RWSmtpClientImp(void);
    // Default constructor.

    ~RWSmtpClientImp(void);
    // destructor

    void
    setTimeout(unsigned long timeout);
    // sets network timeout in milliseconds

    unsigned long
    getTimeout(void) const;
    // gets network timeout in milliseconds

    void
    addFunctor(const RWTFunctor<void()>& functor);
    // adds a functor to execute in thread pool

    void
    connect(RWTIOUEscrow<RWSmtpReply> iouEscrow,
            RWCString address);
    // connects to server.

    void
    helo(RWTIOUEscrow<RWSmtpReply> iouEscrow,
         RWCString host);
    // sends helo protocol message.

    void
    ehlo(RWTIOUEscrow<RWSmtpReply> iouEscrow,
         RWCString host);
    // sends ehlo protocol message.

    void
    auth(RWTIOUEscrow<RWSmtpReply> iouEscrow,
         RWCString /* user */, RWCString /* passwd */);
    // performs authentication (supported: CRAM-MD5)

    void
    mail(RWTIOUEscrow<RWSmtpReply> iouEscrow,
         RWCString from);
    // sends mail protocol message.

    void
    rcpt(RWTIOUEscrow<RWSmtpReply> iouEscrow,
         RWCString to);
    // sends the rcpt protocol message.

    void
    vrfy(RWTIOUEscrow<RWSmtpReply> iouEscrow,
         RWCString who);
    // sends the vrfy protocol message.

    void
    expn(RWTIOUEscrow<RWSmtpReply> iouEscrow,
         RWCString who);
    // sends the expn protocol message.

    void
    rset(RWTIOUEscrow<RWSmtpReply> iouEscrow);
    // sends the rset protocol message.

    void
    dataOpen(RWTIOUEscrow<RWSmtpDataReply> iouEscrow);
    // opens the users data channel to the server

    void
    dataClose(RWTIOUEscrow<RWSmtpReply> iouEscrow);
    // closes the users data channels to the server

    void
    quit(RWTIOUEscrow<RWSmtpReply> iouEscrow);
    // quits the exchange

    void
    noop(RWTIOUEscrow<RWSmtpReply> iouEscrow);
    // sends noop protocol message.

private:

    RWSmtpClientImp(const RWSmtpClientImp&);

    RWSmtpClientImp&
    operator=(const RWSmtpClientImp&);

private:

    RWSmtpFSM*   sm_;
    RWThreadPool pool_;
    //    RWMutexLock  lock_; // lock unnecessary for pool with 1 thread

};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWSmtpClientImp instead") RWSmtpClientImp RWISmtpClientImpl;
#endif

#endif // __rw_smtp_RWSmtpClientImp_h__
