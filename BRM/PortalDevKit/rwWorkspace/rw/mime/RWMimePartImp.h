#ifndef rw_mime_RWMimePartImp_h
#define rw_mime_RWMimePartImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimePartImp.h#1 $
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

#include <rw/mime/RWMimeHeader.h>
#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>
#include <rw/pointer/RWBodyBase.h>
#include <rw/tvslist.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/* @internal
 * This class is a base class for the implementation of an RWMimePart object.
 * There's no need for an application to use derived classes directly;
 * a handle provides appropriate access.
 */
class RW_MIME_GLOBAL RWMimePartImp
    : public RWBodyBase
{
    typedef RWTValSlist<RWMimeHeader>   RWMimeHeaderList;

public:

    /*
     * Default constructor.
     * Constructs a MIME part with no headers and no body.
     */
    RWMimePartImp(void);

    /*
     * Destructor.
     */
    virtual
    ~RWMimePartImp(void);

    /*
     * Returns a string representation of self.
     */
    RWCString
    asString(void) const;

    /*
     * Pure virtual function.  In derived classes, returns self's body as a
     * string. A derived class may validate \a body and throw RWMimeParseError
     * if \a body is invalid.
     */
    virtual RWCString
    getBody(void) const = 0;

    /*
     * Pure virtual function.  In derived classes, sets self's body to \a body.
     * A derived class may validate \a body and throw RWMimeParseError if
     * \a body is invalid.
     */
    virtual void
    setBody(const RWCString& body) = 0;

    /*
     * Returns \c true if self is multipart, \c false otherwise.
     */
    virtual bool
    isMultipart(void) const = 0;

    /*
     * Returns the number of headers this MIME part contains.
     */
    size_t
    getHeaderCount(void) const;

    /*
     * Returns the header at \a position. Throws RWBoundsErr if
     * \a position is greater than or equal to getHeaderCount().
     */
    RWMimeHeader
    getHeader(size_t position) const;

    /*
     * Inserts \a header at the end of self's header list.
     */
    void
    insertHeader(const RWMimeHeader& header);

    /*
     * Inserts \a header at \a position.  Throws RWBoundsErr if
     * \a position is greater than getHeaderCount().
     */
    void
    insertHeaderAt(size_t position, const RWMimeHeader& header);

    /*
     * Removes the header located at \a position.  Throws RWBoundsErr
     * if \a position is greater than or equal to getHeaderCount().
     */
    void
    removeHeaderAt(size_t position);

    /*
     * Returns the position of the first header in the list with
     * a label matching \a label. Begins searching at \a start.
     * Returns #RW_NPOS if no such header is present or if \a start is
     * greater than or equal to getHeaderCount().
     */
    size_t
    findHeader(const RWCString& label, size_t start = 0) const;

    /*
     * @internal
     * Equality operator.
     * Returns \c true if \a first and \a second are equal, \c false
     * otherwise.
     *
     * Compares the headers of the parts to determine if the headers are
     * identical and in the same order. If so, the operator compares the
     * bodies of \a first and \a second to determine if the bodies are equal.
     *
     * For two single parts, bodies are equal if they are identical
     * strings.  For two multipart parts, the operator compares the
     * preambles of the messages and then compares each part contained
     * in \a first to the corresponding part in \a second. If one part
     * is a single part and one part is a multipart, the asString() form
     * of the multipart body is compared to the single part body.
     *
     * Provided for use by standard library containers.
     */
    friend RW_MIME_SYMBOLIC bool
    operator==(const RWMimePartImp& first, const RWMimePartImp& second);

    /*
     * @internal
     * Inequality operator.
     * Returns \c true if first and second are not equal, \c false otherwise.
     *
     * Compares the headers of the parts to determine if the headers are
     * identical and in the same order. If so, the operator compares the
     * bodies of \a  first and \a second to determine if the bodies are equal.
     *
     * For two single parts, bodies are equal if they are identical
     * strings.  For two multipart parts, the operator compares the
     * preambles of the messages and then compares each part contained
     * in \a first to the corresponding part in \a second. If one part
     * is a single part and one part is a multipart, the asString() form
     * of the multipart body is compared to the single part body.
     *
     * Provided for use by standard library containers.
     *
     */
    friend RW_MIME_SYMBOLIC bool
    operator!=(const RWMimePartImp& first, const RWMimePartImp& second);

    /*
     * Compare self to \a part, and return true if self is
     * logically equal to \a part.
     */
    virtual bool
    compareTo(const RWMimePartImp& part) const = 0;

    /*
     * @internal
     * Double-dispatch comparison.  Virtual function for
     * comparing RWMimeStringPartImp part types.
     */
    virtual bool
    compareTo(const RWMimeStringPartImp& part) const = 0;

    /*
     * @internal
     * Double-dispatch comparison.  Virtual function for
     * comparing RWMimeMultipartImp part types.
     */
    virtual bool
    compareTo(const RWMimeMultipartImp& part) const = 0;

protected:
    /*
     * @internal
     * Compare the headers of two RWMimePartImp objects
     * to verify they are equivalent.
     */
    bool
    compareHeaders(const RWMimePartImp& part) const;

private:
    RWMimeHeaderList   headers_;
};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif  // rw_mime_RWMimePartImp_h
