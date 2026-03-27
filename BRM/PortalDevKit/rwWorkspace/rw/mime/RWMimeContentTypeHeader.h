#ifndef rw_mime_RWMimeContentTypeHeader_h
#define rw_mime_RWMimeContentTypeHeader_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentTypeHeader.h#1 $
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

#include <rw/mime/RWMimeContentType.h>
#include <rw/mime/RWMimeHeader.h>
#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents the \c Content-Type header of a MIME part.
 *
 * RWMimeContentTypeHeader represents the Content-Type header of a MIME
 * part. The header specifies the type of data the part contains so that a
 * recipient can process the data correctly. A Content-Type contains two
 * elements, a <em>media type</em> and a <em>subtype</em>. The media type
 * describes the content in broad terms, while the subtype describes the
 * specific content. The two-level hierarchy allows both flexibility and
 * precision.
 *
 * For example, a plain text email message generally has the content type
 * \c text/plain, whereas an HTML document has the content type
 * \c text/html, and an XML document has the content type \c text/xml. In
 * all three cases, the basic format of the document is text, and the
 * document can be considered text for many purposes (such as deciding
 * whether the document can be usefully opened within a text editor). The
 * subtype indicates the specific format of the text message. While an HTML
 * document can be displayed as plain text, rendering the document in a
 * browser or opening the document in an HTML editor may be more
 * appropriate.
 *
 * Some content types require other parameters which contain additional
 * information. For example, the MIME specification requires all
 * \c multipart content type values to contain a \c boundary parameter which
 * specifies the delimiter for message parts. A complete Content-Type header
 * for a \c multipart/mixed message
 *
 * \code
 * Content-Type: multipart/mixed; boundary=unique-string
 * \endcode
 *
 * has the label \c Content-Type and the value
 * <tt>multipart/mixed; boundary=unique-string</tt>. The value itself
 * contains the media type \c multipart, the subtype \c mixed, and a single
 * parameter with the name \c boundary and the value \c unique-string.
 *
 * Since the value of a Content-Type header has a complex structure,
 * RWMimeContentType provides a convenient representation of a Content-Type
 * value. See RWMimeContentType for details.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeContentTypeHeader conforms to the Content-Type header requirements
 * specified in RFC 2045, Section 5 (p. 10). For details on the content
 * types the MIME specification defines, see RFC 2046.
 */
class RW_MIME_GLOBAL RWMimeContentTypeHeader
    : public RWMimeHeader
{
public:

    /**
     * Static constant string containing \c "Content-Type", the label for a
     * Content-Type header. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    static const RWCString Label;

    /**
     * Default constructor. Constructs a header with the label
     * \c "Content-Type" and an empty value.
     *
     * \note
     * A header with an empty value does not meet the requirements for a
     * Content-Type header.
     */
    RWMimeContentTypeHeader(void);

    /**
     * Constructs a header with the label \c "Content-Type" and the value
     * \a contentType.
     */
    RWMimeContentTypeHeader(const RWMimeContentType& contentType);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeContentTypeHeader(const RWMimeContentTypeHeader& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if \a second does not have the label
     * \c "Content-Type".
     */
    RWMimeContentTypeHeader(const RWMimeHeader& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeContentTypeHeader&
    operator=(const RWMimeContentTypeHeader& second);

    /**
     * Destructor
     */
    virtual
    ~RWMimeContentTypeHeader(void);

    /*
     * Returns a copy of the content type value this header contains.
     */
    /**
     * Returns the value of this header as an RWMimeContentType.
     */
    RWMimeContentType
    getContentType(void) const;

    /**
     * Sets the Content-Type this header contains to \a contentType.
     */
    void
    setContentType(const RWMimeContentType& contentType);

protected:

    /**
     * Returns \c true if label matches \c "Content-Type", \c false
     * otherwise. The comparison is case-insensitive. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    virtual bool
    checkLabel(const RWCString& label) const;

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeContentTypeHeaderImp&
    body(void) const;
};


#endif // rw_mime_RWMimeContentTypeHeader_h
