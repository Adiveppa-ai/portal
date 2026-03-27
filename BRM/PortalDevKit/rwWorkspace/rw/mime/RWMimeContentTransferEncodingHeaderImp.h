#ifndef rw_mime_RWMimeContentTransferEncodingHeaderImp_h
#define rw_mime_RWMimeContentTransferEncodingHeaderImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentTransferEncodingHeaderImp.h#1 $
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

#include <rw/mime/RWMimeHeaderImp.h>
#include <rw/mime/pkgdefs.h>

/*
 * @internal
 * RWMimeContentTransferEncodingHeaderImp represents the
 * Content-Transfer-Encoding header of a MIME part.  The
 * Content-Transfer-Encoding header identifies whether the
 * body of the part has been encoded and/or the character set
 * of the body. The MIME specification defines five values
 * for this header.  A value of \c 7bit, \c 8bit, or \c binary
 * indicates that the body has not been encoded and that the data
 * is 7-bit US-ASCII, 8-bit US-ASCII, or binary, respectively. A value of
 * \c base64 or \c quoted-printable indicates that the body
 * has been encoded.  Since both Base 64 and Quoted-Printable
 * encodings result in 7bit encoded messages, these values also
 * indicate that the body contains only 7bit US-ASCII data.
 *
 * @reference
 * RWMimeContentTransferEncodingHeaderImp conforms to the
 * "Content-Transfer-Encoding" header requirements specified
 * in RFC 2045, Section 6 (p. 14).  For more details on encodings,
 * see RFC 2045 or the discussion in the <i>Internet Protocols
 * Module User's Guide</i>.
 */
class RW_MIME_GLOBAL RWMimeContentTransferEncodingHeaderImp
    : public RWMimeHeaderImp
{
public:

    /*
     * Default constructor.
     * Constructs a header with the label \c "Content-Transfer-Encoding" and
     * an empty value.
     *
     * @note A header with an empty value does not meet the requirements
     * for an Internet Message Format header.
     */
    RWMimeContentTransferEncodingHeaderImp(void);

    /*
     * Constructs a header with the label \c "Content-Transfer-Encoding" and
     * the value \a encoding.  Does not validate \a encoding.
     */
    RWMimeContentTransferEncodingHeaderImp(const RWCString& encoding);

    /*
     * Copy constructor. Constructs a new header as a deep copy of \a second.
     */
    RWMimeContentTransferEncodingHeaderImp(const RWMimeContentTransferEncodingHeaderImp& second);

    /*
     * Destructor.
     */
    virtual
    ~RWMimeContentTransferEncodingHeaderImp(void);

    /*
     * Return the value associated with self, formatted for inclusion
     * in a MIME message.  Throws RWMimeError if self cannot be
     * represented as valid MIME.
     */
    virtual RWCString
    getValueAsString(void) const;

    /*
     * Set the value of self to \a value.
     */
    virtual void
    setValueFromString(const RWCString& value);

    /*
     * Returns the encoding value of this header.
     */
    RWCString
    getEncoding(void) const;

    /*
     * Sets the encoding value of this header.  Does not validate
     * \a encoding.
     */
    void
    setEncoding(const RWCString& encoding);

    /*
     * static make function for creating a RWMimeHeader with an
     * RWMimeUnstructuredHeaderImp.
     */
    static
    RWMimeHeader
    make(void);

    /*
     * Returns a deep copy of self on the heap.
     */
    RWMimeHeaderImp*
    copy(void) const;

protected:

    /*
     * Compare values of RWMimeContentTransferEncodingHeader in
     * case-insensitive manner.
     */
    virtual bool
    compareValueTo(const RWMimeHeaderImp& second) const;

private:
    RWCString encoding_;
};


#endif // rw_mime_RWMimeContentTransferEncodingHeaderImp_h
