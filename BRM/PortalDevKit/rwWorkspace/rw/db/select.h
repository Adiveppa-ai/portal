#ifndef __RWDB_SELECT_H__
#define __RWDB_SELECT_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/select.h#1 $
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
 * RWDBSelector provides an encapsulation of the SQL "SELECT" statement.
 * The result of a select is a table. This is an awkward concept to
 * represent: the "is a" relationship does not exist for the entire life
 * of the object. Nevertheless, RWDBSelector is derived from RWDBTable
 * in order to provide convenient syntax for getting results. Apps can
 * use a reader to get rows from a selector, without having to manipulate
 * an intermediate table object.
 *
 * RWDBCompoundSelector instances result from applying set operations to
 * selectors or other compound selectors.  To implement this, both
 * selector and compoundSelector are derived from a common base class,
 * RWDBSelectorBase. This is important because not all selector methods
 * can be applied to compound selectors.
 *
 **************************************************************************/

#include <rw/db/cursor.h>
#include <rw/db/dbase.h>
#include <rw/db/defs.h>
#include <rw/db/expr.h>
#include <rw/db/phrase.h>
#include <rw/db/reader.h>
#include <rw/db/result.h>
#include <rw/db/schema.h>
#include <rw/db/status.h>

class RWDBBulkReader;

/**
 * \ingroup db_data_manipulation_group
 *
 * \brief
 * Base class for selector classes RWDBSelector and RWDBCompoundSelector.
 *
 * RWDBSelectorBase is a base class from which RWDBSelector and
 * RWDBCompoundSelector are derived. It encapsulates the features common to
 * RWDBSelector and RWDBCompoundSelector.
 *
 * RWDBSelectorBase provides no useful functionality on its own.
 * Applications should treat it as though it were an abstract base class.
 *
 * \synopsis
 * #include <rw/db/select.h>
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBSelectorBase
{
public:
    enum OrderByDirection { Ascending, Descending };

    // constructors, destructor, assignment
    RWDBSelectorBase();
    RWDBSelectorBase(RWDBSelectorBaseImp* anImp);
    RWDBSelectorBase(const RWDBDatabase& dbase);
    RWDBSelectorBase(const RWDBSelectorBase& base);
    virtual ~RWDBSelectorBase();

    RWDBSelectorBase& operator= (const RWDBSelectorBase& base);

    // database operations
    RWDBResult execute();

    RWDBResult execute(const RWDBConnection& connection);

    RWDBStatus clear();

    bool  fetchSchema();

    bool  fetchSchema(const RWDBConnection& connection);

    // accessors

    RWDBDatabase      database() const;

    RWDBSchema        schema() const;

    RWDBColumn        column(size_t index) const;

    RWDBColumn        column(const RWCString& name) const;

    RWDBColumn        column(const RWCString& name,
                             RWCString::caseCompare caseCompare) const;

    RWDBColumn        operator[](const RWCString& name) const;

    RWDBColumn        operator[](size_t           position) const;

    // mutators
    RWDBSelectorBase& orderBy(const RWDBColumn& column);
    RWDBSelectorBase& orderBy(int columnNumber);
    RWDBSelectorBase& orderBy(const RWDBExpr& expr);
    RWDBSelectorBase& orderByDescending(const RWDBColumn& column);
    RWDBSelectorBase& orderByDescending(int columnNumber);
    RWDBSelectorBase& orderByDescending(const RWDBExpr& expr);
    RWDBSelectorBase& orderByClear();

    // error handling

    void                     setErrorHandler(RWDBStatus::ErrorHandler handler);

    RWDBStatus::ErrorHandler errorHandler() const;

    bool                isValid() const;

    bool                isReady() const;

    RWDBStatus               status() const;

    // producers

    RWDBCursor   cursor(RWDBCursor::CursorType type = RWDBCursor::Sequential,
                        RWDBCursor::CursorAccess access =
                            RWDBCursor::Read) const;

    RWDBCursor   cursor(const RWDBConnection& connection,
                        RWDBCursor::CursorType type = RWDBCursor::Sequential,
                        RWDBCursor::CursorAccess access =
                            RWDBCursor::Read) const;

    RWDBCursor   cursor(const RWDBSchema& updateCols,
                        RWDBCursor::CursorType type = RWDBCursor::Sequential,
                        RWDBCursor::CursorAccess access =
                            RWDBCursor::Read) const;

    RWDBCursor   cursor(const RWDBSchema& updateCols,
                        const RWDBConnection& connection,
                        RWDBCursor::CursorType type = RWDBCursor::Sequential,
                        RWDBCursor::CursorAccess access =
                            RWDBCursor::Read) const;

    RWDBReader   reader(size_t cacheSize = 0) const;

    RWDBReader   reader(const RWDBConnection& connection, size_t cacheSize = 0) const;

    RWDBBulkReader   bulkReader(const RWDBConnection& conn) const;

    // set operations

    virtual RWDBCompoundSelector union_
    (const RWDBSelectorBase& base) const;

    virtual RWDBCompoundSelector unionAll
    (const RWDBSelectorBase& base) const;

    virtual RWDBCompoundSelector intersection
    (const RWDBSelectorBase& base) const;

    virtual RWDBCompoundSelector difference
    (const RWDBSelectorBase& base) const;

    // format self as SQL string
    inline RWCString asString() const
    {
        return rwAsString(database().timeZone(),
                          database().verboseAsString());
    }

    inline RWCString asString(const RWDBConnection& conn) const
    {
        return rwAsString(conn.timeZone(),
                          database().verboseAsString());
    }

    inline RWCString asString(bool verbose) const
    {
        return rwAsString(database().timeZone(), verbose);
    }

    inline RWCString asString(const RWDBConnection& conn,
                              bool verbose) const
    {
        return rwAsString(conn.timeZone(), verbose);
    }

    // Needs to be made virtual if derived in RWDBSelector
    // or RWDBCompoundSelector.
    RWCString rwAsString(const RWZone& timeZone,
                         bool verbose = false) const;

    // utilities
    bool isEquivalent(const RWDBSelectorBase& sel) const;

protected:

    RWDBCountedRef<RWDBSelectorBaseImp> impl_;

private:
    virtual RWDBCompoundSelector compoundSelector
    (RWDBPhraseBook::RWDBPhraseKey,
     const RWDBSelectorBase&) const;

    friend RWDBSelectorBaseImp* getImp(const RWDBSelectorBase& selector)
    {
        return selector.impl_;
    }
};

// set operators
/**
 * \relates RWDBSelector
 * Union. Equivalent to
 *
 * \code
 * left.union_(right);
 * \endcode
 */
RWDBCompoundSelector RWDB_SYMBOLIC operator+ (const RWDBSelectorBase& left,
        const RWDBSelectorBase& right);

/**
 * \relates RWDBSelector
 * Difference. Equivalent to
 *
 * \code
 * left.difference(right);
 * \endcode
 */
RWDBCompoundSelector RWDB_SYMBOLIC operator- (const RWDBSelectorBase& left,
        const RWDBSelectorBase& right);

/**
 * \relates RWDBSelector
 * Intersection. Equivalent to
 *
 * \code
 * left.intersection(right);
 * \endcode
 */
RWDBCompoundSelector RWDB_SYMBOLIC operator* (const RWDBSelectorBase& left,
        const RWDBSelectorBase& right);


class RWDBCompoundSelector;

/**
 * \ingroup db_data_manipulation_group
 * \class RWDBSelector
 *
 * \brief
 * Encapsulates the SQL \c SELECT statement.
 *
 * RWDBSelector is an encapsulation of an SQL \c SELECT statement. Its
 * methods provide an application with explicit control over the \c SELECT
 * statement's select list, as well as its \c FROM, \c WHERE,
 * <tt>ORDER BY</tt>, and <tt>GROUP BY</tt> clauses. The set operators \c +,
 * \c *, and \c - (union, intersection, and difference) may be applied to
 * RWDBSelector objects in order to achieve the semantics of the SQL
 * \c UNION, \c INTERSECTION, and \c DIFFERENCE operations. See the entry
 * for RWDBCompoundSelector. An RWDBSelector may be used to instantiate an
 * RWDBExpr, so subqueries are also supported. See the entry for RWDBExpr.
 *
 * The insertion operator operator<<() is used to add items to an
 * RWDBSelector select list; the where() method is used to specify a
 * \c WHERE clause. The items which are inserted into an RWDBSelector are
 * RWDBExpr objects, which may be any combination of constants, column
 * references, predefined functions, or RWDBSelector objects combined by
 * arithmetic or functional operators. The \c WHERE clause is encapsulated
 * by an RWDBCriterion, which is some number of RWDBExpr objects combined
 * with logical operators.
 *
 * The result of an SQL \c SELECT statement execution is an SQL table
 * expression. The DB Interface Module represents this concept as a
 * \c ResultTable. Hence, the following are equivalent:
 *
 * \code
 * (1)  RWDBReader  rdr  =  selector.execute().table().reader();
 * (2)  RWDBReader  rdr  =  selector.reader();
 * \endcode
 *
 * RWDBSelector also derives from RWDBSelectorBase so that RWDBSelector and
 * RWDBCompoundSelector may be handled in a uniform manner.
 *
 * RWDBSelector is designed around the Interface/Implementation paradigm. An
 * RWDBSelector instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation. An RWDBSelector
 * implementation is a base class from which a family of database-specific
 * selector implementations is derived.
 *
 * Most RWDBSelector methods return a reference to self. This allows calls
 * to be stacked, as in:
 *
 * \code
 * select.where(...).orderBy(...).groupBy(...), etc.
 * \endcode
 *
 * \synopsis
 * #include <rw/db/select.h>
 *
 * RWDBSelector select = myDbase.selector();
 * \endsynopsis
 *
 * \example
 * <b>Example1</b>
 *
 * Assuming that dBase is a valid RWDBDatabase, we can encapsulate the SQL
 * statement:
 *
 * \code
 * SELECT myTable.name, yourTable.city FROM myTable,
 * yourTable WHERE myTable.key = yourTable.key
 * \endcode
 *
 * as follows:
 *
 * \code
 * RWDBTable myTable = dBase.table("myTable");
 * RWDBTable yourTable = dBase.table("yourTable");
 * RWDBSelector select = dBase.selector();
 * select << myTable["name"] << yourTable["city"];
 * select.where(myTable["key"] == yourTable["key"]);
 * \endcode
 *
 * Notice that it is not necessary to specify the \c FROM clause. The DB
 * Interface Module deduces what tables to select from the column references
 * in the select list; it generates a member of the \c FROM clause for each
 * unique table reference. You can override this behavior by using the
 * from(), fromGeneration(), and fromExtern() member functions.
 *
 * Assuming that the \c name and \c city columns mentioned above are
 * strings, we would read the results of our query like this:
 *
 * \code
 * RWDBReader rdr = select.reader();
 * RWCString name;
 * RWCString city;
 * while(rdr()) {
 *     rdr >> name >> city;
 *     // process the name and city
 * }
 * \endcode
 *
 * <b>Example 2</b>
 *
 * To introduce multiple instances of a table into an encapsulated \c SELECT
 * statement, declare additional RWDBTable instances. The fragment:
 *
 * \code
 * SELECT a.name, b.type from myTable a, myTable b
 * \endcode
 *
 * can be captured as in the following example:
 *
 * \code
 * RWDBTable aTable = myDbase.table("myTable");
 * RWDBTable bTable = myDbase.table("myTable");
 * RWDBSelector select = myDbase.selector();
 * select << aTable["name"] << bTable["type"];
 * \endcode
 *
 * Note that the instantiations of \c aTable and \c bTable do not require
 * database access, so this technique does not incur excessive overhead.
 *
 * <b>Example 3</b>
 *
 * This example introduces the binding of application variables within a
 * \c WHERE clause of a \c SELECT statement. This allows an application to
 * repeatedly execute the RWDBSelector without clearing and constructing the
 * \c WHERE clause each time. The following example uses an \c AutoParts
 * table in the database, with text column \c name and integer column \c id:
 *
 * \code
 * RWDBTable partsTable = myDbase.table("AllParts");
 * RWDBConnection connection = myDbase.connection();
 * RWDBSelector select = myDbase.selector();
 * int id = 1001;
 * select << partsTable["name"];
 * select.where( partsTable["id"] == RWDBBoundExpr(&id) );
 * RWDBReader reader = select.reader(connection);
 * // process reader...
 * id = 2001;
 * reader = select.reader(connection);
 * // process reader...
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBSelector : public RWDBSelectorBase
{
public:

    /**
     * A class-scoped \c enum presents different behaviors that can be used
     * to compose the \c FROM clause. It is used in the fromGeneration()
     * methods. Please refer to the Section "Composing FROM clause" in the
     * Chapter "The Data Manipulation Classes" in the <em>DB Interface
     * Module User's Guide</em>, for detailed information.
     */
    enum FromGeneration {

        /**
         * If there are any explicit from() entries, uses only those to
         * generate the \c FROM clause, otherwise uses only implicit
         * entries.
         */
        ExplicitOrImplicit,

        /**
         * Combines the implicit and explicit entries to generate the
         * \c FROM clause, removing duplicate entries.
         */
        ExplicitAndImplicit
    };

    // constructors, destructor, assignment

    /**
     * The default constructor creates an RWDBSelector whose status is
     * RWDBStatus::notInitialized. This constructor is provided as a
     * convenience, for example, for declaring an array of RWDBSelector
     * objects. Usable RWDBSelector instances are obtained from
     * RWDBDatabase.
     */
    RWDBSelector();

    /**
     * Copy constructor. The created object shares an implementation with
     * \a select.
     */
    RWDBSelector(const RWDBSelector& select);

    RWDBSelector(RWDBSelectorImp* imp);

    /**
     * Assignment operator. Self shares an implementation with \a select.
     * Returns a reference to self.
     */
    RWDBSelector& operator= (const RWDBSelector& select);

    virtual ~RWDBSelector();

    // inherited from RWDBSelectorBase
    //virtual RWCString  asString () const;

    /**
     * Returns a copy of self's RWDBCriterion, an encapsulated SQL \c WHERE
     * clause. Returns an empty RWDBCriterion if self has no \c WHERE
     * clause.
     */
    RWDBCriterion where() const;

    /**
     * The insertion operator adds \a manip to self's select list. Returns a
     * reference to self.
     */
    RWDBSelector& operator<< (RWDBValueManip manip);

    /**
     * The insertion operator adds an item to self's select list. The
     * supplied \a expr may be made up of constants, column references,
     * predefined functions, or RWDBSelector instances, combined with
     * arithmetic or functional operators. See RWDBExpr. Returns a reference
     * to self.
     */
    RWDBSelector& operator<< (const RWDBExpr& expr);

    /**
     * Use this method to specify \c SELECT \c * \c FROM \a table. Returns a
     * reference to self.
     */
    RWDBSelector& operator<< (const RWDBTable& table);

    /**
     * This is a synonym for \c *this \c << \a expr. Returns a reference to
     * self.
     */
    RWDBSelector& select(const RWDBExpr& expr);

    /**
     * This is a synonym for \c *this \c << \a table. Returns a reference to
     * self.
     */
    RWDBSelector& select(const RWDBTable& table);

    // undo projection

    /**
     * Clears self's select list. Returns a reference to self.
     */
    RWDBSelector& selectClear();

    /**
     * Specifies \a criterion as self's SQL \c WHERE clause. If self already
     * has a \c WHERE clause, this method replaces it. Returns a reference
     * to self.
     */
    RWDBSelector& where(const RWDBCriterion& criterion);

    // assorted SQL concepts

    /**
     * Specifies the \c INTO clause of a select statement. If self already
     * has an \c INTO clause, this method replaces it. A blank \a tableName
     * removes the clause from self. If self's database does not support
     * <tt>SELECT INTO</tt>, the DB Interface Module does not attempt to
     * emulate this functionality. In such cases this method sets self's
     * status to RWDBStatus::notSupported. Returns a reference to self.
     */
    RWDBSelector& into(const RWCString& tableName);

    /**
     * Specifies \a column as an <tt>ORDER BY</tt> column for self. A select
     * statement may have multiple <tt>ORDER BY</tt> columns; successive
     * calls to orderBy() and orderByDescending() add <tt>ORDER BY</tt>
     * columns to self. The order of orderBy() and orderByDescending() calls
     * is retained. Returns a reference to self.
     */
    RWDBSelector& orderBy(const RWDBColumn& column);

    /**
     * Specifies \a expr as an <tt>ORDER BY \<expression\></tt> for self. A
     * select statement may have multiple <tt>ORDER BY</tt> expressions;
     * successive calls to orderBy() and orderByDescending() add
     * <tt>ORDER BY</tt> expressions to self. The order of orderBy() and
     * orderByDescending() calls is retained. Returns a reference to self.
     */
    RWDBSelector& orderBy(const RWDBExpr& expr);

    /**
     * Specifies \a columnNumber as an <tt>ORDER BY</tt> column for self. A
     * select statement may have multiple <tt>ORDER BY</tt> columns;
     * successive calls to orderBy() and orderByDescending() add
     * <tt>ORDER BY</tt> columns to self. The order of orderBy() and
     * orderByDescending() calls is retained. Returns a reference to self.
     */
    RWDBSelector& orderBy(int columnNumber);

    /**
     * Specifies \a column as an <tt>ORDER BY DESCENDING</tt> column for
     * self. A select statement may have multiple <tt>ORDER BY</tt> columns;
     * successive calls to orderBy() and orderByDescending() add
     * <tt>ORDER BY</tt> columns to self. The order of orderBy() and
     * orderByDescending() calls is retained. Returns a reference to self.
     */
    RWDBSelector& orderByDescending(const RWDBColumn& column);

    RWDBSelector& orderByDescending(const RWDBExpr& expr);

    /**
     * Specifies \a columnNumber as an <tt>ORDER BY DESCENDING</tt> column
     * for self. A select statement may have multiple <tt>ORDER BY</tt>
     * columns; successive calls to orderBy() and orderByDescending() add
     * <tt>ORDER BY</tt> columns to self. The order of orderBy() and
     * orderByDescending() calls is retained. Returns a reference to self.
     */
    RWDBSelector& orderByDescending(int columnNumber);

    /**
     * Clears self's <tt>ORDER BY</tt> clause. Returns a reference to self.
     */
    RWDBSelector& orderByClear();

    /**
     * Specifies \a criterion as self's \c HAVING clause. If self already
     * has a \c HAVING clause, this method replaces it. This method is most
     * often used in conjunction with groupBy(). Returns a reference to
     * self.
     */
    RWDBSelector& having(const RWDBCriterion& criterion);

    /**
     * Specifies \a column as a \c GROUP \c BY column for self. A select
     * statement may have multiple \c GROUP \c BY columns; successive calls
     * to groupBy() add \c GROUP \c BY columns to self. The order of
     * groupBy() calls is retained. Returns a reference to self.
     */
    RWDBSelector& groupBy(const RWDBColumn& column);

    /**
     * Specifies \a expr as a \c GROUP \c BY \c \<expression\> for self. A
     * select statement may have multiple \c GROUP \c BY expressions;
     * successive calls to groupBy() add \c GROUP \c BY expressions to self.
     * The order of groupBy() calls is retained. Returns a reference to
     * self.
     */
    RWDBSelector& groupBy(const RWDBExpr& expr);

    /**
     * Specifies \a columnNumber as a \c GROUP \c BY column for self. A
     * select statement may have multiple \c GROUP \c BY columns; successive
     * calls to groupBy() add \c GROUP \c BY columns to self. The order of
     * groupBy() calls is retained. Returns a reference to self.
     */
    RWDBSelector& groupBy(int columnNumber);

    /**
     * Clears self's \c GROUP \c BY clause. Returns a reference to self.
     */
    RWDBSelector& groupByClear();

    /**
     * By default, adds the \c DISTINCT SQL keyword to the select statement
     * encapsulated by self. If \a logic is specified as \c false, removes
     * the \c DISTINCT keyword if it is present. Returns a reference to
     * self.
     */
    RWDBSelector& distinct(bool logic = true);

    // the "from" clause is usually implicit. use these to
    // manipulate it directly or when using outer joins

    /**
     * Adds \a tableName to self's explicit \c FROM list. Normally,
     * RWDBSelector has no explicit \c FROM clause. It can deduce which
     * tables to query from the column references in its select list. By
     * using the from() method, you can manipulate default \c FROM clause
     * generation and cause an explicit \c FROM list to be maintained. Each
     * call to from() adds an entry to the explicit \c FROM list. The
     * explicit \c FROM list can be used by itself or combined with the
     * default implicit list, depending on the fromGeneration() setting.
     * This is explained in detail in the Section "Composing FROM clause" in
     * the Chapter "The Data Manipulation Classes" in the <em>DB Interface
     * Module User's Guide</em>. Returns a reference to self.
     */
    RWDBSelector& from(const RWCString& tableName);

    /**
     * Adds name of \a table to self's explicit \c FROM list. Normally,
     * RWDBSelector has no explicit \c FROM clause. It can deduce which
     * tables to query from the column references in its select list. By
     * using the from() method, you can manipulate default \c FROM clause
     * generation and cause an explicit \c FROM list to be maintained. Each
     * call to from() adds an entry to the explicit \c FROM list. The
     * explicit \c FROM list can be used by itself or combined with the
     * default implicit list, depending on the fromGeneration() setting.
     * This is explained in detail in the Section "Composing FROM clause" in
     * the Chapter "The Data Manipulation Classes" in the <em>DB Interface
     * Module User's Guide</em>. Returns a reference to self.
     */
    RWDBSelector& from(const RWDBTable& table);

    /**
     * Adds \a jExpr to self's explicit \c FROM list. This method is used
     * for adding outer join constructs to the \c FROM clause. Each call to
     * from() adds an entry to the explicit \c FROM list. See the Section on
     * "Outer Joins" in the Chapter "The Data Manipulation Classes" in the
     * <em>DB Interface Module User's Guide</em> and the RWDBJoinExpr entry
     * in this Reference Guide for information on generating appropriate
     * outer join constructs. The \c FROM clause generation is explained in
     * detail in the Section "Composing FROM clause" in the Chapter "The
     * Data Manipulation Classes" in the <em>DB Interface Module User's
     * Guide</em>. Returns a reference to self.
     */
    RWDBSelector& from(const RWDBJoinExpr& jExpr);


    /**
     * Clears self's explicit \c FROM list. See from() for an explanation of
     * implicit and explicit \c FROM clauses. This is also explained in
     * detail in the Section "Composing FROM clause" in the Chapter "The
     * Data Manipulation Classes" in the <em>DB Interface Module User's
     * Guide</em>. Returns a reference to self.
     */
    RWDBSelector& fromClear();

    // Gets and sets the from clause generation mechanism.

    /**
     * Sets self's \c FROM clause generation behavior. Class-scoped enum
     * #FromGeneration defines the behavior in generating self's \c FROM
     * clause from the implicit and explicit \c FROM entries. The default
     * behavior is #ExplicitOrImplicit. The \c FROM clause generation is
     * explained in detail in the Section "Composing FROM clause" in the
     * Chapter "The Data Manipulation Classes" in the <em>DB Interface
     * Module User's Guide</em>. Returns a reference to self.
     */
    RWDBSelector& fromGeneration(FromGeneration flag);

    /**
     * Returns self's \c FROM clause generation behavior. Class-scoped enum
     * #FromGeneration defines the behaviors in which to generate self's
     * \c FROM clause from the implicit and explicit \c FROM entries. The
     * default behavior is #ExplicitOrImplicit. The \c FROM clause
     * generation is explained in detail in the Section "Composing FROM
     * clause" in the Chapter "The Data Manipulation Classes" in the <em>DB
     * Interface Module User's Guide</em>.
     */
    FromGeneration fromGeneration() const;

    // Defines certain tables to be external to this query.
    // These tables are not included in the FROM clause.

    /**
     * Declares \a table as an externally defined table and hence to not be
     * included in the self's \c FROM clause. Each call to fromExtern() adds
     * an entry to self's extern table list. This method is especially
     * useful in forming correlated SQLs in which the correlated subquery
     * references a table defined in the outer SQL. The \c FROM clause
     * generation and correlated subqueries are explained in detail in the
     * Section "Composing FROM clause" and the Section "Subqueries" in the
     * Chapter "The Data Manipulation Classes" in the <em>DB Interface
     * Module User's Guide</em>. Returns a reference to self.
     */
    RWDBSelector& fromExtern(const RWDBTable& table);

    /**
     * Clears self's extern table list. See fromExtern() for an explanation
     * of the extern table list. The \c FROM clause generation is explained
     * in detail in the Section "Composing FROM clause" in the Chapter "The
     * Data Manipulation Classes" in the <em>DB Interface Module User's
     * Guide</em>. Returns a reference to self.
     */
    RWDBSelector& fromExternClear();

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 1, use RWDBJoinExpr::on(const RWDBCriterion&) to
     * attach a join condition to a specific RWDBJoinExpr.
     *
     * Attaches the \a criterion as an SQL \c ON clause to the first
     * RWDBJoinExpr attached to self using the
     * \ref from(const RWDBJoinExpr&) "from()" method. If the first
     * RWDBJoinExpr already has an \c ON clause, this method replaces it.
     * Returns a reference to self.
     */
    RW_DEPRECATE_FUNC("Use RWDBJoinExpr::on(const RWDBCriterion&) instead")
    RWDBSelector& on(const RWDBCriterion& criterion);
#endif

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 1, use RWDBJoinExpr::on(const RWDBColumn&) to add a
     * column to the SQL \c USING clause of a specific RWDBJoinExpr.
     *
     * Adds the \a column to the SQL \c USING clause of the first
     * RWDBJoinExpr attached to self using the
     * \ref from(const RWDBJoinExpr&) "from()" method. Returns a reference
     * to self.
     */
    RW_DEPRECATE_FUNC("Use RWDBJoinExpr::on(const RWDBColumn&) instead")
    RWDBSelector& on(const RWDBColumn& column);
#endif

    /**
     * Uses a default database connection to submit the SQL \c SELECT
     * statement encapsulated by self for execution. There will always be
     * one or more RWDBTable objects in the returned RWDBResult.
     */
    inline RWDBResult execute()
    {
        return RWDBSelectorBase::execute();
    }

    /**
     * Uses the supplied \a connection to submit the SQL \c SELECT statement
     * encapsulated by self for execution. There will always be one or more
     * RWDBTable objects in the returned RWDBResult. This function can
     * behave asynchronously if executed using an asynchronous connection.
     */
    inline RWDBResult execute(const RWDBConnection& connection)
    {
        return RWDBSelectorBase::execute(connection);
    }

    /**
     * Clears self's clauses, selection lists, and internal controls.
     */
    inline RWDBStatus clear()
    {
        return RWDBSelectorBase::clear();
    }

    /**
     * Executes the SQL statement associated with self, then populates
     * self's internal schema with the result set, that is, the columns in
     * the table that resulted from the execution of the SQL statement. This
     * function returns \c true if successful.
     *
     * To obtain schema information, the DB Interface Module uses a default
     * database connection to query the database. If no schema can be
     * obtained, this function returns \c false.
     */
    inline bool  fetchSchema()
    {
        return RWDBSelectorBase::fetchSchema();
    }

    /**
     * Executes the SQL statement associated with self, then populates
     * self's internal schema with the result set, that is, the columns in
     * the table that resulted from the execution of the SQL statement. This
     * function returns \c true if successful.
     *
     * To obtain schema information, the DB Interface Module uses the
     * supplied \a connection to query the database. If no schema can be
     * obtained, this function returns \c false.
     */
    inline bool  fetchSchema(const RWDBConnection& connection)
    {
        return RWDBSelectorBase::fetchSchema(connection);
    }

    // accessors

    /**
     * Returns the RWDBDatabase that produced this selector. If there is no
     * such object, for example, if this selector was created using the
     * default constructor, returns an RWDBDatabase with a status of
     * RWDBStatus::notInitialized.
     */
    inline RWDBDatabase      database() const
    {
        return RWDBSelectorBase::database();
    }

    /**
     * Returns a deep copy of self's RWDBSchema. The copy is made so that an
     * application can modify the returned RWDBSchema without modifying
     * self's schema. The schema is empty until self's fetchSchema() method
     * is called.
     */
    inline RWDBSchema        schema() const
    {
        return RWDBSelectorBase::schema();
    }

    /**
     * Returns a deep copy of the RWDBColumn in self's schema at the given
     * \a index. If \a index is out of range, returns an RWDBColumn with
     * status RWDBStatus::invalidPosition. A deep copy is made so that
     * applications can modify the returned RWDBColumn without modifying
     * self's schema.
     */
    inline RWDBColumn        column(size_t index) const
    {
        return RWDBSelectorBase::column(index);
    }

    /**
     * Returns a deep copy of the first RWDBColumn in self's schema whose
     * name matches the given \a name. If no matching column is found,
     * returns an RWDBColumn whose status is RWDBStatus::columnNotFound. A
     * deep copy is made so that applications can modify the returned
     * RWDBColumn without modifying self's schema.
     */
    inline RWDBColumn        column(const RWCString& name) const
    {
        return RWDBSelectorBase::column(name);
    }

    /**
     * Returns a deep copy of the first RWDBColumn in self's schema whose
     * name matches the given \a name. If no matching column is found,
     * returns an RWDBColumn whose status is RWDBStatus::columnNotFound. A
     * deep copy is made so that applications can modify the returned
     * RWDBColumn without modifying self's schema. The \a caseCompare
     * argument toggles case sensitivity when comparing column names. Valid
     * arguments are RWCString::exact and RWCString::ignoreCase.
     */
    inline RWDBColumn        column(const RWCString& name,
                                    RWCString::caseCompare caseCompare) const
    {
        return RWDBSelectorBase::column(name, caseCompare);
    }

    /**
     * Returns a deep copy of the first RWDBColumn in self's schema whose
     * name matches the given \a name. If no matching column is found,
     * returns an RWDBColumn whose status is RWDBStatus::columnNotFound. A
     * deep copy is made so that applications can modify the returned
     * RWDBColumn without modifying self's schema.
     */
    inline RWDBColumn        operator[](const RWCString& name) const
    {
        return RWDBSelectorBase::operator[](name);
    }

    /**
     * Returns a deep copy of the RWDBColumn in self's schema whose position
     * matches the given \a position. If no matching column is found,
     * returns an RWDBColumn whose status is RWDBStatus::columnNotFound. A
     * deep copy is made so that the application can modify the returned
     * RWDBColumn without modifying self's schema.
     */
    inline RWDBColumn        operator[](size_t           position) const
    {
        return RWDBSelectorBase::operator[](position);
    }

    /**
     * Installs \a handler as self's error handler. The supplied \a handler
     * is inherited by all objects produced by self. By default, an
     * RWDBStatus::ErrorHandler is inherited from the object that produced
     * self; this method overrides the default.
     */
    inline void                     setErrorHandler(RWDBStatus::ErrorHandler handler)
    {
        return RWDBSelectorBase::setErrorHandler(handler);
    }

    /**
     * Returns \c true if self's status is RWDBStatus::ok, otherwise returns
     * \c false. Does not return \c false if the previous executed statement
     * failed. You must check the status of the RWDBResult returned from
     * execute() instead of the status of the RWDBSelector object.
     */
    inline bool                isValid() const
    {
        return RWDBSelectorBase::isValid();
    }

    /**
     * Returns the status of self.
     */
    inline RWDBStatus               status() const
    {
        return RWDBSelectorBase::status();
    }

    // producers

    /**
     * Produces an RWDBCursor for execution of the SQL select statement
     * encapsulated by self. The cursor is created on a default database
     * connection, using the \a type and \a access specifications provided.
     * The connection is held by the RWDBCursor until the RWDBCursor is
     * destroyed.
     */
    inline RWDBCursor   cursor(RWDBCursor::CursorType type = RWDBCursor::Sequential,
                               RWDBCursor::CursorAccess access =
                                   RWDBCursor::Read) const
    {
        return RWDBSelectorBase::cursor(type, access);
    }

    /**
     * Produces an RWDBCursor for execution of the SQL statement
     * encapsulated by self. The cursor is created on the supplied database
     * \a connection, using the \a type and \a access specifications
     * provided. The connection is held by the RWDBCursor until the
     * RWDBCursor is destroyed. This function can behave asynchronously if
     * executed using an asynchronous connection.
     */
    inline RWDBCursor   cursor(const RWDBConnection& connection,
                               RWDBCursor::CursorType type = RWDBCursor::Sequential,
                               RWDBCursor::CursorAccess access =
                                   RWDBCursor::Read) const
    {
        return RWDBSelectorBase::cursor(connection, type, access);
    }

    /**
     * Produces an RWDBCursor for execution of the SQL select statement
     * encapsulated by self. The argument \a updateCols is used in building
     * a clause:
     *
     * <tt>FOR UPDATE OF column-name, column-name, ...</tt>
     *
     * Some SQL dialects require this form. The cursor is created on a
     * default database connection, using the \a type and \a access
     * specifications provided. The connection is held by the RWDBCursor
     * until the RWDBCursor is destroyed.
     */
    inline RWDBCursor   cursor(const RWDBSchema& updateCols,
                               RWDBCursor::CursorType type = RWDBCursor::Sequential,
                               RWDBCursor::CursorAccess access =
                                   RWDBCursor::Read) const
    {
        return RWDBSelectorBase::cursor(updateCols, type, access);
    }

    /**
     * Produces an RWDBCursor for execution of the SQL statement
     * encapsulated by self. The cursor is created on the supplied database
     * \a connection, using the \a type and \a access specifications
     * provided. The connection is held by the RWDBCursor until the
     * RWDBCursor is destroyed. The argument \a updateCols is used in
     * building a clause:
     *
     * <tt>FOR UPDATE OF column-name, column-name, ...</tt>
     *
     * Some SQL dialects require this form. This function can behave
     * asynchronously if executed using an asynchronous connection.
     */
    inline RWDBCursor   cursor(const RWDBSchema& updateCols,
                               const RWDBConnection& connection,
                               RWDBCursor::CursorType type = RWDBCursor::Sequential,
                               RWDBCursor::CursorAccess access =
                                   RWDBCursor::Read) const
    {
        return RWDBSelectorBase::cursor(updateCols, connection, type, access);
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
     * Returns an RWDBBulkReader able to read the result set associated with
     * the rows of self. The RWDBBulkReader executes using the supplied
     * connection.
     */
    inline RWDBBulkReader   bulkReader(const RWDBConnection& conn) const
    {
        return RWDBSelectorBase::bulkReader(conn);
    }

    /**
     * Returns the SQL equivalent of:
     *
     * \code
     * SELECT <column-list> FROM <from-list>
     * WHERE <where-clause> GROUP BY <groupby-list>
     * HAVING <having-clause> ORDER BY <orderby-list>
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
     * RWDBDatabase::verboseAsString() set to \c true will result in a
     * string with blob data returned as hex numbers, such as \c 0x0A32F5.
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
     * SELECT <column-list> FROM <from-list>
     * WHERE <where-clause> GROUP BY <groupby-list>
     * HAVING <having-clause> ORDER BY <orderby-list>
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
     * SELECT <column-list> FROM <from-list>
     * WHERE <where-clause> GROUP BY <groupby-list>
     * HAVING <having-clause> ORDER BY <orderby-list>
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
     * SELECT <column-list> FROM <from-list>
     * WHERE <where-clause> GROUP BY <groupby-list>
     * HAVING <having-clause> ORDER BY <orderby-list>
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

    /**
     * Returns an RWDBCompoundSelector that represents the SQL selector:
     *
     * \e select-stmt \c UNION \a selector
     *
     * where \e select-stmt is the \c SELECT statement represented by self.
     * The trailing underscore is to avoid conflict with the C++ \c union
     * keyword.
     */
    virtual RWDBCompoundSelector union_
    (const RWDBSelectorBase& selector) const;

    /**
     * Returns an RWDBCompoundSelector which represents the SQL selector:
     *
     * \e select-stmt <tt>UNION ALL</tt> \a selector
     *
     * where \e select-stmt is the \c SELECT statement represented by self.
     */
    virtual RWDBCompoundSelector unionAll
    (const RWDBSelectorBase& selector) const;

    /**
     * Returns an RWDBCompoundSelector that represents the SQL selector:
     *
     * \e select-stmt \c INTERSECTION \a selector
     *
     * where \e select-stmt is the \c SELECT statement represented by self.
     */
    virtual RWDBCompoundSelector intersection
    (const RWDBSelectorBase& selector) const;

    /**
     * Returns an RWDBCompoundSelector that represents the SQL selector:
     *
     * \e select-stmt \c DIFFERENCE \a selector
     *
     * where \e select-stmt is the \c SELECT statement represented by self.
     */
    virtual RWDBCompoundSelector difference
    (const RWDBSelectorBase& selector) const;

};

#endif
