#ifndef BAS_SPINLOCK_HPP
#define BAS_SPINLOCK_HPP

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
//  Spinlock primitive to provide for short, critical sections of code. 
//
// Current Issues:
//
//-----------------------------------------------------------------------------
//
// Group:              Platform
// Responsible:        Greg Olson
// Backup-Responsible: Keith Brefczynski
//
//-----------------------------------------------------------------------------
// Change Log
//-----------------------------------------------------------------------------
// Date         Name                Description
// -----------  ------------------  -------------------------------------------
// 07-Jun-2003  Greg Olson          Created
// 13-Nov-2003	Keith Brefczynski	Changed to RWMutexLock to get isAcquired()
// 13-Jan-2005  Giles Douglas       Rewrote
//
//=============================================================================

#ifndef _pin_os_locks_h_
  #include "pin_os_locks.h"
#endif
#ifndef BAS_LOCKIF_HPP
  #include "BAS/LockIf.hpp"
#endif

namespace BAS {
    /** SpinLock
     * SpinLock for lightweight mutual exclusion. Suited for very short 
     * critical sections 
     */

	class SpinLock : public LockIf
	{
	public:
		/** Constructor. Constructs a SpinLock.
		 * @param attr (optional) - Allows passing of a mutex attribute 
		 * so that optional characteristics of the latch can be set prior
		 * to latch creation. If set, this overrides any default behaviour 
		 * implemented in the latch
		 */
		SpinLock(spin_lock_attr_t* attr = 0);
		
		/** Destructor */
		~SpinLock();
		
		/** Acquire the mutex */
		void acquire();

		/** Release the mutex */
		void release();

		/** Acquire read lock. Not implemented, just gets a regular lock
		 */
		void acquireRead();

		/** Acquire write lock. Not implemented, just gets a regular lock
		 */
		void acquireWrite();
	private:
		spin_lock_type mutexM;
	};

	inline void
	SpinLock::acquire()
	{
	  spin_lock_acquire(&mutexM);
	}

	inline void
	SpinLock::release()
	{
	  spin_lock_release(&mutexM);
	}

	inline void
	SpinLock::acquireRead()
	{
		acquire();
	}
   
	inline void
	SpinLock::acquireWrite()
	{
		acquire();
	}

}

#endif
