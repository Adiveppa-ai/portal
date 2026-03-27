#ifndef __rw_functor_list_RWTMaskedCallbackListBase_h__
#define __rw_functor_list_RWTMaskedCallbackListBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWTMaskedCallbackListBase.h#1 $
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

#include <rw/functor/list/RWTCallbackListBase.h>
#include <rw/functor/list/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWTMaskedCallbackListBase RWTMaskedCallbackListBase

RW_SUPPRESS_DEPRECATED_WARNINGS

class RW_FUNCTOR_LIST_SYMBOLIC RWMaskedCallbackElemBase : public RWCallbackElemBase
{

public:

    // Copy constructor
    RWMaskedCallbackElemBase(const RWMaskedCallbackElemBase& second);

    // Destructor
    ~RWMaskedCallbackElemBase(void);

    // Assignment operator
    RWMaskedCallbackElemBase&
    operator=(const RWMaskedCallbackElemBase& second);

    // Returns the mask stored in this element.
    unsigned long
    mask(void) const;

    // Sets the mask stored in this element.
    void
    mask(unsigned long newMask);

    // Required for storage in RWTValSlist.
    bool
    operator==(const RWMaskedCallbackElemBase& second);

protected:
    // Make constructors protected since this is a base class
    RWMaskedCallbackElemBase(void);

    RWMaskedCallbackElemBase(unsigned long mask, RWCallbackScope scope);

protected:

    unsigned long        mask_;

};


template <class Mutex>
class RWTMaskedCallbackListBase : public RWTCallbackListBase<Mutex>
{

    typedef RWTCallbackListBase<Mutex> BaseType;

public:

    // The type of mutex protecting the lists data.
    typedef  Mutex MutexType;

    // Destructor
    ~RWTMaskedCallbackListBase(void);


protected:

    // Constructs a callback list, using the given mutex
    // to protect the list's state.
    // Make protected since this is a base class.
    RWTMaskedCallbackListBase(Mutex& mutex);

    // Assignment operator
    RWTMaskedCallbackListBase<Mutex>&
    operator=(const RWTMaskedCallbackListBase<Mutex>& second);

    // Returns the mask stored in this element.
    unsigned long
    mask(void) const;

    // Sets the mask stored in this element.
    void
    mask(unsigned long newMask);

private:

    // Copy constructor
    RWTMaskedCallbackListBase(const RWTMaskedCallbackListBase<Mutex>& second);

protected:

    // An OR'd value of the masks of all the callbacks in list_.
    unsigned long mask_;

};



inline unsigned long
RWMaskedCallbackElemBase::mask(void) const
{
    return mask_;
}

inline void
RWMaskedCallbackElemBase::mask(unsigned long newMask)
{
    mask_ = newMask;
}

inline bool
RWMaskedCallbackElemBase::operator==(const RWMaskedCallbackElemBase& second)
{
    return mask_ == second.mask_ && RWCallbackElemBase::operator==(second);
}

template <class Mutex>
inline unsigned long
RWTMaskedCallbackListBase<Mutex>::mask(void) const
{
    return mask_;
}

template <class Mutex>
inline void
RWTMaskedCallbackListBase<Mutex>::mask(unsigned long newMask)
{
    mask_ = newMask;
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/list/RWTMaskedCallbackListBase.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_list_RWTMaskedCallbackListBase_h__
