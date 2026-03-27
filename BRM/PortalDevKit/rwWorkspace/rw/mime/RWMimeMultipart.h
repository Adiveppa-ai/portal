#ifndef rw_mime_RWMimeMultipart_h
#define rw_mime_RWMimeMultipart_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeMultipart.h#1 $
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
#include <rw/mime/RWMimePart.h>
#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents a MIME part with the media type \c multipart.
 *
 * RWMimeMultipart represents a MIME part with the media type \c multipart.
 * The MIME \c multipart media type indicates that the part may contain
 * other MIME parts. An instance of this class contains a vector of
 * RWMimePart objects. The class inherits general functionality from
 * RWMimePart and provides functions for working with the vector of MIME
 * parts.
 *
 * The MIME specification requires that a multipart part contain a
 * Content-Type header with a \c multipart media type and a \c boundary
 * parameter. For example, the simple multipart MIME part:
 *
 * \code
 * Content-Type: multipart/mixed; boundary="__the_boundary__"
 *
 * --__the_boundary__
 *
 * This is the first part, in plain text.
 * --__the_boundary__
 * Content-Type: text/plain; charset=US-ASCII
 *
 * This is the second part, also in plain text but with a
 * Content-Type header.
 * --__the_boundary__--
 * \endcode
 *
 * contains two plain text MIME parts. The value of the boundary parameter
 * delimits each part. Therefore, an RWMimeMultipart object must contain a
 * multipart Content-Type header to be converted to a string.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeMultipart provides an encapsulation of the Multipurpose Internet
 * Mail Extensions (MIME) as described in RFC 2045 - 2049.
 */
class RW_MIME_GLOBAL RWMimeMultipart
    : public RWMimePart
{
public:

    /**
     * Default constructor. Constructs a MIME part with no headers and no
     * body.
     *
     * \note
     * A default-constructed RWMimeMultipart does not contain a multipart
     * Content-Type header.
     */
    RWMimeMultipart(void);

    /**
     * Content-Type constructor. Constructs an RWMimeMultipart with a
     * Content-Type header that contains the value \a type.
     */
    RWMimeMultipart(const RWMimeMultipartType& type);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeMultipart(const RWMimeMultipart& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if \a second is not a multipart
     * message.
     */
    RWMimeMultipart(const RWMimePart& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeMultipart&
    operator=(const RWMimeMultipart& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeMultipart(void);

    /**
     * Returns self's preamble. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    RWCString
    getPreamble(void) const;

    /**
     * Sets self's preamble to \a preamble. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    void
    setPreamble(const RWCString& preamble);

    /**
     * Returns the number of parts self contains.
     */
    size_t
    getPartCount(void) const;

    /**
     * Retrieve the MIME part located at \a position. Throws RWBoundsErr if
     * \a position is greater than or equal to getPartCount().
     */
    RWMimePart
    getPart(size_t position) const;

    /**
     * Inserts \a part at the end of self's part collection.
     *
     * \note
     * An RWMimeMultipart must not contain itself either directly or
     * indirectly. A part that contains itself cannot be converted to a
     * string.
     */
    void
    insertPart(const RWMimePart& part);

    /**
     * Inserts \a part into self's part collection at \a position. Throws
     * RWBoundsErr if \a position is greater than getPartCount().
     *
     * \note
     * An RWMimeMultipart must not contain itself either directly or
     * indirectly. A part that contains itself cannot be converted to a
     * string.
     */
    void
    insertPartAt(size_t position, const RWMimePart& part);

    /**
     * Removes the part located at \a position from self's part collection.
     * Throws RWBoundsErr if \a position is greater than or equal to
     * getPartCount().
     */
    void
    removePartAt(size_t position);

    /**
     * Returns the position of the first part in self's part collection that
     * contains a header matching \a header. Begins searching at \a start.
     * If no such part is present, returns #RW_NPOS. Compares both the label
     * and value of headers. Uses a case-insensitive string comparison for
     * labels. For values, the comparison is defined by the header type.
     * This function does not search the part collections of any
     * RWMimeMultipart objects contained by self.
     */
    size_t
    findPart(const RWMimeHeader& header, size_t start = 0) const;

protected:

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeMultipartImp&
    body(void) const;
};

#endif  // rw_mime_RWMimeMultipart_h
