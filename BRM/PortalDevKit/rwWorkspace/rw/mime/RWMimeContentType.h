#ifndef rw_mime_RWMimeContentType_h
#define rw_mime_RWMimeContentType_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentType.h#1 $
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

#include <rw/mime/RWMimeParameterList.h>
#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

/*
 *
 * RWMimeContentType represents the value of a MIME Content-Type header.
 * The Content-Type of a part declares the original file type of body of the
 * part.  A Content-Type value contains three pieces of information: a \e media
 * \e type, a \e subtype, and any number of parameters.
 */
/**
 * \ingroup mime_package
 *
 * \brief
 * Represents the \e value of a MIME \c Content-Type header.
 *
 * RWMimeContentType represents the value of a MIME Content-Type header. A
 * Content-Type value contains a <em>media type</em>, a <em>subtype</em>,
 * and any number of parameters.
 *
 * The media type declares the type of content in broad terms. The MIME
 * specification itself defines media types of \c image, \c text, \c audio,
 * \c video, \c application, \c message and \c multipart. The subtype
 * declares the specific file format of the content. For example, the media
 * type \c image allows subtype values such as \c gif, \c jpeg, \c tiff, and
 * so forth.
 *
 * Parameters, if present, add information about the media type. For
 * example, the media type \c text allows a parameter \c charset which
 * states the character set used for the \c text.
 *
 * A complete Content-Type value for a MIME part containing XML has the
 * media type \c text, the subtype \c xml, and a single parameter with the
 * name \c charset and the value \c US-ASCII.
 *
 * \code
 * text/xml;charset=US-ASCII
 * \endcode
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeContentType conforms to the Content-Type header requirements
 * specified in RFC 2045, section 5 (p. 10). For details on the content
 * types that the MIME specification defines, see RFC 2046.
 */
class RW_MIME_GLOBAL RWMimeContentType
    : public RWHandleBase
{

public:

    /**
     * Default constructor. Constructs a content type with no media type, an
     * empty subtype, and no parameters.
     *
     * \note
     * A Content-Type header with an empty value does not meet the
     * requirements for an Internet Message header.
     */
    RWMimeContentType(void);

    /*
     * @internal
     * Constructs an RWMimeContentType with implementation \c imp.
     */
    RWMimeContentType(RWMimeContentTypeImp* imp);

    /**
     * Constructs a Content-Type header value with the media type
     * \a mediaType, the subtype \a subType, and the parameter list
     * \a parameters. Does not validate \a mediaType, \a subType or
     * \a parameters. The RWCString should contain 7-bit US-ASCII data.
     */
    RWMimeContentType(const RWCString& mediaType,
                      const RWCString& subType,
                      const RWMimeParameterList& parameters = RWMimeParameterList());

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeContentType(const RWMimeContentType& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeContentType&
    operator=(const RWMimeContentType& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeContentType(void);

    /**
     * Returns self's media type. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString
    getMediaType(void) const;

    /**
     * Returns self's subtype. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    RWCString
    getSubType(void) const;

    /**
     * Returns a string representation of self. The returned string is
     * formatted as specified by RFC 2045 for a Content-Type value.
     *
     * \exception RWMimeError
     * Thrown if self cannot be represented as valid MIME. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWCString
    asString(void) const;

    /**
     * Populates self from \a contentType. The function parses but does not
     * validate \a contentType.
     *
     * A MIME Content-Type value requires that the media type and subtype
     * appear first in the string, separated by a slash. Each parameter must
     * be preceded by a semicolon and contain the parameter name, an equal
     * sign, and the parameter value. For example, the string
     * \c "text/xml;charset=US-ASCII" is a valid \a contentType that
     * contains the media type \c text, the subtype \c xml, and a single
     * parameter with the name \c charset and the value \c US-ASCII.
     *
     * Derived classes may place additional requirements on this function to
     * ensure that the function creates an RWMimeContentType of the
     * appropriate type. The RWCString should contain 7-bit US-ASCII data.
     *
     * \exception RWMimeParseError
     * Thrown if \a contentType is not in the format of a Content-Type
     * value.
     */
    void
    fromString(const RWCString& contentType);

    /**
     * Returns the total number of parameters in self.
     */
    size_t
    getParameterCount(void) const;

    /**
     * Returns the parameter at the specified position.
     *
     * \exception RWBoundsErr
     * Thrown if \a i is greater than or equal to getParameterCount().
     */
    RWMimeParameter
    getParameter(size_t i) const;

    /**
     * Returns the value of the first parameter that contains a name
     * matching \a name, or the empty string if no such parameter is
     * present. Begins searching at \a start. Matches parameter names using
     * a case-insensitive string comparison. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWCString
    getParameterValue(const RWCString& name, size_t start = 0) const;

    /**
     * Changes the value of the first parameter with a name matching \a name
     * to \a value. If no such parameter exists, creates a new parameter and
     * inserts the new parameter at the end of self's parameter list. Begins
     * searching at \a start. Matches parameter names using a
     * case-insensitive string comparison. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    void
    setParameterValue(const RWCString& name, const RWCString& value, size_t start = 0);

    /**
     * Inserts \a parameter at the end of self's parameter list.
     */
    void
    insertParameter(const RWMimeParameter& parameter);

    /**
     * Removes the parameter located at \a position from the parameter list.
     *
     * \exception RWBoundsErr
     * Thrown if \a position is greater than or equal to
     * getParameterCount().
     */
    void
    removeParameter(size_t position);

    /**
     * Returns the index of the first parameter in the collection with a
     * name matching \a name, or #RW_NPOS if no parameter with that name is
     * present. Begins searching at position \a start. Uses a
     * case-insensitive string comparison to match \a name. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    size_t
    findParameter(const RWCString& name, size_t start = 0) const;

    /**
     * Removes all parameters from self.
     */
    void
    removeAllParameters(void);

    /**
     * Equality operator. Returns \c true if \a first is equal to \a second,
     * \c false otherwise. Compares the media type and the subtype using a
     * case-insensitive string comparison. Compares the number of parameters
     * the objects contain, then compares each parameter in each object with
     * the parameter of the same name in the other object. Parameter
     * comparisons use a case-insensitive comparison for parameter name and
     * a case-sensitive comparison for parameter value.
     */
    friend RW_MIME_SYMBOLIC bool
    operator==(const RWMimeContentType& first, const RWMimeContentType& second);

    /**
     * Inequality operator. Returns \c true if \a first is not equal to
     * \a second, \c false otherwise. Compares the media type and the
     * subtype using a case-insensitive string comparison. Compares the
     * number of parameters the objects contain, then compares each
     * parameter in each object with the parameter of the same name in the
     * other object. Parameter comparisons use a case-insensitive comparison
     * for parameter name and a case-sensitive comparison for parameter
     * value.
     */
    friend RW_MIME_SYMBOLIC bool
    operator!=(const RWMimeContentType& first, const RWMimeContentType& second);

    /*
     * Returns a handle to a deep copy of self.
     */
    RWMimeContentType
    copy(void) const;

protected:

    /**
     * Returns \c true. Since RWMimeContentType does not represent any
     * specific content type value, this class imposes no special
     * requirements on the type. In RWMimeContentType, this class returns
     * \c true without examining either the \a mediaType or \a subType.
     * Derived classes that represent specific content types may require
     * specific values. The RWCString should contain 7-bit US-ASCII data.
     */
    virtual bool
    checkType(const RWCString& mediaType, const RWCString& subType) const;

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeContentTypeImp&
    body(void) const;

private:

    /*
     * @internal
     * Hiding RWHandleBase::operator<().
     */
    bool
    operator<(const RWHandleBase& second) const;
};

#endif // rw_mime_RWMimeContentType_h
