#ifndef RW_CURRENCY_MONEYCALC_CC
#define RW_CURRENCY_MONEYCALC_CC

/***************************************************************
 *
 * Implementation of the RWMoneyCalculator class
 *
 * $Id: //spro/rel2016.1/rw/currency/moneycalc.cc#1 $
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
 ***************************************************************/

/* for backward compatibility */
#ifndef RW_MONEY_MONEYCALC_CC
#  define RW_MONEY_MONEYCALC_CC
#endif

#include <rw/currency/currexchange.h>
#include <rw/currency/decimal.h>
#include <rw/currency/mpint.h>

// Rounding functions
template< class M >
RWDecimal<M> rw_round(const RWDecimal<M>& x, unsigned int n,
                      int rm, unsigned int roundDigit)
{
    // xlC cannot make the conversion from unsigned to int.  So we
    // need the casts in the following
    switch (rm) {
        case RWMoneyCalculator< RWDecimal<M> >::up:
            return round(x, (int)n, RWDecimalBase::UP, roundDigit);

        case RWMoneyCalculator< RWDecimal<M> >::down:
            return round(x, (int)n, RWDecimalBase::DOWN, roundDigit);

        case RWMoneyCalculator< RWDecimal<M> >::plain:
            return round(x, (int)n, RWDecimalBase::PLAIN, roundDigit);

        case RWMoneyCalculator< RWDecimal<M> >::bankers:
            return round(x, (int)n, RWDecimalBase::BANKERS, roundDigit);

        default:
            return x;
    }
}

long double rw_round(double x, unsigned int n, int method,
                     unsigned int roundDigit)
{
    RWDecimal< RWMP1Int> xDecimal = RWDecimal<RWMP1Int>::from(x);
    switch (method) {
        case RWMoneyCalculator< RWDecimal<RWMP1Int> >::up:
            return toDouble(round(xDecimal, (int)n, RWDecimalBase::UP, roundDigit)) ;

        case RWMoneyCalculator< RWDecimal<RWMP1Int> >::down:
            return toDouble(round(xDecimal, (int)n, RWDecimalBase::DOWN, roundDigit)) ;

        case RWMoneyCalculator< RWDecimal<RWMP1Int> >::plain:
            return toDouble(round(xDecimal, (int)n, RWDecimalBase::PLAIN, roundDigit)) ;

        case RWMoneyCalculator< RWDecimal<RWMP1Int> >::bankers:
            return toDouble(round(xDecimal, (int)n, RWDecimalBase::BANKERS, roundDigit)) ;

        default:
            return x;
    }
}

// Constructors ---------------------------------------------------------------

// Default ctor
template< class T >
RWMoneyCalculator<T>::RWMoneyCalculator()
    : roundDigit_(5)
    , accuracy_(2)
    , roundingMethod_(noRounding)
    , conversionType_(noConversion)
{
    ;
}



// Copy ctor
template< class T >
RWMoneyCalculator<T>::RWMoneyCalculator(const RWMoneyCalculator<T>& c)
    : roundDigit_(c.roundDigit_), accuracy_(c.accuracy_), roundingMethod_(c.roundingMethod_),
      conversionType_(c.conversionType_), exchangeFactory_(c.exchangeFactory_),
      baseCurrency_(c.baseCurrency_)
{
    ;
}


// Public member functions -------------------------------------------------

template< class T >
RWMoney<T> RWMoneyCalculator<T>::round(const RWMoney<T>& x) const
{
    return RWMoney<T>(static_cast<T>(
                          rw_round(x.amount(), accuracy_, (int)roundingMethod_, roundDigit_)),
                      x.currency());
}


// Arithmetic functions
template< class T >
RWMoney<T> RWMoneyCalculator<T>::add(const RWMoney<T>& x, const RWMoney<T>& y) const
{
    if (conversionType_ == noConversion ||
            y.currency().compareTo(x.currency(), RWCString::ignoreCase) == 0) {
        if (roundingMethod_ == noRounding) {
            return (x + y);
        }
        return round(x + y);
    }

    // conversion needed
    RWMoney<T> xConv, yConv;
    doConversions(x, y, xConv, yConv);
    if (roundingMethod_ == noRounding) {
        return (xConv + yConv);
    }
    return round(xConv + yConv);
}


template< class T >
RWMoney<T> RWMoneyCalculator<T>::subtract(const RWMoney<T>& x, const RWMoney<T>& y) const
{
    if (conversionType_ == noConversion ||
            y.currency().compareTo(x.currency(), RWCString::ignoreCase) == 0) {
        if (roundingMethod_ == noRounding) {
            return (x - y);
        }
        return round(x - y);
    }

    // conversion needed
    RWMoney<T> xConv, yConv;
    doConversions(x, y, xConv, yConv);
    if (roundingMethod_ == noRounding) {
        return (xConv - yConv);
    }
    return round(xConv - yConv);
}


// Private helper functions

// Convert operands so that they are both of the same currency based on the
// conversion option set for the calculator.
template< class T >
void RWMoneyCalculator<T>::doConversions(const RWMoney<T>& lhs, const RWMoney<T>& rhs,
        RWMoney<T>& lhsConv, RWMoney<T>& rhsConv) const
{
    switch (conversionType_) {
        case base:
            convertToBase(lhs, rhs, lhsConv, rhsConv);
            break;

        case target:
            rhsConv = rhs;
            if (lhs.currency().compareTo(rhs.currency(), RWCString::ignoreCase) != 0) {
                RWExchange<T> ce =
                    exchangeFactory_.getExchange(lhs.currency(), rhs.currency());
                if (!ce.isValid()) {
                    RWTHROW(RWInternalErr(RWMessage(RWDCML_NOEXCHGOBJ)));
                }
                lhsConv = ce.exchange(lhs);
            }
            else {
                lhsConv = lhs;
            }
            break;

        case source:
            lhsConv = lhs;
            if (rhs.currency().compareTo(lhs.currency(), RWCString::ignoreCase) != 0) {
                RWExchange<T> ce =
                    exchangeFactory_.getExchange(rhs.currency(), lhs.currency());
                if (!ce.isValid()) {
                    RWTHROW(RWInternalErr(RWMessage(RWDCML_NOEXCHGOBJ)));
                }
                rhsConv = ce.exchange(rhs);
            }
            else {
                rhsConv = rhs;
            }
            break;

        default:
            rhsConv = rhs;
            lhsConv = lhs;
    }
}


// Convert both arguments to the base currency (if necessary).
template< class T >
void RWMoneyCalculator<T>::convertToBase(const RWMoney<T>& a, const RWMoney<T>& b,
        RWMoney<T>& aBase, RWMoney<T>& bBase) const
{
    if (baseCurrency_.compareTo(a.currency(), RWCString::ignoreCase) == 0) {
        aBase = a;
    }
    else {
        RWExchange<T> ce = exchangeFactory_.getExchange(a.currency(), baseCurrency_);
        if (!ce.isValid()) {
            RWTHROW(RWInternalErr(RWMessage(RWDCML_NOEXCHGOBJ)));
        }
        aBase = ce.exchange(a);
    }
    if (baseCurrency_.compareTo(b.currency(), RWCString::ignoreCase) == 0) {
        bBase = b;
    }
    else {
        RWExchange<T> ce = exchangeFactory_.getExchange(b.currency(), baseCurrency_);
        if (!ce.isValid()) {
            RWTHROW(RWInternalErr(RWMessage(RWDCML_NOEXCHGOBJ)));
        }
        bBase = ce.exchange(b);
    }
}


// Public member operators
template< class T >
RWMoneyCalculator<T>& RWMoneyCalculator<T>::operator=(const RWMoneyCalculator<T>& c)
{
    if (&c != this) {
        roundDigit_ = c.roundDigit_;
        accuracy_ = c.accuracy_;
        roundingMethod_ = c.roundingMethod_;
        conversionType_ = c.conversionType_;
        exchangeFactory_ = c.exchangeFactory_;
        baseCurrency_ = c.baseCurrency_;
    }
    return *this;
}

#endif // RW_CURRENCY_MONEYCALC_CC
