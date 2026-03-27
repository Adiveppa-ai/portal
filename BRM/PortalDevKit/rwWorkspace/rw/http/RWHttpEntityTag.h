#ifndef __rw_http_RWHttpEntityTag_h__
#define __rw_http_RWHttpEntityTag_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpEntityTag.h#1 $
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

#include <rw/http/pkgdefs.h>
#include <rw/cstring.h>

/**
 * \ingroup http_package
 * \class RWHttpEntityTag
 *
 * \brief
 * Describes an HTTP entity tag.
 *
 * RWHttpEntityTag maintains the entity tag. It compares two entity tags as
 * defined in the HTTP/1.1 specification. RWHttpEntityTag is used primarily
 * within entity-tag based classes.
 */
class RW_HTTP_SYMBOLIC RWHttpEntityTag
{

public:

    /**
     * Defines the strictness of the comparison used when requesting an
     * entity. A validator is used by the server to determine if the version
     * of an entity stored in a cache should be refreshed.
     *
     * See RFC 2616 for information about cache validators.
     */
    enum validator {

        /**
         * A weak validator.
         */
        weak = 0,

        /**
         * A strong validator.
         */
        strong = 1
    };

    /**
     * Constructs a default RWHttpEntityTag. The stored tag is an empty
     * string with its validator level set to #weak.
     */
    RWHttpEntityTag(void);

    /**
     * Constructs an RWHttpEntityTag with its value set to \a str, and its
     * validator level set to \a val. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWHttpEntityTag(const RWCString& tag, validator val = RWHttpEntityTag::strong);

    /**
     * Returns the entity tag as an RWCString. Weakness is indicated by
     * \c W/. The RWCString should contain 7-bit US-ASCII data.
     */
    RWCString
    asString(void) const;

    /**
     * Returns the strength of the entity tag.
     */
    RWHttpEntityTag::validator
    getStrength() const;

    /**
     * Returns the entity tag. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    RWCString
    getTag() const;


    /**
     * Assigns the internal tag from an RWCString. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    void
    setEntityTag(const RWCString& tag, validator val = RWHttpEntityTag::strong);

    /**
     * Compares \c this and \a etag as defined in RFC2616 [13.3.3]. \a val
     * specifies whether this is a weak or strong comparison.
     */
    bool
    compareTo(const RWHttpEntityTag& etag, validator val = RWHttpEntityTag::strong);

private:

    RWCString tag_;
    validator val_;
};

inline
RWHttpEntityTag::RWHttpEntityTag()
    : val_(RWHttpEntityTag::strong)
{
}

inline
RWHttpEntityTag::RWHttpEntityTag(const RWCString& tag, validator val)
    : tag_(tag.strip(RWCString::both, '\"')), val_(val)
{
}

inline void
RWHttpEntityTag::setEntityTag(const RWCString& tag, validator val)
{
    tag_ = tag;
    val_ = val;
}

inline RWHttpEntityTag::validator
RWHttpEntityTag::getStrength() const
{
    return val_;
}

inline RWCString
RWHttpEntityTag::getTag() const
{
    return tag_;
}

#endif // __rw_http_RWHttpEntityTag_h__
