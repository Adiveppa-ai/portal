#ifndef rw_mime_RWMimeVersionHeader_h
#define rw_mime_RWMimeVersionHeader_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeVersionHeader.h#1 $
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
#include <rw/mime/pkgdefs.h>

/**
 * \ingroup mime_package
 *
 * \brief
 * Represents the \c MIME-Version header of a MIME message.
 *
 * RWMimeVersionHeader represents the MIME-Version header of a MIME message.
 * The header states the version of MIME to which the message conforms. The
 * MIME specification requires that each MIME message contain a MIME-Version
 * header.
 *
 * \note
 * RFC 2045 specifies a version number of 1.0.
 *
 * An instance of this class is a handle to a private, reference-counted
 * body.
 *
 * @reference
 * RWMimeVersionHeader conforms to the MIME-Version header requirements
 * specified in RFC 2045, Section 4 (p.8).
 */
class RW_MIME_GLOBAL RWMimeVersionHeader
    : public RWMimeHeader
{
public:

    /**
     * Static constant string containing \c "MIME-Version", the label for a
     * MIME-Version header. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    static const RWCString Label;

    /**
     * Default constructor. Constructs a header with the label
     * \c "MIME-Version" and the value \c "1.0".
     */
    RWMimeVersionHeader(void);

    /**
     * Constructs a header with the label \c "MIME-Version" and a value
     * constructed from \a majorVersion and \a minorVersion. For example,
     * when \a majorVersion is \c 1 and \a minorVersion is \c 0, the new
     * header contains the value \c "1.0".
     */
    RWMimeVersionHeader(unsigned majorVersion, unsigned minorVersion);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeVersionHeader(const RWMimeVersionHeader& second);

    /**
     * Conversion constructor. Constructs a new handle to the body \a second
     * refers to. Throws RWMimeError if \a second does not have the label
     * \c "MIME-Version".
     */
    RWMimeVersionHeader(const RWMimeHeader& second);

    /**
     * Assignment operator. Makes self a copy of \a second.
     */
    RWMimeVersionHeader&
    operator=(const RWMimeVersionHeader& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeVersionHeader(void);

    /**
     * Returns the major version number of self's value. For example, when
     * self's value is \c "1.0", returns \c 1.
     */
    unsigned
    getMajorVersion(void) const;

    /**
     * Returns the major version number of self's value. For example, when
     * self's value is \c "1.0", returns \c 0.
     */
    unsigned
    getMinorVersion(void) const;

    /**
     * Sets the value of self to \a majorVersion and \a minorVersion. For
     * example, when \a majorVersion is \c 1 and \a minorVersion is \c 0,
     * self's value is set to \c "1.0".
     */
    void
    setVersion(unsigned majorVersion, unsigned minorVersion);

protected:

    /**
     * Returns \c true if \a label matches \c "MIME-Version", \c false
     * otherwise. The comparison is case-insensitive. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    virtual bool
    checkLabel(const RWCString& label) const;

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeVersionHeaderImp&
    body(void) const;
};


#endif //rw_mime_RWMimeVersionHeader_h_
