/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/RWTMRUCache.cc#1 $
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

#include <rw/internet/RWTMRUCache.h>

template < class Key, class T >
RWTMRUCache< Key, T >::RWTMRUCache(unsigned(*hash)(const Key&), size_t maxCount)
    : cachePool_(RWTHasher< Key >(hash))
    , maxCount_(maxCount)
{
}


template < class Key, class T >
typename RWTMRUCache< Key, T >::Guard
RWTMRUCache< Key, T >::get(const Key& key)
{
    RWTMRUCacheList< T > cacheList((RWTMRUCacheListImp<T>*)0);

    if (!cachePool_.findValue(key, cacheList)) {
        cacheList = RWTMRUCacheList< T > (maxCount_);
        cachePool_.insert(key, cacheList);
    }

    return RWTMRUCacheGuard< T > (cacheList.getNext());
}


template < class Key, class T >
void
RWTMRUCache< Key, T >::setMaxCount(size_t count)
{
    maxCount_ = count;

    typename RWTValHashDictionary< Key, RWTMRUCacheList< T >, RWTHasher<Key> >::const_iterator iter = cachePool_.begin();

    for (; iter != cachePool_.end(); ++iter) {
        RWTMRUCacheList< T > list = (*iter).second;
        list.setMaxCount(maxCount_);
    }

}


template < class Key, class T >
size_t
RWTMRUCache< Key, T >::getMaxCount(void) const
{
    return maxCount_;
}


template < class Key, class T >
void
RWTMRUCache< Key, T >::removeIfUnusedSince(const RWDateTime& date)
{
    typename RWTValHashDictionary< Key, RWTMRUCacheList< T >, RWTHasher<Key> >::const_iterator iter = cachePool_.begin();

    for (; iter != cachePool_.end(); ++iter) {
        List list = (*iter).second;
        list.removeIfUnusedSince(date);
    }
}


template < class T >
RWTMRUCacheItem< T >::RWTMRUCacheItem(const T& item, RWTMRUCacheListImp< T >* list)
    : access_(RWDateTime::now())
    , list_(list)
    , item_(item)
{}


template < class T >
T&
RWTMRUCacheItem< T >::getItem(void)
{
    return item_;
}


template < class T >
void
RWTMRUCacheItem< T >::setAccessTime(const RWDateTime& time)
{
    access_ = time;
}


template < class T >
RWDateTime
RWTMRUCacheItem< T >::getAccessTime(void) const
{
    return access_;
}


template < class T >
void
RWTMRUCacheItem< T >::returnToList(void)
{
    list_->add(this);
}

template < class T >
void
RWTMRUCacheItem< T >::removeFromList(void)
{
    list_->remove(this);
}


template < class T >
RWTMRUCacheGuard< T >::RWTMRUCacheGuard(RWTMRUCacheItem< T >* item)
    : item_(item), owner_(true)
{}


template < class T >
RWTMRUCacheGuard< T >::RWTMRUCacheGuard(const RWTMRUCacheGuard< T >& cref)
{
    RWTMRUCacheGuard< T >& ref = const_cast<RWTMRUCacheGuard< T >&>(cref);

    item_      = ref.item_;
    owner_     = ref.owner_;
    ref.owner_ = false;
}

template < class T >
RWTMRUCacheGuard< T >::~RWTMRUCacheGuard(void)
{
    if (owner_) {
        item_->setAccessTime(RWDateTime::now());
        item_->returnToList();
    }
}


template < class T >
T&
RWTMRUCacheGuard< T >::getItem(void)
{
    return item_->getItem();
}

template < class T >
void
RWTMRUCacheGuard< T >::abort(void)
{
    if (owner_) {
        item_->removeFromList();
        item_ = 0;
    }

    owner_ = false;
}


template < class T >
RWTMRUCacheListImp< T >::RWTMRUCacheListImp(size_t max)
    : available_(lock_)
    , current_(0)
    , max_(max)
{}

template < class T >
RWTMRUCacheListImp< T >::~RWTMRUCacheListImp(void)
{
    list_.clearAndDestroy();
}

template < class T >
RWTMRUCacheItem< T >*
RWTMRUCacheListImp< T >::getNext(void)
{
    RWMutexLock::LockGuard guard(lock_);

    while (list_.isEmpty() && (max_ != 0 && max_ <= current_)) {
        available_.wait();
    }

    Item* item = 0;

    if (!list_.isEmpty()) {
        item = list_.removeLast();
    }
    else {
        current_++;
        item = new Item(T(), this);
    }

    return item;
}

template < class T >
void
RWTMRUCacheListImp< T >::setMaxCount(size_t max)
{
    RWMutexLock::LockGuard guard(lock_);

    const size_t diff = max - max_;

    if (diff > 0) {
        available_.signalAll();
    }

    max_ = max;
}

template < class T >
void
RWTMRUCacheListImp< T >::add(Item* item)
{
    RWMutexLock::LockGuard guard(lock_);

    if (item != NULL) {
        if (current_ > max_) {
            current_--;
            delete item;
            return;
        }

        list_.insert(item);
        available_.signal();
    }
}

template < class T >
void
RWTMRUCacheListImp< T >::remove(Item* item)
{
    RWMutexLock::LockGuard guard(lock_);

    if (item != NULL) {
        current_--;
        delete item;

        available_.signal();
    }
}

template < class T >
void
RWTMRUCacheListImp< T >::removeIfUnusedSince(const RWDateTime& date)
{
    RWMutexLock::LockGuard guard(lock_);

    typename RWTPtrSlist<Item>::iterator iter = list_.begin();

    while (iter != list_.end()) {
        Item* temp = *iter;
        if (temp->getAccessTime() < date) {
            iter = list_.erase(iter);
            current_--;
            delete temp;
        }
        else {
            ++iter;
        }
    }
}
