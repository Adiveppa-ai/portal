#ifndef __rw_network_RWSockAddr_h__
#define __rw_network_RWSockAddr_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSockAddr.h#1 $
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
 * RWSockAddr: a socket address proxy
 *
 * An RWSockAddr is a proxy to a socket address of some unknown type.  The
 * RWSockAddr keeps a handle to a reference counted RWSockAddrBase object
 * which is used to do the actual work; the RWSockAddr passes requests on
 * to this real address.
 *
 * RWSockAddr is used by the rwSockAddrFactory to return addresses whose
 * precise types are unknown.  It is used indirectly by RWSocket functions
 * such as getpeername() which return an address of unknown type.  A common
 * use in applications will be to construct an RWSockAddr from an istream.
 * This allows you to specify different address families at run time, for
 * example by storing the address in a configuration file.
 */

#include <rw/network/RWSockAddrBase.h>
#include <rw/network/RWTNetHandle.h>
#include <rw/network/fwd.h>
#include <rw/network/pkgdefs.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/**
 * \ingroup networking_module
 *
 * \brief
 * A proxy to a socket address.
 *
 * RWSockAddr is a proxy to a socket address of a type that is not known
 * until runtime. The RWSockAddr keeps a handle to a reference-counted
 * RWSockAddrBase object, which is the real address. The RWSockAddr passes
 * requests on to this object.
 */
class RW_NETWORK_GLOBAL RWSockAddr : public RWSockAddrBase
{
public:
    /**
     * Creates an invalid address. The address must be set to something
     * useful before trying to use it. Common methods to set the address
     * include shifting the address in from an \b std::istream or using the
     * assignment operator.
     */
    RWSockAddr();

    // Creates an address object from the C API representation.
    // This uses the rwSockAddrFactory to look up a specific construction
    // routine to construct the address.
    // The optional type parameter indicates the type of the
    // socket (ie SOCK_DGRAM).
    // An exception is thrown if the address is not a recognized address type.
    /**
     * Creates an address object from the C API representation. This
     * constructor uses the
     * \ref RWSockAddrFactory::rwSockAddrFactory "rwSockAddrFactory" to look
     * up a specific construction routine to construct the address. An
     * RWNetNoNumberFactoryRegisteredError exception is thrown if the
     * address is not a recognized type.
     */
    RWSockAddr(sockaddr* addr, RWSockLenType len);

    /**
     * Creates an address object from the C API representation. This
     * constructor uses the
     * \ref RWSockAddrFactory::rwSockAddrFactory "rwSockAddrFactory" to look
     * up a specific construction routine to construct the address. An
     * RWNetNoNumberFactoryRegisteredError exception is thrown if the
     * address is not a recognized type.
     */
    RWSockAddr(sockaddr* addr, RWSockLenType len, int type);


    /**
     * Constructs an address from the address specification in the string.
     * The first token in the string indicates the type of address. The
     * remainder indicates the specific address. Examples of the format are
     * \"<tt>inet ftp.roguewave.com ftp</tt>\" and
     * \"<tt>inet www.roguewave.com 80</tt>\". The RWSockAddrFactory is used
     * to actually construct the address. An
     * RWNetNoNameFactoryRegisteredError exception is thrown if the address
     * is not a recognized type. The RWCString should contain 7-bit US-ASCII
     * data.
     */
    RWSockAddr(const RWCString& str);

    /**
     * Constructs an RWSockAddr that represents \a addr. \a addr must be an
     * object allocated on the heap. It is deleted when no RWSockAddr
     * objects refer to it. This constructor is available for general use,
     * but it is most often used by the RWSockAddrFactory.
     */
    RWSockAddr(RWSockAddrBase* addr);

    /**
     * Returns the type of address.
     */
    virtual RWSockType addressType() const;

    /**
     * Returns a pointer to an internal representation of the address that
     * was cast to a \c sockaddr structure, as defined by the sockets and
     * TLI APIs (TLI is the Unix System V network communication interface).
     * The pointer is to an internal data structure, so it becomes invalid
     * if this object is changed in any way or goes out of scope. If the
     * address has no representation as a \c sockaddr, a null pointer is
     * returned.
     */
    virtual sockaddr* asSockaddr() const;

    /**
     * Returns the size of an internal representation of the socket address
     * defined by the sockets.
     */
    virtual size_t    sockaddrSize() const;

    /**
     * Forwards the prepare() request onto the real address object. The
     * address object sets up all internal data so that subsequent calls to
     * interfaces on this address do not block.
     */
    virtual void prepare() const;

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
    virtual RWCString id(unsigned level = 0) const;

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWSockAddr::isValid() instead")
    bool valid() const;
#endif

    /**
     * Returns \c true if this address is a proxy to a real address. A proxy
     * to an invalid address is created using the default constructor.
     */
    bool isValid() const;

private:
    virtual const RWSockAddrBase* myAddress() const;
    // Returns the address of the object being proxied.  If the
    // object being proxied is itself a proxy, the request is forwarded,
    // and so on.

    RWTNetHandle<RWSockAddrBase> addr_;
    // A reference counted handle to the address that we are a proxy to.
};

// Reads the input stream and constructs an address from the information
// on the stream.  Example allowed formats are "inet ftp.roguewave.com ftp",
// and "unix /tmp/here", for example.
// The rwSockAddrFactory is used to actually construct the address.
/**
 * \relates RWSockAddr
 *
 * Reads an address from an input stream or writes it onto an output stream.
 */
RW_NETWORK_SYMBOLIC std::istream&
operator>>(std::istream&, RWSockAddr&);


inline bool
RWSockAddr::isValid() const
{
    RWSockAddrBase* base = (RWSockAddrBase*)addr_;
    return (base ? true : false);
}

#if !defined(RW_DISABLE_DEPRECATED)
inline bool
RWSockAddr::valid() const
{
    return isValid();
}
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif  // __rw_network_RWSockAddr_h__ 
