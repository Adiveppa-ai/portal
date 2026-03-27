#ifndef __rw_http_RWHttpIfDateRangeHeader_h__
#define __rw_http_RWHttpIfDateRangeHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpIfDateRangeHeader.h#1 $
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

#include <rw/http/RWHttpDate.h>
#include <rw/http/RWHttpDateHeader.h>
#include <rw/http/pkgdefs.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class that defines an HTTP If-Range header with HTTP-date.
 *
 * RWHttpIfDateRangeHeader is a specialization class of RWHttpDateHeader. It
 * is a helper class that formats its contents as \c If-Range: followed by a
 * valid HTTP date string.
 */
class RW_HTTP_GLOBAL RWHttpIfDateRangeHeader
    : public RWHttpDateHeader
{
public:

    /**
     * Constructs a default RWHttpIfDateRangeHeader object with the header
     * label set to \c If-Range and the HTTP date set to the current date
     * and time.
     */
    RWHttpIfDateRangeHeader(void);

    /**
     * Constructs an RWHttpIfDateRangeHeader with the header label set to
     * \c If-Range and the HTTP date set to \a date.
     */
    RWHttpIfDateRangeHeader(const RWHttpDate& date);

    /**
     * Constructs an RWHttpIfDateRangeHeader from the RWHttpGenericHeader
     * \a hdr. If the RWHttpGenericHeader is not a validly formatted HTTP
     * \c If-Range header, an RWHttpHeaderParseError is thrown.
     */
    RWHttpIfDateRangeHeader(const RWHttpGenericHeader& hdr);
};

inline
RWHttpIfDateRangeHeader::RWHttpIfDateRangeHeader(void)
    : RWHttpDateHeader("If-Range", RW_HTTP_REQUEST_HEADER)
{
}

inline
RWHttpIfDateRangeHeader::RWHttpIfDateRangeHeader(const RWHttpDate& d)
    : RWHttpDateHeader("If-Range", d, RW_HTTP_REQUEST_HEADER)
{
}

#endif // __rw_http_RWHttpIfDateRangeHeader_h__
