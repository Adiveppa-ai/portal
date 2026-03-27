#ifndef RW_CURRENCY_EUROEXCHGGRP_H
#define RW_CURRENCY_EUROEXCHGGRP_H

/***************************************************************************
 *
 * File:  euroexchggrp.h
 *
 * Declarations for the class RWEuroGroup and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/euroexchggrp.h#1 $
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
 ***************************************************************************
 */

/* for backward compatibility */
#ifndef RW_MONEY_EUROEXCHGGRP_H
#  define RW_MONEY_EUROEXCHGGRP_H
#endif

#include <rw/currency/exchggroup.h>
#include <rw/dcmldefs.h>
#include <rw/cstring.h>
#include <rw/tvslist.h>
#include <iosfwd>


/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * A collection of all currencies replaced by the Euro, in which each object
 * implements the RWTriangularExchange conversion type.
 *
 * Currency exchange groups are collections of currencies that have a common
 * distinguishing characteristic when it comes to converting money from one
 * currency to money of another currency. RWEuroGroup is a currency exchange
 * group class that consists of all currencies replaced by the Euro.
 * RWEuroGroup objects create and return RWExchange objects with the
 * RWTriangularExchange implementation.
 *
 * \note
 * The Euro itself is not in the Euro exchange group because the triangular
 * exchange algorithm is not used when converting to or from Euros.
 *
 * \synopsis
 * #include <rw/currency/euroexchggrp.h>
 * #include <rw/tvslist.h>
 * RWTValSlist<RWCString> euroCurrencies;
 * RWEuroGroup<double> euroGroup(euroCurrencies);
 * \endsynopsis
 */
template< class T >
class RWEuroGroup : public RWExchangeGroupImpl<T>
{
public:

    /**
     * Name that identifies the Euro exchange group. Returned by the name()
     * method.
     */
    static const char* groupName;

    // Constructors ----------------------------------------------------------

    /**
     * Default constructor. Constructs an empty group. The default value of
     * \a euro_mnemonic identifies the Euro currency and is used to look up
     * rates in the exchange rate table, information in the currency book,
     * and so forth.
     */
    RWEuroGroup(const char* euro_mnemonic = "EUR")
        : euroMnemonic_(euro_mnemonic)
    {}

    /**
     * Copy constructor.
     */
    RWEuroGroup(const RWEuroGroup<T>&);

    /**
     * Constructs a Euro exchange group containing the currencies whose
     * mnemonics are contained in \a euroCurrencies. The default value of
     * \a euroMnemonic identifies the Euro currency and is used to look up
     * rates in the exchange rate table, information in the currency book,
     * and so forth.
     */
    RWEuroGroup(const RWTValSlist<RWCString>& euroCurrencies, const char* euroMnemonic = "EUR");

    // Public Member Functions -----------------------------------------------

    /**
     * Creates and returns an RWExchangeGroup object with a RWEuroGroup
     * implementation. The list of Euro currencies contained in the
     * implementation is empty.
     */
    static RWExchangeGroup<T> create();

    /**
     * Creates and returns an RWExchangeGroup object with a RWEuroGroup
     * implementation. This implementation uses \a strm to define the
     * currencies in the Euro group. The stream format must have one
     * currency mnemonic per line, as in the following example:
     *
     * \code
     * ATS
     * BEF
     * FIM
     * FRF
     * DEM
     * IEP
     * ITL
     * LUF
     * NLG
     * ESP
     * PTE
     * \endcode
     */
    static RWExchangeGroup<T> create(std::istream& strm, const char* euroMnem = "EUR");

    /**
     * Creates and returns an RWExchangeGroup object with an RWEuroGroup
     * implementation. This implementation uses the currencies in
     * \a currencyList to define the currencies in the Euro group.
     */
    static RWExchangeGroup<T> create(const RWTValSlist<RWCString>& currencyList, const char* euroMnem = "EUR");

    // documented in the base class
    virtual RWExchange<T> getExchange(const RWCString& srcMnemonic,
                                      const RWCString& tragetMnemonic,
                                      const RWExchangeRateTable& rates) const;

    // documented in the base class
    virtual RWCString name() const
    {
        return groupName;
    }

    // documented in the base class
    virtual RWExchangeGroupImpl<T>* clone() const
    {
        return (RWExchangeGroupImpl<T>*)new RWEuroGroup<T>(*this);
    }

    // new member functions
    /**
     * Returns \c true if the given currency is in the Euro exchange group.
     * Note that the Euro is <em>not</em> in the Euro exchange group since
     * you do not use the triangulation algorithm when converting from or to
     * Euros.
     */
    bool              containsCurrency(const RWCString&) const;

    /**
     * Returns a list of currency mnemonics that are in the Euro group.
     */
    RWTValSlist<RWCString> getCurrencies() const;

    /**
     * Returns the number of currencies in the Euro group.
     */
    size_t                 numCurrencies() const;

    /**
     * Adds the currency mnemonic to the Euro exchange group. Returns
     * \c false if the currency was already in the group and \c true
     * otherwise.
     */
    bool              addCurrency(const RWCString&);

    /**
     * Removes the given currency from the Euro group. Returns \c false if
     * the currency was not found in the group, and \c true otherwise.
     */
    bool              removeCurrency(const RWCString&);

    /**
     * Replaces the list of Euro currencies with \a list.
     */
    void                   setCurrencies(const RWTValSlist<RWCString>& list);

    /**
     * Removes all Euro currencies from the group.
     */
    void                   clear();

    /**
     * Returns the RWCString for the Euro currency mnemonic.
     */
    RWCString euroMnemonic() const
    {
        return euroMnemonic_;
    }

    /**
     * Sets the Euro currency mnemonic for this object.
     */
    void      setEuroMnemonic(const RWCString& em)
    {
        euroMnemonic_ = em;
    }

    // Public Member Operators -----------------------------------------------

    /**
     * Assignment operator.
     */
    RWEuroGroup<T>& operator=(const RWEuroGroup<T>&);

    // Related Global Operators ----------------------------------------------
    // Friendly global operators now replaced with statics to avoid casting...
    static std::ostream& lShift(std::ostream& strm,
                                const RWEuroGroup<T>& grp);

    static std::istream& rShift(std::istream& strm,
                                RWEuroGroup<T>& grp);
private:
    RWTValSlist<RWCString> euroCurrencies_;
    RWCString euroMnemonic_;
};

/**
 * \relates RWEuroGroup
 * Writes \a grp to a stream. The stream has the format described in the
 * RWEuroGroup::create(std::istream&, const char*) method.
 */
template< class T >
inline std::ostream& operator<<(std::ostream& strm,
                                const RWEuroGroup<T>& grp)
{
    return RWEuroGroup<T>::lShift(strm, grp);
}

/**
 * \relates RWEuroGroup
 * Reads \a grp from a stream. The stream has the format described in the
 * RWEuroGroup::create(std::istream&, const char*) method.
 */
template< class T >
inline std::istream& operator>>(std::istream& strm, RWEuroGroup<T>& grp)
{
    return RWEuroGroup<T>::rShift(strm, grp);
}

#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/euroexchggrp.cc>
#endif

#endif // RW_CURRENCY_EUROEXCHGGRP_H
