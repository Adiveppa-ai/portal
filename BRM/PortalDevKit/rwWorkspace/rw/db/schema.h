#ifndef __RWDB_SCHEMA_H__
#define __RWDB_SCHEMA_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/schema.h#1 $
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
 * Class RWDBSchema is an ordered collection of RWDBColumn instances.  As such,
 * it serves as an encapsulation of the database notion of schema, a set
 * of attributes defining a table.  We extend the notion slightly: an
 * RWDBSchema may also be used to define a stored procedure's formal
 * parameters.
 *
 **************************************************************************/
#include <rw/db/column.h>
#include <rw/db/defs.h>

class RWDBPrimaryKey;

/**
 * \ingroup db_common_group
 *
 * \brief
 * An ordered collection of RWDBColumn instances, encapsulating the database
 * notion of a schema.
 *
 * Class RWDBSchema is an ordered collection of RWDBColumn instances. An
 * RWDBSchema serves as an encapsulation of the database notion of schema, a
 * set of attributes defining a table. The DB Interface Module extends this
 * notion slightly by using an RWDBSchema to define a stored procedure's
 * formal parameter list, and to specify a list of columns wherever one is
 * required. Each RWDBSchema can have foreign key, primary key, check
 * constraint, and unique constraint information associated with it.
 *
 * Every RWDBTable has an RWDBSchema. An application can interrogate the
 * RWDBSchema of an RWDBTable for schema information, or obtain a copy of an
 * RWDBSchema for its own use. An RWDBSchema instance may be used to create
 * a database table. To do this, an application can use an RWDBSchema
 * obtained from an existing RWDBTable, modify an existing RWDBSchema, or
 * build one from scratch using the methods appendColumn(), foreignKey(),
 * primaryKey(), checkConstraint(), and uniqueConstraint().
 *
 * This class is implemented using a technique called <em>copy on
 * write</em>. With this technique, the copy constructor and assignment
 * operators reference the old object and, as a result, are very fast. An
 * actual copy is made only when the object is about to be changed. The net
 * result is excellent performance, with easy-to-understand copy semantics.
 *
 * \synopsis
 * #include <rw/db/schema.h>
 *
 * RWDBSchema s;
 * s = myTable.schema();
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBSchema
{
    friend class RWDBPrimaryKey;
    friend class RWDBForeignKeyImp;

public:

    /**
     * The default constructor creates an empty RWDBSchema, that is, one
     * with zero columns.
     */
    RWDBSchema();

    RWDBSchema(const RWDBStatus& status);

    /**
     * Copy constructor. Self shares an implementation with \a schema until
     * the data is modified.
     */
    RWDBSchema(const RWDBSchema& schema);

    /**
     * Constructor. Self shares an implementation with \a pk until the data
     * is modified.
     */
    RWDBSchema(const RWDBPrimaryKey& pk);

    virtual ~RWDBSchema();

    /**
     * Assignment operator. Self shares an implementation with \a schema
     * until the data is modified.
     */
    RWDBSchema& operator=(const RWDBSchema& schema);

    /**
     * Compares self to \a schema. Returns \c true if \a schema and self are
     * identical.
     */
    bool        operator==(const RWDBSchema& schema) const;

    /**
     * Compares self to \a schema. Returns \c true if \a schema and self are
     * unequal.
     */
    bool        operator!=(const RWDBSchema& schema) const;

    /**
     * Produces a deep copy of self.
     */
    RWDBSchema  clone() const;

    // multithreading functions

    /**
     * Attempts to acquire the internal mutex lock. If the mutex is already
     * locked by another thread, the function blocks until the mutex is
     * released. This function can be called from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void        acquire() const;

    /**
     * Releases a previously acquired mutex. This function can be called
     * from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void        release() const;

    // indexing

    /**
     * Returns the RWDBColumn in self at position \a index. If \a index is
     * out of range, returns an RWDBColumn with a status of
     * RWDBStatus::invalidPosition. Indexing into an empty schema is treated
     * as out of range.
     *
     * \note
     * The returned RWDBColumn is not a deep copy; modifications to it
     * change the containing schema.
     */
    RWDBColumn  operator[](size_t index) const;

    /**
     * Returns the first RWDBColumn in self with the given \a name. If no
     * such column exists, an RWDBColumn is returned with a status
     * RWDBStatus::columnNotFound.
     *
     * \note
     * The returned RWDBColumn is not a deep copy; modifications to it
     * change the containing schema.
     */
    RWDBColumn  operator[](const RWCString& name) const;

    /**
     * Returns a shallow copy of the column from self at the specified
     * \a index. If \a index is out of range, returns an RWDBColumn with a
     * status of RWDBStatus::invalidPosition.
     */
    RWDBColumn  column(size_t index) const;

    /**
     * Returns a shallow copy of the column from self whose name matches the
     * given \a name. If there is no match, returns an RWDBColumn with a
     * status of RWDBStatus::columnNotFound.
     */
    RWDBColumn  column(const RWCString& name) const;

    /**
     * Returns a shallow copy of the column from self whose name matches the
     * given \a name, according to \a caseCompare. If there is no match,
     * returns an RWDBColumn with a status of RWDBStatus::columnNotFound.
     */
    RWDBColumn  column(const RWCString& name,
                       RWCString::caseCompare caseCompare) const;

    /**
     * Returns the name of the column at the specified \a index.
     */
    RWCString   columnName(size_t index) const;

    /**
     * Returns the index of the first RWDBColumn in self with the given
     * \a name. Returns #RW_NPOS if no such column is found.
     */
    size_t      index(const RWCString& name) const;

    /**
     * Returns the index of the first column from self whose name matches
     * the given \a name, according to \a caseCompare. If there is no match,
     * returns #RW_NPOS.
     */
    size_t      index(const RWCString& name,
                      RWCString::caseCompare caseCompare) const;

    /**
     * Returns the index of the first RWDBColumn in self with the same name
     * as the name of the given \a column. Returns #RW_NPOS if no such
     * column is found.
     */
    size_t      index(const RWDBColumn& column) const;


    /**
     * Returns a comma-delimited string of the foreign keys attached to
     * self.
     */
    RWCString   keysAsString(const RWDBPhraseBook& pb) const;

    /**
     * \copydoc keysAsString(const RWDBPhraseBook&) const
     */
    RWCString   keysAsString() const;

    /**
     * Returns a comma-delimited string of the check constraints attached to
     * self.
     */
    RWCString   checkConstraintsAsString(const RWDBPhraseBook& pb) const;

    /**
     * \copydoc checkConstraintsAsString(const RWDBPhraseBook&) const
     */
    RWCString   checkConstraintsAsString() const;

    /**
     * Returns a comma-delimited string of the unique constraints attached
     * to self.
     */
    RWCString   uniqueConstraintsAsString(const RWDBPhraseBook& pb) const;

    /**
     * \copydoc uniqueConstraintsAsString(const RWDBPhraseBook&) const
     */
    RWCString   uniqueConstraintsAsString() const;

    // accessors

    /**
     * Returns the number of RWDBColumn instances in self.
     */
    size_t      entries() const;

    /**
     * Returns \c true if self contains zero entries, otherwise returns
     * \c false.
     */
    bool        isEmpty() const;

    /**
     * Appends a deep copy of \a fk to self's list of foreign keys. Returns
     * a reference to self.
     */
    RWDBSchema& foreignKey(const RWDBForeignKey& fk);

    /**
     * Sets self's primary key to \a pk. Returns a reference to self.
     */
    RWDBSchema& primaryKey(const RWDBPrimaryKey& pk);

    /**
     * Returns the primary key associated with self. An empty RWDBPrimaryKey
     * indicates there is no primary key associated with self.
     *
     * \note
     * If this schema was retrieved from a database table using
     * RWDBTable::schema(), the primary key will be set only if
     * RWDBTable::primaryKey() was called first.
     */
    RWDBPrimaryKey  primaryKey() const;

    /**
     * Appends a deep copy of \a cc to self's list of check constraints.
     * Returns a reference to self.
     */
    RWDBSchema& checkConstraint(const RWDBCheckConstraint& cc);

    /**
     * Appends a deep copy of \a uc to self's list of unique constraints.
     * Returns a reference to self.
     */
    RWDBSchema& uniqueConstraint(const RWDBUniqueConstraint& uc);

    /**
     * Constructs a new RWDBColumn according to the supplied parameters,
     * appends it to self, and returns it. Applications using this method
     * must usually supply only \a name and \a type, as well as
     * \a storageLength, if \a type is RWDBValue::String.
     *
     * \param name
     * Represents the name of the new column appended to the schema.
     *
     * \param type
     * Should be one of the data type attributes of the DB Interface Module.
     * See RWDBValue::ValueType for more explanation.
     *
     * \param storageLength
     * Should be set if the data type requires a size, such as
     * \ref RWDBValue::String "String" or \ref RWDBValue::Blob "Blob" data
     * types.
     *
     * \param nativeType
     * Should be set if one of the data type attributes of the DB Interface
     * Module cannot represent the native data type of the database. If this
     * field is set, \a type should be left as the default to show that a
     * native data type was requested. You can determine native data types
     * of a specific database through documentation or header files.
     *
     * \param precision
     * \a precision is set when specifying a numeric data type, such as
     * \ref RWDBValue::Decimal "Decimal". The \a precision of the resulting
     * column is set accordingly.
     *
     * \param scale
     * \a scale is set when specifying a numeric data type, such as
     * \ref RWDBValue::Decimal "Decimal". The \a scale of the resulting
     * column is set accordingly.
     *
     * \param nullAllowed
     * Should be set to \c false if a column requires a value. The default
     * value of \c true allows a column's value to be set to \c NULL.
     *
     * \param paramType
     * Should be set when specifying the parameters of a stored procedure.
     * See RWDBStoredProc for more information on how to use this parameter.
     * For normal tables, use the default value.
     */
    RWDBColumn  appendColumn(const RWCString&      name,
                             RWDBValue::ValueType  type = RWDBValue::NoType,
                             long                  storageLength = RWDB_NO_TRAIT,
                             int                   nativeType = RWDB_NO_TRAIT,
                             int                   precision = RWDB_NO_TRAIT,
                             int                   scale = RWDB_NO_TRAIT,
                             bool             nullAllowed = true,
                             RWDBColumn::ParamType paramType =
                                 RWDBColumn::notAParameter);

    /**
     * Creates a deep copy of the RWDBColumn \a col, using the
     * RWDBColumn::clone() method. Appends the copied column to self, and
     * returns it.
     */
    RWDBColumn  appendColumn(const RWDBColumn& col);

    // format self as SQL string

    /**
     * Produces a comma-delimited list of names of RWDBColumn instances in
     * self.
     */
    RWCString   asString() const;

    /**
     * Produces a list of the names of the RWDBColumn instances in self,
     * delimited by the \c listDelimiter character defined in \a phrasebook.
     */
    RWCString   asString(const RWDBPhraseBook& phrasebook) const;

    // error handling

    /**
     * Installs \a handler as self's error handler. The supplied \a handler
     * is inherited by all objects produced by self. By default, the
     * RWDBStatus::ErrorHandler of an RWDBSchema is inherited from the
     * object that produced it; this method overrides the default.
     */
    void        setErrorHandler(RWDBStatus::ErrorHandler handler);

    /**
     * Returns the error handler attached to self.
     */
    RWDBStatus::ErrorHandler errorHandler() const;

    /**
     * Returns \c true if self's status is RWDBStatus::ok, otherwise returns
     * \c false.
     */
    bool        isValid() const;

    /**
     * Returns the current status of self.
     */
    RWDBStatus  status() const;

    /**
     * Returns the number of bytes necessary to store the object using the
     * global functions:
     *
     * \code
     * RWFile& operator<<(RWFile&, const RWDBSchema&);
     * RWvostream& operator<<(RWvostream&, const RWDBSchema&);
     * \endcode
     */
    RWspace     binaryStoreSize() const;

    /**
     * Saves \a obj to an RWvostream.
     *
     * Throws an RWExternalErr if the stream is corrupted.
     */
    friend RWDB_SYMBOLIC
    RWvostream& operator<<(RWvostream& v, const RWDBSchema& obj);

    /**
     * Saves \a obj to an RWFile.
     *
     * Throws an RWExternalErr if the file is corrupted.
     */
    friend RWDB_SYMBOLIC
    RWFile&  operator<<(RWFile& f, const RWDBSchema& obj);

    /**
     * Restores an RWDBSchema into \a obj from an RWvistream, replacing the
     * previous contents of \a obj.
     *
     * Throws an RWExternalErr if the stream is corrupted.
     */
    friend RWDB_SYMBOLIC
    RWvistream& operator>>(RWvistream& v, RWDBSchema& obj);


    /**
     * Restores an RWDBSchema into \a obj from an RWFile, replacing the
     * previous contents of \a obj.
     *
     * Throws an RWExternalErr if the file is corrupted.
     */
    friend RWDB_SYMBOLIC
    RWFile& operator>>(RWFile& f, RWDBSchema& obj);

private:

    RWDBCountedRef<RWDBSchemaImp> impl_;

    void cow();
    void cloneSelf();

    /**
     * \internal
     */
    RWDBSchema(RWDBSchemaImp* imp);
};


#endif
