#ifndef __rw_http_RWHttpReply_h__
#define __rw_http_RWHttpReply_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpReply.h#1 $
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
#include <rw/http/RWHttpRequest.h>
#include <rw/http/pkgdefs.h>
#include <rw/internet/RWNumReply.h>
#include <rw/network/fwd.h>
#include <rw/network/util.h>
#include <rw/cstring.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Encapsulates HTTP headers and a protocol reply.
 *
 * RWHttpReply encapsulates HTTP headers and a protocol reply. It is a
 * subclass of RWNumReply and includes additional methods for retrieving
 * HTTP header information.
 */
class RW_HTTP_GLOBAL RWHttpReply : public RWNumReply
{

public:

    /**
     * Constructs a default invalid RWHttpReply object.
     */
    RWHttpReply(void);

    /**
     * Constructs an RWHttpReply with \a portal as the data source.
     * \a request is a reference to the RWHttpRequest object that was sent
     * to the server to generate the reply.
     */
    RWHttpReply(const RWPortal& portal, const RWHttpRequest& request);

    /**
     * Copy constructor.
     */
    RWHttpReply(const RWHttpReply& reply);

    /**
     * Sets self to the value of \a reply. The previous contents of self are
     * lost.
     */
    RWHttpReply&
    operator=(const RWHttpReply& reply);

    /**
     * Returns the HTTP version number as an RWCString. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    versionAsString(void) const;

    /**
     * Returns an RWCString representing the status line and header fields
     * for the RWHttpReply instance. The returned string does not contain
     * the message body of the reply. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString
    asString() const;

    /**
     * Returns an RWHttpHeaderList object containing all of the headers
     * associated with this reply.
     */
    RWHttpHeaderList
    getHeaders() const;

    /**
     * Returns a copy of the request that generated this reply.
     */
    RWHttpRequest
    getRequest(void) const;

    /**
     * Returns the HTTP major version number.
     */
    int
    getMajorVersion(void) const;

    /**
     * Returns the HTTP minor version number.
     */
    int
    getMinorVersion(void) const;

    /**
     * Retrieves the internal body associated with this reply object.
     */
    RWCString
    getBody(void) const;

    /**
     * Sets the internal body object of this reply.
     */
    void
    setBody(const RWCString& body);

private:

    virtual void
    readFromPortal(const RWPortal& portal);
    // reads return code and header info from the portal
    // and morphs it into a more readable form

    RWCString
    getLine(const RWPortal& portal);
    // reads a line of data from the portal

    char
    getByte(const RWPortal& portal);
    // reads a single byte of data from the portal

    RWHttpHeaderList  headerList_;
    int               majorVersion_;
    int               minorVersion_;
    RWHttpRequest     request_;
    RWCString         body_;

    /**
     * Outputs an RWHttpReply object to an \c std::ostream using the
     * asString() member function.
     */
    friend RW_HTTP_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWHttpReply& r);
};

inline
RWHttpReply::RWHttpReply(void)
    : majorVersion_(0),
      minorVersion_(0)
{
}

inline
RWHttpReply::RWHttpReply(const RWHttpReply& reply)
    : RWNumReply(reply),
      headerList_(reply.headerList_),
      majorVersion_(reply.majorVersion_),
      minorVersion_(reply.minorVersion_),
      request_(reply.request_),
      body_(reply.body_)
{
}

inline RWCString
RWHttpReply::versionAsString(void) const
{
    // Returns version in the format "HTTP/1.1";
    RWCString msg("HTTP/", 5);
    msg.append(rwNetItoa(majorVersion_));
    msg.append('.', 1);
    msg.append(rwNetItoa(minorVersion_));

    return msg;
}

inline RWHttpHeaderList
RWHttpReply::getHeaders() const
{
    return headerList_;
}

inline RWHttpRequest
RWHttpReply::getRequest(void) const
{
    return request_;
}

inline int
RWHttpReply::getMajorVersion(void) const
{
    return majorVersion_;
}

inline int
RWHttpReply::getMinorVersion(void) const
{
    return minorVersion_;
}

inline RWCString
RWHttpReply::getBody(void) const
{
    return body_;
}

inline void
RWHttpReply::setBody(const RWCString& str)
{
    body_ = str;
}

#endif // __rw_http_RWHttpReply_h__
