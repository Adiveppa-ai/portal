#ifndef rw_mime_RWMimeVersionHeaderImp_h
#define rw_mime_RWMimeVersionHeaderImp_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeVersionHeaderImp.h#1 $
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
 * RWMimeVersionHeaderImp represents the MIME-Version header of a
 * MIME message. The header states the version of MIME to which
 * the message conforms. The MIME specification requires that each
 * MIME message contain a MIME-Version header.
 *
 * @note
 * RFC 2045 specifies a version number of \c "1.0".
 *
 * @reference
 * RWMimeVersionHeaderImp conforms to the "MIME-Version" header requirements
 * specified in RFC 2045, Section 4 (p.8).
 */

class RW_MIME_GLOBAL RWMimeVersionHeaderImp
    : public RWMimeHeaderImp
{
public:

    /*
     * Default constructor.
     * Constructs a header with the label \c "MIME-Version" and the value
     * \c "1.0".
     */
    RWMimeVersionHeaderImp(void);

    /*
     * Copy constructor.
     */
    RWMimeVersionHeaderImp(const RWMimeVersionHeaderImp& second);

    /*
     * Destructor.
     */
    virtual
    ~RWMimeVersionHeaderImp(void);

    /*
     * Gets the self's value, as it should appear in a MIME message.
     */
    virtual RWCString
    getValueAsString(void) const;

    /*
     * Sets the value of self to \a value.  Throws
     * RWMimeParseError if \a value does not consist
     * of two numbers separated by a period.
     */
    virtual void
    setValueFromString(const RWCString& value);

    /*
     * Returns the major version number of self's value.  For example,
     * when self's value is \c "1.0", returns \c 1.
     */
    unsigned
    getMajorVersion(void) const;

    /*
     * Returns the minor version version number of self's value.  For example,
     * when self's value is \c "1.0", returns \c 0.
     */
    unsigned
    getMinorVersion(void) const;

    /*
     * Sets the value of self to a string constructed from \a majorVersion
     * and \a minorVersion.  For example, when \a majorVersion is \c 1 and
     * \a minorVersion is \c 0, self's value is set to \c "1.0".
     */
    void
    setVersion(unsigned majorVersion, unsigned minorVersion);

    /*
     * static make function for creating a RWMimeHeader with an
     * RWMimeUnstructuredHeaderImp.
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
     * Override compareValueTo to compare the values of major_
     * and minor_ directly.
     */
    virtual bool
    compareValueTo(const RWMimeHeaderImp& second) const;

private:
    unsigned    major_;
    unsigned    minor_;
};


#endif //rw_mime_RWMimeVersionHeaderImp_h_
