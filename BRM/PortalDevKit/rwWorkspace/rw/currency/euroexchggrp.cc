#ifndef RW_CURRENCY_EUROEXCHGGRP_CC
#define RW_CURRENCY_EUROEXCHGGRP_CC

/***************************************************************************
 *
 * File:  euroexchggrp.cc
 *
 * Implementations for the class RWEuroGroup
 *
 * $Id: //spro/rel2016.1/rw/currency/euroexchggrp.cc#1 $
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
 ***************************************************************************
 */

/* for backward compatibility */
#ifndef RW_MONEY_EUROEXCHGGRP_CC
#  define RW_MONEY_EUROEXCHGGRP_CC
#endif

#include <rw/currency/currexchange.h>
#include <rw/currency/euroexchggrp.h>
#include <rw/currency/exchgratetbl.h>
#include <rw/currency/triexchange.h>

// static group name
template< class T >
const char* RWEuroGroup<T>::groupName = "EuroTriangular";

// Constructors ------------------------------------------------------------

// copy ctor
template <class T>
RWEuroGroup<T>::RWEuroGroup(const RWEuroGroup<T>& g)
    : RWExchangeGroupImpl<T>(g)
    , euroCurrencies_(g.euroCurrencies_)
    , euroMnemonic_(g.euroMnemonic_)
{
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
    g.groupName = groupName;
#else
    ;
#endif
}


// construct from list of currencies
template <class T>
RWEuroGroup<T>::RWEuroGroup(const RWTValSlist<RWCString>& currs, const char* euro_mnemonic)
    : euroCurrencies_(currs), euroMnemonic_(euro_mnemonic)
{
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
    groupName = "EuroTriangular";
#else
    ;
#endif
}


// Public member functions -------------------------------------------------


template <class T>
bool RWEuroGroup<T>::containsCurrency(const RWCString& c) const
{
    // can't usr RWTValSlist's contains() method since it uses RWCString's == operator,
    // which is case sensitive.  We want case insensitive compares.
    RWTValSlist<RWCString>::const_iterator iter = euroCurrencies_.begin();
    for (; iter != euroCurrencies_.end(); ++iter) {
        if (c.compareTo(*iter, RWCString::ignoreCase) == 0) {
            return true;
        }
    }
    return false;
}


// The exchange rate table contains multiplicative exchange rates.  i.e. to
// convert an amount s in the source currency to an amount t in the target
// currency you would find the rate r for the source/target pair in the
// exchange rate table and multiply: t = s*t.
template <class T>
RWExchange<T> RWEuroGroup<T>::getExchange(const RWCString& srcMnemonic,
        const RWCString& targetMnemonic,
        const RWExchangeRateTable& rates) const
{
    // create an invalid exchange object (null impl)
    RWExchange<T> exchangeObject;

    if (containsCurrency(srcMnemonic) && containsCurrency(targetMnemonic)) {
        // look for multiplicative rates from the euro
        // to source and from the euro to target.
        RWExchangeRate euroToSrcRate, euroToTargetRate;
        if (rates.findExchangeRate(euroMnemonic_, srcMnemonic, euroToSrcRate) &&
                rates.findExchangeRate(euroMnemonic_, targetMnemonic, euroToTargetRate)) {
            // Found exchange rates. Create and set the impl for the exchange object
            // making it valid.
            RWTriangularExchange<T>* impl =
                new RWTriangularExchange<T>(euroToSrcRate.target(),
                                            euroToTargetRate.target(),
                                            euroMnemonic_,
                                            euroToSrcRate.conversionFactor(),
                                            euroToTargetRate.conversionFactor());
            exchangeObject.setImpl(impl);
        }
    }

    return exchangeObject;
}


template <class T>
bool RWEuroGroup<T>::addCurrency(const RWCString& c)
{
    if (containsCurrency(c)) {
        return false;
    }

    euroCurrencies_.insert(c);
    return true;
}


template <class T>
bool RWEuroGroup<T>::removeCurrency(const RWCString& c)
{
    // can't usr RWTValSlist's remove() method since it uses RWCString's == operator,
    // which is case sensitive.  We want case insensitive compares.
    for (size_t i = 0; i < euroCurrencies_.entries(); ++i) {

        // working around intel bug 416477: when trying to access euroCurrencies_[i],
        // icc complains that it cannot access members in private base
        // RW# 32294

#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER <= 1000) && defined(__linux)

        if (c.compareTo(euroCurrencies_.operator[](i), RWCString::ignoreCase) == 0)

#else

        if (c.compareTo(euroCurrencies_[i], RWCString::ignoreCase) == 0)

#endif

        {
            euroCurrencies_.removeAt(i);
            return true;
        }
    }
    return false;
}


template <class T>
void RWEuroGroup<T>::clear()
{
    euroCurrencies_.clear();
}


template <class T>
RWTValSlist<RWCString> RWEuroGroup<T>::getCurrencies() const
{
    return euroCurrencies_;
}


template <class T>
void RWEuroGroup<T>::setCurrencies(const RWTValSlist<RWCString>& c)
{
    euroCurrencies_ = c;
}


template <class T>
size_t RWEuroGroup<T>::numCurrencies() const
{
    return euroCurrencies_.entries();
}


template <class T>
RWExchangeGroup<T> RWEuroGroup<T>::create()
{
    RWExchangeGroupImpl<T>* i = new RWEuroGroup<T>;
    return RWExchangeGroup<T>(i);
}


template <class T>
RWExchangeGroup<T> RWEuroGroup<T>::create(std::istream& strm, const char* euroMnem)
{
    RWEuroGroup<T>* euroImpl = new RWEuroGroup<T>;
    strm >> (*euroImpl);
    euroImpl->setEuroMnemonic(euroMnem);
    return RWExchangeGroup<T>(euroImpl);
}


template <class T>
RWExchangeGroup<T> RWEuroGroup<T>::create(const RWTValSlist<RWCString>& euroCurrencies, const char* euroMnem)
{
    RWEuroGroup<T>* euroImpl = new RWEuroGroup<T>;
    euroImpl->setCurrencies(euroCurrencies);
    euroImpl->setEuroMnemonic(euroMnem);
    return RWExchangeGroup<T>(euroImpl);
}

// Assignment operator
template <class T>
RWEuroGroup<T>& RWEuroGroup<T>::operator=(const RWEuroGroup<T>& rhs)
{
    if (this != &rhs) {
        euroCurrencies_ = rhs.euroCurrencies_;
        euroMnemonic_ = rhs.euroMnemonic_;
    }

    return *this;
}

template <class T>
std::ostream& RWEuroGroup<T>::lShift(std::ostream& strm,
                                     const RWEuroGroup<T>& grp)
{
    for (size_t i = 0; i < grp.euroCurrencies_.entries(); ++i) {
        strm << grp.euroCurrencies_[i] << '\n';
    }
    return strm;
}

template <class T>
std::istream& RWEuroGroup<T>::rShift(std::istream& strm,
                                     RWEuroGroup<T>& grp)
{
    RWCString currencyMnemonic;
    while (!strm.eof()) {
        strm >> currencyMnemonic;
        grp.euroCurrencies_.append(currencyMnemonic);
    }
    return strm;
}

#endif // RW_CURRENCY_EUROXCHGGRP_CC
