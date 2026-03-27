#ifndef __rw_http_RWHttpHeaderList_h__
#define __rw_http_RWHttpHeaderList_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpHeaderList.h#1 $
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
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>
#include <rw/tvordvec.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup http_package
 *
 * \brief
 * Stores and organizes a collection of RWHttpHeaderBase objects.
 *
 * RWHttpHeaderList provides a mechanism for storing and organizing a
 * collection of RWHttpHeaderBase objects.
 */
class RW_HTTP_SYMBOLIC RWHttpHeaderList
{
public:
    /**
     * Constructs an empty RWHttpHeaderList.
     */
    RWHttpHeaderList();

    /**
     * Attempts to add an RWHttpHeaderBase object to the internal list of
     * headers. If successful, it returns \c true. If the header cannot be
     * added for any reason (for example, the header already exists), this
     * function returns \c false.
     */
    bool
    addHeader(const RWHttpHeaderBase& hdr);

    /**
     * Removes any header with a label of \a label from the
     * RWHttpHeaderList. Returns \c true if the header is found and removed.
     * Otherwise returns \c false. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    bool
    removeHeader(const RWCString& label);

    /**
     * Returns an RWCString representing the value of the header associated
     * with \a label. If no headers with that label exist in the
     * RWHttpHeaderList, an empty string is returned. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getValue(const RWCString& label) const;

    /**
     * Returns the index where \a label is found. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    size_t
    index(const RWCString& label) const;

    /**
     * Returns the number of headers currently stored in the
     * RWHttpHeaderList.
     */
    size_t
    entries() const;

    /**
     * Returns a string representing the header list. The string is
     * formatted for sending as part of a request to an HTTP server. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    RWCString
    asString() const;

    /**
     * Returns an RWHttpGenericHeader.
     */
    RWHttpGenericHeader
    operator[](size_t i) const;
    // Returns a generic header representing the header at
    // entry i

private:

    RWTValOrderedVector<RWHttpGenericHeader> list_;
};

inline
RWHttpHeaderList::RWHttpHeaderList(void)
    : list_(0)
{
}

inline bool
RWHttpHeaderList::removeHeader(const RWCString& label)
{
    // We're removing based on the label, so we'll create a fake entry with
    // that field and pass it along
    return list_.remove(RWHttpGenericHeader(label, "", RW_HTTP_ENTITY_HEADER));
}

inline size_t
RWHttpHeaderList::entries() const
{
    return list_.entries();
}

inline RWHttpGenericHeader
RWHttpHeaderList::operator[](size_t i) const
{
    return list_[i];
}

inline size_t
RWHttpHeaderList::index(const RWCString& label) const
{
    return list_.index(RWHttpGenericHeader(label, "", RW_HTTP_ENTITY_HEADER));
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_http_RWHttpHeaderList_h__
