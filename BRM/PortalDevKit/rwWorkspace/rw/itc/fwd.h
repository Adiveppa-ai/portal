#ifndef __rw_itc_fwd_h__
#define __rw_itc_fwd_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/fwd.h#1 $
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

#include <rw/itc/pkgdefs.h>

class RW_ITC_GLOBAL RWTHRClosedException;
class RW_ITC_GLOBAL RWTHREscrowAlreadyClosed;
class RW_ITC_GLOBAL RWEscrowImpBase;
class RW_ITC_GLOBAL RWPCBufferBase;
template <class Type> class RWTDecorator;
template <class Redeemable> class RWTEscrowHandle;
template <class Redeemable> class RWTEscrowImp;
template <class Type> class RWTGuardAndPriorityDecorator;
template <class Type> class RWTGuardDecorator;
template <class Redeemable> class RWTIOUEscrow;
template <class Redeemable> class RWTIOUResult;
template <class Redeemable> class RWTIOUTrap;
template <class Redeemable> class RWTIOUTrapImp;

template <class Type> class RWTPCPtrBufferBase;
template <class Type> class RWTPCPtrQueue;
template <class Type> class RWTPCPtrStack;
template <class Type> class RWTPCValBufferBase;
template <class Type, class Decorator> class RWTPCValBufferBaseDecorated;
template <class Type, class GuardDecorator> class RWTPCValBufferBaseGuarded;
template <class Type, class GuardAndPriorityDecorator> class RWTPCValBufferBaseGuardedPrioritized;
template <class Type, class PriorityDecorator> class RWTPCValBufferBasePrioritized;
template <class Type> class RWTPCValQueue;
template <class Type> class RWTPCValQueueGuarded;
template <class Type> class RWTPCValQueueGuardedPrioritized;
template <class Type> class RWTPCValQueuePrioritized;
template <class Type> class RWTPCValStack;
template <class Type> class RWTPCValStackGuarded;
template <class Type> class RWTPCValStackGuardedPrioritized;
template <class Type> class RWTPCValStackPrioritized;
template <class Type> class RWTPriorityDecorator;

#endif // __rw_itc_fwd_h__
