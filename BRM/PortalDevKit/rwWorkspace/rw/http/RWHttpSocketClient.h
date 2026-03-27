#ifndef __rw_http_RWHttpSocketClient_h__
#define __rw_http_RWHttpSocketClient_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/http/RWHttpSocketClient.h#1 $
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

#include <rw/http/RWHttpClient.h>
#include <rw/http/RWHttpSocketClientImp.h>
#include <rw/functor/fwd.h>
#include <rw/pointer/RWHandleBase.h>

/**
 * \ingroup http_package
 *
 * \brief
 * Handle class for parent RWHttpClient, providing implementation-specific
 * details for HTTP clients.
 *
 * RWHttpSocketClient is a derived handle class for RWHttpClient. It
 * provides implementation specific details for HTTP clients over normal
 * network sockets.
 */
class RW_HTTP_GLOBAL RWHttpSocketClient : public RWHttpClient
{
protected:
    RWHttpSocketClient(RWHttpSocketClientImp* imp);
    // Protected constructor from imp

public:
    /**
     * Default constructor.
     */
    RWHttpSocketClient(void);

    /**
     * Copy constructor.
     */
    RWHttpSocketClient(const RWHttpSocketClient& client);

    /**
     * Assignment operator.
     */
    RWHttpSocketClient&
    operator=(const RWHttpSocketClient& other);

    /**
     * Virtual destructor.
     */
    virtual
    ~RWHttpSocketClient();

    /**
     * Creates a new initialized RWHttpSocketClient.
     */
    static RWHttpSocketClient
    make();

    /**
     * Creates a new initialized RWHttpSocketClient. The functor \a f is
     * used by RWHttpClient::connect() to get a socket connected to the
     * provided address.
     */
    static RWHttpSocketClient
    make(const RWTFunctor<RWSocket(const RWSockAddrBase&, unsigned long)>& f);

protected:

    RWHttpSocketClientImp&
    body() const;
    // returns a reference to the body

};

inline
RWHttpSocketClient::RWHttpSocketClient()
{
}

inline
RWHttpSocketClient::RWHttpSocketClient(const RWHttpSocketClient& client)
    : RWHttpClient(client)
{
}

inline
RWHttpSocketClient::RWHttpSocketClient(RWHttpSocketClientImp* imp)
    : RWHttpClient(imp)
{
}

RW_SUPPRESS_OP_ASSIGN_SELF_CHECK_WARNING
inline RWHttpSocketClient&
RWHttpSocketClient::operator=(const RWHttpSocketClient& client)
{
    RWHandleBase::operator=(client);
    return *this;
}
RW_RESTORE_OP_ASSIGN_SELF_CHECK_WARNING

inline RWHttpSocketClientImp&
RWHttpSocketClient::body() const
{
    return (RWHttpSocketClientImp&)RWHandleBase::body();
}

#endif // __rw_http_RWHttpSocketClient_h__
