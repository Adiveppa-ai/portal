#ifndef RW_TOOLS_STDLIB_H
#define RW_TOOLS_STDLIB_H

/**********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/tools/stdlib.h#1 $
 *
 **********************************************************************
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

#include <rw/defs.h>
#include <rw/tools/ctype.h>
#include <rw/tools/traits/RWTIsSigned.h>
#include <limits>
#include <errno.h>

/**
 * \internal
 * \ingroup cstdlib
 *
 * Converts the string pointed to by \a str to a double, stopping at the
 * first character that is not a part of the double representation (see
 * below). If \a endptr is not null, it will be set to the first character
 * that is not a part of the double representation. Leading whitespace is
 * consumed before the conversion begins.
 *
 * A valid double string representation consists of an optional plus \c '+'
 * or minus \c '-' sign, followed by a non-empty sequence of digits which
 * may include a decimal separator \c '.', followed by an optional exponent
 * string. An exponent string is represented as a string beginning with
 * either \c 'e' or \c 'E', followed by an optional plus \c '+' or minus
 * \c '-' sign, followed by a non-empty sequence of digits.
 *
 * \note
 * This function differs from the C Standard Library function \b strtod()
 * in that it does not take the current locale into account. This
 * function's behavior is consistent with the "C" locale. This function
 * does not support parsing strings containing hexadecimal digits, or
 * representations of infinity and NaN.
 */
RW_TOOLS_SYMBOLIC double rw_strtod_nolocale(const char* str, char** endptr);

/**
 * \internal
 * \ingroup cstdlib
 *
 * Calls wcstombs_s on platforms where it is available, otherwise calls
 * wcstombs.
 *
 * \note
 * In release builds, wcstombs is preferred. wcstombs_s will be invoked in
 * release builds if RW_SECURE_CHECK is defined.
 */
RW_TOOLS_SYMBOLIC int rw_wcstombs_s(size_t* ret_value, char* mbstr, size_t size_in_bytes, const wchar_t* wcstr, size_t count);


template <bool>
inline
int rw_strtox_parse_sign(const char*& s)
{
    int sign = 1;

    // Optional + or -
    if (*s == '-') {
        ++s;
        sign = -1;
    }
    else if (*s == '+') {
        ++s;
    }

    return sign;
}

template <>
inline
int rw_strtox_parse_sign<false>(const char*&)
{
    return 1;
}

/**
 * \internal
 * \ingroup cstdlib
 *
 * Converts the string pointed to by \a s to an integral value of type
 * \c R, stopping at the first character that is not part of a valid
 * integer representation.
 *
 * For signed integral types, the valid integer representation consists
 * of optional opening whitespace, an optional \c '+' or \c '-' sign,
 * followed by a non-empty sequence of digits.
 *
 * For unsigned integral types, the valid representation consists of
 * optional opening whitespace followed by a non-empty sequence of digits.
 *
 * If no digits are parsed and \a endp is non-null, \a endp will be
 * updated to point to the beginning of the input sequence \a s.
 * Otherwise, a non-null \a endp will point to the character in the
 * input sequence that was not valid for the representation.
 *
 * \return If no number was parsed, this function sets errno to EINVAL
 * and returns 0. If a number is parsed, but the value was too large
 * to be stored into the return type, errno is set to ERANGE and the
 * nearest legal value for the given type is returned. Otherwise, errno
 * is left unchanged, and the parsed value is returned.
 *
 * \note This function differs from the C Standard Library \b strtol()
 * family of functions in that it does not take the current locale into
 * account and it only parses decimal values.
 */
template <typename R>
R rw_strtox_nolocale(const char* s, char** endp)
{
    RW_ASSERT(s != 0);

    const char* const save = s;

    // skip leading whitespace
    while (rw_isspace_nolocale(*s)) {
        ++s;
    }

    // parse the sign
    const int sign = rw_strtox_parse_sign<RWTIsSigned<R>::value>(s);

    bool conversion_performed = false;

    // now, while we have digits, change retval
    R retval = 0;

    while ('0' <= *s && *s <= '9') {

        const R prev = retval;
        retval = static_cast<R>(10 * retval + *s++ - '0');

        if (retval < prev) {
            const R min = (std::numeric_limits<R>::min)();
            const R max = (std::numeric_limits<R>::max)();

            // positive number overflow
            if (0 < sign) {
                errno = ERANGE;
                retval = max;
            }

            // two's-compliment representation has an additional negative value. one
            // past the largest possible value is the largest negative value. if we
            // land on this value it is possible that this is by design. i.e., if we
            // are parsing -128, we eat the sign, and then parse 128. 128 is not a
            // representable 8-bit signed value, so we have -128 and we will end up
            // in this block of code.
            //
            // if we are in this block, and `retval' is not equal to `min', then we
            // have completely overflowed. if `retval' is equal to `min' we have not
            // yet overflowed. look at the next character to see if we would have.
            else if (retval != min || ('0' <= *s && *s <= '9')) {
                errno = ERANGE;
                retval = min;
            }

            // consume the remainder of the subsequence
            if (endp) {

                while ('0' <= *s && *s <= '9') {
                    ++s;
                }

                *endp = const_cast<char*>(s);
            }

            return retval;
        }

        conversion_performed = true;
    }


    if (!conversion_performed) {
        errno = EINVAL;

        if (endp) {
            *endp = const_cast<char*>(save);
        }

        return 0;
    }

    else if (endp) {
        *endp = const_cast<char*>(s);
    }

    return static_cast<R>(sign * retval);
}

#endif
