#ifndef __rw_http_RWHttpRange_h__
#define __rw_http_RWHttpRange_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpRange.h#1 $
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
 * \class RWHttpRange
 *
 * \brief
 * Helper class that describes a Byte Range for requesting a portion of a
 * document.
 *
 * RWHttpRange represents an HTTP/1.1 format range for requesting portions
 * of a document.
 */
class RW_HTTP_SYMBOLIC RWHttpRange
{
public:

    /**
     * Defines from which end of the document to start counting bytes.
     */
    enum rangeEnd {

        /**
         * The range starts at the beginning of the document and extends
         * toward the end.
         */
        head,

        /**
         * The range starts at the end of the document and extends toward
         * the beginning.
         */
        tail
    };

    /**
     * Constructs a default RWHttpRange object where the range is the
     * complete document.
     */
    RWHttpRange();

    /**
     * Constructs an RWHttpRange object from an RWCString. The RWCString
     * must be a properly formatted range according to RFC 2616. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    RWHttpRange(const RWCString& range);

    /**
     * Constructs an RWHttpRange object where the range starts at \a offset
     * and continues for \a length bytes. A \a length of \c 0 means that the
     * range continues to the end of the document.
     */
    RWHttpRange(size_t offset, size_t length = 0);

    /**
     * Constructs an RWHttpRange object where the range extends \a length
     * bytes from \a end.
     */
    RWHttpRange(size_t length, rangeEnd end);

    /**
     * Sets the range to \a range. RWCString must be a properly formatted
     * range according to RFC 2616. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    void
    setRange(const RWCString& range);

    /**
     * Sets the range to start at \a offset and to continue for \a length
     * bytes.
     */
    void
    setRange(size_t offset, size_t length);

    /**
     * Sets the range to start at \a end and to extend for \a length bytes.
     */
    void
    setRange(size_t length, rangeEnd end);

    /**
     * Returns the range as an RWCString. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString
    getValue() const;

private:
    RWCString range_;
};

inline
RWHttpRange::RWHttpRange()
    : range_("0-")
{
}

inline
RWHttpRange::RWHttpRange(const RWCString& range)
{
    setRange(range);
}

inline
RWHttpRange::RWHttpRange(size_t offset, size_t length)
{
    setRange(offset, length);
}

inline
RWHttpRange::RWHttpRange(size_t length, rangeEnd end)
{
    setRange(length, end);
}

inline RWCString
RWHttpRange::getValue() const
{
    return range_;
}

#endif // __rw_http_RWHttpRange_h__
