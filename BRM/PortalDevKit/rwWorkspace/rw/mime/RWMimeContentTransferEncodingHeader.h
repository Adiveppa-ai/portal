#ifndef rw_mime_RWMimeContentTransferEncodingHeader_h
#define rw_mime_RWMimeContentTransferEncodingHeader_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentTransferEncodingHeader.h#1 $
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
 * Represents the Content-Transfer-Encoding header of a MIME part.
 *
 * RWMimeContentTransferEncodingHeader represents the
 * Content-Transfer-Encoding header of a MIME part. The
 * Content-Transfer-Encoding header identifies whether the body of the part
 * has been encoded and/or the character set of the body. A value of
 * \c 7bit, \c 8bit, or \c binary indicates that the body has not been
 * encoded, and the data is 7-bit US-ASCII, 8-bit US-ASCII, or binary,
 * respectively. A value of \c base64 or \c quoted-printable indicates that
 * the body has been encoded. Since both \c base64 encoding and
 * \c quoted-printable encoding result in 7-bit US-ASCII encoded messages,
 * either of these values also indicates that the body contains 7-bit
 * US-ASCII data.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeContentTransferEncodingHeader conforms to the
 * Content-Transfer-Encoding header requirements specified in RFC 2045,
 * Section 6 (p. 14). For more details on encodings, see RFC 2045 or the
 * discussion in the <em>Internet Protocols Module User's Guide</em>.
 */
class RW_MIME_GLOBAL RWMimeContentTransferEncodingHeader
    : public RWMimeHeader
{
public:

    /**
     * Static constant string containing \c "Content-Transfer-Encoding", the
     * label for a Content-Transfer-Encoding header. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    static const RWCString Label;

    /**
     * Default constructor. Constructs a header with the label
     * \c "Content-Transfer-Encoding" and an empty value.
     *
     * \note
     * A header with an empty value does not meet the requirements for a
     * Content-Transfer-Encoding header.
     */
    RWMimeContentTransferEncodingHeader(void);

    /**
     * Constructs a header with the label \c "Content-Transfer-Encoding" and
     * the value \a encoding. Does not validate \a encoding. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWMimeContentTransferEncodingHeader(const RWCString& encoding);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeContentTransferEncodingHeader(const RWMimeContentTransferEncodingHeader& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if \a second does not have the label
     * \c "Content-Transfer-Encoding".
     */
    RWMimeContentTransferEncodingHeader(const RWMimeHeader& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeContentTransferEncodingHeader&
    operator=(const RWMimeContentTransferEncodingHeader& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeContentTransferEncodingHeader(void);

    /**
     * Returns the encoding value of this header. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getEncoding(void) const;

    /**
     * Sets the encoding value of this header. Does not validate
     * \a encoding. The RWCString should contain 7-bit US-ASCII data.
     */
    void
    setEncoding(const RWCString& encoding);

protected:

    /**
     * Returns \c true if label matches \c "Content-Transfer-Encoding",
     * \c false otherwise. The comparison is case-insensitive. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    virtual bool
    checkLabel(const RWCString& label) const;

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeContentTransferEncodingHeaderImp&
    body(void) const;
};


#endif // rw_mime_RWMimeContentTransferEncodingHeader_h
