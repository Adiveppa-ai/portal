#ifndef rw_mime_RWMimeUnstructuredHeaderImp_h
#define rw_mime_RWMimeUnstructuredHeaderImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeUnstructuredHeaderImp.h#1 $
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

#include <rw/mime/RWMimeHeaderImp.h>
#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>

/*
 * @internal
 *
 * RWMimeUnstructuredHeaderImp is a concrete derived class for
 * unstructured header data.
 */

class RW_MIME_GLOBAL RWMimeUnstructuredHeaderImp
    : public RWMimeHeaderImp
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
    RWMimeUnstructuredHeaderImp(void);

    /*
     * Copy constructor.
     */
    RWMimeUnstructuredHeaderImp(const RWMimeUnstructuredHeaderImp& second);

    /*
     * Destructor.
     */
    virtual
    ~RWMimeUnstructuredHeaderImp(void);

    /*
     * Returns the value of this header.
     */
    RWCString
    getValue(void) const;

    /*
     * Sets the value of this header to \a value.
     *
     * A derived class may check \a value against the requirements
     * specified for the header type that class represents.  Classes
     * that check \a value throw RWMimeParseError if \a value is
     * not valid.
     *
     */
    void
    setValue(const RWCString& value);

    /*
     * Returns the value of this header, as it should appear in a
     * MIME message.
     */
    virtual RWCString
    getValueAsString(void) const;

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
    setValueFromString(const RWCString& value);

    /*
     * static make function for creating a RWMimeHeader with an
     * RWMimeUnstructuredHeaderImp.
     */
    static
    RWMimeHeader
    make(void);

    RWMimeHeaderImp*
    copy(void) const;

protected:

    /*
     * @internal
     * Assignment operator. Makes self a deep copy of \a second.
     */
    RWMimeUnstructuredHeaderImp&
    operator=(const RWMimeUnstructuredHeaderImp& second);

private:
    RWCString   value_;
};


#endif // rw_mime_RWMimeUnstructuredHeaderImp_h
