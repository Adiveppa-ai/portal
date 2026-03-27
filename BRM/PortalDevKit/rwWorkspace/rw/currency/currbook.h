#ifndef RW_CURRENCY_CURRBOOK_H
#define RW_CURRENCY_CURRBOOK_H

/***************************************************************************
 *
 * File:  currbook.h
 *
 * Declarations for the class RWCurrencyBook and related global functions
 *
 * $Id: //spro/rel2016.1/rw/currency/currbook.h#1 $
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
#ifndef RW_MONEY_CURRBOOK_H
#  define RW_MONEY_CURRBOOK_H
#endif

#include <rw/currency/currency.h>
#include <rw/currency/decdefs.h>
#include <rw/currency/nameval.h>
#include <rw/dcmldefs.h>
#include <rw/cstring.h>
#include <rw/decbase.h>
#include <rw/rstream.h>
#include <rw/tvhdict.h>
#include <rw/tvslist.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup currency_group
 *
 * \brief
 * Stores RWCurrency objects in which each is identified by a unique
 * mnemonic.
 *
 * Class RWCurrencyBook stores RWCurrency objects. Each currency in the
 * currency book is identified by a unique mnemonic. A currency's mnemonic
 * can only appear once--duplicates are not allowed.
 *
 * Class RWCurrencyBook can be initialized from an \b std::istream. Currency
 * Module includes a file that can be used to initialize an RWCurrencyBook
 * through an \b std::ifstream. Appendix B lists the countries and the
 * currency mnemonics in the provided file.
 *
 * \synopsis
 * #include <rw/currency/currbook.h>
 * std::ifstream strm("currency_book.txt");
 * RWCurrencyBook b;
 * b.initialize(strm);
 * \endsynopsis
 */
class RW_DCML_GLOBAL RWCurrencyBook
{
public:
    // Valid names for name/value pairs used when parsing from a stream
    /**
     * The following static data members define the strings that provide
     * names for the name/value pairs used when initializing from a stream.
     * They are initialized to the valid names described in
     * RWCurrencyBook::initialize().
     */
    static const RWCString mnemonicTag;
    /**
     * \copydoc mnemonicTag
     */
    static const RWCString codeTag;
    /**
     * \copydoc mnemonicTag
     */
    static const RWCString nameTag;
    /**
     * \copydoc mnemonicTag
     */
    static const RWCString fractionNameTag;
    /**
     * \copydoc mnemonicTag
     */
    static const RWCString wholeToFractionTag;
    /**
     * \copydoc mnemonicTag
     */
    static const RWCString introDateTag;
    /**
     * \copydoc mnemonicTag
     */
    static const RWCString expDateTag;
    /**
     * \copydoc mnemonicTag
     */
    static const RWCString beginToken;
    /**
     * \copydoc mnemonicTag
     */
    static const RWCString endToken;

    // Constructors ------------------------------------------------------------

    /**
     * Default constructor. Creates an empty currency book.
     */
    RWCurrencyBook();

    /**
     * Copy constructor.
     */
    RWCurrencyBook(const RWCurrencyBook&);

    // Public Member Functions -------------------------------------------------

    /**
     * Initializes a currency book with currencies from \a strm. This method
     * returns \c false if there is an error in the stream format, or if one
     * or more of the currencies is missing a mnemonic.
     *
     * \note
     * The previous contents of self are deleted when this function is
     * invoked.
     *
     * A currency specification begins with the token \c BEGIN_CURRENCY, on
     * a line by itself. Each attribute of the currency is specified as a
     * name/value pair, one per line. The name/value separator is the equal
     * sign `='. The end of a currency specification is indicated by the
     * token \c END_CURRENCY. Comment lines start with a \c # character and
     * are automatically skipped. For example:
     *
     * \code
     * #Kenya
     * BEGIN_CURRENCY
     * mnemonic=KES
     * ratio =.01
     * name=shilling
     * fraction=cents
     * code=404
     * introduced=
     * expires=
     * END_CURRENCY
     * \endcode
     *
     * Name matching is case-<em>insensitive</em> and the only required
     * value is \c mnemonic. The initialize() function returns \c false if
     * one or more of the currencies is missing a mnemonic.
     *
     * Valid names are:
     *
     * \code
     * mnemonic
     * ratio
     * name
     * fraction
     * code
     * introduced
     * expires
     * \endcode
     */
    bool initialize(std::istream& strm);

    /**
     * Returns a collection of all the currencies in the currency book.
     */
    RWTValSlist<RWCurrency> getAllCurrencies() const;

    /**
     * Returns the mnemonics of all the currencies in the currency book.
     */
    RWTValSlist<RWCString> getAllCurrencyMnemonics() const;

    /**
     * Finds the currency indicated by \a mnemonic, places it in \a currency
     * and returns \c true. If no such currency exists, \a c is unchanged
     * and the function returns \c false.
     */
    bool find(const RWCString& mnemonic, RWCurrency& currency) const;

    /**
     * Returns \c true if the currency book contains the currency with the
     * given \a mnemonic.
     */
    bool contains(const RWCString& mnemonic) const;

    /**
     * Returns the number of currencies currently in the book.
     */
    size_t entries() const;

    /**
     * Adds the given \a currency to the currency book. If the currency book
     * already contains an entry that matches \a currency, insert() does not
     * add \a currency, and it returns \c false. Otherwise, insert() adds
     * \a currency to the currency book and returns \c true.
     */
    bool insert(const RWCurrency& currency);

    /**
     * Removes the currency indicated by \a mnemonic if it exists in the
     * currency book, and returns \c true. If \a mnemonic does not exist,
     * returns \c false.
     */
    bool remove(const RWCString& mnemonic);

    /**
     * Removes all currencies.
     */
    void clear();

    /**
     * Persists the currency book to a virtual stream.
     */
    void saveOn(RWvostream&) const;

    /**
     * Persists the currency book to an RWFile.
     */
    void saveOn(RWFile&) const;

    /**
     * Restores the currency book from a virtual stream.
     */
    void restoreFrom(RWvistream&);

    /**
     * Restores the currency book from an RWFile.
     */
    void restoreFrom(RWFile&);


    // Public Member Operators -----------------------------------------------

    /**
     * Assignment operator.
     */
    RWCurrencyBook& operator=(const RWCurrencyBook&);

    // Global Operators ------------------------------------------------------
    /**
     * Outputs the RWCurrencyBook to a stream in the same format shown in
     * the initialize() function.
     */
    friend std::ostream& operator<<(std::ostream&, const RWCurrencyBook&);

private:
    bool enterCurrency(RWTValSlist<RWNameValuePair>&);

    // Currencies are stored in a dictionary with the currency's mnemonic as
    // the key.
    RWTValHashDictionary<RWCString, RWCurrency> book_;

};


// Persistence to virtual streams and RWFiles
/**
 * Saves the object to a virtual stream.
 */
inline RWvostream& operator<<(RWvostream& s, const RWCurrencyBook& c)
{
    c.saveOn(s);
    return s;
}

/**
 * Restores a object from a virtual stream.
 */
inline RWvistream& operator>>(RWvistream& s, RWCurrencyBook& c)
{
    c.restoreFrom(s);
    return s;
}

/**
 * Saves the object to a RWFile.
 */
inline RWFile& operator<<(RWFile& f, const RWCurrencyBook& c)
{
    c.saveOn(f);
    return f;
}

/**
 * Restores a object from a RWFile.
 */
inline RWFile& operator>>(RWFile& f, RWCurrencyBook& c)
{
    c.restoreFrom(f);
    return f;
}


// Print to a stream in a human readable form

// MSVC 5.0 will not generate code unless this is inline.
inline std::ostream& operator<<(std::ostream& strm, const RWCurrencyBook& b)
{
    RWCurrency currency;
    RWTValHashDictionary<RWCString, RWCurrency>::const_iterator iter = b.book_.begin();

    double ratio;
    int code;
    RWDate introDate, expDate;
    while (iter != b.book_.end()) {
        currency = (*iter++).second;
        strm << RWCurrencyBook::beginToken << '\n';
        strm << RWCurrencyBook::mnemonicTag << "=" << currency.mnemonic() << '\n';
        strm << RWCurrencyBook::nameTag << "=" << currency.name() << '\n';

        code = currency.code();
        strm << RWCurrencyBook::codeTag << "=";
        if (code == 0) {
            strm << "";
        }
        else {
            strm << code;
        }
        strm << '\n';

        strm << RWCurrencyBook::fractionNameTag << "=" << currency.fractionName() << '\n';

        strm << RWCurrencyBook::wholeToFractionTag << "=";
        ratio = currency.wholeToFractionRatio();
        if (ratio == 0.0) {
            strm << "";
        }
        else {
            strm << ratio;
        }
        strm << '\n';

        introDate = currency.introductionDate();
        strm << RWCurrencyBook::introDateTag << "=";
        if (introDate == RWCurrency::noIntroductionDate) {
            strm << "";
        }
        else {
            strm << introDate;
        }
        strm << '\n';

        expDate = currency.expirationDate();
        strm << RWCurrencyBook::expDateTag << "=";
        if (expDate == RWCurrency::noExpirationDate) {
            strm << "";
        }
        else {
            strm << expDate;
        }
        strm << '\n';

        strm << RWCurrencyBook::endToken << "\n\n";
    }
    return strm;
}

/**
 * \relates RWCurrencyBook
 * Replaces the contents of the currency book with the contents of the
 * stream. The format of the stream is the same as that described in the
 * initialize() member function.
 */
inline std::istream& operator>>(std::istream& strm, RWCurrencyBook& b)
{
    b.initialize(strm);
    return strm;
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // RW_CURRENCY_CURRBOOK_H
