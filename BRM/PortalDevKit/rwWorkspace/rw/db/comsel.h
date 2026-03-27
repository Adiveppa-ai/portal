#ifndef __RWDB_COMSEL_H__
#define __RWDB_COMSEL_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/comsel.h#1 $
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
 * A compound selector is the result of applying set operations (union,
 * intersection, difference) to selectors and/or other compound
 * selectors. Unfortunately, it is not the case that such an object
 * "is_a" selector: one cannot intelligently apply methods such as
 * where() to it (this is a direct consequence of SQL semantics).
 * So, rather than deriving compound selector from selector, they are
 * both derived from a common base class.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/db/select.h>

/**
 * \ingroup db_data_manipulation_group
 *
 * \brief
 * Represents the result of the set operators \c Union, \c Intersection, or
 * \c Difference applied to RWDBSelector.
 *
 * Instances of this class are created as the result of the set operators
 * \c Union, \c Intersection, \e or \c Difference applied to RWDBSelector.
 *
 * RWDBSelector and RWDBCompoundSelector share the common base class
 * RWDBSelectorBase.
 *
 * \synopsis
 * #include <rw/db/comsel.h>
 *
 * RWDBSelector s1, s2;
 *
 * RWDBCompoundSelector cs = s1 + s2;
 * RWDBCompoundSelector cs = s1 * s2
 * RWDBCompoundSelector cs = s1 - s2;
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBCompoundSelector : public RWDBSelectorBase
{
public:

    /**
     * Copy constructor. The created RWDBCompoundSelector shares an
     * implementation with \a csel.
     */
    RWDBCompoundSelector(const RWDBCompoundSelector& csel);

    RWDBCompoundSelector(RWDBCompoundSelectorImp* imp);

    /**
     * Assignment operator. Self shares an implementation with \a csel.
     * Returns a reference to self.
     */
    RWDBCompoundSelector& operator=(const RWDBCompoundSelector& csel);

    /**
     * Returns an RWDBCompoundSelector that represents the SQL selector:
     *
     * \e select-stmt \c UNION \a selector
     *
     * where \e select-stmt is the \c SELECT statement represented by self.
     * The trailing underscore avoids a conflict with the C++ \c union
     * keyword.
     */
    virtual
    RWDBCompoundSelector union_(const RWDBSelectorBase& selector) const
    {
        return RWDBSelectorBase::union_(selector);
    }

    /**
     * Returns an RWDBCompoundSelector that represents the SQL selector:
     *
     * \e select-stmt <tt>UNION ALL</tt> \a selector
     *
     * where \e select-stmt is the \c SELECT statement represented by self.
     */
    virtual
    RWDBCompoundSelector unionAll(const RWDBSelectorBase& selector) const
    {
        return RWDBSelectorBase::unionAll(selector);
    }

    /**
     * Returns an RWDBCompoundSelector that represents the SQL selector:
     *
     * \e select-stmt \c INTERSECTION \a selector
     *
     * where \e select-stmt is the \c SELECT statement represented by self.
     */
    virtual
    RWDBCompoundSelector intersection(const RWDBSelectorBase& selector) const
    {
        return RWDBSelectorBase::intersection(selector);
    }

    /**
     * Returns an RWDBCompoundSelector that represents the SQL selector:
     *
     * \e select-stmt \c DIFFERENCE \a selector
     *
     * where \e select-stmt is the \c SELECT statement represented by self.
     */
    virtual
    RWDBCompoundSelector difference(const RWDBSelectorBase& selector) const
    {
        return RWDBSelectorBase::difference(selector);
    }

    /**
     * Specifies \a column as an <tt>ORDER BY</tt> column for self. A select
     * statement may have multiple <tt>ORDER BY</tt> columns; successive
     * calls to orderBy() and orderByDescending() add <tt>ORDER BY</tt>
     * columns to self. The order of orderBy() and orderByDescending() calls
     * is retained. Returns a reference to self.
     */
    inline RWDBSelectorBase& orderBy(const RWDBColumn& column)
    {
        return RWDBSelectorBase::orderBy(column);
    }

    /**
     * Specifies \a columnNumber as an <tt>ORDER BY</tt> column for self. A
     * select statement may have multiple <tt>ORDER BY</tt> columns;
     * successive calls to orderBy() and orderByDescending() add
     * <tt>ORDER BY</tt> columns to self. The order of orderBy() and
     * orderByDescending() calls is retained. Returns a reference to self.
     */
    inline RWDBSelectorBase& orderBy(int columnNumber)
    {
        return RWDBSelectorBase::orderBy(columnNumber);
    }

    /**
     * Specifies \a column as an <tt>ORDER BY DESCENDING</tt> column for
     * self. A select statement may have multiple <tt>ORDER BY</tt> columns;
     * successive calls to orderBy() and orderByDescending() add
     * <tt>ORDER BY</tt> columns to self. The order of orderBy() and
     * orderByDescending() calls is retained. Returns a reference to self.
     */
    inline RWDBSelectorBase& orderByDescending(const RWDBColumn& column)
    {
        return RWDBSelectorBase::orderByDescending(column);
    }

    /**
     * Specifies \a columnNumber as an <tt>ORDER BY DESCENDING</tt> column
     * for self. A select statement may have multiple <tt>ORDER BY</tt>
     * columns; successive calls to orderBy() and orderByDescending() add
     * <tt>ORDER BY</tt> columns to self. The order of orderBy() and
     * orderByDescending() calls is retained. Returns a reference to self.
     */
    inline RWDBSelectorBase& orderByDescending(int columnNumber)
    {
        return RWDBSelectorBase::orderByDescending(columnNumber);
    }

    /**
     * Clears self's <tt>ORDER BY</tt> clause. Returns a reference to self.
     */
    inline RWDBSelectorBase& orderByClear()
    {
        return RWDBSelectorBase::orderByClear();
    }

    /**
     * Produces an RWDBReader that can be used to read data from self one
     * row at a time. Uses a default database connection which is held by
     * the RWDBReader until the RWDBReader is destroyed.
     *
     * \note
     * When \a cacheSize is \c 0, an acceptable default is selected by your
     * Access Module. Please check your Access Module documentation for
     * limitations on the cache size.
     */
    inline RWDBReader   reader(size_t cacheSize = 0) const
    {
        return RWDBSelectorBase::reader(cacheSize);
    }

    /**
     * Produces an RWDBReader that can be used to read data from self one
     * row at a time. Uses the supplied \a connection, which is held by the
     * RWDBReader until the RWDBReader is destroyed. This function can
     * behave asynchronously if executed using an asynchronous connection.
     *
     * \note
     * When \a cacheSize is \c 0, an acceptable default is selected by your
     * Access Module. Please check your Access Module documentation for
     * limitations on the cache size.
     */
    inline RWDBReader   reader(const RWDBConnection& connection, size_t cacheSize = 0) const
    {
        return RWDBSelectorBase::reader(connection, cacheSize);
    }

    /**
     * Returns \c true if self's status is RWDBStatus::ok, otherwise
     * \c false. Does not return \c false if the previously executed
     * statement failed. You must check the status of the RWDBResult
     * returned from execute() instead of the status of the
     * RWDBCompoundSelector object.
     */
    inline bool         isValid() const
    {
        return RWDBSelectorBase::isValid();
    }

    /**
     * Uses a default database connection to submit the SQL \c SELECT
     * statement encapsulated by self for execution. There will always be
     * one or more RWDBTable instances in the returned RWDBResult.
     */
    inline RWDBResult execute()
    {
        return RWDBSelectorBase::execute();
    }

    /**
     * Uses the supplied \a connection to submit the SQL \c SELECT statement
     * encapsulated by self for execution. There will always be one or more
     * RWDBTable instances in the returned RWDBResult. This function can
     * behave asynchronously if executed using an asynchronous connection.
     */
    inline RWDBResult execute(const RWDBConnection& connection)
    {
        return RWDBSelectorBase::execute(connection);
    }


    /**
     * Installs \a handler as self's error handler. The supplied \a handler
     * is inherited by all objects produced by self. By default, an
     * RWDBStatus::ErrorHandler is inherited from the object that produced
     * self; this method overrides the default.
     */
    inline void      setErrorHandler(RWDBStatus::ErrorHandler handler)
    {
        return RWDBSelectorBase::setErrorHandler(handler);
    }

    /**
     * Returns the error handler attached to self.
     */
    RWDBStatus::ErrorHandler errorHandler() const
    {
        return RWDBSelectorBase::errorHandler();
    }

    /**
     * Returns the status of self.
     */
    inline RWDBStatus       status() const
    {
        return RWDBSelectorBase::status();
    }

    /**
     * Returns the RWDBDatabase that produced this selector. If there is no
     * such object, for example, if this RWDBCompoundSelector was produced
     * using invalid RWDBSelector objects, returns an RWDBDatabase with a
     * status of RWDBStatus::notInitialized.
     */
    inline RWDBDatabase     database() const
    {
        return RWDBSelectorBase::database();
    }

    /**
     * Returns the SQL equivalent of:
     *
     * \code
     * (SELECT ...) <operator> (SELECT ...)
     * ORDER BY <orderby-list>
     * \endcode
     *
     * This method returns an SQL statement that would be produced by
     * executing self with an implicit RWDBConnection object. An implicit
     * RWDBConnection object inherits the time zone setting from the
     * producer RWDBDatabase instance. Hence, the time zone setting of the
     * producer RWDBDatabase object will be used for creating the string
     * representations of any RWDateTime instances in self.
     *
     * The behavior of this method depends upon the
     * RWDBDatabase::verboseAsString() setting in the producer RWDBDatabase
     * instance.
     *
     * - If \ref RWDBDatabase::verboseAsString() "verboseAsString()" is
     * \c false, the SQL returned is the same as that passed to the database
     * for execution. This is the default.
     * - If \ref RWDBDatabase::verboseAsString() "verboseAsString()" is
     * \c true, any placeholders in the returned SQL are replaced with their
     * bound values.
     *
     * \note
     * When the RWDBDatabase::verboseAsString() option is set to \c true,
     * the SQL returned by this method may not be a valid SQL statement.
     * However, this method's return value is not necessarily the same SQL
     * that is sent to the database for execution. For example, if an
     * RWDBBlob object is bound, calling this method with
     * RWDBDatabase::verboseAsString() set to \c true results in a string
     * with blob data returned as hex numbers, such as \c 0x0A32F5.
     *
     * \sa
     * RWDBDatabase::timeZone(const RWZone*) for time zone setting on
     * RWDBDatabase.
     */
    inline RWCString asString() const
    {
        return RWDBSelectorBase::asString();
    }

    /**
     * Returns the SQL equivalent of:
     *
     * \code
     * (SELECT ...) <operator> (SELECT ...)
     * ORDER BY <orderby-list>
     * \endcode
     *
     * This method returns an SQL statement that would be produced by
     * executing self with \a conn. The time zone setting of \a conn will be
     * used for creating string representations of any RWDateTime instances
     * in self.
     *
     * The behavior of this method depends upon the
     * RWDBDatabase::verboseAsString() setting in the producer RWDBDatabase
     * instance.
     *
     * - If \ref RWDBDatabase::verboseAsString() "verboseAsString()" is
     * \c false, the SQL returned is the same as that passed to the database
     * for execution. This is the default.
     * - If \ref RWDBDatabase::verboseAsString() "verboseAsString()" is
     * \c true, any placeholders in the returned SQL are replaced with their
     * bound values.
     *
     * \note
     * When the RWDBDatabase::verboseAsString() option is set to \c true,
     * the SQL returned by this method may not be a valid SQL statement.
     * However, this method's return value is not necessarily the same SQL
     * that is sent to the database for execution. For example, if an
     * RWDBBlob object is bound, calling this method with
     * RWDBDatabase::verboseAsString() set to \c true will result in a
     * string with blob data returned as hex numbers, such as \c 0x0A32F5.
     *
     * \sa
     * RWDBConnection::timeZone(const RWZone*) for time zone setting on
     * RWDBConnection.
     */
    inline RWCString asString(const RWDBConnection& conn) const
    {
        return RWDBSelectorBase::asString(conn);
    }

    /**
     * Returns the SQL equivalent of:
     *
     * \code
     * (SELECT ...) <operator> (SELECT ...)
     * ORDER BY <orderby-list>
     * \endcode
     *
     * This method returns an SQL statement that would be produced by
     * executing self with an implicit RWDBConnection object. An implicit
     * RWDBConnection object inherits the time zone setting from the
     * producer RWDBDatabase instance. Hence, the time zone setting of the
     * producer RWDBDatabase object will be used for creating the string
     * representations of any RWDateTime instances in self.
     *
     * The behavior of this method depends on the value of \a verbose, and
     * is independent of the RWDBDatabase::verboseAsString() setting.
     *
     * - If \a verbose is \c false, the SQL returned is the same as that
     * passed to the database for execution.
     * - If \a verbose is \c true, any placeholders in the returned SQL are
     * replaced with their bound values although the SQL passed to the
     * database for execution will not be affected.
     *
     * \note
     * The SQL returned by this method when \a verbose is \c true may not be
     * a valid SQL statement. However, this is not necessarily the same SQL
     * sent to the database for execution. For example, if an RWDBBlob
     * object is bound, calling this method with \a verbose as \c true will
     * result in a string with blob data returned as hex numbers, such as
     * \c 0x0A32F5.
     *
     * \sa
     * RWDBDatabase::timeZone(const RWZone*) for time zone setting on
     * RWDBDatabase.
     */
    inline RWCString asString(bool verbose) const
    {
        return RWDBSelectorBase::asString(verbose);
    }

    /**
     * Returns the SQL equivalent of:
     *
     * \code
     * (SELECT ...) <operator> (SELECT ...)
     * ORDER BY <orderby-list>
     * \endcode
     *
     * This method returns an SQL statement that would be produced by
     * executing self with \a conn. The time zone setting of \a conn will be
     * used for creating string representations of any RWDateTime instances
     * in self.
     *
     * The behavior of this method depends on the value of \a verbose, and
     * is independent of the RWDBDatabase::verboseAsString() setting.
     *
     * - If \a verbose is \c false, the SQL returned is the same as that
     * passed to the database for execution.
     * - If \a verbose is \c true, any placeholders in the returned SQL are
     * replaced with their bound values although the SQL passed to the
     * database for execution will not be affected.
     *
     * \note
     * The SQL returned by this method when \a verbose is \c true may not be
     * a valid SQL statement. However, this is not necessarily the same SQL
     * sent to the database for execution. For example, if an RWDBBlob
     * object is bound, calling this method with \a verbose as \c true will
     * result in a string with blob data returned as hex numbers, such as
     * \c 0x0A32F5.
     *
     * \sa
     * RWDBConnection::timeZone(const RWZone*) for time zone setting on
     * RWDBConnection.
     */
    inline RWCString asString(const RWDBConnection& conn,
                              bool verbose) const
    {
        return RWDBSelectorBase::asString(conn, verbose);
    }

    virtual ~RWDBCompoundSelector();

    //RWCString  asString( const RWDBPhraseBook& pb ) const;

private:
    RWDBCompoundSelector();
};


#endif
