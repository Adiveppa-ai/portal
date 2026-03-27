#ifndef rw_factory_RWTFactory2Ctor_h_
#define rw_factory_RWTFactory2Ctor_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/factory/RWTFactory2Ctor.h#1 $
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
//--a constructor with two arguments.
//--The 'Result' template parameter is a pointer to a base class.
//--The 'Derived' template parameter is the derived class whose instance will
//--be created on the heap and returned as a base class pointer.
//--The 'Arg1' template parameter is the type for the first constructor argument.
//--The 'Arg2' template parameter is the type for the second constructor argument.
//--
//--Example:
//--#include <rw/factory/RWTFactory2.h>
//--#include <iostream.h>
//--
//--class Base {
//--  public:
//--    virtual ~Base(){;}
//--};
//--class Derived :public Base {
//--  public:
//--    Derived(int i,float f){
//--        cout << "Derived created\n"
//--             << i << endl
//--             << f << endl;}
//--};
//--typedef Base* (*BCreator)(int, float);
//--
//--int main(void)
//--{
//--   RWTFunctor<Base*(int, float)> derivedBuilder =
//--       RWTFactory2Ctor<Base*,Derived,int,float>::ctor;
//--
//--   RWTFactory2<Base*, RWCString, int, float> factory;
//--   factory.addCreator("Derived", derivedBuilder);
//--   Base * basePtr = factory.create("Derived", 1, 2.0f);
//--   delete basePtr;
//--   return 0;
//--}
//--


template <class Result, class Derived, class Arg1, class Arg2>
class RWTFactory2Ctor
{

public:

    //--Creates a derived class instance on the heap, returning its base class pointer.
    //--Param <arg1> The first argument for the constructor of the derived type.
    //--Param <arg2> The second argument for the constructor of the derived type.
    //--Returns <Result> The base class pointer of the constructed derived object.
    static Result ctor(Arg1 arg1, Arg2 arg2);
};


/****************************************************************************/

template <class Result, class Derived, class Arg1, class Arg2>
inline
Result RWTFactory2Ctor<Result, Derived, Arg1, Arg2>::ctor(Arg1 arg1, Arg2 arg2)
{
    return new Derived(arg1, arg2);
}

#endif // rw_factory_RWTFactory2Ctor_h_
