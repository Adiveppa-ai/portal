#ifndef rw_mime_RWMimeStructuredHeaderImp_h
#define rw_mime_RWMimeStructuredHeaderImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeStructuredHeaderImp.h#1 $
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
#include <rw/mime/pkgdefs.h>

/*
 * @internal
 *
 * RWMimeStructuredHeaderImp is a concrete derived class for
 * structured header data--that is, header data in which comments
 * contained within parens have no semantic meaning.
 */
class RW_MIME_GLOBAL RWMimeStructuredHeaderImp
    : public RWMimeHeaderImp
{
public:

    /*
     * Default constructor.
     * Constructs a header with an empty label and an empty value.
     *
     * @note A header with an empty value and an empty value does
     * not meet the requirements of an Internet Message Format header.
     */
    RWMimeStructuredHeaderImp(void);

    /*
     * Copy constructor.
     */
    RWMimeStructuredHeaderImp(const RWMimeStructuredHeaderImp& second);

    /*
     * Destructor.
     */
    virtual
    ~RWMimeStructuredHeaderImp(void);

    /*
     * Return the value associated with self.
     */
    RWCString
    getValue(void) const;

    /*
     * Set the value of self to \a value.
     *
     * A derived class may check \a value against the requirements
     * specified for the header type that class represents.  Classes
     * that check \a value throw RWMimeParseError if \a value is
     * not valid.
     */
    void
    setValue(const RWCString& value);

    /*
     * Return the value associated with self, as it should appear in
     * a MIME message.
     */
    virtual RWCString
    getValueAsString(void) const;

    /*
     * Set the value of self to \a value, after removing comments from
     * \a value.
     *
     * A derived class may check \a value against the requirements
     * specified for the header type that class represents.  Classes
     * that check \a value throw RWMimeParseError if \a value is
     * not valid.
     */
    virtual void
    setValueFromString(const RWCString& value);

    /*
     * static make function for creating a RWMimeHeader with an
     * RWMimeStructuredHeaderImp.
     */
    static
    RWMimeHeader
    make(void);

    /*
     * Creates a deep copy of self on the heap.
     */
    RWMimeHeaderImp*
    copy(void) const;

private:
    RWCString value_;
};

#endif // rw_mime_RWMimeStructuredHeaderImp_h
