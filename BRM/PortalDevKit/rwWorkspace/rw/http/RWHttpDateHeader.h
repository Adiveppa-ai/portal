#ifndef __rw_http_RWHttpDateHeader_h__
#define __rw_http_RWHttpDateHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpDateHeader.h#1 $
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
#include <rw/http/RWHttpHeaderBase.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class that defines an HTTP Date header.
 *
 * RWHttpDateHeader is a specialization class of RWHttpHeaderBase that
 * defines the HTTP Date header. It is a helper class that formats its
 * contents as \c Date: \c header_value, where \c header_value is
 * information on date and time.
 */
class RW_HTTP_GLOBAL RWHttpDateHeader : public RWHttpHeaderBase
{

public:

    /**
     * Constructs a default RWHttpDateHeader object with the associated
     * value of the Date label as the current date and time.
     */
    RWHttpDateHeader(void);

    /**
     * Constructs an RWHttpDateHeader object with the label of the header
     * equal to \a label, and its associated value equal to the current date
     * and time. The label is a specific type of the Date header, such as
     * the \c If-Modified-Since header. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWHttpDateHeader(const RWCString& label,
                     RWHttpHeaderType type = RW_HTTP_ENTITY_HEADER);

    /**
     * Constructs an RWHttpDateHeader object with the value equal to \a d.
     */
    RWHttpDateHeader(const RWHttpDate& d);

    /**
     * Constructs an RWHttpDateHeader object with the label of the header
     * equal to \a label, and its associated value equal to \a d. The label
     * is the specific type of the Date header, such as the
     * \c If-Modified-Since header. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWHttpDateHeader(const RWCString& label, const RWHttpDate& d,
                     RWHttpHeaderType type = RW_HTTP_ENTITY_HEADER);

    /**
     * Constructs an RWHttpDateHeader object from an RWHttpGenericHeader
     * that represents a Date HTTP header. If the RWHttpGenericHeader does
     * not represent a Date HTTP header or if the value of the
     * RWHttpGenericHeader does not conform to the formatting of a Date
     * value, an RWHttpHeaderParseError exception is thrown.
     */
    RWHttpDateHeader(const RWHttpGenericHeader& hdr);

    /**
     * Assigns \a d to the internal value.
     */
    void
    setDate(const RWHttpDate& d);

    /**
     * Returns the internal value of the header.
     */
    RWHttpDate
    getDate(void) const;

    /**
     * Returns the internal value that is associated with the label of the
     * header in an RWCString format. The RWCString should contain 7-bit
     * US-ASCII data. Throws RWInternalErr if RWHttpDate::isValid() returns
     * false.
     */
    virtual RWCString
    getValue(void) const;

private:

    RWHttpDate   date_;
};

inline
RWHttpDateHeader::RWHttpDateHeader(void)
    : RWHttpHeaderBase("Date", RW_HTTP_GENERAL_HEADER)
{
}

inline
RWHttpDateHeader::RWHttpDateHeader(const RWCString& s,
                                   RWHttpHeaderType type)
    : RWHttpHeaderBase(s, type)
{
}

inline
RWHttpDateHeader::RWHttpDateHeader(const RWHttpDate& d)
    : RWHttpHeaderBase("Date", RW_HTTP_GENERAL_HEADER), date_(d)
{
}

inline
RWHttpDateHeader::RWHttpDateHeader(const RWCString& s, const RWHttpDate& d,
                                   RWHttpHeaderType type)
    : RWHttpHeaderBase(s, type), date_(d)
{
}

inline void
RWHttpDateHeader::setDate(const RWHttpDate& d)
{
    date_ = d;
}

inline RWHttpDate
RWHttpDateHeader::getDate(void) const
{
    return date_;
}

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWHttpDateHeader instead") RWHttpDateHeader RWIHttpDateHeader;
#endif

#endif // __rw_http_RWHttpDateHeader_h__
