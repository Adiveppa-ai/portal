#ifndef __rw_itc_RWTGuardDecorator_h__
#define __rw_itc_RWTGuardDecorator_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/itc/RWTGuardDecorator.h#1 $
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
#include <rw/functor/RWTFunctor.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWGuardDecorator RWTGuardDecorator
#endif

#if defined(RW_GCC_VERSION) && (RW_GCC_VERSION >= 40400 && RW_GCC_VERSION < 40500)
#  define RW_RESTRICTED_INLINE __attribute__((noinline))
#else
#  define RW_RESTRICTED_INLINE inline
#endif

template <class Type>
class RWTGuardDecorator : virtual public RWTDecorator<Type>
{
public:

    RWTFunctor<bool()>  guard_;

    RWTGuardDecorator(void);

    RWTGuardDecorator(const Type& value);

    RWTGuardDecorator(const Type& value,
                      const RWTFunctor<bool()>& guard);

    RW_RESTRICTED_INLINE RWTGuardDecorator(const RWTGuardDecorator<Type>& second);

    ~RWTGuardDecorator(void);

    RW_RESTRICTED_INLINE RWTGuardDecorator<Type>&
    operator=(const RWTGuardDecorator& second);

};

/*****************************************************************************/

template <class Type>
inline
RWTGuardDecorator<Type>::RWTGuardDecorator(void)
{
}

template <class Type>
inline
RWTGuardDecorator<Type>::RWTGuardDecorator(const Type& value)
    : RWTDecorator<Type>(value)
{
}

template <class Type>
inline
RWTGuardDecorator<Type>::RWTGuardDecorator(const Type& value, const RWTFunctor<bool()>& guard)
    : RWTDecorator<Type>(value),
      guard_(guard)
{
}

template <class Type>
RW_RESTRICTED_INLINE
RWTGuardDecorator<Type>::RWTGuardDecorator(const RWTGuardDecorator<Type>& second)
    : RWTDecorator<Type>(second),
      guard_(second.guard_)
{
}

template <class Type>
inline
RWTGuardDecorator<Type>::~RWTGuardDecorator(void)
{
}

template <class Type>
RW_RESTRICTED_INLINE RWTGuardDecorator<Type>&
RWTGuardDecorator<Type>::operator=(const RWTGuardDecorator<Type>& second)
{
    RWTDecorator<Type>::operator=(second);
    guard_ = second.guard_;
    return *this;
}

#undef RW_RESTRICTED_INLINE

#endif // __rw_itc_RWTGuardDecorator_h__
