#ifndef BAS_OBJECTPOOL_HPP
#define BAS_OBJECTPOOL_HPP

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
//	Generic object pool. Templatized on object type and synchronization type.
//
// Current Issues:
/** @todo Should this be a registered object?
 *
 *	@todo The object pool itself contsructs the objects being pooled and
 *	      as such, uses the default ctor to do so. This will obviously
 *	      not be sufficient for all objects. One option would be to
 *	      have the user pass a proto instance which the pool then clones.
 *	      Another possibility is to force the user to populate the pool.
 *
 *  @todo The pool container is hardcoded to be a stack. May want
 *        to templatize on this container type to make generic. If so,
 *	      would likely need a common container interface + adaptors.
 *
 *	@todo A single physical pool is used - if this is too much of a hit on
 *	      concurrency, could move to multiple. 
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
// 23-May-2003  Keith Brefczynski	Created
// 10-Feb-2003  Mitch Nelson 		Added growth logic member and methods.
// 08-Apr-2004  kbref				Templatize on sync object.
//
//=============================================================================

#ifndef RW_TOOLS_TSTACK_H
  #include <rw/tstack.h>
#endif
#ifndef RW_TOOLS_TVDLIST_H
  #include <rw/tvdlist.h> 
#endif
#ifndef __rw_sync_RWTLockGuard_h__
  #include <rw/sync/RWTLockGuard.h>
#endif
#ifndef __rw_sync_RWTMonitor_h__
  #include <rw/sync/RWTMonitor.h> 
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
#ifndef BAS_LATCH_HPP
  #include "BAS/Latch.hpp"
#endif
#ifndef ONLYPOINTER_HPP
  #include "BAS/OnlyPointer.hpp"
#endif

namespace BAS
{
	class GrowingStrategy;

	/** \class ObjectPool<T, L> ObjectPool.hpp "BAS/ObjectPool.hpp"
 	 *  Generic object pool, templatized on the type being pooled, and
	 *	on the synchronization object type for guarding access to the pool. 
	 *	The default synchronization type is a latch.
 	 */
	template <class T, class L = BAS::Latch>
	class ObjectPool : public RWTMonitor<L> D_THREADINFO_M
	{
	D_THREADSAFE

	public:
		/** @name Typedefs */
		//@{
		/** \typedef ObjectType
		 *	Type of objects contained within. 
		 */
		typedef T ObjectType;
		//@}

		/** @name Public Constructors */
		//@{
		/*  Initializing constructor.  
	 	 *	Creates a new pool, populated with the specified number 
		 *	of instances.  Growing strategy defaulted to no growing.
	 	 *  @param size Total number of instances that are pooled.
	 	 */
		ObjectPool(size_t size);

		/*  Initializing constructor.  
	 	 *	Creates a new pool, populated with the specified number 
		 *	of instances, and the specified growing strategy.
	 	 *  @param size Total number of instances that are pooled.
	 	 *  @param GrowingStrategy& Grow strategy for the pool.
	 	 */
		ObjectPool(size_t size, BAS::GrowingStrategy& iGrowingStrategy);
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		virtual ~ObjectPool();
		//@}

		/** @name Public Member Functions */
		//@{
		/** Get an instance from the pool. 
	 	 *  Throws BAS::Status exception if the pool is exhausted.
	 	 *  @return An instance!
	 	 */
		virtual T& get();

		/** Return an instance to the pool.
	 	 *  @param object Instance to return.
	 	 */
		virtual void put(T& object);

		/** Get the number of free instances.
	 	 *  @return Number of free instances.
	 	 */
		size_t numberFree() const;

		/** Get the number of active instances.
	 	 *  @return Number of active instances.
	 	 */
		size_t numberActive() const;

		/** Increment sizeM of the pool.
		 *  @param increment default to 1
		 */
		void incrementSize(size_t increment = 1);

		//@}
	
	private:
		/**	\typedef LockGuard
		 *	Define our own since the hpux compiler chokes on picking it
		 *	up from the RWTMonitor class. 
		 */
		typedef RWTLockGuard< RWTMonitor<L> > LockGuard;

		// Size of the pool - the total number of instances that are pooled.
		size_t sizeM;

		// Grow logic of the pool - object telling the pool how to grow.
		BAS::OnlyPointer<BAS::GrowingStrategy> growingStrategyM;

		// The pool. The RWTStack is value-based so we store pointers in it
		// to minimize copy constructor overhead.
		RWTStack<T*, RWTValDlist<T*> > poolM;

		//
		// Add an instance to the pool. General purpose as it could be an 
		// instance being returned or a new instance.
		//
		void addInstance(T* object);

		//
		// Add the given number of *new* instances to the pool.
		//
		void addNewInstances(size_t count);

		//
		// Disallow use.
		//
		ObjectPool();
		ObjectPool(const ObjectPool& p);
		const ObjectPool& operator=(const ObjectPool& p);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/ObjectPool.cpp"
#endif

#endif
