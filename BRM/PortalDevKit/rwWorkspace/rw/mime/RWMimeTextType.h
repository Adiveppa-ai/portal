#ifndef rw_mime_RWMimeTextType_h
#define rw_mime_RWMimeTextType_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeTextType.h#1 $
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
#include <rw/mime/pkgdefs.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents a \c Content-Type value with the media type \c text.
 *
 * RWMimeTextType represents a Content-Type value with the media type text.
 * The MIME specification states that a Content-Type header for text may
 * contain a charset parameter. If present, the parameter specifies the
 * character set used for the body of the MIME part containing the header.
 * If the charset parameter is not present, the character set of the part is
 * defined as US-ASCII.
 *
 * An instance of the class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeTextType conforms to the text Content-Type header requirements
 * specified in RFC 2046, section 4.1 (p. 6).
 */
class RW_MIME_GLOBAL RWMimeTextType
    : public RWMimeContentType
{
public:

    /**
     * Default constructor. Constructs a text Content-Type value with the
     * subtype \c "plain". The value does not contain a charset parameter.
     *
     * \note
     * A text Content-Type value without a charset parameter defines the
     * character set of the part body as US-ASCII.
     */
    RWMimeTextType(void);

    /**
     * Constructs a text Content-Type value with the subtype \a subType.
     * When a \a charset argument is present, the new value contains a
     * \c charset parameter with the value \a charset. Otherwise, the new
     * value does not contain a \c charset parameter. The RWCString should
     * contain 7-bit US-ASCII data.
     *
     * \note
     * A text Content-Type value without a charset parameter defines the
     * character set of the part body as US-ASCII.
     */
    RWMimeTextType(const RWCString& subType, const RWCString& charset = "");

    /**
     * Constructs a new handle to the body \a second refers to.
     */
    RWMimeTextType(const RWMimeTextType& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if \a second does not have the media
     * type \c "text".
     */
    RWMimeTextType(const RWMimeContentType& second);

    /**
     * Makes self a handle identical to \a second.
     */
    RWMimeTextType&
    operator=(const RWMimeTextType& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeTextType(void);

    /**
     * Returns the value of self's \c charset parameter, or an empty string
     * if self does not contain a \c charset parameter. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getCharset(void) const;

    /**
     * Sets the value of self's \c charset parameter. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    void
    setCharset(const RWCString& charset);

protected:

    /**
     * Returns \c true if \a mediaType is \c "text", \c false otherwise. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    virtual bool
    checkType(const RWCString& mediaType, const RWCString& subType) const;
};


#endif //rw_mime_RWMimeTextType_h_
