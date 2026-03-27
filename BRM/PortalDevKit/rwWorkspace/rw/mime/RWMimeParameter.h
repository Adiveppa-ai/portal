#ifndef rw_mime_RWMimeParameter_h
#define rw_mime_RWMimeParameter_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeParameter.h#1 $
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

#include <rw/mime/pkgdefs.h>
#include <rw/cstring.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents a parameter within the content of a MIME header.
 *
 * RWMimeParameter represents a parameter within the value of a MIME header.
 * Each MIME parameter has a name and a value. An equal sign separates the
 * name and the value. For example, the parameter \c charset=US-ASCII
 * contains the name \c charset and the value \c US-ASCII.
 *
 * The parameter name may consist of US-ASCII characters with the exception
 * of control characters, space, or any of the special characters shown
 * below:
 *
 * \code
 * ()<>@,;:\"/[]?=
 * \endcode
 *
 * The parameter value may contain any US-ASCII character with the exception
 * of US-ASCII control characters, carriage return, and linefeed.
 *
 * @reference
 * RWMimeParameter creates parameters in the syntax specified by RFC 2045,
 * Section 5 (p. 9-12) and in compliance with RFC 2822.
 */
class RW_MIME_SYMBOLIC RWMimeParameter
{
public:

    /**
     * Default constructor. Constructs a parameter with an empty name and an
     * empty value.
     *
     * \note
     * A parameter with an empty name and an empty value does not meet the
     * specification of a MIME Content-Type parameter.
     */
    RWMimeParameter(void);

    /**
     * Constructs a parameter with the given \a name and \a value. Does not
     * validate \a name or \a value. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWMimeParameter(const RWCString& name, const RWCString& value);

    /**
     * Copy constructor. Constructs a new parameter as a deep copy of
     * \a second.
     */
    RWMimeParameter(const RWMimeParameter& second);

    /**
     * Assignment operator. Makes self a deep copy of \a second.
     */
    RWMimeParameter&
    operator=(const RWMimeParameter& second);

    /**
     * Destructor.
     */
    ~RWMimeParameter(void);

    /**
     * Equality operator. Returns \c true if \a first and \a second are
     * equal, \c false otherwise. Uses a case-insensitive string comparison
     * for parameter names, a case-sensitive string comparison for parameter
     * values.
     */
    friend RW_MIME_SYMBOLIC bool
    operator==(const RWMimeParameter& first, const RWMimeParameter& second);

    /**
     * Returns the name of this parameter. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWCString
    getName(void) const;

    /**
     * Sets the name of this parameter to \a name. Does not validate
     * \a name. The RWCString should contain 7-bit US-ASCII data.
     */
    void
    setName(const RWCString& name);

    /**
     * Returns the value of this parameter. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWCString
    getValue(void) const;

    /**
     * Sets the value of this parameter to \a value. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    void
    setValue(const RWCString& value);

    /**
     * Returns this parameter as a string. Produces a string in the format
     * <tt><em>name</em>=\"<em>value</em>\"</tt>. Escapes the parameter
     * value as necessary to generate a correctly quoted and escaped string.
     * Does not otherwise validate the returned string. Throws RWMimeError
     * if self cannot be represented as valid MIME. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    asString(void) const;

    /**
     * Populates self with the contents of \a parameterString. Throws
     * RWMimeParseError if the function cannot parse \a parameterString as a
     * valid MIME parameter. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    void
    fromString(const RWCString& parameterString);

private:
    RWCString   name_;
    RWCString   value_;
};


#endif // rw_mime_RWMimeParameter_h
