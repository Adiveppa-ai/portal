#ifndef __rw_functor_list_RWTCallbackListBase_h__
#define __rw_functor_list_RWTCallbackListBase_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/list/RWTCallbackListBase.h#1 $
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

#include <rw/functor/list/pkgdefs.h>

#if !defined(RW_DISABLE_DEPRECATED)
#  define RWCallbackListBase RWTCallbackListBase
#  define RW_THR_CALL_ONCE RW_CALL_ONCE
#  define RW_THR_CALL_REPEATEDLY RW_CALL_REPEATEDLY

RW_SUPPRESS_DEPRECATED_WARNINGS

#include <rw/functor/RWCallbackScope.h>

class RW_FUNCTOR_LIST_SYMBOLIC RWCallbackElemBase
{

public:

    // Copy constructor
    RWCallbackElemBase(const RWCallbackElemBase& second);

    // Destructor
    ~RWCallbackElemBase(void);

    // Assignment operator
    RWCallbackElemBase&
    operator=(const RWCallbackElemBase& second);

    // Required for stdlib-based list collections
    bool
    operator==(const RWCallbackElemBase& second) const;

    bool
    operator<(const RWCallbackElemBase& second) const;

    // Returns the scope of this element.
    RWCallbackScope
    scope(void) const;

    // Sets the scope of this element.
    void
    scope(RWCallbackScope newScope);

protected:

    // Make constructors protected since this is a base class
    RWCallbackElemBase(void);

    RWCallbackElemBase(RWCallbackScope scope);

    RWCallbackScope      scope_;

};


template <class Mutex>
class RWTCallbackListBase
{

public:

    // The type of mutex protecting the lists data.
    typedef  Mutex MutexType;

    // Destructor
    ~RWTCallbackListBase(void);

protected:
    // Construct the callback list object, passing in the mutex
    // that is to be used to protect the list state.
    // Make protected since this is a base class.
    RWTCallbackListBase(Mutex& mutex);

    // Get a reference to the mutex associated with the callback list
    Mutex&
    mutex(void) const;

private:

    // Copy constructor
    RWTCallbackListBase(const RWTCallbackListBase<Mutex>& second);

    // Assignment operator
    RWTCallbackListBase<Mutex>&
    operator=(const RWTCallbackListBase<Mutex>& second);


protected:

    // Callback lists are generally owned by other objects, so
    // it uses the owner's mutex instead of creating a local one.
    Mutex& mutex_;


};


inline bool
RWCallbackElemBase::operator==(const RWCallbackElemBase& second) const
{
    return scope_ == second.scope_;
}

inline bool
RWCallbackElemBase::operator<(const RWCallbackElemBase& second) const
{
    return scope_ < second.scope_;
}

inline RWCallbackScope
RWCallbackElemBase::scope(void) const
{
    return scope_;
}

inline void
RWCallbackElemBase::scope(RWCallbackScope newScope)
{
    scope_ = newScope;
}

template <class Mutex>
inline Mutex&
RWTCallbackListBase<Mutex>::mutex(void) const
{
    return mutex_;
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/functor/list/RWTCallbackListBase.cc>
#endif

RW_RESTORE_DEPRECATED_WARNINGS
#endif // !RW_DISABLE_DEPRECATED

#endif // __rw_functor_list_RWTCallbackListBase_h__
