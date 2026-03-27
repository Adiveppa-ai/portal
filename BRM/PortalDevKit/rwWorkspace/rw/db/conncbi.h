#ifndef __RWDB_CONNCBI_H__
#define __RWDB_CONNCBI_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/conncbi.h#1 $
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

//////////////////////////////////////////////////////////////////////////
//
// RWDBConnCallbackImp (abstract)
//
//   Reference counted implementation class for connection callbacks.
//   Users need to derive from this class to implement connection
//   callbacks.
//
//   The class provides six callbacks:
//     preConnAllocate
//         This callback is invoked just before the allocation of the
//         database specific connection handle. All the SourcePro DB
//         configuration before the allocation is complete.
//     postConnAllocate
//         This callback is invoked just after the allocation of the
//         database specific connection handle. None of the SourcePro DB
//         properties have been set on the connection handle.
//     preConnect
//         This callback is invoked just before establishing the database
//         connection. All the SourcePro DB configuration before
//         establishing connection is complete.
//     postConnect
//         This callback is invoked after establishing the database
//         connection. The callback is invoked after all the SourcePro DB
//         default properties have been set.
//     preDisconnect
//         This callback is invoked just before disconnecting the database
//         server connection. All the SourcePro DB configuration before
//         the disconnect is complete.
//     preConnDestroy
//         This callback is invoked just before the deallocation of
//         connection handle. All the SourcePro DB configuration before
//         the deallocation is complete.
//
//////////////////////////////////////////////////////////////////////////

/**
 * \ingroup db_execution_callbacks_group
 *
 * \brief
 * Abstract base class from which all custom connection callbacks must
 * derive.
 *
 * RWDBConnCallbackImp is an abstract base implementation class used for
 * implementing connection callbacks. It is reference counted.
 *
 * You must derive from this class to implement your custom connection
 * callbacks.
 *
 * This class provides six connection callback methods that you must
 * redefine in your derived class: preConnAllocate(), postConnAllocate(),
 * preConnect(), postConnect(), preDisconnect() and preConnDestroy().
 *
 * Please refer to the <em>DB Interface Module User's Guide</em> and the
 * applicable <em>DB Access Module User's Guide</em> for more information on
 * these methods.
 *
 * \synopsis
 * #include <rw/db/conncbi.h>
 *
 * class MyConnCallbackImp : public RWDBConnCallbackImp {
 * public:
 *     // PreConnect callback
 *     virtual void preConnect();
 *
 *     // PostConnect callback
 *     virtual void postConnect();
 * };
 *
 * RWDBConnection connection = myDbase.connection(RWDBCONNCALLBACK(MyConnCallbackImp));
 * \endsynopsis
 */
class RWDB_GLOBAL RWDBConnCallbackImp
    : public RWDBReference
{
public:
    // Destructor
    virtual ~RWDBConnCallbackImp();

    /**
     * This callback is invoked just before the allocation of the
     * database-specific connection handle. It is defined as a no-op. To
     * implement it, derive from this class and redefine this method.
     */
    virtual void preConnAllocate();

    /**
     * This callback is invoked just after the allocation of the
     * database-specific connection handle. It is defined as a no-op. To
     * implement it, derive from this class and redefine this method.
     */
    virtual void postConnAllocate();

    /**
     * This callback is invoked just before establishing the database
     * connection. It is defined as a no-op. To implement it, derive from
     * this class and redefine this method.
     */
    virtual void preConnect();

    /**
     * This callback is invoked after establishing the database connection.
     * It is defined as a no-op. To implement it, derive from this class and
     * redefine this method.
     */
    virtual void postConnect();

    /**
     * This callback is invoked just before the database connection is
     * closed. It is defined as a no-op. To implement it, derive from this
     * class and redefine this method. This callback is typically called
     * from the destructor of an RWDBConnection object and therefore, you
     * should refrain from throwing an exception.
     */
    virtual void preDisconnect();

    /**
     * This callback is invoked just before the deallocation of the
     * connection handle. It is defined as a no-op. To implement it, derive
     * from this class and redefine this method. This callback is typically
     * called from the destructor of an RWDBConnection object and therefore,
     * you should refrain from throwing an exception.
     */
    virtual void preConnDestroy();

    /**
     * Returns the RWDBDatabaseCallback associated with the RWDBDatabase
     * object that produced the RWDBConnection object associated with self.
     * If self is not associated with any RWDBConnection object, this
     * callback returns an uninitialized RWDBDatabaseCallback object.
     */
    RWDBDatabaseCallback databaseCallback() const;

    /**
     * Returns a pointer to the RWDBEnvironmentHandle of the RWDBDatabase
     * object that produced the RWDBConnection object associated with self.
     * If self is not associated with any RWDBConnection object, returns
     * \c 0.
     */
    RWDBEnvironmentHandle* environmentHandle() const;

    /**
     * Returns a pointer to the RWDBSystemHandle of the RWDBConnection
     * object associated with self. If self is not associated with any
     * RWDBConnection object, returns \c 0.
     */
    RWDBSystemHandle* systemHandle() const;

    /**
     * Returns the current status of self.
     */
    RWDBStatus status() const;

    /**
     * Sets error on self. Optionally, invalidates the RWDBConnection object
     * associated with self.
     *
     * Parameters \a code, \a message, \a vendorMessage1, \a vendorMessage2,
     * \a vendorError1, \a vendorError2 and \a isTerminal are RWDBStatus
     * attributes used to set an error on self's RWDBStatus object.
     *
     * Parameter \a invokeErrorHandler indicates if the associated error
     * handler should be invoked.
     *
     * Parameter \a invalidateConnection indicates whether the
     * RWDBConnection object associated with self should be invalidated. If
     * invalidated, the RWDBConnection object will have an error code of
     * RWDBStatus::applicationError.
     */
    void setError(RWDBStatus::ErrorCode code,
                  const RWCString&      message,
                  const RWCString&      vendorMessage1 = RWCString(),
                  const RWCString&      vendorMessage2 = RWCString(),
                  long                  vendorError1 = 0,
                  long                  vendorError2 = 0,
                  bool             isTerminal = false,
                  bool             invokeErrorHandler = true,
                  bool             invalidateConnection = false);

    // Initialization
    // INTERNAL API. MAY NOT BE USED OR REDEFINED. API MAY CHANGE
    // IN THE FUTURE.
    virtual void init(RWDBConnectionImp* conn);

protected:
    /**
     * The default protected constructor.
     */
    RWDBConnCallbackImp();

private:
    // RWDBConnection object to which this callback object is associated
    RWDBConnectionImp* conn_;
    // Status of this callback object
    RWDBStatus status_;

    // not implemented:
    RWDBConnCallbackImp(const RWDBConnCallbackImp&);
    RWDBConnCallbackImp& operator=(const RWDBConnCallbackImp&);
};


//////////////////////////////////////////////////////////////////////////
//
// Constructor
//
//////////////////////////////////////////////////////////////////////////
inline
RWDBConnCallbackImp::RWDBConnCallbackImp()
    : conn_(0)
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
RWDBConnCallbackImp::status() const
{
    return status_;
}


//////////////////////////////////////////////////////////////////////////
//
// RWDBConnDefaultCallbackImp
//
//   INTERNAL CLASS. MAY NOT BE USED OR DERIVED FROM.
//   API MAY CHANGE IN THE FUTURE.
//
//////////////////////////////////////////////////////////////////////////
class RWDB_GLOBAL RWDBConnDefaultCallbackImp
    : public RWDBConnCallbackImp
{
public:
    // Initialization
    virtual void init(RWDBConnectionImp* conn);
};


#endif // __RWDB_CONNCBI_H__
