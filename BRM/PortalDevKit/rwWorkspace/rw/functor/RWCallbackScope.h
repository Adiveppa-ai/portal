#ifndef __rw_functor_RWCallbackScope_h__
#define __rw_functor_RWCallbackScope_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/RWCallbackScope.h#1 $
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


/***************************************************************************
 *
 * Name:
 *   RWCallbackScope
 * Synopsis:
 *   The enumeration used to identify the lifetime of a functor within the list.
 *
 * Description:
 *   Elements added to the list with the value RW_CALL_ONCE will be removed
 *   from the list after their first invocation, elements added to the list
 *   with the value RW_CALL_REPEATEDLY will remain in the list until explicitly
 *   removed.
 *
 ****************************************************************************/

/**
 * \ingroup functor_module
 *
 * \headerfileloc{#include <rw/functor/RWCallbackScope.h>}
 *
 * Used when adding a callback functor to a callback list, to define how
 * many times the functor can be invoked before being automatically removed
 * from the list.
 */
enum RWCallbackScope {

    /**
     * Elements added to the list with this value will be removed from the
     * list after their first invocation.
     */
    RW_CALL_ONCE,

    /**
     * Elements added to the list with this value will remain in the list
     * until explicitly removed.
     */
    RW_CALL_REPEATEDLY
};

#endif // __rw_functor_RWCallbackScope_h__
