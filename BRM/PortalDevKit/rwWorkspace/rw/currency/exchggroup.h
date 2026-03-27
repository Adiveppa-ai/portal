#ifndef RW_CURRENCY_EXCHGGROUP_H
#define RW_CURRENCY_EXCHGGROUP_H

/***************************************************************************
 *
 * File:  exchggroup.h
 *
 * Declarations for the class RWExchangeGroup and related global
 * functions
 *
 * $Id: //spro/rel2016.1/rw/currency/exchggroup.h#1 $
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
#ifndef RW_MONEY_EXCHGGROUP_H
#  define RW_MONEY_EXCHGGROUP_H
#endif

#include <rw/dcmldefs.h>
#include <rw/dcmlerr.h>
#include <rw/cstring.h>
#include <rw/decbase.h>

// Forward Declarations
class                     RW_DCML_GLOBAL  RWExchangeRateTable;
template< class T > class RWExchange;


/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * Abstract base class from which all exchange group implementation classes
 * must derive. Implements the handle-body pattern in which RWExchangeGroup
 * is the handle.
 *
 * RWExchangeGroupImpl is an abstract base class from which all exchange
 * group implementation classes must derive. Class RWExchangeGroup is the
 * handle class, which forwards all conversion requests to its associated
 * implementation class.
 *
 * \synopsis
 * #include<rw/currency/exchggroup.h>
 * \endsynopsis
 */
template< class T >
class RWExchangeGroupImpl
{
public:
    // Constructors ----------------------------------------------------------

    /**
     * Default constructor.
     */
    RWExchangeGroupImpl()
    {
        ;
    }

    virtual ~RWExchangeGroupImpl()
    {
        ;
    }

    // Public Member Functions -----------------------------------------------

    /**
     * Creates and returns a currency exchange object for converting money
     * in the source currency to money in the target currency using the
     * exchange rates table \a rates. If the parameters are invalid, the
     * Rogue Wave classes that derive from this class return an invalid
     * exchange object.
     */
    virtual RWExchange<T> getExchange(const RWCString& srcMnemonic,
                                      const RWCString& tragetMnemonic,
                                      const RWExchangeRateTable& rates) const = 0;

    /**
     * Returns a name to be associated with the group.
     */
    virtual RWCString name() const = 0;

    /**
     * Returns a copy of self allocated off the heap.
     */
    virtual RWExchangeGroupImpl<T>* clone() const = 0;
};


/**
 * \ingroup currency_conversion_group
 *
 * \brief
 * The handle for the implementation class RWExchangeGroupImpl, the abstract
 * base class for all currency exchange group implementations. A currency
 * exchange group is a collection of currencies that use the same
 * currency-conversion rules.
 *
 * A <em>currency exchange group</em> is a collection of currencies that
 * have a common distinguishing characteristic related to converting money
 * from one currency to money of another currency. For example, the <em>Euro
 * Currency Exchange Group</em> consists of all the currencies that will
 * eventually be replaced by the Euro. All currencies in the Euro Currency
 * Exchange Group use the same, special rule for converting money between
 * currencies in this group.
 *
 * The exchange group classes are implemented using a <em>handle/body</em>
 * or <em>bridge</em> design pattern. The handle class is RWExchangeGroup.
 * This class contains a pointer to implementation class
 * RWExchangeGroupImpl. RWExchangeGroupImpl is an abstract base class from
 * which all currency group implementations must derive. The purpose of an
 * exchange group object is to take as input a source currency, target
 * currency, and an exchange rate table, then produce an exchange object.
 * Thus a key component of the class RWExchangeGroupImpl is a pure virtual
 * method:
 *
 * \code
 * virtual  RWExchange<T>
 * RWExchangeGroupImpl<T>::getExchange(const  RWCString&  source,
 *                                     const  RWCString&  target,
 *                                     const  RWExchangeRateTable&  rates) const;
 * \endcode
 *
 * Currency Module includes three currency exchange group implementation
 * classes:
 *
 * - RWEuroGroup, which creates and returns an RWExchange object with the
 * RWTriangularExchange implementation.
 * - RWMultiplicationGroup, which creates and returns an RWExchange object
 * with the RWMultiplicationExchange implementation.
 * - RWDivisionGroup, which creates and returns an RWExchange object with
 * the RWDivisionExchange implementation.
 *
 * \synopsis
 * #include<rw/currency/exchggroup.h>
 * \endsynopsis
 */
template< class T >
class RWExchangeGroup
{
public:
    // Constructors ----------------------------------------------------------

    /**
     * Default constructor.
     */
    RWExchangeGroup(): impl_(rwnil)
    {
        ;
    }

    /**
     * Makes a (deep) copy of the implementation for currency exchange group
     * object \a eg.
     */
    RWExchangeGroup(const RWExchangeGroup<T>& eg)
    {
        impl_ = (eg.impl_ == rwnil ? rwnil : eg.impl_->clone());
    }

    /**
     * Constructs an exchange group object with the provided implementation
     * \a imp. The object's destructor will delete \a imp.
     */
    RWExchangeGroup(RWExchangeGroupImpl<T>* imp): impl_(imp)
    {
        ;
    }

    // Destructor ------------------------------------------------------------
    ~RWExchangeGroup()
    {
        delete impl_;
    }

    // Public Member Functions -----------------------------------------------

    /**
     * Creates and returns a currency exchange object for converting money
     * in the source currency to money in the target currency using the
     * exchange rates table \a rates. If the parameters are not valid, an
     * invalid exchange object is returned.
     */
    RWExchange<T> getExchange(const RWCString& srcMnemonic,
                              const RWCString& targetMnemonic,
                              const RWExchangeRateTable& rates) const
    {
        if (impl_ == rwnil) {
            RWTHROW(RWInternalErr(RWMessage(RWDCML_NULLEXCHGGRPIMPL)));
        }

        return impl_->getExchange(srcMnemonic, targetMnemonic, rates);
    }

    /**
     * Returns a name to be associated with the group.
     */
    RWCString name() const
    {
        if (impl_ == rwnil) {
            RWTHROW(RWInternalErr(RWMessage(RWDCML_NULLEXCHGGRPIMPL)));
        }

        return impl_->name();
    }

    /**
     * Returns a pointer to the implementation class.
     */
    RWExchangeGroupImpl<T>* impl() const
    {
        return impl_;
    }

    /**
     * Sets self to the RWExchangeGroupImpl object pointed to by \a i.
     */
    void setImpl(RWExchangeGroupImpl<T>* i)
    {
        if (impl_ != i) {
            delete impl_;
            impl_ = i;
        }
    }

    // Public Member Operators -----------------------------------------------

    /**
     * Deletes self's current implementation and clones a copy of the
     * implementation for \a eg.
     */
    RWExchangeGroup<T>& operator=(const RWExchangeGroup<T>& eg)
    {
        if (&eg != this) {
            delete impl_;
            impl_ = eg.impl_->clone();
        }

        return *this;
    }

private:
    RWExchangeGroupImpl<T>* impl_;
};


// Some compilers, like xlC, instantiate *every* member function in a class template.
// So, even though I do not want to define an == operator for this class I must if
// I want to use it as a template parameter to RWTValSlist<T>.
template< class T >
inline bool operator==(const RWExchangeGroup<T>& a, const RWExchangeGroup<T>& b)
{
    return (a.name() == b.name());
}

template< class T >
inline bool operator<(const RWExchangeGroup<T>& a, const RWExchangeGroup<T>& b)
{
    return (a.name() < b.name());
}


#endif // RW_CURRENCY_EXCHGGROUP_H
