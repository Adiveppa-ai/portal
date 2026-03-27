#ifndef rw_mime_RWMimeContentIdHeader_h
#define rw_mime_RWMimeContentIdHeader_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeContentIdHeader.h#1 $
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
#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents the Content-ID header of a MIME part.
 *
 * RWMimeContentIdHeader represents the Content-ID header of a MIME part.
 * The header is designed to allow external references to a MIME part.
 * Therefore, the MIME format requires that the value of the header be
 * world-unique. For example, a MIME message might contain the Content-ID
 * header:
 *
 * \code
 * Content-ID: <part.0014@roguewave.example>
 * \endcode
 *
 * In general, a MIME message contains one Content-ID header at the top
 * level of the message. For \c multipart/alternative messages, the MIME
 * specification suggests that each alternative have a different Content-ID
 * header unless all alternatives contain equivalent information.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeContentIdHeader conforms to the Content-ID header requirements
 * specified in RFC 2045, Section 7 (p. 26). For a discussion of Content-ID
 * and \c multipart/alternative messages, see RFC 2046 Section 5.1.4 (p.
 * 24).
 */
class RW_MIME_GLOBAL RWMimeContentIdHeader
    : public RWMimeHeader
{
public:

    /**
     * Static constant string containing \c "Content-ID", the label for a
     * Content-ID header. The RWCString should contain 7-bit US-ASCII data.
     */
    static const RWCString Label;

    /**
     * Default constructor. Constructs a Content-ID header with the empty
     * string for a value. Since the empty string is not world-unique, a
     * default-constructed RWMimeContentIdHeader does not meet the
     * requirements of the MIME format.
     *
     * \note
     * A header with an empty value does not meet the requirements for a
     * Content-ID header.
     */
    RWMimeContentIdHeader(void);

    /**
     * Constructs a Content-ID header with the value \a id. The RWCString
     * should contain 7-bit US-ASCII data.
     *
     * \note
     * This constructor cannot verify that the provided \a id is
     * world-unique.
     */
    RWMimeContentIdHeader(const RWCString& id);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeContentIdHeader(const RWMimeContentIdHeader& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if \a second does not have the label
     * \c "Content-ID".
     */
    RWMimeContentIdHeader(const RWMimeHeader& second);

    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeContentIdHeader&
    operator=(const RWMimeContentIdHeader& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeContentIdHeader(void);

    /**
     * Returns the content ID value of this header. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString
    getId(void) const;

    /**
     * Sets the content ID value of this header. The RWCString should
     * contain 7-bit US-ASCII data.
     *
     * \note
     * This function cannot verify that the provided id is world-unique.
     */
    void
    setId(const RWCString& id);

protected:

    /**
     * Returns \c true if label matches \c "Content-ID", \c false otherwise.
     * The comparison is case-insensitive. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    virtual bool
    checkLabel(const RWCString& label) const;

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeStructuredHeaderImp&
    body(void) const;
};


#endif // rw_mime_RWMimeContentIdHeader_h
