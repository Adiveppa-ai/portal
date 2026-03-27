/**********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/tools/timetupleoffsetformatter.h#1 $
 *
 * Copyright (c) 1989-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 **********************************************************************/

#ifndef RW_TOOLS_TIMETUPLEOFFSET_FORMATTER_H
#define RW_TOOLS_TIMETUPLEOFFSET_FORMATTER_H

#include <rw/cstring.h> // for RWCString
#include <rw/edefs.h>   // for rw_move

class RWLocale;
class RWTimeTupleOffset;

/**
 * \ingroup tools_date_and_time_group
 *
 * \brief
 * Formats a RWTimeTupleOffset based on a user-defined format.
 *
 * RWTimeTupleOffsetFormatter uses a \b strftime()-based format specification,
 * however not all \b strftime() format specifiers are supported, and some
 * have a different meaning than in \b strftime().
 *
 * The format specification may contain conversion specifications and literal
 * characters. A conversion specification consists of a leading '\%' character,
 * an optional format flag character, an optional field width, and a conversion
 * specification character to terminate. All other characters are considered
 * to be literals and are copied to the output directly. For example, the format
 * string \c '%+6Y' uses the format flag '+', a field width of 6, and the format
 * specification character 'Y'.
 *
 * The following table shows the conversion specification characters that may
 * be used with RWTimeTupleOffsetFormatter. In all cases, the behavior of the
 * format function is unspecified when the input tuple is not normalized.
 *
 * <table>
 * <tr>
 * <th><b>Conversion character</b></th>
 * <th><b>Meaning</b></th>
 * </tr>
 * <tr>
 * <td>\c \%b</td>
 * <td>Replaced by the locale's abbreviated month name. Month values outside the range [1,12] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%B</td>
 * <td>Replaced by the locale's full month name. Month values outside the range [1,12] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%C</td>
 * <td>Replaced by the year divided by 100 and truncated to an integer, as a decimal number. Year values outside the range [INT_MIN + 1,INT_MAX] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%d</td>
 * <td>Replaced by the day of the month as a decimal number [01,31]. Day of month values outside the range [1,31] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%e</td>
 * <td>Replaced by the day of the month as a decimal number [1,31]; a single digit is preceded by a space. Day of month values outside the range [1,31] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%m</td>
 * <td>Replaced by the month as a decimal number [01,12]. Month values outside the range [1,12] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%y</td>
 * <td>Replaced by the last two digits of the year as a decimal number [00,99]. Year values outside the range [INT_MIN + 1,INT_MAX] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%Y</td>
 * <td>Replaced by the year as a decimal number (for example, 1997). Year values outside the range [INT_MIN + 1,INT_MAX] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%F</td>
 * <td>Replaced by the fractional seconds as a decimal number [000000000000,999999999999]. Picosecond values outside the range [0,999999999999] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%H</td>
 * <td>Replaced by the hour (24-hour clock) as a decimal number [00,23]. Hour values outside the range [0,23] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%I</td>
 * <td>Replaced by the hour (12-hour clock) as a decimal number [01,12]. Hour values outside the range [0,23] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%M</td>
 * <td>Replaced by the minute as a decimal number [00,59]. Minute values outside the range [0,59] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%p</td>
 * <td>Replaced by the locale's equivalent of either a.m. or p.m., as if a call were made to locale.asString(..., 'p') for the provided locale, or RWLocale::global() if no locale is provided.</td>
 * </tr>
 * <tr><td>\c \%r</td>
 * <td>Replaced by the time in a.m. and p.m. notation, as if a call were made to locale.asString(..., 'r') for the provided locale, or RWLocale::global() if no locale is provided.</td>
 * </tr>
 * <tr><td>\c \%S</td>
 * <td>Replaced by the second as a decimal number [00,60]. The range is up to 60 to allow for occasional leap seconds. Second values outside the range [0,60] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%z</td>
 * <td>Replaced by the offset from UTC in the ISO 8601:2000 standard format (\c +hh:mm or \c -hh:mm). For example, \c -04:30 means 4 hours 30 minutes behind UTC (west of Greenwich). Offset values outside the range [-359999,359999] result in unspecified behavior.</td>
 * </tr>
 * <tr><td>\c \%\%</td>
 * <td>Replaced by \c \%</td>
 * </tr>
 * </table>
 *
 * Not all conversions support the flag or field width specifiers. The following
 * tables summarize the supported format options and their meanings for each
 * format specification character that supports them.
 *
 * <table>
 * <tr>
 * <th><b>Conversion character</b></th>
 * <th><b>Flag</b></th>
 * <th><b>Meaning</b></th>
 * </tr>
 * <tr>
 * <td rowspan="3">\c \%C</td>
 * <td>\c +</td>
 * <td>Sign should be output for positive values, but only when the specified field width or the number of digits to represent is greater than 2. A minimum field width must be specified.</td>
 * </tr>
 * <tr>
 * <td>\c 0</td>
 * <td>The output should be padded with 0 out to the minimum field width or 2, whichever is greater. A minimum field width must be specified.</td>
 * </tr>
 * <tr>
 * <td>\c &lt;width&gt;</td>
 * <td>An unsigned integer that specifies the minimum field width, including the sign.</td>
 * </tr>
 * <tr><td rowspan="3">\c \%Y</td>
 * <td>\c +</td>
 * <td>Sign should be output for positive values, but only when the specified field width or the number of digits to represent is greater than 4. A minimum field width must be specified.</td>
 * </tr>
 * <tr>
 * <td>\c 0</td>
 * <td>The output should be padded with 0 out to the minimum field width or 2, whichever is greater. A minimum field width must be specified.</td>
 * </tr>
 * <tr>
 * <td>\c &lt;width&gt;</td>
 * <td>An unsigned integer that specifies the minimum field width, including the sign.</td>
 * </tr>
 * <tr>
 * <td>\c \%F</td>
 * <td>\c &lt;width&gt;</td>
 * <td>An unsigned integer that specifies the field width. If the number of digits to represent is greater than this value, the result will be truncated.</td>
 * </tr>
 * </table>
 *
 * As an example, given the year \c 15, the full format specification \c "%+5Y" would
 * produce \c "+0015", and \c "%5Y" would produce \c "00015".
 *
 */
class RW_TOOLS_GLOBAL RWTimeTupleOffsetFormatter
{
public:
    /**
     * Constructs an RWTimeTupleOffsetFormatter with the format specification \a
     * format.
     */
    RWTimeTupleOffsetFormatter(const RWCString& format);

#if !defined(RW_NO_RVALUE_REFERENCES)
    /**
     * \copydoc RWTimeTupleOffsetFormatter(const RWCString&)
     *
     * \conditional
     * This method is only available on platforms with rvalue reference
     * support.
     */
    RWTimeTupleOffsetFormatter(RWCString&& format);
#endif

    /**
     * Copy constructor.
     */
    RWTimeTupleOffsetFormatter(const RWTimeTupleOffsetFormatter& rhs);

#if !defined(RW_NO_RVALUE_REFERENCES)
    /**
     * Move constructor.
     *
     * \conditional
     * This method is only available on platforms with rvalue reference
     * support.
     */
    RWTimeTupleOffsetFormatter(RWTimeTupleOffsetFormatter&& rhs);
#endif

    /**
     * Copy assignment operator.
     */
    RWTimeTupleOffsetFormatter& operator=(const RWTimeTupleOffsetFormatter& rhs);

#if !defined(RW_NO_RVALUE_REFERENCES)
    /**
     * Move assignment operator.
     *
     * \conditional
     * This method is only available on platforms with rvalue reference
     * support.
     */
    RWTimeTupleOffsetFormatter& operator=(RWTimeTupleOffsetFormatter&& rhs);
#endif

    /**
     * Destructor.
     */
    ~RWTimeTupleOffsetFormatter();

    /**
     * Generates a string representation of \a tt based on the current
     * format. For locale-specific behavior, the RWLocale returned by
     * RWLocale::global() is used.
     */
    RWCString operator()(const RWTimeTupleOffset& tt) const;

    /**
     * Generates a string representation of \a tt based on the current
     * format. For locale-specific behavior, \a locale is used.
     */
    RWCString operator()(const RWTimeTupleOffset& tt, const RWLocale& locale) const;

private:
    RWCString format_;
};

inline
RWTimeTupleOffsetFormatter::RWTimeTupleOffsetFormatter(const RWCString& format)
    : format_(format)
{
}

#if !defined(RW_NO_RVALUE_REFERENCES)

inline
RWTimeTupleOffsetFormatter::RWTimeTupleOffsetFormatter(RWCString&& format)
    : format_(rw_move(format))
{
}

#endif

inline
RWTimeTupleOffsetFormatter::RWTimeTupleOffsetFormatter(const RWTimeTupleOffsetFormatter& rhs)
    : format_(rhs.format_)
{
}

#if !defined(RW_NO_RVALUE_REFERENCES)

inline
RWTimeTupleOffsetFormatter::RWTimeTupleOffsetFormatter(RWTimeTupleOffsetFormatter&& rhs)
    : format_(rw_move(rhs.format_))
{
}

#endif

inline RWTimeTupleOffsetFormatter&
RWTimeTupleOffsetFormatter::operator=(const RWTimeTupleOffsetFormatter& rhs)
{
    format_ = rhs.format_;
    return *this;
}

#if !defined(RW_NO_RVALUE_REFERENCES)

inline RWTimeTupleOffsetFormatter&
RWTimeTupleOffsetFormatter::operator=(RWTimeTupleOffsetFormatter&& rhs)
{
    format_ = rw_move(rhs.format_);
    return *this;
}

#endif

inline
RWTimeTupleOffsetFormatter::~RWTimeTupleOffsetFormatter()
{
}

#endif
