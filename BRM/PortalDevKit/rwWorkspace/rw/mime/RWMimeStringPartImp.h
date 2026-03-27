#ifndef rw_mime_RWMimeStringPartImp_h
#define rw_mime_RWMimeStringPartImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeStringPartImp.h#1 $
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

#include <rw/mime/RWMimeHeader.h>
#include <rw/mime/RWMimePartImp.h>
#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>

/*
 * @internal
 * This class provides the implementation of an RWMimePart containing a
 * single string as body content.  There's no need for an application
 * to use this class directly; a handle provides appropriate access.
 */
class RW_MIME_GLOBAL RWMimeStringPartImp
    : public RWMimePartImp
{
public:

    /*
     * Default constructor.
     * Constructs a MIME part with no headers and no body.
     */
    RWMimeStringPartImp(void);

    /*
     * Destructor.
     */
    virtual
    ~RWMimeStringPartImp(void);

    /*
     * Returns self's body as a string.
     */
    RWCString
    getBody(void) const;

    /*
     * Sets self's body to \a body.
     * Does not validate \a body.
     */
    void
    setBody(const RWCString& body);

    /*
     * Returns \c false to indicate that self is \e not multipart.
     */
    virtual bool
    isMultipart(void) const;

    /*
     * Compare self to \a part, and return true if self is
     * logically equal to \a part.
     */
    virtual bool
    compareTo(const RWMimePartImp& part) const;

    /*
     * @internal
     * Double-dispatch comparison.  Virtual function for
     * comparing RWMimeStringPartImp part types.
     */
    virtual bool
    compareTo(const RWMimeStringPartImp& part) const;

    /*
     * @internal
     * Double-dispatch comparison.  Virtual function for
     * comparing RWMimeMultipartImp part types.
     */
    virtual bool
    compareTo(const RWMimeMultipartImp& part) const;

private:
    RWCString          body_;
};

#endif  // rw_mime_RWMimeStringPartImp_h
