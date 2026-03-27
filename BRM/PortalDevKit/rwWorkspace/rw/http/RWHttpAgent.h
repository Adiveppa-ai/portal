#ifndef __rw_http_RWHttpAgent_h__
#define __rw_http_RWHttpAgent_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpAgent.h#1 $
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

#include <rw/http/RWHttpClientManager.h>
#include <rw/http/RWHttpFromHeader.h>
#include <rw/http/RWHttpHeaderList.h>
#include <rw/http/RWHttpReply.h>
#include <rw/http/RWHttpRequestStringBody.h>
#include <rw/http/RWHttpUserAgentHeader.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>
#include <rw/internet/fwd.h>
#include <rw/itc/fwd.h>
#include <rw/pointer/RWTCountingPointer.h>
#include <rw/cstring.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup http_package
 *
 * \brief
 * Provides a high-level interface for issuing common HTTP requests.
 *
 * RWHttpAgent handles the details of the most common HTTP requests. It
 * calls RWHttpClient to perform these requests. RWHttpAgent uses an
 * RWHttpClientManager to cache connections to HTTP servers, which means
 * that requests from multiple RWHttpAgent instances can use the same
 * underlying network connection to make requests of an HTTP server.
 *
 * The default constructor creates an RWHttpAgent that uses a default,
 * global RWHttpClientManager. For greater control, you can first create an
 * RWHttpClientManager and then create an RWHttpAgent that uses this
 * manager. The constructor for the manager takes parameters for the number
 * of threads and the number of connections the manager can create, and the
 * resulting object has methods for querying and resetting these parameters.
 * See the RWHttpClientManager description for details.
 */
class RW_HTTP_SYMBOLIC RWHttpAgent
{

public :

    /**
     * Constructs an RWHttpAgent that uses the default, global
     * RWHttpClientManager instance.
     */
    RWHttpAgent();

    /**
     * Constructs an RWHttpAgent that uses a supplied RWHttpClientManager
     * instance.
     */
    RWHttpAgent(RWHttpClientManager::PointerType clientManager);

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains the reply from the HTTP server for the requested
     * URL.
     */
    RWTIOUResult<RWHttpReply>
    executeGet(const RWURL& url) const;

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains the reply from the HTTP server for the requested
     * URL. Only the subrange specified by \c start and \c end will be
     * returned.
     */
    RWTIOUResult<RWHttpReply>
    executeGetRange(const RWURL& url, const RWHttpRange& range) const;

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains the reply from the HTTP server for the requested
     * URL. If the \c Last-Modified date for the requested URL is older than
     * the date specified, then only the sub-range requested will be
     * returned, otherwise the entire document associated with the URL will
     * be returned.
     */
    RWTIOUResult<RWHttpReply>
    executeGetRange(const RWURL& url, const RWHttpRange& range, const RWHttpDate& date) const;

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains the reply from the HTTP server for the requested
     * URL. If the Etag for the document matches the \a etag parameter of
     * the request, only the specified subrange will be returned, otherwise
     * the entire document will be returned. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWTIOUResult<RWHttpReply>
    executeGetRange(const RWURL& url, const RWHttpRange& range, const RWCString& etag) const;

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains the document associated with the URL, if it has
     * been modified since \a date. Otherwise it returns a \c 304 (not
     * modified) return code.
     */
    RWTIOUResult<RWHttpReply>
    executeGetIfModifiedSince(const RWURL& url, const RWHttpDate& date) const;

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains the header information associated with the
     * user-defined URL. The body of the document associated with the URL is
     * not returned.
     */
    RWTIOUResult<RWHttpReply>
    executeHead(const RWURL& url) const;

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains information about the success or failure of the
     * delete request and any information from the server concerning the
     * delete request.
     */
    RWTIOUResult<RWHttpReply>
    executeDelete(const RWURL& url) const;

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains information about the success or failure of the
     * \c PUT request and any information from the server concerning the
     * \c PUT request. The body of the \c POST request is extracted from the
     * \a body parameter.
     */
    RWTIOUResult<RWHttpReply>
    executePut(const RWURL& url, const RWHttpRequestBody& body) const;
    // Returns an RWTIOUResult that can be redeemed for an RWHttpReply.
    // The RWHttpReply will contain information on whether the put
    // request succeeded or failed, and any additional information
    // from the server concerning the put request.  The body of the put
    // request will consist of the first length bytes of data from the
    // body ostream.  If the length is specified to 0, then the ostream
    // will be read until EOF.

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains information about the success or failure of the
     * \c POST request and the response from the server to the \c POST
     * request. The body of the \c POST request is extracted from the
     * \a body parameter.
     */
    RWTIOUResult<RWHttpReply>
    executePost(const RWURL& url, const RWHttpRequestBody& body) const;
    // Returns an RWTIOUResult that can be redeemed for an RWHttpReply.
    // The RWHttpReply will contain information on whether the post
    // request succeeded or failed, and the response from the server
    // for the post request.  The body of the post request will consist
    // of the first length bytes of data from the body ostream.
    // If the length is specified to 0, then the ostream will be read
    // until EOF.

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains information about the network path that the
     * request followed to reach the destination URL.
     */
    RWTIOUResult<RWHttpReply>
    executeTrace(const RWURL& url) const;
    // Returns an RWTIOUResult that can be redeemed for an RWHttpReply.
    // The RWHttpReply will contain information concerning the network
    // path that the request followed to reach the destination url.

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 3, use
     * \ref RWHttpAgent::executeServerTrace() "executeServerTrace()"
     * instead.
     *
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains information about the network path that the
     * request followed to reach the destination server. This is equivalent
     * to executing a <tt>TRACE * HTTP/1.1</tt> request to
     * \a server:\a port.
     */
    RW_DEPRECATE_FUNC("Use RWHttpAgent::executeServerTrace(const RWURL&) instead")
    RWTIOUResult<RWHttpReply>
    executeTrace(const RWCString& server, int port = 80) const;
    // Returns an RWTIOUResult that can be redeemed for an RWHttpReply.
    // The RWHttpReply will contain information concerning the network
    // path that the request followed to reach the destination server.
    // This is equivalent to executing a TRACE * HTTP/1.1 request to
    // server:port.  This function has been deprecated since it does
    // not work with non-http servers. Use the executeServerTrace method
    // instead.  You can refuse to support this function by defining
    // the macro RW_DISABLE_DEPRECATED.
#endif

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply will contain information concerning the network path that
     * the request followed to reach the destination server. This is
     * equivalent to executing a <tt>TRACE * HTTP/1.1</tt> request to
     * \a url's \c server:port. This version uses the scheme encoded in the
     * URL to determine the type of connection to make to the server. The
     * path portion of the specified URL is ignored.
     */
    RWTIOUResult<RWHttpReply>
    executeServerTrace(const RWURL& url) const;

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains information about the options associated with
     * the URL.
     */
    RWTIOUResult<RWHttpReply>
    executeOptions(const RWURL& url, const RWHttpRequestBody& body = RWHttpRequestStringBody()) const;

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 3, use
     * \ref RWHttpAgent::executeServerOptions() "executeServerOptions()"
     * instead.
     *
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply contains information about the options associated with
     * the server. This is equivalent to executing an
     * <tt>OPTIONS * HTTP/1.1</tt> request to <tt>\a server:\a port</tt>.
     */
    RW_DEPRECATE_FUNC("Use RWHttpAgent::executeServerOptions(const RWURL&, const RWHttpRequestBody&) instead")
    RWTIOUResult<RWHttpReply>
    executeOptions(const RWCString& server, int port = 80,
                   const RWHttpRequestBody& body = RWHttpRequestStringBody()) const;
    // Returns an RWTIOUResult that can be redeemed for an RWHttpReply.
    // The RWHttpReply will contain information concerning the options
    // associated with the server server.  This is equivalent to executing
    // an OPTIONS * HTTP/1.1 request to server:port.  This function has
    // been deprecated since it does not work with non-http servers.
    // Use the executeServerOptions method instead.  You can refuse to
    // support this function by defining the macro RW_DISABLE_DEPRECATED.
#endif

    /**
     * Returns an RWTIOUResult that can be redeemed for an RWHttpReply. The
     * RWHttpReply will contain information concerning the options
     * associated with the server. This is equivalent to executing an
     * <tt>OPTIONS * HTTP/1.1</tt> request to the \a url's \c server:port.
     * This version uses the scheme encoded in the URL to determine the type
     * of connection to make to the server. The path portion of the
     * specified URL is ignored.
     */
    RWTIOUResult<RWHttpReply>
    executeServerOptions(const RWURL& url, const RWHttpRequestBody& body = RWHttpRequestStringBody()) const;

    /**
     * Assigns the string \a agent to the internal User-Agent value. If
     * User-Agent is set to a non-empty string, an RWHttpUserAgentHeader is
     * attached to all requests issued from the RWHttpAgent object. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    void
    setUserAgent(const RWCString& agent);

    /**
     * Returns the value of the internal User-Agent value. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWCString
    getUserAgent() const;

    /**
     * Determines whether redirect replies (those with reply codes \c 3XX)
     * are automatically followed. If it is set to \c true then redirects
     * are followed automatically, and the resulting document is returned
     * instead of the document requested. If redirects are not followed, the
     * \c 3XX reply from the original request is returned along with any
     * associated message body. The default is to follow the redirects.
     */
    void
    setFollowRedirects(bool b);

    /**
     * Returns \c true if redirects are automatically followed. Otherwise
     * returns \c false.
     */
    bool
    getFollowRedirects() const;

    /**
     * Assigns the string from to the internal \a from value. If \a from is
     * set to a non-empty string, an RWHttpFromHeader is attached to all
     * requests issued from the RWHttpAgent object. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    void
    setFrom(const RWCString& from);

    /**
     * Returns the value of the internal from value. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getFrom() const;

    /**
     * Determines whether a Date header is sent with a request. If \a b is
     * \c true, all subsequent requests from this RWHttpAgent object attach
     * an RWHttpDateHeader with the current date. If \a b is \c false, a
     * date header is not appended. The default is \c false.
     */
    void
    setSendDate(bool b);

    /**
     * Returns \c true if a Date header is appended to outgoing requests.
     * Otherwise returns \c false.
     */
    bool
    getSendDate() const;

    /**
     * Sets the maximum amount of time in milliseconds that the RWHttpAgent
     * waits for data to become available from the server or for data to be
     * sent to the server. If you set \a ms to \c 0, the RWHttpAgent waits
     * indefinitely.
     *
     * If data for a request is not available within the user-defined time
     * \a ms, an RWNetOperationTimeoutError is thrown.
     */
    void
    setNetworkMaxWait(unsigned long ms);

    /**
     * Returns the amount of time in milliseconds that a request blocks on a
     * socket and waits for data before deciding that the socket is dead.
     */
    unsigned long
    getNetworkMaxWait() const;

    /**
     * Adds a custom header to the internal header list of the agent. This
     * header is sent with all outgoing requests from this agent.
     */
    void
    addCustomHeader(const RWHttpHeaderBase& hdr);

    /**
     * Removes a header from the internal header list of the agent. If the
     * header was not present in the RWHttpHeaderList, this function returns
     * \c false.
     */
    bool
    removeCustomHeader(const RWHttpHeaderBase& hdr);

    /**
     * Returns an RWHttpHeaderList containing all of the headers that are
     * sent with requests from this RWHttpAgent.
     */
    const RWHttpHeaderList&
    headers() const;

    /**
     * Returns a reference to the underlying RWHttpClientManager instance
     * associated with this agent.
     */
    RWHttpClientManager&
    getClientManagerInstance() const;
    // Returns a reference to the global ClientManager singleton.

private:
    void
    attachHeaders(const RWURL& url, RWHttpHeaderList& headerList) const;
    // Method used internally to attach all the automatic headers to the request.

    void
    attachInfo(const RWURL& url, RWHttpRequestInfo& info) const;
    // Method used internally to generate request info for use by the
    // HttpClientManager

    RWCString
    getPath(const RWURL& url) const;
    // extracts a HTTP path from the url, taking in to account proxy requests.


private:
    unsigned long                                            maxwait_;
    bool                                                sendDate_;
    bool                                                followRedirects_;
    RWHttpFromHeader                                         from_;
    RWHttpUserAgentHeader                                    userAgent_;
    RWHttpHeaderList                                         headerList_;
    RWTCountingPointer<RWHttpClientManager, RWAtomicCounter>   clientManager_;
};

inline void
RWHttpAgent::setUserAgent(const RWCString& agent)
{
    userAgent_.setValue(agent);
}

inline RWCString
RWHttpAgent::getUserAgent() const
{
    return userAgent_.getValue();
}

inline void
RWHttpAgent::setFollowRedirects(bool b)
{
    followRedirects_ = b;
}

inline bool
RWHttpAgent::getFollowRedirects() const
{
    return followRedirects_;
}

inline void
RWHttpAgent::setFrom(const RWCString& from)
{
    from_.setValue(from);
}

inline RWCString
RWHttpAgent::getFrom() const
{
    return from_.getValue();
}

inline void
RWHttpAgent::setSendDate(bool b)
{
    sendDate_ = b;
}

inline bool
RWHttpAgent::getSendDate() const
{
    return sendDate_;
}

inline void
RWHttpAgent::setNetworkMaxWait(unsigned long seconds)
{
    maxwait_ = seconds;
}

inline unsigned long
RWHttpAgent::getNetworkMaxWait() const
{
    return maxwait_;
}

inline void
RWHttpAgent::addCustomHeader(const RWHttpHeaderBase& hdr)
{
    headerList_.addHeader(hdr);
}

inline bool
RWHttpAgent::removeCustomHeader(const RWHttpHeaderBase& hdr)
{
    return headerList_.removeHeader(hdr.getLabel());
}

inline const RWHttpHeaderList&
RWHttpAgent::headers() const
{
    return headerList_;
}

inline RWHttpClientManager&
RWHttpAgent::getClientManagerInstance() const
{
    return *clientManager_;
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_http_RWHttpAgent_h__
