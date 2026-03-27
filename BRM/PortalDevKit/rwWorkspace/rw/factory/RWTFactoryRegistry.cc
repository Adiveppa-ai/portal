/*********************************************************************
 *
 * $Id: //spro/rel2016.1/rw/factory/RWTFactoryRegistry.cc#1 $
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

#include <rw/factory/RWTFactoryRegistry.h>
#include <typeinfo>

template <class Key, class Creator>
RWTFactoryRegistry<Key, Creator>::RWTFactoryRegistry(void)
    :
    registry_(new RegistryMapType(RWTHasher<Key>(RWTHashTraits<Key>::rwtHashTraits))),
    isDefaultCreatorRegistered_(false)
{
}

template <class Key, class Creator>
RWTFactoryRegistry<Key, Creator>::RWTFactoryRegistry(const creator_type c)
    :
    registry_(new RegistryMapType(RWTHasher<Key>(RWTHashTraits<Key>::rwtHashTraits))),
    defaultCreator_(c),
    isDefaultCreatorRegistered_(false)
{
}

template <class Key, class Creator>
RWTFactoryRegistry<Key, Creator>::RWTFactoryRegistry(const RWTFactoryRegistry<Key, Creator>& other)
    :
    registry_(new RegistryMapType(*other.registry_)),
    defaultCreator_(other.defaultCreator_),
    isDefaultCreatorRegistered_(other.isDefaultCreatorRegistered_)
{
}

template <class Key, class Creator>
RWTFactoryRegistry<Key, Creator>&
RWTFactoryRegistry<Key, Creator>::operator=(const RWTFactoryRegistry<Key, Creator>& other)
{
    if (this == &other) {
        return *this;
    }
    registry_.reset(new RegistryMapType(*other.registry_));
    defaultCreator_ = other.defaultCreator_;
    isDefaultCreatorRegistered_ = other.isDefaultCreatorRegistered_;
    return *this;
}

template <class Key, class Creator>
bool
RWTFactoryRegistry<Key, Creator>::findCreator(const Key& key, creator_type& creator) const
{
    return registry_->findValue(key, creator);
}

template <class Key, class Creator>
bool
RWTFactoryRegistry<Key, Creator>::addCreator(const Key& key,
        const creator_type& creator)
{
    return registry_->insertKeyAndValue(key, creator);
}

template <class Key, class Creator>
bool
RWTFactoryRegistry<Key, Creator>::removeCreator(void)
{
    if (isDefaultCreatorRegistered_) {
        creator_type invalidCreator;
        defaultCreator_ = invalidCreator;
        isDefaultCreatorRegistered_ = false;
        return true;
    }
    else {
        return false;
    }
}
