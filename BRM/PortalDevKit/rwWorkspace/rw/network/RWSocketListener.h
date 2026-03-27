#ifndef __rw_network_RWSocketListener_h__
#define __rw_network_RWSocketListener_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSocketListener.h#1 $
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

#include <rw/network/RWSocketPortalBase.h>
#include <rw/network/RWSocketPortalImp.h>
#include <rw/network/RWTNetHandle.h>
#include <rw/network/fwd.h>
#include <rw/network/pkgdefs.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

class RW_NETWORK_GLOBAL RWSockAddrBase;

/**
 * \ingroup networking_module
 *
 * \brief
 * Waits on a specified socket address for incoming connections.
 *
 * Waits on a specified socket address for incoming connections. Connections
 * are obtained as RWSocketPortal instances.
 */
class RW_NETWORK_GLOBAL RWSocketListener : public RWSocketPortalBase
{
public:
    /**
     * Creates an uninitialized socket listener. \c Self needs to be
     * initialized using listen() before it can be used.
     */
    RWSocketListener();

    /**
     * Sets up a listener on the \a address indicated, and sets up a queue
     * to wait for connections. The \a backlog parameter specifies the
     * number of incoming connection requests that the protocol software
     * enqueues while a connection is being processed.
     *
     * \note
     * This constructor initializes a socket and sets the \c SO_REUSEADDR
     * option on the socket. If you do not want this option to be set, pass
     * an initalized socket to
     * RWSocketListener(const RWSocket&,WhoShouldClose). See section "Socket
     * Security" under Chapter 8, "The Windows Socket Adapter" in the
     * <em>Essential Networking Module User's Guide</em> for more
     * information.
     */
    RWSocketListener(const RWSockAddrBase& address, int backlog = 5);

    /**
     * Creates a listening portal to the communications channel, where
     * \a socket is the socket doing the listening. Using this constructor
     * is the only way to create a socket that is not closed automatically
     * when portals are no longer using it.
     */
    RWSocketListener(const RWSocket& socket, WhoShouldClose who = Portal);

    // Closes the socket if no one else needs it
    /**
     * Destructor.
     */
    ~RWSocketListener();

    /**
     * Binds the listener to the \a address indicated, and sets up a queue
     * to wait for connections. The \a backlog parameter specifies the
     * number of incoming connection requests that the protocol software
     * enqueues while a connection is being processed.
     *
     * \note
     * This function initializes a socket and sets the \c SO_REUSEADDR
     * option on the socket. If you do not want this option to be set, pass
     * an initalized socket to
     * RWSocketListener(const RWSocket&,WhoShouldClose). See section "Socket
     * Security" under Chapter 8, "The Windows Socket Adapter" in the
     * <em>Essential Networking Module User's Guide</em> for more
     * information.
     */
    void listen(const RWSockAddrBase& address, int backlog = 5);

    /**
     * Receives the next waiting connection. The address of the connecting
     * client will be stored in the RWSockAddr referenced by \a addr.
     */
    RWSocketPortal accept(RWSockAddr* addr = 0) const;

    /**
     * Receives the next waiting connection. The address of the connecting
     * client will be stored in the RWSockAddr referenced by \a addr.
     */
    RWSocketPortal operator()(RWSockAddr* addr = 0) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWSocketListener::getSocket() instead")
    RWSocket socket() const;
#endif

    /**
     * Obtains a reference to the underlying socket.
     */
    RWSocket getSocket() const;

private:
    RWTNetHandle<RWSocketPortalImp> imp_;
    // The socket which is doing the work
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWSocket
RWSocketListener::socket() const
{
    return getSocket();
}
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif  // __rw_network_RWSocketListener_h__ 
