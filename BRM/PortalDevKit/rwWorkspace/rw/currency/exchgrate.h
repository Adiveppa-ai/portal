#ifndef RW_CURRENCY_EXCHGRATE_H
#define RW_CURRENCY_EXCHGRATE_H

/***************************************************************************
 *
 * File:  exchgrate.h
 *
 * Declarations for the class RWExchangeRate and related global functions
 *
 * $Id: //spro/rel2016.1/rw/currency/exchgrate.h#1 $
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
#ifndef RW_MONEY_EXCHGRATE_H
#  define RW_MONEY_EXCHGRATE_H
#endif

#include <rw/currency/decdefs.h>
#include <rw/dcmldefs.h>
#include <rw/cstring.h>
#include <rw/decbase.h>
#include <rw/rwfile.h>
#include <rw/vstream.h>
#include <math.h>


/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * Encapsulates a source currency, a target currency, and a conversion
 * factor, which is, by convention, a <em>multiplicative conversion
 * factor</em>.
 *
 * Class RWExchangeRate encapsulates a source currency, a target currency,
 * and a conversion factor, which is, by convention, a <em>multiplicative
 * conversion factor</em>. This means that the source currency amount is
 * multiplied by the conversion factor to obtain the equivalent amount in
 * the target currency. Source and target currencies are stored by their
 * mnemonics and the conversion factor is stored as a double precision
 * floating point number.
 *
 * \synopsis
 * #include <rw/currency/exchgrate.h>
 * RWExchangeRate r("USD", "INR",42.254);
 * \endsynopsis
 */
class RW_DCML_GLOBAL RWExchangeRate
{
public:
    // Constructors ----------------------------------------------------------

    /**
     * Default constructor. The source and target are set to null strings
     * and the rate is set to zero.
     */
    RWExchangeRate(): rate_(0.0)
    {
        ;
    }

    /**
     * Copy constructor. Contents of \a r are copied to self.
     */
    RWExchangeRate(const RWExchangeRate& r);

    /**
     * Constructs an exchange rate object with the given information. The
     * source currency mnemonic is contained in \a sourceMnemonic, the
     * target mnemonic is contained in \a targetMnemonic, and the
     * multiplicative conversion factor is contained in \a rate.
     */
    RWExchangeRate(const RWCString& sourceMnemonic,
                   const RWCString& targetMnemonic,
                   double rate);

    // Public Member Functions -----------------------------------------------

    // Accessors

    /**
     * Returns the mnemonic for the source currency.
     */
    RWCString source() const
    {
        return source_;
    }

    /**
     * Returns the mnemonic for the target currency.
     */
    RWCString target() const
    {
        return target_;
    }

    /**
     * Returns the multiplicative conversion factor for converting money
     * from source currency to target currency.
     */
    double    conversionFactor() const
    {
        return rate_;
    }

    // Mutators

    /**
     * Sets the source mnemonic to \a mnemonic.
     */
    void setSource(const RWCString& mnemonic)
    {
        source_ = mnemonic;
    }

    /**
     * Sets the target mnemonic to \a mnemonic.
     */
    void setTarget(const RWCString& mnemonic)
    {
        target_ = mnemonic;
    }

    /**
     * Sets the multiplicative conversion factor for converting money from
     * source currency to target currency to \a factor.
     */
    void setConversionFactor(double factor)
    {
        rate_ = factor;
    }

    // Persistence

    /**
     * Persist to a virtual stream.
     */
    void saveOn(RWvostream&) const;

    /**
     * Persist to an RWFile.
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

    // Public Member Operators -----------------------------------------------

    /**
     * Assignment operator. Assigns contents of \a r to self.
     */
    RWExchangeRate& operator=(const RWExchangeRate& r);

    // Related Global Friend Functions

    /**
     * \relates RWExchangeRate
     * Returns \c true if \a a and \a b have the same source mnemonic,
     * target mnemonic, and conversion factor. Returns \c false if not. The
     * comparison of the source and target mnemonics is case
     * <em>insensitive</em>.
     */
    friend bool operator==(const RWExchangeRate& a, const RWExchangeRate& b)
    {
        return ((a.source_.compareTo(b.source_, RWCString::ignoreCase) == 0) &&
                (a.target_.compareTo(b.target_, RWCString::ignoreCase) == 0) &&
                (fabs(a.rate_ - b.rate_) < DBL_EPSILON));
    }

private:
    RWCString source_;
    RWCString target_;
    double rate_;
};


// Some compilers, like xlC, instantiate everything in a class.  Whether you
// use it or not.  Consequently, if want to store exchange rates in a Tools
// hash dictionary you have to define a < operator for them.  The below
// operator is completely arbitrary and should not ever actually be
// used.  It's just here so xlC will be happy.
inline bool operator<(const RWExchangeRate& a, const RWExchangeRate& b)
{
    if (a.source() == b.source() && a.target() == b.target()) {
        return a.conversionFactor() < b.conversionFactor();
    }
    return false;
}

//--Global shift operators -------------------------------------------------

/**
 * \relates RWExchangeRate
 * Saves the object to a virtual stream.
 */
inline RWvostream& operator<<(RWvostream& s, const RWExchangeRate& r)
{
    r.saveOn(s);
    return s;
}

/**
 * \relates RWExchangeRate
 * Saves the object to a RWFile.
 */
inline RWFile& operator<<(RWFile& f, const RWExchangeRate& r)
{
    r.saveOn(f);
    return f;
}

/**
 * \relates RWExchangeRate
 * Restores a object from a virtual stream.
 */
inline RWvistream& operator>>(RWvistream& s, RWExchangeRate& r)
{
    r.restoreFrom(s);
    return s;
}

/**
 * \relates RWExchangeRate
 * Restores a object from a RWFile.
 */
inline RWFile& operator>>(RWFile& f, RWExchangeRate& r)
{
    r.restoreFrom(f);
    return f;
}

#endif // RW_CURRENCY_EXCHGRATE_H
