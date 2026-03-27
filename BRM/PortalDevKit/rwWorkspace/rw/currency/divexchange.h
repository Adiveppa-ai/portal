#ifndef RW_CURRENCY_DIVEXCHANGE_H
#define RW_CURRENCY_DIVEXCHANGE_H

/***************************************************************************
 *
 * File:  divexchange.h
 *
 * Declarations for the class RWDivisionExchange and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/divexchange.h#1 $
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
#ifndef RW_MONEY_DIVEXCHANGE_H
#  define RW_MONEY_DIVEXCHANGE_H
#endif

#include <rw/currency/biexchange.h>
#include <rw/dcmldefs.h>

/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * Concrete currency exchange implementation class that converts a source
 * currency to a target currency by \e dividing the amount of the source
 * currency by the associated conversion factor.
 *
 * RWDivisionExchange derives from the abstract base class
 * RWBilateralExchange. An RWDivisionExchange object converts a source
 * currency to a target currency by <em>dividing</em> the amount of the
 * source currency by the associated conversion factor to obtain the target
 * currency. This contrasts with RWMultiplicationExchange, which multiplies
 * its source currency by the conversion factor to obtain the target amount.
 *
 * \synopsis
 * #include<rw/currency/divexchange.h>
 * RWDivisionExchange<double> e("CAD","XEC", 0.57241)
 * \endsynopsis
 */
template< class T >
class RWDivisionExchange : public RWBilateralExchange<T>
{
public:

    /**
     * This data member is the name returned by the name() function. It
     * contains the name associated with this exchange class.
     */
    static const char* exchangeMethodName;

    // Constructors ----------------------------------------------------------

    /**
     * Default constructor. Sets source and target strings to null and the
     * conversion factor to zero.
     */
    RWDivisionExchange();

    /**
     * Copy constructor.
     */
    RWDivisionExchange(const RWDivisionExchange<T>&);

    /**
     * Constructs an exchange object with source currency mnemonic
     * \a source, target currency mnemonic \a target, and source to target
     * conversion factor \a convFactor.
     */
    RWDivisionExchange(const RWCString& source,
                       const RWCString& target,
                       double           convFactor);

    /**
     * Constructs an exchange object with source, target, and conversion
     * factor provided in the RWExchangeRate object \a r.
     */
    RWDivisionExchange(const RWExchangeRate& r);

    // Public Member Functions -----------------------------------------------

    // Inherited from RWExchangeImpl

    // documented in base class
    virtual RWExchangeImpl<T>* clone() const;

    /**
     * Virtual function for converting money from the source currency to the
     * target currency. If the currency associated with money does not match
     * the source currency for self, an exception will be thrown.
     */
    virtual RWMoney<T>         exchange(const RWMoney<T>&) const;

    /**
     * Returns the value of the static data member #exchangeMethodName.
     */
    virtual RWCString          name() const
    {
        return exchangeMethodName;
    }

    /**
     * Assignment operator.
     */
    RWDivisionExchange<T>& operator=(const RWDivisionExchange<T>&);
};

#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/divexchange.cc>
#endif

#endif // RW_CURRENCY_DIVEXCHANGE_H
