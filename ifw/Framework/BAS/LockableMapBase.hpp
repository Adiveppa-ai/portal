#ifndef BAS_LOCKABLEMAPBASE_HPP
#define BAS_LOCKABLEMAPBASE_HPP

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
//	Base class for lockable map containers.
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
// 09-Jun-2003  Keith Brefczynski	Created
//
//=============================================================================

#ifndef BAS_LOCKABLETABLE_HPP
  #include "BAS/LockableTable.hpp"
#endif


namespace BAS
{
	/** \class LockableMapBase<K, T, C> LockableMapBase.hpp "BAS/LockableMapBase.hpp"
 	 *  Base class for lockable map containers.
 	 */
	template <class K, class T, class C> 
	class LockableMapBase : 
		public BAS::LockableTable<K, T, C> D_THREADINFO_M
	{
	D_NONTHREADSAFE

	protected:
		//
		// Standard constructor.  
		//
		LockableMapBase();

		//
		// Standard destructor
		//
		virtual ~LockableMapBase();

	private:
		//
		// Disallow use.
		//
		LockableMapBase(const LockableMapBase& h);
		const LockableMapBase& operator=(const LockableMapBase& h);
	};
}

#ifdef INC_TEMPL_DEFS
#include "BAS/LockableMapBase.cpp"
#endif

#endif
