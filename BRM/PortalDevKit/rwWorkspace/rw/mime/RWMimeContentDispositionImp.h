#ifndef rw_mime_RWMimeContentDispositionImp_h
#define rw_mime_RWMimeContentDispositionImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentDispositionImp.h#1 $
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
#include <rw/mime/pkgdefs.h>
#include <rw/pointer/RWBodyBase.h>

/*
 * @internal
 *
 * RWMimeContentDispositionImp represents the value of the Content-Disposition
 * header of a MIME part.  The Content-Disposition specifies the way in which a
 * recipient should present the message.
 *
 * The value of a Content-Disposition header contains a disposition type and
 * an optional filename parameter. This class provides a convenient interface
 * for creating and working with Content-Disposition values.
 *
 * @reference
 * RWMimeContentDispositionImp conforms to the "Content-Disposition" header
 * requirements in RFC 1806.
 */
class RW_MIME_GLOBAL RWMimeContentDispositionImp
    : public RWBodyBase
{

public:

    /*
     * Default constructor.
     * Constructs a value with no disposition type and no filename parameter.
     *
     * @note A Content-Disposition value with no disposition type does not meet
     * the requirements of RFC 1806.
     */
    RWMimeContentDispositionImp(void);

    /*
     * Constructs a value the given disposition type \a type.
     * If \a filename is not empty, adds a filename parameter with a value of
     * \a filename to the new object.
     */
    RWMimeContentDispositionImp(const RWCString& type,
                                const RWCString& filename = "");

    /*
     * Copy constructor. Creates a new value as a deep copy of \a second.
     */
    RWMimeContentDispositionImp(const RWMimeContentDispositionImp& second);

    /*
     * Destructor.
     */
    ~RWMimeContentDispositionImp(void);

    /*
     * Returns self's disposition type.
     */
    RWCString
    getType(void) const;

    /*
     * Sets self's disposition type.
     * Does not validate \a type.
     */
    void
    setType(const RWCString& type);

    /*
     * Return the value of self's filename parameter, or the
     * empty string if no filename parameter is present.
     */
    RWCString
    getFilename(void) const;


    /*
     * Sets the value of self's filename parameter.  Does
     * not validate \a filename.
     */
    void
    setFilename(const RWCString& filename);

    /*
     * Returns a string representation of self.
     * The returned string is formatted as specified by RFC 1806 for
     * a Content-Disposition header value.
     *
     * @throw RWMimeError Thrown if self cannot be represented as valid MIME.
     */
    RWCString
    asString(void) const;

    /*
     * Populates self from \a dispositionValue.
     * Clears self before parsing begins.
     *
     * A Content-Disposition value must contain a disposition type, and may
     * contain a filename parameter. So, for example,
     * \c inline;filename="bluebox.jpg" is a valid \a dispositionValue.
     *
     * @throw RWMimeParseError Thrown if \a dispositionValue is not in the
     * format of a Content-Disposition value.
     */
    void
    fromString(const RWCString& dispositionValue);

    /*
     * Returns \c true if \a first is equal to \a second,
     * \c false otherwise.
     * First compares the disposition types using a case-insensitive string
     * comparison, then compares each parameter in first with the parameter
     * of the same name in second. Uses a case-insensitive comparison for
     * parameter name and a case-sensitive comparison for parameter value.
     */
    friend RW_MIME_SYMBOLIC bool
    operator==(const RWMimeContentDispositionImp& first, const RWMimeContentDispositionImp& second);

    /*
     * Returns \c true if \a first is not equal to \a second,
     * \c false otherwise.
     * First compares the disposition types using a case-insensitive string
     * comparison, then compares each parameter in first with the parameter
     * of the same name in second. Uses a case-insensitive comparison for
     * parameter name and a case-sensitive comparison for parameter value.
     */
    friend RW_MIME_SYMBOLIC bool
    operator!=(const RWMimeContentDispositionImp& first, const RWMimeContentDispositionImp& second);

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
    getParameterValue(const RWCString& name, size_t start) const;

    /*
     * Changes the value of the first parameter that contains a name
     * matching name to \a value.  If no such parameter exists, creates
     * a new parameter and inserts the new parameter into self's parameter
     * list. Begins searching at \a start.  Matches parameter names using
     * a case-insensitive string comparison.
     */
    void
    setParameterValue(const RWCString& name, const RWCString& value, size_t start);

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
     * @throw RWBoundsErr Thrown if \a position is greater than or equal to
     * getParameterCount().
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
    findParameter(const RWCString& name, size_t start) const;

    /*
     * Removes all parameters from self.
     */
    void
    removeAllParameters(void);

    /*
     * Returns a deep copy of self on the heap.
     */
    RWMimeContentDispositionImp*
    copy(void) const;

private:
    RWCString             type_;
    RWMimeParameterList   parameterList_;
};

#endif // rw_mime_RWMimeContentDispositionImp_h
