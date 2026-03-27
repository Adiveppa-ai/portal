#ifndef __rw_network_RWInet6AddrFactory_h__
#define __rw_network_RWInet6AddrFactory_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWInet6AddrFactory.h#1 $
 *
 * Copyright (c) 1995-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

/*
 * RWInet6AddrFactory: Construct Internet style socket addresses
 *
 * RWInet6AddrFactory has a singleton instance which is registered with
 * the global socket address factory.
 * The registration and construction of the singleton
 * happen the first time an instance of RWInet6AddrFactory is constructed.  Thus
 * you must make sure that at least one RWInet6AddrFactory gets constructed
 * somewhere along the line.
 * One is constructed for you at the time the socket factory is created, so
 * you are covered.
 */

#include <rw/network/RWSockAddrFactoryBase.h>
#include <rw/network/RWTNetHandle.h>
#include <rw/network/pkgdefs.h>

/**
 * \ingroup networking_module
 *
 * \brief
 * Used by RWSockAddrFactory to create instances of RWInet6Addr.
 *
 * RWInet6AddrFactory is used by RWSockAddrFactory to create instances of
 * RWInet6Addr. It is not used directly by clients of the Networking
 * classes. Only a single instance of RWInet6AddrFactory exists, and it is
 * created at the time the RWSockAddrFactory is constructed.
 */
class RW_NETWORK_GLOBAL RWInet6AddrFactory : public RWSockAddrFactoryBase
{
public:

    /**
     * Default constructor.
     *
     * \note
     * This function creates a local RWInet6AddrFactory instance. It does
     * not instantiate the RWInet6AddrFactory singleton and is not
     * registered with the RWSockAddrFactory.
     */
    RWInet6AddrFactory();

    virtual ~RWInet6AddrFactory();

    /**
     * Returns a pointer to an RWInet6Addr instance constructed from the
     * provided \c sockaddr structure and the given socket type.
     *
     * The \a addr parameter is expected to point to an object that is
     * compatible with \c sockaddr_in6. The socket address family of \a addr
     * is expected to be AF_INET6.
     *
     * The \a addrLen parameter is expected to describe the size, in bytes,
     * of the object pointed to by \a addr.
     *
     * The newly created RWInet6Addr is allocated on the heap. The caller is
     * responsible for deleting it. Often, this is managed by wrapping the
     * object using an RWSockAddr.
     */
    virtual RWSockAddrBase* operator()(struct sockaddr* addr,
                                       RWSockLenType addrLen) const;

    /**
     * Returns a pointer to an RWInet6Addr instance constructed from the
     * provided \c sockaddr structure and the given socket type.
     *
     * The \a addr parameter is expected to point to an object that is
     * compatible with \c sockaddr_in6. The socket address family of \a addr
     * is expected to be AF_INET6.
     *
     * The \a addrLen parameter is expected to describe the size, in bytes,
     * of the object pointed to by \a addr.
     *
     * The \a type parameter describes the type of socket address. This
     * would normally be one of \c SOCK_STREAM or \c SOCK_DGRAM.
     *
     * The newly created RWInet6Addr is allocated on the heap. The caller is
     * responsible for deleting it. Often, this is managed by wrapping the
     * object using an RWSockAddr.
     */
    virtual RWSockAddrBase* operator()(struct sockaddr* addr,
                                       RWSockLenType addrLen, int type) const;

    /**
     * Returns a pointer to an RWInet6Addr instance constructed from from
     * the provided RWCString.
     *
     * The \a str parameter should be in the format described by the
     * RWInet6Addr::id() method and should contain only 7-bit US-ASCII data.
     *
     * The newly created RWInet6Addr is allocated on the heap. The caller is
     * responsible for deleting it. Often, this is managed by wrapping the
     * object using an RWSockAddr.
     */
    virtual RWSockAddrBase* operator()(const RWCString& str) const;

    static RWTNetHandle<RWInet6AddrFactory> instance();
};

// Macro for getting reference to singleton.
#define rwInet6AddrFactory (*RWInet6AddrFactory::instance())

#endif // __rw_network_RWInet6AddrFactory_h__
