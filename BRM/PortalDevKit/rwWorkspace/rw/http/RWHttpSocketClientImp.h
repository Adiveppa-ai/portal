#ifndef __rw_http_RWHttpSocketClientImp_h__
#define __rw_http_RWHttpSocketClientImp_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpSocketClientImp.h#1 $
 *
 * Copyright (c) 1996-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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

#include <rw/http/RWHttpClientImp.h>
#include <rw/network/RWSocketPortal.h>
#include <rw/network/fwd.h>
#include <rw/itc/RWTPCValQueue.h>
#include <rw/functor/fwd.h>



#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4251)
#endif

class RW_HTTP_GLOBAL RWHttpSocketClientImp : public RWHttpClientImp
{
    friend class RWHttpSocketClient;

protected:

    RWHttpSocketClientImp();
    // Default constructor

    RWHttpSocketClientImp(const RWTFunctor<RWSocket(const RWSockAddrBase&, unsigned long)>& f);
    // Constructor

    virtual RWPortal
    portal() const;
    // returns a handle to the current portal.

    virtual void
    connect_(const RWSockAddrBase& address, unsigned long maxwait);
    // connects to host on port, waits maxwait milliseconds for connect
    // to complete

    virtual void
    disconnect_();
    // disconnects from the current host/port

    virtual bool
    isConnected_() const;
    // Returns true if last known state was connected, false otherwise

private:

    RWSocket       socket_;
    RWPortal       portal_;

    RWTFunctor<RWSocket(const RWSockAddrBase&, unsigned long)> functor_;
};

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // __rw_http_RWHttpSocketClientImp_h__
