#ifndef __rw_http_RWHttpDate_h__
#define __rw_http_RWHttpDate_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpDate.h#1 $
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

#include <rw/http/pkgdefs.h>
#include <iosfwd>

class RWCString;

#include <rw/tools/datetime.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Helper class to convert an RWDateTime instance to a date from a string
 * and vice versa, conforming to the HTTP/1.1 specification.
 *
 * RWHttpDate maintains the date and time. It outputs the date as a string
 * that conforms to the HTTP/1.1 date specification.
 */
class RW_HTTP_GLOBAL RWHttpDate
{

public:

    /**
     * Constructs a default RWHttpDate object. Internal date and time are
     * initialized to the current date and time, respectively.
     */
    RWHttpDate(void);

    /**
     * Constructs an RWHttpDate object with the internal date and time set
     * to those in \a dt.
     */
    RWHttpDate(const RWDateTime& dt);

    /**
     * Constructs an RWHttpDate object with the input \a str. The \a str
     * argument must be an HTTP/1.1-compliant date string. The \a str is
     * parsed for date and time, and the internals are set to the result. If
     * \a str cannot be parsed, an invalid date is constructed.
     *
     * HTTP/1.1 defines the following formats as acceptable date strings:
     *
     * - Sun, 06 Nov 1994 08:49:37 GMT; RFC 822, updated by RFC 1123
     * - Sunday, 06-Nov-94 08:49:37 GMT; RFC 850, obsoleted by RFC 1036
     * - Sun Nov 06 08:49:37 1994; C++ Standard Library \b std::asctime()
     * format
     *
     * \note
     * RWHttpDate assumes a two-digit RFC 850 date that appears to be more
     * than 50 years in the future is in fact in the past. (This helps solve
     * the "year 2000" problem.)
     */
    RWHttpDate(const RWCString& str);

    /**
     * Returns the internal date and time formatted to comply with the
     * HTTP/1.1 specification. The RWCString should contain 7-bit US-ASCII
     * data. Throws RWInternalErr if isValid() is \c false.
     */
    RWCString asString() const;
    // outputs date in the format listed in the
    // HTTP/1.1 spec "Thu, 04 Jul 1996 08:22:37 GMT"

    /**
     * Returns an RWDateTime constructed on the date associated with the
     * RWHttpDate object.
     */
    RWDateTime
    getDate() const;

    /**
     * Sets the internal date of the RWHttpDate object from the string
     * \a str. The \a str argument must be an HTTP/1.1-compliant date
     * string. The \a str is parsed for date and time, and the internals are
     * set to the result. If \a str cannot be parsed, an invalid date is
     * constructed. The RWCString should contain 7-bit US-ASCII data.
     */
    void
    setDate(const RWCString& str);

    /**
     * Sets the internal date of the RWHttpDate object to the date and time
     * in \a dt.
     */
    void
    setDate(const RWDateTime& dt);

    /**
     * Returns \c true if the internal RWDateTime is not a sentinel value.
     */
    bool
    isValid() const;

private:

    RWDateTime dt_;
    static const RWLocaleSnapshot locale_;
};

inline
RWHttpDate::RWHttpDate()
{
    // RWHttpDate times do not contain milliseconds, so we need to
    // strip those off before using them.
    dt_ = RWDateTime(RWDateTime::setCurrentTime);
    dt_ = dt_ - dt_.milliSecond();
}

inline
RWHttpDate::RWHttpDate(const RWDateTime& dt)
    : dt_(dt - dt.milliSecond())
{
    // we strip the milliseconds from the RWDateTime so that compares
    // of RWHttpDates do not compare millisecond values as well.
}

inline
RWHttpDate::RWHttpDate(const RWCString& str)
{
    setDate(str);     // setDate converts from known HTTP date formats
}

inline RWDateTime
RWHttpDate::getDate() const
{
    return dt_;
}

inline void
RWHttpDate::setDate(const RWDateTime& dt)
{
    dt_ = dt - dt.milliSecond();
}

inline bool
RWHttpDate::isValid() const
{
    return !dt_.isSentinel();
}

/**
 * \relates RWHttpDate
 *
 * Comparison operators.
 */
inline bool
operator==(const RWHttpDate& date1, const RWHttpDate& date2)
{
    return date1.getDate() == date2.getDate();
}

/**
 * \relates RWHttpDate
 *
 * Comparison operators.
 */
inline bool
operator!=(const RWHttpDate& date1, const RWHttpDate& date2)
{
    return date1.getDate() != date2.getDate();
}

/**
 * \relates RWHttpDate
 *
 * Comparison operators.
 */
inline bool
operator<(const RWHttpDate& date1, const RWHttpDate& date2)
{
    return date1.getDate() < date2.getDate();
}

/**
 * \relates RWHttpDate
 *
 * Comparison operators.
 */
inline bool
operator<=(const RWHttpDate& date1, const RWHttpDate& date2)
{
    return date1.getDate() <= date2.getDate();
}

/**
 * \relates RWHttpDate
 *
 * Comparison operators.
 */
inline bool
operator>(const RWHttpDate& date1, const RWHttpDate& date2)
{
    return date1.getDate() > date2.getDate();
}

/**
 * \relates RWHttpDate
 *
 * Comparison operators.
 */
inline bool
operator>=(const RWHttpDate& date1, const RWHttpDate& date2)
{
    return date1.getDate() >= date2.getDate();
}

/**
 * \relates RWHttpDate
 *
 * Outputs an RWHttpDate object to an \c std::ostream.
 */
RW_HTTP_SYMBOLIC std::ostream&
operator<<(std::ostream& s, const RWHttpDate& d);

/**
 * \relates RWHttpDate
 *
 * Restores an RWHttpDate from an \c std::istream into \a d, replacing the
 * previous contents of \a d.
 */
RW_HTTP_SYMBOLIC std::istream&
operator>>(std::istream& s, RWHttpDate& d);

#if !defined(RW_DISABLE_DEPRECATED)
typedef RW_DEPRECATE_TYPE("Use RWHttpDate instead") RWHttpDate RWIHttpDate;
#endif

#endif // __rw_http_RWHttpDate_h__
