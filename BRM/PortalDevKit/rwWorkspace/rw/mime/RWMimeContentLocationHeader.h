#ifndef rw_mime_RWMimeContentLocationHeader_h
#define rw_mime_RWMimeContentLocationHeader_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentLocationHeader.h#1 $
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

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents the Content-Location header of a MIME part.
 *
 * RWMimeContentLocationHeader represents the Content-Location header of a
 * MIME part. The Content-Location header declares a URI for the MIME part
 * containing the header. When a part declares a URI, the part can be
 * referenced from elsewhere in the message by using the URI. This header is
 * specified for use in \c multipart/related messages, which typically
 * contain an HTML document and a set of images referenced in that document.
 *
 * For example, a MIME part containing an image can set the URI for the
 * image with a Content-Location header:
 *
 * \code
 * Content-Location: images/logo.gif
 * \endcode
 *
 * An HTML document in the same message can reference the image using the
 * URI:
 *
 * \code
 * <IMG SRC="images/logo.gif">
 * \endcode
 *
 * By setting a URI for each image within the message, the complete set of
 * files needed to render an HTML document can be included in a message
 * without changing the text of the HTML document.
 *
 * The value of a Content-Location header must meet the format requirements
 * for a URI. The value does not, however, need to indicate an actual
 * resource reachable through the Internet.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeContentLocationHeader conforms to the Content-Location header
 * requirements specified in RFC 2557, Section 4.2 (p. 7). RFC1630 specifies
 * the format for a URI.
 */
class RW_MIME_GLOBAL RWMimeContentLocationHeader
    : public RWMimeHeader
{
public:

    /**
     * Static constant string containing \c "Content-Location", the label
     * for a Content-Location header. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    static const RWCString Label;

    /**
     * Default constructor. Constructs a header with the label
     * \c "Content-Location" and an empty value.
     *
     * \note
     * A header with an empty value does not meet the requirements for a
     * Content-Location header.
     */
    RWMimeContentLocationHeader(void);

    /**
     * Constructs a header with the label \c "Content-Location" and the
     * value \a uri. Does not validate \a uri. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWMimeContentLocationHeader(const RWCString& uri);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeContentLocationHeader(const RWMimeContentLocationHeader& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if second does not have the label
     * \c "Content-Location".
     */
    RWMimeContentLocationHeader(const RWMimeHeader& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeContentLocationHeader&
    operator=(const RWMimeContentLocationHeader& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeContentLocationHeader(void);

    /**
     * Returns the location URI contained within this header. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWCString
    getURI(void) const;

    /**
     * Sets the location URI contained within this header. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    void
    setURI(const RWCString& uri);

protected:

    /**
     * Returns \c true if label matches \c "Content-Location", \c false
     * otherwise. The comparison is case-insensitive. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    virtual bool
    checkLabel(const RWCString& label) const;

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeStructuredHeaderImp&
    body(void) const;
};


#endif //rw_mime_RWMimeContentLocationHeader_h_
