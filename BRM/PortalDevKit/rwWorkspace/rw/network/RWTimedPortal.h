#ifndef __rw_network_RWTimedPortal_h__
#define __rw_network_RWTimedPortal_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWTimedPortal.h#1 $
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
#include <rw/network/pkgdefs.h>

/**
 * \ingroup networking_module
 *
 * \brief
 * Provides timed send() and recv() calls.
 *
 * RWTimedPortal inherits from RWPortal to provide timed send() and recv()
 * calls. If send() and recv() calls on the underlying RWPortal might block
 * for too long, RWTimedPortal provides a mechanism for breaking out of
 * those calls after a predetermined amount of time.
 *
 * If the underlying RWPortal does not support timed send() and recv()
 * calls, an RWNetTimeoutNotImplementedError exception is thrown the first
 * time either send() or recv() is invoked.
 *
 * If the specified timeout is exceeded in a call to send() or recv(), an
 * RWNetOperationTimeoutError exception is thrown.
 *
 * \example
 * \code
 * #include <rw/network/RWInetAddr.h>
 * #include <rw/network/RWTimedPortal.h>
 * #include <rw/network/RWSocketPortal.h>
 *
 * int
 * main()
 * {
 *     RWWinSockInfo info;
 *
 *     try {
 *         // make an address for echo port on localhost
 *         RWInetAddr address(7, RWInetHost::me());
 *
 *         // make up some garbage data to send/recv
 *         RWCString outgoing("Hello World");
 *         RWCString incoming;
 *
 *         // construct a socket-based portal to echo port
 *         RWSocketPortal portal(address);
 *
 *         // create a timed portal on portal with a 100 ms timeout
 *         RWTimedPortal timed(portal, 100);
 *
 *         // do an untimed send using original portal
 *         portal.send(outgoing);
 *
 *         // do a timed recv using timed portal
 *         incoming = timed.recv();
 *     }
 *     catch(const RWxmsg& msg) {
 *         cerr << "Error: " << msg.why() << endl;
 *     }
 *     return 0;
 * }
 * \endcode
 * \endexample
 */
class RW_NETWORK_SYMBOLIC RWTimedPortal : public RWPortal
{
public:
    // create an invalid timed portal.  The body of the portal will be
    // associated with RWNoPortalImp object.  Attempts to recv or
    // send on the portal will throw an exception.
    /**
     * Constructs an invalid RWTimedPortal. Attempts to send or receive on
     * the portal throw an RWNetNoChannelError exception.
     */
    RWTimedPortal();

    /**
     * Constructs an RWTimedPortal from a portal object and a timeout. The
     * RWTimedPortal object uses the underlying implementation from
     * \a portal as the data sink for calls to send() and as the data source
     * for calls to recv(). Passes the \c timeout parameter on every \c send
     * and \c recv operation to that implementation.
     */
    RWTimedPortal(const RWPortal& portal, unsigned long timeout);
};

#endif  // __rw_network_RWTimedPortal_h__
