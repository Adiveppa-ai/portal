#ifndef __RWDB_TPMEMTAB_H__
#define __RWDB_TPMEMTAB_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/tpmemtab.h#1 $
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
#include <rw/db/tmtbase.h>


#if defined(RW_NO_TEMPLATES) || defined(RW_BROKEN_TEMPLATES)
#  error The template in tpmemtab.h cannot be used with your compiler!
#endif

/**
 * \ingroup db_utility_and_diagnostics_group
 *
 * \brief
 * Represents a parameterized memory table.
 *
 * This class represents a parameterized memory table. Not only can the type
 * of the object inserted into the memory table be parameterized, but also
 * the implementation.
 *
 * Parameter \c T represents the type of the object to be stored in the
 * memory table. It can be a class or a built-in type. The class must have:
 *
 * - Well-defined copy semantics (<tt>T::T(const T&)</tt> or the equivalent)
 * - Well-defined assignment semantics (<tt>T::operator=(const T&)</tt> or
 * the equivalent)
 * - Any other semantics required by class \c C. For Rogue Wave collections,
 * this includes a default constructor.
 * - A friend function to map the columns read by an RWDBReader to the
 * elements of \c T:
 * \code
 * friend RWDBReader& operator>>(const RWDBReader&, const T&)
 * \endcode
 *
 * Parameter \c C represents the pointer- based template collection used as
 * the implementation of the memory table. It must have:
 *
 * - A well-defined <tt>void insert(T*)</tt> method
 * - A well-defined <tt>T* %operator[](size_t)</tt> method
 * - A well-defined <tt>size_t %entries()</tt> method
 *
 * Possible choices for \c C are classes RWTPtrSlist and RWTPtrOrderedVector
 * of the Essential Tools Module.
 *
 * The constructors for the class dynamically allocate space for the
 * elements of type \c T that are placed in the collection. It is the
 * application's responsibility to free this memory when the
 * RWDBTPtrMemTable goes out of scope. An effective way to do this is to
 * have the collection class \c C call <tt>operator delete</tt> on each of
 * the entries in its destructor.
 *
 * \synopsis
 * #include <rw/db/tpmemtab.h>
 *
 * RWDBTPtrMemTable<T, C> mt;
 * \endsynopsis
 */
template <class T, class C>
class RWDBTPtrMemTable : public C, public RWDBTMemTableBase
{
public:
    /**
     * Constructor that builds an empty instance with an upper limit of
     * \a maxElements. If \a maxElements is zero, no upper limit is imposed
     * on the number of elements in the memory table.
     */
    RWDBTPtrMemTable(size_t maxElements = 0);

    /**
     * Constructor that builds an instance with an upper limit of
     * \a maxElements. If \a maxElements is zero, no upper limit is imposed
     * on the number of elements in the memory table. After building the
     * memory table, an RWDBReader instance is created on the \a table. From
     * this reader, up to \a maxElements instances of class \c T are
     * allocated and inserted into the memory table. It is the application's
     * responsibility to free the memory associated with the table.
     */
    RWDBTPtrMemTable(const RWDBTable& table, size_t maxElements = 0);

    /**
     * Constructor that builds an instance with an upper limit of
     * \a maxElements. If \a maxElements is zero, no upper limit is imposed
     * on the number of elements in the memory table. After building the
     * memory table, an RWDBReader instance, using the connection specified
     * by \a connection, is created on the \a table. From this reader, up to
     * \a maxElements instances of class \c T are allocated and inserted
     * into the memory table. It is the application's responsibility to free
     * the memory associated with the table.
     */
    RWDBTPtrMemTable(const RWDBTable& table, const RWDBConnection& connection,
                     size_t maxElements = 0);

    /**
     * Constructor that builds an instance with an upper limit of
     * \a maxElements. If \a maxElements is zero, no upper limit is imposed
     * on the number of elements in the memory table. After building the
     * memory table, an RWDBReader instance is created on the \a selector.
     * From this reader, up to \a maxElements instances of class \c T are
     * allocated and inserted into the memory table. It is the application's
     * responsibility to free the memory associated with the table.
     */
    RWDBTPtrMemTable(const RWDBSelectorBase& selector, size_t maxElements = 0);

    /**
     * Constructor that builds an instance with an upper limit of
     * \a maxElements. If \a maxElements is zero, no upper limit is imposed
     * on the number of elements in the memory table. After building the
     * memory table, an RWDBReader instance, using the connection specified
     * by \a connection, is created on the \a selector. From this reader, up
     * to \a maxElements instances of class \c T are allocated and inserted
     * into the memory table. It is the application's responsibility to free
     * the memory associated with the table.
     */
    RWDBTPtrMemTable(const RWDBSelectorBase& selector,
                     const RWDBConnection& connection, size_t maxElements = 0);

    /**
     * Constructor that builds an instance with an upper limit of
     * \a maxElements. If \a maxElements is zero, no upper limit is imposed
     * on the number of elements in the memory table. After building the
     * memory table, the RWDBReader instance \a reader is used to allocate
     * and insert into the memory table up to \a maxElements instances of
     * class \c T. It is the application's responsibility to free the memory
     * associated with the table.
     */
    RWDBTPtrMemTable(RWDBReader& reader, size_t maxElements = 0);

    virtual ~RWDBTPtrMemTable();

    /**
     * Returns number of rows in self. Uses user-defined method
     * <tt>C::entries()</tt>.
     */
    size_t entries();

    /**
     * Returns a pointer to the \c T* in self at position \a index. Uses
     * user-defined operator <tt>T* C::operator[](size_t index)</tt>.
     */
    T* operator[](size_t index);

protected:
    bool readRow(RWDBReader& reader);
};

#ifdef RW_COMPILE_INSTANTIATE
#  include <rw/db/tpmemtab.cc>
#endif

#endif
