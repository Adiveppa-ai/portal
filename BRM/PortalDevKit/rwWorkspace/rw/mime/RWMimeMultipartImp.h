#ifndef rw_mime_RWMimeMultipartImp_h
#define rw_mime_RWMimeMultipartImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeMultipartImp.h#1 $
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
#include <rw/tvslist.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/*
 * @internal
 *
 * This class provides the implementation of an RWMimeMultipart object.
 * There's no need for an application to use this class directly; a
 * handle provides appropriate access.
 */
class RW_MIME_GLOBAL RWMimeMultipartImp
    : public RWMimePartImp
{
    typedef RWTValSlist<RWMimePart>   RWMimePartList;

public:

    /*
     * Default constructor.
     * Constructs a MIME part with no headers and no body.
     */
    RWMimeMultipartImp(void);

    /*
     * Copy constructor. Constructs a new MIME part as a deep
     * copy of \a second.
     */
    RWMimeMultipartImp(const RWMimeMultipartImp& second);

    /*
     * Assignment operator. Makes self a deep copy of \a second.
     */
    RWMimeMultipartImp&
    operator=(const RWMimeMultipartImp& second);

    /*
     * Destructor.
     */
    virtual
    ~RWMimeMultipartImp(void);

    /*
     * Returns self's body as a string.
     *
     * @throw RWMimeParseError Thrown if the function cannot create a valid
     * MIME part body.
     */
    virtual RWCString
    getBody(void) const;

    /*
     * Sets self's body to \a body.
     *
     * @throw RWMimeParseError Thrown if the function cannot process
     * \a body as a multipart body.
     */
    virtual void
    setBody(const RWCString& body);

    /*
     * Returns \c true to indicate that self is multipart.
     */
    virtual bool
    isMultipart(void) const;

    /*
     * Returns self's preamble.
     */
    RWCString
    getPreamble(void) const;

    /*
     * Sets self's preamble to \a preamble.
     */
    void
    setPreamble(const RWCString& preamble);

    /*
     * Returns the number of parts self contains.
     */
    size_t
    getPartCount(void) const;

    /*
     * Retrieves the MIME part located at \a position.
     *
     * @throw RWBoundsErr Thrown if \a position is greater than or equal to
     * getPartCount().
     */
    RWMimePart
    getPart(size_t position) const;

    /*
     * Inserts \a part at the end of self's part list.
     */
    void
    insertPart(const RWMimePart& part);

    /*
     * Inserts \a part into self's part list at \a position.
     *
     * @throw RWBoundsErr Thrown if \a position is greater than getPartCount().
     */
    void
    insertPartAt(size_t position, const RWMimePart& part);

    /*
     * Removes the part located at \a position from self's part list.
     *
     * @throw RWBoundsErr Thrown if \a position is greater than or equal to
     * getPartCount().
     */
    void
    removePartAt(size_t position);

    /*
     * Returns the position of the first part in the list that
     * contains a header matching \a header.  Begins searching at
     * \a start. If no such part is present, returns #RW_NPOS.
     * Compares both the label and value of headers, using a
     * case-insensitive string comparison for labels, a case-sensitive
     * string comparison for values.
     */
    size_t
    findPart(const RWMimeHeader& header, size_t start = 0) const;

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
    RWCString          preamble_;
    RWMimePartList     parts_;
};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif  // rw_mime_RWMimeMultipartImp_h
