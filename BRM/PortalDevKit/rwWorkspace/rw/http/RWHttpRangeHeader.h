#ifndef __rw_http_RWHttpRangeHeader_h__
#define __rw_http_RWHttpRangeHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpRangeHeader.h#1 $
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
#include <rw/http/RWHttpRange.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>
#include <rw/network/util.h>
#include <rw/tvslist.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class that defines an HTTP Range header.
 *
 * RWHttpRangeHeader is a specialization class of RWHttpHeaderBase that
 * defines the HTTP Range header. It is a helper class that formats its
 * contents as \c Range: \c bytes=start_range \c - \c stop_range.
 */
class RW_HTTP_GLOBAL RWHttpRangeHeader
    : public RWHttpHeaderBase
{
public:

    /**
     * Constructs a default RWHttpRangeHeader object with the header label
     * set to \c Range and its associated range request to the current
     * length of the entity-body in bytes.
     */
    RWHttpRangeHeader();

    /**
     * Constructs an RWHttpRangeHeader object with the header label set to
     * \c Range and its associated range request set by the RWHttpRange
     * object \a range.
     */
    RWHttpRangeHeader(const RWHttpRange& range);

    /**
     * Constructs an RWHttpRangeHeader from a RWHttpGenericHeader. If the
     * RWHttpGenericHeader is not a properly formatted HTTP \c Range
     * \c Header, an RWHttpHeaderParseError exception is thrown.
     */
    RWHttpRangeHeader(const RWHttpGenericHeader& hdr);

    /**
     * Adds a range defined by the RWHttpRange object \a range to the
     * internal range list.
     */
    void
    addRange(const RWHttpRange& range);

    /**
     * Returns an RWCString representing the range request. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    virtual RWCString
    getValue() const;

private:
    RWTValSlist<RWHttpRange> ranges_;
};

inline
RWHttpRangeHeader::RWHttpRangeHeader(void)
    : RWHttpHeaderBase("Range", RW_HTTP_REQUEST_HEADER)
{
}

inline
RWHttpRangeHeader::RWHttpRangeHeader(const RWHttpRange& range)
    : RWHttpHeaderBase("Range", RW_HTTP_REQUEST_HEADER)
{
    ranges_.append(range);
}

inline void
RWHttpRangeHeader::addRange(const RWHttpRange& range)
{
    ranges_.append(range);
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_http_RWHttpRangeHeader_h__
