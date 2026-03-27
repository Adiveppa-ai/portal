#ifndef RW_TOOLS_TRAITS_RWTADDPOINTER_H
#define RW_TOOLS_TRAITS_RWTADDPOINTER_H

/***************************************************************************
 *
 * Copyright (c) 1989-2016 Rogue Wave Software, Inc.  All Rights Reserved.
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
 * $Id: //spro/rel2016.1/rw/tools/traits/RWTAddPointer.h#1 $
 *
 ***************************************************************************/

#include <rw/defs.h>

#include <rw/tools/traits/RWTRemoveReference.h>

/**
 * \internal
 * \ingroup tools_type_traits_group
 *
 * \brief
 * Adds a pointer to a type
 *
 * Specifies a typedef \c type which is a pointer to the type referenced
 * by \c T.
 *
 * \example
 * \code
 * RWTAddPointer<int>::type;                 // -> int*
 * RWTAddPointer<const int>::type;           // -> const int*
 * RWTAddPointer<volatile int>::type;        // -> volatile int*
 * RWTAddPointer<const volatile int>::type;  // -> const volatile int*
 * RWTAddPointer<int&>::type;                // -> int*
 * RWTAddPointer<int*>::type;                // -> int**
 * RWTAddPointer<int(int)>::type;            // -> int(*)(int)
 * \endcode
 * \endexample
 */
template <typename T>
struct RWTAddPointer {
    /**
     * A pointer to \c T or to the type referenced by \c T.
     */
#if defined(DOXYGEN)
    typedef unspecified_type type;
#else
    typedef typename RWTRemoveReference<T>::type* type;
#endif
};

#endif
