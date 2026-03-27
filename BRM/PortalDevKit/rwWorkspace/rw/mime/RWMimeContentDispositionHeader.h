#ifndef rw_mime_RWMimeContentDispositionHeader_h
#define rw_mime_RWMimeContentDispositionHeader_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentDispositionHeader.h#1 $
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
#include <rw/mime/RWMimeHeader.h>
#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>


/**
 * \ingroup mime_package
 *
 * \brief
 * Represents the Content-Disposition header of a MIME part.
 *
 * RWMimeContentDispositionHeader represents the Content-Disposition header
 * of a MIME part. The Content-Disposition specifies the way in which a
 * recipient should present the part.
 *
 * The Content-Disposition Header specification, RFC 1806, defines two
 * values for the header. A value of \c inline states that the part should
 * be presented at the same time the rest of the message is presented. A
 * value of \c attachment states that the part should be treated as a
 * separate file attached to the message. The specification also defines an
 * optional filename parameter that provides a filename for the MIME part.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * \note
 * RWMimeContentDispositionHeader conforms to the Content-Disposition header
 * requirements specified in RFC 1806.
 */
class RW_MIME_GLOBAL RWMimeContentDispositionHeader
    : public RWMimeHeader
{
public:

    /**
     * Static constant string containing \c "Content-Disposition", the label
     * for a Content-Disposition header. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    static const RWCString Label;

    /**
     * Default constructor. Constructs a header with no value.
     *
     * \note
     * A header with an empty value does not meet the requirements for a
     * Content-Disposition header.
     */
    RWMimeContentDispositionHeader(void);

    /**
     * Constructs a header with the value \a contentDisposition.
     */
    RWMimeContentDispositionHeader(const RWMimeContentDisposition& contentDisposition);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeContentDispositionHeader(const RWMimeContentDispositionHeader& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if \a second does not have the label
     * \c "Content-Description".
     */
    RWMimeContentDispositionHeader(const RWMimeHeader& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeContentDispositionHeader&
    operator=(const RWMimeContentDispositionHeader& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeContentDispositionHeader(void);

    /**
     * Returns a copy of self's value as an RWMimeContentDisposition.
     */
    RWMimeContentDisposition
    getContentDisposition(void) const;

    /**
     * Sets self's value to \a contentDisposition.
     */
    void
    setContentDisposition(const RWMimeContentDisposition& contentDisposition);

protected:

    /**
     * Returns \c true if label matches \c "Content-Disposition", \c false
     * otherwise. The comparison is case-insensitive. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    virtual bool
    checkLabel(const RWCString& label) const;

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeContentDispositionHeaderImp&
    body(void) const;
};


#endif // rw_mime_RWMimeContentDispositionHeader_h
