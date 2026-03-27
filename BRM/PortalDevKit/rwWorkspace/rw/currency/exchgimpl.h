#ifndef RW_CURRENCY_EXCHGIMPL_H
#define RW_CURRENCY_EXCHGIMPL_H

/***************************************************************************
 *
 * File:  exchgimpl.h
 *
 * Declarations for the class RWExchangeImpl and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/exchgimpl.h#1 $
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
#ifndef RW_MONEY_EXCHGIMPL_H
#  define RW_MONEY_EXCHGIMPL_H
#endif

#include <rw/currency/money.h>
#include <rw/dcmldefs.h>
#include <rw/cstring.h>

/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * The abstract base class from which all currency implementation classes
 * must derive.
 *
 * RWExchangeImpl is an abstract base class from which all currency
 * implementation classes must derive. Class RWExchange is the handle class,
 * which forwards all conversion requests to its associated implementation
 * class.
 *
 * \synopsis
 * #include <rw/currency/exchgimpl.h>
 * \endsynopsis
 */
template< class T >
class RWExchangeImpl
{
public:
    // Constructors ------------------------------------------

    // default ctor
    RWExchangeImpl()
    {
        ;
    }

    // copy ctor
    RWExchangeImpl(const RWExchangeImpl<T>& i)
        : source_(i.source_), target_(i.target_)
    {
        ;
    }

    // construct with given source and target currency mnemonics
    RWExchangeImpl(const RWCString& source, const RWCString& target)
        : source_(source), target_(target)
    {
        ;
    }

    virtual ~RWExchangeImpl()
    {
        ;
    }

    // Public member functions -----------------------------------------------

    // Pure virtual methods

    /**
     * Returns a copy of self off the heap.
     */
    virtual RWExchangeImpl<T>* clone() const = 0;

    /**
     * Pure virtual function for converting money from the source currency
     * to the target currency. If the currency associated with \a money does
     * not match the source currency for self, an exception will be thrown.
     */
    virtual RWMoney<T> exchange(const RWMoney<T>& money) const = 0;

    /**
     * Pure virtual function that returns the name of the implementation
     * class. Rogue Wave implementation classes return their static data
     * member \c exchangeMethodName. For example, when an RWExchange object
     * contains an RWTriangularExchange implementation, name() returns
     * RWTriangularExchange::exchangeMethodName.
     */
    virtual RWCString name() const = 0;

    // source and target accessors/mutators

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
     * Sets the mnemonic for the source currency.
     */
    void setSource(const RWCString& src)
    {
        source_ = src;
    }

    /**
     * Sets the mnemonic for the target currency.
     */
    void setTarget(const RWCString& trg)
    {
        target_ = trg;
    }

    // Public member operators -----------------------------------------------

    // Assignment operator
    RWExchangeImpl<T>& operator=(const RWExchangeImpl<T>& e)
    {
        if (&e != this) {
            source_ = e.source_;
            target_ = e.target_;
        }
        return *this;
    }

protected:
    RWCString source_;
    RWCString target_;
};


#endif // RW_CURRENCY_EXCHGIMPL_H
