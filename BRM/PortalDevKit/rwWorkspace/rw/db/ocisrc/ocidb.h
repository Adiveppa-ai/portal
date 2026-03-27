#ifndef __RWDB_OCIDB_H__
#define __RWDB_OCIDB_H__

/***************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/ocisrc/ocidb.h#1 $
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
 *  Oracle OCI Library implementation of RWDBDatabaseImp
 *
 **************************************************************************/

#include <rw/db/ocisrc/ocienvh.h>
#include <rw/db/dbsrc/dbasei.h>
#include <rw/db/result.h>
#include <rw/db/table.h>


class RWDB_ACCESS_GLOBAL RWDBOCIDatabaseImp : public RWDBDatabaseImp
{

public:
    RWDBOCIDatabaseImp(const RWCString& serverName,
                       const RWCString& userName,
                       const RWCString& passWord,
                       const RWCString& dbName);
    ~RWDBOCIDatabaseImp();

    const RWDBPhraseBook&   phraseBook() const;

    virtual
    RWDBConnectionImp*  connectionImp(RWDBConnection::ConnectionType type);

    virtual
    RWDBStoredProcImp*  storedProcImp(const RWDBDatabase& dbase,
                                      const RWCString& name,
                                      const RWDBStatus& status,
                                      const RWDBConnection&);
    virtual
    RWDBStoredProcImp*  storedProcImp(const RWDBDatabase& dbase,
                                      const RWCString& name,
                                      const RWDBStatus& status,
                                      const RWDBSchema&,
                                      const RWDBColumn&,
                                      const RWCString& text);

    RWDBTable           dbTables(const RWDBConnection& conn,
                                 const RWCString& namePattern,
                                 const RWCString& ownerPattern,
                                 int type, int adjustCase);

    virtual
    RWCString           version() const;

    using RWDBDatabaseImp::tableImp;

    virtual
    RWDBTableImp*       tableImp(const RWDBDatabase& dbase,
                                 const RWCString& name);
    virtual
    RWDBTableImp*       tableImp(const RWDBDatabase& dbase,
                                 const RWCString& name,
                                 const RWDBSchema& sch,
                                 bool isView);

    RWDBSelectorImp*    selectorImp(const RWDBDatabase&  dbase,
                                    const RWDBCriterion& crit);

    RWDBStatus          createProcedure(const RWCString&      name,
                                        const RWCString&      sql,
                                        const RWDBSchema&     params,
                                        const RWDBConnection& connection);

    RWDBStatus          createProcedure(const RWDBStoredProc& procedure,
                                        const RWDBConnection& connection);

    RWDBTable           dbStoredProcedures(const RWDBConnection& conn,
                                           const RWCString& name,
                                           const RWCString& owner,
                                           int adjustCase);

    RWDBStatus          createTable(const RWCString& name,
                                    const RWDBSchema& updateCols,
                                    const RWDBConnection& connection);

    RWDBStatus          createView(const RWCString&      name,
                                   const RWCString&      sql,
                                   const RWDBConnection& connection);
    RWDBStatus          createView(const RWCString&        name,
                                   const RWDBSelectorBase& select,
                                   const RWDBConnection&   connection);
    RWDBStatus          createView(const RWCString&        name,
                                   const RWDBSchema&       columnList,
                                   const RWDBSelectorBase& select,
                                   const RWDBConnection&   connection);
    RWDBStatus          createView(const RWCString&      name,
                                   const RWDBSchema&     columnList,
                                   const RWCString&      sql,
                                   const RWDBConnection& connection);

    RWDBStatus          dropView(const RWCString&      name,
                                 const RWDBConnection& connection);

    RWDBStatus          appendElement(const RWDBColumn& column,
                                      const RWDBPhraseBook& phrasebook,
                                      RWCString& statement);

protected:

    // Constructor for RWDBOCIXADatabaseImp to call.
    RWDBOCIDatabaseImp(const RWCString& serverName,
                       const RWCString& userName,
                       const RWCString& passWord,
                       const RWCString& dbName,
                       int);

    static const char                                  version_[];

private:

    RWDBStatus          appendParameter(const RWDBColumn&     column,
                                        const RWDBPhraseBook& phrasebook,
                                        RWCString&            statement);

    RWDBStatus          rwparamtype(RWCString&            datatype,
                                    const RWDBColumn&     column,
                                    const RWDBPhraseBook&);

    RWCString           largeString(const RWDBColumn& c);

    RWCString           largeBlob(const RWDBColumn& c);

    RWDBStatus          rwdatatype(RWCString& datatype,
                                   const RWDBColumn& column,
                                   const RWDBPhraseBook& phrase);

    static
    RWDBStatus          oradatatype(RWCString& datatype,
                                    const RWDBColumn& column,
                                    const RWDBPhraseBook& phrase);

    // not implemented
    RWDBOCIDatabaseImp(const RWDBOCIDatabaseImp&);
    RWDBOCIDatabaseImp& operator=(const RWDBOCIDatabaseImp&);

};


#endif
