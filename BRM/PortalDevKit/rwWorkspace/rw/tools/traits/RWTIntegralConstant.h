#ifndef RW_TOOLS_TRAITS_RWTINTEGRALCONSTANT_H
#define RW_TOOLS_TRAITS_RWTINTEGRALCONSTANT_H

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
 * $Id: //spro/rel2016.1/rw/tools/traits/RWTIntegralConstant.h#1 $
 *
 ***************************************************************************/

#include <rw/defs.h>

/**
 * \internal
 * \ingroup tools_type_traits_group
 *
 * \brief
 * Encapsulates a constant of a given type.
 *
 * Defines a unique type that encapsulates an integral constant value of
 * the provided type \c T.
 *
 * \example
 * \code
 * enum E { e1, e2 };
 * RWTIntegralConstant<int, 1>::value; // -> 1
 * RWTIntegralConstant<E, e2>::value;  // -> e2
 * \endcode
 * \endexample
 */
template <typename T, T v>
struct RWTIntegralConstant {

    /**
     * An alias for the typename \c T.
     */
    typedef T value_type;

    /**
     * An alias for the typename of this type.
     */
    typedef RWTIntegralConstant<T, v> type;

    /**
     * The integral constant value encapsulated by self.
     */
    static const T value = v;

    /**
     * Conversion operator returns the encapsulated integral constant
     * value.
     */
    operator const value_type() const RW_NOEXCEPT
    {
        return value;
    }

    /**
     * Function call operator that returns the encapsulated integral
     * constant value.  Useful when a constant value is to be provided
     * as a function object.
     */
    const value_type operator()() const RW_NOEXCEPT
    {
        return value;
    }
};

#endif
