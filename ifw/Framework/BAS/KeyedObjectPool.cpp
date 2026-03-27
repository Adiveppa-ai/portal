//=============================================================================
//
// Copyright (c) 2003, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	Generic key-based object pool. Templatized on key type and object type.
//	Does not grow nor shrink. Enforces one instance per key.
//
// Current Issues:
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Keith Brefczynski
// Backup-Responsible: Alan Lu
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 28-May-2003  Keith Brefczynski	Created
// 10-Jun-2003	kbref				Containment of pools
// 25-Feb-2004	Mitch Nelson		Added constructor with GrowStrategy
//
//=============================================================================

#ifndef BAS_KEYEDOBJECTPOOL_HPP
  #include "BAS/KeyedObjectPool.hpp"
#endif
#ifndef BAS_KEYEDLOCKGUARD_HPP
  #include "BAS/KeyedLockGuard.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif


template <class K, class T>
BAS::KeyedObjectPool<K, T>::KeyedObjectPool(size_t size) :
	sizeM(size),
	freePoolM(size)
{
	D_ENTER("BAS::KeyedObjectPool::KeyedObjectPool(size_t size)");
	D_ARG(size);
	RWPRECONDITION(size > 0);

	// Nothing else to do.
}

template <class K, class T>
BAS::KeyedObjectPool<K, T>::KeyedObjectPool(size_t size, BAS::GrowingStrategy& iGrowingStrategy) :
	sizeM(size),
	freePoolM(size, iGrowingStrategy)
{
	D_ENTER("BAS::KeyedObjectPool::KeyedObjectPool(size_t size, BAS::GrowingStrategy& iGrowingStrategy)");
	D_ARG(size);
	D_ARG(iGrowingStrategy);
	RWPRECONDITION(size > 0);

	// Nothing else to do.
}

template <class K, class T>
BAS::KeyedObjectPool<K, T>::~KeyedObjectPool()
{
	D_ENTER("BAS::KeyedObjectPool::~KeyedObjectPool()");
	RWPRECONDITION(activePoolM.entries() == 0);
}

template <class K, class T>
T& 
BAS::KeyedObjectPool<K, T>::get(const K& key) 
{
	D_ENTER("BAS::KeyedObjectPool::get(const K& key)");
	D_ARG(key);

	//
	// Lock the active pool for the given key.
	// This lock will also guard free pool access (ok since LockableMap
	//	is guarded with a single lock).
	//
	BAS::KeyedLockGuard<K, ActivePool> guard(key, activePoolM);

	//
	// Check if there is already an active object for this key. 
	// If so, add a reference to it to pin in the active pool until
	// we are done with it.
	//
	PooledObject* activeObjectHdl; 
	bool status = activePoolM.findValue(key, activeObjectHdl);
	if (status == true)
	{
		D_PRINT("active object found");

		activeObjectHdl->addReference();

		return activeObjectHdl->getObject();
	}
	D_PRINT("active object not found");

	//
	// If not, get one from the free pool
	//
	/** @todo The free pool throws an exception if the pool is exhausted.
	 *        May someday want to catch the exception and do auto-growth.
	 */	
	PooledObject& objectHdl = freePoolM.get();

	//
	// Set the key, and insert into the active pool.
	//
	status = activePoolM.insert(key, &objectHdl);

	// 'status' will be false only if the key was a duplicate, but that
	// should never happen since the findValue() above would have found it.
	RWASSERT(status == true);

	//
	// Add a reference to it to pin in the active pool until we are
	// done with it.
	//
	objectHdl.addReference();

	return objectHdl.getObject();
}

template <class K, class T>
void 
BAS::KeyedObjectPool<K, T>::put(const K& key)
{
	D_ENTER("BAS::KeyedObjectPool::put(const K& key)");
	D_ARG(key);

	// Object handle from active pool.
	PooledObject* activeObjectHdl;

	// No more outstanding references?
	bool noLongerActive;

	//
	// Lock the active pool for the given key.
	// This lock will also guard free pool access (ok since LockableMap
	// is guarded with a single lock).
	//
	BAS::KeyedLockGuard<K, ActivePool> guard(key, activePoolM);

	//
	// Find the active object for this key. 
	//
	typename ActivePool::Itr itr;
	bool status = activePoolM.find(key, itr);
	RWASSERT(status == true);

	activeObjectHdl = (*itr).second;

	//
	// Remove our reference to the object. If there are no outstanding
	// references, remove from the active pool.
	//
	noLongerActive = activeObjectHdl->removeReference();
	D_BARG(noLongerActive);

	//
	// If the object is no longer active, remove from active pool and
	// return it to the free pool.
	//
	if (noLongerActive == true)
	{
		activePoolM.remove(itr);
		freePoolM.put(*activeObjectHdl);
	}
}

template <class K, class T>
size_t 
BAS::KeyedObjectPool<K, T>::numberFree() const
{
	D_ENTER("BAS::KeyedObjectPool::numberFree()");

	return freePoolM.numberFree();
}

template <class K, class T>
size_t 
BAS::KeyedObjectPool<K, T>::numberActive() const
{
	D_ENTER("BAS::KeyedObjectPool::numberActive()");

	return freePoolM.numberActive();
}
