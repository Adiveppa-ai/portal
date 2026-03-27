#ifndef rw_mime_RWMimeContentDispositionHeaderImp_h
#define rw_mime_RWMimeContentDispositionHeaderImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentDispositionHeaderImp.h#1 $
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

#include <rw/mime/RWMimeContentDisposition.h>
#include <rw/mime/RWMimeHeaderImp.h>
#include <rw/mime/pkgdefs.h>

/*
 * @internal
 * RWMimeContentDispositionHeaderImp is an internal implementation of the
 * RWMimeContentDispositionHeader.
 *
 * The Content-Disposition Header specification, RFC 1806, defines two values
 * for the header.  A value of \c inline states that the part should be
 * presented at the same time as the rest of the message is presented.  A
 * value of \c attachment states that the part should be treated as a
 * separate file attached to the message.  The specification also defines
 * an optional filename parameter that provides a filename for the MIME part.
 *
 * @reference
 * Refer to the RWMimeContentTypeHeader for more information on
 * support for the "Content-Disposition" MIME header.
 */
class RW_MIME_GLOBAL RWMimeContentDispositionHeaderImp
    : public RWMimeHeaderImp
{
public:

    /*
     * Default constructor. Constructs a header with no value.
     */
    RWMimeContentDispositionHeaderImp(void);

    /*
     * Copy constructor.  Constructs a new header as a deep copy of \a second.
     */
    RWMimeContentDispositionHeaderImp(const RWMimeContentDispositionHeaderImp& second);

    /*
     * Destructor.
     */
    virtual
    ~RWMimeContentDispositionHeaderImp(void);

    /*
     * Get the value associated with this header as
     * a string, as it should appear in a MIME message.
     */
    virtual RWCString
    getValueAsString(void) const;

    /*
     * Sets self's value to the contents of \a value.
     *
     * @throw RWMimeParseError Thrown if \a value does not match the format of a
     * Content-Disposition header value.
     */
    virtual void
    setValueFromString(const RWCString& value);

    /*
     * Returns a copy of self's value as an RWMimeContentDisposition.
     */
    RWMimeContentDisposition
    getContentDisposition(void) const;

    /*
     * Sets self's value to \a contentDisposition.
     */
    void
    setContentDisposition(const RWMimeContentDisposition& contentDisposition);

    /*
     * static make function for creating a RWMimeHeader with an
     * RWMimeUnstructuredHeaderImp.
     */
    static
    RWMimeHeader
    make(void);

    /*
     * Returns a new deep copy of self on the heap.
     */
    RWMimeHeaderImp*
    copy(void) const;

protected:

    /*
     * Compare values of RWMimeContentDispositionHeaderImp in
     * case-insensitive manner.
     */
    virtual bool
    compareValueTo(const RWMimeHeaderImp& second) const;

private:
    RWMimeContentDisposition    contentDisposition_;
};


#endif // rw_mime_RWMimeContentDispositionHeaderImp_h
