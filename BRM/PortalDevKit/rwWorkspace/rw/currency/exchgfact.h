#ifndef RW_CURRENCY_EXCHGFACT_H
#define RW_CURRENCY_EXCHGFACT_H

/***************************************************************************
 *
 * File:  exchgfact.h
 *
 * Declarations for the class RWExchangeFactory and related global
 * functions
 *
 * The exchange factory class basically maintains a list of
 * currency exchange groups.  When an exchange factory object receives
 * a request to construct a currency exchange object it finds the first
 * currency exchange group in the list which can construct such an object
 * and returns it.  The class is an adapter for the RWTValSlist<T> class.
 *
 * $Id: //spro/rel2016.1/rw/currency/exchgfact.h#1 $
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
#ifndef RW_MONEY_EXCHGFACT_H
#  define RW_MONEY_EXCHGFACT_H
#endif

#include <rw/currency/exchggroup.h>
#include <rw/currency/exchgratetbl.h>
#include <rw/dcmldefs.h>
#include <rw/cstring.h>
#include <rw/tvslist.h>


/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * Factory class that creates currency exchange objects.
 *
 * Currency Module provides a factory class, RWExchangeFactory that creates
 * currency exchange objects. The currency exchange factory is essentially a
 * list of RWExchangeGroup objects. When the factory receives a request for
 * a currency exchange object, it finds the first currency exchange group
 * that can create an RWExchange object and returns the object it found. By
 * default, upon construction, the RWExchangeFactory class always contains
 * one currency exchange group: RWMultiplicationGroup.
 *
 * The RWMultiplicationGroup group is the <em>default exchange group</em>,
 * and, initially, is always available in the factory's list of currency
 * groups. When presented with a source/target currency pair and exchange
 * rate table, the default exchange group looks for an exchange rate in the
 * table for the pair and, if found, constructs an RWExchange exchange rate
 * object, with an RWMultiplicationExchange implementation.
 *
 * \synopsis
 * #include <rw/currency/exchgfact.h>
 * #include <rw/currency/exchgratetbl.h>
 * RWExchangeRateTable rates;
 * RWExchangeFactory<double> factory(rates);
 * \endsynopsis
 */
template< class T >
class RWExchangeFactory
{
public:
    // Constructors ----------------------------------------------------------

    /**
     * Default constructor. By default the only exchange group in the
     * factory is the RWMultiplicationGroup group.
     */
    RWExchangeFactory();

    /**
     * Copy constructor. Constructs a copy of the factory \a f.
     */
    RWExchangeFactory(const RWExchangeFactory<T>& f);

    /**
     * Constructs an exchange factory that will use the given exchange rate
     * table and contain the RWMultiplicationGroup group.
     */
    RWExchangeFactory(const RWExchangeRateTable&);

    // Public Member Functions -----------------------------------------------

    /**
     * Returns \c true if the list contains the exchange group specified by
     * \a groupName. Note that Rogue Wave group names are given by the
     * class's static variable \a groupName, for example,
     * RWEuroGroup<T>::groupName.
     */
    bool containsExchangeGroup(const RWCString& groupName) const;

    /**
     * Removes all exchange groups from the factory, including the default
     * group.
     */
    void clearExchangeGroups()
    {
        exchangeGroups_.clear();
    }

    /**
     * Returns the number of exchange groups that are currently in the
     * factory.
     */
    size_t numberOfExchangeGroups() const
    {
        return exchangeGroups_.entries();
    }

    /**
     * Returns the list of exchange groups contained in the factory.
     */
    RWTValSlist< RWExchangeGroup<T> > exchangeGroups() const
    {
        return exchangeGroups_;
    }

    /**
     * Replaces the exchange groups in the factory with the ones in the list
     * \a l.
     */
    void setExchangeGroups(const RWTValSlist< RWExchangeGroup<T> >& l)
    {
        exchangeGroups_ = l;
    }

    // Find the named exchange group.  For Rogue Wave(R) currency exchange groups you
    // can use <Class Name>::groupName, eg, for division exchange group
    // RWDivisionGroup<T>::groupName (group name is a static RWCString
    // member of all the Rogue Wave(R) currency exchange groups).

    /**
     * Searches for exchange group \a name. If found, it is placed in \a grp
     * and the function returns \c true. If \a name is not found, \a grp
     * remains unchanged and the function returns \c false.
     */
    bool findExchangeGroup(const RWCString& name, RWExchangeGroup<T>& grp) const;

    /**
     * Returns the first exchange group in the list. The behavior is
     * undefined if the list is empty.
     */
    RWExchangeGroup<T> firstExchangeGroup() const
    {
        return exchangeGroups_.first();
    }

    /**
     * Returns the last exchange group in the list. The behavior is
     * undefined if the list is empty.
     */
    RWExchangeGroup<T> lastExchangeGroup() const
    {
        return ((RWTValSlist< RWExchangeGroup<T> >&)exchangeGroups_).last();
    }

    /**
     * Returns the exchange group at index \a i. An exception of type
     * RWBoundsErr will be thrown if \a i is not a valid index.
     */
    RWExchangeGroup<T> exchangeGroupAt(size_t i) const
    {
        return exchangeGroups_.at(i);
    }

    /**
     * Returns the index of the first exchange group whose name matches
     * \a groupName, or #RW_NPOS if there is no such object.
     */
    size_t exchangeGroupIndex(const RWCString& groupName) const;

    /**
     * Adds group \a g to the end of the list.
     */
    void appendExchangeGroup(const RWExchangeGroup<T>& g)
    {
        exchangeGroups_.append(g);
    }

    /**
     * Inserts group \a a into the index position specified by \a i. If the
     * index position is not between zero and the number of groups in the
     * list, the function throws an exception of type RWBoundsErr.
     */
    void insertExchangeGroupAt(size_t i, const RWExchangeGroup<T>& a)
    {
        exchangeGroups_.insertAt(i, a);
    }

    /**
     * Adds exchange group \a a to the beginning of the list.
     */
    void prependExchangeGroup(const RWExchangeGroup<T>& a)
    {
        exchangeGroups_.prepend(a);
    }

    /**
     * Removes the first object named \a groupName and returns \c true. If
     * \a groupName is not found, returns \c false.
     */
    bool removeExchangeGroup(const RWCString& groupName);

    /**
     * Removes the exchange group at index \a i and returns it. An exception
     * of type RWBoundsErr is thrown if \a i is not a valid index. Valid
     * indices are from zero to the number of items in the list less one.
     */
    RWExchangeGroup<T> removeExchangeGroupAt(size_t i)
    {
        return exchangeGroups_.removeAt(i);
    }

    /**
     * Removes the first exchange group in the list and returns it. The
     * behavior is undefined if the list is empty.
     */
    RWExchangeGroup<T> removeFirstExchangeGroup()
    {
        return exchangeGroups_.removeFirst();
    }

    /**
     * Removes the last exchange group in the list and returns it. The
     * behavior is undefined if the list is empty.
     */
    RWExchangeGroup<T> removeLastExchangeGroup()
    {
        return exchangeGroups_.removeLast();
    }

    /**
     * Returns the exchange rate table being used by the factory.
     */
    RWExchangeRateTable exchangeRateTable() const
    {
        return exchangeRateTable_;
    }

    /**
     * Returns the exchange rate table being used by the factory and can be
     * used to modify the table's contents.
     */
    RWExchangeRateTable& exchangeRateTable()
    {
        return exchangeRateTable_;
    }

    /**
     * Replaces the exchange rate table being used by the factory with \a t.
     */
    void setExchangeRateTable(const RWExchangeRateTable& t)
    {
        exchangeRateTable_ = t;
    }

    /**
     * Searches the list of currency groups in the factory until it finds
     * one that can create an exchange object, then returns the exchange
     * object. If no exchange group in the factory can create an exchange
     * object, this function returns an invalid exchange object. A valid
     * exchange object is determined by using the RWExchange<T>::isValid()
     * method.
     */
    RWExchange<T> getExchange(const RWCString& src, const RWCString& target) const;


    /**
     * Assignment operator.
     */
    RWExchangeFactory<T>& operator=(const RWExchangeFactory<T>&);

private:
    RWTValSlist< RWExchangeGroup<T> > exchangeGroups_;
    RWExchangeRateTable                  exchangeRateTable_;
};

#ifdef RW_MONEY_COMPILE_INSTANTIATE
#  include <rw/currency/exchgfact.cc>
#endif

#endif // RW_CURRENCY_EXCHGFACT_H
