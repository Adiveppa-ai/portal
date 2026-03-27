#ifndef __rw_network_RWInetAddr_h__
#define __rw_network_RWInetAddr_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWInetAddr.h#1 $
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
 * Internet addresses: Encapsulate internet naming
 *
 * These classes encapsulate internet ports and hosts, including converting
 * between symbolic and integer representations for these.  The classes
 * include:
 * <DL>
 * <DT>RWInetType
 * <DD>The Internet address type.
 * This is like an envelope with no address on it.
 * <DT>RWInetPort
 * <DD>Encapsulates an internet port and its service names.  You can
 * construct an RWInetPort from either an explicit port number or a
 * symbolic service name.
 * <DT>RWInetHost
 * <DD>Encapsulates an internet host IP address and its names.
 * You can
 * construct an RWInetHost from either an explicit IP address or a
 * symbolic name.
 * <DT>RWInetAddr
 * <DD>A complete internet address:  type information, a host, and a port
 * </DL>
 *
 */

#include <rw/network/RWInetHost.h>
#include <rw/network/RWInetPort.h>
#include <rw/network/RWSockAddrBase.h>
#include <rw/network/RWWinSockInfo.h>
#include <rw/network/pkgdefs.h>

/*
 * RWInetAddr: address for a TCP/IP connection
 *
 * An internet address has two parts: the port number and the host.
 * This class contains both of these parts, each represented using the
 * classes defined above.
 */

/**
 * \ingroup networking_module
 *
 * \brief
 * Encapsulates a complete Internet address that includes type information,
 * a host, and a port.
 *
 * Encapsulates a complete Internet address that includes type information,
 * a host, and a port.
 *
 * \example
 * \code
 * RWInetAddr addr(80, "www.roguewave.com");
 * \endcode
 * \endexample
 */
class RW_NETWORK_GLOBAL RWInetAddr : public RWSockAddrBase
{
public:

    // Construct an address for a TCP/IP internet connection.
    // Note that the RWInetPort and RWInetHost classes have conversion
    // constructors that take either a string or an integer, so you can
    // specify either a string or an integer for either the port or the host.
    // The default constructor needs to be set (probably using [[operator=]]
    // to another address before it can be used.
    // Use the constructor taking only a port to represent a special address
    // used to bind to any of the network interfaces on the machine on which
    // the process is running;
    // this is done, for example, when you are setting a server address.
    // None of the constructors block.
    /**
     * Constructs an address for a TCP/IP Internet connection. The
     * constructor that takes only a port argument creates a special address
     * used to bind to any of the network interfaces on the machine on which
     * the process is running. This is done, for example, when you are
     * setting a server address. An address created using the default
     * constructor binds to an arbitrary port number on any network
     * interface on the local machine. These constructors do not block.
     */
    RWInetAddr();

    ~RWInetAddr();

    /**
     * \copydoc RWInetAddr::RWInetAddr()
     */
    RWInetAddr(const RWInetPort& port);

    /**
     * \copydoc RWInetAddr::RWInetAddr()
     */
    RWInetAddr(int port);

    /**
     * \copydoc RWInetAddr::RWInetAddr()
     */
    RWInetAddr(const RWInetPort& port,
               const RWInetHost& host,
               short type = SOCK_STREAM,
               short protocol = 0);

    /**
     * \copydoc RWInetAddr::RWInetAddr()
     */
    RWInetAddr(const sockaddr_in& addr,
               short type = SOCK_STREAM,
               short protocol = 0);

    /**
     * Constructs an address from the ASCII string \a s, where \a s has the
     * form \c type:host:port. Both \c type and \c host are optional. If
     * \c type is supplied, it must be \c stream for a stream socket address
     * or \c dgram for a datagram socket. If not specified, \c type defaults
     * to a value of \c stream and \c host to a value of \c "ANY".
     */
    RWInetAddr(const RWCString& s);

    /**
     * Ensures that future calls do not block on this address. If necessary,
     * this function looks up the IP address and port number from the host
     * name and service name. It is not necessary to call prepare(), but if
     * you don't, future calls may block. No exceptions are thrown from
     * prepare().
     */
    virtual void prepare() const;

    // Returns the correct address type, constructed from an RWInetType.
    /**
     * Returns the address type.
     */
    virtual RWSockType addressType() const;

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * Returns the port part of the address.
     */
    RW_DEPRECATE_FUNC("Use RWInetAddr::getPort() instead")
    const RWInetPort& port() const;

    /**
     * Returns the host part of the address.
     */
    RW_DEPRECATE_FUNC("Use RWInetAddr::getHost() instead")
    const RWInetHost& host() const;
#endif

    /**
     * Returns the port part of the address.
     */
    const RWInetPort& getPort() const;

    /**
     * Returns the host part of the address.
     */
    const RWInetHost& getHost() const;

    /**
     * Returns a pointer to an internal representation of the address that
     * was cast to a \c sockaddr structure, as defined by the sockets and
     * TLI APIs (TLI is the Unix System V network communication interface).
     * The pointer is to an internal data structure, so it becomes invalid
     * if self is changed in any way or goes out of scope. If the address
     * has no representation as a \c sockaddr, a null pointer is returned.
     */
    virtual sockaddr* asSockaddr() const;

    // Returns a pointer to an internal representation of the address cast to
    // a sockaddr structure, as defined by the sockets and TLI APIs.  The
    // pointer is to an internal data structure, so it will become invalid if
    // this object is changed in any way or goes out of scope.  If the address
    // has no representation as a sockaddr, a null pointer is returned.
    /**
     * Returns the size of an internal representation of the socket address
     * defined by the sockets.
     */
    virtual size_t    sockaddrSize() const;

    /**
     * Returns a string describing self. The verbosity of the output is
     * controlled by \a level, where \c level=0 is the most basic output,
     * and \c level=9 is the most verbose. If not specified, a default value
     * of 0 is used and is guaranteed not to block.
     *
     * <b>Grammar Definitions</b>
     *
     * <pre>
     * type ::= <em>\<the result of addressType().id(\a level)\></em>
     * hostname ::= <em>\<the result of getHost().id(\a level)\></em>
     * port ::= <em>\<the result of getPort().id(\a level)\></em>
     * </pre>
     *
     * <table>
     * <tr>
     * <th>\a level</th>
     * <th>Calls %prepare()</th>
     * <th>Output Grammar</th>
     * <th>Sample Output for id(\a level) given
     * %RWInetAddr(80, "127.0.0.1")</th>
     * </tr>
     * <tr>
     * <td>\c 0</td>
     * <td></td>
     * <td><tt>hostname ":" port</tt></td>
     * <td><tt>127.0.0.1:80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 1</td>
     * <td></td>
     * <td><tt>hostname ":" port</tt></td>
     * <td><tt>127.0.0.1:80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 2</td>
     * <td></td>
     * <td><tt>type ":" hostname ":" port</tt></td>
     * <td><tt>inet:stream:127.0.0.1:80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 3</td>
     * <td align="center">\c X</td>
     * <td><tt>hostname ":" port</tt></td>
     * <td><tt>localhost:80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 4</td>
     * <td align="center">\c X</td>
     * <td><tt>hostname ":" port</tt></td>
     * <td><tt>localhost(127.0.0.1):80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 5</td>
     * <td align="center">\c X</td>
     * <td><tt>hostname ":" port</tt></td>
     * <td><tt>localhost(127.0.0.1):80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 6</td>
     * <td align="center">\c X</td>
     * <td><tt>type ":" hostname ":" port</tt></td>
     * <td><tt>inet:stream:localhost:80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 7</td>
     * <td align="center">\c X</td>
     * <td><tt>type ":" hostname ":" port</tt></td>
     * <td><tt>inet:stream:localhost(127.0.0.1):80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 8</td>
     * <td align="center">\c X</td>
     * <td><tt>type ":" hostname ":" port</tt></td>
     * <td><tt>inet:stream:localhost(127.0.0.1):80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 9</td>
     * <td align="center">\c X</td>
     * <td><tt>type ":" hostname ":" port</tt></td>
     * <td><tt>inet:stream:localhost(127.0.0.1):80(http,www,www-http)</tt></td>
     * </tr>
     * </table>
     */
    virtual RWCString id(unsigned level = 0) const;

    /**
     * Returns \c true if the two address objects are equal.
     */
    bool operator==(const RWInetAddr& rhs) const;

    /**
     * Returns \c true if the two address objects are not equal.
     */
    bool operator!=(const RWInetAddr& rhs) const;

    /**
     * Returns \c true if \a addr is an RWInetAddr.
     */
    static bool  is(const RWSockAddrBase&);

    // Narrowing conversion from a base class, or from an RWSockAddr.
    // These are also accessible as the global template functions
    // is<RWInetAddr>() and as<RWInetAddr>() (provided your compiler
    // supports explicit template functions).
    /**
     * Casts \a addr to RWInetAddr, if appropriate. Otherwise it throws an
     * RWSockWrongAddressTypeError exception.
     */
    static RWInetAddr as(const RWSockAddrBase&);

private:
    RWInetPort   port_;
    RWInetHost   host_;
    short        type_;
    short        protocol_;
    sockaddr_in  addr_;
};

/**
 * \relates RWInetAddr
 *
 * Reads an address \a x from input stream \a strm.
 */
RW_NETWORK_SYMBOLIC std::istream&
operator>>(std::istream& strm, RWInetAddr& x);

inline const RWInetPort&
RWInetAddr::getPort() const
{
    return port_;
}

inline const RWInetHost&
RWInetAddr::getHost() const
{
    return host_;
}

#if !defined(RW_DISABLE_DEPRECATED)
inline const RWInetPort&
RWInetAddr::port() const
{
    return getPort();
}

inline const RWInetHost&
RWInetAddr::host() const
{
    return getHost();
}
#endif

#endif // __rw_network_RWInetAddr_h__
