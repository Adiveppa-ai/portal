#ifndef __rw_http_RWIHttpClientImpl_h__
#define __rw_http_RWIHttpClientImpl_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWIHttpClientImpl.h#1 $
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


#if !defined(RW_DISABLE_DEPRECATED)

#  include <rw/http/RWIHttpReply.h>
#  include <rw/http/pkgdefs.h>
#  include <rw/network/RWTNetHandle.h>
#  include <rw/thread/RWThreadPool.h>
#  include <rw/itc/RWTIOUEscrow.h>
#  include <rw/cstring.h>


// forward declaration
class RWHttpFSM;
class RWIHttpClient;
class RWIHttpClientImpl;

/*
 * RWIHttpClientImpl
 *
 * RWIHttpClientImpl is an implementation class of its interface counterpart
 * RWIHttpClient. The main functionality of RWIHttpClientImpl is to handle
 * all HTTP commands dispatched from RWIHttpClient.
 *
 * RWIHttpClientImpl also provides lock mechanisms for its interface to
 * have synchronization control in a multithreaded environment.
 *
 */

class
    RW_DEPRECATE_TYPE("Use RWHttpClientImp instead")
    RW_HTTP_SYMBOLIC RWIHttpClientImpl
{

    friend class RWIHttpClient;
    friend class RWTNetHandle<RWIHttpClientImpl>;

private:

    RWIHttpClientImpl(void);
    // Default constructor.

    ~RWIHttpClientImpl(void);
    // destructor

    void
    setTimeout(unsigned long timeout);
    // set the network timeout in milliseconds

    unsigned long
    getTimeout(void) const;
    // get the network timeout in milliseconds

    void
    addFunctor(const RWTFunctor<void()>& functor);
    // add a functor to the pool

    void
    setMajorVersionNumber(int num);
    // sets the HTTP major version number

    void
    connect(RWTIOUEscrow<bool> iouEscrow,
            RWCString host);
    // connects to server.

    void
    execute(RWTIOUEscrow<RWIHttpReply> iouEscrow,
            RWCString method);
    // sends execute protocol message.

private:

    RWIHttpClientImpl(const RWIHttpClientImpl&);

    RWIHttpClientImpl&
    operator=(const RWIHttpClientImpl&);

private:

    RWHttpFSM*   sm_;
    RWThreadPool pool_;
    //    RWMutexLock  lock_;
};

#endif  // RW_DISABLE_DEPRECATED

#endif // __rw_http_RWIHttpClientImpl_h__
