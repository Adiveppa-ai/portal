#ifndef __rw_http_RWHttpContentLengthHeader_h__
#define __rw_http_RWHttpContentLengthHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpContentLengthHeader.h#1 $
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
 * Helper class that defines an HTTP Content-Length entity header.
 *
 * RWHttpContentLengthHeader is a specialization class of RWHttpHeaderBase.
 * It is a helper class that formats its contents as \c Content-Length:
 * \c header_value, where \c header_value is the length in bytes of an HTTP
 * command's body information.
 */
class RW_HTTP_GLOBAL RWHttpContentLengthHeader : public RWHttpHeaderBase
{

public:

    /**
     * Constructs a default RWHttpContentLengthHeader object with the label
     * \c Content-Length and a value of \c 0.
     */
    RWHttpContentLengthHeader(void);

    /**
     * Constructs an RWHttpContentLengthHeader object with the label
     * \c Content-Length and a value of \a value.
     */
    RWHttpContentLengthHeader(int value);

    /**
     * Constructs an RWHttpContentLengthHeader object from an
     * RWHttpGenericHeader that represents a \c Content-Length HTTP header.
     * If the RWHttpGenericHeader does not represent a \c Content-Length
     * HTTP header or if the value of the RWHttpGenericHeader does not
     * conform to the formatting of a \c Content-Length value, an
     * RWHttpHeaderParseError exception is thrown.
     */
    RWHttpContentLengthHeader(const RWHttpGenericHeader& hdr);

    /**
     * Assigns internal value to \a value.
     */
    void
    setValue(int value);

    /**
     * Returns the internal length of the header.
     */
    int
    getLength() const;

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 4, use
     * \ref RWHttpContentLengthHeader::getValue() "getValue()" instead.
     *
     * Returns the internal value as an RWCString. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RW_DEPRECATE_FUNC("Use RWHttpContentLengthHeader::getValue() instead")
    RWCString
    value(void) const;
#endif
    /**
     * Returns the internal value as an RWCString. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getValue(void) const;

private:

    int   value_;
};

inline
RWHttpContentLengthHeader::RWHttpContentLengthHeader(void)
    : RWHttpHeaderBase("Content-Length", RW_HTTP_GENERAL_HEADER),
      value_(0)
{
}

inline
RWHttpContentLengthHeader::RWHttpContentLengthHeader(int n)
    : RWHttpHeaderBase("Content-Length", RW_HTTP_GENERAL_HEADER),
      value_(n)
{
}

inline int
RWHttpContentLengthHeader::getLength() const
{
    return value_;
}

inline void
RWHttpContentLengthHeader::setValue(int n)
{
    value_ = n;
}

#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWHttpContentLengthHeader::value(void) const
{
    return getValue();
}

typedef RW_DEPRECATE_TYPE("Use RWHttpContentLengthHeader instead") RWHttpContentLengthHeader RWIHttpContentLengthHeader;
#endif

#endif // __rw_http_RWHttpContentLengthHeader_h__
