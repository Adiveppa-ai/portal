#ifndef __rw_network_RWInet6Addr_h__
#define __rw_network_RWInet6Addr_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWInet6Addr.h#1 $
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
 * <DT>RWInet6Addr
 * <DD>A complete internet address:  type information, a host, and a port
 * </DL>
 *
 */

#include <rw/network/RWInet6Host.h>
#include <rw/network/RWInetPort.h>
#include <rw/network/RWSockAddrBase.h>
#include <rw/network/RWWinSockInfo.h>
#include <rw/network/pkgdefs.h>

/**
 * \ingroup networking_module
 *
 * \brief
 * Encapsulates a complete IPv6 address.
 *
 * Encapsulates a complete IPv6 address that includes type information,
 * host, port, and scope.
 *
 * \example
 * \code
 * RWInet6Addr addr(8001, "0::1");
 * \endcode
 * \endexample
 */
class RW_NETWORK_GLOBAL RWInet6Addr : public RWSockAddrBase
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
     * Constructs an address for an IPv6 Internet connection. The
     * constructor that takes only a port argument creates a special address
     * used to bind to any of the network interfaces on the machine on which
     * the process is running. This is done, for example, when you are
     * setting a server address. An address created using the default
     * constructor binds to an arbitrary port number on any network
     * interface on the local machine. These constructors do not block.
     */
    RWInet6Addr();

    ~RWInet6Addr();

    /**
     * \copydoc RWInet6Addr::RWInet6Addr()
     */
    RWInet6Addr(const RWInetPort& port);

    /**
     * \copydoc RWInet6Addr::RWInet6Addr()
     */
    RWInet6Addr(int port);

    /**
     * \copydoc RWInet6Addr::RWInet6Addr()
     */
    RWInet6Addr(const RWInetPort& port,
                const RWInet6Host& host,
                unsigned scope = 0,
                short type = SOCK_STREAM,
                short protocol = 0);

    /**
     * \copydoc RWInet6Addr::RWInet6Addr()
     */
    RWInet6Addr(const sockaddr_in6& addr,
                short type = SOCK_STREAM,
                short protocol = 0);

    /**
     * Constructs an address from the ASCII string \a s, where \a s has the
     * form \c type:host\%scope:port. \c type, \c host, and \c scope are
     * optional. If type is supplied, it must be \c stream for a stream
     * socket address, or \c dgram for a datagram socket. \c host should be
     * wrapped in square brackets (<tt>'['</tt> and <tt>']'</tt>) if the
     * string should contain an IPv6 hex address. \c scope is only required
     * if its value is nonzero. If not specified, \c type defaults to a
     * value of \c stream, \c host to a value of \c "ANY" and \c scope to a
     * value of \c 0.
     */
    RWInet6Addr(const RWCString& s);

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

    /**
     * Returns the port portion of the address.
     */
    RWInetPort   getPort() const;

    /**
     * Returns the host portion of the address.
     */
    RWInet6Host  getHost() const;

    /**
     * Returns the scope portion of the address.
     */
    unsigned     getScope() const;

    /**
     * Returns a pointer to an internal representation of the address that
     * was cast to a \c sockaddr structure, as defined by the sockets and
     * TLI APIs. (TLI is the UNIX System V network communication interface.)
     * The pointer is to an internal data structure, so it becomes invalid
     * if self is changed in any way or goes out of scope. If the address
     * has no representation as a \c sockaddr, a \c null pointer is
     * returned.
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
     * and \c level=9 is the most verbose.
     *
     * <b>Grammar Definitions</b>
     *
     * <pre>
     * type ::= <em>\<the result of addressType().id(\a level)\></em>
     * host-value ::= <em>\<the result of getHost().id(\a level)\></em>
     * hostname ::= host-value | <em>See Note Below</em>
     * port ::= <em>\<the result of getPort().id(\a level)\></em>
     * scope-value ::= <em>\<the result of getScope() if non-zero\></em>
     * scope ::= "%" scope-value
     * </pre>
     *
     * \note
     * \parblock
     * When the result of RWInet6Host::id() is interpreted by
     * RWInet6Addr::id(), the grammar of RWInet6Host is updated as follows:
     *
     * <pre>
     *     host ::= hostname | '[' ip-address ']'
     * </pre>
     *
     * The extra '[' and ']' isolate the ':' that are a part of the address
     * from the ':' delimiter used in RWInet6Addr's representation.
     * \endparblock
     *
     * <table>
     * <tr>
     * <th>\a level</th>
     * <th>Calls %prepare()</th>
     * <th>Output Grammar</th>
     * <th>Sample Output for id(\a level) given %RWInet6Addr(80, "::1")</th>
     * </tr>
     * <tr>
     * <td>\c 0</td>
     * <td></td>
     * <td><tt>hostname (scope)? ":" port</tt></td>
     * <td><tt>[::1]:80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 1</td>
     * <td></td>
     * <td><tt>hostname (scope)? ":" port</tt></td>
     * <td><tt>[::1]:80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 2</td>
     * <td></td>
     * <td><tt>type ":" hostname (scope)? ":" port</tt></td>
     * <td><tt>inet6:stream:[::1]:80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 3</td>
     * <td align="center">\c X</td>
     * <td><tt>hostname (scope)? ":" port</tt></td>
     * <td><tt>server.example.com:80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 4</td>
     * <td align="center">\c X</td>
     * <td><tt>hostname (scope)? ":" port</tt></td>
     * <td><tt>server.example.com(::1):80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 5</td>
     * <td align="center">\c X</td>
     * <td><tt>hostname (scope)? ":" port</tt></td>
     * <td><tt>server.example.com(::1):80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 6</td>
     * <td align="center">\c X</td>
     * <td><tt>type ":" hostname (scope)? ":" port</tt></td>
     * <td><tt>inet6:stream:server.example.com:80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 7</td>
     * <td align="center">\c X</td>
     * <td><tt>type ":" hostname (scope)? ":" port</tt></td>
     * <td><tt>inet6:stream:server.example.com(::1):80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 8</td>
     * <td align="center">\c X</td>
     * <td><tt>type ":" hostname (scope)? ":" port</tt></td>
     * <td><tt>inet6:stream:server.example.com(::1):80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 9</td>
     * <td align="center">\c X</td>
     * <td><tt>type ":" hostname (scope)? ":" port</tt></td>
     * <td><tt>inet6:stream:server.example.com(::1):80(http,www,www-http)</tt></td>
     * </tr>
     * </table>
     */
    virtual RWCString id(unsigned level = 0) const;

    // Returns true or false to indicate whether two address objects
    // are equal or not.
    /**
     * Comparison operator.
     */
    bool operator==(const RWInet6Addr& rhs) const;

    // Returns true or false to indicate whether two address objects
    // are equal or not.
    /**
     * Comparison operator.
     */
    bool operator!=(const RWInet6Addr& rhs) const;

    /**
     * Returns \c true if \c addr is an RWInet6Addr.
     */
    static bool  is(const RWSockAddrBase&);

    // Narrowing conversion from a base class, or from an RWSockAddr.
    // These are also accessible as the global template functions
    // is<RWInet6Addr>() and as<RWInet6Addr>() (provided your compiler
    // supports explicit template functions).
    /**
     * Casts \a addr to RWInet6Addr, if appropriate. Otherwise, it throws an
     * RWSockWrongAddressTypeError exception.
     */
    static RWInet6Addr as(const RWSockAddrBase&);

private:
    RWInetPort   port_;
    RWInet6Host  host_;
    short        type_;
    short        protocol_;
    unsigned     scope_;
    sockaddr_in6 addr_;
};

/**
 * \relates RWInet6Addr
 *
 * Reads a representation of \a addr from \a strm. The representation should
 * be of the form produced by id() with \c level=2.
 */
RW_NETWORK_SYMBOLIC std::istream&
operator>>(std::istream&, RWInet6Addr&);

inline RWInetPort
RWInet6Addr::getPort() const
{
    return port_;
}

inline RWInet6Host
RWInet6Addr::getHost() const
{
    return host_;
}

inline unsigned
RWInet6Addr::getScope() const
{
    return scope_;
}

#endif // __rw_network_RWInet6Addr_h__
