#ifndef RW_CURRENCY_EXCHGFACT_CC
#define RW_CURRENCY_EXCHGFACT_CC

/***************************************************************************
 *
 * File:  exchgfact.cc
 *
 * Implementation for the class RWExchangeFactory and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/exchgfact.cc#1 $
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
#ifndef RW_MONEY_EXCHGFACT_CC
#  define RW_MONEY_EXCHGFACT_CC
#endif

#include <rw/currency/currexchange.h>
#include <rw/currency/multexchggrp.h>

// Constructors ------------------------------------------------------------

// Default ctor.  The bilateral multiplicative group is added by default.
template< class T >
RWExchangeFactory<T>::RWExchangeFactory()
{
    RWExchangeGroup<T> multGrp(new RWMultiplicationGroup<T>());
    exchangeGroups_.prepend(multGrp);
}


// Copy ctor
template< class T >
RWExchangeFactory<T>::RWExchangeFactory(const RWExchangeFactory<T>& f)
    : exchangeGroups_(f.exchangeGroups_), exchangeRateTable_(f.exchangeRateTable_)
{
    ;
}


// Construct with given exchange rate table.  Bilateral Multiplicative
// group added by default.
template< class T >
RWExchangeFactory<T>::RWExchangeFactory(const RWExchangeRateTable& t)
    : exchangeRateTable_(t)
{
    RWExchangeGroup<T> multGrp(new RWMultiplicationGroup<T>());
    exchangeGroups_.prepend(multGrp);
}


// Public member functions -------------------------------------------------

// Starting with the first entry in the exchange group list traverse the list
// until we find an exchange group which can create an exchange object.  If none
// can an invalid exchange object is returned.
template< class T >
RWExchange<T> RWExchangeFactory<T>::getExchange(const RWCString& src, const RWCString& trg) const
{
    typename RWTValSlist< RWExchangeGroup<T> >::const_iterator iter = exchangeGroups_.begin();
    RWExchange<T> exchangeObject;
    for (; iter != exchangeGroups_.end(); ++iter) {
        exchangeObject = (*iter).getExchange(src, trg, exchangeRateTable_);
        if (exchangeObject.isValid()) {
            return exchangeObject;
        }
    }
    return exchangeObject;
}



// Search list for named exchange group
template< class T >
bool RWExchangeFactory<T>::containsExchangeGroup(const RWCString& groupName) const
{
    typename RWTValSlist< RWExchangeGroup<T> >::const_iterator iter = exchangeGroups_.begin();
    for (; iter != exchangeGroups_.end(); ++iter) {
        if ((*iter).name() == groupName) {
            return true;
        }
    }
    return false;
}


// Find named group and place in grp.  If not found False returned and
// grp is left unchanged.
template< class T >
bool RWExchangeFactory<T>::findExchangeGroup(const RWCString& groupName,
        RWExchangeGroup<T>& grp) const
{
    typename RWTValSlist< RWExchangeGroup<T> >::const_iterator iter = exchangeGroups_.begin();
    for (; iter != exchangeGroups_.end(); ++iter) {
        if ((*iter).name() == groupName) {
            grp = *iter;
            return true;
        }
    }

    return false;
}


// Return the index of the named group
template< class T >
size_t RWExchangeFactory<T>::exchangeGroupIndex(const RWCString& groupName) const
{
    typename RWTValSlist< RWExchangeGroup<T> >::const_iterator iter = exchangeGroups_.begin();
    size_t index = 0;
    for (; iter != exchangeGroups_.end(); ++iter, ++index) {
        if ((*iter).name() == groupName) {
            return index;
        }
    }

    return RW_NPOS;
}


// If named group found it is removed and true is returned.  Otherwise false
// is returned.
template< class T >
bool RWExchangeFactory<T>::removeExchangeGroup(const RWCString& groupName)
{
    typename RWTValSlist< RWExchangeGroup<T> >::iterator iter = exchangeGroups_.begin();
    for (; iter != exchangeGroups_.end(); ++iter) {
        if ((*iter).name() == groupName) {
            exchangeGroups_.erase(iter);
            return true;
        }
    }

    return false;
}


// Public member operators ----------------------------------------------------
template< class T >
RWExchangeFactory<T>& RWExchangeFactory<T>::operator=(const RWExchangeFactory<T>& rhs)
{
    if (this != &rhs) {
        exchangeGroups_ = rhs.exchangeGroups_;
        exchangeRateTable_ = rhs.exchangeRateTable_;
    }
    return *this;
}

#endif // RW_CURRENCY_EXCHGFACT_CC
