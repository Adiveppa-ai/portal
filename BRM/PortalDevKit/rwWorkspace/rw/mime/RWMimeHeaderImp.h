#ifndef rw_mime_RWMimeHeaderImp_h
#define rw_mime_RWMimeHeaderImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeHeaderImp.h#1 $
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
#include <rw/pointer/RWBodyBase.h>

/*
 *
 * RWMimeHeaderImp is an abstract base class for defining the Imp
 * hierarchy for RWMimeHeader.
 */

class RW_MIME_GLOBAL RWMimeHeaderImp
    : public RWBodyBase
{
public:

    /*
     * Default constructor.
     * Constructs a header with an empty label and an empty value.
     *
     * @note A header with an empty value and an empty value does
     * not meet the requirements of an Internet Message Format header.
     *
     */
    RWMimeHeaderImp(void);

    /*
     * Destructor.
     */
    virtual
    ~RWMimeHeaderImp(void);

    /*
     * Returns the label of this header.
     */
    RWCString
    getLabel(void) const;


    /*
     * Sets self's label to \a label.
     *
     * @note
     * A derived class may require that \a label match the label
     * of the header type the class represents.  Classes that
     * check \a label throw RWMimeParseError if \a label is not
     * valid.
     */
    void
    setLabel(const RWCString& label);

    /*
     * Returns the value of this header, as it should appear in a MIME
     * message.
     */
    virtual RWCString
    getValueAsString(void) const = 0;

    /*
     * Sets the value of this header to \a value.
     *
     * A derived class may check \a value against the requirements
     * specified for the header type that class represents.  Classes
     * that check \a value throw RWMimeParseError if \a value is
     * not valid.
     *
     */
    virtual void
    setValueFromString(const RWCString& value) = 0;

    /*
     * Returns this header as a string.  Throws RWMimeError if the
     * header cannot be formatted as valid MIME.
     */
    RWCString
    asString(void) const;

    /*
     * Equality operator.
     */
    friend RW_MIME_SYMBOLIC bool
    operator==(const RWMimeHeaderImp& first, const RWMimeHeaderImp& second);

    /*
     * Inequality operator.
     */
    friend RW_MIME_SYMBOLIC bool
    operator!=(const RWMimeHeaderImp& first, const RWMimeHeaderImp& second);

    /*
     * Returns a copy of self on the heap.  This function is intended
     * for use with the clone() method of the handle class.
     */
    virtual RWMimeHeaderImp*
    copy(void) const = 0;

protected:
    /*
     * Compares labels in case-insensitive manner.
     */
    bool
    compareLabelTo(const RWMimeHeaderImp& second) const;

    /*
     * Compares values in case-sensitive manner.  Overridden in
     * derived classes to provide specialized comparison semantics.
     */
    virtual bool
    compareValueTo(const RWMimeHeaderImp& second) const;

private:
    RWCString   label_;
};


#endif // rw_mime_RWMimeHeaderImp_h
