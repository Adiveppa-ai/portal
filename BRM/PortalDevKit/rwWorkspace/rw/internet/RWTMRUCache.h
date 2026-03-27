#ifndef __rw_internet_RWTMRUCache_h__
#define __rw_internet_RWTMRUCache_h__
/**************************************************************************
 *
 * $Id: //spro/rel2016.1/rw/internet/RWTMRUCache.h#1 $
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

#include <rw/internet/pkgdefs.h>
#include <rw/sync/RWCondition.h>
#include <rw/sync/RWMutexLock.h>
#include <rw/tools/datetime.h>
#include <rw/tools/handlebody.h>
#include <rw/tpslist.h>
#include <rw/tvhdict.h>

template < class T > class RWTMRUCacheItem;
template < class T > class RWTMRUCacheGuard;
template < class T > class RWTMRUCacheList;
template < class T > class RWTMRUCacheListImp;

template < class T >
class RWTMRUCacheItem
{
public:
    RWTMRUCacheItem(const T& item, RWTMRUCacheListImp< T >* list);

    T& getItem(void);

    void       setAccessTime(const RWDateTime& time);
    RWDateTime getAccessTime(void) const;

    void returnToList(void);
    void removeFromList(void);

private:
    RWDateTime access_;
    RWTMRUCacheListImp< T >* list_;
    T item_;
};

template < class T >
class RWTMRUCacheGuard
{
public:
    typedef RWTMRUCacheItem< T >  Item;

    RWTMRUCacheGuard(Item*);
    RWTMRUCacheGuard(const RWTMRUCacheGuard<T>&);

    ~RWTMRUCacheGuard(void);

    T& getItem(void);

    void abort(void);

private:
    RWTMRUCacheGuard();

    Item* item_;
    bool  owner_;
};

template < class T >
class RWTMRUCacheListImp : public RWBody
{
public:
    typedef RWTMRUCacheItem< T >  Item;

    RWTMRUCacheListImp(size_t max);
    ~RWTMRUCacheListImp(void);

    Item* getNext(void);

    void setMaxCount(size_t max);

    void add(Item* item);
    void remove(Item* item);

    void removeIfUnusedSince(const RWDateTime& date);

private:

    RWTPtrSlist< Item > list_;
    RWMutexLock lock_;
    RWCondition available_;
    size_t current_;
    size_t max_;
};

template < class T >
class RWTMRUCacheList : public RWHandle
{
public:
    typedef RWTMRUCacheItem< T >  Item;

    RWTMRUCacheList(size_t max)
        : RWHandle(new RWTMRUCacheListImp< T >(max))
    {}

    RWTMRUCacheList(const RWTMRUCacheList< T >& second)
        : RWHandle(second)
    {}

    RWTMRUCacheList(RWTMRUCacheListImp< T >* imp = 0)
        : RWHandle(imp)
    {}


    Item* getNext(void)
    {
        return body().getNext();
    }

    void setMaxCount(size_t max)
    {
        body().setMaxCount(max);
    }

    void removeIfUnusedSince(const RWDateTime& date)
    {
        body().removeIfUnusedSince(date);
    }

protected:
    RWTMRUCacheListImp< T >& body(void)
    {
        return static_cast< RWTMRUCacheListImp< T >& >(RWHandle::body());
    }

    const RWTMRUCacheListImp< T >& body(void) const
    {
        return static_cast<const RWTMRUCacheListImp< T >& >(RWHandle::body());
    }
};

template < class Key, class T >
class RWTMRUCache
{
public:
    typedef RWTMRUCacheGuard< T >    Guard;

private:
    typedef RWTMRUCacheItem< T >     Item;
    typedef RWTMRUCacheList< T >     List;
    typedef RWTMRUCacheListImp< T >  ListImp;

public:
    RWTMRUCache(unsigned(*hash)(const Key&), size_t maxCount = 0);

    Guard get(const Key& key);

    void setMaxCount(size_t count);

    size_t getMaxCount(void) const;

    void removeIfUnusedSince(const RWDateTime& date);

private:
    RWTValHashDictionary< Key, List, RWTHasher<Key> > cachePool_;
    size_t maxCount_;
};


#ifdef RW_NO_IMPLICIT_INCLUSION
#  include <rw/internet/RWTMRUCache.cc>
#endif

#endif // __rw_internet_RWTMRUCache_h__
