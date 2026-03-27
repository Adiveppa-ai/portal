#ifndef rw_mime_RWMimeContentDescriptionHeader_h
#define rw_mime_RWMimeContentDescriptionHeader_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentDescriptionHeader.h#1 $
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
 * Represents the Content-Description header of a MIME part.
 *
 * RWMimeContentDescriptionHeader represents the Content-Description header
 * of a MIME part. The Content-Description provides a short text description
 * of the contents of the message part. For example, a MIME message
 * containing a sales report might contain the Content-Description header
 *
 * \code
 * Content-Description: Sales report for last quarter.
 * \endcode
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeContentDescriptionHeader conforms to the Content-Description header
 * requirements specified in RFC 2045, Section 8 (p. 27).
 */
class RW_MIME_GLOBAL RWMimeContentDescriptionHeader

    : public RWMimeHeader
{
public:

    /**
     * Static constant string containing \c "Content-Description", the label
     * for a Content-Description header. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    static const RWCString Label;

    /**
     * Default constructor. Constructs a header with an empty value.
     */
    RWMimeContentDescriptionHeader(void);

    /**
     * Constructs a header with the value \a description. Does not validate
     * \a description. The \a description provided must be in US-ASCII
     * format or be encoded according to the guidelines in RFC 2047 for the
     * header to meet the requirements of the Internet Message Format
     * specification. The RWCString should contain 7-bit US-ASCII data.
     */
    RWMimeContentDescriptionHeader(const RWCString& description);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeContentDescriptionHeader(const RWMimeContentDescriptionHeader& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if \a second does not have the label
     * \c "Content-Description".
     */
    RWMimeContentDescriptionHeader(const RWMimeHeader& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeContentDescriptionHeader&
    operator=(const RWMimeContentDescriptionHeader& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeContentDescriptionHeader(void);

    /**
     * Returns the content description value contained within this header.
     * The RWCString should contain 7-bit US-ASCII data.
     */
    RWCString
    getDescription(void) const;

    /**
     * Sets the content description value contained within this header. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    void
    setDescription(const RWCString& description);

protected:

    /**
     * Returns \c true if \a label matches \c "Content-Description",
     * \c false otherwise. The comparison is case-insensitive. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    virtual bool checkLabel(const RWCString& label) const;

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeUnstructuredHeaderImp&
    body(void) const;
};


#endif //rw_mime_RWMimeContentDescriptionHeader_h_
