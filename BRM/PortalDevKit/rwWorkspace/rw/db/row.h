#ifndef __RWDB_ROW_H__
#define __RWDB_ROW_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/row.h#1 $
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
 * Declaration of class RWDBRow
 *
 * Provides an object that represents a row from a table.
 *
 **************************************************************************/

#include <rw/db/dbref.h>
#include <rw/db/defs.h>
#include <rw/db/value.h>
#include <rw/ordcltn.h>

/**
 * \ingroup db_utility_and_diagnostics_group
 *
 * \brief
 * An ordered collection of RWDBValue instances.
 *
 * RWDBRow is an ordered collection of RWDBValue objects. RWDBRow is a
 * relatively low level construct used by the DB Interface Module to store a
 * row of data on its way to or from the database. It is visible to
 * applications for two reasons:
 *
 * - An RWDBRow is a single row of an RWDBMemTable.
 *
 * - Some applications may want to manage raw data without knowing anything
 * about its structure. RWDBRow can be used as a container in these cases.
 *
 * The only semantics that RWDBRow adds to RWCollectable are:
 *
 * - The index operator operator[]() return \ref RWDBValue "RWDBValue&",
 * rather than \ref RWCollectable "RWCollectable*&".
 *
 * - The destructor deallocates the contents of the RWDBRow by calling
 * clearAndDestroy().
 *
 * RWDBRow is designed around the Interface/Implementation paradigm. An
 * RWDBRow instance is an interface to a reference-counted implementation;
 * copy constructors and assignment operators produce additional references
 * to a shared implementation.
 *
 * \synopsis
 * #include <rw/db/row.h>
 *
 * RWDBRow& r = myMemTable[i];
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBRow : public RWCollectable
{
public:
    /**
     * The default constructor produces an empty RWDBRow.
     */
    RWDBRow();

    /**
     * Copy constructor. The created RWDBRow shares an implementation with
     * \a rvalue.
     */
    RWDBRow(const RWDBRow& rvalue);

    /**
     * The default destructor.
     */
    virtual ~RWDBRow();

    /**
     * Assignment operator. Returns reference to self which shares an
     * implementation with \a rvalue.
     */
    RWDBRow&         operator=(const RWDBRow& rvalue);

    /**
     * Returns a reference to the RWDBValue at position \a index in the
     * collection. Throws an exception of type RWBoundsErr if \a index is
     * out of range.
     */
    RWDBValue&       operator[](size_t index) const;

    bool             operator==(const RWDBRow& rhs) const;

    /**
     * Appends \a value to self.
     */
    virtual void     append(const RWDBValue& value);

    /**
     * Returns the total number of values in the collection.
     */
    virtual size_t   entries() const;

    /**
     * Removes all values from the collection and deletes them.
     */
    virtual void     clearAndDestroy();

    /**
     * If \a c points to an RWDBRow, this method returns:
     *
     * - \c 0, if self and \a c share the same implementation
     * - \c >0, if self has length greater than \a c
     * - \c <0, if \a c has length greater than self
     *
     * If self and \a c do not share the same implementation and both have
     * the same length, compares each RWDBValue in self with each value in
     * \a c. Returns \c 0 if all values compare equal, otherwise returns the
     * result of the first comparison that does not return \c 0.
     *
     * If \a c does not point to an RWDBRow, throws an \b std::bad_cast
     * exception.
     *
     * As a precondition, \a c is tested to determine if it is a null
     * pointer. If null, the method asserts in debug mode, and throws
     * RWInternalErr in optimized builds.
     */
    virtual int      compareTo(const RWCollectable* c) const;

    /**
     * Returns \c true if \ref compareTo() "compareTo(c)" <tt>== 0</tt>,
     * otherwise returns \c false.
     */
    virtual bool     isEqual(const RWCollectable* c) const;

    /**
     * Returns a hash value for use in collection classes.
     */
    virtual unsigned hash() const;

    /**
     * Returns the number of bytes required to store self.
     */
    RWspace          binaryStoreSize() const;

    /**
     * Writes the contents of self to \a file.
     */
    virtual void     saveGuts(RWFile& file) const;

    /**
     * Writes the contents of self to \a stream.
     */
    virtual void     saveGuts(RWvostream& stream) const;

    /**
     * Reads \a file, replacing the contents of self.
     */
    virtual void     restoreGuts(RWFile& file);

    /**
     * Reads \a stream, replacing the contents of self.
     */
    virtual void     restoreGuts(RWvistream& stream);

    RWOrdered*       ordered() const;

    /**
     * Redefined from class RWCollectable. Returns __RWDBROW.
     */
    virtual RWClassID isA() const;

    // any documentation for the following is in the base class
    virtual RWCollectable* newSpecies() const;
    virtual RWCollectable* copy() const;
    static RWClassID       classIsA();

    friend RWDB_SYMBOLIC RWvistream&
    operator>>(RWvistream& s, RWDBRow*& pCl);

    friend RWDB_SYMBOLIC RWFile&
    operator>>(RWFile& f, RWDBRow*& pCl);

    RW_INLINE_FRIEND
    RWvostream& operator<<(RWvostream& v, const RWDBRow& Cl)
    {
        Cl.recursiveSaveOn(v);
        return v;
    }

    RW_INLINE_FRIEND
    RWFile& operator<<(RWFile& f, const RWDBRow& Cl)
    {
        Cl.recursiveSaveOn(f);
        return f;
    }

    RW_INLINE_FRIEND
    RWvistream& operator>>(RWvistream& v, RWDBRow& Cl)
    {
        RWCollectable::recursiveRestoreFrom(v, &Cl);
        return v;
    }

    RW_INLINE_FRIEND
    RWFile& operator>>(RWFile& f, RWDBRow& Cl)
    {
        RWCollectable::recursiveRestoreFrom(f, &Cl);
        return f;
    }

private:
    static RWClassID myAtom;
    friend struct RWInit(RWDBRow);
    friend RWCollectable* rwCreateFN(RWDBRow)();

    RWDBCountedRef<RWDBRowImp> impl_;
};
#endif
