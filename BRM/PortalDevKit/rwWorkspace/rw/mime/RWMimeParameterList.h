#ifndef rw_mime_RWMimeParameterList_h
#define rw_mime_RWMimeParameterList_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeParameterList.h#1 $
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

#include <rw/mime/RWMimeParameter.h>
#include <rw/mime/pkgdefs.h>
#include <rw/tvordvec.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup mime_package
 *
 * \brief
 * Contains a bounds-checked vector of RWMimeParameter objects.
 *
 * RWMimeParameterList contains a bounds-checked vector of RWMimeParameter
 * objects.
 */
class RW_MIME_SYMBOLIC RWMimeParameterList
{

public:

    typedef RWTValOrderedVector<RWMimeParameter> RWMimeParameterVector;

    /**
     * Default constructor. Constructs an empty parameter list.
     */
    RWMimeParameterList(void);

    /**
     * Copy constructor. Constructs a new list as a deep copy of \a second.
     */
    RWMimeParameterList(const RWMimeParameterList& second);

    /**
     * Assignment operator. Makes self a deep copy of \a second.
     */
    RWMimeParameterList&
    operator=(const RWMimeParameterList& second);

    /**
     * Destructor.
     */
    ~RWMimeParameterList(void);

    /**
     * Returns the total number of parameters in self.
     */
    size_t
    getParameterCount(void) const;

    /**
     * Returns the parameter at the specified position. Throws RWBoundsErr
     * if \a i is greater than or equal to getParameterCount().
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
     * Changes the value of the first parameter that contains a name
     * matching \a name to \a value. Begins searching at \a start. If no
     * such parameter exists, creates a new parameter and inserts the new
     * parameter into self's parameter list. Matches parameter names using a
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
     * Throws RWBoundsErr if \a position is greater than or equal to
     * getParameterCount().
     */
    void
    removeParameter(size_t position);

    /**
     * Returns the index of the first parameter in the collection with a
     * name matching \a name, or #RW_NPOS if no parameter with that name is
     * present. Begins searching at \a start. Uses a case-insensitive
     * comparison to match \a name. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    size_t
    findParameter(const RWCString& name, size_t start = 0) const;

    /**
     * Removes all parameters from self.
     */
    void
    removeAllParameters(void);

    /**
     * Returns a string representation of self. Throws RWMimeError if self
     * cannot be represented as valid MIME. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    RWCString
    asString(void) const;

    /**
     * Parses \a paramString and populates self with the contents of
     * \a paramString. Throws RWMimeParseError if the function cannot parse
     * the contents of \a paramString. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    void
    fromString(const RWCString& paramString);

    /**
     * Equality operator. Returns \c true if \a first and \a second are
     * equal, \c false otherwise. Compares the number of parameters the
     * objects contain, then compares each parameter in each object with the
     * parameter of the same name in the other object. Uses a
     * case-insensitive comparison for parameter name and a case-sensitive
     * comparison for parameter value.
     */
    friend RW_MIME_SYMBOLIC bool
    operator==(const RWMimeParameterList& first, const RWMimeParameterList& second);

private:
    RWMimeParameterVector parameters_;
};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // rw_mime_RWMimeParameterList_h
