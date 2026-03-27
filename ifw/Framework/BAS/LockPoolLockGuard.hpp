#ifndef BAS_LOCKPOOLLOCKGUARD_HPP
#define BAS_LOCKPOOLLOCKGUARD_HPP

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
//	Guard for auto-acquire/release of a lock from a LockPool.
//	This class is not thread-safe, and does not need to be.
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
//
//=============================================================================

#ifndef BAS_LOCKPOOL_HPP
  #include "BAS/LockPool.hpp"
#endif


namespace BAS
{
	/** \class LockPoolLockGuard<Pool> LockPoolLockGuard.hpp "BAS/LockPoolLockGuard.hpp"
 	*  Guard for auto-acquire/release of a lock from a lock pool.  
 	*	This class is not thread-safe, and does not need to be.
 	*/
	template <class Pool>
	class LockPoolLockGuard D_THREADINFO
	{
	D_NONTHREADSAFE

	public:
		/** @name Public Constructors */
		//@{
		/*  Initializing constructor.  
	 	 *	Gets a lock from the specified lock pool and then acquires it.
	 	 *	@param key The key to get a lock for. Must remain valid for the
	 	 *             lifetime of the guard.
	 	 *  @param lockPool The lock pool to get lock from.
	 	 */
		LockPoolLockGuard(const typename Pool::KeyType& key, Pool& lockPool);
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor.
	 	 *  Releases lock acquired at construction, and returns to lock pool.
	 	 */
		virtual ~LockPoolLockGuard();
		//@}

	private:
		// The key being locked. 
		const typename Pool::KeyType& keyM;

		// The lock we got from the pool.
		typename Pool::LockType& lockM;

		// Lock pool we got the lock from.
		Pool& lockPoolM;

		// Has the lock been fetch from the pool?
		bool gotLockFromPoolM;

		// Has the lock been acquired?
		bool isAcquiredM;

		//
		// Disallow use.
		//
		LockPoolLockGuard();
		LockPoolLockGuard(const LockPoolLockGuard& g);
		const LockPoolLockGuard& operator=(const LockPoolLockGuard& g);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/LockPoolLockGuard.cpp"
#endif

#endif
