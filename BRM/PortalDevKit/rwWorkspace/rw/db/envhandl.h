#ifndef __RWDB_ENVHANDL_H__
#define __RWDB_ENVHANDL_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/envhandl.h#1 $
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
 * RWDBEnvironmentHandle is a base class for database-specific
 * " environment handles."
 * Each DB Access Module defines an environment handle for its
 * own database. The functionality provided by the environment handles can be
 * expected to vary widely among access modules. Check the access module
 * specific documentation for the functionality supported by the environment
 * handle. The access module-specific environment handle is also expected to
 * provide a direct handle to the underlying API to set unsupported
 * functionalities.
 *
 **************************************************************************/

#include <rw/db/dbasecb.h>
#include <rw/db/dbref.h>
#include <rw/db/defs.h>


/**
 * \ingroup db_common_group
 *
 * \brief
 * Abstract base class from which all vendor-specific environment handles
 * must derive. Environment handles are methods that can set or retrieve
 * certain configuration parameters.
 *
 * RWDBEnvironmentHandle is a base class from which a family of
 * implementation-specific classes is derived.
 * RWDBDatabase::environmentHandle() returns a pointer to this base class.
 * To set connect time configuration parameters or configuration properties
 * for an entire application, the application downcasts this pointer to the
 * appropriate type, and uses its implementation-specific features. The
 * configuration parameters that an application can set vary widely among
 * vendors. Please see the guide for your Access Module.
 *
 * <b>DB XA Module:</b> Also see the chapter on using access modules with DB
 * XA functionality in the <em>DB XA Module User's Guide</em>.
 *
 * \note
 * You must link the appropriate DB Access Module directly with your
 * application in order to downcast an instance of RWDBEnvironmentHandle to
 * a particular database type. Using this class reduces the portability of
 * your application.
 *
 * \synopsis
 * #include <rw/db/envhandl.h>
 *
 * RWDBDatabase::connect(false);
 * RWDBDatabase myDbase = RWDBManager::database( ... );
 * RWDBEnvironmentHandle* envHandle = myDbase.environmentHandle();
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBEnvironmentHandle
    : public RWDBReference
{
public:
    /**
     * Constructs an empty RWDBEnvironmentHandle. This constructor is
     * provided as a convenience. A usable RWDBEnvironmentHandle should be
     * produced by an RWDBDatabase. See the guide for your Access Module for
     * specific details on how to use the methods of class
     * RWDBEnvironmentHandle.
     *
     * <b>DB XA Module:</b> Also see the chapter on using access modules
     * with DB XA functionality in the <em>DB XA Module User's Guide</em>.
     */
    RWDBEnvironmentHandle();

    virtual ~RWDBEnvironmentHandle();

    /**
     * Returns \c false.
     *
     * If this functionality is implemented by the Access Module specific
     * derived class, this function shall return \c true if a
     * higher-performance version of RWDBTable::foreignKeys() is used.
     * Returns \c false otherwise.
     */
    virtual bool foreignKeysFromView();

    /**
     * Returns \c false.
     *
     * If this functionality is implemented by the Access Module specific
     * derived class, passing \a value as \c true enables a
     * higher-performance version of RWDBTable::foreignKeys() to be used.
     * Passing \c false enables the standard version of
     * RWDBTable::foreignKeys() to be used. Returns the previous value.
     */
    virtual bool foreignKeysFromView(bool value);

    /**
     * Returns the state of the flag that controls whether to install and
     * use result schema caching.
     */
    bool cacheResultSchemas() const;

    /**
     * Enables or disables result schema caching. Result schema caching can
     * improve performance, but should not be used when database schemas are
     * dynamic. See Section 9.5, "Result Schema Caching," in the <em>DB
     * Interface Module User's Guide</em>.
     */
    bool cacheResultSchemas(bool value);

    /**
     * Returns the maximum number of result sets being cached from execution
     * of an SQL query. Result sets are cached by SourcePro DB when using a
     * Data Manipulation class.
     */
    size_t maxCachedResultSets() const;

    /**
     * Limits the number of result sets that are cached from execution of an
     * SQL query to \a value. Caching result sets improves performance for
     * subsequent executions of the same SQL, but if the SQL returns a large
     * number of result sets, or some number of very large sets, memory
     * usage can become an issue. The result sets are cached by SourcePro DB
     * when using a Data Manipulation class. The default value is \c 100.
     */
    size_t maxCachedResultSets(size_t value);

    //For internal use only:
    virtual void initialize();
    virtual const RWDBBufferFactory& bufferFactory() const;
    void databaseCallback(const RWDBDatabaseCallback& callback);
    RWDBDatabaseCallback databaseCallback() const;

protected:
    RWDBDatabaseCallback databasecb_;

private:
    bool cacheResultSchemas_;
    size_t maxCachedResultSets_;

    static const
    size_t defaultMaxCachedResultSets_;

    //Unimplemented:
    RWDBEnvironmentHandle(const RWDBEnvironmentHandle& handle);
    RWDBEnvironmentHandle& operator=(const RWDBEnvironmentHandle& handle);
};

#endif
