#ifndef __rw_functor_fwd_h__
#define __rw_functor_fwd_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/fwd.h#1 $
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

#include <rw/functor/pkgdefs.h>

template <typename T> class RWTFunctor;

#if !defined(RW_DISABLE_DEPRECATED)

class RW_FUNCTOR_SYMBOLIC RWFunctor0;
class RW_FUNCTOR_SYMBOLIC RWFunctor0Imp;

template <class DR> class RWTFunctor0GImp;
template <class DR, class A1> class RWTFunctor0GA1Imp;
template <class DR, class A1, class A2> class RWTFunctor0GA2Imp;
template <class DR, class A1, class A2, class A3> class RWTFunctor0GA3Imp;

template <class Callee, class DR> class RWTFunctor0MImp;
template <class Callee, class DR, class A1> class RWTFunctor0MA1Imp;
template <class Callee, class DR, class A1, class A2> class RWTFunctor0MA2Imp;
template <class Callee, class DR, class A1, class A2, class A3> class RWTFunctor0MA3Imp;



template <class S1> class RWTFunctor1;
template <class S1> class RWTFunctor1Imp;

template <class S1, class DR, class D1> class RWTFunctor1GImp;
template <class S1, class DR, class D1, class A1> class RWTFunctor1GA1Imp;
template <class S1, class DR, class D1, class A1, class A2> class RWTFunctor1GA2Imp;

template <class S1, class Callee, class DR, class D1> class RWTFunctor1MImp;
template <class S1, class Callee, class DR, class D1, class A1> class RWTFunctor1MA1Imp;
template <class S1, class Callee, class DR, class D1, class A1, class A2> class RWTFunctor1MA2Imp;


template <class S1, class S2> class RWTFunctor2;
template <class S1, class S2> class RWTFunctor2Imp;

template <class S1, class S2, class DR, class D1, class D2> class RWTFunctor2GImp;
template <class S1, class S2, class DR, class D1, class D2, class A1> class RWTFunctor2GA1Imp;
template <class S1, class S2, class DR, class D1, class D2, class A1, class A2> class RWTFunctor2GA2Imp;

template <class S1, class S2, class Callee, class DR, class D1, class D2> class RWTFunctor2MImp;
template <class S1, class S2, class Callee, class DR, class D1, class D2, class A1> class RWTFunctor2MA1Imp;
template <class S1, class S2, class Callee, class DR, class D1, class D2, class A1, class A2> class RWTFunctor2MA2Imp;


template <class SR> class RWTFunctorR0;
template <class SR> class RWTFunctorR0Imp;

template <class SR, class DR> class RWTFunctorR0GImp;
template <class SR, class DR, class A1> class RWTFunctorR0GA1Imp;
template <class SR, class DR, class A1, class A2> class RWTFunctorR0GA2Imp;
template <class SR, class DR, class A1, class A2, class A3> class RWTFunctorR0GA3Imp;

template <class SR, class Callee, class DR> class RWTFunctorR0MImp;
template <class SR, class Callee, class DR, class A1> class RWTFunctorR0MA1Imp;
template <class SR, class Callee, class DR, class A1, class A2> class RWTFunctorR0MA2Imp;
template <class SR, class Callee, class DR, class A1, class A2, class A3> class RWTFunctorR0MA3Imp;


template <class SR, class S1> class RWTFunctorR1;
template <class SR, class S1> class RWTFunctorR1Imp;

template <class SR, class S1, class DR, class D1> class RWTFunctorR1GImp;
template <class SR, class S1, class DR, class D1, class A1> class RWTFunctorR1GA1Imp;
template <class SR, class S1, class DR, class D1, class A1, class A2> class RWTFunctorR1GA2Imp;

template <class SR, class S1, class Callee, class DR, class D1> class RWTFunctorR1MImp;
template <class SR, class S1, class Callee, class DR, class D1, class A1> class RWTFunctorR1MA1Imp;
template <class SR, class S1, class Callee, class DR, class D1, class A1, class A2> class RWTFunctorR1MA2Imp;


template <class SR, class S1, class S2> class RWTFunctorR2;
template <class SR, class S1, class S2> class RWTFunctorR2Imp;

template <class SR, class S1, class S2, class DR, class D1, class D2> class RWTFunctorR2GImp;
template <class SR, class S1, class S2, class DR, class D1, class D2, class A1> class RWTFunctorR2GA1Imp;
template <class SR, class S1, class S2, class DR, class D1, class D2, class A1, class A2> class RWTFunctorR2GA2Imp;

template <class SR, class S1, class S2, class Callee, class DR, class D1, class D2> class RWTFunctorR2MImp;
template <class SR, class S1, class S2, class Callee, class DR, class D1, class D2, class A1> class RWTFunctorR2MA1Imp;
template <class SR, class S1, class S2, class Callee, class DR, class D1, class D2, class A1, class A2> class RWTFunctorR2MA2Imp;

#endif

#endif // __rw_functor_fwd_h__
