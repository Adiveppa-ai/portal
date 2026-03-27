#ifndef __rw_http_RWHttpUserAgentHeader_h__
#define __rw_http_RWHttpUserAgentHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpUserAgentHeader.h#1 $
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

#include <rw/http/RWHttpGenericHeader.h>
#include <rw/http/pkgdefs.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Defines an HTTP User-Agent request header.
 *
 * RWHttpUserAgentHeader is a specialization class of RWHttpGenericHeader.
 * It defines the HTTP User-Agent request header. It is a helper class that
 * formats its contents as \c User-Agent: \e header_value, where
 * \e header_value is text that describes the client application.
 */
class RW_HTTP_GLOBAL RWHttpUserAgentHeader : public RWHttpGenericHeader
{

public:

    /**
     * Constructs a default RWHttpUserAgentHeader object with the associated
     * value of the \c User-Agent label set to empty.
     */
    RWHttpUserAgentHeader(void);

    /**
     * Constructs an RWHttpUserAgentHeader object with the associated value
     * of the \c User-Agent label set to \a value. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWHttpUserAgentHeader(const RWCString& value);

    /**
     * Constructs an RWHttpUserAgentHeader object from an
     * RWHttpGenericHeader that represents a \c User-Agent header. If the
     * RWHttpGenericHeader does not represent a \c User-Agent header or if
     * the value of the RWHttpGenericHeader does not conform to the
     * formatting of a \c User-Agent value, an RWHttpHeaderParseError
     * exception is thrown.
     */
    RWHttpUserAgentHeader(const RWHttpGenericHeader& hdr);
};

inline
RWHttpUserAgentHeader::RWHttpUserAgentHeader(void)
    : RWHttpGenericHeader("User-Agent", RW_HTTP_REQUEST_HEADER)
{
}

inline
RWHttpUserAgentHeader::RWHttpUserAgentHeader(const RWCString& s)
    : RWHttpGenericHeader("User-Agent", s, RW_HTTP_REQUEST_HEADER)
{
}

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWHttpUserAgentHeader instead") RWHttpUserAgentHeader RWIHttpUserAgentHeader;
#endif

#endif // __rw_http_RWHttpUserAgentHeader_h__
