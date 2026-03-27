#ifndef BAS_KEYEDOBJECTPOOL_HPP
#define BAS_KEYEDOBJECTPOOL_HPP

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
/** @todo Should this be a registered object?
 *
 *	@todo Currently, a map is used for the active pool container. This
 *	      is to simplify things initially. Eventually, it will need to be
 *	      a hashmap, for the Timos lock manager. Will a hashmap be overkill
 *	      for DAT_Account use? If a map is better suited, could possibly
 *	      simplify the locking by using a single mutex for both the free pool
 *	      and active pool, instead of a mutex for each. 
 *
 *	@todo A pool is fixed size, i.e. no auto-growth is done if it gets
 *	      exhausted. Could be extended to support a "when exhausted" policy.
 */
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
// 10-Jun-2003  kbref				Containment of pools.
// 25-Feb-2004	Mitch Nelson		Added constructor with GrowStrategy
//
//=============================================================================

#ifndef BAS_KEYEDOBJECTPOOLOBJECT_HPP
  #include "BAS/KeyedObjectPoolObject.hpp"
#endif
#ifndef BAS_OBJECTPOOL_HPP
  #include "BAS/ObjectPool.hpp"
#endif
#ifndef BAS_LATCH_HPP
  #include "BAS/Latch.hpp"
#endif
#ifndef BAS_LOCKABLEMAP_HPP
  #include "BAS/LockableMap.hpp"
#endif

namespace BAS
{
	/** \class KeyedObjectPool<K, T> KeyedObjectPool.hpp "BAS/KeyedObjectPool.hpp"
 	 *  Generic key-based object pool, templatized on key type and the object 
 	 *	type being pooled. Does not grow nor shrink. Enforces one instance 
	 *	per key.
 	 */
	template <class K, class T>
	class KeyedObjectPool D_THREADINFO
	{
	D_THREADSAFE

	public:
		/** @name Public Typedefs */
		//@{
		/** The pool's key type.
	 	 */ 
		typedef K KeyType;

		/** The pool's object type.
	 	 */ 
		typedef T ObjectType;
		//@}

		/** @name Public Constructors */
		//@{
		/** Initializing constructor.  
	 	 *	Creates a new pool, populated with the specified number of 
		 *	instances.
	 	 *  @param size Total number of instances that are pooled.
	 	 */
		KeyedObjectPool(size_t size);

		/** Initializing constructor.  
	 	 *	Creates a new pool, populated with the specified number of 
		 *	instances and the specified growing strategy.
	 	 *  @param size Total number of instances that are pooled.
	 	 *  @param GrowingStrategy& Growing strategy for the pool.
	 	 */
		KeyedObjectPool(size_t size, BAS::GrowingStrategy& iGrowingStrategy);
		//@}


		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		virtual ~KeyedObjectPool();
		//@}

		/** @name Public Member Functions */
		//@{
		/** Get an instance from the pool for the specified key.
	 	 *	Throws a BAS_Status exception if the pool is exhausted.
	 	 *	@param key The key! 
	 	 *  @return An instance.
	 	 */
		virtual T& get(const K& key);

		/** Return an instance to the pool.
	 	 *	@param key Key of instance being returned.
	 	 */
		virtual void put(const K& key);

		/** Get the number of free instances.
	 	 *  @return Number of free instances.
	 	 */
		size_t numberFree() const;

		/** Get the number of active instances.
	 	 *  @return Number of active instances.
	 	 */
		size_t numberActive() const;

		//@}

	private:
		// Free pool (not guarded).
		typedef BAS::KeyedObjectPoolObject<T> PooledObject;
		BAS::ObjectPool<PooledObject, BAS::NullLatch> freePoolM;

		// Active pool.
		typedef BAS::LockableMap<K, PooledObject*, std::less<K> > ActivePool;
		ActivePool activePoolM;

		// Size of the pool - the total number of instances that are pooled.
		size_t sizeM;

		//
		// Disallow use.
		//
		KeyedObjectPool();
		KeyedObjectPool(const KeyedObjectPool& p);
		const KeyedObjectPool& operator=(const KeyedObjectPool& p);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/KeyedObjectPool.cpp"
#endif

#endif
