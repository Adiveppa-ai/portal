#ifndef rw_mime_RWMimeContentTypeImp_h
#define rw_mime_RWMimeContentTypeImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentTypeImp.h#1 $
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
#include <rw/pointer/RWBodyBase.h>

/*
 * @internal
 *
 * RWMimeContentTypeImp represents the value of a MIME Content-Type header.
 * The Content-Type of a part declares the original file type of body of the
 * part.  A Content-Type value contains three pieces of information: a \e media
 * \e type, a \e subtype, and any number of parameters.
 *
 * The media type declares the type of content in broad terms.  The MIME
 * specification itself defines media types of \c image, \c text, \c audio,
 * \c video, and \c application.  The minor type declares the specific file
 * format of the content.  For example, the media type \c image allows
 * subtype values such as \c gif, \c jpg, \c tiff, and so forth.
 *
 * Parameters, if present, add information about the media type. For
 * example, the media type \c text allows a parameter \c charset which states
 * the character set used for the text.
 *
 * For example, a complete Content-Type value for a MIME part containing XML
 *
 * @code
 * text/xml; charset=US-ASCII
 * @endcode
 *
 * has the media type \c text, the subtype \c xml, and a single parameter with
 * the name \c charset and the value \c US-ASCII.
 *
 * @reference
 * RWMimeContentTypeImp conforms to the "Content-Type" header requirements
 * specified in RFC 2045, Section 5 (p. 10).  For details on the content types
 * the MIME specification defines, see RFC 2046.
 */
class RW_MIME_GLOBAL RWMimeContentTypeImp
    : public RWBodyBase
{

public:

    /*
     * Default Constructor.
     * Constructs a content type value with an empty media type, an empty
     * subtype, and no parameters.
     *
     * @note A Content-Type header with an empty value does not meet the
     * requirements for an Internet Message header.
     */
    RWMimeContentTypeImp(void);

    /*
     * Copy Constructor.
     */
    RWMimeContentTypeImp(const RWMimeContentTypeImp& second);

    /*
     * Destructor.
     */
    virtual
    ~RWMimeContentTypeImp(void);

    /*
     * Return self's media type.
     */
    RWCString
    getMediaType(void) const;

    /*
     * Sets self's media type.
     */
    void
    setMediaType(const RWCString& mediaType);

    /*
     * Return self's subtype.
     */
    RWCString
    getSubType(void) const;

    /*
     * Sets self's subtype.
     */
    void
    setSubType(const RWCString& subType);

    /*
     * Returns a string representation of self.  The returned string
     * is formatted as specified by RFC 2045 for a Content-Type value.
     *
     * @throw RWMimeError Thrown if self cannot be represented as valid MIME.
     */
    virtual
    RWCString
    asString(void) const;

    /*
     * Returns the total number of parameters in self.
     */
    size_t
    getParameterCount(void) const;

    /*
     * Returns the parameter at the specified position.
     *
     * @throw RWBoundsErr Thrown if \a i is greater than or equal to
     * getParameterCount().
     */
    RWMimeParameter
    getParameter(size_t i) const;

    /*
     * Returns the value of the first parameter that contains a name matching
     * \a name, or the empty string if no such parameter is present.
     * Begins searching at \a start.  Matches parameter names using a
     * case-insensitive string comparison.
     */
    RWCString
    getParameterValue(const RWCString& name, size_t start = 0) const;

    /*
     * Changes the value of the first parameter that contains a name
     * matching name to \a value.  If no such parameter exists, creates
     * a new parameter and inserts the new parameter into self's parameter
     * list. Begins searching at \a start.  Matches parameter names using
     * a case-insensitive string comparison.
     */
    void
    setParameterValue(const RWCString& name, const RWCString& value, size_t start = 0);

    /*
     * Inserts \a parameter at the end of self's
     * parameter list.
     */
    void
    insertParameter(const RWMimeParameter& parameter);

    /*
     * Removes the parameter located at \a position from the
     * parameter list.
     *
     * @throw RWBoundsErr Thrown if \a position is greater than or
     * equal to getParameterCount().
     */
    void
    removeParameter(size_t position);

    /*
     * Returns the index of the first parameter starting from
     * \a start in the collection with a name matching \a name,
     * or #RW_NPOS if no parameter with that name is present. Uses a
     * case-insensitive string comparison to match \a name.
     */
    size_t
    findParameter(const RWCString& name, size_t start = 0) const;

    /*
     * Removes all parameters from self.
     */
    void
    removeAllParameters(void);

    /*
     * Returns \c true if \a first and \a second are equal, \c false
     * otherwise.
     * Compares the media type and the subtype using a case-insensitive
     * string comparison, then compares each parameter in first with
     * the parameter of the same name in second. Uses a case-insensitive
     * comparison for parameter name and a case-sensitive comparison for
     * parameter value.
     */
    friend RW_MIME_SYMBOLIC bool
    operator==(const RWMimeContentTypeImp& first, const RWMimeContentTypeImp& second);

    /*
     * Returns \c true if \a first and \a second are not equal, \c false
     * otherwise.
     * Compares the media type and the subtype using a case-insensitive
     * string comparison, then compares each parameter in first with
     * the parameter of the same name in second. Uses a case-insensitive
     * comparison for parameter name and a case-sensitive comparison for
     * parameter value.
     */
    friend RW_MIME_SYMBOLIC bool
    operator!=(const RWMimeContentTypeImp& first, const RWMimeContentTypeImp& second);


    virtual RWMimeContentTypeImp*
    copy(void) const;


private:

    RWCString mediaType_;
    RWCString subType_;
    RWMimeParameterList parameterList_;
};

#endif // rw_mime_RWMimeContentTypeImp_h
