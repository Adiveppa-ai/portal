#ifndef __rw_network_RWMulticastSocket_h__
#define __rw_network_RWMulticastSocket_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWMulticastSocket.h#1 $
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

#include <rw/network/RWInetAddr.h>
#include <rw/network/RWSocket.h>

/**
 * \ingroup networking_module
 *
 * \brief
 * Extends RWSocket to provide support for multicast UDP sockets.
 *
 * RWMulticastSocket is derived from RWSocket, providing an extended
 * interface to support multicast UDP sockets.
 */
class RW_NETWORK_SYMBOLIC RWMulticastSocket : public RWSocket
{
public:
    /**
     * Default constructor. Sets the socket to an invalid state. You must
     * initialize it with a call to
     * \ref socket(const RWSockType&) "socket()", connect(), bind(), or
     * listen() before it can be used.
     */
    RWMulticastSocket();

    /**
     * Creates an unconnected socket of the specified type. The resulting
     * socket must be bound to an address using bind(), connect(), or
     * listen() before it can be used.
     *
     * \note
     * In order to effectively take advantage of the methods provided in
     * this class, the RWSockType instance should represent a UDP socket
     * type.
     */
    RWMulticastSocket(const RWSockType& socketType);

    /**
     * Creates an RWSocket that encapsulates the C socket.
     */
    RWMulticastSocket(SOCKET existingSocket);

    /**
     * Assignment operator.
     */
    RWMulticastSocket& operator=(const RWSocket& socket);

    /**
     * Joins an IPv4 multicast socket group. If \c localAddr is specified,
     * then it will be used as the local interface for receiving messages
     * from the group, otherwise an interface will be chosen by the system.
     */
    void
    joinGroup(const RWInetAddr& group, const RWInetAddr& localAddr = RWInetAddr());

    /**
     * Joins an IPv6 multicast socket group. If interface is specified, it
     * will be used as the local interface for receiving messages from the
     * group, otherwise an interface will be chosen by the system.
     *
     * \conditional
     * This method is available only on systems that support IPv6-based
     * socket addresses.
     */
    void
    joinGroup(const RWInet6Addr& group, unsigned int inter = 0);

    /**
     * Leaves an IPv4 mulitcast socket group. The arguments to this function
     * should match those passed to joinGroup() when the socket joined the
     * multicast group.
     */
    void
    leaveGroup(const RWInetAddr& group, const RWInetAddr& localAddr = RWInetAddr());

    /**
     * Leaves an IPv6 multicast socket group. The arguments to this function
     * should match those passed to joinGroup() when the socket joined the
     * multicast group.
     *
     * \conditional
     * This method is available only on systems that support IPv6-based
     * socket addresses.
     */
    void
    leaveGroup(const RWInet6Addr& group, unsigned int inter = 0);

    /**
     * Sets the local IPv4 address to be used when sending messages to the
     * multicast group. If an interface is not specified, the system will
     * choose one.
     */
    void
    setInterface(const RWInetAddr& inter);

    /**
     * Sets the local IPv6 address to be used when sending messages to the
     * multicast group. If an interface is not specified, the system will
     * choose one.
     *
     * \conditional
     * This method is available only on systems that support IPv6-based
     * socket addresses.
     */
    void
    setInterface(unsigned int inter);

    /**
     * Sets the maximum number of hops a packet is allowed to travel. The
     * value of this argument is treated differently depending on whether
     * this is an IPv4 or IPv6 multicast socket. If it is IPv4 based, the
     * scope sets the TTL field of the message header. If it is IPv6 based,
     * the scope sets the maximum number of hops (times the packet will be
     * forwarded by a router) on the message header.
     */
    void
    setScope(unsigned int scope);

    /**
     * Determines whether messages sent from this socket will also be
     * received by this socket (if it is a member of the same group), or
     * will be sent only to other members of the group. If loop is \c true,
     * the sending socket will receive the message as well. The default is
     * \c true.
     */
    void
    setLoopback(bool loop);
};

#endif
