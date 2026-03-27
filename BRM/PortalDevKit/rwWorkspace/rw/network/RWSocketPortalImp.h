#ifndef __rw_network_RWSocketPortalImp_h__
#define __rw_network_RWSocketPortalImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/network/RWSocketPortalImp.h#1 $
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

#include <rw/network/RWPortalImp.h>
#include <rw/network/RWSocket.h>
#include <rw/network/RWSocketPortalBase.h>
#include <rw/network/fwd.h>
#include <rw/network/pkgdefs.h>

/*
 * RWSocketPortalImp: implementation of socket portal
 *
 * The actual work is done by the RWSocket class
 */

/*
 * The whoShouldClose_ member function is left as a simple public data
 * member since the use of this class is private to this file anyway
 */

class RWSocketPortalImp
    : public RWSocket,
      public RWPortalImp
{
public:
    RWSocketPortalImp();

    ~RWSocketPortalImp();

    virtual RWNetBuf
    recv();

    virtual RWNetBuf
    recv(unsigned long timeout);

    virtual int
    recv(char* buf, int len, RWNetBuf::State* state);

    virtual int
    recv(char* buf, int len, RWNetBuf::State* state, unsigned long timeout);

    virtual int
    send(const char* buf, int len);

    virtual int
    send(const char* buf, int len, unsigned long timeout);

    RWSocketPortalBase::WhoShouldClose whoShouldClose_;

protected:
    enum SocketState { RW_NET_ERROR = -1,
                       RW_NET_TIMEOUT = 0,
                       RW_NET_OK = 1
                     };

    SocketState
    checkSocketAttribute(const RWSocketAttribute& attr, unsigned long timeout);

private:
    // Copy constructor and assignment declared (only) private so they can't
    // be used accidentally
    RWSocketPortalImp(const RWSocketPortalImp&);
    RWSocketPortalImp& operator=(const RWSocketPortalImp&);
};

inline
RWSocketPortalImp::RWSocketPortalImp()
    : whoShouldClose_(RWSocketPortalBase::Portal)
{}

#endif  // __rw_network_RWSocketPortalImp_h__ 
