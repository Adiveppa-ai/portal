#ifndef __rw_network_RWInetPort_h__
#define __rw_network_RWInetPort_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWInetPort.h#1 $
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
 * The Internet address type. This is like an envelope with no address on it.
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
 *
 * \brief
 * Encapsulates an Internet port and its service names.
 *
 * Encapsulates an Internet port and its service names. You can construct an
 * RWInetPort from either an explicit port number or a symbolic service
 * name.
 */
class RW_NETWORK_SYMBOLIC RWInetPort
{
public:

    // Build a port from the port number itself, or from a string representing
    // the name of the port.
    // Both the string and char* constructors are necessary.
    // This way you can use either a char* or a string where a port is
    // needed.
    // None of the constructors will block.
    /**
     * Builds a port from the port number itself or from a string
     * representing the name of the port.
     */
    RWInetPort(int port = 0);

    /**
     * Builds a port from the port number itself or from a string
     * representing the name of the port.
     */
    RWInetPort(const RWCString& service);

    /**
     * Builds a port from the port number itself or from a string
     * representing the name of the port.
     */
    RWInetPort(const char*);

    // Set up so no future operations will block.
    // This calls
    // the service database routines to learn all that can be
    // learned about this port name.
    //
    // It is not necessary to explicitly call prepare().
    // It will be called by other member functions if necessary.
    /**
     * Ensures that no future operations block. This function calls the
     * service database routines to learn all that can be learned about this
     * port name. It is not necessary to explicitly call prepare() because
     * it is called by other member functions if needed.
     */
    void prepare() const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWInetPort::getPort() instead")
    int                     port() const;

    RW_DEPRECATE_FUNC("Use RWInetPort::getName() instead")
    RWCString               name() const;

    RW_DEPRECATE_FUNC("Use RWInetPort::getAliases() instead")
    RWTValVector<RWCString> aliases() const;
#endif

    /**
     * Returns the port number for this port.
     */
    int                     getPort() const;

    /**
     * Returns the official service name for this port. The RWCString should
     * contain 7-bit US-ASCII data.
     */
    RWCString               getName() const;

    /**
     * Returns the list of aliases for this service name. The RWCString
     * should contain 7-bit US-ASCII data.
     */
    RWTValVector<RWCString> getAliases() const;

    /**
     * Returns a string describing self. The verbosity of the output is
     * controlled by \a level where \c level=0 is the most basic output, and
     * \c level=9 is the most verbose. The RWCString should contain 7-bit
     * US-ASCII data.
     *
     * <b>Grammar Definitions</b>
     *
     * <pre>
     * port ::= <em>\<port number\></em>
     * service-name-value ::= <em>\<service name\></em>
     * service-name ::= "(" service-name-value ")"
     * service-name-list ::= "(" service-name-value ("," service-name-value)* ")"
     * </pre>
     *
     * <table>
     * <tr>
     * <th>\a level</th>
     * <th>Calls %prepare()</th>
     * <th>Output Grammar</th>
     * <th>Sample Output for id(\a level) given %RWInetPort(80)</th>
     * </tr>
     * <tr>
     * <td>\c 0</td>
     * <td></td>
     * <td><tt>port</tt></td>
     * <td><tt>80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 1</td>
     * <td></td>
     * <td><tt>port</tt></td>
     * <td><tt>80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 2</td>
     * <td></td>
     * <td><tt>port</tt></td>
     * <td><tt>80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 3</td>
     * <td align="center">\c X</td>
     * <td><tt>port</tt></td>
     * <td><tt>80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 4</td>
     * <td align="center">\c X</td>
     * <td><tt>port (service-name)?</tt></td>
     * <td><tt>80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 5</td>
     * <td align="center">\c X</td>
     * <td><tt>port (service-name)?</tt></td>
     * <td><tt>80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 6</td>
     * <td align="center">\c X</td>
     * <td><tt>port</tt></td>
     * <td><tt>80</tt></td>
     * </tr>
     * <tr>
     * <td>\c 7</td>
     * <td align="center">\c X</td>
     * <td><tt>port (service-name)?</tt></td>
     * <td><tt>80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 8</td>
     * <td align="center">\c X</td>
     * <td><tt>port (service-name)?</tt></td>
     * <td><tt>80(http)</tt></td>
     * </tr>
     * <tr>
     * <td>\c 9</td>
     * <td align="center">\c X</td>
     * <td><tt>port (service-name-list)?</tt></td>
     * <td><tt>80(http,www,www-http)</tt></td>
     * </tr>
     * </table>
     */
    RWCString id(unsigned level = 0) const;

    /**
     * Returns \c true if the two port objects are equal.
     */
    bool operator==(const RWInetPort& rhs) const;

    /**
     * Returns \c true if the two port objects are not equal.
     */
    bool operator!=(const RWInetPort& rhs) const;

private:
    int                     port_;  // in host, not network, byte order
    RWCString               name_;
    RWTValVector<RWCString> aliases_;
    // These items of data are only valid if the corresponding flags are
    // set to true.

    bool knowPort_;
    bool knowName_;
    // These flags indicate what we know about the port.  Once we know
    // both the port and the name we know everything.

};

/**
 * \relates RWInetPort
 *
 * Outputs a representation of \a port on \a strm. The representation is
 * generated using the member function port.id() with \c level=0.
 *
 * \note
 * This class does not have an extraction (>>) operator.
 */
RW_NETWORK_SYMBOLIC std::ostream&
operator<<(std::ostream& strm, const RWInetPort& port);

#if !defined(RW_DISABLE_DEPRECATED)
inline int
RWInetPort::port() const
{
    return getPort();
}

inline RWCString
RWInetPort::name() const
{
    return getName();
}

inline RWTValVector<RWCString>
RWInetPort::aliases() const
{
    return getAliases();
}
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_network_RWInetPort_h__
