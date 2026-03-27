#ifndef __rw_itc_RWTGuardAndPriorityDecorator_h__
#define __rw_itc_RWTGuardAndPriorityDecorator_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTGuardAndPriorityDecorator.h#1 $
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

#include <rw/itc/RWTGuardDecorator.h>
#include <rw/itc/RWTPriorityDecorator.h>
#include <rw/itc/pkgdefs.h>
#include <rw/functor/RWTFunctor.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWGuardAndPriorityDecorator RWTGuardAndPriorityDecorator
#endif

template <class Type>
class RWTGuardAndPriorityDecorator :
    public RWTGuardDecorator<Type>, public RWTPriorityDecorator<Type>
{

public:

    RWTGuardAndPriorityDecorator(void);

    RWTGuardAndPriorityDecorator(const Type& value);

    RWTGuardAndPriorityDecorator(const Type& value,
                                 const RWTFunctor<bool()>& guard);

    RWTGuardAndPriorityDecorator(const Type& value,
                                 long priority);

    RWTGuardAndPriorityDecorator(const Type& value,
                                 const RWTFunctor<bool()>& guard,
                                 long priority);

    RWTGuardAndPriorityDecorator(const RWTGuardAndPriorityDecorator<Type>& second);

    ~RWTGuardAndPriorityDecorator(void);

    RWTGuardAndPriorityDecorator<Type>&
    operator=(const RWTGuardAndPriorityDecorator<Type>& second);

};

/*****************************************************************************/

template <class Type>
inline
RWTGuardAndPriorityDecorator<Type>::RWTGuardAndPriorityDecorator(void)
{
}

template <class Type>
inline
RWTGuardAndPriorityDecorator<Type>::RWTGuardAndPriorityDecorator(const Type& value)
    : RWTDecorator<Type>(value)
{
}

template <class Type>
inline
RWTGuardAndPriorityDecorator<Type>::RWTGuardAndPriorityDecorator(const Type& value,
        const RWTFunctor<bool()>& guard)
    : RWTDecorator<Type>(value),
      RWTGuardDecorator<Type>(value, guard)
{
}

template <class Type>
inline
RWTGuardAndPriorityDecorator<Type>::RWTGuardAndPriorityDecorator(const Type& value,
        long priority)
    : RWTDecorator<Type>(value),
      RWTPriorityDecorator<Type>(value, priority)
{
}

template <class Type>
inline
RWTGuardAndPriorityDecorator<Type>::RWTGuardAndPriorityDecorator(const Type& value,
        const RWTFunctor<bool()>& guard,
        long priority)
    : RWTDecorator<Type>(value),
      RWTGuardDecorator<Type>(value, guard),
      RWTPriorityDecorator<Type>(value, priority)
{
}

template <class Type>
inline
RWTGuardAndPriorityDecorator<Type>::RWTGuardAndPriorityDecorator(const RWTGuardAndPriorityDecorator<Type>& second)
    : RWTDecorator<Type>(second),
      RWTGuardDecorator<Type>(second),
      RWTPriorityDecorator<Type>(second)
{
}

template <class Type>
inline
RWTGuardAndPriorityDecorator<Type>::~RWTGuardAndPriorityDecorator(void)
{
}

template <class Type>
inline RWTGuardAndPriorityDecorator<Type>&
RWTGuardAndPriorityDecorator<Type>::operator=(const RWTGuardAndPriorityDecorator<Type>& second)
{
    RWTDecorator<Type>::operator=(second);
    RWTGuardDecorator<Type>::operator=(second);
    RWTPriorityDecorator<Type>::operator=(second);
    return *this;
}

#endif // __rw_itc_RWTGuardAndPriorityDecorator_h__
