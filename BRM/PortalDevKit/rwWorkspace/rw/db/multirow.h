#ifndef __RWDB_MULTIROW_H__
#define __RWDB_MULTIROW_H__

/*************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/multirow.h#1 $
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
 **************************************************************************
 *
 * Declaration of class RWDBMultiRow
 *
 * Provides an object that represents a generic buffer list.
 *
 *************************************************************************/

#include <rw/db/adapter.h>
#include <rw/db/dbref.h>
#include <rw/db/defs.h>
#include <rw/db/row.h>

/**
 * \ingroup db_open_sql_group
 *
 * \brief
 * Provides a mechanism by which a collection of bindable objects can be
 * used with the RWDBValue and RWDBRow interface.
 *
 * Class RWDBMultiRow provides a mechanism by which a collection of bindable
 * objects can be used with the RWDBValue and RWDBRow interface. These
 * bindable objects are subclasses of RWDBAbstractBuffer, typically
 * RWDBTBuffer objects, and subclasses of RWDBDataCallback. They can be
 * manually created and appended to the RWDBMultiRow, or the RWDBMultiRow
 * can create appropriate RWDBAbstractBuffer objects when given an
 * RWDBSchema.
 *
 * \synopsis
 * #include <rw/db/multirow.h>
 * \endsynopsis
 *
 * \example
 * Please see <b>Example 2</b> in the entry for RWDBOSql.
 * \endexample
 */
class RWDB_SYMBOLIC RWDBMultiRow
{
public:

    /**
     * Default constructor. Creates an RWDBMultiRow with no bindable objects
     * or ownership indicators; in other words, an empty instance.
     * Internally, RWDBMultiRow is a handle class that refers to a body that
     * contains the state. The constructor creates a new implementation
     * object for the body.
     */
    RWDBMultiRow();

    // ownership flag is ignored, equivalent to the default constructor.
    RWDBMultiRow(bool ownership);

    /**
     * Copy constructor. Creates an RWDBMultiRow that shares an
     * implementation with \a rhs.
     */
    RWDBMultiRow(const RWDBMultiRow& rhs);

    /**
     * Creates an RWDBMultiRow and populates it with multiple RWDBTBuffer
     * instances, each corresponding to, and type-compatible with, the
     * columns from \a s. Each created RWDBTBuffer is of length \a rows.
     * Each created RWDBTBuffer is owned by the RWDBMultiRow.
     */
    RWDBMultiRow(const RWDBSchema& s,
                 size_t rows = 1);

    RWDBMultiRow(const RWDBSchema& schema,
                 size_t rows,
                 const RWDBBufferFactory& factory);
    RWDBMultiRow(RWDBMultiRowImp* imp);

    /**
     * Standard handle/body destructor. The destructor of the body object
     * deletes all \b Type arrays that are owned by the RWDBMultiRow.
     */
    ~RWDBMultiRow();

    /**
     * Assignment operator. Discards self's current implementation and
     * shares that of \a r.
     */
    RWDBMultiRow& operator=(const RWDBMultiRow& r);

    /**
     * Returns an RWDBRow by value for the data in all the contained
     * RWDBAbstractBuffer and RWDBDataCallback instances at row \a i. The
     * RWDBRow will contain values of RWDBValue::NoType for any
     * RWDBDataCallback instances in the row. In debug mode libraries,
     * bounds checking is performed on \a i. Note that changes made to the
     * returned RWDBRow are not reflected in the RWDBAbstractBuffer
     * instances held by the RWDBMultiRow.
     */
    RWDBRow operator[](size_t i) const;

    /**
     * Appends \a b to the collection of bindable objects. \a b is not
     * considered to be owned by the RWDBMultiRow. This operator is
     * overloaded to allow the following syntax:
     *
     * \code
     * RWDBOSql  aSql  ("SELECT  INTCOL  FROM  MYTABLE");
     * RWDBTBuffer<int>  aBuffer(10);
     *
     * aSql[0]  >>  aBuffer;
     *
     * aSql.execute(aConnection);
     * aSql.fetch();
     * \endcode
     *
     * In this example, \c aBuffer is appended to the output RWDBMultiRow
     * for the \c 0 <sup>th</sup> result set, and the result data for
     * \c INTCOL is fetched into \c aBuffer. Also see
     * RWDBOSql::operator[](size_t).
     */
    RWDBMultiRow& operator>>(RWDBAbstractBuffer& b);

    /**
     * Appends \a b to the collection of bindable objects. \a b is not
     * considered to be owned by the RWDBMultiRow.
     */
    RWDBMultiRow& operator>>(RWDBDataCallback& b);

    /**
     * Returns a reference to the \a index <sup>th</sup> RWDBAbstractBuffer.
     * Bounds checking is performed on \a index in debug versions of the
     * library.
     */
    RWDBAbstractBuffer& bufferAt(size_t index) const;

    /**
     * Appends this bindable object to the collection of bindable objects.
     * If \a ownership is true the \a item is considered to be owned by
     * self.
     */
    void append(RWDBAbstractBuffer* item, bool ownership = true);

    /**
     * Appends this bindable object to the collection of bindable objects.
     * If \a ownership is true the \a item is considered to be owned by
     * self.
     */
    void append(RWDBDataCallback* item, bool ownership = true);

    void replaceAt(size_t index,
                   RWDBAbstractBuffer* newBuffer,
                   bool ownership = true);
    void clear();

    /**
     * Returns the number of rows. If bindable objects of varying lengths
     * were appended, returns the minimum of the lengths of the contained
     * bindable objects.
     */
    size_t entries() const;

    /**
     * Returns the number of columns in the RWDBMultiRow, that is, the
     * number of bindable objects appended to it.
     */
    size_t numberOfColumns() const;

    /**
     * Returns the RWDBSchema passed in during construction if the relevant
     * constructor was chosen. Otherwise, creates and returns a schema
     * representing the metadata of the contained RWDBAbstractBuffer
     * instances.
     */
    RWDBSchema schema() const;

    bool operator==(const RWDBMultiRow& rhs) const;
    bool operator<(const RWDBMultiRow& rhs) const;
    bool operator!=(const RWDBMultiRow& rhs) const;

    void      extract(size_t index, RWDBRow& row);

    // For internal use.
    void sync(RWDBAdapterFactory& f, size_t entries);

    void syncOutputParams(RWDBAdapterFactory& f, size_t entries);

    bool update(RWDBAdapterFactory& f, RWDBTracer& tr,
                size_t bulksize, const RWZone& timeZone);

private:
    RWDBCountedRef<RWDBMultiRowImp> impl_;

    friend RWDBMultiRowImp* getImp(const RWDBMultiRow& mr)
    {
        return mr.impl_;
    }
};


#endif // __RWDB_MULTIROW_H__
