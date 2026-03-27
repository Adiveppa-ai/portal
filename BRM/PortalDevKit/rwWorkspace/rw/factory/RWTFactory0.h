#ifndef rw_factory_RWTFactory0_h_
#define rw_factory_RWTFactory0_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/factory/RWTFactory0.h#1 $
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

#include <rw/factory/RWTFactory0Ctor.h>
#include <rw/factory/RWTFactoryRegistry.h>
#include <rw/factory/pkgdefs.h>
#include <rw/functor/RWTFunctor.h>

//--Implements the "Factory Method Pattern," using 'RWTFunctor' functors
//--as creators.
//--
//--The 'Result' template parameter must be a pointer to a base class type
//--whose derived instances will be created by the factory.
//--The 'Key' template parameter is the type of an index used to identify which
//--'Result' object should be created by the factory.
//--The 'Key' type must provide:
//--  -Well-defined copy semantics;
//--  -well-defined assignment semantics;
//--  -well-defined equality semantics;
//--  -A hash function with the signature: 'unsigned hash(const Key& a)'
//--that returns a suitable hash value for the object 'a'.
//--RWCString, RWDate, RWDateTime and RWWString all satisfy the above requirements.
//--If your factory's Key object is some other type, and doesn't provide the
//--needed hash function, you can still provide a global hash function by
//--specializing the RWTHashTraits<Key>::rwtHashTraits(const Key&) static
//--function. Refer to the RWTHashTraits class documentation for that.
//--
//--Example:
//--  #include <rw/factory/RWTFactory0.h>
//--  #include <rw/factory/RWTFactory0Ctor.h>
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
//--    D1() { cout << "D1" << endl; }
//--  };
//--
//--  class D2 :public Base {
//--    public:
//--     D2() { cout << "D2" << endl; };
//--  };
//--
//--  typedef Base* (*BCreator)();    // Signature for the functor
//--
//--  void main(void)
//-- {
//--   //Constructs a functor to call the D1 class constructor.
//--   RWTFunctor<Base*()> d1Builder = RWTFactory0Ctor<Base*,D1>::ctor;
//--
//--   //Constructs a functor to call the D2 class constructor.
//--   RWTFunctor<Base*()> d2Builder = RWTFactory0Ctor<Base*,D2>::ctor;
//--
//--   //Creates the factory.
//--   RWTFactory0<Base*, RWCString> factory;
//--
//--   //Registers the functors inside the factory.
//--   factory.addCreator("D1", d1Builder);
//--   factory.addCreator("D2", d2Builder);
//--
//--   //Creates objects.
//--   Base * ptr1 = factory.create("D1");
//--   Base * ptr2 = factory.create("D2");
//--
//--   //Releases memory.
//--   delete ptr1;
//--   delete ptr2;
//-- }
//--
//-- Output:
//--
//--  D1
//--  D2
//--


template <class Result, class Key>
class RWTFactory0 : public RWTFactoryRegistry<Key, RWTFunctor<Result()> >
{

public:
    //--The type of the factory.
    typedef RWTFactory0<Result, Key> factory_type;

    // types from base class
    typedef RWTFunctor<Result()> creator_type;
    typedef RWTFactoryRegistry<Key, creator_type>  factory_registry_type;

    //--Constructs an empty factory.
    RWTFactory0(void) {}

    //--Constructs and assigns a default 'creator' object to be used when the lookup key
    //--doesn't match any currently registered keys.
    //--'defaultCreator' is a functor handle of the type 'RWTFunctor<Result()>',
    //--which will be used by the factory to construct the derived 'Result' type.
    RWTFactory0(const creator_type&);

    //--Runs the creator functor identified by the key to create an instance on the heap
    //--returning its 'result' base class pointer.
    //--If a creator doesn't exist for the given key, then the default creator is used.
    //--If the default creator is not registered, then an 'RWTHRInternalError' exception is thrown.
    virtual Result create(const Key& key) const;

    //--The factory destructor.
    virtual ~RWTFactory0() {}
};


/*****************************************************************************/
template <class Result, class Key>
inline
RWTFactory0<Result, Key>::RWTFactory0(const creator_type& c)
    : factory_registry_type(c)
{
}

#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/factory/RWTFactory0.cc>
#endif

#endif // rw_factory_RWTFactory0_h_
