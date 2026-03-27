#ifndef __rw_network_RWSockAddrFactoryBase_h__
#define __rw_network_RWSockAddrFactoryBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSockAddrFactoryBase.h#1 $
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

#include <rw/network/fwd.h>
#include <rw/network/pkgdefs.h>

class RWCString;

/**
 * \ingroup networking_module
 *
 * \brief
 * Abstract class that builds socket addresses.
 *
 * RWSockAddrFactoryBase is an abstract class that builds socket addresses.
 * It represents the concept of an object that can build socket addresses
 * from either an input string or from the C API representation.
 */
class RW_NETWORK_GLOBAL RWSockAddrFactoryBase
{
public:
    // Need a virtual destructor because we keep collections typed to this.
    /**
     * Destroys self.
     */
    virtual ~RWSockAddrFactoryBase();

    /**
     * Returns a pointer to an RWSockAddrBase derived object constructed
     * from the provided \c sockaddr.
     *
     * The \a addr parameter is expected to point to a concrete socket
     * address type appropriate for this factory. For instance, a factory
     * for creating RWInetAddr instances would expect \a addr to be a
     * pointer to \c sockaddr_in.
     *
     * The \a addrLen parameter is expected to describe the size, in bytes,
     * of the object pointed to by \a addr.
     *
     * The newly created RWSockAddrBase is allocated on the heap. The caller
     * is responsible for deleting it. Often, this is managed by wrapping
     * the object using an RWSockAddr.
     */
    virtual RWSockAddrBase* operator()(struct sockaddr* addr,
                                       RWSockLenType addrLen) const = 0;

    /**
     * Returns a pointer to an RWSockAddrBase derived object constructed
     * from the provided \c sockaddr.
     *
     * The \a addr parameter is expected to point to a concrete socket
     * address type appropriate for this factory. For instance, a factory
     * for creating RWInetAddr instances would expect \a addr to be a
     * pointer to \c sockaddr_in.
     *
     * The \a addrLen parameter is expected to describe the size, in bytes,
     * of the object pointed to by \a addr.
     *
     * The \a type parameter describes the type of socket address to be
     * created. This would normally be one of \c SOCK_STREAM or
     * \c SOCK_DGRAM.
     *
     * The newly created RWSockAddrBase is allocated on the heap. The caller
     * is responsible for deleting it. Often, this is managed by wrapping
     * the object using an RWSockAddr.
     */
    virtual RWSockAddrBase* operator()(struct sockaddr* addr,
                                       RWSockLenType addrLen, int type) const = 0;

    /**
     * Returns a pointer to an RWSockAddrBase derived object constructed
     * from the provided RWCString.
     *
     * The newly created RWSockAddrBase is allocated on the heap. The caller
     * is responsible for deleting it. Often, this is managed by wrapping
     * the object using an RWSockAddr.
     */
    virtual RWSockAddrBase* operator()(const RWCString& str) const = 0;

};

#endif  // __rw_network_RWSockAddrFactoryBase_h__
