#if !defined(RW_TOOLPRO_LEGACY_H)
#define RW_TOOLRPO_LEGACY_H
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/thr/legacy.h#1 $
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

/*
 * This header provides backward compatibility with previous
 * versions of the SourcePro Core - Threads Module.  This header
 * forwards into the umbrella headers for the packages that
 * previously made up the Threads.h++ product.
 *
 * USE OF THIS HEADER IS DEPRECATED
 *
 * It is recommended that users that have a dependency on this
 * header (directly or indirectly through another legacy header)
 * should migrate to the current header structure for the products
 * they are using.
 */

#include <rw/thread/thread.h>
#include <rw/itc/itc.h>
#include <rw/functor/map/map.h>
#include <rw/functor/list/list.h>
#include <rw/functor/functor.h>
#include <rw/pointer/pointer.h>
#include <rw/sync/sync.h>
#include <rw/threxcept/threxcept.h>
#include <rw/trace/trace.h>

#if defined(RW_DISABLE_DEPRECATED)
#  error Use of this header has been deprecated. \
Please refer to the latest documentation \
for the appropriate include.
#endif

#endif // RW_TOOLPRO_LEGACY_H
