#ifndef RW_CURRENCY_INTUTIL_CC
#define RW_CURRENCY_INTUTIL_CC

/*--------------------------------------------------------------
 *
 * Implementation of template-based utility functions used
 * by RWMultiPrecisionInt.
 *
 * $Id: //spro/rel2016.1/rw/currency/intutil.cc#1 $
 *
 * Copyright (c) 1993-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 *--------------------------------------------------------------*/

/* for backward compatibility */
#ifndef RW_MONEY_INTUTIL_CC
#  define RW_MONEY_INTUTIL_CC
#endif

#include <rw/currency/mpint.h>
#include <rw/rstream.h>
#include <rw/tools/pointer.h>

#if defined(RW_MNY_NO_NEW_HEADER)
#  include <limits.h> // CHAR_BIT
#else
#  include <climits>
#endif


long RW_DCML_MEMBER_EXPORT rw_rint(double x);

// The following macro is used inside the two next template functions
// to generate a static const double for use in repeated divides
#define RW_LARGEST_POW_10(lgshft) \
   ((lgshft ==  3) ? 1000L /* 16-bit systems  (8-bit halfwords)*/ \
  :((lgshft ==  6) ? 1e+6  /* 32-bit systems (16-bit halfwords)*/ \
  :((lgshft == 10) ? 1e+10 /* 64-bit systems (32-bit halfwords)*/ \
  : (lgshft == 20) ? 1e+20 /*128-bit systems (64-bit halfwords)*/ \
  :rw_rint(::pow(10.0,(double)lgshft))))) /*Any other-bit systems */

#define RW_LOG2 0.301029995664


// This utility function repeatedly divides the integer represented in a
// halfword array by ten.  The number of divides is indicated by *nshift*.
template< class T >
unsigned int decimalShiftRight(T* hw_array,
                               unsigned int hw_arraysize,
                               unsigned int nshift)
{
    // largest_shift is technically log10(pow(2,HWDigitSize)-1),
    // however, this value is approximately equal to
    // log10(pow(2,HWDigitSize)), which can be simplified to
    //   HWDigitSize * log 2.
    // Using this value is faster than using log10(), and since the
    // result is truncated, there is no extra inaccuracy, even for
    // 16-bit systems (8-bit halfwords). log 2 == .301029995664
    //
    static const unsigned int largest_shift =
        (unsigned int)((RWIntutilConstants<T>::HWDigitSize) * RW_LOG2);

    // by using predefined values for known "bitnesses", we can can
    // make the computation of largest_pow10 a little more efficient by
    // not calling pow(). For weird platforms, we still use pow().
    //

    static const T largest_pow10 =
#if defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x005
        RW_LARGEST_POW_10(largest_shift);
#else
        (T)(RW_LARGEST_POW_10(largest_shift));
#endif

    unsigned int i, nshifted = 0, divisor = static_cast<unsigned int>(largest_pow10);

    while (nshift > 0) {
        // Determine the divisor.
        if (nshift >= largest_shift) {
            nshift -= largest_shift;
            nshifted += largest_shift;
        }
        else if (nshift > 0) {
            divisor = 1U;
            for (i = 0; i < nshift; ++i) {
                divisor *= 10U;
            }
            nshifted += nshift;
            nshift = 0;
        }

        // Fast division algorithm.
        T fast_remainder = 0;
        for (i = 0; i < hw_arraysize; i++) {
            fast_remainder = (fast_remainder << RWIntutilConstants<T>::HWDigitSize) +
                             hw_array[i];
            hw_array[i] = fast_remainder / divisor;
            fast_remainder %= divisor;
        }
    }
    return nshifted;
}

// This utility function repeatedly divides the integer represented in a
// halfword array by ten.  Upon exit, it is guaranteed that the integer fits
// into a halfword array half the size of the one passed in.
template< class T >
unsigned int decimalShiftRightToHalfSize(T* hw_array, unsigned int hw_arraysize, unsigned int nshift)
{
    // largest_shift is technically log10(pow(2,HWDigitSize)-1),
    // however, this value is approximately equal to
    // log10(pow(2,HWDigitSize)), which can be simplified to
    //   HWDigitSize * log 2.
    // Using this value is faster than using log10(), and since the
    // result is truncated, there is no extra inaccuracy, even for
    // 16-bit systems (8-bit halfwords). log 2 == .301029995664
    //
    static const unsigned int largest_shift =
        (unsigned int)((RWIntutilConstants<T>::HWDigitSize) * RW_LOG2);

    // by using predefined values for known "bitnesses", we can can
    // make the computation of largest_pow10 a little more efficient by
    // not calling pow(). For weird platforms, we still use pow().
    //

    static const T largest_pow10 =
#if defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x005
        RW_LARGEST_POW_10(largest_shift);
#else
        (T)(RW_LARGEST_POW_10(largest_shift));
#endif

    unsigned int i, nshifted = 0, divisor = static_cast<unsigned int>(largest_pow10);

    // The second condition below is necessary because always knowing the exact
    // number of decimal shifts is hard; we know we're within one halfword digit
    // of having a good answer when nshift is zero. The third test checks that
    // will eventually become the sign bit must be zero, along with all more
    // significant bits.
    T one_currency = 1;
    while (nshift > 0                          ||
            (hw_array[(hw_arraysize / 2) - 1] != 0) ||
            (hw_array[(hw_arraysize / 2)] & (one_currency << (RWIntutilConstants<T>::HWDigitSize - one_currency)))) {
        // Determine the divisor.
        if (nshift >= largest_shift) {
            nshift -= largest_shift;
            nshifted += largest_shift;
        }
        else if (nshift > 0) {
            divisor = 1U;
            for (i = 0; i < nshift; ++i) {
                divisor *= 10U;
            }

            nshifted += nshift;
            nshift = 0;
        }
        else {
            divisor = 10;
            nshifted++;
        }

        // Fast division algorithm.
        T fast_remainder = 0;
        for (i = 0; i < hw_arraysize; i++) {
            fast_remainder = (fast_remainder << RWIntutilConstants<T>::HWDigitSize) +
                             hw_array[i];
            hw_array[i] = fast_remainder / divisor;
            fast_remainder %= divisor;
        }
    }
    return nshifted;
}

template< class T >
void printAsBinary(const T* digits, const size_t numDigits)
{
    unsigned bitsPerDigit = sizeof(T) * CHAR_BIT;
    int numBits = numDigits * bitsPerDigit;
    RWTScopedPointer<char[]> binaryDigits(new char[numBits + 1]);
    T temp;
    size_t i, j, bdigit;
    for (i = 0; i < numDigits; i++) {
        bdigit = i * bitsPerDigit + bitsPerDigit - 1;
        for (j = 0; j < bitsPerDigit; j++) {
            temp = (digits[i] >> j) & ~(~0 << 1);
            if (temp == 1) {
                binaryDigits[bdigit] = '1';
            }
            else {
                binaryDigits[bdigit] = '0';
            }
            --bdigit;
        }
    }

    binaryDigits[numBits] = '\0';
    std::cout << binaryDigits.get() << std::endl;
}

#undef RW_LARGEST_POW_10
#undef RW_LOG2

#endif // RW_CURRENCY_INTUTIL_CC
