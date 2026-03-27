#ifndef __rw_http_RWHttpClient_h__
#define __rw_http_RWHttpClient_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpClient.h#1 $
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

#include <rw/http/RWHttpClientImp.h>
#include <rw/http/RWHttpReply.h>
#include <rw/http/except.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>
#include <rw/functor/RWTFunctor.h>
#include <rw/pointer/RWHandleBase.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  include <rw/network/RWInetAddr.h>
#  include <rw/network/RWInetHost.h>
#  include <rw/network/RWInetPort.h>
#endif

/**
 * \ingroup http_package
 *
 * \brief
 * Provides a low-level interface for communicating with an HTTP server.
 *
 * RWHttpClient enables detailed control over HTTP communications. The
 * asynchronous nature of HTTP/1.1 enables you to submit multiple requests
 * to the server before retrieving any of the replies. Replies are returned
 * in the same order that they are submitted.
 *
 * RWHttpClient objects are lightweight. They are implemented using the
 * handle-body pattern. The RWHttpClient is a handle to an implementation
 * that performs the protocol interaction.
 */
class RW_HTTP_GLOBAL RWHttpClient : public RWHandleBase
{
protected:
    /**
     * Protected constructor from \a imp.
     */
    RWHttpClient(RWHttpClientImp* imp);

public:
    /**
     * Constructs a default RWHttpClient object.
     */
    RWHttpClient(void);

    /**
     * Copy constructor. The body of the new client is the same as
     * \a client.
     */
    RWHttpClient(const RWHttpClient& client);

    /**
     * Assigns the body of \a other to \c this. Any previous bodies
     * associated with this RWHttpClient object are released.
     */
    RWHttpClient&
    operator=(const RWHttpClient& other);

    /**
     * Virtual destructor.
     */
    virtual
    ~RWHttpClient();

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWHttpClient::connect(const RWSockAddrBase&, unsigned long) instead")
    void
    connect(const RWCString& host, int port = 80, unsigned long maxwait = 0);
    // provides a connect method, host is expected to
    // be an IP address or machine domain name
    // maxwait is the maximum amount of time to wait
    // for the connection attempt in milliseconds
#endif

    /**
     * Enables an HTTP client to establish a connection session with an HTTP
     * server. The \a address argument specifies the address of the server
     * to connect to.
     *
     * The optional value \a maxwait specifies how long the RWHttpClient
     * waits for data to become available on a socket before deciding that
     * the socket is dead. \a maxwait defaults to \c 0, which specifies that
     * RWHttpClient waits indefinitely for data. If the \a maxwait time
     * expires, an RWNetOperationTimeoutError exception is thrown.
     *
     * \note
     * A timeout may take longer to complete than the timeout specified if
     * \a address was not prepared (RWSockAddr::prepare()) prior to this
     * call. RWSockAddr::prepare() is called internally and may block
     * indefinitely in \b gethostbyname() when attempting to determine the
     * IP address.
     */
    void
    connect(const RWSockAddrBase& address, unsigned long maxwait = 0);
    // provides a connect method.  address must be
    // a validly constructed derived address type.
    // maxwait is the maximum amount of time to wait
    // for the connection attempt to succeed, in
    // milliseconds.

    /**
     * Returns \c true if it successfully submits a \a request to the
     * server. Otherwise returns \c false. If \a pl is equal to
     * RW_HTTP_ALLOW_PIPELINING, the client assumes that it is safe to
     * pipeline the request. For information about pipelining, see the
     * <em>Internet Protocols Module User's Guide</em>.
     *
     * The optional value \a maxwait is the number of milliseconds that the
     * RWHttpClient waits for data to become available on a socket before
     * deciding that the socket is dead. \a maxwait defaults to \c 0, which
     * specifies that RWHttpClient waits indefinitely for data. If the
     * \a maxwait time expires, an RWNetOperationTimeoutError exception is
     * thrown.
     */
    bool
    submit(RWHttpRequest request,
           RWHttpPipeline pl = RW_HTTP_FORBID_PIPELINING,
           unsigned long maxwait = 0);
    // sends method to server and retrieve possible response
    // maxwait is the maximum amount of time to wait for
    // the transmission channel to accept data in milliseconds

    /**
     * Returns the next response from the server. The response contains the
     * status code and headers, plus the body of the response as an
     * RWCString.
     *
     * The optional value \a maxwait is the number of milliseconds that the
     * RWHttpClient waits for data to become available on a socket before
     * deciding that the socket is dead. \a maxwait defaults to \c 0, which
     * specifies that RWHttpClient waits indefinitely for data. If the
     * \a maxwait time expires, an RWNetOperationTimeoutError exception is
     * thrown.
     */
    RWHttpReply
    getReply(unsigned long maxwait = 0);

    /**
     * Returns the next reply from the server. The reply contains the status
     * code and headers for the reply. A portal containing the body of the
     * message is passed to the user-defined \a handler. If the message is
     * not read fully from the portal by the \a handler, an
     * RWHttpHandlerError exception is thrown.
     *
     * The optional value \a maxwait is the number of milliseconds that the
     * RWHttpClient waits for data to become available on a socket before
     * deciding that the socket is dead. \a maxwait defaults to \c 0, which
     * specifies that RWHttpClient waits indefinitely for data. If the
     * \a maxwait time expires, an RWNetOperationTimeoutError exception is
     * thrown.
     */
    RWHttpReply
    getReply(RWTFunctor<void(RWPortal)> handler, unsigned long maxwait = 0);
    // Returns the next response from the server.  The response will
    // contain the status code and headers of the response.  The body
    // of the message will have been consumed by the passed in
    // handler function, so no body will be associated with the reply.
    // maxwait is the maximum amount of time to wait for the
    // transmission channel to receive data in milliseconds

    /**
     * Equivalent to getReply(RWTFunctor<void(RWPortal)>, unsigned long),
     * however this method also receives a reference to the RWHttpReply
     * instance that is returned when the function completes. This method
     * allows the user to access the headers and status of the message while
     * processing the body.
     */
    RWHttpReply
    getReply(RWTFunctor<void(RWPortal, RWHttpReply&)> handler, unsigned long maxwait = 0);
    // Equivalent to the previous getReply implementation, however
    // the RWHttpReply that is being constructed is also passed
    // into the functor method, so that users can query header
    // values, and modify attributes as appropriate.

    /**
     * Returns \c true if the client was last known to be connected to an
     * HTTP server. Otherwise returns \c false.
     *
     * A return of \c true does not guarantee that the client is currently
     * connected to the server. \c true indicates only the state of the
     * connection after the last read or write attempt. For example, if the
     * server silently closed the connection, this function returns \c true.
     */
    bool
    isConnected() const;

    //void
    //close();
    // Detaches the handle from it's current body (if any).  If this is
    // the last handle to the connection, then the socket connection to
    // the server is closed.

protected:

    /**
     * Returns a reference to the body.
     */
    RWHttpClientImp&
    body() const;
};

inline
RWHttpClient::RWHttpClient()
{
}

inline
RWHttpClient::RWHttpClient(const RWHttpClient& client)
    : RWHandleBase(client)
{
}

inline
RWHttpClient::RWHttpClient(RWHttpClientImp* imp)
    : RWHandleBase(imp)
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
inline RWHttpClient&
RWHttpClient::operator=(const RWHttpClient& client)
{
    RWHandleBase::operator=(client);
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING

inline RWHttpClientImp&
RWHttpClient::body() const
{
    return (RWHttpClientImp&)RWHandleBase::body();
}

inline bool
RWHttpClient::isConnected() const
{
    return (isValid() && body().isConnected());
}

#if !defined(RW_DISABLE_DEPRECATED)
inline void
RWHttpClient::connect(const RWCString& host, int port, unsigned long maxwait)
{
    RWInetPort inetport(port);
    RWInetHost inethost(host);
    RWInetAddr inetaddr(inetport, inethost);
    body().connect(inetaddr, maxwait);
}
#endif

inline void
RWHttpClient::connect(const RWSockAddrBase& address, unsigned long maxwait)
{
    body().connect(address, maxwait);
}

inline bool
RWHttpClient::submit(RWHttpRequest request, RWHttpPipeline pl, unsigned long maxwait)
{
    return body().submit(request, pl, maxwait);
}

inline RWHttpReply
RWHttpClient::getReply(unsigned long maxwait)
{
    return body().getReply(maxwait);
}

inline RWHttpReply
RWHttpClient::getReply(RWTFunctor<void(RWPortal)> handler, unsigned long maxwait)
{
    return body().getReply(handler, maxwait);
}

inline RWHttpReply
RWHttpClient::getReply(RWTFunctor<void(RWPortal, RWHttpReply&)> handler, unsigned long maxwait)
{
    return body().getReply(handler, maxwait);
}

#endif // __rw_http_RWHttpClient_h__
