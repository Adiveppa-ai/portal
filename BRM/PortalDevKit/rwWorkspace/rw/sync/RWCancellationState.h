#ifndef __rw_sync_RWCancellationState_h__
#define __rw_sync_RWCancellationState_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/sync/RWCancellationState.h#1 $
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

#include <rw/sync/pkgdefs.h>

/**
 * \relates RWSynchObject
 *
 * This function pointer type is used with the Synchronization objects to
 * set the cancellation policy.
 *
 * #RW_CANCELLATION_DISABLED is defined in the Synchronization package to be 0.
 * #RW_CANCELLATION_ENABLED is defined in the Threading package as
 * \ref rwServiceCancellation() "&rwServiceCancellation". Either macro may
 * be passed where an #RWCancellationState is expected. For example, see
 * RWSynchObject::setCancellation(RWCancellationState).
 *
 * For information on changes in RWCancellationState and compatibility with
 * previous versions of Threads.h++, please see the <em>Threads Module
 * User's Guide</em>.
 *
 * \sa
 * RWSynchObject
 */
typedef void(*RWCancellationState)();

/**
 * \relates RWSynchObject
 *
 * Flag to specify cancellation state.
 */
#define RW_CANCELLATION_DISABLED 0

// Forward reference for throw specs...
class RW_SYNC_SYMBOLIC RWCancellation;


/*****************************************************************************/

#endif  // __rw_sync_RWCancellationState_h__
