#ifndef __RWDB_CONNCB_H__
#define __RWDB_CONNCB_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/conncb.h#1 $
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

#include <rw/db/conncbi.h>
#include <rw/db/dbref.h>
#include <rw/db/defs.h>


/**
 * \relates RWDBConnCallback
 * This macro takes as a parameter the name of an implemented connection
 * callback implementation class, which must derive from
 * RWDBConnCallbackImp. To create an instance with the default constructor,
 * just provide the name of the class. To use a different constructor, pass
 * the parameter values along with it. For example:
 * \code
 * RWDBCONNCALLBACK(MyConnCallbackImp("abc", 1248))
 * \endcode
 * This macro must be used while supplying an instance of the connection
 * callback implementation class in the method RWDBDatabase::connection() or
 * while producing new connection callbacks in the method redefined from
 * RWDBDatabaseCallbackImp::produceConnCallback(). This macro ensures that a
 * new instance of the connection callback implementation class is produced.
 */
#define RWDBCONNCALLBACK(CALLBACK) RWDBConnCallback(new CALLBACK)


/**
 * \ingroup db_execution_callbacks_group
 *
 * \brief
 * Handle class for connection callbacks that encapsulate a
 * reference-counted pointer to the RWDBConnCallbackImp body class.
 *
 * RWDBConnCallback is the interface handle class for connection callbacks
 * that encapsulate a reference-counted pointer to the RWDBConnCallbackImp
 * body class. Please refer to the RWDBConnCallbackImp class for
 * implementing connection callbacks.
 *
 * \synopsis
 * #include <rw/db/conncb.h>
 *
 * RWDBConnection connection = myDbase.connection(RWDBCONNCALLBACK(MyConnCallbackImp) );
 * \endsynopsis
 */
class RWDB_SYMBOLIC RWDBConnCallback
{
public:

    // Constructors, destructor, assignment operator

    /**
     * The default constructor creates an uninitialized connection callback
     * with all callback methods as no-ops. The status of the
     * RWDBConnCallback will be RWDBStatus::notInitialized. This constructor
     * is provided for convenience; usable RWDBConnCallback objects must be
     * obtained by using the macro RWDBCONNCALLBACK(CALLBACK).
     */
    RWDBConnCallback();

    /**
     * Copy constructor. The object created shares an implementation with
     * \a conncb.
     */
    RWDBConnCallback(const RWDBConnCallback& conncb);

    RWDBConnCallback(RWDBConnCallbackImp* imp);
    ~RWDBConnCallback();

    /**
     * Assignment operator. Self shares an implementation with \a conncb.
     * Returns a reference to self.
     */
    RWDBConnCallback& operator=(const RWDBConnCallback& conncb);

    /**
     * Returns a pointer to the connection callback implementation
     * encapsulated by self.
     */
    RWDBConnCallbackImp* operator()() const;

    // Callbacks
    void preConnAllocate();
    void postConnAllocate();
    void preConnect();
    void postConnect();
    void preDisconnect();
    void preConnDestroy();

    /**
     * Returns the RWDBDatabaseCallback associated with the RWDBDatabase
     * object that produced the RWDBConnection object associated with self.
     */
    RWDBDatabaseCallback databaseCallback() const;

    /**
     * Returns the current status of self.
     */
    RWDBStatus status() const;

    // Initialization
    // INTERNAL API. MAY NOT BE USED. API MAY CHANGE IN THE FUTURE.
    void init(RWDBConnectionImp* conn);

    // Default connection callback
    // INTERNAL API. MAY NOT BE USED. API MAY CHANGE IN THE FUTURE.
    static RWDBConnCallback& defaultCallback();

private:
    RWDBCountedRef<RWDBConnCallbackImp> impl_;
};


//////////////////////////////////////////////////////////////////////////
//
// Constructors, destructor, operators
//
//////////////////////////////////////////////////////////////////////////
inline
RWDBConnCallback::RWDBConnCallback()
    : impl_(defaultCallback().impl_)
{
}

inline
RWDBConnCallback::RWDBConnCallback(RWDBConnCallbackImp* imp)
    : impl_(imp)
{
}

inline
RWDBConnCallback::RWDBConnCallback(const RWDBConnCallback& conncb)
    : impl_(conncb.impl_)
{
}

inline
RWDBConnCallback::~RWDBConnCallback()
{
}

inline
RWDBConnCallback&
RWDBConnCallback::operator=(const RWDBConnCallback& conncb)
{
    impl_ = conncb.impl_;
    return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Implementation
//
//////////////////////////////////////////////////////////////////////////
inline
RWDBConnCallbackImp*
RWDBConnCallback::operator()() const
{
    return impl_;
}


//////////////////////////////////////////////////////////////////////////
//
// Callbacks
//
//////////////////////////////////////////////////////////////////////////
inline
void
RWDBConnCallback::preConnAllocate()
{
    impl_->preConnAllocate();
}

inline
void
RWDBConnCallback::postConnAllocate()
{
    impl_->postConnAllocate();
}

inline
void
RWDBConnCallback::preConnect()
{
    impl_->preConnect();
}

inline
void
RWDBConnCallback::postConnect()
{
    impl_->postConnect();
}

inline
void
RWDBConnCallback::preDisconnect()
{
    impl_->preDisconnect();
}

inline
void
RWDBConnCallback::preConnDestroy()
{
    impl_->preConnDestroy();
}


//////////////////////////////////////////////////////////////////////////
//
// Error handling
//
//////////////////////////////////////////////////////////////////////////
inline
RWDBStatus
RWDBConnCallback::status() const
{
    return impl_->status();
}


//////////////////////////////////////////////////////////////////////////
//
// Initialization
//
//////////////////////////////////////////////////////////////////////////
inline
void
RWDBConnCallback::init(RWDBConnectionImp* conn)
{
    impl_->init(conn);
}


#endif // __RWDB_CONNCB_H__
