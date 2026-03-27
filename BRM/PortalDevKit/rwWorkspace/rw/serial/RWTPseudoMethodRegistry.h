#ifndef rw_serial_RWTPseudoMethodRegistry_h_
#define rw_serial_RWTPseudoMethodRegistry_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/serial/RWTPseudoMethodRegistry.h#1 $
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

#include <rw/serial/RWTypeInfo.h>
#include <rw/serial/pkgdefs.h>
#include <rw/pointer/RWTOnlyPointer.h>
#include <rw/tvhdict.h>
#include <new>

/**************************************************************************/

template <class T>
class RW_SERIAL_SUN_GLOBAL RWTPseudoMethodRegistryImp
{
public:

    typedef  T         method_type;
    typedef RWTypeInfo key_type;

    typedef
    RWTValHashDictionary<key_type, T> registry_type;

    // Accessor
    static registry_type*
    registry();

    // Initialization method
    static void
    init();

private:

    // Initialization method
    static void
    do_init();

private:

    static registry_type* registry_;

    static RWOnce initInstanceOnce_;

};

// Definition of static data members
template<class T>
/* static */ typename RWTPseudoMethodRegistryImp<T>::registry_type*
RWTPseudoMethodRegistryImp<T>::registry_ /* = 0 */;

template<class T>
/* static */ RWOnce
RWTPseudoMethodRegistryImp< T >::initInstanceOnce_ = RW_ONCE_INITIALIZER;

template<class T>
/* static */ void
RWTPseudoMethodRegistryImp<T>::do_init()
{
    RWTPseudoMethodRegistryImp<T>::registry_ = new(std::nothrow) registry_type;

    RW_ASSERT(registry_);
}

template<class T>
/* static */ void
RWTPseudoMethodRegistryImp<T>::init()
{
    initInstanceOnce_((void(*)())RWTPseudoMethodRegistryImp< T >::do_init);
}

template<class T>
typename RWTPseudoMethodRegistryImp<T>::registry_type*
RWTPseudoMethodRegistryImp<T>::registry()
{
    return registry_;
}

/**************************************************************************/

// Base for RWPseudoMethodRegistration
class RW_SERIAL_SUN_GLOBAL RWPseudoMethodRegistrationBase
{
public:
    virtual ~RWPseudoMethodRegistrationBase() { }
};


//--This template represents a base class for functions whose
//--behavior is specialized, based on the dynamic type (derived class) of
//--the first argument. This accomplishes the same thing as a virtual
//--method, but does not require anything to be added to the base class
//--declaration.

template <class Method>
class RW_SERIAL_SUN_GLOBAL RWTPseudoMethodRegistry
{

public:

    //--Accepted method types include members of the 'RWTFunctor' family
    //--of interfaces.
    typedef Method registered_method_type;

    typedef RWTypeInfo key_type;
    typedef RWTPseudoMethodRegistry<Method>  method_registry_type;

    typedef RWTValHashDictionary<key_type, Method> registry_type;

    //--'Ctor' takes an optional default method.
    RWTPseudoMethodRegistry(registered_method_type defaultMethod = NULL);

    //--
    virtual ~RWTPseudoMethodRegistry() {}

    /**********************************************************************/

    //--Associate method with 'key'.
    void registerMethod(key_type key, registered_method_type method);

    //--Disassociate method from 'key'.
    void unregisterMethod(key_type key);

    //--Get the method associated with 'key'.
    virtual registered_method_type
    getMethod(key_type key);

    //--See if 'key' is registered.
    bool contains(key_type key);

    /**********************************************************************/

    //--Set the default method.
    void defaultMethod(registered_method_type method)
    {
        defaultMethod_ = method;
    }

    //--Get the default method.
    registered_method_type  defaultMethod()
    {
        return defaultMethod;
    }

    /**********************************************************************/

    //--Class to support registration during static init. Used in
    //--'RW_REGISTER_PSEUDO_METHOD()' macro.
    class RW_SERIAL_SUN_GLOBAL Registration : public RWPseudoMethodRegistrationBase
    {
    public:
        Registration(method_registry_type& methodRegistry,
                     key_type key,
                     registered_method_type method)
            : methodRegistry_(methodRegistry),
              key_(key),
              isDefault_(0)
        {
            methodRegistry_.registerMethod(key_, method);
        }

        Registration(method_registry_type& methodRegistry,
                     registered_method_type method)
            : methodRegistry_(methodRegistry),
              isDefault_(1)
        {
            methodRegistry_.defaultMethod(method);
        }

        ~Registration()
        {
            if (!isDefault_) {
                methodRegistry_.unregisterMethod(key_);
            }
        }

    private:

        method_registry_type& methodRegistry_;

        key_type key_;

        int isDefault_;
    };

    RWPseudoMethodRegistrationBase*
    mkRegistration(key_type key, registered_method_type method);

protected:

    static void init()
    {
        // Call implementation init
        RWTPseudoMethodRegistryImp<Method>::init();
    }

    registered_method_type defaultMethod_;

};

/**************************************************************************/

template <class Method>
RWTPseudoMethodRegistry<Method>::RWTPseudoMethodRegistry(
    registered_method_type m)
    : defaultMethod_(m)
{
    init();
}

template <class Method>
typename
RWTPseudoMethodRegistry<Method>::registered_method_type
RWTPseudoMethodRegistry<Method>::getMethod(key_type key)
{
    init();

    registered_method_type result;

    if (!RWTPseudoMethodRegistryImp<Method>::registry()->
            findValue(key, result)) {
        result = defaultMethod_;
    }

    return result;
}

template <class Method>
void
RWTPseudoMethodRegistry<Method>::registerMethod(
    key_type key, registered_method_type method)
{
    init();
    RWTPseudoMethodRegistryImp<Method>::registry()->
    insertKeyAndValue(key, method);
}

template <class Method>
void
RWTPseudoMethodRegistry<Method>::unregisterMethod(key_type key)
{
    init();
    RWTPseudoMethodRegistryImp<Method>::registry()->remove(key);
}

template <class Method>
bool
RWTPseudoMethodRegistry<Method>::contains(key_type key)
{
    init();
    return RWTPseudoMethodRegistryImp<Method>::registry()->contains(key);
}

template <class Method>
RWPseudoMethodRegistrationBase*
RWTPseudoMethodRegistry<Method>::mkRegistration(
    key_type key, registered_method_type method)
{
    init();
    return new Registration(*this, key, method);
}

#endif // rw_serial_RWTPseudoMethodRegistry_h_
