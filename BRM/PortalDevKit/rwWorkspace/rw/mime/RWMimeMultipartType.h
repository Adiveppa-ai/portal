#ifndef rw_mime_RWMimeMultipartType_h
#define rw_mime_RWMimeMultipartType_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeMultipartType.h#1 $
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
#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents a \c Content-Type value with the media type \c multipart.
 *
 * RWMimeMultipartType represents a Content-Type value with the media type
 * \c multipart. As the name implies, the body of a \c multipart MIME part
 * contains other MIME parts. The MIME specification requires that the
 * header for a multipart Content-Type header contain a boundary parameter.
 * The value of that parameter forms the boundary between the contained
 * parts. For example, the message below specifies a
 * \c multipart/alternative Content-Type with the boundary \c uniquestring.
 *
 * \code
 * MIME-Version: 1.0
 * Content-Type: multipart/alternative; boundary=uniquestring
 * From: Rudi Marquez <rudi_marquez@roguewave.com>
 * To: Andy Roture <roture@example.org>
 * Date: Tue, 30 Oct 2001 08:00:53 -0700 (PDT)
 * Subject: A multipart/alternative message
 *
 * Preamble text.
 *
 * --uniquestring
 * Content-Type: text/plain; charset=US-ASCII
 *
 * The message (in plain text).
 * --uniquestring
 * Content-Type: text/html; charset=US-ASCII
 *
 * The message (in bold HTML text).
 * --uniquestring--
 * \endcode
 *
 * This class inherits general purpose functions for working with a
 * parameter list and provides convenience functions for working with the
 * boundary parameter.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeMultipartType conforms to the multipart Content-Type header
 * requirements specified in RFC 2046, section 5.1 (p. 12).
 */
class RW_MIME_GLOBAL RWMimeMultipartType
    : public RWMimeContentType
{
public:

    /**
     * Default constructor. Constructs a multipart Content-Type value with
     * the subtype \c "mixed". The value contains a boundary parameter with
     * a boundary created by RWMimeUtils::getUniqueBoundary().
     */
    RWMimeMultipartType(void);

    /**
     * Constructs a multipart Content-Type value with the subtype
     * \a subType. The value contains a boundary parameter with the value
     * \a boundary. If no \a boundary is provided, a boundary value is
     * created using RWMimeUtils::getUniqueBoundary(). The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWMimeMultipartType(const RWCString& subType, const RWCString& boundary = "");

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeMultipartType(const RWMimeMultipartType& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if the media type of \a second is not
     * \c "multipart".
     */
    RWMimeMultipartType(const RWMimeContentType& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeMultipartType&
    operator=(const RWMimeMultipartType& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeMultipartType(void);

    /**
     * Returns the value of self's boundary parameter, or an empty string if
     * self does not contain a boundary parameter. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getBoundary(void) const;

    /**
     * Sets the value of self's boundary parameter. The RWCString should
     * contain 7-bit US-ASCII data.
     *
     * \note
     * The RWMimeUtils::getUniqueBoundary() function generates boundary
     * strings.
     */
    void
    setBoundary(const RWCString& boundary);

protected:

    /**
     * Returns \c true if \a mediaType is \c "multipart". The RWCString
     * should contain 7-bit US-ASCII data.
     */
    virtual bool
    checkType(const RWCString& mediaType, const RWCString& subType) const;
};


#endif //rw_mime_RWMimeMultipartType_h_
