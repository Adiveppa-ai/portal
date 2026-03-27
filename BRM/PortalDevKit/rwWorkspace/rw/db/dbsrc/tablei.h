#ifndef __RWDB_TABLEI_H__
#define __RWDB_TABLEI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/tablei.h#1 $
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
#include <rw/db/dbsrc/taggen.h>
#include <rw/db/dbase.h>
#include <rw/db/dbref.h>
#include <rw/db/forkey.h>
#include <rw/db/schema.h>
#include <rw/db/status.h>
#include <rw/db/table.h>


//////////////////////////////////////////////////////////////////////////
//
//  RWDBTableImp
//
//////////////////////////////////////////////////////////////////////////
class RWDBBulkInserterImp;
class RWDBBulkReaderImp;

class RWDB_GLOBAL RWDBTableImp
    : public RWDBReference,
      public RWDBStatus
{
public:
    RWDBTableImp(const RWDBStatus& status);
    RWDBTableImp(const RWDBStatus& status, const RWDBDatabase& db,
                 const RWCString& name);
    RWDBTableImp(const RWDBStatus& status, const RWDBDatabase& db,
                 const RWCString& name, const RWDBSchema& sch);
    virtual ~RWDBTableImp();

    // indexing
    virtual RWDBColumn   column(size_t position) const;
    virtual RWDBColumn   column(const RWCString& name) const;
    virtual RWDBColumn   column(const RWCString& name,
                                RWCString::caseCompare caseCompare) const;
    virtual RWDBColumn   operator[](const RWCString& name) const;

    virtual RWDBColumn   identityColumn() const;

    virtual size_t       index(const RWCString& name) const;
    virtual size_t       index(const RWCString& name,
                               RWCString::caseCompare caseCompare) const;
    virtual size_t       index(const RWDBColumn& column) const;

    // accessors
    virtual size_t       numberOfColumns() const;
    virtual RWDBDatabase database() const;
    virtual RWCString    name() const;
    virtual RWCString    tag() const;

    // mutators
    virtual void         name(const RWCString&);
    virtual void         tag(const RWCString& newtag);
    virtual void         schema(const RWDBSchema& newschema);
    virtual RWDBSchema   schema();

    // DDL support
    virtual RWDBStatus   referredToBy(const RWDBConnection& conn,
                                      RWDBForeignKeyList& keyList);
    virtual RWDBStatus   referredToBy(RWDBForeignKeyList& keyList);

    virtual RWDBStatus   foreignKeys(const RWDBConnection& conn,
                                     const RWCString& refName,
                                     RWDBForeignKeyList& keyList);
    virtual RWDBStatus   foreignKeys(const RWCString& refName,
                                     RWDBForeignKeyList& keyList);

    virtual RWDBStatus   checkConstraints(const RWDBConnection& conn,
                                          const RWCString& cName,
                                          RWDBCheckConstraintList& list);

    virtual RWDBStatus   checkConstraints(const RWCString& cName,
                                          RWDBCheckConstraintList& list);

    virtual RWDBStatus   uniqueConstraints(const RWDBConnection& conn,
                                           const RWCString& cName,
                                           RWDBUniqueConstraintList& list);
    virtual RWDBStatus   uniqueConstraints(const RWCString& cName,
                                           RWDBUniqueConstraintList& list);

    virtual RWDBPrimaryKey primaryKey(const RWDBConnection&);
    virtual RWDBPrimaryKey primaryKey();

    virtual RWDBSchema describe(RWDBTable::Metadata, const RWDBConnection*);

    virtual bool         existsAllocateConnection(bool forceLookup);
    virtual bool         exists(const RWDBConnection& connection,
                                bool forceLookup);

    virtual bool         isViewAllocateConnection();
    virtual bool         isView(const RWDBConnection& conn);

    virtual RWDBStatus   addColumn(const RWDBColumn& aCol,
                                   const RWDBConnection& conn);

    virtual RWDBStatus   dropColumn(const RWDBColumn& aCol,
                                    const RWDBConnection& conn);

    virtual RWDBStatus   addConstraint(const RWDBPrimaryKey& pk,
                                       const RWDBConnection& conn);
    virtual RWDBStatus   addConstraint(const RWDBForeignKey& fk,
                                       const RWDBConnection& conn);
    virtual RWDBStatus   addConstraint(const RWDBCheckConstraint& cc,
                                       const RWDBConnection& conn);
    virtual RWDBStatus   addConstraint(const RWDBUniqueConstraint& uc,
                                       const RWDBConnection& conn);

    virtual RWDBStatus   dropConstraint(const RWCString& constraintName,
                                        const RWDBConnection& conn);
    virtual RWDBStatus   dropConstraint(const RWDBPrimaryKey& pk,
                                        const RWDBConnection& conn);
    virtual RWDBStatus   dropConstraint(const RWDBForeignKey& fk,
                                        const RWDBConnection& conn);
    virtual RWDBStatus   dropConstraint(const RWDBCheckConstraint& cc,
                                        const RWDBConnection& conn);
    virtual RWDBStatus   dropConstraint(const RWDBUniqueConstraint& uc,
                                        const RWDBConnection& conn);

    virtual RWDBStatus   privilege(const RWCString& command,
                                   const RWCString& priv,
                                   const RWDBSchema& schema,
                                   const RWCString& user,
                                   const RWDBConnection& conn);

    virtual RWDBStatus   createIndex(const RWCString& name,
                                     const RWDBSchema& columns,
                                     const RWDBConnection& connection,
                                     bool unique = true,
                                     bool clustered = true);

    virtual RWDBStatus   drop(const RWDBConnection& connection);
    virtual RWDBStatus   dropIndex(const RWCString& indexName,
                                   const RWDBConnection& connection);

    // producers
    virtual RWDBDeleterImp*  deleterImp(const RWDBTable&) const;
    virtual RWDBDeleterImp*  deleterImp(const RWDBTable&,
                                        const RWDBCriterion& criterion) const;
    virtual RWDBUpdaterImp*  updaterImp(const RWDBTable&) const;
    virtual RWDBUpdaterImp*  updaterImp(const RWDBTable&,
                                        const RWDBCriterion& criterion) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         size_t cache = 1) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         const RWDBSelector&) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         const RWDBCompoundSelector&) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         const RWDBSchema&,
                                         size_t cache) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         const RWDBSelector&,
                                         const RWDBSchema&) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         const RWDBCompoundSelector&,
                                         const RWDBSchema&) const;

    virtual
    RWDBBulkInserterImp*    bulkInserterImp(const RWDBTable&,
                                            const RWDBConnection& conn);
    virtual
    RWDBBulkReaderImp*      bulkReaderImp(const RWDBTable&,
                                          const RWDBConnection&);

    virtual RWDBReaderImp*  readerImp(const RWDBTable&, size_t cacheSize);
    virtual RWDBReaderImp*  readerImp(const RWDBTable&,
                                      const RWDBConnection&,
                                      size_t cacheSize);
    virtual RWDBCursorImp*  cursorImp(const RWDBConnection& connection,
                                      RWDBCursor::CursorType type,
                                      RWDBCursor::CursorAccess access);
    virtual RWDBCursorImp*  cursorImp(const RWDBSchema& updateCols,
                                      const RWDBConnection& connection,
                                      RWDBCursor::CursorType type,
                                      RWDBCursor::CursorAccess access);

    // Defining self in the SQL statement
    virtual RWCString       asString(RWDBStatementImp* stmt,
                                     const RWZone& timeZone,
                                     bool verbose) const;

    void acquire() const
    {
        const_cast<RWDBLocalRecursiveMutex*>(&mutex_)->acquire();
    }

    void release() const
    {
        const_cast<RWDBLocalRecursiveMutex*>(&mutex_)->release();
    }

    virtual void clearCache(RWDBTable::CacheType cache);

private:
    // Mutex lock should be first to protect any data members if needed.
    RWDBLocalRecursiveMutex     mutex_;

protected:
    RWDBTagGenerator&     tagGenerator();
    RWDBConnection        connection() const;

    // Member variables
    RWCString             tag_;
    RWCString             name_;
    RWDBDatabase          parentDatabase_;
    RWDBSchema            schema_;

private:
    // not implemented
    RWDBTableImp(const RWDBTableImp&);
    RWDBTableImp& operator=(const RWDBTableImp&);

};


#endif
