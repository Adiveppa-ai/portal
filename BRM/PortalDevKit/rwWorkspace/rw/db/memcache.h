#ifndef __RWDB_INMEMCACHE_H__
#define __RWDB_INMEMCACHE_H__

/***************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/memcache.h#1 $
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
 ***************************************************************************/

#include <rw/db/cachemgr.h>
#include <rw/db/checkconstr.h>
#include <rw/db/column.h>
#include <rw/db/forkey.h>
#include <rw/db/primarykey.h>
#include <rw/db/schema.h>
#include <rw/db/uniqueconstr.h>
#include <rw/cstring.h>
#include <rw/rwfile.h>
#include <rw/tvhmap.h>
#include <rw/vstream.h>

/**
 * \ingroup db_utility_and_diagnostics_group
 * \class RWDBInMemoryCacheManager
 *
 * \brief
 * In memory metadata cache manager.
 *
 * RWDBInMemoryCacheManager is an in-memory implementation for caching of
 * schema metadata.
 *
 * Install an instance of RWDBInMemoryCacheManager in an instance of
 * RWDBDatabase. The metadata of the objects produced by that RWDBDatabase
 * instance will be cached. An RWDBInMemoryCacheManager instance may not be
 * shared amongst multiple RWDBDatabase objects. If you need to access the
 * currently installed cache manager, acquire the lock to the RWDBDatabase
 * and then release it when done via the methods RWDBDatabase::acquire() and
 * RWDBDatabase::release(). The cache manager must remain in scope for the
 * lifetime of the RWDBDatabase instance in which it is installed.
 *
 * Please refer to the <em>DB Interface Module User's Guide</em> and the
 * applicable <em>DB Access Module User's Guide</em> for more information on
 * caching metadata.
 *
 * \synopsis
 * #include <rw/db/memcache.h>
 *
 * int main()
 * {
 *     RWDBInMemoryCacheManager cacheManager;
 *     RWDBDatabase dBase =
 *     RWDBManager::database("accessLib", "Servername", "Username", "Password", "DatabaseName");
 *     dBase.cacheManager(&cacheManager);
 * }
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBInMemoryCacheManager : public RWDBCacheManager
{
public:

    /**
     * Types allowed for removeAll().
     */
    enum RemovalType {

        /**
         * Remove metadata cached for any and all tables.
         */
        table,

        /**
         * Remove metadata cached for any and all stored procedures.
         */
        storedProc,

        /**
         * Remove metadata cached for any and all tables and stored
         * procedures.
         */
        both
    };

    /**
     * Constructor.
     */
    RWDBInMemoryCacheManager() {}

    /**
     * Destructor.
     */
    ~RWDBInMemoryCacheManager();

    // tools persistence API
    /**
     * Saves the object \a cm to an RWFile.
     */
    friend RWDB_SYMBOLIC
    RWFile& operator<<(RWFile& file, const RWDBInMemoryCacheManager& cm);

    /**
     * Saves the object \a cm to a virtual stream.
     */
    friend RWDB_SYMBOLIC
    RWvostream& operator<<(RWvostream& strm, const RWDBInMemoryCacheManager& cm);

    /**
     * Restores an RWDBInMemoryCacheManager into \a cm from an RWFile,
     * replacing the previous contents of \a cm.
     */
    friend RWDB_SYMBOLIC
    RWFile& operator>>(RWFile& file, RWDBInMemoryCacheManager& cm);

    /**
     * Restores an RWDBInMemoryCacheManager into \a cm from a virtual
     * stream, replacing the previous contents of \a cm.
     */
    friend RWDB_SYMBOLIC
    RWvistream& operator>>(RWvistream& strm, RWDBInMemoryCacheManager& cm);

    // all the set()/get() methods
    // Documented in the base class
    void setTable(const RWCString& key, const RWDBTableEntry& entry);

    void setStoredProc(const RWCString& key, const RWDBStoredProcEntry& entry);

    RWDBTableEntry getTable(const RWCString& key) const;

    RWDBStoredProcEntry getStoredProc(const RWCString& key) const;

    /**
     * Clears all entries from the cache of type \a t.
     */
    void removeAll(RemovalType t = both);

private:
    // Not implemented
    RWDBInMemoryCacheManager(const RWDBInMemoryCacheManager&);
    RWDBInMemoryCacheManager& operator=(const RWDBInMemoryCacheManager&);

    RWTValHashMap<RWCString, RWDBStoredProcEntry> procMap_;
    RWTValHashMap<RWCString, RWDBTableEntry> tableMap_;

};

#endif
