#ifndef __RWDB_CACHEMGR_H__
#define __RWDB_CACHEMGR_H__

/***************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/cachemgr.h#1 $
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

#include <rw/db/checkconstr.h>
#include <rw/db/column.h>
#include <rw/db/defs.h>
#include <rw/db/forkey.h>
#include <rw/db/primarykey.h>
#include <rw/db/schema.h>
#include <rw/db/table.h>
#include <rw/db/uniqueconstr.h>
#include <rw/tools/pointer.h>

class RWCString;

/**
 * \ingroup db_utility_and_diagnostics_group
 *
 * \brief
 * Class to hold RWDBStoredProc metadata for cache managers.
 *
 * RWDBStoredProcEntry is a class for moving RWDBStoredProc metadata in and
 * out of a cache manager class that inherits from RWDBCacheManager.
 *
 * \synopsis
 * #include <rw/db/cachemgr.h>
 * #include <rw/tvhmap.h>
 *
 * class MyCacheManager : public RWDBCacheManager
 * {
 *     void setStoredProc(const RWCString& name, const RWDBStoredProcEntry& spEntry) {
 *         spCache.insert(name, spEntry);
 *     }
 *
 *     RWDBStoredProcEntry getStoredProc(const RWCString& name) const {
 *         RWDBStoredProcEntry spEntry;
 *         spCache.findValue(name, spEntry);
 *         return spEntry;
 *     }
 * private:
 *     RWTValHashMap<RWCString, RWDBStoredProcEntry> spCache;
 * };
 * \endsynopsis
 */
class RWDB_SYMBOLIC RWDBStoredProcEntry
{
public:
    /**
     * Constructs an empty object with no metadata information.
     */
    RWDBStoredProcEntry();

    /**
     * Copies all metadata information from \a entry.
     */
    RWDBStoredProcEntry(const RWDBStoredProcEntry& entry);

    /**
     * Copies all metadata information from \a entry.
     */
    RWDBStoredProcEntry& operator=(const RWDBStoredProcEntry& entry);

    /**
     * Returns \c true if the exists flag has been set on self.
     */
    bool hasExists() const;

    /**
     * Returns the value of the exists flag.
     *
     * \note
     * If hasExists() returns \c false this function returns \c false.
     */
    bool getExists() const;

    /**
     * Sets exists flag on self. After this call, hasExists() returns
     * \c true.
     */
    void setExists(bool exists);

    /**
     * Clears the value of the exists flag. After this call, hasExists()
     * returns \c false.
     */
    void clearExists();

    /**
     * Returns \c true if a parameter list has been set on self.
     */
    bool hasParams() const;

    /**
     * Returns the parameter list set on self.
     *
     * \note
     * If hasParams() returns \c false this call returns an empty
     * RWDBSchema.
     */
    RWDBSchema getParams() const;

    /**
     * Sets the parameter list on self. After this call hasParams() returns
     * \c true.
     */
    void setParams(const RWDBSchema& schema);

    /**
     * Clears the parameter list on self. After this call hasParams()
     * returns \c false.
     */
    void clearParams();

    /**
     * Returns \c true if the return value column has been set on self.
     */
    bool hasReturnValue() const;

    /**
     * Returns the return value column set on self.
     *
     * \note
     * If hasReturnValue() returns \c false this call returns an empty
     * RWDBColumn.
     */
    RWDBColumn getReturnValue() const;

    /**
     * Sets the return value column on self. After this call
     * hasReturnValue() returns \c true.
     */
    void setReturnValue(const RWDBColumn& col);

    /**
     * Clears the return value column on self. After this call
     * hasReturnValue() returns \c false.
     */
    void clearReturnValue();

    /**
     * Returns \c true if the text has been set on self.
     */
    bool hasText() const;

    /**
     * Returns the text set on self.
     *
     * \note
     * If hasText() returns \c false this call returns an empty RWCString.
     */
    RWCString getText() const;

    /**
     * Sets the text on self. After this call hasText() returns \c true.
     */
    void setText(const RWCString& text);

    /**
     * Clears the text on self. After this call hasText() returns \c false.
     */
    void clearText();

    /**
     * Saves the object \a item to a virtual stream. Recursively calls the
     * function saveGuts(), taking duplicate objects into account. See the
     * discussion on Persistence in the <em>Essential Tools Module User's
     * Guide</em> for more information.
     */
    friend RWDB_SYMBOLIC RWvostream& operator<<(RWvostream& strm, const RWDBStoredProcEntry& item);

    /**
     * Restores an RWDBStoredProcEntry into \a obj from a virtual stream,
     * replacing the previous contents of \a obj. Recursively calls the
     * function restoreGuts(), taking duplicate objects into account. For
     * more information, see the discussion on Persistence in the
     * <em>Essential Tools Module User's Guide</em>.
     */
    friend RWDB_SYMBOLIC RWvistream& operator>>(RWvistream& strm, RWDBStoredProcEntry& obj);

    /**
     * Saves the object \a item to an RWFile. Recursively calls the function
     * saveGuts(), taking duplicate objects into account. See the discussion
     * on Persistence in the <em>Essential Tools Module User's Guide</em>
     * for more information.
     */
    friend RWDB_SYMBOLIC RWFile& operator<<(RWFile& file, const RWDBStoredProcEntry& item);

    /**
     * Restores an RWDBStoredProcEntry into \a obj from an RWFile, replacing
     * the previous contents of \a obj. Recursively calls the function
     * restoreGuts(), taking duplicate objects into account. For more
     * information, see the discussion on Persistence in the <em>Essential
     * Tools Module User's Guide</em>.
     */
    friend RWDB_SYMBOLIC RWFile& operator>>(RWFile& file, RWDBStoredProcEntry& obj);

    void saveGuts(RWvostream&) const;
    void saveGuts(RWFile&) const;
    void restoreGuts(RWvistream&);
    void restoreGuts(RWFile&);

private:
    RWCString text_;
    RWTScopedPointer<RWDBSchema> params_;
    RWTScopedPointer<RWDBColumn> returnValue_;
    bool exists_;
    bool hasExists_;
    bool hasText_;
};

/**
 * \ingroup db_utility_and_diagnostics_group
 *
 * \brief
 * Class to hold RWDBTable metadata for cache managers.
 *
 * RWDBTableEntry is a class for moving RWDBTable metadata in and out of a
 * cache manager class that inherits from RWDBCacheManager.
 *
 * \synopsis
 * #include <rw/db/cachemgr.h>
 * #include <rw/tvhmap.h>
 *
 * class MyCacheManager : public RWDBCacheManager
 * {
 *     void setTable(const RWCString& name, const RWDBTableEntry& tEntry) {
 *         tCache.insert(name, tEntry);
 *     }
 *
 *     RWDBTableEntry getTable(const RWCString& name) const {
 *         RWDBTableEntry tEntry;
 *         tCache.findValue(name, tEntry);
 *         return tEntry;
 *     }
 * private:
 *     RWTValHashMap<RWCString, RWDBTableEntry> tCache;
 * };
 * \endsynopsis
 */
class RWDB_SYMBOLIC RWDBTableEntry
{
public:
    /**
     * Constructs an empty object with no metadata information.
     */
    RWDBTableEntry();

    /**
     * Copies all metadata information from \a entry.
     */
    RWDBTableEntry(const RWDBTableEntry& entry);

    /**
     * Returns \c true if the exists flag has been set on self.
     */
    bool hasExists() const;

    /**
     * Returns the exists flag set on self.
     *
     * \note
     * If hasExists() returns \c false this call returns \c false.
     */
    bool getExists() const;

    /**
     * Sets the exists flag on self. After this call hasExists() returns
     * \c true.
     */
    void setExists(bool exists);

    /**
     * Clears the exists flag on self. After this call hasExists() returns
     * \c false.
     */
    void clearExists();

    /**
     * Returns \c true if the RWDBSchema has been set on self.
     */
    bool hasSchema() const;

    /**
     * Returns the RWDBSchema set on self.
     *
     * \note
     * If hasSchema() returns \c false this call returns an empty
     * RWDBSchema.
     */
    RWDBSchema getSchema() const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 13.1, use
     * setSchema(const RWDBSchema&, RWDBTable::Metadata md) instead.
     */
    void setSchema(const RWDBSchema& schema);

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * Sets the RWDBSchema and RWDBTable::Metadata on self. After this call
     * hasSchema() returns \c true. The parameter \a md indicates the
     * metadata from \a schema that is to be set on self.
     */
    void setSchema(const RWDBSchema& schema, RWDBTable::Metadata md);

    /**
     * Returns the RWDBTable::Metadata set on self for the associated
     * schema. Indicates the metadata information that is currently known by
     * the schema.
     */
    RWDBTable::Metadata getMetadata() const;

    /**
     * Clears the RWDBSchema set on self. After this call hasSchema()
     * returns \c false.
     */
    void clearSchema();

    /**
     * Returns \c true if the isView flag has been set on self.
     */
    bool hasIsView() const;

    /**
     * Returns the isView flag set on self.
     *
     * \note
     * If hasIsView() returns \c false this call returns \c false.
     */
    bool getIsView() const;

    /**
     * Sets the isView flag on self. After this call hasIsView() returns
     * \c true.
     */
    void setIsView(bool isView);

    /**
     * Clears the isView flag on self. After this call hasIsView() returns
     * \c false.
     */
    void clearIsView();

#if !defined(RW_DISABLE_DEPRECATED)
    RW_SUPPRESS_DEPRECATED_WARNINGS

    /**
     * \deprecated
     * As of SourcePro 13.1, use getMetadata() checking for
     * RWDBTable::ColumnList instead.
     */
    bool hasPrimaryKey() const;

    /**
     * \deprecated
     * As of SourcePro 13.1, use
     * getSchema().\ref RWDBSchema::primaryKey() "primaryKey()" to get the
     * RWDBPrimaryKey on the underlying schema.
     */
    RWDBPrimaryKey getPrimaryKey() const;

    /**
     * \deprecated
     * As of SourcePro 13.1, use setSchema() to set a schema that has a
     * primary key.
     */
    void setPrimaryKey(const RWDBPrimaryKey& pk);

    /**
     * \deprecated
     * As of SourcePro 13.1, use setSchema() to set a schema that has no
     * primary key.
     */
    void clearPrimaryKey();

    RW_RESTORE_DEPRECATED_WARNINGS
#endif

    /**
     * Returns \c true if the RWDBForeignKeyList has been set on self.
     */
    bool hasForeignKeys() const;

    /**
     * Returns the RWDBForeignKeyList set on self.
     *
     * \note
     * If hasForeignKeys() returns \c false this call returns an empty
     * RWDBForeignKeyList.
     */
    const RWDBForeignKeyList& getForeignKeys() const;

    /**
     * Sets the RWDBForeignKeyList on self, with a deep copy of \a fk. After
     * this call hasForeignKeys() returns \c true.
     */
    void setForeignKeys(const RWDBForeignKeyList& fk);

    /**
     * Clears the RWDBForeignKeyList set on self. After this call
     * hasForeignKeys() returns \c false.
     */
    void clearForeignKeys();

    /**
     * Returns \c true if the referredToBy list has been set on self.
     */
    bool hasReferredToBy() const;

    /**
     * Returns the referredToBy list set on self.
     *
     * \note
     * If hasReferredToBy() returns \c false this call returns an empty
     * RWDBForeignKeyList.
     */
    const RWDBForeignKeyList& getReferredToBy() const;

    /**
     * Sets the referredToBy list on self with a deep copy of \a rk. After
     * this call hasReferredToBy() returns \c true.
     */
    void setReferredToBy(const RWDBForeignKeyList& rk);

    /**
     * Clears the referredToBy list set on self. After this call
     * hasReferredToBy() returns \c false.
     */
    void clearReferredToBy();

    /**
     * Returns \c true if the RWDBCheckConstraintList has been set on self.
     */
    bool hasCheckConstraints() const;

    /**
     * Returns the RWDBCheckConstraintList set on self.
     *
     * \note
     * If hasCheckConstraints() returns \c false this call returns an empty
     * RWDBCheckConstraintList.
     */
    const RWDBCheckConstraintList& getCheckConstraints() const;

    /**
     * Sets the RWDBCheckConstraintList on self with a deep copy of \a cc.
     * After this call hasCheckConstraints() returns \c true.
     */
    void setCheckConstraints(const RWDBCheckConstraintList& cc);

    /**
     * Clears the RWDBCheckConstraintList set on self. After this call
     * hasCheckConstraints() returns \c false.
     */
    void clearCheckConstraints();

    /**
     * Returns \c true if the RWDBUniqueConstraintList has been set on self.
     */
    bool hasUniqueConstraints() const;

    /**
     * Returns the RWDBUniqueConstraintList set on self.
     *
     * \note
     * If hasUniqueConstraints() returns \c false this call returns an empty
     * RWDBUniqueConstraintList.
     */
    const RWDBUniqueConstraintList& getUniqueConstraints() const;

    /**
     * Sets the RWDBUniqueConstraintList on self with a deep copy of \a uc.
     * After this call hasUniqueConstraints() returns \c true.
     */
    void setUniqueConstraints(const RWDBUniqueConstraintList& uc);

    /**
     * Clears the RWDBUniqueConstraintList set on self. After this call
     * hasUniqueConstraints() returns \c false.
     */
    void clearUniqueConstraints();

    /**
     * Saves the object \a item to a virtual stream. Recursively calls the
     * function saveGuts(), taking duplicate objects into account. See the
     * discussion on Persistence in the <em>Essential Tools Module User's
     * Guide</em> for more information.
     */
    friend RWDB_SYMBOLIC RWvostream& operator<<(RWvostream& strm, const RWDBTableEntry& item);

    /**
     * Restores an RWDBTableEntry into \a obj from a virtual stream,
     * replacing the previous contents of \a obj. Recursively calls the
     * function restoreGuts(), taking duplicate objects into account. For
     * more information, see the discussion on Persistence in the
     * <em>Essential Tools Module User's Guide</em>.
     */
    friend RWDB_SYMBOLIC RWvistream& operator>>(RWvistream& strm, RWDBTableEntry& obj);

    /**
     * Restores an RWDBTableEntry into \a obj from an RWFile, replacing the
     * previous contents of \a obj. Recursively calls the function
     * restoreGuts(), taking duplicate objects into account. For more
     * information, see the discussion on Persistence in the <em>Essential
     * Tools Module User's Guide</em>.
     */
    friend RWDB_SYMBOLIC RWFile& operator>>(RWFile& file, RWDBTableEntry& obj);

    /**
     * Saves the object \a item to an RWFile. Recursively calls the function
     * saveGuts(), taking duplicate objects into account. See the discussion
     * on Persistence in the <em>Essential Tools Module User's Guide</em>
     * for more information.
     */
    friend RWDB_SYMBOLIC RWFile& operator<<(RWFile& file, const RWDBTableEntry& item);


    void saveGuts(RWvostream&) const;
    void saveGuts(RWFile&) const;
    void restoreGuts(RWvistream&, size_t);
    void restoreGuts(RWFile&, size_t);

    /**
     * Assignment operator. Copies all of the contained objects.
     */
    RWDBTableEntry& operator=(const RWDBTableEntry& entry);

private:
    RWTScopedPointer<RWDBSchema> schema_; // also holds primary key meta-data
    RWTScopedPointer<RWDBForeignKeyList> fKeys_, refKeys_;
    RWTScopedPointer<RWDBUniqueConstraintList> uKeys_;
    RWTScopedPointer<RWDBCheckConstraintList> checkC_;
    bool exists_;
    bool isView_;
    bool hasExists_;
    bool hasFKeys_;
    bool hasIsView_;
    bool hasRefKeys_;
    bool hasUKeys_;
    bool hasCheckC_;
    RWDBTable::Metadata metadata_;
};

/**
 * \ingroup db_utility_and_diagnostics_group
 *
 * \brief
 * Base class for user-defined metadata cache managers.
 *
 * RWDBCacheManager is a base class for implementing the caching of schema
 * metadata. The types of metadata that is cached are defined RWDBTableEntry
 * and RWDBStoredProcEntry. Caching this data allows the program to create
 * and use RWDBTable and RWDBStoredProc ojects with fewer queries to the
 * database.
 *
 * Install an instance of a cache manager class derived from
 * RWDBCacheManager, in only one instance of RWDBDatabase. A cache manager
 * instance may not be shared with multiple RWDBDatabase instances. If you
 * need to access the currently installed cache manager, acquire the global
 * lock to the RWDBDatabase and then release it when done via the methods
 * RWDBDatabase::acquire() and RWDBDatabase::release(). The cache manager
 * must remain in scope for the lifetime of the RWDBDatabase instance in
 * which it is installed.
 *
 * Please refer to the <em>DB Interface Module User's Guide</em> and the
 * applicable <em>DB Access Module User's Guide</em> for more information on
 * caching metadata.
 *
 * \sa
 * RWDBInMemoryCacheManager
 *
 * \synopsis
 * #include <rw/db/cachemgr.h>
 * \endsynopsis
 *
 * \example
 * \code
 * #include <rw/db/cachemgr.h>
 * #include <rw/tvhmap.h>
 *
 * class MyCacheManager : public RWDBCacheManager
 * {
 *     void setTable(const RWCString& name, const RWDBTableEntry& tEntry) {
 *         tCache.insert(name, tEntry);
 *     }
 *
 *     void setStoredProc(const RWCString& name, const RWDBStoredProcEntry& spEntry) {
 *         spCache.insert(name, spEntry);
 *     }
 *
 *     RWDBTableEntry getTable(const RWCString& name) const {
 *         RWDBTableEntry tEntry;
 *         tCache.findValue(name, tEntry);
 *         return tEntry;
 *     }
 *     RWDBStoredProcEntry getStoredProc(const RWCString& name) const {
 *         RWDBStoredProcEntry spEntry;
 *         spCache.findValue(name, spEntry);
 *         return spEntry;
 *     }
 * private:
 *     RWTValHashMap<RWCString, RWDBTableEntry> tCache;
 *     RWTValHashMap<RWCString, RWDBStoredProcEntry> spCache;
 * };
 *
 * int main()
 * {
 *     MyCacheManager cache;
 *
 *     RWDBDatabase db =
 *         RWDBManager::database("accessLib", "Servername",
 *                               "Username", "Password", "DatabaseName");
 *     db.cacheManager(&cache);
 * }
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBCacheManager
{
public:

    /**
     * Destructor.
     */
    virtual ~RWDBCacheManager();

    /**
     * This method is called whenever we have fetched any table metadata
     * from the database and need to cache it. The \a key is the return
     * value of RWDBTable::name(), and the \a tableEntry contains all of the
     * table metadata.
     *
     * The default implementation is a no-op.
     */
    virtual void setTable(const RWCString& key, const RWDBTableEntry& tableEntry);

    /**
     * This method is called whenever we have fetched any stored procedure
     * metadata from the database and need to cache it. The \a key is the
     * return value of RWDBStoredProc::name(), and the \a spEntry contains
     * all of the stored procedure metadata.
     *
     * The default implementation is a no-op.
     */
    virtual void setStoredProc(const RWCString& key, const RWDBStoredProcEntry& spEntry);

    /**
     * This method is called whenever we need any table metadata from the
     * cache. If the \a key is not in the cache, this method returns an
     * empty RWDBTableEntry. The \a key is the return value of
     * RWDBTable::name().
     *
     * The default implementation returns an empty RWDBTableEntry.
     */
    virtual RWDBTableEntry getTable(const RWCString& key) const;

    /**
     * This method is called whenever we need any stored procedure metadata
     * from the cache. If the \a key is not in the cache, this method
     * returns an empty RWDBStoredProcEntry. The \a key is the return value
     * of RWDBStoredProc::name().
     *
     * The default implementation returns an empty RWDBStoredProcEntry.
     */
    virtual RWDBStoredProcEntry getStoredProc(const RWCString& key) const;

    /**
     * \internal
     * This function rethrows and catches any exception, setting the
     * RWDBStatus, \a st to either RWDBStatus::cacheReadError, or
     * RWDBStatus::cacheWriteError. Any exception thrown from the cache
     * should be handled by this function.
     *
     * \note
     * This function can only be called from a catch block.
     *
     * \code
     * try {
     *     cacheManager.setStoredProc(key, spEntry);
     * }
     * catch(...) {
     *     RWDBStatus xstatus(errorHandler(), RWDBStatus::cacheWriteError);
     *     RWDBCacheManager::handleDBCacheError(xstatus);
     * }
     * \endcode
     */
    static void handleDBCacheError(RWDBStatus& st);

protected:

    /**
     * Default constructor.
     */
    RWDBCacheManager();

    /**
     * Copy constructor.
     */
    RWDBCacheManager(const RWDBCacheManager&);
};


#endif
