#ifndef __rw_http_RWHttpClientImp_h__
#define __rw_http_RWHttpClientImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpClientImp.h#1 $
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

#include <rw/http/RWHttpRequest.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>
#include <rw/network/RWSocket.h>
#include <rw/network/fwd.h>
#include <rw/itc/RWTPCValQueue.h>
#include <rw/functor/RWTFunctor.h>
#include <rw/pointer/RWBodyBase.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup http_package
 *
 * \headerfileloc{#include <rw/http/RWHttpClientImp.h>}
 *
 * Specifies that a request is pipelined or that a request waits until the
 * server responds to a previous request. For information about pipelining,
 * see the <em>Internet Protocols Module User's Guide</em>.
 */
enum RWHttpPipeline {
    /**
     * Pipelined requests are forbidden. Only one request may be outstanding
     * at any given time.
     */
    RW_HTTP_FORBID_PIPELINING = 0,

    /**
     * Pipelined requests are allowed. This allows multiple requests to be
     * issued over a persistent connection without waiting for the replies
     * to previous requests.
     */
    RW_HTTP_ALLOW_PIPELINING = 1
};

class RW_HTTP_GLOBAL RWHttpClientImp : public RWBodyBase
{
    friend class RWHttpClient;

protected:

    RWHttpClientImp();
    // Default constructor

public:
    virtual
    ~RWHttpClientImp();

    void
    connect(const RWSockAddrBase& address, unsigned long maxwait);
    // connects to host on port, waits maxwait milliseconds for connect
    // to complete

    void
    disconnect();
    // disconnects from the current host and port.

    bool
    submit(RWHttpRequest request, RWHttpPipeline pl, unsigned long maxwait = 0);
    // sends method to server and retrieve possible response

    RWHttpReply
    getReply(unsigned long maxwait = 0);
    // gets the next available RWHttpReply, throw an exception if the
    // current RWHttpReply has not finished with the portal.

    RWHttpReply
    getReply(RWTFunctor<void(RWPortal)> handler, unsigned long maxwait = 0);
    // gets the next available RWHttpReply and passes the data portal to
    // handler where the data can be stored or manipulated. This will
    // throw an exception if the current RWHttpReply has not finished
    // with the portal.

    RWHttpReply
    getReply(RWTFunctor<void(RWPortal, RWHttpReply&)> handler, unsigned long maxwait = 0);
    // Equivalent to the previous getReply, however the RWHttpReply
    // instance is passed to the user functor as well, so that they
    // can manipulate the RWHttpReply response in their handler.

    bool
    isConnected() const;
    // Returns true if last known state was connected, false otherwise

protected:

    virtual RWPortal
    portal() const = 0;
    // Provides access to an RWPortal specified by the derived class.

    virtual void
    connect_(const RWSockAddrBase& address, unsigned long maxwait) = 0;
    // Executes a derived class specific connect call.

    virtual void
    disconnect_() = 0;
    // Executes a derived class specific disconnect call.

    virtual bool
    isConnected_() const;
    // Executed by isConnected to allow derived classes to provide
    // additional connected/unconnected information.

    void
    stringHandler(RWPortal portal, RWCString& str);
    // Handler function for processing the body of a message and
    // storing it as a string.

    void
    compatHandler(RWPortal portal, RWHttpReply&, RWTFunctor<void(RWPortal)> functor);

protected:

    RWCString      host_;

private:

    static RWHttpPortal
    restrictedPortal(RWHttpReply reply, RWPortal portal);

    bool
    checkSubmit(RWHttpPipeline pl);
    // Checks to see if it is alright to submit a request to the
    // server.  If it isn't, the function will return false, otherwise
    // it will return true, and will set pipeline_ to the appropriate
    // type

    int            port_;
    RWHttpPipeline pipeline_;

    RWTPCValQueue<RWHttpRequest> request_;
};


inline
RWHttpClientImp::RWHttpClientImp()
    : pipeline_(RW_HTTP_ALLOW_PIPELINING)
{
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_http_RWHttpClientImp_h__
