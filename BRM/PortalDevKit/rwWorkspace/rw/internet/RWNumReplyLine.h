#ifndef __rw_internet_RWNumReplyLine_h__
#define __rw_internet_RWNumReplyLine_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/RWNumReplyLine.h#1 $
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

#include <rw/internet/pkgdefs.h>
#include <rw/cstring.h>

/**
 * \ingroup internet_basics_package
 *
 * \brief
 * Encapsulates a single numerical protocol reply as defined by the FTP and
 * SMTP protocols.
 *
 * RWNumReplyLine encapsulates a single numerical protocol reply as defined
 * by the FTP and SMTP protocols. An example reply line is \c 200 \c Command
 * \c Ok. If the 4th character of a reply line is the character \c - (dash)
 * instead of <tt>\<space\></tt>, the reply consists of multiple lines, with
 * \c - as the continuation marker. The continuation marker is used by
 * RWNumReply to build a complete reply that encapsulates an entire server
 * response.
 */
class RW_INTERNET_GLOBAL RWNumReplyLine
{
public:

    enum Family { INVALID,   VALID_1XX, VALID_2XX,
                  VALID_3XX, VALID_4XX, VALID_5XX
                };
    // enumerates all possible reply categories

    /**
     * Constructs a default RWNumReplyLine object. You need to use the
     * \c set method to initialize it.
     */
    RWNumReplyLine(void);

    /**
     * Constructs an RWNumReplyLine object using the input \a s. The
     * RWCString should contain 7-bit US-ASCII data.
     */
    RWNumReplyLine(const RWCString& s);

    /**
     * Returns \c true if self is equal to \a other.
     */
    bool
    operator==(const RWNumReplyLine& other) const;

    // STL fix : added < operator
    /**
     * Returns \c true if \a other is less than self.
     */
    bool
    operator<(const RWNumReplyLine& other) const;

    /**
     * Reads the reply line into self from \a data. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    void set(const RWCString& data);

    /**
     * Resets self back to the default state. The \c data member function
     * will still return the original reply line from the constructor or
     * from the \c set member function.
     */
    void reset(void);

#if !defined(RW_DISABLE_DEPRECATED)

    /**
     * \deprecated
     * As of SourcePro 1, use
     * \ref RWNumReplyLine::getStatusCode() "getStatusCode()" instead.
     *
     * Returns the 3-digit reply code.
     */
    RW_DEPRECATE_FUNC("Use RWNumReplyLine::getStatusCode() instead")
    unsigned int code(void) const;
#endif
    /**
     * Returns the 3-digit reply code.
     */
    unsigned int getStatusCode(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 1, use
     * \ref RWNumReplyLine::getStatusCode() "getStatusCode()" instead.
     *
     * Returns the reply code as an RWCString.
     */
    RW_DEPRECATE_FUNC("Use RWNumReplyLine::getStatusCode() instead")
    RWCString codeAsString(void) const;
#endif

    /**
     * Returns \c true if self is in the reply family. For more information
     * about reply families, see RFC 959.
     *
     * \note
     * Only one of these five methods returns true for any valid instance.
     */
    bool is1XX(void) const;

    /**
     * \copydoc is1XX()
     */
    bool is2XX(void) const;

    /**
     * \copydoc is1XX()
     */
    bool is3XX(void) const;

    /**
     * \copydoc is1XX()
     */
    bool is4XX(void) const;

    /**
     * \copydoc is1XX()
     */
    bool is5XX(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWNumReplyLine::getText() instead")
    RWCString text(void) const;
#endif
    /**
     * Returns the text portion of the reply line. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString getText(void) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWNumReplyLine::getData() instead")
    RWCString data(void) const;
#endif
    /**
     * Returns the raw text line that was parsed. The RWCString should
     * contain 7-bit US-ASCII data.
     *
     * \note
     * This is the only RWNumReplyLine method an application can call after
     * an exception is thrown.
     */
    RWCString getData(void) const;

    /**
     * Returns \c true if additional reply lines follow self in a whole
     * reply.
     */
    bool isContinued(void) const;

    /**
     * Returns \c true if the reply line is valid.
     */
    bool isValid(void) const;

private:

    /**
     * Outputs an RWNumReplyLine object to an \c std::ostream.
     *
     * \note
     * This class does not have an extraction (>>) operator.
     */
    friend RW_INTERNET_SYMBOLIC std::ostream&
    operator<<(std::ostream& str, const RWNumReplyLine& rl);

private:

    unsigned int code_;
    RWCString text_;
    RWCString data_;
    bool continued_;
    Family    attribute_;
};

#if !defined(RW_DISABLE_DEPRECATED)
inline unsigned int
RWNumReplyLine::code(void) const
{
    return getStatusCode();
}

inline RWCString
RWNumReplyLine::text(void) const
{
    return getText();
}

inline RWCString
RWNumReplyLine::data(void) const
{
    return getData();
}

typedef RW_DEPRECATE_TYPE("Use RWNumReplyLine instead") RWNumReplyLine RWINumReplyLine;
#endif

#endif // __rw_internet_RWNumReplyLine_h__
