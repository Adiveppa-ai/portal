#ifndef __RWDB_IDENTITY_H__
#define __RWDB_IDENTITY_H__
/*************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/identity.h#1 $
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
 **************************************************************************/
#include <rw/db/dbref.h>
#include <rw/db/defs.h>
#include <rw/db/value.h>

/**
 * \ingroup db_common_group
 *
 * \brief
 * Represents an identity constraint of a column within a table or schema.
 *
 * An RWDBIdentityConstraint is used to represent an identity column in a
 * database. It is used with RWDBColumn to define an identity column when
 * building up an RWDBSchema in preparation for an
 * RWDBDatabase::createTable() call.
 *
 * An RWDBIdentityConstraint is also used with RWDBColumn instances in an
 * RWDBSchema. An RWDBSchema is a collection of RWDBColumn objects used to
 * describe a database table. If a column of the database table is an
 * identity column, it is represented by an RWDBIdentityConstraint. The
 * attributes of an identity column are available via the accessor methods
 * in RWDBIdentityConstraint.
 *
 * The identity column attributes supported by database vendors varies. If
 * an attribute is not defined for the identity column, or not available,
 * the returned RWDBValue will be \c NULL and of NoType.
 */
class RWDB_SYMBOLIC RWDBIdentityConstraint
{
public:
    // no attributes are set and no impl is created
    /**
     * Default constructor. No attributes are set. The created identity
     * constraint is not valid unless \c true is passed to the constructor.
     */
    RWDBIdentityConstraint(bool valid = false);

    /**
     * Constructs a new RWDBIdentityConstraint with the supplied parameters:
     *
     * - \b startWith --- the first value for the identity column
     *
     * - \b incrementBy --- the interval between consecutive values of the
     * identity column
     *
     * - \b maxValue --- the maximum value at which an ascending identity
     * column either cycles or stops generating values, or a descending
     * identity column cycles to after reaching the minimum value
     *
     * - \b minValue --- the minimum value at which a descending identity
     * column either cycles or stops generating values, or an ascending
     * identity column cycles to after reaching the maximum value
     *
     * - \b cycle --- bool that specifies whether values continue to be
     * generated for this column after the maximum or minimum value has been
     * reached. The maximum and minimum values for the identity column
     * determine the range that is used for cycling.
     */
    RWDBIdentityConstraint(const RWDBValue& startWith,
                           const RWDBValue& incrementBy,
                           const RWDBValue& maxValue,
                           const RWDBValue& minValue, bool cycle);

    /**
     * Copy constructor. The created constraint is a deep copy of \a idC.
     */
    RWDBIdentityConstraint(const RWDBIdentityConstraint& idC);

    ~RWDBIdentityConstraint();

    /**
     * Assignment operator. Self copies the implementation of \a idC.
     */
    RWDBIdentityConstraint& operator=(const RWDBIdentityConstraint& idC);

    /**
     * Sets the START WITH value to \a startWith. When creating a table, if
     * startWith() is set, the <tt>START WITH \a startWith</tt> clause is
     * used during table creation. If not supported by the database vendor
     * it is silently ignored.
     */
    RWDBIdentityConstraint& startWith(const RWDBValue& startWith);

    /**
     * Returns the START WITH value, if available, as an RWDBValue of the
     * appropriate type and value; otherwise the returned RWDBValue is
     * \c NULL and of NoType.
     */
    RWDBValue               startWith() const;

    /**
     * Sets the INCREMENT BY value to \a incrementBy. When creating a table,
     * if incrementBy() is set, then the
     * <tt>INCREMENT BY \a incrementBy</tt> clause is used during table
     * creation. If not supported by the database vendor it is silently
     * ignored.
     */
    RWDBIdentityConstraint& incrementBy(const RWDBValue& incrementBy);

    /**
     * Returns the INCREMENT BY value, if available, as an RWDBValue of the
     * appropriate type and value; otherwise the returned RWDBValue is
     * \c NULL and of NoType.
     */
    RWDBValue               incrementBy() const;

    /**
     * Sets the MAXVALUE value to \a max. When creating a table, if
     * maxValue() is set, the <tt>MAXVALUE \a max</tt> clause is used during
     * table creation. If not supported by the database vendor it is
     * silently ignored.
     */
    RWDBIdentityConstraint& maxValue(const RWDBValue& max);

    /**
     * Returns the MAXVALUE, if available, as an RWDBValue of the
     * appropriate type and value; otherwise the returned RWDBValue is
     * \c NULL and of NoType.
     */
    RWDBValue               maxValue() const;

    /**
     * Sets the MINVALUE to \a min. When creating a table, if minValue() is
     * set, the <tt>MINVALUE \a min</tt> clause is used during table
     * creation. If not supported by the database vendor it is silently
     * ignored.
     */
    RWDBIdentityConstraint& minValue(const RWDBValue& min);

    /**
     * Returns the MINVALUE, if available, as an RWDBValue of the
     * appropriate type and value; otherwise the returned RWDBValue is
     * \c NULL and of NoType.
     */
    RWDBValue               minValue() const;

    /**
     * Sets the CYCLE value to \a cycle. When creating a table, if cycle()
     * is \c true, the <tt>CYCLE</tt> clause is used during table creation.
     * If not supported by the database vendor it is silently ignored.
     */
    RWDBIdentityConstraint& cycle(bool cycle);

    /**
     * Returns \c true if the CYCLE attribute is set.
     */
    bool                    cycle() const;

    /**
     * Returns \c true if self is an identity column (or any properties for
     * defining identity columns are set).
     */
    bool                    isValid() const;

    // undocumented methods to allow the cache manager to be persisted.
    void saveGuts(RWFile& f) const;
    void restoreGuts(RWFile& f);
    void saveGuts(RWvostream& s) const;
    void restoreGuts(RWvistream& s);

private:
    RWDBCountedRef<RWDBIdentityConstraintImp> impl_;
};



#endif
