#ifndef rw_factory_RWTFactory0Ctor_h_
#define rw_factory_RWTFactory0Ctor_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/factory/RWTFactory0Ctor.h#1 $
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

#include <rw/factory/pkgdefs.h>

//--Helper class that works as proxy allowing a functor to call
//--a default constructor.
//--The 'Result' template parameter is a pointer to a base class.
//--The 'Derived' template parameter is the derived class whose instance will
//--be created on the heap and returned as a base class pointer.
//--
//--Example:
//--#include <rw/factory/RWTFactory0.h>
//--#include <iostream.h>
//--
//--class Base {
//--  public:
//--    virtual ~Base(){;}
//--};
//--
//--class Derived :public Base {
//--  public:
//--    Derived(){ cout << "Derived created" << endl;}
//--};
//--
//--typedef Base* (*BCreator)();
//--
//--
//--int main(void)
//--{
//--   RWTFunctor<Base*()> derivedBuilder =
//--       RWTFactory0Ctor<Base*,Derived>::ctor;
//--
//--   RWTFactory0<Base *, RWCString> factory;
//--   factory.addCreator("Derived", derivedBuilder);
//--   Base * basePtr = factory.create("Derived");
//--   delete basePtr;
//--   return 0;
//--}
//--


template <class Result, class Derived>
class RWTFactory0Ctor
{

public:

    //--Creates a derived class instance on the heap, returning its base class pointer.
    //--Returns <Result> - The base class pointer of the constructed derived object.
    static Result ctor();
};

/****************************************************************************/

template <class Result, class Derived>
inline
Result RWTFactory0Ctor<Result, Derived>::ctor()
{
    return new Derived;
}

#endif // rw_factory_RWTFactory0Ctor_h_
