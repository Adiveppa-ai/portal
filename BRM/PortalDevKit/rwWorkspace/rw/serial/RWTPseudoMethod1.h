#ifndef rw_serial_RWTPseudoMethod1_h_
#define rw_serial_RWTPseudoMethod1_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWTPseudoMethod1.h#1 $
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
 ********************************************************************/

#include <rw/serial/RWTPseudoMethodRegistry.h>
#include <rw/serial/pkgdefs.h>
#include <rw/functor/RWTFunctor.h>


//--This template represents a pseudovirtual method that takes one
//--additional argument, and returns no values.
template <class Arg1, class Arg2>
class RW_SERIAL_SUN_SYMBOLIC RWTPseudoMethod1
    : public RWTPseudoMethodRegistry<RWTFunctor<void(Arg1, Arg2)> >
{

public:

    //-- Construct a pseudovirtual method.  The optional defaultMethod
    //-- represents the generic behavior of the method, when there is no
    //-- specialized behavior defined for the argument type.

    typedef typename
    RWTPseudoMethodRegistry<RWTFunctor<void(Arg1, Arg2)> >::registered_method_type
    registered_method_type;

    RWTPseudoMethod1(registered_method_type defaultMethod = NULL);


    //-- Call the method on arg1 (a base class pointer), invoking
    //-- specialized behavior according to the dynamic (derived) type of
    //-- arg1.
    virtual void
    operator()(Arg1, Arg2);
};

template <class Arg1, class Arg2>
RWTPseudoMethod1<Arg1, Arg2>::RWTPseudoMethod1(registered_method_type m)
    : RWTPseudoMethodRegistry<RWTFunctor<void(Arg1, Arg2)> >(m) {}

template <class Arg1, class Arg2>
void
RWTPseudoMethod1<Arg1, Arg2>::operator()(Arg1 arg1, Arg2 arg2)
{
    typename
    RWTPseudoMethodRegistry<RWTFunctor<void(Arg1, Arg2)> >::registered_method_type
    method = this->getMethod(typeid(*arg1));

    // call the method
    method(arg1, arg2);
}

#endif // rw_serial_RWTPseudoMethod1_h_
