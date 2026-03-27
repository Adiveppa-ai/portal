#ifndef RW_TOOLS_TRAITS_RWTREMOVEEXTENT_H
#define RW_TOOLS_TRAITS_RWTREMOVEEXTENT_H

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
 * $Id: //spro/rel2016.1/rw/tools/traits/RWTRemoveExtent.h#1 $
 *
 ***************************************************************************/

#include <rw/defs.h>

template <typename T>
struct RWTRemoveExtentImp {
    typedef T type;
};

template <typename T>
struct RWTRemoveExtentImp<T[]> {
    typedef T type;
};

template <typename T, size_t N>
struct RWTRemoveExtentImp<T[N]> {
    typedef T type;
};

/**
 * \internal
 * \ingroup tools_type_traits_group
 *
 * \brief
 * Removes one array extent from a type
 *
 * Specifies a typedef \c type to \c T with one extent removed. If \c T
 * is a "<tt>T1[]</tt>", \c type is a typedef to \c T1; otherwise \c type
 * is a typedef to \c T.
 *
 * \example
 * \code
 * RWTRemoveExtent<int>::type;              // -> int
 * RWTRemoveExtent<int&>::type;             // -> int&
 * RWTRemoveExtent<int&&>::type;            // -> int&&
 * RWTRemoveExtent<int*>::type;             // -> int*
 * RWTRemoveExtent<int(&)[]>::type;         // -> int&
 * RWTRemoveExtent<int(&&)[]>::type;        // -> int&&
 * RWTRemoveExtent<int(*[])(void)>::type;   // -> int(*)(void)
 * RWTRemoveExtent<int(*[2])(void)>::type;  // -> int(*)(void)
 * \endcode
 * \endexample
 */
template <typename T>
struct RWTRemoveExtent {
    /**
     * Specifies a typedef to \c T1 if \c T is "an array of type \c T1";
     * otherwise \c T.
     */
#if DOXYGEN
    typedef unspecified_type type;
#else
    typedef typename RWTRemoveExtentImp<T>::type type;
#endif
};

#endif
