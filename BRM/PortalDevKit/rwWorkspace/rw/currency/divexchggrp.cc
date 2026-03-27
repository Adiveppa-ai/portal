#ifndef RW_CURRENCY_DIVEXCHGGRP_CC
#define RW_CURRENCY_DIVEXCHGGRP_CC

/***************************************************************************
 *
 * File:  divexchggrp.cc
 *
 * Implementations for the class RWDivisionGroup
 *
 * $Id: //spro/rel2016.1/rw/currency/divexchggrp.cc#1 $
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
#ifndef RW_MONEY_DIVEXCHGGRP_CC
#  define RW_MONEY_DIVEXCHGGRP_CC
#endif

#include <rw/currency/currexchange.h>
#include <rw/currency/divexchange.h>
#include <rw/currency/exchgratetbl.h>


// static group name
template< class T >
const char* RWDivisionGroup<T>::groupName
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
;
#else
    = "BilateralDivision";
#endif

// The exchange rate table contains multiplicative exchange rates.  i.e. to
// convert an amount s in the source currency to an amount t in the target
// currency you would find the rate r for the source/target pair in the
// exchange rate table and multiply: t = s*t.
// The division exchange group creates exchange objects that divide the source
// amounts by the exchange rate to obtain the target amount.  Thus this
// division exchange rate for a given source/target pair is found by
// searching the exchange rate table for multiplicative rate for the
// target/source pair
template< class T >
RWExchange<T> RWDivisionGroup<T>::getExchange(const RWCString& srcMnemonic,
        const RWCString& targetMnemonic,
        const RWExchangeRateTable& rates) const
{
    RWExchangeRate r;
    // create an invalid exchange object (null impl)
    RWExchange<T> exchangeObject;

    // look for a multiplicative rate from the target to the source.
    // We'll divide source amount by this rate to yield the target amount.
    if (rates.findExchangeRate(targetMnemonic, srcMnemonic, r)) {
        // Found an exchange rate.  Create and set the impl for the exchange object
        // making it valid.
        RWDivisionExchange<T>* impl =
            new RWDivisionExchange<T>(r.target(), r.source(), r.conversionFactor());
        exchangeObject.setImpl(impl);
    }
    return exchangeObject;
}


// static function for creating currency exchange group object with a division
// group implementation

template< class T >
RWExchangeGroup<T> RWDivisionGroup<T>::create()
{
    RWExchangeGroupImpl<T>* i = new RWDivisionGroup<T>;
    return RWExchangeGroup<T>(i);
}

// Some compilers will not generate symbols for the static const data member
// groupName.  You must explicitly reference them somewhere in the
// compilation unit to avoid unresolved symbol errors.  Unfortunately this means
// that RWDivisionGroup<T> is supported for SunPro only with the types
// listed below.
#if defined(__SUNPRO_CC)
#  include <rw/currency/decimal.h>
#  include <rw/currency/mp1int.h>
#  include <rw/currency/mp2int.h>
#  include <rw/currency/mp3int.h>

static RWCString rwInitDivGrpName1__ = RWDivisionGroup< RWDecimal<RWMP1Int> >::groupName;
static RWCString rwInitDivGrpName2__ = RWDivisionGroup< RWDecimal<RWMP2Int> >::groupName;
static RWCString rwInitDivGrpName3__ = RWDivisionGroup< RWDecimal<RWMP3Int> >::groupName;
static RWCString rwInitDivGrpNameDbl__ = RWDivisionGroup<double>::groupName;
#endif

#endif // RW_CURRENCY_DIVEXCHGGRP_CC
