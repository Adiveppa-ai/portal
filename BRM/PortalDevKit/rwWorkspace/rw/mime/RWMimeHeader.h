#ifndef rw_mime_RWMimeHeader_h
#define rw_mime_RWMimeHeader_h

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/mime/RWMimeHeader.h#1 $
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

#include <rw/mime/fwd.h>
#include <rw/mime/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>

/*
 * Notes:
 *
 * All header field names MUST be composed of printable characters in
 * the US-ASCII character set, excluding colon. (RFC 2822 2.2 p. 7).
 *
 * All header field bodies MUST be composed of characters in the
 * US-ASCII character set, excluding CR (0x13) and LF (0x10).
 */

/**
 * \ingroup mime_package
 *
 * \brief
 * Base class for classes that represent message headers as defined in the
 * Internet Message format specification (RFC 2822).
 *
 * RWMimeHeader is a base class for classes that represent message headers
 * as defined in the Internet Message format specification (RFC 2822). A
 * header consists of a \e label and a \e value. MIME requires that both the
 * label and value contain only printable characters in the US-ASCII
 * character set. The name may not contain a colon. To create a header value
 * in another character set, encode the value according to the guidelines in
 * RFC 2047.
 *
 * The label appears first in the header, and is separated from the value by
 * a colon. So, the header line
 *
 * \code
 * From: Rudi Marquez <rudi_marquez@roguewave.com>
 * \endcode
 *
 * contains the label \c From, a colon as a separator, and the value
 *
 * \code
 * Rudi Marquez <rudi_marquez@roguewave.com>
 * \endcode
 *
 * The Internet Message Format does not define the structure or meaning of a
 * value. Therefore, RWMimeHeader does not define an interface for working
 * with a header value. Just as each individual header in the specification
 * defines the structure and semantics of its value, each derived class
 * implements its own interface for working with the header value.
 *
 * An instance of RWMimeHeader is a handle to a private, reference-counted
 * body. Note that the body is always a specific header implementation.
 *
 * Classes that contain MIME headers collect the headers as instances of
 * RWMimeHeader. Each derived class contains a conversion constructor which
 * creates a new derived-class handle to the implementation of the
 * RWMimeHeader. Conversion happens automatically when an RWMimeHeader is
 * assigned to a handle of the appropriate type. For example,
 *
 * \code
 * // RWMimePart part contains a MIME-Version header.
 * size_t index = part.findHeader(RWMimeVersionHeader::Label);
 * if (index != RW_NPOS)
 * {
 *   RWMimeVersionHeader versionHdr = part.getHeader(index);
 *   // ...
 * }
 * \endcode
 *
 * In the code above, the RWMimePart::getHeader() function returns an
 * RWMimeHeader. Because RWMimeVersionHeader provides a conversion
 * constructor from RWMimeHeader, the compiler automatically invokes that
 * conversion constructor. The result is a completely typesafe assignment;
 * no downcast is required. The conversion is also efficient, since the
 * conversion constructor simply creates a new handle to the existing
 * implementation.
 *
 * @reference
 * RWMimeHeader conforms to the header requirements specified in Section 2.2
 * (p. 7) of RFC 2822, the Internet Message Format specification. RFC 2822
 * is an update of RFC 822, which originally defined the format for Internet
 * message headers.
 */
class RW_MIME_GLOBAL RWMimeHeader
    : public RWHandleBase
{
public:

    /*
     * The underlying implementation is created by the default functor
     * registered in the RWMimeHeaderFactory.
     */
    /**
     * Default constructor. Constructs a header with an empty label and an
     * empty value.
     *
     * \note
     * A header with an empty label and an empty value does not meet the
     * requirements of an Internet Message Format header.
     */
    RWMimeHeader(void);

    /**
     * Constructs a header with the given \a label and an empty value. Does
     * not verify that the string provided meets the requirements for an
     * Internet Message Format header. The RWCString should contain 7-bit
     * US-ASCII data.
     *
     * \note
     * A header with an empty value does not meet the requirements of an
     * Internet Message Format header.
     */
    RWMimeHeader(const RWCString& label);

    /**
     * Copy constructor. Constructs a new handle to the body \a second
     * refers to.
     */
    RWMimeHeader(const RWMimeHeader& second);

    /*
     * @internal
     * Construct a RWMimeHeader with implementation \a imp.
     */
    RWMimeHeader(RWMimeHeaderImp* imp);


    /**
     * Assignment operator. Makes self a handle identical to \a second.
     */
    RWMimeHeader&
    operator=(const RWMimeHeader& second);

    /**
     * Destructor.
     */
    virtual
    ~RWMimeHeader(void);

    /**
     * Equality operator. Returns \c true if \a first is equal to \a second,
     * \c false otherwise. Uses a case-insensitive comparison for labels. If
     * the labels match, compares the values as appropriate for the specific
     * header type.
     */
    friend RW_MIME_SYMBOLIC bool
    operator==(const RWMimeHeader& first, const RWMimeHeader& second);

    /**
     * Inequality operator. Returns \c true if \a first is not equal to
     * \a second, \c false otherwise. Uses a case-insensitive comparison for
     * labels. If the labels match, compares the values as appropriate for
     * the specific header type.
     */
    friend RW_MIME_SYMBOLIC bool
    operator!=(const RWMimeHeader& first, const RWMimeHeader& second);

    /**
     * Returns the label of this header. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString
    getLabel(void) const;

    /*
     * Returns this header as a string. Throws RWMimeError
     * if self cannot be represented as a valid header (for example,
     * if self has no value).
     */
    /**
     * Returns this header as a string. Throws RWMimeError if self cannot be
     * represented as a valid header. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString
    asString(void) const;

    /**
     * Populates self with the contents of \a headerString. Throws
     * RWMimeParseError if the function cannot parse \a headerString as a
     * valid header. In derived classes, throws RWMimeError if the label in
     * \a headerString is not a valid label for the header that the class
     * represents. The RWCString should contain 7-bit US-ASCII data.
     */
    void
    fromString(const RWCString& headerString);

    /*
     * Creates a copy of the body, and returns a handle to the new body.
     */
    RWMimeHeader
    copy(void) const;

protected:

    /**
     * Returns \c true. Since RWMimeHeader does not represent any specific
     * header, this class imposes no special requirements on a label. In
     * RWMimeHeader this function returns \c true without examining
     * \a label. Derived classes that represent specific headers may require
     * specific values for a label.
     */
    virtual bool
    checkLabel(const RWCString& label) const;

    /**
     * Returns a reference to the underlying implementation.
     */
    RWMimeHeaderImp&
    body(void) const;

private:

    /*
     * @internal
     * Hiding RWHandleBase::operator<().
     */
    bool
    operator<(const RWHandleBase& second) const;
};


#endif // rw_mime_RWMimeHeader_h
