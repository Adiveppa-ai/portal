#ifndef __rw_http_RWHttpHostHeader_h__
#define __rw_http_RWHttpHostHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpHostHeader.h#1 $
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

#include <rw/http/RWHttpHeaderBase.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class that defines an HTTP Host header.
 *
 * RWHttpHostHeader is a specialization class of RWHttpHeaderBase that
 * defines the HTTP Host header. It is a helper class that formats its
 * contents as \c Host: \c uri, where \c uri is the host machine to contact.
 */
class RW_HTTP_GLOBAL RWHttpHostHeader
    : public RWHttpHeaderBase
{
public:

    /**
     * Constructs a default RWHttpHostHeader object with the header label
     * set to \c Host and its associated value set to an empty string.
     */
    RWHttpHostHeader();

    /**
     * Constructs an RWHttpHostHeader object with the header label set to
     * \c Host and its associated host set to \a host, and its associated
     * port set to \a port. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    RWHttpHostHeader(const RWCString& host, int port = 80);

    /**
     * Constructs an RWHttpHostHeader from an RWHttpGenericHeader object. If
     * the constructor is not able to parse a complete RWHttpHostHeader from
     * the RWHttpGenericHeader, an RWHttpHeaderParseError exception is
     * thrown.
     */
    RWHttpHostHeader(const RWHttpGenericHeader& hdr);

    /**
     * Assigns \a host to the internal host value. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    void
    setHost(const RWCString& host);

    /**
     * Assigns \a port to the internal port value.
     */
    void
    setPort(int port);

    /**
     * Returns a copy of the internal host value. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getHost() const;

    /**
     * Returns a copy of the internal port value.
     */
    int
    getPort() const;

    /**
     * Returns \c host:port as an RWCString. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    virtual RWCString
    getValue() const;

private:
    RWCString host_;
    int port_;

};

inline
RWHttpHostHeader::RWHttpHostHeader()
    : RWHttpHeaderBase("Host", RW_HTTP_REQUEST_HEADER), port_(80)
{
}

inline
RWHttpHostHeader::RWHttpHostHeader(const RWCString& host, int port)
    : RWHttpHeaderBase("Host", RW_HTTP_REQUEST_HEADER), host_(host), port_(port)
{
}

inline void
RWHttpHostHeader::setHost(const RWCString& host)
{
    host_ = host;
}

inline void
RWHttpHostHeader::setPort(int port)
{
    port_ = port;
}

inline RWCString
RWHttpHostHeader::getHost() const
{
    return host_;
}

inline int
RWHttpHostHeader::getPort() const
{
    return port_;
}

#endif // __rw_http_RWHttpHostHeader_h__
