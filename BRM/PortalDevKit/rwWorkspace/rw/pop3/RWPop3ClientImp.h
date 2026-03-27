#ifndef __rw_pop3_RWPop3ClientImp_h__
#define __rw_pop3_RWPop3ClientImp_h__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/pop3/RWPop3ClientImp.h#1 $
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

#include <rw/pop3/RWPop3ConnReply.h>
#include <rw/pop3/RWPop3DataReply.h>
#include <rw/pop3/RWPop3Reply.h>
#include <rw/pop3/RWPop3StatReply.h>
#include <rw/pop3/pkgdefs.h>
#include <rw/network/RWTNetHandle.h>
#include <rw/thread/RWThreadPool.h>
#include <rw/itc/RWTIOUEscrow.h>
#include <rw/cstring.h>

// forward declaration
class RWPop3FSM;
class RWPop3Client;
class RWPop3ClientImp;

/*
 * RWPop3ClientImp
 *
 * RWPop3ClientImp is an implementation class of its interface counterpart
 * RWPop3Client. The main functionality of RWPop3ClientImp is to handle
 * all POP3 commands dispatched from RWPop3Client.
 *
 * RWPop3ClientImp also provides lock mechanisms for its interface to
 * have synchronization control in a multithreaded environment.
 *
 */

class RW_POP3_SYMBOLIC RWPop3ClientImp
{

    friend class RWPop3Client;
    friend class RWTNetHandle<RWPop3ClientImp>;

private:

    RWPop3ClientImp(void);
    // Default constructor.

    ~RWPop3ClientImp(void);
    // destructor

    void
    setTimeout(unsigned long timeout);
    // sets network timeout in milliseconds

    unsigned long
    getTimeout(void) const;
    // gets network timeout in milliseconds

    void
    addFunctor(const RWTFunctor<void()>& functor);
    // append a functor to be executed by pool_

    void
    connect(RWTIOUEscrow<RWPop3ConnReply> iouEscrow,
            RWCString host);
    // connects to server.

    void
    user(RWTIOUEscrow<RWPop3Reply> iouEscrow,
         RWCString user);
    // sends user

    void
    pass(RWTIOUEscrow<RWPop3Reply> iouEscrow,
         RWCString pass);
    // sends password.

    void
    stat(RWTIOUEscrow<RWPop3StatReply> iouEscrow);
    // sends the stat protocol message.

    void
    list(RWTIOUEscrow<RWPop3DataReply> iouEscrow,
         RWCString message);
    // performs list protocol action

    void
    retr(RWTIOUEscrow<RWPop3DataReply> iouEscrow,
         RWCString message);
    // returns a mail message on the server.

    void
    dele(RWTIOUEscrow<RWPop3Reply> iouEscrow,
         RWCString message);
    // deletes a mail message on the server.

    void
    noop(RWTIOUEscrow<RWPop3Reply> iouEscrow);
    // performs a protocol noop.

    void
    quit(RWTIOUEscrow<RWPop3Reply> iouEscrow);
    // quits the exchange

    void
    top(RWTIOUEscrow<RWPop3DataReply> iouEscrow,
        RWCString message);
    // opens a data connection to the mail message.
    // Returns n number of lines of the text item.

    void
    uidl(RWTIOUEscrow<RWPop3DataReply> iouEscrow,
         RWCString message);
    // sends the uidl command

    void
    rset(RWTIOUEscrow<RWPop3Reply> iouEscrow);
    // sends the rset command

private:

    RWPop3ClientImp(const RWPop3ClientImp&);

    RWPop3ClientImp&
    operator=(const RWPop3ClientImp&);

private:

    RWPop3FSM*   sm_;
    RWThreadPool pool_;
    //    RWMutexLock  lock_; // not necessary with single thread in pool

};

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWPop3ClientImp instead") RWPop3ClientImp RWIPop3ClientImpl;
#endif

#endif // __rw_pop3_RWPop3ClientImp_h__
