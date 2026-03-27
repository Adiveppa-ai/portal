#ifndef RW_CURRENCY_MONEY_H
#define RW_CURRENCY_MONEY_H

/**************************************************************************
 *
 * Definition of RWMoney and supporting classes.
 *
 * $Id: //spro/rel2016.1/rw/currency/money.h#1 $
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
 **************************************************************************/

/* for backward compatibility */
#ifndef RW_MONEY_MONEY_H
#  define RW_MONEY_MONEY_H
#endif

#include <rw/currency/decimal.h>
#include <rw/dcmldefs.h>
#include <rw/dcmlerr.h>
#include <rw/cstring.h>
#include <rw/rwfile.h>
#include <rw/vstream.h>


/**
 * \ingroup currency_money_group
 *
 * \brief
 * Represents a specified amount of money in a specified currency.
 *
 * Class RWMoney provides a mapping between an amount and a currency, by
 * encapsulating a decimal value and referencing a currency. In C++, the
 * value is an arbitrary decimal type specified as a template parameter.
 *
 * When RWMoney objects are used in arithmetic operations, all operands must
 * be the same currency. If the currencies for RWMoney operands used in the
 * same equation differ, the operator will throw an exception. Similarly,
 * all assignments to RWMoney objects must have the same currency as the
 * original object. If not, an exception is thrown.
 *
 * Operations between monies of different currencies may be performed using
 * class RWMoneyCalculator.
 *
 * \synopsis
 * #include <rw/currency/money.h>
 * RWMoney<double> m(1.25, "CAD");
 * \endsynopsis
 *
 * \example
 * Here is an example assignment and some arithmetic calculations:
 *
 * \code
 * .
 * .
 * .
 * RWMoney<RWDecimal64> x("1.23","USD"), y("9.87","USD"),
 * z("7.99","CAD");
 * RWMoney<RWDecimal64> s("0","USD");
 * s = x + y;  // Okay, same currencies
 * s = y - z;  // Error, different currencies. Exception thrown.
 * s = x;      // Okay, same currencies
 * s = z;      // Error, different currencies. Exception thrown.
 *
 * .
 * .
 * .
 * \endcode
 * \endexample
 */
template <class T>
class RWMoney
{
public:
    // Constructors ---------------------------------------------------------

    /**
     * Default constructor. Behavior is undefined.
     */
    RWMoney();

    /**
     * Copy constructor.
     */
    RWMoney(const RWMoney<T>& m);

    /**
     * Constructs a money object with the given amount and currency.
     */
    RWMoney(const T& amount, const RWCString& currencyMnemonic);

    /**
     * Constructs a money object with the given currency and amount equal to
     * zero.
     */
    RWMoney(const RWCString& currencyMnemonic);


    // Public member functions ----------------------------------------------

    /**
     * Returns the currency's mnemonic
     */
    RWCString currency() const;

    /**
     * Returns the amount.
     */
    T amount() const;

    /**
     * Sets the currency mnemonic
     */
    void setCurrency(const RWCString& currencyMnemonic);

    /**
     * Sets the amount.
     */
    void setAmount(const T& amount);

    /**
     * Returns negation of self. Returned money object will have the same
     * currency as self, but amount will be the negative of self.
     */
    RWMoney<T>& operator-();

    // Assignment operators

    /**
     * Sets contents of self to \a rhs.
     */
    RWMoney<T>& operator= (const RWMoney<T>& rhs);

    /**
     * Sets contents of self to self plus \a rhs.
     */
    RWMoney<T>& operator+=(const RWMoney<T>& rhs);

    /**
     * Sets contents of self to self minus \a rhs.
     */
    RWMoney<T>& operator-=(const RWMoney<T>& rhs);

    /**
     * Sets contents of self to self times \a rhs.
     */
    RWMoney<T>& operator*=(const T& rhs);

    /**
     * Sets contents of self to self divided by \a rhs.
     */
    RWMoney<T>& operator/=(const T& rhs);

    /**
     * Persist to a virtual stream.
     */
    void saveOn(RWvostream&) const;

    /**
     * Persist to an RWFile.
     */
    void saveOn(RWFile&) const;

    /**
     * Restore from a virtual stream.
     */
    void restoreFrom(RWvistream&);

    /**
     * Restore from an RWFile.
     */
    void restoreFrom(RWFile&);

    // Provide some local static methods for globals to use, rather than
    // fighting with templated friends.

    static bool isEqual(const RWMoney<T>& lhs, const RWMoney<T>& rhs)
    {
        return
            (lhs.amount() == rhs.amount()) &&
            (lhs.currencyMnemonic_.compareTo(rhs.currencyMnemonic_, RWCString::ignoreCase) == 0);
    }

    static bool isLess(const RWMoney<T>& lhs, const RWMoney<T>& rhs)
    {
        RWMoney<T>::checkCurrenciesEqual(lhs, rhs);
        return (lhs.amount_ < rhs.amount_);
    }

private: // data
    T amount_;
    RWCString currencyMnemonic_;

private: // methods
    static void checkCurrenciesEqual(const RWMoney<T>& lhs, const RWMoney<T>& rhs)
    {
        if (lhs.currencyMnemonic_.compareTo(rhs.currencyMnemonic_, RWCString::ignoreCase) != 0) {
            RWTHROW(RWExternalErr(RWMessage(RWDCML_CURRENCIESDIFF,
                                            lhs.currencyMnemonic_.data(), rhs.currencyMnemonic_.data())));
        }
        return;
    }
};


// Global comparison operators --------------------------------------------

/**
 * \relates RWMoney
 * Equality operator.
 */
template <class T>
inline bool RW_DCML_MEMBER_EXPORT operator==(const RWMoney<T>& l, const RWMoney<T>& r)
{
    return RWMoney<T>::isEqual(l, r);
}

/**
 * \relates RWMoney
 * Less than operator.
 */
template <class T>
inline bool RW_DCML_MEMBER_EXPORT operator<(const RWMoney<T>& l, const RWMoney<T>& r)
{
    return RWMoney<T>::isLess(l, r);
}

#if !defined(RWSTD_NO_NAMESPACE)
/**
 * \relates RWMoney
 * Greater than operator.
 */
template <class T>
inline bool RW_DCML_MEMBER_EXPORT operator>(const RWMoney<T>& lhs, const RWMoney<T>& rhs)
{
    return (rhs < lhs);
}

/**
 * \relates RWMoney
 * Inequality operator.
 */
template <class T>
inline bool RW_DCML_MEMBER_EXPORT operator!=(const RWMoney<T>& lhs, const RWMoney<T>& rhs)
{
    return !(lhs == rhs);
}

/**
 * \relates RWMoney
 * Greater than or equal to operator.
 */
template <class T>
inline bool RW_DCML_MEMBER_EXPORT operator>=(const RWMoney<T>& lhs, const RWMoney<T>& rhs)
{
    return !(lhs < rhs);
}

/**
 * \relates RWMoney
 * Less than or equal to operator.
 */
template <class T>
inline bool RW_DCML_MEMBER_EXPORT operator<=(const RWMoney<T>& lhs, const RWMoney<T>& rhs)
{
    return !(lhs > rhs);
}
#endif  // not using STL comparitors

/**
 * \relates RWMoney
 * Subtraction operator.
 */
template <class T>
inline RWMoney<T> RW_DCML_MEMBER_EXPORT operator-(const RWMoney<T>& lhs, const RWMoney<T>& rhs);

/**
 * \relates RWMoney
 * Addition operator.
 */
template <class T>
inline RWMoney<T> RW_DCML_MEMBER_EXPORT operator+(const RWMoney<T>& lhs, const RWMoney<T>& rhs);

/**
 * \relates RWMoney
 * Multiplication operator.
 */
template <class T>
inline RWMoney<T> RW_DCML_MEMBER_EXPORT operator*(const RWMoney<T>& lhs, const T& rhs);

/**
 * \relates RWMoney
 * Multiplication operator.
 */
template <class T>
inline RWMoney<T> RW_DCML_MEMBER_EXPORT operator*(const T& lhs, const RWMoney<T>& rhs);

/**
 * \relates RWMoney
 * Division operator.
 */
template <class T>
inline RWMoney<T> RW_DCML_MEMBER_EXPORT operator/(const RWMoney<T>& lhs, const T& rhs);

// Inline member function definitions for class RWMoney<T>.
// Unary minus (negation) -------------------------------------------------
template <class T>
inline RWMoney<T>& RWMoney<T>::operator-()
{
    amount_ = -amount_;
    return *this;
}


// Assignment operators ---------------------------------------------------
template <class T>
inline RWMoney<T>& RWMoney<T>::operator=(const RWMoney<T>& rhs)
{
    if (this != &rhs) {
        amount_ = rhs.amount_;
        currencyMnemonic_ = rhs.currencyMnemonic_;
    }
    return *this;
}

template <class T>
inline RWMoney<T>& RWMoney<T>::operator+=(const RWMoney<T>& rhs)
{
    checkCurrenciesEqual(*this, rhs);
    amount_ += rhs.amount_;
    return *this;
}

template <class T>
inline RWMoney<T>& RWMoney<T>::operator-=(const RWMoney<T>& rhs)
{
    checkCurrenciesEqual(*this, rhs);
    amount_ -= rhs.amount_;
    return *this;
}

template <class T>
inline RWMoney<T>& RWMoney<T>::operator*=(const T& rhs)
{
    amount_ *= rhs;
    return *this;
}

template <class T>
inline RWMoney<T>& RWMoney<T>::operator/=(const T& rhs)
{
    amount_ /= rhs;
    return *this;
}

// Set and get methods.
template <class T>
inline RWCString RWMoney<T>::currency() const
{
    return currencyMnemonic_;
}

template <class T>
inline T RWMoney<T>::amount() const
{
    return amount_;
}

template <class T>
inline void RWMoney<T>::setCurrency(const RWCString& currencyMnemonic)
{
    currencyMnemonic_ = currencyMnemonic;
}

template <class T>
inline void RWMoney<T>::setAmount(const T& amount)
{
    amount_ = amount;
}

// Global arithmetic operators --------------------------------------------

template <class T> inline  RWMoney<T> RW_DCML_MEMBER_EXPORT operator-(const RWMoney<T>& lhs, const RWMoney<T>& rhs)
{
    return RWMoney<T>(lhs) -= rhs;
}

template <class T> inline  RWMoney<T> RW_DCML_MEMBER_EXPORT operator+(const RWMoney<T>& lhs, const RWMoney<T>& rhs)
{
    return RWMoney<T>(lhs) += rhs;
}

template <class T> inline  RWMoney<T> RW_DCML_MEMBER_EXPORT operator*(const RWMoney<T>& lhs, const T& rhs)
{
    return RWMoney<T>(lhs) *= rhs;
}

template <class T> inline  RWMoney<T> RW_DCML_MEMBER_EXPORT operator*(const T& lhs, const RWMoney<T>& rhs)
{
    return RWMoney<T>(rhs) *= lhs;
}

template <class T> inline  RWMoney<T> RW_DCML_MEMBER_EXPORT operator/(const RWMoney<T>& lhs, const T& rhs)
{
    return RWMoney<T>(lhs) /= rhs;
}

// Global shift operators -------------------------------------------------

/**
 * \relates RWMoney
 * Saves the object to a virtual stream.
 */
template <class T>
inline RWvostream& RW_DCML_MEMBER_EXPORT operator<<(RWvostream& strm, const RWMoney<T>& n)
{
    n.saveOn(strm);
    return strm;
}

/**
 * \relates RWMoney
 * Restores a object from a virtual stream.
 */
template <class T>
inline RWvistream& RW_DCML_MEMBER_EXPORT operator>>(RWvistream& strm, RWMoney<T>& n)
{
    n.restoreFrom(strm);
    return strm;
}

/**
 * \relates RWMoney
 * Saves the object to an RWFile.
 */
template <class T>
inline RWFile& RW_DCML_MEMBER_EXPORT operator<<(RWFile& f, const RWMoney<T>& n)
{
    n.saveOn(f);
    return f;
}

/**
 * \relates RWMoney
 * Restores a object from an RWFile.
 */
template <class T>
inline RWFile& RW_DCML_MEMBER_EXPORT operator>>(RWFile& f, RWMoney<T>& n)
{
    n.restoreFrom(f);
    return f;
}

/**
 * \relates RWMoney
 * Rounds the amount to the indicated number of decimal places. See the
 * description of class RWMoneyCalculator for a discussion of the available
 * rounding methods.
 */
template <class T>
RWMoney<T> round(const RWMoney<T>& x, unsigned int places);

template <class M>
inline RWDecimal<M> rw_money_round(const RWDecimal<M>& x, unsigned int n)
{
    return round(x, (int)n, RWDecimalBase::PLAIN);
}


inline double rw_money_round(double x, unsigned int n)
{
    RWDecimal< RWMP1Int> xDecimal = RWDecimal<RWMP1Int>::from(x);
    return static_cast<double>(toDouble(round(xDecimal, (int)n, RWDecimalBase::PLAIN)));
}

#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/money.cc>
#endif

#endif // RW_CURRENCY_MONEY_H
