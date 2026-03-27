#ifndef __RWDB_NULLIND_H__
#define __RWDB_NULLIND_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/nullind.h#1 $
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
 * Null Indicators are used to signal the presence of NULL data fetched
 * from a database.  They can be used in conjunction with RWDBReader.
 * Applying the extraction RWDBReader::operator>>() to null indicator,
 * sets the null indicator to true/false if the next data item to be
 * read is/not NULL.
 * eg:
 * RWDBNullIndicator n1, n2;
 * int x, y;
 * rdr >> n1 >> x >> n2 >> y;  // rdr is an RWDBReader instance
 * After the above, n1 is true iff x is NULL; n2 is true iff y is NULL
 *
 **************************************************************************/

#include <rw/db/defs.h>

/**
 * \ingroup db_data_types_group
 *
 * \brief
 * Provides a way to determine whether some given data is \c NULL.
 *
 * RWDBNullIndicator allows application code:
 *
 * - to determine whether a particular piece of data extracted from an
 * RWDBReader is \c NULL
 * - to specify whether a bound value is \c NULL when using an RWDBBoundExpr
 *
 * An RWDBNullIndicator instance may be interpreted as a boolean value:
 * \c true means a data item is \c NULL; \c false means a data item is not
 * \c NULL.
 *
 * \synopsis
 * #include <rw/db/nullind.h>
 *
 * RWDBNullIndicator nullInd;
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBNullIndicator is designed specifically to detect \c NULL values as
 * they are extracted from an RWDBReader. See RWDBReader for more details.
 *
 * The setting of RWDBDatabase::emptyStringIsNull can affect the way that
 * empty strings are inserted and read. For more details, see
 * RWDBManager::emptyStringIsNull(bool).
 * \endparblock
 *
 * \example
 * This code fragment selects an integer and a string from a table, and
 * checks for \c NULL before processing the results:
 *
 * \code
 * RWDBTable myTable = myDBase.table("myTable");
 * RWDBSelector select = myDBase.selector();
 * select << myTable["id"] << myTable["name"];
 * RWDBReader rdr = select.reader();
 * int id;
 * RWCString name;
 * RWDBNullIndicator idIsNull;
 * RWDBNullIndicator nameIsNull;
 *
 * while (rdr()) {
 *   rdr >> idIsNull >> id >> nameIsNull >> name;
 *   if (idIsNull || nameIsNull) {
 *     // handle NULL case
 *   }
 *   else {
 *     // process name and id normally
 *   }
 * }
 * \endcode
 * \endexample
 */
class RWDB_SYMBOLIC RWDBNullIndicator
{
public:

    /**
     * Constructs an RWDBNullIndicator with the given initial \a value.
     */
    RWDBNullIndicator(bool value = 0)
        : value_(value)
    { }

    RWDBNullIndicator(const RWDBNullIndicator& ni)
        : value_(ni.value_)
    { }

    /**
     * Returns the current boolean value of self.
     */
    operator bool() const
    {
        return value_;
    }

    RWDBNullIndicator& operator=(const bool val)
    {
        value_ = val;
        return *this;
    }

private:
    bool value_;
};

#endif
