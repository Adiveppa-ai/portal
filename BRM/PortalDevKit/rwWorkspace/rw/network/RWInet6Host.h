#ifndef __rw_network_RWInet6Host_h__
#define __rw_network_RWInet6Host_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWInet6Host.h#1 $
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
 * <DT>RWInet6Host
 * <DD>Encapsulates an internet host IP address and its names.
 * You can
 * construct an RWInet6Host from either an explicit IP address or a
 * symbolic name.
 * <DT>RWInetAddr
 * <DD>A complete internet address:  type information, a host, and a port
 * </DL>
 *
 */

#include <rw/network/RWWinSockInfo.h>
#include <rw/network/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/tvvector.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup networking_module
 * \class RWInet6Host
 *
 * \brief
 * Encapsulates an Internet host IPv6 address and its names.
 *
 * Encapsulates an Internet host IPv6 address and its names. You can
 * construct an RWInet6Host from either an IPv6 address or a symbolic name.
 */
class RW_NETWORK_SYMBOLIC RWInet6Host
{
public:

    /**
     * Attributes to change name lookup behavior.
     */
    enum NameLookup {
        /**
         * If the host address is already known, a lookup will not be used
         * to discover the host name. The colon-hexadecimal form of the host
         * address will be used as the host name.
         */
        numeric
    };

    // An internet host can be specified as an actual address or using
    // a string.  The string can be either the symbolic name of the host,
    // or an IP address in dotted decimal notation.  If an address is passed
    // in as a long, it must be in network byte order.  The default constructor
    // sets the host address as INADDR_ANY to mean any IP address on the current
    // host.  This can not be done as a default arg to the (long) constructor
    // without including system header files.
    // <P>
    // Both the string and char* constructors are necessary.
    // This way you can use either a char* or a string where a port is
    // needed.
    // <P>
    // None of these constructors will block.
    /**
     * An Internet host can be specified as an actual address or through a
     * string. The string can be either the symbolic name of the host or an
     * IPv6 hex address. The default constructor creates a special host that
     * represents an unspecified IPv6 address on the current machine. This
     * is useful when constructing servers.
     */
    RWInet6Host(void);

    /**
     * \copydoc RWInet6Host::RWInet6Host(void)
     */
    RWInet6Host(struct in6_addr IPAddress);

    /**
     * \copydoc RWInet6Host::RWInet6Host(void)
     */
    RWInet6Host(const RWCString& hostname);

    /**
     * \copydoc RWInet6Host::RWInet6Host(void)
     */
    RWInet6Host(const char*);

    /**
     * Ensures that no future operations block. The prepare() function calls
     * the host database routines to gather information about this host. It
     * is not necessary to explicitly call prepare() because it is called by
     * other member functions if needed. No exceptions are thrown by
     * prepare().
     */
    void prepare() const;

    /**
     * \copydoc prepare()
     */
    void prepare(NameLookup lookup) const;


    // Returns true if this host represents any available host interface
    // on the machine.
    bool anyHost() const;

    /**
     * Returns the official name for this host entry. This call may block if
     * prepare() has not been called.
     */
    RWCString                      getName() const;

    /**
     * Returns the primary IPv6 address for this host entry as an
     * \c in6_addr. If you want to print out an IPv6 address, use the
     * addressAsString() static member function.
     */
    struct in6_addr                getAddress() const;

    /**
     * Returns the list of aliases for this host entry. The official name is
     * not included in the list of aliases. This call may block if prepare()
     * has not been called.
     *
     * \note
     * This method is provided only for compatibility with RWInetHost, and
     * will return an empty collection.
     */
    RWTValVector<RWCString>        getAliases() const;

    /**
     * Returns a list of addresses for this host entry as \c in6_addr
     * structs. If you want to print out an IPv6 address, use the
     * addressAsString() static member function. The primary address is the
     * first entry in the getAddresses() array. This call may block if
     * prepare() has not been called.
     */
    RWTValVector<struct in6_addr>  getAddresses() const;


    /**
     * Returns a string describing self. The verbosity of the output is
     * controlled by \a level, where \c level=0 is the most basic output,
     * and \c level=9 is the most verbose.
     *
     * Depending on the \a level and input provided, the output may contain
     * the host name or IP address, and known aliases for that name and
     * aliased IP addresses.
     *
     * <b>Grammar Definitions</b>
     *
     * <pre>
     * ip-address ::= <em>\<ip address in colon hexadecimal notation\></em>
     * ip-address-list ::= ip-address ("," ip-address)*
     * hostname ::= <em>\<domain name\></em>
     * host ::= hostname | ip-address
     * alias-list ::= "(" hostname ("," hostname)* ")"
     * </pre>
     *
     * <table>
     * <tr>
     * <th>\a level</th>
     * <th>Calls %prepare()</th>
     * <th>Output Grammar</th>
     * <th>Sample Output for id(\a level) given
     * %RWInet6Host("localhost")</th>
     * </tr>
     * <tr>
     * <td>\c 0</td>
     * <td></td>
     * <td><tt>host</tt></td>
     * <td><tt>localhost</tt></td>
     * </tr>
     * <tr>
     * <td>\c 1</td>
     * <td></td>
     * <td><tt>host</tt></td>
     * <td><tt>localhost</tt></td>
     * </tr>
     * <tr>
     * <td>\c 2</td>
     * <td></td>
     * <td><tt>host</tt></td>
     * <td><tt>localhost</tt></td>
     * </tr>
     * <tr>
     * <td>\c 3</td>
     * <td align="center">\c X</td>
     * <td><tt>host</tt></td>
     * <td><tt>localhost</tt></td>
     * </tr>
     * <tr>
     * <td>\c 4</td>
     * <td align="center">\c X</td>
     * <td><tt>host "(" ip-address ")"</tt></td>
     * <td><tt>localhost(::1)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 5</td>
     * <td align="center">\c X</td>
     * <td><tt>host "(" ip-address ")"</tt></td>
     * <td><tt>localhost(::1)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 6</td>
     * <td align="center">\c X</td>
     * <td><tt>host</tt></td>
     * <td><tt>localhost</tt></td>
     * </tr>
     * <tr>
     * <td>\c 7</td>
     * <td align="center">\c X</td>
     * <td><tt>host "(" ip-address ")"</tt></td>
     * <td><tt>localhost(::1)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 8</td>
     * <td align="center">\c X</td>
     * <td><tt>host "(" ip-address ")"</tt></td>
     * <td><tt>localhost(::1)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 9</td>
     * <td align="center">\c X</td>
     * <td><tt>host (alias-list)? "(" ip-address-list ")"</tt></td>
     * <td><tt>localhost(::1)</tt></td>
     * </tr>
     * </table>
     */
    RWCString id(unsigned level = 0) const;

    /**
     * Return true or false to indicate whether two hosts objects are equal
     * or not.
     */
    bool operator==(const RWInet6Host& rhs) const;

    /**
     * Return true or false to indicate whether two hosts objects are equal
     * or not.
     */
    bool operator!=(const RWInet6Host& rhs) const;

    /**
     * Returns the host object for the host on which this program is
     * currently running.
     */
    static RWInet6Host me();

    // Auxiliary functions related to internet hosts and addresses.
    // me() returns the host object for the host on which we are currently
    // running.  addressAsString() takes an address in network byte order
    // and returns the dotted decimal string representation of the address.
    // To go from a dotted decimal string to a address, build an RWInet6Host
    // object from the dotted decimal string.
    /**
     * Takes an address as an \c in6_addr and returns the IPv6 hex address
     * string representation of the address. To go from an IPv6 hex address
     * string to an address, build an RWInet6Host object from the IPv6 hex
     * address string.
     */
    static RWCString  addressAsString(struct in6_addr IPAddress);


private:
    RWCString                     name_;
    struct in6_addr               addr_;
    RWTValVector<RWCString>       aliases_;
    RWTValVector<struct in6_addr> addresses_;

    // These pieces of information are only valid as long as the corresponding
    // know flags are true.
    // If name_ is set to null, this means that we couldn't manage to
    // look up the host name.

    bool knowName_;
    bool knowAddr_;
    bool problem_;
    // These flags indicate which data we currently know about the host.
    // If we know both the name and address then we must have everything.
    // Calling prepare_ teaches us all.
    // The problem_ flag is set if there was a problem looking up the host.
    // If name_ is null, then we couldn't find the name given the IP, if
    // name_ is non-null, then we couldn't find the IP given the name.

};

/**
 * \relates RWInet6Host
 *
 * Outputs a representation of \a host on \a strm. The representation is
 * generated using the member function <tt>host.id()</tt> with \c level=0.
 */
RW_NETWORK_SYMBOLIC std::ostream&
operator<<(std::ostream& strm, const RWInet6Host& host);

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_network_RWInet6Host_h__
