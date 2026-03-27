#ifndef __RWDB_STOREDI_H__
#define __RWDB_STOREDI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/storedi.h#1 $
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
 * Definition of class RWDBStoredProcImp
 *
 * This is a base class for a family of database-specific stored procedure
 * implementations.
 *
 **************************************************************************/

#include <rw/db/dbsrc/insertri.h>
#include <rw/db/dbsrc/stmt.h>
#include <rw/db/connect.h>
#include <rw/db/dbase.h>
#include <rw/db/dbref.h>
#include <rw/db/expr.h>
#include <rw/db/schema.h>
#include <rw/db/select.h>
#include <rw/db/stored.h>
#include <rw/db/table.h>
#include <rw/bitvec.h>
#include <rw/ordcltn.h>

class RWDBStoredProcEntry;

//////////////////////////////////////////////////////////////////////////
//
// RWDBStoredProcImp
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBStoredProcImp
    : public RWDBReference,
      public RWDBStatus
{
public:
    RWDBStoredProcImp(const RWDBStatus& status);
    RWDBStoredProcImp(const RWDBStatus& status,
                      const RWDBDatabase& database,
                      const RWCString& name,
                      const RWDBStatement& = RWDBStatement());
    RWDBStoredProcImp(const RWDBStatus& status,
                      const RWDBDatabase& database,
                      const RWCString& name,
                      const RWDBSchema& params,
                      const RWCString& text,
                      const RWDBStatement& = RWDBStatement());
    virtual ~RWDBStoredProcImp();

    virtual void               initialize(const RWDBSchema& columnList);

    // for SQL expansion
    virtual RWCString          asString(const RWZone& timeZone);

    virtual const RWDBPhraseBook& phraseBook() const;

    // for execution
    RWDBResult                 execute(const RWDBConnection& conn);
    void                       cancel(const RWDBConnection& conn,
                                      RWDBStatus&     status);
    void                       parse(const RWDBConnection& conn,
                                     RWDBStatus&     status);
    virtual void               bind(const RWDBConnection& conn,
                                    RWDBStatus&     status);
    RWDBResult                 perform(const RWDBConnection& conn,
                                       RWDBStatus&     status);

    virtual RWDBStatus         fetchReturnParams();
    virtual RWDBValue          returnValue() const;
    virtual RWDBColumn         returnValueColumn() const;

    virtual RWDBStatus         clear();

    virtual void               clearCache(RWDBStoredProc::CacheType cache);

    RWDBStatementImp*          statement() const;

    //DDL methods
    RWCString                  text(bool forceLookup);
    RWCString                  text(const RWDBConnection& conn,
                                    bool forceLookup);

    RWDBSchema                 params(bool forceLookup);
    RWDBSchema                 params(const RWDBConnection& conn,
                                      bool forceLookup);

    bool                       exists(bool forceLookup);
    bool                       exists(const RWDBConnection& conn,
                                      bool forceLookup);

    virtual RWDBStatus         drop(const RWDBConnection& conn);

    // implemented in access modules
    virtual bool               doExists(const RWDBConnection&,
                                        RWDBStoredProcEntry*)
    {
        return false;
    }
    virtual void               doInitialize(const RWDBSchema& columnList,
                                            RWDBStoredProcEntry* entry);
    virtual RWDBSchema         doParams(const RWDBConnection&,
                                        RWDBStoredProcEntry*)
    {
        return RWDBSchema(pattern());
    }
    virtual RWCString          doText(const RWDBConnection&,
                                      RWDBStoredProcEntry*)
    {
        return RWCString();
    }

    // for modifying scalar expressions
    virtual void               addScalar(const RWDBExpr& scalar,
                                         RWDBColumn::ParamType paramType);
    virtual void               addScalar(const RWDBBoundExpr& scalar,
                                         RWDBColumn::ParamType paramType);
    virtual void               addValue(const RWDBValue& scalar,
                                        size_t capacity,
                                        RWDBColumn::ParamType paramType);
    virtual void               addConstant(const RWCString& asStr);
    virtual size_t             position() const
    {
        return position_;
    }
    virtual size_t             position(const RWCString& name);
    virtual size_t             position(size_t position);
    virtual size_t             index(const RWCString& name);

    //accessors
    RWDBDatabase               database() const;
    RWCString                  name() const;
    bool                       isNull(size_t index) const;

    void acquire() const
    {
        const_cast<RWDBLocalRecursiveMutex*>(&mutex_)->acquire();
    }

    void release() const
    {
        const_cast<RWDBLocalRecursiveMutex*>(&mutex_)->release();
    }

private:
    // Mutex lock should be first to protect any data members if needed.
    RWDBLocalRecursiveMutex    mutex_;

    void checkParams();
    RWCString getText(const RWDBConnection*, bool);
    RWDBSchema getParams(const RWDBConnection*, bool);
    bool getExists(const RWDBConnection*, bool);

protected:
    enum Exists { Yes, No, DontKnow };

    RWOrdered                  scalarList_;
    RWBitVec                   shiftedInto_;
    RWBitVec                   lastShiftedInto_;
    bool                       executed_;

    RWCString                  sql_;
    RWCString                  name_;
    RWCString                  text_;
    RWDBSchema                 paramSchema_;

    size_t                     position_;
    bool                       changed_;        // has the state changed?

    RWDBStatement              statement_;

    Exists exists_;
    bool schemaFetched_;
    enum { Function, Procedure } procedureType_;
    RWTScopedPointer<RWDBInserterEntry> returnValue_;
    RWDBConnection conn_;

    virtual const RWDBBufferFactory& bufferFactory() const;
    virtual void returnValueColumn(const RWDBColumn& retCol);
private:
    /**
     * \internal
     * If there is a cache manager, obtain an entry with this name() from
     * the cache and update local variables with the data contained in the
     * cache.
     */
    RWDBStoredProcEntry getCachedData();

    /**
     * \internal
     * If there is a cache manager, store the data contained in \a entry
     * with label name(). If there is a pre-existing entry in the cache,
     * update it with the data contained in \a entry.
     */
    void setCachedData(const RWDBStoredProcEntry& entry);

    // not implemented:
    RWDBStoredProcImp(const RWDBStoredProcImp&);
    RWDBStoredProcImp& operator=(const RWDBStoredProcImp&);

    RWDBDatabase               database_;

    // Do not dereference. RWZone it points may have been destructed.
    const RWZone*              lastExecZone_;
};

#endif
