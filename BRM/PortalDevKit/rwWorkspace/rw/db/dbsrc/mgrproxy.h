#ifndef __RWDB_MGRPROXY_H__
#define __RWDB_MGRPROXY_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbsrc/mgrproxy.h#1 $
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

#include <rw/db/dbsrc/dbentry.h>
#include <rw/db/dbase.h>
#include <rw/db/dbmgr.h>
#include <rw/tvdlist.h>


////////////////////////////////////////////////////////////////////////
//
// RWDBManagerProxy
//
// Maintains the list of RWDBEntrys and provides accessor functions
// for the RWDBEntry members.
//
// In case of multithreading the access to the static data of
// RWDBManagerProxy is guarded by:
//   * RWDBManager::database(),
//   * RWDBManager::add(),
//   * RWDBManagerProxyAnchor::RWDBManagerProxyAnchor()
//   * static RWDBManagerProxy::deregisterDb()
//
//
//////////////////////////////////////////////////////////////////////////

class  RWDBManagerProxy
{
    friend class RWDBManager;

public:
    ~RWDBManagerProxy();

private:

    RWDBManagerProxy();

    // helper function for managing singleton
    static RWDBManagerProxy* instance();

    // helper function for RWOnce to guard creation RWDBManagerProxy instance
    static void createInstance();

    // Accessor method for the function returning regular (Non-XA)
    // database implementation.
    // If no RWDBEntry found, it creates one with the given database type.
    RWDBNewImpFunc     impFunc(const RWCString& dbType);

    // Accessor method for the function returning XA-Enabled
    // database implementation.
    // If no RWDBEntry found, it creates one with the given database type.
    RWDBNewImpFunc     xaImpFunc(const RWCString& dbType);

    // Accessor method for the function returning XA Switch.
    // If no RWDBEntry found, it creates one with the given database type.
    RWDBXASwitchFunc   xaSwitchFunc(const RWCString& dbType);

    // Returns RWDBEntry with the given database type if it exists
    // else creates a new entry with that database type, appends it to
    // the list and returns the same.
    // Generally, used by the dynamic builds to create their RWDBEntry.
    RWDBEntry          addEntry(const RWCString& dbType);

    // Creates RWDBEntry with the given function pointers and appends
    // it to the list
    // Generally, used by static builds to create their RWDBEntry.
    void               addEntry(const RWCString& dbType,
                                RWDBNewImpFunc impFunc,
                                RWDBNewImpFunc xaImpFunc = 0,
                                RWDBXASwitchFunc xaSwitchFunc = 0
                               );

    RWTScopedPointer<RWTValDlist<RWDBEntry> > entries_;
};

#endif // __RWDB_MGRPROXY_H__
