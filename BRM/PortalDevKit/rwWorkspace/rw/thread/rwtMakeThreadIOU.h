#ifndef __rw_thread_rwtMakeThreadIOU_h__
#define __rw_thread_rwtMakeThreadIOU_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/rwtMakeThreadIOU.h#1 $
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

#include <rw/thread/RWTThreadEscrowImp.h>
#include <rw/thread/pkgdefs.h>
#include <rw/itc/RWTEscrowHandle.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define rwMakeThreadIOU    rwtMakeThreadIOU

/**
 * \ingroup rwtMakeThreadIOU
 *
 * \deprecated
 * As of SourcePro 12.5, use RWTThreadEscrowImp<Redeemable>::make() instead.
 *
 * Creates an RWTEscrowHandle. A pointer to the redeemable type is passed in
 * order for the template function to ascertain the \c Redeemable template
 * argument type. This allows the function to create a threaded escrow
 * implementation of the proper type.
 */
template <class Redeemable>
RW_DEPRECATE_FUNC("Use RWTThreadEscrowImp<Redeemable>::make() instead")
inline RWTEscrowHandle<Redeemable>
rwtMakeThreadIOU(const Redeemable* r)
{
    RW_UNUSED(r);
    return RWTThreadEscrowImp<Redeemable>::make();
}
#endif

#endif // __rw_thread_rwtMakeThreadIOU_h__
