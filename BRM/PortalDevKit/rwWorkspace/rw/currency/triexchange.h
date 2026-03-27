#ifndef RW_CURRENCY_TRIEXCHANGE_H
#define RW_CURRENCY_TRIEXCHANGE_H

/***************************************************************************
 *
 * File:  triexchange.h
 *
 * Declarations for the class RWTriangularExchange and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/triexchange.h#1 $
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
#ifndef RW_MONEY_TRIEXCHANGE_H
#  define RW_MONEY_TRIEXCHANGE_H
#endif

#include <rw/currency/exchgimpl.h>
#include <rw/dcmldefs.h>
#include <rw/cstring.h>


/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * Converts between local currencies that are part of the European Monetary
 * Union (EMU).
 *
 * RWTriangularExchange derives from the abstract base class RWExchangeImpl
 * and implements the currency conversion method used to convert between
 * local currencies that are part of the European Monetary Union (EMU). This
 * class may be used as an implementation class for the RWExchange class, or
 * by itself.
 *
 * In the triangular currency exchange method of conversion, the source
 * currency is converted to an intermediate currency, for example, the Euro,
 * and the result is converted to the target currency. In a direct currency
 * exchange, the source currency is converted directly to the target
 * currency.
 *
 * Classes RWMultiplicationExchange and RWDivisionExchange allow a direct
 * conversion from a source to a target currency.
 *
 * \synopsis
 * #include <rw/currency/triexchange.h>
 * RWTriangularExchange<double> t("ESP","PTE","EUR" 167.8,203.4);
 * \endsynopsis
 */
template< class T >
class RWTriangularExchange : public RWExchangeImpl<T>
{
public:

    /**
     * This data member is the name returned by the name() function.
     */
    static const char* exchangeMethodName;

    // Constructors ----------------------------------------------------------

    /**
     * Default constructor. The exchange rate is set to zero and source and
     * target mnemonic strings are set to null.
     */
    RWTriangularExchange();

    /**
     * Copy constructor.
     */
    RWTriangularExchange(const RWTriangularExchange<T>&);

    /**
     * Constructs a triangular exchange object with source currency mnemonic
     * \a source, target currency mnemonic \a target, and intermediate
     * currency mnemonic \a intermediate. The conversion factor
     * \a intermToSource is the multiplicative factor for converting amounts
     * in the intermediate currency to amounts in the source currency. The
     * second conversion factor, \a intermToTarget, is the multiplicative
     * factor for converting amounts in the intermediate currency to amounts
     * in the target currency.
     */
    RWTriangularExchange(const RWCString& source,
                         const RWCString& target,
                         const RWCString& interm,
                         double           intermToSource,
                         double           intermToTarget);

    // Public Member Functions -----------------------------------------------

    // Inherited from RWExchangeImpl
    virtual RWExchangeImpl<T>* clone() const;
    virtual RWMoney<T>         exchange(const RWMoney<T>&) const;
    virtual RWCString          name() const
    {
        return exchangeMethodName;
    }

    // Accessors
    /**
     * Returns the intermediate currency's mnemonic.
     */
    RWCString intermediate() const
    {
        return interm_;
    }

    /**
     * Returns the multiplicative conversion factor used to convert the
     * intermediate currency to the source currency.
     */
    double    intermediateToSourceFactor() const
    {
        return intermToSrc_;
    }

    /**
     * Returns the multiplicative conversion factor used to convert the
     * intermediate currency to the target currency.
     */
    double    intermediateToTargetFactor() const
    {
        return intermToTrg_;
    }

    // Mutators
    /**
     * Sets the intermediate currency using the given currency mnemonic.
     */
    void setIntermediate(const RWCString& i)
    {
        interm_ = i;
    }

    /**
     * Sets the multiplicative conversion factor used to convert the
     * intermediate currency to the source currency.
     */
    void setIntermediateToSourceFactor(double f)
    {
        intermToSrc_ = f;
    }

    /**
     * Sets the multiplicative conversion factor used to convert the
     * intermediate currency to the target currency.
     */
    void setIntermediateToTargetFactor(double f)
    {
        intermToTrg_ = f;
    }

    // Public Member Operators -----------------------------------------------

    /**
     * Assignment operator. Copies contents of \a t to self.
     */
    RWTriangularExchange<T>& operator=(const RWTriangularExchange<T>& t);

private:
    RWCString interm_;
    double    intermToSrc_;
    double    intermToTrg_;
};

#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/triexchange.cc>
#endif

#endif // RW_CURRENCY_TRIEXCHANGE_H
