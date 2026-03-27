#ifndef rw_factory_RWTSingleFactory1_h_
#define rw_factory_RWTSingleFactory1_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/factory/RWTSingleFactory1.h#1 $
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

#include <rw/factory/RWTFactory1.h>
#include <rw/factory/pkgdefs.h>
#include <rw/pointer/RWTSingleton.h>

//--The 'RWTSingleFactory1' provides a singleton class interface to 'RWTFactory1'.
//--'RWTSingleFactory1' derives from 'RWTSingleton', which manages the C++ static
//--initialization issues associated with singleton classes.
//--
//--Example:
//--  #include <rw/factory/RWTSingleFactory1.h>
//--  #include <rw/factory/RWTFactory1Ctor.h>
//--  #include <rw/cstring.h>
//--  #include <iostream.h>
//--
//--  class Base {
//--  public:
//--    virtual ~Base(){;}
//--  };
//--
//--  class D1 :public Base {
//--   public:
//--    D1(int i) {cout << "D1=" << i << endl; }
//--  };
//--
//--  class D2 :public Base {
//--    public:
//--     D2(int i) { cout << "D2=" << i << endl; };
//--  };
//--
//--  typedef Base* (*BCreator)();    // Signature for the functor
//--
//--   //Creates singleton the factory.
//--  RWTCountingPointer<  RWTFactory1<Base*, RWCString, int> > factory =
//--      RWTSingleFactory1<Base*, RWCString, int>::instance();
//--
//-- int main(void)
//-- {
//--
//--   try {
//--   //Constructs a functor to call the D1 class constructor.
//--   RWTFunctor<Base*(int)> d1Builder = RWTFactory1Ctor<Base*,D1,int>::ctor;
//--
//--   //Constructs a functor to call the D2 class constructor.
//--   RWTFunctor<Base*(int)> d2Builder = RWTFactory1Ctor<Base*,D2,int>::ctor;
//--
//--   //Registers the functors inside the factory.
//--   factory->addCreator("D1", d1Builder);
//--   factory->addCreator("D2", d2Builder);
//--
//--   //Creates objects.
//--   Base * ptr1 = factory->create("D1", 10);
//--   Base * ptr2 = factory->create("D2", 20);
//--
//--   //Releases memory.
//--   delete ptr1;
//--   delete ptr2;
//--   }
//--   catch(const RWxmsg& msg) {
//--     cout << "Error:" << msg.why() << endl;
//--   }
//--   return 0;
//-- }
//--
//-- Output:
//--
//--  D1=10
//--  D2=20
//--
//--
//--See also 'RWTSingleton' and 'RWTFactory1'
//--
template<class Result, class Key, class Arg1>
class RWTSingleFactory1 : public RWTSingleton< RWTFactory1<Result, Key, Arg1> >
{
private:

    //Disables constructor. The only way to create an instance
    //is through the inherited static 'instance()' method.
    RWTSingleFactory1(void);
};

#endif // rw_factory_RWTSingleFactory1_h_
