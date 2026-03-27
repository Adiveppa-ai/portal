#ifndef RW_CURRENCY_DIVEXCHANGE_CC
#define RW_CURRENCY_DIVEXCHANGE_CC

/***************************************************************************
 *
 * File:  divexchange.cc
 *
 * Implementations for the class RWDivisionExchange and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/divexchange.cc#1 $
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
#ifndef RW_MONEY_DIVEXCHANGE_CC
#  define RW_MONEY_DIVEXCHANGE_CC
#endif

#include <rw/dcmlerr.h>

template< class T >
const char* RWDivisionExchange<T>::exchangeMethodName
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
;
#else
    = "RWBilateralDivision";
#endif


template< class T >
RWDivisionExchange<T>::RWDivisionExchange()
{
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
    exchangeMethodName = "RWBilateralDivision";
#else
    ;
#endif

}


template< class T >
RWDivisionExchange<T>::RWDivisionExchange(const RWDivisionExchange<T>& e)
    : RWBilateralExchange<T>(e)
{
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
    e.exchangeMethodName = exchangeMethodName;
#else
    ;
#endif

}


template< class T >
RWDivisionExchange<T>::RWDivisionExchange(const RWCString& source,
        const RWCString& target,
        double           convFact)
    : RWBilateralExchange<T>(source, target, convFact)
{
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
    exchangeMethodName = "RWBilateralDivision";
#else
    ;
#endif

}


template< class T >
RWDivisionExchange<T>::RWDivisionExchange(const RWExchangeRate& er)
    : RWBilateralExchange<T>(er)
{
    ;
}


template< class T >
RWDivisionExchange<T>& RWDivisionExchange<T>::operator=(const RWDivisionExchange<T>& t)
{
    if (&t != this) {
        RWBilateralExchange<T>::operator=(t);
    }

    return *this;
}


template< class T >
RWExchangeImpl<T>* RWDivisionExchange<T>::clone() const
{
    return (new RWDivisionExchange<T>(*this));
}

// Sorry about all the this-> crap in the following. HP aCC gives these "future error"
// warnings if they are not there (something about the variable doesn't depend on the
// template type parameter so it won't be looked up when templates are generated?)
template< class T >
RWMoney<T> RWDivisionExchange<T>::exchange(const RWMoney<T>& src) const
{
    if (this->source_.compareTo(src.currency(), RWCString::ignoreCase) != 0) {
        RWTHROW(RWExternalErr(RWMessage(RWDCML_EXCHGSOURCEDIFF)));
    }

    T newAmount = src.amount() / this->convFactor_;
    return RWMoney<T>(newAmount, this->target_);
}


// Some compilers will not generate symbols for the static const data member
// exchangeMethodName.  You must explicitly reference them somewhere in the
// compilation unit to avoid unresolved symbol errors.  Unfortunately this means
// that RWDivisionExchange<T> is supported for SunPro only with the types
// listed below.
#if defined(__SUNPRO_CC)
#  include <rw/currency/decimal.h>
#  include <rw/currency/mp1int.h>
#  include <rw/currency/mp2int.h>
#  include <rw/currency/mp3int.h>

static RWCString rwInitDivName1__ = RWDivisionExchange< RWDecimal<RWMP1Int> >::exchangeMethodName;
static RWCString rwInitDivName2__ = RWDivisionExchange< RWDecimal<RWMP2Int> >::exchangeMethodName;
static RWCString rwInitDivName3__ = RWDivisionExchange< RWDecimal<RWMP3Int> >::exchangeMethodName;
static RWCString rwInitDivNameDbl__ = RWDivisionExchange<double>::exchangeMethodName;
#endif

#endif // RW_CURRENCY_DIVEXCHANGE_CC
