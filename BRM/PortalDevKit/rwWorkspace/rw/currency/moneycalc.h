#ifndef RW_CURRENCY_MONEYCALC_H
#define RW_CURRENCY_MONEYCALC_H

/***************************************************************************
 *
 * File:  moneycalc.h
 *
 * Declarations for the class RWMoneyCalculator and related global functions
 *
 * $Id: //spro/rel2016.1/rw/currency/moneycalc.h#1 $
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
#ifndef RW_MONEY_MONEYCALC_H
#  define RW_MONEY_MONEYCALC_H
#endif

#include <rw/currency/exchgfact.h>
#include <rw/currency/money.h>
#include <rw/dcmldefs.h>


/**
 * \ingroup currency_money_calculator
 * \class RWMoneyCalculator
 *
 * \brief
 * Performs algebraic operations when the money operands in an equation are
 * not of the same currency.
 *
 * Class RWMoneyCalculator can perform algebraic operations when the money
 * operands in the equation are not of the same currency. Because some
 * conversion from one currency to another must occur before such an
 * operation can be carried out, RWMoneyCalculator lets you specify a
 * <em>conversion policy</em> for calculator objects.
 *
 * \synopsis
 * #include <rw/currency/moneycalc.h>
 * RWMoneyCalculator<double>
 *            calc(RWMoneyCalculator<double>::plain, 2u);
 * \endsynopsis
 *
 * <h4>Conversion Policies</h4>
 * Four conversion policies are available:
 *
 * - <b>No Conversion</b>. Any operations performed on monies of different
 * currencies will throw an exception.
 *
 * - <b>Base Currency Conversion</b>. When arithmetic operations are
 * performed on monies of different currencies both operands will first be
 * converted to the base currency. The operation will then be performed and
 * the result returned in the base currency.
 *
 * - <b>Target Currency Conversion</b>. When arithmetic operations are
 * performed on monies of different currencies, the source operand (first
 * argument) is converted to the target operand (second argument) currency
 * and the result is returned in the target currency.
 *
 * - <b>Source Currency Conversion</b>. When arithmetic operations are
 * performed on monies of different currencies, the target operand (second
 * argument) is converted to the source operand (first argument) currency
 * and the result is returned in the source currency.
 *
 * Conversions are carried out through the RWExchangeFactory object that is
 * associated with the particular calculator object.
 *
 * <h4>Rounding Policies</h4>
 * In addition to setting the conversion policy, you must set a rounding
 * policy and an accuracy for the calculator. The accuracy specifies how
 * many digits to the right of the decimal points should be reported.
 * Rounding a negative number is equivalent to rounding the absolute value
 * of the negative number, then multiplying the result by negative one.
 * Briefly, the available rounding policies available for RWMoneyCalculator
 * are:
 *
 * - <b>Don't round</b>. No rounding will occur, and accuracy is ignored.
 *
 * - <b>Round up</b>. Always add one to the digit at the specified accuracy
 * decimal place, then truncate any digits to the right.
 *
 * - <b>Round down</b>. Truncate all digits to the right of the specified
 * accuracy decimal place.
 *
 * - <b>Plain</b>. If the digit one to the right of the specified accuracy
 * decimal place is greater than a comparison digit, increase the digit at
 * the accuracy position by one and truncate all numbers to the right.
 * Otherwise, truncate all digits to the right of the accuracy place digit.
 *
 * - <b>Bankers</b>. If the digit one to the right of the specified accuracy
 * decimal place is equal to a comparison digit, round so that the digit at
 * the specified accuracy position is even. If the digit one to the right of
 * the specified accuracy position is greater than a comparison digit,
 * increment by one the digit at the specified accuracy position. If the
 * digit one to the right of the specified accuracy position is less than a
 * comparison digit, truncate all numbers to the right of the accuracy
 * position.
 */
template< class T >
class RWMoneyCalculator
{
public:

    /**
     * Enumeration for rounding method. For details see the Rounding
     * Policies section.
     */
    enum RoundMethod {

        /**
         * No rounding
         */
        noRounding,

        /**
         * Round up
         */
        up,

        /**
         * Round down
         */
        down,

        /**
         * Plain
         */
        plain,

        /**
         * Bankers
         */
        bankers
    };

    /**
     * Enumeration for the currency conversion policy. For details see the
     * Conversion Policies section.
     */
    enum ConversionType {

        /**
         * No Conversion
         */
        noConversion,

        /**
         * Base currency conversion
         */
        base,

        /**
         * Target currency conversion
         */
        target,

        /**
         * Source currency conversion
         */
        source
    };

    // Constructors ----------------------------------------------------------

    /**
     * Constructs a calculator object that does no rounding or currency
     * conversion.
     */
    RWMoneyCalculator();

    /**
     * Copy constructor.
     */
    RWMoneyCalculator(const RWMoneyCalculator<T>& calc);

    /**
     * Construct a calculator that does rounding, but does not do currency
     * conversion.
     */
    RWMoneyCalculator(RoundMethod rm, unsigned int accuracy, unsigned int roundDigit = 5)
        : roundDigit_(roundDigit)
        , accuracy_(accuracy)
        , roundingMethod_(rm)
        , conversionType_(noConversion)
    {
        ;
    }

    /**
     * Construct a calculator that does currency conversion and rounding, if
     * other than the default #RoundMethod is provided.
     */
    RWMoneyCalculator(const RWExchangeFactory<T>& ef, ConversionType ct, const RWCString& baseCurr = "",
                      RoundMethod rm = noRounding, unsigned int accuracy = 2, unsigned int roundDigit = 5)
        : roundDigit_(roundDigit), accuracy_(accuracy), roundingMethod_(rm),
          conversionType_(ct), exchangeFactory_(ef), baseCurrency_(baseCurr)
    {
        ;
    }

    /**
     * Same as above, except use the given exchange rate table to construct
     * the exchange factory argument.
     */
    RWMoneyCalculator(const RWExchangeRateTable& ert, ConversionType ct, const RWCString& baseCurr = "",
                      RoundMethod rm = noRounding, unsigned int accuracy = 2, unsigned int roundDigit = 5)
        : roundDigit_(roundDigit), accuracy_(accuracy), roundingMethod_(rm),
          conversionType_(ct), baseCurrency_(baseCurr)
    {
        exchangeFactory_ = RWExchangeFactory<T>(ert);
    }

    // Public Member Functions --------------------------------------------------

    // Accessors

    /**
     * Returns the current value for the round digit.
     */
    unsigned int roundDigit() const
    {
        return roundDigit_;
    }

    /**
     * Returns the accuracy for this RWMoneyCalculator object.
     */
    unsigned int accuracy() const
    {
        return accuracy_;
    }

    /**
     * Returns the current conversion type for this RWMoneyCalculator
     * object.
     */
    ConversionType conversionType() const
    {
        return conversionType_;
    }

    /**
     * Returns the rounding method for this RWMoneyCalculator object.
     */
    RoundMethod roundMethod() const
    {
        return roundingMethod_;
    }

    /**
     * Returns the exchange factory that is being used by the calculator.
     */
    RWExchangeFactory<T> exchangeFactory() const
    {
        return exchangeFactory_;
    }

    /**
     * Returns the exchange factory that is being used by the calculator.
     * This version may be used to modify the exchange factory.
     */
    RWExchangeFactory<T>& exchangeFactory()
    {
        return exchangeFactory_;
    }

    /**
     * Returns the currency that is used when the conversion type is set to
     * #base.
     */
    RWCString baseCurrency() const
    {
        return baseCurrency_;
    }

    // Mutators
    /**
     * Sets the value for the rounding digit. The default value is 5.
     */
    void setRoundDigit(unsigned int rd)
    {
        roundDigit_ = rd;
    }

    /**
     * Sets the accuracy value for this RWMoneyCalculator object.
     */
    void setAccuracy(unsigned int a)
    {
        accuracy_ = a;
    }

    /**
     * Sets the conversion type for this RWMoneyCalculator object.
     */
    void setConversionType(ConversionType ct)
    {
        conversionType_ = ct;
    }

    /**
     * Sets the rounding method for the calculator.
     */
    void setRoundMethod(RoundMethod rm)
    {
        roundingMethod_ = rm;
    }

    void setBaseCurrency(const RWCString& mnemonic)
    {
        baseCurrency_ = mnemonic;
    }

    /**
     * Sets the exchange factory used by the calculator.
     */
    void setExchangeFactory(const RWExchangeFactory<T>& f)
    {
        exchangeFactory_ = f;
    }

    /**
     * Rounds the provided RWMoney value according to the current rounding
     * method and accuracy for RWMoneyCalculator.
     */
    RWMoney<T> round(const RWMoney<T>&) const;

    /**
     * Adds the two RWMoney operands and returns the result.
     *
     * Addition and subtraction are allowed on monies of different currency
     * types if the conversion type for the calculator object is set to
     * #base, #target, or #source.
     */
    RWMoney<T> add(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const;

    /**
     * Subtracts the second operand from the first and returns the result.
     *
     * Addition and subtraction are allowed on monies of different currency
     * types if the conversion type for the calculator object is set to
     * #base, #target, or #source.
     */
    RWMoney<T> subtract(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const;

    /**
     * Multiplies the first operand by the second and returns the result.
     */
    RWMoney<T> multiply(const RWMoney<T>& lhs, const T& rhs) const;

    /**
     * Multiplies the first operand by the second and returns the result.
     */
    RWMoney<T> multiply(const T& lhs, const RWMoney<T>& rhs) const;

    /**
     * Divides the first operand by the second and returns the result.
     */
    RWMoney<T> divide(const RWMoney<T>& lhs, const T& rhs) const;

    /**
     * Returns the absolute value of the parameter.
     */
    RWMoney<T> abs(const RWMoney<T>& x) const;

    /**
     * Relational comparisons for monies of the same or different currency
     * types. If the currency types differ, the conversion type for the
     * calculator object must be set to #base, #target, or #source. This
     * allows the values to be converted before they are compared.
     */
    bool lessThan(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const;

    /**
     * \copydoc lessThan(const RWMoney<T>&, const RWMoney<T>&) const
     */
    bool lessThanOrEqual(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const;

    /**
     * Relational comparisons for monies of the same or different currency
     * types. If the currency types differ, the conversion type for the
     * calculator object must be set to #base, #target, or #source. This
     * allows the values to be converted before they are compared.
     */
    bool greaterThan(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const;

    /**
     * \copydoc greaterThan(const RWMoney<T>&, const RWMoney<T>&) const
     */
    bool greaterThanOrEqual(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const;

    /**
     * Tests for equality for monies of the same or different currency
     * types. If the currency types differ, the conversion type for the
     * calculator object must be set to #base, #target, or #source. This
     * allows the values to be converted before they are compared.
     */
    bool equal(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const;

    /**
     * Tests whether the indicated value is greater than zero.
     */
    bool greaterThanZero(const RWMoney<T>& x) const;

    /**
     * Tests whether the indicated value is less than zero.
     */
    bool lessThanZero(const RWMoney<T>& x) const;

    /**
     * Tests whether the indicated value is equal to zero.
     */
    bool isZero(const RWMoney<T>& x) const;

    /**
     * Compares whether the given values have the same currency type.
     */
    bool sameCurrency(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const
    {
        return (lhs.currency().compareTo(rhs.currency(), RWCString::ignoreCase) == 0);
    }


    // Public Member Operators -----------------------------------------------
    /**
     * Assignment operator.
     */
    RWMoneyCalculator<T>& operator=(const RWMoneyCalculator<T>&);

private:
    unsigned int         roundDigit_;
    unsigned int         accuracy_;
    RoundMethod          roundingMethod_;
    ConversionType       conversionType_;
    RWExchangeFactory<T> exchangeFactory_;
    RWCString            baseCurrency_;

    // Helper functions
    void convertToBase(const RWMoney<T>& a, const RWMoney<T>& b, RWMoney<T>& aBase, RWMoney<T>& bBase) const;
    void doConversions(const RWMoney<T>& a, const RWMoney<T>& b, RWMoney<T>& aConv, RWMoney<T>& bConv) const;
};


template< class T >
inline RWMoney<T> RWMoneyCalculator<T>::multiply(const RWMoney<T>& lhs, const T& rhs) const
{
    if (roundingMethod_ == noRounding) {
        return lhs * rhs;
    }
    return round(lhs * rhs);
}

template< class T >
inline RWMoney<T> RWMoneyCalculator<T>::multiply(const T& lhs, const RWMoney<T>& rhs) const
{
    return multiply(rhs, lhs);
}

template< class T >
inline RWMoney<T> RWMoneyCalculator<T>::divide(const RWMoney<T>& lhs, const T& rhs) const
{
    if (roundingMethod_ == noRounding) {
        return lhs / rhs;
    }
    return round(lhs / rhs);
}

template< class T >
inline RWMoney<T> RWMoneyCalculator<T>::abs(const RWMoney<T>& x) const
{
    T amt = x.amount() < T(0) ? -x.amount() : x.amount();
    return RWMoney<T>(amt, x.currency());
}

// Comparison Functions
template< class T >
inline bool RWMoneyCalculator<T>::lessThan(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const
{
    if (conversionType_ == noConversion) {
        return (lhs < rhs);
    }

    RWMoney<T> lhsConv, rhsConv;
    doConversions(lhs, rhs, lhsConv, rhsConv);
    return ((lhsConv.amount() < rhsConv.amount()) != 0);
}

template< class T >
inline bool RWMoneyCalculator<T>::lessThanOrEqual(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const
{
    return !lessThan(rhs, lhs);
}

template< class T >
inline bool RWMoneyCalculator<T>::greaterThan(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const
{
    return lessThan(rhs, lhs);
}

template< class T >
inline bool RWMoneyCalculator<T>::greaterThanOrEqual(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const
{
    return !lessThan(lhs, rhs);
}

template< class T >
inline bool RWMoneyCalculator<T>::equal(const RWMoney<T>& lhs, const RWMoney<T>& rhs) const
{
    if (conversionType_ == noConversion) {
        return (lhs == rhs);
    }

    RWMoney<T> lhsConv, rhsConv;
    doConversions(lhs, rhs, lhsConv, rhsConv);
    return ((lhsConv.amount() == rhsConv.amount()) != 0);
}

template< class T >
inline bool RWMoneyCalculator<T>::greaterThanZero(const RWMoney<T>& x) const
{
    return ((x.amount() > T(0)) != 0);
}

template< class T >
inline bool RWMoneyCalculator<T>::lessThanZero(const RWMoney<T>& x) const
{
    return ((x.amount() < T(0)) != 0);
}

template< class T >
inline bool RWMoneyCalculator<T>::isZero(const RWMoney<T>& x) const
{
    return ((x.amount() == T(0)) != 0);
}



// xlC Does not allow default values for parameters for template functions.
// So we gotta write two versions of each of the following functions.
template< class M >
RWDecimal<M> rw_round(const RWDecimal<M>&, unsigned int n, int roundMethod,
                      unsigned int roundDigit);

template< class M >
RWDecimal<M> rw_round(const RWDecimal<M>& x, unsigned int n, int roundMethod)
{
    return rw_round(x, n, roundMethod, 4U);
}

long double rw_round(double x, unsigned int n, int roundMethod,
                     unsigned int roundDigit);

long double rw_round(double x, unsigned int n, int roundMethod)
{
    return rw_round(x, n, roundMethod, 4U);
}


#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/moneycalc.cc>
#endif

#endif // RW_CURRENCY_MONEYCALC_H
