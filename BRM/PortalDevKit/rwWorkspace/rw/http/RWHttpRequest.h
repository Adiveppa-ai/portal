#ifndef __rw_http_RWHttpRequest_h__
#define __rw_http_RWHttpRequest_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpRequest.h#1 $
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

#include <rw/http/RWHttpHeaderList.h>
#include <rw/http/RWHttpRequestBody.h>
#include <rw/http/RWHttpRequestStringBody.h>
#include <rw/http/pkgdefs.h>
#include <rw/pointer/RWTCountingPointer.h>

#if !defined(RW_DISABLE_DEPRECATED)
class RWIHttpMethod;
#endif

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup http_package
 *
 * \brief
 * Encapsulates an entire HTTP request including the request line, header
 * list, and request body.
 *
 * Class RWHttpRequest defines the HTTP request methods in the HTTP
 * specifications. For HTTP/1.1, the commands \c GET, \c POST, \c HEAD,
 * \c PUT, \c DELETE, \c TRACE, and \c OPTIONS are supported. Class
 * RWHttpRequest enables you to construct a full request and add header
 * information to a request.
 */
class RW_HTTP_GLOBAL RWHttpRequest
{

public:

    /**
     * Constructs a default RWHttpRequest.
     */
    RWHttpRequest();

    /**
     * Accepts the method, path, headers, and body for the request. Both a
     * method and path are required, but a header list and body are
     * optional. The RWCString should contain 7-bit US-ASCII data.
     *
     * \note
     * Some methods require a body. If one of those methods is invoked
     * without a body, no error is reported by the HTTP package, but an
     * error should be returned from the server.
     */
    RWHttpRequest(const RWCString& method,
                  const RWCString& path,
                  const RWHttpHeaderList& headers = RWHttpHeaderList(),
                  const RWHttpRequestBody& body = RWHttpRequestStringBody());

    /**
     * Copy constructor.
     */
    RWHttpRequest(const RWHttpRequest& request);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWHttpRequest(const RWCString&, const RWCString&, const RWHttpHeaderList&, const RWHttpRequestBody&) instead")
    RWHttpRequest(const RWIHttpMethod& method);
#endif

    ~RWHttpRequest();
    // destructor

    /**
     * Assignment operator.
     */
    RWHttpRequest&
    operator=(const RWHttpRequest& request);

    /**
     * Returns \c true if this is a valid RWHttpRequest object. Otherwise
     * returns \c false. To be valid, the object must have a method verb and
     * URI associated with it, and the body of the object must be valid.
     */
    bool
    isValid() const;

    /**
     * Sets the target path of the RWHttpRequest to \a path. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    void
    setPath(const RWCString& path);

    /**
     * Returns the path associated with the RWHttpRequest. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWCString
    getPath() const;

    /**
     * Returns a string representing the \c Request-Line for this request.
     * It is similar to \c GET \c / \c HTTP/1.1. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    requestLine(void) const;

    /**
     * Sets the internal list of headers to \a headerList.
     */
    void
    setHeaders(const RWHttpHeaderList& headerList);

    /**
     * Returns the list of headers associated with self.
     */
    RWHttpHeaderList
    getHeaders() const;

    /**
     * Sets the internal body of the request to \a body.
     */
    void
    setBody(const RWHttpRequestBody& body);

    /**
     * Returns a reference to the internal body object. This method can be
     * used to retrieve the body associated with the request object.
     */
    RWHttpRequestBody&
    getBody(void) const;

    /**
     * Sets the internal HTTP version that is used in the request. The
     * default version is 1.1.
     */
    void
    setVersion(int majorVersion, int minorVersion);

    /**
     * Returns the major portion of the HTTP version. The default value is
     * \c 1.
     */
    int
    getMajorVersion(void) const;

    /**
     * Returns the minor portion of the HTTP version. The default value is
     * \c 1.
     */
    int
    getMinorVersion(void) const;

    /**
     * Sets the request type, such as \c GET. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    void
    setMethod(const RWCString& method);

    /**
     * Returns the request type, such as \c GET. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getMethod(void) const;

public:
    static const RWCString Options;
    static const RWCString Get;
    static const RWCString Head;
    static const RWCString Post;
    static const RWCString Put;
    static const RWCString Delete;
    static const RWCString Trace;
    static const RWCString Connect;

private:
    RWCString               method_;
    RWCString               path_;
    int                     majorVersion_;
    int                     minorVersion_;
    RWHttpHeaderList        headerList_;
    RWTCountingPointer<RWHttpRequestBody, RWAtomicCounter> body_;
};


inline bool
RWHttpRequest::isValid() const
{
    return (!method_.isNull() &&
            !path_.isNull() &&
            body_.isValid() &&
            body_->isValid());
}

inline void
RWHttpRequest::setPath(const RWCString& path)
{
    path_ = path;
}

inline RWCString
RWHttpRequest::getPath() const
{
    return path_;
}

inline void
RWHttpRequest::setHeaders(const RWHttpHeaderList& headers)
{
    headerList_ = headers;
}

inline RWHttpHeaderList
RWHttpRequest::getHeaders() const
{
    return headerList_;
}

inline void
RWHttpRequest::setBody(const RWHttpRequestBody& body)
{
    if (body_ != &body) {
        body_ = body.clone();
    }
}

inline RWHttpRequestBody&
RWHttpRequest::getBody() const
{
    return *body_;
}

inline void
RWHttpRequest::setVersion(int majorVersion, int minorVersion)
{
    majorVersion_ = majorVersion;
    minorVersion_ = minorVersion;
}

inline int
RWHttpRequest::getMajorVersion(void) const
{
    return majorVersion_;
}

inline int
RWHttpRequest::getMinorVersion(void) const
{
    return minorVersion_;
}

inline void
RWHttpRequest::setMethod(const RWCString& method)
{
    method_ = method;
}

inline RWCString
RWHttpRequest::getMethod(void) const
{
    return method_;
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_http_RWHttpRequest_h__
