#ifndef RW_CURRENCY_BILATERALEXCHANGE_H
#define RW_CURRENCY_BILATERALEXCHANGE_H

/***************************************************************************
 *
 * File:  biexchange.h
 *
 * Declarations for the class RWBilateralExchange and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/biexchange.h#1 $
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
#ifndef RW_MONEY_BILATERALEXCHANGE_H
#  define RW_MONEY_BILATERALEXCHANGE_H
#endif

#include <rw/currency/exchgimpl.h>

// Forward Declarations
class RW_DCML_GLOBAL RWExchangeRate;


/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * Implements a standard form of currency conversion.
 *
 * RWBilateralExchange is an abstract base class derived from the base class
 * RWExchangeImpl, and is a parent of both the RWMultiplicationExchange and
 * RWDivisionExchange classes. RWBilateralExchange implements the usual
 * method of currency conversion: multiplying or dividing the amount of a
 * source currency by a conversion factor to obtain the equivalent amount in
 * the target currency.
 *
 * \synopsis
 * #include <rw/currency/currexchange.h>
 * #include <rw/currency/divexchange.h>
 * #include <rw/currency/multexchange.h>
 * \endsynopsis
 */
template< class T >
class RWBilateralExchange : public RWExchangeImpl<T>
{
public:

    /**
     * Default constructor. The source and target mnemonic strings are set
     * to null, and the conversion factor is set to zero.
     */
    RWBilateralExchange();

    /**
     * Copy constructor.
     */
    RWBilateralExchange(const RWBilateralExchange<T>&);

    /**
     * Constructs a bilateral exchange object with source currency mnemonic
     * given by \a source, target currency mnemonic given by \a target, and
     * source to target conversion factor given by \a f.
     */
    RWBilateralExchange(const RWCString& source,
                        const RWCString& target,
                        double           f);

    /**
     * Constructs a bilateral exchange object with source currency, target
     * currency and conversion factor provided by the RWExchangeRate object
     * \a rate.
     */
    RWBilateralExchange(const RWExchangeRate& rate);

    /**
     * Returns the conversion factor.
     */
    double         conversionFactor() const
    {
        return convFactor_;
    }

    /**
     * Returns the source currency, target currency and conversion factor in
     * an RWExchangeRate object.
     */
    RWExchangeRate exchangeRate() const;

    /**
     * Sets the conversion factor.
     */
    void setConversionFactor(double f)
    {
        convFactor_ = f;
    }

    /**
     * Sets the source currency, target currency and conversion factor to
     * those contained in \a rate.
     */
    void setExchangeRate(const RWExchangeRate& rate);

    /**
     * Assignment operator.
     */
    RWBilateralExchange<T>& operator=(const RWBilateralExchange<T>&);

protected:
    double    convFactor_;
};

#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/biexchange.cc>
#endif

#endif // RW_CURRENCY_BILATERALEXCHANGE_H
