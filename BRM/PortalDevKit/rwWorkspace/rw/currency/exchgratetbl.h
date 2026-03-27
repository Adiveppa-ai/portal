#ifndef RW_CURRENCY_EXCHGRATETBL_H
#define RW_CURRENCY_EXCHGRATETBL_H

/***************************************************************************
 *
 * File:  exchgratetbl.h
 *
 * Declarations for the classes RWExchangeTableRef and RWExchangeRateTable
 * and related global functions
 *
 * The exchange rate table class stores currency exchange rates in the form
 * of two strings, one for the source currency mnemonic and one for the
 * target currency mnemonic, and a double for the multiplicative conversion
 * factor.  The table is potentially very large. To enable the use of value
 * semantics and make it somewhat efficient to make copies of the table, the
 * data structure containing the data is reference counted.  Copy on write
 * semantics are used.
 *
 * $Id: //spro/rel2016.1/rw/currency/exchgratetbl.h#1 $
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
#ifndef RW_MONEY_EXCHGRATETBL_H
#  define RW_MONEY_EXCHGRATETBL_H
#endif

#include <rw/currency/exchgrate.h>
#include <rw/currency/nameval.h>
#include <rw/dcmldefs.h>
#include <rw/cstring.h>
#include <rw/ref.h>
#include <rw/rwfile.h>
#include <rw/tvhdict.h>
#include <rw/tvslist.h>
#include <rw/vstream.h>


// **************************************************************************
//
// Class RWExchangeTableRef
//
// This is the reference counted part of the exchange rate table class.
//
// **************************************************************************
class RWExchangeTableRef : public RWReference
{
public:
    // Constructors ----------------------------------------------------------

    // default ctor
    RWExchangeTableRef();

    // Return a pointer to the underlying table
    RWTValHashDictionary<RWCString, RWExchangeRate>& table()
    {
        return RW_EXPOSE(table_);
    }
    const RWTValHashDictionary<RWCString, RWExchangeRate>& table() const
    {
        return RW_EXPOSE(table_);
    }

private:
    // prohibit copy
    RWExchangeTableRef(const RWExchangeTableRef&);

    // prohibit assignment
    RWExchangeTableRef& operator=(const RWExchangeTableRef&);

private:
    RWTValHashDictionary<RWCString, RWExchangeRate> table_;
};


// **************************************************************************
//
// Class RWExchangeRateTable
//
// **************************************************************************

/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * Stores exchange rates as unique pairs of source and target currencies.
 *
 * Class RWExchangeRateTable stores exchange rates as unique pairs of source
 * and target currencies. No two exchange rates in the table have the same
 * source-target currency pair.
 *
 * The RWExchangeRateTable class can be initialized from a stream, in
 * particular, from an \b std::ifstream (file). The format for the stream
 * is:
 *
 * \code
 * BEGIN_EXCHANGE
 * source=
 * target=
 * rate=
 * END_EXCHANGE
 * \endcode
 *
 * \synopsis
 * #include<rw/currency/exchgratetbl.h>
 * std::ifstream strm("exchange_rates.txt");
 * RWExchangeRateTable rates;
 * rates.initialize(strm);
 * \endsynopsis
 */
class RW_DCML_GLOBAL RWExchangeRateTable
{
public:
    // Static Data Members

    // The initialize member function takes a stream containing name value
    // for exchange rate attributes.  The following are the names that will
    // be searched for.

    /**
     * Used for the names in the name/value pairs described in the
     * RWExchangeRateTable::initialize() member function.
     */
    static const RWCString sourceTag;

    /**
     * Used for the names in the name/value pairs described in the
     * RWExchangeRateTable::initialize() member function.
     */
    static const RWCString targetTag;

    /**
     * Used for the names in the name/value pairs described in the
     * RWExchangeRateTable::initialize() member function.
     */
    static const RWCString conversionFactorTag;

    // Begin and end tokens for parsing exchange rates from a stream
    static const RWCString beginToken;
    static const RWCString endToken;


    // Constructors ----------------------------------------------------------

    /**
     * Default constructor. Constructs an empty exchange rate table.
     */
    RWExchangeRateTable();

    /**
     * Copy constructor. Copies contents of \a t to self.
     */
    RWExchangeRateTable(const RWExchangeRateTable& t);

    // Destructor ------------------------------------------------------------
    ~RWExchangeRateTable();


    // Public Member Operators -----------------------------------------------

    /**
     * Assignment operator.
     */
    RWExchangeRateTable& operator=(const RWExchangeRateTable&);

    // Public Member Functions -----------------------------------------------

    /**
     * Initializes an exchange rate table from the information in \a strm.
     * Returns \c false if there is an error in the stream format.
     *
     * An exchange rate specification begins with the token
     * \c BEGIN_EXCHANGE on a line by itself. Each attribute of the exchange
     * rate follows, specified as a name/value pair, one per line. The
     * name/value separator is the equal sign `='. The end of an exchange
     * rate specification is indicated by the token \c END_EXCHANGE. Comment
     * lines start with a \c # character and are automatically skipped. For
     * example:
     *
     * \code
     * # DZD/CAD (Algeria to Canada)
     * BEGIN_EXCHANGE
     * source=CAD
     * target=DZD
     * rate=35.5
     * END_EXCHANGE
     * .
     * .
     * .
     * \endcode
     *
     * Name matching is case-<em>insensitive</em>. Valid names for the
     * name/value pairs are:
     *
     * \code
     * source = RWExchangeRateTable::sourceTag
     * target = RWExchangeRateTable::targetTag
     * rate = RWExchangeRateTable::conversionFactorTag
     * \endcode
     */
    bool initialize(std::istream& strm);

    /**
     * Searches the exchange rate table to determine whether an exchange
     * rate for the currency specified by \a sourceMnemonic into the
     * currency specified by \a targetMnemonic exists. If an exchange rate
     * is found, it is placed in \a rate and the function returns \c true.
     * If an exchange rate is not found, the function returns \c false and
     * \a rate is unchanged.
     */
    bool findExchangeRate(const RWCString& sourceMnemonic,
                          const RWCString& targetMnemonic,
                          RWExchangeRate& rate) const;

    /**
     * Searches the exchange rate table to find the exchange rate for
     * converting money with currency specified by \a sourceMnemonic into
     * money in currency specified by \a targetMnemonic. If the rate is
     * found, the conversion factor is placed in \a factor and the function
     * returns \c true. If the rate is not found, the function returns
     * \c false and \a factor is unchanged.
     */
    bool findConversionFactor(const RWCString& sourceMnemonic,
                              const RWCString& targetMnemonic,
                              double& factor) const;

    /**
     * Returns \c true if the table contains a rate for the given \a source
     * and \a target currencies. Returns \c false otherwise.
     */
    bool contains(const RWCString& source, const RWCString& target) const;

    /**
     * Returns \c true if the table contains the given \a rate. Returns
     * \c false otherwise.
     */
    bool contains(const RWExchangeRate& rate) const;

    /**
     * Returns the number of exchange rates in the table.
     */
    size_t    entries() const;

    /**
     * Returns a list of all the exchange rates in the table.
     */
    RWTValSlist<RWExchangeRate> getAllExchangeRates() const;

    /**
     * Adds \a exchangeRate to the table and returns \c true if there is no
     * exchange rate in the table with the same source and target currency
     * as \a exchangeRate. If the table already contains an exchange rate
     * with the same source and target currencies as \a exchangeRate exists,
     * the function returns \c false without adding to the table.
     */
    bool add(const RWExchangeRate& exchangeRate);

    /**
     * Adds an exchange rate object with the given \a source, \a target and
     * \a convFactor to the table if none exists, and returns true. If the
     * table already contains an exchange rate with the given source and
     * target, this function returns \c false without adding to the table.
     */
    bool add(const RWCString& source, const RWCString& target, double convFactor)
    {
        return add(RWExchangeRate(source, target, convFactor));
    }

    /**
     * Removes the given exchange rate. If no such exchange rate was found,
     * this function returns \c false. Otherwise, it returns \c true.
     */
    bool remove(const RWExchangeRate& rate);

    /**
     * Removes the exchange rate for the given \a source and \a target
     * currencies. If no such exchange rate was found, this function returns
     * \c false. Otherwise, it returns \c true.
     */
    bool remove(const RWCString& source, const RWCString& target);

    /**
     * Searches the exchange rate table for an exchange rate with the same
     * source and target currencies as \a source and \a target. If one
     * exists, this function replaces its conversion factor with
     * \a convFactor, and returns \c true. If one does not exist, this
     * function returns \c false.
     */
    bool setConversionFactor(const RWCString& source, const RWCString& target, double convFactor);

    /**
     * Removes all exchange rates from the table.
     */
    void      clear();

    // Persistence to files and virtual streams.

    /**
     * Persists to a virtual stream.
     */
    void saveOn(RWvostream&) const;

    /**
     * Persists to an RWFile.
     */
    void saveOn(RWFile&) const;

    /**
     * Restore from a virtual stream.
     */
    void restoreFrom(RWvistream&);

    /**
     * Restore from an RWFile.
     */
    void restoreFrom(RWFile&);

    // Related Global Operators ----------------------------------------------
#ifndef _MSC_VER
    friend RW_DCML_MEMBER_EXPORT std::ostream& operator <<(std::ostream& strm, const RWExchangeRateTable& t);
#else
    friend std::ostream& operator <<(std::ostream& strm, const RWExchangeRateTable& t);
#endif

#ifndef _MSC_VER
    friend RW_DCML_MEMBER_EXPORT std::istream& operator >>(std::istream& strm, RWExchangeRateTable& t)
#else
    friend std::istream& operator >>(std::istream& strm, RWExchangeRateTable& t)
#endif
    {
        t.initialize(strm);
        return strm;
    }

private:

    RWTValHashDictionary<RWCString, RWExchangeRate>& table()
    {
        return tableRef_->table();
    }

    const RWTValHashDictionary<RWCString, RWExchangeRate>& table() const
    {
        return tableRef_->table();
    }

    void swap(RWExchangeRateTable& rhs);

private:
    RWExchangeTableRef* tableRef_;

    // Make sure that we have our own copy of the data.
    void makeDeepCopy();

    // For the hash dictionary key from the source and target mnemonics
    static RWCString formKey(const RWCString& source, const RWCString& target);

    // Create an exchange rate with the name value pairs and insert
    // it into the table.
    bool enterExchangeRate(RWTValSlist<RWNameValuePair>&);
};


// Persistence to virtual streams and RWFiles via shift operators

/**
 * \relates RWExchangeRateTable
 * Saves the object to a virtual stream.
 */
inline RWvostream& operator<<(RWvostream& s, const RWExchangeRateTable& t)
{
    t.saveOn(s);
    return s;
}

/**
 * \relates RWExchangeRateTable
 * Restores a object from a virtual stream.
 */
inline RWvistream& operator>>(RWvistream& s, RWExchangeRateTable& t)
{
    t.restoreFrom(s);
    return s;
}

/**
 * \relates RWExchangeRateTable
 * Saves the object to a RWFile.
 */
inline RWFile& operator<<(RWFile& f, const RWExchangeRateTable& t)
{
    t.saveOn(f);
    return f;
}

/**
 * \relates RWExchangeRateTable
 * Restores a object from a RWFile.
 */
inline RWFile& operator>>(RWFile& f, RWExchangeRateTable& t)
{
    t.restoreFrom(f);
    return f;
}

// MSVC 5.0 sp3 needs this inline or it will get unresolved symbols.
inline std::ostream& operator <<(std::ostream& strm, const RWExchangeRateTable& extable)
{
    const RWTValHashDictionary<RWCString, RWExchangeRate>& constTable =
        extable.table();
    RWTValHashDictionary<RWCString, RWExchangeRate>::const_iterator iter = constTable.begin();

    for (; iter != constTable.end(); ++iter) {
        const RWExchangeRate& rate = (*iter).second;
        strm << RWExchangeRateTable::beginToken << '\n';
        strm << RWExchangeRateTable::sourceTag << "=" << rate.source() << '\n';
        strm << RWExchangeRateTable::targetTag << "=" << rate.target() << '\n';
        strm << RWExchangeRateTable::conversionFactorTag << "=" << rate.conversionFactor() << '\n';
        strm << RWExchangeRateTable::endToken << "\n\n";
    }

    return strm;
}

#endif // RW_CURRENCY_EXCHGRATETBL_H
