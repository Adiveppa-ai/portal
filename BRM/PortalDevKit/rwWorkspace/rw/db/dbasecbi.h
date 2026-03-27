#ifndef __RWDB_DBASECBI_H__
#define __RWDB_DBASECBI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbasecbi.h#1 $
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

#include <rw/db/dbref.h>
#include <rw/db/defs.h>
#include <rw/db/status.h>

/**
 * \ingroup db_execution_callbacks_group
 *
 * \brief
 * Abstract base class from which all custom database callbacks derive.
 *
 * RWDBDatabaseCallbackImp is a reference-counted implementation class that
 * is the abstract base class for implementing database callbacks. Derive
 * from this class to implement your custom database callbacks.
 *
 * This class provides three database callback methods: preEnvAllocate(),
 * postEnvAllocate() and preEnvDestroy(). It also provides a connection
 * callback producer method produceConnCallback(). Please refer to the
 * <em>DB Interface Module User's Guide</em> and applicable <em>DB Access
 * Module User's Guide</em> for more information on these methods. You need
 * to redefine the methods to implement database callbacks and/or produce
 * connection callback instances.
 *
 * \synopsis
 * #include <rw/db/dbasecbi.h>
 *
 * class MyDBaseCallbackImp : public RWDBDatabaseCallbackImp {
 * public:
 *     // PostEnvAllocate callback
 *     virtual void postEnvAllocate();
 *
 *     // Connection callback producer
 *     virtual RWDBConnCallback produceConnCallback();
 * };
 *
 * RWDBDatabase dBase =
 *   RWDBManager::database("accessLib", "Servername",
 *                         "Username", "Password",
 *                         "DatabaseName",
 *              RWDBDATABASECALLBACK(MyDBaseCallbackImp) );
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBDatabaseCallbackImp
    : public RWDBReference
{
public:
    // Destructor
    virtual ~RWDBDatabaseCallbackImp();


    /**
     * This callback is invoked just before opening a connection to the
     * database. It passes to the callback function the parameters used to
     * establish a database connection. All the parameters, except
     * \a password, are passed as \c const and so cannot be modified. The
     * \a password set during this call will be used to open a connection to
     * the database. To implement \c connParams() callback, derive from this
     * class and redefine this method.
     */
    virtual void connParams(const RWCString& serverName, const RWCString& userName, RWCString& password,
                            const RWCString& databaseName, const RWCString& propertyString);

    /**
     * This callback is invoked just before the allocation of
     * database-specific environment/context handle. It is defined as a
     * no-op. To implement preEnvAllocate callback, derive from this class
     * and redefine this method.
     */
    virtual void preEnvAllocate();

    /**
     * This callback is invoked after the allocation of
     * database-specific-environment/context handle. It is defined as a
     * no-op. To implement postEnvAllocate callback, derive from this class
     * and redefine this method.
     */
    virtual void postEnvAllocate();

    /**
     * This callback is invoked just before the deallocation of
     * environment/context handle. It is defined as a no-op. To implement
     * preEnvDestroy callback, derive from this class and redefine this
     * method. This callback is typically called from the destructor of the
     * RWDBDatabase object and, hence, applications should refrain from
     * throwing an exception.
     */
    virtual void preEnvDestroy();

    /**
     * Returns a pointer to the RWDBEnvironmentHandle of the RWDBDatabase
     * object to which self is associated. If self is not associated with
     * any RWDBDatabase object, returns \c 0.
     */
    RWDBEnvironmentHandle* environmentHandle() const;

    /**
     * Returns the \ref RWDBDatabase::serverType() "serverType" of the
     * RWDBDatabase object to which self is associated. If self is not
     * associated with any RWDBDatabase object, returns an empty string.
     */
    RWCString serverType() const;

    /**
     * This method must produce a new instance of a connection callback
     * implementation.
     *
     * An RWDBDatabase object invokes this method when producing a new
     * RWDBConnection object. The RWDBConnCallback object produced by this
     * method is then associated with the new RWDBConnection.
     *
     * Note that this method produces an \e uninitialized connection
     * callback object with all connection callbacks as no-ops. To produce
     * custom connection callbacks, derive from this class and redefine this
     * method to produce new instances of connection callbacks using the
     * macro RWDBCONNCALLBACK(CALLBACK).
     *
     * For example:
     *
     * \code
     * RWDBConnCallback
     * MyDBaseCallbackImp::produceConnCallback()
     * {
     *     return RWDBCONNCALLBACK(MyConnCallbackImp);
     * }
     * \endcode
     */
    virtual RWDBConnCallback produceConnCallback();

    /**
     * Returns the current status of self.
     */
    RWDBStatus status() const;

    /**
     * Sets an error on self. Optionally, invalidates the RWDBDatabase
     * object to which self is associated.
     *
     * \param code
     * RWDBStatus attribute used to set the error on self's RWDBStatus
     * object.
     *
     * \param message
     * RWDBStatus attribute used to set the error on self's RWDBStatus
     * object.
     *
     * \param vendorMessage1
     * RWDBStatus attribute used to set the error on self's RWDBStatus
     * object.
     *
     * \param vendorMessage2
     * RWDBStatus attribute used to set the error on self's RWDBStatus
     * object.
     *
     * \param vendorError1
     * RWDBStatus attribute used to set the error on self's RWDBStatus
     * object.
     *
     * \param vendorError2
     * RWDBStatus attribute used to set the error on self's RWDBStatus
     * object.
     *
     * \param isTerminal
     * RWDBStatus attribute used to set the error on self's RWDBStatus
     * object.
     *
     * \param invokeErrorHandler
     * Indicates if the associated error handler should be invoked.
     *
     * \param invalidateDatabase
     * Indicates if the RWDBDatabase object to which self is associated
     * should be invalidated. If invalidated, the RWDBDatabase object has an
     * error code of RWDBStatus::applicationError.
     */
    void setError(RWDBStatus::ErrorCode code,
                  const RWCString&      message,
                  const RWCString&      vendorMessage1 = RWCString(),
                  const RWCString&      vendorMessage2 = RWCString(),
                  long                  vendorError1 = 0,
                  long                  vendorError2 = 0,
                  bool             isTerminal = false,
                  bool             invokeErrorHandler = true,
                  bool             invalidateDatabase = false);

    // Initialization
    // INTERNAL API. MAY NOT BE USED OR REDEFINED. API MAY CHANGE
    // IN THE FUTURE.
    virtual void init(RWDBDatabaseImp* db);

protected:

    /**
     * The default protected constructor.
     */
    RWDBDatabaseCallbackImp();

private:
    // RWDBDatabase object to which this callback object is associated
    RWDBDatabaseImp* dbase_;
    // Status of this callback object
    RWDBStatus status_;

    // Not implemented:
    RWDBDatabaseCallbackImp(const RWDBDatabaseCallbackImp&);
    RWDBDatabaseCallbackImp& operator=(const RWDBDatabaseCallbackImp&);
};


//////////////////////////////////////////////////////////////////////////
//
// Constructor
//
//////////////////////////////////////////////////////////////////////////
inline
RWDBDatabaseCallbackImp::RWDBDatabaseCallbackImp()
    : dbase_(0)
    , status_(RWDBStatus::notInitialized)
{
}

//////////////////////////////////////////////////////////////////////////
//
// Error handling
//
//////////////////////////////////////////////////////////////////////////
inline
RWDBStatus
RWDBDatabaseCallbackImp::status() const
{
    return status_;
}


//////////////////////////////////////////////////////////////////////////
//
// RWDBDatabaseDefaultCallbackImp
//
//   INTERNAL CLASS. MAY NOT BE USED OR DERIVED FROM.
//   API MAY CHANGE IN THE FUTURE.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBDatabaseDefaultCallbackImp
    : public RWDBDatabaseCallbackImp
{
public:
    // Initialization
    virtual void init(RWDBDatabaseImp* db);
};


#endif // __RWDB_DBASECBI_H__
