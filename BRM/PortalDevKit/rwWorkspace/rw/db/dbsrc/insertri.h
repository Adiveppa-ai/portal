#ifndef __RWDB_INSERTRI_H__
#define __RWDB_INSERTRI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/insertri.h#1 $
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
 * Definition of class RWDBInserterImp
 *
 * This is a base class for a family of database-specific inserter
 * implementations.  An inserter is an object used to insert data into
 * a database table.
 *
 **************************************************************************/

#include <rw/db/dbsrc/stmt.h>
#include <rw/db/connect.h>
#include <rw/db/dbref.h>
#include <rw/db/expr.h>
#include <rw/db/select.h>
#include <rw/db/status.h>
#include <rw/db/table.h>
#include <rw/bitvec.h>
#include <rw/ordcltn.h>

//////////////////////////////////////////////////////////////////////////
//
// RWDBInserterEntryList
//    a list of RWDBInserterEntry
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBInserterEntryList
    : public RWOrdered
{
public:
    RWDBInserterEntryList(size_t size = RWCollection::DEFAULT_CAPACITY)
        : RWOrdered(size)
    { }
    virtual ~RWDBInserterEntryList()
    {
        RWOrdered::clearAndDestroy();
    }
};
//////////////////////////////////////////////////////////////////////////
//
// RWDBInserterEntry
//    Contents of valueList_.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBInserterEntry
    : public RWCollectable
{
public:
    RWDBInserterEntry();
    RWDBInserterEntry(const RWCString& asStr);
    RWDBInserterEntry(const RWDBExpr& sc);
    RWDBInserterEntry(const RWDBBoundExpr& sc);
    RWDBInserterEntry(RWDBAbstractBuffer* buf);
    RWDBInserterEntry(RWDBValue::ValueType vt,
                      size_t cacheSize,
                      size_t capacity,
                      const RWDBBufferFactory& factory);
    RWDBInserterEntry(RWDBValue::ValueType vt,
                      const RWDBColumn& col,
                      size_t cacheSize,
                      size_t capacity,
                      const RWDBBufferFactory& factory);
    virtual ~RWDBInserterEntry();

    RWCString                  name() const;
    void                       setName(const RWCString& n,
                                       bool pushNameToBuffer = false);
    RWDBExpr                   expr() const;
    RWDBAbstractBuffer*        buffer() const;
    RWCString                  asString() const;
    void                       setAsString(const RWCString& str);

    bool                  checkScalar(const RWDBExpr& s) const;
    bool                  checkScalar(const RWDBBoundExpr& s) const;
    bool                  checkValue(size_t capacity) const;

    void                       scalar(const RWDBExpr& scalar);
    void                       scalar(const RWDBBoundExpr& scalar);
    void                       value(const RWDBValue& value,
                                     size_t index,
                                     size_t cacheSize,
                                     size_t capacity,
                                     bool emptyStringIsNull,
                                     const RWDBBufferFactory& factory);
    bool                  hasScalar() const;
    bool                  hasBuffer() const;

    static void                clearScalar(RWCollectable* c, void*);

    // to make the entry a collectable
    int                        compareTo(const RWCollectable*) const;
    unsigned                   hash() const;
    bool                  isEqual(const RWCollectable*) const;

private:
    RWDBLocalRecursiveMutex    mutex_;
    RWCString                  asString_;
    RWCString                  name_;
    RWDBColumn                 columnInfo_;
    bool                  hasColumnInfo_;
    RWTScopedPointer<RWDBExpr> expr_;
    RWDBAbstractBuffer*        buff_;
    bool                  pushNameToBuffer_;

    // not implemented:
    RWDBInserterEntry(const RWDBInserterEntry& entry);
    RWDBInserterEntry& operator=(const RWDBInserterEntry& entry);
};

//////////////////////////////////////////////////////////////////////////
//
// RWDBInserterImp
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBInserterImp
    : public RWDBReference,
      public RWDBStatus
{
public:
    RWDBInserterImp(const RWDBStatus& status);
    RWDBInserterImp(const RWDBStatus& status,
                    const RWDBTable& table,
                    const RWDBSelectorBase& selector,
                    const RWDBSchema& columnList,
                    const RWDBStatement& = RWDBStatement());
    virtual ~RWDBInserterImp();

    virtual void               initialize(const RWDBSchema& columnList);

    // accessors
    virtual RWDBTable          table() const;

    // for SQL expansion
    virtual RWCString          asString(const RWZone& timeZone,
                                        bool verbose = false);

    virtual const RWDBPhraseBook& phraseBook() const;

    // for execution
    virtual RWDBResult         execute(const RWDBConnection& conn);
    virtual RWDBResult         flush();

    virtual void               cancel(const RWDBConnection& conn,
                                      RWDBStatus&     status);
    virtual void               parse(const RWDBConnection& conn,
                                     RWDBStatus&     status);
    virtual void               bind(const RWDBConnection& conn,
                                    RWDBStatus&     status);
    virtual RWDBResult         perform(const RWDBConnection& conn,
                                       RWDBStatus&     status);
    virtual RWDBStatus         clear();

    virtual RWDBStatementImp*  statement() const;

    virtual size_t             position() const;

    // for modifying scalar expressions
    virtual void               addScalar(const RWDBExpr& scalar);
    virtual void               addScalar(const RWDBBoundExpr& scalar);
    virtual void               addValue(const RWDBValue& scalar, size_t capacity);
    virtual void               addConstant(const RWCString& asStr);
    virtual size_t             position(const RWCString& name);
    virtual size_t             index(const RWCString&);

    virtual bool               hasSchema() const;

    virtual void  addTypeInfo(RWDBAbstractBuffer* /*buffer*/,
                              RWCString& /*placeholder*/,
                              size_t /*entries*/) const
    { }

    // Thread safety operations
    void acquire() const
    {
        const_cast<RWDBLocalRecursiveMutex*>(&mutex_)->acquire();
    }

    void release() const
    {
        const_cast<RWDBLocalRecursiveMutex*>(&mutex_)->release();
    }

private:
    // Thread safety
    RWDBLocalRecursiveMutex    mutex_;

protected:
    RWDBConnection             conn_;

    // Do not dereference. RWZone it points may have been destructed.
    const RWZone*              lastExecZone_;

    RWDBTable                  table_;
    RWDBSelectorBase           selector_;
    RWDBInserterEntryList      scalarList_;

    RWBitVec                   shiftedInto_;
    RWBitVec                   lastShiftedInto_;
    RWBitVec                   boundExprLocations_;

    RWCString                  sql_;
    bool                       changed_;        // has the state changed?

    RWDBStatement              statement_;

    size_t                     position_;
    size_t                     cacheSize_;
    size_t                     cachedRows_;

    virtual void flushAndPrepareForNextExecute(size_t capacity);
    virtual const RWDBBufferFactory& bufferFactory() const;

private:
    // not implemented:
    RWDBInserterImp(const RWDBInserterImp& inserter);
    RWDBInserterImp& operator=(const RWDBInserterImp& inserter);
};

//////////////////////////////////////////////////////////////////////////
//
// RWDBCachedInserterImp
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBCachedInserterImp
    : public RWDBInserterImp
{
public:
    RWDBCachedInserterImp(const RWDBStatus& status);
    RWDBCachedInserterImp(const RWDBStatus& status,
                          const RWDBTable& table,
                          const RWDBSelectorBase& selector,
                          const RWDBSchema& columnList,
                          size_t cache,
                          const RWDBStatement& = RWDBStatement());

    virtual ~RWDBCachedInserterImp();

    virtual RWDBResult         execute(const RWDBConnection& conn);
    virtual RWDBResult         flush();

    virtual RWDBResult         perform(const RWDBConnection& conn,
                                       RWDBStatus&     status);

protected:

    RWDBResult                 deferedResult_;

private:
    // not implemented:
    RWDBCachedInserterImp(const RWDBCachedInserterImp&);
    RWDBCachedInserterImp& operator=(const RWDBCachedInserterImp&);
};


#endif
