#ifndef RW_CURRENCY_CURRENCY_H
#define RW_CURRENCY_CURRENCY_H

/***************************************************************************
 *
 * File:  currency.h
 *
 * Declarations for the class RWCurrency and related global functions
 *
 * $Id: //spro/rel2016.1/rw/currency/currency.h#1 $
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
#ifndef RW_MONEY_CURRENCY_H
#  define RW_MONEY_CURRENCY_H
#endif

#include <rw/currency/decdefs.h>
#include <rw/dcmldefs.h>
#include <rw/cstring.h>
#include <rw/decbase.h>
#include <rw/rwdate.h>
#include <rw/rwfile.h>
#include <rw/vstream.h>



/**
 * \ingroup currency_group
 *
 * \brief
 * A repository for currency information.
 *
 * The RWCurrency class provides a repository for the following currency
 * information:
 *
 * - <b>Mnemonic</b>. Defined in the ISO 4217:1995 standard. The mnemonic
 * uniquely identifies a currency.
 *
 * - <b>Numeric Code</b>. Defined in the ISO 4217:1995 standard. The numeric
 * code uniquely identifies a currency.
 *
 * - <b>Name</b>. Defined in the ISO 4217:1995 standard. The name uniquely
 * identifies a currency.
 *
 * - <b>Fraction Name</b>. The name of the fractional portion of a currency.
 * For example "Cents" is the fractional name of the United States dollar,
 * and "Pence" is the fractional name for the United Kingdom pound.
 *
 * - <b>Ratio of Whole to Fraction</b>. Ratio between one unit of the whole
 * part of a currency and the smallest unit of the fractional part of that
 * currency. For example, for United States Dollars the ratio is one dollar
 * to one penny which is 0.01.
 *
 * - <b>Introduction Date.</b> Date upon which the currency was, or will be,
 * introduced.
 *
 * - <b>Expiration Date.</b> Date upon which the currency is, or was, no
 * longer valid.
 *
 * If you omit the introduction date and the expiration date when
 * constructing an RWCurrency object, the constructor assigns them values of
 * the public static data members RWCurrency::noIntroductionDate and
 * RWCurrency::noExpirationDate, respectively.
 *
 * \synopsis
 * #include<rw/currency/currency.h>
 * RWCurrency USDollars("USD", 840, "dollar", "cents", 0.01);
 * \endsynopsis
 */
class RW_DCML_GLOBAL RWCurrency
{
public:
    // Values for the introduction and expiration dates when there are none.

    /**
     * These data members provide a way to deal with currencies that do not
     * have introduction or expiration dates. The data member
     * \ref RWCurrency::noIntroductionDate "noIntroductionDate" represents a
     * date that is "before the beginning of time." Similarly,
     * \ref RWCurrency::noExpirationDate "noExpirationDate" represents a
     * date that is "after the end of time." If you omit the introduction
     * date and the expiration date when constructing an RWCurrency object,
     * the constructor assigns these values. You can also use them in
     * applications to determine whether specific introduction or expiration
     * dates occur. The following example shows how they are used:
     *
     * \code
     * RWCurrency C;
     * .
     * .
     * .
     * if(C.expirationDate==RWCurrency::noExpirationDate)
     * {
     * .
     * .
     * .
     * }
     * RWDate d;
     * if(d<=RWCurrency::noExpirationDate)
     * //Always true
     * if(d>=RWCurrency::noIntroductionDate)
     * //Always true
     * \endcode
     */
    static const RWDate noIntroductionDate;

    /**
     * \copydoc noIntroductionDate
     */
    static const RWDate noExpirationDate;

    /**
     * Default constructor.
     */
    RWCurrency();

    /**
     * Copy constructor.
     */
    RWCurrency(const RWCurrency&);

    /**
     * Constructs an RWCurrency with the given information. The introduction
     * and expiration dates are assigned RWCurrency::noIntroductionDate and
     * RWCurrency::noExpirationDate, respectively.
     */
    RWCurrency(const RWCString& mnemonic,
               int              code,
               const RWCString& name,
               const RWCString& fractionName,
               double           wholeToFractRatio);

    /**
     * Constructs an RWCurrency with the given information.
     */
    RWCurrency(const RWCString& mnemonic,
               int              code,
               const RWCString& name,
               const RWCString& fractionName,
               double           wholeToFractRatio,
               const RWDate&    introDate,
               const RWDate&    expDate);

    // Public Member Functions -------------------------------------------------

    /**
     * Sets the currency's mnemonic to \a m.
     */
    void setMnemonic(const RWCString& m)
    {
        mnemonic_ = m;
    }

    /**
     * Sets the currency's name to \a n.
     */
    void setName(const RWCString& n)
    {
        name_ = n;
    }

    /**
     * Sets the currency's numeric code to \a c.
     */
    void setCode(int c)
    {
        code_ = c;
    }

    /**
     * Sets the currency's fraction name to \a fn.
     */
    void setFractionName(const RWCString& fn)
    {
        fractionName_ = fn;
    }

    /**
     * Sets the ratio between one unit of the whole part of the currency and
     * the smallest unit of the fractional part of the currency to \a r.
     */
    void setWholeToFractionRatio(double r)
    {
        wholeToFractionRatio_ = r;
    }

    /**
     * Sets a currency's introduction date. Note that this can be a date in
     * the past.
     */
    void setIntroductionDate(const RWDate& d)
    {
        introDate_ = d;
    }

    /**
     * Sets a currency's expiration date. Note that this can be a date in
     * the past.
     */
    void setExpirationDate(const RWDate& d)
    {
        expDate_ = d;
    }

    /**
     * Returns the currency's mnemonic.
     */
    RWCString mnemonic() const
    {
        return mnemonic_;
    }

    /**
     * Returns the currency's name.
     */
    RWCString name() const
    {
        return name_;
    }

    /**
     * Returns the currency's numeric code.
     */
    int code() const
    {
        return code_;
    }

    /**
     * Returns the currency's fraction name.
     */
    RWCString fractionName() const
    {
        return fractionName_;
    }

    /**
     * Returns the ratio between one unit of the whole part of the currency
     * and the smallest unit of the fractional part of the currency
     */
    double wholeToFractionRatio() const
    {
        return wholeToFractionRatio_;
    }

    /**
     * Returns a currency's introduction date. A return value of
     * RWCurrency::noIntroductionDate indicates there is no introduction
     * date.
     */
    RWDate introductionDate() const
    {
        return introDate_;
    }

    /**
     * Returns a currency's expiration date. A return value of
     * RWCurrency::noExpirationDate indicates there is no expiration date.
     */
    RWDate expirationDate() const
    {
        return expDate_;
    }

    /**
     * Returns \c true if today's date is beyond the currency's expiration
     * date.
     */
    bool hasExpired() const;

    /**
     * Returns \c true if today's date lies between the introduction date
     * and the expiration date.
     */
    bool isActive() const;

    /**
     * Persists the currency to a virtual stream.
     */
    void saveOn(RWvostream&) const;

    /**
     * Persists the currency to an RWFile.
     */
    void saveOn(RWFile&) const;

    /**
     * Restores the currency from a virtual stream.
     */
    void restoreFrom(RWvistream&);

    /**
     * Restores the currency from an RWFile.
     */
    void restoreFrom(RWFile&);

    // Operators----------------------------------------------------------------

    /**
     * Assignment operator.
     */
    RWCurrency& operator=(const RWCurrency&);

    // Related Global Operators --------------------------------------------------

    /**
     * Returns \c true if and only if all data members are equal.
     */
    friend RW_DCML_MEMBER_EXPORT bool operator==(const RWCurrency& a, const RWCurrency& b);

private:
    RWCString mnemonic_;
    int       code_;
    RWCString name_;
    RWCString fractionName_;
    double    wholeToFractionRatio_;
    RWDate    introDate_;
    RWDate    expDate_;
};

// xlC wants to instantiate everything.  So if I want to use templatized
// collection classes in std lib to store RWCurrency objects I have to
// define a < operator.  The following definition is arbitrary since the
// < operator makes no sense for currencies.yes
inline bool operator<(const RWCurrency& a, const RWCurrency& b)
{
    return (a.code() < b.code());
}

/**
 * \relates RWCurrency
 * Saves the currency object to a virtual stream.
 */
inline RWvostream& operator<<(RWvostream& s, const RWCurrency& c)
{
    c.saveOn(s);
    return s;
}

/**
 * \relates RWCurrency
 * Restores a currency object from a virtual stream.
 */
inline RWvistream& operator>>(RWvistream& s, RWCurrency& c)
{
    c.restoreFrom(s);
    return s;
}


/**
 * \relates RWCurrency
 * Saves the currency object to an RWFile.
 */
inline RWFile& operator<<(RWFile& f, const RWCurrency& c)
{
    c.saveOn(f);
    return f;
}

/**
 * \relates RWCurrency
 * Restores a currency object from an RWFile.
 */
inline RWFile& operator>>(RWFile& f, RWCurrency& c)
{
    c.restoreFrom(f);
    return f;
}

#endif // RW_CURRENCY_CURRENCY_H
