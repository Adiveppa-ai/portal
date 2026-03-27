#ifndef __RWDB_DBTABLEI_H__
#define __RWDB_DBTABLEI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/dbtablei.h#1 $
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
 * Definition of RWDBDatabaseTableImp
 *
 *     RWDBDatabaseTableImp is a base class for a family of database-
 *     specific database table implementations.
 *
 **************************************************************************/

#include <rw/db/dbsrc/bkinsi.h>
#include <rw/db/dbsrc/tablei.h>
#include <rw/db/dberr.h>


class RWDB_SYMBOLIC RWDBTableEntry;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBDatabaseTableImp
    : public RWDBTableImp
{
public:
    RWDBDatabaseTableImp(const RWDBStatus& status,
                         const RWDBDatabase& db,
                         const RWCString& name);
    RWDBDatabaseTableImp(const RWDBStatus& status,
                         const RWDBDatabase& db,
                         const RWCString& name,
                         const RWDBSchema& sch,
                         bool isView);
    virtual ~RWDBDatabaseTableImp();

    // these methods check the cache manager and then forward the call
    // to the access module, if needed
    bool       existsAllocateConnection(bool forceLookup);
    bool       exists(const RWDBConnection& connection, bool forceLookup);
    bool       isViewAllocateConnection();
    bool       isView(const RWDBConnection& connection);

    RWDBSchema describe(RWDBTable::Metadata md, const RWDBConnection* cn);

    RWDBPrimaryKey     primaryKey(const RWDBConnection& conn);
    RWDBPrimaryKey     primaryKey();

    RWDBStatus         referredToBy(const RWDBConnection& conn,
                                    RWDBForeignKeyList& keyList);
    RWDBStatus         referredToBy(RWDBForeignKeyList& keyList);

    RWDBStatus         foreignKeys(const RWDBConnection& conn,
                                   const RWCString& refName,
                                   RWDBForeignKeyList& keyList);

    RWDBStatus         foreignKeys(const RWCString& refName,
                                   RWDBForeignKeyList& keyList);

    RWDBStatus         checkConstraints(const RWDBConnection& conn,
                                        const RWCString& cName,
                                        RWDBCheckConstraintList& list);
    RWDBStatus         checkConstraints(const RWCString& cName,
                                        RWDBCheckConstraintList& list);

    RWDBStatus         uniqueConstraints(const RWDBConnection& conn,
                                         const RWCString& cName,
                                         RWDBUniqueConstraintList& list);
    RWDBStatus         uniqueConstraints(const RWCString& cName,
                                         RWDBUniqueConstraintList& list);

    virtual RWDBStatus      privilege(const RWCString& command,
                                      const RWCString& priv,
                                      const RWDBSchema& schema,
                                      const RWCString& user,
                                      const RWDBConnection& conn);

    virtual RWDBStatus      addColumn(const RWDBColumn& aCol,
                                      const RWDBConnection& aConn);
    virtual RWDBStatus      dropColumn(const RWDBColumn& aCol,
                                       const RWDBConnection& conn);

    virtual RWDBStatus      addConstraint(const RWCString& constraintStr,
                                          const RWDBConnection& conn);
    virtual RWDBStatus      addConstraint(const RWDBPrimaryKey& pk,
                                          const RWDBConnection& conn);
    virtual RWDBStatus      addConstraint(const RWDBForeignKey& fk,
                                          const RWDBConnection& conn);
    virtual RWDBStatus      addConstraint(const RWDBCheckConstraint& cc,
                                          const RWDBConnection& conn);
    virtual RWDBStatus      addConstraint(const RWDBUniqueConstraint& uc,
                                          const RWDBConnection& conn);

    virtual RWDBStatus      dropConstraint(const RWCString& constraintName,
                                           const RWDBConnection& conn);
    virtual RWDBStatus      dropConstraint(const RWDBPrimaryKey& pk,
                                           const RWDBConnection& conn);
    virtual RWDBStatus      dropConstraint(const RWDBForeignKey& fk,
                                           const RWDBConnection& conn);
    virtual RWDBStatus      dropConstraint(const RWDBCheckConstraint& cc,
                                           const RWDBConnection& conn);
    virtual RWDBStatus      dropConstraint(const RWDBUniqueConstraint& uc,
                                           const RWDBConnection& conn);

    virtual RWDBBulkInserterImp* bulkInserterImp(const RWDBTable&,
            const RWDBConnection& conn);
    virtual RWDBDeleterImp*  deleterImp(const RWDBTable&) const;
    virtual RWDBDeleterImp*  deleterImp(const RWDBTable&,
                                        const RWDBCriterion&) const;
    virtual RWDBUpdaterImp*  updaterImp(const RWDBTable&) const;
    virtual RWDBUpdaterImp*  updaterImp(const RWDBTable&,
                                        const RWDBCriterion&) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         size_t cache = 1) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         const RWDBSelector&) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         const RWDBCompoundSelector&) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         const RWDBSchema&,
                                         size_t cache = 1) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         const RWDBSelector&,
                                         const RWDBSchema&) const;
    virtual RWDBInserterImp* inserterImp(const RWDBTable&,
                                         const RWDBCompoundSelector&,
                                         const RWDBSchema&) const;
    virtual RWDBReaderImp*   readerImp(const RWDBTable&, size_t cacheSize);
    virtual RWDBReaderImp*   readerImp(const RWDBTable&,
                                       const RWDBConnection&,
                                       size_t cacheSize);
    virtual RWDBCursorImp*   cursorImp(const RWDBConnection& connection,
                                       RWDBCursor::CursorType type,
                                       RWDBCursor::CursorAccess access);
    virtual RWDBCursorImp*   cursorImp(const RWDBSchema& updateCols,
                                       const RWDBConnection& connection,
                                       RWDBCursor::CursorType type,
                                       RWDBCursor::CursorAccess access);

    virtual void    clearCache(RWDBTable::CacheType cache);

protected:
    virtual bool doSchema(const RWDBConnection&, RWDBTableEntry*)
    {
        return false;
    }
    virtual bool doSchemaCompat(const RWDBConnection&,
                                RWDBTableEntry*)
    {
        return false;
    }
    virtual RWDBPrimaryKey doPrimaryKey(const RWDBConnection&,
                                        RWDBTableEntry*)
    {
        return RWDBPrimaryKey();
    }
    virtual RWDBStatus doReferredToBy(const RWDBConnection&,
                                      RWDBForeignKeyList&,
                                      RWDBTableEntry*)
    {
        return RWDBStatus();
    }
    virtual RWDBStatus doForeignKeys(const RWDBConnection&,
                                     const RWCString&,
                                     RWDBForeignKeyList&,
                                     RWDBTableEntry*)
    {
        return RWDBStatus();
    }
    virtual RWDBStatus doCheckConstraints(const RWDBConnection&,
                                          const RWCString&,
                                          RWDBCheckConstraintList&,
                                          RWDBTableEntry*)
    {
        return RWDBStatus();
    }
    virtual RWDBStatus doUniqueConstraints(const RWDBConnection&,
                                           const RWCString&,
                                           RWDBUniqueConstraintList&,
                                           RWDBTableEntry*)
    {
        return RWDBStatus();
    }

    virtual RWDBSchema doDescribe(RWDBTable::Metadata, const RWDBConnection&)
    {
        RWDBStatus stat(RWMessage(RWDB_NOTSUPPORTED,
                                  "describe",
                                  "implementation").str(),
                        RWDBStatus::notSupported);
        return RWDBSchema(stat);
    }

    /**
     * \internal
     * If there is a cache manager, check if a RWDBTable with this name()
     * has already been cached, and update the local variables with this
     * data.
     */
    RWDBTableEntry getCachedData();

    /**
     * \internal
     * If there is a cache manager, check if a RWDBTable with this name()
     * has already been cached, updates the entry with any new data
     * contained in \a entry.
     */
    void setCachedData(const RWDBTableEntry& entry);

    enum Exists { Yes, No, DontKnow };

    RWDBTable::Metadata md_;
    bool  isView_;
    Exists exists_;


private:
    bool getExists(const RWDBConnection* cnPtr, bool forceLookup);
    RWDBStatus getCheckConstraints(const RWDBConnection* cnPtr,
                                   const RWCString& conName,
                                   RWDBCheckConstraintList& ls);
    RWDBStatus getForeignKeys(const RWDBConnection* cnPtr,
                              const RWCString& refName,
                              RWDBForeignKeyList& ls);
    RWDBPrimaryKey getPrimaryKey(const RWDBConnection* cnPtr);
    RWDBStatus getReferredToBy(const RWDBConnection* cnPtr,
                               RWDBForeignKeyList& ls);
    RWDBSchema getSchema(const RWDBConnection* cnPtr);
    RWDBStatus getUniqueConstraints(const RWDBConnection* cnPtr,
                                    const RWCString& conName,
                                    RWDBUniqueConstraintList& ls);
    // not implemented
    RWDBDatabaseTableImp(const RWDBDatabaseTableImp&);
    RWDBDatabaseTableImp& operator=(const RWDBDatabaseTableImp&);
};

#endif
