/***************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/tpmemtab.cc#1 $
 *
 * Template definitions for RWTPtrMemTable<T,C>
 *    This memory table is parameterized on T, the type of object
 *    which is a 'row' of the table, and C, the collection class
 *    which implements the table.
 * See the class reference for restrictions on T and C
 *
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

//////////////////////////////////////////////////////////////////////////
//
// RWDBTPtrMemTable constructors, destructor, operator=
//
//////////////////////////////////////////////////////////////////////////
template <class T, class C>
RWDBTPtrMemTable<T, C>::RWDBTPtrMemTable(size_t max)
    : RWDBTMemTableBase(max)
{
    ;
}
template <class T, class C>
RWDBTPtrMemTable<T, C>::RWDBTPtrMemTable(const RWDBTable& t, size_t max)
    : RWDBTMemTableBase(t.status(), max)
{
    RWDBReader aReader = t.reader();
    populate(aReader);
}
template <class T, class C>
RWDBTPtrMemTable<T, C>::RWDBTPtrMemTable(const RWDBTable& t,
        const RWDBConnection& aConn,
        size_t max)
    : RWDBTMemTableBase(t.status(), max)
{
    RWDBReader aReader = t.reader(aConn);
    populate(aReader);
}
template <class T, class C>
RWDBTPtrMemTable<T, C>::RWDBTPtrMemTable(const RWDBSelectorBase& selector,
        size_t max)
    : RWDBTMemTableBase(selector.status(), max)
{
    RWDBReader aReader = selector.reader();
    populate(aReader);
}
template <class T, class C>
RWDBTPtrMemTable<T, C>::RWDBTPtrMemTable(const RWDBSelectorBase& selector,
        const RWDBConnection& aConn,
        size_t max)
    : RWDBTMemTableBase(selector.status(), max)
{
    RWDBReader aReader = selector.reader(aConn);
    populate(aReader);
}
template <class T, class C>
RWDBTPtrMemTable<T, C>::RWDBTPtrMemTable(RWDBReader& r, size_t max)
    : RWDBTMemTableBase(r.status(), max)
{
    populate(r);
}
template <class T, class C>
RWDBTPtrMemTable<T, C>::~RWDBTPtrMemTable()
{
    ;
}


//////////////////////////////////////////////////////////////////////////
//
// RWDBTPtrMemTable<T,C>:: entries()
//
//////////////////////////////////////////////////////////////////////////
template <class T, class C>
size_t
RWDBTPtrMemTable<T, C>::entries()
{
    return C::entries();
}

//////////////////////////////////////////////////////////////////////////
//
// RWDBTPtrMemTable<T,C>:: operator[]
//
//////////////////////////////////////////////////////////////////////////
template <class T, class C>
T*
RWDBTPtrMemTable<T, C>::operator[](size_t i)
{
    return C::operator[](i);
}

//////////////////////////////////////////////////////////////////////////
//
// RWDBTPtrMemTable<T,C>::readRow()
//
//////////////////////////////////////////////////////////////////////////
template <class T, class C>
bool
RWDBTPtrMemTable<T, C>::readRow(RWDBReader& aReader)
{
    if (maxAllowedSize_ != 0 && entries() >= maxAllowedSize_) {
        return false;
    }
    if (!aReader()) {
        return false;
    }
    RWTScopedPointer<T> aTPtr(new T);
    aReader >> *aTPtr;
    this->insert(aTPtr.get());
    aTPtr.release();
    return true;
}
