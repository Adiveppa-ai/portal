#ifndef __RWDB_CONNECT_H__
#define __RWDB_CONNECT_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/connect.h#1 $
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

#include <rw/db/cursor.h>
#include <rw/db/defs.h>
#include <rw/db/handle.h>
#include <rw/db/status.h>

/**
 * \ingroup db_common_group
 * \class RWDBConnection
 *
 * \brief
 * Represents an explicit database connection object that can be used in
 * place of the implicit database connection provided by RWDBDatabase.
 *
 * Connections represent a scarce resource that applications can allocate
 * and manage themselves. An RWDBConnection is an object that may be
 * requested from an RWDBDatabase, and passed to many methods to specify
 * that the method should use the given connection. Operations requested
 * without supplying a connection are performed using a connection supplied
 * invisibly by RWDBDatabase. If none are available, an error results. Thus,
 * the use of explicit connections eliminates one likely source of errors,
 * at some cost in program complexity.
 *
 * Each RWDBConnection knows which RWDBDatabase produced it, and each
 * RWDBDatabase knows the connections it has produced.
 *
 * RWDBConnection is designed around the Interface/Implementation paradigm.
 * An RWDBConnection instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation. An RWDBConnection
 * implementation is a base class from which a family of database-specific
 * connection implementations is derived.
 *
 * \synopsis
 * #include <rw/db/connect.h>
 *
 * RWDBConnection connection = myDbase.connection();
 * \endsynopsis
 *
 * <h4>DB XA Module</h4>
 * In an XA environment, connections are opened and managed by the
 * transaction processing monitor, based on criteria defined during the
 * set-up phase of the resource manager. An RWDBConnection in this
 * environment does not have the responsibility of opening and closing a
 * database connection directly with the server. Instead, it attempts to get
 * a valid handle to a connection previously opened by the TPM. This handle
 * is held, and used whenever it is needed.
 *
 * Even though the TPM actually establishes connections, your programs will
 * still request RWDBConnection objects from an RWDBDatabase.
 *
 * The DB Interface Module restricts the number of RWDBConnection objects
 * you can create. This is because the DB Interface Module makes use of
 * connections opened by the TPM. Therefore, you should be careful when
 * using default connections. If the number of connections requested is
 * greater than one, the DB Interface Module returns a
 * RWDBStatus::notSupported error (with the exception of Sybase).
 *
 * \note
 * We recommend that you always use explicit connections.
 *
 * Because the TPM actually opens and closes connections, the following
 * RWDBConnection member functions should \b not be called when using the DB
 * Interface Module: open() and close().
 *
 * Transactions in an XA environment are controlled by the TPM. Therefore,
 * the following methods should \b not be called in an XA connection:
 * beginTransaction(), commitTransaction(), and rollbackTransaction().
 */
class RWDB_SYMBOLIC RWDBConnection
{
public:

    /**
     * These are the values used for the isolation() methods:
     */
    enum IsolationType {

        /**
         * Isolation level is set to Unknown.
         */
        Unknown,

        /**
         * Isolation level is set to ANSI Level 1.
         */
        ANSILevel1,

        /**
         * Isolation level is set to ANSI Level 2.
         */
        ANSILevel2,

        /**
         * Isolation level is set to ANSI Level 3.
         */
        ANSILevel3
    };

    /**
     * These are the values used for the connectionType() methods:
     */
    enum ConnectionType {

        /**
         * Connection type is set to Synchronous.
         */
        Synchronous = 1,

        /**
         * Connection type is set to Asynchronous.
         */
        Asynchronous
    };

    /**
     * The default constructor creates an RWDBConnection with a status of
     * RWDBStatus::notInitialized. This constructor is provided as a
     * convenience, for example, for declaring an array of RWDBConnection
     * instances. Usable RWDBConnection objects are obtained from an
     * RWDBDatabase.
     */
    RWDBConnection();

    RWDBConnection(RWDBConnectionImp* imp);

    /**
     * Copy constructor. The created object shares an implementation with
     * \a connection.
     */
    RWDBConnection(const RWDBConnection& connection);

    /**
     * Assignment operator. Self shares an implementation with
     * \a connection.
     */
    RWDBConnection&       operator=(const RWDBConnection& connection);

    ~RWDBConnection();

    /**
     * Reopens this connection after closing or an error condition. If the
     * connection cannot be opened for use, both the status returned and the
     * connection will be invalid.
     *
     * <b>DB XA Module:</b> Returns a RWDBStatus::notSupported error.
     */
    RWDBStatus            open();

    /**
     * Closes this connection. This method should only be used in
     * exceptional circumstances, as it causes all references to this
     * connection to become unusable. It is usually best to allow
     * connections to close themselves as they go out of scope.
     *
     * <b>DB XA Module:</b> Returns a RWDBStatus::notSupported error.
     */
    RWDBStatus            close();

    /**
     * Provides access to the RWDBDatabase that produced the connection.
     */
    RWDBDatabase          database() const;

    /**
     * Sends a <tt>begin transaction</tt>, or the vendor-specific
     * equivalent, to the database server. Here \a name means the name of
     * the transaction, if you choose to supply it and the vendor supports
     * named transactions. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> Returns a RWDBStatus::notSupported error.
     */
    RWDBStatus            beginTransaction(const RWCString& name = RWCString());

    /**
     * Sends a <tt>commit transaction</tt>, or the vendor-specific
     * equivalent, to the database server. Here \a name means the name of
     * the transaction, if you choose to supply it and the vendor supports
     * named transactions. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> Returns a RWDBStatus::notSupported error.
     */
    RWDBStatus            commitTransaction(const RWCString& name = RWCString());

    /**
     * Sends a <tt>rollback transaction</tt>, or the vendor-specific
     * equivalent, to the database server. Here \a name means the name of
     * the transaction, if you choose to supply it and the vendor supports
     * named transactions. This function can behave asynchronously if
     * executed using an asynchronous connection.
     *
     * <b>DB XA Module:</b> Returns a RWDBStatus::notSupported error.
     */
    RWDBStatus            rollbackTransaction(const RWCString& name = RWCString());

    /**
     * Sends a \c savepoint \a name or the vendor-specific equivalent to the
     * database server.
     */
    RWDBStatus            setSavepoint(const RWCString& name);

    /**
     * Makes a database-specific call or calls to set self's isolation level
     * to the specified \a level. The details vary widely among database
     * vendor implementations. This function can behave asynchronously if
     * executed using an asynchronous connection. See your DB Access Module
     * guide and your database vendor's manual for exact details on
     * isolation levels.
     */
    RWDBStatus            isolation(IsolationType level);

    /**
     * Returns self's isolation level, as defined by the most recent call to
     * isolation(IsolationType). If isolation(IsolationType) has not been
     * called, returns #Unknown. In this case, self's isolation level is
     * whatever the database vendor provides by default.
     */
    IsolationType         isolation() const;

    /**
     * Returns the connection type of self. An RWDBConnection can be
     * #Synchronous or #Asynchronous.
     */
    ConnectionType        connectionType() const;

    RWDBHandle            handle() const;
    RWDBHandle            handle(RWDBCursor::CursorType type,
                                 RWDBCursor::CursorAccess access) const;

    /**
     * This member allows an application to gain access to the underlying
     * vendor-specific database API. The result is a pointer to the base
     * class RWDBSystemHandle, which must be cast by the application to a
     * derived class representing a database-specific system handle. This
     * can be done in a type-safe manner if your compiler supports runtime
     * type identification. See your DB Access Module guide for details on
     * the name and contents of the database-specific system handle
     * variants.
     *
     * <b>DB XA Module:</b> See the chapter on using the DB access modules
     * with XA functionality in the <em>DB XA Module User's Guide</em>.
     */
    RWDBSystemHandle*     systemHandle() const;

    /**
     * Provides the current status of this connection.
     */
    RWDBStatus               status() const;

    /**
     * Returns \c true if the status of this connection is RWDBStatus::ok,
     * otherwise returns \c false.
     */
    bool                isValid() const;

    /**
     * This function returns \c true if the object is in ready state,
     * indicating that accessing the object will not block. Accessing a
     * nonready object may potentially block.
     */
    bool                isReady() const;

    /**
     * Installs \a handler as the error handler for self. The supplied
     * handler is called whenever the status of self changes to anything
     * except RWDBStatus::ok. By default, the RWDBStatus::ErrorHandler is
     * inherited from the RWDBDatabase that produced self; this method
     * overrides the default.
     */
    void                     setErrorHandler(RWDBStatus::ErrorHandler handler);

    /**
     * Returns the error handler attached to self.
     */
    RWDBStatus::ErrorHandler errorHandler() const;

    /**
     * Returns a reference to the time zone set on self. If the time zone is
     * not set, returns RWZone::local(). When self is produced, it inherits
     * the time zone setting from the producer RWDBDatabase object. If the
     * time zone was not set on the RWDBDatabase object at the time, the
     * time zone is not set on self.
     *
     * \sa
     * timeZone(const RWZone*) for setting the time zone and information on
     * how the time zone setting is used.
     *
     * \note
     * This method does not fetch the time zone set on the database server
     * or the database client.
     */
    const RWZone&         timeZone() const;

    /**
     * Sets the time zone used when extracting the date and time data from
     * the RWDateTime objects sent \e to the database, and when creating the
     * RWDateTime objects from the date and time data retrieved \e from the
     * database. When the time zone is not set, RWZone::local() is used.
     * When self is produced, it inherits the time zone setting from the
     * producer RWDBDatabase object. If the time zone was not set on the
     * RWDBDatabase object at the time, the time zone is not set on self.
     *
     * \param zone
     * The time zone to be set on self. Pass \c NULL to unset the time zone
     * setting.
     *
     * \return
     * The previous time zone set on self. Returns \c NULL when the time
     * zone was not set.
     *
     * \note
     * Self retains a reference to \a zone. It is the application's
     * responsibility to ensure that \a zone has a lifetime greater than
     * self or any object using self.
     *
     * \note
     * This method does not set the time zone on the database server or the
     * database client.
     */
    const RWZone*         timeZone(const RWZone* zone);

    /**
     * Attempts to acquire the internal mutex lock. If the mutex is already
     * locked by another thread, the function blocks until the mutex is
     * released. This function can be called from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void                  acquire(void) const;

    /**
     * Releases a previously acquired mutex. This function can be called
     * from a \c const object.
     *
     * \note
     * In single-threaded builds, this function evaluates to a no-op.
     */
    void                  release(void) const;

    /**
     * The SQL statement(s) in \a sqlProgram are submitted to the connection
     * for execution. The DB Interface Module does not check the contents of
     * \a sqlProgram for validity. The return value represents a sequence of
     * zero or more RWDBTable objects. This function can behave
     * asynchronously if executed using an asynchronous connection.
     */
    RWDBResult            executeSql(const RWCString& sqlProgram) const;

    /**
     * Returns \c true if self and \a conn share the same implementation.
     * Otherwise, returns \c false.
     */
    bool             operator==(const RWDBConnection& conn) const;

    /**
     * Returns \c true if self and \a conn do not share the same
     * implementation. Otherwise, returns \c false.
     */
    bool             operator!=(const RWDBConnection& conn) const;

private:

    class RWDBConnectionDeallocator
    {
    public:
        static void discard(RWDBConnectionImp*& imp);

    };

    //RWDBDECLARE_COUNTED_REF( RWDBConnectionImp );
    //RWDBConnectionImpCR impl_;
    RWDBCountedRefWithDeallocator < RWDBConnectionImp,
                                  RWDBConnectionDeallocator > impl_;

    static RWDBConnection& uninitialized();

    friend RWDBConnectionImp* getImp(const RWDBConnection& conn)
    {
        return conn.impl_;
    }
};

#endif
