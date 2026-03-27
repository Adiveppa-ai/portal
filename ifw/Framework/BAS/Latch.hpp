#ifndef BAS_LATCH_HPP
#define BAS_LATCH_HPP

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
//	Latch for lightweight mutual exclusion. Suited for very short critical
//	sections with no system calls, lock acquisition, etc,
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
// 05-Jun-2003  Keith Brefczynski	Created
// 10-Jan-2005  Giles Douglas       Real 'latch'
//=============================================================================

#ifndef _pin_os_locks_h_
  #include "pin_os_locks.h"
#endif
#ifndef BAS_LOCKIF_HPP
  #include "BAS/LockIf.hpp"
#endif
#ifndef __rw_sync_RWNullMutexLock_h__
  #include <rw/sync/RWNullMutexLock.h>
#endif

namespace BAS
{
	/*
 	 *	Latch for lightweight mutual exclusion. Suited for very short critical
 	 *	sections with no system calls, lock acquisition, etc,
  	 */
	class Latch : public LockIf
	{
	public:
		/** Constructor. Constructs a Latch.
		 * @param attr (optional) - Allows passing of a mutex attribute 
		 * so that optional characteristics of the latch can be set prior
		 * to latch creation. If set, this overrides any default behaviour 
		 * implemented in the latch
		 */
		Latch(latch_attr_t* attr = 0);
		
		/** Destructor */
		~Latch();
		
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
	  latch_t mutexM;
	};

	inline void
	Latch::acquire()
	{
	  latch_acquire(&mutexM);
	}

	inline void
	Latch::release()
	{
	  latch_release(&mutexM);
	}

	inline void
	Latch::acquireRead()
	{
		acquire();
	}
   
	inline void
	Latch::acquireWrite()
	{
		acquire();
	}

	/** \typedef NullLatch
 	 *	A noop latch.
  	 */
	typedef RWNullMutexLock NullLatch;
}

#endif
