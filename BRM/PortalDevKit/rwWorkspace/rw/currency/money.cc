#ifndef RW_CURRENCY_MONEY_CC
#define RW_CURRENCY_MONEY_CC

/*******************************************************
 *
 * Implementation of RWMoney and supporting classes.
 *
 * $Id: //spro/rel2016.1/rw/currency/money.cc#1 $
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
 *******************************************************/

/* for backward compatibility */
#ifndef RW_MONEY_MONEY_CC
#  define RW_MONEY_MONEY_CC
#endif

#include <rw/rwfile.h>
#include <rw/vstream.h>


//-----------------------------------------------------
//
// Constructors
//
//-----------------------------------------------------

// Default constructor.  Behavior undefined.
template < class T >
RWMoney<T>::RWMoney()
{
    ;
}

// Copy constructor.
template < class T >
RWMoney<T>::RWMoney(const RWMoney<T>& m)
    : amount_(m.amount_), currencyMnemonic_(m.currencyMnemonic_)
{
    ;
}

// Construct with the given amount and currency.
template < class T >
RWMoney<T>::RWMoney(const T& amount, const RWCString& currencyMnemonic)
    : amount_(amount), currencyMnemonic_(currencyMnemonic)
{
    ;
}

// Construct with the given currency and set amount to zero.
template < class T >
RWMoney<T>::RWMoney(const RWCString& currencyMnemonic)
    : amount_(T(0)), currencyMnemonic_(currencyMnemonic)
{
    ;
}

//- Member functions -----------------------------------

//******************************************************
// Persistence to RWFiles and streams
//******************************************************

// RWvistream, RWvostream.
template < class T >
void RWMoney<T>::saveOn(RWvostream& strm) const
{
    strm << currencyMnemonic_;
    strm << amount_;
}

template < class T >
void RWMoney<T>::restoreFrom(RWvistream& strm)
{
    strm >> currencyMnemonic_;
    strm >> amount_;
}


// RWFile
template < class T >
void RWMoney<T>::saveOn(RWFile& f) const
{
    f << currencyMnemonic_;
    f << amount_;
}

template < class T >
void RWMoney<T>::restoreFrom(RWFile& f)
{
    f >> currencyMnemonic_;
    f >> amount_;
}


// Global round function -------------------------------------

// xlC cannot make the conversion from unsigned to int.
// So we need the casts in the following

template< class T >
RWMoney<T> round(const RWMoney<T>& m, unsigned int places)
{
    T rounded = rw_money_round(m.amount(), places);
    return RWMoney<T>(rounded, m.currency());
}


#endif // RW_CURRENCY_MONEY_CC
