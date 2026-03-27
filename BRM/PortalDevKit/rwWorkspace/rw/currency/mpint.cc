#ifndef RW_CURRENCY_MPINT_CC
#define RW_CURRENCY_MPINT_CC

/*-------------------------------------------------------------------------
 *
 * Implementation of RWMultiPrecisionInt and related classes.
 *
 * $Id: //spro/rel2016.1/rw/currency/mpint.cc#1 $
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
 *-------------------------------------------------------------------------
 */

/* for backward compatibility */
#ifndef RW_MONEY_MPINT_CC
#  define RW_MONEY_MPINT_CC
#endif

#include <rw/currency/mpint.h>
#include <rw/currency/mppot.h>
#include <rw/cstring.h>
#include <rw/rwfile.h>
#include <rw/vstream.h>

#if defined(RW_MNY_NO_NEW_HEADER)
#  include <limits.h>    // CHAR_BIT
#  include <string.h>
#else
#  include <climits>
#  include <cstring>
#endif


// Static data initialization
template <int S>
const rwuint32 RWMultiPrecisionInt<S>::decimalPrecision_ =
    static_cast<unsigned int>(log10(pow(2.0, (double)(S* sizeof(unsigned_type) * CHAR_BIT - 1))));

template <int S>
const rwint32 RWMultiPrecisionInt<S>::SIGNED_TYPE_MAX = RW_INT32_MAX;

template <int S>
const rwint32 RWMultiPrecisionInt<S>::SIGNED_TYPE_MIN = RW_INT32_MIN;

template <int S>
const rwuint32 RWMultiPrecisionInt<S>::UNSIGNED_TYPE_MAX = RW_UINT32_MAX;

template <int S>
const rwuint32 RWMultiPrecisionInt<S>::UNSIGNED_TYPE_MIN = rwuint32(0);

// Constructors
template <int S>
RWMultiPrecisionInt<S>::RWMultiPrecisionInt(double x)
{
    double nonnegX = x;
    bool isNegative = false;

    // Make the double precision value positive.
    if (x < 0.0) {
        isNegative = true;
        nonnegX = -x;
    }

    // Repeatedly divide the value by the wholeword digit radix;
    // place remainders in the unsigned array.
    static const double divisor = double(RWIntutilConstants<unsigned_type>::MaxDigitInt) + 1.0;
    for (int i = S - 2; i >= 0; --i) {
        trailingDigits_[i] = static_cast<unsigned_type>(fmod(nonnegX, divisor));
        nonnegX = floor(nonnegX / divisor);
    }

    // Make sure the remaining value will fit into a signed digit.
    if (nonnegX > SIGNED_TYPE_MAX) {
        *this = badValue();
        return;
    }
    else {
        leadDigit_ = static_cast<unsigned_type>(nonnegX);
    }

    // Set the correct sign.
    if (isNegative) {
        *this = -*this;
    }
}

// modified from previous
template <int S>
RWMultiPrecisionInt<S>::RWMultiPrecisionInt(long double x)
{
    long double nonnegX = x;
    bool isNegative = false;

    // Make the double precision value positive.
    if (x < 0.0L) {
        isNegative = true;
        nonnegX = -x;
    }

    // Repeatedly divide the value by the wholeword digit radix;
    // place remainders in the unsigned array.
    static const long double divisor = (long double)(RWIntutilConstants<unsigned_type>::MaxDigitInt) + 1.0L;
    for (int i = S - 2; i >= 0; --i) {
        trailingDigits_[i] = static_cast<unsigned_type>(fmodl(nonnegX, divisor));
        nonnegX = floorl(nonnegX / divisor);
    }

    // Make sure the remaining value will fit into a signed digit.
    if (nonnegX > SIGNED_TYPE_MAX) {
        *this = badValue();
        return;
    }
    else {
        leadDigit_ = static_cast<unsigned_type>(nonnegX);
    }

    // Set the correct sign.
    if (isNegative) {
        *this = -*this;
    }
}

template <int S>
RWMultiPrecisionInt<S>::RWMultiPrecisionInt(const char* string)
    : leadDigit_(0)
{
    RWHalfwordInit < unsigned_type, S - 2 >::init(trailingDigits_,
            static_cast<unsigned_type>(0));

    unsigned int j = 0;
    size_t stringLen = strlen(string);
    bool isNegative = false;

    if (string[0] == '-') {
        ++j;
        isNegative = true;
    }
    if (stringLen < j + 1) {
        std::cerr << "Invalid integer string in RWMultiPrecisionInt<S>::RWMultiPrecisionInt(const char* string)" << std::endl;
        return;
    }

    while (true) {
        *this += static_cast<unsigned long>(string[j] - '0');
        ++j;
        if (j > stringLen - 1) {
            break;
        }

        *this = decimalShiftLeft();
    }

    if (isNegative) {
        *this = -*this;
    }
}

//-------------------------------------------------------------------------
// preciseAdd
//
// This function carries out addition in full precision.  If
// the answer is too big to fit in an RWMultiPrecisionInt, The
// last digit(s) is truncated to make it fit.  The function returns
// the number of digits truncated from the result.
//-------------------------------------------------------------------------
template <int S> // static
unsigned RWMultiPrecisionInt<S>::preciseAdd(const RWMultiPrecisionInt<S>& x,
        const RWMultiPrecisionInt<S>& y,
        RWMultiPrecisionInt<S>& sum)
{
    int carry = RWDigitAdd < unsigned_type, S - 2 >::add(x.trailingDigits_,
                y.trailingDigits_,
                sum.trailingDigits_);
    sum.leadDigit_ = x.leadDigit_ + y.leadDigit_ + carry;
    // We have an overflow condition if both summands have the same sign and
    // the sum has a different sign, OR if the sum is equal to "badValue()"
    // (checked by the isGood() member function).
    if (
        (
            ((x.leadDigit_ & Constants::HighDigitBit)
             == (y.leadDigit_   & Constants::HighDigitBit))
            &&
            ((x.leadDigit_ & Constants::HighDigitBit)
             != (sum.leadDigit_ & Constants::HighDigitBit))
        )
        ||
        !sum.isGood()
    ) {
        // Overflow condition. Remember that we currently have S words of
        // precision (one leading digit of type signed_type and S-1 digits of
        // type unsigned_type).  Redo the addition with S+1 words of precision,
        // truncate one decimal digit from the result, and then put the result
        // back into S words of precision.  Unfortunately, the routine that
        // truncates a decimal digit (decimalShiftRight) only works on
        // nonnegative values.  So we must switch to positive values (note that
        // we are in this block of code only if both summands have the same sign)
        RWMultiPrecisionInt<S> xPos(x);
        RWMultiPrecisionInt<S> yPos(y);
        bool isNegative = false;
        if (x.leadDigit_ < 0) {
            xPos = -x;
            yPos = -y;
            isNegative = true;
        }

        // Copy the original summands into the higher precision arrays, add -them-
        unsigned_type trailingDigitsX[S], trailingDigitsY[S], trailingDigitsSum[S];
        signed_type leadDigitSum;
        RWArrayCopy < unsigned_type, S - 2 >::copy(xPos.trailingDigits_,
                &trailingDigitsX[1]);
        trailingDigitsX[0] = static_cast<unsigned_type>(xPos.leadDigit_);
        RWArrayCopy < unsigned_type, S - 2 >::copy(yPos.trailingDigits_,
                &trailingDigitsY[1]);
        trailingDigitsY[0] = static_cast<unsigned_type>(yPos.leadDigit_);
        carry = RWDigitAdd < unsigned_type, S - 1 >::add(trailingDigitsX,
                trailingDigitsY,
                trailingDigitsSum);
        leadDigitSum = carry;

        // The decimal shift function needs things in halfword arrays. So: Do
        // the split.  The leading digit goes into the the first 2 elements
        // of the halfword array and the trailing digits go into the rest.
        unsigned_type halfwords[2 * S + 2];
        HalfwordSplit_1::split(trailingDigitsSum, &halfwords[2]);
        HalfwordSplit_0::split(reinterpret_cast<unsigned_type*>(&leadDigitSum),
                               halfwords);

        // Now do the shift
        ::decimalShiftRight(halfwords, static_cast<unsigned int>(2 * S + 2), 1u);

        // Merge the result back into the sum
        RWHalfwordMerge < unsigned_type, S - 2 >::merge(&halfwords[4],
                sum.trailingDigits_);
        // cannot use static_cast or reinterpret_cast below: modern compilers won't //
        RWHalfwordMerge<unsigned_type, 0>::merge(&halfwords[2],
                (unsigned_type*)(&sum.leadDigit_));
        if (isNegative) {
            sum = -sum;
        }
        return 1;
    }
    else {
        return 0;
    }
}

template <int S> // static
bool RWMultiPrecisionInt<S>::longDivide(
    const RWMultiPrecisionInt<S>& dividend,
    const RWMultiPrecisionInt<S>& divisor,
    RWMultiPrecisionInt<S>& quot,
    RWMultiPrecisionInt<S>& rem)
{
    bool isNegative;
    RWMultiPrecisionInt<S> divisor_pos(divisor), dividend_pos(dividend);

    isNegative = !(static_cast<int>(divisor.leadDigit_ < 0) ^ static_cast<int>(dividend.leadDigit_ < 0));

    //If divisor or *this negative, convert to positive.
    if (divisor.leadDigit_ < 0) {
        divisor_pos = - divisor;
    }
    if (dividend.leadDigit_ < 0) {
        dividend_pos = - dividend;
    }

    bool success = longDividePos(dividend_pos, divisor_pos, quot, rem);
    if (isNegative == 0) {
        quot = -quot;
    }
    // Remainder has same sign as the dividend.
    if (dividend.leadDigit_ < 0) {
        rem = -rem;
    }

    return success;
}

//-------------------------------------------------------------------------
// Algorithm is from Knuth Vol.2: the "Classical Algorithm" for dividing
// two nonnegative integers to get a quotient and remainder.  The algorithm
// must take place over halfwords to guarantee no overflow in intermediate
// calculations.
// Algorithm returns true on success; if unsuccessful, values for *quot* and
// *rem* are set to badValue().
//-------------------------------------------------------------------------
template <int S>
bool RWMultiPrecisionInt<S>::longDividePos(
    const RWMultiPrecisionInt<S>& dividend,
    const RWMultiPrecisionInt<S>& divisor,
    RWMultiPrecisionInt<S>& quot,
    RWMultiPrecisionInt<S>& rem)
{
    static const RWMultiPrecisionInt<S> zero(0);

    // Check for division by zero or bad operands.
    if ((divisor == zero) || !dividend.isGood() || !divisor.isGood()) {
        quot = badValue();
        rem  = badValue();
        return false;
    }

    // If dividend < divisor, then dividend -is- the remainder: 3/5 = 0 (r3)
    if (dividend < divisor) {
        quot = zero;
        rem = dividend;
        return true;
    }

    // Split divisor and dividend into halfwords; initialize quotient.
    // Set extra, most significant digits for the dividend and divisor
    // equal to zero.
    unsigned_type hw_dividend[2 * S + 1], hw_divisor[2 * S + 1], hw_quot[2 * S];

    hw_dividend[0] = 0;
    // cannot use static_cast or reinterpret_cast below: modern compilers won't //
    HalfwordSplit_0::split((unsigned_type*)(&(dividend.leadDigit_)),
                           &(hw_dividend[1]));
    HalfwordSplit_2::split(dividend.trailingDigits_, &(hw_dividend[3]));
    hw_divisor[0] = 0;
    HalfwordSplit_0::split((unsigned_type*) & (divisor.leadDigit_), &(hw_divisor[1]));
    HalfwordSplit_2::split(divisor.trailingDigits_, &(hw_divisor[3]));

    RWHalfwordInit < unsigned_type, 2 * S - 1 >::init(hw_quot, 0);

    // Find the first nonzero halfword digits of divisor and dividend;
    // the difference equals the number of halfword digits in the quotient.
    unsigned int i = 0, j = 0;

    while (hw_divisor[j] == 0) {
        ++j;
    }
    while (hw_dividend[i] == 0) {
        ++i;
    }

    // Perform fast division if the divisor fits into a single halfword.
    // Start performing division where the dividend is nonzero (value *i*).
    if (j == 2 * S) {
        unsigned_type fast_remainder = 0;
        for (; i <= 2 * S; ++i) {
            fast_remainder = (fast_remainder << RWIntutilConstants<unsigned_type>::HWDigitSize) +
                             hw_dividend[i];

            // i is always greater than 0
            RW_SUPPRESS_OUT_OF_BOUNDS_ACCESS_WARNING
            hw_quot[i - 1] = fast_remainder / hw_divisor[j];
            RW_RESTORE_OUT_OF_BOUNDS_ACCESS_WARNING
            fast_remainder %= hw_divisor[j];
        }
        RWHalfwordMerge < unsigned_type, S - 2 >::merge(&(hw_quot[2]), quot.trailingDigits_);
        quot.leadDigit_ = (hw_quot[0] << RWIntutilConstants<unsigned_type>::HWDigitSize) + hw_quot[1];

        rem = fast_remainder;

        return (true);
    }

    // Multiply the divisor and dividend; choose a multiplier such that
    // the divisor's most significant digit has a nonzero leftmost bit.
    unsigned_type multiplier(0);
    unsigned_type divisor_digit(0);
    unsigned_type quot_digit(0);
    unsigned_type one(1);
    divisor_digit = hw_divisor[j];

    while (!(divisor_digit & (one << (RWIntutilConstants<unsigned_type>::HWDigitSize - 1)))) {
        divisor_digit <<= 1;
        ++multiplier;
    }

    RWHalfwordShiftLeft<unsigned_type, 2 * S>::left(multiplier, hw_divisor);
    RWHalfwordShiftLeft<unsigned_type, 2 * S>::left(multiplier, hw_dividend);


    // Make the divisor's number of digits match the dividend's number of
    // digits by left shifting the divisor digits.  In the division loop
    // below, the value of the divisor will "shift right" to equal the size
    // of the dividend as the dividend gets smaller through subtraction.
    size_t nquot_digits = j - i;
    size_t nquot_rem = (2 * S + 1) - nquot_digits;
    memmove(hw_divisor, &(hw_divisor[nquot_digits]), nquot_rem * sizeof(unsigned_type));
    memset(&(hw_divisor[nquot_rem]), 0, nquot_digits * sizeof(unsigned_type));

    if (i != 0) {
        // Loop over quotient digits.
        for (size_t q = 0; q <= nquot_digits; q++) {
            // Start with the leading dividend digit, which may have shifted left
            // by one.
            size_t curr = i + q - 1;
            if (hw_dividend[curr] == hw_divisor[curr + 1]) {
                quot_digit = RWIntutilConstants<unsigned_type>::LowerMask;
            }
            else {
                quot_digit = ((hw_dividend[curr] << RWIntutilConstants<unsigned_type>::HWDigitSize) + hw_dividend[curr + 1]) / hw_divisor[curr + 1];
            }

            // Test if the quotient digit is too large; reduction should never
            // happen more than twice (proof in Knuth vol. 2).  The test for a
            // second decrement occurs in subsequent steps.  A preliminary test
            // prevents exceeding array bounds.
            unsigned_type dividend_curr_2;
            if ((2 * S - curr) >= 2) {
                dividend_curr_2 = hw_dividend[curr + 2];
            }
            else {
                dividend_curr_2 = 0;
            }

            // Straightforward evaluation of Knuth's test can result in overflow,
            // so it is done in stages.
            unsigned_type rhs_part;
            rhs_part = ((hw_dividend[curr] << RWIntutilConstants<unsigned_type>::HWDigitSize) +
                        hw_dividend[curr + 1] - quot_digit * hw_divisor[curr + 1]);
            if ((quot_digit * hw_divisor[curr + 2] >
                    (rhs_part << RWIntutilConstants<unsigned_type>::HWDigitSize) + dividend_curr_2) &&
                    ((rhs_part >> RWIntutilConstants<unsigned_type>::HWDigitSize) == 0)) {
                --quot_digit;
            }

            // Compute how much to subtract from the dividend; shift amount left
            // to match the current dividend digits being subtracted.  Any carry-out
            // from multiplication should be assigned to the most significant digit
            // of the subtractor.
            unsigned_type subtractor[2 * S + 1];
            RWHalfwordMultiply<unsigned_type, 2 * S>::multiply(hw_divisor, quot_digit, subtractor);

            // Subtract from the dividend.
            bool went_negative;
            went_negative = RWHalfwordSubtract<unsigned_type, 2 * S>::subtract(hw_dividend, subtractor, hw_dividend);

            // Add back an amount equal to the divisor if the result went negative,
            // and subtract one from the quotient digit.  Overflow should occur in
            // the addition, but this just cancels out the "borrow" from subtraction.
            if (went_negative) {
                RWHalfwordAdd<unsigned_type, 2 * S>::add(hw_divisor, hw_dividend, hw_dividend);
                --quot_digit;
            }

            // Set quotient digit, shift divisor, and increment quotient digit counter.
            // I should eventually change divisor shift so that only nonzero values
            // are shifted right.
#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 900) && (__INTEL_COMPILER < 1300)
            unsigned_type quot_index = (2 * S - 1) - nquot_digits + q;
            hw_quot[quot_index] = quot_digit;
#else
            hw_quot[(2 * S - 1) - nquot_digits + q] = quot_digit;
#endif
            memmove(&(hw_divisor[1]), hw_divisor, 2 * S * sizeof(unsigned_type));
            hw_divisor[0] = 0;
        }
    }

    // Get the remainder by right shifting what's left in the dividend.
    RWHalfwordShiftRight<unsigned_type, 2 * S>::right(multiplier, hw_dividend);

    // Merge halfwords back into words.
    RWHalfwordMerge < unsigned_type, S - 2 >::merge(&(hw_dividend[3]), rem.trailingDigits_);
    rem.leadDigit_ = (hw_dividend[1] << RWIntutilConstants<unsigned_type>::HWDigitSize) + hw_dividend[2];
    RWHalfwordMerge < unsigned_type, S - 2 >::merge(&(hw_quot[2]), quot.trailingDigits_);
    quot.leadDigit_ = (hw_quot[0] << RWIntutilConstants<unsigned_type>::HWDigitSize) + hw_quot[1];

    return (true);
}

//-------------------------------------------------------------------------
// preciseMultiply(): perform multiplication to full precision, truncate
// least significant decimal digits in the result, and return the number
// of truncated digits.
//
//Note: this multiply algorithm breaks down if there are too many
//intermediate adds, which eventually cause overflow: breakdown can
//occur when the number of words used to represent a MultiPrecisionInt
//exceeds the number of bits in a halfword.  In the case where words are
//of type "unsigned long", the limit on number of words is typically 16
//(since an unsigned long often comprises 32 bits).
//-------------------------------------------------------------------------
template <int S>
unsigned int RWMultiPrecisionInt<S>::preciseMultiply(const RWMultiPrecisionInt<S>& lhs, const RWMultiPrecisionInt<S>& rhs,
        RWMultiPrecisionInt<S>& result)
{
    unsigned int i;
    int j;
    unsigned_type temp;
    size_t lhs_hw_size;      // number of nonzero halfwords in operands
    size_t rhs_hw_size;   // number of nonzero halfwords in operands

    // Change the sign of both operands to positive.
    bool resultNegative = ((lhs.leadDigit_ < 0) != (rhs.leadDigit_ < 0));
    RWMultiPrecisionInt<S> lhs_pos(lhs);
    RWMultiPrecisionInt<S> rhs_pos(rhs);

    if (lhs.leadDigit_ < 0) {
        lhs_pos = -lhs;
    }
    if (rhs.leadDigit_ < 0) {
        rhs_pos = -rhs;
    }

    // Split the current digits into halfword digits to make enough
    // room for intermediate multiplications and additions.
    const unsigned int opsize = 2 * S;
    unsigned_type hw_lhs[2 * S], hw_rhs[2 * S], hw_result[4 * S];

    HalfwordSplit_2::split(lhs_pos.trailingDigits_, &(hw_lhs[2]));
    //cannot use static_cast or reinterpret_cast below: modern compilers won't//
    HalfwordSplit_0::split((unsigned_type*)(&(lhs_pos.leadDigit_)), hw_lhs);
    RWHalfwordSplitReverse < unsigned_type, S - 2 >::split(rhs_pos.trailingDigits_,
            hw_rhs);
    //cannot use static_cast or reinterpret_cast below: modern compilers won't//
    RWHalfwordSplitReverse<unsigned_type, 0>::split((unsigned_type*)(&(rhs_pos.leadDigit_)), &(hw_rhs[opsize - 2]));

    // Reset the digits used for intermediate calculation and determine the
    // sizes of the operands (point to their first zero-values).
    RWHalfwordInit < unsigned_type, 4 * S - 1 >::init(hw_result, 0);
    lhs_hw_size = 0;
    while (lhs_hw_size < opsize && hw_lhs[lhs_hw_size] == 0) {
        ++lhs_hw_size;
    }

    rhs_hw_size = RWIndexOfLastNonZero < unsigned_type, 2 * S - 1 >::index(hw_rhs);

    // Exit if all halfword digits were zero in the above loop.
    if (lhs_hw_size == opsize || rhs_hw_size == RW_NPOS) {
        result = 0;
        return 0;
    }

    // Perform multiplication.
    int indexLower, indexUpper;
    for (i = 0; i <= rhs_hw_size; i++) {
        // Central steps of multiply.
        for (j = opsize - 1; j >= (int)lhs_hw_size; --j) {
            temp = hw_lhs[j] * hw_rhs[i];
            indexLower = opsize + j - i;
            indexUpper = opsize + j - i - 1;
            hw_result[indexLower]   += temp &  RWIntutilConstants<unsigned_type>::LowerMask;
            hw_result[indexUpper] += temp >> RWIntutilConstants<unsigned_type>::HWDigitSize;
        }
    }

    // Propagate carries in the result.
    RWHalfwordPropagate < unsigned_type, 4 * S - 2 >::propagate(hw_result);

    // Perform decimal shift right until the result fits into S digits.
    // The number of nonzero halfword digits in *hw_result* is
    // (opsize-lhs_hw_size+this_hw_size); reduce this number to 2*S.

    // The number of full halfwords we need to shift.
    int ndigshift = rwmax((int) - 1, ((int)rhs_hw_size - (int)lhs_hw_size - 1));

    // The number of additional bits we need to shift.
    int nbitshift = 0;
    if ((ndigshift != -1) && hw_result[(opsize - 1) - ((int)rhs_hw_size - lhs_hw_size)] != 0) {
        // If the result does not fit into the answer (ndigshift != -1),
        // and there are some bits we need to shift
        // (hw_result[(opsize-1)-(rhs_hw_size-lhs_hw_size)] != 0), then
        // count the number of bits we need to shift.

        // Start out assuming we need to shift all the bits.
        nbitshift = static_cast<int>(RWIntutilConstants<unsigned_type>::HWDigitSize);

        // Decrement this value until it is correct by shifting the halfword
        // bitwise left (in order to count the number of significant bits in
        // it). As long as the most significant bit in the halfword is 0,
        // continue counting. The first 1 represents the start of where we need
        // to shift.
        //
        for (long hw_value(hw_result[(opsize - 1) - ((int)rhs_hw_size - lhs_hw_size)]);
                (hw_value = (hw_value << 1)) == 0; --ndigshift) {
        }
    }

    if ((hw_result[0] >> RWIntutilConstants<unsigned_type>::HWDigitSize) != 0) {
        ndigshift++;
    }

    // Convert the ndigshift and nbitshift values into a decimal
    // equivalent. This is done by converting ndigshift to bits
    // (ndigshift*HWDigitSize), adding nbitshift, and converting this to
    // decimal digits by multiplying by log 2 (0.301029995664). We add
    // one to account for fractional results.
    unsigned int ndecshift = (unsigned int)(ndigshift == -1 ? 0U : 0.301029995664 * (ndigshift * RWIntutilConstants<unsigned_type>::HWDigitSize + nbitshift) + 1);
    unsigned int numTruncated = ::decimalShiftRightToHalfSize(hw_result, (unsigned int)4 * S, ndecshift);

    // copy shifted result into an MPInt of size S.
    result.leadDigit_ = (hw_result[2 * S]  << RWIntutilConstants<unsigned_type>::HWDigitSize) +
                        (hw_result[2 * S + 1] & RWIntutilConstants<unsigned_type>::LowerMask);
    RWHalfwordMerge < unsigned_type, S - 2 >::merge(&(hw_result[2 * S + 2]), result.trailingDigits_);

    // Set result sign.
    if (resultNegative) {
        result = -result;
    }

    return numTruncated;
}

//-------------------------------------------------------------------------
//Note: this multiply algorithm breaks down if there are too many
//intermediate adds, which eventually cause overflow: breakdown can
//occur when the number of words used to represent a MultiPrecisionInt
//exceeds the number of bits in a halfword.  In the case where words are
//of type "unsigned long", the limit on number of words is typically 16
//(since an unsigned long often comprises 32 bits).
//-------------------------------------------------------------------------
template <int S>
RWMultiPrecisionInt<S>& RWMultiPrecisionInt<S>::operator*=(const RWMultiPrecisionInt<S>& rhs)
{
    unsigned int i, j;
    unsigned_type temp;
    size_t rhs_hw_size; // number of nonzero halfwords in operands
    size_t this_hw_size;   // number of nonzero halfwords in operands

    // Perform operation only if both operands are good.
    if (!isGood() || !rhs.isGood()) {
        *this = badValue();
        return *this;
    }

    // Change the sign of both operands to positive.
    bool resultNegative;
    RWMultiPrecisionInt<S> this_pos(*this);
    RWMultiPrecisionInt<S> rhs_pos(rhs);

    resultNegative = ((leadDigit_ < 0) != (rhs.leadDigit_ < 0));
    if (leadDigit_ < 0) {
        this_pos = - *this;
    }
    if (rhs.leadDigit_ < 0) {
        rhs_pos = -rhs;
    }

    // Split the current digits into halfword digits to make enough
    // room for intermediate multiplications and additions.
    const unsigned int opsize = 2 * S;
    unsigned_type hw_op1[2 * S], hw_op2[2 * S], hw_result[2 * S];

    HalfwordSplit_2::split(this_pos.trailingDigits_, &(hw_op1[2]));
    //cannot use static_cast or reinterpret_cast below: modern compilers won't//
    HalfwordSplit_0::split((unsigned_type*)(&(this_pos.leadDigit_)), hw_op1);
    RWHalfwordSplitReverse < unsigned_type, S - 2 >::split(rhs_pos.trailingDigits_,
            hw_op2);
    //cannot use static_cast or reinterpret_cast below: modern compilers won't//
    RWHalfwordSplitReverse<unsigned_type, 0>::split((unsigned_type*)(&(rhs_pos.leadDigit_)), &(hw_op2[opsize - 2]));

    // Reset the digits used for intermediate calculation and determine the
    // sizes of the operands (find their first nonzero halfwords).
    RWHalfwordInit < unsigned_type, 2 * S - 1 >::init(hw_result, 0);
    this_hw_size = 0;

    while (this_hw_size < opsize && hw_op1[this_hw_size] == 0) {
        this_hw_size++;
    }

    rhs_hw_size = RWIndexOfLastNonZero < unsigned_type, 2 * S - 1 >::index(hw_op2);

    // Exit if all halfword digits were zero in the above loop.
    if (this_hw_size == opsize || rhs_hw_size == RW_NPOS) {
        *this = 0;
        return *this;
    }

    // Check for possible overflow caused by too many nonzero digits.
    // "Too many" is defined as more than 2*S+1 digits combined from both
    // operands.
    if (rhs_hw_size > this_hw_size) {
        *this = badValue();
        return (*this);
    }

    // Perform multiplication.
    unsigned int termination;
    int upperIndex, lowerIndex;

    for (i = 0; i <= rhs_hw_size; i++) {
        // Central steps of multiply; looping to *termination* prevents
        // negative indexing into result, plus it avoids unnecessary
        // multiplies by zero-valued digits in *halfword_digits_*.
        termination = (int)this_hw_size - 1 > (int) i ? (int)this_hw_size - 1 : i;
        for (j = opsize - 1; j > termination; --j) {
            temp = hw_op2[i] * hw_op1[j];
            upperIndex = j - i;
            lowerIndex = j - i - 1;
            hw_result[upperIndex]   += temp &  RWIntutilConstants<unsigned_type>::LowerMask;
            hw_result[lowerIndex] += temp >> RWIntutilConstants<unsigned_type>::HWDigitSize;
        }
        if (termination == i) {
            hw_result[0] += hw_op2[i] * hw_op1[i];
        }
    }

    // Propagate carries in the result.
    RWHalfwordPropagate < unsigned_type, 2 * S - 2 >::propagate(hw_result);

    // Test for overflow; test one extra bit because this bit must stay
    // zero or the result becomes negative.
    if (hw_result[0] >> (RWIntutilConstants<unsigned_type>::HWDigitSize - 1)) {
        *this = badValue();
        return (*this);
    }

    // Put digits back together again.
    RWHalfwordMerge < unsigned_type, S - 2 >::merge(&(hw_result[2]), trailingDigits_);
    leadDigit_ = (hw_result[0] << RWIntutilConstants<unsigned_type>::HWDigitSize) +
                 (hw_result[1] & RWIntutilConstants<unsigned_type>::LowerMask);

    // Set result sign.
    if (resultNegative) {
        *this = -*this;
    }

    return (*this);
}


template <int S>
RWCString RWMultiPrecisionInt<S>::asString() const
{
    static const RWMultiPrecisionInt<S> zero(0);
    RWMultiPrecisionInt<S> tmp(*this);
    RWCString s;
    int i;
    bool isNegative = false;

    if (!isGood()) {
        s = "(bad value)";
        return s;
    }

    // Make a positive version of the number.
    if (leadDigit_ < 0) {
        tmp = -*this;
        isNegative = true;
    }

    if (tmp == zero) {
        s = "0";
        return s;
    }

    char char_digit;
    while (tmp != zero) {
        // Compute the least significant decimal digit.  Algorithm takes
        // advantage of the relationship between moduli of powers of 2:
        // [ 2^(4t) * x ] % 10 = 6 * (x % 10) for any positive integers x, t.
        unsigned long modctr = tmp.trailingDigits_[S - 2] % 10;
        for (i = S - 3; i >= 0; --i) {
            modctr += (tmp.trailingDigits_[i] % 10) * 6;
        }
        modctr += (tmp.leadDigit_ % 10) * 6;
        char_digit = static_cast<char>('0' + (modctr % 10));
        s.prepend(char_digit);

        tmp = tmp.decimalShiftRight();

        if (!tmp.isGood()) {
            std::cerr << "asString(): Fatal: Bad decimal shift right!" << std::endl;
        }
    }

    if (isNegative) {
        s.prepend('-');
    }
    return s;
}

template <int S>
RWMultiPrecisionInt<S> RWMultiPrecisionInt<S>::decimalShiftLeft(unsigned int shiftBy) const
{
    if (shiftBy == 0UL) {
        return *this;
    }

    RWMultiPrecisionInt<S> shifted(*this);
    // Attempt a one-two-big fix: If ==, then it -may- be ok to do it in two parts
    // Let some other code catch the over/underflow
    if (shiftBy == RWMPPowersOfTen<S>::numPowers()) {
        shifted *= RWMPPowersOfTen<S>::power(1);
        shiftBy -= 1;
    }
    if (shiftBy >= RWMPPowersOfTen<S>::numPowers()) {
        return badValue();
    }

    shifted *= RWMPPowersOfTen<S>::power(shiftBy);
    return shifted;
}

template <int S>
RWMultiPrecisionInt<S> RWMultiPrecisionInt<S>::decimalShiftRight(unsigned int shiftBy) const
{
    if (shiftBy == 0UL) {
        return *this;
    }

    RWMultiPrecisionInt<S> shifted(*this);
    // Attempt a one-too-big fix: If ==, then it -may- be ok to do it in two parts
    // Let some other code catch the over/underflow
    if (shiftBy == RWMPPowersOfTen<S>::numPowers()) {
        shifted /= RWMPPowersOfTen<S>::power(1);
        shiftBy -= 1;
    }
    if (shiftBy >= RWMPPowersOfTen<S>::numPowers()) {
        return badValue();
    }
    shifted /= RWMPPowersOfTen<S>::power(shiftBy);
    return shifted;
}

template <int S>
void RWMultiPrecisionInt<S>::saveOn(RWFile& f) const
{
    f.Write(leadDigit_);
    for (int i = 0; i < S - 1; ++i) {
        f.Write(trailingDigits_[i]);
    }
}


template <int S>
void RWMultiPrecisionInt<S>::restoreFrom(RWFile& f)
{
    f.Read(leadDigit_);
    for (int i = 0; i < S - 1; ++i) {
        f.Read(trailingDigits_[i]);
    }
}

template <int S>
void RWMultiPrecisionInt<S>::saveOn(RWvostream& s) const
{
    s << leadDigit_;
    for (int i = 0; i < S - 1; ++i) {
        s << trailingDigits_[i];
    }
}

template <int S>
void RWMultiPrecisionInt<S>::restoreFrom(RWvistream& s)
{
    s >> leadDigit_;
    for (int i = 0; i < S - 1; ++i) {
        s >> trailingDigits_[i];
    }
}

#endif // RW_CURRENCY_MPINT_CC
