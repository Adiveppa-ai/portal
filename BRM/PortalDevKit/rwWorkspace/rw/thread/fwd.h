#ifndef __rw_thread_fwd_h__
#define __rw_thread_fwd_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thread/fwd.h#1 $
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

#include <rw/thread/pkgdefs.h>

class RW_THREAD_GLOBAL RWCancellation;
class RW_THREAD_GLOBAL RWCancellationImp;
class RW_THREAD_SYMBOLIC RWGuardedRunnable;
class RW_THREAD_SYMBOLIC RWGuardedRunnableQueue;
class RW_THREAD_GLOBAL RWProductInfo;
class RW_THREAD_GLOBAL RWRunnable;
class RW_THREAD_GLOBAL RWRunnableFunction;
class RW_THREAD_GLOBAL RWRunnableFunctionImp;
class RW_THREAD_GLOBAL RWRunnableFunctionSelf;
class RW_THREAD_GLOBAL RWRunnableHandle;
class RW_THREAD_GLOBAL RWRunnableImp;
class RW_THREAD_GLOBAL RWRunnableSelf;
class RW_THREAD_GLOBAL RWRunnableServer;
class RW_THREAD_GLOBAL RWRunnableServerImp;
class RW_THREAD_GLOBAL RWRunnableTrap;
class RW_THREAD_GLOBAL RWRunnableTrapImp;
class RW_THREAD_GLOBAL RWServerPool;
class RW_THREAD_GLOBAL RWServerPoolImp;
class RW_THREAD_GLOBAL RWThread;
class RW_THREAD_GLOBAL RWThreadAttribute;
class RW_THREAD_GLOBAL RWThreadAttributeImp;
class RW_THREAD_GLOBAL RWThreadFunction;
class RW_THREAD_GLOBAL RWThreadFunctionImp;
class RW_THREAD_GLOBAL RWThreadFunctionSelf;
class RW_THREAD_GLOBAL RWThreadImp;
class RW_THREAD_GLOBAL RWThreadManager;
class RW_THREAD_GLOBAL RWThreadManagerImp;
class RW_THREAD_GLOBAL RWThreadPool;
class RW_THREAD_GLOBAL RWThreadPoolImp;
class RW_THREAD_GLOBAL RWThreadSelf;
class RW_THREAD_GLOBAL RWThreadsProductInfo;

template <class Return> class RWTRunnableIOUFunction;
template <class Return> class RWTRunnableIOUFunctionImp;
template <class Redeemable> class RWTThreadEscrowImp;
template <class Return> class RWTThreadIOUFunction;
template <class Return> class RWTThreadIOUFunctionImp;
template <class Type> class RWTThreadLocal;

#endif // __rw_thread_fwd_h__
