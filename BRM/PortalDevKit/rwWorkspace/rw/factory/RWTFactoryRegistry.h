#ifndef rw_factory_RWTFactoryRegistry_h_
#define rw_factory_RWTFactoryRegistry_h_

/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/factory/RWTFactoryRegistry.h#1 $
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

#include <rw/factory/RWTHashTraits.h>
#include <rw/factory/pkgdefs.h>
#include <rw/pointer/RWTCountingPointer.h>
#include <rw/threxcept/RWTHRInternalError.h>
#include <rw/tvhdict.h>

//--'RWTFactoryRegistry' is a base class that provides the creator registry, indexed
//--by key. This class is used to provide the creator registry behavior to each of
//--the derived factory classes. Creators are classes that contains a factory method.
//--A factory method is a method that creates an instance.
//--Our factory classes use functors as creators to build instances.

template <class Key, class Creator>
class RWTFactoryRegistry
{

public:
    //--The type of the key object.
    typedef Key  key_type;
    //--The type of the hash function pointer.
    typedef unsigned(*hash_key_fn)(const Key&);
    //--The type of the creator object.
    typedef Creator  creator_type;
    //--The type fo the factory registry.
    typedef RWTFactoryRegistry<Key, Creator>  factory_registry_type;

    //--Constructs a factory registry.
    //Since the registry is based on 'RWTValHashDictionary', the template
    //'RWTHashTraits::rwtHashTraits()' is used to obtain a hash function for the key.
    //See 'RWTHashTraits.h' for more information.
    RWTFactoryRegistry(void);

    //--Constructs a factory registry assigning a default creator instance.
    //--This default creator is used when the lookup key doesn't match any currently
    //--added keys.
    //--Param <defaultCreator> - A default creator instance to be used when the
    //--lookup key doesn't match any currently added keys.
    RWTFactoryRegistry(const creator_type defaultCreator);

    //--Constructs a factory registry from another factory registry.
    RWTFactoryRegistry(const RWTFactoryRegistry<Key, Creator>& other);

    //--Assigns other factory registry to this factory registry.
    RWTFactoryRegistry<Key, Creator>& operator=(const RWTFactoryRegistry<Key, Creator>& other);

    //--Destroys the factory registry.
    virtual ~RWTFactoryRegistry() {}

    //--Registers a creator to the registry, associated with key.
    //--Returns 'true' if the creator is successfully added, and returns 'false' if not.
    //--A value of 'false' is returned if the key was previously registered.
    //--Param <key> - The creator identifier.
    bool addCreator(const Key& key, const creator_type& creator);

    //--Registers a default creator to be used when the key is not found when the
    //--factory is asked to create an object.
    //--Param <creator> - The default creator to be added.
    void defaultCreator(const creator_type creator);

    //--Returns the default creator. If the default creator is not registered,
    //--this function throws an 'RWTHRInternalError' exception.
    creator_type defaultCreator(void) const;

    //--Removes the creator associated with key from the registry.
    //--Returns 'true' if removed, and returns 'false' if the key given to be
    //--removed doesn't exist.
    bool removeCreator(const Key& key);

    //--Remove the default creator from the registry..
    //--Returns 'true' if removed, 'false' if no default creator exists.
    bool removeCreator(void);

    //--Check the registry for the existence of an entry for the key.
    //--Returns 'true' if exists an entry for the given key, otherwise returns 'false'.
    //--Param <key> the identifier for the creator whose existence will be checked.
    bool contains(const Key& key) const;

    //--Check the registry for the existence of a default creator.
    //--Returns 'true' if the default creator is registered, otherwise returns 'false'.
    bool contains(void) const;

    //--Returns 'true' if the factory registry contains a key which is equal to 'key' and
    //--puts the associated value into 'creator'. Otherwise, it returns 'false' and leaves
    //--creator untouched.
    bool findCreator(const Key& key, creator_type& creator) const;

    //--Accesses the internal hash dictionary table (an 'RWTValHashDictionary')
    //--and changes its number of buckets to the given size.
    //--The initial number of buckets in the table is equal to 'RW_DEFAULT_CAPACITY'.
    //--This value is '64'.
    //--See <RWTValHashDictionary> class in tools.h++ reference.
    //--Param <n> the new number of buckets.
    void resize(size_t n);

    //--Removes all creators from the registry including the defaultCreator.
    void clear(void);

    //--'RWRegistration' - A nested class that provides automatic registration and
    //--deregistration through its constructor and destructor.
    //--
    //--Example:
    //-- //the registration type
    //-- typedef RWTFactory0<Base*,RWCString>::RWRegistration Registration;
    //--  .
    //--  .
    //--  .
    //-- //register the creator functor with the "someDerived" key and
    //-- //deregister it when the reg object dies.
    //-- Registration reg(factory,"someDerived",creator);
    //--
    class RWRegistration
    {

    public:
        //--Registers a default creator to the given factory.
        //--Param <fact> a reference to 'RWTFactoryRegistry'
        //--Param <defaultCreator> the creator to be used when the lookup
        //--key doesn't match any currently added keys.
        RWRegistration(factory_registry_type& fact,
                       const creator_type& defaultCreator)
            : fact_(fact),
              default_(1),
              success_(0)
        {
            fact_.defaultCreator(defaultCreator);
        }

        //--Registers a creator to the given factory, associated with key.
        //--Param <fact> a reference to 'RWTFactoryRegistry'
        //--Param <key> - The creator identifier
        RWRegistration(factory_registry_type& fact,
                       const Key& key,
                       const creator_type& creator)
            : fact_(fact),
              key_(key),
              default_(0),
              success_(0)
        {
            success_ = fact_.addCreator(key_, creator) ? 1U : 0U;

        }

        //--Removes the creator registered in the constructor. It does not remove the default
        //--creator if registered.
        ~RWRegistration()
        {
            if (!default_ && success_) {
                fact_.removeCreator(key_);
            }
        }

    private:

        factory_registry_type& fact_;
        Key key_;

        unsigned default_: 1;
        unsigned success_: 1;
    };

protected:

    typedef RWTValHashMap<Key, creator_type, RWTHasher<Key>, std::equal_to<Key> > RegistryMapType;

    RWTScopedPointer<RegistryMapType> registry_;
    creator_type  defaultCreator_;
    bool isDefaultCreatorRegistered_;
};

/*****************************************************************************/


template <class Key, class Creator>
inline
void
RWTFactoryRegistry<Key, Creator>::defaultCreator(const creator_type c)
{
    defaultCreator_ = c;
    isDefaultCreatorRegistered_ = true;
}

template <class Key, class Creator>
inline
#if defined(__hpux)
Creator
#else
typename RWTFactoryRegistry<Key, Creator>::
creator_type
#endif
RWTFactoryRegistry<Key, Creator>::defaultCreator(void) const
{
    if (this->contains()) {
        return defaultCreator_;
    }
    else {
        throw RWTHRInternalError("Trying to obtain the default creator when none is set");
    }
}

template <class Key, class Creator>
inline
bool
RWTFactoryRegistry<Key, Creator>::contains(void) const
{
    return isDefaultCreatorRegistered_;
}


template <class Key, class Creator>
inline
bool
RWTFactoryRegistry<Key, Creator>::removeCreator(const Key& key)
{
    return registry_->remove(key);
}

template <class Key, class Creator>
inline
bool
RWTFactoryRegistry<Key, Creator>::contains(const Key& key) const
{
    return registry_->contains(key);
}

template <class Key, class Creator>
inline
void RWTFactoryRegistry<Key, Creator>::resize(size_t size)
{
    registry_->resize(size);
}

template <class Key, class Creator>
inline
void RWTFactoryRegistry<Key, Creator>::clear(void)
{
    registry_->clear();
    this->removeCreator();
}


#if defined(RW_NO_IMPLICIT_INCLUSION)
#  include <rw/factory/RWTFactoryRegistry.cc>
#endif

#endif // rw_factory_RWTFactoryRegistry_h_
