#ifndef __rw_http_RWHttpEntityTagHeaderBase_h__
#define __rw_http_RWHttpEntityTagHeaderBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpEntityTagHeaderBase.h#1 $
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
#include <rw/http/RWHttpHeaderBase.h>
#include <rw/http/pkgdefs.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class that defines the basic formatting and structure of headers
 * that take an entity tag as an argument.
 *
 * RWHttpEntityTagHeaderBase is a specialization of RWHttpHeaderBase. It is
 * a helper class that defines the basic formatting and structure of headers
 * that take an entity tag as an argument.
 */
class RW_HTTP_GLOBAL RWHttpEntityTagHeaderBase
    : public RWHttpHeaderBase
{
protected:
    /**
     * Constructs a default RWHttpEntityTagHeaderBase object with the label
     * value set to \a label and the internal RWHttpHeaderType set to
     * \a type. The RWCString should contain 7-bit US-ASCII data.
     */
    RWHttpEntityTagHeaderBase(const RWCString& label,
                              RWHttpHeaderType type = RW_HTTP_ENTITY_HEADER);

    /**
     * Constructs an RWHttpEntityTagHeaderBase object with the label set to
     * \a label, the entity tag set to \a etag, and the type set to \a type.
     * The RWCString should contain 7-bit US-ASCII data.
     */
    RWHttpEntityTagHeaderBase(const RWCString& label,
                              const RWHttpEntityTag& etag,
                              RWHttpHeaderType type = RW_HTTP_ENTITY_HEADER);

public:

    /**
     * Sets the internal entity tag value to \a etag.
     */
    void
    setEntityTag(const RWHttpEntityTag& etag);
    // sets the entity tag

    /**
     * Returns the internal entity tag value.
     */
    RWHttpEntityTag
    getEntityTag() const;

    /**
     * Returns the entity tag as a HTTP formatted string. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    virtual RWCString
    getValue() const;

protected:
    RWHttpEntityTag etag_;
};

inline
RWHttpEntityTagHeaderBase::RWHttpEntityTagHeaderBase(const RWCString& s,
        RWHttpHeaderType type)
    : RWHttpHeaderBase(s, type)
{
}

inline
RWHttpEntityTagHeaderBase::RWHttpEntityTagHeaderBase(const RWCString& s,
        const RWHttpEntityTag& etag,
        RWHttpHeaderType type)
    : RWHttpHeaderBase(s, type),
      etag_(etag)
{
}

inline void
RWHttpEntityTagHeaderBase::setEntityTag(const RWHttpEntityTag& etag)
{
    etag_ = etag;
}

inline RWHttpEntityTag
RWHttpEntityTagHeaderBase::getEntityTag() const
{
    return etag_;
}

inline RWCString
RWHttpEntityTagHeaderBase::getValue() const
{
    return etag_.asString();
}

#endif // __rw_http_RWHttpEntityTagHeaderBase_h__
