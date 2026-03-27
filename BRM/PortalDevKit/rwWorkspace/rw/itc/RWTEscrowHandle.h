#ifndef __rw_itc_RWTEscrowHandle_h__
#define __rw_itc_RWTEscrowHandle_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTEscrowHandle.h#1 $
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

#include <rw/itc/RWEscrowImpBase.h>
#include <rw/itc/fwd.h>
#include <rw/itc/pkgdefs.h>
#include <rw/pointer/RWHandleBase.h>
#include <rw/pointer/fwd.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWEscrowHandle RWTEscrowHandle
#endif

/**
 * \ingroup interthread_communication_package
 *
 * \brief
 * Base class for RWTIOUResult and RWTIOUEscrow. Not intended for direct
 * use.
 *
 * Do not use this class directly. This class is the base class for
 * RWTIOUResult and RWTIOUEscrow. It is intended for the internal use of
 * derived classes only.
 *
 * An RWTEscrowHandle instance may be used to initialize RWTIOUResult and
 * RWTIOUEscrow handles.
 */
template <class Redeemable>
class RWTEscrowHandle : public RWHandleBase
{
public:
    /**
     * A synonym for the value type of the IOU, or future, result.
     */
    typedef Redeemable   RedeemableType;

public:

    ~RWTEscrowHandle(void);

    /**
     * Creates an uninitialized handle.
     */
    RWTEscrowHandle(void);

    /**
     * Creates a handle that points to an RWTEscrowImp.
     */
    RWTEscrowHandle(RWEscrowImpBase* imp);

    /**
     * Copy constructor.
     */
    RWTEscrowHandle(const RWTEscrowHandle<Redeemable>& second);

    /**
     * Assigns this handle to point to the same RWTEscrowImp as \a second.
     */
    RWTEscrowHandle<Redeemable>&
    operator=(const RWTEscrowHandle<Redeemable>& second);

};

/*****************************************************************************/

template <class Redeemable>
inline
RWTEscrowHandle<Redeemable>::RWTEscrowHandle(void)
{
}

template <class Redeemable>
inline
RWTEscrowHandle<Redeemable>::~RWTEscrowHandle(void)
{
}

template <class Redeemable>
inline
RWTEscrowHandle<Redeemable>::RWTEscrowHandle(RWEscrowImpBase* imp)
    : RWHandleBase(imp)
{
}

template <class Redeemable>
inline
RWTEscrowHandle<Redeemable>::RWTEscrowHandle(const RWTEscrowHandle<Redeemable>& second)
    : RWHandleBase(second)
{
}

template <class Redeemable>
inline RWTEscrowHandle<Redeemable>&
RWTEscrowHandle<Redeemable>::operator=(const RWTEscrowHandle<Redeemable>& second)
{
    if (&second != this) {
        RWHandleBase::operator=(second);
    }
    return *this;
}

#endif // __rw_itc_RWTEscrowHandle_h__
