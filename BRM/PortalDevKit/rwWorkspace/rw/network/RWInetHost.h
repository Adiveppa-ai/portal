#ifndef __rw_network_RWInetHost_h__
#define __rw_network_RWInetHost_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWInetHost.h#1 $
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
 *
 * RWInetType
 * The Internet address type.
 * This is like an envelope with no address on it.
 *
 * RWInetPort
 * Encapsulates an internet port and its service names.  You can
 * construct an RWInetPort from either an explicit port number or a
 * symbolic service name.
 *
 * RWInetHost
 * Encapsulates an internet host IP address and its names. You can
 * construct an RWInetHost from either an explicit IP address or a
 * symbolic name.
 *
 * RWInetAddr
 * A complete internet address:  type information, a host, and a port
 *
 */

#include <rw/network/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/tvvector.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup networking_module
 * \class RWInetHost
 *
 * \brief
 * Encapsulates an Internet host IP address and its names.
 *
 * Encapsulates an Internet host IP address and its names. You can construct
 * an RWInetHost from either an IP address or a symbolic name.
 *
 * \note
 * Typically, Winsock implementations do not return a default alias. As a
 * result, an RWInetHost object on a Windows platform includes alias names
 * only if they have been explicitly defined.
 */
class RW_NETWORK_SYMBOLIC RWInetHost
{
public:

    /**
     * Attributes to change name lookup behavior.
     */
    enum NameLookup {
        /**
         * If the host address is already known, a lookup will not be used
         * to discover the host name. The dotted decimal form of the host
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
    //
    // Both the string and char* constructors are necessary.
    // This way you can use either a char* or a string where a port is
    // needed.
    //
    // None of these constructors will block.
    /**
     * An Internet host can be specified as an actual address or through a
     * string. The string can be either the symbolic name of the host or an
     * IP address in dotted decimal notation. If an IP address is passed in
     * as a \c long, it must be in network byte order. The default
     * constructor creates a special host that represents an unspecified IP
     * address on the current machine. This is useful when constructing
     * servers. The RWCString should contain 7-bit US-ASCII data.
     */
    RWInetHost();

    /**
     * \copydoc RWInetHost::RWInetHost()
     */
    RWInetHost(unsigned long IPAddress);

    /**
     * \copydoc RWInetHost::RWInetHost()
     */
    RWInetHost(const RWCString& hostname);

    /**
     * \copydoc RWInetHost::RWInetHost()
     */
    RWInetHost(const char*);

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

    bool anyHost() const;
    // Returns true if this host represents any available host interface
    // on the machine.

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWInetHost::getName() instead")
    RWCString                    name() const;

    RW_DEPRECATE_FUNC("Use RWInetHost::getAddress() instead")
    unsigned long                address() const;

    RW_DEPRECATE_FUNC("Use RWInetHost::getAliases() instead")
    RWTValVector<RWCString>      aliases() const;

    RW_DEPRECATE_FUNC("Use RWInetHost::getAddresses() instead")
    RWTValVector<unsigned long>  addresses() const;
#endif

    /**
     * Returns the official name for this host entry. This call may block if
     * prepare() has not been called. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString                    getName() const;

    /**
     * Returns the primary IP address for this host entry in network byte
     * order. If you want to print out an IP address, use the
     * addressAsString() static member function.
     */
    unsigned long                getAddress() const;

    /**
     * Returns the list of aliases for this host entry. The official name is
     * not included in the list of aliases. This call may block if prepare()
     * has not been called. The RWCString should contain 7-bit US-ASCII
     * data.
     *
     * \note
     * Aliases are returned only if the RWInetHost was constructed with a
     * hostname (as opposed to an IP Address). If the class was constructed
     * with an IP address, no aliases are fetched.
     */
    RWTValVector<RWCString>      getAliases() const;

    /**
     * Returns a list of addresses for this host entry. Addresses are
     * returned in network byte order. If you want to print out an IP
     * address, use the addressAsString() static member function. The
     * primary address is the first entry in the getAddresses() array. This
     * call may block if prepare() has not been called.
     */
    RWTValVector<unsigned long>  getAddresses() const;

    /**
     * Returns a string describing self. The verbosity of the output is
     * controlled by \a level, where \c level=0 is the most basic output,
     * and \c level=9 is the most verbose. If not specified, a default value
     * of 0 is used and is guaranteed not to block.
     *
     * Depending on the \a level and the constructor the instance was
     * instantiated with, the output may contain the host name or IP
     * address, any known aliases for that name and any alternate IP
     * addresses.
     *
     * <b>Grammar Definitions</b>
     *
     * <pre>
     * ip-address ::= <em>\<ip address in dotted decimal notation\></em>
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
     * %RWInetHost("127.0.0.1")</th>
     * </tr>
     * <tr>
     * <td>\c 0</td>
     * <td></td>
     * <td><tt>host</tt></td>
     * <td><tt>127.0.0.1</tt></td>
     * </tr>
     * <tr>
     * <td>\c 1</td>
     * <td></td>
     * <td><tt>host</tt></td>
     * <td><tt>127.0.0.1</tt></td>
     * </tr>
     * <tr>
     * <td>\c 2</td>
     * <td></td>
     * <td><tt>host</tt></td>
     * <td><tt>127.0.0.1</tt></td>
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
     * <td><tt>localhost(127.0.0.1)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 5</td>
     * <td align="center">\c X</td>
     * <td><tt>host "(" ip-address ")"</tt></td>
     * <td><tt>localhost(127.0.0.1)</tt></td>
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
     * <td><tt>localhost(127.0.0.1)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 8</td>
     * <td align="center">\c X</td>
     * <td><tt>host "(" ip-address ")"</tt></td>
     * <td><tt>localhost(127.0.0.1)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 9</td>
     * <td align="center">\c X</td>
     * <td><tt>host (alias-list)? "(" ip-address-list ")"</tt></td>
     * <td><tt>localhost(127.0.0.1)</tt></td>
     * </tr>
     * </table>
     */
    RWCString id(unsigned level = 0) const;

    /**
     * Returns \c true if the two host objects are equal.
     */
    bool operator==(const RWInetHost& rhs) const;

    /**
     * Returns \c true if the two host objects are not equal.
     */
    bool operator!=(const RWInetHost& rhs) const;

    /**
     * Returns the host object for the host on which this program is
     * currently running.
     */
    static RWInetHost me();

    // Auxiliary functions related to internet hosts and addresses.
    // me() returns the host object for the host on which we are currently
    // running.  addressAsString() takes an address in network byte order
    // and returns the dotted decimal string representation of the address.
    // To go from a dotted decimal string to a address, build an RWInetHost
    // object from the dotted decimal string.
    /**
     * Takes an address in network byte order and returns the dotted decimal
     * string representation of the address. To go from a dotted decimal
     * string to an address, build an RWInetHost object from the dotted
     * decimal string. The RWCString should contain 7-bit US-ASCII data.
     */
    static RWCString  addressAsString(unsigned long IPAddress);

private:
    RWCString                    name_;
    RW_INADDR_TYPE                 addr_;
    RWTValVector<RWCString>      aliases_;
    RWTValVector<unsigned long>  addresses_;

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
 * \relates RWInetHost
 *
 * Outputs a representation of \a host on \a strm. The representation is
 * generated using the member function host.id() with \c level=0.
 *
 * \note
 * This class does not have an extraction (>>) operator.
 */
RW_NETWORK_SYMBOLIC std::ostream&
operator<<(std::ostream& strm, const RWInetHost& host);

#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWInetHost::name() const
{
    return getName();
}

inline unsigned long
RWInetHost::address() const
{
    return getAddress();
}

inline RWTValVector<RWCString>
RWInetHost::aliases() const
{
    return getAliases();
}

inline RWTValVector<unsigned long>
RWInetHost::addresses() const
{
    return getAddresses();
}
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_network_RWInetHost_h__
