#ifndef __RWDB_DBMGR_H__
#define __RWDB_DBMGR_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbmgr.h#1 $
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

#include <rw/db/dbasecb.h>
#include <rw/db/defs.h>
#include <rw/db/status.h>


/**
 * \ingroup db_common_group
 *
 * \brief
 * A monostate class that manages RWDBDatabase instances, thus mediating
 * access to database servers.
 *
 * There is a single, global RWDBManager in charge of producing RWDBDatabase
 * instances typed according to the application's request. It mediates
 * access to database servers, abstracting details of access to
 * vendor-supplied libraries, including any dynamic loading and linking. The
 * RWDBManager, through its database() method, is responsible for filling
 * requests for database implementations of a particular type. To do so, it
 * maintains a set of database types for which it is able to produce an
 * implementation.
 *
 * Associated with each database type is a method that produces the
 * implementation. Once this method is invoked, a connection is established
 * and the result is returned to the caller. In a static build, this method
 * resides in the statically linked Access Module library. In a dynamic
 * build, this method resides in the dynamically-linked Access Module
 * library that is loaded at runtime.
 *
 * \synopsis
 * #include <rw/db/dbmgr.h>
 *
 * RWDBDatabase myDbase = RWDBManager::database("myDbaseType",
 *                         "myDbaseServerName", "myLoginName",
 *                         "myPassword", "myDbaseName");
 * \endsynopsis
 *
 * <h4>DB XA Module</h4>
 * For the DB XA Module you provide a sixth parameter, \c propertyString,
 * defined with key <tt>XA=\e xaParameter</tt>. This produces an XA-enabled
 * RWDBDatabase object. For database-specific values of \c xaParameter, see
 * the <em>DB XA Module User's Guide</em>.
 *
 * \code
 * RWDBDatabase myDbase = RWDBManager::database("myDbaseType",
 *                        "", "", "", "", "XA=xaParameter");
 * \endcode
 *
 * \internal
 * Associated with each database type is a method that produces the
 * implementation. This method may reside in a dynamically-linked library,
 * or may be statically linked with a specialized object. In the former
 * case, the method is identified by a conventional name,
 * \c rwdbNewDatabaseImp, with any ambiguity alleviated by the containing
 * library. In the latter case, each method must be uniquely named, as in
 * \c rwdbNewSybaseDatabaseImp, for example. The association between method
 * names and database types is made at link time via static initialization.
 *
 * When presented with a request for a particular type of database
 * implementation, the RWDBManager consults its set of known
 * implementations. If no entry is found, and the operating environment
 * supports dynamic linking, a search is made for a dynamically-linked
 * library (DLL) whose name matches the requested type. If a DLL is found,
 * it is loaded, the conventionally-named method is located, and the
 * association is added to the set of implementations of the RWDBManager.
 * Once an entry is located, its method is invoked to obtain an
 * implementation of the requested type, a connection is established, and
 * the result is returned to the caller. If no entry is found, the object
 * returned to the caller has a status of RWDBStatus::notFound.
 */
class RWDB_GLOBAL RWDBManager
{
public:

    /**
     * Produces an RWDBDatabase. The first parameter lets the DB Interface
     * Module identify the kind of database being requested. The remaining
     * parameters except the last are used to establish a session with the
     * requested database server. Since the details of logging into a
     * database vary widely among vendors, the actual values supplied for
     * the various parameters vary according to the DB Access Module which
     * will be used. Your DB Access Module guide explains the values you
     * must supply to obtain RWDBDatabase instances from your library. The
     * last parameter provides an instance of the RWDBDatabaseCallback to be
     * associated with the produced RWDBDatabase object.
     *
     * \note
     * If no Access Module library is found for the \a serverType requested,
     * the object being returned has a status of RWDBStatus::notFound.
     */
    static RWDBDatabase database(const RWCString& serverType,
                                 const RWCString& serverName,
                                 const RWCString& userName,
                                 const RWCString& password,
                                 const RWCString& databaseName,
                                 const RWDBDatabaseCallback& databasecb
                                 = RWDBDatabaseCallback());
    /**
     * \copydoc database(const RWCString&, const RWCString&, const RWCString&, const RWCString&, const RWCString&, const RWDBDatabaseCallback&)
     *
     * <b>DB XA Module:</b> The sixth parameter, \a propertyString, is used
     * to set the key <tt>XA=\e xaParameter</tt>.
     */
    static RWDBDatabase database(const RWCString& serverType,
                                 const RWCString& serverName,
                                 const RWCString& userName,
                                 const RWCString& password,
                                 const RWCString& databaseName,
                                 const RWCString& propertyString,
                                 const RWDBDatabaseCallback& databasecb
                                 = RWDBDatabaseCallback());



    static RWDBDatabase database(const RWCString& serverType,
                                 const RWCString& serverName,
                                 const RWCString& userName,
                                 const RWCString& password,
                                 const RWCString& databaseName,
                                 const RWCString& role,
                                 const RWCString& propertyString,
                                 const RWDBDatabaseCallback& databasecb
                                 = RWDBDatabaseCallback());

    /**
     * Installs \a handler as the error handler for the RWDBManager. The
     * supplied \a handler is inherited by all RWDBDatabase instances
     * created by the RWDBManager. By default, the RWDBManager error handler
     * does nothing; this method overrides the default.
     */
    static RWDBStatus::ErrorHandler     setErrorHandler(
        RWDBStatus::ErrorHandler handler);

    /**
     * Retrieves the error handler currently installed in the RWDBManager,
     * if any.
     */
    static RWDBStatus::ErrorHandler     errorHandler();

    /**
     * Returns a string that identifies the version of the DB Interface
     * Module in which self resides.
     *
     * \note
     * This method does not identify the version of the DB Access Module
     * being used. To see the DB Access Module Version, use
     * RWDBDatabase::version().
     */
    static RWCString                    version();

    /**
     * Retrieves the setting of this flag.
     */
    static bool                    emptyStringIsNull();

    /**
     * Allows an application to specify whether the RWDBDatabase instance
     * produced by the call to RWDBManager::database() treats empty strings
     * as \c NULL values.
     *
     * The default setting is \c false, which means that empty strings are
     * handled as the database vendor normally handles them. If this flag is
     * set to \c true, empty strings are treated as \c NULL values by
     * SourcePro DB.
     *
     * Note that the SQL92 standard does not specify if empty strings are
     * \c NULL values or not. Various database vendors treat empty strings
     * differently. For example, Oracle considers an empty string to be the
     * same as a \c NULL, while other database vendors do not. Consider the
     * following example:
     *
     * \code
     * RWCString  empty;
     * RWDBInserter  ins=aTbl.inserter();
     * ins<<empty;
     * ins.execute();
     * \endcode
     *
     * If the setting is \c true, the SQL generated is like:
     *
     * \code
     * insert into sometable values(NULL)
     * \endcode
     *
     * Otherwise, it is like:
     *
     * \code
     * insert into sometable values('')
     * \endcode
     *
     * However, these two SQL statements mean the same to Oracle. Setting
     * the flag to \c true has no effect.
     */
    static void                         emptyStringIsNull(bool n);

    /**
     * <b>DB XA Module Only</b>
     *
     * Returns a database-specific XA switch table based on the server type.
     * The switch table is a structure that lists the names of the \c xa_
     * routines implemented in the resource manager. Note that this function
     * returns a \c void*, which must be cast to a
     * <tt>struct xa_switch_t</tt> pointer.
     */
    static void*                        xaSwitch(const RWCString& serverType);

protected:
    static void                       getConnection(const RWDBDatabase& db);

    static void                       add(const RWCString& serverType,
                                          RWDBNewImpFunc DbImp,
                                          RWDBNewImpFunc xaDbImp,
                                          RWDBXASwitchFunc xaSwitch);

private:
    static RWDBStatus::ErrorHandler&    getErrorHandler();
    static bool emptyStringIsNull_;
};

#endif
