#ifndef RW_CURRENCY_FIXEDDEC_CC
#define RW_CURRENCY_FIXEDDEC_CC

/* for backward compatibility */
#ifndef RW_MONEY_FIXEDDEC_CC
#  define RW_MONEY_FIXEDDEC_CC
#endif

/******************************************************************
 *
 * Implementation of RWFixedDecimal and related classes.
 *
 * $Id: //spro/rel2016.1/rw/currency/fixeddec.cc#1 $
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
 ******************************************************************
 *
 * Note:
 *
 * For some reason the HPUX aCC compiler (ver 1.0.6) gives an
 * error (future) that the member data exponent_ and mantissa_are
 * are undeclared, because, perhaps we forgot to make it depend on
 * the template type parameters.  I'm not sure what this means but
 * the message goes away when we qualify these variables with a
 * "this->".  Hence all the really unnecessary this->'s in the
 * following code.
 *
 ******************************************************************/

// Initialized static data
template< class M >
const RWFixedDecimal<M> RWFixedDecimal<M>::null = RWFixedDecimal<M>(RWDecimalBase::nullstate);

template< class M >
const RWFixedDecimal<M> RWFixedDecimal<M>::missing = RWFixedDecimal<M>(RWDecimalBase::missingstate);

template< class M >
const RWFixedDecimal<M> RWFixedDecimal<M>::NaN = RWFixedDecimal<M>(RWDecimalBase::NaNstate);

template< class M >
const RWFixedDecimal<M> RWFixedDecimal<M>::SNaN = RWFixedDecimal<M>(RWDecimalBase::SNaNstate);

template< class M >
const RWFixedDecimal<M> RWFixedDecimal<M>::infinity = RWFixedDecimal<M>(RWDecimalBase::infinitystate);

#if !defined(RW_DISABLE_DEPRECATED)

// g++ must use static functions to return the values.
template< class M >
RWFixedDecimal<M> RWFixedDecimal<M>::nullValue()
{
    static const RWFixedDecimal<M> n = RWFixedDecimal<M>(RWDecimalBase::nullstate);
    return n;
}

template< class M >
RWFixedDecimal<M> RWFixedDecimal<M>::missingValue()
{
    static const RWFixedDecimal<M> n = RWFixedDecimal<M>(RWDecimalBase::missingstate);
    return n;
}

template< class M >
RWFixedDecimal<M> RWFixedDecimal<M>::NaNValue()
{
    static const RWFixedDecimal<M> n = RWFixedDecimal<M>(RWDecimalBase::NaNstate);
    return n;
}

template< class M >
RWFixedDecimal<M> RWFixedDecimal<M>::SNaNValue()
{
    static const RWFixedDecimal<M> n = RWFixedDecimal<M>(RWDecimalBase::SNaNstate);
    return n;
}

template< class M >
RWFixedDecimal<M> RWFixedDecimal<M>::infinityValue()
{
    static const RWFixedDecimal<M> n = RWFixedDecimal<M>(RWDecimalBase::infinitystate);
    return n;
}

#endif

template< class M >
RWFixedDecimal<M>& RWFixedDecimal<M>::operator=(const RWFixedDecimal<M>& x)
{
    if (!x.state_) {
        if (this->state_) {
            // Do not allow the exponent to exceed maxDigits, or overflow may occur
            // on reassignment.
            if (x.exponent_ > x.maxDigits()) {
                this->exponent_ = RWFixedDecimal<M>::maxDigits();
                this->mantissa_ = x.mantissa_.decimalShiftRight(static_cast<unsigned>(x.exponent_ - x.maxDigits()));
            }
            else {
                this->mantissa_ = x.mantissa_;
                this->exponent_ = x.exponent_;
            }
        }
        else {
            if (this->exponent_ == x.exponent_) {
                this->mantissa_ = x.mantissa_;
            }
            else if (this->exponent_ > x.exponent_) {
                this->mantissa_ = x.mantissa_.decimalShiftLeft(static_cast<unsigned>(this->exponent_ - x.exponent_));
                if (!this->mantissa_.isGood()) {
                    RWDecimal<M>::overflow(RWDecimalBase::assign, RWFixedDecimal<M>(RWDecimalBase::nullstate), x,
                                           RWMessage(RWDCML_ASSIGNOVER, RWDecimal<M>::classname));
                }
            }
            else {
                RWFixedDecimal<M> tmp = round(x, this->exponent_);
                this->mantissa_ = tmp.mantissa_;
            }
        }
    }
    else if (x.state_ == RWDecimalBase::infinitystate) {
        this->mantissa_ = x.mantissa_;
    }

    this->state_ = x.state_;

    return *this;
}

#endif // RW_CURRENCY_FIXEDDEC_CC
