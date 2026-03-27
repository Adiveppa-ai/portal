#ifndef rw_mime_RWMimeMultipartRelatedType_h
#define rw_mime_RWMimeMultipartRelatedType_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeMultipartRelatedType.h#1 $
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

#include <rw/mime/RWMimeMultipartType.h>
#include <rw/mime/pkgdefs.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents a \c Content-Type value with the media type \c multipart and
 * the subtype \c related.
 *
 * RWMimeMultipartRelatedType represents a Content-Type value with the media
 * type \c multipart and the subtype \c related. A \c multipart/related MIME
 * part contains a set of other MIME parts intended for use as a whole. For
 * example, a single \c multipart/related message can contain an HTML page
 * and the images referenced in the page.
 *
 * A \c multipart/related Content-Type value includes parameters describing
 * how the recipient should process the message.
 *
 * - The \c start parameter declares the Content-ID of the part which a
 * recipient should process first. For example, a message containing an HTML
 * page and images uses the Content-ID of the HTML page as the value of the
 * \c start parameter. This parameter is optional. If the parameter is not
 * present, the first part in the message will be processed first.
 * - The \c type parameter declares the Content-Type of the part which a
 * recipient should process first. For example, a message containing an HTML
 * page and images uses \c "text/html" as the value of the \c type
 * parameter.
 * - The \c start-info parameter provides additional information to the
 * receiving application. For example, a typical use of this parameter is to
 * provide command-line arguments for the receiving application. This
 * parameter is optional and should only be used when the message is
 * intended for a specific application.
 * - The \c boundary parameter contains a string used to separate the parts
 * of the message.
 *
 * RWMimeMultipartRelatedType inherits general purpose functions for working
 * with a parameter list and convenience functions for working with the
 * \c boundary parameter. The class provides functions for working with the
 * \c type parameter, the \c start parameter, and the \c start-info
 * parameter.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeMultipartRelatedType conforms to the requirements in RFC 2837 for
 * the value of a \c multipart/related Content-Type header.
 */
class RW_MIME_GLOBAL RWMimeMultipartRelatedType
    : public RWMimeMultipartType
{
public:

    /**
     * Default constructor. Constructs a \c multipart/related Content-Type
     * value. The new value does not contain a \c type parameter, a \c start
     * parameter, or a \c start-info parameter. The constructor creates a
     * boundary value using RWMimeUtils::getUniqueBoundary().
     *
     * \note
     * A default-constructed RWMimeMultipartRelatedType is invalid. A
     * multipart/related content type must contain a type parameter.
     */
    RWMimeMultipartRelatedType(void);

    /**
     * Constructs a \c multipart/related Content-Type value with the given
     * parameters. If no argument is provided for \a start or \a start_info,
     * the new value does not contain a start parameter or a start-info
     * parameter. If no boundary is provided, the constructor creates a
     * boundary value using RWMimeUtils::getUniqueBoundary(). The RWCString
     * should contain 7-bit US-ASCII data.
     *
     * \note
     * The multipart/related specification requires the value of the type
     * parameter to match the actual Content-Type of the document to be
     * processed first. The constructor itself cannot enforce this
     * requirement.
     */
    RWMimeMultipartRelatedType(const RWCString& type,
                               const RWCString& start = "",
                               const RWCString& start_info = "",
                               const RWCString& boundary = "");

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeMultipartRelatedType(const RWMimeMultipartRelatedType& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeParseError if \a second is not a
     * \c multipart/related content type.
     */
    RWMimeMultipartRelatedType(const RWMimeContentType& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeMultipartRelatedType&
    operator=(const RWMimeMultipartRelatedType& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeMultipartRelatedType(void);

    /**
     * Returns the value of self's type parameter, or an empty string if
     * self does not contain a type parameter. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWCString
    getType(void) const;

    /**
     * Sets the value of self's type parameter. The RWCString should contain
     * 7-bit US-ASCII data.
     *
     * \note
     * The multipart/related specification requires the value of the type
     * parameter to match the actual Content-Type of the document to be
     * processed first. The function itself cannot enforce this requirement.
     */
    void
    setType(const RWCString& type);

    /**
     * Returns the value of self's start parameter, or an empty string if
     * self does not contain a start parameter. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWCString
    getStart(void) const;

    /**
     * Sets the value of self's start parameter. The RWCString should
     * contain 7-bit US-ASCII data.
     *
     * \note
     * The multipart/related specification requires the value of the start
     * parameter to match the Content-ID of a part contained in the MIME
     * message. The function itself cannot enforce this requirement.
     */
    void
    setStart(const RWCString& contentId);

    /**
     * Returns the value of self's start-info parameter, or an empty string
     * if self does not contain a start-info parameter. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getStartInfo(void) const;

    /**
     * Sets the value of self's start-info parameter. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    void
    setStartInfo(const RWCString& startInfo);

protected:

    /**
     * Returns true if \a mediaType matches \c "multipart" and \a subType
     * matches \c "related". Both comparisons are case-insensitive. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    virtual bool
    checkType(const RWCString& mediaType, const RWCString& subType) const;
};


#endif // rw_mime_RWMimeMultipartRelatedType_h
