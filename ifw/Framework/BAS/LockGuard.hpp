#ifndef BAS_LOCKGUARD_HPP
#define BAS_LOCKGUARD_HPP

//=============================================================================
//
// Copyright (c) 2005, 2009, Oracle and/or its affiliates. 
// All rights reserved. 
// This material is the confidential property of Oracle Corporation.
// or its subsidiaries or licensors and may be used, reproduced, stored
// or transmitted only in accordance with a valid Oracle license or
// sublicense agreement.
//
//-----------------------------------------------------------------------------
// Component:
//-----------------------------------------------------------------------------
// Module Description:
//  Lockguard primitive to provide for short, critical sections of code. 
//
// Current Issues:
/** @todo Defer to a RWLockguardLock for now.  Eventually we may want 
 *        to further investigate this for more optimal implementation.
 *        NOTE: This lockguard does not support recursion at this time.
 */
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Alan Lu
// Backup-Responsible: Keith Brefczynski
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 07-Jan-2005	Giles Douglas       Initial revision
//
//=============================================================================

namespace BAS 
{
	template<class L> class LockGuard
	{
	public:
		LockGuard(L& lock);
		~LockGuard();
	private:
		L& lockM;
	};

	template<class L>
	inline LockGuard<L>::LockGuard(L& lock) : lockM(lock)
	{
		lockM.acquire();
	}

	template<class L>
	inline LockGuard<L>::~LockGuard()
	{
		lockM.release();
	}
}

#endif
