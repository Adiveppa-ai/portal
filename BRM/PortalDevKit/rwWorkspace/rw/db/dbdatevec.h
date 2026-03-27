#ifndef __RWDB_DBDATEVEC_H__
#define __RWDB_DBDATEVEC_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbdatevec.h#1 $
 *
 * Copyright (c) 1994-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 * ** DEPRECATED **
 * Interface of RWDBDateVector
 *  This is provided only for backward compatibility with the 3.x versions
 *  and RWDBTBuffer<RWDBDateTime> should be used for new code.
 *
 **************************************************************************/
#include <rw/db/datetime.h>
#include <rw/db/dbref.h>
#include <rw/db/defs.h>

#if !defined(RW_DISABLE_DEPRECATED)
RW_SUPPRESS_DEPRECATED_WARNINGS

/**
 * \ingroup db_bulk_operations_group
 *
 * \deprecated
 * As of SourcePro 6, use RWDateTime along with
 * \ref RWDBTBuffer "RWDBTBuffer<RWDateTime>" instead.
 *
 * \brief
 * Deprecated. Encapsulates vendor-specific date structures.
 *
 * RWDBVendorDate is used to encapsulate vendor-specific date structures.
 * RWDBDateVector is an array of RWDBVendorDate objects. Methods are
 * provided to transfer date values between RWDBVendorDate and RWDBDateTime.
 *
 * \synopsis
 * #include <rw/db/dbdatevec.h>
 *
 * RWDBDateVector dateVector = db.dateVector(n);
 * RWDBVendorDate date = dateVector[i];
 * \endsynopsis
 *
 * \example
 * In the following example, a vector \c dateVector is produced. The vector
 * is initialized with the current date and the following four days:
 *
 * \code
 * RWDBDateVector dateVector = aDB.dateVector(5);
 * RWDBDateTime dt; // Today's date.
 *
 * for (int k = 0; k < 5; k++) {
 *    dateVector[k] = dt;
 *    dt.addDays(1);
 * }
 * \endcode
 * \endexample
 */
class RW_DEPRECATE_TYPE("Use RWDateTime and RWDBTBuffer<RWDateTime> instead") RWDBVendorDate
{
public:

    RWDBVendorDate(RWDBDateTime& datetime)
        : datetime_(datetime)
    {
    }

    /**
     * Copies the date held in \a datetime to self.
     */
    RWDBVendorDate(const RWDBVendorDate& datetime)
        : datetime_(datetime.datetime_)
    {
    }

    /**
     * Assigns the date value held in \a date to self.
     */
    RWDBVendorDate& operator=(const RWDBVendorDate& date)
    {
        datetime_ = date.datetime_;
        return *this;
    }

    /**
     * Assigns the date value held in \a dt to self.
     */
    RWDBVendorDate& operator=(const RWDBDateTime& dt)
    {
        datetime_ = dt;
        return *this;
    }

    /**
     * Conversion operator. Returns an RWDBDateTime representation of self.
     */
    operator RWDBDateTime()
    {
        return datetime_;
    }

    /**
     * Returns a string representation of the \c date held in self.
     */
    RWCString asString() const
    {
        return datetime_.asString();
    }
private:
    RWDBDateTime& datetime_;
};

/**
 * \ingroup db_bulk_operations_group
 *
 * \deprecated
 * As of SourcePro 6, use \ref RWDBTBuffer "RWDBTBuffer<RWDateTime>" and
 * RWDateTime instead.
 *
 * \brief
 * Deprecated. Used as a buffer when transferring date values between the
 * application and the database.
 *
 * RWDBDateVector is used to transfer date values between the application
 * and the database via instances of RWDBBulkReader and RWDBBulkInserter.
 * Class RWDBDateVector implements basic vector methods and adds null
 * processing capabilities similar to RWDBVector. RWDBDateVector objects are
 * produced by RWDBDatabase. The resulting RWDBDateVector elements are
 * RWDBVendorDate instances of the type appropriate for the underlying
 * database.
 *
 * \synopsis
 * #include <rw/db/dbdatevec.h>
 * #include <rw/db/dbase.h>
 *
 * RWDBDateVector dateVector = db.dateVector(n);
 * \endsynopsis
 *
 * \example
 * In the following example, a vector \c dateVector is produced. The vector
 * could later be used with either an RWDBBulkInserter or an RWDBBulkReader.
 *
 * \code
 * RWDBDateVector dateVector = aDB.dateVector(n);
 * \endcode
 * \endexample
 */
class RW_DEPRECATE_TYPE("Use RWDBTBuffer<RWDateTime> and RWDateTime instead") RWDB_SYMBOLIC RWDBDateVector
{
public:
    RWDBDateVector(RWDBDateVectorImp* imp);
    RWDBDateVector(const RWDBDateVector& dVec);
    RWDBDateVector& operator=(const RWDBDateVector& dVec);
    ~RWDBDateVector();

    /**
     * Returns an instance of an RWDBVendorDate, which in turn holds a
     * reference to the underlying vendor date structure held in the
     * \a index <sup>th</sup> position.
     */
    RWDBVendorDate operator[](size_t index) const;

    /**
     * Returns the number of elements in self.
     */
    size_t entries() const;

    /**
     * Returns the number of elements in self.
     */
    size_t length() const;

    /**
     * Returns \c true if the \a index <sup>th</sup> element of self is
     * null, otherwise returns \c false .
     */
    bool isNull(size_t index) const;

    /**
     * Sets the \a index <sup>th</sup> element of self to null.
     */
    void      setNull(size_t index);

    /**
     * Sets the \a index <sup>th</sup> element of self to not null.
     */
    void      unsetNull(size_t index);

private:
    RWDBCountedRef<RWDBDateVectorImp> impl_;
    friend RWDBDateVectorImp* getImp(const RWDBDateVector& dv)
    {
        return dv.impl_;
    }
};

RW_RESTORE_DEPRECATED_WARNINGS
#endif // ! RW_DISABLE_DEPRECATED

#endif
