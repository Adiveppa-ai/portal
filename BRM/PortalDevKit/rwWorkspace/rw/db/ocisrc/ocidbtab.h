#ifndef __RWDB_OCITAB_H__
#define __RWDB_OCITAB_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocidbtab.h#1 $
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
 * Oracle OCI Access Module definition of RWDBDatabaseTableImp
 *
 **************************************************************************/

#include <rw/db/dbsrc/dbtablei.h>
#include <rw/cstring.h>


class RWDB_ACCESS_GLOBAL RWDBOCIDatabaseTableImp : public RWDBDatabaseTableImp
{
public:
    RWDBOCIDatabaseTableImp(const RWDBDatabase& dbase,
                            const RWCString& name);
    RWDBOCIDatabaseTableImp(const RWDBStatus& status,
                            const RWDBDatabase& dbase,
                            const RWCString& name);
    RWDBOCIDatabaseTableImp(const RWDBStatus& status,
                            const RWDBDatabase& db,
                            const RWCString& name,
                            const RWDBSchema& sch,
                            bool isView);
    ~RWDBOCIDatabaseTableImp();

    RWDBStatus          status();

    RWDBStatus          privilege(const RWCString& command,
                                  const RWCString& priv,
                                  const RWDBSchema& schema,
                                  const RWCString& user,
                                  const RWDBConnection& conn);
    RWDBStatus          createIndex(const RWCString& name,
                                    const RWDBSchema& columns,
                                    const RWDBConnection& conn,
                                    bool unique,
                                    bool clustered);

    RWDBStatus          foreignKeysFromView(const RWCString& pKeyName,
                                            const RWDBConnection& conn,
                                            RWDBForeignKeyList& keyList);

    RWDBStatus          drop(const RWDBConnection& conn);
    RWDBStatus          dropIndex(const RWCString& indexName,
                                  const RWDBConnection& conn);
    RWDBStatus          addColumn(const RWDBColumn& column,
                                  const RWDBConnection& conn);
    // producers
    virtual RWDBInserterImp* inserterImp(const RWDBTable& table,
                                         size_t cache = 1) const;

    virtual RWDBInserterImp* inserterImp(const RWDBTable& table,
                                         const RWDBSelector& selector) const;

    virtual RWDBInserterImp* inserterImp(const RWDBTable& table,
                                         const RWDBCompoundSelector& selector
                                        ) const;

    virtual RWDBInserterImp* inserterImp(const RWDBTable& table,
                                         const RWDBSchema& columnList,
                                         size_t cache = 1) const;

    virtual RWDBInserterImp* inserterImp(const RWDBTable& table,
                                         const RWDBSelector& selector,
                                         const RWDBSchema& columnList) const;

    virtual RWDBInserterImp* inserterImp(const RWDBTable& table,
                                         const RWDBCompoundSelector& selector,
                                         const RWDBSchema& columnList) const;

    RWDBInserterImp* inserterImp(const RWDBTable& table,
                                 const RWDBSelector& selector,
                                 const RWDBSchema& columnList,
                                 size_t cacheSize) const;

    RWDBInserterImp* inserterImp(const RWDBTable& table,
                                 const RWDBCompoundSelector& selector,
                                 const RWDBSchema& columnList,
                                 size_t cacheSize) const;

    RWDBBulkInserterImp* bulkInserterImp(const RWDBTable& tab,
                                         const RWDBConnection& conn);
    RWDBBulkReaderImp*   bulkReaderImp(const RWDBTable& tab,
                                       const RWDBConnection& conn);

    RWDBDeleterImp*      deleterImp(const RWDBTable& table) const;
    RWDBDeleterImp*      deleterImp(const RWDBTable& table,
                                    const RWDBCriterion& crit) const;
    RWDBUpdaterImp*      updaterImp(const RWDBTable& table) const;
    RWDBUpdaterImp*      updaterImp(const RWDBTable& table,
                                    const RWDBCriterion& crit) const;

protected:
    virtual bool doSchema(const RWDBConnection& conn, RWDBTableEntry* entry);
    virtual bool doSchemaCompat(const RWDBConnection& conn, RWDBTableEntry* entry);

    virtual RWDBSchema doDescribe(RWDBTable::Metadata md,
                                  const RWDBConnection& cn);

    virtual RWDBPrimaryKey      doPrimaryKey(const RWDBConnection&,
            RWDBTableEntry* entry);

    virtual RWDBStatus          doReferredToBy(const RWDBConnection& conn,
            RWDBForeignKeyList& keyList,
            RWDBTableEntry* entry);

    virtual RWDBStatus          doForeignKeys(const RWDBConnection& conn,
            const RWCString& targetTableName,
            RWDBForeignKeyList& keyList,
            RWDBTableEntry* entry);

    virtual RWDBStatus          doCheckConstraints(const RWDBConnection& conn,
            const RWCString& cName,
            RWDBCheckConstraintList& list,
            RWDBTableEntry* entry);

    virtual RWDBStatus          doUniqueConstraints(const RWDBConnection& conn,
            const RWCString& cName,
            RWDBUniqueConstraintList& list,
            RWDBTableEntry* entry);

private:
    void                  enquote(RWCString& name) const;
    void                  createForeignKeySchema(RWDBReader& rdr,
            const RWDBConnection& conn,
            RWDBForeignKeyList& keyList) const;
    RWDBStatus            fetchReferencedTable(const RWDBConnection& conn);
    RWDBCriterion         rwdbPkeyNameCriteria(const RWCString& fullName,
            RWDBTable& allTable);
    RWDBCriterion         rwdbNameCriteria(RWDBOCIDatabaseTableImp& t,
                                           RWDBTable& allConstraints);
    RWDBResult            createForeignKeyProc(const RWDBConnection& conn);
    RWDBResult            createForeignKeyView(const RWDBConnection& conn);

    bool                  fetchSchema(const RWDBConnection& conn,
                                      RWDBStatus& status);

    RWDBPrimaryKey        fetchPrimaryKey(const RWDBConnection& conn, RWDBStatus& stat);

    bool                  describeColumnList(const RWDBConnection& conn,
            RWDBStatus& status);

    bool                  describePrimaryKey(const RWDBConnection& conn, RWDBStatus& stat);

    bool                  describeDefaultValues(const RWDBConnection& conn,
            RWDBStatus& status);

    // if the table is a synonym, this will hold the *table*
    // name that the synonym refers to, not another synonym name
    RWCString referencedTable_;

    static bool createdForeignKeyView_;
    static bool createdForeignKeyProc_;

    // not implemented
    RWDBOCIDatabaseTableImp(const RWDBOCIDatabaseTableImp&);
    RWDBOCIDatabaseTableImp& operator=(const RWDBOCIDatabaseTableImp&);
};

#endif
