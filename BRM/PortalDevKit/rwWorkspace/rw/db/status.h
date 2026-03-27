#ifndef __RWDB_STATUS_H__
#define __RWDB_STATUS_H__

/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/db/status.h#1 $
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
 * Class RWDBStatus encapsulates the status of an object or operation.
 * Most database-specific implementation classes derive from RWDBStatus.
 * RWDBStatus supports error-handling through explicit testing (isValid()),
 * through callbacks(setErrorHandler()), and through exceptions (raise()).
 * See the Users Guide for details.
 *
 **************************************************************************/

#include <rw/db/defs.h>
#include <rw/db/future.h>
#include <rw/db/tracer.h>
#include <rw/cstring.h>

/**
 * \ingroup db_utility_and_diagnostics_group
 * \class RWDBStatus
 *
 * \brief
 * Encapsulates the error state of an object or operation.
 *
 * RWDBStatus encapsulates the error state of an object or operation. A
 * valid object or a successful operation is represented by RWDBStatus::ok.
 * An RWDBStatus that is not valid contains an error code, an error message,
 * and often some supplemental information provided by a database vendor's
 * API.
 *
 * Each RWDBStatus object contains a callback routine that can be changed by
 * an application. If an RWDBStatus changes state to anything but
 * RWDBStatus::ok, the installed handler is called with self as an argument.
 *
 * In the error model of the DB Interface Module, the use of exceptions is
 * optional, and is under the application's control. The raise() method of
 * RWDBStatus throws an exception of type RWExternalErr. Thus, an
 * application may choose to enforce a terminating or nonterminating model
 * of error handling by installing an appropriate error handler.
 *
 * When objects of the DB Interface Module are produced by other objects,
 * the produced object's status is copied from the producer. Consequently,
 * an application can control error handling at any level it chooses. A
 * handler installed in the RWDBManager is propagated to every object of
 * <b><em>The DB Interface Module</em></b> in the application; one installed
 * in an RWDBDatabase is propagated to each object produced by that
 * RWDBDatabase, and so on down to the level of individual objects.
 *
 * RWDBStatus is designed around the Interface/Implementation paradigm. An
 * RWDBStatus instance is an interface to a reference-counted
 * implementation; copy constructors and assignment operators produce
 * additional references to a shared implementation.
 *
 * \synopsis
 * #include <rw/db/status.h>
 *
 * RWDBStatus status = myDbase.status();    //status of object
 * RWDBStatus status = myDbase.createTable("tableName",myschema);
 *                                          //status of function
 * \endsynopsis
 *
 * \example
 * An application that requires C++ exceptions throughout would proceed this
 * way:
 *
 * \code
 * void throwStatus(const RWDBStatus& status)
 * {
 *     status.raise();
 * }
 * RWDBManager::setErrorHandler(throwStatus);
 * \endcode
 * \endexample
 */
class RWDB_GLOBAL RWDBStatus : public RWDBFuture
{
public:
    /**
     * A typedef for the error handling function.
     */
    typedef void (*ErrorHandler)(const RWDBStatus& status);

    /**
     * Possible RWDBStatus error codes.
     */
    enum ErrorCode {

        /**
         * No error
         */
        ok = 0,

        /**
         * Out of Memory
         */
        noMem,

        /**
         * Object never initialized
         */
        notInitialized,

        /**
         * Type conversion error
         */
        typeConversion,

        /**
         * Database not registered
         */
        dbNotFound,

        /**
         * Error reported by server
         */
        serverError,

        /**
         * Message from server
         */
        serverMessage,

        /**
         * Error in vendor's library
         */
        vendorLib,

        /**
         * Lost connection
         */
        notConnected,

        /**
         * End of fetch
         */
        endOfFetch,

        /**
         * Invalid usage of object
         */
        invalidUsage,

        /**
         * Column does not exist
         */
        columnNotFound,

        /**
         * Invalid positioning within object, i.e. bounds error
         */
        invalidPosition,

        /**
         * Unsupported feature
         */
        notSupported,

        /**
         * Null reference parameter
         */
        nullReference,

        /**
         * Database object not found
         */
        notFound,

        /**
         * Required piece of information is missing
         */
        missing,

        /**
         * This object cannot support multiple readers
         */
        noMultiReaders,

        /**
         * This object cannot support deletions
         */
        noDeleter,

        /**
         * This object cannot support insertions
         */
        noInserter,

        /**
         * This object cannot support updates
         */
        noUpdater,

        /**
         * This object cannot support readers
         */
        noReader,

        /**
         * This object cannot support indices
         */
        noIndex,

        /**
         * This object cannot be dropped
         */
        noDrop,

        /**
         * Incorrect connection was supplied
         */
        wrongConnection,

        /**
         * This object cannot support privileges
         */
        noPrivilege,

        /**
         * This object cannot support cursors
         */
        noCursor,

        /**
         * Unable to open
         */
        cantOpen,

        /**
         * For errors produced at the application level
         */
        applicationError,

        /**
         * For future use
         */
        notReady,

        /**
         * Error in the SourcePro library
         */
        internalError,

        /**
         * Error writing to the cache.
         */
        cacheWriteError,

        /**
         * Error reading from the cache.
         */
        cacheReadError

    };
    /*
    ** Not all compilers support default values for "complicated"
    ** arguments. These overloads mimic default values for CStrings.
    */

    /**
     * The default constructor creates an RWDBStatus of #notInitialized.
     * Data members are set to default values of \c 0 or the empty string,
     * and the error handler is set to #rwnil.
     */
    RWDBStatus();

    RWDBStatus(ErrorCode errorCode,
               long      vendorError1 = 0,
               long      vendorError2 = 0,
               bool isTerminal = false);

    RWDBStatus(ErrorHandler errorHandler,
               ErrorCode errorCode = notInitialized,
               long      vendorError1 = 0,
               long      vendorError2 = 0,
               bool isTerminal = false);
    RWDBStatus(const RWDBFuture& future,
               ErrorCode errorCode = notInitialized,
               long      vendorError1 = 0,
               long      vendorError2 = 0,
               bool isTerminal = false);
    RWDBStatus(const RWCString& message,
               ErrorCode        errorCode = notInitialized,
               long             vendorError1 = 0,
               long             vendorError2 = 0,
               bool        isTerminal = false);
    RWDBStatus(const RWCString& message,
               const RWCString& vendorMessage1,
               ErrorCode        errorCode = notInitialized,
               long             vendorError1 = 0,
               long             vendorError2 = 0,
               bool        isTerminal = false);
    RWDBStatus(const RWCString& message,
               const RWCString& vendorMessage1,
               const RWCString& vendorMessage2,
               ErrorCode        errorCode = notInitialized,
               long             vendorError1 = 0,
               long             vendorError2 = 0,
               bool        isTerminal = false);
    RWDBStatus(RWDBStatusImp* impl);

    /**
     * Copy constructor. The created RWDBStatus shares an implementation
     * with \a status.
     */
    RWDBStatus(const RWDBStatus& status);

    /**
     * Assignment operator. Self shares an implementation with \a status.
     * Returns a reference to self.
     */
    RWDBStatus& operator=(const RWDBStatus& status);

    virtual ~RWDBStatus();

    // Mutator functions (see comment above regarding defaults):
    // NB: setError calls error handler; changeError doesn't. Otherwise
    // they are identical.

    void          setError(ErrorCode code,
                           bool isTerminal,
                           long      vendorError1 = 0,
                           long      vendorError2 = 0);
    void          setError(ErrorCode code,
                           bool isTerminal,
                           const     RWCString& message,
                           long      vendorError1 = 0,
                           long      vendorError2 = 0);
    void          setError(ErrorCode        code,
                           bool        isTerminal,
                           const RWCString& message,
                           const RWCString& vendorMessage1,
                           long             vendorError1 = 0,
                           long             vendorError2 = 0);
    void          setError(ErrorCode        code,
                           bool        isTerminal,
                           const RWCString& message,
                           const RWCString& vendorMessage1,
                           const RWCString& vendorMessage2,
                           long             vendorError1 = 0,
                           long             vendorError2 = 0);

    void          changeError(ErrorCode code,
                              bool isTerminal,
                              long      vendorError1 = 0,
                              long      vendorError2 = 0);
    void          changeError(ErrorCode        code,
                              bool        isTerminal,
                              const RWCString& message,
                              long             vendorError1 = 0,
                              long             vendorError2 = 0);
    void          changeError(ErrorCode        code,
                              bool        isTerminal,
                              const RWCString& message,
                              const RWCString& vendorMessage1,
                              long             vendorError1 = 0,
                              long             vendorError2 = 0);
    void          changeError(ErrorCode        code,
                              bool        isTerminal,
                              const RWCString& message,
                              const RWCString& vendorMessage1,
                              const RWCString& vendorMessage2,
                              long             vendorError1 = 0,
                              long             vendorError2 = 0);

    /**
     * Installs \a handler as self's error handler. The supplied \a handler
     * is inherited by all objects produced by self. By default, an
     * RWDBStatus::ErrorHandler is inherited from the object that produced
     * it; this method overrides the default.
     */
    void          setErrorHandler(ErrorHandler handler);

    /**
     * Throws an exception that contains the error message associated with
     * self.
     */
    void          raise() const;

    // Accessor functions:

    /**
     * Returns self's error code. The code <tt>errorCode() != #ok</tt> can
     * be interpreted as an abnormal condition.
     */
    ErrorCode     errorCode() const;

    /**
     * Returns self's installed error handler, if any.
     */
    ErrorHandler  errorHandler() const;

    /**
     * Returns a code supplied by the database vendor, or \c 0 if not
     * relevant.
     */
    long          vendorError1() const;

    /**
     * Returns a code supplied by the database vendor, or \c 0 if not
     * relevant.
     */
    long          vendorError2() const;

    /**
     * Returns \c true if <tt>errorCode() == #ok</tt>, otherwise returns
     * \c false.
     */
    bool     isValid() const;

    /**
     * Returns \c true if the error that occurred will terminate the
     * application.
     */
    bool     isTerminal() const;

    /**
     * Returns the error message associated with the current error code.
     * Returns an empty string if the current error code is #ok.
     */
    RWCString     message() const;

    /**
     * Returns a string supplied by the database vendor, or an empty string
     * if not relevant.
     */
    RWCString     vendorMessage1() const;

    /**
     * Returns a string supplied by the database vendor, or an empty string
     * if not relevant.
     */
    RWCString     vendorMessage2() const;

    // This function creates a new RWDBStatus by making a deep copy if the
    // current status is ok, otherwise a shallow copy
    RWDBStatus    pattern() const;

private:
    RWDBCountedRef<RWDBStatusImp> impl_;
};

#endif
