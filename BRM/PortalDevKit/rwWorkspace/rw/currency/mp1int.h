#ifndef RW_CURRENCY_MP1INT_H
#define RW_CURRENCY_MP1INT_H

/*-------------------------------------------------------------------------
 *
 * Declaration of RWMultiPrecisionInt where the underlying
 * integer representation is based on a double precision variable
 *
 * $Id: //spro/rel2016.1/rw/currency/mp1int.h#1 $
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
#ifndef RW_MONEY_MP1INT_H
#  define RW_MONEY_MP1INT_H
#endif

#include <rw/currency/mpint.h>  // just in case we get #included solo
#include <rw/dcmldefs.h>
#include <rw/decio.h>
#include <rw/cstring.h>
#include <rw/decbase.h>
#include <rw/rwfile.h>
#include <rw/vstream.h>
#include <sstream>

#if defined(RW_MNY_NO_NEW_HEADER)
#  include <float.h>
#  include <math.h>
#else
#  include <cfloat>
#  include <cmath>
#endif


template<>
class RW_DCML_SYMBOLIC RWMultiPrecisionInt<1>
{
public:
    // Constructors ---------------------------------------------------------
    RWMultiPrecisionInt<1>()
        : data_(0)
    {
    }

    RWMultiPrecisionInt<1>(int num)
        : data_(double(num))
    {
    }

    RWMultiPrecisionInt<1>(long num)
        : data_(double(num))
    {
    }

    RWMultiPrecisionInt<1>(double data)
        : data_(data)
    {
    }

    RWMultiPrecisionInt<1>(long double data)
        : data_(double(data))
    {
    }

    RWMultiPrecisionInt<1>(const RWMultiPrecisionInt<1>& x)
        : data_(x.data_)
    {
    }

    static unsigned int decimalPrecision()
    {
        return DBL_DIG;    // DBL_DIG is defined in <float.h>
    }

    // Unary arithmetic operators
    RWMultiPrecisionInt<1> operator-() const
    {
        return RWMultiPrecisionInt<1>(-data_);
    }

    // Public member functions ----------------------------------------------
    bool isGood() const
    {
        RW_SUPPRESS_FLOATING_POINT_EQUALITY_WARNING
        return (data_ != badValue());
        RW_RESTORE_FLOATING_POINT_EQUALITY_WARNING
    }

    double    asDouble() const
    {
        return data_;
    }

    // Shifting out  --------------------------------------------------------
    // Gotta be defined inline since most compilers do not support non-type
    // template parameters for function templates.
    friend std::ostream& operator<<(std::ostream& strm, const RWMultiPrecisionInt<1>& n)
    {
        if (!n.isGood()) {
            strm << "(bad value)";
        }
        else {
#ifndef __hpux
            // Set flags so that it looks like an int (no scientific notation
            // and no digits to the right of the decimal point).
            std::ios::fmtflags oldFlags = strm.setf(std::ios::fixed, std::ios::floatfield);
            std::streamsize oldPrecision = strm.precision(0);
            strm << n.data_;
            strm.setf(oldFlags, std::ios::floatfield);
            strm.precision(oldPrecision);
#else
            // We have seen rounding errors on the last digit when outputting
            // a double on a stream using precision 0.  We get around this by
            // using precision 1 and truncating the trailing ".0".
            std::ostringstream stringStrm;
            stringStrm.setf(std::ios::fixed, std::ios::floatfield);
            stringStrm.precision(1);
            stringStrm << n.data_;
            strm << stringStrm.str().substr(0, stringStrm.str().size() - 2);
#endif
        }

        return strm;
    }

    // Assignment operators -------------------------------------------------
#if defined(__INTEL_COMPILER)
    RWMultiPrecisionInt<1>& operator=(const RWMultiPrecisionInt<1>& rhs);
#endif
    RWMultiPrecisionInt<1>& operator+=(const RWMultiPrecisionInt<1>& lhs);
    RWMultiPrecisionInt<1>& operator-=(const RWMultiPrecisionInt<1>& lhs);
    RWMultiPrecisionInt<1>& operator*=(const RWMultiPrecisionInt<1>& lhs);
    RWMultiPrecisionInt<1>& operator/=(const RWMultiPrecisionInt<1>& lhs);

#if defined(_MSC_VER) && (_MSC_VER <= 1300)
    RWMultiPrecisionInt<1>& operator+=(const long double& lhs);
    RWMultiPrecisionInt<1>& operator-=(const long double& lhs);
    RWMultiPrecisionInt<1>& operator*=(const long double& lhs);
    RWMultiPrecisionInt<1>& operator/=(const long double& lhs);
#endif


    // Binary and relational operators simply globals that call back inside

    // Global long division -------------------------------------------------
    static bool longDividePos(const RWMultiPrecisionInt<1>& dividend,
                              const RWMultiPrecisionInt<1>& divisor,
                              RWMultiPrecisionInt<1>& quot,
                              RWMultiPrecisionInt<1>& rem)
    {
        return longDivide(dividend, divisor, quot, rem);
    }

    static bool longDivide(const RWMultiPrecisionInt<1>& dividend,
                           const RWMultiPrecisionInt<1>& divisor,
                           RWMultiPrecisionInt<1>& quot,
                           RWMultiPrecisionInt<1>& rem)
    {
        bool result = true;
        if (divisor.data_ == 0.0) {
            quot.data_ = badValue();
            rem.data_ = badValue();
            result = false;
        }
        else {
            if (dividend.data_ == 0.0) {
                quot.data_ = dividend.data_;
                rem.data_ = 0.0;
            }
            else {
                quot.data_ = RWMNY_STD::floor(dividend.data_ / divisor.data_);
                rem.data_ = dividend.data_ - divisor.data_ * quot.data_;
            }
        }
        return result;
    }

    // Public member functions ----------------------------------------------
    RWMultiPrecisionInt<1> decimalShiftLeft(unsigned int shiftBy = 1) const;

    RWMultiPrecisionInt<1> decimalShiftRight(unsigned int shiftBy = 1) const
    {
#if defined(_AIX71)
        // AIX 7.1 has an implementation of pow() that returns a different value
        // past DBL_DIG that differs from previous AIX and other UNIXs.
        double divisor = 1.0;
        for (unsigned i = 0; i < shiftBy; ++i) {
            divisor *= 10.0;
        }
#else
        double divisor = RWMNY_STD::pow(10.0, (double)shiftBy);
#endif
        double data = data_ / divisor;
        if (RWMNY_STD::fabs(data) < 1.0) {
            data = 0.0;
        }
        return RWMultiPrecisionInt<1>(RWMNY_STD::floor(data));
    }

    bool isEven()
    {
        RW_SUPPRESS_FLOATING_POINT_EQUALITY_WARNING
        return (data_ / 2.0 == RWMNY_STD::floor(data_ / 2.0));
        RW_RESTORE_FLOATING_POINT_EQUALITY_WARNING
    }

    void saveOn(RWFile& f) const
    {
        f.Write(data_);
    }
    void restoreFrom(RWFile& f)
    {
        f.Read(data_);
    }
    void saveOn(RWvostream& strm) const
    {
        strm << data_;
    }
    void restoreFrom(RWvistream& strm)
    {
        strm >> data_;
    }


    static RWMultiPrecisionInt<1> maxValue()
    {
        return maxDouble();
    }

    static RWMultiPrecisionInt<1> minValue()
    {
        return -maxDouble();
    }

    static RWMultiPrecisionInt<1> zero()
    {
        return 0.0;
    }

    static unsigned preciseAdd(const RWMultiPrecisionInt<1>& x,
                               const RWMultiPrecisionInt<1>& y,
                               RWMultiPrecisionInt<1>& sum)
    {
        unsigned result = 0;
        sum.data_ = x.data_ + y.data_;
        if (sum.data_ > maxDouble() || sum.data_ < -maxDouble()) {
            sum.data_ /= 10.0;
            result = 1;
        }
        return result;
    }

    static unsigned preciseMultiply(const RWMultiPrecisionInt<1>& x,
                                    const RWMultiPrecisionInt<1>& y,
                                    RWMultiPrecisionInt<1>& product);

    RWCString asString() const;
public: // provided to avoid friendship with global relationals
    double compareTo(const RWMultiPrecisionInt<1>& other) const
    {
        return data_ - other.data_;
    }
private:
    double data_;
private: // methods
    static double badValue()
    {
        return maxDouble() + 1.0;
    }
    static double maxDouble()
    {
        return 9007199254740991.0;
    }
};

/**
 * \ingroup currency_decimal_numbers_group
 *
 * Convenience typedef for integer where a \c double is used to store the
 * integer value. This results in an integer with 15 digit precision.
 */
typedef RWMultiPrecisionInt<1> RWMP1Int;

// Inline Assignment Operators --------------------------------------------
#if defined(__INTEL_COMPILER)
inline RWMultiPrecisionInt<1>&
RWMultiPrecisionInt<1>::operator=(const RWMultiPrecisionInt<1>& rhs)
{
    data_ = rhs.data_;
    return *this;
}
#endif

inline RWMultiPrecisionInt<1>&
RWMultiPrecisionInt<1>::operator+=(const RWMultiPrecisionInt<1>& lhs)
{
    if (!isGood() || !lhs.isGood()) {
        data_ = badValue();
    }
    else {
        data_ += lhs.data_;
        if (data_ > maxDouble() || data_ < -maxDouble()) {
            data_ = badValue();
        }
    }
    return *this;
}

inline RWMultiPrecisionInt<1>&
RWMultiPrecisionInt<1>::operator-=(const RWMultiPrecisionInt<1>& lhs)
{
    if (!isGood() || !lhs.isGood()) {
        data_ = badValue();
    }
    else {
        data_ -= lhs.data_;
        if (data_ > maxDouble() || data_ < -maxDouble()) {
            data_ = badValue();
        }
    }
    return *this;
}

inline RWMultiPrecisionInt<1>&
RWMultiPrecisionInt<1>::operator*=(const RWMultiPrecisionInt<1>& lhs)
{
    if (!isGood() || !lhs.isGood()) {
        data_ = badValue();
    }
    else {
        data_ *= lhs.data_;
        if (data_ > maxDouble() || data_ < -maxDouble()) {
            data_ = badValue();
        }
    }
    return *this;
}

inline RWMultiPrecisionInt<1>&
RWMultiPrecisionInt<1>::operator/=(const RWMultiPrecisionInt<1>& lhs)
{
    RWMultiPrecisionInt<1> q, r;
    RWMultiPrecisionInt<1>::longDivide(*this, lhs, q, r);
    *this = q;

    return *this;
}

// Basic Relational operators -------------------------------------------
inline bool
operator==(const RWMultiPrecisionInt<1>& lhs, const RWMultiPrecisionInt<1>& rhs)
{
    return 0.0 == lhs.compareTo(rhs);
}

inline bool
operator<(const RWMultiPrecisionInt<1>& lhs, const RWMultiPrecisionInt<1>& rhs)
{
    return lhs.compareTo(rhs) < 0.0;
}

// Derived Relational operators -----------------------------------------
#if !defined(RWSTD_NO_NAMESPACE)
inline bool
operator>(const RWMultiPrecisionInt<1>& lhs, const RWMultiPrecisionInt<1>& rhs)
{
    return lhs.compareTo(rhs) > 0.0;
}

inline bool
operator!=(const RWMultiPrecisionInt<1>& lhs, const RWMultiPrecisionInt<1>& rhs)
{
    return lhs.compareTo(rhs) != 0.0;
}

inline bool
operator>=(const RWMultiPrecisionInt<1>& lhs, const RWMultiPrecisionInt<1>& rhs)
{
    return lhs.compareTo(rhs) >= 0.0;
}

inline bool
operator<=(const RWMultiPrecisionInt<1>& lhs, const RWMultiPrecisionInt<1>& rhs)
{
    return lhs.compareTo(rhs) <= 0.0;
}

#endif // no STL relationals

// Inline Binary Operators ------------------------------------------------
inline RWMultiPrecisionInt<1> operator+(const RWMultiPrecisionInt<1>& lhs,
                                        const RWMultiPrecisionInt<1>& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) += rhs;
}

inline RWMultiPrecisionInt<1> operator-(const RWMultiPrecisionInt<1>& lhs,
                                        const RWMultiPrecisionInt<1>& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) -= rhs;
}

inline RWMultiPrecisionInt<1> operator*(const RWMultiPrecisionInt<1>& lhs,
                                        const RWMultiPrecisionInt<1>& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) *= rhs;
}

inline RWMultiPrecisionInt<1> operator/(const RWMultiPrecisionInt<1>& lhs,
                                        const RWMultiPrecisionInt<1>& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) /= rhs;
}



//if VC 6.0 or 7.0
#if defined(_MSC_VER) && (_MSC_VER <= 1300)
inline bool
operator==(const RWMultiPrecisionInt<1>& lhs, const long double& rhs)
{
    return 0.0 == lhs.compareTo(RWMultiPrecisionInt<1>(rhs));
}

inline bool
operator<(const RWMultiPrecisionInt<1>& lhs, const long double& rhs)
{
    return lhs.compareTo(RWMultiPrecisionInt<1>(rhs)) < 0.0;
}

inline RWMultiPrecisionInt<1>&
RWMultiPrecisionInt<1>::operator+=(const long double& lhs)
{
    return *this += RWMultiPrecisionInt<1>(lhs);
}

inline RWMultiPrecisionInt<1>&
RWMultiPrecisionInt<1>::operator-=(const long double& lhs)
{
    return *this -= RWMultiPrecisionInt<1>(lhs);
}

inline RWMultiPrecisionInt<1>&
RWMultiPrecisionInt<1>::operator*=(const long double& lhs)
{
    return *this *= RWMultiPrecisionInt<1>(lhs);
}

inline RWMultiPrecisionInt<1>&
RWMultiPrecisionInt<1>::operator/=(const long double& lhs)
{
    return *this /= RWMultiPrecisionInt<1>(lhs);
}

inline RWMultiPrecisionInt<1> operator+(const RWMultiPrecisionInt<1>& lhs,
                                        const long double& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) += RWMultiPrecisionInt<1>(rhs);
}

inline RWMultiPrecisionInt<1> operator-(const RWMultiPrecisionInt<1>& lhs,
                                        const long double& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) -= RWMultiPrecisionInt<1>(rhs);
}

inline RWMultiPrecisionInt<1> operator*(const RWMultiPrecisionInt<1>& lhs,
                                        const long double& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) *= RWMultiPrecisionInt<1>(rhs);
}

inline RWMultiPrecisionInt<1> operator/(const RWMultiPrecisionInt<1>& lhs,
                                        const long double& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) /= RWMultiPrecisionInt<1>(rhs);
}

inline RWMultiPrecisionInt<1> operator+(const long double& lhs,
                                        const RWMultiPrecisionInt<1>& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) += rhs;
}

inline RWMultiPrecisionInt<1> operator-(const long double& lhs,
                                        const RWMultiPrecisionInt<1>& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) -= rhs;
}

inline RWMultiPrecisionInt<1> operator*(const long double& lhs,
                                        const RWMultiPrecisionInt<1>& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) *= rhs;
}

inline RWMultiPrecisionInt<1> operator/(const long double& lhs,
                                        const RWMultiPrecisionInt<1>& rhs)
{
    return RWMultiPrecisionInt<1>(lhs) /= rhs;
}
#endif // _MSC_VER && _MSC_VER < 1300
#endif // RW_CURRENCY_MP1INT_H
