#ifndef RW_CURRENCY_MULTEXCHGGRP_H
#define RW_CURRENCY_MULTEXCHGGRP_H

/***************************************************************************
 *
 * File:  multexchggrp.h
 *
 * Declarations for the class RWMultiplicationGroup and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/multexchggrp.h#1 $
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
#ifndef RW_MONEY_MULTEXCHGGRP_H
#  define RW_MONEY_MULTEXCHGGRP_H
#endif

#include <rw/currency/exchggroup.h>
#include <rw/dcmldefs.h>

class RWCString;


/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * Represents a collection of currencies that have a common distinguishing
 * characteristic for converting money from one currency to money of another
 * currency.
 *
 * Currency exchange groups are collections of currencies that have a common
 * distinguishing characteristic for converting money from one currency to
 * money of another currency. RWMultiplicationGroup is made up of objects
 * that convert a source currency to a target currency by
 * <em>multiplying</em> the amount of the source currency by a conversion
 * factor.
 *
 * \note
 * Currencies that use the triangular conversion method required by the EMU
 * are available in class RWEuroGroup. Currencies that convert a source
 * currency to a target currency by dividing the amount of the source by a
 * conversion factor are available in RWDivisionGroup.
 *
 * The multiplication exchange group overrides the base class method:
 *
 * \code
 * RWExchange<T>
 * const RWCString& target,
 * const RWExchangeRateTable& rates);
 * \endcode
 *
 * so that it looks in the exchange rate table for an exchange rate that
 * converts the source currency to the target currency. If it finds one, it
 * creates and returns an RWExchange object with an RWMultiplicationExchange
 * implementation. If it does not find one, it returns an invalid RWExchange
 * object.
 *
 * \synopsis
 * #include <rw/currency/multexchggrp.h>
 * RWMultiplicatonGroup multGroup;
 * \endsynopsis
 */
template< class T >
class RWMultiplicationGroup : public RWExchangeGroupImpl<T>
{
public:

    /**
     * Name associated with the group. Returned by the name() member
     * function.
     */
    static const char* groupName;

    /**
     * Default constructor. Constructs an empty group.
     */
    RWMultiplicationGroup()
    {
#ifdef RW_MNY_NO_EXPLICIT_INSTANTIATION
        groupName = "RWBilateralMultiplicative";
#else
        ;
#endif
    }

    // Public Member Functions -----------------------------------------------

    /**
     * Creates an RWExchangeGroup object with an RWMultiplicationGroup
     * implementation.
     */
    static RWExchangeGroup<T> create();

    virtual RWExchange<T> getExchange(const RWCString& srcMnemonic,
                                      const RWCString& tragetMnemonic,
                                      const RWExchangeRateTable& rates) const;

    virtual RWCString name() const
    {
        return groupName;
    }

    virtual RWExchangeGroupImpl<T>* clone() const
    {
        return (RWExchangeGroupImpl<T>*)new RWMultiplicationGroup<T>;
    }
};

#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/multexchggrp.cc>
#endif

#endif // RW_CURRENCY_MULTEXCHGGRP_H
