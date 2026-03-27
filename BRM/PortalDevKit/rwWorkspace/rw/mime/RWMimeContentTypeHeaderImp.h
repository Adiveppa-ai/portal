#ifndef rw_mime_RWMimeContentTypeHeaderImp_h
#define rw_mime_RWMimeContentTypeHeaderImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentTypeHeaderImp.h#1 $
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

#include <rw/mime/RWMimeContentType.h>
#include <rw/mime/RWMimeHeaderImp.h>
#include <rw/mime/pkgdefs.h>

/*
 * @internal
 * RWMimeContentTypeHeaderImp is an internal implementation of the
 * RWMimeContentTypeHeader.
 *
 * @reference
 * Refer to the RWMimeContentTypeHeader for more information on
 * support for the "Content-Type" MIME header.
 */
class RW_MIME_GLOBAL RWMimeContentTypeHeaderImp
    : public RWMimeHeaderImp
{
public:

    /*
     * Default constructor.
     * Constructs a default, empty header.
     *
     * @note A header with an empty value does not meet the requirements
     * for an Internet Message Format header.
     */
    RWMimeContentTypeHeaderImp(void);

    /*
     * Copy constructor
     */
    RWMimeContentTypeHeaderImp(const RWMimeContentTypeHeaderImp& second);

    /*
     * Destructor
     */
    virtual
    ~RWMimeContentTypeHeaderImp(void);

    /*
     * Gets self's value, as it should appear in a MIME message.
     */
    virtual RWCString
    getValueAsString(void) const;

    /*
     * Sets self's value to \a value.
     *
     * @throw RWMimeParseError Thrown if \a value does not match the format
     * of a Content-Type value.
     *
     */
    virtual void
    setValueFromString(const RWCString& value);

    /*
     * Returns a copy of the content type value this header contains.
     */
    RWMimeContentType
    getContentType(void) const;

    /*
     * Sets the Content-Type this header contains to contentType.
     */
    void
    setContentType(const RWMimeContentType& contentType);

    /*
     * Creates and returns a new RWMimeHeader object with an
     * RWMimeContentTypeHeaderImp implementation.
     */
    static
    RWMimeHeader
    make(void);

    /*
     * Returns a deep copy of self on the heap.
     */
    RWMimeHeaderImp*
    copy(void) const;

protected:

    /*
     * Compare values of RWMimeContentTypeHeaderImp in
     * case-insensitive manner.
     */
    virtual bool
    compareValueTo(const RWMimeHeaderImp& second) const;

private:
    RWMimeContentType    contentType_;
};


#endif // rw_mime_RWMimeContentTypeHeaderImp_h
