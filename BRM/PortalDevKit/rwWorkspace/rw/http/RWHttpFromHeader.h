#ifndef __rw_http_RWHttpFromHeader_h__
#define __rw_http_RWHttpFromHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpFromHeader.h#1 $
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
 * Helper class that defines an HTTP From header.
 *
 * RWHttpFromHeader is a specialization class of RWHttpGenericHeader that
 * defines the HTTP From header. It is a helper class that formats its
 * contents as \c From: \c header_value, where \c header_value is a valid
 * e-mail address. The validity of \c header_value is not checked.
 */
class RW_HTTP_GLOBAL RWHttpFromHeader : public RWHttpGenericHeader
{

public:

    /**
     * Constructs a default RWHttpFromHeader object with the label equal to
     * \c From and the value equal to the empty string.
     */
    RWHttpFromHeader(void);

    /**
     * Constructs an RWHttpFromHeader object with the label equal to \c From
     * and the value equal to \a value. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWHttpFromHeader(const RWCString& value);

    /**
     * Constructs an RWHttpFromHeader object from an RWHttpGenericHeader
     * that represents a \c From HTTP header. If the RWHttpGenericHeader
     * does not represent a \c From HTTP header or if the value of the
     * RWHttpGenericHeader does not conform to the formatting of a \c From
     * value, an RWHttpHeaderParseError exception is thrown.
     */
    RWHttpFromHeader(const RWHttpGenericHeader& hdr);
};

inline
RWHttpFromHeader::RWHttpFromHeader(void)
    : RWHttpGenericHeader("From", RW_HTTP_REQUEST_HEADER)
{
}

inline
RWHttpFromHeader::RWHttpFromHeader(const RWCString& s)
    : RWHttpGenericHeader("From", s, RW_HTTP_REQUEST_HEADER)
{
}

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWHttpFromHeader instead") RWHttpFromHeader RWIHttpFromHeader;
#endif

#endif // __rw_http_RWHttpFromHeader_h__
