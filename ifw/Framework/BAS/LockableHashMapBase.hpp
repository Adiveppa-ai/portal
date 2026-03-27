#ifndef BAS_LOCKABLEHASHMAPBASE_HPP
#define BAS_LOCKABLEHASHMAPBASE_HPP

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
//	Base class for lockable hashmap containers.
//
// Current Issues:
/** 
 *	@todo Currently the locking semantics are very simple - the entire
 *	      container is locked. This *may* be good enough since for the
 *	      cases when finer-granularity locking is required, a lockable 
 *	      hashmap be the better choice.
 */
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
// 10-Jun-2003  Keith Brefczynski	Created
//
//=============================================================================

#ifndef BAS_LOCKABLETABLE_HPP
  #include "BAS/LockableTable.hpp"
#endif


namespace BAS
{
	/** \class LockableHashMapBase<K, T, C> LockableHashMapBase.hpp "BAS/LockableHashMapBase.hpp"
 	 *  Base class for lockable hashmap containers.
 	 */
	template <class K, class T, class C> 
	class LockableHashMapBase : 
		public BAS::LockableTable<K, T, C> D_THREADINFO_M
	{
	D_NONTHREADSAFE

	protected:
		//
		// Standard constructor.  
		//
		LockableHashMapBase();

		//
		// Standard destructor
		//
		virtual ~LockableHashMapBase();

	private:
		//
		// Disallow use.
		//
		LockableHashMapBase(const LockableHashMapBase& h);
		const LockableHashMapBase& operator=(const LockableHashMapBase& h);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/LockableHashMapBase.cpp"
#endif

#endif
