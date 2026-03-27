#ifndef __rw_http_RWHttpGenericHeader_h__
#define __rw_http_RWHttpGenericHeader_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpGenericHeader.h#1 $
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
#include <rw/http/pkgdefs.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class that defines a generic HTTP header.
 *
 * RWHttpGenericHeader is a specialization class of RWHttpHeaderBase. It is
 * a helper class that formats its contents as \c header_label:
 * \c header_value.
 */
class RW_HTTP_GLOBAL RWHttpGenericHeader : public RWHttpHeaderBase
{

public:

    /**
     * Constructs a default RWHttpGenericHeader object.
     */
    RWHttpGenericHeader(void);

    /**
     * Constructs an RWHttpGenericHeader object with the label equal to
     * \a label. The RWCString should contain 7-bit US-ASCII data.
     */
    RWHttpGenericHeader(const RWCString& label,
                        RWHttpHeaderType type = RW_HTTP_ENTITY_HEADER);

    /**
     * Constructs an RWHttpGenericHeader object with the label equal to
     * \a label and the value equal to \a value. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWHttpGenericHeader(const RWCString& label,
                        const RWCString& value,
                        RWHttpHeaderType type = RW_HTTP_ENTITY_HEADER);

    /**
     * Constructs an RWHttpGenericHeader object with the same values as
     * \a hdr.
     */
    RWHttpGenericHeader(const RWHttpHeaderBase& hdr);

    /**
     * Assigns \a value to the internal value. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    void
    setValue(const RWCString& value);

    /**
     * Returns a copy of the internal value associated with the label. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    virtual RWCString
    getValue(void) const;

private:

    RWCString   value_;
};

inline
RWHttpGenericHeader::RWHttpGenericHeader(void)
{
}

inline
RWHttpGenericHeader::RWHttpGenericHeader(const RWCString& s,
        RWHttpHeaderType type)
    : RWHttpHeaderBase(s, type)
{
}

inline
RWHttpGenericHeader::RWHttpGenericHeader(const RWCString& s,
        const RWCString& val,
        RWHttpHeaderType type)
    : RWHttpHeaderBase(s, type), value_(val)
{
}

inline
RWHttpGenericHeader::RWHttpGenericHeader(const RWHttpHeaderBase& hdr)
    : RWHttpHeaderBase(hdr.getLabel(), hdr.getType()), value_(hdr.getValue())
{
}

inline void
RWHttpGenericHeader::setValue(const RWCString& val)
{
    value_ = val;
}

inline RWCString
RWHttpGenericHeader::getValue(void) const
{
    return value_;
}

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWHttpGenericHeader instead") RWHttpGenericHeader RWIHttpGenericHeader;
#endif

#endif // __rw_http_RWHttpGenericHeader_h__
