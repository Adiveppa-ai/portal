#ifndef rw_mime_RWMimeGenericHeader_h
#define rw_mime_RWMimeGenericHeader_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeGenericHeader.h#1 $
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

/*
 * Notes:
 *
 * All header field names MUST be composed of printable characters in
 * the US-ASCII character set, excluding colon. (RFC 2822 2.2 p. 7).
 *
 * All header field bodies MUST be composed of characters in the
 * US-ASCII character set, excluding CR (0x13) and LF (0x10).
 */

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents Internet Message Format headers other than the headers defined
 * by MIME.
 *
 * RWMimeGenericHeader represents Internet Message Format headers other than
 * the headers defined by MIME. A header consists of a \e label and a
 * \e value. MIME requires that both the label and value contain only
 * printable characters in the US-ASCII character set. The name may not
 * contain a colon. To create a header with a value in another character
 * set, encode the value according to the guidelines in RFC 2047.
 *
 * The label appears first in the header, and is separated from the value by
 * a colon. So, the header line
 *
 * \code
 * From: Rudi Marquez <rudi_marqez@roguewave.com>
 * \endcode
 *
 * contains the label \c From, a colon as a separator, and the value
 * <tt>Rudi Marquez \<rudi_marquez\@roguewave.com\></tt>.
 * RWMimeGenericHeader represents this structure by containing a pair of
 * strings, one string for the label and one string for the value.
 *
 * This class only represents headers which are not defined in the MIME
 * specification. For MIME headers, use the class corresponding to the
 * header instead. The class enforces this constraint by refusing to accept
 * a label for another header type. The constructors and assignment operator
 * throw RWMimeError if the label provided is a label for any other header
 * type.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeGenericHeader conforms to the header requirements specified in
 * Section 2.2 (p. 7) of RFC 2822, the Internet Message Format
 * specification. RFC 2822 is an update of RFC 822, which originally defined
 * the format for Internet message headers.
 */
class RW_MIME_GLOBAL RWMimeGenericHeader
    : public RWMimeHeader
{
public:

    /**
     * Default constructor. Constructs a header with an empty label and an
     * empty value.
     *
     * \note
     * A header with an empty label and an empty value does not meet the
     * requirements of an Internet Message Format header.
     */
    RWMimeGenericHeader(void);

    /**
     * Constructs a header with the given \a label and \a value. Does not
     * verify that the strings provided meet the requirements for an
     * Internet Message Format header. Throws RWMimeError if \a label is the
     * label for one of the other header classes. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWMimeGenericHeader(const RWCString& label, const RWCString& value);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeGenericHeader(const RWMimeGenericHeader& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if the label of \a second is the label
     * for one of the other header classes.
     */
    RWMimeGenericHeader(const RWMimeHeader& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     * Throws RWMimeError if the label of \a second is the label for one of
     * the other header classes.
     */
    RWMimeGenericHeader&
    operator=(const RWMimeGenericHeader& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeGenericHeader(void);

    /**
     * Returns the value of this header. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString
    getValue(void) const;

    /**
     * Sets the value of this header to \a value. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    void
    setValue(const RWCString& value);

protected:

    /**
     * Returns \c true if label is not the label for one of the other header
     * classes, \c false otherwise. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    virtual bool
    checkLabel(const RWCString& label) const;

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeUnstructuredHeaderImp&
    body(void) const;
};

#endif // rw_mime_RWMimeGenericHeader_h
