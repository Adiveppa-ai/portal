//=============================================================================
//
// Copyright (c) 2003, 2023, Oracle and/or its affiliates. 
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	Generic object pool. Templatized on object type.
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
// 29-May-2003  Keith Brefczynski	Created
// 10-Feb-2003  Mitch Nelson 		Added growth logic member and methods.
// 09-Dec-2004  Giles Douglas       Fixed irritating warnings
//=============================================================================

#ifndef BAS_OBJECTPOOL_HPP
  #include "BAS/ObjectPool.hpp"
#endif
#ifndef BAS_NOGROWINGSTRATEGY_HPP
  #include "BAS/NoGrowingStrategy.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_STATUS_HPP
  #include "BAS/Status.hpp"
#endif
 

template <class T, class L>
BAS::ObjectPool<T, L>::ObjectPool(size_t size) : 
	sizeM(0),
	growingStrategyM(new BAS::NoGrowingStrategy)
{
	D_ENTER("BAS::ObjectPool::ObjectPool(size_t size)");
	D_ARG(size);

	//
	// Populate the pool.
	//
	addNewInstances(size);
}

template <class T, class L>
BAS::ObjectPool<T, L>::ObjectPool(size_t size, BAS::GrowingStrategy& iGrowingStrategy) : 
	sizeM(0)
{
	D_ENTER("BAS::ObjectPool::ObjectPool(size_t size, BAS::GrowingStrategy& iGrowingStrategy)");
	D_ARG(size);
	D_ARG(iGrowingStrategy);

	//
	// Populate the pool.
	//
	addNewInstances(size);
	growingStrategyM = iGrowingStrategy.clone();
}

template <class T, class L>
BAS::ObjectPool<T, L>::~ObjectPool()
{
	D_ENTER("BAS::ObjectPool::~ObjectPool()");

	// All objects should have been returned to the pool!
	RWASSERT(poolM.entries() == sizeM);

	//
	// Destroy the pool's pointer entries and the objects they point to.
	// (clear() does not do the latter) 
	//
	for (size_t i = poolM.entries(); i != 0; i--)
	{
		delete poolM.pop();
	}
	poolM.clear();	// Sanity.
}

template <class T, class L>
T& 
BAS::ObjectPool<T, L>::get()
{
	D_ENTER("BAS::ObjectPool::get()");

	LockGuard lock(this->monitor());

	//
	// Check if the pool is exhausted. If so, throw an exception.
	//
	if (poolM.entries() == 0)
	{
		D_PRINT("pool is exhausted"); 

		size_t adds = growingStrategyM->growBy(sizeM);
		if (adds < 1) {
			throw BAS::Status("ERR_OBJECTPOOL_EXHAUSTED", BAS::Status::warning);
		}
		else {
			// Grow the pool.
			addNewInstances(adds);
		}

	}

	// 
	// Get an instance from the pool. 
	//
	T* object = poolM.pop();
	RWASSERT(object != 0);

	return *object;
}

template <class T, class L>
void 
BAS::ObjectPool<T, L>::put(T& object)
{
	D_ENTER("BAS::ObjectPool::put(T& object)");

	LockGuard lock(this->monitor());

	addInstance(&object);
}

template <class T, class L>
void
BAS::ObjectPool<T, L>::addInstance(T* object)
{
	D_ENTER("BAS::ObjectPool::addInstance(T* object)");

	poolM.push(object);	
}

template <class T, class L>
void
BAS::ObjectPool<T, L>::addNewInstances(size_t count)
{
	D_ENTER("BAS::ObjectPool::addNewInstances(size_t count)");
	D_ARG(count);

	for (size_t i = 0; i < count; i++)
	{
		addInstance(new T);
		++sizeM;
	}
}

template <class T, class L>
size_t 
BAS::ObjectPool<T, L>::numberFree() const
{
	D_ENTER("BAS::ObjectPool::numberFree()");

	LockGuard lock(this->monitor());

	return poolM.entries();
}

template <class T, class L>
size_t 
BAS::ObjectPool<T, L>::numberActive() const
{
	D_ENTER("BAS::ObjectPool::numberActive()");

	LockGuard lock(this->monitor());

	return sizeM - poolM.entries();
}

template <class T, class L>
void
BAS::ObjectPool<T, L>::incrementSize(size_t increment)
{
	D_ENTER("BAS::ObjectPool::incrementSize()");
	D_ARG(increment);
	
	LockGuard lock(this->monitor());

	sizeM += increment;
}
