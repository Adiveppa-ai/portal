#ifndef __rw_network_RWSockAddrBase_h__
#define __rw_network_RWSockAddrBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSockAddrBase.h#1 $
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
 * RWSockAddrBase: a socket address
 *
 * RWSockAddrBase is an abstract base class for representing socket addresses.
 * It corresponds to the C API struct sockaddr.
 *
 * Derived class constructors will not block.
 * Blocking may occur, however, when you call
 * one of the member functions, such as asSockaddr().
 * A routine like this can also be called indirectly, for example when you
 * connect an RWSocket to an address.
 * To prevent blocking, call prepare() before using the address.
 * This will do any preparation necessary to make the address completely
 * ready for use.
 * For example, in the Internet family, prepare() will obtain the host
 * address from the name, and the port number from the service name.
 */

#include <rw/network/fwd.h>
#include <rw/network/pkgdefs.h>
#include <rw/cstring.h>
#include <rw/tvordvec.h>

struct sockaddr;

/**
 * \ingroup networking_module
 *
 * \brief
 * Interface class that represents a socket address.
 *
 * RWSockAddrBase is an interface class that represents a socket address.
 * All member functions are virtual. The class RWSockAddr is a proxy class
 * that provides an interface to an RWSockAddrBase object whose exact type
 * can be known only at run time.
 */
class RW_NETWORK_GLOBAL RWSockAddrBase
{
public:
    // Destroy this address object.  We need a virtual destructor so that the
    // correct destructor will be called when destroying an RWSockAddr.
    /**
     * Virtual destructor.
     */
    virtual ~RWSockAddrBase();

    // Set up all internal data so that no subsequent calls to interfaces on
    // this address will block.
    // This is declared const because conceptually, nothing in the address
    // is changed.
    // Also, this may be called from const functions like asSockaddr(), so
    // it needs to be const.
    // In practice, implementations of this class will often have to either
    // use mutable, or cast away the constness.
    /**
     * Sets up all internal data so that subsequent calls to interfaces on
     * this address do not block.
     */
    virtual void prepare() const;

    /**
     * Returns the type of address.
     */
    virtual RWSockType addressType() const = 0;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWSockAddrBase::getFamilyName() instead")
    RWCString familyName() const;

    RW_DEPRECATE_FUNC("Use RWSockAddrBase::getFamily() instead")
    int family() const;

    RW_DEPRECATE_FUNC("Use RWSockAddrBase::getDomain() instead")
    int domain() const;

    RW_DEPRECATE_FUNC("Use RWSockAddrBase::getType() instead")
    int type() const;

    RW_DEPRECATE_FUNC("Use RWSockAddrBase::getProtocol() instead")
    int protocol() const;
#endif

    /**
     * Gets the socket family name. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    RWCString getFamilyName() const;

    /**
     * Returns the integer identifier of the address domain for the socket
     * type, such as \c AF_INET for an Internet domain.
     */
    int getFamily() const;

    /**
     * Alias for getFamily().
     */
    int getDomain() const;

    /**
     * Gets the socket address type.
     */
    int getType() const;

    /**
     * Gets the socket protocol.
     */
    int getProtocol() const;

    /**
     * Returns a pointer to an internal representation of the address cast
     * to a \c sockaddr structure, as defined by the sockets and TLI APIs
     * (TLI is the Unix System V network communication interface). The
     * pointer points to an internal data structure, so it becomes invalid
     * if this object is changed in any way or goes out of scope. If the
     * address has no representation as a \c sockaddr, a null pointer is
     * returned. These operations may block if prepare() has not been
     * called.
     */
    virtual sockaddr* asSockaddr() const = 0;

    /**
     * Returns the size of an internal representation of the socket address
     * defined by the sockets.
     */
    virtual size_t    sockaddrSize() const = 0;

    // converts a particular address to a RWCString. The returned value of id(),
    // which is a RWCString, is used as default. Specialization classes of
    // this RWSockAddrBase may overwrite this type conversion operator, if
    // necessary.
    /**
     * Conversion operator. Converts its address to an RWCString. This
     * operator is similar to the id() function, but it can be used for
     * implicit conversion to an RWCString. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    virtual operator RWCString() const;

    // Return a string which identifies this address.
    // The higher the setting on level, the more information is provided.
    // Using level=0 (the default) is guaranteed not to block, higher
    // levels may hit the network to determine information.
    /**
     * Returns a string describing self. The verbosity of the output is
     * controlled by \a level where \c level=0 is the most basic output, and
     * \c level=9 is the most verbose. The RWCString should contain 7-bit
     * US-ASCII data.
     */
    virtual RWCString id(unsigned level = 0) const = 0;

    /**
     * Used by derived classes to implement narrowing conversions from an
     * RWSockAddr or an RWSockAddrBase to a derived address type. It returns
     * \c this, unless \c this address is a proxy, in which case it returns
     * the pointer to the base class of the object being proxied.
     */
    virtual const RWSockAddrBase* myAddress() const;

    /**
     * Outputs a representation of \a x on \a strm. The representation is
     * generated using the member function x.id() with \c level=0.
     *
     * \note
     * This class does not have an extraction (>>) operator.
     */
    friend RW_NETWORK_SYMBOLIC std::ostream&
    operator<<(std::ostream& strm, const RWSockAddrBase& x);

    static RWCString cannonicalizeInputString(const RWCString& in);
    // Do canonical transformations on a string from which we are
    // going to extract a socket address.
    // Removes comments (in parentheses) & replaces colons with spaces.

    static RWTValOrderedVector<RWCString> tokenizeInputString(const RWCString& s);
    // Break the string up into tokens at whitespace.  Before breaking up,
    // the string is put into canonical form using cannonicalizeInputString.

    static short stringToSocketType(const RWCString& s);
    // Convert the string s to a socket type, or else throw an exception.
    // The socket types are the ones that can be output by RWSockAddrBase::id().

    static RWCString stripComments(const RWCString& in);
    // Strips comments from an address.
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWCString
RWSockAddrBase::familyName() const
{
    return getFamilyName();
}

inline int
RWSockAddrBase::family() const
{
    return getFamily();
}

inline int
RWSockAddrBase::domain() const
{
    return getDomain();
}

inline int
RWSockAddrBase::type() const
{
    return getType();
}

inline int
RWSockAddrBase::protocol() const
{
    return getProtocol();
}
#endif

#endif  // __rw_network_RWSockAddrBase_h__ 
