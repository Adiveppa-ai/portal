#ifndef __RWDB_DBASECB_H__
#define __RWDB_DBASECB_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/dbasecb.h#1 $
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

#include <rw/db/dbasecbi.h>
#include <rw/db/dbref.h>
#include <rw/db/defs.h>


//////////////////////////////////////////////////////////////////////////
//
// Macro Definition for instantiating an RWDBDatabaseCallback object
//
//////////////////////////////////////////////////////////////////////////
/**
 * \relates RWDBDatabaseCallback
 *
 * The macro takes as argument the name of the user-implemented database
 * callback implementation class. The user database callback implementation
 * class must have been derived from the RWDBDatabaseCallbackImp class.
 * Providing simply the name of the callback implementation class creates
 * its instance using its default constructor. To use a different
 * constructor, pass the arguments along with it. For example:
 * \code
 * RWDBDATABASECALLBACK(MyDBaseCallbackImp(100, "abc"))
 * \endcode
 * This macro must be used while supplying an instance of database callback
 * implementation class in the method RWDBManager::database(). This macro
 * ensures that a new instance of the database callback implementation class
 * is produced.
 */
#define RWDBDATABASECALLBACK(CALLBACK) RWDBDatabaseCallback(new CALLBACK)


/**
 * \ingroup db_execution_callbacks_group
 *
 * \brief
 * Handle class for database callbacks, encapsulating a reference-counted
 * pointer to the RWDBDatabaseCallbackImp body class.
 *
 * RWDBDatabaseCallback is the interface handle class for database callbacks
 * that encapsulate a reference-counted pointer to the
 * RWDBDatabaseCallbackImp body class. Please refer to the
 * RWDBDatabaseCallbackImp class for implementing database callbacks.
 *
 * \synopsis
 * #include <rw/db/dbasecb.h>
 *
 * RWDBDatabase dBase =
 *   RWDBManager::database("accessLib", "Servername",
 *                         "Username", "Password",
 *                         "DatabaseName",
 *  RWDBDATABASECALLBACK(MyDBaseCallbackImp));
 * \endsynopsis
 */
class RWDB_SYMBOLIC RWDBDatabaseCallback
{
public:

    /**
     * Default constructor that creates an uninitialized database callback
     * with all callback methods as no-ops. The status of the
     * RWDBDatabaseCallback will be RWDBStatus::notInitialized. This
     * constructor is provided for convenience; usable RWDBDatabaseCallback
     * objects must be obtained by using the macro
     * RWDBDATABASECALLBACK(CALLBACK).
     */
    RWDBDatabaseCallback();

    /**
     * Copy constructor. The object created shares an implementation with
     * \a dbasecb.
     */
    RWDBDatabaseCallback(const RWDBDatabaseCallback& dbasecb);

    RWDBDatabaseCallback(RWDBDatabaseCallbackImp* imp);
    ~RWDBDatabaseCallback();

    /**
     * Assignment operator. Self shares an implementation with \a dbasecb.
     * Returns a reference to self.
     */
    RWDBDatabaseCallback& operator=(const RWDBDatabaseCallback& dbasecb);

    /**
     * Returns a pointer to the database callback implementation
     * encapsulated by self.
     */
    RWDBDatabaseCallbackImp* operator()() const;

    // Callbacks
    void connParams(const RWCString& serverName, const RWCString& userName, RWCString& password,
                    const RWCString& databaseName, const RWCString& propertyString);
    void preEnvAllocate();
    void postEnvAllocate();
    void preEnvDestroy();

    // Connection callback producer
    RWDBConnCallback produceConnCallback();

    /**
     * Returns the current status of self.
     */
    RWDBStatus status() const;

    // Initialization
    // INTERNAL API. MAY NOT BE USED. API MAY CHANGE IN THE FUTURE.
    void init(RWDBDatabaseImp* db);

    // Default database callback
    // INTERNAL API. MAY NOT BE USED. API MAY CHANGE IN THE FUTURE.
    static RWDBDatabaseCallback& defaultCallback();

private:
    RWDBMTCountedRef<RWDBDatabaseCallbackImp> impl_;
};


//////////////////////////////////////////////////////////////////////////
//
// Constructors, destructor, operators
//
//////////////////////////////////////////////////////////////////////////
inline
RWDBDatabaseCallback::RWDBDatabaseCallback()
    : impl_(defaultCallback().impl_)
{
}

inline
RWDBDatabaseCallback::RWDBDatabaseCallback(RWDBDatabaseCallbackImp* imp)
    : impl_(imp)
{
}

inline
RWDBDatabaseCallback::RWDBDatabaseCallback(const RWDBDatabaseCallback& dbasecb)
    : impl_(dbasecb.impl_)
{
}

inline
RWDBDatabaseCallback::~RWDBDatabaseCallback()
{
}

inline
RWDBDatabaseCallback&
RWDBDatabaseCallback::operator=(const RWDBDatabaseCallback& dbasecb)
{
    impl_ = dbasecb.impl_;
    return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Implementation
//
//////////////////////////////////////////////////////////////////////////
inline
RWDBDatabaseCallbackImp*
RWDBDatabaseCallback::operator()() const
{
    return impl_;
}


//////////////////////////////////////////////////////////////////////////
//
// Error handling
//
//////////////////////////////////////////////////////////////////////////
inline
RWDBStatus
RWDBDatabaseCallback::status() const
{
    return impl_->status();
}


//////////////////////////////////////////////////////////////////////////
//
// Callbacks
//
//////////////////////////////////////////////////////////////////////////
inline
void
RWDBDatabaseCallback::connParams(const RWCString& serverName, const RWCString& userName, RWCString& password,
                                 const RWCString& databaseName, const RWCString& propertyString)
{
    impl_->connParams(serverName, userName, password, databaseName, propertyString);
}

inline
void
RWDBDatabaseCallback::preEnvAllocate()
{
    impl_->preEnvAllocate();
}

inline
void
RWDBDatabaseCallback::postEnvAllocate()
{
    impl_->postEnvAllocate();
}

inline
void
RWDBDatabaseCallback::preEnvDestroy()
{
    impl_->preEnvDestroy();
}


//////////////////////////////////////////////////////////////////////////
//
// Initialization
// INTERNAL API. MAY NOT BE USED. API MAY CHANGE IN THE FUTURE.
//
//////////////////////////////////////////////////////////////////////////
inline
void
RWDBDatabaseCallback::init(RWDBDatabaseImp* db)
{
    impl_->init(db);
}


#endif // __RWDB_DBASECB_H__
