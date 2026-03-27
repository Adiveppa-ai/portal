#ifndef __RWDB_MEMTABI_H__
#define __RWDB_MEMTABI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/memtabi.h#1 $
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

#include <rw/db/dbsrc/tablei.h>
#include <rw/db/row.h>
#include <rw/tpordvec.h>


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class RWDBRowVect : public RWTPtrOrderedVector<RWDBRow>
{
public:
    RWDBRowVect(unsigned i);
private:
    RWDBRowVect(const RWDBRowVect& r);
    RWDBRowVect operator=(const RWDBRowVect& r);
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBMemTableImp : public RWDBTableImp
{
public:
    RWDBMemTableImp(const RWDBStatus&, const RWDBSchema&, size_t);
    RWDBMemTableImp(const RWDBStatus&, RWDBReader&, size_t);

    virtual ~RWDBMemTableImp();

    virtual size_t           entries() const;
    virtual RWDBRow&         row(size_t);
    virtual void             depopulate();
    virtual bool        populate(RWDBReader&);

    virtual RWDBReaderImp*   readerImp(const RWDBTable&, size_t);
    virtual RWDBReaderImp*   readerImp(const RWDBTable&, const RWDBConnection&, size_t);

    void                     insert(RWDBRow*);

    virtual RWDBSchema describe(RWDBTable::Metadata, const RWDBConnection*);
protected:
    RWDBRowVect              theRows_;
    size_t                   maxAllowedSize;

    bool                readRow(RWDBReader&);

private:
    // not implemented:
    RWDBMemTableImp(const RWDBMemTableImp&);
    RWDBMemTableImp& operator=(const RWDBMemTableImp&);
};

#endif
