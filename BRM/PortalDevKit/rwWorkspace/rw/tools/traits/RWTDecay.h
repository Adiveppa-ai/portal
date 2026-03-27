#ifndef RW_TOOLS_TRAITS_RWTDECAY_H
#define RW_TOOLS_TRAITS_RWTDECAY_H

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
 * $Id: //spro/rel2016.1/rw/tools/traits/RWTDecay.h#1 $
 *
 ***************************************************************************/

#include <rw/defs.h>

#include <rw/tools/traits/RWTAddPointer.h>
#include <rw/tools/traits/RWTConditional.h>
#include <rw/tools/traits/RWTIsArray.h>
#include <rw/tools/traits/RWTIsFunction.h>
#include <rw/tools/traits/RWTRemoveCV.h>
#include <rw/tools/traits/RWTRemoveReference.h>
#include <rw/tools/traits/RWTRemoveExtent.h>

template <typename T>
struct RWTDecayImp {
    typedef typename RWTRemoveReference<T>::type U;

    typedef typename RWTConditional<
        RWTIsArray<U>::value, 
        typename RWTRemoveExtent<U>::type*,
        typename RWTConditional<
            RWTIsFunction<U>::value,
            typename RWTAddPointer<U>::type,
            typename RWTRemoveCV<U>::type
        >::type
    >::type type;
};

/**
 * \internal
 * \ingroup tools_type_traits_group
 *
 * \brief
 * Applies implicit conversions to the type T
 *
 * Specifies a typedef \c type to an lvalue reference version of \c T.
 * If \c T is an array of \c T1, sets \c type to \c T1*; if \c T is a
 * function type, sets \c type to be a pointer to that function type;
 * otherwise, \c type is \c T with all cv and reference qualifiers
 * removed.
 *
 * \example
 * \code
 * RWTDecay<int>::type;         // -> int
 * RWTDecay<int&>::type;        // -> int
 * RWTDecay<const int&>::type;  // -> int
 * RWTDecay<int&&>::type;       // -> int
 * RWTDecay<int*>::type;        // -> int*
 * RWTDecay<const int*>::type;  // -> const int*
 * RWTDecay<int const*>::type;  // -> const int*
 * RWTDecay<int* const>::type;  // -> int*
 * RWTDecay<int[5]>::type;      // -> int*
 * RWTDecay<int(int)>::type;    // -> int(*)(int)
 * RWTDecay<int(&)(int)>::type; // -> int(*)(int)
 * \endcode
 * \endexample
 */
template <typename T>
struct RWTDecay {
    /**
     * A decayed version of \c T, as if applying implicit lvalue-to-rvalue,
     * array-to-pointer, function-to-pointer conversions.
     */
#if defined(DOXYGEN)
    typedef unspecified_type type;
#else
    typedef typename RWTDecayImp<T>::type type;
#endif
};

#endif
