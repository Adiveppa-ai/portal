#ifndef __RWDB_FORKEY_H__
#define __RWDB_FORKEY_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/forkey.h#1 $
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
 * Class RWDBForeignKey is an ordered collection of RWDBColumn instances.
 * As such, it serves as an encapsulation of the database notion of
 * ForeignKey, a set of attributes defining a key.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/db/status.h>
#include <rw/collect.h>
#include <rw/ordcltn.h>
#include <rw/tools/pointer.h>

/**
 * \ingroup db_common_group
 * \class RWDBForeignKey
 *
 * \brief
 * Represents foreign keys in a database, used when creating a database
 * table or fetching a database table schema.
 *
 * RWDBForeignKey is used to represent foreign keys in a database, used when
 * building up an RWDBSchema in preparation for an
 * RWDBDatabase::createTable() call. An RWDBForeignKey is also used as
 * elements of lists that are returned from RWDBTable::foreignKeys() and
 * RWDBTable::referredToBy(). RWDBForeignKey has much the same interface and
 * semantics as RWDBSchema.
 *
 * RWDBForeignKey is designed around the Interface/Implementation paradigm.
 * An RWDBForeignKey instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation. An RWDBForeignKey
 * implementation is a base class from which a family of database-specific
 * foreign key implementations is derived.
 *
 * \synopsis
 * #include <rw/db/forkey.h>
 *
 * RWDBForeignKey fk;
 * \endsynopsis
 *
 * \sa
 * RWDBDatabase, RWDBTable, RWDBForeignKeyList, and RWDBSchema.
 *
 * \example
 * <b>Example 1</b>
 *
 * In this example, two tables are created, a \c Professor table with \c pid
 * as the primary key and a \c Course table with \c profid as a foreign key
 * into the \c Professor table.
 *
 * \code
 * RWDBSchema  profSchema;
 * RWDBSchema  primeKey;
 *
 * RWDBColumn aCol1;
 * aCol1.name("profname").type(RWDBValue::String).
 *                      nullAllowed(false).storageLength(30);
 * profSchema.appendColumn( aCol1 );
 *
 * RWDBColumn aCol2;
 * aCol2.name("pid").type(RWDBValue::Int).nullAllowed(false);
 * profSchema.appendColumn( aCol2 );
 *
 * primeKey.appendColumn( profSchema["pid"] ); //pid is the
 *                                             //primary key;
 * profSchema.primaryKey( primeKey );          //Attach the
 *                                             //primary key
 *                                             //to the
 *                                             //professor schema.
 *
 * // Create the Professor table
 * aDatabase.createTable("Professor", profSchema);
 *
 * // Now create the Course table
 * RWDBSchema courseSchema;
 * courseSchema.appendColumn( aCol1 );
 * courseSchema.appendColumn( aCol2 );
 *
 * RWDBColumn aCol3;
 * aCol3.name("coursename").type(RWDBValue::String).
 *                         nullAllowed(false).storageLength(30);
 * courseSchema.appendColumn( aCol3 );
 * RWDBColumn aCol4;
 * aCol4.name("profid").type(RWDBValue::Int).nullAllowed(false);
 * courseSchema.appendColumn( aCol4 );
 *
 * RWDBForeignKey keyToProf("Professor");
 * keyToProf.appendColumn(courseSchema["profid"]);
 *                                       //profid is the
 *                                       //foreign key for the
 *                                       //Professor table.
 *
 * courseSchema.foreignKey( keyToProf ); //Attach the foreign
 *                                       //key to the
 *                                       //course Schema.
 * aDatabase.createTable("Course", courseSchema);
 *                                       //Create the Course
 *                                       //table.
 * \endcode
 *
 * <b>Example 2</b>
 *
 * This next example queries the \c Course table for its foreign key into
 * the \c Professor table. It assumes the tables have been set up according
 * to the example above.
 *
 * \code
 * RWDBTable course = aDatabase.table("Course");
 * assert( course.exists() );
 * RWDBForeignKeyList aList;
 * RWDBStatus status = course.foreignKeys("Professor", aList);
 * RWDBForeignKey& fKey = aList[0];
 * assert( fKey.referenceName() == "Professor" );
 * assert( fKey[0].name() ==  "profid");
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBForeignKey : public RWCollectable
{
public:
    /**
     * This enum defines the constraint options.
     */
    enum Constraint {
#if !defined(RWDB_RESTRICT_DEFINED)
        /**
         * cascade
         */
        cascade = 'C',

        /**
         * restrict
         */
        restrict = 'R',

        /**
         * nullify
         */
        nullify = 'N',

        /**
         * defaultify
         */
        defaultify = 'D',
#endif
        Cascade = 'C',
        Restrict = 'R',
        Nullify = 'N',
        Defaultify = 'D'
    };

    /**
     * Creates an empty RWDBForeignKey. Provided for convenience only.
     */
    RWDBForeignKey();

    /**
     * This constructor creates an empty RWDBForeignKey, that is, one with
     * zero columns. The name of the table to which self refers is
     * \a refName. The update constraint associated with self is
     * \a updateConstraint. The delete constraint associated with self is
     * \a deleteConstraint.
     */
    RWDBForeignKey(const RWCString& refName,
                   Constraint updateConstraint = Restrict,
                   Constraint deleteConstraint = Restrict);

    /**
     * Constructor.
     */
    RWDBForeignKey(const RWCString& constraintName,
                   const RWCString& refName,
                   Constraint updateConstraint = Restrict,
                   Constraint deleteConstraint = Restrict);

    /**
     * Copy constructor. Self shares an implementation with \a fk.
     */
    RWDBForeignKey(const RWDBForeignKey& fk);

    virtual ~RWDBForeignKey();

    /**
     * Assignment operator. Self shares an implementation with \a fk.
     */
    RWDBForeignKey&  operator=(const RWDBForeignKey& fk);

    /**
     * Compares self to \a fk. Returns \c true if \a fk and self share the
     * same implementation.
     */
    bool             operator==(const RWDBForeignKey& fk) const;

    /**
     * Returns the RWDBColumn in self at position \a index. If the \a index
     * is out of range, returns an RWDBColumn with a status of
     * RWDBStatus::invalidPosition. Indexing into an empty RWDBForeignKey is
     * treated as out of range. Note that the returned RWDBColumn is not a
     * deep copy; modifications to RWDBColumn change the containing
     * RWDBForeignKey.
     */
    RWDBColumn       operator[](size_t index) const;

    /**
     * Returns the first RWDBColumn in self with the given \a name. If no
     * such column exists, returns an RWDBColumn with a status of
     * RWDBStatus::columnNotFound. Note that the returned RWDBColumn is not
     * a deep copy; modifications to RWDBColumn change the containing
     * schema.
     */
    RWDBColumn       operator[](const RWCString& name) const;

    /**
     * Returns a shallow copy of the column from self at the specified
     * \a index. If the \a index is out of range, returns an RWDBColumn
     * whose status is RWDBStatus::invalidPosition.
     */
    RWDBColumn       column(size_t index) const;

    /**
     * Returns a shallow copy of the column from self whose name matches the
     * given \a name. If there is no match, returns an RWDBColumn whose
     * status is RWDBStatus::columnNotFound.
     */
    RWDBColumn       column(const RWCString& name) const;

    /**
     * Returns a shallow copy of the column from self whose name matches the
     * given \a name, according to \a caseCompare. If there is no match,
     * returns an RWDBColumn whose status is RWDBStatus::columnNotFound.
     */
    RWDBColumn       column(const RWCString& name,
                            RWCString::caseCompare caseCompare) const;

    /**
     * Returns the index of the first RWDBColumn in self with the given
     * \a name. Returns #RW_NPOS if no such column is found.
     */
    size_t           index(const RWCString& name) const;

    /**
     * Returns the index of the first column from self whose name matches
     * the given \a name, according to \a caseCompare. If there is no match,
     * returns #RW_NPOS.
     */
    size_t           index(const RWCString& name,
                           RWCString::caseCompare caseCompare) const;

    /**
     * Returns the index of the first RWDBColumn in self with the same name
     * as the name of the given \a column. Returns #RW_NPOS if no such
     * column is found.
     */
    size_t           index(const RWDBColumn& column) const;

    /**
     * Returns the number of RWDBColumn instances in self.
     */
    size_t           entries() const;

    /**
     * Returns \c true if self contains zero entries, otherwise returns
     * \c false.
     */
    bool             isEmpty() const;

    /**
     * Returns the constraint name of this foreign key.
     */
    RWCString        constraintName() const;

    /**
     * Returns the reference name of self.
     */
    RWCString        referenceName() const;

    /**
     * Returns a reference to the currently held reference key of self.
     */
    RWDBSchema&      referenceKey();

    /**
     * Returns the update constraint of self.
     */
    Constraint       updateConstraint() const;

    /**
     * Returns the delete constraint of self.
     */
    Constraint       deleteConstraint() const;

    /**
     * Creates a copy of \a col and appends to self. Returns the copy
     * \a col.
     */
    RWDBColumn       appendColumn(const RWDBColumn& col);

    /**
     * Sets the constraint name of self to be \a newName. Note that this
     * does not change the name of the foreign key in a table which already
     * exists in the database.
     */
    void             constraintName(const RWCString& newName);

    void             referenceName(const RWCString& newName);

    /**
     * Sets the update constraint of self to the \a newConstraint. Note that
     * this does not change the update constraint of a foreign key of a
     * table that already exists.
     */
    void             updateConstraint(Constraint newConstraint);

    /**
     * Sets the delete constraint of self to the \a newConstraint. Note that
     * this does not change the delete constraint of a foreign key of a
     * table which already exists.
     */
    void             deleteConstraint(Constraint newConstraint);

    /**
     * Sets the referenced key of self to \a schema. This does not change
     * the referenced key of a foreign key in a table that already exists in
     * the database.
     */
    void             referenceKey(const RWDBSchema& schema);

    /**
     * Returns an RWCString representing self as string based on the format
     * found in \a phraseBook.
     */
    RWCString        asString(const RWDBPhraseBook& phraseBook) const;

    /**
     * Installs \a handler as self's error handler. The supplied \a handler
     * is inherited by all objects produced by self. By default, an
     * RWDBStatus::ErrorHandler is inherited from the object that produced
     * self; this method overrides the default.
     */
    void             setErrorHandler(RWDBStatus::ErrorHandler handler);

    /**
     * Returns the error handler attached to self.
     */
    RWDBStatus::ErrorHandler errorHandler() const;

    /**
     * Returns \c true if self's status is RWDBStatus::ok, otherwise returns
     * \c false.
     */
    bool             isValid() const;

    /**
     * Returns a deep copy of self.
     */
    RWDBForeignKey   clone() const;

    /**
     * Returns the current status of self.
     */
    RWDBStatus       status() const;

    /**
     * If \a c points to an RWDBForeignKey, returns the result of
     * asString().\ref RWCString::compareTo() "compareTo(c->asString())"
     * using the default \c phrasebook. Throws an \b std::bad_cast exception
     * if \a c does not point to an RWDBForeignKey.
     *
     * As a precondition, \a c is tested to determine if it is a null
     * pointer. If null, the method asserts in debug mode, and throws
     * RWInternalErr in optimized builds.
     */
    virtual int      compareTo(const RWCollectable* c) const;

    /**
     * If \a c is an RWDBForeignKey according to the method isA(), compares
     * the result of its asString() method to the result of this
     * RWDBForeignKey object's asString() method using the default
     * phrasebook. Returns \c true if they are equal, otherwise returns
     * \c false. If \a c is not an RWDBForeignKey, returns \c false.
     *
     * As a precondition, \a c is tested to determine if it is a null
     * pointer. If null, the method asserts in debug mode, and throws
     * RWInternalErr in optimized builds.
     */
    virtual bool     isEqual(const RWCollectable* c) const;

    /**
     * Returns asString().\ref RWCString::hash() "hash()".
     */
    virtual unsigned hash() const;

    /**
     * Returns __RWDBFOREIGNKEY.
     */
    virtual RWClassID isA() const;

    // any documentation for the following is in the base class
    RWspace          binaryStoreSize() const;
    virtual void     saveGuts(RWFile& file) const;
    virtual void     saveGuts(RWvostream& stream) const;
    virtual void     restoreGuts(RWFile& file);
    virtual void     restoreGuts(RWvistream& stream);
    virtual RWCollectable* newSpecies() const;
    virtual RWCollectable* copy() const;
    static RWClassID       classIsA();

    friend RWDB_SYMBOLIC RWvistream&
    operator>>(RWvistream& s, RWDBForeignKey*& pCl);

    friend RWDB_SYMBOLIC RWFile&
    operator>>(RWFile& f, RWDBForeignKey*& pCl);

    RW_INLINE_FRIEND
    RWvostream& operator<<(RWvostream& v, const RWDBForeignKey& Cl)
    {
        Cl.recursiveSaveOn(v);
        return v;
    }

    RW_INLINE_FRIEND
    RWFile& operator<<(RWFile& f, const RWDBForeignKey& Cl)
    {
        Cl.recursiveSaveOn(f);
        return f;
    }

    RW_INLINE_FRIEND
    RWvistream& operator>>(RWvistream& v, RWDBForeignKey& Cl)
    {
        RWCollectable::recursiveRestoreFrom(v, &Cl);
        return v;
    }

    RW_INLINE_FRIEND
    RWFile& operator>>(RWFile& f, RWDBForeignKey& Cl)
    {
        RWCollectable::recursiveRestoreFrom(f, &Cl);
        return f;
    }

private:
    static RWClassID myAtom;
    friend struct RWInit(RWDBForeignKey);
    friend RWCollectable* rwCreateFN(RWDBForeignKey)();

    RWDBCountedRef<RWDBForeignKeyImp> impl_;

    /**
     * \internal
     */
    RWDBForeignKey(RWDBForeignKeyImp* imp);
};

/**
 * \ingroup db_common_group
 *
 * \brief
 * Holds an ordered collection of RWDBForeignKey instances.
 *
 * RWDBForeignKeyList is an ordered collection of RWDBForeignKey instances.
 * RWDBForeignKeyList is a relatively low-level construct used by the DB
 * Interface Module as an input/output parameter in the functions
 * RWDBTable::foreignKeys() and RWDBTable::referredToBy().
 *
 * All RWDBForeignKeyList methods are inherited from RWOrdered.
 *
 * The only semantics that RWDBForeignKeyList adds to RWOrdered are:
 *
 * - The index operator operator[]() returns reference to RWDBForeignKey,
 * rather than reference to RWCollectable pointer.
 * - The destructor deallocates the contents of the RWDBForeignKeyList by
 * calling clearAndDestroy().
 *
 * \synopsis
 * #include <rw/db/forkey.h>
 * RWDBForeignKeyList aList;
 *
 * RWDBStatus aStatus = aTable.foreignKeys("targetTable", aList);
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBForeignKeyList : public RWOrdered
{
public:

    /**
     * The default constructor produces an empty RWDBForeignKeyList.
     */
    RWDBForeignKeyList();

    /**
     * Copy constructor. Makes a copy of \a aList.
     */
    RWDBForeignKeyList(const RWDBForeignKeyList& aList)
        : RWOrdered()
    {
        RWDBForeignKeyList tmpList;
        tmpList.resize(aList.entries());
        RWTScopedPointer<RWDBForeignKey> tmp(0);
        for (size_t i = 0; i < aList.entries(); ++i) {
            tmp.reset(new RWDBForeignKey(aList[i]));
            RW_SUPPRESS_CTOR_CALLS_VIRTUAL_FUNC_WARNING
            tmpList.append(tmp.get());
            RW_RESTORE_CTOR_CALLS_VIRTUAL_FUNC_WARNING
            tmp.release();
        }
        tmpList.swap(*this);
    }

    /**
     * Returns a reference to the RWDBForeignKey at a position \a index in
     * self. The call is forwarded to RWOrdered, which throws an exception
     * of type RWBoundsErr if the \a index is out of range.
     */
    RWDBForeignKey& operator[](size_t index) const;

    virtual ~RWDBForeignKeyList();

    /**
     * Assignment operator. Destroys existing contents and makes a copy of
     * \a aList.
     */
    RWDBForeignKeyList& operator=(const RWDBForeignKeyList& aList)
    {
        if (this != &aList) {
            RWDBForeignKeyList(aList).swap(*this);
        }
        return *this;
    }

    /**
     * Returns a deep copy of self.
     */
    RWDBForeignKeyList clone() const
    {
        RWDBForeignKeyList ret;
        ret.resize(entries());
        RWTScopedPointer<RWDBForeignKey> tmp(0);
        for (size_t i = 0; i < entries(); ++i) {
            tmp.reset((RWDBForeignKey*)((*this)[i].copy()));
            ret.append(tmp.get());
            tmp.release();
        }
        return ret;
    }
};

#endif
