#ifndef __rw_functor_functor_h__
#define __rw_functor_functor_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/functor/functor.h#1 $
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

/**************************************************************************
 *
 * Description:
 *
 * The include file for the entire functor package. Including this file
 * will pull in all public classes provided by the functor package.
 *
 *************************************************************************/

#include <rw/functor/RWCallbackScope.h>
#include <rw/functor/RWFunctor0.h>
#include <rw/functor/RWFunctor0Imp.h>
#include <rw/functor/RWTFunctor.h>
#include <rw/functor/RWTFunctor0GA1Imp.h>
#include <rw/functor/RWTFunctor0GA2Imp.h>
#include <rw/functor/RWTFunctor0GA3Imp.h>
#include <rw/functor/RWTFunctor0GImp.h>
#include <rw/functor/RWTFunctor0MA1Imp.h>
#include <rw/functor/RWTFunctor0MA2Imp.h>
#include <rw/functor/RWTFunctor0MA3Imp.h>
#include <rw/functor/RWTFunctor0MImp.h>
#include <rw/functor/RWTFunctor1.h>
#include <rw/functor/RWTFunctor1GA1Imp.h>
#include <rw/functor/RWTFunctor1GA2Imp.h>
#include <rw/functor/RWTFunctor1GImp.h>
#include <rw/functor/RWTFunctor1Imp.h>
#include <rw/functor/RWTFunctor1MA1Imp.h>
#include <rw/functor/RWTFunctor1MA2Imp.h>
#include <rw/functor/RWTFunctor1MImp.h>
#include <rw/functor/RWTFunctor2.h>
#include <rw/functor/RWTFunctor2GA1Imp.h>
#include <rw/functor/RWTFunctor2GA2Imp.h>
#include <rw/functor/RWTFunctor2GImp.h>
#include <rw/functor/RWTFunctor2Imp.h>
#include <rw/functor/RWTFunctor2MA1Imp.h>
#include <rw/functor/RWTFunctor2MA2Imp.h>
#include <rw/functor/RWTFunctor2MImp.h>
#include <rw/functor/RWTFunctorR0.h>
#include <rw/functor/RWTFunctorR0GA1Imp.h>
#include <rw/functor/RWTFunctorR0GA2Imp.h>
#include <rw/functor/RWTFunctorR0GA3Imp.h>
#include <rw/functor/RWTFunctorR0GImp.h>
#include <rw/functor/RWTFunctorR0Imp.h>
#include <rw/functor/RWTFunctorR0MA1Imp.h>
#include <rw/functor/RWTFunctorR0MA2Imp.h>
#include <rw/functor/RWTFunctorR0MA3Imp.h>
#include <rw/functor/RWTFunctorR0MImp.h>
#include <rw/functor/RWTFunctorR1.h>
#include <rw/functor/RWTFunctorR1GA1Imp.h>
#include <rw/functor/RWTFunctorR1GA2Imp.h>
#include <rw/functor/RWTFunctorR1GImp.h>
#include <rw/functor/RWTFunctorR1Imp.h>
#include <rw/functor/RWTFunctorR1MA1Imp.h>
#include <rw/functor/RWTFunctorR1MA2Imp.h>
#include <rw/functor/RWTFunctorR1MImp.h>
#include <rw/functor/RWTFunctorR2.h>
#include <rw/functor/RWTFunctorR2GA1Imp.h>
#include <rw/functor/RWTFunctorR2GA2Imp.h>
#include <rw/functor/RWTFunctorR2GImp.h>
#include <rw/functor/RWTFunctorR2Imp.h>
#include <rw/functor/RWTFunctorR2MA1Imp.h>
#include <rw/functor/RWTFunctorR2MA2Imp.h>
#include <rw/functor/RWTFunctorR2MImp.h>
#include <rw/functor/pkgdefs.h>
#include <rw/functor/rwBind.h>
#include <rw/functor/rwtMakeFunctor0.h>
#include <rw/functor/rwtMakeFunctor1.h>
#include <rw/functor/rwtMakeFunctor2.h>
#include <rw/functor/rwtMakeFunctorR0.h>
#include <rw/functor/rwtMakeFunctorR1.h>
#include <rw/functor/rwtMakeFunctorR2.h>


#endif // __rw_functor_functor_h__
