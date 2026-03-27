#ifndef rw_mime_RWMimePart_h
#define rw_mime_RWMimePart_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimePart.h#1 $
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
#include <rw/pointer/RWHandleBase.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents a MIME part, with methods for manipulating the header list and
 * setting the body of the part.
 *
 * RWMimePart represents a MIME part. Each part has a body, the actual
 * content of the part, and a list of headers that describe the body. The
 * body may contain either a single document or a collection of other MIME
 * parts.
 *
 * RWMimePart provides functions for manipulating the header list and
 * setting the body of the part. The derived class RWMimeMultipart
 * represents parts with multipart bodies and provides functions for working
 * with multipart bodies.
 *
 * The MIME specification requires a top-level MIME message to contain a
 * MIME-Version header. This header is optional for parts within a multipart
 * message. No headers are required for every MIME part, but the MIME
 * specification defines the following default values:
 *
 * - When a part does not contain a Content-Type header, the content type of
 * the part is <tt>text-plain;charset=US-ASCII</tt>.
 * - When a part does not contain a Content-Transfer-Encoding header, the
 * transfer encoding of the part is \c 7bit.
 *
 * The example below is a complete MIME part. The part has the transfer
 * encoding \c 7bit, even though the part does not contain a
 * Content-Transfer-Encoding header. The body of the part is a simple HTML
 * document.
 *
 * \code
 * Content-Type: text/html;charset=iso-8859-1
 *
 * <HTML>
 *   <HEAD>
 *     <TITLE>Sample document</TITLE>
 *   </HEAD>
 *   <BODY>
 *     <H1>Sample Document</H1>
 *     <P>This is a sample document.</P>
 *   </BODY>
 * </HTML>
 * \endcode
 *
 * This code snippet constructs an equivalent MIME part.
 *
 * \code
 * RWMimePart part;
 *
 * part.setBody(
 * "<HTML>\r\n"
 * "  <HEAD>\r\n"
 * "    <TITLE>Sample document</TITLE>\r\n"
 * "  </HEAD>\r\n"
 * "  <BODY>\r\n"
 * "    <H1>Sample Document</H1>\r\n"
 * "    <P>This is a sample document.</P>\r\n"
 * "  </BODY>\r\n"
 * "</HTML>\r\n");
 *
 * RWMimeTextType htmlType("html", "iso-8859-1");
 * RWMimeContentTypeHeader htmlTypeHeader(htmlType);
 *
 * part.insertHeader(htmlTypeHeader);
 * \endcode
 *
 * An instance of this class is a handle to a private, reference-counted
 * implementation.
 *
 * @reference
 * RWMimePart provides an encapsulation of the Multipurpose Internet Mail
 * Extensions (MIME) as described in RFC 2045 - 2049.
 */
class RW_MIME_GLOBAL RWMimePart
    : public RWHandleBase
{
public:

    /**
     * Default constructor. Constructs a MIME part with no headers and an
     * empty body.
     */
    RWMimePart(void);

    /**
     * Content-Type constructor. Constructs a MIME part that contains a
     * Content-Type header with the value \a type. The new part contains an
     * empty part body.
     */
    RWMimePart(const RWMimeContentType& type);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimePart(const RWMimePart& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimePart&
    operator=(const RWMimePart& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimePart(void);

    /**
     * Returns a string representation of self. Throws RWMimeError if the
     * function cannot create a MIME part with valid structure.
     */
    RWCString
    asString(void) const;

    /**
     * Populates self with the contents of \a partString. Throws
     * RWMimeParseError if the function cannot parse \a partString as a MIME
     * part.
     */
    void
    fromString(const RWCString& partString);

    /**
     * Returns self's body as a string. If the underlying implementation is
     * multipart, throws RWMimeError if the function cannot create a valid
     * MIME part body.
     */
    RWCString
    getBody(void) const;

    /**
     * Sets self's body to \a body. Does not validate \a body if the
     * underlying implementation is a single part. If the underlying
     * implementation is multipart, throws RWMimeParseError if the function
     * cannot parse \a body.
     */
    void
    setBody(const RWCString& body);

    /**
     * Returns \c true if the underlying implementation is multipart,
     * \c false otherwise.
     */
    bool
    isMultipart(void) const;

    /**
     * Returns the number of headers this MIME part contains.
     */
    size_t
    getHeaderCount(void) const;

    /**
     * Returns the header at \a position. Throws RWBoundsErr if \a position
     * is greater than or equal to getHeaderCount().
     */
    RWMimeHeader
    getHeader(size_t position) const;

    /**
     * Inserts \a header at the end of self's header list.
     */
    void
    insertHeader(const RWMimeHeader& header);

    /**
     * Inserts \a header at \a position. Throws RWBoundsErr if \a position
     * is greater than getHeaderCount().
     */
    void
    insertHeaderAt(size_t position, const RWMimeHeader& header);

    /**
     * Removes the header at \a position. Throws RWBoundsErr if \a position
     * is greater than or equal to getHeaderCount().
     */
    void
    removeHeaderAt(size_t position);

    /**
     * Returns the position of the first header in the header list with a
     * label matching \a label. Begins searching at \a start. Returns
     * #RW_NPOS if no such header is present or if \a start is greater than
     * or equal to getHeaderCount(). The RWCString should contain 7-bit
     * US-ASCII data.
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
    operator==(const RWMimePart& first, const RWMimePart& second);

    /*
     * @internal
     * Inequality operator.
     * Returns \c true if \a first and \a second are not equal, \c false
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
    operator!=(const RWMimePart& first, const RWMimePart& second);

protected:
    RWMimePart(RWMimePartImp* imp);

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimePartImp&
    body(void) const;

private:
    /*
     * @internal
     * Hiding RWHandleBase::operator<().
     */
    bool
    operator<(const RWHandleBase& second) const;

    /*
     * @internal
     * Returns \c true if this part has a Content-Type header with a
     * media type of "multipart."
     */
    bool
    hasMultipartHeader(void) const;
};

#endif  // rw_mime_RWMimePart_h
