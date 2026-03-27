#ifndef __RWDB_PRIMARYKEY_H__
#define __RWDB_PRIMARYKEY_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/primarykey.h#1 $
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
#include <rw/db/phrase.h>
#include <rw/db/schema.h>

/**
 * \ingroup db_common_group
 *
 * \brief
 * Represents a primary key, used when creating a database table or fetching
 * a database table primary key.
 *
 * Class RWDBPrimaryKey is an ordered collection of RWDBColumn instances. An
 * RWDBPrimaryKey serves as an encapsulation of the database notion of
 * primary key, a set of attributes defining a primary key.
 *
 * An RWDBTable can have an RWDBPrimaryKey. An application can interrogate
 * an RWDBTable for primary key information, or obtain a copy of an
 * RWDBPrimaryKey for its own use. An RWDBPrimaryKey instance can be used
 * with RWDBSchema to create a database table with a primary key. To do
 * this, an application can use an RWDBPrimaryKey obtained from an existing
 * RWDBTable, modify an existing RWDBPrimaryKey, or build one from scratch
 * using the methods appendColumn() and constraintName().
 *
 * This class is implemented using a technique called
 * <em>copy-on-write</em>. With this technique, the copy constructor and
 * assignment operator reference the existing object, making a copy only
 * when the object changes. The result is excellent performance, with
 * easy-to-understand copy semantics.
 *
 * \synopsis
 * #include <rw/db/primarykey.h>
 *
 * RWDBPrimaryKey pk;
 * pk = myTable.primaryKey();
 * \endsynopsis
 */
class RWDB_SYMBOLIC RWDBPrimaryKey
{
    friend class RWDB_GLOBAL RWDBSchema;
    friend class RWDB_GLOBAL RWDBSchemaImp;

public:
    /**
     * The default constructor creates an empty RWDBPrimaryKey, that is, one
     * with zero columns.
     */
    RWDBPrimaryKey(const RWCString& constraintName = "");

    /**
     * Copy constructor. Self shares an implementation with \a pk until the
     * data is modified.
     */
    RWDBPrimaryKey(const RWDBPrimaryKey& pk);

    /**
     * Constructor. Self shares an implementation with \a sch until the data
     * is modified.
     */
    RWDBPrimaryKey(const RWDBSchema& sch);

    RWDBPrimaryKey(const RWDBStatus& status);

    ~RWDBPrimaryKey();

    /**
     * Assignment operator. Self shares an implementation with \a pk until
     * the data is modified.
     */
    RWDBPrimaryKey& operator=(const RWDBPrimaryKey& pk);

    /**
     * Assignment operator. Self shares an implementation with \a sch until
     * the data is modified.
     */
    RWDBPrimaryKey& operator=(const RWDBSchema& sch);

    /**
     * Compares self to \a pk. Returns \c true if \a pk and self share the
     * same implementation.
     */
    bool            operator==(const RWDBPrimaryKey& pk) const;

    /**
     * Compares self to \a pk. Returns \c true if \a pk and self do not
     * share the same implementation.
     *
     * This is equivalent to:
     * \code
     * !(self == pk)
     * \endcode
     */
    bool            operator!=(const RWDBPrimaryKey& pk) const;

    /**
     * Returns the RWDBColumn in self at position \a index. If \a index is
     * out of range, returns an RWDBColumn with a status of
     * RWDBStatus::invalidPosition. Indexing into an empty primary key is
     * treated as out of range.
     *
     * \note
     * The returned RWDBColumn is not a deep copy; modifications to it
     * change the containing primary key.
     */
    RWDBColumn      operator[](size_t index) const;

    /**
     * Returns the first RWDBColumn in self with the given \a name. If no
     * such column exists, an RWDBColumn is returned with a status
     * RWDBStatus::columnNotFound.
     *
     * \note
     * The returned RWDBColumn is not a deep copy; modifications to it
     * change the containing primary key.
     */
    RWDBColumn      operator[](const RWCString& name) const;

    /**
     * Constructs a new RWDBColumn according to the supplied parameters,
     * appends it to self, and returns it. Applications using this method
     * must usually supply only a \a name.
     *
     * \param name
     * Represents the name of the column appended to the primary key.
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
     * \ref RWDBValue::Decimal "Decimal". The \a precision and \a scale of
     * the resulting column is set accordingly.
     *
     * \param nullAllowed
     * Should be set to \c false if a column requires a value. The default
     * value of \c true allows a column's value to be set to \c NULL.
     *
     * \param paramType
     * Not applicable to primary keys.
     */
    RWDBColumn      appendColumn(const RWCString& name,
                                 RWDBValue::ValueType type = RWDBValue::NoType,
                                 long storageLength = RWDB_NO_TRAIT,
                                 int nativeType = RWDB_NO_TRAIT,
                                 int precision = RWDB_NO_TRAIT,
                                 int scale = RWDB_NO_TRAIT,
                                 bool nullAllowed = true,
                                 RWDBColumn::ParamType paramType = RWDBColumn::notAParameter);

    /**
     * Creates a deep copy of the RWDBColumn \a col, using the
     * RWDBColumn::clone() method. Appends the copied column to self, and
     * returns it.
     */
    RWDBColumn      appendColumn(const RWDBColumn& col);

    /**
     * \internal
     *
     * Creates a deep copy of the RWDBColumn \a col, using the
     * RWDBColumn::clone() method. Prepends the copied column to self, and
     * returns it.
     */
    RWDBColumn      prependColumn(const RWDBColumn& col);

    /**
     * Returns an RWCString representing self as a string based on the
     * format found in \a pb.
     */
    RWCString       asString(const RWDBPhraseBook& pb) const;

    /**
     * Produces a deep copy of self.
     */
    RWDBPrimaryKey  clone() const;

    /**
     * Returns a shallow copy of the column from self at the specified
     * \a index. If \a index is out of range, returns an RWDBColumn with a
     * status of RWDBStatus::invalidPosition.
     */
    RWDBColumn      column(size_t index) const;

    /**
     * Returns a shallow copy of the column from self whose name matches the
     * given \a name. If there is no match, returns an RWDBColumn with a
     * status of RWDBStatus::columnNotFound.
     */
    RWDBColumn      column(const RWCString& name) const;

    /**
     * Returns a shallow copy of the column from self whose name matches the
     * given \a name, according to \a caseCompare. If there is no match,
     * returns an RWDBColumn with a status of RWDBStatus::columnNotFound.
     */
    RWDBColumn      column(const RWCString& name,
                           RWCString::caseCompare caseCompare) const;
    /**
     * Returns the name of the column at the specified \a index. Returns an
     * empty string if the index is out of range.
     */
    RWCString       columnName(size_t index) const;

    /**
     * Returns the constraint name of this primary key.
     */
    RWCString       constraintName() const;

    /**
     * Sets the constraint name of self to \a newName. Returns a reference
     * to self.
     *
     * \note
     * This does not change the name of the primary key on a table that
     * already exists in the database.
     */
    RWDBPrimaryKey& constraintName(const RWCString& newName);

    /**
     * Returns the number of RWDBColumn instances in self.
     */
    size_t          entries() const;

    /**
     * Returns the index of the first RWDBColumn in self with the given
     * \a name. Returns #RW_NPOS if no such column is found.
     */
    size_t          index(const RWCString& name) const;

    /**
     * Returns the index of the first column from self whose name matches
     * the given \a name, according to \a caseCompare. If there is no match,
     * returns #RW_NPOS.
     */
    size_t          index(const RWCString& name,
                          RWCString::caseCompare caseCompare) const;

    /**
     * Returns the index of the first RWDBColumn in self with the same name
     * as the name of the given \a column. Returns #RW_NPOS if no such
     * column is found.
     */
    size_t          index(const RWDBColumn& column) const;

    /**
     * Returns \c true if self contains zero entries, otherwise returns
     * \c false.
     */
    bool            isEmpty() const;

    /**
     * Returns \c true if self's status is RWDBStatus::ok, otherwise returns
     * \c false.
     */
    bool            isValid() const;

    /**
     * Installs \a handler as self's error handler. The supplied \a handler
     * is inherited by all objects produced by self. By default, the
     * RWDBStatus::ErrorHandler of an RWDBPrimaryKey is inherited from the
     * object that produced it; this method overrides the default.
     */
    void            setErrorHandler(RWDBStatus::ErrorHandler handler);

    /**
     * Returns the error handler attached to self.
     */
    RWDBStatus::ErrorHandler errorHandler() const;

    /**
     * Returns the current status of self.
     */
    RWDBStatus      status() const;

    /**
     * Returns the number of bytes necessary to store the object using the
     * global functions:
     *
     * \code
     * RWFile& operator<<(RWFile&, const RWDBPrimaryKey&);
     * RWvostream& operator<<(RWvostream&, const RWDBPrimaryKey&);
     * \endcode
     */
    RWspace         binaryStoreSize() const;

    /**
     * Saves \a pk to an RWvostream.
     *
     * Throws an RWExternalErr if the stream is corrupted.
     */
    friend RWDB_SYMBOLIC
    RWvostream& operator<<(RWvostream& v, const RWDBPrimaryKey& pk);

    /**
     * Saves \a pk to an RWFile.
     *
     * Throws an RWExternalErr if the file is corrupted.
     */
    friend RWDB_SYMBOLIC
    RWFile& operator<<(RWFile& f, const RWDBPrimaryKey& pk);

    /**
     * Restores an RWDBPrimaryKey into \a pk from an RWvistream, replacing
     * the previous contents of \a pk.
     *
     * Throws an RWExternalErr if the stream is corrupted.
     */
    friend RWDB_SYMBOLIC
    RWvistream& operator>>(RWvistream& v, RWDBPrimaryKey& pk);

    /**
     * Restores an RWDBPrimaryKey into \a pk from an RWFile, replacing the
     * previous contents of \a pk.
     *
     * Throws an RWExternalErr if the file is corrupted.
     */
    friend RWDB_SYMBOLIC
    RWFile& operator>>(RWFile& f, RWDBPrimaryKey& pk);

private:
    RWDBCountedRef<RWDBPrimaryKeyImp> impl_;
    void cow();

    /**
     * \internal
     */
    RWDBPrimaryKey(RWDBPrimaryKeyImp* imp);
};

#endif //__RWDB_PRIMARYKEY_H__
