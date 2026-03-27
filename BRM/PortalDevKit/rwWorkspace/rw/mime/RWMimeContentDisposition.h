#ifndef rw_mime_RWMimeContentDisposition_h
#define rw_mime_RWMimeContentDisposition_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentDisposition.h#1 $
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

#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents the value of a Content-Disposition header of a MIME part.
 *
 * RWMimeContentDisposition represents the value of a Content-Disposition
 * header of a MIME part. The Content-Disposition specifies the way in which
 * a recipient should present the part.
 *
 * The value of a Content-Disposition header contains a disposition type and
 * an optional filename parameter. This class provides a convenient
 * interface for creating and working with Content-Disposition values.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeContentDisposition conforms to the "Content-Disposition" header
 * requirements in RFC 1806.
 */
class RW_MIME_GLOBAL RWMimeContentDisposition
    : public RWHandleBase
{

public:

    /**
     * Default constructor. Constructs a value with no disposition type and
     * no filename parameter.
     *
     * \note
     * A Content-Disposition value with no disposition type does not meet
     * the requirements of RFC 1806.
     */
    RWMimeContentDisposition(void);

    /**
     * Constructs a value with the given disposition type \a type. If
     * \a filename is not empty, adds a filename parameter with a value of
     * \a filename to the new object. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWMimeContentDisposition(const RWCString& type,
                             const RWCString& filename = "");

    /*
     * @internal
     * Body constructor. Constructs a new handle to body.
     */
    RWMimeContentDisposition(RWMimeContentDispositionImp* body);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeContentDisposition(const RWMimeContentDisposition& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeContentDisposition&
    operator=(const RWMimeContentDisposition& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeContentDisposition(void);

    /**
     * Returns self's disposition type. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString
    getType(void) const;

    /**
     * Sets self's disposition type. Does not validate \a type. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    void
    setType(const RWCString& type);

    /**
     * Returns the value of self's filename parameter, or the empty string
     * if no filename parameter is present.
     */
    RWCString
    getFilename(void) const;

    /**
     * Sets the value of self's filename parameter. Does not validate
     * \a filename.
     */
    void
    setFilename(const RWCString& filename);

    /**
     * Returns a string representation of self. The returned string is
     * formatted as specified by RFC 1806 for a Content-Disposition header
     * value. Throws RWMimeError if self cannot be represented as valid
     * MIME. The RWCString should contain 7-bit US-ASCII data.
     */
    RWCString
    asString(void) const;

    /**
     * Populates self from \a dispositionValue. Throws RWMimeParseError if
     * \a dispositionValue is not in the format of a Content-Disposition
     * value.
     *
     * A Content-Disposition value must contain a disposition type, and may
     * contain a filename parameter. So, for example,
     * <tt>inline;filename="bluebox.jpg"</tt> is a valid
     * \a dispositionValue. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    void
    fromString(const RWCString& dispositionValue);

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
     * a case-insensitive string comparison to match \a name. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWCString
    getParameterValue(const RWCString& name, size_t start = 0) const;

    /**
     * Changes the value of the first parameter that contains a name
     * matching \a name to \a value. If no matching parameter exists,
     * creates a new parameter and inserts the new parameter into self's
     * parameter list. Begins searching at \a start. Matches parameter names
     * using a case-insensitive string comparison. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    void
    setParameterValue(const RWCString& name, const RWCString& value, size_t start = 0);

    /**
     * Inserts \a parameter at the end of self's parameter list.
     */
    void
    insertParameter(const RWMimeParameter& parameter);

    /**
     * Removes the parameter at the specified position. Throws RWBoundsErr
     * if \a position is greater than or equal to getParameterCount().
     */
    void
    removeParameter(size_t position);

    /**
     * Returns the index of the first parameter in the collection with a
     * name matching \a name, or #RW_NPOS if no parameter with that name is
     * present. Begins searching at position \a start. Uses a
     * case-insensitive comparison to match \a name. The RWCString should
     * contain 7-bit US-ASCII data.
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
     * \c false otherwise. The function compares the disposition types using
     * a case-insensitive string comparison. Compares the number of
     * parameters each object contains then compares each parameter in each
     * object to the parameter of the same name in the other object.
     * Parameter comparisons use a case-insensitive comparison for parameter
     * name and a case-sensitive comparison for parameter value.
     */
    friend RW_MIME_SYMBOLIC bool
    operator==(const RWMimeContentDisposition& first, const RWMimeContentDisposition& second);

    /**
     * Inequality operator. Returns \c true if \a first is not equal to
     * \a second, \c false otherwise. The function compares the disposition
     * types using a case-insensitive string comparison. Compares the number
     * of parameters each object contains then compares each parameter in
     * each object to the parameter of the same name in the other object.
     * Parameter comparisons use a case-insensitive comparison for parameter
     * name and a case-sensitive comparison for parameter value.
     */
    friend RW_MIME_SYMBOLIC bool
    operator!=(const RWMimeContentDisposition& first, const RWMimeContentDisposition& second);

    /*
     * Returns a deep copy of self
     */
    RWMimeContentDisposition
    copy(void) const;

protected:

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeContentDispositionImp&
    body(void) const;

private:

    /*
     * @internal
     * Hiding RWHandleBase::operator<().
     */
    bool
    operator<(const RWHandleBase& second) const;
};



#endif // rw_mime_RWMimeContentDisposition_h
