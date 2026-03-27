#ifndef __rw_itc_RWTPriorityDecorator_h__
#define __rw_itc_RWTPriorityDecorator_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTPriorityDecorator.h#1 $
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

#include <rw/itc/RWTDecorator.h>
#include <rw/itc/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWPriorityDecorator RWTPriorityDecorator
#endif

#if defined(RW_GCC_VERSION) && (RW_GCC_VERSION >= 40400 && RW_GCC_VERSION < 40500)
#  define RW_RESTRICTED_INLINE __attribute__((noinline))
#else
#  define RW_RESTRICTED_INLINE inline
#endif

template <class Type>
class RWTPriorityDecorator : virtual public RWTDecorator<Type>
{
public:

    long priority_;

    RWTPriorityDecorator(void);

    RWTPriorityDecorator(const Type& value);

    RWTPriorityDecorator(const Type& value,
                         long priority);

    RW_RESTRICTED_INLINE RWTPriorityDecorator(const RWTPriorityDecorator<Type>& second);

    ~RWTPriorityDecorator(void);

    RW_RESTRICTED_INLINE RWTPriorityDecorator<Type>&
    operator=(const RWTPriorityDecorator<Type>& second);

};

/*****************************************************************************/

template <class Type>
inline
RWTPriorityDecorator<Type>::RWTPriorityDecorator(void)
    : priority_(0)
{
}

template <class Type>
inline
RWTPriorityDecorator<Type>::RWTPriorityDecorator(const Type& value)
    : RWTDecorator<Type>(value),
      priority_(0)
{
}

template <class Type>
inline
RWTPriorityDecorator<Type>::RWTPriorityDecorator(const Type& value, long priority)
    : RWTDecorator<Type>(value),
      priority_(priority)
{
}

template <class Type>
RW_RESTRICTED_INLINE
RWTPriorityDecorator<Type>::RWTPriorityDecorator(const RWTPriorityDecorator<Type>& second)
    : RWTDecorator<Type>(second),
      priority_(second.priority_)
{
}

template <class Type>
inline
RWTPriorityDecorator<Type>::~RWTPriorityDecorator(void)
{
}

template <class Type>
RW_RESTRICTED_INLINE RWTPriorityDecorator<Type>&
RWTPriorityDecorator<Type>::operator=(const RWTPriorityDecorator<Type>& second)
{
    RWTDecorator<Type>::operator=(second);
    priority_ = second.priority_;
    return *this;
}

#undef RW_RESTRICTED_INLINE

#endif // __rw_itc_RWTPriorityDecorator_h__
