#ifndef __RWDB_UNIQUECONSTRAINT_H__
#define __RWDB_UNIQUECONSTRAINT_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/uniqueconstr.h#1 $
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
#include <rw/ordcltn.h>
#include <rw/toolerr.h>
#include <rw/tools/pointer.h>

/**
 * \ingroup db_common_group
 *
 * \brief
 * Represents unique constraints, used when creating a database table or
 * fetching a database table schema.
 *
 * RWDBUniqueConstraint represents a table's unique constraints, used when
 * building up an RWDBSchema in preparation for an
 * RWDBDatabase::createTable() call. When creating a table, the instances of
 * RWDBColumn are used to define the set of columns that make up a unique
 * constraint.
 *
 * RWDBUniqueConstraint instances are also used as elements of lists that
 * are returned from RWDBTable::uniqueConstraints(). If the table columns in
 * the definition of the constraint can be obtained from the database, they
 * will be available via the methods operator[]() and column() when the
 * unique constraints are fetched via RWDBTable::uniqueConstraints().
 *
 * RWDBUniqueConstraint is designed around the Interface/Implementation
 * paradigm. An RWDBUniqueConstraint instance is an interface to a
 * reference-counted implementation; copy constructors and assignment
 * operators produce additional references to a shared implementation.
 */
class RWDB_GLOBAL RWDBUniqueConstraint : public RWCollectable
{
public:

    /**
     * Creates an empty RWDBUniqueConstraint. The object is not valid until
     * it contains at least one column.
     */
    RWDBUniqueConstraint();

    /**
     * Constructs a unique constraint. If \a constraintName is the empty
     * string, no name will be used when creating the table.
     */
    RWDBUniqueConstraint(const RWCString& constraintName);

    /**
     * Copy constructor. Self shares an implementation with \a constr.
     */
    RWDBUniqueConstraint(const RWDBUniqueConstraint& constr);

    /**
     * Destructor.
     */
    virtual ~RWDBUniqueConstraint();

    /**
     * Sets the constraint name of self to \a newName. Returns a reference
     * to self.
     *
     * \note
     * This does not change the name of the unique constraint on a table
     * that already exists in the database.
     */
    RWDBUniqueConstraint&  constraintName(const RWCString& newName);

    /**
     * Returns the constraint name of this unique constraint.
     */
    RWCString             constraintName() const;

    /**
     * Returns an RWCString representing self as a string based on the
     * format found in \a phrasebook.
     */
    RWCString             asString(const RWDBPhraseBook& phrasebook) const;

    /**
     * Creates a deep copy of the RWDBColumn \a col, using the
     * RWDBColumn::clone() method. Appends the copied column to self, and
     * returns it.
     */
    RWDBColumn            appendColumn(const RWDBColumn& col);

    /**
     * Assignment operator. Self shares an implementation with \a constr.
     * Returns a reference to self.
     */
    RWDBUniqueConstraint&  operator=(const RWDBUniqueConstraint& constr);

    /**
     * Compares self to \a constraint. Returns \c true if \a constraint and
     * self share the same implementation.
     */
    bool                  operator==(const RWDBUniqueConstraint& constraint) const;

    /**
     * Returns the RWDBColumn in self at position \a index. If the \a index
     * is out of range, returns an RWDBColumn with a status of
     * RWDBStatus::invalidPosition. Indexing into an empty
     * RWDBUniqueConstraint is treated as out of range. Note that the
     * returned RWDBColumn is not a deep copy; modifications to RWDBColumn
     * change the containing RWDBUniqueConstraint.
     */
    RWDBColumn            operator[](size_t index) const;

    /**
     * Returns the first RWDBColumn in self with the given \a name. If no
     * such column exists, returns an RWDBColumn with a status of
     * RWDBStatus::columnNotFound. Note that the returned RWDBColumn is not
     * a deep copy; modifications to RWDBColumn change the containing
     * RWDBUniqueConstraint.
     */
    RWDBColumn            operator[](const RWCString& name) const;

    /**
     * Returns a shallow copy of the column from self at the specified
     * \a index. If the \a index is out of range, returns an RWDBColumn
     * whose status is RWDBStatus::invalidPosition.
     */
    RWDBColumn            column(size_t index) const;

    /**
     * Returns a shallow copy of the column from self whose name matches the
     * given \a name. If there is no match, returns an RWDBColumn whose
     * status is RWDBStatus::columnNotFound.
     */
    RWDBColumn            column(const RWCString& name) const;

    /**
     * Returns a shallow copy of the column from self whose name matches the
     * given \a name, according to \a cc. If there is no match, returns an
     * RWDBColumn whose status is RWDBStatus::columnNotFound.
     */
    RWDBColumn            column(const RWCString& name,
                                 RWCString::caseCompare cc) const;
    /**
     * Returns the index of the first RWDBColumn in self with the given
     * \a name. Returns #RW_NPOS if no such column is found.
     */
    size_t                index(const RWCString& name) const;

    /**
     * Returns the index of the first column from self whose name matches
     * the given \a name, according to \a cc. If there is no match, returns
     * #RW_NPOS.
     */
    size_t                index(const RWCString& name,
                                RWCString::caseCompare cc) const;

    /**
     * Returns the index of the first RWDBColumn in self with the same name
     * as the name of the given \a column. Returns #RW_NPOS if no such
     * column is found.
     */
    size_t                index(const RWDBColumn& column) const;

    /**
     * Returns the number of RWDBColumn instances in self.
     */
    size_t                entries() const;

    /**
     * Returns \c false if self has no columns (i.e. entries()
     * <tt>== 0</tt>), otherwise returns \c true.
     */
    bool                  isValid() const;

    /**
     * Returns a deep copy of self.
     */
    RWDBUniqueConstraint  clone() const;

    /**
     * If \a c is an RWDBUniqueConstraint according to the method isA(),
     * compares the result of its asString() method to the result of this
     * RWDBUniqueConstraint object's asString() method using the default
     * \c phrasebook. Returns \c true if they are equal, otherwise returns
     * \c false. If \a c is not an RWDBUniqueConstraint, returns \c false.
     *
     * As a precondition, \a c is tested to determine if it is a null
     * pointer. If null, the method asserts in debug mode, and throws
     * RWInternalErr in optimized builds.
     */
    virtual bool          isEqual(const RWCollectable* c) const;

    /**
     * If \a c points to an RWDBUniqueConstraint, returns the result of
     * asString().\ref RWCString::compareTo() "compareTo(c->asString())"
     * using the default \c phrasebook. Throws an \b std::bad_cast exception
     * if \a c does not point to an RWDBUniqueConstraint.
     *
     * As a precondition, \a c is tested to determine if it is a null
     * pointer. If null, the method asserts in debug mode, and throws
     * RWInternalErr in optimized builds.
     */
    virtual int           compareTo(const RWCollectable* c) const;

    // collectable API methods
    /**
     * Returns asString().\ref RWCString::hash() "hash()".
     */
    virtual unsigned      hash() const;

    /**
     * Returns __RWDBUNIQUECONSTRAINT.
     */
    virtual RWClassID     isA() const;

    // any documentation for the following is in the base class
    RWspace               binaryStoreSize() const;
    virtual void          saveGuts(RWFile& file) const;
    virtual void          saveGuts(RWvostream& stream) const;
    virtual void          restoreGuts(RWFile& file);
    virtual void          restoreGuts(RWvistream& stream);
    virtual RWCollectable* newSpecies() const;
    virtual RWCollectable* copy() const;
    static RWClassID       classIsA();

    friend RWDB_SYMBOLIC RWvistream&
    operator>>(RWvistream& s, RWDBUniqueConstraint*& pCl);

    friend RWDB_SYMBOLIC RWFile&
    operator>>(RWFile& f, RWDBUniqueConstraint*& pCl);

    RW_INLINE_FRIEND
    RWvostream& operator<<(RWvostream& v, const RWDBUniqueConstraint& Cl)
    {
        Cl.recursiveSaveOn(v);
        return v;
    }

    RW_INLINE_FRIEND
    RWFile& operator<<(RWFile& f, const RWDBUniqueConstraint& Cl)
    {
        Cl.recursiveSaveOn(f);
        return f;
    }

    RW_INLINE_FRIEND
    RWvistream& operator>>(RWvistream& v, RWDBUniqueConstraint& Cl)
    {
        RWCollectable::recursiveRestoreFrom(v, &Cl);
        return v;
    }

    RW_INLINE_FRIEND
    RWFile& operator>>(RWFile& f, RWDBUniqueConstraint& Cl)
    {
        RWCollectable::recursiveRestoreFrom(f, &Cl);
        return f;
    }

private:
    static RWClassID myAtom;
    friend struct RWInit(RWDBUniqueConstraint);
    friend RWCollectable* rwCreateFN(RWDBUniqueConstraint)();

    /**
     * \internal
     */
    RWDBUniqueConstraint(RWDBUniqueConstraintImp* imp);
    RWDBCountedRef<RWDBUniqueConstraintImp> impl_;
};

#define RWDBUniqueConstraintListDEFAULT_CAPACITY 10

/**
 * \ingroup db_common_group
 *
 * \brief
 * Holds an ordered collection of RWDBUniqueConstraint instances.
 *
 * RWDBUniqueConstraintList is an ordered collection of RWDBUniqueConstraint
 * instances. RWDBUniqueConstraintList is used by the DB Interface Module as
 * an input/output parameter in the function RWDBTable::uniqueConstraints().
 * When the list is populated with instances of RWDBUniqueConstraint, the
 * instances are owned by the containing list. The destructor deallocates
 * the contents of the RWDBUniqueConstraintList by calling
 * clearAndDestroy().
 *
 * \synopsis
 * #include <rw/db/uniqueconstr.h>
 * RWDBUniqueConstraintList aList;
 *
 * aStatus = aTable.uniqueConstraints("aConstraintName", aList);
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBUniqueConstraintList
{
public:
    /**
     * Constructor.
     */
    RWDBUniqueConstraintList() : uniqueConstraintList_(RWDBUniqueConstraintListDEFAULT_CAPACITY) {}

    /**
     * Copy constructor. Makes a copy \a aList.
     */
    RWDBUniqueConstraintList(const RWDBUniqueConstraintList& aList)
        : uniqueConstraintList_(RWDBUniqueConstraintListDEFAULT_CAPACITY)
    {
        RWDBUniqueConstraintList tmpList;
        tmpList.uniqueConstraintList_.resize(aList.entries());
        RWTScopedPointer<RWDBUniqueConstraint> tmp(0);
        for (size_t i = 0; i < aList.entries(); ++i) {
            tmp.reset(new RWDBUniqueConstraint(aList[i]));
            tmpList.append(tmp.get());
            tmp.release();
        }
        tmpList.uniqueConstraintList_.swap(uniqueConstraintList_);
    }

    /**
     * Destructor. This <em>deletes</em> the objects in the list.
     */
    ~RWDBUniqueConstraintList()
    {
        clearAndDestroy();
    }

    /**
     * Returns a reference to the RWDBUniqueConstraint at a position
     * \a index in self. Throws RWBoundsErr if the \a index is out of range.
     */
    const RWDBUniqueConstraint& operator[](size_t index) const
    {
        return *static_cast<const RWDBUniqueConstraint*>(uniqueConstraintList_[index]);
    }

    /**
     * Returns a reference to the RWDBUniqueConstraint at a position
     * \a index in self. Throws RWBoundsErr if the \a index is out of range.
     */
    RWDBUniqueConstraint& operator[](size_t index)
    {
        return *static_cast<RWDBUniqueConstraint*>(uniqueConstraintList_[index]);
    }

    /**
     * Returns a reference to the RWDBUniqueConstraint at a position
     * \a index in self. Bounds checking is enabled by defining the
     * preprocessor directive \c RWBOUNDS_CHECK before including the header
     * file \c rw\\db\\uniqueconstr.h. In this case, throws RWBoundsErr if
     * the \a index is out of range.
     */
    const RWDBUniqueConstraint& operator()(size_t index) const
    {
        return *static_cast<const RWDBUniqueConstraint*>(uniqueConstraintList_(index));
    }

    /**
     * Returns a reference to the RWDBUniqueConstraint at a position
     * \a index in self. Bounds checking is enabled by defining the
     * preprocessor directive \c RWBOUNDS_CHECK before including the header
     * file \c rw\\db\\uniqueconstr.h. In this case, throws RWBoundsErr if
     * the \a index is out of range.
     */
    RWDBUniqueConstraint& operator()(size_t index)
    {
        return *static_cast<RWDBUniqueConstraint*>(uniqueConstraintList_(index));
    }

    /**
     * Returns the total number of items in the collection.
     */
    size_t entries() const
    {
        return uniqueConstraintList_.entries();
    }

    /**
     * Adds \a uc to the end of the collection and returns it. If
     * successful, self assumes ownership of \a uc. Returns #rwnil if the
     * insertion was unsuccessful.
     */
    RWDBUniqueConstraint* append(RWDBUniqueConstraint* uc)
    {
        RW_ASSERT(0 != uc);
        return static_cast<RWDBUniqueConstraint*>(uniqueConstraintList_.append(uc));
    }

    /**
     * Removes all objects from the collection <em>and deletes</em> them.
     * Takes into account duplicate objects within the collection and only
     * deletes them once. However, it does <em>not</em> take into account
     * objects shared with another collection.
     */
    void clearAndDestroy()
    {
        uniqueConstraintList_.clearAndDestroy();
    }

    /**
     * Removes all objects from the collection. Does not delete the objects
     * themselves.
     */
    void clear()
    {
        uniqueConstraintList_.clear();
    }

    /**
     * Removes the oject at the position \a index in the collection and
     * returns it. It is up to the user to delete the returned object.
     */
    RWDBUniqueConstraint* removeAt(size_t index)
    {
        return static_cast<RWDBUniqueConstraint*>(uniqueConstraintList_.removeAt(index));
    }

    RWDBUniqueConstraint* insert(RWDBUniqueConstraint* uc)
    {
        RW_ASSERT(0 != uc);
        return static_cast<RWDBUniqueConstraint*>(uniqueConstraintList_.insert(uc));
    }

    /**
     * Returns the number of bytes required to store self using the
     * saveGuts() method.
     */
    RWspace binaryStoreSize() const
    {
        return uniqueConstraintList_.recursiveStoreSize();
    }

    /**
     * Writes the contents of self to \a f.
     */
    void saveGuts(RWFile& f) const
    {
        f << uniqueConstraintList_;
    }

    /**
     * Writes the contents of self to \a s.
     */
    void saveGuts(RWvostream& s) const
    {
        s << uniqueConstraintList_;
    }

    /**
     * Reads \a f, replacing the contents of self.
     */
    void restoreGuts(RWFile& f)
    {
        f >> uniqueConstraintList_;
    }

    /**
     * Reads \a s, replacing the contents of self.
     */
    void restoreGuts(RWvistream& s)
    {
        s >> uniqueConstraintList_;
    }

    /**
     * Returns a new list that is a deep copy of self.
     */
    RWDBUniqueConstraintList clone() const
    {
        RWDBUniqueConstraintList ret;
        RWTScopedPointer<RWDBUniqueConstraint> tmp(0);
        for (size_t i = 0; i < uniqueConstraintList_.entries(); ++i) {
            tmp.reset(new RWDBUniqueConstraint((*this)[i].clone()));
            ret.append(tmp.get());
            tmp.release();
        }
        return ret;
    }

    /**
     * Assignment operator. Destroys contents of self and makes a copy of
     * \a aList.
     */
    RWDBUniqueConstraintList& operator=(const RWDBUniqueConstraintList& aList)
    {
        if (this != &aList) {
            RWDBUniqueConstraintList tmp(aList);
            tmp.uniqueConstraintList_.swap(uniqueConstraintList_);
        }
        return *this;
    }

private:

    RWOrdered uniqueConstraintList_;
};

/**
 * Saves \a obj to \a f.
 */
inline RWFile& operator<<(RWFile& f, const RWDBUniqueConstraintList& obj)
{
    obj.saveGuts(f);
    return f;
}

/**
 * Restores \a obj from \a f, replacing the previous contents of \a obj.
 */
inline RWFile& operator>>(RWFile& f, RWDBUniqueConstraintList& obj)
{
    obj.restoreGuts(f);
    return f;
}

/**
 * Saves \a obj to \a s.
 */
inline RWvostream& operator<<(RWvostream& s, const RWDBUniqueConstraintList& obj)
{
    obj.saveGuts(s);
    return s;
}

/**
 * Restores \a obj from \a s, replacing the previous contents of \a obj.
 */
inline RWvistream& operator>>(RWvistream& s, RWDBUniqueConstraintList& obj)
{
    obj.restoreGuts(s);
    return s;
}


#endif
