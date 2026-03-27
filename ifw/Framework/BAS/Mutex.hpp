#ifndef BAS_MUTEX_HPP
#define BAS_MUTEX_HPP

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
//  Mutex primitive to provide for short, critical sections of code. 
//
// Current Issues:
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

#ifndef BAS_LOCKIF_HPP
  #include "BAS/LockIf.hpp"
#endif
#ifndef _pin_os_locks_h_
  #include "pin_os_locks.h"
#endif

namespace BAS 
{
	/** Portal's C++ mutex. This is a "always kernel" mutex, it does
	 * not spin at all
	 */
	class Mutex : public LockIf
	{
	public:
		/** Constructor. Constructs a mutex.
		 * @param attr (optional) - Allows passing of a mutex attribute 
		 * so that optional characteristics of the mutex can be set prior
		 * to mutex creation. If set, this overrides any default behaviour 
		 * implemented in the mutex, other than the no-spin option, which
		 * is always set.
		 */
		Mutex(real_mutex_attr_t* attr = 0);
		
		/** Destructor */
		~Mutex();
		
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
		real_mutex_t mutexM;
	};

	inline void
	Mutex::acquire()
	{
	  real_mutex_acquire(&mutexM);
	}

	inline void
	Mutex::release()
	{
	  real_mutex_release(&mutexM);
	}

	inline void
	Mutex::acquireRead()
	{
		acquire();
	}
   
	inline void
	Mutex::acquireWrite()
	{
		acquire();
	}
}

#endif
