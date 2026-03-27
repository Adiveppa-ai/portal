#ifndef __rw_http_RWHttpIfEntityTagRangeHeader_h__
#define __rw_http_RWHttpIfEntityTagRangeHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpIfEntityTagRangeHeader.h#1 $
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

#include <rw/http/RWHttpEntityTag.h>
#include <rw/http/RWHttpEntityTagHeaderBase.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class that defines the HTTP If-Range header with entity tag.
 *
 * RWHttpIfEntityTagRangeHeader is a specialization class of
 * RWHttpEntityTagHeaderBase. It is a helper class that formats its contents
 * as \c If-Range: followed by an entity tag.
 */
class RW_HTTP_GLOBAL RWHttpIfEntityTagRangeHeader
    : public RWHttpEntityTagHeaderBase
{
public:

    /**
     * Constructs a default RWHttpIfEntityTagRangeHeader object with the
     * header label set to \c If-Range and the entity tag set to a default
     * RWHttpEntityTag object.
     */
    RWHttpIfEntityTagRangeHeader(void);

    /**
     * Constructs an RWHttpIfEntityTagRangeHeader with the header label set
     * to \c If-Range and entity tag set to \a etag.
     */
    RWHttpIfEntityTagRangeHeader(const RWHttpEntityTag& etag);

    /**
     * Constructs an RWHttpIfEntityTagRangeHeader from the
     * RWHttpGenericHeader \a hdr. If the RWHttpGenericHeader is not a
     * validly formatted HTTP \c If-Range header, an RWHttpHeaderParseError
     * is thrown.
     */
    RWHttpIfEntityTagRangeHeader(const RWHttpGenericHeader& hdr);
};

inline
RWHttpIfEntityTagRangeHeader::RWHttpIfEntityTagRangeHeader()
    : RWHttpEntityTagHeaderBase("If-Range", RW_HTTP_REQUEST_HEADER)
{
}

inline
RWHttpIfEntityTagRangeHeader::RWHttpIfEntityTagRangeHeader(const RWHttpEntityTag& etag)
    : RWHttpEntityTagHeaderBase("If-Range", etag, RW_HTTP_REQUEST_HEADER)
{
}

#endif // __rw_http_RWHttpIfEntityTagRangeHeader_h__
