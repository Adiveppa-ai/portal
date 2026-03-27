#ifndef __rw_network_fwd_h__
#define __rw_network_fwd_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/fwd.h#1 $
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

#include <rw/network/pkgdefs.h>

class RWInet6Addr;
class RWInet6AddrFactory;
class RWInet6Host;
class RWInet6Type;
class RWInetAddr;
class RWInetAddrFactory;
class RWInetHost;
class RWInetPort;
class RWInetType;
class RWNetBuf;
class RWPortal;
class RWSockAddr;
class RWSockAddrBase;
class RWSockAddrFactory;
class RWSockAddrFactoryBase;
class RWSocket;
class RWSocketListener;
class RWSocketPortal;
class RWSocketPortalBase;
class RWSockType;
class RWTimedPortal;
class RWWinSockInfo;

template <class charT, class traits = std::char_traits<charT> > class RWTPortalIStream;
template <class charT, class traits = std::char_traits<charT> > class RWTPortalOStream;
template <class charT, class traits = std::char_traits<charT> > class RWTPortalStream;
template <class charT, class traits = std::char_traits<charT> > class RWTPortalStreambuf;
template <class Socket> class RWTSocketAttribute;

typedef RWTPortalIStream<char, std::char_traits<char> > RWPortalIStream;
typedef RWTPortalOStream<char, std::char_traits<char> > RWPortalOStream;
typedef RWTPortalStream<char, std::char_traits<char> > RWPortalStream;
typedef RWTPortalStreambuf<char, std::char_traits<char> > RWPortalStreambuf;
typedef RWTSocketAttribute<RWSocket> RWSocketAttribute;

// Exceptions

class RWInetHostNotFoundError;
class RWInetServiceNotFoundError;
class RWNetAlreadyRegisteredError;
class RWNetCantCreatePortalError;
class RWNetCantRecvError;
class RWNetCantSendError;
class RWNetInvalidSocketError;
class RWNetNoChannelError;
class RWNetNoFactoryRegisteredError;
class RWNetNoNameFactoryRegisteredError;
class RWNetNoNumberFactoryRegisteredError;
class RWNetNoSuchBlockingHookError;
class RWNetOperationTimeoutError;
class RWNetSelectError;
class RWNetTimeoutNotImplementedError;
class RWNetWinsockInitError;
class RWSockBadAddressFormatError;
class RWSocketError;
class RWSockTypeChangeError;
class RWSockWrongAddressTypeError;

#endif // __rw_network_fwd_h__
