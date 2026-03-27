#ifndef RW_CURRENCY_TRIEXCHANGE_CC
#define RW_CURRENCY_TRIEXCHANGE_CC

/***************************************************************************
 *
 * File:  triexchange.cc
 *
 * Implementations for the class RWTriangularExchange and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/triexchange.cc#1 $
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
#ifndef RW_MONEY_TRIEXCHANGE_CC
#  define RW_MONEY_TRIEXCHANGE_CC
#endif

#include <rw/dcmlerr.h>

template< class T >
const char* RWTriangularExchange<T>::exchangeMethodName
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
;
#else
    = "RWTriangular";
#endif


template< class T >
RWTriangularExchange<T>::RWTriangularExchange()
    : intermToSrc_(0.0), intermToTrg_(0.0)
{
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
    exchangeMethodName = "RWTriangular";
#else
    ;
#endif
}


template< class T >
RWTriangularExchange<T>::RWTriangularExchange(const RWTriangularExchange<T>& e)
    : RWExchangeImpl<T>(e.source_, e.target_), interm_(e.interm_), intermToSrc_(e.intermToSrc_), intermToTrg_(e.intermToTrg_)
{
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
    e.exchangeMethodName = exchangeMethodName;
#else
    ;
#endif
}


template< class T >
RWTriangularExchange<T>::RWTriangularExchange(const RWCString& source,
        const RWCString& target,
        const RWCString& interm,
        double           intermToSrc,
        double           intermToTrg)
    : RWExchangeImpl<T>(source, target), interm_(interm), intermToSrc_(intermToSrc), intermToTrg_(intermToTrg)
{
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
    exchangeMethodName = "RWTriangular";
#endif
}


template< class T >
RWExchangeImpl<T>* RWTriangularExchange<T>::clone() const
{
    return (new RWTriangularExchange<T>(*this));
}

// Sorry about all the this-> crap in the following. HP aCC gives these "future error"
// warnings if they are not there (something about the variable doesn't depend on the
// template type parameter so it won't be looked up when templates are generated?)
template< class T >
RWMoney<T> RWTriangularExchange<T>::exchange(const RWMoney<T>& src) const
{
    if (this->source_.compareTo(src.currency(), RWCString::ignoreCase) != 0) {
        RWTHROW(RWExternalErr(RWMessage(RWDCML_EXCHGSOURCEDIFF)));
    }

    T temp = src.amount() / intermToSrc_;
    return RWMoney<T>(temp * intermToTrg_, this->target_);
}


template< class T >
RWTriangularExchange<T>& RWTriangularExchange<T>::operator=(const RWTriangularExchange<T>& t)
{
    if (&t != this) {
        RWExchangeImpl<T>::operator=(t);
        interm_ = t.interm_;
        intermToSrc_ = t.intermToSrc_;
        intermToTrg_ = t.intermToTrg_;
    }

    return *this;
}


// Some compilers will not generate symbols for the static const data member
// exchangeMethodName.  You must explicitly reference them somewhere in the
// compilation unit to avoid unresolved symbol errors.  Unfortunately this means
// that RWTriangularExchange<T> is supported for SunPro only with the types
// listed below.
#if defined(__SUNPRO_CC)
#  include <rw/currency/decimal.h>
#  include <rw/currency/mp1int.h>
#  include <rw/currency/mp2int.h>
#  include <rw/currency/mp3int.h>

static RWCString rwInitTriangularName1__ = RWTriangularExchange< RWDecimal<RWMP1Int> >::exchangeMethodName;
static RWCString rwInitTriangularName2__ = RWTriangularExchange< RWDecimal<RWMP2Int> >::exchangeMethodName;
static RWCString rwInitTriangularName3__ = RWTriangularExchange< RWDecimal<RWMP3Int> >::exchangeMethodName;
static RWCString rwInitTriangularNameDbl__ = RWTriangularExchange<double>::exchangeMethodName;
#endif


#endif // RW_CURRENCY_TRIEXCHANGE_CC
