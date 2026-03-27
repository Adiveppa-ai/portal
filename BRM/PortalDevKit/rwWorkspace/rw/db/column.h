#ifndef __RWDB_COLUMN_H__
#define __RWDB_COLUMN_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/column.h#1 $
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

#include <rw/db/defs.h>
#include <rw/db/status.h>
#include <rw/db/value.h>
#include <rw/tools/bustring.h>


/**
 * \ingroup db_common_group
 * \class RWDBColumn
 *
 * \brief
 * Represents a column within a table or schema, or a particular parameter
 * of a stored procedure.
 *
 * RWDBColumn provides a way to refer to a particular column of a table or
 * schema, or to a particular parameter of a stored procedure. An
 * application obtains instances of RWDBColumn by indexing into an RWDBTable
 * or RWDBSchema.
 *
 * RWDBColumn instances may be used in expressions (see RWDBExpr), which in
 * turn are used to build up encapsulated SQL objects such as RWDBSelector.
 *
 * RWDBColumn instances are also used in RWDBSchema. An RWDBSchema is a
 * collection of RWDBColumn objects used to describe a database table, view,
 * or stored procedure. When used in this way, RWDBColumn stores several
 * pieces of information:
 *
 * - \b Name --- the name of the column
 *
 * - \b Type --- the type used to represent the data in the DB Interface
 * Module
 *
 * - <b>Native Type</b> --- the type specified by the database vendor
 *
 * - <b>Storage Length</b> --- used mainly to store the length of string
 * fields.
 *
 * - \b Precision --- the precision as defined by the database vendor
 *
 * - \b Scale --- the scale as defined by the database vendor
 *
 * - <b>Null Allowed</b> --- indicates if this column allows \c NULL values
 *
 * - <b>Parameter Type</b> --- used in stored procedures to indicate if the
 * parameter is for input, output, or both
 *
 * - \b Table --- the table associated with the column
 *
 * - <b>Identity Constraint</b> --- the identity constraint attributes if
 * the column is an identity column
 *
 * \note
 * The DB Interface Module does not obtain schema information until it is
 * required. See RWDBTable::fetchSchema.
 *
 * If no schema information has been obtained for the table containing a
 * column, the column will contain default values. For <b>Native Type</b>,
 * <b>Storage Length</b>, \b Precision, and \b Scale, this default value is
 * #RWDB_NO_TRAIT, and may be used in conditional expressions as follows:
 *
 * \code
 *  RWDBTable  myTable  =  myDbase.table("myTable");
 *  ...
 *  ...
 *  RWDBColumn  myColumn  =  myTable["someColumn"];
 *  if(  myColumn.scale()  ==  RWDB_NO_TRAIT  ) {
 *      //  do  something;
 *  }
 * \endcode
 *
 * RWDBColumn is designed around the Interface/Implementation paradigm. An
 * RWDBColumn instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation. Unlike many classes in
 * the DB Interface Module, RWDBColumn implementations do not require
 * database-specific variants.
 *
 * <h4>About Precision and Scale</h4>
 * \e Precision and \e scale are used when defining numeric data types. Each
 * database applies these specifications to data types in a slightly
 * different manner. For example, Sybase applies precision and scale to
 * decimal \e and numeric data types, while Oracle applies precision and
 * scale to numeric data types only.
 *
 * The \e precision of a column defines the total precision of the data
 * type. For decimal data types, this translates into the total number of
 * base ten digits. For floating point data types, this translates into
 * binary digits or size.
 *
 * The \e scale of a column defines the precision of the \e fractional part
 * of the data type. For decimal data types, this translates into the total
 * number of digits following the decimal point.
 *
 * Note that precision and scale are often optional for a data type and that
 * many databases apply default sizes when precision and scale are not
 * provided.
 *
 * For applications written with the DB Interface Module, precision and
 * scale should always be specified if an application will create columns of
 * a certain precision and scale. A DB Access Module can either disregard or
 * use the necessary information in order to create a column of the correct
 * data type. Typically, precision and scale should always be given for
 * decimal columns.
 *
 * \synopsis
 * #include <rw/db/column.h>
 *
 * RWDBColumn c = myTable["columnName"];
 * \endsynopsis
 *
 * \sa
 * \parblock
 * RWDBColumn is commonly used to construct encapsulated SQL expressions
 * that can in turn become part of encapsulated SQL statements like
 * RWDBSelector, RWDBInserter, RWDBDeleter, and RWDBUpdater. For example, to
 * create an encapsulation of the SQL statement:
 *
 * <tt>UPDATE myTable SET myColumn = 10 WHERE myKey < 100</tt>
 *
 * we would write:
 *
 * \code
 *  RWDBTable myTable = myDbase.table("myTable");
 *  RWDBUpdater upd = myTable.updater();
 *  upd << myTable["myColumn"].assign(10);
 *  upd.where(myTable["myKey"] < 100);
 * \endcode
 *
 * Note that the index expressions <tt>myTable["myColumn"]</tt> and
 * <tt>myTable["myKey"]</tt> result in the construction of RWDBColumn
 * instances that are then used to construct instances of an RWDBAssignment
 * and RWDBExpr, respectively.
 *
 * For additional details, see RWDBExpr, RWDBAssignment, RWDBCriterion,
 * RWDBSelector, RWDBInserter, RWDBUpdater, and RWDBDeleter.
 * \endparblock
 */
class RWDB_GLOBAL RWDBColumn
{
public:
    /**
     * Default constructor that creates a column whose status is
     * RWDBStatus::notInitialized. This constructor is provided for
     * convenience, for example, for declaring arrays of columns; valid
     * columns are obtained by indexing into RWDBTable and RWDBSchema
     * objects.
     */
    RWDBColumn();

    RWDBColumn(RWDBColumnImp* imp);

    /**
     * Copy constructor. The created RWDBColumn shares an implementation
     * with \a column.
     */
    RWDBColumn(const RWDBColumn& column);

    /**
     * Assignment operator. Self shares an implementation with \a column.
     * Returns a reference to self.
     */
    RWDBColumn&             operator=(const RWDBColumn& column);

    virtual ~RWDBColumn();

    /**
     * Returns a deep copy of self.
     */
    RWDBColumn              clone() const;

    /**
     * RWDBColumn can be used to describe a parameter to a stored procedure.
     * The #ParamType \c enum describes the method of passing parameters
     * between the application and the stored procedure. See RWDBStoredProc
     * for more information.
     */
    enum ParamType {

        /**
         * (the default) column does not represent a parameter or parameter
         * type is unknown.
         */
        notAParameter,

        /**
         * input parameter.
         */
        inParameter,

        /**
         * output parameter.
         */
        outParameter,

        /**
         * input and output parameter.
         */
        inOutParameter
    };

    /**
     * Returns the name of the column.
     */
    RWCString               name() const;

    /**
     * Returns the name of the column qualified with the
     * \ref RWDBTable::tag() "tag" of the RWDBTable to which the column is
     * associated. For example:
     *
     * \code
     *  RWDBColumn  col1  =  table["col1"];
     *  cout  <<  col1.qualifiedName();
     * \endcode
     *
     * would produce output something like \c t123.col1. If self is not
     * associated with any table, an unqualified name is returned.
     */
    RWCString               qualifiedName() const;

    /**
     * Returns the length of the column as reported by the database. This is
     * often used to obtain the maximum string length. If no schema
     * information has been obtained, returns #RWDB_NO_TRAIT.
     */
    long                    storageLength() const;

    /**
     * Returns the precision of the column as reported by the database. If
     * not applicable to this column, or if no schema information has been
     * obtained, returns #RWDB_NO_TRAIT.
     */
    int                     precision() const;

    /**
     * Returns the scale of the column as reported by the database. If not
     * applicable to this column, or if no schema information has been
     * obtained, this routine returns #RWDB_NO_TRAIT.
     */
    int                     scale() const;

    /**
     * Returns \c true if the database reports that a null value is allowed
     * in this column, or if no schema information has been obtained.
     * Otherwise returns \c false.
     */
    bool                    nullAllowed() const;

    /**
     * Returns the data type used by the DB Interface Module to store this
     * column's data; see RWDBValue for a list of valid types. If the type
     * is not yet known, returns RWDBValue::NoType.
     */
    RWDBValue::ValueType    type() const;

    /**
     * Returns a value indicating the data type of the column as specified
     * by the database vendor, or #RWDB_NO_TRAIT if this information is not
     * available. The meaning of the value returned depends on the database
     * vendor's definitions.
     */
    int                     nativeType() const;

    /**
     * Returns a value indicating the parameter type of the column.
     */
    ParamType               paramType() const;

    /**
     * Returns the table with which self is associated, or a table whose
     * status is RWDBStatus::notInitialized if self is not associated with a
     * table.
     */
    RWDBTable               table() const;

    /**
     * Changes the name of this column to \a newName. Note that this does
     * not change the definition of the column in the database. Returns a
     * reference to self.
     */
    RWDBColumn&             name(const RWCString& newName);

    /**
     * Changes the value of self's \c nullAllowed attribute to the value of
     * \a nullAllowed. Note that this does not change the definition of the
     * column in the database. Returns a reference to self.
     */
    RWDBColumn&             nullAllowed(bool nullAllowed);

    /**
     * Changes the data type attribute of self to \a newType. Note that this
     * does not change the definition of the column in the database. Returns
     * a reference to self.
     */
    RWDBColumn&             type(RWDBValue::ValueType newType);

    /**
     * Changes the \c nativeType attribute of self to \a newType. Note that
     * this does not change the definition of the column in the database.
     * Returns a reference to self.
     */
    RWDBColumn&             nativeType(int newType);

    /**
     * Changes the \c storageLength attribute of self to \a newLength. Note
     * that this does not change the definition of the column in the
     * database. Returns a reference to self.
     */
    RWDBColumn&             storageLength(long newLength);

    /**
     * Changes the \c precision attribute of self to \a newPrecision. Note
     * that this does not change the definition of the column in the
     * database. Returns a reference to self.
     */
    RWDBColumn&             precision(int newPrecision);

    /**
     * Changes the \c scale attribute of self to \a newScale. Note that this
     * does not change the definition of the column in the database. Returns
     * a reference to self.
     */
    RWDBColumn&             scale(int newScale);

    /**
     * Changes the \c paramType attribute of self to \a newType. Note that
     * this does not change the definition of the parameter in the database.
     * Returns a reference to self.
     */
    RWDBColumn&             paramType(RWDBColumn::ParamType newType);

    /**
     * Changes the \c table attribute of self to \a table, thus associating
     * the column with \a table. Returns a reference to self.
     */
    RWDBColumn&             table(const RWDBTable& table);

    /**
     * Dissociates self from any table. Returns a reference to self.
     */
    RWDBColumn&             clearTable();

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the SQL
     * clause:
     *
     * \e column <tt>IS NULL</tt>
     *
     * where \e column refers to self. An RWDBCriterion is an encapsulation
     * of an SQL \c WHERE clause.
     */
    RWDBCriterion           isNull() const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the SQL
     * clause:
     *
     * \e column \c LIKE \a expression
     *
     * where \e column refers to self. For example, to produce the SQL
     * clause:
     *
     * <tt>col1 LIKE "%object%"</tt>
     *
     * you would write:
     *
     * \code
     *  table["col1"].like("%object%");
     * \endcode
     */
    RWDBCriterion           like(const RWDBExpr& expression) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the SQL
     * clause:
     *
     * \e column <tt>MATCH UNIQUE</tt> \a expression
     *
     * where \e column refers to self. An RWDBCriterion is an encapsulation
     * of an SQL \c WHERE clause.
     */
    RWDBCriterion           matchUnique(const RWDBExpr& expression) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the SQL
     * clause:
     *
     * \e column \c BETWEEN \a expression1 \c AND \a expression2
     *
     * where \e column refers to self. An RWDBCriterion is an encapsulation
     * of an SQL \c WHERE clause.
     */
    RWDBCriterion           between(const RWDBExpr& expression1,
                                    const RWDBExpr& expression2) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the SQL
     * phrase:
     *
     * \e column \c IN \a expression
     *
     * where \e column refers to self. An RWDBCriterion is an encapsulation
     * of an SQL \c WHERE clause. For example, to produce the SQL clause:
     *
     * <tt>col1 in (1, 2, 3)</tt>
     *
     * you could write:
     *
     * \code
     *  RWOrdered  aCollection;
     *  RWDBCollectableExpr  e1(RWDBExpr(1));
     *  RWDBCollectableExpr  e2(RWDBExpr(2));
     *  RWDBCollectableExpr  e3(RWDBExpr(3));
     *  aCollection.insert(&e1);
     *  aCollection.insert(&e2);
     *  aCollection.insert(&e3);
     *  RWDBExpr  e(aCollection);
     *
     *  table["col1"].in(e);
     * \endcode
     *
     * Alternatively, you could write:
     *
     * \code
     *  table["col1"].in(RWDBExpr("(1,2,3)",false));
     * \endcode
     *
     * \note
     * The parameter \c false in the constructor for the RWDBExpr in the
     * example above is required in order to suppress quotation marks in the
     * resultant SQL string. See RWDBExpr for more details.
     */
    RWDBCriterion           in(const RWDBExpr& expression) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the
     * <tt>LEFT OUTER JOIN</tt> SQL phrase for non-ANSI-compliant databases.
     * See the entry for RWDBJoinExpr regarding ANSI-compliant joins. Also
     * see the Access Module guides to determine which version of join is
     * supported. An RWDBCriterion is an encapsulation of an SQL \c WHERE
     * clause.
     */
    RWDBCriterion           leftOuterJoin(const RWDBExpr& expr) const;

    /**
     * Returns an RWDBCriterion that represents an encapsulation of the
     * <tt>RIGHT OUTER JOIN</tt> SQL phrase for non-ANSI-compliant
     * databases. See the entry for RWDBJoinExpr regarding ANSI-compliant
     * joins. Also see the Access Module guides to determine which version
     * of join is supported. This function can be called from a \c const
     * object. An RWDBCriterion is an encapsulation of an SQL \c WHERE
     * clause.
     */
    RWDBCriterion           rightOuterJoin(const RWDBExpr& expr) const;

    RWDBCriterion           fullOuterJoin(const RWDBExpr& expr) const;

    /**
     * Returns an RWDBAssignment that represents an encapsulation of the SQL
     * clause:
     *
     * \e column \c = \a value
     *
     * where \e column refers to self. Like the SQL \c SET clause, it is
     * used only in the SQL \c UPDATE statement.
     */
    RWDBAssignment          assign(char value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(unsigned char value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(short int value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(unsigned short int value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(long int value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(unsigned long int value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(int value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(unsigned int value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(long long value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(unsigned long long value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(float value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(double value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(long double value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const char* value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const wchar_t* value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const RWCString& value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const RWDBMBString& value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const RWWString& value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const RWDate& value) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 11.1, use
     * \ref RWDBColumn::assign(const RWDateTime&) const "assign(const RWDateTime&)"
     * instead.
     *
     * \copydoc assign(char) const
     */
    RW_DEPRECATE_FUNC("Use RWDBColumn::assign(const RWDateTime&) instead")
    RWDBAssignment          assign(const RWTime& value) const;

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const RWDateTime& value) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 11.1, use
     * \ref RWDBColumn::assign(const RWDateTime&) const "assign(const RWDateTime&)"
     * instead.
     *
     * \copydoc assign(char) const
     */
    RW_DEPRECATE_FUNC("Use RWDBColumn::assign(const RWDateTime&) instead")
    RWDBAssignment          assign(const RWDBDateTime& value) const;

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const RWDBDuration& value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const RWDecimalPortable& value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const RWDBBlob& value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const RWBasicUString& value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(RWDBValueManip value) const;

    /**
     * \copydoc assign(char) const
     */
    RWDBAssignment          assign(const RWDBExpr& expression) const;

    /**
     * Installs \a handler as the error handler for self. By default, an
     * RWDBStatus::ErrorHandler is inherited from the object that produced
     * self; this method overrides the default.
     */
    void                    setErrorHandler(RWDBStatus::ErrorHandler handler);

    /**
     * Returns the error handler attached to self.
     */
    RWDBStatus::ErrorHandler errorHandler() const;

    /**
     * Returns \c true if self's status is RWDBStatus::ok, otherwise
     * \c false.
     */
    bool                    isValid() const;

    /**
     * Returns the status of self.
     */
    RWDBStatus              status() const;

    /**
     * Returns a boolean value indicating whether or not self and \a column
     * are equivalent. Columns are equivalent if they have the same names
     * and are associated with the same table.
     */
    bool                    isEquivalent(const RWDBColumn& column) const;

    /**
     * Attempts to acquire the internal mutex lock. If the mutex is already
     * locked by another thread, the function blocks until the mutex is
     * released. This function can be called from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void                    acquire() const;

    /**
     * Releases a previously acquired mutex. This function can be called
     * from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void                    release() const;

    // allow use of a second data type ID
    int                     auxiliaryType() const;
    RWDBColumn&             auxiliaryType(int type);

    /**
     * Returns a deep copy of self's RWDBIdentityConstraint.
     */
    RWDBIdentityConstraint  getIdentity() const;

    /**
     * Sets self's identity constraint to a deep copy of \a constraint.
     */
    RWDBColumn&             setIdentity(const RWDBIdentityConstraint& constraint);

    /**
     * Sets the default value for this column to \a expr. To unset a default
     * value, pass an empty RWDBExpr created with the default constructor.
     */
    RWDBColumn&             defaultValue(const RWDBExpr& expr);

    /**
     * Returns the default value for this column. If there is no default,
     * the returned RWDBExpr is not valid.
     */
    RWDBExpr                defaultValue() const;

    /**
     * Returns \c true if this column has a default value.
     */
    bool                    hasDefault() const;

    // undocumented methods to allow the cache manager to be persisted.
    void     saveGuts(RWFile& f) const;
    void     saveGuts(RWvostream& s) const;
    void     restoreGuts(RWFile& f);
    void     restoreGuts(RWvistream& s);

private:
    RWDBCountedRef<RWDBColumnImp> impl_;

};

#endif
