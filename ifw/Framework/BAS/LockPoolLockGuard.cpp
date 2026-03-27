//=============================================================================
//
// Copyright (c) 2003 - 2007 Oracle. All rights reserved.
//
// This material is the confidential property of Oracle Corporation
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component: BAS
//-----------------------------------------------------------------------------
// Module Description:
//	Guard for "automatic" acquire/release of a lock from a LockPool.
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
// 31-May-2003  Keith Brefczynski   Created
// 10-Apr-2007  Bert McLellan       bug5983899 FIX VARIOUS PROBLEMS DISCOVERED
//                                  BY HP'S CODE_ADVISOR
//
//=============================================================================

#ifndef BAS_LOCKPOOLLOCKGUARD_HPP
  #include "BAS/LockPoolLockGuard.hpp"
#endif
#ifndef TRACE_HPP
  #include "BAS/Trace.hpp"
#endif
 

template <class Pool>
BAS::LockPoolLockGuard<Pool>::LockPoolLockGuard(
	const typename Pool::KeyType& key, Pool& lockPool) :
		keyM(key),
		lockPoolM(lockPool),
		lockM(lockPool.get(key)),
		gotLockFromPoolM(false),
		isAcquiredM(false)
{
	D_ENTER("BAS::LockPoolLockGuard::LockPoolLockGuard(const Pool::KeyType& key, Pool& lockPool");
	D_ARG(key);

	//
	// Fetch the lock from the pool (done during member init).
	//
	gotLockFromPoolM = true;

	//
	// Acquire the lock.
	//
	lockM.acquire();
	isAcquiredM = true;
}

template <class Pool>
BAS::LockPoolLockGuard<Pool>::~LockPoolLockGuard()
{
	D_ENTER("BAS::LockPoolLockGuard::~LockPoolLockGuard()");
	D_ARG(keyM);

	//
	// Release the lock.
	//
	if (isAcquiredM == true)
	{
		lockM.release();
	}

	//
	// Return lock back to the pool.
	//
	if (gotLockFromPoolM == true)
	{
		lockPoolM.put(keyM);
	}
}
