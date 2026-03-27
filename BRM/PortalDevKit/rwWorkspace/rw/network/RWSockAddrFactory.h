#ifndef __rw_network_RWSockAddrFactory_h__
#define __rw_network_RWSockAddrFactory_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSockAddrFactory.h#1 $
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
 * rwSockAddrFactory:  Construct an address whose type varies at run time
 *
 * The object rwSockAddrFactory is a factory for constructing socket addresses
 * whose types are not known until runtime.
 * Usually, the use of this factory is transparent to the library client.
 * It is used by the istream shift operator, and by the constructor from
 * the C struct sockaddr.
 *
 * The types are indicated to the factory by either the address family integer
 * identifier (as used defined by the C sockets API) or a string.
 * From there, the factory turns around and invokes a factory specific to
 * the address family.
 * If finds the specific factory using a dictionary kept with the factory.
 *
 * Specific address factory objects need to be registered with the factory via
 * the general factory's register() method.
 * Check out [[RWInetAddrFactory]] for an example of a specific
 * address family factory.
 * In an initial prototype code line, we experimented with using a template
 * class for specific address families, but found that subtle differences
 * between the families and subtle template bugs in some compilers made
 * this approach more trouble that it was worth.
 *
 * All singleton objects are constructed explicitly rather than relying
 * on static initialization.  This way we have no dependence on static
 * initialization here.
 */

#include <rw/network/RWSockAddrFactoryBase.h>
#include <rw/network/RWTNetHandle.h>
#include <rw/network/fwd.h>
#include <rw/network/pkgdefs.h>
#include <rw/tvsldict.h>

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

/*
 * RWSockAddrFactory: Build addresses of any (registered) type
 *
 * Building an address using this factory happens in two stages.  First,
 * the type of address is determined.  Next, the type of address is used
 * to look up an RWSockAddrFactoryBase object, and that is used to actually
 * construct the address.  Note that since an RWSockAddrFactory is itself
 * an RWSockAddrFactoryBase, this scheme can be used in a hierarchical fashion.
 */

/**
 * \ingroup networking_module
 *
 * \brief
 * Builds addresses of any registered type. Not intended for explicit use.
 *
 * RWSockAddrFactory builds addresses of any registered type. This class is
 * used by the Networking classes implementation and is not normally used
 * explicitly. The global object #rwSockAddrFactory is used by functions
 * such as RWSocket::getsockname(), which do not know the type of socket
 * address to build.
 *
 * Specific address factory objects need to be registered with the factory
 * via the general factory's registerWithFactory() method. Check
 * RWInetAddrFactory for an example of a specific address family factory.
 *
 * These singleton objects are constructed when used, so they are not
 * dependent on the order of static initialization.
 */
class RW_NETWORK_GLOBAL RWSockAddrFactory : public RWSockAddrFactoryBase
{
public:
    // Be very careful using this. This will create a local address factory
    // with which you can register creator factories and create addresses.
    // Invoking methods on your local copy will not change the singleton
    // factory instance.
    //
    // Using the constructor will _not_ create the singleton instance.
    /**
     * Creates a factory with no create methods attached.
     */
    RWSockAddrFactory();

    // destroy all factories for known address types
    // User is responsible for destroying their Factory types
    /**
     * Virtual destructor.
     */
    virtual ~RWSockAddrFactory();

    /**
     * Registers maker objects. Duplicate registration is a no-op. If you
     * attempt to register two different factories with the same family, an
     * exception is thrown. The variant that takes a socket type argument
     * registers both the standard family name for that socket type and the
     * family number. The pointer to the factory must remain valid as long
     * as self is used to build addresses. The RWCString should contain
     * 7-bit US-ASCII data.
     */
    void registerWithFactory(const RWSockType& family, RWSockAddrFactoryBase* maker);

    /**
     * \copydoc registerWithFactory(const RWSockType&, RWSockAddrFactoryBase*)
     */
    void registerWithFactory(int family, RWSockAddrFactoryBase* maker);

    /**
     * \copydoc registerWithFactory(const RWSockType&, RWSockAddrFactoryBase*)
     */
    void registerWithFactory(const RWCString& family, RWSockAddrFactoryBase* maker);

    /**
     * Removes all knowledge from the factory of how to build addresses of
     * the indicated family. This is useful if you want to explicitly
     * replace one factory with another for the same family. Unless you
     * first unRegister(), an RWNetAlreadyRegisteredError exception is
     * thrown. It is not an error to unregister a type that has never been
     * registered. The RWCString should contain 7-bit US-ASCII data.
     */
    void unRegister(const RWSockType&);

    /**
     * \copydoc unRegister(const RWSockType&)
     */
    void unRegister(int family);

    /**
     * \copydoc unRegister(const RWSockType&)
     */
    void unRegister(const RWCString& family);

    // Construct a socket address.
    // First extract the
    // family name (from the strm/string)
    // or identifier (from the sockaddr), then look up the appropriate maker
    // object and use it.  If no maker has been registered for the family, an
    // exception is thrown.
    // The string is first canonicalized using
    // RWSockAddrBase::cannonicalizeInputString().
    /**
     * Returns a pointer to an RWSockAddrBase derived object constructed
     * from the provided \c sockaddr. This function will find the
     * RWSockAddrFactoryBase registered for the socket address family of
     * \a addr. It will then pass the input parameters \a addr and
     * \a addrLen to that factory to get an RWSockAddrBase derived object of
     * the appropriate type. If no factory has been registered for the
     * requested family, an RWNetNoNumberFactoryRegisteredError exception is
     * thrown.
     *
     * The \a addr parameter is expected to point to an concrete socket
     * address type such as \c sockaddr_in, \c sockaddr_in6 or
     * \c sockaddr_un cast to a \c sockaddr.
     *
     * The \a addrLen parameter is expected to describe the size, in bytes,
     * of the object pointed to by \a addr.
     *
     * The newly created RWSockAddrBase is allocated on the heap. The caller
     * is responsible for deleting it. Often, this is managed by wrapping
     * the object using an RWSockAddr.
     */
    virtual RWSockAddrBase* operator()(struct sockaddr* addr,
                                       RWSockLenType  addrLen) const;

    /**
     * Returns a pointer to an RWSockAddrBase derived object constructed
     * from the provided \c sockaddr. This function will find the
     * RWSockAddrFactoryBase registered for the socket address family of
     * \a addr. It will then pass the input parameters \a addr, \a addrLen,
     * and \a type to that factory to get an RWSockAddrBase derived object
     * of the appropriate type. If no factory has been registered for the
     * requested family, an RWNetNoNumberFactoryRegisteredError exception is
     * thrown.
     *
     * The \a addr parameter is expected to point to an concrete socket
     * address type such as \c sockaddr_in, \c sockaddr_in6 or
     * \c sockaddr_un cast to a \c sockaddr.
     *
     * The \a addrLen parameter is expected to describe the size, in bytes,
     * of the object pointed to by \a addr.
     *
     * The \a type parameter is passed to the appropriate
     * RWSockAddrFactoryBase instance when a request is made to create a
     * derived RWSockAddrBase. It describes the type of socket address to be
     * created. This would normally be one of \c SOCK_STREAM or
     * \c SOCK_DGRAM.
     *
     * The newly created RWSockAddrBase is allocated on the heap. The caller
     * is responsible for deleting it. Often, this is managed by wrapping
     * the object using an RWSockAddr.
     */
    virtual RWSockAddrBase* operator()(struct sockaddr* addr,
                                       RWSockLenType addrLen, int type) const;

    /**
     * Returns a pointer to an RWSockAddrBase derived object constructed
     * from from the provided RWCString. This function will find the
     * RWSockAddrFactoryBase registered for the socket address family
     * described in \a str. It will then pass a string derived from \a str
     * to that factory to get an RWSockAddrBase derived object of the
     * appropriate type. If no factory has been registered for the requested
     * family, an RWNetNoNameFactoryRegisteredError exception is thrown.
     *
     * The newly created RWSockAddrBase is allocated on the heap. The caller
     * is responsible for deleting it. Often, this is managed by wrapping
     * the object using an RWSockAddr.
     */
    virtual RWSockAddrBase* operator()(const RWCString& str) const;

#if !defined(RW_DISABLE_DEPRECATED)
    /**
     * \deprecated
     * As of SourcePro 4, use rwSockAddrFactory() instead.
     *
     * Returns the global factory that is used by the Networking classes.
     * This is more conveniently accessed via the #rwSockAddrFactory macro.
     * If the factory has not yet been constructed, it is constructed and
     * the well-known families are registered.
     */
    RW_DEPRECATE_FUNC("Use rwSockAddrFactory() instead")
    static RWSockAddrFactory& theGlobalRWSockAddrFactory();
#endif

    static RWTNetHandle<RWSockAddrFactory> instance();
    // Returns the global factory that is used by the SourcePro Net -
    // Essential Networking Module.  This is more conveniently accessed via
    // the rwSockAddrFactory macro.  If the factory has not yet been
    // constructed, it will be constructed, and the well known families will
    // be registered.

private:

    RWTValSlistDictionary<int, RWSockAddrFactoryBase*> factoryKeyedByInt_;

    RWTValSlistDictionary<RWCString, RWSockAddrFactoryBase*> factoryKeyedByString_;
    // The factories called indirectly to build the address.
};

#if !defined(RW_DISABLE_DEPRECATED)
inline RWSockAddrFactory&
RWSockAddrFactory::theGlobalRWSockAddrFactory()
{
    return *RWSockAddrFactory::instance();
}
#endif

/**
 * \relates RWSockAddrFactory
 *
 * Defined internally as a macro to obtain a reference to the factory
 * object.
 */
#define rwSockAddrFactory (*RWSockAddrFactory::instance())

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif  // __rw_network_RWSockAddrFactory_h__
