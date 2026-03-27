#ifndef __rw_network_RWSocketPortal_h__
#define __rw_network_RWSocketPortal_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSocketPortal.h#1 $
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

#include <rw/network/RWPortal.h>
#include <rw/network/RWSocket.h>  /* we return an RWSocket from a member fn */
#include <rw/network/RWSocketPortalBase.h>
#include <rw/network/pkgdefs.h>

/**
 * \ingroup networking_module
 *
 * \brief
 * Socket implementation of a portal.
 *
 * RWSocketPortal is a socket implementation of a portal, implemented using
 * the RWSocket class. State is not added to RWPortal. This means that you
 * can assign an RWSocketPortal to an RWPortal without loss of data, except
 * for the type.
 *
 * The RWSocket representing the RWSocketPortal communication channel is
 * normally closed when the last portal into the channel is destroyed. It is
 * possible to prevent this by using a special constructor.
 */
class RW_NETWORK_GLOBAL RWSocketPortal : public RWPortal, public RWSocketPortalBase
{
public:
    /**
     * Creates a socket portal. You need to establish a connection using
     * connect() or the assignment operator before the portal can be used.
     */
    RWSocketPortal();

    /**
     * Creates a socket portal connected to the address provided.
     */
    RWSocketPortal(const RWSockAddrBase&);

    /**
     * Creates a portal to the communications channel represented by socket.
     * Using this constructor is the only way to create a socket that is not
     * automatically closed when portals are no longer using it.
     */
    RWSocketPortal(const RWSocket& socket, WhoShouldClose = Portal);

    /**
     * Connects this portal to the \a address provided.
     */
    void connect(const RWSockAddrBase& address);

#if !defined(RW_DISABLE_DEPRECATED)
    RW_DEPRECATE_FUNC("Use RWSocketPortal::getSocket() instead")
    RWSocket socket() const;
#endif

    /**
     * Returns a copy of the underlying RWSocket object.
     */
    RWSocket getSocket() const;
};


#if !defined(RW_DISABLE_DEPRECATED)
inline RWSocket
RWSocketPortal::socket() const
{
    return getSocket();
}
#endif

#endif  // __rw_network_RWSocketPortal_h__
