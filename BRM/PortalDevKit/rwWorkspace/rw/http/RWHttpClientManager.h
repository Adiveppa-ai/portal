#ifndef __rw_http_RWHttpClientManager_h__
#define __rw_http_RWHttpClientManager_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpClientManager.h#1 $
 *
 * Copyright (c) 1996-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 *************************************************************************/

#include <rw/http/RWHttpClient.h>
#include <rw/http/RWHttpRequestInfo.h>
#include <rw/http/fwd.h>
#include <rw/http/pkgdefs.h>
#include <rw/internet/RWTMRUCache.h>
#include <rw/thread/RWServerPool.h>
#include <rw/itc/fwd.h>
#include <rw/functor/RWTFunctor.h>
#include <rw/pointer/RWTCountingPointer.h>
#include <rw/sync/RWMutexLock.h>
#include <rw/sync/RWTLockGuard.h>
#include <rw/cstring.h>
#include <rw/once.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup http_package
 *
 * \brief
 * Provides a high-level interface for issuing HTTP requests using a cache
 * of connected RWHttpClient instances.
 *
 * RWHttpClientManager provides a resource for pooling connection requests
 * for RWHttpAgent. The RWHttpClientManager is thread-hot, allowing for
 * multiple requests to be processed simultaneously.
 *
 * Additionally, RWHttpClientManager provides a mechanism for reusing
 * connected clients for multiple requests to the same host.
 */
class  RW_HTTP_SYMBOLIC RWHttpClientManager
{

public:

    /**
     * &nbsp;
     */
    typedef RWTCountingPointer<RWHttpClientManager, RWAtomicCounter> PointerType;

    /**
     * Constructs a default RWHttpClientManager. The client manager
     * maintains a pool of 20 threads for executing HTTP requests, and
     * allows a maximum of 2 connections to any host (as recommended by the
     * HTTP specification).
     */
    RWHttpClientManager();
    // Default constructor.  Initializes the maximum connections
    // per host to 2 (as recommended in RFC 2616), and the maximum
    // number of threads to 20.

    /**
     * Constructs an RWHttpClientManager instance with a pool containing
     * \a maxThreads threads, and with a limit of \a maxConnections
     * connections to any host. A \a maxConnections value of \c 0 indicates
     * that there is no limit on the number of connections.
     */
    RWHttpClientManager(size_t maxConnections, size_t maxThreads);

    static PointerType&
    instance(void);
    // creates, if not created already, and returns the single instance
    // of RWHttpClientManager

    ~RWHttpClientManager();
    // destructor

    RWTIOUResult<RWHttpReply>
    execute(const RWHttpRequest& request, const RWHttpRequestInfo& info);
    // Spawns a thread to send the method request to the given server and port,
    // and returns an IOU for the response.  The execute method will create a
    // RWHttpClient connected to the server if one does not already exist, or
    // if any active RWHttpClients to that server are busy, and we have not
    // reached our maximum number of connections for a particular host. The
    // optional value maxwait specifies how long the RWHttpClientManager
    // should wait for data to become available on a socket before the socket
    // is considered dead.  The maxwait value defaults to 0, indicating that
    // it will wait indefinitely for data to become available. If data does not
    // become available on the socket before the maxwait time has expired,
    // then an RWHttpNetworkWaitExceeded exception will be thrown.

protected:

    void init(void);
    // Initialize the RWHttpClientManager.  This method is invoked by
    // the constructor.

    RWHttpReply
    request(RWHttpRequest request, RWHttpRequestInfo info);
    // Execute a request in the client manager.

    static bool
    checkRedirect(const RWHttpRequest& request, const RWHttpReply& reply);
    // Verify whether or not we can follow a redirect request
    // from a server given the original request and reply

    RWHttpReply
    requestAsGet(const RWHttpRequest& request, const RWHttpRequestInfo& info);
    // Reissues a request as a GET request in response
    // to a redirect from a server

public:

    /**
     * Sets the maximum number of threads that can be created by the client
     * manager.
     *
     * \note
     * If the number of threads is being reduced, the actual thread count
     * may not decrease immediately if the threads are actively executing
     * requests. Once a request completes, its thread will be released if
     * the number of threads in the manager is greater than \a maxThreads.
     */
    void
    setMaxThreads(size_t maxThreads);

    /**
     * Returns the value for the maximum number of threads that can be
     * created by the client manager.
     *
     * \note
     * This value represents the target maximum number of threads, not the
     * current number of threads in the system. See the setMaxThreads()
     * method for details on when these values may differ.
     */
    size_t
    getMaxThreads() const;

    /**
     * Sets the maximum number of clients allowed to connect to a host. If
     * \a maxConn is set to \c 0, there is no limit on the number of
     * connections.
     *
     * \note
     * If the number of connections is being reduced, the actual number of
     * connections may not decrease immediately if the clients are actively
     * being used. Once a request completes, its connection will be released
     * if the number of connections in the manager is greater than
     * \a maxConn.
     */
    void
    setMaxConnectionsPerHost(size_t maxConn);

    /**
     * Returns the value for the maximum number of clients allowed to
     * connect to a host.
     *
     * \note
     * This value represents the target maximum number of connections per
     * host, not the current number of connections. See the
     * setMaxConnectionsPerHost() method for details on when these values
     * may differ.
     */
    size_t
    getMaxConnectionsPerHost() const;

    /**
     * Closes all connections that not have not been used since \a date.
     */
    void
    closeIfNotUsedSince(const RWHttpDate& date);

    /**
     * Registers a new URL scheme with the client manager. The functor
     * object \a functor should return an RWHttpClient instance that can
     * correctly handle requests of the associated scheme.
     *
     * If the specified \a scheme has already been registered with this
     * instance, the new functor is ignored the method returns \c false;
     * otherwise, the method returns \c true.
     *
     * By default, the only scheme registered with an RWHttpClientManager is
     * "http".
     */
    bool
    registerScheme(const RWCString& scheme, RWTFunctor<RWHttpClient()> functor);

    /**
     * Unregisters the specified URL scheme from the client manager. If the
     * specified \a scheme is not registered with the client manager
     * instance, the method returns \c false; otherwise, the scheme is
     * removed and the method returns \c true.
     */
    bool
    unregisterScheme(const RWCString& scheme);

private:

    typedef RWTMRUCache< RWCString, RWHttpClient>  PoolType;

    PoolType pool_;
    RWTValHashMap<RWCString, RWTFunctor<RWHttpClient()> > clientFactory_;
    RWServerPool server_;
    RWMutexLock poolLock_;

private:

    static void initInstance();

    static RWOnce initInstanceOnce_;
    static PointerType instance_;
};



inline void
RWHttpClientManager::setMaxThreads(size_t maxThreads)
{
    server_.resize(maxThreads);
}

inline size_t
RWHttpClientManager::getMaxThreads() const
{
    return server_.size();
}

inline void
RWHttpClientManager::setMaxConnectionsPerHost(size_t maxConn)
{
    RWTLockGuard<RWMutexLock> guard(poolLock_);
    pool_.setMaxCount(maxConn);
}

inline size_t
RWHttpClientManager::getMaxConnectionsPerHost() const
{
    return pool_.getMaxCount();
}

inline bool
RWHttpClientManager::registerScheme(const RWCString& key, RWTFunctor<RWHttpClient()> functor)
{
    RWTFunctor<RWHttpClient()> f = functor;
    return clientFactory_.insert(key, functor);
}

inline bool
RWHttpClientManager::unregisterScheme(const RWCString& key)
{
    return clientFactory_.remove(key);
}
#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_http_RWHttpClientManager_h__
