#ifndef BAS_KEYEDLOCKGUARD_HPP
#define BAS_KEYEDLOCKGUARD_HPP

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
//	Generic lock guard for key-based locking of a resource.
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
// 27-May-2003  Keith Brefczynski	Created
//
//=============================================================================

namespace BAS
{
	/** \class KeyedLockGuard<K, T> KeyedLockGuard.hpp "BAS/KeyedLockGuard.hpp"
 	 *	Lock guard for key-based locking of a resource.
 	 *	The resource must provide 'acquire(key)' and 'release(key)' methods.
 	 */
	template <class K, class T>
	class KeyedLockGuard D_THREADINFO
	{
	D_NONTHREADSAFE

	public:
		/** @name Public Constructors */
		//@{
		/*  Initializing constructor.  
	 	 *	Acquires key-based lock on the given resource.
	 	 *  @param resource The lockable resource.
	 	 *	@param key The key to do locking with respect to. Must remain valid
	 	 *             for the lifetime of the guard.
	 	 */
		KeyedLockGuard(const K& key, T& resource);
		//@}

		/** @name Public Destructors */
		//@{
		/** Standard destructor.
	 	 *  Releases lock acquired at construction.
	 	 */
		~KeyedLockGuard();
		//@}

	private:
		// The key the locking is done with respect to. 
		const K& keyM;

		// The lockable resource.
		T& resourceM;	

		// Has the lock been acquired?
		bool acquiredM;

		//
		// Disallow use.
		//
		KeyedLockGuard();
		KeyedLockGuard(const KeyedLockGuard& g);
		const KeyedLockGuard& operator=(const KeyedLockGuard& g);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/KeyedLockGuard.cpp"
#endif

#endif
