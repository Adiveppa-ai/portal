#ifndef BAS_LOCKPOOL_HPP
#define BAS_LOCKPOOL_HPP

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
//	Specific type of key-based object pool for locks. Templatized on key
//	type and lock type.
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
// 23-May-2003  Keith Brefczynski	Created
// 25-Feb-2004  Mitch Neson 		Added constructor with GrowStrategy
//
//=============================================================================

#ifndef BAS_KEYEDOBJECTPOOL_HPP
  #include "BAS/KeyedObjectPool.hpp"
#endif


namespace BAS
{
	/** \class LockPool<K, L> LockPool.hpp "BAS/LockPool.hpp"
 	 *  A key-based object pool specifically for locks. Templatized on key type
 	 *	and lock type.
 	 */
	template <class K, class L>
	class LockPool : public BAS::KeyedObjectPool<K, L> D_THREADINFO_M
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
		typedef L LockType;
		//@}

		/** @name Public Constructors */
		//@{
		/*  Initializing constructor.  
	 	 *	Creates a new pool, populated with the specified number of locks.
	 	 *  @param size Total number of locks that are pooled.
	 	 */
		LockPool(size_t size);

		/*  Initializing constructor.  
	 	 *	Creates a new pool, populated with the specified number of locks
	         *      and the given growing strategy.
	 	 *  @param size Total number of locks that are pooled.
	 	 *  @param GrowingStrategy& Growing strategy for the pool.
	 	 */
		LockPool(size_t size, BAS::GrowingStrategy& iGrowingStrategy);
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor
	 	 */
		virtual ~LockPool();
		//@}

	private:
		//
		// Disallow use.
		//
		LockPool();
		LockPool(const LockPool& p);
		const LockPool& operator=(const LockPool& p);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/LockPool.cpp"
#endif

#endif
