#ifndef __rw_http_RWHttpIfModifiedSinceHeader_h__
#define __rw_http_RWHttpIfModifiedSinceHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpIfModifiedSinceHeader.h#1 $
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

#include <rw/http/RWHttpDateHeader.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class that defines an HTTP If-Modified-Since header.
 *
 * RWHttpIfModifiedSinceHeader is a specialization class of
 * RWHttpDateHeader. It is a helper class that formats its contents as
 * \c If-Modified-Since: \c header_value, where \c header_value is an
 * RWHttpDate object.
 */
class RW_HTTP_GLOBAL RWHttpIfModifiedSinceHeader
    : public RWHttpDateHeader
{
public:

    /**
     * Constructs a default RWHttpIfModifiedSinceHeader object with the
     * header label set to \c If-Modified-Since and its associated value set
     * to the current date and time.
     */
    RWHttpIfModifiedSinceHeader(void);

    /**
     * Constructs an RWHttpIfModifiedSinceHeader object with the header
     * label set to \c If-Modified-Since and its associated value set to
     * \a d.
     */
    RWHttpIfModifiedSinceHeader(const RWHttpDate& d);

    /**
     * Constructs an RWHttpIfModifiedSinceHeader object from an
     * RWHttpGenericHeader that represents an \c If-Modified-Since HTTP
     * header. If the RWHttpGenericHeader does not represent an
     * \c If-Modified-Since HTTP header or if the value of the
     * RWHttpGenericHeader does not conform to the formatting of an
     * \c If-Modified-Since value, an RWHttpHeaderParseError exception is
     * thrown.
     */
    RWHttpIfModifiedSinceHeader(const RWHttpGenericHeader& hdr);
};

inline
RWHttpIfModifiedSinceHeader::RWHttpIfModifiedSinceHeader(void)
    : RWHttpDateHeader("If-Modified-Since", RW_HTTP_REQUEST_HEADER)
{
}

inline
RWHttpIfModifiedSinceHeader::RWHttpIfModifiedSinceHeader(const RWHttpDate& d)
    : RWHttpDateHeader("If-Modified-Since", d, RW_HTTP_REQUEST_HEADER)
{
}

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWHttpIfModifiedSinceHeader instead") RWHttpIfModifiedSinceHeader RWIHttpIfModifiedSinceHeader;
#endif

#endif // __rw_http_RWHttpIfModifiedSinceHeader_h__
