#ifndef RW_CURRENCY_BIEXCHANGE_CC
#define RW_CURRENCY_BIEXCHANGE_CC

/***************************************************************************
 *
 * File:  biexchange.cc
 *
 * Implementations for the class RWBilateralExchange and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/biexchange.cc#1 $
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
#ifndef RW_MONEY_BIEXCHANGE_CC
#  define RW_MONEY_BIEXCHANGE_CC
#endif

#include <rw/currency/exchgrate.h>
#include <rw/dcmldefs.h>


template< class T >
RWBilateralExchange<T>::RWBilateralExchange()
    : convFactor_(0.0)
{
    ;
}


template< class T >
RWBilateralExchange<T>::RWBilateralExchange(const RWBilateralExchange<T>& e)
    : RWExchangeImpl<T>(e), convFactor_(e.convFactor_)
{
    ;
}


template< class T >
RWBilateralExchange<T>::RWBilateralExchange(const RWCString& source,
        const RWCString& target,
        double convFact)
    : RWExchangeImpl<T>(source, target), convFactor_(convFact)
{
    ;
}


template< class T >
RWBilateralExchange<T>::RWBilateralExchange(const RWExchangeRate& er)
    : RWExchangeImpl<T>(er.source(), er.target()), convFactor_(er.conversionFactor())
{
    ;
}


template< class T >
RWBilateralExchange<T>& RWBilateralExchange<T>::operator=(const RWBilateralExchange<T>& t)
{
    if (&t != this) {
        RWExchangeImpl<T>::operator=(t);
        convFactor_ = t.convFactor_;
    }

    return *this;
}

// Sorry about all the this-> crap in the following. HP aCC gives these "future error"
// warnings if they are not there (something about the variable doesn't depend on the
// template type parameter so it won't be looked up when templates are generated?)
template< class T >
RWExchangeRate RWBilateralExchange<T>::exchangeRate() const
{
    return RWExchangeRate(this->source_, this->target_, this->convFactor_);
}


template< class T >
void RWBilateralExchange<T>::setExchangeRate(const RWExchangeRate& er)
{
    this->source_ = er.source();
    this->target_ = er.target();
    this->convFactor_ = er.conversionFactor();
}

#endif // RW_CURRENCY_BIEXCHANGE_CC
