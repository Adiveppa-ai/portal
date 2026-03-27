#ifndef RW_CURRENCY_CURREXCHANGE_H
#define RW_CURRENCY_CURREXCHANGE_H

/***************************************************************************
 *
 * File:  currexchange.h
 *
 * Declarations for the class RWExchange and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/currexchange.h#1 $
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
#ifndef RW_MONEY_CURREXCHANGE_H
#  define RW_MONEY_CURREXCHANGE_H
#endif

#include <rw/currency/exchgimpl.h>
#include <rw/dcmldefs.h>
#include <rw/dcmlerr.h>
#include <rw/cstring.h>


/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * Handle class for the abstract body class RWExchangeImpl from which all
 * concrete currency converters derive.
 *
 * Currency exchange objects are responsible for converting money of one
 * currency into money of another currency. They encapsulate the source and
 * target currency mnemonics, an exchange algorithm and any required
 * exchange rates.
 *
 * RWExchangeImpl is an abstract base class from which all currency
 * implementation classes must derive. Class RWExchange is the handle class,
 * which forwards all conversion requests to its associated implementation
 * class.
 *
 * Currency Module provides three types of currency exchange objects. The
 * first type implements a triangular exchange algorithm required for
 * converting between local currencies through an intermediate currency,
 * such as the EMU requires for the Euro transition. The second type of
 * exchange object multiplies the source currency amount by the exchange
 * factor to obtain a target amount. The third type of exchange object
 * divides the source currency amount by the exchange factor to obtain the
 * target currency amount. All of the exchange objects share a common API
 * for performing the actual conversion of money.
 *
 * \synopsis
 * #include <rw/currency/currexchange.h>
 * #include <rw/currency/divexchange.h>
 * #include <rw/currency/decimal.h>
 * #include <rw/currency/mp2int.h>
 *
 * typedef RWDecimal<RWMP2Int> Decimal;
 * RWDivisionGroup<Decimal>* impl =
 *   new RWDivisionGroup<Decimal>("LBP","CAD",971.8);
 * RWExchange<Decimal> divExchange(impl);
 * \endsynopsis
 */
template< class T >
class RWExchange
{
public:
    // Constructors ----------------------------------------------------------

    /**
     * Default constructor.
     */
    RWExchange(): impl_(rwnil)
    {
        ;
    }

    /**
     * Makes a (deep) copy of the implementation for currency exchange
     * object \a c.
     */
    RWExchange(const RWExchange<T>& c)
    {
        impl_ = (c.impl_ == rwnil ? rwnil : c.impl_->clone());
    }

    /**
     * Constructs an exchange object with the provided implementation
     * \a impl. The object's destructor will delete \a impl.
     */
    RWExchange(RWExchangeImpl<T>* impl): impl_(impl)
    {
        ;
    }


    // Destructor ------------------------------------------------------------

    ~RWExchange()
    {
        delete impl_;
    }

    // Public Member Functions -----------------------------------------------

    /**
     * Sets \a impl as the implementation for this exchange object.
     */
    void setImpl(RWExchangeImpl<T>* impl)
    {
        delete impl_;
        impl_ = impl;
    }

    /**
     * Returns a pointer to the implementation class.
     */
    const RWExchangeImpl<T>* impl() const
    {
        return impl_;
    }

    /**
     * Converts the amount \a m from the source currency to the target
     * currency. If the currency associated with \a m does not match the
     * source currency of self, an exception is thrown.
     */
    RWMoney<T> exchange(const RWMoney<T>& m) const
    {
        if (impl_ == rwnil) {
            RWTHROW(RWInternalErr(RWMessage(RWDCML_NULLEXCHGIMPL)));
        }

        return impl_->exchange(m);
    }

    /**
     * Returns the mnemonic for the source currency.
     */
    RWCString source() const
    {
        if (impl_ == rwnil) {
            RWTHROW(RWInternalErr(RWMessage(RWDCML_NULLEXCHGIMPL)));
        }

        return impl_->source();
    }

    /**
     * Returns the mnemonic for the target currency.
     */
    RWCString target() const
    {
        if (impl_ == rwnil) {
            RWTHROW(RWInternalErr(RWMessage(RWDCML_NULLEXCHGIMPL)));
        }

        return impl_->target();
    }

    /**
     * Returns the name of the implementation class. Rogue Wave
     * implementation classes return their static data member
     * \c exchangeMethodName. For example, when an RWExchange object
     * contains an RWTriangularExchange implementation, name() returns
     * RWTriangularExchange::exchangeMethodName.
     */
    RWCString name() const
    {
        if (impl_ == rwnil) {
            RWTHROW(RWInternalErr(RWMessage(RWDCML_NULLEXCHGIMPL)));
        }

        return impl_->name();
    }

    /**
     * Returns \c true if this exchange object has a valid implementation,
     * \c false otherwise.
     */
    bool isValid() const
    {
        return impl_ == rwnil ? false : true;
    }

    // Public Member Operators -----------------------------------------------

    /**
     * Deletes self's current implementation and clones a copy of the
     * implementation for \a c.
     */
    RWExchange<T>& operator=(const RWExchange<T>& c)
    {
        if (&c != this) {
            delete impl_;
            impl_ = (c.impl_ == rwnil ? rwnil : c.impl_->clone());
        }

        return *this;
    }

private:
    RWExchangeImpl<T>* impl_;
};


#endif // RW_CURRENCY_CURREXCHANGE_H
