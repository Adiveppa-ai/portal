#ifndef __rw_network_RWSockType_h__
#define __rw_network_RWSockType_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSockType.h#1 $
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
 * Socket address: Socket type and address classes
 *
 * RWSockType represents a type of socket communications channel.  It
 * has three components:  the family, the type, and the protocol.  These
 * correspond to the three components used to classify sockets in the C
 * API.  Derived classes RWInetType and RWUnixSockType (parallel to
 * RWInetAddr and RWUnixSockAddr) provide simplified construction for
 * those domains.
 *
 * The RWSockAddrBase class is an interface class that represents a socket
 * address.  All member functions are pure virtual.  Specific derived
 * classes include RWInetAddr and RWUnixSockAddr and are defined in
 * their own header files.
 *
 * The RWSockAddr class is a concrete socket address reference class.
 * It is a proxy for the real socket address, which is stored on the free
 * store and reference counted.
 *
 */

#include <rw/network/RWWinSockInfo.h>
#include <rw/network/pkgdefs.h>
#include <rw/cstring.h>


struct sockaddr;

const int RWNET_MAX_SOCKADDR_SIZE = 257;
// Size to use when you are passing a buffer for a C API to fill in with
// an address.  Usually, the next step is to take the buffer and pass it
// to a [[SockAddr]] constructor, so you can use the SourcePro Net -
// Essential Networking Module types.  This is used mainly in the
// implementation of [[RWSocket]], it shouldn't concern the Essential
// Networking Module clients.  The value chosen is long enough for any
// of the Essential Networking Module supported address families.

/**
 * \ingroup networking_module
 *
 * \brief
 * A type of socket communications channel.
 *
 * RWSockType represents a type of socket communications channel. It is made
 * up of a family (or domain), a type, and a protocol. An example of a
 * family is the Internet TCP/IP family \c AF_INET. A socket type is
 * \c SOCK_STREAM or \c SOCK_DGRAM. A protocol could be \c PF_INET or
 * \c PF_UNSPEC.
 */
class RW_NETWORK_SYMBOLIC RWSockType
{
public:
    /**
     * Builds an invalid socket type. To set it to a valid type, use the
     * assignment operator.
     */
    RWSockType();

    // Generally, you don't need to call this constructor.  Instead, use
    // one of the derived classes like RWInetType.
    //
    // Build a socket communication type descriptor.  The domain specifies
    // the type of communications channel.  For the Internet domain, this
    // is AF_INET; for unix domain, AF_UNIX.  The type specifies the
    // type of channel, usually SOCK_STREAM or SOCK_DGRAM.  The protocol
    // is a specific protocol to use.  It defaults to zero, which means to
    // use the most sensible protocol; this is usually the correct thing to do.
    /**
     * Builds a socket communication type descriptor. The \a domain
     * specifies the type of communications channel. For the Internet
     * domain, it is \c AF_INET; for the Unix domain, it is \c AF_UNIX.
     * \a type specifies the type of channel, usually \c SOCK_STREAM or
     * \c SOCK_DGRAM. The RWCString should contain 7-bit US-ASCII data.
     */
    RWSockType(const RWCString& familyName, int domain,
               int type = SOCK_STREAM, int protocol = 0);

    /**
     * Destructor.
     */
    ~RWSockType();

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWSockType::getFamilyName() instead")
    RWCString familyName() const;

    RW_DEPRECATE_FUNC("Use RWSockType::getFamily() instead")
    int family() const;

    RW_DEPRECATE_FUNC("Use RWSockType::getDomain() instead")
    int domain() const;

    RW_DEPRECATE_FUNC("Use RWSockType::getType() instead")
    int type() const;

    RW_DEPRECATE_FUNC("Use RWSockType::getProtocol() instead")
    int protocol() const;
#endif

    /**
     * Returns a string representation of the address domain, such as "inet"
     * for the Internet address domain. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString getFamilyName() const;

    /**
     * Returns the integer identifier of the address domain for the socket
     * type, such as \c AF_INET for an Internet domain address.
     */
    int getFamily() const;

    /**
     * Alias for getFamily().
     */
    int getDomain() const;

    /**
     * Gets the socket type that describes the socket protocol.
     */
    int getType() const;

    /**
     * Gets the protocol family that describes the socket type.
     */
    int getProtocol() const;

    /**
     * Returns a string describing self. The parameter \a level is currently
     * unused. This method will return a string representing the address
     * family and socket type.
     *
     * Given the example input:
     * \code
     * RWSockType("inet", AF_INET, SOCK_DGRAM, IPPROTO_UDP);
     * \endcode
     * the following output would be returned:
     * \code
     * inet:dgram
     * \endcode
     */
    RWCString id(unsigned level) const;

    // To be equal, all components must be the same (name,family,type,protocol)
    // special case protocol == 0, which is any protocol
    /**
     * Returns \c true if all of the components (name, family, type,
     * protocol) in the two classes are equivalent.
     */
    bool operator==(const RWSockType&) const;

    // not equal if all components are not the same (name,family,type,protocol)
    // special case protocol == 0, which is any protocol
    /**
     * Returns \c true if any of the components (name, family, type,
     * protocol) differ between the two classes.
     */
    bool operator!=(const RWSockType&) const;

private:
    RWCString familyName_;
    int family_;
    int type_;
    int protocol_;
};

inline RWCString
RWSockType::getFamilyName() const
{
    return familyName_;
}

inline int
RWSockType::getFamily() const
{
    return family_;
}

inline int
RWSockType::getDomain() const
{
    return family_;
}

inline int
RWSockType::getType() const
{
    return type_;
}

inline int
RWSockType::getProtocol() const
{
    return protocol_;
}


#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWSockType::familyName() const
{
    return getFamilyName();
}

inline int
RWSockType::family() const
{
    return getFamily();
}

inline int
RWSockType::domain() const
{
    return getDomain();
}

inline int
RWSockType::type() const
{
    return getType();
}

inline int
RWSockType::protocol() const
{
    return getProtocol();
}
#endif

#endif  // __rw_network_RWSockType_h__
