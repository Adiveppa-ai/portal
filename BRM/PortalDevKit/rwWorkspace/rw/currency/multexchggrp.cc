#ifndef RW_CURRENCY_MULTEXCHGGRP_CC
#define RW_CURRENCY_MULTEXCHGGRP_CC

/***************************************************************************
 *
 * File:  multexchggrp.cc
 *
 * Implementations for the class RWMultiplicationGroup
 *
 * $Id: //spro/rel2016.1/rw/currency/multexchggrp.cc#1 $
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
#ifndef RW_MONEY_MULTEXCHGGRP_CC
#  define RW_MONEY_MULTEXCHGGRP_CC
#endif

#include <rw/currency/currexchange.h>
#include <rw/currency/exchgratetbl.h>
#include <rw/currency/multexchange.h>
#include <rw/cstring.h>


// static group name
template< class T >
const char* RWMultiplicationGroup<T>::groupName
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
;
#else
    =  "RWBilateralMultiplicative";
#endif

// The exchange rate table contains multiplicative exchange rates.  i.e. to
// convert an amount s in the source currency to an amount t in the target
// currency you would find the rate r for the source/target pair in the
// exchange rate table and multiply: t = s*t.
template< class T >
RWExchange<T> RWMultiplicationGroup<T>::getExchange(const RWCString& srcMnemonic,
        const RWCString& targetMnemonic,
        const RWExchangeRateTable& rates) const
{
    RWExchangeRate r;
    // create an invalid exchange object (null impl)
    RWExchange<T> exchangeObject;
    if (rates.findExchangeRate(srcMnemonic, targetMnemonic, r)) {
        // Found an exchange rate.  Create and set the impl for the exchange object
        // making it valid.
        RWMultiplicationExchange<T>* impl =
            new RWMultiplicationExchange<T>(r.source(), r.target(), r.conversionFactor());
        exchangeObject.setImpl(impl);
    }
    return exchangeObject;
}


template< class T >
RWExchangeGroup<T> RWMultiplicationGroup<T>::create()
{
    RWExchangeGroupImpl<T>* i = new RWMultiplicationGroup<T>;
    return RWExchangeGroup<T>(i);
}

#endif // RW_CURRENCY_MULTEXCHGGRP_CC
