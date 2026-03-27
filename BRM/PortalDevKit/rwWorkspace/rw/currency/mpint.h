#ifndef RW_CURRENCY_MPINT_H
#define RW_CURRENCY_MPINT_H

/*-------------------------------------------------------------------------
 * Definition of RWMultiPrecisionInt and related classes.
 *
 * $Id: //spro/rel2016.1/rw/currency/mpint.h#1 $
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
#ifndef RW_MONEY_MPINT_H
#  define RW_MONEY_MPINT_H
#endif

#include <rw/currency/intutil.h>
#include <rw/currency/utlconst.h>
#include <rw/dcmldefs.h>
#include <rw/tools/cstrstrm.h>

#if defined(RW_MNY_NO_NEW_HEADER)
#  include <math.h>
#else
#  include <cmath>
#endif


class RWFile;
class RWCString;
class RWvistream;
class RWvostream;

/**
 * \ingroup currency_decimal_numbers_group
 *
 * \brief
 * Provides a very large number of bits of precision for representing
 * decimals.
 *
 * Provides a very large number of bits of precision for representing
 * decimals. This class should only be used as a template parameter for
 * RWDecimal.
 *
 * \tparam S An integer from 1 to 16 to specify the number of
 * <tt>S * 32</tt> bits of precision
 */
template <int S>
class RWMultiPrecisionInt
{
public:
    typedef rwint32          signed_type;
    typedef rwuint32         unsigned_type;

    //  Constants used to set the minimum and maximum values for an M.P. int
    static const   rwuint32 UNSIGNED_TYPE_MAX;
    static const   rwuint32 UNSIGNED_TYPE_MIN;
    static const   rwint32  SIGNED_TYPE_MAX;
    static const   rwint32  SIGNED_TYPE_MIN;

    typedef RWIntutilConstants<unsigned_type> Constants;

    // Constructors -----------------------------------------------------------
    RWMultiPrecisionInt()
        : leadDigit_(0)
    {
        RWHalfwordInit < unsigned_type, S - 2 >::init(trailingDigits_,
                static_cast<unsigned_type>(0));
    }

    RWMultiPrecisionInt(int x)
    {
        unsigned_type fillValue = x < 0 ? static_cast<unsigned_type>(~0) : static_cast<unsigned_type>(0);
        leadDigit_ = fillValue;
        RWHalfwordInit < unsigned_type, S - 3 >::init(trailingDigits_, fillValue);
        trailingDigits_[S - 2] = (unsigned_type)x;
    }

    RWMultiPrecisionInt(unsigned int x)
        : leadDigit_(0)
    {
        RWHalfwordInit < unsigned_type, S - 3 >::init(trailingDigits_, static_cast<unsigned_type>(0));
        trailingDigits_[S - 2] = static_cast<unsigned_type>(x);
    }

    RWMultiPrecisionInt(long x)
    {
        unsigned_type fillValue = x < 0 ? static_cast<unsigned_type>(~0) : static_cast<unsigned_type>(0);
        leadDigit_ = fillValue;
        RWHalfwordInit < unsigned_type, S - 3 >::init(trailingDigits_, fillValue);
        trailingDigits_[S - 2] = static_cast<unsigned_type>(x);
    }

    RWMultiPrecisionInt(unsigned long x)
        : leadDigit_(0)
    {
        RWHalfwordInit < unsigned_type, S - 3 >::init(trailingDigits_, (unsigned_type)0);
        trailingDigits_[S - 2] = static_cast<unsigned_type>(x);
    }

    RWMultiPrecisionInt(double num);
    RWMultiPrecisionInt(long double num);
    RWMultiPrecisionInt(const char* string);
    RWMultiPrecisionInt(const RWMultiPrecisionInt<S>& x)
    {
        leadDigit_ = x.leadDigit_;
        SubArrayCopy::copy(x.trailingDigits_, trailingDigits_);
    }

    // Comparison operators ---------------------------------------------------
    static bool isEqual(const RWMultiPrecisionInt<S>& lhs,
                        const RWMultiPrecisionInt<S>& rhs)
    {
        return lhs.leadDigit_ == rhs.leadDigit_ &&
               RWMPIntEqual < unsigned_type, S - 2 >::equal(
                   lhs.trailingDigits_,
                   rhs.trailingDigits_);
    }

    static bool isLess(const RWMultiPrecisionInt<S>& lhs,
                       const RWMultiPrecisionInt<S>& rhs)
    {
        bool result = (lhs.leadDigit_ < rhs.leadDigit_);
        if (! result && lhs.leadDigit_ == rhs.leadDigit_) {
            size_t index = IndexOfDiff::index(lhs.trailingDigits_, rhs.trailingDigits_);
            result =
                index == RW_NPOS ?
                false : (lhs.trailingDigits_[index] < rhs.trailingDigits_[index]);
        }
        return result;
    }

    // Unary minus (negation)
    RWMultiPrecisionInt<S> operator-() const;

    // static member functions
    static const RWMultiPrecisionInt<S>& maxValue();
    static const RWMultiPrecisionInt<S>& minValue();
    static const RWMultiPrecisionInt<S>& zero();

    static unsigned int decimalPrecision()
    {
        return decimalPrecision_;
    }

    //-------------------------------------------------------------------------
    // preciseAdd
    //
    // This function carries out addition in full precision.  If
    // the answer is too big to fit in an RWMultiPrecisionInt, The
    // last digit(s) is truncated to make it fit.  The function returns
    // the number of digits truncated from the result.
    //-------------------------------------------------------------------------
    static unsigned preciseAdd(const RWMultiPrecisionInt<S>& x,
                               const RWMultiPrecisionInt<S>& y,
                               RWMultiPrecisionInt<S>& sum) ;

    static bool longDivide(const RWMultiPrecisionInt<S>& dividend,
                           const RWMultiPrecisionInt<S>& divisor,
                           RWMultiPrecisionInt<S>& quot,
                           RWMultiPrecisionInt<S>& rem) ;

    //-------------------------------------------------------------------------
    // Algorithm is from Knuth Vol.2: the "Classical Algorithm" for dividing
    // two nonnegative integers to get a quotient and remainder.  The algorithm
    // must take place over halfwords to guarantee no overflow in intermediate
    // calculations.
    // Algorithm returns true on success; if unsuccessful, values for *quot* and
    // *rem* are set to badValue().
    //-------------------------------------------------------------------------
    static bool longDividePos(const RWMultiPrecisionInt<S>& dividend,
                              const RWMultiPrecisionInt<S>& divisor,
                              RWMultiPrecisionInt<S>& quot,
                              RWMultiPrecisionInt<S>& rem) ;

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
    static unsigned int preciseMultiply(const RWMultiPrecisionInt<S>& lhs,
                                        const RWMultiPrecisionInt<S>& rhs,
                                        RWMultiPrecisionInt<S>& result) ;

    // Assignment operators ---------------------------------------------------
#if defined(__INTEL_COMPILER)
    RWMultiPrecisionInt<S>& operator=(const RWMultiPrecisionInt<S>& rhs)
    {
        leadDigit_ = rhs.leadDigit_;
        SubArrayCopy::copy(rhs.trailingDigits_, trailingDigits_);
        return *this;
    }
#endif
    RWMultiPrecisionInt<S>& operator+=(const RWMultiPrecisionInt<S>& lhs)
    {
        if (!isGood() || !lhs.isGood()) {
            *this = badValue();
        }
        else {
            int carry = RWDigitAdd < unsigned_type, S - 2 >::add(trailingDigits_,
                        lhs.trailingDigits_,
                        trailingDigits_);
            signed_type lead = leadDigit_ + lhs.leadDigit_ + carry;
            if ((leadDigit_ & Constants::HighDigitBit) ==
                    (lhs.leadDigit_ & Constants::HighDigitBit)
                    &&
                    (leadDigit_ & Constants::HighDigitBit) != (lead & Constants::HighDigitBit)) {
                *this = badValue();
            }
            else {
                leadDigit_ = lead;
            }
        }
        return *this;
    }

    RWMultiPrecisionInt<S>& operator-=(const RWMultiPrecisionInt<S>& lhs)
    {
        *this += -(lhs);
        return *this;
    }


    //-------------------------------------------------------------------------
    //Note: this multiply algorithm breaks down if there are too many
    //intermediate adds, which eventually cause overflow: breakdown can
    //occur when the number of words used to represent a MultiPrecisionInt
    //exceeds the number of bits in a halfword.  In the case where words are
    //of type "unsigned long", the limit on number of words is typically 16
    //(since an unsigned long often comprises 32 bits).
    //-------------------------------------------------------------------------
    RWMultiPrecisionInt<S>& operator*=(const RWMultiPrecisionInt<S>& rhs);

    RWMultiPrecisionInt<S>& operator/=(const RWMultiPrecisionInt<S>& lhs)
    {
        MPInt_S quot, rem;

        longDivide(*this, lhs, quot, rem);
        *this = quot;
        return *this;
    }

    // Binary operators -------------------------------------------------------
    // if the compiler allows no type template functions these global operators
    // are defined outside the class.

    // Public member functions ------------------------------------------------
    double    asDouble() const;

    RWCString asString() const;

    RWMultiPrecisionInt<S> decimalShiftLeft(unsigned int shiftBy = 1) const;
    RWMultiPrecisionInt<S> decimalShiftRight(unsigned int shiftBy = 1) const;

    bool isGood() const
    {
        return
            static_cast<unsigned_type>(leadDigit_) != Constants::HighDigitBit ||
            RWIndexOfLastNonZero < unsigned_type, S - 2 >::index(trailingDigits_) != RW_NPOS;
    }

    bool isEven() const
    {
        return !(trailingDigits_[S - 2] & Constants::LowDigitBit);
    }

    void saveOn(RWvostream&) const;
    void saveOn(RWFile&) const;
    void restoreFrom(RWvistream&);
    void restoreFrom(RWFile& f);

private:
    signed_type   leadDigit_;
    unsigned_type trailingDigits_[S - 1];

private: // internal-only convenience typenames
    typedef RWMultiPrecisionInt<S>                 MPInt_S;
    typedef RWIndexOfFirstDiff < unsigned_type, S - 2 > IndexOfDiff;
    typedef RWMPIntEqual < unsigned_type, S - 2 >       MPIntEqual;
    typedef RWArrayCopy < unsigned_type, S - 2 >         SubArrayCopy;
    typedef RWHalfwordSplit<unsigned_type, 0>      HalfwordSplit_0;
    typedef RWHalfwordSplit < unsigned_type, S - 1 >    HalfwordSplit_1;
    typedef RWHalfwordSplit < unsigned_type, S - 2 >    HalfwordSplit_2;

private: // constructor, methods
    RWMultiPrecisionInt(signed_type ld, unsigned_type* td)
        : leadDigit_(ld)
    {
        SubArrayCopy::copy(td, trailingDigits_);
    }


    inline static const RWMultiPrecisionInt<S>& badValue()
    {
        static RWMultiPrecisionInt<S> badValue_;
        if (badValue_.leadDigit_ == 0) {
            badValue_.leadDigit_ = static_cast<signed_type>(Constants::HighDigitBit);
            RWHalfwordInit < unsigned_type, S - 2 >::init(badValue_.trailingDigits_,
                    static_cast<unsigned_type>(0));
        }
        return badValue_;
    }

    static const unsigned int decimalPrecision_;
};

// End class RWMultiPrecisionInt ------------------------------------------

// static functions  --------------------------------------------------

template <int S>
#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1100)
const RWMultiPrecisionInt<S>& RWMultiPrecisionInt<S>::maxValue()
#else
inline const RWMultiPrecisionInt<S>& RWMultiPrecisionInt<S>::maxValue()
#endif
{
    static RWMultiPrecisionInt<S> maxValue_;
    if (maxValue_.leadDigit_ == 0) {
        RWHalfwordInit < unsigned_type, S - 2 >::init(maxValue_.trailingDigits_, UNSIGNED_TYPE_MAX);
        maxValue_.leadDigit_ = SIGNED_TYPE_MAX;
    }
    return maxValue_;
}

template <int S>
#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1100)
const RWMultiPrecisionInt<S>& RWMultiPrecisionInt<S>::minValue()
#else
inline const RWMultiPrecisionInt<S>& RWMultiPrecisionInt<S>::minValue()
#endif
{
    static RWMultiPrecisionInt<S> minValue_;
    if (minValue_.leadDigit_ == 0) {
        preciseAdd(badValue(), RWMultiPrecisionInt<S>(1), minValue_);
    }
    return minValue_;
}

template <int S>
#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1100)
const RWMultiPrecisionInt<S>& RWMultiPrecisionInt<S>::zero()
#else
inline const RWMultiPrecisionInt<S>& RWMultiPrecisionInt<S>::zero()
#endif
{
    static RWMultiPrecisionInt<S> zero_ = RWMultiPrecisionInt<S>(0);
    return zero_;
}


// Arithmetic operators --------------------------------------------------
template <int S>
inline RWMultiPrecisionInt<S> operator-(const RWMultiPrecisionInt<S>& lhs,
                                        const RWMultiPrecisionInt<S>& rhs)
{
    return RWMultiPrecisionInt<S>(lhs) -= rhs;
}

template <int S>
inline  RWMultiPrecisionInt<S> operator+(const RWMultiPrecisionInt<S>& lhs,
        const RWMultiPrecisionInt<S>& rhs)
{
    return RWMultiPrecisionInt<S>(lhs) += rhs;
}

template <int S>
inline RWMultiPrecisionInt<S> operator*(const RWMultiPrecisionInt<S>& lhs,
                                        const RWMultiPrecisionInt<S>& rhs)
{
    return RWMultiPrecisionInt<S>(lhs) *= rhs;
}

template <int S>
inline RWMultiPrecisionInt<S> operator/(const RWMultiPrecisionInt<S>& lhs,
                                        const RWMultiPrecisionInt<S>& rhs)
{
    return RWMultiPrecisionInt<S>(lhs) /= rhs;
}

// Shifting in and out of streams
template <int S>
inline std::ostream& operator<<(std::ostream& strm,
                                const RWMultiPrecisionInt<S>& n)
{
    return strm << n.asString();
}

// Comparison operators ---------------------------------------------------
template <int S>
inline bool operator==(const RWMultiPrecisionInt<S>& lhs,
                       const RWMultiPrecisionInt<S>& rhs)
{
    return RWMultiPrecisionInt<S>::isEqual(lhs, rhs);
}

template <int S>
inline bool operator<(const RWMultiPrecisionInt<S>& lhs,
                      const RWMultiPrecisionInt<S>& rhs)
{
    return RWMultiPrecisionInt<S>::isLess(lhs, rhs);
}

#if !defined(RWSTD_NO_NAMESPACE)
template <int S>
inline   bool operator>(const RWMultiPrecisionInt<S>& lhs, const RWMultiPrecisionInt<S>& rhs)
{
    return RWMultiPrecisionInt<S>::isLess(rhs, lhs);
}

template <int S>
inline   bool operator!=(const RWMultiPrecisionInt<S>& lhs, const RWMultiPrecisionInt<S>& rhs)
{
    return ! RWMultiPrecisionInt<S>::isEqual(lhs, rhs);
}

template <int S>
inline   bool operator>=(const RWMultiPrecisionInt<S>& lhs, const RWMultiPrecisionInt<S>& rhs)
{
    return ! RWMultiPrecisionInt<S>::isLess(lhs, rhs);
}

template <int S>
inline   bool operator<=(const RWMultiPrecisionInt<S>& lhs, const RWMultiPrecisionInt<S>& rhs)
{
    return ! RWMultiPrecisionInt<S>::isLess(rhs, lhs);
}

#endif   // NO STL

template <int S>
RWMultiPrecisionInt<S> RWMultiPrecisionInt<S>::operator-() const
{
    unsigned_type trailing[(S <= 1) ? 1 : S - 1];
    int carry = RWDigitNegate < unsigned_type, S - 2 >::negate(trailingDigits_, trailing);
    signed_type lead = (Constants::MaxDigitInt - leadDigit_) + carry;
    return RWMultiPrecisionInt<S>(lead, trailing);
}

template <int S>
double RWMultiPrecisionInt<S>::asDouble() const
{
    RWMultiPrecisionInt<S> tmp(*this);
    bool neg;
    if (leadDigit_ < 0) {
        tmp = -(*this);
        neg = true;
    }
    else {
        neg = false;
    }

    unsigned_type digits[S];
    digits[0] = static_cast<unsigned_type>(tmp.leadDigit_);
    SubArrayCopy::copy(tmp.trailingDigits_, &(digits[1]));

    double value = RWIntToDouble < unsigned_type, S - 1 >::todouble(digits);
    if (neg) {
        value = -value;
    }
    return value;
}

#include <rw/currency/mp1int.h> // get the base case specializations

#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/mpint.cc>
#endif

#endif // RW_CURRENCY_MPINT_H
